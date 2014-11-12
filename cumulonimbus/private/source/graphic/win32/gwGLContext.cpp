/* 
 * - Cumulonimbus - ☁
 * File: gwContext.cpp
 * 
 * Licence:
 * ============================================================================
 * Copyright (C) Staff 42 Entertainment LTDA ME - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * 
 * Written by Douglas Machado de Freitas <douglas@staff42.com>, May 2014
 * ============================================================================
 */
#include <cb/graphic/GLContext.h>
#include <graphic/GLEWmx.h>
#include <cb/graphic/PixelFormat.h>

#include <cb/base/Exception.h>
#include <cb/base/Log.h>

#include <cb/video/Window.h>
#include <video/win32/Windows.h>
#include <video/win32/WindowInfo.h>

namespace cb {
	namespace graphic {
		_thread_local GLContext *_active_context = nullptr;

		class CbAPI w32GLContextInfo {
		public:
			HDC _device_context;
			HGLRC _opengl_context;
			GLEWContext _glew_context;
			WGLEWContext _wglew_context;
		};

		KinKey(video::kin::WindowInfo, video::w32WindowInfo);
		KinKey(kin::GLContextInfo, w32GLContextInfo);

		GLContext::GLContext() {
			_context_info << new w32GLContextInfo;
			_dummy = true;
			_is_active = false;

			_window = new video::Window;

			//Inicializa o device context para a criação do contexto do OpenGL.
			(*_context_info)._device_context = GetDC((*_window->info()).window);

			PixelFormat pf(*_window, BPP::c32, Depth::d24, true);
			pf.set(*_window);

			//Cria e ativa o contexto do graphic primario.
			(*_context_info)._opengl_context = wglCreateContext((*_context_info)._device_context);
			activate();

			//Inicializa a GLEW
			if(glewInit() != GLEW_OK) {
				Throw(tokurei::CreateError);
			}

			//Inicializa a WGLEW
			if(wglewInit() != GLEW_OK) {
				Throw(tokurei::CreateError);
			}
		}

		GLContext::GLContext(video::Window &iwindow, Version iversion) {
			_context_info << new w32GLContextInfo;
			_dummy = false;
			_is_active = false;

			_window = &iwindow;

			//Inicializa o device context para a criação do contexto do OpenGL.
			(*_context_info)._device_context = GetDC((*_window->info()).window);

			GLContext *dummy = new GLContext;

			PixelFormat pf(iwindow, BPP::c32, Depth::d24, true, true, 8);
			pf.set(iwindow);

			//Verifica se a criação de contextos de versões específicas está disponivel.
			if(WGLEW_ARB_create_context) {
				std::string version_name;
				//Prepara os atributos para a criação do contexto do OpenGL 2.1
				int attribs[] = {
					WGL_CONTEXT_MAJOR_VERSION_ARB, 0,
					WGL_CONTEXT_MINOR_VERSION_ARB, 0,
					WGL_CONTEXT_FLAGS_ARB, 0,
					0
				};

				//Seleciona a versão requisitada.
				if(GLEW_VERSION_4_3 && iversion >= Version::v43) {
					base::log.nothing("OpenGLContext::OpenGLContext() : OpenGL 4.3 e GLSL 4.30 escolhidos.");
					attribs[1] = 4;
					attribs[3] = 3;
					version_name = "OpenGL 4.3 - GLSL 4.30";
					_version = Version::v43;
				} else if(GLEW_VERSION_3_3 && iversion >= Version::v33) {
					base::log.nothing("OpenGLContext::OpenGLContext() : OpenGL 3.3 e GLSL 3.30 escolhidos.");
					attribs[1] = 3;
					attribs[3] = 3;
					version_name = "OpenGL 3.3 - GLSL 3.30";
					_version = Version::v33;
				} else if(GLEW_VERSION_3_0 && iversion >= Version::v30) {
					base::log.nothing("OpenGLContext::OpenGLContext() : OpenGL 3.0 e GLSL 1.30 escolhidos.");
					attribs[1] = 3;
					attribs[3] = 0;
					version_name = "OpenGL 3.0 - GLSL 1.30";
					_version = Version::v30;
				} else if(GLEW_VERSION_2_1 && iversion >= Version::v21) {
					base::log.nothing("OpenGLContext::OpenGLContext() : OpenGL 2.1 e GLSL 1.20 escolhidos.");
					attribs[1] = 2;
					attribs[3] = 1;
					version_name = "OpenGL 2.1 - GLSL 1.20";
					_version = Version::v21;
				} else {
					//Exceção lançada caso nenhuma versão suportada estiver disponivel.
					Throw(tokurei::CreateError);
				}

				(*_context_info)._opengl_context = wglCreateContextAttribsARB((*_context_info)._device_context, 0, attribs);
				delete dummy;
				activate();

				//Inicializa a GLEW
				if(glewInit() != GLEW_OK) {
					Throw(tokurei::CreateError);
				}

				//Inicializa a WGLEW
				if(wglewInit() != GLEW_OK) {
					Throw(tokurei::CreateError);
				}

				base::log.nothing("OpenGLContext::OpenGLContext() : Contexto OpenGL criado: %s", version_name.c_str());
			} else {
				delete dummy;

				_version = Version::Legacy;

				(*_context_info)._opengl_context = wglCreateContext((*_context_info)._device_context);
				activate();

				//Inicializa a GLEW
				if(glewInit() != GLEW_OK) {
					Throw(tokurei::CreateError);
				}

				//Inicializa a WGLEW
				if(wglewInit() != GLEW_OK) {
					Throw(tokurei::CreateError);
				}

				base::log.nothing("OpenGLContext::OpenGLContext() : Contexto OpenGL não foi possivel criar o contexto específico.");
			}
		}

		GLContext::~GLContext() {
			video::Window *win = _window;
			unbind();
			wglDeleteContext((*_context_info)._opengl_context);
			if(_dummy) {
				delete win;
			}
			delete &_context_info;
		}

		void GLContext::bind(video::Window &iwindow) {
			if(_active_guard.try_lock()) {
				if(_window) {
					unbind();
				}

				_window = &iwindow;
				(*_context_info)._device_context = GetDC((*_window->info()).window);
				if(isActive()) {
					deactivate();
					activate();
				}
				_active_guard.unlock();
			} else {
				Throw(tokurei::BindFailed);
			}
		}

		void GLContext::unbind() {
			if(_active_guard.try_lock()) {
				if(_window) {
					(*_context_info)._device_context = nullptr;
					_window = nullptr;
					if(isActive()) {
						deactivate();
					}
				}

				_active_guard.unlock();
			} else {
				Throw(tokurei::UnbindFailed);
			}
		}

		void GLContext::swap() {
			SwapBuffers((*_context_info)._device_context);
		}

		void GLContext::vsync(bool ivsync) {
			activate();
			if(_vsync != ivsync) {
				_vsync = ivsync;
				if(WGLEW_EXT_swap_control) {
					wglSwapIntervalEXT(_vsync?1:0);
					base::log.nothing("GLContext::vsync() : VSYNC ativado.");
				} else {
					base::log.nothing("GLContext::vsync() : VSYNC não disponivel.");
				}
			}
		}

		void GLContext::activate() {
			if(_active_guard.try_lock()) {
				if((*_context_info)._device_context) {
					deactivate();

					_active_guard.lock();

					activateGLEW(&(*_context_info)._glew_context);
					activateWGLEW(&(*_context_info)._wglew_context);
					_active_context = this;
					_is_active = true;

					wglMakeCurrent((*_context_info)._device_context, (*_context_info)._opengl_context);
				} else {

				}

				_active_guard.unlock();
			} else {
				Throw(tokurei::ActivateFailed);
			}
		}

		void GLContext::deactivate() {
			if(_active_context) {
				_active_context->_active_guard.unlock();
				_active_context->_is_active = false;

				activateGLEW(nullptr);
				activateWGLEW(nullptr);
				_active_context = nullptr;

				wglMakeCurrent(nullptr, nullptr);
			}
		}

		GLContext *GLContext::active() {
			return _active_context;
		}

		bool GLContext::isActive() const {
			return _is_active;
		}

		void GLContext::share(GLContext &iglcontext) {
			wglShareLists((*_context_info)._opengl_context, (*iglcontext._context_info)._opengl_context);
		}
	}  // namespace graphic
}  // namespace cb
