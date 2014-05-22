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
		namespace ev {
			typedef enum Type : unsigned char {
				Void = 0,

				KeyPress,
				KeyRelease,
				KeyMove,
				Char,

				ButtonPress,
				ButtonRelease,
				Move,

				Resize,
				Activate,
				Deactivate,
				Close,
				Quit
			} Type;

			typedef struct CbAPI KeyT {
				KeyCode k;
				float v;
			} KeyT;

			typedef struct CbAPI CharT {
				base::lchar_t c;
			} CharT;

			typedef struct CbAPI ButtonT {
				KeyCode k;
				int x;
				int y;
			} ButtonT;

			typedef struct CbAPI MoveT {
				int x;
				int y;
				int rx;
				int ry;
				int rz;
			} MoveT;

			typedef struct CbAPI SizeT {
				size_t w;
				size_t h;
			} SizeT;
		}  // namespace ev

		class CbAPI Event {
		private:
			ev::Type _type;
			char _e[sizeof(ev::MoveT)];
			
		public:
			Event();
			Event(ev::Type itype);
			Event(ev::Type itype, KeyCode ikey);
			Event(ev::Type itype, KeyCode ikey, float ivalue);
			Event(ev::Type itype, base::lchar_t ichar);
			Event(ev::Type itype, KeyCode ibutton, int ix, int iy);
			Event(ev::Type itype, int ix, int iy, int irelx, int irely, int irelz);
			Event(ev::Type itype, int iwidth, int iheight);
			Event(const Event &iev);
			~Event();

			ev::Type &type();
			ev::KeyT &key();
			ev::CharT &character();
			ev::ButtonT &button();
			ev::MoveT &move();
			ev::SizeT &size();

			Event &operator=(const Event &iev);
			bool operator==(const ev::Type iev);

			base::string str();
		};

		inline Event::Event() {
			_type = ev::Void;
		}

		inline Event::Event(ev::Type itype) {
			_type = itype;
		}

		inline Event::Event(ev::Type itype, KeyCode ikey) {
			_type = itype;
			key().k = ikey;
		}

		inline Event::Event(ev::Type itype, KeyCode ikey, float ivalue) {
			_type = itype;
			key().k = ikey;
			key().v = ivalue;
		}

		inline Event::Event(ev::Type itype, base::lchar_t ichar) {
			_type = itype;
			character().c = ichar;
		}

		inline Event::Event(ev::Type itype, KeyCode ibutton, int ix, int iy) {
			_type = itype;
			button().k = ibutton;
			button().x = ix;
			button().y = iy;
		}

		inline Event::Event(ev::Type itype, int ix, int iy, int irelx, int irely, int irelz) {
			_type = itype;
			move().x = ix;
			move().y = iy;
			move().rx = irelx;
			move().ry = irely;
			move().rz = irelz;
		}

		inline Event::Event(ev::Type itype, int iwidth, int iheight) {
			_type = itype;
			size().w = iwidth;
			size().h = iheight;
		}

		inline Event::Event(const Event &iev) {
			memcpy(_e, iev._e, sizeof(_e));
			_type = iev._type;
		}

		inline Event::~Event() {
		}

		inline ev::Type &Event::type() {
			return _type;
		}

		inline ev::KeyT &Event::key() {
			return reinterpret_cast<ev::KeyT&>(_e);
		}

		inline ev::CharT &Event::character() {
			return reinterpret_cast<ev::CharT&>(_e);
		}

		inline ev::ButtonT &Event::button() {
			return reinterpret_cast<ev::ButtonT&>(_e);
		}

		inline ev::MoveT &Event::move() {
			return reinterpret_cast<ev::MoveT&>(_e);
		}

		inline ev::SizeT &Event::size() {
			return reinterpret_cast<ev::SizeT&>(_e);
		}

		inline Event &Event::operator=(const Event &iev) {
			memcpy(_e, iev._e, sizeof(_e));
			_type = iev._type;
			return *this;
		}

		inline bool Event::operator==(const ev::Type itype) {
			return _type == itype;
		}
	}  // namespace video
}  // namespace cb
