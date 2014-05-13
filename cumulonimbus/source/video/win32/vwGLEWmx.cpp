/* 
 * - Cumulonimbus - ☁
 * File: vwGLEWmx.cpp
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

#include <video/win32/GLEWmx.h>
#include <base/Exception.h>

namespace cb {
	namespace video {
#ifdef _MSC_VER
		__declspec(thread) GLEWContext *_context = nullptr;
		__declspec(thread) WGLEWContext *_wcontext = nullptr;
#elif defined __MINGW32__
		__thread GLEWContext *GLEWmx::_context = nullptr;
		__thread WGLEWContext *GLEWmx::_wcontext = nullptr;
#else
		__thread GLEWContext *GLEWmx::_context = nullptr;
		__thread WGLEWContext *GLEWmx::_wcontext = nullptr;
#endif
		GLEWContext *GLEWmx::getGLEWContext() {
			return _context;
		}

		WGLEWContext *GLEWmx::getWGLEWContext() {
			return _wcontext;
		}

		void GLEWmx::activate(GLEWContext *icontext, WGLEWContext *iwcontext) {
			_context = icontext;
			_wcontext = iwcontext;
		}
	}  // namespace video
}  // namespace cb

#endif
