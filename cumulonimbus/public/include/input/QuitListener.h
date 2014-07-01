/* 
 * - Cumulonimbus - ☁
 * File: QuitListener.h
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
#include <input/input.h>

namespace cb {
	namespace input {
		class CbAPI QuitListener {
		public:
			virtual void onQuit()=0;
		};
	}  // namespace input
}  // namespace cb
