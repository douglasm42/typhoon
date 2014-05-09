/*
 * video.cpp
 *
 *  Created on: May 9, 2014
 *      Author: douglas
 */

#include <base/Log.h>
#include <base/Exception.h>

using namespace cb;

int cbMain(int argc, char **argv) {
	base::log.init("log.video.txt", "test.video", true, true, true);

	base::log.info("Testando o modulo video!");
	return EXIT_SUCCESS;
}
CBMAIN



