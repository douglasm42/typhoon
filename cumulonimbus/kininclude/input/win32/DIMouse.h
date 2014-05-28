/* 
 * - Cumulonimbus - ☁
 * File: DIMouse.h
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

#include <input/input.h>

#include <input/win32/DIDevice.h>
#include <input/EventQueue.h>

#include <list>

namespace cb {
	namespace input {
		class CbAPI DIMouse {
		private:
			HWND _window;
			EventQueue *_event_queue;

			int _granularity;

			DIDevice _device;

		public:
			DIMouse(HWND iwindow, EventQueue *ievent_queue);
			~DIMouse();

			void update();
		};
	}  // namespace input
}  // namespace cb
