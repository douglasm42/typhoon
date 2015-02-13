/* 
 * - Cumulonimbus - ☁
 * File: XInput.h
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

#include <cb/video/win32/Windows.h>
#include <XInput.h>

#include <cb/input/Key.h>

namespace cb {
	namespace input {
		class CbAPI XInput {
		private:
			EventHub *_event_hub;
			XINPUT_GAMEPAD _state_old[4];

			void fireThumbEvents(Key ikeyp, Key ikeym, SHORT inew, SHORT &ioold, SHORT ideadzone);

		public:
			XInput(EventHub *ievent_hub);
			~XInput();

			void update();

			input::EventHub *getEventHub();
			void setEventHub(input::EventHub *ievent_hub);
		};

		inline input::EventHub *XInput::getEventHub() {return _event_hub;}
		inline void XInput::setEventHub(input::EventHub *ievent_hub) {_event_hub = ievent_hub;}
	}  // namespace input
}  // namespace cb
