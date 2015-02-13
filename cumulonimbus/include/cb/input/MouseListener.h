/* 
 * - Cumulonimbus - ☁
 * File: MouseListener.h
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
#include <cb/input/input.h>

#include <cb/input/Key.h>

namespace cb {
	namespace input {
		class CbAPI MouseListener {
		public:
			virtual void onButtonPress(Key ikey, int ix, int iy)=0;
			virtual void onButtonRelease(Key ikey, int ix, int iy)=0;
			virtual void onMouseMove(int ix, int iy)=0;
			virtual void onWheelMove(float iv, float ih)=0;
		};
	}  // namespace input
}  // namespace cb
