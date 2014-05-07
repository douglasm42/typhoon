/*
 * Window.h
 *
 *  Created on: May 3, 2014
 *      Author: douglas
 */

#pragma once

#include <window/window.h>

#include <base/String.h>
#include <base/Kin.h>

#include <math/math.h>

namespace cb {
	namespace window {
		KinLock(WindowInfo);

		namespace win {
			typedef enum ShowCmd {
				Null = 0,
				Maximize,
				Minimize,
				Restore
			} ShowCmd;

			class CbAPI Placement {
			public:
				size_t x;
				size_t y;
				size_t width;
				size_t height;
				ShowCmd showcmd;
				bool border;

				Placement()
				:x(0), y(0), width(0), height(0), showcmd(Null), border(false) {
				}

				Placement(size_t ix, size_t iy, size_t iwidth, size_t iheight, ShowCmd ishowcmd, bool iborder)
				:x(ix), y(iy), width(iwidth), height(iheight), showcmd(ishowcmd), border(iborder) {
				}

				void centralize();
			};
		}  // namespace win

		class CbAPI Window {
		private:
			kin::WindowInfo _window_info;
			win::Placement _placement;

		public:
			Window(base::wstring ititle, win::Placement iplacement);
			Window(base::wstring ititle, size_t ix, size_t iy, size_t iwidth, size_t iheight, win::ShowCmd ishowcmd, bool iborder);
			~Window();

			void title(base::wstring ititle);

			void placement(win::Placement iplacement);
			win::Placement placement();

			void resize(size_t iwidth, size_t iheight);
			void move(size_t ix, size_t iy);
			void border(bool iborder);

			void show(win::ShowCmd icmd);

			void visible(bool ivisible);

			kin::WindowInfo &info() {return _window_info;}
		};
	}  // namespace window
}  // namespace cb
