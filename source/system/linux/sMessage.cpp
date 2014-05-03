/*
 * sMessage.cpp
 *
 *  Created on: Apr 30, 2014
 *      Author: douglas
 */
#include <system/Message.h>
#ifdef CbLinux

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/Xlib.h>

namespace cb {
	namespace system {
		class SimpleXMessageBox {
		private:
			std::vector<std::vector<XChar2b> > _message_line;
			std::vector<XChar2b> _title;
			std::vector<XChar2b> _sorry;
			std::vector<XChar2b> _signature;

			int _width;
			int _height;

			Display * _display;
			int _screen;
			Window _root;
			Window _window;
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
				_message_line.push_back(std::vector<XChar2b>());
				_message_line[i].reserve(ilines[i].length());
				for(size_t j=0 ; j<ilines[i].length() ; j++) {
					unsigned char *pt = (unsigned char *)&ilines[i][j];
					XChar2b c = {pt[1], pt[0]};
					_message_line[i].push_back(c);
				}
			}
			base::wstring str;
			if(itype == msg::Error) {
				str = L"- Error Message -";
			} else if(itype == msg::Warning) {
				str = L"- Warning Message -";
			} else if(itype == msg::Info) {
				str = L"- Information Message -";
			}

			_title.reserve(str.length());
			for(size_t j=0 ; j<str.length() ; j++) {
				unsigned char *pt = (unsigned char *)&str[j];
				XChar2b c = {pt[1], pt[0]};
				_title.push_back(c);
			}

			str = L"Sorry about the inconvenience.";
			_sorry.reserve(str.length());
			for(size_t j=0 ; j<str.length() ; j++) {
				unsigned char *pt = (unsigned char *)&str[j];
				XChar2b c = {pt[1], pt[0]};
				_sorry.push_back(c);
			}

			str = L"- Staff42";
			_signature.reserve(str.length());
			for(size_t j=0 ; j<str.length() ; j++) {
				unsigned char *pt = (unsigned char *)&str[j];
				XChar2b c = {pt[1], pt[0]};
				_signature.push_back(c);
			}

			//Connect to XServer
			_display = XOpenDisplay(":0");
			if (!_display) {
				fprintf(stderr, "Could not open display.\n");
				exit(1);
			}
			_screen = DefaultScreen(_display);
			_root = RootWindow(_display, _screen);
			_black_pixel = BlackPixel(_display, _screen);
			_white_pixel = WhitePixel(_display, _screen);

			//Create Window
			XSetWindowAttributes attr;
			attr.override_redirect = true;
			attr.event_mask = ExposureMask | ButtonPressMask | ButtonReleaseMask | StructureNotifyMask;
			attr.border_pixel = _black_pixel;
			attr.background_pixel = _white_pixel;

			_window = XCreateWindow(_display, _root,
					1, 1, 600, 300,
					0, CopyFromParent, InputOutput, CopyFromParent,
					CWBorderPixel | CWEventMask | CWOverrideRedirect | CWBackPixel,
					&attr);

			XSelectInput(_display, _window, ExposureMask | ButtonPressMask | ButtonReleaseMask | StructureNotifyMask);
			XMapWindow(_display, _window);

			//Setup graphics context
			_screen = DefaultScreen(_display);
			_gc = XCreateGC(_display, _window, 0, 0);
			XSetBackground(_display, _gc, _white_pixel);
			XSetForeground(_display, _gc, _black_pixel);

			//Setup font
			_font = XLoadQueryFont(_display, "fixed");
			XSetFont(_display, _gc, _font->fid);

			//Ajust Window Size.
			XCharStruct overall;
			int x, y, direction, ascent, descent;
			_width = 0;
			XTextExtents16(_font, _title.data(), _title.size(), &direction, &ascent, &descent, &overall);
			if(overall.width > _width) {
				_width = overall.width;
			}
			XTextExtents16(_font, _sorry.data(), _sorry.size(), &direction, &ascent, &descent, &overall);
			if(overall.width > _width) {
				_width = overall.width + 40;
			}
			XTextExtents16(_font, _signature.data(), _signature.size(), &direction, &ascent, &descent, &overall);
			if(overall.width > _width) {
				_width = overall.width;
			}
			for(size_t i=0 ; i<_message_line.size() ; i++) {
				XTextExtents16(_font, _message_line[i].data(), _message_line[i].size(), &direction, &ascent, &descent, &overall);
				if(overall.width > _width) {
					_width = overall.width;
				}
			}
			_width += 40;
			_height = (ascent + descent) * _message_line.size() + 40 + (ascent+descent)*8 + 6;
			x = XDisplayWidth(_display, _screen)/2 - _width/2;
			y = XDisplayHeight(_display, _screen)/4 - _height/2;
			XMoveResizeWindow(_display, _window, x, y, _width, _height);

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
			XCloseDisplay(_display);
		}

		void SimpleXMessageBox::draw() {
			int x;
			int y;
			int direction;
			int ascent;
			int descent;
			XCharStruct overall;

			x = 20;
			y = 20;
			XClearWindow(_display, _window);

			XTextExtents16(_font, _title.data(), _title.size(), &direction, &ascent, &descent, &overall);
			XDrawString16(_display, _window, _gc, (_width - overall.width)/2, y + ascent, _title.data(), _title.size());

			for(size_t i=0 ; i<_message_line.size() ; i++) {
				XTextExtents16(_font, _message_line[i].data(), _message_line[i].size(), &direction, &ascent, &descent, &overall);
				XDrawString16(_display, _window, _gc, x, y + (ascent + descent)*(i+2) + ascent, _message_line[i].data(), _message_line[i].size());
			}

			XTextExtents16(_font, _sorry.data(), _sorry.size(), &direction, &ascent, &descent, &overall);
			XDrawString16(_display, _window, _gc, (_width - overall.width - 20), y + (ascent + descent)*(_message_line.size()+4) + ascent, _sorry.data(), _sorry.size());

			XTextExtents16(_font, _signature.data(), _signature.size(), &direction, &ascent, &descent, &overall);
			XDrawString16(_display, _window, _gc, (_width - overall.width - 20), y + (ascent + descent)*(_message_line.size()+5) + ascent, _signature.data(), _signature.size());

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
	}  // namespace system
}  // namespace cb

#endif
