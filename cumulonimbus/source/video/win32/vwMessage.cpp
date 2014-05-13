/* 
 * - Cumulonimbus - ☁
 * File: vwMessage.cpp
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

#include <video/Message.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <video/win32/Windows.h>

namespace cb {
	namespace video {

		void Message::show() {
			_message_lines.push_back(base::wstring());
			_message_lines.push_back(base::wstring(L"Sorry about the inconvenience,"));
			_message_lines.push_back(base::wstring(L"- Staff42"));

			base::wstring str = L"";
			str += _message_lines[0];
			for(size_t i=1 ; i<_message_lines.size() ; ++i) {
				str += L"\n" + _message_lines[i];
			}

			if(_type == msg::Error) {
				MessageBox(NULL, str.c_str(), L"Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL | MB_TOPMOST);
			} else if(_type == msg::Warning) {
				MessageBox(NULL, str.c_str(), L"Warning", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL | MB_TOPMOST);
			} else if(_type == msg::Info) {
				MessageBox(NULL, str.c_str(), L"Information", MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL | MB_TOPMOST);
			} else {
				MessageBox(NULL, str.c_str(), L"Unknown", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL | MB_TOPMOST);
			}
		}
	}  // namespace video
}  // namespace cb

#endif
