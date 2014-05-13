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

class EventListener : public input::KeyListener {
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
	win.eventHub().bind(&ev);

	data::iFile curfile("cursor.png");
	if(curfile.isOpen()) {
		data::ubBitmapRGBA curimg(curfile);
		win.cursor().add("cursor", curimg, 0, 0);
		win.cursor().select("cursor");
	} else {
		base::log.nothing("Não abriu!");
	}

	base::log.nothing("Iniciando loop!");
	while(!win.empty() && input::EventLoop::update()) {
		glcontext.swap();
	}

	return EXIT_SUCCESS;
}
