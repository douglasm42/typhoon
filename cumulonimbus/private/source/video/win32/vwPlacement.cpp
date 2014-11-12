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

#include <video/win32/Windows.h>
#include <video/win32/WindowStyle.h>

namespace cb {
	namespace video {
		void getPlacement(const Placement &iplacement, WINDOWPLACEMENT &oplacement) {
			RECT window_rectangle;
			window_rectangle.left   = (long)iplacement.x();
			window_rectangle.top    = (long)iplacement.y();
			window_rectangle.right  = (long)(iplacement.width() + iplacement.x());
			window_rectangle.bottom = (long)(iplacement.height() + iplacement.y());

			if(iplacement.border() != Border::Empty) {
				AdjustWindowRectEx(&window_rectangle, getStyle(iplacement.border()), FALSE, getStyleEx(iplacement.border()));
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

			if(iplacement.minimized()) {
				oplacement.showCmd = SW_MINIMIZE;
				if(iplacement.maximized()) {
					oplacement.flags = WPF_RESTORETOMAXIMIZED;
				}
			} else if(iplacement.maximized()) {
				oplacement.showCmd = SW_MAXIMIZE;
			} else {
				oplacement.showCmd = SW_RESTORE;
			}
		}

		void getPlacement(const WINDOWPLACEMENT &iplacement, Border iborder, Placement &oplacement) {
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

			oplacement.pos(window_rectangle.left, window_rectangle.top);

			oplacement.size(window_rectangle.right - window_rectangle.left, window_rectangle.bottom - window_rectangle.top);

			if(iplacement.flags == WPF_RESTORETOMAXIMIZED || iplacement.showCmd == SW_MAXIMIZE) {
				oplacement.maximized(true);
			} else {
				oplacement.maximized(false);
			}

			if(iplacement.showCmd == SW_MINIMIZE) {
				oplacement.minimized(true);
			} else {
				oplacement.minimized(false);
			}

			oplacement.border(iborder);
		}
	}  // namespace video
}  // namespace cb
