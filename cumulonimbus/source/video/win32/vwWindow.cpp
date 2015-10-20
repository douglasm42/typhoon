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
#include <cb/video/Window.hpp>
#include <cb/base/Exception.hpp>
#include <cb/base/Log.hpp>

#include <cb/video/win32/Windows.hpp>

#include <cb/video/win32/WindowClass.hpp>
#include <cb/video/win32/WindowStyle.hpp>

#include <cb/input/EventLoop.hpp>

namespace cb {
	namespace video {
		Window::Window(base::string ititle, Border iborder)
		:_w_hwnd(nullptr)
		,_w_dimouse(nullptr)
		,_w_xinput(nullptr)
		
		,_border(iborder)

		,_width()
		,_height()

		,_cursor(nullptr)
		,_cursor_show(true)
		,_cursor_hold(false)
		,_cursor_held_position(0,0)

		,_big_icon(nullptr)
		,_small_icon(nullptr)

		,_event_hub(nullptr) {
			create(base::utf16(ititle), iborder);
		}

		Window::Window(base::string16 ititle, Border iborder)
		:_w_hwnd(nullptr)
		,_w_dimouse(nullptr)
		,_w_xinput(nullptr)
		
		,_border(iborder)

		,_width()
		,_height()

		,_cursor(nullptr)
		,_cursor_show(true)
		,_cursor_hold(false)
		,_cursor_held_position(0,0)

		,_big_icon(nullptr)
		,_small_icon(nullptr)

		,_event_hub(nullptr) {
			create(ititle, iborder);
		}

		Window::~Window() {
			input::EventLoop::unbind(this);

			delete _w_dimouse;
			delete _w_xinput;

			SetWindowLongPtr(_w_hwnd, GWLP_USERDATA, LONG(NULL));

			if(!DestroyWindow(_w_hwnd)) {
				Throw(tokurei::DeleteError);
			}
			
			w32WindowClass::unreg();

			_w_hwnd = nullptr;
		}

		void Window::create(base::string16 ititle, Border iborder) {
			w32WindowClass::reg();

			_w_hwnd = CreateWindowEx(
				getStyleEx(_border),
				MAKEINTATOM(w32WindowClass::getATOM()),
				L"Teste",
				getStyle(_border),
				0, 0,
				100,
				100,
				NULL, NULL, GetModuleHandle(NULL), reinterpret_cast<LPVOID>(this)
			);
			DWORD error = GetLastError();

			if(!_w_hwnd) {
				ThrowDet(tokurei::CreateError, "Error: %p", error);
			}

			_w_dimouse = new input::DIMouse(_w_hwnd, _event_hub);
			_w_xinput = new input::XInput(_event_hub);

			input::EventLoop::bind(this);
		}

		void Window::setTitle(base::string16 ititle) {
			SetWindowText(_w_hwnd, (const wchar_t *)ititle.c_str());
		}

		void Window::setPlacement(const Placement &iplacement) {
			WINDOWPLACEMENT wplacement;
			Placement::wConvert(iplacement, _border, wplacement);

			SetWindowPlacement(_w_hwnd, &wplacement);
		}

		Placement Window::getPlacement() {
			WINDOWPLACEMENT wplacement;
			wplacement.length = sizeof(WINDOWPLACEMENT);

			GetWindowPlacement(_w_hwnd, &wplacement);

			Placement oplacement;
			Placement::wConvert(wplacement, _border, oplacement);

			return oplacement;
		}

		void Window::show() {
			ShowWindow(_w_hwnd, SW_SHOW);
		}

		void Window::hide() {
			ShowWindow(_w_hwnd, SW_HIDE);
		}

		void Window::minimize() {
			SendMessage(_w_hwnd, WM_SYSCOMMAND, SC_MINIMIZE, -1);
		}

		void Window::maximize() {
			SendMessage(_w_hwnd, WM_SYSCOMMAND, SC_MAXIMIZE, -1);
		}

		void Window::restore() {
			SendMessage(_w_hwnd, WM_SYSCOMMAND, SC_RESTORE, -1);
		}

		void Window::close() {
			SendMessage(_w_hwnd, WM_SYSCOMMAND, SC_CLOSE, -1);
		}

		bool Window::isActive() const {
			return GetActiveWindow() == _w_hwnd;
		}

		void Window::setCursor(Cursor *icursor) {
			_cursor = icursor;

			if(isActive() && Cursor::wIsInsideWindow(_w_hwnd)) {
				Cursor::wSet(_cursor);
			}
		}

		bool Window::cursorIsShown() {
			return _cursor_show;
		}

		void Window::cursorShow(bool ishow) {
			_cursor_show = ishow;

			if(isActive() && !_cursor_hold) {
				Cursor::wShow(ishow);
			}
		}

		bool Window::cursorIsHeld() {
			return _cursor_hold;
		}

		void Window::cursorSetHold(bool ihold) {
			if(!_cursor_hold && ihold) {
				_cursor_held_position = cursorGetPosition();
			}

			if(isActive() && _cursor_hold && !ihold) {
				cursorSetPosition(_cursor_held_position);
			}

			_cursor_hold = ihold;
			ShowCursor(_cursor_show);

			if(isActive()) {
				Cursor::wHold(_w_hwnd, _cursor_hold);
			}
		}

		void Window::cursorSetPosition(ivec2 iposition) {
			Cursor::wSetPosition(_w_hwnd, iposition);
		}

		ivec2 Window::cursorGetPosition() {
			if(_cursor_hold) {
				return _cursor_held_position;
			} else {
				return Cursor::wGetPosition(_w_hwnd);
			}
		}

		void Window::setBigIcon(Icon *ibig_icon) {
			_big_icon = ibig_icon;
			if(_big_icon) {
				SendMessage(_w_hwnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(_big_icon->wGetHICON()));
			} else {
				SendMessage(_w_hwnd, WM_SETICON, ICON_BIG, NULL);
			}
		}

		void Window::setSmallIcon(Icon *ismall_icon) {
			_small_icon = ismall_icon;
			if(_small_icon) {
				SendMessage(_w_hwnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(_small_icon->wGetHICON()));
			} else {
				SendMessage(_w_hwnd, WM_SETICON, ICON_SMALL, NULL);
			}
		}

		void Window::setEventHub(input::EventHub *ievent_hub) {
			_event_hub = ievent_hub;

			_w_dimouse->setEventHub(ievent_hub);
			_w_xinput->setEventHub(ievent_hub);
			if(_event_hub) {
				_event_hub->onResize(_width, _height);
			}
		}

		void Window::onResize(uint32 iwidth, uint32 iheight) {
			_width = iwidth;
			_height = iheight;
		}

		void Window::onActivate() {
			cursorSetHold(_cursor_hold);
		}

		void Window::onDeactivate() {
			cursorSetHold(_cursor_hold);
		}

		void Window::onClose() {
			Cursor::wHold(nullptr, false);
		}

		void Window::setPixelFormat(graphic::PixelFormat &ipf) {
			if(ipf.isValid()) {
				if(SetPixelFormat(GetDC(_w_hwnd), ipf.wGetPixelFormatId(), &ipf.wGetPFD()) == FALSE) {
					ThrowDet(tokurei::SetFailed, "Error: %d", GetLastError());
				}
			} else {
				ThrowDet(tokurei::SetFailed, "PixelFormat invalid.");
			}
		}
	}  // namespace video
}  // namespace cb
