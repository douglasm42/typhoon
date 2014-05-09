/*
 * data.cpp
 *
 *  Created on: May 9, 2014
 *      Author: douglas
 */

#include <base/Log.h>
#include <base/Exception.h>

using namespace cb;

int cbMain(int argc, char **argv) {
	base::log.init("log.data.txt", "test.data", true, true, true);

	base::log.info("Testando o modulo data!");
	return EXIT_SUCCESS;
}
CBMAIN
