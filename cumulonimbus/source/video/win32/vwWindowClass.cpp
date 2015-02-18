/* 
 * - Cumulonimbus - ☁
 * File: vwWindows.cpp
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
#include <cb/base/Exception.h>

#include <cb/video/win32/WindowClass.h>
#include <cb/input/win32/WindowProc.h>

#include <cb/base/Log.h>

namespace cb {
	namespace video {
		const wchar_t *w32WindowClass::_name = L"Cumulonimbus::WindowClass";
		size_t w32WindowClass::_window_count = 0;
		ATOM w32WindowClass::_atom = 0;

		void w32WindowClass::reg() {
			if(_window_count == 0) {
				WNDCLASSEX window_class;
				window_class.cbSize			= sizeof(WNDCLASSEX);
				window_class.style			= CS_OWNDC;
				window_class.lpfnWndProc	= input::WindowProc;
				window_class.cbClsExtra		= 0;
				window_class.cbWndExtra		= 0;
				window_class.hInstance		= GetModuleHandle(NULL);
				window_class.hIcon			= NULL;
				window_class.hCursor		= NULL;
				window_class.hbrBackground	= (HBRUSH) GetStockObject(BLACK_BRUSH);
				window_class.lpszMenuName	= NULL;
				window_class.lpszClassName	= _name;
				window_class.hIconSm		= NULL;

				_atom = RegisterClassEx(&window_class);

				if(!_atom) {
					Throw(tokurei::CreateError);
				}
			}
			_window_count++;
		}

		void w32WindowClass::unreg() {
			_window_count--;
			if(_window_count == 0) {
				if(!UnregisterClass(_name,GetModuleHandle(NULL))) {
					Throw(tokurei::DeleteError);
				}
			}
		}

		const wchar_t *w32WindowClass::getName() {
			return _name;
		}

		ATOM w32WindowClass::getATOM() {
			return _atom;
		}
	}  // namespace video
}  // namespace cb
