/* 
 * - Cumulonimbus - ☁
 * File: vwWindow.cpp
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
#ifdef CbWindows

#include <video/Window.h>
#include <base/Exception.h>
#include <base/Log.h>

#include <video/win32/Windows.h>
#include <video/win32/WindowInfo.h>

#include <input/EventLoop.h>

namespace cb {
	namespace video {
		KinKey(kin::WindowInfo, w32WindowInfo);

		Window::Window() {
			_window_info << new w32WindowInfo;
		}
		Window::Window(base::wstring ititle, win::Placement iplacement) {
			_window_info << new w32WindowInfo;
			create(ititle, iplacement);
		}
		Window::Window(base::wstring ititle, size_t ix, size_t iy, size_t iwidth, size_t iheight, bool imaximized, bool iminimized, bool iborder) {
			_window_info << new w32WindowInfo;
			create(ititle, win::Placement(ix, iy, iwidth, iheight, imaximized, iminimized, iborder));
		}
		Window::~Window() {
			delete [] (*_window_info).window;
			destroy();
		}

		void Window::create(base::wstring ititle, win::Placement iplacement) {
			if(!empty()) {
				Throw(tokurei::CreateError);
			}

			w32WindowClass::reg();

			DWORD style_ex = 0;
			DWORD style = WS_OVERLAPPEDWINDOW;

			RECT window_rectangle;
			window_rectangle.left   = (long)0;
			window_rectangle.top    = (long)0;
			window_rectangle.right  = (long)100;
			window_rectangle.bottom = (long)100;

			AdjustWindowRectEx(&window_rectangle, style, FALSE, style_ex);

			(*_window_info).window = CreateWindowEx(
				style_ex,
				w32WindowClass::name(),
				ititle.c_str(),
				style,
				0, 0,
				window_rectangle.right-window_rectangle.left,
				window_rectangle.bottom-window_rectangle.top,
				NULL, NULL, GetModuleHandleW(NULL), NULL
			);

			if(!(*_window_info).window) {
				Throw(tokurei::CreateError);
			}

			SetWindowLongPtr((*_window_info).window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

			placement(iplacement);

			(*_window_info).dimouse = new input::DIMouse((*_window_info).window, &_event_hub);

			_event_hub.onCreate();

			input::EventLoop::bind(this);
		}

		void Window::destroy() {
			if(!empty()) {
				input::EventLoop::unbind(this);
				delete (*_window_info).dimouse;
				_event_hub.onDestroy();

				SetWindowLongPtr((*_window_info).window, GWLP_USERDATA, LONG(NULL));

				if(!DestroyWindow((*_window_info).window)) {
					Throw(tokurei::DeleteError);
				}
			
				w32WindowClass::unreg();

				(*_window_info).window = nullptr;
			}
		}

		void Window::title(base::wstring ititle) {
			SetWindowText((*_window_info).window, ititle.c_str());
		}

		void Window::placement(win::Placement iplacement) {
			WINDOWPLACEMENT wplacement;
			wplacement.length = sizeof(WINDOWPLACEMENT);

			wplacement.ptMaxPosition.x = 0;
			wplacement.ptMaxPosition.y = 0;

			wplacement.ptMinPosition.x = 0;
			wplacement.ptMinPosition.y = 0;

			wplacement.rcNormalPosition.left = iplacement.x();
			wplacement.rcNormalPosition.top = iplacement.y();
			wplacement.rcNormalPosition.right = wplacement.rcNormalPosition.left + iplacement.width();
			wplacement.rcNormalPosition.bottom = wplacement.rcNormalPosition.top + iplacement.height();

			wplacement.flags = 0;

			if(iplacement.minimized()) {
				wplacement.showCmd = SW_MINIMIZE;
				if(iplacement.maximized()) {
					wplacement.flags = WPF_RESTORETOMAXIMIZED;
				}
			} else if(iplacement.maximized()) {
				wplacement.showCmd = SW_MAXIMIZE;
			} else {
				wplacement.showCmd = SW_RESTORE;
			}

			if(border() != iplacement.border()) {
				border(iplacement.border());
			}
			SetWindowPlacement((*_window_info).window, &wplacement);
		}

		win::Placement Window::placement() {
			WINDOWPLACEMENT wplacement;
			wplacement.length = sizeof(WINDOWPLACEMENT);

			GetWindowPlacement((*_window_info).window, &wplacement);

			win::Placement oplacement;

			oplacement.pos(wplacement.rcNormalPosition.left, wplacement.rcNormalPosition.top);
			oplacement.size(wplacement.rcNormalPosition.right - wplacement.rcNormalPosition.left, wplacement.rcNormalPosition.bottom - wplacement.rcNormalPosition.top);

			if(wplacement.flags == WPF_RESTORETOMAXIMIZED || wplacement.showCmd == SW_MAXIMIZE) {
				oplacement.maximized(true);
			} else {
				oplacement.maximized(false);
			}

			if(wplacement.showCmd == SW_MINIMIZE) {
				oplacement.minimized(true);
			} else {
				oplacement.minimized(false);
			}

			oplacement._border = border();

			return oplacement;
		}

		void Window::resize(size_t iwidth, size_t iheight) {
			SetWindowPos((*_window_info).window, 0, 0, 0, iwidth, iheight, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
		}

		void Window::move(size_t ix, size_t iy) {
			SetWindowPos((*_window_info).window, 0, ix, iy, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
		}

		void Window::border(bool iborder) {
			if(border() != iborder) {
				win::Placement p = placement();
				p.border(iborder);

				DWORD style_ex = 0;
				DWORD style = 0;

				if(iborder) {
					style_ex = 0;
					style = WS_OVERLAPPEDWINDOW;
				} else {
					style_ex = WS_EX_TOPMOST;
					style = WS_POPUP;
				}

				SetWindowLong((*_window_info).window, GWL_STYLE, style);
				SetWindowLong((*_window_info).window, GWL_EXSTYLE, style_ex);

				placement(p);
			}
		}

		bool Window::border() {
			DWORD style = 0;

			style = GetWindowLong((*_window_info).window, GWL_STYLE);

			if((style & WS_POPUP) != 0) {
				return false;
			} else {
				return true;
			}
		}

		void Window::show() {
			ShowWindow((*_window_info).window, SW_SHOW);
		}

		void Window::hide() {
			ShowWindow((*_window_info).window, SW_HIDE);
		}

		bool Window::active() {
			return GetActiveWindow() == (*_window_info).window;
		}

		bool Window::empty() {
			return !(*_window_info).window;
		}
	}  // namespace video
}  // namespace cb

#endif
