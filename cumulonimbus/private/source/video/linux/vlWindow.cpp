/* 
 * - Cumulonimbus - ☁
 * File: vlWindow.cpp
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
#include <base/Setup.h>
#ifdef CbLinux

#include <video/Window.h>

#include <video/linux/Xlib.h>

namespace cb {
	namespace video {
		KinKey(kin::WindowInfo, XWindowInfo);

		Window::Window(base::string16 ititle, win::Placement iplacement) {

		}

		Window::Window(base::string16 ititle, size_t ix, size_t iy, size_t iwidth, size_t iheight, win::ShowCmd ishowcmd, bool iborder) {

		}

		Window::~Window() {

		}

		void Window::title(base::string16 ititle) {

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



