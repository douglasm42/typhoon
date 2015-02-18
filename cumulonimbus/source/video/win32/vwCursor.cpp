/* 
 * - Cumulonimbus - ☁
 * File: vwCursor.cpp
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
#include <cb/video/Cursor.h>

#include <cb/base/Exception.h>
#include <cb/base/Log.h>

#include <cb/video/win32/BitmapToIcon.h>

namespace cb {
	namespace video {
		Cursor::Cursor(const data::ubBitmapRGBA &ibmp, uint32 ixhotspot, uint32 iyhotspot) {
			HCURSOR cur = bitmapToIcon(ibmp, ixhotspot, iyhotspot, FALSE);

			if(cur) {
				_w_hcursor = cur;
			} else {
				Throw(tokurei::CreateError);
			}
		}

		Cursor::Cursor(const data::ubBitmapRGB &ibmp, uint32 ixhotspot, uint32 iyhotspot, u8vec3 itransparent) {
			HCURSOR cur = bitmapToIcon(ibmp, ixhotspot, iyhotspot, itransparent, FALSE);

			if(cur) {
				_w_hcursor = cur;
			} else {
				Throw(tokurei::CreateError);
			}
		}

		Cursor::~Cursor() {
			DestroyIcon(_w_hcursor);
		}

		void Cursor::wSet(Cursor *icursor) {
			SetCursor(icursor->wGetHCURSOR());
		}

		void Cursor::wShow(bool ishow_cursor) {
			if(ishow_cursor) {
				while(ShowCursor(TRUE) < 0);
			} else {
				while(ShowCursor(FALSE) >= 0);
			}
		}

		void Cursor::wHold(HWND iwindow, bool ihold_cursor) {
			if(ihold_cursor) {
				//Prende o cursor dentro da janela.
				POINT p = {0, 0};
				ClientToScreen(iwindow, &p);

				RECT rect;
				GetClientRect(iwindow, &rect);
				rect.left += p.x;
				rect.right += p.x;
				rect.top += p.y;
				rect.bottom += p.y;
				ClipCursor(&rect);
			} else {
				ClipCursor(NULL);
			}
		}

		void Cursor::wSetPosition(HWND iwindow, ivec2 iposition) {
			POINT pt = {iposition.x, iposition.y};
			if(!ClientToScreen(iwindow, &pt)) {
				Throw(tokurei::SetFailed);
			}
			if(!SetCursorPos(pt.x,pt.y)) {
				Throw(tokurei::SetFailed);
			}
		}

		ivec2 Cursor::wGetPosition(HWND iwindow) {
			POINT pt = {0,0};
			if(!GetCursorPos(&pt)) {
				Throw(tokurei::GetFailed);
			}
			if(!ScreenToClient(iwindow, &pt)) {
				Throw(tokurei::SetFailed);
			}
			return ivec2(pt.x, pt.y);
		}
	}  // namespace video
}  // namespace cb
