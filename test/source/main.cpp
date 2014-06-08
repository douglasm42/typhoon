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
#include <base/Entry.h>

#include <video/Window.h>
#include <graphic/GLContext.h>
#include <input/EventLoop.h>
#include <input/Event.h>

#include <data/File.h>
#include <data/Bitmap.h>

#include <iostream>
using namespace std;

using namespace cb;

int cbEntry(int argc, char **argv) {
	base::log.init("log.txt", "test.base");

	data::file::init(argv[0]);
	data::file::mount("./", "");

	video::Window win(base::utf16("Testando!"), 100, 100, 500, 500, false, false, true);

	graphic::GLContext context(win, graphic::Version::v30);

	win.show();

	data::iFile curfile;

	curfile.open("cursor_hand_point.png");
	if(curfile.isOpen()) {
		data::ubBitmapRGBA curimg(curfile);
		win.cursor().add("hand.point", curimg, 3, 0);
	} else {
		base::log.nothing("Não abriu!");
	}

	curfile.open("cursor_hand_point_click.png");
	if(curfile.isOpen()) {
		data::ubBitmapRGBA curimg(curfile);
		win.cursor().add("hand.click", curimg, 3, 0);
	} else {
		base::log.nothing("Não abriu!");
	}

	curfile.open("cumulonimbus_icon.png");
	if(curfile.isOpen()) {
		data::ubBitmapRGBA curimg(curfile);
		win.icon(curimg);
	} else {
		base::log.nothing("Não abriu!");
	}

	win.cursor().hold(true);

	win.cursor().select("hand.point");
	base::log.nothing("Iniciando loop!");

	while(!win.empty() && input::EventLoop::update()) {
		context.swap();

		while(!win.events().empty()) {
			input::Event e(win.events().next());
			if(e == input::EventType::KeyPress || e == input::EventType::KeyRelease || e == input::EventType::ButtonPress || e == input::EventType::ButtonRelease) {
				base::log.nothing("%s", e.str().c_str());
			}

			if(e == input::EventType::KeyMove) {
				base::log.nothing("%s", e.str().c_str());
			}

			if(e == input::EventType::KeyPress && e.key.k == input::KBEsc) {
				input::EventLoop::postQuit();
			}
		}
	}

	return EXIT_SUCCESS;
}
