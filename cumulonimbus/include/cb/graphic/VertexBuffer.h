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

#include <cb/graphic/graphic.h>

#include <cb/data/Mesh.h>

namespace cb {
	namespace graphic {
		class CbAPI VertexBuffer {
		public:
			typedef data::Mesh::Format Format;

		private:
			GLObject _vertex_buffer;

			GLObject _quad_index_buffer;
			GLObject _tri_index_buffer;
			GLObject _line_index_buffer;
			GLObject _point_index_buffer;

			int _quad_index_buffer_size;
			int _tri_index_buffer_size;
			int _line_index_buffer_size;
			int _point_index_buffer_size;

			Format _format;

		public:
			VertexBuffer();
			virtual ~VertexBuffer();

			void draw();

			void load(const data::Mesh &imesh);

			void clear();
		};
	}  // namespace graphic
}  // namespace cb
