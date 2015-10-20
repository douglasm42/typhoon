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
#include <cb/graphic/GLContext.hpp>
#include <cb/graphic/PixelFormat.hpp>
#include <cb/graphic/DummyGLContext.hpp>

#include <cb/base/Exception.hpp>
#include <cb/base/Log.hpp>

#include <cb/video/Window.hpp>
#include <cb/video/win32/Windows.hpp>

namespace cb {
	namespace graphic {
		_thread_local GLContext *_active_context = nullptr;

		GLContext::GLContext(video::Window &iwindow, Version iversion) {
			_is_active = false;

			_window = &iwindow;

			//Inicializa o device context para a criação do contexto do OpenGL.
			_w_device_context = GetDC(_window->wGetHWND());

			DummyGLContext *dummy = new DummyGLContext;

			PixelFormat pf(ColorBits::c24, AlphaBits::c8, DepthBits::d24, true, true, 4);
			pf.validate();

			_window->setPixelFormat(pf);

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

				_w_opengl_context = wglCreateContextAttribsARB(_w_device_context, 0, attribs);
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

				_w_opengl_context = wglCreateContext(_w_device_context);
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
			unbind();
			wglDeleteContext(_w_opengl_context);
		}

		void GLContext::bind(video::Window &iwindow) {
			if(_active_guard.try_lock()) {
				if(_window) {
					unbind();
				}

				_window = &iwindow;
				_w_device_context = GetDC(_window->wGetHWND());

				activate();

				//Inicializa a GLEW
				if(glewInit() != GLEW_OK) {
					Throw(tokurei::BindFailed);
				}

				//Inicializa a WGLEW
				if(wglewInit() != GLEW_OK) {
					Throw(tokurei::BindFailed);
				}
				_active_guard.unlock();
			} else {
				Throw(tokurei::BindFailed);
			}
		}

		void GLContext::unbind() {
			if(_active_guard.try_lock()) {
				if(_window) {
					_w_device_context = nullptr;
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
			SwapBuffers(_w_device_context);
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
				if(_w_device_context) {
					deactivate();

					_active_guard.lock();

					_glewmx_context.activate();

					_active_context = this;
					_is_active = true;

					wglMakeCurrent(_w_device_context, _w_opengl_context);
				} else {
					Throw(tokurei::ActivateFailed);
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

				GLEWmxContext::deactivate();

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
			wglShareLists(_w_opengl_context, iglcontext._w_opengl_context);
		}
	}  // namespace graphic
}  // namespace cb
