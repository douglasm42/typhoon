/* 
 * - Cumulonimbus - ☁
 * File: bString.cpp
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
#include <base/String.h>

#include <base/FormatMacro.h>

#include <locale>
#include <codecvt>

#include <functional>
#include <sstream>

namespace cb {
	namespace base {
		string format(string iformat, ...) {
			string str;
			CUMULONIMBUS_FORMAT(str, iformat);

			return str;
		}

		string16 utf16(string itext) {
			std::wstring_convert<std::codecvt_utf8<char16_t>,char16_t> cv;
			return cv.from_bytes(itext);
		}

		string32 utf32(string itext) {
			std::wstring_convert<std::codecvt_utf8<char32_t>,char32_t> cv;
			return cv.from_bytes(itext);
		}

		string utf8(string16 itext) {
			std::wstring_convert<std::codecvt_utf8<char16_t>,char16_t> cv;
			return cv.to_bytes(itext);
		}

		string32 utf32(string16 itext) {
			return utf32(utf8(itext));
		}

		string utf8(string32 itext) {
			std::wstring_convert<std::codecvt_utf8<char32_t>,char32_t> cv;
			return cv.to_bytes(itext);
		}

		string16 utf16(string32 itext) {
			return utf16(utf8(itext));
		}

		string upper(string istr) {
			std::locale loc;
			string ustr;
			for (std::string::size_type i=0; i<istr.length(); ++i) {
				ustr.push_back(std::toupper(istr[i],loc));
			}
			return ustr;
		}

		string lower(string istr) {
			std::locale loc;
			string ustr;
			for (std::string::size_type i=0; i<istr.length(); ++i) {
				ustr.push_back(std::tolower(istr[i],loc));
			}
			return ustr;
		}

		string CbAPI trim(string istr, int iflags) {
			string result;
			string::iterator it = istr.begin();

			string::iterator endit = istr.end();
			if(endit != istr.begin()) endit--;
			while(endit != istr.begin() && isspace(*endit)) {
				endit--;
			}
			if(endit != istr.end()) {
				endit++;
			}

			if(iflags & TrimLeft) {
				while(it != istr.end() && isspace(*it)) {
					it++;
				}
			} else {
				while(it != istr.end() && isspace(*it)) {
					result.push_back(*it);
					it++;
				}
			}

			if(iflags & TrimInner) {
				bool islastspace = false;
				while(it != istr.end() && it != endit) {
					if(isspace(*it)) {
						if(!islastspace) {
							result.push_back(' ');
						}
						islastspace = true;
					} else {
						islastspace = false;
						result.push_back(*it);
					}
					it++;
				}
			} else {
				while(it != istr.end() && it != endit) {
					result.push_back(*it);
					it++;
				}
			}

			if(!(iflags & TrimRight)) {
				while(it != istr.end()) {
					result.push_back(*it);
					it++;
				}
			}

			return result;
		}

		size_t hash(string istr) {
			std::hash<string> strhash;
			return strhash(istr);
		}
	}  // namespace base
}  // namespace cb

