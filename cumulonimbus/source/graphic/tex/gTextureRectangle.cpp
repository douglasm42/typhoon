/* 
 * - Cumulonimbus - ☁
 * File: gTextureRectangle.cpp
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
#include <cb/graphic/tex/TextureRectangle.hpp>

#include <cb/graphic/GLEWmx.hpp>
#include <cb/graphic/tex/TextureHelper.hpp>

namespace cb {
	namespace graphic {
		TextureRectangle::TextureRectangle(tex::Format iformat)
		:Texture(tex::Target::Rectangle, iformat)

		,_wrap_s(tex::Wrap::Repeat)
		,_wrap_t(tex::Wrap::Repeat)

		,_width(0)
		,_height(0) {
		}

		TextureRectangle::~TextureRectangle() {
		}

		bool TextureRectangle::isSizeValid(uint32 ibmp_width, uint32 ibmp_height, uint32 ibmp_depth, uint32 ilod) {
			return ibmp_depth == 1 && ilod == 0;
		}

		void TextureRectangle::loadBlank(uint32 iwidth, uint32 iheight) {
			_width = iwidth;
			_height = iheight;

			texImage2D(0, iwidth, iheight, 1, data::bmp::Format::Luminance, data::bmp::Type::UByte, nullptr);
		}

		void TextureRectangle::loadImage(const data::Bitmap &ibmp) {
			_width = ibmp.width();
			_height = ibmp.height();

			texImage2D(0, ibmp.width(), ibmp.height(), ibmp.depth(), ibmp.format(), ibmp.type(), ibmp.data());
		}

		void TextureRectangle::loadSubImage(const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset) {
			texSubImage2D(0, ixoffset, iyoffset, ibmp.width(), ibmp.height(), ibmp.format(), ibmp.type(), ibmp.data());
		}

		void TextureRectangle::setWrap(tex::Wrap iwrap) {
			_wrap_s = iwrap;
			_wrap_t = iwrap;
			bind();
			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_S, GLenum(_wrap_s));
			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_T, GLenum(_wrap_t));
		}

		void TextureRectangle::setWrapS(tex::Wrap iwrap) {
			_wrap_s = iwrap;
			bind();
			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_S, GLenum(_wrap_s));
		}

		void TextureRectangle::setWrapT(tex::Wrap iwrap) {
			_wrap_t = iwrap;
			bind();
			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_T, GLenum(_wrap_t));
		}
	}  // namespace graphic
}  // namespace cb
