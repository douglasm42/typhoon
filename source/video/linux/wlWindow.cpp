/*
 * wlWindow.cpp
 *
 *  Created on: May 5, 2014
 *      Author: douglas
 */

#include <base/Setup.h>
#ifdef CbLinux

#include <video/Window.h>

#include <video/linux/Xlib.h>

namespace cb {
	namespace video {
		KinKey(WindowInfo, XWindowInfo);

		Window::Window(base::wstring ititle, win::Placement iplacement) {

		}

		Window::Window(base::wstring ititle, size_t ix, size_t iy, size_t iwidth, size_t iheight, win::ShowCmd ishowcmd, bool iborder) {

		}

		Window::~Window() {

		}

		void Window::title(base::wstring ititle) {

		}

		void Window::placement(win::Placement iplacement) {

		}

		win::Placement Window::placement() {
			win::Placement p;

		}

		void Window::resize(size_t iwidth, size_t iheight) {

		}

		void Window::move(size_t ix, size_t iy) {

		}

		void Window::border(bool iborder) {

		}

		void Window::show(win::ShowCmd icmd) {

		}

		void Window::visible(bool ivisible) {

		}
	}  // namespace video
}  // namespace cb

#endif



