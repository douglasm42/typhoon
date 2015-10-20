/* 
 * - Cumulonimbus - ☁
 * File: Listener.h
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
#include <cb/input/input.hpp>

#include <cb/input/Key.hpp>

#include <cb/math/math.hpp>

namespace cb {
	namespace input {
		class CbAPI KeyListener {
		public:
			virtual void onKeyPress(Key ikey)=0;
			virtual void onKeyRelease(Key ikey)=0;
			virtual void onKeyMove(Key ikey, float ivalue)=0;
		};

		class CbAPI CharListener {
		public:
			virtual void onChar(char32_t ichar)=0;
		};

		class CbAPI MouseListener {
		public:
			virtual void onButtonPress(Key ikey, int ix, int iy)=0;
			virtual void onButtonRelease(Key ikey, int ix, int iy)=0;
			virtual void onMouseMove(int ix, int iy)=0;
			virtual void onWheelMove(float iv, float ih)=0;
		};

		class CbAPI WindowListener {
		public:
			virtual void onResize(uint32 iwidth, uint32 iheight)=0;
			virtual void onActivate()=0;
			virtual void onDeactivate()=0;
			virtual void onClose()=0;
		};

		class CbAPI QuitListener {
		public:
			virtual void onQuit()=0;
		};
	}  // namespace input
}  // namespace cb
