/* 
 * - Cumulonimbus - ☁
 * File: vwWindowPlacement.cpp
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
#include <video/Window.h>

#include <video/win32/Windows.h>

namespace cb {
	namespace video {
		namespace win {
			void Placement::ajust() {
				DWORD style_ex = 0;
				DWORD style = 0;

				if(_border) {
					style_ex = 0;
					style = WS_OVERLAPPEDWINDOW;
				} else {
					style_ex = WS_EX_TOPMOST;
					style = WS_POPUP;
				}

				RECT window_rectangle;
				window_rectangle.left   = (long)0;
				window_rectangle.top    = (long)0;
				window_rectangle.right  = (long)_width;
				window_rectangle.bottom = (long)_height;

				AdjustWindowRectEx(&window_rectangle, style, FALSE, style_ex);

				_width = window_rectangle.right - window_rectangle.left;
				_height = window_rectangle.bottom - window_rectangle.top;
			}

			void Placement::border(bool iborder) {
				if(iborder && !_border) {
					ajust();
				} else if(!iborder && _border) {
					DWORD style_ex = 0;
					DWORD style = WS_OVERLAPPEDWINDOW;

					RECT window_rectangle;
					window_rectangle.left   = (long)0;
					window_rectangle.top    = (long)0;
					window_rectangle.right  = (long)0;
					window_rectangle.bottom = (long)0;

					AdjustWindowRectEx(&window_rectangle, style, FALSE, style_ex);

					_width -= window_rectangle.right - window_rectangle.left;
					_height -= window_rectangle.bottom - window_rectangle.top;
				}
				_border = iborder;
			}
		}  // namespace win
	}  // namespace video
}  // namespace cb
