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
#include <video/Placement.h>
#include <video/Cursor.h>

#include <input/EventHub.h>

namespace cb {
	namespace video {
		KinLock(WindowInfo);

		class CbAPI Window {
		private:
			kin::WindowInfo _window_info;
			Border _border;
			input::EventHub _event_hub;
			Cursor _cursor;

			void create(base::string16 ititle, const Placement &iplacement);
			void destroy();

		public:
			Window(base::string16 ititle, const Placement &iplacement);
			Window(base::string16 ititle, int ix, int iy, int iwidth, int iheight, bool imaximized, bool iminimized, Border iborder);
			~Window();

			void title(base::string16 ititle);
			void title(base::string ititle) {title(base::utf16(ititle));}

			void placement(const Placement &iplacement);
			Placement placement();

			void resize(int iwidth, int iheight);
			void move(int ix, int iy);

			void border(Border iborder);
			Border border() const {return _border;}

			void show();
			void hide();

			void minimize();
			void maximize();
			void restore();
			void close();

			bool active();
			bool empty();

			void icon(data::ubBitmapRGBA &ibmp);
			void icon(data::ubBitmapRGB &ibmp, u8vec3 itransparent);

			Cursor &cursor() {return _cursor;}

			kin::WindowInfo &info() {return _window_info;}

			input::EventHub &eventhub() {return _event_hub;}
		};
	}  // namespace video
}  // namespace cb
