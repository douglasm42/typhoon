/* 
 * - Cumulonimbus - ☁
 * File: TextureRectangle.h
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
		class CbAPI TextureRectangle : public Texture {
		private:
			tex::Wrap _wrap_s;
			tex::Wrap _wrap_t;

			uint32 _width;
			uint32 _height;

			virtual bool isSizeValid(uint32 ibmp_width, uint32 ibmp_height, uint32 ibmp_depth, uint32 ilod);

		public:
			TextureRectangle(tex::Format iformat);
			virtual ~TextureRectangle();

			void loadBlank(uint32 iwidth, uint32 iheight);
			void loadImage(const data::Bitmap &ibmp);

			void loadSubImage(const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset);

			void setWrap(tex::Wrap iwrap);
			void setWrapS(tex::Wrap iwrap);
			void setWrapT(tex::Wrap iwrap);

			tex::Wrap getWrapS() const;
			tex::Wrap getWrapT() const;

			uint32 width() const;
			uint32 height() const;
		};

		inline tex::Wrap TextureRectangle::getWrapS() const {return _wrap_s;}
		inline tex::Wrap TextureRectangle::getWrapT() const {return _wrap_t;}

		inline uint32 TextureRectangle::width() const {return _width;}
		inline uint32 TextureRectangle::height() const {return _height;}
	}  // namespace graphic
}  // namespace cb
