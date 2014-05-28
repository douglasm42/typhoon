/* 
 * - Cumulonimbus - ☁
 * File: Texture.h
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

#include <graphic/graphic.h>

#include <cstdint>

namespace cb {
	namespace graphic {
		enum class TextureType : uint8_t {
			Color = 1,
			Depth = 2
		};

		class CbAPI Texture {
		private:
			size_t _id;

		public:
			static void clear(uint32_t iflags);
		};
	}  // namespace graphic
}  // namespace cb
