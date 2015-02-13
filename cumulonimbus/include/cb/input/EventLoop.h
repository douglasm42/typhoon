/* 
 * - Cumulonimbus - ☁
 * File: EventLoop.h
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

#include <cb/input/input.h>

#include <cb/video/video.h>
#include <list>

namespace cb {
	namespace input {
		class CbAPI EventLoop {
		private:
			static std::list<video::Window *> _window_list;

			static void bind(video::Window *iwindow);
			static void unbind(video::Window *iwindow);

		public:
			static void postQuit();
			static bool update();

			friend class CbAPI cb::video::Window;
		};
	}  // namespace video
}  // namespace cb
