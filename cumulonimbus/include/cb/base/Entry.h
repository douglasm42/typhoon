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

#include <cb/base/base.h>

#include <cb/base/Exception.h>
#include <cb/base/Log.h>

int cbEntry(int argc, char **argv);

#ifdef CbLinux
int main(int argc, char **argv) {
	try {
		return cbEntry(argc, argv);
	} catch (cb::tokurei::LogUninitialized &e) {
		cb::base::log.show(cb::base::Log::Error, cb::base::format(
				"This is a fatal error and was caused by a STUPID programmer.\n"
				"We will fix this soon and scold him.\n\n"
				"Error message:\n%s", e.what()));
		return EXIT_FAILURE;
	} catch (cb::tokurei::Log &e) {
		cb::base::log.show(cb::base::Log::Error, cb::base::format("Fatal error:\n%s", e.what()));
		return EXIT_FAILURE;
	} catch (std::exception &e) {
		cb::base::log.error("Fatal Error: %s", e.what());
		return EXIT_FAILURE;
	}\
	return EXIT_FAILURE;
}
#elif defined CbWindows

#ifdef __MINGW32__
	#ifndef WINVER
		#define WINVER 0x0502
	#endif
	#include <Windows.h>
#else
	#include <Windows.h>
#endif

#include <cstdio>
#include <io.h>
#include <fcntl.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    AllocConsole();

    HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
    int hCrt = _open_osfhandle((long) handle_out, _O_TEXT);
    FILE* hf_out = _fdopen(hCrt, "w");
    setvbuf(hf_out, NULL, _IONBF, 1);
    *stdout = *hf_out;

    HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
    hCrt = _open_osfhandle((long) handle_in, _O_TEXT);
    FILE* hf_in = _fdopen(hCrt, "r");
    setvbuf(hf_in, NULL, _IONBF, 128);
    *stdin = *hf_in;

	try {
		int argc;
		wchar_t **wargv;
		char **argv;

		wargv = CommandLineToArgvW(GetCommandLineW(), &argc);

		cb::base::string *argvstr;
		argv = new char*[argc];
		argvstr = new cb::base::string[argc];
		for(int i=0 ; i<argc ; ++i) {
			argvstr[i] = cb::base::utf8(cb::base::string16((char16_t *)wargv[i]));
			argv[i] = new char[argvstr[i].size()+1];
			strcpy(argv[i], argvstr[i].c_str());
		}

		delete [] argvstr;
		argvstr = nullptr;

		int result =  cbEntry(argc, argv);
		for(int i=0 ; i<argc ; ++i) {
			delete [] argv[i];
		}
		delete [] argv;

		return result;
	} catch (cb::tokurei::LogUninitialized &e) {
		cb::base::log.show(cb::base::Log::Error, cb::base::format(
				"This is a fatal error and was caused by a STUPID programmer.\n"
				"We will fix this soon and scold him.\n\n"
				"Error message:\n%s", e.what()));
		return EXIT_FAILURE;
	} catch (cb::tokurei::Log &e) {
		cb::base::log.show(cb::base::Log::Error, cb::base::format("Fatal error:\n%s", e.what()));
		return EXIT_FAILURE;
	} catch (std::exception &e) {
		cb::base::log.error("Fatal Error: %s", e.what());
		return EXIT_FAILURE;
	}\
	return EXIT_FAILURE;
}
#endif
