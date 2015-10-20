/* 
 * - Cumulonimbus - ☁
 * File: vwBitmapToIcon.cpp
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
#include <cb/video/win32/BitmapToIcon.hpp>

namespace cb {
	namespace video {
		HICON CbAPI bitmapToIcon(const data::ubBitmapRGBA &ibmp, uint32 ixhotspot, uint32 iyhotspot, BOOL iicon) {
			HDC hMemDC;
			BITMAPV5HEADER bi;
			HBITMAP hBitmap, hOldBitmap;
			void *lpBits;

			uint32 width	= ibmp.width();
			uint32 height	= ibmp.height();

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

			for(uint32 x=0;x<width;++x) {
				for(uint32 y=0;y<height;++y) {
					u8vec4 color = ibmp(x,height-y-1,0).vec();
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
				for(uint32 x=0 ; x<width ; x++) {
					// Clear the alpha bits
					*lpdwPixel &= 0x00FFFFFF;
					// Set the alpha bits to 0x9F (semi-transparent)
					DWORD alpha = ibmp(x,height-y-1,0).a;

					*lpdwPixel |= alpha << 24;
					lpdwPixel++;
				}
			}

			ICONINFO ii;
			ii.fIcon = iicon;  // Change fIcon to TRUE to create an alpha icon
			ii.xHotspot = ixhotspot;
			ii.yHotspot = iyhotspot;
			ii.hbmMask = hMonoBitmap;
			ii.hbmColor = hBitmap;

			// Create the alpha cursor with the alpha DIB section.
			HICON icon = CreateIconIndirect(&ii);

			DeleteObject(hBitmap);
			DeleteObject(hMonoBitmap);

			ReleaseDC(NULL,hdc);

			return icon;
		}

		HICON CbAPI bitmapToIcon(const data::ubBitmapRGB &ibmp, uint32 ixhotspot, uint32 iyhotspot, u8vec3 itransparent, BOOL iicon) {
			HDC hDC        = GetDC(NULL);
			HDC hAndMaskDC = CreateCompatibleDC(hDC);
			HDC hXorMaskDC = CreateCompatibleDC(hDC);
 
			uint32 width	= ibmp.width();
			uint32 height	= ibmp.height();

			HBITMAP hAndMaskBitmap = CreateCompatibleBitmap(hDC, width, height);
			HBITMAP hXorMaskBitmap = CreateCompatibleBitmap(hDC, width, height);
 
			//Select the bitmaps to DC
			HBITMAP hOldAndMaskBitmap = (HBITMAP)SelectObject(hAndMaskDC,hAndMaskBitmap);
			HBITMAP hOldXorMaskBitmap = (HBITMAP)SelectObject(hXorMaskDC,hXorMaskBitmap);
 
			//Scan each pixel of the souce bitmap and create the masks
			for(uint32 x=0;x<width;++x) {
				for(uint32 y=0;y<height;++y) {
					u8vec3 color = ibmp(x,height-y-1,0).vec();
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
			iconinfo.fIcon		= iicon;
			iconinfo.xHotspot	= ixhotspot;
			iconinfo.yHotspot	= iyhotspot;
			iconinfo.hbmMask	= hAndMaskBitmap;
			iconinfo.hbmColor	= hXorMaskBitmap;

			HICON icon = CreateIconIndirect(&iconinfo);

			DeleteObject(hAndMaskBitmap);
			DeleteObject(hXorMaskBitmap);

			return icon;
		}
	}  // namespace video
}  // namespace cb
