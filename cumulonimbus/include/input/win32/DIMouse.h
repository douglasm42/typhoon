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
#include <input/EventHub.h>

#include <list>
#include <dinput.h>

namespace cb {
	namespace input {
		class CbAPI DIMouse {
		private:
			HWND _window;
			EventHub *_event_hub;

			bool _hold;

			int _absx;
			int _absy;

			int _granularity;

			DIDevice _device;

			void doHoldCursor();

		public:
			DIMouse(HWND iwindow, EventHub *ievent_hub);
			~DIMouse();

			void update();

			void hold(bool ihold);
			bool hold() const {return _hold;}

			void move(size_t ix, size_t iy);
		};
	}  // namespace input
}  // namespace cb
