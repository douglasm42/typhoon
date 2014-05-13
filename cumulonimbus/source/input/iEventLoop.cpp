/* 
 * - Cumulonimbus - ☁
 * File: iEventLoop.cpp
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
#include <input/EventLoop.h>

namespace cb {
	namespace input {
		std::list<video::Window *> EventLoop::_window_list;

		void EventLoop::bind(video::Window *iwindow) {
			_window_list.push_back(iwindow);
		}

		void EventLoop::unbind(video::Window *iwindow) {
			std::list<video::Window *>::iterator it;
			for(it = _window_list.begin() ; it != _window_list.end() ; ++it) {
				if((*it) == iwindow) {
					_window_list.erase(it);
				}
			}
		}
	}  // namespace input
}  // namespace cb

