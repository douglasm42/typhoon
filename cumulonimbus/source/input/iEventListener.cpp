/* 
 * - Cumulonimbus - ☁
 * File: iEventListener.cpp
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
#include <input/EventListener.h>

#include <input/EventHub.h>

namespace cb {
	namespace input {
		UpdateListener::~UpdateListener() {
			if(_event_hub) {
				_event_hub->unbind(this);
			}
		}

		KeyListener::~KeyListener() {
			if(_event_hub) {
				_event_hub->unbind(this);
			}
		}

		WindowListener::~WindowListener() {
			if(_event_hub) {
				_event_hub->unbind(this);
			}
		}
	}  // namespace input
}  // namespace cb

