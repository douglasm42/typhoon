/* 
 * - Cumulonimbus - ☁
 * File: Texture1D.h
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
#include <cb/graphic/graphic.h>

#include <cb/graphic/tex/Texture.h>

namespace cb {
	namespace graphic {
		class CbAPI Texture1D : public Texture {
		private:
			tex::Wrap _wrap_s;

			uint32 _width;

			virtual bool isSizeValid(uint32 ibmp_width, uint32 ibmp_height, uint32 ibmp_depth, uint32 ilod);

		public:
			Texture1D(tex::Format iformat);
			virtual ~Texture1D();

			void loadBlank(uint32 ilod, uint32 iwidth);
			void loadImage(uint32 ilod, const data::Bitmap &ibmp);

			void loadSubImage(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset);

			void addBlankLOD();
			void addImageLOD(const data::Bitmap &ibmp);

			void setWrap(tex::Wrap iwrap);
			tex::Wrap getWrap() const;

			uint32 width() const;

			uint32 lodWidth(uint32 ilod) const;
		};

		inline tex::Wrap Texture1D::getWrap() const {return _wrap_s;}
		inline uint32 Texture1D::width() const {return _width;}
		inline uint32 Texture1D::lodWidth(uint32 ilod) const {return cbTexLODSize(_width, ilod);}
	}  // namespace graphic
}  // namespace cb
