/* 
 * - Cumulonimbus - ☁
 * File: Texture3D.h
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
		class CbAPI Texture3D : public Texture {
		private:
			tex::Wrap _wrap_s;
			tex::Wrap _wrap_t;
			tex::Wrap _wrap_r;

			uint32 _width;
			uint32 _height;
			uint32 _depth;

			virtual bool Texture3D::isSizeValid(uint32 ibmp_width, uint32 ibmp_height, uint32 ibmp_depth, uint32 ilod);

		public:
			Texture3D(tex::Format iformat);
			virtual ~Texture3D();

			void loadBlank(uint32 ilod, uint32 iwidth, uint32 iheight, uint32 idepth);
			void loadImage(uint32 ilod, const data::Bitmap &ibmp);

			void loadSubImage(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset, uint32 izoffset);

			void addBlankLOD();
			void addImageLOD(const data::Bitmap &ibmp);

			void setWrap(tex::Wrap iwrap);
			void setWrapS(tex::Wrap iwrap);
			void setWrapT(tex::Wrap iwrap);
			void setWrapR(tex::Wrap iwrap);

			tex::Wrap getWrapS() const;
			tex::Wrap getWrapT() const;
			tex::Wrap getWrapR() const;

			uint32 width() const;
			uint32 height() const;
			uint32 depth() const;

			uint32 lodWidth(uint32 ilod) const;
			uint32 lodHeight(uint32 ilod) const;
			uint32 lodDepth(uint32 ilod) const;
		};

		inline tex::Wrap Texture3D::getWrapS() const {return _wrap_s;}
		inline tex::Wrap Texture3D::getWrapT() const {return _wrap_t;}
		inline tex::Wrap Texture3D::getWrapR() const {return _wrap_r;}

		inline uint32 Texture3D::width() const {return _width;}
		inline uint32 Texture3D::height() const {return _height;}
		inline uint32 Texture3D::depth() const {return _depth;}

		inline uint32 Texture3D::lodWidth(uint32 ilod) const {return cbTexLODSize(_width, ilod);}
		inline uint32 Texture3D::lodHeight(uint32 ilod) const {return cbTexLODSize(_height, ilod);}
		inline uint32 Texture3D::lodDepth(uint32 ilod) const {return cbTexLODSize(_depth, ilod);}
	}  // namespace graphic
}  // namespace cb
