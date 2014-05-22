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

#include <video/video.h>

#include <win32/video/Windows.h>

namespace cb {
	namespace video {
		class CbAPI w32WindowClass {
		private:
			static const wchar_t *_name;
			static size_t _window_count;

		public:
			static void reg();
			static void unreg();
			static const wchar_t *name() {return _name;}
		};
	}  // namespace video
}  // namespace cb
