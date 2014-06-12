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

#include <graphic/graphic.h>

#include <base/Kin.h>

#include <video/Window.h>

#include <mutex>

namespace cb {
	namespace graphic {
		KinLock(GLContextInfo);

		enum class Version {
			v21,
			v30,
			v33,
			v43
		};

		class CbAPI GLContext {
		private:
			video::Window *_window;
			kin::GLContextInfo _context_info;

			bool _vsync;
			Version _version;

			GLContext(const GLContext &);

			std::recursive_mutex _active_guard;
			bool _is_active;

		public:
			GLContext(video::Window &iwindow, Version iversion = Version::v43);
			virtual ~GLContext();

			Version version() const {return _version;}

			void vsync(bool ivsync);
			bool vsync() const {return _vsync;}

			void activate();
			bool isActive() const;

			static void deactivate();
			static GLContext *active();

			void bind(video::Window &iwindow);
			void unbind();

			void swap();

			void share(GLContext &iglcontext);
		};
	}  // namespace graphic
}  // namespace cb
