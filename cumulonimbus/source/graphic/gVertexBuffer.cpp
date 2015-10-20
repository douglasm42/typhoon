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
#include <cb/graphic/VertexBuffer.hpp>

#include <cb/graphic/GLEWmx.hpp>

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

		void VertexBuffer::draw(Program &iprogram) {
			glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);

			for(auto &at : _format) {
				at.index​ = iprogram.attribute(at.name);
				glEnableVertexAttribArray(at.index​);
				glVertexAttribPointer(at.index​, at.size​, at.type​, at.normalized​, at.stride​, at.offset);
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

			for(const auto &at : _format) {
				glDisableVertexAttribArray(at.index​);
			}

			glCheckError;
		}

		void VertexBuffer::load(const data::Mesh &imesh) {
			const GLenum gltype[] = {
				GL_UNSIGNED_BYTE,	//Bool
				GL_INT,				//Int
				GL_UNSIGNED_INT,	//UInt
				GL_FLOAT,			//Float
				GL_DOUBLE			//Double
			};

			clear();

			for(const auto &at : imesh.getFormat().attr()) {
				attribute attr;
				attr.name		= at.name;
				attr.index​		= 0;
				attr.size​		= (GLint)at.components;
				attr.type​		= gltype[(uint)at.type];
				attr.normalized​	= GL_TRUE;
				attr.stride​		= (GLsizei)_format.size();
				attr.offset	= reinterpret_cast<void*>(at.offset);
				
				_format.push_back(attr);
			}

			glGenBuffers(1, &_vertex_buffer);
			glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)*imesh.getVerticesData().size(), (void *)imesh.getVerticesData().data(), GL_STATIC_DRAW);

			if(imesh.getQuadsData().size()) {
				_quad_index_buffer_size = sizeof(unsigned int) * (int)imesh.getQuadsData().size();
				glGenBuffers(1, &_quad_index_buffer);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _quad_index_buffer);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, _quad_index_buffer_size, (void *)imesh.getQuadsData().data(), GL_STATIC_DRAW);
			}

			if(imesh.getTrianglesData().size()) {
				_tri_index_buffer_size = sizeof(unsigned int) * (int)imesh.getTrianglesData().size();
				glGenBuffers(1, &_tri_index_buffer);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _tri_index_buffer);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, _tri_index_buffer_size, (void *)imesh.getTrianglesData().data(), GL_STATIC_DRAW);
			}

			if(imesh.getLinesData().size()) {
				_line_index_buffer_size = sizeof(unsigned int) * (int)imesh.getLinesData().size();
				glGenBuffers(1, &_line_index_buffer);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _line_index_buffer);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, _line_index_buffer_size, (void *)imesh.getLinesData().data(), GL_STATIC_DRAW);
			}

			if(imesh.getPointsData().size()) {
				_point_index_buffer_size = sizeof(unsigned int) * (int)imesh.getPointsData().size();
				glGenBuffers(1, &_point_index_buffer);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _point_index_buffer);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, _point_index_buffer_size, (void *)imesh.getPointsData().data(), GL_STATIC_DRAW);
			}
		}

		void VertexBuffer::clear() {
			_format.clear();

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
