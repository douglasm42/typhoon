/* 
 * - Cumulonimbus - ☁
 * File: vwWindow.cpp
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
#include <base/Setup.h>
#ifdef CbWindows

#include <input/EventLoop.h>
#include <video/Window.h>
#include <win32/video/Windows.h>
#include <win32/video/WindowInfo.h>

namespace cb {
	namespace input {
		KinKey(video::kin::WindowInfo, video::w32WindowInfo);

		void EventLoop::postQuit() {
			PostQuitMessage(0);
		}

		bool EventLoop::update() {
			std::list<video::Window *>::iterator it;

			MSG msg;
			while(PeekMessage(&msg,NULL,0,0,PM_REMOVE)) {
				if (msg.message==WM_QUIT) {
					return false;
				} else {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}

			for(it = _window_list.begin() ; it != _window_list.end() ; ++it) {
				(*(*it)->info()).dimouse->update();
			}

			return true;
		}
	}  // namespace input
}  // namespace cb

#endif
