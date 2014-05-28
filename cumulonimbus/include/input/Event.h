/* 
 * - Cumulonimbus - ☁
 * File: Event.h
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

#include <input/KeyCode.h>

#include <base/String.h>

namespace cb {
	namespace input {
		enum class EventType : unsigned char {
			Void = 0,

			KeyPress,
			KeyRelease,
			KeyMove,
			Char,

			ButtonPress,
			ButtonRelease,
			MouseMove,
			WheelMove,

			Resize,
			Activate,
			Deactivate,
			Close,
			Quit
		};

		union CbAPI Event {
		public:
			EventType type;
			struct {EventType type; KeyCode k; float v;}			key;
			struct {EventType type; base::lchar_t c;}				character;
			struct {EventType type; KeyCode k; int x; int y;}		button;
			struct {EventType type; int x; int y;}				move;
			struct {EventType type; float v; float h;}				wheel;
			struct {EventType type; size_t w; size_t h;}			size;
			
			Event();
			Event(EventType itype);
			Event(EventType itype, KeyCode ikey);
			Event(EventType itype, KeyCode ikey, float ivalue);
			Event(EventType itype, base::lchar_t ichar);
			Event(EventType itype, KeyCode ibutton, int ix, int iy);
			Event(EventType itype, int ix, int iy);
			Event(EventType itype, float ix, float iy);
			Event(EventType itype, size_t iwidth, size_t iheight);
			Event(const Event &iev);
			~Event();

			Event &operator=(const Event &iev);
			bool operator==(const EventType iev);

			base::string str();
		};

		inline Event::Event() {
			type = EventType::Void;
		}

		inline Event::Event(EventType itype) {
			type = itype;
		}

		inline Event::Event(EventType itype, KeyCode ikey) {
			type = itype;
			key.k = ikey;
		}

		inline Event::Event(EventType itype, KeyCode ikey, float ivalue) {
			type = itype;
			key.k = ikey;
			key.v = ivalue;
		}

		inline Event::Event(EventType itype, base::lchar_t ichar) {
			type = itype;
			character.c = ichar;
		}

		inline Event::Event(EventType itype, KeyCode ibutton, int ix, int iy) {
			type = itype;
			button.k = ibutton;
			button.x = ix;
			button.y = iy;
		}

		inline Event::Event(EventType itype, int ix, int iy) {
			type = itype;
			move.x = ix;
			move.y = iy;
		}

		inline Event::Event(EventType itype, float iv, float ih) {
			type = itype;
			wheel.v = iv;
			wheel.h = ih;
		}

		inline Event::Event(EventType itype, size_t iwidth, size_t iheight) {
			type = itype;
			size.w = iwidth;
			size.h = iheight;
		}

		inline Event::Event(const Event &iev) {
			memcpy(this, &iev, sizeof(Event));
			type = iev.type;
		}

		inline Event::~Event() {
		}

		inline Event &Event::operator=(const Event &iev) {
			memcpy(this, &iev, sizeof(Event));
			type = iev.type;
			return *this;
		}

		inline bool Event::operator==(const EventType itype) {
			return type == itype;
		}
	}  // namespace video
}  // namespace cb
