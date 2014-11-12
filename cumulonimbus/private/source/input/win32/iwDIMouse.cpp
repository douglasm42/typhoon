/* 
 * - Cumulonimbus - ☁
 * File: iwDIMouse.cpp
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
#include <input/win32/DIMouse.h>

#include <cb/base/Log.h>

namespace cb {
	namespace input {
		input::Key buttonkeycode(size_t ibutton) {
			switch(ibutton) {
			case 0:
				return input::Key(input::Key::MouseLeft);
			case 1:
				return input::Key(input::Key::MouseRight);
			case 2:
				return input::Key(input::Key::MouseMiddle);
			case 3:
				return input::Key(input::Key::MouseX1);
			case 4:
				return input::Key(input::Key::MouseX2);
			case 5:
				return input::Key(input::Key::MouseX3);
			case 6:
				return input::Key(input::Key::MouseX4);
			case 7:
				return input::Key(input::Key::MouseX5);
			default:
				return input::Key(input::Key::Null);
			}
		}

		DIMouse::DIMouse(HWND iwindow, EventHub *ievent_hub)
		:_window(iwindow)
		,_event_hub(ievent_hub)
		,_granularity(0)
		,_device(_window, GUID_SysMouse, &c_dfDIMouse2) {
			_device.bufferSize(128);
			_granularity = (int)_device.property(DIPROP_GRANULARITY, DIMOFS_Z, DIPH_BYOFFSET);
		}

		DIMouse::~DIMouse() {
		}

		void DIMouse::update() {
			int relx = 0;
			int rely = 0;

			int z = 0;

			DIDEVICEOBJECTDATA *data;
			DWORD n = _device.data(&data);
			for(DWORD i=0 ; i<n ; i++) {
				DIDEVICEOBJECTDATA &d = data[i];

				if(d.dwOfs == DIMOFS_X) {
					relx += d.dwData;
				} else if(d.dwOfs == DIMOFS_Y) {
					rely += d.dwData;
				} else if(d.dwOfs == DIMOFS_Z) {
					z += d.dwData;
				} else if(d.dwOfs == DIMOFS_BUTTON0) {
					if(d.dwData & 0x80) {_event_hub->onKeyPress(buttonkeycode(0));} else {_event_hub->onKeyRelease(buttonkeycode(0));}
				} else if(d.dwOfs == DIMOFS_BUTTON1) {
					if(d.dwData & 0x80) {_event_hub->onKeyPress(buttonkeycode(1));} else {_event_hub->onKeyRelease(buttonkeycode(1));}
				} else if(d.dwOfs == DIMOFS_BUTTON2) {
					if(d.dwData & 0x80) {_event_hub->onKeyPress(buttonkeycode(2));} else {_event_hub->onKeyRelease(buttonkeycode(2));}
				} else if(d.dwOfs == DIMOFS_BUTTON3) {
					if(d.dwData & 0x80) {_event_hub->onKeyPress(buttonkeycode(3));} else {_event_hub->onKeyRelease(buttonkeycode(3));}
				} else if(d.dwOfs == DIMOFS_BUTTON4) {
					if(d.dwData & 0x80) {_event_hub->onKeyPress(buttonkeycode(4));} else {_event_hub->onKeyRelease(buttonkeycode(4));}
				} else if(d.dwOfs == DIMOFS_BUTTON5) {
					if(d.dwData & 0x80) {_event_hub->onKeyPress(buttonkeycode(5));} else {_event_hub->onKeyRelease(buttonkeycode(5));}
				} else if(d.dwOfs == DIMOFS_BUTTON6) {
					if(d.dwData & 0x80) {_event_hub->onKeyPress(buttonkeycode(6));} else {_event_hub->onKeyRelease(buttonkeycode(6));}
				} else if(d.dwOfs == DIMOFS_BUTTON7) {
					if(d.dwData & 0x80) {_event_hub->onKeyPress(buttonkeycode(7));} else {_event_hub->onKeyRelease(buttonkeycode(7));}
				}
			}
			delete [] data;

			if(relx != 0 || rely != 0 || z != 0) {
				if(relx > 0) {
					_event_hub->onKeyMove(input::Key(input::Key::MouseVu), (float)relx);
				} else if(relx < 0) {
					_event_hub->onKeyMove(input::Key(input::Key::MouseVd), (float)relx);
				}

				if(rely > 0) {
					_event_hub->onKeyMove(input::Key(input::Key::MouseHu), (float)rely);
				} else if(rely < 0) {
					_event_hub->onKeyMove(input::Key(input::Key::MouseHd), (float)rely);
				}

				if(z > 0) {
					_event_hub->onKeyMove(input::Key(input::Key::MouseMu), (float)(z)/(float)WHEEL_DELTA);
				} else if(z < 0) {
					_event_hub->onKeyMove(input::Key(input::Key::MouseMd), (float)(z)/(float)WHEEL_DELTA);
				}
			}
		}
	}  // namespace input
}  // namespace cb
