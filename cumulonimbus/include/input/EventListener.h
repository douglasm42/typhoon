/* 
 * - Cumulonimbus - ☁
 * File: EventListener.h
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

#include <input/KeyCode.h>

namespace cb {
	namespace input {
		class CbAPI UpdateListener {
		private:
			EventHub *_event_hub;

		public:
			UpdateListener() {_event_hub = nullptr;}
			virtual ~UpdateListener();

			virtual void onUpdateStart()=0;
			virtual void onUpdateEnd()=0;

			virtual void onQuit()=0;

			friend class CbAPI EventHub;
		};

		class CbAPI KeyListener {
		private:
			EventHub *_event_hub;

		public:
			KeyListener() {_event_hub = nullptr;}
			virtual ~KeyListener();

			virtual void onKeyPress(KeyCode ikey)=0;
			virtual void onKeyRelease(KeyCode ikey)=0;
			virtual void onKeyMove(KeyCode ikey, float ivalue)=0;

			virtual void onChar(base::lchar_t ichar)=0;

			friend class CbAPI EventHub;
		};

		class CbAPI WindowListener {
		private:
			EventHub *_event_hub;

		public:
			WindowListener() {_event_hub = nullptr;}
			virtual ~WindowListener();

			virtual void onResize(size_t iwidth, size_t iheight)=0;

			virtual void onActivate()=0;
			virtual void onDeactivate()=0;

			virtual void onCreate()=0;
			virtual void onDestroy()=0;

			friend class CbAPI EventHub;
		};
	}  // namespace video
}  // namespace cb
