/* 
 * - Cumulonimbus - ☁
 * File: origin.h
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

#include <glm/detail/type_vec3.hpp>
#include <glm/detail/type_mat4x4.hpp>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace glm {
	namespace custom {
		template<typename T, precision P>
		tvec3<T, P> transform(const tvec3<T, P> &ivec, const tquat<T, P> &iquat) {
			tquat<T, P> qvec = iquat * tquat<T, P>(0, ivec.x, ivec.y, ivec.z) * inverse(iquat);
			return tvec3<T, P>(qvec.x, qvec.y, qvec.z);
		}

		template<typename T, precision P>
		tvec3<T, P> transform(const tvec3<T, P> &ivec, const tmat4x4<T, P> &imat) {
			tvec4<T, P> v(ivec);
			v.w = 1.0f;
			return (imat * v).xyz();
		}

		template<typename T, precision P>
		tvec4<T, P> transform(const tvec4<T, P> &ivec, const tmat4x4<T, P> &imat) {
			return imat * ivec;
		}

		template<typename T, precision P>
		class torigin {
		private:
			tvec3<T, P> _t;
			tvec3<T, P> _s;
			tquat<T, P> _r;

		protected:
			virtual void onChange() {}

		public:
			torigin();
			torigin(const torigin &itorigin);
			virtual ~torigin();

			void rotate(float iang, float iax, float iay, float iaz, bool ilocal = false);
			void rotate(float iang, tvec3<T, P> iaxis, bool ilocal = false);

			void pitch(float iang, bool ilocal = false)	{rotate(iang, tvec3<T, P>(1.0f, 0.0f, 0.0f), ilocal);}
			void yaw(float iang, bool ilocal = false)	{rotate(iang, tvec3<T, P>(0.0f, 1.0f, 0.0f), ilocal);}
			void roll(float iang, bool ilocal = false)	{rotate(iang, tvec3<T, P>(0.0f, 0.0f, 1.0f), ilocal);}

			void scale(float isx, float isy, float isz);
			void scale(tvec3<T, P> is);

			void translate(float ix, float iy, float iz, bool ilocal = true);
			void translate(tvec3<T, P> it, bool ilocal = true);

			void position(float ix, float iy, float iz) {_t.x = ix; _t.y = iy; _t.z = iz;}
			void position(tvec3<T, P> ip) {_t = ip;}

			const tvec3<T, P> &scale() const {return _s;}
			const tvec3<T, P> &position() const {return _t;}

			void lookAt(tvec3<T, P> itarget, tvec3<T, P> iup = glm::vec3(0.0f, 1.0f, 0.0f));

			void clear();

			void invert();
			void concat(const torigin &itorigin);
			tmat4x4<T, P> matrix() const;

			tvec3<T, P> transform(const tvec3<T, P> &iv) const;
		};

		template<typename T, precision P>
		torigin<T, P>::torigin() {
			clear();
		}

		template<typename T, precision P>
		torigin<T, P>::torigin(const torigin &itorigin)
		:_t(itorigin._t), _s(itorigin._s), _r(itorigin._r) {
		}

		template<typename T, precision P>
		torigin<T, P>::~torigin() {
		}

		template<typename T, precision P>
		void torigin<T, P>::rotate(float iang, float iax, float iay, float iaz, bool ilocal) {
			tvec3<T, P> axis(normalize(tvec3<T, P>(iax, iay, iaz)));
			tquat<T, P> rot;
			rot = rotate(rot, iang, axis);
			if(ilocal) {
				_r = _r * rot;
			} else {
				_r = rot * _r;
			}

			onChange();
		}

		template<typename T, precision P>
		void torigin<T, P>::rotate(float iang, tvec3<T, P> iaxis, bool ilocal) {
			tquat<T, P> rot;
			rot = rotate(rot, iang, iaxis);
			if(ilocal) {
				_r = _r * rot;
			} else {
				_r = rot * _r;
			}

			onChange();
		}

		template<typename T, precision P>
		void torigin<T, P>::scale(float isx, float isy, float isz) {
			_s.x *= isx;
			_s.y *= isy;
			_s.z *= isz;

			onChange();
		}

		template<typename T, precision P>
		void torigin<T, P>::scale(tvec3<T, P> is) {
			_s.x *= is.x;
			_s.y *= is.y;
			_s.z *= is.z;

			onChange();
		}

		template<typename T, precision P>
		void torigin<T, P>::translate(float ix, float iy, float iz, bool ilocal) {
			tquat<T, P> t(0, ix, iy, iz);
			if(ilocal) {
				t = (_r * t) * inverse(_r);
				t.x *= _s.x;
				t.y *= _s.y;
				t.z *= _s.z;
			}
			_t += tvec3<T, P>(t.x, t.y, t.z);

			onChange();
		}

		template<typename T, precision P>
		void torigin<T, P>::translate(tvec3<T, P> it, bool ilocal) {
			tquat<T, P> t(0, it.x, it.y, it.z);
			if(ilocal) {
				t = _r * t * inverse(_r);
				t.x *= _s.x;
				t.y *= _s.y;
				t.z *= _s.z;
			}
			_t += tvec3<T, P>(t.x, t.y, t.z);

			onChange();
		}

		template<typename T, precision P>
		void torigin<T, P>::lookAt(tvec3<T, P> itarget, tvec3<T, P> iup) {
			tvec3<T, P> forward = glm::normalize(itarget - _t);
			tvec3<T, P> side = glm::normalize(glm::cross(forward, iup));
			tvec3<T, P> up = glm::normalize(glm::cross(side, forward));

			glm::mat3 rot;
			rot[0][0] = side.x;		rot[1][0] = side.y;		rot[2][0] = side.z;
			rot[0][1] = up.x;		rot[1][1] = up.y;		rot[2][1] = up.z;
			rot[0][2] = forward.x;	rot[1][2] = forward.y;	rot[2][2] = forward.z;

			_r = glm::quat_cast(rot);
		}

		template<typename T, precision P>
		void torigin<T, P>::clear() {
			_t.x = 0.0f;	_t.y = 0.0f;	_t.z = 0.0f;
			_s.x = 1.0f;	_s.y = 1.0f;	_s.z = 1.0f;
			_r.w = 1.0f;	_r.x = 0.0f;	_r.y = 0.0f;	_r.z = 0.0f;

			onChange();
		}

		template<typename T, precision P>
		void torigin<T, P>::invert() {
			_t.x *= -1.0f;
			_t.y *= -1.0f;
			_t.z *= -1.0f;

			_r = inverse(_r);

			tquat<T, P> t = _r * tquat<T, P>(0, _t.x, _t.y, _t.z) * inverse(_r);

			_t.x = t.x * _s.x;
			_t.y = t.y * _s.y;
			_t.z = t.z * _s.z;

			onChange();
		}

		template<typename T, precision P>
		void torigin<T, P>::concat(const torigin &itorigin) {
			//Concatenação da translação.
			translate(itorigin._t.x, itorigin._t.y, itorigin._t.z);

			//Concatenação da rotação.
			_r = _r * itorigin._r;

			_r = normalize(_r);

			//Concatenação da escala.
			scale(itorigin._s.x, itorigin._s.y, itorigin._s.z);

			onChange();
		}

		template<typename T, precision P>
		tmat4x4<T, P> torigin<T, P>::matrix() const {
			tmat4x4<T, P> om = mat4_cast(_r);

			om[0][0] *= _s.x;	om[1][0] *= _s.y;	om[2][0] *= _s.z;	om[3][0] = _t.x;
			om[0][1] *= _s.x;	om[1][1] *= _s.y;	om[2][1] *= _s.z;	om[3][1] = _t.y;
			om[0][2] *= _s.x;	om[1][2] *= _s.y;	om[2][2] *= _s.z;	om[3][2] = _t.z;

			return om;
		}

		template<typename T, precision P>
		tvec3<T, P> torigin<T, P>::transform(const tvec3<T, P> &iv) const {
			tvec3<T, P> v = _r * iv;

			return tvec3<T, P>(
				v.x * _s.x + _t.x,
				v.y * _s.y + _t.y,
				v.z * _s.z + _t.z
			);
		}

		template<typename T, precision P>
		class ttransf {
		private:
			tmat4x4<T, P> _projection;
			tmat4x4<T, P> _modelview;
			tmat4x4<T, P> _projection_modelview;
			tmat3x3<T, P> _normal;

		public:
			ttransf()
			:_projection(1.0f)
			,_modelview(1.0f)
			,_projection_modelview(1.0f)
			,_normal(1.0f) {}

			void update(const tmat4x4<T, P> &iprojection, const tmat4x4<T, P> &iinverse_projection, const tmat4x4<T, P> &imodelview) {
				_projection = iprojection;
				_modelview = imodelview;
				_projection_modelview = _projection * _modelview;
				_normal = glm::transpose(glm::inverse(tmat3x3<T, P>(_modelview)));
			}

			void modelview(const tmat4x4<T, P> &imodelview) {
				_modelview = imodelview;
				_projection_modelview = _projection * _modelview;
				_normal = glm::transpose(glm::inverse(tmat3x3<T, P>(_modelview)));
			}

			const tmat4x4<T, P> &projection()			const {return _projection;}
			const tmat4x4<T, P> &modelview()			const {return _modelview;}
			const tmat4x4<T, P> &projectionModelview()	const {return _projection_modelview;}
			const tmat3x3<T, P> &normal()				const {return _normal;}
		};
	}  // namespace custom
}  // namespace glm
