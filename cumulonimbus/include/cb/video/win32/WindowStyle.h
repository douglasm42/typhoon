/* 
 * - Cumulonimbus - ☁
 * File: WindowStyle.h
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

#include <cb/video/Placement.h>
#include <cb/video/win32/Windows.h>

namespace cb {
	namespace video {
		inline DWORD getStyle(Border iborder) {
			DWORD styles[] = {
				WS_POPUP | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CAPTION,//Empty
				WS_POPUP,//PopUp
				WS_OVERLAPPEDWINDOW//System
			};
			return styles[(int)iborder];
		}
		inline DWORD getStyleEx(Border iborder) {
			DWORD styles_ex[] = {
				WS_EX_WINDOWEDGE,//Empty
				WS_EX_TOPMOST,//PopUp
				0//System
			};
			return styles_ex[(int)iborder];
		}
	}  // namespace video
}  // namespace cb
