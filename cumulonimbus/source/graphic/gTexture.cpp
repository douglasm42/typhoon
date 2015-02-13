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
#include <cb/graphic/Texture.h>

#include <cb/graphic/GLEWmx.h>

#include <cb/graphic/TextureTranslate.h>

namespace cb {
	namespace graphic {
		inline void validate(const data::Bitmap &ibmp, Texture::Target itarget, Texture::Format iformat) {
			if(itarget == Texture::Target::CubeMap) {
				Throw(tokurei::LoadFailed);
			}
			if(ibmp.format() != data::bmp::Format::Luminance && (iformat == Texture::Format::Depth || iformat == Texture::Format::Depth16 || iformat == Texture::Format::Depth24 || iformat == Texture::Format::Depth32 || iformat == Texture::Format::Depth32f)) {
				Throw(tokurei::LoadFailed);
			}
		}

		inline void validate(const data::Bitmap &ibmp_xp, const data::Bitmap &ibmp_xm, const data::Bitmap &ibmp_yp, const data::Bitmap &ibmp_ym, const data::Bitmap &ibmp_zp, const data::Bitmap &ibmp_zm, Texture::Target itarget, Texture::Format iformat) {
			if(itarget != Texture::Target::CubeMap) {
				Throw(tokurei::LoadFailed);
			}
			if((iformat == Texture::Format::Depth || iformat == Texture::Format::Depth16 || iformat == Texture::Format::Depth24 || iformat == Texture::Format::Depth32 || iformat == Texture::Format::Depth32f)
					&& (ibmp_xp.format() != data::bmp::Format::Luminance
					|| ibmp_xm.format() != data::bmp::Format::Luminance
					|| ibmp_yp.format() != data::bmp::Format::Luminance
					|| ibmp_ym.format() != data::bmp::Format::Luminance
					|| ibmp_zp.format() != data::bmp::Format::Luminance
					|| ibmp_zm.format() != data::bmp::Format::Luminance)
			) {
				Throw(tokurei::LoadFailed);
			}
			if(ibmp_xp.width() == ibmp_xp.height()
				&& ibmp_xp.width() == ibmp_xm.height()
				&& ibmp_xp.width() == ibmp_yp.height()
				&& ibmp_xp.width() == ibmp_ym.height()
				&& ibmp_xp.width() == ibmp_zp.height()
				&& ibmp_xp.width() == ibmp_zm.height()
			) {
				return;
			} else {
				Throw(tokurei::LoadFailed);
			}
		}


		Texture::Texture()
		:_id(0)
		,_format(Texture::Format::Void)
		,_target(Texture::Target::Void)

		,_wrap_s(Texture::Wrap::Repeat)
		,_wrap_t(Texture::Wrap::Repeat)
		,_wrap_r(Texture::Wrap::Repeat)

		,_min_filter(Texture::MinFilter::Nearest)
		,_mag_filter(Texture::MagFilter::Nearest)

		,_max_level(0) {
		}

		Texture::Texture(Texture::Target itarget, Texture::Format iformat)
		:_id(0)
		,_format(Texture::Format::Void)
		,_target(Texture::Target::Void)

		,_wrap_s(Texture::Wrap::Repeat)
		,_wrap_t(Texture::Wrap::Repeat)
		,_wrap_r(Texture::Wrap::Repeat)

		,_min_filter(Texture::MinFilter::Nearest)
		,_mag_filter(Texture::MagFilter::Nearest)

		,_max_level(0) {
			init(itarget, iformat);
		}

		Texture::~Texture() {
			clear();
		}

		void Texture::blank(size_t iwidth, size_t iheight, size_t idepth) {
			bind();

			GLenum target = GLenum(_target);
			GLenum internalformat = GLenum(_format);
			GLenum format = translateBmpFormat(data::bmp::Format::Luminance, _format);
			GLenum type = GL_UNSIGNED_BYTE;

			Texture::Size size;

			size.width = iwidth;
			size.height = iheight;
			size.depth = idepth;

			if(_target == Texture::Target::Tex2D || _target == Texture::Target::Rectangle || _target == Texture::Target::Tex1DArray) {
				glTexImage2D(target, (GLint)_size.size(), internalformat, (GLsizei)size.width, (GLsizei)size.height, 0, format, type, nullptr);

			} else if(_target == Texture::Target::Tex1D) {
				if(size.height > 1) {
					Throw(tokurei::LoadFailed);
				}
				glTexImage1D(target, (GLint)_size.size(), internalformat, (GLsizei)size.width, 0, format, type, nullptr);

			} else if(_target == Texture::Target::Tex3D || _target == Texture::Target::Tex2DArray) {
				glTexImage3D(target, (GLint)_size.size(), internalformat, (GLsizei)size.width, (GLsizei)size.height, (GLsizei)size.depth, 0, format, type, nullptr);
			} else {
				Throw(tokurei::LoadFailed);
			}

			_size.push_back(size);

			glCheckError();
		}

		void Texture::cubeMap(const data::Bitmap &ibmp_xp, const data::Bitmap &ibmp_xm, const data::Bitmap &ibmp_yp, const data::Bitmap &ibmp_ym, const data::Bitmap &ibmp_zp, const data::Bitmap &ibmp_zm) {
			bind();
			validate(ibmp_xp, ibmp_xm, ibmp_yp, ibmp_ym, ibmp_zp, ibmp_zm, _target, _format);
			const data::Bitmap *vbmp[] = {
				&ibmp_xp,
				&ibmp_xm,
				&ibmp_yp,
				&ibmp_ym,
				&ibmp_zp,
				&ibmp_zm
			};

			GLenum internalformat = GLenum(_format);
			GLenum format[] = {
				translateBmpFormat(ibmp_xp.format(), _format),
				translateBmpFormat(ibmp_xm.format(), _format),
				translateBmpFormat(ibmp_yp.format(), _format),
				translateBmpFormat(ibmp_ym.format(), _format),
				translateBmpFormat(ibmp_zp.format(), _format),
				translateBmpFormat(ibmp_zm.format(), _format)
			};

			GLenum type[] = {
				translateBmpType(ibmp_xp.type()),
				translateBmpType(ibmp_xm.type()),
				translateBmpType(ibmp_yp.type()),
				translateBmpType(ibmp_ym.type()),
				translateBmpType(ibmp_zp.type()),
				translateBmpType(ibmp_zm.type())
			};

			Texture::Size size;

			size.width = ibmp_xp.width();
			size.height = ibmp_xp.height();
			size.depth = 1;

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, (GLint)_size.size(), internalformat, (GLsizei)size.width, (GLsizei)size.height, 0, format[0], type[0], vbmp[0]->data());
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, (GLint)_size.size(), internalformat, (GLsizei)size.width, (GLsizei)size.height, 0, format[1], type[1], vbmp[1]->data());
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, (GLint)_size.size(), internalformat, (GLsizei)size.width, (GLsizei)size.height, 0, format[2], type[2], vbmp[2]->data());
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, (GLint)_size.size(), internalformat, (GLsizei)size.width, (GLsizei)size.height, 0, format[3], type[3], vbmp[3]->data());
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, (GLint)_size.size(), internalformat, (GLsizei)size.width, (GLsizei)size.height, 0, format[4], type[4], vbmp[4]->data());
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, (GLint)_size.size(), internalformat, (GLsizei)size.width, (GLsizei)size.height, 0, format[5], type[5], vbmp[5]->data());

			_size.push_back(size);

			glCheckError();
		}

		void Texture::image(const data::Bitmap &ibmp) {
			bind();
			validate(ibmp, _target, _format);

			GLenum target = GLenum(_target);
			GLenum internalformat = GLenum(_format);
			GLenum format = translateBmpFormat(ibmp.format(), _format);
			GLenum type = translateBmpType(ibmp.type());

			Texture::Size size;

			size.width = ibmp.width();
			size.height = ibmp.height();
			size.depth = ibmp.depth();

			if(_target == Texture::Target::Tex2D || _target == Texture::Target::Rectangle || _target == Texture::Target::Tex1DArray) {
				glTexImage2D(target, (GLint)_size.size(), internalformat, (GLsizei)size.width, (GLsizei)size.height, 0, format, type, ibmp.data());

			} else if(_target == Texture::Target::Tex1D) {
				glTexImage1D(target, (GLint)_size.size(), internalformat, (GLsizei)size.width, 0, format, type, ibmp.data());

			} else if(_target == Texture::Target::Tex3D || _target == Texture::Target::Tex2DArray) {
				glTexImage3D(target, (GLint)_size.size(), internalformat, (GLsizei)size.width, (GLsizei)size.height, (GLsizei)size.depth, 0, format, type, ibmp.data());
			} else {
				Throw(tokurei::LoadFailed);
			}

			_size.push_back(size);

			glCheckError();
		}

		void Texture::subImage(const data::Bitmap &ibmp, size_t ilevel, size_t ixoffset) {
			bind();
			validate(ibmp, _target, _format);

			GLenum target = GLenum(_target);
			GLenum internalformat = GLenum(_format);
			GLenum format = translateBmpFormat(ibmp.format(), _format);
			GLenum type = translateBmpType(ibmp.type());

			Texture::Size size;

			size.width = ibmp.width();
			size.height = ibmp.height();
			size.depth = 1;

			if(_target == Texture::Target::Tex1D) {
				if(size.height > 1) {
					Throw(tokurei::LoadFailed);
				}
				glTexSubImage1D(target, (GLint)ilevel, (GLint)ixoffset, (GLsizei)size.width, format, type, ibmp.data());
			} else {
				Throw(tokurei::LoadFailed);
			}

			_size.push_back(size);

			glCheckError();
		}

		void Texture::subImage(const data::Bitmap &ibmp, size_t ilevel, size_t ixoffset, size_t iyoffset) {
			bind();
			validate(ibmp, _target, _format);

			GLenum target = GLenum(_target);
			GLenum internalformat = GLenum(_format);
			GLenum format = translateBmpFormat(ibmp.format(), _format);
			GLenum type = translateBmpType(ibmp.type());

			Texture::Size size;

			size.width = ibmp.width();
			size.height = ibmp.height();
			size.depth = 1;

			_size.push_back(size);

			if(_target == Texture::Target::Tex2D || _target == Texture::Target::Rectangle || _target == Texture::Target::Tex1DArray) {
				glTexSubImage2D(target, (GLint)ilevel, (GLint)ixoffset, (GLint)iyoffset, (GLsizei)size.width, (GLsizei)size.height, format, type, ibmp.data());

			} else {
				Throw(tokurei::LoadFailed);
			}

			glCheckError();
		}

		void Texture::subImage(const data::Bitmap &ibmp, size_t ilevel, size_t ixoffset, size_t iyoffset, size_t izoffset) {
			bind();
			validate(ibmp, _target, _format);

			GLenum target = GLenum(_target);
			GLenum internalformat = GLenum(_format);
			GLenum format = translateBmpFormat(ibmp.format(), _format);
			GLenum type = translateBmpType(ibmp.type());

			Texture::Size size;

			size.width = ibmp.width();
			size.height = ibmp.height();
			size.depth = ibmp.depth();

			if(_target == Texture::Target::Tex3D || _target == Texture::Target::Tex2DArray) {
				glTexSubImage3D(target, (GLint)ilevel, (GLint)ixoffset, (GLint)iyoffset, (GLint)izoffset, (GLsizei)size.width, (GLsizei)size.height, (GLsizei)size.depth, format, type, ibmp.data());
			} else {
				Throw(tokurei::LoadFailed);
			}

			_size.push_back(size);

			glCheckError();
		}

		void Texture::init(Texture::Target itarget, Texture::Format iformat) {
			if(!empty()) {
				clear();
			}

			glGenTextures(1, &_id);
			_size.clear();

			_format = iformat;
			_target = itarget;

			wrap(Texture::Wrap::Repeat);

			minFilter(Texture::MinFilter::Nearest);
			magFilter(Texture::MagFilter::Nearest);

			_max_level = 0;
		}

		void Texture::clear() {
			if(!empty()) {
				glDeleteTextures(1, &_id);
				_id = 0;
				_size.clear();

				_format = Texture::Format::Void;
				_target = Texture::Target::Void;

				wrap(Texture::Wrap::Repeat);

				minFilter(Texture::MinFilter::Nearest);
				magFilter(Texture::MagFilter::Nearest);

				_max_level = 0;
			}
		}

		void Texture::bind() const {
			glBindTexture(GLenum(_target), _id);
		}

		void Texture::unbind() const {
			glBindTexture(GLenum(_target), 0);
		}

		void Texture::wrap(Texture::Wrap iwrap) {
			_wrap_s = iwrap;
			_wrap_t = iwrap;
			_wrap_r = iwrap;

			bind();

			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_S, GLenum(_wrap_s));
			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_T, GLenum(_wrap_t));
			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_R, GLenum(_wrap_r));
		}

		void Texture::wrapS(Texture::Wrap iwrap) {
			_wrap_s = iwrap;
			bind();
			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_S, GLenum(_wrap_s));
		}

		void Texture::wrapT(Texture::Wrap iwrap) {
			_wrap_t = iwrap;
			bind();
			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_T, GLenum(_wrap_t));
		}

		void Texture::wrapR(Texture::Wrap iwrap) {
			_wrap_r = iwrap;
			bind();
			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_R, GLenum(_wrap_r));
		}

		void Texture::minFilter(Texture::MinFilter ifilter) {
			_min_filter = ifilter;

			bind();

			glTexParameteri(GLenum(_target), GL_TEXTURE_MIN_FILTER, GLenum(_min_filter));
		}

		void Texture::magFilter(Texture::MagFilter ifilter) {
			_mag_filter = ifilter;

			bind();

			glTexParameteri(GLenum(_target), GL_TEXTURE_MAG_FILTER, GLenum(_mag_filter));
		}
	}  // namespace graphic
}  // namespace cb
