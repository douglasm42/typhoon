/* 
 * - Cumulonimbus - ☁
 * File: TextureHelper.h
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
#include <cb/graphic/tex/Texture.h>

namespace cb {
	namespace graphic {
		namespace tex {
#			define TextureValidateAddLOD \
			if(ilod > _lod_count) {\
				ThrowDet(tokurei::LoadFailed, "Invalid LOD.");\
			}

#			define TextureValidateLOD \
			if(ilod >= _lod_count) {\
				ThrowDet(tokurei::LoadFailed, "Invalid LOD.");\
			}

#			define TextureAddLOD \
			if(ilod == _lod_count) {\
				_lod_count++;\
			}

			inline bool isDepth(tex::Format iformat) {
				return iformat == tex::Format::Depth || iformat == tex::Format::Depth16 || iformat == tex::Format::Depth24 || iformat == tex::Format::Depth32 || iformat == tex::Format::Depth32f;
			}

			inline GLenum translateBmpFormat(data::bmp::Format iformat, tex::Format itexformat) {
				GLenum dic[] = {
					0,//Void = 0,

					GL_RED,//Luminance,
					GL_RG,//LA,
					GL_RGB,//RGB,
					GL_RGBA//RGBA,
				};
				if(iformat == data::bmp::Format::Luminance && isDepth(itexformat)) {
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

			inline GLenum translateBmpDataType(data::bmp::Type itype) {
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
				return dic[size_t(itype)];
			}
		}  // namespace tex
	}  // namespace graphic
}  // namespace cb
