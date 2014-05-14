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
#include <video/win32/Windows.h>
#include <video/win32/WindowInfo.h>

namespace cb {
	namespace video {
		KinKey(WindowInfo, w32WindowInfo);
	}  // namespace video

	namespace input {
		void EventLoop::postQuit() {
			PostQuitMessage(0);
		}

		bool EventLoop::update() {
			std::list<video::Window *>::iterator it;

			for(it = _window_list.begin() ; it != _window_list.end() ; ++it) {
				(*it)->eventHub().onUpdateStart();
			}

			MSG msg;
			while(PeekMessage(&msg,NULL,0,0,PM_REMOVE)) {
				if (msg.message==WM_QUIT) {
					for(it = _window_list.begin() ; it != _window_list.end() ; ++it) {
						(*it)->eventHub().onQuit();
					}
					return false;
				} else {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}

			for(it = _window_list.begin() ; it != _window_list.end() ; ++it) {
				video::kin::pt((*it)->info())->dimouse->update();
				(*it)->eventHub().onUpdateEnd();
			}

			return true;
		}
	}  // namespace input
}  // namespace cb

#endif
