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
#include <cb/graphic/graphic.hpp>
#include <cb/graphic/GLTypedefs.hpp>

#include <cb/graphic/VertexBuffer.hpp>
#include <cb/graphic/Color.hpp>

#include <cb/data/Bitmap.hpp>

#include <vector>

namespace cb {
	namespace graphic {
		namespace gl {
			void CbAPI viewport(int ix, int iy, int iwidth, int iheight);
			void CbAPI clear(Clear iflag);
			void CbAPI clearColor(rgba icolor);
			void CbAPI clearDepth(double idepth);

			void CbAPI enable(Capability icap);
			void CbAPI disable(Capability icap);

			void CbAPI texSquare(VertexBuffer &teste, VertexBuffer &grid, Program &iprogram);

			void CbAPI shaderTest();
		}  // namespace gl
	}  // namespace graphic
}  // namespace cb
