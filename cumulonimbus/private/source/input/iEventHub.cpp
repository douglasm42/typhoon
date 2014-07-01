/* 
 * - Cumulonimbus - ☁
 * File: iEventHub.cpp
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
#include <input/EventHub.h>

#include <input/KeyListener.h>
#include <input/CharListener.h>
#include <input/MouseListener.h>
#include <input/WindowListener.h>
#include <input/QuitListener.h>

#include <base/Exception.h>

namespace cb {
	namespace input {
		void EventHub::bind(KeyListener *ikey_listener) {
			std::vector<KeyListener*>::iterator it;
			for(it = _key_listener_list.begin() ; it != _key_listener_list.end() ; ++it) {
				if(*it == ikey_listener) {
					return;
				}
			}
			_key_listener_list.push_back(ikey_listener);
		}

		void EventHub::bind(CharListener *ichar_listener) {
			std::vector<CharListener*>::iterator it;
			for(it = _char_listener_list.begin() ; it != _char_listener_list.end() ; ++it) {
				if(*it == ichar_listener) {
					return;
				}
			}
			_char_listener_list.push_back(ichar_listener);
		}

		void EventHub::bind(MouseListener *imouse_listener) {
			std::vector<MouseListener*>::iterator it;
			for(it = _mouse_listener_list.begin() ; it != _mouse_listener_list.end() ; ++it) {
				if(*it == imouse_listener) {
					return;
				}
			}
			_mouse_listener_list.push_back(imouse_listener);
		}

		void EventHub::bind(WindowListener *iwindow_listener) {
			std::vector<WindowListener*>::iterator it;
			for(it = _window_listener_list.begin() ; it != _window_listener_list.end() ; ++it) {
				if(*it == iwindow_listener) {
					return;
				}
			}
			_window_listener_list.push_back(iwindow_listener);
		}

		void EventHub::bind(QuitListener *iquit_listener) {
			std::vector<QuitListener*>::iterator it;
			for(it = _quit_listener_list.begin() ; it != _quit_listener_list.end() ; ++it) {
				if(*it == iquit_listener) {
					return;
				}
			}
			_quit_listener_list.push_back(iquit_listener);
		}

		void EventHub::unbind(KeyListener *ikey_listener) {
			std::vector<KeyListener*>::iterator it;
			for(it = _key_listener_list.begin() ; it != _key_listener_list.end() ; ++it) {
				if(*it == ikey_listener) {
					_key_listener_list.erase(it);
					return;
				}
			}
		}

		void EventHub::unbind(CharListener *ichar_listener) {
			std::vector<CharListener*>::iterator it;
			for(it = _char_listener_list.begin() ; it != _char_listener_list.end() ; ++it) {
				if(*it == ichar_listener) {
					_char_listener_list.erase(it);
					return;
				}
			}
		}

		void EventHub::unbind(MouseListener *imouse_listener) {
			std::vector<MouseListener*>::iterator it;
			for(it = _mouse_listener_list.begin() ; it != _mouse_listener_list.end() ; ++it) {
				if(*it == imouse_listener) {
					_mouse_listener_list.erase(it);
					return;
				}
			}
		}

		void EventHub::unbind(WindowListener *iwindow_listener) {
			std::vector<WindowListener*>::iterator it;
			for(it = _window_listener_list.begin() ; it != _window_listener_list.end() ; ++it) {
				if(*it == iwindow_listener) {
					_window_listener_list.erase(it);
					return;
				}
			}
		}

		void EventHub::unbind(QuitListener *iquit_listener) {
			std::vector<QuitListener*>::iterator it;
			for(it = _quit_listener_list.begin() ; it != _quit_listener_list.end() ; ++it) {
				if(*it == iquit_listener) {
					_quit_listener_list.erase(it);
					return;
				}
			}
		}

		void EventHub::onKeyPress(Key ikey) {
			std::vector<KeyListener*>::iterator it;
			for(it = _key_listener_list.begin() ; it != _key_listener_list.end() ; ++it) {
				(*it)->onKeyPress(ikey);
			}
		}

		void EventHub::onKeyRelease(Key ikey) {
			std::vector<KeyListener*>::iterator it;
			for(it = _key_listener_list.begin() ; it != _key_listener_list.end() ; ++it) {
				(*it)->onKeyRelease(ikey);
			}
		}

		void EventHub::onKeyMove(Key ikey, float ivalue) {
			std::vector<KeyListener*>::iterator it;
			for(it = _key_listener_list.begin() ; it != _key_listener_list.end() ; ++it) {
				(*it)->onKeyMove(ikey, ivalue);
			}
		}

		void EventHub::onChar(char32_t ichar) {
			std::vector<CharListener*>::iterator it;
			for(it = _char_listener_list.begin() ; it != _char_listener_list.end() ; ++it) {
				(*it)->onChar(ichar);
			}
		}

		void EventHub::onButtonPress(Key ikey, int ix, int iy) {
			std::vector<MouseListener*>::iterator it;
			for(it = _mouse_listener_list.begin() ; it != _mouse_listener_list.end() ; ++it) {
				(*it)->onButtonPress(ikey, ix, iy);
			}
		}

		void EventHub::onButtonRelease(Key ikey, int ix, int iy) {
			std::vector<MouseListener*>::iterator it;
			for(it = _mouse_listener_list.begin() ; it != _mouse_listener_list.end() ; ++it) {
				(*it)->onButtonRelease(ikey, ix, iy);
			}
		}

		void EventHub::onMouseMove(int ix, int iy) {
			std::vector<MouseListener*>::iterator it;
			for(it = _mouse_listener_list.begin() ; it != _mouse_listener_list.end() ; ++it) {
				(*it)->onMouseMove(ix, iy);
			}
		}

		void EventHub::onWheelMove(float iv, float ih) {
			std::vector<MouseListener*>::iterator it;
			for(it = _mouse_listener_list.begin() ; it != _mouse_listener_list.end() ; ++it) {
				(*it)->onWheelMove(iv, ih);
			}
		}

		void EventHub::onResize(size_t iwidth, size_t iheight) {
			std::vector<WindowListener*>::iterator it;
			for(it = _window_listener_list.begin() ; it != _window_listener_list.end() ; ++it) {
				(*it)->onResize(iwidth, iheight);
			}
		}

		void EventHub::onActivate() {
			std::vector<WindowListener*>::iterator it;
			for(it = _window_listener_list.begin() ; it != _window_listener_list.end() ; ++it) {
				(*it)->onActivate();
			}
		}

		void EventHub::onDeactivate() {
			std::vector<WindowListener*>::iterator it;
			for(it = _window_listener_list.begin() ; it != _window_listener_list.end() ; ++it) {
				(*it)->onDeactivate();
			}
		}

		void EventHub::onClose() {
			std::vector<WindowListener*>::iterator it;
			for(it = _window_listener_list.begin() ; it != _window_listener_list.end() ; ++it) {
				(*it)->onClose();
			}
		}

		void EventHub::onQuit() {
			std::vector<QuitListener*>::iterator it;
			for(it = _quit_listener_list.begin() ; it != _quit_listener_list.end() ; ++it) {
				(*it)->onQuit();
			}
		}
	}  // namespace input
}  // namespace cb
