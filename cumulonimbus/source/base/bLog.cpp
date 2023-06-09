/* 
 * - Cumulonimbus - ☁
 * File: bLog.cpp
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
#include <cb/base/Log.h>
#include <cb/base/LogFile.h>

#include <cb/base/FormatMacro.h>
#include <cb/base/Exception.h>

#include <cb/video/Message.h>

#include <iostream>

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

		void Log::write(Type itype, Date idate, string imsg) {
			std::lock_guard<std::mutex> lock(_log_write_guard);
			if(_file) {
				_file->write(itype, idate, imsg);
			} else {
				Throw(tokurei::LogUninitialized);
			}
		}

		void Log::init(string ifilename, string ititle, bool ierror, bool iwarning, bool iinfo) {
			_file = NULL;
			_error = ierror;
			_warning = iwarning;
			_info = iinfo;

			_file = new LogFile(ifilename, ititle, Date());
		}

		void Log::show(Type itype, string imsg) {
			switch(itype) {
				case Error:
					video::Message(video::msg::Error, imsg);
					break;
				case Warning:
					video::Message(video::msg::Warning, imsg);
					break;
				case Info:
					video::Message(video::msg::Info, imsg);
					break;
				default:
					break;
			}
		}

		void Log::log(Type itype, string iformat, ...) {
			Date date;
			string msg;
			CUMULONIMBUS_FORMAT(msg, iformat);

			write(itype, date, msg);
			if((itype == Error && _error) || (itype == Warning && _warning) || (itype == Info && _info)) {
				show(itype, msg);
			}
		}

		void Log::error(string iformat, ...) {
			Date date;
			string msg;
			CUMULONIMBUS_FORMAT(msg, iformat);

			write(Error, date, msg);
			if(_error) {
				show(Error, msg);
			}
		}

		void Log::warning(string iformat, ...) {
			Date date;
			string msg;
			CUMULONIMBUS_FORMAT(msg, iformat);

			write(Warning, date, msg);
			if(_warning) {
				show(Warning, msg);
			}
		}

		void Log::info(string iformat, ...) {
			Date date;
			string msg;
			CUMULONIMBUS_FORMAT(msg, iformat);

			write(Info, date, msg);
			if(_info) {
				show(Info, msg);
			}
		}

		void Log::nothing(string iformat, ...) {
			Date date;
			string msg;
			CUMULONIMBUS_FORMAT(msg, iformat);

			write(Nothing, date, msg);
		}

		void Log::operator()(Type itype, string iformat, ...) {
			Date date;
			string msg;
			CUMULONIMBUS_FORMAT(msg, iformat);

			write(itype, date, msg);
			if((itype == Error && _error) || (itype == Warning && _warning) || (itype == Info && _info)) {
				show(itype, msg);
			}
		}
	}  // namespace base
}  // namespace cb
