/* 
 * - Cumulonimbus - ☁
 * File: gCubeMap.cpp
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
#include <cb/graphic/tex/CubeMap.hpp>

#include <cb/graphic/GLEWmx.hpp>
#include <cb/graphic/tex/TextureHelper.hpp>

namespace cb {
	namespace graphic {
		CubeMap::CubeMap(tex::Format iformat)
		:Texture(tex::Target::CubeMap, iformat)

		,_wrap_s(tex::Wrap::Repeat)
		,_wrap_t(tex::Wrap::Repeat)

		,_width(0)
		,_height(0) {
		}

		CubeMap::~CubeMap() {
		}

		bool CubeMap::isSizeValid(uint32 ibmp_width, uint32 ibmp_height, uint32 ibmp_depth, uint32 ilod) {
			return ibmp_depth == 1 && ibmp_width == lodWidth(ilod) && ibmp_height == lodHeight(ilod);
		}

		//------------------------------------------------------------------------------
		// - loadBlank -
		//------------------------------------------------------------------------------


		void CubeMap::loadBlank(uint32 ilod, tex::CubeMapFace iface, uint32 iwidth, uint32 iheight) {
			if(ilod == 0) {
				_width = iwidth;
				_height = iheight;
			}

			texImageCubeMap(iface, ilod, lodWidth(ilod), lodHeight(ilod), 1, data::bmp::Format::Luminance, data::bmp::Type::UByte, nullptr);
		}

		void CubeMap::loadBlank(uint32 ilod, uint32 iwidth, uint32 iheight) {
			if(ilod == 0) {
				_width = iwidth;
				_height = iheight;
			}

			texImageCubeMap(tex::CubeMapFace::CubeMapXp, ilod, lodWidth(ilod), lodHeight(ilod), 1, data::bmp::Format::Luminance, data::bmp::Type::UByte, nullptr);
			texImageCubeMap(tex::CubeMapFace::CubeMapXm, ilod, lodWidth(ilod), lodHeight(ilod), 1, data::bmp::Format::Luminance, data::bmp::Type::UByte, nullptr);
			texImageCubeMap(tex::CubeMapFace::CubeMapYp, ilod, lodWidth(ilod), lodHeight(ilod), 1, data::bmp::Format::Luminance, data::bmp::Type::UByte, nullptr);
			texImageCubeMap(tex::CubeMapFace::CubeMapYm, ilod, lodWidth(ilod), lodHeight(ilod), 1, data::bmp::Format::Luminance, data::bmp::Type::UByte, nullptr);
			texImageCubeMap(tex::CubeMapFace::CubeMapZp, ilod, lodWidth(ilod), lodHeight(ilod), 1, data::bmp::Format::Luminance, data::bmp::Type::UByte, nullptr);
			texImageCubeMap(tex::CubeMapFace::CubeMapZm, ilod, lodWidth(ilod), lodHeight(ilod), 1, data::bmp::Format::Luminance, data::bmp::Type::UByte, nullptr);
		}

		//------------------------------------------------------------------------------
		// - loadBlankFaces -
		//------------------------------------------------------------------------------

		void CubeMap::loadBlankXp(uint32 ilod, uint32 iwidth, uint32 iheight) {
			if(ilod == 0) {
				_width = iwidth;
				_height = iheight;
			}

			texImageCubeMap(tex::CubeMapFace::CubeMapXp, ilod, lodWidth(ilod), lodHeight(ilod), 1, data::bmp::Format::Luminance, data::bmp::Type::UByte, nullptr);
		}

		void CubeMap::loadBlankXm(uint32 ilod, uint32 iwidth, uint32 iheight) {
			if(ilod == 0) {
				_width = iwidth;
				_height = iheight;
			}

			texImageCubeMap(tex::CubeMapFace::CubeMapXm, ilod, lodWidth(ilod), lodHeight(ilod), 1, data::bmp::Format::Luminance, data::bmp::Type::UByte, nullptr);
		}

		void CubeMap::loadBlankYp(uint32 ilod, uint32 iwidth, uint32 iheight) {
			if(ilod == 0) {
				_width = iwidth;
				_height = iheight;
			}

			texImageCubeMap(tex::CubeMapFace::CubeMapYp, ilod, lodWidth(ilod), lodHeight(ilod), 1, data::bmp::Format::Luminance, data::bmp::Type::UByte, nullptr);
		}

		void CubeMap::loadBlankYm(uint32 ilod, uint32 iwidth, uint32 iheight) {
			if(ilod == 0) {
				_width = iwidth;
				_height = iheight;
			}

			texImageCubeMap(tex::CubeMapFace::CubeMapYm, ilod, lodWidth(ilod), lodHeight(ilod), 1, data::bmp::Format::Luminance, data::bmp::Type::UByte, nullptr);
		}

		void CubeMap::loadBlankZp(uint32 ilod, uint32 iwidth, uint32 iheight) {
			if(ilod == 0) {
				_width = iwidth;
				_height = iheight;
			}

			texImageCubeMap(tex::CubeMapFace::CubeMapZp, ilod, lodWidth(ilod), lodHeight(ilod), 1, data::bmp::Format::Luminance, data::bmp::Type::UByte, nullptr);
		}

		void CubeMap::loadBlankZm(uint32 ilod, uint32 iwidth, uint32 iheight) {
			if(ilod == 0) {
				_width = iwidth;
				_height = iheight;
			}

			texImageCubeMap(tex::CubeMapFace::CubeMapZm, ilod, lodWidth(ilod), lodHeight(ilod), 1, data::bmp::Format::Luminance, data::bmp::Type::UByte, nullptr);
		}

		//------------------------------------------------------------------------------
		// - loadImage -
		//------------------------------------------------------------------------------

		void CubeMap::loadImage(uint32 ilod, tex::CubeMapFace iface, const data::Bitmap &ibmp) {
			if(ilod == 0) {
				_width = ibmp.width();
				_height = ibmp.height();
			}

			texImageCubeMap(iface, ilod, ibmp.width(), ibmp.height(), ibmp.depth(), ibmp.format(), ibmp.type(), ibmp.data());
		}

		void CubeMap::loadImage(uint32 ilod, const data::Bitmap &ibmp_xp, const data::Bitmap &ibmp_xm, const data::Bitmap &ibmp_yp, const data::Bitmap &ibmp_ym, const data::Bitmap &ibmp_zp, const data::Bitmap &ibmp_zm) {
			if(ibmp_xp.width() != ibmp_xm.width() ||
					ibmp_xp.width() != ibmp_yp.width() ||
					ibmp_xp.width() != ibmp_ym.width() ||
					ibmp_xp.width() != ibmp_zp.width() ||
					ibmp_xp.width() != ibmp_zm.width() ||

					ibmp_xp.width() != ibmp_xp.height() ||
					ibmp_xp.width() != ibmp_xm.height() ||
					ibmp_xp.width() != ibmp_yp.height() ||
					ibmp_xp.width() != ibmp_ym.height() ||
					ibmp_xp.width() != ibmp_zp.height() ||
					ibmp_xp.width() != ibmp_zm.height()) {
				ThrowDet(tokurei::LoadFailed, "Inconsistent CubeMap image sizes.");
			}
			
			if(ilod == 0) {
				_width = ibmp_xp.width();
				_height = ibmp_xp.height();
			}

			texImageCubeMap(tex::CubeMapFace::CubeMapXp, ilod, ibmp_xp.width(), ibmp_xp.height(), ibmp_xp.depth(), ibmp_xp.format(), ibmp_xp.type(), ibmp_xp.data());
			texImageCubeMap(tex::CubeMapFace::CubeMapXm, ilod, ibmp_xm.width(), ibmp_xm.height(), ibmp_xm.depth(), ibmp_xm.format(), ibmp_xm.type(), ibmp_xm.data());
			texImageCubeMap(tex::CubeMapFace::CubeMapYp, ilod, ibmp_yp.width(), ibmp_yp.height(), ibmp_yp.depth(), ibmp_yp.format(), ibmp_yp.type(), ibmp_yp.data());
			texImageCubeMap(tex::CubeMapFace::CubeMapYm, ilod, ibmp_ym.width(), ibmp_ym.height(), ibmp_ym.depth(), ibmp_ym.format(), ibmp_ym.type(), ibmp_ym.data());
			texImageCubeMap(tex::CubeMapFace::CubeMapZp, ilod, ibmp_zp.width(), ibmp_zp.height(), ibmp_zp.depth(), ibmp_zp.format(), ibmp_zp.type(), ibmp_zp.data());
			texImageCubeMap(tex::CubeMapFace::CubeMapZm, ilod, ibmp_zm.width(), ibmp_zm.height(), ibmp_zm.depth(), ibmp_zm.format(), ibmp_zm.type(), ibmp_zm.data());
		}

		//------------------------------------------------------------------------------
		// - loadImageFaces -
		//------------------------------------------------------------------------------

		void CubeMap::loadImageXp(uint32 ilod, const data::Bitmap &ibmp) {
			if(ilod == 0) {
				_width = ibmp.width();
				_height = ibmp.height();
			}

			texImageCubeMap(tex::CubeMapFace::CubeMapXp, ilod, ibmp.width(), ibmp.height(), ibmp.depth(), ibmp.format(), ibmp.type(), ibmp.data());
		}

		void CubeMap::loadImageXm(uint32 ilod, const data::Bitmap &ibmp) {
			if(ilod == 0) {
				_width = ibmp.width();
				_height = ibmp.height();
			}

			texImageCubeMap(tex::CubeMapFace::CubeMapXm, ilod, ibmp.width(), ibmp.height(), ibmp.depth(), ibmp.format(), ibmp.type(), ibmp.data());
		}

		void CubeMap::loadImageYp(uint32 ilod, const data::Bitmap &ibmp) {
			if(ilod == 0) {
				_width = ibmp.width();
				_height = ibmp.height();
			}

			texImageCubeMap(tex::CubeMapFace::CubeMapYp, ilod, ibmp.width(), ibmp.height(), ibmp.depth(), ibmp.format(), ibmp.type(), ibmp.data());
		}

		void CubeMap::loadImageYm(uint32 ilod, const data::Bitmap &ibmp) {
			if(ilod == 0) {
				_width = ibmp.width();
				_height = ibmp.height();
			}

			texImageCubeMap(tex::CubeMapFace::CubeMapYm, ilod, ibmp.width(), ibmp.height(), ibmp.depth(), ibmp.format(), ibmp.type(), ibmp.data());
		}

		void CubeMap::loadImageZp(uint32 ilod, const data::Bitmap &ibmp) {
			if(ilod == 0) {
				_width = ibmp.width();
				_height = ibmp.height();
			}

			texImageCubeMap(tex::CubeMapFace::CubeMapZp, ilod, ibmp.width(), ibmp.height(), ibmp.depth(), ibmp.format(), ibmp.type(), ibmp.data());
		}

		void CubeMap::loadImageZm(uint32 ilod, const data::Bitmap &ibmp) {
			if(ilod == 0) {
				_width = ibmp.width();
				_height = ibmp.height();
			}

			texImageCubeMap(tex::CubeMapFace::CubeMapZm, ilod, ibmp.width(), ibmp.height(), ibmp.depth(), ibmp.format(), ibmp.type(), ibmp.data());
		}

		//------------------------------------------------------------------------------
		// - loadSubImage -
		//------------------------------------------------------------------------------

		void CubeMap::loadSubImage(uint32 ilod, tex::CubeMapFace iface, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset) {
			texSubImageCubeMap(iface, ilod, ixoffset, iyoffset, ibmp.width(), ibmp.height(), ibmp.format(), ibmp.type(), ibmp.data());
		}

		//------------------------------------------------------------------------------
		// - loadSubImageFaces -
		//------------------------------------------------------------------------------

		void CubeMap::loadSubImageXp(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset) {
			texSubImageCubeMap(tex::CubeMapFace::CubeMapXp, ilod, ixoffset, iyoffset, ibmp.width(), ibmp.height(), ibmp.format(), ibmp.type(), ibmp.data());
		}

		void CubeMap::loadSubImageXm(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset) {
			texSubImageCubeMap(tex::CubeMapFace::CubeMapXm, ilod, ixoffset, iyoffset, ibmp.width(), ibmp.height(), ibmp.format(), ibmp.type(), ibmp.data());
		}

		void CubeMap::loadSubImageYp(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset) {
			texSubImageCubeMap(tex::CubeMapFace::CubeMapYp, ilod, ixoffset, iyoffset, ibmp.width(), ibmp.height(), ibmp.format(), ibmp.type(), ibmp.data());
		}

		void CubeMap::loadSubImageYm(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset) {
			texSubImageCubeMap(tex::CubeMapFace::CubeMapYm, ilod, ixoffset, iyoffset, ibmp.width(), ibmp.height(), ibmp.format(), ibmp.type(), ibmp.data());
		}

		void CubeMap::loadSubImageZp(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset) {
			texSubImageCubeMap(tex::CubeMapFace::CubeMapZp, ilod, ixoffset, iyoffset, ibmp.width(), ibmp.height(), ibmp.format(), ibmp.type(), ibmp.data());
		}

		void CubeMap::loadSubImageZm(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset) {
			texSubImageCubeMap(tex::CubeMapFace::CubeMapZm, ilod, ixoffset, iyoffset, ibmp.width(), ibmp.height(), ibmp.format(), ibmp.type(), ibmp.data());
		}

		//------------------------------------------------------------------------------
		// - addBlankLOD -
		//------------------------------------------------------------------------------

		void CubeMap::addBlankLOD(tex::CubeMapFace iface) {
			loadBlank(_lod_count, iface, lodWidth(_lod_count), lodHeight(_lod_count));
		}

		void CubeMap::addBlankLOD() {
			loadBlank(_lod_count, lodWidth(_lod_count), lodHeight(_lod_count));
		}

		//------------------------------------------------------------------------------
		// - addBlankLODFaces -
		//------------------------------------------------------------------------------

		void CubeMap::addBlankXpLOD() {
			loadBlankXp(_lod_count, lodWidth(_lod_count), lodHeight(_lod_count));
		}

		void CubeMap::addBlankXmLOD() {
			loadBlankXm(_lod_count, lodWidth(_lod_count), lodHeight(_lod_count));
		}

		void CubeMap::addBlankYpLOD() {
			loadBlankYp(_lod_count, lodWidth(_lod_count), lodHeight(_lod_count));
		}

		void CubeMap::addBlankYmLOD() {
			loadBlankYm(_lod_count, lodWidth(_lod_count), lodHeight(_lod_count));
		}

		void CubeMap::addBlankZpLOD() {
			loadBlankZp(_lod_count, lodWidth(_lod_count), lodHeight(_lod_count));
		}

		void CubeMap::addBlankZmLOD() {
			loadBlankZm(_lod_count, lodWidth(_lod_count), lodHeight(_lod_count));
		}

		//------------------------------------------------------------------------------
		// - addImageLOD -
		//------------------------------------------------------------------------------

		void CubeMap::addImageLOD(tex::CubeMapFace iface, const data::Bitmap &ibmp) {
			loadImage(_lod_count, iface, ibmp);
		}

		void CubeMap::addImageLOD(const data::Bitmap &ibmp_xp, const data::Bitmap &ibmp_xm, const data::Bitmap &ibmp_yp, const data::Bitmap &ibmp_ym, const data::Bitmap &ibmp_zp, const data::Bitmap &ibmp_zm) {
			loadImage(_lod_count, ibmp_xp, ibmp_xm, ibmp_yp, ibmp_ym, ibmp_zp, ibmp_zm);
		}

		//------------------------------------------------------------------------------
		// - addImageLODFaces -
		//------------------------------------------------------------------------------

		void CubeMap::addImageXpLOD(const data::Bitmap &ibmp) {
			loadImageXp(_lod_count, ibmp);
		}

		void CubeMap::addImageXmLOD(const data::Bitmap &ibmp) {
			loadImageXm(_lod_count, ibmp);
		}

		void CubeMap::addImageYpLOD(const data::Bitmap &ibmp) {
			loadImageYp(_lod_count, ibmp);
		}

		void CubeMap::addImageYmLOD(const data::Bitmap &ibmp) {
			loadImageYm(_lod_count, ibmp);
		}

		void CubeMap::addImageZpLOD(const data::Bitmap &ibmp) {
			loadImageZp(_lod_count, ibmp);
		}

		void CubeMap::addImageZmLOD(const data::Bitmap &ibmp) {
			loadImageZm(_lod_count, ibmp);
		}

		//------------------------------------------------------------------------------
		// - setWrap -
		//------------------------------------------------------------------------------

		void CubeMap::setWrap(tex::Wrap iwrap) {
			_wrap_s = iwrap;
			_wrap_t = iwrap;
			bind();
			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_S, GLenum(_wrap_s));
			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_T, GLenum(_wrap_t));
		}

		void CubeMap::setWrapS(tex::Wrap iwrap) {
			_wrap_s = iwrap;
			bind();
			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_S, GLenum(_wrap_s));
		}

		void CubeMap::setWrapT(tex::Wrap iwrap) {
			_wrap_t = iwrap;
			bind();
			glTexParameteri(GLenum(_target), GL_TEXTURE_WRAP_T, GLenum(_wrap_t));
		}
	}  // namespace graphic
}  // namespace cb
