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

#include <cb/video/video.h>

#include <video/win32/Windows.h>
#include <input/win32/DIMouse.h>
#include <input/win32/XInput.h>

namespace cb {
	namespace video {
		class CbAPI w32WindowInfo {
		public:
			HWND window;
			input::DIMouse *dimouse;
			input::XInput *xinput;

			w32WindowInfo() :window(nullptr), dimouse(nullptr) {}
		};
	}  // namespace video
}  // namespace cb
