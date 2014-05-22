/* 
 * - Cumulonimbus - ☁
 * File: vwGLContext.cpp
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
#include <base/Setup.h>
#ifdef CbWindows

#include <opengl/GLContext.h>
#include <win32/opengl/GLEWmx.h>

#include <base/Exception.h>
#include <base/Log.h>

#include <video/Window.h>
#include <win32/video/Windows.h>
#include <win32/video/WindowInfo.h>

namespace cb {
	namespace opengl {
		class CbAPI w32GLContextInfo {
		public:
			HDC _device_context;
			HGLRC _opengl_context;
			GLEWContext _glew_context;
			WGLEWContext _wglew_context;
		};

		KinKey(video::kin::WindowInfo, video::w32WindowInfo);
		KinKey(kin::GLContextInfo, w32GLContextInfo);

		GLContext::GLContext(video::Window &iwindow, gl::Version iversion) {
			_context_info << new w32GLContextInfo;
			activate();
			_window = &iwindow;

			//Inicializa o device context para a criação do contexto do OpenGL.
			(*_context_info)._device_context = GetDC((*_window->info()).window);

			//Cria uma descrição de formato de pixel para a criação do contexto do OpenGL.
			PIXELFORMATDESCRIPTOR pixel_format;
			memset(&pixel_format, 0, sizeof(PIXELFORMATDESCRIPTOR));
			pixel_format.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			pixel_format.nVersion = 1;
			pixel_format.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
			pixel_format.iPixelType = PFD_TYPE_RGBA;
			pixel_format.cColorBits = 32;
			pixel_format.cDepthBits = 0;

			//Ativa e verifica se o formato de pixel escolhido é valido.
			int pixel_format_id = ChoosePixelFormat((*_context_info)._device_context, &pixel_format);
			if(pixel_format_id == 0) {
				char *lpMsgBuf;
				DWORD dw = GetLastError(); 

				FormatMessageA(
					FORMAT_MESSAGE_ALLOCATE_BUFFER | 
					FORMAT_MESSAGE_FROM_SYSTEM |
					FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL,
					dw,
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					(LPSTR)&lpMsgBuf,
					0, NULL );
				ThrowDet(tokurei::CreateError, "Error: %s", lpMsgBuf);
			}
			if(SetPixelFormat((*_context_info)._device_context, pixel_format_id, &pixel_format) == FALSE) {
				ThrowDet(tokurei::CreateError, "Error: %d", GetLastError());
			}

			//Cria e ativa o contexto do opengl primario.
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

			std::string version_name;
			//Prepara os atributos para a criação do contexto do OpenGL 2.1
			int attribs[] = {
				WGL_CONTEXT_MAJOR_VERSION_ARB, 0,
				WGL_CONTEXT_MINOR_VERSION_ARB, 0,
				WGL_CONTEXT_FLAGS_ARB, 0,
				0
			};

			//Seleciona a versão requisitada.
			if(GLEW_VERSION_4_3 && iversion >= gl::v43) {
				base::log.nothing("OpenGLContext::OpenGLContext() : OpenGL 4.3 e GLSL 4.30 escolhidos.");
				attribs[1] = 4;
				attribs[3] = 3;
				version_name = "OpenGL 4.3 - GLSL 4.30";
				_version = gl::v43;
			} else if(GLEW_VERSION_3_3 && iversion >= gl::v33) {
				base::log.nothing("OpenGLContext::OpenGLContext() : OpenGL 3.3 e GLSL 3.30 escolhidos.");
				attribs[1] = 3;
				attribs[3] = 3;
				version_name = "OpenGL 3.3 - GLSL 3.30";
				_version = gl::v33;
			} else if(GLEW_VERSION_3_0 && iversion >= gl::v30) {
				base::log.nothing("OpenGLContext::OpenGLContext() : OpenGL 3.0 e GLSL 1.30 escolhidos.");
				attribs[1] = 3;
				attribs[3] = 0;
				version_name = "OpenGL 3.0 - GLSL 1.30";
				_version = gl::v30;
			} else if(GLEW_VERSION_2_1 && iversion >= gl::v21) {
				base::log.nothing("OpenGLContext::OpenGLContext() : OpenGL 2.1 e GLSL 1.20 escolhidos.");
				attribs[1] = 2;
				attribs[3] = 1;
				version_name = "OpenGL 2.1 - GLSL 1.20";
				_version = gl::v21;
			} else {
				//Exceção lançada caso nenhuma versão suportada estiver disponivel.
				Throw(tokurei::CreateError);
			}

			//Verifica se a criação de contextos de versões específicas está disponivel.
			if(WGLEW_ARB_create_context) {
				//Cria o contexto específico e substitui o antigo contexto.
				HGLRC temp = (*_context_info)._opengl_context;
				(*_context_info)._opengl_context = wglCreateContextAttribsARB((*_context_info)._device_context, 0, attribs);
				wglMakeCurrent(NULL, NULL);
				wglDeleteContext(temp);
				wglMakeCurrent((*_context_info)._device_context, (*_context_info)._opengl_context);

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
				base::log.nothing("OpenGLContext::OpenGLContext() : Contexto OpenGL não foi possivel criar o contexto específico.");
			}
		}

		GLContext::~GLContext() {
			unbind();
			wglDeleteContext((*_context_info)._opengl_context);

			delete &_context_info;
		}

		void GLContext::bind(video::Window &iwindow) {
			if(_window) {
				unbind();
			}

			_window = &iwindow;
			(*_context_info)._device_context = GetDC((*_window->info()).window);
			wglMakeCurrent((*_context_info)._device_context, (*_context_info)._opengl_context);
		}

		void GLContext::unbind() {
			if(_window) {
				(*_context_info)._device_context = nullptr;
				_window = nullptr;
				if(active()) {
					activate();
				}
			}
		}

		void GLContext::swap() {
			activate();
			video::win::Placement p = _window->placement();

			glViewport(0, 0, p.width(), p.height());

			glClearColor(0.2f, 0.3f, 0.7f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

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
			if((*_context_info)._device_context) {
				GLEWmx::activate(&(*_context_info)._glew_context, &(*_context_info)._wglew_context);
				wglMakeCurrent((*_context_info)._device_context, (*_context_info)._opengl_context);
			} else {
				GLEWmx::activate(nullptr, nullptr);
				wglMakeCurrent(nullptr, nullptr);
			}
		}

		bool GLContext::active() {
			return GLEWmx::getGLEWContext() == (&(*_context_info)._glew_context);
		}

		void GLContext::share(GLContext &iglcontext) {
			wglShareLists((*_context_info)._opengl_context, (*iglcontext._context_info)._opengl_context);
		}
	}  // namespace opengl
}  // namespace cb

#endif
