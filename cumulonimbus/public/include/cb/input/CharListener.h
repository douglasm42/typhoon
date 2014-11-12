/* 
 * - Cumulonimbus - ☁
 * File: CharListener.h
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

#include <cstdlib>

namespace cb {
	namespace input {
		class CbAPI CharListener {
		public:
			virtual void onChar(char32_t ichar)=0;
		};
	}  // namespace input
}  // namespace cb
