/* 
 * - Cumulonimbus - ☁
 * File: main.cpp
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
#include <base/Log.h>
#include <base/Exception.h>

#include <base/Entry.h>

using namespace cb;

int cbEntry(int argc, char **argv) {
	//base::log.init("log.base.txt", "test.base", true, true, true);

	base::log.info("Testing module: base");
	base::log.error("Error test!");
	base::log.warning("Warning test!");
	base::log.info("Info test!");

	return EXIT_SUCCESS;
}
