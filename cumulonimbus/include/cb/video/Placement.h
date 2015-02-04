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

#ifdef CbWindows
#	include <cb/video/win32/Windows.h>
#endif

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

		public:
			Placement();
			Placement(int ix, int iy, int iwidth, int iheight, bool imaximized, bool iminimized);

			int x() const;
			int y() const;
			int width() const;
			int height() const;

			void setSize(int iwidth, int iheight);
			void setPosition(int ix, int iy);

			void maximize();
			void restore();
			void minimize();
			void unminimize();

			bool isMaximized() const;
			void setMaximized(bool imaximized);

			bool isMinimized() const;
			void setMinimized(bool iminimized);

			void centralize();

			Placement &operator=(const Placement &iplacement);

#			ifdef CbWindows
				static void wConvert(const Placement &iplacement, Border iborder, WINDOWPLACEMENT &oplacement);
				static void wConvert(const WINDOWPLACEMENT &iplacement, Border iborder, Placement &oplacement);
#			endif
		};

		inline Placement::Placement()
		:_x(0), _y(0), _width(0), _height(0), _maximized(false), _minimized(false) {
		}

		inline Placement::Placement(int ix, int iy, int iwidth, int iheight, bool imaximized, bool iminimized)
		:_x(ix), _y(iy), _width(iwidth), _height(iheight), _maximized(imaximized), _minimized(iminimized) {
		}

		inline int Placement::x() const {return _x;}
		inline int Placement::y() const {return _y;}
		inline int Placement::width() const {return _width;}
		inline int Placement::height() const {return _height;}

		inline void Placement::setSize(int iwidth, int iheight) {
			_width = iwidth;
			_height = iheight;
		}

		inline void Placement::setPosition(int ix, int iy) {
			_x = ix;
			_y = iy;
		}

		inline void Placement::maximize() {_maximized = true;}
		inline void Placement::restore() {_maximized = false;}
		inline void Placement::minimize() {_minimized = true;}
		inline void Placement::unminimize() {_minimized = false;}

		inline bool Placement::isMaximized() const {return _maximized;}
		inline void Placement::setMaximized(bool imaximized) {_maximized = imaximized;}

		inline bool Placement::isMinimized() const {return _minimized;}
		inline void Placement::setMinimized(bool iminimized) {_minimized = iminimized;}

		inline Placement &Placement::operator=(const Placement &iplacement) {
			_x = iplacement._x;
			_y = iplacement._y;
			_width = iplacement._width;
			_height = iplacement._height;
			_maximized = iplacement._maximized;
			_minimized = iplacement._minimized;

			return *this;
		}
	}  // namespace video
}  // namespace cb
