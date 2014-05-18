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
#include <base/Setup.h>
#ifdef CbWindows

#include <video/Cursor.h>

#include <base/Exception.h>
#include <base/Log.h>

#include <video/win32/Windows.h>

namespace cb {
	namespace video {
		KinKey(kin::CursorHandler, HICON__);

		Cursor::Cursor():_show(true) {
		}
		
		Cursor::~Cursor() {
			SetCursor(NULL);
			std::map<base::string, kin::CursorHandler>::iterator it;
			for(it=_cursors.begin() ; it != _cursors.end() ; ++it) {
				DestroyIcon(&it->second);
			}
		}

		void Cursor::show(bool ishow) {
			_show = ishow;
			if(_show) {
				while(ShowCursor(TRUE) < 0);
			} else {
				while(ShowCursor(FALSE) >= 0);
			}
		}

		bool Cursor::show() {
			return _show;
		}

		void Cursor::add(const base::string &ikey, data::ubBitmapRGBA &ibmp, size_t ixhotspot, size_t iyhotspot) {
			HDC hMemDC;
			size_t width, height;
			BITMAPV5HEADER bi;
			HBITMAP hBitmap, hOldBitmap;
			void *lpBits;

			width	= ibmp.width();  // width of cursor
			height	= ibmp.height();  // height of cursor

			ZeroMemory(&bi,sizeof(BITMAPV5HEADER));
			bi.bV5Size			= sizeof(BITMAPV5HEADER);
			bi.bV5Width			= width;
			bi.bV5Height		= height;
			bi.bV5Planes		= 1;
			bi.bV5BitCount		= 32;
			bi.bV5Compression	= BI_BITFIELDS;
			// The following mask specification specifies a supported 32 BPP
			// alpha format for Windows XP.
			bi.bV5RedMask	= 0x00FF0000;
			bi.bV5GreenMask	= 0x0000FF00;
			bi.bV5BlueMask	= 0x000000FF;
			bi.bV5AlphaMask	= 0xFF000000;

			HDC hdc;
			hdc = GetDC(NULL);

			// Create the DIB section with an alpha channel.
			hBitmap = CreateDIBSection(hdc, (BITMAPINFO *)&bi, DIB_RGB_COLORS, (void **)&lpBits, NULL, (DWORD)0);

			hMemDC = CreateCompatibleDC(hdc);
			ReleaseDC(NULL,hdc);

			// Draw something on the DIB section.
			hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

			for(size_t x=0;x<ibmp.width();++x) {
				for(size_t y=0;y<ibmp.height();++y) {
					math::u8vec4 color = ibmp(x,y).vec();
					SetPixel(hMemDC,x,y,RGB(color.r, color.g, color.b));
				}
			}

			SelectObject(hMemDC, hOldBitmap);
			DeleteDC(hMemDC);

			// Create an empty mask bitmap.
			HBITMAP hMonoBitmap = CreateBitmap(width,height,1,1,NULL);

			// Set the alpha values for each pixel in the cursor so that
			// the complete cursor is semi-transparent.
			DWORD *lpdwPixel;
			lpdwPixel = (DWORD *)lpBits;
			for(int y=(height-1) ; y>=0 ; y--) {
				for(size_t x=0 ; x<width ; x++) {
					// Clear the alpha bits
					*lpdwPixel &= 0x00FFFFFF;
					// Set the alpha bits to 0x9F (semi-transparent)
					DWORD alpha = ibmp(x,y).a;

					*lpdwPixel |= alpha << 24;
					lpdwPixel++;
				}
			}

			ICONINFO ii;
			ii.fIcon = FALSE;  // Change fIcon to TRUE to create an alpha icon
			ii.xHotspot = ixhotspot;
			ii.yHotspot = iyhotspot;
			ii.hbmMask = hMonoBitmap;
			ii.hbmColor = hBitmap;

			// Create the alpha cursor with the alpha DIB section.
			HCURSOR cur = CreateIconIndirect(&ii);

			DeleteObject(hBitmap);
			DeleteObject(hMonoBitmap);

			ReleaseDC(NULL,hdc);

			if(cur) {
				std::map<base::string, kin::CursorHandler>::iterator it = _cursors.find(ikey);
				if(it != _cursors.end()) {
					rem(ikey);
				}
				_cursors[ikey] << cur;
			} else {
				Throw(tokurei::CreateError);
			}
		}

		void Cursor::add(const base::string &ikey, data::ubBitmapRGB &ibmp, size_t ixhotspot, size_t iyhotspot, math::u8vec3 itransparent) {
			HDC hDC        = GetDC(NULL);
			HDC hAndMaskDC = CreateCompatibleDC(hDC);
			HDC hXorMaskDC = CreateCompatibleDC(hDC);
 
			HBITMAP hAndMaskBitmap = CreateCompatibleBitmap(hDC, ibmp.width(), ibmp.height());
			HBITMAP hXorMaskBitmap = CreateCompatibleBitmap(hDC, ibmp.width(), ibmp.height());
 
			//Select the bitmaps to DC
			HBITMAP hOldAndMaskBitmap = (HBITMAP)SelectObject(hAndMaskDC,hAndMaskBitmap);
			HBITMAP hOldXorMaskBitmap = (HBITMAP)SelectObject(hXorMaskDC,hXorMaskBitmap);
 
			//Scan each pixel of the souce bitmap and create the masks
			COLORREF MainBitPixel;
			for(int x=0;x<ibmp.width();++x) {
				for(int y=0;y<ibmp.height();++y) {
					math::u8vec3 color = ibmp(x,y).vec();
					if(color == itransparent) {
						::SetPixel(hAndMaskDC,x,y,RGB(255,255,255));
						::SetPixel(hXorMaskDC,x,y,RGB(0,0,0));
					} else {
						::SetPixel(hAndMaskDC,x,y,RGB(0,0,0));
						::SetPixel(hXorMaskDC,x,y,RGB(color.r, color.g, color.b));
					}
				}
			}
 
			SelectObject(hAndMaskDC,hOldAndMaskBitmap);
			SelectObject(hXorMaskDC,hOldXorMaskBitmap);
 
			DeleteDC(hXorMaskDC);
			DeleteDC(hAndMaskDC);

			ReleaseDC(NULL,hDC);

			ICONINFO iconinfo = {0};
			iconinfo.fIcon		= FALSE;
			iconinfo.xHotspot	= ixhotspot;
			iconinfo.yHotspot	= iyhotspot;
			iconinfo.hbmMask	= hAndMaskBitmap;
			iconinfo.hbmColor	= hXorMaskBitmap;

			HCURSOR cur = CreateIconIndirect(&iconinfo);

			DeleteObject(hAndMaskBitmap);
			DeleteObject(hXorMaskBitmap);

			if(cur) {
				std::map<base::string, kin::CursorHandler>::iterator it = _cursors.find(ikey);
				if(it != _cursors.end()) {
					rem(ikey);
				}
				_cursors[ikey] << cur;
			} else {
				Throw(tokurei::CreateError);
			}
		}

		void Cursor::rem(const base::string &ikey) {
			std::map<base::string, kin::CursorHandler>::iterator it = _cursors.find(ikey);
			if(it != _cursors.end()) {
				if(it->second._pointer == _active._pointer) {
					SetCursor(NULL);
					_active << nullptr;
				}
				DestroyIcon(&it->second);
				_cursors.erase(it);
			}
		}

		void Cursor::select(const base::string &ikey) {
			std::map<base::string, kin::CursorHandler>::iterator it = _cursors.find(ikey);
			if(it != _cursors.end()) {
				if(it->second._pointer != _active._pointer) {
					_active._pointer = it->second._pointer;
					SetCursor(&_active);
				}
			} else {
				ThrowDet(tokurei::SetFailed, "Key: %s", ikey.c_str());
			}
		}

		void Cursor::set() {
			SetCursor(&_active);
		}
	}  // namespace video
}  // namespace cb

#endif
