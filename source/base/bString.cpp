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

#include <boost/locale.hpp>

#include <functional>
#include <sstream>

namespace cb {
	namespace base {
		string format(string iformat, ...) {
			string str;
			CUMULONIMBUS_FORMAT(str, iformat);

			return str;
		}

		wstring utf16(string itext) {
			return boost::locale::conv::utf_to_utf<wchar_t>(itext);
		}
		lstring utf32(string itext) {
			return boost::locale::conv::utf_to_utf<unsigned int>(itext);
		}

		string utf8(wstring itext) {
			return boost::locale::conv::utf_to_utf<char>(itext);
		}
		lstring utf32(wstring itext) {
			return boost::locale::conv::utf_to_utf<unsigned int>(itext);
		}

		string utf8(lstring itext) {
			return boost::locale::conv::utf_to_utf<char>(itext);
		}
		wstring utf16(lstring itext) {
			return boost::locale::conv::utf_to_utf<wchar_t>(itext);
		}

		string encode(string itext, string iencoding) {
			return boost::locale::conv::from_utf(itext, iencoding);
		}

		string encode(wstring itext, string iencoding) {
			return boost::locale::conv::from_utf(itext, iencoding);
		}

		string upper(string istr) {
			return boost::locale::to_upper(istr);
		}

		string lower(string istr) {
			return boost::locale::to_lower(istr);
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

		unsigned int hash(string istr) {
			std::hash<string> strhash;
			return strhash(istr);
		}
	}  // namespace base
}  // namespace cb

