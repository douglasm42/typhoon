/* 
 * - Cumulonimbus - ☁
 * File: vlMessage.cpp
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
#include <base/Setup.h>
#ifdef CbLinux

#include <video/Message.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <video/linux/Xlib.h>

namespace cb {
	namespace video {
		class SimpleXMessageBox {
		private:
			std::vector<xstring> _message_line;
			xstring _title;
			xstring _sorry;
			xstring _signature;

			int _width;
			int _height;
			int _max_length;

			XDisplay * _display;
			int _screen;
			XWindow _root;
			XWindow _window;
			GC _gc;
			XFontStruct * _font;
			unsigned long _black_pixel;
			unsigned long _white_pixel;

			int _rectangle_x;
			int _rectangle_y;
			int _rectangle_width;
			int _rectangle_height;

			bool _button_press;

		public:
			SimpleXMessageBox(msg::Type itype, std::vector<base::wstring> ilines);
			~SimpleXMessageBox();

			void draw();
			void drawButton(bool ipress);
		};

		SimpleXMessageBox::SimpleXMessageBox(msg::Type itype, std::vector<base::wstring> ilines) {
			_message_line.reserve(ilines.size());

			for(size_t i=0 ; i<ilines.size() ; i++) {
				_message_line.push_back(xstring());
				_message_line[i].clear();
				_message_line[i] << ilines[i];
			}
			base::wstring str;
			if(itype == msg::Error) {
				str = L"- Error Message -";
			} else if(itype == msg::Warning) {
				str = L"- Warning Message -";
			} else if(itype == msg::Info) {
				str = L"- Information Message -";
			}

			_title.clear();
			_title << str;

			str = L"Sorry about the inconvenience,";
			_sorry.clear();
			_sorry << str;

			str = L"- Staff42";
			_signature.clear();
			_signature << str;

			//Connect to XServer
			_display = XConnection::connect();
			if (!_display) {
				fprintf(stderr, "Could not open display.\n");
				exit(1);
			}
			_screen = DefaultScreen(_display);
			_root = RootWindow(_display, _screen);
			_black_pixel = BlackPixel(_display, _screen);
			_white_pixel = WhitePixel(_display, _screen);

			//Load font
			_font = XLoadQueryFont(_display, "fixed");

			//Ajust Window Size.
			XCharStruct overall;
			int x, y, direction, ascent, descent;
			_width = 0;
			_max_length = 0;
			XTextExtents16(_font, _title.data(), _title.size(), &direction, &ascent, &descent, &overall);
			if(overall.width > _width) {
				_width = overall.width;
				_max_length = _title.size();
			}
			XTextExtents16(_font, _sorry.data(), _sorry.size(), &direction, &ascent, &descent, &overall);
			if(overall.width > _width) {
				_width = overall.width;
				_max_length = _sorry.size();
			}
			XTextExtents16(_font, _signature.data(), _signature.size(), &direction, &ascent, &descent, &overall);
			if(overall.width > _width) {
				_width = overall.width;
			}
			for(size_t i=0 ; i<_message_line.size() ; i++) {
				XTextExtents16(_font, _message_line[i].data(), _message_line[i].size(), &direction, &ascent, &descent, &overall);
				if(overall.width > _width) {
					_width = overall.width;
					_max_length = _message_line[i].size();
				}
			}
			XTextExtents(_font, "------------------------------------------------------------", 60, &direction, &ascent, &descent, &overall);
			if(overall.width > _width) {
				_width = overall.width;
				_max_length = 60;
			}
			_width += 40;
			_height = (ascent + descent) * _message_line.size() + 40 + (ascent+descent)*8 + 6;
			x = XDisplayWidth(_display, _screen)/2 - _width/2;
			y = XDisplayHeight(_display, _screen)/4 - _height/2;

			//Create Window
			XSetWindowAttributes attr;
			attr.override_redirect = true;
			attr.event_mask = ExposureMask | ButtonPressMask | ButtonReleaseMask | StructureNotifyMask;
			attr.border_pixel = _black_pixel;
			attr.background_pixel = _white_pixel;

			_window = XCreateWindow(_display, _root,
					x, y, _width, _height,
					0, CopyFromParent, InputOutput, CopyFromParent,
					CWBorderPixel | CWEventMask | CWOverrideRedirect | CWBackPixel,
					&attr);

			XSelectInput(_display, _window, ExposureMask | ButtonPressMask | ButtonReleaseMask | StructureNotifyMask);
			XMapWindow(_display, _window);

			//Setup graphic context
			_screen = DefaultScreen(_display);
			_gc = XCreateGC(_display, _window, 0, 0);
			XSetBackground(_display, _gc, _white_pixel);
			XSetForeground(_display, _gc, _black_pixel);

			//Setup font
			XSetFont(_display, _gc, _font->fid);

			//Setup button rectangle
			_rectangle_width = 100;
			_rectangle_height = 6+(ascent+descent);
			_rectangle_x = _width/2 - _rectangle_width/2;
			_rectangle_y = _height - 20 - _rectangle_height;

			_button_press = false;

			//Setup close event
			Atom wmDeleteMessage = XInternAtom(_display, "WM_DELETE_WINDOW", False);
			XSetWMProtocols(_display, _window, &wmDeleteMessage, 1);

			//Start event loop
			while(true) {
				XEvent e;
				XNextEvent(_display, &e);
				if (e.type == Expose) {
					draw();
				} else if(e.type == ButtonPress) {
					if(e.xbutton.button == 1 && e.xbutton.x > _rectangle_x && e.xbutton.x < _rectangle_x + _rectangle_width) {
						if((e.xbutton.y > _rectangle_y) && (e.xbutton.y < _rectangle_y + _rectangle_height)) {
							_button_press = true;
							draw();
						}
					}
				} else if(e.type == ButtonRelease) {
					if(e.xbutton.button == 1) {
						_button_press = false;
						if(e.xbutton.x > _rectangle_x && e.xbutton.x < _rectangle_x + _rectangle_width) {
							if((e.xbutton.y > _rectangle_y) && (e.xbutton.y < _rectangle_y + _rectangle_height)) {
								return;
							}
						}
						draw();
					}
				} else if(e.type == ClientMessage) {
					if((Atom)e.xclient.data.l[0] == wmDeleteMessage) {
						return;
					}
				}
			}
		}

		SimpleXMessageBox::~SimpleXMessageBox() {
			XConnection::disconnect();
		}

		void SimpleXMessageBox::draw() {
			int x;
			int y;
			int direction;
			int ascent;
			int descent;
			XCharStruct overall;

			base::string linha;
			for(int i=0 ; i<_max_length ; i++) {
				linha.push_back('-');
			}

			x = 20;
			y = 20;
			XClearWindow(_display, _window);

			XTextExtents16(_font, _title.data(), _title.size(), &direction, &ascent, &descent, &overall);
			XDrawString16(_display, _window, _gc, (_width - overall.width)/2, y + ascent, _title.data(), _title.size());

			XTextExtents(_font, linha.c_str(), linha.size(), &direction, &ascent, &descent, &overall);
			XDrawString(_display, _window, _gc, (_width - overall.width - 20), y + (ascent + descent)*(1) + ascent, linha.c_str(), linha.size());

			for(size_t i=0 ; i<_message_line.size() ; i++) {
				XTextExtents16(_font, _message_line[i].data(), _message_line[i].size(), &direction, &ascent, &descent, &overall);
				XDrawString16(_display, _window, _gc, x, y + (ascent + descent)*(i+3) + ascent, _message_line[i].data(), _message_line[i].size());
			}

			XTextExtents(_font, linha.c_str(), linha.size(), &direction, &ascent, &descent, &overall);
			XDrawString(_display, _window, _gc, (_width - overall.width - 20), y + (ascent + descent)*(_message_line.size()+4) + ascent, linha.c_str(), linha.size());

			XTextExtents16(_font, _sorry.data(), _sorry.size(), &direction, &ascent, &descent, &overall);
			XDrawString16(_display, _window, _gc, (_width - overall.width - 20), y + (ascent + descent)*(_message_line.size()+5) + ascent, _sorry.data(), _sorry.size());

			XTextExtents16(_font, _signature.data(), _signature.size(), &direction, &ascent, &descent, &overall);
			XDrawString16(_display, _window, _gc, (_width - overall.width - 20), y + (ascent + descent)*(_message_line.size()+6) + ascent, _signature.data(), _signature.size());

			drawButton(false);
		}

		void SimpleXMessageBox::drawButton(bool ipress) {
			int x, y, direction, ascent, descent;
			XCharStruct overall;

			XTextExtents(_font, "Ok", strlen("Ok"), &direction, &ascent, &descent, &overall);

			y = _rectangle_y + 3;
			x = _rectangle_x + _rectangle_width/2;

			XDrawRectangle(_display, _window, _gc, 0, 0, _width-1, _height-1);

			if(_button_press) {
				XFillRectangle(_display, _window, _gc, _rectangle_x-1, _rectangle_y-1, _rectangle_width+3, _rectangle_height+3);
				XSetBackground(_display, _gc, _black_pixel);
				XSetForeground(_display, _gc, _white_pixel);
			}

			XDrawString(_display, _window, _gc, x - overall.width/2, y + ascent, "Ok", strlen("Ok"));
			XDrawRectangle(_display, _window, _gc, _rectangle_x, _rectangle_y, _rectangle_width, _rectangle_height);

			XSetBackground(_display, _gc, _white_pixel);
			XSetForeground(_display, _gc, _black_pixel);
		}

		void Message::show() {
			SimpleXMessageBox(_type, _message_lines);
		}
	}  // namespace video
}  // namespace cb

#endif
