/* 
 * - Cumulonimbus - ☁
 * File: Window.h
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

#include <cb/video/video.h>

#include <cb/base/String.h>
#include <cb/data/Bitmap.h>

#include <cb/video/Display.h>
#include <cb/video/Placement.h>
#include <cb/video/Cursor.h>
#include <cb/video/Icon.h>

#include <cb/input/EventHub.h>

#include <cb/graphic/PixelFormat.h>

#ifdef CbWindows
#	include <cb/video/win32/Windows.h>
#	include <cb/input/win32/DIMouse.h>
#	include <cb/input/win32/XInput.h>
#endif

namespace cb {
	namespace video {
		class CbAPI Window {
		private:
#			ifdef CbWindows
				HWND _w_hwnd;
				input::DIMouse *_w_dimouse;
				input::XInput *_w_xinput;
#			endif

			const Border _border;

			size_t _width;
			size_t _height;

			Cursor *_cursor;
			bool _cursor_show;
			bool _cursor_hold;
			ivec2 _cursor_held_position;

			Icon *_big_icon;
			Icon *_small_icon;

			input::EventHub *_event_hub;

			void create(base::string16 ititle, Border iborder);

		public:
			Window(base::string ititle, Border iborder);
			Window(base::string16 ititle, Border iborder);
			~Window();

			void setTitle(base::string16 ititle);
			void setTitle(base::string ititle);

			void setPlacement(const Placement &iplacement);
			Placement getPlacement();

			Border getBorder() const;

			void show();
			void hide();

			void minimize();
			void maximize();
			void restore();
			void close();

			bool isActive() const;

			Cursor *getCursor() const;
			void setCursor(Cursor *icursor);

			bool cursorIsShown();
			void cursorShow(bool ishow);

			bool cursorIsHeld();
			void cursorSetHold(bool ihold);

			void cursorSetPosition(ivec2 iposition);
			ivec2 cursorGetPosition();

			Icon *getBigIcon() const;
			void setBigIcon(Icon *ibig_icon);

			Icon *getSmallIcon() const;
			void setSmallIcon(Icon *ismall_icon);

			input::EventHub *getEventHub();
			void setEventHub(input::EventHub *ievent_hub);

			void onResize(size_t iwidth, size_t iheight);
			void onActivate();
			void onDeactivate();
			void onClose();

			void setPixelFormat(graphic::PixelFormat &ipf);

#			ifdef CbWindows
				HWND wGetHWND() const;
				input::DIMouse *wGetDIMouse() const;
				input::XInput *wGetXInput() const;
#			endif
		};

		inline void Window::setTitle(base::string ititle) {setTitle(base::utf16(ititle));}

		inline Border Window::getBorder() const {return _border;}

		inline Cursor *Window::getCursor() const {return _cursor;}

		inline Icon *Window::getBigIcon() const {return _big_icon;}
		inline Icon *Window::getSmallIcon() const {return _small_icon;}

		inline input::EventHub *Window::getEventHub() {return _event_hub;}

#		ifdef CbWindows
			inline HWND Window::wGetHWND() const {return _w_hwnd;}
			inline input::DIMouse *Window::wGetDIMouse() const {return _w_dimouse;}
			inline input::XInput *Window::wGetXInput() const {return _w_xinput;}
#		endif
	}  // namespace video
}  // namespace cb
