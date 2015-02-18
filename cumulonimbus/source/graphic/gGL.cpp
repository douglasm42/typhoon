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
#include <cb/graphic/GL.h>

#include <cb/graphic/GLEWmx.h>

#include <cb/graphic/VertexBuffer.h>
#include <cb/graphic/Color.h>

#include <cb/base/Timer.h>

namespace cb {
	namespace graphic {
		namespace gl {
			void viewport(int ix, int iy, int iwidth, int iheight) {
				glViewport(ix, iy, iwidth, iheight);
			}

			void clear(Clear iflag) {
				if(iflag == Clear::Depth) {
					glClear(GL_DEPTH_BUFFER_BIT);
				} else if(iflag == Clear::Color) {
					glClear(GL_COLOR_BUFFER_BIT);
				} else if(iflag == Clear::ColorDepth) {
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				}
			}

			void clearColor(rgba icolor) {
				glClearColor(icolor.r, icolor.g, icolor.b, icolor.a);
			}

			void clearDepth(double idepth) {
				glClearDepth(idepth);
			}

			void CbAPI enable(Capability icap) {
				switch(icap) {
				case Capability::DepthTest:
					glEnable(GL_DEPTH_TEST);
					break;
				}
			}

			void CbAPI disable(Capability icap) {
				switch(icap) {
				case Capability::DepthTest:
					glDisable(GL_DEPTH_TEST);
					break;
				}
			}

			void texSquare(VertexBuffer &teste, VertexBuffer &grid) {
				static base::Timer timer;
				static float angle = 0.0f;
				static float scale = 45;
				timer.tick();

				angle += timer.delta() * scale;

				glEnable(GL_DEPTH_TEST);
				glEnable(GL_CULL_FACE);
				glCullFace(GL_BACK);

				GLint vp[4];
				glGetIntegerv( GL_VIEWPORT, vp );

				glEnable(GL_MULTISAMPLE);
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				//glEnable(GL_BLEND);
				//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
				glDisable(GL_TEXTURE_2D);
				glEnable(GL_TEXTURE_2D);
				grid.draw();

				glPushMatrix();
					glRotatef(angle, 0.0f, 0.0f, 1.0f);
					teste.draw();
				glPopMatrix();

				glPushMatrix();
					glTranslatef(1.0f, -0.1f, 0.0f);
					teste.draw();
				glPopMatrix();

				glPushMatrix();
					glTranslatef(-1.0f, -0.1f, 0.0f);
					glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
					teste.draw();
				glPopMatrix();

				glDisable(GL_TEXTURE_2D);
				glDisable(GL_MULTISAMPLE);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
				//glDisable(GL_BLEND);
			}

			void shaderTest() {
				static base::Timer timer;
				static float alpha = 0.0f;
				static float scale = 2.0f;
				timer.tick();

				alpha += timer.delta() * scale;
				if(scale == 2.0f && alpha > 1.0f) {
					scale = -2.0f;
					alpha = 1.0f;
				} else if(scale == -2.0f && alpha < 0.0f) {
					scale = 2.0f;
					alpha = 0.0f;
				}

				glEnable(GL_MULTISAMPLE);
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);

				glBegin(GL_TRIANGLES);
					for(int i=-100 ; i<100 ; i++) {
						for(int j=-100 ; j<100 ; j++) {
							bool white;

							if(glm::abs(i)%2) {
								if(glm::abs(j)%2) {
									white = true;
									glColor4f(tango::aluminium1.r, tango::aluminium1.g, tango::aluminium1.b, alpha);
								} else {
									white = false;
									glColor4f(tango::aluminium6.r, tango::aluminium6.g, tango::aluminium6.b, alpha);
								}
							} else {
								if(glm::abs(j)%2) {
									white = false;
									glColor4f(tango::aluminium6.r, tango::aluminium6.g, tango::aluminium6.b, alpha);
								} else {
									white = true;
									glColor4f(tango::aluminium1.r, tango::aluminium1.g, tango::aluminium1.b, alpha);
								}
							}

							if(true) {
								glVertex3f((i+0)*0.5f, 0.0f, (j+0)*0.5f);
								glVertex3f((i+0)*0.5f, 0.0f, (j+1)*0.5f);
								glVertex3f((i+1)*0.5f, 0.0f, (j+1)*0.5f);

								glVertex3f((i+1)*0.5f, 0.0f, (j+0)*0.5f);
								glVertex3f((i+0)*0.5f, 0.0f, (j+0)*0.5f);
								glVertex3f((i+1)*0.5f, 0.0f, (j+1)*0.5f);
							}
						}
					}
				glEnd();

				glDisable(GL_MULTISAMPLE);
				glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
			}
		}  // namespace gl
	}  // namespace graphic
}  // namespace cb
