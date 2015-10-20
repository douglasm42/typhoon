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
#include <cb/base/String.hpp>

#include <cb/base/FormatMacro.hpp>

#include <locale>
#include <codecvt>

#include <functional>
#include <sstream>

namespace cb {
	namespace base {
		typedef std::wstring_convert<std::codecvt_utf8<char16_t>,char16_t> utf8_16;
		typedef std::wstring_convert<std::codecvt_utf8<char32_t>,char32_t> utf8_32;
		typedef std::wstring_convert<std::codecvt_utf8<wchar_t>,wchar_t> utf8_wide;

		string format(const string &iformat, ...) {
			string str;
			CUMULONIMBUS_FORMAT(str, iformat);

			return str;
		}

		wstring format(const wstring &iformat, ...) {
			string iformat8 = utf8(iformat);
			string str;
			CUMULONIMBUS_FORMAT(str, iformat8);

			return wstr(str);
		}

		string16 format(const string16 &iformat, ...) {
			string iformat8 = utf8(iformat);
			string str;
			CUMULONIMBUS_FORMAT(str, iformat8);

			return utf16(str);
		}

		string32 format(const string32 &iformat, ...) {
			string iformat8 = utf8(iformat);
			string str;
			CUMULONIMBUS_FORMAT(str, iformat8);

			return utf32(str);
		}

		string utf8(const wstring &itext) {
			utf8_wide cv;
			return cv.to_bytes(itext);
		}
		string utf8(const string16 &itext) {
			utf8_16 cv;
			return cv.to_bytes(itext);
		}
		string utf8(const string32 &itext) {
			utf8_32 cv;
			return cv.to_bytes(itext);
		}

		wstring wstr(const string &itext) {
			utf8_wide cv;
			return cv.from_bytes(itext);
		}
		wstring wstr(const string16 &itext) {
			utf8_wide cv;
			utf8_16 cv16;
			return cv.from_bytes(cv16.to_bytes(itext));
		}
		wstring wstr(const string32 &itext) {
			utf8_wide cv;
			utf8_32 cv32;
			return cv.from_bytes(cv32.to_bytes(itext));
		}

		string16 utf16(const string &itext) {
			utf8_16 cv;
			return cv.from_bytes(itext);
		}
		string16 utf16(const wstring &itext) {
			utf8_16 cv;
			utf8_wide cvwide;
			return cv.from_bytes(cvwide.to_bytes(itext));
		}
		string16 utf16(const string32 &itext) {
			utf8_16 cv;
			utf8_32 cv32;
			return cv.from_bytes(cv32.to_bytes(itext));
		}

		string32 utf32(const string &itext) {
			utf8_32 cv;
			return cv.from_bytes(itext);
		}
		string32 utf32(const wstring &itext) {
			utf8_32 cv;
			utf8_wide cvwide;
			return cv.from_bytes(cvwide.to_bytes(itext));
		}
		string32 utf32(const string16 &itext) {
			utf8_32 cv;
			utf8_16 cv16;
			return cv.from_bytes(cv16.to_bytes(itext));
		}

		string upper(const string &istr) {
			std::locale loc;
			string ustr;
			for (std::string::size_type i=0; i<istr.length(); ++i) {
				ustr.push_back(std::toupper(istr[i],loc));
			}
			return ustr;
		}

		wstring upper(const wstring &istr) {
			std::locale loc;
			wstring ustr;
			for (std::wstring::size_type i=0; i<istr.length(); ++i) {
				ustr.push_back(std::toupper(istr[i],loc));
			}
			return ustr;
		}

		string16 upper(const string16 &istr) {
			std::locale loc;
			string16 ustr;
			for (string16::size_type i=0; i<istr.length(); ++i) {
				ustr.push_back(std::toupper(istr[i],loc));
			}
			return ustr;
		}

		string32 upper(const string32 &istr) {
			std::locale loc;
			string32 ustr;
			for (string32::size_type i=0; i<istr.length(); ++i) {
				ustr.push_back(std::toupper(istr[i],loc));
			}
			return ustr;
		}

		string lower(const string &istr) {
			std::locale loc;
			string ustr;
			for (std::string::size_type i=0; i<istr.length(); ++i) {
				ustr.push_back(std::tolower(istr[i],loc));
			}
			return ustr;
		}

		wstring lower(const wstring &istr) {
			std::locale loc;
			wstring ustr;
			for (std::wstring::size_type i=0; i<istr.length(); ++i) {
				ustr.push_back(std::tolower(istr[i],loc));
			}
			return ustr;
		}

		string16 lower(const string16 &istr) {
			std::locale loc;
			string16 ustr;
			for (string16::size_type i=0; i<istr.length(); ++i) {
				ustr.push_back(std::tolower(istr[i],loc));
			}
			return ustr;
		}

		string32 lower(const string32 &istr) {
			std::locale loc;
			string32 ustr;
			for (string32::size_type i=0; i<istr.length(); ++i) {
				ustr.push_back(std::tolower(istr[i],loc));
			}
			return ustr;
		}

		string trim(const string &istr, int iflags) {
			string result;
			string::const_iterator it = istr.begin();

			string::const_iterator endit = istr.end();
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

		size_t hash(const string &istr) {
			std::hash<string> strhash;
			return strhash(istr);
		}
	}  // namespace base
}  // namespace cb

