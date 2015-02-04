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
#include <cb/video/Placement.h>

#include <cb/video/Window.h>
#include <cb/video/win32/WindowStyle.h>

namespace cb {
	namespace video {
		void Placement::wConvert(const Placement &iplacement, Border iborder, WINDOWPLACEMENT &oplacement) {
			RECT window_rectangle;
			window_rectangle.left   = (long)iplacement._x;
			window_rectangle.top    = (long)iplacement._y;
			window_rectangle.right  = (long)(iplacement._width + iplacement._x);
			window_rectangle.bottom = (long)(iplacement._height + iplacement._y);

			if(iborder != Border::Empty) {
				AdjustWindowRectEx(&window_rectangle, getStyle(iborder), FALSE, getStyleEx(iborder));
			}

			oplacement.length = sizeof(WINDOWPLACEMENT);

			oplacement.ptMaxPosition.x = 0;
			oplacement.ptMaxPosition.y = 0;

			oplacement.ptMinPosition.x = 0;
			oplacement.ptMinPosition.y = 0;

			oplacement.rcNormalPosition.left = window_rectangle.left;
			oplacement.rcNormalPosition.top = window_rectangle.top;
			oplacement.rcNormalPosition.right = window_rectangle.right;
			oplacement.rcNormalPosition.bottom = window_rectangle.bottom;

			oplacement.flags = 0;

			if(iplacement._minimized) {
				oplacement.showCmd = SW_MINIMIZE;
				if(iplacement._maximized) {
					oplacement.flags = WPF_RESTORETOMAXIMIZED;
				}
			} else if(iplacement._maximized) {
				oplacement.showCmd = SW_MAXIMIZE;
			} else {
				oplacement.showCmd = SW_RESTORE;
			}
		}

		void Placement::wConvert(const WINDOWPLACEMENT &iplacement, Border iborder, Placement &oplacement) {
			RECT window_rectangle;
			window_rectangle.left   = (long)0;
			window_rectangle.top    = (long)0;
			window_rectangle.right  = (long)0;
			window_rectangle.bottom = (long)0;

			if(iborder != Border::Empty) {
				AdjustWindowRectEx(&window_rectangle, getStyle(iborder), FALSE, getStyleEx(iborder));
			}

			window_rectangle.left = iplacement.rcNormalPosition.left - window_rectangle.left;
			window_rectangle.top = iplacement.rcNormalPosition.top - window_rectangle.top;
			window_rectangle.right = iplacement.rcNormalPosition.right - window_rectangle.right;
			window_rectangle.bottom = iplacement.rcNormalPosition.bottom - window_rectangle.bottom;

			oplacement._x = window_rectangle.left;
			oplacement._y = window_rectangle.top;

			oplacement._width = window_rectangle.right - window_rectangle.left;
			oplacement._width = window_rectangle.bottom - window_rectangle.top;

			if(iplacement.flags == WPF_RESTORETOMAXIMIZED || iplacement.showCmd == SW_MAXIMIZE) {
				oplacement._maximized = true;
			} else {
				oplacement._maximized = false;
			}

			if(iplacement.showCmd == SW_MINIMIZE) {
				oplacement._minimized = true;
			} else {
				oplacement._minimized = false;
			}
		}
	}  // namespace video
}  // namespace cb
