/* 
 * - Cumulonimbus - ☁
 * File: EventQueue.h
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
#pragma once

#include <input/input.h>

#include <input/Event.h>
#include <queue>

#define CbEventQueueMaxSize 32

namespace cb {
	namespace input {
		class CbAPI EventQueue {
		private:
			Event _event_queue[CbEventQueueMaxSize];
			size_t _size;
			size_t _front;
			size_t _back;

			std::queue<Event> _aux_event_queue;

			void push(Event &e);
			Event pop();

		public:
			EventQueue();
			~EventQueue();

			bool empty();

			Event next();

			void onKeyPress(KeyCode ikey_listener);
			void onKeyRelease(KeyCode ikey_listener);
			void onKeyMove(KeyCode ikey_listener, float ivalue);

			void onChar(base::lchar_t ichar);

			void onButtonPress(KeyCode ikey, int ix, int iy);
			void onButtonRelease(KeyCode ikey, int ix, int iy);
			void onMouseMove(int ix, int iy);
			void onWheelMove(float iv, float ih);

			void onResize(size_t iwidth, size_t iheight);
			void onActivate();
			void onDeactivate();
			void onClose();

			void onQuit();
		};

		inline EventQueue::EventQueue() :_size(0), _front(0), _back(0) {
		}

		inline EventQueue::~EventQueue() {
		}

		inline bool EventQueue::empty() {
			return !_size;
		}

		inline Event EventQueue::next() {
			return pop();
		}

		inline void EventQueue::onKeyPress(KeyCode ikey) {
			push(Event(EventType::KeyPress, ikey));
		}

		inline void EventQueue::onKeyRelease(KeyCode ikey) {
			push(Event(EventType::KeyRelease, ikey));
		}

		inline void EventQueue::onKeyMove(KeyCode ikey, float ivalue) {
			push(Event(EventType::KeyMove, ikey, ivalue));
		}

		inline void EventQueue::onChar(base::lchar_t ichar) {
			push(Event(EventType::Char, ichar));
		}

		inline void EventQueue::onButtonPress(KeyCode ikey, int ix, int iy) {
			push(Event(EventType::ButtonPress, ikey, ix, iy));
		}

		inline void EventQueue::onButtonRelease(KeyCode ikey, int ix, int iy) {
			push(Event(EventType::ButtonRelease, ikey, ix, iy));
		}

		inline void EventQueue::onMouseMove(int ix, int iy) {
			push(Event(EventType::MouseMove, ix, iy));
		}

		inline void EventQueue::onWheelMove(float iv, float ih) {
			push(Event(EventType::WheelMove, iv, ih));
		}

		inline void EventQueue::onResize(size_t iwidth, size_t iheight) {
			push(Event(EventType::Resize, iwidth, iheight));
		}

		inline void EventQueue::onActivate() {
			push(Event(EventType::Activate));
		}

		inline void EventQueue::onDeactivate() {
			push(Event(EventType::Deactivate));
		}

		inline void EventQueue::onClose() {
			push(Event(EventType::Close));
		}

		inline void EventQueue::onQuit() {
			push(Event(EventType::Quit));
		}
	}  // namespace input
}  // namespace cb
