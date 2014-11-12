/* 
 * - Cumulonimbus - ☁
 * File: Placement.h
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
#include <cb/video/video.h>

namespace cb {
	namespace video {
		enum class Border : unsigned char {
			Empty = 0,
			PopUp,
			System
		};

		class CbAPI Placement {
		private:
			int _x;
			int _y;
			int _width;
			int _height;

			bool _maximized;
			bool _minimized;
			Border _border;

		public:
			Placement();
			Placement(int ix, int iy, int iwidth, int iheight, bool imaximized, bool iminimized, Border iborder);

			int x() const;
			int y() const;
			int width() const;
			int height() const;

			void size(int iwidth, int iheight);
			void pos(int ix, int iy);

			void maximize();
			void restore();
			void minimize();
			void unminimize();

			bool maximized() const;
			void maximized(bool imaximized);

			bool minimized() const;
			void minimized(bool iminimized);

			Border border() const;
			void border(Border iborder);

			void centralize();
		};

		inline Placement::Placement()
		:_x(0), _y(0), _width(0), _height(0), _maximized(false), _minimized(false), _border(Border::System) {
		}

		inline Placement::Placement(int ix, int iy, int iwidth, int iheight, bool imaximized, bool iminimized, Border iborder)
		:_x(ix), _y(iy), _width(iwidth), _height(iheight), _maximized(imaximized), _minimized(iminimized), _border(iborder) {
		}

		inline int Placement::x() const {return _x;}
		inline int Placement::y() const {return _y;}
		inline int Placement::width() const {return _width;}
		inline int Placement::height() const {return _height;}

		inline void Placement::size(int iwidth, int iheight) {
			_width = iwidth;
			_height = iheight;
		}

		inline void Placement::pos(int ix, int iy) {
			_x = ix;
			_y = iy;
		}

		inline void Placement::maximize() {_maximized = true;}
		inline void Placement::restore() {_maximized = false;}
		inline void Placement::minimize() {_minimized = true;}
		inline void Placement::unminimize() {_minimized = false;}

		inline bool Placement::maximized() const {return _maximized;}
		inline void Placement::maximized(bool imaximized) {_maximized = imaximized;}

		inline bool Placement::minimized() const {return _minimized;}
		inline void Placement::minimized(bool iminimized) {_minimized = iminimized;}

		inline Border Placement::border() const {return _border;}
		inline void Placement::border(Border iborder) {_border = iborder;}
	}  // namespace video
}  // namespace cb
