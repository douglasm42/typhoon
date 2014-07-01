/* 
 * - Cumulonimbus - ☁
 * File: TextureTranslate.h
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
#include <graphic/Texture.h>

#include <graphic/GLEWmx.h>

namespace cb {
	namespace graphic {
		inline GLenum translateTarget(tex::Target itarget) {
			GLenum dic[] = {
				0,								//Void

				GL_TEXTURE_1D,					//Tex1D
				GL_TEXTURE_2D,					//Tex2D
				GL_TEXTURE_3D,					//Tex3D

				GL_TEXTURE_1D_ARRAY,			//Tex1DArray
				GL_TEXTURE_2D_ARRAY,			//Tex2DArray

				GL_TEXTURE_RECTANGLE,			//Rectangle

				GL_TEXTURE_CUBE_MAP,			//CubeMap
				GL_TEXTURE_CUBE_MAP_POSITIVE_X,	//CubeMapXp
				GL_TEXTURE_CUBE_MAP_NEGATIVE_X,	//CubeMapXm
				GL_TEXTURE_CUBE_MAP_POSITIVE_Y,	//CubeMapYp
				GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,	//CubeMapYm
				GL_TEXTURE_CUBE_MAP_POSITIVE_Z,	//CubeMapZp
				GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,	//CubeMapZm
			};
			if(itarget == tex::Target::CubeMap) {
				Throw(tokurei::LoadFailed);
			}
			return dic[size_t(itarget)];
		}

		inline GLenum translateWrap(tex::Wrap iwrap) {
			GLenum dic[] = {
				GL_REPEAT,			//Repeat
				GL_MIRRORED_REPEAT,	//Mirror
				GL_CLAMP_TO_EDGE	//Clamp
			};
			return dic[size_t(iwrap)];
		}

		inline GLenum translateMinFilter(tex::MinFilter ifilter) {
			GLenum dic[] = {
				GL_NEAREST,					//Nearest
				GL_LINEAR,					//Linear
				GL_NEAREST_MIPMAP_NEAREST,	//NearestMipMapNearest
				GL_NEAREST_MIPMAP_LINEAR,	//NearestMipMapLinear
				GL_LINEAR_MIPMAP_NEAREST,	//LinearMipMapNearest
				GL_LINEAR_MIPMAP_LINEAR		//LinearMipMapLinear
			};
			return dic[size_t(ifilter)];
		}

		inline GLenum translateMagFilter(tex::MagFilter ifilter) {
			GLenum dic[] = {
				GL_NEAREST,					//Nearest
				GL_LINEAR,					//Linear
			};
			return dic[size_t(ifilter)];
		}

		inline GLenum translateFormat(tex::Format iformat) {
			GLenum dic[] = {
				0,							//Void

				GL_DEPTH_COMPONENT16,		//Depth
				GL_DEPTH_COMPONENT24,		//Depth16
				GL_DEPTH_COMPONENT32,		//Depth24
				GL_DEPTH_COMPONENT32F,		//Depth32f

				GL_R8,						//Red8
				GL_R8_SNORM,				//Red8s
				GL_R16,						//Red16
				GL_R16_SNORM,				//Red16s
				GL_RG8,						//RG8
				GL_RG8_SNORM,				//RG8s
				GL_RG16,					//RG16
				GL_RG16_SNORM,				//RG16s
				GL_R3_G3_B2,				//R3G3B2
				GL_RGB4,					//RGB4
				GL_RGB5,					//RGB5
				GL_RGB8,					//RGB8
				GL_RGB8_SNORM,				//RGB8s
				GL_RGB10,					//RGB10
				GL_RGB12,					//RGB12
				GL_RGB16_SNORM,				//RGB16s
				GL_RGBA2,					//RGBA2
				GL_RGBA4,					//RGBA4
				GL_RGB5_A1,					//RGB5A1
				GL_RGBA8,					//RGBA8
				GL_RGBA8_SNORM,				//RGBA8s
				GL_RGB10_A2,				//RGB10A2
				GL_RGB10_A2UI,				//RGB10A2ui
				GL_RGBA12,					//RGBA12
				GL_RGBA16,					//RGBA16
				GL_SRGB8,					//SRGB8
				GL_SRGB8_ALPHA8,			//SRGB8A8
				GL_R16F,					//Red16f
				GL_RG16F,					//RG16f
				GL_RGB16F,					//RGB16f
				GL_RGBA16F,					//RGBA16f
				GL_R32F,					//Red32f
				GL_RG32F,					//RG32f
				GL_RGB32F,					//RGB32f
				GL_RGBA32F,					//RGBA32f
				GL_R11F_G11F_B10F,			//R11fG11fB10f
				GL_RGB9_E5,					//RGB9E5
				GL_R8I,						//Red8i
				GL_R8UI,					//Red8ui
				GL_R16I,					//Red16i
				GL_R16UI,					//Red16ui
				GL_R32I,					//Red32i
				GL_R32UI,					//Red32ui
				GL_RG8I,					//RG8i
				GL_RG8UI,					//RG8ui
				GL_RG16I,					//RG16i
				GL_RG16UI,					//RG16ui
				GL_RG32I,					//RG32i
				GL_RG32UI,					//RG32ui
				GL_RGB8I,					//RGB8i
				GL_RGB8UI,					//RGB8ui
				GL_RGB16I,					//RGB16i
				GL_RGB16UI,					//RGB16ui
				GL_RGB32I,					//RGB32i
				GL_RGB32UI,					//RGB32ui
				GL_RGBA8I,					//RGBA8i
				GL_RGBA8UI,					//RGBA8ui
				GL_RGBA16I,					//RGBA16i
				GL_RGBA16UI,				//RGBA16ui
				GL_RGBA32I,					//RGBA32i
				GL_RGBA32UI,				//RGBA32ui

				GL_COMPRESSED_RED,			//CompRed
				GL_COMPRESSED_RG,			//CompRG
				GL_COMPRESSED_RGB,			//CompRGB
				GL_COMPRESSED_RGBA,			//CompRGBA
				GL_COMPRESSED_SRGB,			//CompSRGB
				GL_COMPRESSED_SRGB_ALPHA,	//CompSRGBA
			};
			return dic[size_t(iformat)];
		}

		inline GLenum translateBmpFormat(data::bmp::Format iformat, tex::Format itexformat) {
			GLenum dic[] = {
				0,//Void = 0,

				GL_RED,//Luminance,
				GL_RG,//LA,
				GL_RGB,//RGB,
				GL_RGBA//RGBA,
			};
			if(iformat == data::bmp::Format::Luminance && (itexformat == tex::Format::Depth || itexformat == tex::Format::Depth16 || itexformat == tex::Format::Depth24 || itexformat == tex::Format::Depth32f)) {
				return GL_DEPTH_COMPONENT;
			}
			return dic[size_t(iformat)];
		}

		inline GLenum translateBmpFormatInt(data::bmp::Format iformat) {
			GLenum dic[] = {
				0,					//Void

				GL_RED_INTEGER,		//Luminance
				GL_RG_INTEGER,		//LA
				GL_RGB_INTEGER,		//RGB
				GL_RGBA_INTEGER		//RGBA
			};
			return dic[size_t(iformat)];
		}

		inline GLenum translateBmpType(data::bmp::Type itarget) {
			GLenum dic[] = {
				0,//Void

				GL_BYTE,//Byte
				GL_UNSIGNED_BYTE,//UByte

				GL_SHORT,//Int16
				GL_UNSIGNED_SHORT,//UInt16

				GL_INT,//Int32
				GL_UNSIGNED_INT,//UInt32

				GL_FLOAT//Float
			};
			return dic[size_t(itarget)];
		}
	}  // namespace graphic
}  // namespace cb
