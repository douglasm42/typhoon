/* 
 * - Cumulonimbus - ☁
 * File: vPlacement.cpp
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
#include <cb/video/Placement.h>

#include <cb/video/Display.h>

namespace cb {
	namespace video {
		void Placement::centralize() {
			Display::Mode mode = Display::getActiveMode();
			_x = int(mode.width())/2 - _width/2;
			_y = int(mode.height())/2 - _height/2;
		}
	}  // namespace video
}  // namespace cb
