/*
 * bString.cpp
 *
 *  Created on: 16/12/2012
 *      Author: Douglas M. Freitas
 * 
 *   Copyright: Staff 42 © 2013
 */

#include <base/bString.h>

#include <base/bPrint.h>

#include <boost/locale.hpp>

#include <functional>

#include <locale>

#include <sstream>

namespace cb {
	namespace base {
		string print(string iformat, ...) {
			string str;
			PRINT(str, iformat);

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
			for(size_t i=0 ; i<istr.size() ; i++) {
				istr[i] = toupper(istr[i]);
			}
			return istr;
		}

		string lower(string istr) {
			for(size_t i=0 ; i<istr.size() ; i++) {
				istr[i] = tolower(istr[i]);
			}
			return istr;
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

		//Converte do tipo para a string
		string tostr(int ivalue) {
			std::ostringstream out;
			out << ivalue;
			return out.str();
		}

		string tostr(unsigned int ivalue) {
			std::ostringstream out;
			out << ivalue;
			return out.str();
		}

		string tostr(float ivalue) {
			std::ostringstream out;
			out << ivalue;
			return out.str();
		}

		string tostr(double ivalue) {
			std::ostringstream out;
			out << ivalue;
			return out.str();
		}

		string tostr(bool ivalue) {
			return ivalue?"true":"false";
		}

		//Converte de string para o tipo
		int toint(string istr) {
			std::istringstream in(istr);
			int value;
			in >> value;
			if(in.rdstate() & std::ios::failbit) {
				return 0;
			}
			return value;
		}

		unsigned int touint(string istr) {
			std::istringstream in(istr);
			unsigned int value;
			in >> value;
			if(in.rdstate() & std::ios::failbit) {
				return 0u;
			}
			return value;
		}

		float tofloat(string istr) {
			std::istringstream in(istr);
			float value;
			in >> value;
			if(in.rdstate() & std::ios::failbit) {
				return 0.0f;
			}
			return value;
		}

		double todouble(string istr) {
			std::istringstream in(istr);
			double value;
			in >> value;
			if(in.rdstate() & std::ios::failbit) {
				return 0.0f;
			}
			return value;
		}

		bool tobool(string istr) {
			istr = upper(istr);
			if(istr == "FALSE" || istr == "OFF" || istr == "0") {
				return false;
			} else if(istr == "TRUE" || istr == "ON" || istr == "1") {
				return true;
			}
			return false;
		}

		//Funções para verificar o tipo
		bool isint(string istr) {
			std::istringstream in(istr);
			int value;
			in >> value;
			if(in.rdstate() & std::ios::failbit) {
				return false;
			}
			return true;
		}

		bool isuint(string istr) {
			std::istringstream in(istr);
			unsigned int value;
			in >> value;
			if(in.rdstate() & std::ios::failbit) {
				return false;
			}
			return true;
		}

		bool isfloat(string istr) {
			std::istringstream in(istr);
			float value;
			in >> value;
			if(in.rdstate() & std::ios::failbit) {
				return false;
			}
			return true;
		}

		bool isdouble(string istr) {
			std::istringstream in(istr);
			double value;
			in >> value;
			if(in.rdstate() & std::ios::failbit) {
				return false;
			}
			return true;
		}

		bool isbool(string istr) {
			istr = upper(istr);
			return istr == "FALSE" || istr == "OFF" || istr == "0" || istr == "TRUE" || istr == "ON" || istr == "1";
		}
	}  // namespace base
}  // namespace cb

