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
#include <cb/base/Entry.hpp>

#include <cb/base/Timer.hpp>

#include <cb/video/Window.hpp>
#include <cb/graphic/GLContext.hpp>
#include <cb/input/EventLoop.hpp>

#include <cb/input/Listener.hpp>

#include <cb/data/Blob.hpp>
#include <cb/data/Bitmap.hpp>
#include <cb/data/Mesh.hpp>

#include <cb/graphic/GL.hpp>
#include <cb/graphic/tex/Texture.hpp>
#include <cb/graphic/tex/Texture2D.hpp>
#include <cb/graphic/Shader.hpp>
#include <cb/graphic/Program.hpp>
#include <cb/graphic/FrameBuffer.hpp>
#include <cb/graphic/PixelFormat.hpp>

#include <cb/math/math.hpp>
#include <glm/gtc/matrix_inverse.hpp>

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

	bool click;

	Listener() {
		close = false;
		maximize = false;
		minimize = false;
		border = false;
		quit = false;
		width = 0;
		height = 0;
		click = false;
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
		base::log.nothing("Move: %s - %f", ikey.str().c_str(), ivalue);
	}

	virtual void onChar(char32_t ichar) {}

	virtual void onButtonPress(input::Key ikey, int ix, int iy) {
		if(ikey == input::Key::MouseLeft) {
			base::log.nothing("Mouse Press: %s", ikey.str().c_str());
			click = true;
		}
	}
	virtual void onButtonRelease(input::Key ikey, int ix, int iy) {
		if(ikey == input::Key::MouseLeft) {
			base::log.nothing("Mouse Release: %s", ikey.str().c_str());
			click = false;
		}
	}
	virtual void onMouseMove(int ix, int iy) {}
	virtual void onWheelMove(float iv, float ih) {}

	virtual void onResize(uint32 iwidth, uint32 iheight) {
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

#include <cb/video/DummyWindow.hpp>

int cbEntry(int argc, char **argv) {

	cb::base::Timer t;

	t.tick();

	//base::log.init("log.txt", "test.base");

	//video::Window win(base::utf16("Testando"), video::Border::System);
	//video::Window winBorderless("Testando", video::Border::Empty);

	//bool border = true;

	//graphic::PixelFormat pf(graphic::ColorBits::c24, graphic::AlphaBits::c0, graphic::DepthBits::d24, true, true, 4);
	//pf.validate();

	//win.setPixelFormat(pf);
	//winBorderless.setPixelFormat(pf);

	//graphic::GLContext context(win, graphic::Version::v30);

	//video::Placement placement(100,100,800,600,false, false);
	//placement.centralize();
	//win.setPlacement(placement);

	//win.show();
	//context.activate();

	//data::Blob curfile;

	//video::Cursor *point;
	//video::Cursor *click;

	//curfile.load("cursor_hand_point.png");
	//{
	//	data::ubBitmapRGBA curimg(curfile);
	//	point = new video::Cursor(curimg, 3, 0);
	//}

	//curfile.load("cursor_hand_point_click.png");
	//{
	//	data::ubBitmapRGBA curimg(curfile);
	//	click = new video::Cursor(curimg, 3, 0);
	//}

	//video::Icon *cumulonimbus;

	//curfile.load("cumulonimbus_icon.png");
	//{
	//	data::ubBitmapRGBA curimg(curfile);
	//	cumulonimbus = new video::Icon(curimg);
	//}

	//win.setBigIcon(cumulonimbus);
	//win.setSmallIcon(cumulonimbus);

	//winBorderless.setBigIcon(cumulonimbus);
	//winBorderless.setSmallIcon(cumulonimbus);

	//base::log.info("Loading texuvmap: gizmos/grid.png");
	//graphic::Texture2D texuvmap(graphic::tex::Format::RGBA8);
	//curfile.load("gizmos/grid.png");
	//{
	//	data::Bitmap uvmap(curfile, data::bmp::Format::RGBA, data::bmp::Type::UByte);
	//	texuvmap.loadImage(0, uvmap);
	//}

	//base::log.info("Loading texgrid: gizmos/grid-xx.png");
	//graphic::Texture2D texgrid(graphic::tex::Format::RGBA8);
	//{
	//	data::Bitmap grid;
	//	curfile.load("gizmos/grid-00.png");
	//	grid.load(curfile, data::bmp::Format::RGBA, data::bmp::Type::UByte);
	//	texgrid.loadImage(0, grid);

	//	curfile.load("gizmos/grid-01.png");
	//	grid.load(curfile, data::bmp::Format::RGBA, data::bmp::Type::UByte);
	//	texgrid.addImageLOD(grid);

	//	curfile.load("gizmos/grid-02.png");
	//	grid.load(curfile, data::bmp::Format::RGBA, data::bmp::Type::UByte);
	//	texgrid.addImageLOD(grid);

	//	curfile.load("gizmos/grid-03.png");
	//	grid.load(curfile, data::bmp::Format::RGBA, data::bmp::Type::UByte);
	//	texgrid.addImageLOD(grid);

	//	curfile.load("gizmos/grid-04.png");
	//	grid.load(curfile, data::bmp::Format::RGBA, data::bmp::Type::UByte);
	//	texgrid.addImageLOD(grid);

	//	curfile.load("gizmos/grid-05.png");
	//	grid.load(curfile, data::bmp::Format::RGBA, data::bmp::Type::UByte);
	//	texgrid.addImageLOD(grid);

	//	curfile.load("gizmos/grid-06.png");
	//	grid.load(curfile, data::bmp::Format::RGBA, data::bmp::Type::UByte);
	//	texgrid.addImageLOD(grid);

	//	curfile.load("gizmos/grid-07.png");
	//	grid.load(curfile, data::bmp::Format::RGBA, data::bmp::Type::UByte);
	//	texgrid.addImageLOD(grid);

	//	texgrid.setMagFilter(graphic::tex::MagFilter::Linear);
	//	texgrid.setMinFilter(graphic::tex::MinFilter::LinearMipMapLinear);
	//}

	//data::Mesh gridmesh(data::mesh::Format(3,2,0,3,0));
	//gridmesh.plane(1,1,1,1);
	//graphic::VertexBuffer gridvb;
	//gridvb.load(gridmesh);

	//base::log.nothing("Aqui!");
	//data::Bitmap cards[52];//(64, 32, 1, data::bmp::Format::RGB, data::bmp::Type::UByte)

	//data::Bitmap *card = cards;
	//for(size_t i=0 ; i<13 ; i++) {
	//	curfile.load(base::format("cards/spades_%d.png", i+1));
	//	card->load(curfile, data::bmp::Format::RGBA, data::bmp::Type::UByte);
	//	base::log.nothing("Card #%d", i);
	//	card++;
	//}

	//for(size_t i=0 ; i<13 ; i++) {
	//	curfile.load(base::format("cards/clubs_%d.png", i+1));
	//	card->load(curfile, data::bmp::Format::RGBA, data::bmp::Type::UByte);
	//	base::log.nothing("Card #%d", i + 13);
	//	card++;
	//}

	//for(size_t i=0 ; i<13 ; i++) {
	//	curfile.load(base::format("cards/hearts_%d.png", i+1));
	//	card->load(curfile, data::bmp::Format::RGBA, data::bmp::Type::UByte);
	//	base::log.nothing("Card #%d", i + 13*2);
	//	card++;
	//}

	//for(size_t i=0 ; i<13 ; i++) {
	//	curfile.load(base::format("cards/diamonds_%d.png", i+1));
	//	card->load(curfile, data::bmp::Format::RGBA, data::bmp::Type::UByte);
	//	base::log.nothing("Card #%d", i + 13*3);
	//	card++;
	//}

	//data::Bitmap back;
	//curfile.load("cards/back.png");
	//back.load(curfile, data::bmp::Format::RGBA, data::bmp::Type::UByte);

	//base::log.nothing("Aqui2!");
	//graphic::Texture2D *cards_tex[52];
	//for(int i=0 ; i<52 ; i++) {
	//	cards_tex[i] = new graphic::Texture2D(graphic::tex::Format::RGB8);
	//	cards_tex[i]->loadBlank(0, 64, 32);
	//	cards_tex[i]->loadSubImage(0, cards[i], 0, 0);
	//	cards_tex[i]->loadSubImage(0, back, 32, 0);
	//}
	//base::log.nothing("Aqui3!");

	//win.setCursor(point);
	//winBorderless.setCursor(point);

	//base::log.nothing("Iniciando loop!");

	//graphic::gl::clearColor(graphic::tango::sky1);

	//data::Mesh mesh(data::Mesh::Format(3,2,0,3,0));
	//data::Mesh::Vertex v;

	////Back
	//v.pos    = vec4(-0.5f, 0.0f,-0.5f,0.0f);
	//v.normal = vec3( 0.0f, 1.0f, 0.0f);
	//v.tex    = vec4( 0.5f, 0.0f, 0.0f, 0.0f);
	//mesh.quad(mesh.vertex(v));

	//v.pos    = vec4( 0.5f, 0.0f,-0.5f,0.0f);
	//v.normal = vec3( 0.0f, 1.0f, 0.0f);
	//v.tex    = vec4( 1.0f, 0.0f, 0.0f, 0.0f);
	//mesh.quad(mesh.vertex(v));

	//v.pos    = vec4( 0.5f, 0.0f, 0.5f,0.0f);
	//v.normal = vec3( 0.0f, 1.0f, 0.0f);
	//v.tex    = vec4( 1.0f, 1.0f, 0.0f, 0.0f);
	//mesh.quad(mesh.vertex(v));

	//v.pos    = vec4(-0.5f, 0.0f, 0.5f,0.0f);
	//v.normal = vec3( 0.0f, 1.0f, 0.0f);
	//v.tex    = vec4( 0.5f, 1.0f, 0.0f, 0.0f);
	//mesh.quad(mesh.vertex(v));

	////Face
	//v.pos    = vec4(-0.5f, 0.0f, 0.5f,0.0f);
	//v.normal = vec3( 0.0f, 1.0f, 0.0f);
	//v.tex    = vec4( 0.5f, 1.0f, 0.0f, 0.0f);
	//mesh.quad(mesh.vertex(v));

	//v.pos    = vec4( 0.5f, 0.0f, 0.5f,0.0f);
	//v.normal = vec3( 0.0f, 1.0f, 0.0f);
	//v.tex    = vec4( 0.0f, 1.0f, 0.0f, 0.0f);
	//mesh.quad(mesh.vertex(v));

	//v.pos    = vec4( 0.5f, 0.0f,-0.5f,0.0f);
	//v.normal = vec3( 0.0f, 1.0f, 0.0f);
	//v.tex    = vec4( 0.0f, 0.0f, 0.0f, 0.0f);
	//mesh.quad(mesh.vertex(v));

	//v.pos    = vec4(-0.5f, 0.0f,-0.5f,0.0f);
	//v.normal = vec3( 0.0f, 1.0f, 0.0f);
	//v.tex    = vec4( 0.5f, 0.0f, 0.0f, 0.0f);
	//mesh.quad(mesh.vertex(v));

	////mesh.plane(1.0f, 1.0f, 1.0f, 1.0f);
	////mesh.box(1.0f, 1.0f, 1.0f);
	////mesh.sphere(0.5f, 256, 256);
	////mesh.dome(10.0f, 256, 256, 1.0);

	//graphic::VertexBuffer teste;
	//teste.load(mesh);

	//curfile.load("shaders/teste.vert");
	//graphic::Shader vertex(curfile, graphic::Shader::Type::Vertex);

	//curfile.load("shaders/teste.frag");
	//graphic::Shader fragment(curfile, graphic::Shader::Type::Fragment);

	//graphic::Program prog;
	//prog.add(&vertex);
	//prog.add(&fragment);
	//prog.link();

	//size_t w,h;

	//vec4 clearcolor = graphic::tango::sky1;

	//int i = 0;

	//Listener ltn;
	//win.setEventHub(new input::EventHub());
	//win.getEventHub()->bind((input::KeyListener*)&ltn);
	//win.getEventHub()->bind((input::CharListener*)&ltn);
	//win.getEventHub()->bind((input::MouseListener*)&ltn);
	//win.getEventHub()->bind((input::WindowListener*)&ltn);
	//win.getEventHub()->bind((input::QuitListener*)&ltn);

	//base::log.nothing("ltn: size: %dx%d", ltn.width, ltn.height);
	//ltn.width = win.getPlacement().width();
	//ltn.height = win.getPlacement().height();

	//base::Timer t;
	//float light = 0.0f;
	//float dir = 1.0f;
	//float vel = 1.0f;

	//while(input::EventLoop::update()) {
	//	t.tick();
	//	light += dir*vel*t.delta();
	//	if(light > 1.0f) {
	//		light = 1.0f;
	//		dir = -1.0f;
	//	} else if(light < 0.0f) {
	//		light = 0.0f;
	//		dir = 1.0f;
	//	}

	//	if(ltn.maximize) {
	//		if(win.getPlacement().isMaximized()) {
	//			win.restore();
	//		} else {
	//			win.maximize();
	//		}
	//	}

	//	if(ltn.minimize) {
	//		win.minimize();
	//	}

	//	if(ltn.click) {
	//		win.setCursor(click);
	//		winBorderless.setCursor(click);
	//	} else {
	//		win.setCursor(point);
	//		winBorderless.setCursor(point);
	//	}

	//	if(ltn.border) {
	//		video::Placement p;
	//		if(border) {
	//			p = win.getPlacement();
	//			base::log.nothing("Placement: %dx%d", p.width(), p.height());

	//			win.hide();
	//			winBorderless.setPlacement(p);

	//			winBorderless.setEventHub(win.getEventHub());
	//			win.setEventHub(nullptr);

	//			border = false;
	//			context.bind(winBorderless);
	//		} else {
	//			p = winBorderless.getPlacement();
	//			base::log.nothing("Placement: %dx%d", p.width(), p.height());

	//			winBorderless.hide();
	//			win.setPlacement(p);

	//			win.setEventHub(winBorderless.getEventHub());
	//			winBorderless.setEventHub(nullptr);

	//			border = true;
	//			context.bind(win);
	//		}
	//	}

	//	origin o;
	//	transf t;

	//	mat4 proj = perspective(60.0f, 640.0f/480.0f, 0.1f, 1000.0f);
	//	mat4 view = lookAt(vec3(0,5,-3), vec3(0,0,0), vec3(0,1,0));

	//	t.update(proj, inverse(proj), view);

	//	graphic::gl::viewport(0, 0, ltn.width, ltn.height);
	//	graphic::gl::clearColor(clearcolor);
	//	graphic::gl::clear(graphic::Clear::ColorDepth);

	//	cards_tex[i]->bind();
	//	//texuvmap.bind();
	//	//texgrid.bind();
	//	graphic::gl::texSquare(teste, gridvb);
	//	cards_tex[i]->unbind();

	//	prog.bind();
	//	graphic::gl::shaderTest();
	//	prog.unbind();

	//	context.swap();

	//	ltn.maximize = false;
	//	ltn.minimize = false;
	//	ltn.border = false;
	//}

	return EXIT_SUCCESS;
}
