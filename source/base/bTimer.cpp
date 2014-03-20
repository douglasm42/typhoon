/*
 * bTimer.cpp
 *
 *  Created on: 19/12/2012
 *      Author: Douglas M. Freitas
 * 
 *   Copyright: Staff 42 © 2013
 */

#include <base/bTimer.h>

#include <boost/chrono.hpp>
#include <boost/thread.hpp>

#include <base/bLog.h>

namespace cb {
	namespace base {
		typedef boost::chrono::system_clock::time_point TimePoint;
		KinKey(TimerTimePoint, TimePoint);

		Timer::Timer() {
			_before << new TimePoint();
			update();
		}
		Timer::~Timer() {
			kin::erase(_before);
		}

		void Timer::sleep(float iseconds) {
			log.nothing("iseconds: %f", iseconds);
			boost::this_thread::sleep_for(boost::chrono::microseconds((int)(iseconds*1000000)));
			log.nothing("end");
		}

		void Timer::update() {
			TimePoint now = boost::chrono::system_clock::now();
			TimePoint &before = *_before;
			boost::chrono::duration<float> sec = now - before;

			_delta = sec.count();
			before = now;
		}
	}  // namespace base
}  // namespace cb
