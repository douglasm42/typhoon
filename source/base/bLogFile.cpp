/*
 * bLogFile.cpp
 *
 *  Created on: 19/12/2012
 *      Author: Douglas M. Freitas
 * 
 *   Copyright: Staff 42 © 2013
 */

#include <base/LogFile.h>

#include <base/Exception.h>

#include <fstream>
#include <iostream>
#include <cwchar>

namespace cb {
	namespace base {
		LogFile::LogFile(string ifilename, string ititle, Date idate)
		:_filename(ifilename) {
			std::ofstream out(this->_filename.c_str(), std::ios::trunc);
			if(out.is_open()) {
				ititle = idate.str("%d/%m/%Y %H:%M:%S - Log: ") + ititle + " ";

				string title = "-- -----------------------------------------------------------------------------";
				title.replace(3, ititle.size(), ititle);

				out << "--------------------------------------------------------------------------------" << std::endl;
				out << title << std::endl;
				out << "--------------------------------------------------------------------------------" << std::endl;
				out << std::endl;

				std::cout << "--------------------------------------------------------------------------------" << std::endl;
				std::cout << title << std::endl;
				std::cout << "--------------------------------------------------------------------------------" << std::endl;
				std::cout << std::endl;

			} else {
				ThrowDet(tokurei::LogCreateFileError, "Filename: " + this->_filename);
			}
			out.close();
		}

		LogFile::~LogFile() {
			std::ofstream out(this->_filename.c_str(), std::ios::app);
			if(out.is_open()) {

				out << std::endl;
				out << "--------------------------------------------------------------------------------" << std::endl;

				std::cout << std::endl;
				std::cout << "--------------------------------------------------------------------------------" << std::endl;

			} else {
				ThrowDet(tokurei::LogOpenFileError, "Filename: " + this->_filename);
			}
			out.close();
		}

		void LogFile::write(Log::Type itype, Date idate, string iline) {
			std::ofstream out(this->_filename.c_str(), std::ios::app);
			if(out.is_open()) {

				string buffer = idate.str("%H:%M:%S");

				switch (itype) {
					case Log::Error:
						out			<< buffer << " - Error:   " << iline << std::endl;
						std::cout	<< buffer << " - Error:   " << iline << std::endl;
						break;
					case Log::Warning:
						out			<< buffer << " - Warning: " << iline << std::endl;
						std::cout	<< buffer << " - Warning: " << iline << std::endl;
						break;
					case Log::Info:
						out			<< buffer << " - Info:    " << iline << std::endl;
						std::cout	<< buffer << " - Info:    " << iline << std::endl;
						break;
					case Log::Nothing:
						out			<< buffer << " - Nothing: " << iline << std::endl;
						std::cout	<< buffer << " - Nothing: " << iline << std::endl;
						break;
					default:
						break;
				}

			} else {
				ThrowDet(tokurei::LogOpenFileError, "Filename: " + this->_filename);
			}
			out.close();
		}
	}  // namespace base
}  // namespace cb


