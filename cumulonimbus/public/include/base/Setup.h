/* 
 * - Cumulonimbus - ☁
 * File: Setup.h
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

#if defined _WIN32
#	define CbWindows
#else
#	define CbLinux
#endif

#if defined _DEBUG
#	define CbDebug
#endif

#ifndef __func__
#define __func__ __FUNCTION__
#endif

#ifndef thread_local
	#ifdef _MSC_VER
		#define _thread_local __declspec(thread)
	#elif defined __MINGW32__
		#define _thread_local __thread
	#else
		#define _thread_local __thread
	#endif
#else
	#define _thread_local thread_local
#endif

#if defined _WIN32
#	define CUMULONIMBUS_DLL_IMPORT __declspec(dllimport)
#	define CUMULONIMBUS_DLL_EXPORT __declspec(dllexport)
#	define CUMULONIMBUS_DLL_LOCAL
#else
#	if __GNUC__ >= 4
#		define CUMULONIMBUS_DLL_IMPORT __attribute__ ((visibility ("default")))
#		define CUMULONIMBUS_DLL_EXPORT __attribute__ ((visibility ("default")))
#		define CUMULONIMBUS_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#	else
#		define CUMULONIMBUS_DLL_IMPORT
#		define CUMULONIMBUS_DLL_EXPORT
#		define CUMULONIMBUS_DLL_LOCAL
#	endif
#endif

#ifndef CUMULONIMBUS_STATIC
#	ifdef CUMULONIMBUS_EXPORTS
#		define CbAPI CUMULONIMBUS_DLL_EXPORT
#		define CbTemplate
#	else
#		define CbAPI CUMULONIMBUS_DLL_IMPORT
#		define CbTemplate extern
#	endif
#else
#	define CbAPI
#	define CbTemplate
#endif
