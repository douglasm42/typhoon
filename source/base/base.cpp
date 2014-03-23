/*
 * base.cpp
 *
 *  Created on: 16/12/2012
 *      Author: Douglas M. Freitas
 * 
 *   Copyright: Staff 42 © 2013
 */

#include <base/base.h>
#include <base/bLog.h>

#include <cstdarg>
#include <cstdio>

#include <sstream>
#include <fstream>
#include <string>

#include <base/bWindows.h>

namespace cb {
	namespace base {
		void readFile(std::string ifilename, std::string &ofilestring) {
			char *buffer;
			std::streamoff frag_source_length;

			std::ifstream fin(ifilename.c_str(), std::ios::binary);
			if(fin.is_open()) {
				fin.seekg(0, std::ios::end);
				frag_source_length = fin.tellg();
				fin.seekg(0, std::ios::beg);

				buffer = new char[size_t(frag_source_length)];
				fin.read(buffer, frag_source_length);

				ofilestring.assign(buffer, (std::string::size_type)frag_source_length);
				delete [] buffer;
			} else {
				throw FatalException(base::print("base::readFile : Não foi possivel abrir o arquivo '%s'.", ifilename.c_str()));
			}
		}
	}  // namespace base
}  // namespace cb

