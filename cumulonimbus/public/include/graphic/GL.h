/* 
 * - Cumulonimbus - ☁
 * File: GL.h
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
#include <graphic/GLTypedefs.h>

#include <graphic/VertexBuffer.h>
#include <data/Bitmap.h>

#include <vector>

namespace cb {
	namespace graphic {
		class CbAPI GL {
		public:
			virtual ~GL() {}

			void viewport(int ix, int iy, int iwidth, int iheight);
			void clear(Clear iflag);
			void clearColor(vec4 icolor);
			void clearDepth(double idepth);

			void texSquare(VertexBuffer &teste, VertexBuffer &grid);
		};
	}  // namespace graphic
}  // namespace cb
