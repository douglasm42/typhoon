/* 
 * - Cumulonimbus - ☁
 * File: CubeMap.h
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
#pragma once
#include <cb/graphic/graphic.hpp>

#include <cb/graphic/tex/Texture.hpp>

namespace cb {
	namespace graphic {
		class CbAPI CubeMap : public Texture {
		private:
			tex::Wrap _wrap_s;
			tex::Wrap _wrap_t;

			uint32 _width;
			uint32 _height;

			virtual bool isSizeValid(uint32 ibmp_width, uint32 ibmp_height, uint32 ibmp_depth, uint32 ilod);

		public:
			CubeMap(tex::Format iformat);
			virtual ~CubeMap();
			
			void loadBlank(uint32 ilod, tex::CubeMapFace iface, uint32 iwidth, uint32 iheight);
			void loadBlank(uint32 ilod, uint32 iwidth, uint32 iheight);

			void loadBlankXp(uint32 ilod, uint32 iwidth, uint32 iheight);
			void loadBlankXm(uint32 ilod, uint32 iwidth, uint32 iheight);
			void loadBlankYp(uint32 ilod, uint32 iwidth, uint32 iheight);
			void loadBlankYm(uint32 ilod, uint32 iwidth, uint32 iheight);
			void loadBlankZp(uint32 ilod, uint32 iwidth, uint32 iheight);
			void loadBlankZm(uint32 ilod, uint32 iwidth, uint32 iheight);

			void loadImage(uint32 ilod, tex::CubeMapFace iface, const data::Bitmap &ibmp);
			void loadImage(uint32 ilod, const data::Bitmap &ibmp_xp, const data::Bitmap &ibmp_xm, const data::Bitmap &ibmp_yp, const data::Bitmap &ibmp_ym, const data::Bitmap &ibmp_zp, const data::Bitmap &ibmp_zm);

			void loadImageXp(uint32 ilod, const data::Bitmap &ibmp);
			void loadImageXm(uint32 ilod, const data::Bitmap &ibmp);
			void loadImageYp(uint32 ilod, const data::Bitmap &ibmp);
			void loadImageYm(uint32 ilod, const data::Bitmap &ibmp);
			void loadImageZp(uint32 ilod, const data::Bitmap &ibmp);
			void loadImageZm(uint32 ilod, const data::Bitmap &ibmp);

			void loadSubImage(uint32 ilod, tex::CubeMapFace iface, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset);

			void loadSubImageXp(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset);
			void loadSubImageXm(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset);
			void loadSubImageYp(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset);
			void loadSubImageYm(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset);
			void loadSubImageZp(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset);
			void loadSubImageZm(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset);

			void addBlankLOD(tex::CubeMapFace iface);
			void addBlankLOD();

			void addBlankXpLOD();
			void addBlankXmLOD();
			void addBlankYpLOD();
			void addBlankYmLOD();
			void addBlankZpLOD();
			void addBlankZmLOD();

			void addImageLOD(tex::CubeMapFace iface, const data::Bitmap &ibmp);
			void addImageLOD(const data::Bitmap &ibmp_xp, const data::Bitmap &ibmp_xm, const data::Bitmap &ibmp_yp, const data::Bitmap &ibmp_ym, const data::Bitmap &ibmp_zp, const data::Bitmap &ibmp_zm);

			void addImageXpLOD(const data::Bitmap &ibmp);
			void addImageXmLOD(const data::Bitmap &ibmp);
			void addImageYpLOD(const data::Bitmap &ibmp);
			void addImageYmLOD(const data::Bitmap &ibmp);
			void addImageZpLOD(const data::Bitmap &ibmp);
			void addImageZmLOD(const data::Bitmap &ibmp);

			void setWrap(tex::Wrap iwrap);
			void setWrapS(tex::Wrap iwrap);
			void setWrapT(tex::Wrap iwrap);

			tex::Wrap getWrapS() const;
			tex::Wrap getWrapT() const;

			uint32 width() const;
			uint32 height() const;

			uint32 lodWidth(uint32 ilod) const;
			uint32 lodHeight(uint32 ilod) const;
		};

		inline tex::Wrap CubeMap::getWrapS() const {return _wrap_s;}
		inline tex::Wrap CubeMap::getWrapT() const {return _wrap_t;}

		inline uint32 CubeMap::width() const {return _width;}
		inline uint32 CubeMap::height() const {return _height;}

		inline uint32 CubeMap::lodWidth(uint32 ilod) const {return cbTexLODSize(_width, ilod);}
		inline uint32 CubeMap::lodHeight(uint32 ilod) const {return cbTexLODSize(_height, ilod);}
	}  // namespace graphic
}  // namespace cb
