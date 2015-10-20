/* 
 * - Cumulonimbus - ☁
 * File: Icon.h
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

#include <cb/data/Bitmap.hpp>

#ifdef CbWindows
#	include <cb/video/win32/Windows.hpp>
#endif

namespace cb {
	namespace video {
		class CbAPI Icon {
		private:
#			ifdef CbWindows
				HICON _w_hicon;
#			endif

		public:
			Icon(const data::ubBitmapRGBA &ibmp);
			Icon(const data::ubBitmapRGB &ibmp, u8vec3 itransparent);
			~Icon();

#			ifdef CbWindows
				HICON wGetHICON() const;
#			endif
		};

#		ifdef CbWindows
			inline HICON Icon::wGetHICON() const {return _w_hicon;}
#		endif
	}  // namespace video
}  // namespace cb
