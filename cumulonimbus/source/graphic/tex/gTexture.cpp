/* 
 * - Cumulonimbus - ☁
 * File: g21Texture.cpp
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
#include <cb/graphic/tex/Texture.hpp>

#include <cb/graphic/GLEWmx.hpp>
#include <cb/graphic/tex/TextureHelper.hpp>

#include <cb/base/Log.hpp>

namespace cb {
	namespace graphic {
		Texture::Texture(tex::Target itarget, tex::Format iformat)
		:_id(0)
		,_format(iformat)
		,_target(itarget)

		,_min_filter(tex::MinFilter::NearestMipMapLinear)
		,_mag_filter(tex::MagFilter::Linear)

		,_lod_count(0)
		,_lod_base(0)
		,_lod_max(1000) {
			glGenTextures(1, &_id);

			_format = iformat;
		}

		Texture::~Texture() {
			glDeleteTextures(1, &_id);
		}

		bool Texture::isFormatValid(data::bmp::Format ibmp_format) {
			return true;//!(ibmp_format != data::bmp::Format::Luminance && isDepth(_format));
		}

		bool Texture::isValid(data::bmp::Format ibmp_format, uint32 iwidth, uint32 iheight, uint32 idepth, uint32 ilod) {
			return isFormatValid(ibmp_format) && isSizeValid(iwidth, iheight, idepth, ilod);
		}

		//------------------------------------------------------------------------------
		// - texImage -
		//------------------------------------------------------------------------------

		void Texture::texImage1D(uint32 ilod, uint32 ibmp_width, uint32 ibmp_height, uint32 ibmp_depth, data::bmp::Format ibmp_format, data::bmp::Type ibmp_type, const void *ibmp_data) {
			TextureValidateAddLOD;

			if(isValid(ibmp_format, ibmp_width, ibmp_height, ibmp_depth, ilod)) {
				bind();
				glTexImage1D(GLenum(_target), ilod, GLenum(_format), ibmp_width, 0, translateBmpFormat(ibmp_format, _format), tex::translateBmpDataType(ibmp_type), ibmp_data);
				glCheckError;

				TextureAddLOD;
			} else {
				Throw(tokurei::LoadFailed);
			}
		}

		void Texture::texImage2D(uint32 ilod, uint32 ibmp_width, uint32 ibmp_height, uint32 ibmp_depth, data::bmp::Format ibmp_format, data::bmp::Type ibmp_type, const void *ibmp_data) {
			TextureValidateAddLOD;

			if(isValid(ibmp_format, ibmp_width, ibmp_height, ibmp_depth, ilod)) {
				bind();
				glTexImage2D(GLenum(_target), ilod, GLenum(_format), ibmp_width, ibmp_height, 0, translateBmpFormat(ibmp_format, _format), tex::translateBmpDataType(ibmp_type), ibmp_data);
				glCheckError;

				if(ilod == _lod_count) {
					_lod_count++;
				}
			} else {
				Throw(tokurei::LoadFailed);
			}
		}

		void Texture::texImage3D(uint32 ilod, uint32 ibmp_width, uint32 ibmp_height, uint32 ibmp_depth, data::bmp::Format ibmp_format, data::bmp::Type ibmp_type, const void *ibmp_data) {
			TextureValidateAddLOD;

			if(isValid(ibmp_format, ibmp_width, ibmp_height, ibmp_depth, ilod)) {
				bind();
				glTexImage3D(GLenum(_target), ilod, GLenum(_format), ibmp_width, ibmp_height, ibmp_depth, 0, translateBmpFormat(ibmp_format, _format), tex::translateBmpDataType(ibmp_type), ibmp_data);
				glCheckError;

				TextureAddLOD;
			} else {
				Throw(tokurei::LoadFailed);
			}
		}

		//------------------------------------------------------------------------------
		// - texSubImage -
		//------------------------------------------------------------------------------

		void Texture::texSubImage1D(uint32 ilod, uint32 ixoffset, uint32 ibmp_width, data::bmp::Format ibmp_format, data::bmp::Type ibmp_type, const void *ibmp_data) {
			TextureValidateLOD;

			if(isFormatValid(ibmp_format)) {
				bind();
				glTexSubImage1D(GLenum(_target), ilod, ixoffset, ibmp_width, translateBmpFormat(ibmp_format, _format), tex::translateBmpDataType(ibmp_type), ibmp_data);
				glCheckError;
			} else {
				Throw(tokurei::LoadFailed);
			}
		}

		void Texture::texSubImage2D(uint32 ilod, uint32 ixoffset, uint32 iyoffset, uint32 ibmp_width, uint32 ibmp_height, data::bmp::Format ibmp_format, data::bmp::Type ibmp_type, const void *ibmp_data) {
			TextureValidateLOD;

			if(isFormatValid(ibmp_format)) {
				bind();
				glTexSubImage2D(GLenum(_target), ilod, ixoffset, iyoffset, ibmp_width, ibmp_height, translateBmpFormat(ibmp_format, _format), tex::translateBmpDataType(ibmp_type), ibmp_data);
				glCheckError;
			} else {
				Throw(tokurei::LoadFailed);
			}
		}

		void Texture::texSubImage3D(uint32 ilod, uint32 ixoffset, uint32 iyoffset, uint32 izoffset, uint32 ibmp_width, uint32 ibmp_height, uint32 ibmp_depth, data::bmp::Format ibmp_format, data::bmp::Type ibmp_type, const void *ibmp_data) {
			TextureValidateLOD;

			if(isFormatValid(ibmp_format)) {
				bind();
				glTexSubImage3D(GLenum(_target), ilod, ixoffset, iyoffset, izoffset, ibmp_width, ibmp_height, ibmp_depth, translateBmpFormat(ibmp_format, _format), tex::translateBmpDataType(ibmp_type), ibmp_data);
				glCheckError;
			} else {
				Throw(tokurei::LoadFailed);
			}
		}

		//------------------------------------------------------------------------------
		// - texImageCubeMap -
		//------------------------------------------------------------------------------

		void Texture::texImageCubeMap(tex::CubeMapFace iface, uint32 ilod, uint32 ibmp_width, uint32 ibmp_height, uint32 ibmp_depth, data::bmp::Format ibmp_format, data::bmp::Type ibmp_type, const void *ibmp_data) {
			TextureValidateAddLOD;

			if(isValid(ibmp_format, ibmp_width, ibmp_height, ibmp_depth, ilod)) {
				bind();
				glTexImage2D(GLenum(iface), ilod, GLenum(_format), ibmp_width, ibmp_height, 0, translateBmpFormat(ibmp_format, _format), tex::translateBmpDataType(ibmp_type), ibmp_data);
				glCheckError;

				TextureAddLOD;
			} else {
				Throw(tokurei::LoadFailed);
			}
		}

		void Texture::texSubImageCubeMap(tex::CubeMapFace iface, uint32 ilod, uint32 ixoffset, uint32 iyoffset, uint32 ibmp_width, uint32 ibmp_height, data::bmp::Format ibmp_format, data::bmp::Type ibmp_type, const void *ibmp_data) {
			TextureValidateLOD;

			if(isFormatValid(ibmp_format)) {
				bind();
				glTexSubImage2D(GLenum(iface), ilod, ixoffset, iyoffset, ibmp_width, ibmp_height, translateBmpFormat(ibmp_format, _format), tex::translateBmpDataType(ibmp_type), ibmp_data);
				glCheckError;
			} else {
				Throw(tokurei::LoadFailed);
			}
		}

		void Texture::bind() const {
			glBindTexture(GLenum(_target), _id);
		}
		void Texture::unbind() const {
			glBindTexture(GLenum(_target), 0);
		}

		void Texture::setMinFilter(tex::MinFilter ifilter) {
			_min_filter = ifilter;
			bind();
			glTexParameteri(GLenum(_target), GL_TEXTURE_MIN_FILTER, GLenum(_min_filter));
		}

		void Texture::setMagFilter(tex::MagFilter ifilter) {
			_mag_filter = ifilter;
			bind();
			glTexParameteri(GLenum(_target), GL_TEXTURE_MAG_FILTER, GLenum(_mag_filter));
		}

		void Texture::setLODBase(uint32 ilod) {
			_lod_base = ilod;
			glTexParameteri(GLenum(_target), GL_TEXTURE_BASE_LEVEL, ilod);
		}

		void Texture::setLODMax(uint32 ilod) {
			_lod_max = ilod;
			glTexParameteri(GLenum(_target), GL_TEXTURE_MAX_LEVEL, ilod);
		}
	}  // namespace graphic
}  // namespace cb
