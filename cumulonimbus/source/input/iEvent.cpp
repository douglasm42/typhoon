/* 
 * - Cumulonimbus - ☁
 * File: iEvent.cpp
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
#include <input/EventQueue.h>

namespace cb {
	namespace input {
		base::string Event::str() {
			if(type == EventType::Void) {
				return base::string("Void");

			} else if(type == EventType::KeyPress) {
				return base::format("KeyPress : %s", keyname(key.k).c_str());

			} else if(type == EventType::KeyRelease) {
				return base::format("KeyRelease : %s", keyname(key.k).c_str());

			} else if(type == EventType::KeyMove) {
				return base::format("KeyMove : %s - %f", keyname(key.k).c_str(), key.v);

			} else if(type == EventType::Char) {
				char32_t lstr[2] = {character.c, 0};
				return base::format("Char : %s", base::utf8(base::string32(lstr)).c_str());

			} else if(type == EventType::ButtonPress) {
				return base::format("ButtonPress : %s - %d:%d", keyname(button.k).c_str(), button.x, button.y);

			} else if(type == EventType::ButtonRelease) {
				return base::format("ButtonRelease : %s - %d:%d", keyname(button.k).c_str(), button.x, button.y);

			} else if(type == EventType::MouseMove) {
				return base::format("MouseMove : x:%d y:%d", move.x, move.y);

			} else if(type == EventType::WheelMove) {
				return base::format("WheelMove : v:%f h:%f", wheel.v, wheel.h);

			} else if(type == EventType::Resize) {
				return base::format("Resize : %dx%d", size.w, size.h);

			} else if(type == EventType::Activate) {
				return base::string("Activate");

			} else if(type == EventType::Deactivate) {
				return base::string("Deactivate");

			} else if(type == EventType::Close) {
				return base::string("Close");

			} else if(type == EventType::Quit) {
				return base::string("Quit");
			}
			return base::string("Unknown");
		}
	}  // namespace input
}  // namespace cb

