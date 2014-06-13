/* 
 * - Cumulonimbus - ☁
 * File: Texture.h
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

#include <graphic/graphic.h>
#include <graphic/GLTypedefs.h>

#include <data/Bitmap.h>

#include <cstdint>
#include <vector>

namespace cb {
	namespace graphic {
		class Texture {
		private:
			GLObject _id;
			tex::Format _format;
			tex::Target _target;

			tex::Wrap _wrap_s;
			tex::Wrap _wrap_t;
			tex::Wrap _wrap_r;

			tex::MinFilter _min_filter;
			tex::MagFilter _mag_filter;

			std::vector<tex::Size> _size;

			size_t _max_level;

		public:
			Texture(tex::Target itarget, tex::Format iformat);
			virtual ~Texture();

			void blank(size_t iwidth, size_t iheight, size_t idepth = 1);
			void cubeMap(const data::Bitmap &ibmp_xp, const data::Bitmap &ibmp_xm, const data::Bitmap &ibmp_yp, const data::Bitmap &ibmp_ym, const data::Bitmap &ibmp_zp, const data::Bitmap &ibmp_zm);

			void image(const data::Bitmap &ibmp);
			void image(const std::vector<data::Bitmap> &ivbmp);

			void subImage(const data::Bitmap &ibmp, size_t ilevel, size_t ixoffset);
			void subImage(const data::Bitmap &ibmp, size_t ilevel, size_t ixoffset, size_t iyoffset);
			void subImage(const data::Bitmap &ibmp, size_t ilevel, size_t ixoffset, size_t iyoffset, size_t izoffset);
			void subImage(const std::vector<data::Bitmap> &ivbmp, size_t ilevel, size_t ixoffset, size_t iyoffset, size_t izoffset);

			void clear(tex::Target itarget, tex::Format iformat);

			void bind() const;

			void wrap(tex::Wrap iwrap);
			void wrapS(tex::Wrap iwrap);
			void wrapT(tex::Wrap iwrap);
			void wrapR(tex::Wrap iwrap);

			void minFilter(tex::MinFilter ifilter);
			void magFilter(tex::MagFilter ifilter);

			tex::Wrap wrapS() const;
			tex::Wrap wrapT() const;
			tex::Wrap wrapR() const;

			tex::MinFilter minFilter() const;
			tex::MagFilter magFilter() const;

			bool empty() const;

			GLObject id() const;
			tex::Format format() const;
			tex::Target type() const;

			size_t width() const;
			size_t height() const;
			size_t depth() const;

			size_t width(size_t ilevel) const;
			size_t height(size_t ilevel) const;
			size_t depth(size_t ilevel) const;

			size_t levels() const;
		};

		inline tex::Wrap Texture::wrapS() const {return _wrap_s;}
		inline tex::Wrap Texture::wrapT() const {return _wrap_t;}
		inline tex::Wrap Texture::wrapR() const {return _wrap_r;}

		inline tex::MinFilter Texture::minFilter() const {return _min_filter;}
		inline tex::MagFilter Texture::magFilter() const {return _mag_filter;}

		inline bool Texture::empty() const {return _target == tex::Target::Void;}

		inline GLObject Texture::id() const { return _id; }
		inline tex::Format Texture::format() const {return _format;}
		inline tex::Target Texture::type() const {return _target;}

		inline size_t Texture::width() const {return _size[0].width;}
		inline size_t Texture::height() const {return _size[0].height;}
		inline size_t Texture::depth() const {return _size[0].depth;}

		inline size_t Texture::width(size_t ilevel) const {return _size[ilevel].width;}
		inline size_t Texture::height(size_t ilevel) const {return _size[ilevel].height;}
		inline size_t Texture::depth(size_t ilevel) const {return _size[ilevel].depth;}

		inline size_t Texture::levels() const {return _max_level;}
	}  // namespace graphic
}  // namespace cb
