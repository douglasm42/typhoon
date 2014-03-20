/*
 * bDate.cpp
 *
 *  Created on: 19/12/2012
 *      Author: Douglas M. Freitas
 * 
 *   Copyright: Staff 42 © 2013
 */

#include <base/bDate.h>

#define BOLT_BASE_DATE_BUFFER_CHUNK_SIZE 1024

#include <boost/thread.hpp>

namespace cb {
	namespace base {
		Date::Date() {
			getTimeInfo(&_timeinfo);
		}

		Date::Date(const Date &idate) {
			_timeinfo = idate._timeinfo;
		}

#if defined __MINGW32__ || __GNUC__
		boost::mutex guard_getTimeInfo;
#endif
		void Date::getTimeInfo(struct tm *itimeinfo) {
			time_t rawtime;
			time(&rawtime);
#if defined __MINGW32__ || __GNUC__
			boost::lock_guard<boost::mutex> lock(guard_getTimeInfo);
			struct tm *timeinfo = localtime(&rawtime);
			memcpy(itimeinfo, timeinfo, sizeof(struct tm));
#else
			localtime_s(itimeinfo, &rawtime);
#endif
		}

		string Date::str(const char *iformat) {
			string strdate;
			for(size_t n = BOLT_BASE_DATE_BUFFER_CHUNK_SIZE ; strdate.empty() ; n+=BOLT_BASE_DATE_BUFFER_CHUNK_SIZE) {
				char *buffer = new char[n];

				if(strftime(buffer, n, iformat, &_timeinfo)) {
					strdate = buffer;
				}

				delete [] buffer;
			}
			return strdate;
		}

		Date &Date::operator=(const Date &idate) {
			_timeinfo = idate._timeinfo;
			return *this;
		}
	}  // namespace base
}  // namespace cb