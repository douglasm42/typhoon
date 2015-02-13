/* 
 * - Cumulonimbus - ☁
 * File: vwIcon.cpp
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
#include <cb/video/Icon.h>

#include <cb/base/Exception.h>
#include <cb/base/Log.h>

#include <cb/video/win32/BitmapToIcon.h>

namespace cb {
	namespace video {
		Icon::Icon(const data::ubBitmapRGBA &ibmp) {
			HICON cur = bitmapToIcon(ibmp, 0, 0, TRUE);

			if(cur) {
				_w_hicon = cur;
			} else {
				Throw(tokurei::CreateError);
			}
		}

		Icon::Icon(const data::ubBitmapRGB &ibmp, u8vec3 itransparent) {
			HICON cur = bitmapToIcon(ibmp, 0, 0, itransparent, TRUE);

			if(cur) {
				_w_hicon = cur;
			} else {
				Throw(tokurei::CreateError);
			}
		}

		Icon::~Icon() {
			DestroyIcon(_w_hicon);
		}

	}  // namespace video
}  // namespace cb
