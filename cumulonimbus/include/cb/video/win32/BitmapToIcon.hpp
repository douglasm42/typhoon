/* 
 * - Cumulonimbus - ☁
 * File: BitmapToIcon.h
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

#include <cb/video/win32/Windows.hpp>
#include <cb/data/Bitmap.hpp>

namespace cb {
	namespace video {
		HICON CbAPI bitmapToIcon(const data::ubBitmapRGBA &ibmp, uint32 ixhotspot, uint32 iyhotspot, BOOL iicon);
		HICON CbAPI bitmapToIcon(const data::ubBitmapRGB &ibmp, uint32 ixhotspot, uint32 iyhotspot, u8vec3 itransparent, BOOL iicon);
	}  // namespace video
}  // namespace cb
