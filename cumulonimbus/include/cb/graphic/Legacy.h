/* 
 * - Cumulonimbus - ☁
 * File: Legacy.h
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
#include <cb/graphic/graphic.h>

#include <cb/graphic/Color.h>

namespace cb {
	namespace graphic {
		namespace legacy {
			enum class MatrixMode : uint8 {
				ModelView = 0,
				Projection
			};

			enum class Mode : uint8 {
				Points,
				Lines,
				Triangles,
				Quads
			};

			enum class Capability : uint8 {
				Tex1D,
				Tex2D,
				Tex3D,

				CubeMap
			};

			void CbAPI begin(Mode imode);
			void CbAPI end();

			void CbAPI color(rgba icolor);
			void CbAPI color(float ir, float ig, float ib);
			void CbAPI color(float ir, float ig, float ib, float ia);

			void CbAPI vertex(vec2 ivertex);
			void CbAPI vertex(float ix, float iy);

			void CbAPI vertex(vec3 ivertex);
			void CbAPI vertex(float ix, float iy, float iz);

			void CbAPI normal(vec3 inormal);
			void CbAPI normal(float inx, float iny, float inz);

			void CbAPI tex(float is);

			void CbAPI tex(vec2 itexcoord);
			void CbAPI tex(float is, float it);

			void CbAPI tex(vec3 itexcoord);
			void CbAPI tex(float is, float it, float ip);

			void CbAPI enable(Capability icap);
			void CbAPI disable(Capability icap);

			void CbAPI push();
			void CbAPI pop();

			void CbAPI identity();
			void CbAPI load(mat4 imat);

			void CbAPI mode(MatrixMode imatrix_mode);

			void CbAPI perspective(float ifovy, float iaspect, float iznear, float izfar);
			void CbAPI ortho(float ileft, float iright, float ibottom, float itop, float iznear, float izfar);

			void CbAPI lookAt(vec3 ipos, vec3 itarget, vec3 iup);
			void CbAPI lookAt(float ipx, float ipy, float ipz, float itx, float ity, float itz, float iux, float iuy, float iuz);

			void CbAPI rotate(float iang, vec3 iaxis);
			void CbAPI rotate(float iang, float iax, float iay, float iaz);

			void CbAPI translate(vec3 idelta);
			void CbAPI translate(float idx, float idy, float idz);

			void CbAPI scale(vec3 iscale);
			void CbAPI scale(float isx, float isy, float isz);
		}  // namespace legacy
	}  // namespace graphic
}  // namespace cb
