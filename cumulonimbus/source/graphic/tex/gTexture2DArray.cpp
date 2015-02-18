/* 
 * - Cumulonimbus - ☁
 * File: gTexture2DArray.cpp
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
#include <cb/graphic/tex/Texture2DArray.h>

#include <cb/graphic/GLEWmx.h>
#include <cb/graphic/tex/TextureHelper.h>

namespace cb {
	namespace graphic {
		Texture2DArray::Texture2DArray(tex::Format iformat)
		:Texture(tex::Target::Tex3D, iformat)

		,_wrap_s(tex::Wrap::Repeat)
		,_wrap_t(tex::Wrap::Repeat)

		,_width(0)
		,_height(0)
		,_layers(0) {
		}

		Texture2DArray::~Texture2DArray() {
		}

		bool Texture2DArray::isSizeValid(uint32 ibmp_width, uint32 ibmp_height, uint32 ibmp_depth, uint32 ilod) {
			return ibmp_width == lodWidth(ilod) && ibmp_height == lodHeight(ilod) && ibmp_depth == _layers;
		}

		void Texture2DArray::loadBlank(uint32 ilod, uint32 iwidth, uint32 iheight, uint32 ilayers) {
			if(ilod == 0) {
				_width = iwidth;
				_height = iheight;
				_layers = ilayers;
			}

			texImage3D(ilod, lodWidth(ilod), lodHeight(ilod), 1, data::bmp::Format::Luminance, data::bmp::Type::UByte, nullptr);
		}

		void Texture2DArray::loadImage(uint32 ilod, const data::Bitmap &ibmp) {
			if(ilod == 0) {
				_width = ibmp.width();
				_height = ibmp.height();
			}

			texImage3D(ilod, ibmp.width(), ibmp.height(), ibmp.depth(), ibmp.format(), ibmp.type(), ibmp.data());
		}

		void Texture2DArray::loadSubImage(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset, uint32 izoffset) {
			texSubImage3D(ilod, ixoffset, iyoffset, izoffset, ibmp.width(), ibmp.height(), ibmp.depth(), ibmp.format(), ibmp.type(), ibmp.data());
		}

		void Texture2DArray::addBlankLOD() {
			loadBlank(_lod_count, lodWidth(_lod_count), lodHeight(_lod_count), _layers);
		}

		void Texture2DArray::addImageLOD(const data::Bitmap &ibmp) {
			loadImage(_lod_count, ibmp);
		}

		void Texture2DArray::setWrap(tex::Wrap iwrap) {
			_wrap_s = iwrap;
			_wrap_t = iwrap;
			bind();
			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_S, GLenum(_wrap_s));
			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_T, GLenum(_wrap_t));
		}

		void Texture2DArray::setWrapS(tex::Wrap iwrap) {
			_wrap_s = iwrap;
			bind();
			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_S, GLenum(_wrap_s));
		}

		void Texture2DArray::setWrapT(tex::Wrap iwrap) {
			_wrap_t = iwrap;
			bind();
			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_T, GLenum(_wrap_t));
		}

	}  // namespace graphic
}  // namespace cb
