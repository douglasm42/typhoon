/* 
 * - Cumulonimbus - ☁
 * File: gGLEWmx.cpp
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
#include <cb/graphic/GLEWmx.h>

#include <cb/base/Exception.h>

_thread_local cb::graphic::GLEWmxContext *_active = nullptr;

CbAPI GLEWContext *glewGetContext() {
	return &(_active->_context);
}

#ifdef CbWindows
	CbAPI WGLEWContext *wglewGetContext() {
		return &(_active->_wcontext);
	}
#endif

namespace cb {
	namespace graphic {
		GLEWmxContext::GLEWmxContext() {
		}

		GLEWmxContext::~GLEWmxContext() {
			deactivate();
		}

		void GLEWmxContext::activate() {
			_active = this;
		}

		void GLEWmxContext::deactivate() {
			_active = nullptr;
		}

		GLEWmxContext *GLEWmxContext::active() {
			return _active;
		}

		bool GLEWmxContext::isActive() const {
			return _active == this;
		}

		const char *glErrorStr(GLenum error) {
			switch(error) {
			case GL_NO_ERROR:
				return "GL_NO_ERROR";
			case GL_INVALID_ENUM:
				return "GL_INVALID_ENUM";
			case GL_INVALID_VALUE:
				return "GL_INVALID_VALUE";
			case GL_INVALID_OPERATION:
				return "GL_INVALID_OPERATION";
			case GL_STACK_OVERFLOW:
				return "GL_STACK_OVERFLOW";
			case GL_STACK_UNDERFLOW:
				return "GL_STACK_UNDERFLOW";
			case GL_OUT_OF_MEMORY:
				return "GL_OUT_OF_MEMORY";
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				return "GL_INVALID_FRAMEBUFFER_OPERATION";
			default:
				return "GL_UNKNOWN";
			}
		}

		const char *glErrorStrDescription(GLenum error) {
			switch(error) {
			case GL_NO_ERROR:
				return "No error has been recorded";
			case GL_INVALID_ENUM:
				return "An unacceptable value is specified for an enumerated argument";
			case GL_INVALID_VALUE:
				return "A numeric argument is out of range";
			case GL_INVALID_OPERATION:
				return "The specified operation is not allowed in the current state";
			case GL_STACK_OVERFLOW:
				return "An attempt has been made to perform an operation that would cause an internal stack to overflow";
			case GL_STACK_UNDERFLOW:
				return "An attempt has been made to perform an operation that would cause an internal stack to underflow";
			case GL_OUT_OF_MEMORY:
				return "There is not enough memory left to execute the command";
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				return "The framebuffer object is not complete";
			default:
				return "Unknown error code";
			}
		}
	}
}  // namespace cb
