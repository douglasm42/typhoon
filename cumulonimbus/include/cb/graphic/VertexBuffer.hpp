/* 
 * - Cumulonimbus - ☁
 * File: VertexBuffer.h
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
#include <cb/graphic/Program.hpp>

#include <cb/data/Mesh.hpp>

namespace cb {
	namespace graphic {
		class CbAPI VertexBuffer {
		private:
			typedef struct {
				base::string name;
				GLuint index​;
				GLint size​;
				GLenum type​;
				GLboolean normalized​;
				GLsizei stride​;
				GLvoid *offset;
			} attribute;

			GLuint _vertex_buffer;

			GLuint _quad_index_buffer;
			GLuint _tri_index_buffer;
			GLuint _line_index_buffer;
			GLuint _point_index_buffer;

			int _quad_index_buffer_size;
			int _tri_index_buffer_size;
			int _line_index_buffer_size;
			int _point_index_buffer_size;

			std::vector<attribute> _format;

		public:
			VertexBuffer();
			virtual ~VertexBuffer();

			void draw(Program &iprogram);

			void load(const data::Mesh &imesh);

			void clear();
		};
	}  // namespace graphic
}  // namespace cb
