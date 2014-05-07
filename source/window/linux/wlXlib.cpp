/*
 * wlXlib.cpp
 *
 *  Created on: May 4, 2014
 *      Author: douglas
 */

#include <base/Setup.h>
#ifdef CbLinux

#include <window/linux/Xlib.h>

#include <base/Exception.h>

namespace cb {
	namespace window {
		xstring &operator<<(xstring &ixstr, const base::string &istr) {
			return ixstr << base::utf16(istr);
		}

		xstring &operator<<(xstring &ixstr, const base::wstring &iwstr) {
			ixstr.reserve(ixstr.size() + iwstr.length());
			for(size_t j=0 ; j<iwstr.length() ; j++) {
				unsigned char *pt = (unsigned char *)&iwstr[j];
				XChar2b c = {pt[1], pt[0]};
				ixstr.push_back(c);
			}
			return ixstr;
		}

		xstring &operator<<(xstring &ixstr, const base::lstring &ilstr) {
			return ixstr << base::utf16(ilstr);
		}

		XDisplay *XConnection::_display = nullptr;
		size_t XConnection::_connections_count = 0;

		XDisplay *XConnection::connect() {
			_connections_count++;
			if(!_display) {
				_display = XOpenDisplay(":0");
			}
			return _display;
		}

		void XConnection::disconnect() {
			if(_connections_count) {
				_connections_count--;
				if(!_connections_count) {
					XCloseDisplay(_display);
					_display = nullptr;
				}
			} else {
				Throw(tokurei::CloseError);
			}
		}
	}  // namespace window
}  // namespace cb

#endif
