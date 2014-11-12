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

#include <cb/video/video.h>

#include <video/win32/Windows.h>
#include <cb/data/Bitmap.h>

namespace cb {
	namespace video {
		HICON CbAPI bitmapToIcon(data::ubBitmapRGBA &ibmp, size_t ixhotspot, size_t iyhotspot, BOOL iicon);
		HICON CbAPI bitmapToIcon(data::ubBitmapRGB &ibmp, size_t ixhotspot, size_t iyhotspot, u8vec3 itransparent, BOOL iicon);
	}  // namespace video
}  // namespace cb
