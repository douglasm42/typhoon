/* 
 * - Cumulonimbus - ☁
 * File: vwCursor.cpp
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
#include <cb/video/Cursor.h>

#include <cb/base/Exception.h>
#include <cb/base/Log.h>

#include <cb/video/Window.h>

#include <video/win32/Windows.h>
#include <video/win32/WindowInfo.h>
#include <video/win32/BitmapToIcon.h>

namespace cb {
	namespace video {
		KinKey(kin::CursorHandler, HICON__);
		KinKey(kin::WindowInfo, w32WindowInfo);

		Cursor::Cursor(Window *iwindow):_window(iwindow), _show(true), _hold(false), _is_active(false) {
		}
		
		Cursor::~Cursor() {
			SetCursor(NULL);
			std::map<base::string, kin::CursorHandler>::iterator it;
			for(it=_cursors.begin() ; it != _cursors.end() ; ++it) {
				DestroyIcon(&it->second);
			}
		}

		void Cursor::show(bool ishow) {
			_show = ishow;
			if(_show) {
				while(ShowCursor(TRUE) < 0);
			} else {
				while(ShowCursor(FALSE) >= 0);
			}
		}

		bool Cursor::show() {
			return _show;
		}

		void Cursor::add(const base::string &ikey, data::ubBitmapRGBA &ibmp, size_t ixhotspot, size_t iyhotspot) {
			HCURSOR cur = bitmapToIcon(ibmp, ixhotspot, iyhotspot, FALSE);

			if(cur) {
				std::map<base::string, kin::CursorHandler>::iterator it = _cursors.find(ikey);
				if(it != _cursors.end()) {
					rem(ikey);
				}
				_cursors[ikey] << cur;
			} else {
				Throw(tokurei::CreateError);
			}
		}

		void Cursor::add(const base::string &ikey, data::ubBitmapRGB &ibmp, size_t ixhotspot, size_t iyhotspot, u8vec3 itransparent) {
			HCURSOR cur = bitmapToIcon(ibmp, ixhotspot, iyhotspot, itransparent, FALSE);

			if(cur) {
				std::map<base::string, kin::CursorHandler>::iterator it = _cursors.find(ikey);
				if(it != _cursors.end()) {
					rem(ikey);
				}
				_cursors[ikey] << cur;
			} else {
				Throw(tokurei::CreateError);
			}
		}

		void Cursor::rem(const base::string &ikey) {
			std::map<base::string, kin::CursorHandler>::iterator it = _cursors.find(ikey);
			if(it != _cursors.end()) {
				if(GetCursor() == &(it->second)) {
					SetCursor(NULL);
				}
				if(it->second._pointer == _active._pointer) {
					_active << nullptr;
				}
				DestroyIcon(&it->second);
				_cursors.erase(it);
			}
		}

		void Cursor::select(const base::string &ikey) {
			std::map<base::string, kin::CursorHandler>::iterator it = _cursors.find(ikey);
			if(it != _cursors.end()) {
				if(it->second._pointer != _active._pointer) {
					bool reset = false;
					if(GetCursor() == &(_active)) {
						reset = true;
					}
					_active._pointer = it->second._pointer;
					if(reset) {
						onCursorSet();
					}
				}
			} else {
				ThrowDet(tokurei::SetFailed, "Key: %s", ikey.c_str());
			}
		}

		void Cursor::hold(bool ihold) {
			_hold = ihold;
			show(!_hold);

			if(_is_active) {
				onActivate();
			}
		}

		void Cursor::move(size_t ix, size_t iy) {
			POINT pt = {ix, iy};
			ClientToScreen((*_window->info()).window, &pt);
			SetCursorPos(pt.x,pt.y);
		}

		void Cursor::onActivate() {
			_is_active = true;
			show(_show);
			if(_hold) {
				//Prende o cursor dentro da janela.
				POINT p = {0, 0};
				ClientToScreen((*_window->info()).window, &p);
				RECT rect;
				GetClientRect((*_window->info()).window, &rect);
				rect.left += p.x;
				rect.right += p.x;
				rect.top += p.y;
				rect.bottom += p.y;
				ClipCursor(&rect);
			} else {
				//Desprende o cursor de dentro da janela.
				ClipCursor(NULL);
			}
		}

		void Cursor::onDeactivate() {
			_is_active = false;
			ClipCursor(NULL);
			while(ShowCursor(TRUE) < 0);
		}

		void Cursor::onResize() {
			if(_is_active) {
				onActivate();
			}
		}

		void Cursor::onCursorSet() {
			SetCursor(&_active);
		}
	}  // namespace video
}  // namespace cb
