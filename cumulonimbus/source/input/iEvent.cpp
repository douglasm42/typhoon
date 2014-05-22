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
			if(_type == ev::Void) {
				return base::string("Void");

			} else if(_type == ev::KeyPress) {
				return base::format("KeyPress : %s", keyname(key().k).c_str());

			} else if(_type == ev::KeyRelease) {
				return base::format("KeyRelease : %s", keyname(key().k).c_str());

			} else if(_type == ev::KeyMove) {
				return base::format("KeyMove : %s - %f", keyname(key().k).c_str(), key().v);

			} else if(_type == ev::Char) {
				base::lchar_t lstr[2] = {character().c, 0};
				return base::format("Char : %s", base::utf8(base::lstring(lstr)).c_str());

			} else if(_type == ev::ButtonPress) {
				return base::format("ButtonPress : %s - %d:%d", keyname(button().k).c_str(), button().x, button().y);

			} else if(_type == ev::ButtonRelease) {
				return base::format("ButtonRelease : %s - %d:%d", keyname(button().k).c_str(), button().x, button().y);

			} else if(_type == ev::Move) {
				return base::format("Move : Abs:%d:%d - Rel:%d:%d:%d", move().x, move().y, move().rx, move().ry, move().rz);

			} else if(_type == ev::Resize) {
				return base::format("Resize : %dx%d", size().w, size().h);

			} else if(_type == ev::Activate) {
				return base::string("Activate");

			} else if(_type == ev::Deactivate) {
				return base::string("Deactivate");

			} else if(_type == ev::Close) {
				return base::string("Close");

			} else if(_type == ev::Quit) {
				return base::string("Quit");
			}
			return base::string("Unknown");
		}
	}  // namespace input
}  // namespace cb

