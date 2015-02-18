/* 
 * - Cumulonimbus - ☁
 * File: gLegacy.cpp
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
#include <cb/graphic/Legacy.h>

#include <cb/graphic/GLEWmx.h>

namespace cb {
	namespace graphic {
		namespace legacy {
			void CbAPI begin(Mode imode) {
				switch(imode) {
				case Mode::Points:
					glBegin(GL_POINTS);
					break;
				case Mode::Lines:
					glBegin(GL_LINES);
					break;
				case Mode::Triangles:
					glBegin(GL_TRIANGLES);
					break;
				case Mode::Quads:
					glBegin(GL_QUADS);
					break;
				}
			}

			void CbAPI end() {
				glEnd();
			}

			void color(rgba icolor) {
				glColor4f(icolor.r, icolor.g, icolor.b, icolor.a);
			}

			void color(float ir, float ig, float ib) {
				glColor3f(ir, ig, ib);
			}

			void color(float ir, float ig, float ib, float ia) {
				glColor4f(ir, ig, ib, ia);
			}

			void vertex(vec2 ivertex) {
				glVertex2f(ivertex.x, ivertex.y);
			}

			void vertex(float ix, float iy) {
				glVertex2f(ix, iy);
			}

			void vertex(vec3 ivertex) {
				glVertex3f(ivertex.x, ivertex.y, ivertex.z);
			}

			void vertex(float ix, float iy, float iz) {
				glVertex3f(ix, iy, iz);
			}

			void normal(vec3 inormal) {
				glNormal3f(inormal.x, inormal.y, inormal.z);
			}

			void normal(float inx, float iny, float inz) {
				glNormal3f(inx, iny, inz);
			}

			void tex(float is) {
				glTexCoord1f(is);
			}

			void tex(vec2 itexcoord) {
				glTexCoord2f(itexcoord.s, itexcoord.t);
			}

			void tex(float is, float it) {
				glTexCoord2f(is, it);
			}

			void tex(vec3 itexcoord) {
				glTexCoord3f(itexcoord.s, itexcoord.t, itexcoord.p);
			}

			void tex(float is, float it, float ip) {
				glTexCoord3f(is, it, ip);
			}

			void enable(Capability icap) {
				switch(icap) {
				case Capability::Tex1D:
					glEnable(GL_TEXTURE_1D);
					break;
				case Capability::Tex2D:
					glEnable(GL_TEXTURE_2D);
					break;
				case Capability::Tex3D:
					glEnable(GL_TEXTURE_3D);
					break;

				case Capability::CubeMap:
					glEnable(GL_TEXTURE_CUBE_MAP);
					break;
				}
			}

			void disable(Capability icap) {
				switch(icap) {
				case Capability::Tex1D:
					glDisable(GL_TEXTURE_1D);
					break;
				case Capability::Tex2D:
					glDisable(GL_TEXTURE_2D);
					break;
				case Capability::Tex3D:
					glDisable(GL_TEXTURE_3D);
					break;

				case Capability::CubeMap:
					glDisable(GL_TEXTURE_CUBE_MAP);
					break;
				}
			}

			void push() {
				glPushMatrix();
			}

			void pop() {
				glPopMatrix();
			}

			void identity() {
				glLoadIdentity();
			}

			void load(mat4 imat) {
				glLoadMatrixf(&imat[0][0]);
			}

			void mode(MatrixMode imatrix_mode) {
				if(imatrix_mode == MatrixMode::ModelView) {
					glMatrixMode(GL_MODELVIEW);
				} else if(imatrix_mode == MatrixMode::Projection) {
					glMatrixMode(GL_PROJECTION);
				}
			}

			void perspective(float ifovy, float iaspect, float iznear, float izfar) {
				gluPerspective(ifovy, iaspect, iznear, izfar);
			}

			void ortho(float ileft, float iright, float ibottom, float itop, float iznear, float izfar) {
				glOrtho(ileft, iright, ibottom, itop, iznear, izfar);
			}

			void lookAt(vec3 ipos, vec3 itarget, vec3 iup) {
				gluLookAt(ipos.x, ipos.y, ipos.z, itarget.x, itarget.y, itarget.z, iup.x, iup.y, iup.z);
			}

			void lookAt(float ipx, float ipy, float ipz, float itx, float ity, float itz, float iux, float iuy, float iuz) {
				gluLookAt(ipx, ipy, ipz, itx, ity, itz, iux, iuy, iuz);
			}

			void rotate(float iang, vec3 iaxis) {
				glRotatef(iang, iaxis.x, iaxis.y, iaxis.z);
			}

			void rotate(float iang, float iax, float iay, float iaz) {
				glRotatef(iang, iax, iay, iaz);
			}

			void translate(vec3 idelta) {
				glTranslatef(idelta.x, idelta.y, idelta.z);
			}

			void translate(float idx, float idy, float idz) {
				glTranslatef(idx, idy, idz);
			}

			void scale(vec3 iscale) {
				glScalef(iscale.x, iscale.y, iscale.z);
			}

			void scale(float isx, float isy, float isz) {
				glScalef(isx, isy, isz);
			}
		}  // namespace legacy
	}  // namespace graphic
}  // namespace cb
