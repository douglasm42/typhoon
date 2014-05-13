/* 
 * - Cumulonimbus - ☁
 * File: WindowProc.h
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

#include <base/Setup.h>
#ifdef CbWindows

#include <input/input.h>

#include <video/win32/Windows.h>

namespace cb {
	namespace input {
		LRESULT CALLBACK WindowProc(HWND iwindow_handler, UINT imessage, WPARAM iwparam, LPARAM ilparam);
	}  // namespace input
}  // namespace cb

#endif
