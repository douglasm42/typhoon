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

#include <input/KeyListener.h>
#include <input/CharListener.h>
#include <input/MouseListener.h>
#include <input/WindowListener.h>
#include <input/QuitListener.h>

#include <data/File.h>
#include <data/Bitmap.h>
#include <data/Mesh.h>

#include <graphic/GL.h>
#include <graphic/Texture.h>
#include <graphic/Shader.h>
#include <graphic/Program.h>
#include <graphic/FrameBuffer.h>

#include <iostream>
using namespace std;

using namespace cb;

class Listener : public input::KeyListener, public input::CharListener, public input::MouseListener, public input::WindowListener, public input::QuitListener {
public:
	bool close;
	bool quit;

	bool maximize;
	bool minimize;
	bool border;

	size_t width;
	size_t height;

	Listener() {
		close = false;
		maximize = false;
		minimize = false;
		border = false;
		quit = false;
		width = 0;
		height = 0;
	}
	virtual ~Listener() {}

	virtual void onKeyPress(input::Key ikey) {
		if(ikey == input::Key::KBF1) {
			minimize = true;
		} else if(ikey == input::Key::KBF2) {
			maximize = true;
		} else if(ikey == input::Key::KBF3) {
			border = true;
		} else if(ikey == input::Key::KBEsc) {
			quit = true;
			input::EventLoop::postQuit();
		}

		base::log.nothing("Press: %s", ikey.str().c_str());
	}
	virtual void onKeyRelease(input::Key ikey) {
		base::log.nothing("Release: %s", ikey.str().c_str());
	}
	virtual void onKeyMove(input::Key ikey, float ivalue) {
		if(ikey.type() == input::Key::XController) {
			base::log.nothing("Move: %s - %f", ikey.str().c_str(), ivalue);
		}
	}

	virtual void onChar(char32_t ichar) {}

	virtual void onButtonPress(input::Key ikey, int ix, int iy) {}
	virtual void onButtonRelease(input::Key ikey, int ix, int iy) {}
	virtual void onMouseMove(int ix, int iy) {}
	virtual void onWheelMove(float iv, float ih) {}

	virtual void onResize(size_t iwidth, size_t iheight) {
		width = iwidth;
		height = iheight;
		base::log.nothing("size: %dx%d", width, height);
	}
	virtual void onActivate() {}
	virtual void onDeactivate() {}
	virtual void onClose() {
		close = true;
		input::EventLoop::postQuit();
	}

	virtual void onQuit() {
		quit = true;
	}
};

int cbEntry(int argc, char **argv) {
	base::log.init("log.txt", "test.base");

	graphic::GL gl;

	video::Window win(base::utf16("Testando!"), 100, 100, 500, 500, false, false, video::Border::Empty);

	graphic::GLContext context(win, graphic::Version::v21);

	win.show();

	data::File curfile;

	curfile.load("cursor_hand_point.png");
	{
		data::ubBitmapRGBA curimg(curfile);
		win.cursor().add("hand.point", curimg, 3, 0);
	}

	curfile.load("cursor_hand_point_click.png");
	{
		data::ubBitmapRGBA curimg(curfile);
		win.cursor().add("hand.click", curimg, 3, 0);
	}

	curfile.load("cumulonimbus_icon.png");
	{
		data::ubBitmapRGBA curimg(curfile);
		win.icon(curimg);
	}

	context.activate();
	graphic::Texture texuvmap(graphic::tex::Target::Tex2D, graphic::tex::Format::RGBA8);
	curfile.load("gizmos/grid.png");
	{
		data::Bitmap uvmap(curfile, data::bmp::Format::RGBA, data::bmp::Type::UByte);
		texuvmap.image(uvmap);
	}

	graphic::Texture texgrid(graphic::tex::Target::Tex2D, graphic::tex::Format::RGBA8);
	{
		data::Bitmap grid;
		curfile.load("gizmos/grid-00.png");
		grid.load(curfile, data::bmp::Format::RGBA, data::bmp::Type::UByte);
		texgrid.image(grid);

		curfile.load("gizmos/grid-01.png");
		grid.load(curfile, data::bmp::Format::RGBA, data::bmp::Type::UByte);
		texgrid.image(grid);

		curfile.load("gizmos/grid-02.png");
		grid.load(curfile, data::bmp::Format::RGBA, data::bmp::Type::UByte);
		texgrid.image(grid);

		curfile.load("gizmos/grid-03.png");
		grid.load(curfile, data::bmp::Format::RGBA, data::bmp::Type::UByte);
		texgrid.image(grid);

		curfile.load("gizmos/grid-04.png");
		grid.load(curfile, data::bmp::Format::RGBA, data::bmp::Type::UByte);
		texgrid.image(grid);

		curfile.load("gizmos/grid-05.png");
		grid.load(curfile, data::bmp::Format::RGBA, data::bmp::Type::UByte);
		texgrid.image(grid);

		curfile.load("gizmos/grid-06.png");
		grid.load(curfile, data::bmp::Format::RGBA, data::bmp::Type::UByte);
		texgrid.image(grid);

		curfile.load("gizmos/grid-07.png");
		grid.load(curfile, data::bmp::Format::RGBA, data::bmp::Type::UByte);
		texgrid.image(grid);

		texgrid.magFilter(graphic::tex::MagFilter::Linear);
		texgrid.minFilter(graphic::tex::MinFilter::LinearMipMapLinear);
	}

	data::Mesh gridmesh(data::Mesh::Format(3,2,0,3,0));
	gridmesh.plane(100,100,100,100);
	graphic::VertexBuffer gridvb;
	gridvb.load(gridmesh);

	base::log.nothing("Aqui!");
	data::Bitmap cards[52];//(64, 32, 1, data::bmp::Format::RGB, data::bmp::Type::UByte)

	data::Bitmap *card = cards;
	for(size_t i=0 ; i<13 ; i++) {
		curfile.load(base::format("cards/spades_%d.png", i+1));
		card->load(curfile, data::bmp::Format::RGBA, data::bmp::Type::UByte);
		base::log.nothing("Card #%d", i);
		card++;
	}

	for(size_t i=0 ; i<13 ; i++) {
		curfile.load(base::format("cards/clubs_%d.png", i+1));
		card->load(curfile, data::bmp::Format::RGBA, data::bmp::Type::UByte);
		base::log.nothing("Card #%d", i + 13);
		card++;
	}

	for(size_t i=0 ; i<13 ; i++) {
		curfile.load(base::format("cards/hearts_%d.png", i+1));
		card->load(curfile, data::bmp::Format::RGBA, data::bmp::Type::UByte);
		base::log.nothing("Card #%d", i + 13*2);
		card++;
	}

	for(size_t i=0 ; i<13 ; i++) {
		curfile.load(base::format("cards/diamonds_%d.png", i+1));
		card->load(curfile, data::bmp::Format::RGBA, data::bmp::Type::UByte);
		base::log.nothing("Card #%d", i + 13*3);
		card++;
	}

	data::Bitmap back;
	curfile.load("cards/back.png");
	back.load(curfile, data::bmp::Format::RGBA, data::bmp::Type::UByte);

	base::log.nothing("Aqui2!");
	graphic::Texture cards_tex[52];//(graphic::tex::Target::Tex2D, graphic::tex::Format::RGB8);
	for(int i=0 ; i<52 ; i++) {
		cards_tex[i].init(graphic::tex::Target::Tex2D, graphic::tex::Format::RGBA8);
		cards_tex[i].blank(64,32,1);
		cards_tex[i].subImage(cards[i], 0, 0, 0);
		cards_tex[i].subImage(back, 0, 32, 0);
	}
	base::log.nothing("Aqui3!");

	win.cursor().select("hand.point");
	base::log.nothing("Iniciando loop!");

	gl.clearColor(graphic::color::sky1);

	data::Mesh mesh(data::Mesh::Format(3,2,0,3,0));
	data::Mesh::Vertex v;

	//Back
	v.pos    = vec4(-0.5f, 0.0f,-0.5f,0.0f);
	v.normal = vec3( 0.0f, 1.0f, 0.0f);
	v.tex    = vec4( 0.5f, 0.0f, 0.0f, 0.0f);
	mesh.quad(mesh.vertex(v));

	v.pos    = vec4( 0.5f, 0.0f,-0.5f,0.0f);
	v.normal = vec3( 0.0f, 1.0f, 0.0f);
	v.tex    = vec4( 1.0f, 0.0f, 0.0f, 0.0f);
	mesh.quad(mesh.vertex(v));

	v.pos    = vec4( 0.5f, 0.0f, 0.5f,0.0f);
	v.normal = vec3( 0.0f, 1.0f, 0.0f);
	v.tex    = vec4( 1.0f, 1.0f, 0.0f, 0.0f);
	mesh.quad(mesh.vertex(v));

	v.pos    = vec4(-0.5f, 0.0f, 0.5f,0.0f);
	v.normal = vec3( 0.0f, 1.0f, 0.0f);
	v.tex    = vec4( 0.5f, 1.0f, 0.0f, 0.0f);
	mesh.quad(mesh.vertex(v));

	//Face
	v.pos    = vec4(-0.5f, 0.0f, 0.5f,0.0f);
	v.normal = vec3( 0.0f, 1.0f, 0.0f);
	v.tex    = vec4( 0.5f, 1.0f, 0.0f, 0.0f);
	mesh.quad(mesh.vertex(v));

	v.pos    = vec4( 0.5f, 0.0f, 0.5f,0.0f);
	v.normal = vec3( 0.0f, 1.0f, 0.0f);
	v.tex    = vec4( 0.0f, 1.0f, 0.0f, 0.0f);
	mesh.quad(mesh.vertex(v));

	v.pos    = vec4( 0.5f, 0.0f,-0.5f,0.0f);
	v.normal = vec3( 0.0f, 1.0f, 0.0f);
	v.tex    = vec4( 0.0f, 0.0f, 0.0f, 0.0f);
	mesh.quad(mesh.vertex(v));

	v.pos    = vec4(-0.5f, 0.0f,-0.5f,0.0f);
	v.normal = vec3( 0.0f, 1.0f, 0.0f);
	v.tex    = vec4( 0.5f, 0.0f, 0.0f, 0.0f);
	mesh.quad(mesh.vertex(v));

	//mesh.plane(1.0f, 1.0f, 1.0f, 1.0f);
	//mesh.box(1.0f, 1.0f, 1.0f);
	//mesh.sphere(0.5f, 256, 256);
	//mesh.dome(10.0f, 256, 256, 1.0);

	graphic::VertexBuffer teste;
	teste.load(mesh);

	curfile.load("shaders/teste.vert");
	graphic::Shader vertex(curfile, graphic::Shader::Type::Vertex);

	curfile.load("shaders/teste.frag");
	graphic::Shader fragment(curfile, graphic::Shader::Type::Fragment);

	graphic::Program prog;
	prog.add(&vertex);
	prog.add(&fragment);
	prog.link();

	size_t w,h;

	vec4 clearcolor = graphic::color::sky1;

	int i = 0;

	Listener ltn;
	win.eventhub().bind((input::KeyListener*)&ltn);
	win.eventhub().bind((input::CharListener*)&ltn);
	win.eventhub().bind((input::MouseListener*)&ltn);
	win.eventhub().bind((input::WindowListener*)&ltn);
	win.eventhub().bind((input::QuitListener*)&ltn);

	base::log.nothing("size: %dx%d", ltn.width, ltn.height);
	ltn.width = win.placement().width();
	ltn.height = win.placement().height();

	while(!win.empty() && input::EventLoop::update()) {
		if(ltn.maximize) {
			if(win.placement().maximized()) {
				win.restore();
			} else {
				win.maximize();
			}
		}

		if(ltn.minimize) {
			win.minimize();
		}

		if(ltn.border) {
			video::Placement p = win.placement();
			if(p.border() == video::Border::Empty) {
				p.border(video::Border::System);
			} else if(p.border() == video::Border::System) {
				p.border(video::Border::Empty);
			}
			win.placement(p);
		}

		gl.viewport(0, 0, ltn.width, ltn.height);
		gl.clearColor(clearcolor);
		gl.clear(graphic::Clear::ColorDepth);

		cards_tex[i].bind();
		//texuvmap.bind();
		//texgrid.bind();
		gl.texSquare(teste, gridvb);

		context.swap();

		ltn.maximize = false;
		ltn.minimize = false;
		ltn.border = false;
	}

	return EXIT_SUCCESS;
}
