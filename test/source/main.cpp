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
#include <video/GLContext.h>
#include <input/EventLoop.h>
#include <input/EventListener.h>

#include <data/File.h>
#include <data/Bitmap.h>

using namespace cb;

class EventListener : public input::KeyListener, public input::MouseListener {
public:
	virtual void onKeyPress(input::KeyCode ikey) {
		base::log.nothing("Key press: %s", input::keyname(ikey).c_str());
	}
	virtual void onKeyRelease(input::KeyCode ikey) {
		base::log.nothing("Key release: %s", input::keyname(ikey).c_str());
	}
	virtual void onKeyMove(input::KeyCode ikey, float ivalue) {
	}

	virtual void onChar(base::lchar_t ichar) {
	}

	virtual void onButtonPress(input::KeyCode ikey, int ix, int iy) {
		base::log.nothing("Button press: %s in %d:%d", input::keyname(ikey).c_str(), ix, iy);
	}
	virtual void onButtonRelease(input::KeyCode ikey, int ix, int iy) {
		base::log.nothing("Button release: %s in %d:%d", input::keyname(ikey).c_str(), ix, iy);
	}
	virtual void onMove(int ixabs, int iyabs, int ixrel, int iyrel) {
	}
	virtual void onWheel(int iz) {
		base::log.nothing("Mouse wheel move: %d", iz);
	}
};

int cbEntry(int argc, char **argv) {
	base::log.init("log.base.txt", "test.base");

	data::file::init(argv[0]);
	data::file::mount("./", "");

	base::log.nothing("Criando janela!");
	video::Window win(base::wstring(L"Testando!"), 100, 100, 500, 500, false, false, true);

	base::log.nothing("Criando contexto opengl!");
	video::GLContext glcontext(win);
	base::log.nothing("Ligando os dois!");

	base::log.nothing("Ligando os dois!");
	win.eventHub().bind(&glcontext);

	base::log.nothing("Mostrando janela!");
	win.show();

	EventListener ev;
	win.eventHub().bind((input::KeyListener *)&ev);
	win.eventHub().bind((input::MouseListener *)&ev);

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

	curfile.open("cursor_hand_open.png");
	if(curfile.isOpen()) {
		data::ubBitmapRGBA curimg(curfile);
		win.cursor().add("hand.open", curimg, 4, 3);
	} else {
		base::log.nothing("Não abriu!");
	}

	curfile.open("cursor_hand_closed.png");
	if(curfile.isOpen()) {
		data::ubBitmapRGBA curimg(curfile);
		win.cursor().add("hand.closed", curimg, 3, 0);
	} else {
		base::log.nothing("Não abriu!");
	}

	win.cursor().select("hand.point");
	base::log.nothing("Iniciando loop!");
	while(!win.empty() && input::EventLoop::update()) {
		glcontext.swap();
	}

	return EXIT_SUCCESS;
}
