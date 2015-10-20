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
#include <cb/input/input.hpp>

#include <cb/input/Key.hpp>
#include <cb/math/math.hpp>

#include <vector>

namespace cb {
	namespace input {
		class CbAPI EventHub {
		private:
			std::vector<KeyListener*> _key_listener_list;
			std::vector<CharListener*> _char_listener_list;
			std::vector<MouseListener*> _mouse_listener_list;
			std::vector<WindowListener*> _window_listener_list;
			std::vector<QuitListener*> _quit_listener_list;

		public:
			EventHub();
			~EventHub();

			void bind(KeyListener *ikey_listener);
			void bind(CharListener *ichar_listener);
			void bind(MouseListener *imouse_listener);
			void bind(WindowListener *iwindow_listener);
			void bind(QuitListener *iquit_listener);

			void unbind(KeyListener *ikey_listener);
			void unbind(CharListener *ichar_listener);
			void unbind(MouseListener *imouse_listener);
			void unbind(WindowListener *iwindow_listener);
			void unbind(QuitListener *iquit_listener);

			void onKeyPress(Key ikey);
			void onKeyRelease(Key ikey);
			void onKeyMove(Key ikey, float ivalue);

			void onChar(char32_t ichar);

			void onButtonPress(Key ikey, int ix, int iy);
			void onButtonRelease(Key ikey, int ix, int iy);
			void onMouseMove(int ix, int iy);
			void onWheelMove(float iv, float ih);

			void onResize(uint32 iwidth, uint32 iheight);
			void onActivate();
			void onDeactivate();
			void onClose();

			void onQuit();
		};

		inline EventHub::EventHub() {}
		inline EventHub::~EventHub() {}
	}  // namespace input
}  // namespace cb
