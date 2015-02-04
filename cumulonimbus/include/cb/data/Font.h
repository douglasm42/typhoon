/* 
 * - Cumulonimbus - ☁
 * File: Font.h
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

#include <cb/data/data.h>

#include <cb/data/Bitmap.h>
#include <cb/data/File.h>

#include <cb/base/String.h>
#include <cb/base/Kin.h>

#include <cb/math/math.h>

namespace cb {
	namespace data {
		KinLock(FontFace);

		class CbAPI Font {
		public:
			class CbAPI Glyph {
			private:
				size_t _id;

				int _h_offset_x;
				int _h_offset_y;
				int _h_advance;

				int _v_offset_x;
				int _v_offset_y;
				int _v_advance;

				ubBitmapL _bitmap;

				Glyph(size_t iid, int ih_offset_x, int ih_offset_y, int ih_advance, int iv_offset_x, int iv_offset_y, int iv_advance);

			public:
				Glyph();
				Glyph(const Glyph &isrc);
				~Glyph();

				size_t id() const;

				int hOffsetX() const;
				int hOffsetY() const;
				int hAdvance() const;
				int vOffsetX() const;
				int vOffsetY() const;
				int vAdvance() const;

				const ubBitmapL &bmp() const;

				friend class Font;
			};

		private:
			kin::FontFace _face;
			float _border;
			float _size;
			bool _border_inner;
			bool _border_outer;

			int fontUnitsToPixelsX(int ifux);
			int fontUnitsToPixelsY(int ifuy);
			int pixelsToFontUnitsX(int ipxx);
			int pixelsToFontUnitsY(int ipxy);

		public:
			Font();
			Font(File &ifile);
			~Font();

			int height();
			int underlineY();
			int underlineThickness();

			void size(float isize);

			void border(float iborder);
			void borderInner(bool iborder_inner);
			void borderOuter(bool iborder_outer);

			size_t glyphId(size_t ichar);

			void glyph(Glyph &oglyph, size_t iid);
			void glyphs(Glyph *oglyphs, size_t *iids, size_t in);

			void open(File &ifile);
			void close();

			bool isOpen();
		};

		inline Font::Glyph::Glyph(size_t iid, int ih_offset_x, int ih_offset_y, int ih_advance, int iv_offset_x, int iv_offset_y, int iv_advance)
		:_id(iid)
		,_h_offset_x(ih_offset_x)
		,_h_offset_y(ih_offset_y)
		,_h_advance(ih_advance)
		,_v_offset_x(iv_offset_x)
		,_v_offset_y(iv_offset_y)
		,_v_advance(iv_advance) {
		}

		inline Font::Glyph::Glyph()
		:_id(0)
		,_h_offset_x(0)
		,_h_offset_y(0)
		,_h_advance(0)
		,_v_offset_x(0)
		,_v_offset_y(0)
		,_v_advance(0){
		}

		inline Font::Glyph::Glyph(const Glyph &isrc)
		:_id(isrc._id)
		,_h_offset_x(isrc._h_offset_x)
		,_h_offset_y(isrc._h_offset_y)
		,_h_advance(isrc._h_advance)
		,_v_offset_x(isrc._v_offset_x)
		,_v_offset_y(isrc._v_offset_y)
		,_v_advance(isrc._v_advance)
		,_bitmap(isrc._bitmap){
		}

		inline Font::Glyph::~Glyph() {
		}

		inline size_t Font::Glyph::id() const {return _id;}

		inline int Font::Glyph::hOffsetX() const {return _h_offset_x;}
		inline int Font::Glyph::hOffsetY() const {return _h_offset_y;}
		inline int Font::Glyph::hAdvance() const {return _h_advance;}
		inline int Font::Glyph::vOffsetX() const {return _v_offset_x;}
		inline int Font::Glyph::vOffsetY() const {return _v_offset_y;}
		inline int Font::Glyph::vAdvance() const {return _v_advance;}

		inline const ubBitmapL &Font::Glyph::bmp() const {return _bitmap;}

		inline void Font::border(float iborder) {_border = iborder;}
		inline void Font::borderInner(bool iborder_inner) {_border_inner = iborder_inner;}
		inline void Font::borderOuter(bool iborder_outer) {_border_outer = iborder_outer;}
	}  // namespace data
}  // namespace cb
