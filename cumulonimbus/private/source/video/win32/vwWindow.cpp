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
#include <cb/video/Window.h>
#include <cb/base/Exception.h>
#include <cb/base/Log.h>

#include <video/win32/Windows.h>
#include <video/win32/WindowClass.h>
#include <video/win32/WindowInfo.h>
#include <video/win32/BitmapToIcon.h>
#include <video/win32/Placement.h>
#include <video/win32/WindowStyle.h>

#include <cb/input/EventLoop.h>

#include <cb/graphic/GLContext.h>

namespace cb {
	namespace video {
		KinKey(kin::WindowInfo, w32WindowInfo);

		Window::Window() :_border(Border::System), _cursor(this) {
			_window_info << new w32WindowInfo;
			createDummy();
		}

		Window::Window(base::string16 ititle, const Placement &iplacement) :_border(iplacement.border()), _cursor(this) {
			_window_info << new w32WindowInfo;
			create(ititle, iplacement);
		}

		Window::Window(base::string16 ititle, int ix, int iy, int iwidth, int iheight, bool imaximized, bool iminimized, Border iborder) :_border(_border), _cursor(this) {
			_window_info << new w32WindowInfo;
			create(ititle, Placement(ix, iy, iwidth, iheight, imaximized, iminimized, iborder));
		}

		Window::~Window() {
			destroy();
			delete (&_window_info);
		}

		void Window::create(base::string16 ititle, const Placement &iplacement) {
			if(!empty()) {
				Throw(tokurei::CreateError);
			}

			_border = iplacement.border();

			w32WindowClass::reg();

			WINDOWPLACEMENT wp;
			getPlacement(iplacement, wp);

			(*_window_info).window = CreateWindowEx(
				getStyleEx(_border),
				w32WindowClass::name(),
				(const wchar_t *)ititle.c_str(),
				getStyle(_border),
				0, 0,
				wp.rcNormalPosition.right-wp.rcNormalPosition.left,
				wp.rcNormalPosition.bottom-wp.rcNormalPosition.top,
				NULL, NULL, GetModuleHandleW(NULL), reinterpret_cast<LPVOID>(this)
			);

			if(!(*_window_info).window) {
				Throw(tokurei::CreateError);
			}

			SetWindowPlacement((*_window_info).window, &wp);

			(*_window_info).dimouse = new input::DIMouse((*_window_info).window, &_event_hub);
			(*_window_info).xinput = new input::XInput(&_event_hub);

			input::EventLoop::bind(this);
		}

		void Window::createDummy() {
			if(!empty()) {
				Throw(tokurei::CreateError);
			}

			w32WindowClass::reg();

			Placement placement(0, 0, 100, 100, false, false, Border::System);
			WINDOWPLACEMENT wp;
			getPlacement(placement, wp);

			(*_window_info).window = CreateWindowEx(
				getStyleEx(_border),
				w32WindowClass::name(),
				L"Dummy",
				getStyle(_border),
				0, 0,
				wp.rcNormalPosition.right-wp.rcNormalPosition.left,
				wp.rcNormalPosition.bottom-wp.rcNormalPosition.top,
				NULL, NULL, GetModuleHandleW(NULL), reinterpret_cast<LPVOID>(this)
			);

			if(!(*_window_info).window) {
				Throw(tokurei::CreateError);
			}

			(*_window_info).dimouse = new input::DIMouse((*_window_info).window, &_event_hub);
			(*_window_info).xinput = new input::XInput(&_event_hub);

			input::EventLoop::bind(this);
		}

		void Window::destroy() {
			if(!empty()) {
				input::EventLoop::unbind(this);
				delete (*_window_info).dimouse;
				delete (*_window_info).xinput;

				SetWindowLongPtr((*_window_info).window, GWLP_USERDATA, LONG(NULL));

				if(!DestroyWindow((*_window_info).window)) {
					Throw(tokurei::DeleteError);
				}
			
				w32WindowClass::unreg();

				(*_window_info).window = nullptr;
			}
		}

		void Window::title(base::string16 ititle) {
			SetWindowText((*_window_info).window, (const wchar_t *)ititle.c_str());
		}

		void Window::placement(const Placement &iplacement) {
			WINDOWPLACEMENT wplacement;
			getPlacement(iplacement, wplacement);

			if(_border != iplacement.border()) {
				border(iplacement.border());
			}
			SetWindowPlacement((*_window_info).window, &wplacement);
			UpdateWindow((*_window_info).window);
		}

		Placement Window::placement() {
			WINDOWPLACEMENT wplacement;
			wplacement.length = sizeof(WINDOWPLACEMENT);

			GetWindowPlacement((*_window_info).window, &wplacement);

			Placement oplacement;
			getPlacement(wplacement, _border, oplacement);

			return oplacement;
		}

		void Window::resize(int iwidth, int iheight) {
			SetWindowPos((*_window_info).window, 0, 0, 0, iwidth, iheight, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
		}

		void Window::move(int ix, int iy) {
			SetWindowPos((*_window_info).window, 0, ix, iy, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
		}

		void Window::border(Border iborder) {
			if(_border != iborder) {
				_border = iborder;

				POINT corner = {0, 0};
				ClientToScreen((*_window_info).window, &corner);

				RECT client;
				GetClientRect((*_window_info).window, &client);
				client.left		+= corner.x;
				client.top		+= corner.y;
				client.right	+= corner.x;
				client.bottom	+= corner.y;

				if(iborder != Border::Empty) {
					AdjustWindowRectEx(&client, getStyle(iborder), FALSE, getStyleEx(iborder));
				}

				SetWindowLong((*_window_info).window, GWL_STYLE, getStyle(iborder));
				SetWindowLong((*_window_info).window, GWL_EXSTYLE, getStyleEx(iborder));

				SetWindowPos((*_window_info).window, 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
				//UpdateWindow((*_window_info).window);
				//SetWindowPos((*_window_info).window, 0, client.left, client.top, client.right - client.left, client.bottom - client.top, SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED | SWP_SHOWWINDOW);
			}
		}

		void Window::show() {
			ShowWindow((*_window_info).window, SW_SHOW);
		}

		void Window::hide() {
			ShowWindow((*_window_info).window, SW_HIDE);
		}

		void Window::minimize() {
			SendMessage((*_window_info).window, WM_SYSCOMMAND, SC_MINIMIZE, -1);
		}

		void Window::maximize() {
			SendMessage((*_window_info).window, WM_SYSCOMMAND, SC_MAXIMIZE, -1);
		}

		void Window::restore() {
			SendMessage((*_window_info).window, WM_SYSCOMMAND, SC_RESTORE, -1);
		}

		void Window::close() {
			SendMessage((*_window_info).window, WM_SYSCOMMAND, SC_CLOSE, -1);
		}

		bool Window::active() {
			return GetActiveWindow() == (*_window_info).window;
		}

		bool Window::empty() {
			return !(*_window_info).window;
		}

		void Window::icon(data::ubBitmapRGBA &ibmp) {
			HICON icon = bitmapToIcon(ibmp, 0, 0, TRUE);
			if(icon) {
				SendMessage((*_window_info).window, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(icon));
				SendMessage((*_window_info).window, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(icon));
			} else {
				Throw(tokurei::SetFailed);
			}
		}

		void Window::icon(data::ubBitmapRGB &ibmp, u8vec3 itransparent) {
			HICON icon = bitmapToIcon(ibmp, 0, 0, itransparent, TRUE);
			if(icon) {
				SendMessage((*_window_info).window, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(icon));
				SendMessage((*_window_info).window, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(icon));
			} else {
				Throw(tokurei::SetFailed);
			}
		}
	}  // namespace video
}  // namespace cb
