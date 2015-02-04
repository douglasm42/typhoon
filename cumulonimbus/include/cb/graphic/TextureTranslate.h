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
#include <cb/graphic/Texture.h>

namespace cb {
	namespace graphic {
		inline GLenum translateBmpFormat(data::bmp::Format iformat, Texture::Format itexformat) {
			GLenum dic[] = {
				0,//Void = 0,

				GL_RED,//Luminance,
				GL_RG,//LA,
				GL_RGB,//RGB,
				GL_RGBA//RGBA,
			};
			if(iformat == data::bmp::Format::Luminance && (itexformat == Texture::Format::Depth || itexformat == Texture::Format::Depth16 || itexformat == Texture::Format::Depth24 || itexformat == Texture::Format::Depth32f)) {
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
