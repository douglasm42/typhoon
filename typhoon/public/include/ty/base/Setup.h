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
#include <ty/base/base.h>

#include <cb/base/Setup.h>

#if defined _WIN32
#	define TyWindows
#else
#	define TyLinux
#endif

#if defined _DEBUG
#	define TyDebug
#endif

#if defined _WIN32
#	define TYPHOON_DLL_IMPORT __declspec(dllimport)
#	define TYPHOON_DLL_EXPORT __declspec(dllexport)
#	define TYPHOON_DLL_LOCAL
#else
#	if __GNUC__ >= 4
#		define TYPHOON_DLL_IMPORT __attribute__ ((visibility ("default")))
#		define TYPHOON_DLL_EXPORT __attribute__ ((visibility ("default")))
#		define TYPHOON_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#	else
#		define TYPHOON_DLL_IMPORT
#		define TYPHOON_DLL_EXPORT
#		define TYPHOON_DLL_LOCAL
#	endif
#endif

#ifndef TYPHOON_STATIC
#	ifdef TYPHOON_EXPORTS
#		define TyAPI TYPHOON_DLL_EXPORT
#		define TyTemplate
#	else
#		define TyAPI TYPHOON_DLL_IMPORT
#		define TyTemplate extern
#	endif
#else
#	define TyAPI
#	define TyTemplate
#endif
