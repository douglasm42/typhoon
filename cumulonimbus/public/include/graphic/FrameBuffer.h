/* 
 * - Cumulonimbus - ☁
 * File: FrameBuffer.h
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

#include <graphic/Texture.h>

#include <vector>

namespace cb {
	namespace graphic {
		class CbAPI FrameBuffer {
		private:
			GLObject _id;

			Texture *_depth_buffer;
			std::vector<Texture *> _color_buffers;

		public:
			FrameBuffer();
			~FrameBuffer();

			void bind();
			void unbind();

			void validate();
			void clear();

			void attatch(Texture *irendertarget, size_t ilayer = 0);
			void attatch(Texture *irendertarget, tex::Target icube_face, size_t ilayer = 0);

			static size_t maxAttatchments();
		};
	}  // namespace graphic
}  // namespace cb
