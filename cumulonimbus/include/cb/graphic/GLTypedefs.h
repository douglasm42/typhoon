/* 
 * - Cumulonimbus - ☁
 * File: GLTypedefs.h
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

#include <cb/graphic/graphic.h>

#include <cb/math/math.h>

#include <cb/graphic/GLEWmx.h>

namespace cb {
	namespace graphic {

		enum class Clear : uint8 {
			Color = 1,
			Depth = 2,
			ColorDepth = 3
		};

		enum class Capability : uint8 {
			DepthTest
		};
	}  // namespace graphic
}  // namespace cb
