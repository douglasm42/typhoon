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

#include <base/Log.h>

namespace cb {
	namespace input {
		input::KeyCode buttonkeycode(size_t ibutton) {
			switch(ibutton) {
			case 0:
				return input::MouseLeft;
			case 1:
				return input::MouseRight;
			case 2:
				return input::MouseMiddle;
			case 3:
				return input::MouseX1;
			case 4:
				return input::MouseX2;
			case 5:
				return input::MouseX3;
			case 6:
				return input::MouseX4;
			case 7:
				return input::MouseX5;
			default:
				return input::Null;
			}
		}

		DIMouse::DIMouse(HWND iwindow, EventHub *ievent_hub)
		:_window(iwindow)
		,_event_hub(ievent_hub)
		,_hold(false)
		,_absx(0)
		,_absy(0)
		,_granularity(0)
		,_device(_window, GUID_SysMouse, &c_dfDIMouse2) {
			_device.bufferSize(128);
			_granularity = _device.property(DIPROP_GRANULARITY, DIMOFS_Z, DIPH_BYOFFSET);
		}

		DIMouse::~DIMouse() {
		}

		void DIMouse::doHoldCursor() {
			if(_hold) {
				//Prende o DIMouse dentro da janela.
				POINT p = {0, 0};
				ClientToScreen(_window, &p);
				RECT rect;
				GetClientRect(_window, &rect);
				rect.left += p.x;
				rect.right += p.x;
				rect.top += p.y;
				rect.bottom += p.y;
				ClipCursor(&rect);
			} else {
				//Desprende o DIMouse de dentro da janela.
				ClipCursor(NULL);
			}
		}

		void DIMouse::update() {
			int relx = 0;
			int rely = 0;

			int z = 0;

			DIDEVICEOBJECTDATA *data;
			DWORD n = _device.data(&data);
			for(DWORD i=0 ; i<n ; i++) {
				DIDEVICEOBJECTDATA &d = data[i];

				int x = _absx + relx;
				int y = _absy + rely;

				RECT rect;
				if(GetWindowRect(_window, &rect)) {
					int width = rect.right - rect.left;
					int height = rect.bottom - rect.top;

					x = x<0	? 0	: ( x>=width	? height-1	: x );
					y = y<0	? 0	: ( y>=height	? height-1	: y );
				}

				if(d.dwOfs == DIMOFS_X) {
					relx += d.dwData;
				} else if(d.dwOfs == DIMOFS_Y) {
					rely += d.dwData;
				} else if(d.dwOfs == DIMOFS_Z) {
					z += d.dwData;
				} else if(d.dwOfs == DIMOFS_BUTTON0) {
					if(d.dwData & 0x80) {_event_hub->onButtonPress(buttonkeycode(0), x, y);} else {_event_hub->onButtonRelease(buttonkeycode(0), x, y);}
				} else if(d.dwOfs == DIMOFS_BUTTON1) {
					if(d.dwData & 0x80) {_event_hub->onButtonPress(buttonkeycode(1), x, y);} else {_event_hub->onButtonRelease(buttonkeycode(1), x, y);}
				} else if(d.dwOfs == DIMOFS_BUTTON2) {
					if(d.dwData & 0x80) {_event_hub->onButtonPress(buttonkeycode(2), x, y);} else {_event_hub->onButtonRelease(buttonkeycode(2), x, y);}
				} else if(d.dwOfs == DIMOFS_BUTTON3) {
					if(d.dwData & 0x80) {_event_hub->onButtonPress(buttonkeycode(3), x, y);} else {_event_hub->onButtonRelease(buttonkeycode(3), x, y);}
				} else if(d.dwOfs == DIMOFS_BUTTON4) {
					if(d.dwData & 0x80) {_event_hub->onButtonPress(buttonkeycode(4), x, y);} else {_event_hub->onButtonRelease(buttonkeycode(4), x, y);}
				} else if(d.dwOfs == DIMOFS_BUTTON5) {
					if(d.dwData & 0x80) {_event_hub->onButtonPress(buttonkeycode(5), x, y);} else {_event_hub->onButtonRelease(buttonkeycode(5), x, y);}
				} else if(d.dwOfs == DIMOFS_BUTTON6) {
					if(d.dwData & 0x80) {_event_hub->onButtonPress(buttonkeycode(6), x, y);} else {_event_hub->onButtonRelease(buttonkeycode(6), x, y);}
				} else if(d.dwOfs == DIMOFS_BUTTON7) {
					if(d.dwData & 0x80) {_event_hub->onButtonPress(buttonkeycode(7), x, y);} else {_event_hub->onButtonRelease(buttonkeycode(7), x, y);}
				}
			}
			delete [] data;

			if(relx != 0 && rely != 0) {
				POINT point;
				GetCursorPos(&point);
				ScreenToClient(_window, &point);
				_absx = point.x;
				_absy = point.y;

				_event_hub->onMove(_absx, _absy, relx, rely);
			}

			if(z != 0) {
				_event_hub->onWheel(z);
			}
		}

		void DIMouse::hold(bool ihold) {
			_hold = ihold;

			doHoldCursor();
		}

		void DIMouse::move(size_t ix, size_t iy) {
			POINT pt = {ix, iy};
			ClientToScreen(_window, &pt);
			SetCursorPos(pt.x,pt.y);
		}
	}  // namespace input
}  // namespace cb
