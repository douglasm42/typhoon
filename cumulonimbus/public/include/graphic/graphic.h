/* 
 * - Cumulonimbus - ☁
 * File: graphic.h
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

#include <base/base.h>

#include <math/math.h>

namespace cb {
	namespace graphic {
		class CbAPI GLContext;

		class CbAPI Texture;
		class CbAPI RenderTarget;

		class CbAPI FrameBuffer;
		class CbAPI PixelBuffer;
		class CbAPI VertexBuffer;

		class CbAPI Shader;
		class CbAPI Program;

		namespace color {
			extern const CbAPI math::vec4 black;
			extern const CbAPI math::vec4 white;
			extern const CbAPI math::vec4 red;
			extern const CbAPI math::vec4 green;
			extern const CbAPI math::vec4 blue;

			extern const CbAPI math::vec4 butter1;
			extern const CbAPI math::vec4 butter2;
			extern const CbAPI math::vec4 butter3;
			extern const CbAPI math::vec4 chameleon1;
			extern const CbAPI math::vec4 chameleon2;
			extern const CbAPI math::vec4 chameleon3;
			extern const CbAPI math::vec4 orange1;
			extern const CbAPI math::vec4 orange2;
			extern const CbAPI math::vec4 orange3;
			extern const CbAPI math::vec4 sky1;
			extern const CbAPI math::vec4 sky2;
			extern const CbAPI math::vec4 sky3;
			extern const CbAPI math::vec4 plum1;
			extern const CbAPI math::vec4 plum2;
			extern const CbAPI math::vec4 plum3;
			extern const CbAPI math::vec4 chocolate1;
			extern const CbAPI math::vec4 chocolate2;
			extern const CbAPI math::vec4 chocolate3;
			extern const CbAPI math::vec4 scarlet1;
			extern const CbAPI math::vec4 scarlet2;
			extern const CbAPI math::vec4 scarlet3;
			extern const CbAPI math::vec4 aluminium1;
			extern const CbAPI math::vec4 aluminium2;
			extern const CbAPI math::vec4 aluminium3;
			extern const CbAPI math::vec4 aluminium4;
			extern const CbAPI math::vec4 aluminium5;
			extern const CbAPI math::vec4 aluminium6;
		}  // namespace color
	}  // namespace graphic
}  // namespace cb
