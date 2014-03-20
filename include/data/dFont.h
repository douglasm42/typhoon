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

#include <base/bString.h>

#include <math/math.h>

namespace cb {
	namespace data {
		KinLock(FontFace);

		class CbAPI Font {
		public:
			class CbAPI Glyph {
			private:
				size_t _id;

				size_t _width;
				size_t _height;

				int _h_offset_x;
				int _h_offset_y;
				int _h_advance;

				int _v_offset_x;
				int _v_offset_y;
				int _v_advance;

				math::uint8 *_data;

				Glyph(size_t iid, size_t iwidth, size_t iheight, int ih_offset_x, int ih_offset_y, int ih_advance, int iv_offset_x, int iv_offset_y, int iv_advance, math::uint8 *idata)
				:_id(iid)
				,_width(iwidth)
				,_height(iheight)
				,_h_offset_x(ih_offset_x)
				,_h_offset_y(ih_offset_y)
				,_h_advance(ih_advance)
				,_v_offset_x(iv_offset_x)
				,_v_offset_y(iv_offset_y)
				,_v_advance(iv_advance)
				,_data(idata){
				}

				void clear() {
					if(_data) {
						delete [] _data;
					}
					_data = NULL;
				}

			public:
				Glyph()
				:_id(0)
				,_width(0)
				,_height(0)
				,_h_offset_x(0)
				,_h_offset_y(0)
				,_h_advance(0)
				,_v_offset_x(0)
				,_v_offset_y(0)
				,_v_advance(0)
				,_data(NULL){
				}

				Glyph(const Glyph &isrc)
				:_id(isrc._id)
				,_width(isrc._width)
				,_height(isrc._height)
				,_h_offset_x(isrc._h_offset_x)
				,_h_offset_y(isrc._h_offset_y)
				,_h_advance(isrc._h_advance)
				,_v_offset_x(isrc._v_offset_x)
				,_v_offset_y(isrc._v_offset_y)
				,_v_advance(isrc._v_advance)
				,_data(NULL){
					_data = new math::uint8[_width * _height];
					for(size_t i=0 ; i<_width*_height ; i++) {
						_data[i] = isrc._data[i];
					}
				}
				~Glyph() {
					if(_data) {
						delete [] _data;
					}
				}

				size_t id() const {return _id;}

				size_t width() const {return _width;}
				size_t height() const {return _height;}

				int hOffsetX() const {return _h_offset_x;}
				int hOffsetY() const {return _h_offset_y;}
				int hAdvance() const {return _h_advance;}
				int vOffsetX() const {return _v_offset_x;}
				int vOffsetY() const {return _v_offset_y;}
				int vAdvance() const {return _v_advance;}

				const math::uint8 *data() const {return _data;}

				math::uint8 operator()(size_t x, size_t y) const {
					return _data[y*_width + x];
				}

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
			Font(string ifilename);
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

			void open(string ifilename);
			void close();

			bool isOpen();
		};
	}  // namespace data
}  // namespace cb
