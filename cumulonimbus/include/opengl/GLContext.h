/* 
 * - Cumulonimbus - ☁
 * File: GLContext.h
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

#include <opengl/opengl.h>

#include <base/Kin.h>

#include <video/Window.h>

namespace cb {
	namespace opengl {
		KinLock(GLContextInfo);

		namespace gl {
			typedef enum Version {
				v21,
				v30,
				v33,
				v43
			} Version;
		}  // namespace gl

		class CbAPI GLContext {
		private:
			video::Window *_window;
			kin::GLContextInfo _context_info;

			bool _vsync;
			gl::Version _version;

		public:
			GLContext(video::Window &iwindow, gl::Version iversion = gl::v43);
			GLContext(GLContext &icontext);
			virtual ~GLContext();

			gl::Version version() const {return _version;}

			void vsync(bool ivsync);
			bool vsync() const {return _vsync;}

			void activate();
			bool active();

			void bind(video::Window &iwindow);
			void unbind();

			void swap();

			void share(GLContext &iglcontext);
		};
	}  // namespace opengl
}  // namespace cb
