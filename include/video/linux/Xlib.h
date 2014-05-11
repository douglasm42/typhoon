/* 
 * - Cumulonimbus - ☁
 * File: Xlib.h
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
#pragma once

#include <base/Setup.h>
#ifdef CbLinux

#include <video/video.h>

#include <X11/Xlib.h>

#include <base/Kin.h>
#include <base/String.h>

#include <vector>

namespace cb {
	namespace video {
		typedef ::Display XDisplay;
		typedef ::Window XWindow;

		typedef std::vector<XChar2b> xstring;

		xstring &operator<<(xstring &ixstr, const base::string &istr);
		xstring &operator<<(xstring &ixstr, const base::wstring &iwstr);
		xstring &operator<<(xstring &ixstr, const base::lstring &ilstr);

		class CbAPI XConnection {
		private:
			static XDisplay *_display;
			static size_t _connections_count;

		public:
			static XDisplay *connect();
			static void disconnect();
		};

		class CbAPI XWindowInfo {
		public:
			XDisplay *display;
			int screen;
			XWindow *root;
			XWindow *video;
		};
	}  // namespace video
}  // namespace cb

#endif
