/*
 * dFont.h
 *
 *  Created on: 06/01/2014
 *      Author: Douglas
 *
 *   Copyright: Staff 42 © 2013
 */

#pragma once

#include <data/data.h>

#include <data/Bitmap.h>
#include <data/File.h>

#include <base/String.h>
#include <base/Kin.h>

#include <math/math.h>

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

				Glyph(size_t iid, int ih_offset_x, int ih_offset_y, int ih_advance, int iv_offset_x, int iv_offset_y, int iv_advance)
				:_id(iid)
				,_h_offset_x(ih_offset_x)
				,_h_offset_y(ih_offset_y)
				,_h_advance(ih_advance)
				,_v_offset_x(iv_offset_x)
				,_v_offset_y(iv_offset_y)
				,_v_advance(iv_advance) {
				}

			public:
				Glyph()
				:_id(0)
				,_h_offset_x(0)
				,_h_offset_y(0)
				,_h_advance(0)
				,_v_offset_x(0)
				,_v_offset_y(0)
				,_v_advance(0){
				}

				Glyph(const Glyph &isrc)
				:_id(isrc._id)
				,_h_offset_x(isrc._h_offset_x)
				,_h_offset_y(isrc._h_offset_y)
				,_h_advance(isrc._h_advance)
				,_v_offset_x(isrc._v_offset_x)
				,_v_offset_y(isrc._v_offset_y)
				,_v_advance(isrc._v_advance)
				,_bitmap(isrc._bitmap){
				}
				~Glyph() {
				}

				size_t id() const {return _id;}

				int hOffsetX() const {return _h_offset_x;}
				int hOffsetY() const {return _h_offset_y;}
				int hAdvance() const {return _h_advance;}
				int vOffsetX() const {return _v_offset_x;}
				int vOffsetY() const {return _v_offset_y;}
				int vAdvance() const {return _v_advance;}

				const ubBitmapL &bmp() const {return _bitmap;}

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
			Font(const base::string &ifilename);
			Font(istream &ifile);
			Font(MFile &ifile);
			~Font();

			int height();
			int underlineY();
			int underlineThickness();

			void size(float isize);

			void border(float iborder) {_border = iborder;}
			void borderInner(bool iborder_inner) {_border_inner = iborder_inner;}
			void borderOuter(bool iborder_outer) {_border_outer = iborder_outer;}

			size_t glyphId(size_t ichar);

			void glyph(Glyph &oglyph, size_t iid);
			void glyphs(Glyph *oglyphs, size_t *iids, size_t in);

			void open(const base::string &ifilename);
			void open(istream &ifile);
			void open(MFile &ifile);
			void close();

			bool isOpen();
		};
	}  // namespace data
}  // namespace cb
