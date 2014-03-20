/*
 * bLog.cpp
 *
 *  Created on: 19/12/2012
 *      Author: Douglas M. Freitas
 * 
 *   Copyright: Staff 42 © 2013
 */

#include <base/bLog.h>
#include <base/bLogFile.h>

#include <base/bPrint.h>

#include <boost/thread.hpp>

#include <base/bWindows.h>

namespace cb {
	namespace base {
		Log log;

		Log::Log()
		:_file(NULL), _error(false), _warning(false), _info(false) {
		}

		Log::~Log() {
			if(_file) {
				delete _file;
			}
		}

		boost::mutex log_write_guard;
		void Log::write(Type itype, Date idate, string imsg) {
			boost::lock_guard<boost::mutex> lock(log_write_guard);
			if(_file) {
				_file->write(itype, idate, imsg);
			} else {
				show(Error, "O sistema de LOG deve ser inicializado antes de ser utilizado.");
			}
		}

		void Log::init(string ifilename, string ititle) {
			_file = NULL;
			_error = true;
			_warning = false;
			_info = false;

			_file = new LogFile(ifilename, ititle, Date());
		}

		void Log::show(Type itype, string imsg) {
			switch(itype) {
				case Error:
					//MessageBox(NULL, sysEncode(imsg).c_str(), sysEncode("Erro").c_str(), MB_OK | MB_ICONERROR | MB_SYSTEMMODAL | MB_TOPMOST);
					break;
				case Warning:
					//MessageBox(NULL, sysEncode(imsg).c_str(), sysEncode("Aviso").c_str(), MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL | MB_TOPMOST);
					break;
				case Info:
					//MessageBox(NULL, sysEncode(imsg).c_str(), sysEncode("Informação").c_str(), MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL | MB_TOPMOST);
					break;
				default:
					break;
			}
		}

		void Log::log(Type itype, string iformat, ...) {
			Date date;
			string msg;
			PRINT(msg, iformat);

			write(itype, date, msg);
			if((itype == Error && _error) || (itype == Warning && _warning) || (itype == Info && _info)) {
				show(itype, msg);
			}
		}

		void Log::error(string iformat, ...) {
			Date date;
			string msg;
			PRINT(msg, iformat);

			write(Error, date, msg);
			if(_error) {
				show(Error, msg);
			}
		}

		void Log::warning(string iformat, ...) {
			Date date;
			string msg;
			PRINT(msg, iformat);

			write(Warning, date, msg);
			if(_warning) {
				show(Warning, msg);
			}
		}

		void Log::info(string iformat, ...) {
			Date date;
			string msg;
			PRINT(msg, iformat);

			write(Info, date, msg);
			if(_info) {
				show(Info, msg);
			}
		}

		void Log::nothing(string iformat, ...) {
			Date date;
			string msg;
			PRINT(msg, iformat);

			write(Nothing, date, msg);
		}

		void Log::operator()(Type itype, string iformat, ...) {
			Date date;
			string msg;
			PRINT(msg, iformat);

			write(itype, date, msg);
			if((itype == Error && _error) || (itype == Warning && _warning) || (itype == Info && _info)) {
				show(itype, msg);
			}
		}
	}  // namespace base
}  // namespace cb
