/* 
 * - Cumulonimbus - ☁
 * File: gTexture1DArray.cpp
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
#include <cb/graphic/tex/Texture1DArray.hpp>

#include <cb/graphic/GLEWmx.hpp>
#include <cb/graphic/tex/TextureHelper.hpp>

namespace cb {
	namespace graphic {
		Texture1DArray::Texture1DArray(tex::Format iformat)
		:Texture(tex::Target::Tex2D, iformat)

		,_wrap_s(tex::Wrap::Repeat)

		,_width(0)
		,_layers(0) {
		}

		Texture1DArray::~Texture1DArray() {
		}

		bool Texture1DArray::isSizeValid(uint32 ibmp_width, uint32 ibmp_height, uint32 ibmp_depth, uint32 ilod) {
			return ibmp_depth == 1 && ibmp_width == lodWidth(ilod) && ibmp_height == _layers;
		}

		void Texture1DArray::loadBlank(uint32 ilod, uint32 iwidth, uint32 ilayers) {
			if(ilod == 0) {
				_width = iwidth;
				_layers = ilayers;
			}

			texImage2D(ilod, lodWidth(ilod), _layers, 1, data::bmp::Format::Luminance, data::bmp::Type::UByte, nullptr);
		}

		void Texture1DArray::loadImage(uint32 ilod, const data::Bitmap &ibmp) {
			if(ilod == 0) {
				_width = ibmp.width();
				_layers = ibmp.height();
			}

			texImage2D(ilod, ibmp.width(), ibmp.height(), ibmp.depth(), ibmp.format(), ibmp.type(), ibmp.data());
		}

		void Texture1DArray::loadSubImage(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 ilayer_offset) {
			texSubImage2D(ilod, ixoffset, ilayer_offset, ibmp.width(), ibmp.height(), ibmp.format(), ibmp.type(), ibmp.data());
		}

		void Texture1DArray::addBlankLOD() {
			loadBlank(_lod_count, lodWidth(_lod_count), _layers);
		}

		void Texture1DArray::addImageLOD(const data::Bitmap &ibmp) {
			loadImage(_lod_count, ibmp);
		}

		void Texture1DArray::setWrap(tex::Wrap iwrap) {
			_wrap_s = iwrap;
			bind();
			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_S, GLenum(_wrap_s));
		}
	}  // namespace graphic
}  // namespace cb
