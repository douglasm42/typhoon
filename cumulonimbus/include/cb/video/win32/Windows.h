/* 
 * - Cumulonimbus - ☁
 * File: Windows.h
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

#include <cb/video/video.h>

#ifdef __MINGW32__
	#ifndef WINVER
		#define WINVER 0x0502
	#endif
	#include <Windows.h>
	#include <windowsx.h>

	#ifndef MAPVK_VK_TO_VSC_EX
		#define MAPVK_VK_TO_VSC_EX 4
	#endif

	#ifndef MAPVK_VSC_TO_VK_EX
		#define MAPVK_VSC_TO_VK_EX 3
	#endif
#else
	#include <Windows.h>
	#include <windowsx.h>
#endif
