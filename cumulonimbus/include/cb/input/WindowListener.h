/* 
 * - Cumulonimbus - ☁
 * File: WindowListener.h
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

namespace cb {
	namespace input {
		class CbAPI WindowListener {
		public:
			virtual void onResize(size_t iwidth, size_t iheight)=0;
			virtual void onActivate()=0;
			virtual void onDeactivate()=0;
			virtual void onClose()=0;
		};
	}  // namespace input
}  // namespace cb
