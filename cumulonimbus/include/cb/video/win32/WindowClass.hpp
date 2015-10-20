/* 
 * - Cumulonimbus - ☁
 * File: WindowClass.h
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

namespace cb {
	namespace video {
		class CbAPI w32WindowClass {
		private:
			static const wchar_t *_name;
			static ATOM _atom;
			static size_t _window_count;

		public:
			static void reg();
			static void unreg();
			static const wchar_t *getName();
			static ATOM getATOM();
		};
	}  // namespace video
}  // namespace cb
