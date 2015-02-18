/* 
 * - Cumulonimbus - ☁
 * File: gTexture1D.cpp
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
#include <cb/graphic/tex/Texture1D.h>

#include <cb/graphic/GLEWmx.h>
#include <cb/graphic/tex/TextureHelper.h>

namespace cb {
	namespace graphic {
		Texture1D::Texture1D(tex::Format iformat)
		:Texture(tex::Target::Tex1D, iformat)
		,_wrap_s(tex::Wrap::Repeat)
		,_width(0) {
		}

		Texture1D::~Texture1D() {
		}

		bool Texture1D::isSizeValid(uint32 ibmp_width, uint32 ibmp_height, uint32 ibmp_depth, uint32 ilod) {
			return ibmp_height == 1 && ibmp_depth == 1 && ibmp_width == lodWidth(ilod);
		}

		void Texture1D::loadBlank(uint32 ilod, uint32 iwidth) {
			if(ilod == 0) {
				_width = iwidth;
			}

			texImage1D(ilod, lodWidth(ilod), 1, 1, data::bmp::Format::Luminance, data::bmp::Type::UByte, nullptr);
		}

		void Texture1D::loadImage(uint32 ilod, const data::Bitmap &ibmp) {
			if(ilod == 0) {
				_width = ibmp.width();
			}

			texImage1D(ilod, ibmp.width(), ibmp.height(), ibmp.depth(), ibmp.format(), ibmp.type(), ibmp.data());
		}

		void Texture1D::loadSubImage(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset) {
			texSubImage1D(ilod, ixoffset, ibmp.width(), ibmp.format(), ibmp.type(), ibmp.data());
		}

		void Texture1D::addBlankLOD() {
			loadBlank(_lod_count, lodWidth(_lod_count));
		}

		void Texture1D::addImageLOD(const data::Bitmap &ibmp) {
			loadImage(_lod_count, ibmp);
		}

		void Texture1D::setWrap(tex::Wrap iwrap) {
			_wrap_s = iwrap;
			bind();
			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_S, GLenum(_wrap_s));
		}

	}  // namespace graphic
}  // namespace cb
