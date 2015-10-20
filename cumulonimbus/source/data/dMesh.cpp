/* 
 * - Cumulonimbus - ☁
 * File: dMesh.cpp
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
#include <cb/data/Mesh.hpp>

#include <cb/base/Log.hpp>

namespace cb {
	namespace data {
		const size_t mesh::Attribute::_size[] = {
			sizeof(bool),	//Bool
			sizeof(int32),	//Int
			sizeof(uint32),	//UInt
			sizeof(float),	//Float
			sizeof(double)	//Double
		};

		void Mesh::load(const Mesh &imesh) {
			clear();
			_format = imesh._format;

			_vertices.assign(imesh._vertices.begin(), imesh._vertices.end());
			_quads.assign(imesh._quads.begin(), imesh._quads.end());
			_triangles.assign(imesh._triangles.begin(), imesh._triangles.end());
			_lines.assign(imesh._lines.begin(), imesh._lines.end());
			_points.assign(imesh._points.begin(), imesh._points.end());
		}

		void Mesh::append(const Mesh &imesh) {
			if(_format == imesh._format) {
				uint32 offset = (uint32)_vertices.size();
				_vertices.assign(imesh._vertices.begin(), imesh._vertices.end());

				std::vector<uint32>::const_iterator it;
				std::vector<uint32>::size_type i;

				i = _quads.size();
				_quads.resize(_quads.size() + imesh._quads.size());
				for(it=imesh._quads.begin() ; it!=imesh._quads.end() ; ++it, ++i) {
					_quads[i] = (*it) + offset;
				}

				i = _triangles.size();
				_triangles.resize(_triangles.size() + imesh._triangles.size());
				for(it=imesh._triangles.begin() ; it!=imesh._triangles.end() ; ++it, ++i) {
					_triangles[i] = (*it) + offset;
				}

				i = _lines.size();
				_lines.resize(_lines.size() + imesh._lines.size());
				for(it=imesh._lines.begin() ; it!=imesh._lines.end() ; ++it, ++i) {
					_lines[i] = (*it) + offset;
				}

				i = _points.size();
				_points.resize(_points.size() + imesh._points.size());
				for(it=imesh._points.begin() ; it!=imesh._points.end() ; ++it, ++i) {
					_points[i] = (*it) + offset;
				}
			} else {
				Throw(tokurei::LoadFailed);
			}
		}

		void Mesh::load(Blob &ifile) {
			
		}

		void Mesh::save(Blob &ifile) const {

		}
	}  // namespace data
}  // namespace cb
