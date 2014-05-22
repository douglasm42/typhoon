/* 
 * - Cumulonimbus - ☁
 * File: WindowInfo.h
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

#include <video/video.h>

#include <win32/video/Windows.h>
#include <win32/input/DIMouse.h>

namespace cb {
	namespace video {
		class CbAPI w32WindowInfo {
		public:
			HWND window;
			input::DIMouse *dimouse;

			w32WindowInfo() :window(nullptr), dimouse(nullptr) {}
		};
	}  // namespace video
}  // namespace cb
