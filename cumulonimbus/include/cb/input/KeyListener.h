/* 
 * - Cumulonimbus - ☁
 * File: KeyListener.h
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
		class CbAPI KeyListener {
		public:
			virtual void onKeyPress(Key ikey)=0;
			virtual void onKeyRelease(Key ikey)=0;
			virtual void onKeyMove(Key ikey, float ivalue)=0;
		};
	}  // namespace input
}  // namespace cb
