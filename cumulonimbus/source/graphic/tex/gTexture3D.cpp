/* 
 * - Cumulonimbus - ☁
 * File: gTexture3D.cpp
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
#include <cb/graphic/tex/Texture3D.hpp>

#include <cb/graphic/GLEWmx.hpp>
#include <cb/graphic/tex/TextureHelper.hpp>

namespace cb {
	namespace graphic {
		Texture3D::Texture3D(tex::Format iformat)
		:Texture(tex::Target::Tex3D, iformat)

		,_wrap_s(tex::Wrap::Repeat)
		,_wrap_t(tex::Wrap::Repeat)
		,_wrap_r(tex::Wrap::Repeat)

		,_width(0)
		,_height(0)
		,_depth(0) {
		}

		Texture3D::~Texture3D() {
		}

		bool Texture3D::isSizeValid(uint32 ibmp_width, uint32 ibmp_height, uint32 ibmp_depth, uint32 ilod) {
			return ibmp_width == lodWidth(ilod) && ibmp_height == lodHeight(ilod) && ibmp_depth == lodDepth(ilod);
		}

		void Texture3D::loadBlank(uint32 ilod, uint32 iwidth, uint32 iheight, uint32 idepth) {
			if(ilod == 0) {
				_width = iwidth;
				_height = iheight;
				_depth = idepth;
			}

			texImage3D(ilod, lodWidth(ilod), lodHeight(ilod), 1, data::bmp::Format::Luminance, data::bmp::Type::UByte, nullptr);
		}

		void Texture3D::loadImage(uint32 ilod, const data::Bitmap &ibmp) {
			if(ilod == 0) {
				_width = ibmp.width();
				_height = ibmp.height();
			}

			texImage3D(ilod, ibmp.width(), ibmp.height(), ibmp.depth(), ibmp.format(), ibmp.type(), ibmp.data());
		}

		void Texture3D::loadSubImage(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset, uint32 izoffset) {
			texSubImage3D(ilod, ixoffset, iyoffset, izoffset, ibmp.width(), ibmp.height(), ibmp.depth(), ibmp.format(), ibmp.type(), ibmp.data());
		}

		void Texture3D::addBlankLOD() {
			loadBlank(_lod_count, lodWidth(_lod_count), lodHeight(_lod_count), lodDepth(_lod_count));
		}

		void Texture3D::addImageLOD(const data::Bitmap &ibmp) {
			loadImage(_lod_count, ibmp);
		}

		void Texture3D::setWrap(tex::Wrap iwrap) {
			_wrap_s = iwrap;
			_wrap_t = iwrap;
			_wrap_r = iwrap;
			bind();
			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_S, GLenum(_wrap_s));
			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_T, GLenum(_wrap_t));
			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_R, GLenum(_wrap_r));
		}

		void Texture3D::setWrapS(tex::Wrap iwrap) {
			_wrap_s = iwrap;
			bind();
			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_S, GLenum(_wrap_s));
		}

		void Texture3D::setWrapT(tex::Wrap iwrap) {
			_wrap_t = iwrap;
			bind();
			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_T, GLenum(_wrap_t));
		}

		void Texture3D::setWrapR(tex::Wrap iwrap) {
			_wrap_r = iwrap;
			bind();
			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_R, GLenum(_wrap_r));
		}
	}  // namespace graphic
}  // namespace cb
