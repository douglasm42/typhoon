/* 
 * - Cumulonimbus - ☁
 * File: iEventQueue.cpp
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
#include <input/EventQueue.h>

namespace cb {
	namespace input {
		void EventQueue::push(Event &e) {
			if(_size < CbEventQueueMaxSize) {
				_event_queue[_back] = e;
				_back = (_back + 1) % CbEventQueueMaxSize;
			} else {
				_aux_event_queue.push(e);
			}
			_size++;
		}

		Event EventQueue::pop() {
			if(!empty()) {
				_size--;
				if(_aux_event_queue.empty()) {
					Event e(_event_queue[_front]);
					_front = (_front + 1) % CbEventQueueMaxSize;
					return e;
				} else {
					Event e(_aux_event_queue.front());
					_aux_event_queue.pop();
					return e;
				}
			} else {
				return Event(ev::Void);
			}
		}
	}  // namespace input
}  // namespace cb

