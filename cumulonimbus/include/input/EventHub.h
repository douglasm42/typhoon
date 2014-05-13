/* 
 * - Cumulonimbus - ☁
 * File: EventHub.h
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

#include <input/EventListener.h>
#include <list>

namespace cb {
	namespace input {
		class CbAPI EventHub {
		private:
			std::list<UpdateListener *> _update_listener;
			std::list<KeyListener *> _key_listener;
			std::list<WindowListener *> _window_listener;

		public:
			EventHub() {}
			~EventHub() {}

			void bind(UpdateListener *iupdate_listener);
			void bind(KeyListener *ikey_listener);
			void bind(WindowListener *iwindow_listener);

			void unbind(UpdateListener *iupdate_listener);
			void unbind(KeyListener *ikey_listener);
			void unbind(WindowListener *iwindow_listener);

			void onUpdateStart();
			void onUpdateEnd();
			void onQuit();

			void onKeyPress(KeyCode ikey_listener);
			void onKeyRelease(KeyCode ikey_listener);
			void onKeyMove(KeyCode ikey_listener, float ivalue);

			void onChar(base::lchar_t ichar);

			void onResize(size_t iwidth, size_t iheight);
			void onActivate();
			void onDeactivate();
			void onCreate();
			void onDestroy();
		};

		inline void EventHub::onUpdateStart() {
			std::list<UpdateListener *>::iterator it;
			for(it = _update_listener.begin() ; it != _update_listener.end() ; ++it) {
				(*it)->onUpdateStart();
			}
		}

		inline void EventHub::onUpdateEnd() {
			std::list<UpdateListener *>::iterator it;
			for(it = _update_listener.begin() ; it != _update_listener.end() ; ++it) {
				(*it)->onUpdateEnd();
			}
		}

		inline void EventHub::onQuit() {
			std::list<UpdateListener *>::iterator it;
			for(it = _update_listener.begin() ; it != _update_listener.end() ; ++it) {
				(*it)->onQuit();
			}
		}

		inline void EventHub::onKeyPress(KeyCode ikey_listener) {
			std::list<KeyListener *>::iterator it;
			for(it = _key_listener.begin() ; it != _key_listener.end() ; ++it) {
				(*it)->onKeyPress(ikey_listener);
			}
		}

		inline void EventHub::onKeyRelease(KeyCode ikey_listener) {
			std::list<KeyListener *>::iterator it;
			for(it = _key_listener.begin() ; it != _key_listener.end() ; ++it) {
				(*it)->onKeyRelease(ikey_listener);
			}
		}

		inline void EventHub::onKeyMove(KeyCode ikey_listener, float ivalue) {
			std::list<KeyListener *>::iterator it;
			for(it = _key_listener.begin() ; it != _key_listener.end() ; ++it) {
				(*it)->onKeyMove(ikey_listener, ivalue);
			}
		}

		inline void EventHub::onChar(base::lchar_t ichar) {
			std::list<KeyListener *>::iterator it;
			for(it = _key_listener.begin() ; it != _key_listener.end() ; ++it) {
				(*it)->onChar(ichar);
			}
		}

		inline void EventHub::onResize(size_t iwidth, size_t iheight) {
			std::list<WindowListener *>::iterator it;
			for(it = _window_listener.begin() ; it != _window_listener.end() ; ++it) {
				(*it)->onResize(iwidth, iheight);
			}
		}

		inline void EventHub::onActivate() {
			std::list<WindowListener *>::iterator it;
			for(it = _window_listener.begin() ; it != _window_listener.end() ; ++it) {
				(*it)->onActivate();
			}
		}

		inline void EventHub::onDeactivate() {
			std::list<WindowListener *>::iterator it;
			for(it = _window_listener.begin() ; it != _window_listener.end() ; ++it) {
				(*it)->onDeactivate();
			}
		}

		inline void EventHub::onCreate() {
			std::list<WindowListener *>::iterator it;
			for(it = _window_listener.begin() ; it != _window_listener.end() ; ++it) {
				(*it)->onCreate();
			}
		}

		inline void EventHub::onDestroy() {
			std::list<WindowListener *>::iterator it;
			for(it = _window_listener.begin() ; it != _window_listener.end() ; ++it) {
				(*it)->onDestroy();
			}
		}
	}  // namespace video
}  // namespace cb
