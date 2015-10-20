/* 
 * - Cumulonimbus - ☁
 * File: Texture2D.h
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
		class CbAPI Texture2D : public Texture {
		private:
			tex::Wrap _wrap_s;
			tex::Wrap _wrap_t;

			uint32 _width;
			uint32 _height;

			virtual bool isSizeValid(uint32 ibmp_width, uint32 ibmp_height, uint32 ibmp_depth, uint32 ilod);

		public:
			Texture2D(tex::Format iformat);
			virtual ~Texture2D();

			void loadBlank(uint32 ilod, uint32 iwidth, uint32 iheight);
			void loadImage(uint32 ilod, const data::Bitmap &ibmp);

			void loadSubImage(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset);

			void addBlankLOD();
			void addImageLOD(const data::Bitmap &ibmp);

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

		inline tex::Wrap Texture2D::getWrapS() const {return _wrap_s;}
		inline tex::Wrap Texture2D::getWrapT() const {return _wrap_t;}

		inline uint32 Texture2D::width() const {return _width;}
		inline uint32 Texture2D::height() const {return _height;}

		inline uint32 Texture2D::lodWidth(uint32 ilod) const {return cbTexLODSize(_width, ilod);}
		inline uint32 Texture2D::lodHeight(uint32 ilod) const {return cbTexLODSize(_height, ilod);}
	}  // namespace graphic
}  // namespace cb
