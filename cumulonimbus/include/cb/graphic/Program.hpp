/* 
 * - Cumulonimbus - ☁
 * File: Program.h
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
#include <cb/graphic/graphic.hpp>

#include <cb/graphic/GLEWmx.hpp>
#include <cb/graphic/Shader.hpp>
#include <cb/graphic/tex/Texture.hpp>

#include <vector>

namespace cb {
	namespace graphic {
		class CbAPI Program {
		private:
			GLuint _id;
			std::vector<Shader *> _shaders;

			uint32 _next_texture_position;

		public:
			Program();
			~Program();

			void add(Shader *ishader);
			void clear();
			void link();

			void bind();
			void unbind();

			void output(const base::string &iname, uint32 iid);
			void attribute(const base::string &iname, uint32 iid);

			void uniform(const base::string &iname, float ix);
			void uniform(const base::string &iname, float ix, float iy);
			void uniform(const base::string &iname, float ix, float iy, float iz);
			void uniform(const base::string &iname, float ix, float iy, float iz, float iw);

			void uniform(const base::string &iname, int ix);
			void uniform(const base::string &iname, int ix, int iy);
			void uniform(const base::string &iname, int ix, int iy, int iz);
			void uniform(const base::string &iname, int ix, int iy, int iz, int iw);

			void uniform(const base::string &iname, const vec2 &iv);
			void uniform(const base::string &iname, const vec3 &iv);
			void uniform(const base::string &iname, const vec4 &iv);

			void uniform(const base::string &iname, const ivec2 &iv);
			void uniform(const base::string &iname, const ivec3 &iv);
			void uniform(const base::string &iname, const ivec4 &iv);

			void uniform(const base::string &iname, const mat2 &im);
			void uniform(const base::string &iname, const mat3 &im);
			void uniform(const base::string &iname, const mat4 &im);

			void uniform(const base::string &iname, Texture &itex);

			void uniform(int ilocation, float ix);
			void uniform(int ilocation, float ix, float iy);
			void uniform(int ilocation, float ix, float iy, float iz);
			void uniform(int ilocation, float ix, float iy, float iz, float iw);

			void uniform(int ilocation, int ix);
			void uniform(int ilocation, int ix, int iy);
			void uniform(int ilocation, int ix, int iy, int iz);
			void uniform(int ilocation, int ix, int iy, int iz, int iw);

			void uniform(int ilocation, const vec2 &iv);
			void uniform(int ilocation, const vec3 &iv);
			void uniform(int ilocation, const vec4 &iv);

			void uniform(int ilocation, const ivec2 &iv);
			void uniform(int ilocation, const ivec3 &iv);
			void uniform(int ilocation, const ivec4 &iv);

			void uniform(int ilocation, const mat2 &im);
			void uniform(int ilocation, const mat3 &im);
			void uniform(int ilocation, const mat4 &im);

			void uniform(int ilocation, Texture &itex);

			int uniform(const base::string &iname);
			int attribute(const base::string &iname);

			static int maxTextures();

			static int maxOutput();
			static int maxAttribute();
		};
	}  // namespace graphic
}  // namespace cb
