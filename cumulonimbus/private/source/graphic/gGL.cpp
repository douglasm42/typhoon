/* 
 * - Cumulonimbus - ☁
 * File: gGL.cpp
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
#include <graphic/GL.h>

#include <graphic/GLEWmx.h>

namespace cb {
	namespace graphic {
		void GL::viewport(int ix, int iy, int iwidth, int iheight) {
			glViewport(ix, iy, iwidth, iheight);
		}

		void GL::clear(Clear iflag) {
			if(iflag == Clear::Depth) {
				glClear(GL_DEPTH_BUFFER_BIT);
			} else if(iflag == Clear::Color) {
				glClear(GL_COLOR_BUFFER_BIT);
			} else if(iflag == Clear::ColorDepth) {
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			}
		}

		void GL::clearColor(math::vec4 icolor) {
			glClearColor(icolor.r, icolor.g, icolor.b, icolor.a);
		}

		void GL::clearDepth(double idepth) {
			glClearDepth(idepth);
		}

		void GL::texSquare() {
			GLint vp[4];
			glGetIntegerv( GL_VIEWPORT, vp );


			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(60.0, (GLfloat)vp[2]/(GLfloat)vp[3], 1.0, 30.0);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glTranslatef(0.0f, 0.0f, -3.6f);

			glEnable(GL_TEXTURE_2D);
			glBegin(GL_QUADS);
				glColor3f(1.0f,1.0f,1.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f, -1.0f, 0.0f);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, 1.0f, 0.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 1.0f, 0.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, -1.0f, 0.0f);

				glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, 0.0f);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, 1.0f, 0.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(2.41421f, 1.0f, -1.41421f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(2.41421f, -1.0f, -1.41421f);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		}
	}  // namespace graphic
}  // namespace cb
