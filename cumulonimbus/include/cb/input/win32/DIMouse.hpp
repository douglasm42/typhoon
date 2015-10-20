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

#include <cb/input/input.hpp>

#include <cb/input/win32/DIDevice.hpp>
#include <cb/input/EventHub.hpp>

#include <list>

namespace cb {
	namespace input {
		class CbAPI DIMouse {
		private:
			HWND _window;
			EventHub *_event_hub;

			int _granularity;

			DIDevice _device;

		public:
			DIMouse(HWND iwindow, EventHub *ievent_hub);
			~DIMouse();

			void update();

			input::EventHub *getEventHub();
			void setEventHub(input::EventHub *ievent_hub);
		};

		inline input::EventHub *DIMouse::getEventHub() {return _event_hub;}
		inline void DIMouse::setEventHub(input::EventHub *ievent_hub) {_event_hub = ievent_hub;}
	}  // namespace input
}  // namespace cb
