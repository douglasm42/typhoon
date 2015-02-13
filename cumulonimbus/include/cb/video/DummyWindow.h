/* 
 * - Cumulonimbus - ☁
 * File: DummyWindow.h
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

#ifdef CbWindows
#	include <cb/video/win32/Windows.h>
#endif

namespace cb {
	namespace video {
		class CbAPI DummyWindow {
		private:
#			ifdef CbWindows
				HWND _w_hwnd;
#			endif

		public:
			DummyWindow();
			~DummyWindow();

#			ifdef CbWindows
				HWND wGetHWND() const;
#			endif
		};

#		ifdef CbWindows
			HWND DummyWindow::wGetHWND() const {return _w_hwnd;}
#		endif
	}  // namespace video
}  // namespace cb
