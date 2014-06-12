/* 
 * - Cumulonimbus - ☁
 * File: Cursor.h
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

#include <base/Kin.h>

#include <data/Bitmap.h>

#include <map>

namespace cb {
	namespace video {
		KinLock(CursorHandler);

		class CbAPI Cursor {
		private:
			Window *_window;

			std::map<base::string, kin::CursorHandler> _cursors;
			kin::CursorHandler _active;

			bool _show;
			bool _hold;
			bool _is_active;

			Cursor(Window *iwindow);

		public:
			~Cursor();

			void show(bool ishow);
			bool show();

			void add(const base::string &ikey, data::ubBitmapRGBA &ibmp, size_t ixhotspot, size_t iyhotspot);
			void add(const base::string &ikey, data::ubBitmapRGB &ibmp, size_t ixhotspot, size_t iyhotspot, math::u8vec3 itransparent);
			void rem(const base::string &ikey);

			void select(const base::string &ikey);
			kin::CursorHandler &active() {return _active;}

			void hold(bool ihold);
			bool hold();

			bool isActive() const {return _is_active;}

			void move(size_t ix, size_t iy);

			void onActivate();
			void onDeactivate();
			void onCursorSet();
			void onResize();

			friend class CbAPI Window;
		};
	}  // namespace video
}  // namespace cb
