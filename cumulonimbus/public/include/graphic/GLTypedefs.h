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

#include <graphic/graphic.h>

namespace cb {
	namespace graphic {
		namespace tex {
			enum class Wrap : uint8_t {
				Repeat = 0,
				Mirror,
				Clamp
			};

			enum class MinFilter : uint8_t {
				Nearest = 0,
				Linear,
				NearestMipMapNearest,
				NearestMipMapLinear,
				LinearMipMapNearest,
				LinearMipMapLinear,
			};

			enum class MagFilter : uint8_t {
				Nearest = 0,
				Linear,
			};

			enum class Format : uint8_t {
				Void = 0,

				Depth,
				Depth16,
				Depth24,
				Depth32f,

				Red8,
				Red8s,
				Red16,
				Red16s,
				RG8,
				RG8s,
				RG16,
				RG16s,
				R3G3B2,
				RGB4,
				RGB5,
				RGB8,
				RGB8s,
				RGB10,
				RGB12,
				RGB16s,
				RGBA2,
				RGBA4,
				RGB5A1,
				RGBA8,
				RGBA8s,
				RGB10A2,
				RGB10A2ui,
				RGBA12,
				RGBA16,
				SRGB8,
				SRGB8A8,
				Red16f,
				RG16f,
				RGB16f,
				RGBA16f,
				Red32f,
				RG32f,
				RGB32f,
				RGBA32f,
				R11fG11fB10f,
				RGB9E5,
				Red8i,
				Red8ui,
				Red16i,
				Red16ui,
				Red32i,
				Red32ui,
				RG8i,
				RG8ui,
				RG16i,
				RG16ui,
				RG32i,
				RG32ui,
				RGB8i,
				RGB8ui,
				RGB16i,
				RGB16ui,
				RGB32i,
				RGB32ui,
				RGBA8i,
				RGBA8ui,
				RGBA16i,
				RGBA16ui,
				RGBA32i,
				RGBA32ui,

				CompRed,
				CompRG,
				CompRGB,
				CompRGBA,
				CompSRGB,
				CompSRGBA
			};

			enum class Target : uint8_t {
				Void = 0,

				Tex1D,
				Tex2D,
				Tex3D,

				Tex1DArray,
				Tex2DArray,

				Rectangle,
				CubeMap,
				CubeMapXp,
				CubeMapXm,
				CubeMapYp,
				CubeMapYm,
				CubeMapZp,
				CubeMapZm,
			};

			typedef struct {
				size_t width;
				size_t height;
				size_t depth;
			} Size;

		}  // namespace tex

		enum class Clear : uint8_t {
			Color = 1,
			Depth = 2,
			ColorDepth = 3
		};

		typedef unsigned int GLObject;
	}  // namespace graphic
}  // namespace cb
