/* 
 * - Cumulonimbus - ☁
 * File: gVertexBuffer.cpp
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
#include <graphic/VertexBuffer.h>

#include <graphic/GLEWmx.h>

namespace cb {
	namespace graphic {
		VertexBuffer::VertexBuffer()
		:_vertex_buffer(0)
		,_quad_index_buffer(0)
		,_tri_index_buffer(0)
		,_line_index_buffer(0)
		,_point_index_buffer(0)

		,_quad_index_buffer_size(0)
		,_tri_index_buffer_size(0)
		,_line_index_buffer_size(0)
		,_point_index_buffer_size(0) {
		}

		VertexBuffer::~VertexBuffer() {
		}

		void VertexBuffer::draw() {
			glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
			if(_format.position.size) {
				glEnableClientState(GL_VERTEX_ARRAY);
				glVertexPointer(_format.position.size, GL_FLOAT, _format.stride_byte, _format.position.byte_offset);
			}

			if(_format.normal.size) {
				glEnableClientState(GL_NORMAL_ARRAY);
				glNormalPointer(GL_FLOAT, _format.stride_byte,  _format.normal.byte_offset);
			}

			if(_format.texcoord.size) {
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glTexCoordPointer(_format.texcoord.size, GL_FLOAT, _format.stride_byte,  _format.texcoord.byte_offset);
			}

			if(_format.color.size) {
				glEnableClientState(GL_COLOR_ARRAY);
				glColorPointer(_format.color.size, GL_FLOAT, _format.stride_byte,  _format.color.byte_offset);
			}

			if(_quad_index_buffer_size > 0) {
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _quad_index_buffer);
				glDrawElements(GL_QUADS, _quad_index_buffer_size, GL_UNSIGNED_INT, 0);
			}

			if(_tri_index_buffer_size > 0) {
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _tri_index_buffer);
				glDrawElements(GL_TRIANGLES, _tri_index_buffer_size, GL_UNSIGNED_INT, 0);
			}

			if(_line_index_buffer_size > 0) {
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _line_index_buffer);
				glDrawElements(GL_LINES, _line_index_buffer_size, GL_UNSIGNED_INT, 0);
			}

			if(_point_index_buffer_size > 0) {
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _point_index_buffer);
				glDrawElements(GL_POINTS, _point_index_buffer_size, GL_UNSIGNED_INT, 0);
			}

			glCheckError();
		}

		void VertexBuffer::load(const data::Mesh &imesh) {
			clear();
			_format = imesh.format();

			glGenBuffers(1, &_vertex_buffer);
			glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)*imesh.vertices().size(), (void *)imesh.vertices().data(), GL_STATIC_DRAW);

			if(imesh.quads().size()) {
				_quad_index_buffer_size = sizeof(unsigned int) * (int)imesh.quads().size();
				glGenBuffers(1, &_quad_index_buffer);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _quad_index_buffer);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, _quad_index_buffer_size, (void *)imesh.quads().data(), GL_STATIC_DRAW);
			}

			if(imesh.triangles().size()) {
				_tri_index_buffer_size = sizeof(unsigned int) * (int)imesh.triangles().size();
				glGenBuffers(1, &_tri_index_buffer);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _tri_index_buffer);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, _tri_index_buffer_size, (void *)imesh.triangles().data(), GL_STATIC_DRAW);
			}

			if(imesh.lines().size()) {
				_line_index_buffer_size = sizeof(unsigned int) * (int)imesh.lines().size();
				glGenBuffers(1, &_line_index_buffer);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _line_index_buffer);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, _line_index_buffer_size, (void *)imesh.lines().data(), GL_STATIC_DRAW);
			}

			if(imesh.points().size()) {
				_point_index_buffer_size = sizeof(unsigned int) * (int)imesh.points().size();
				glGenBuffers(1, &_point_index_buffer);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _point_index_buffer);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, _point_index_buffer_size, (void *)imesh.points().data(), GL_STATIC_DRAW);
			}
		}

		void VertexBuffer::clear() {
			_format = Format();

			if(_vertex_buffer) {
				glDeleteBuffers(1, &_vertex_buffer);
				_vertex_buffer = 0;
			}
			if(_quad_index_buffer) {
				glDeleteBuffers(1, &_quad_index_buffer);
				_quad_index_buffer = 0;
				_quad_index_buffer_size = 0;
			}
			if(_tri_index_buffer) {
				glDeleteBuffers(1, &_tri_index_buffer);
				_tri_index_buffer = 0;
				_tri_index_buffer_size = 0;
			}
			if(_line_index_buffer) {
				glDeleteBuffers(1, &_line_index_buffer);
				_line_index_buffer = 0;
				_line_index_buffer_size = 0;
			}
			if(_point_index_buffer) {
				glDeleteBuffers(1, &_point_index_buffer);
				_point_index_buffer = 0;
				_point_index_buffer_size = 0;
			}
		}
	}  // namespace graphic
}  // namespace cb
