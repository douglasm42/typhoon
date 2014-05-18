/* 
 * - Cumulonimbus - ☁
 * File: GLEWmx.h
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
#pragma once

#include <base/Setup.h>
#ifdef CbWindows

#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/GL.h>
#include <GL/GLU.h>

#define glewGetContext cb::opengl::GLEWmx::getGLEWContext
#define wglewGetContext cb::opengl::GLEWmx::getWGLEWContext

namespace cb {
	namespace opengl {
		class CbAPI GLEWmx {
		public:
			static GLEWContext *getGLEWContext();
			static WGLEWContext *getWGLEWContext();
			static void activate(GLEWContext *icontext, WGLEWContext *iwcontext);
		};
	}  // namespace opengl
}  // namespace cb

#endif
