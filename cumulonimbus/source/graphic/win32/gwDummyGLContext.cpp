/* 
 * - Cumulonimbus - ☁
 * File: gwDummyGLContext.cpp
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
#include <cb/graphic/DummyGLContext.h>

#include <cb/video/win32/WindowStyle.h>

namespace cb {
	namespace graphic {
		DummyGLContext::DummyGLContext() {
			_w_device_context = GetDC(_window.wGetHWND());

			PIXELFORMATDESCRIPTOR pfd;
			memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
			pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			pfd.nVersion = 1;
			pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
			pfd.iPixelType = PFD_TYPE_RGBA;
			pfd.cColorBits = 32;
			pfd.cDepthBits = 16;

			int pixel_format_id = ChoosePixelFormat(_w_device_context, &pfd);
			if(pixel_format_id == 0) {
				Throw(tokurei::CreateError);
			}
			if(SetPixelFormat(_w_device_context, pixel_format_id, &pfd) == FALSE) {
				ThrowDet(tokurei::CreateError, "Error: %d", GetLastError());
			}

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
		}

		DummyGLContext::~DummyGLContext() {
			if(isActive()) {
				wglMakeCurrent(nullptr, nullptr);
				_glewmx_context.deactivate();
			}
		}

		void DummyGLContext::activate() {
			_glewmx_context.activate();
			wglMakeCurrent(_w_device_context, _w_opengl_context);
		}

		bool DummyGLContext::isActive() const {
			return _glewmx_context.isActive();
		}
	}  // namespace graphic
}  // namespace cb
