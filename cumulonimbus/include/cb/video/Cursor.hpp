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

#include <cb/video/video.hpp>

#include <cb/data/Bitmap.hpp>

#ifdef CbWindows
#	include <cb/video/win32/Windows.hpp>
#endif

namespace cb {
	namespace video {
		class CbAPI Cursor {
		private:
#			ifdef CbWindows
				HCURSOR _w_hcursor;
#			endif

		public:
			Cursor(const data::ubBitmapRGBA &ibmp, uint32 ixhotspot, uint32 iyhotspot);
			Cursor(const data::ubBitmapRGB &ibmp, uint32 ixhotspot, uint32 iyhotspot, u8vec3 itransparent);
			~Cursor();

#			ifdef CbWindows
				HCURSOR wGetHCURSOR() const;

				static void wSet(Cursor *icursor);

				static void wShow(bool ishow_cursor);
				static void wHold(HWND iwindow, bool ihold_cursor);

				static void wSetPosition(HWND iwindow, ivec2 iposition);
				static ivec2 wGetPosition(HWND iwindow);

				static bool wIsInsideWindow(HWND iwindow);
#			endif
		};

#		ifdef CbWindows
			inline HCURSOR Cursor::wGetHCURSOR() const {return _w_hcursor;}
#		endif
	}  // namespace video
}  // namespace cb
