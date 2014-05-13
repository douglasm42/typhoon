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

#include <video/video.h>

#include <base/Kin.h>

#include <video/Window.h>
#include <input/EventListener.h>

namespace cb {
	namespace video {
		KinLock(GLContextInfo);

		namespace gl {
			typedef enum Version {
				v21,
				v30,
				v33,
				v43
			} Version;
		}  // namespace gl

		class CbAPI GLContext : public input::WindowListener {
		private:
			Window *_window;
			kin::GLContextInfo _context_info;

			bool _vsync;
			gl::Version _version;

		public:
			GLContext(Window &iwindow, gl::Version iversion = gl::v43);
			virtual ~GLContext();

			void bind(Window &iwindow);
			void bind();
			void unbind();

			void swap();

			gl::Version version() const {return _version;}

			void vsync(bool ivsync);
			bool vsync() const {return _vsync;}

			void activate();

			void share(GLContext &iglcontext);

			virtual void onResize(size_t iwidth, size_t iheight);

			virtual void onActivate() {}
			virtual void onDeactivate() {}

			virtual void onCreate() {bind();}
			virtual void onDestroy() {unbind();}
		};
	}  // namespace video
}  // namespace cb
