/*
 * bTimer.cpp
 *
 *  Created on: 19/12/2012
 *      Author: Douglas M. Freitas
 * 
 *   Copyright: Staff 42 © 2013
 */

#include <base/bTimer.h>

#include <chrono>
#include <thread>

#include <base/bLog.h>

namespace cb {
	namespace base {
		typedef std::chrono::system_clock::time_point TimePoint;
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
			std::this_thread::sleep_for(std::chrono::microseconds((int)(iseconds*1000000)));
			log.nothing("end");
		}

		void Timer::update() {
			TimePoint now = std::chrono::system_clock::now();
			TimePoint &before = *_before;
			std::chrono::duration<float> sec = now - before;

			_delta = sec.count();
			before = now;
		}
	}  // namespace base
}  // namespace cb
