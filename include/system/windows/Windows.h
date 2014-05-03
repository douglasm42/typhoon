/*
 * swWindows.h
 *
 *  Created on: 28/10/2013
 *      Author: Douglas
 */

#pragma once

#ifdef _WIN32
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
#endif
