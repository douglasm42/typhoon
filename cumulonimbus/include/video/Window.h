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

#include <video/video.h>

#include <base/String.h>
#include <base/Kin.h>
#include <data/Bitmap.h>

#include <video/Display.h>
#include <video/Cursor.h>

#include <input/EventQueue.h>

namespace cb {
	namespace video {
		KinLock(WindowInfo);

		namespace win {
			class CbAPI Placement {
			private:
				size_t _x;
				size_t _y;
				size_t _width;
				size_t _height;
				bool _maximized;
				bool _minimized;
				bool _border;

				void ajust();

			public:
				Placement()
				:_x(0), _y(0), _width(0), _height(0), _maximized(false), _minimized(false), _border(false) {
				}

				Placement(size_t ix, size_t iy, size_t iwidth, size_t iheight, bool imaximized, bool iminimized, bool iborder)
				:_x(ix), _y(iy), _width(iwidth), _height(iheight), _maximized(imaximized), _minimized(iminimized), _border(iborder) {
					ajust();
				}

				size_t x() const {return _x;}
				size_t y() const {return _y;}
				size_t width() const {return _width;}
				size_t height() const {return _height;}

				void size(size_t iwidth, size_t iheight) {
					_width = iwidth;
					_height = iheight;
					ajust();
				}


				void pos(size_t ix, size_t iy) {
					_x = ix;
					_y = iy;
				}

				void maximize() {_maximized = true;}
				void minimize() {_minimized = true;}
				void restore() {_minimized = false;}

				bool maximized() const {return _maximized;}
				void maximized(bool imaximized) {_maximized = imaximized;}

				bool minimized() const {return _minimized;}
				void minimized(bool iminimized) {_minimized = iminimized;}

				bool border() const {return _border;}
				void border(bool iborder);

				void centralize() {
					disp::Mode mode = Display::activeMode();
					_x = mode.width()/2 - _width/2;
					_y = mode.height()/2 - _height/2;
				}

				friend class CbAPI cb::video::Window;
			};
		}  // namespace win

		class CbAPI Window {
		private:
			kin::WindowInfo _window_info;
			input::EventQueue _event_queue;
			Cursor _cursor;

			void create(base::wstring ititle, win::Placement iplacement);
			void destroy();

		public:
			Window(base::wstring ititle, win::Placement iplacement);
			Window(base::wstring ititle, size_t ix, size_t iy, size_t iwidth, size_t iheight, bool imaximized, bool iminimized, bool iborder);
			~Window();

			void title(base::wstring ititle);
			void title(base::string ititle) {title(base::utf16(ititle));}

			void placement(win::Placement iplacement);
			win::Placement placement();

			void resize(size_t iwidth, size_t iheight);
			void move(size_t ix, size_t iy);

			void border(bool iborder);
			bool border();

			void show();
			void hide();

			bool active();
			bool empty();

			Cursor &cursor() {return _cursor;}

			kin::WindowInfo &info() {return _window_info;}

			input::EventQueue &events() {return _event_queue;}
		};
	}  // namespace video
}  // namespace cb
