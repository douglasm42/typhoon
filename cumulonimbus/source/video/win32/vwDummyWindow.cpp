/* 
 * - Cumulonimbus - ☁
 * File: vwDummyWindow.cpp
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
#include <cb/video/DummyWindow.h>

#include <cb/video/win32/WindowStyle.h>

#include <cb/base/Exception.h>

namespace cb {
	namespace video {
		LRESULT CALLBACK DummyWindowProc(HWND iwindow_handler, UINT imessage, WPARAM iwparam, LPARAM ilparam) {
			return DefWindowProc(iwindow_handler,imessage,iwparam,ilparam);
		}

		class CbAPI w32DummyWindowClass {
		private:
			static const wchar_t *_name;
			static size_t _window_count;

		public:
			static void reg();
			static void unreg();
			static const wchar_t *getName() {return _name;}
		};

		const wchar_t *w32DummyWindowClass::_name = L"Cumulonimbus::DummyWindowClass";
		size_t w32DummyWindowClass::_window_count = 0;

		void w32DummyWindowClass::reg() {
			if(_window_count == 0) {
				WNDCLASSEX window_class;
				window_class.cbSize			= sizeof(WNDCLASSEX);
				window_class.style			= CS_OWNDC;
				window_class.lpfnWndProc	= DummyWindowProc;
				window_class.cbClsExtra		= 0;
				window_class.cbWndExtra		= 0;
				window_class.hInstance		= GetModuleHandle(NULL);
				window_class.hIcon			= NULL;
				window_class.hCursor		= NULL;
				window_class.hbrBackground	= (HBRUSH) GetStockObject(BLACK_BRUSH);
				window_class.lpszMenuName	= NULL;
				window_class.lpszClassName	= _name;
				window_class.hIconSm		= NULL;

				if(!RegisterClassEx(&window_class)) {
					Throw(tokurei::CreateError);
				}
			}
			_window_count++;
		}

		void w32DummyWindowClass::unreg() {
			_window_count--;
			if(_window_count == 0) {
				if(!UnregisterClass(_name,GetModuleHandle(NULL))) {
					Throw(tokurei::DeleteError);
				}
			}
		}

		DummyWindow::DummyWindow() {
			w32DummyWindowClass::reg();

			_w_hwnd = CreateWindowEx(
				video::getStyleEx(video::Border::System),
				w32DummyWindowClass::getName(),
				L"DummyWindow",
				getStyle(video::Border::System),
				0, 0,
				100,
				100,
				NULL, NULL, GetModuleHandleW(NULL), reinterpret_cast<LPVOID>(this)
			);

			if(!_w_hwnd) {
				Throw(tokurei::CreateError);
			}
		}

		DummyWindow::~DummyWindow() {
			if(!DestroyWindow(_w_hwnd)) {
				Throw(tokurei::DeleteError);
			}
			
			w32DummyWindowClass::unreg();
		}
	}  // namespace video
}  // namespace cb
