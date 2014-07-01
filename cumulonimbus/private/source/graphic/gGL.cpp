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

#include <graphic/VertexBuffer.h>

#include <base/Timer.h>

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

		void GL::clearColor(vec4 icolor) {
			glClearColor(icolor.r, icolor.g, icolor.b, icolor.a);
		}

		void GL::clearDepth(double idepth) {
			glClearDepth(idepth);
		}

		void GL::texSquare(VertexBuffer &teste, VertexBuffer &grid) {
			static base::Timer timer;
			static float angle = 0.0f;
			static float scale = 45;
			timer.tick();

			angle += timer.delta() * scale;

			//glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);

			GLint vp[4];
			glGetIntegerv( GL_VIEWPORT, vp );

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(60.0, (GLfloat)vp[2]/(GLfloat)vp[3], 1.0, 30.0);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			gluLookAt(0.0, 2.2, -5.3, 0,0,0,0,1,0);

			glBegin(GL_LINES);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(2.0f, 0.0f, 0.0f);

			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 2.0f, 0.0f);

			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 2.0f);
			glEnd();

			glColor3f(1.0f, 1.0f, 1.0f);

			if(GLEW_EXT_texture_filter_anisotropic) {
				GLfloat largest;
				glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest);
			}
			glEnable(GL_TEXTURE_2D);
			//grid.draw();

			glPushMatrix();
				glRotatef(angle, 0.0f, 0.0f, 1.0f);
				teste.draw();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(1.0f, 0.0f, 0.0f);
				teste.draw();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-1.0f, 0.0f, 0.0f);
				glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
				teste.draw();
			glPopMatrix();

			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
		}
	}  // namespace graphic
}  // namespace cb
