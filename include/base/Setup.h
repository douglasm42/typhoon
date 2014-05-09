/*
 * bSetup.h
 *
 *  Created on: 13/12/2012
 *      Author: Douglas M. Freitas
 * 
 *   Copyright: Staff 42 © 2013
 */
#pragma once

#if defined _WIN32
#	define CbWindows
#else
#	define CbLinux
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
#	else
#		define CbAPI CUMULONIMBUS_DLL_IMPORT
#	endif
#else
#	define CbAPI
#endif


#ifdef CbLinux
#define CBMAIN\
		int main(int argc, char **argv) {\
			try {\
				return cbMain(argc, argv);\
			} catch (tokurei::LogUninitialized &e) {\
				base::log.show(base::Log::Error, base::format(\
						"This is a fatal error and was caused by a STUPID programmer.\n"\
						"We will fix this soon and scold him.\n\n"\
						"Error message:\n%s", e.what()));\
				return EXIT_FAILURE;\
			} catch (tokurei::Log &e) {\
				base::log.show(base::Log::Error, base::format("Fatal error:\n%s", e.what()));\
				return EXIT_FAILURE;\
			} catch (std::exception &e) {\
				base::log.error("Fatal Error: %s", e.what());\
				return EXIT_FAILURE;\
			}\
			return EXIT_FAILURE;\
		}
#endif




