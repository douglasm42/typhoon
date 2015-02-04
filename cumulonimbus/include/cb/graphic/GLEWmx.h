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

#include <cb/graphic/graphic.h>

#include <GL/glew.h>

#ifdef CbWindows
	#include <GL/wglew.h>
#endif

#include <GL/GL.h>
#include <GL/GLU.h>

#include <cb/base/Exception.h>

GLEWContext *glewGetContext();

#ifdef CbWindows
	WGLEWContext *wglewGetContext();
#endif

namespace cb {
	namespace graphic {
		class CbAPI GLEWmxContext {
		private:
			GLEWContext _context;

#			ifdef CbWindows
				WGLEWContext _wcontext;
#			endif

		public:
			GLEWmxContext();
			~GLEWmxContext();

			void activate();
			static void deactivate();

			static GLEWmxContext *active();
			bool isActive() const;

			friend GLEWContext *::glewGetContext();

#			ifdef CbWindows
				friend WGLEWContext *::wglewGetContext();
#			endif
		};

		const char *glErrorStr(GLenum error);
		const char *glErrorStrDescription(GLenum error);
	}  // namespace graphic
}  // namespace cb

#define glCheckError() {\
	GLenum error = glGetError();\
	switch(error) {\
	case GL_NO_ERROR:\
		return;\
	case GL_INVALID_ENUM:\
		Throw(cb::tokurei::GLInvalidEnum);\
	case GL_INVALID_VALUE:\
		Throw(cb::tokurei::GLInvalidValue);\
	case GL_INVALID_OPERATION:\
		Throw(cb::tokurei::GLInvalidOperation);\
	case GL_STACK_OVERFLOW:\
		Throw(cb::tokurei::GLStackOverflow);\
	case GL_STACK_UNDERFLOW:\
		Throw(cb::tokurei::GLStackUnderflow);\
	case GL_OUT_OF_MEMORY:\
		Throw(cb::tokurei::GLOutOfMemory);\
	case GL_INVALID_FRAMEBUFFER_OPERATION:\
		Throw(cb::tokurei::GLInvalidFramebufferOperation);\
	default:\
		ThrowDet(cb::tokurei::GLUnknown, "Error code: %p", error);\
	}\
}
