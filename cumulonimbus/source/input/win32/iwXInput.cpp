/* 
 * - Cumulonimbus - ☁
 * File: iwXInput.cpp
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
#include <cb/input/win32/XInput.h>

#include <cb/video/win32/Windows.h>
#include <cb/input/EventHub.h>
#include <cb/input/Key.h>

#include <cb/base/Log.h>

#include <cb/math/math.h>

namespace cb {
	namespace input {
		Key::Code translateVK(WORD ivk) {
			switch(ivk) {
			case VK_PAD_A:
				return Key::XbA;
			case VK_PAD_B:
				return Key::XbB;
			case VK_PAD_X:
				return Key::XbX;
			case VK_PAD_Y:
				return Key::XbY;

			case VK_PAD_RSHOULDER:
				return Key::XbRShoulder;
			case VK_PAD_LSHOULDER:
				return Key::XbLShoulder;

			case VK_PAD_LTRIGGER:
				return Key::XbLTrigger;
			case VK_PAD_RTRIGGER:
				return Key::XbRTrigger;

			case VK_PAD_DPAD_UP:
				return Key::XbUp;
			case VK_PAD_DPAD_DOWN:
				return Key::XbDown;
			case VK_PAD_DPAD_LEFT:
				return Key::XbLeft;
			case VK_PAD_DPAD_RIGHT:
				return Key::XbRight;

			case VK_PAD_START:
				return Key::XbStart;
			case VK_PAD_BACK:
				return Key::XbBack;

			case VK_PAD_LTHUMB_PRESS:
				return Key::XbLThumb;
			case VK_PAD_RTHUMB_PRESS:
				return Key::XbRThumb;

			case VK_PAD_LTHUMB_UP:
				return Key::XbLThumbUp;
			case VK_PAD_LTHUMB_DOWN:
				return Key::XbLThumbDown;
			case VK_PAD_LTHUMB_RIGHT:
				return Key::XbLThumbRight;
			case VK_PAD_LTHUMB_LEFT:
				return Key::XbLThumbLeft;

			case VK_PAD_LTHUMB_UPLEFT:
				return Key::XbLThumbUpLeft;
			case VK_PAD_LTHUMB_UPRIGHT:
				return Key::XbLThumbUpRight;
			case VK_PAD_LTHUMB_DOWNRIGHT:
				return Key::XbLThumbDownRight;
			case VK_PAD_LTHUMB_DOWNLEFT:
				return Key::XbLThumbDownLeft;

			case VK_PAD_RTHUMB_UP:
				return Key::XbRThumbUp;
			case VK_PAD_RTHUMB_DOWN:
				return Key::XbRThumbDown;
			case VK_PAD_RTHUMB_RIGHT:
				return Key::XbRThumbRight;
			case VK_PAD_RTHUMB_LEFT:
				return Key::XbRThumbLeft;

			case VK_PAD_RTHUMB_UPLEFT:
				return Key::XbRThumbUpLeft;
			case VK_PAD_RTHUMB_UPRIGHT:
				return Key::XbRThumbUpRight;
			case VK_PAD_RTHUMB_DOWNRIGHT:
				return Key::XbRThumbDownRight;
			case VK_PAD_RTHUMB_DOWNLEFT:
				return Key::XbRThumbDownLeft;
			default:
				return Key::Null;
			}
		}

		XInput::XInput(EventHub *ievent_hub)
		:_event_hub(ievent_hub) {
			for(int i=0 ; i<4 ; i++) {
				memset(&_state_old[i], 0, sizeof(_state_old[i]));
			}
		}

		XInput::~XInput() {
		}

		void XInput::fireThumbEvents(Key ikeyp, Key ikeym, SHORT inew, SHORT &ioold, SHORT ideadzone) {
			if(inew < ideadzone && inew > -ideadzone) {
				inew = 0;
			}
			if(ioold != inew) {
				float vp = abs(clamp((float)inew, 0.0f, 32767.0f)) / 32767.0f;
				float vm = abs(clamp((float)inew, -32768.0f, 0.0f)) / 32768.0f;

				if(vp != 0.0f || (ioold > 0)) {
					_event_hub->onKeyMove(ikeyp,vp);
				}

				if(vm != 0.0f || (ioold < 0)) {
					_event_hub->onKeyMove(ikeym,vm);
				}

				ioold = inew;
			}
		}

		void XInput::update() {
			XINPUT_KEYSTROKE keystroke;
			DWORD result = XInputGetKeystroke(XUSER_INDEX_ANY, 0, &keystroke);
			while(result == ERROR_SUCCESS) {
				if(keystroke.Flags & XINPUT_KEYSTROKE_KEYDOWN) {
					_event_hub->onKeyPress(Key(
						1 + keystroke.UserIndex,
						translateVK(keystroke.VirtualKey)
					));
				} else if(keystroke.Flags & XINPUT_KEYSTROKE_KEYUP) {
					_event_hub->onKeyRelease(Key(
						1 + keystroke.UserIndex,
						translateVK(keystroke.VirtualKey)
					));
				}

				result = XInputGetKeystroke(XUSER_INDEX_ANY, 0, &keystroke);
			}

			XINPUT_STATE state;
			for(DWORD i=0 ; i<4 ; i++) {
				DWORD result = XInputGetState(i, &state);
				if(result == ERROR_SUCCESS) {
					if(_state_old[i].bLeftTrigger != state.Gamepad.bLeftTrigger) {
						_event_hub->onKeyMove(
							Key(1 + i, Key::XbLTrigger),
							float(state.Gamepad.bLeftTrigger) / 255.0f
						);
						_state_old[i].bLeftTrigger = state.Gamepad.bLeftTrigger;
					}

					if(_state_old[i].bRightTrigger != state.Gamepad.bRightTrigger) {
						_event_hub->onKeyMove(
							Key(1 + i, Key::XbRTrigger),
							float(state.Gamepad.bRightTrigger) / 255.0f
						);
						_state_old[i].bRightTrigger = state.Gamepad.bRightTrigger;
					}

					fireThumbEvents(
						Key(1 + i, Key::XbLThumbRight),
						Key(1 + i, Key::XbLThumbLeft),
						state.Gamepad.sThumbLX,
						_state_old[i].sThumbLX,
						XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
					);

					fireThumbEvents(
						Key(1 + i, Key::XbLThumbUp),
						Key(1 + i, Key::XbLThumbDown),
						state.Gamepad.sThumbLY,
						_state_old[i].sThumbLY,
						XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
					);

					fireThumbEvents(
						Key(1 + i, Key::XbRThumbRight),
						Key(1 + i, Key::XbRThumbLeft),
						state.Gamepad.sThumbRX,
						_state_old[i].sThumbRX,
						XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE
					);

					fireThumbEvents(
						Key(1 + i, Key::XbRThumbUp),
						Key(1 + i, Key::XbRThumbDown),
						state.Gamepad.sThumbRY,
						_state_old[i].sThumbRY,
						XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE
					);
				}
			}
		}
	}  // namespace input
}  // namespace cb
