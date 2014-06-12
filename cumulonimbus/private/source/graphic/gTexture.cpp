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

		inline void validate(const data::Bitmap &ibmp, tex::Target itarget, tex::Format iformat) {
			if((itarget == tex::Target::Tex1D && ibmp.height() != 1) || itarget == tex::Target::CubeMap) {
				Throw(tokurei::LoadFailed);
			}
			if(ibmp.format() != data::bmp::Format::Luminance && (iformat == tex::Format::Depth || iformat == tex::Format::Depth16 || iformat == tex::Format::Depth24 || iformat == tex::Format::Depth32f)) {
				Throw(tokurei::LoadFailed);
			}
		}

		inline void validate(const std::vector<data::Bitmap> &ivbmp, tex::Target itarget, tex::Format iformat) {
			if(itarget != tex::Target::Tex3D && itarget != tex::Target::Tex2DArray) {
				Throw(tokurei::LoadFailed);
			}
			if(iformat == tex::Format::Depth || iformat == tex::Format::Depth16 || iformat == tex::Format::Depth24 || iformat == tex::Format::Depth32f) {
				for(size_t i=0 ; i<ivbmp.size() ; i++) {
					if(ivbmp[i].format() != data::bmp::Format::Luminance) {
						Throw(tokurei::LoadFailed);
					}
				}
			}
		}

		inline void validate(const data::Bitmap &ibmp_xp, const data::Bitmap &ibmp_xm, const data::Bitmap &ibmp_yp, const data::Bitmap &ibmp_ym, const data::Bitmap &ibmp_zp, const data::Bitmap &ibmp_zm, tex::Target itarget, tex::Format iformat) {
			if(itarget != tex::Target::CubeMap) {
				Throw(tokurei::LoadFailed);
			}
			if((iformat == tex::Format::Depth || iformat == tex::Format::Depth16 || iformat == tex::Format::Depth24 || iformat == tex::Format::Depth32f)
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


		Texture::Texture(tex::Target itarget, tex::Format iformat)
		:_id(0)
		,_format(iformat)
		,_target(itarget)

		,_wrap_s(tex::Wrap::Repeat)
		,_wrap_t(tex::Wrap::Repeat)
		,_wrap_r(tex::Wrap::Repeat)

		,_min_filter(tex::MinFilter::Nearest)
		,_mag_filter(tex::MagFilter::Nearest)

		,_max_level(0) {
			glGenTextures(1, &_id);

			wrapS(_wrap_s);
			wrapT(_wrap_t);
			wrapR(_wrap_r);

			minFilter(_min_filter);
			magFilter(_mag_filter);
		}

		Texture::~Texture() {
			glDeleteTextures(1, &_id);
		}

		void Texture::blank(size_t iwidth, size_t iheight, size_t idepth) {
			bind();
			clear(_target, _format);

			GLenum target = translateTarget(_target);
			GLenum internalformat = translateFormat(_format);
			GLenum format = translateBmpFormat(data::bmp::Format::Luminance, _format);
			GLenum type = GL_UNSIGNED_BYTE;

			tex::Size size;

			size.width = iwidth;
			size.height = iheight;
			size.depth = idepth;

			if(_target == tex::Target::Tex2D || _target == tex::Target::Rectangle || _target == tex::Target::Tex1DArray) {
				glTexImage2D(target, _size.size(), internalformat, size.width, size.height, 0, format, type, nullptr);

			} else if(_target == tex::Target::Tex1D) {
				if(size.height > 1) {
					Throw(tokurei::LoadFailed);
				}
				glTexImage1D(target, _size.size(), internalformat, size.width, 0, format, type, nullptr);

			} else if(_target == tex::Target::Tex3D || _target == tex::Target::Tex2DArray) {
				glTexImage3D(target, _size.size(), internalformat, size.width, size.height, size.depth, 0, format, type, nullptr);
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

			GLenum internalformat = translateFormat(_format);
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

			tex::Size size;

			size.width = ibmp_xp.width();
			size.height = ibmp_xp.height();
			size.depth = 1;

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, _size.size(), internalformat, size.width, size.height, 0, format[0], type[0], vbmp[0]->data());
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, _size.size(), internalformat, size.width, size.height, 0, format[1], type[1], vbmp[1]->data());
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, _size.size(), internalformat, size.width, size.height, 0, format[2], type[2], vbmp[2]->data());
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, _size.size(), internalformat, size.width, size.height, 0, format[3], type[3], vbmp[3]->data());
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, _size.size(), internalformat, size.width, size.height, 0, format[4], type[4], vbmp[4]->data());
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, _size.size(), internalformat, size.width, size.height, 0, format[5], type[5], vbmp[5]->data());

			_size.push_back(size);

			glCheckError();
		}

		void Texture::image(const data::Bitmap &ibmp) {
			bind();
			validate(ibmp, _target, _format);

			GLenum target = translateTarget(_target);
			GLenum internalformat = translateFormat(_format);
			GLenum format = translateBmpFormat(ibmp.format(), _format);
			GLenum type = translateBmpType(ibmp.type());

			tex::Size size;

			size.width = ibmp.width();
			size.height = ibmp.height();
			size.depth = 1;

			if(_target == tex::Target::Tex2D || _target == tex::Target::Rectangle || _target == tex::Target::Tex1DArray) {
				glTexImage2D(target, _size.size(), internalformat, size.width, size.height, 0, format, type, ibmp.data());

			} else if(_target == tex::Target::Tex1D) {
				glTexImage1D(target, _size.size(), internalformat, size.width, 0, format, type, ibmp.data());

			} else if(_target == tex::Target::Tex3D || _target == tex::Target::Tex2DArray) {
				glTexImage3D(target, _size.size(), internalformat, size.width, size.height, size.depth, 0, format, type, ibmp.data());
			} else {
				Throw(tokurei::LoadFailed);
			}

			_size.push_back(size);

			glCheckError();
		}

		void Texture::image(const std::vector<data::Bitmap> &ivbmp) {
			bind();
			validate(ivbmp, _target, _format);

			GLenum target = translateTarget(_target);
			GLenum internalformat = translateFormat(_format);
			GLenum format = GL_COMPRESSED_RED;
			GLenum type = GL_UNSIGNED_BYTE;

			if(_format != tex::Format::Depth && _format != tex::Format::Depth16 && _format != tex::Format::Depth24 && _format != tex::Format::Depth32f) {
				format = GL_DEPTH_COMPONENT;
			}

			tex::Size size;

			size.width = ivbmp[0].width();
			size.height = ivbmp[0].height();
			size.depth = ivbmp.size();

			for(size_t i=1 ; i<size.depth ; i++) {
				if(size.width < ivbmp[i].width()) {
					size.width = ivbmp[i].width();
				}

				if(size.height < ivbmp[i].height()) {
					size.height = ivbmp[i].height();
				}
			}

			size_t level = _size.size();

			glTexImage3D(target, level, internalformat, size.width, size.height, size.depth, 0, format, type, nullptr);
			for(size_t i=1 ; i<size.depth ; i++) {
				format = translateBmpFormat(ivbmp[i].format(), _format);
				type = translateBmpType(ivbmp[i].type());

				glTexSubImage3D(target, level, 0, 0, i, ivbmp[i].width(), ivbmp[i].height(), 1, format, type, ivbmp[i].data());
			}

			_size.push_back(size);

			glCheckError();
		}

		void Texture::subImage(const data::Bitmap &ibmp, size_t ilevel, size_t ixoffset) {
			bind();
			validate(ibmp, _target, _format);

			GLenum target = translateTarget(_target);
			GLenum internalformat = translateFormat(_format);
			GLenum format = translateBmpFormat(ibmp.format(), _format);
			GLenum type = translateBmpType(ibmp.type());

			tex::Size size;

			size.width = ibmp.width();
			size.height = ibmp.height();
			size.depth = 1;

			if(_target == tex::Target::Tex1D) {
				if(size.height > 1) {
					Throw(tokurei::LoadFailed);
				}
				glTexSubImage1D(target, ilevel, ixoffset, size.width, format, type, ibmp.data());
			} else {
				Throw(tokurei::LoadFailed);
			}

			_size.push_back(size);

			glCheckError();
		}

		void Texture::subImage(const data::Bitmap &ibmp, size_t ilevel, size_t ixoffset, size_t iyoffset) {
			bind();
			validate(ibmp, _target, _format);

			GLenum target = translateTarget(_target);
			GLenum internalformat = translateFormat(_format);
			GLenum format = translateBmpFormat(ibmp.format(), _format);
			GLenum type = translateBmpType(ibmp.type());

			tex::Size size;

			size.width = ibmp.width();
			size.height = ibmp.height();
			size.depth = 1;

			_size.push_back(size);

			if(_target == tex::Target::Tex2D || _target == tex::Target::Rectangle || _target == tex::Target::Tex1DArray) {
				glTexSubImage2D(target, ilevel, ixoffset, iyoffset, size.width, size.height, format, type, ibmp.data());

			} else {
				Throw(tokurei::LoadFailed);
			}

			glCheckError();
		}

		void Texture::subImage(const data::Bitmap &ibmp, size_t ilevel, size_t ixoffset, size_t iyoffset, size_t izoffset) {
			bind();
			validate(ibmp, _target, _format);

			GLenum target = translateTarget(_target);
			GLenum internalformat = translateFormat(_format);
			GLenum format = translateBmpFormat(ibmp.format(), _format);
			GLenum type = translateBmpType(ibmp.type());

			tex::Size size;

			size.width = ibmp.width();
			size.height = ibmp.height();
			size.depth = 1;

			if(_target == tex::Target::Tex3D || _target == tex::Target::Tex2DArray) {
				glTexSubImage3D(target, ilevel, ixoffset, iyoffset, izoffset, size.width, size.height, size.depth, format, type, ibmp.data());
			} else {
				Throw(tokurei::LoadFailed);
			}

			_size.push_back(size);

			glCheckError();
		}

		void Texture::subImage(const std::vector<data::Bitmap> &ivbmp, size_t ilevel, size_t ixoffset, size_t iyoffset, size_t izoffset) {
			bind();
			validate(ivbmp, _target, _format);

			GLenum target = translateTarget(_target);
			GLenum internalformat = translateFormat(_format);
			GLenum format;
			GLenum type;

			tex::Size size;

			size.width = ivbmp[0].width();
			size.height = ivbmp[0].height();
			size.depth = ivbmp.size();

			for(size_t i=1 ; i<size.depth ; i++) {
				if(size.width < ivbmp[i].width()) {
					size.width = ivbmp[i].width();
				}

				if(size.height < ivbmp[i].height()) {
					size.height = ivbmp[i].height();
				}
			}

			size_t level = _size.size();

			for(size_t i=0 ; i<size.depth ; i++) {
				format = translateBmpFormat(ivbmp[i].format(), _format);
				type = translateBmpType(ivbmp[i].type());

				glTexSubImage3D(target, level, ixoffset, iyoffset, i + izoffset, ivbmp[i].width(), ivbmp[i].height(), 1, format, type, ivbmp[i].data());
			}

			_size.push_back(size);

			glCheckError();
		}

		void Texture::clear(tex::Target itarget, tex::Format iformat) {
			if(!empty()) {
				glDeleteTextures(1, &_id);
				glGenTextures(1, &_id);
				_size.clear();

				_format = iformat;
				_target = itarget;

				wrap(tex::Wrap::Repeat);

				minFilter(tex::MinFilter::Nearest);
				magFilter(tex::MagFilter::Nearest);

				_max_level = 0;
			}
		}

		void Texture::bind() const {
			glBindTexture(translateTarget(_target), _id);
		}

		void Texture::wrap(tex::Wrap iwrap) {
			_wrap_s = iwrap;
			_wrap_t = iwrap;
			_wrap_r = iwrap;

			bind();

			glTexParameteri(translateTarget(_target), GL_TEXTURE_WRAP_S, translateWrap(_wrap_s));
			glTexParameteri(translateTarget(_target), GL_TEXTURE_WRAP_T, translateWrap(_wrap_t));
			glTexParameteri(translateTarget(_target), GL_TEXTURE_WRAP_R, translateWrap(_wrap_r));
		}

		void Texture::wrapS(tex::Wrap iwrap) {
			_wrap_s = iwrap;
			bind();
			glTexParameteri(translateTarget(_target), GL_TEXTURE_WRAP_S, translateWrap(_wrap_s));
		}

		void Texture::wrapT(tex::Wrap iwrap) {
			_wrap_t = iwrap;
			bind();
			glTexParameteri(translateTarget(_target), GL_TEXTURE_WRAP_T, translateWrap(_wrap_t));
		}

		void Texture::wrapR(tex::Wrap iwrap) {
			_wrap_r = iwrap;
			bind();
			glTexParameteri(translateTarget(_target), GL_TEXTURE_WRAP_R, translateWrap(_wrap_r));
		}

		void Texture::minFilter(tex::MinFilter ifilter) {
			_min_filter = ifilter;

			bind();

			glTexParameteri(translateTarget(_target), GL_TEXTURE_MIN_FILTER, translateMinFilter(_min_filter));
		}

		void Texture::magFilter(tex::MagFilter ifilter) {
			_mag_filter = ifilter;

			bind();

			glTexParameteri(translateTarget(_target), GL_TEXTURE_MAG_FILTER, translateMagFilter(_mag_filter));
		}
	}  // namespace graphic
}  // namespace cb
