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

namespace cb {
	namespace input {
		void EventHub::bind(UpdateListener *iupdate_listener) {
			if(iupdate_listener->_event_hub) {
				iupdate_listener->_event_hub->unbind(iupdate_listener);
			}
			iupdate_listener->_event_hub = this;
			_update_listener.push_back(iupdate_listener);
		}

		void EventHub::bind(KeyListener *ikey_listener) {
			if(ikey_listener->_event_hub) {
				ikey_listener->_event_hub->unbind(ikey_listener);
			}
			ikey_listener->_event_hub = this;
			_key_listener.push_back(ikey_listener);
		}

		void EventHub::bind(WindowListener *iwindow_listener) {
			if(iwindow_listener->_event_hub) {
				iwindow_listener->_event_hub->unbind(iwindow_listener);
			}
			iwindow_listener->_event_hub = this;
			_window_listener.push_back(iwindow_listener);
		}

		void EventHub::unbind(UpdateListener *iupdate_listener) {
			std::list<UpdateListener *>::iterator it;
			for(it = _update_listener.begin() ; it != _update_listener.end() ; ++it) {
				if((*it) == iupdate_listener) {
					_update_listener.erase(it);
					iupdate_listener->_event_hub = nullptr;
					return;
				}
			}
		}

		void EventHub::unbind(KeyListener *ikey_listener) {
			std::list<KeyListener *>::iterator it;
			for(it = _key_listener.begin() ; it != _key_listener.end() ; ++it) {
				if((*it) == ikey_listener) {
					_key_listener.erase(it);
					ikey_listener->_event_hub = nullptr;
					return;
				}
			}
		}

		void EventHub::unbind(WindowListener *iwindow_listener) {
			std::list<WindowListener *>::iterator it;
			for(it = _window_listener.begin() ; it != _window_listener.end() ; ++it) {
				if((*it) == iwindow_listener) {
					_window_listener.erase(it);
					iwindow_listener->_event_hub = nullptr;
					return;
				}
			}
		}
	}  // namespace input
}  // namespace cb

