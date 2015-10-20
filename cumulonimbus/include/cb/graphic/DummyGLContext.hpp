/* 
 * - Cumulonimbus - ☁
 * File: DummyGLContext.h
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

#include <cb/graphic/graphic.hpp>

#include <cb/graphic/GLEWmx.hpp>

#ifdef CbWindows
#	include <cb/video/win32/Windows.hpp>
#endif

#include <cb/video/DummyWindow.hpp>

namespace cb {
	namespace graphic {
		class CbAPI DummyGLContext {
		private:
			GLEWmxContext _glewmx_context;
			video::DummyWindow _window;

#			ifdef CbWindows
				HDC _w_device_context;
				HGLRC _w_opengl_context;
#			endif

		public:
			DummyGLContext();
			~DummyGLContext();

			void activate();
			bool isActive() const;

			static void deactivate();

			const video::DummyWindow &getWindow() const;
			video::DummyWindow &getWindow();
		};

		inline const video::DummyWindow &DummyGLContext::getWindow() const {return _window;}
		inline video::DummyWindow &DummyGLContext::getWindow() {return _window;}
	}  // namespace graphic
}  // namespace cb

