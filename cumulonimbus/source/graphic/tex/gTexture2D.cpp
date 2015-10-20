/* 
 * - Cumulonimbus - ☁
 * File: gTexture2D.cpp
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
#include <cb/graphic/tex/Texture2D.hpp>

#include <cb/graphic/GLEWmx.hpp>
#include <cb/graphic/tex/TextureHelper.hpp>

namespace cb {
	namespace graphic {
		Texture2D::Texture2D(tex::Format iformat)
		:Texture(tex::Target::Tex2D, iformat)

		,_wrap_s(tex::Wrap::Repeat)
		,_wrap_t(tex::Wrap::Repeat)

		,_width(0)
		,_height(0) {
		}

		Texture2D::~Texture2D() {
		}

		bool Texture2D::isSizeValid(uint32 ibmp_width, uint32 ibmp_height, uint32 ibmp_depth, uint32 ilod) {
			return ibmp_depth == 1 && ibmp_width == lodWidth(ilod) && ibmp_height == lodHeight(ilod);
		}

		void Texture2D::loadBlank(uint32 ilod, uint32 iwidth, uint32 iheight) {
			if(ilod == 0) {
				_width = iwidth;
				_height = iheight;
			}

			texImage2D(ilod, lodWidth(ilod), lodHeight(ilod), 1, data::bmp::Format::Luminance, data::bmp::Type::UByte, nullptr);
		}

		void Texture2D::loadImage(uint32 ilod, const data::Bitmap &ibmp) {
			if(ilod == 0) {
				_width = ibmp.width();
				_height = ibmp.height();
			}

			texImage2D(ilod, ibmp.width(), ibmp.height(), ibmp.depth(), ibmp.format(), ibmp.type(), ibmp.data());
		}

		void Texture2D::loadSubImage(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset) {
			texSubImage2D(ilod, ixoffset, iyoffset, ibmp.width(), ibmp.height(), ibmp.format(), ibmp.type(), ibmp.data());
		}

		void Texture2D::addBlankLOD() {
			loadBlank(_lod_count, lodWidth(_lod_count), lodHeight(_lod_count));
		}

		void Texture2D::addImageLOD(const data::Bitmap &ibmp) {
			loadImage(_lod_count, ibmp);
		}

		void Texture2D::setWrap(tex::Wrap iwrap) {
			_wrap_s = iwrap;
			_wrap_t = iwrap;
			bind();
			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_S, GLenum(_wrap_s));
			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_T, GLenum(_wrap_t));
		}

		void Texture2D::setWrapS(tex::Wrap iwrap) {
			_wrap_s = iwrap;
			bind();
			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_S, GLenum(_wrap_s));
		}

		void Texture2D::setWrapT(tex::Wrap iwrap) {
			_wrap_t = iwrap;
			bind();
			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_T, GLenum(_wrap_t));
		}
	}  // namespace graphic
}  // namespace cb
