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
#include <cb/graphic/graphic.h>

#include <cb/graphic/tex/Texture.h>
#include <cb/graphic/tex/CubeMap.h>

#include <cb/graphic/GLEWmx.h>

#include <vector>

namespace cb {
	namespace graphic {
		class CbAPI FrameBuffer {
		private:
			GLuint _id;

			Texture *_depth_buffer;
			std::vector<Texture *> _color_buffers;

		public:
			FrameBuffer();
			~FrameBuffer();

			void bind();
			void unbind();

			void validate();
			void clear();

			void attatch(Texture *irendertarget, uint32 ilayer = 0);
			void attatch(CubeMap *irendertarget, tex::CubeMapFace icube_face, uint32 ilayer = 0);

			static uint32 getMaxAttatchments();
		};
	}  // namespace graphic
}  // namespace cb
