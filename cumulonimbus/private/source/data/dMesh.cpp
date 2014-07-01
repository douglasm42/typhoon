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
#include <data/Mesh.h>

#include <base/Log.h>

namespace cb {
	namespace data {
		void Mesh::load(const Format &iformat) {
			clear();
			_format = iformat;
		}

		void Mesh::load(const File &isize) {
			clear();
		}

		void Mesh::load(const Mesh &imesh) {
			clear();
			_format = imesh.format();
			_vertices.assign(imesh._vertices.begin(), imesh._vertices.end());
			_quads.assign(imesh._quads.begin(), imesh._quads.end());
			_triangles.assign(imesh._triangles.begin(), imesh._triangles.end());
			_lines.assign(imesh._lines.begin(), imesh._lines.end());
			_points.assign(imesh._points.begin(), imesh._points.end());
		}

		void Mesh::append(const File &isize) {
		}

		void Mesh::append(const Mesh &imesh) {
			if(_format == imesh._format) {
				size_t offset = (size_t)_vertices.size();
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

		uint32 Mesh::vertex(const Vertex &ivertex) {
			size_t pos = (size_t)_vertices.size();
			_vertices.resize(_vertices.size() + _format.stride);

			if(_format.position.size > 0) {
				_vertices[pos + _format.position.offset] = ivertex.pos.x;
				if(_format.position.size > 1) {
					_vertices[pos + _format.position.offset+1] = ivertex.pos.y;
					if(_format.position.size > 2) {
						_vertices[pos + _format.position.offset+2] = ivertex.pos.z;
						if(_format.position.size > 3) {
							_vertices[pos + _format.position.offset+3] = ivertex.pos.w;
						}
					}
				}
			}

			if(_format.texcoord.size > 0) {
				_vertices[pos + _format.texcoord.offset] = ivertex.tex.x;
				if(_format.texcoord.size > 1) {
					_vertices[pos + _format.texcoord.offset+1] = ivertex.tex.y;
					if(_format.texcoord.size > 2) {
						_vertices[pos + _format.texcoord.offset+2] = ivertex.tex.z;
						if(_format.texcoord.size > 3) {
							_vertices[pos + _format.texcoord.offset+3] = ivertex.tex.w;
						}
					}
				}
			}

			if(_format.color.size > 0) {
				_vertices[pos + _format.color.offset] = ivertex.color.r;
				if(_format.color.size > 1) {
					_vertices[pos + _format.color.offset+1] = ivertex.color.g;
					if(_format.color.size > 2) {
						_vertices[pos + _format.color.offset+2] = ivertex.color.b;
						if(_format.color.size > 3) {
							_vertices[pos + _format.color.offset+3] = ivertex.color.a;
						}
					}
				}
			}

			if(_format.normal.size > 0) {
				_vertices[pos + _format.normal.offset] = ivertex.normal.x;
				if(_format.normal.size > 1) {
					_vertices[pos + _format.normal.offset+1] = ivertex.normal.y;
					if(_format.normal.size > 2) {
						_vertices[pos + _format.normal.offset+2] = ivertex.normal.z;
					}
				}
			}

			if(_format.tangent.size > 0) {
				_vertices[pos + _format.tangent.offset] = ivertex.tangent.x;
				if(_format.tangent.size > 1) {
					_vertices[pos + _format.tangent.offset+1] = ivertex.tangent.y;
					if(_format.tangent.size > 2) {
						_vertices[pos + _format.tangent.offset+2] = ivertex.tangent.z;
					}
				}
			}

			return pos / _format.stride;
		}

		uint32 Mesh::uvertex(const Vertex &ivertex) {
			if(_format.stride) {
				float *vert = new float[_format.stride];

				if(_format.position.size > 0) {
					vert[_format.position.offset] = ivertex.pos.x;
					if(_format.position.size > 1) {
						vert[_format.position.offset+1] = ivertex.pos.y;
						if(_format.position.size > 2) {
							vert[_format.position.offset+2] = ivertex.pos.z;
							if(_format.position.size > 3) {
								vert[_format.position.offset+3] = ivertex.pos.w;
							}
						}
					}
				}

				if(_format.texcoord.size > 0) {
					vert[_format.texcoord.offset] = ivertex.tex.x;
					if(_format.texcoord.size > 1) {
						vert[_format.texcoord.offset+1] = ivertex.tex.y;
						if(_format.texcoord.size > 2) {
							vert[_format.texcoord.offset+2] = ivertex.tex.z;
							if(_format.texcoord.size > 3) {
								vert[_format.texcoord.offset+3] = ivertex.tex.w;
							}
						}
					}
				}

				if(_format.color.size > 0) {
					vert[_format.color.offset] = ivertex.color.r;
					if(_format.color.size > 1) {
						vert[_format.color.offset+1] = ivertex.color.g;
						if(_format.color.size > 2) {
							vert[_format.color.offset+2] = ivertex.color.b;
							if(_format.color.size > 3) {
								vert[_format.color.offset+3] = ivertex.color.a;
							}
						}
					}
				}

				if(_format.normal.size > 0) {
					vert[_format.normal.offset] = ivertex.normal.x;
					if(_format.normal.size > 1) {
						vert[_format.normal.offset+1] = ivertex.normal.y;
						if(_format.normal.size > 2) {
							vert[_format.normal.offset+2] = ivertex.normal.z;
						}
					}
				}

				if(_format.tangent.size > 0) {
					vert[_format.tangent.offset] = ivertex.tangent.x;
					if(_format.tangent.size > 1) {
						vert[_format.tangent.offset+1] = ivertex.tangent.y;
						if(_format.tangent.size > 2) {
							vert[_format.tangent.offset+2] = ivertex.tangent.z;
						}
					}
				}

				size_t vertices_count = _vertices.size()/_format.stride;
				for(size_t i=0 ; i<vertices_count ; i++) {
					float *v = _vertices.data() + _format.stride * i;

					size_t k;
					for(k=0 ; k<_format.stride && v[k] == vert[k] ; k++);

					if(k==_format.stride) {
						delete [] vert;
						return i;
					}
				}

				_vertices.insert(_vertices.end(), vert, vert + _format.stride);
				delete [] vert;
				return vertices_count;
			} else {
				Throw(tokurei::SetFailed);
			}
		}

		void Mesh::quad(uint32 iindex) {
			_quads.push_back(iindex);
		}

		void Mesh::tri(uint32 iindex) {
			_triangles.push_back(iindex);
		}

		void Mesh::line(uint32 iindex) {
			_lines.push_back(iindex);
		}

		void Mesh::point(uint32 iindex) {
			_points.push_back(iindex);
		}

		void Mesh::quad(uint32 iindex1, uint32 iindex2, uint32 iindex3, uint32 iindex4) {
			_quads.push_back(iindex1);
			_quads.push_back(iindex2);
			_quads.push_back(iindex3);
			_quads.push_back(iindex4);
		}

		void Mesh::tri(uint32 iindex1, uint32 iindex2, uint32 iindex3) {
			_triangles.push_back(iindex1);
			_triangles.push_back(iindex2);
			_triangles.push_back(iindex3);
		}

		void Mesh::line(uint32 iindex1, uint32 iindex2) {
			_lines.push_back(iindex1);
			_lines.push_back(iindex2);
		}

		void Mesh::sphere(float iradius, size_t irings, size_t isectors) {
			clear();
			_format = Format(3,2,0,3,0);

			const float R = 1.0f / (float) irings;
			const float S = 1.0f / (float) isectors;
			const float Pi = pi<float>();
			const float Pi2 = 2.0f * Pi;
			const float mhalfPi = -half_pi<float>();

			size_t nv = (irings+1) * (isectors+1);
			Vertex v;
			_vertices.reserve(nv * _format.stride);

			for (size_t r = 0; r < irings+1; r++) {
				const float rR = (float)r * R;
				const float PirR = Pi * rR;
				const float sPirR = sin<float>(PirR);

				float const y = sin<float>(mhalfPi + PirR);

				for (size_t s = 0; s < isectors+1; s++) {
					const float Pi2sS = Pi2 * (float)(s%isectors) * S;

					float const x = cos<float>(Pi2sS) * sPirR;
					float const z = sin<float>(Pi2sS) * sPirR;

					v.tex.x = 1-s * S;
					v.tex.y = r * R;

					v.pos.x = x * iradius;
					v.pos.y = y * iradius;
					v.pos.z = z * iradius;

					v.normal.x = x;
					v.normal.y = y;
					v.normal.z = z;

					vertex(v);
				}
			}

			size_t ni = ((irings) * (isectors)) * 4;
			_quads.resize(ni);
			size_t ii=0;

			uint32 pitch = isectors+1;
			for (uint32 r = 0; r < irings; r++) {
				for (uint32 s = 0; s < isectors; s++) {
					_quads[ii]   = (r + 1) * pitch + s;
					_quads[ii+1] = (r + 1) * pitch + (s + 1);
					_quads[ii+2] = r * pitch + (s + 1);
					_quads[ii+3] = r * pitch + s;
					ii+=4;
				}
			}
		}

		void Mesh::dome(float iradius, size_t irings, size_t isectors, float ifraction) {
			clear();
			_format = Format(3,2,0,3,0);

			const float R = 1.0f / (float) irings * ifraction;
			const float S = 1.0f / (float) isectors;
			const float Pi = pi<float>();
			const float Pi2 = 2.0f * Pi;
			const float mhalfPi = -half_pi<float>();

			const float offset = 1.0f - ifraction;

			size_t nv = (irings+1) * (isectors+1);
			Vertex v;
			_vertices.reserve(nv * _format.stride);

			for (size_t r = 0; r < irings+1; r++) {
				const float rR = (float)r * R;
				const float PirR = Pi * rR + glm::pi<float>() * offset;
				const float sPirR = sin<float>(PirR);

				float const y = sin<float>(mhalfPi + PirR);

				for (size_t s = 0; s < isectors+1; s++) {
					const float Pi2sS = Pi2 * (float)(s%isectors) * S;

					float const x = cos<float>(Pi2sS) * sPirR;
					float const z = sin<float>(Pi2sS) * sPirR;

					v.tex.x = s * S;
					v.tex.y = r * R;

					v.pos.x = x * iradius;
					v.pos.y = y * iradius;
					v.pos.z = z * iradius;

					v.normal.x = x;
					v.normal.y = y;
					v.normal.z = z;

					vertex(v);
				}
			}

			size_t ni = ((irings) * (isectors)) * 4;
			_quads.resize(ni);
			size_t ii=0;

			uint32 pitch = isectors+1;
			for (uint32 r = 0; r < irings; r++) {
				for (uint32 s = 0; s < isectors; s++) {
					_quads[ii]   = r * pitch + s;
					_quads[ii+1] = r * pitch + (s + 1);
					_quads[ii+2] = (r + 1) * pitch + (s + 1);
					_quads[ii+3] = (r + 1) * pitch + s;
					ii+=4;
				}
			}
		}

		void Mesh::box(float ixsize, float iysize, float izsize) {
			clear();
			_format = Format(3,2,0,3,0);

			ixsize = fabs(ixsize);
			iysize = fabs(iysize);
			izsize = fabs(izsize);

			Vertex v;

			//Top
			v.pos    = vec4(-0.5f*ixsize, 0.5f*iysize,-0.5f*izsize, 0.0f);
			v.normal = vec3( 0.0f, 1.0f, 0.0f);
			v.tex    = vec4( 1.0f, 0.0f, 0.0f, 0.0f);
			vertex(v);

			v.pos    = vec4( 0.5f*ixsize, 0.5f*iysize,-0.5f*izsize, 0.0f);
			v.normal = vec3( 0.0f, 1.0f, 0.0f);
			v.tex    = vec4( 0.0f, 0.0f, 0.0f, 0.0f);
			vertex(v);

			v.pos    = vec4( 0.5f*ixsize, 0.5f*iysize, 0.5f*izsize, 0.0f);
			v.normal = vec3( 0.0f, 1.0f, 0.0f);
			v.tex    = vec4( 0.0f, 1.0f, 0.0f, 0.0f);
			vertex(v);

			v.pos    = vec4(-0.5f*ixsize, 0.5f*iysize, 0.5f*izsize, 0.0f);
			v.normal = vec3( 0.0f, 1.0f, 0.0f);
			v.tex    = vec4( 1.0f, 1.0f, 0.0f, 0.0f);
			vertex(v);

			//Bottom
			v.pos    = vec4(-0.5f*ixsize,-0.5f*iysize, 0.5f*izsize, 0.0f);
			v.normal = vec3( 0.0f,-1.0f, 0.0f);
			v.tex    = vec4( 0.0f, 1.0f, 0.0f, 0.0f);
			vertex(v);

			v.pos    = vec4( 0.5f*ixsize,-0.5f*iysize, 0.5f*izsize, 0.0f);
			v.normal = vec3( 0.0f,-1.0f, 0.0f);
			v.tex    = vec4( 1.0f, 1.0f, 0.0f, 0.0f);
			vertex(v);

			v.pos    = vec4( 0.5f*ixsize,-0.5f*iysize,-0.5f*izsize, 0.0f);
			v.normal = vec3( 0.0f,-1.0f, 0.0f);
			v.tex    = vec4( 1.0f, 0.0f, 0.0f, 0.0f);
			vertex(v);

			v.pos    = vec4(-0.5f*ixsize,-0.5f*iysize,-0.5f*izsize, 0.0f);
			v.normal = vec3( 0.0f,-1.0f, 0.0f);
			v.tex    = vec4( 0.0f, 0.0f, 0.0f, 0.0f);
			vertex(v);

			//Left
			v.pos    = vec4(-0.5f*ixsize, 0.5f*iysize,-0.5f*izsize, 0.0f);
			v.normal = vec3(-1.0f, 0.0f, 0.0f);
			v.tex    = vec4( 0.0f, 1.0f, 0.0f, 0.0f);
			vertex(v);

			v.pos    = vec4(-0.5f*ixsize, 0.5f*iysize, 0.5f*izsize, 0.0f);
			v.normal = vec3(-1.0f, 0.0f, 0.0f);
			v.tex    = vec4( 1.0f, 1.0f, 0.0f, 0.0f);
			vertex(v);

			v.pos    = vec4(-0.5f*ixsize,-0.5f*iysize, 0.5f*izsize, 0.0f);
			v.normal = vec3(-1.0f, 0.0f, 0.0f);
			v.tex    = vec4( 1.0f, 0.0f, 0.0f, 0.0f);
			vertex(v);

			v.pos    = vec4(-0.5f*ixsize,-0.5f*iysize,-0.5f*izsize, 0.0f);
			v.normal = vec3(-1.0f, 0.0f, 0.0f);
			v.tex    = vec4( 0.0f, 0.0f, 0.0f, 0.0f);
			vertex(v);

			//Right
			v.pos    = vec4( 0.5f*ixsize, 0.5f*iysize, 0.5f*izsize, 0.0f);
			v.normal = vec3( 1.0f, 0.0f, 0.0f);
			v.tex    = vec4( 0.0f, 1.0f, 0.0f, 0.0f);
			vertex(v);

			v.pos    = vec4( 0.5f*ixsize, 0.5f*iysize,-0.5f*izsize, 0.0f);
			v.normal = vec3( 1.0f, 0.0f, 0.0f);
			v.tex    = vec4( 1.0f, 1.0f, 0.0f, 0.0f);
			vertex(v);

			v.pos    = vec4( 0.5f*ixsize,-0.5f*iysize,-0.5f*izsize, 0.0f);
			v.normal = vec3( 1.0f, 0.0f, 0.0f);
			v.tex    = vec4( 1.0f, 0.0f, 0.0f, 0.0f);
			vertex(v);

			v.pos    = vec4( 0.5f*ixsize,-0.5f*iysize, 0.5f*izsize, 0.0f);
			v.normal = vec3( 1.0f, 0.0f, 0.0f);
			v.tex    = vec4( 0.0f, 0.0f, 0.0f, 0.0f);
			vertex(v);

			//Front
			v.pos    = vec4(-0.5f*ixsize, 0.5f*iysize, 0.5f*izsize, 0.0f);
			v.normal = vec3( 0.0f, 0.0f, 1.0f);
			v.tex    = vec4( 0.0f, 1.0f, 0.0f, 0.0f);
			vertex(v);

			v.pos    = vec4( 0.5f*ixsize, 0.5f*iysize, 0.5f*izsize, 0.0f);
			v.normal = vec3( 0.0f, 0.0f, 1.0f);
			v.tex    = vec4( 1.0f, 1.0f, 0.0f, 0.0f);
			vertex(v);

			v.pos    = vec4( 0.5f*ixsize,-0.5f*iysize, 0.5f*izsize, 0.0f);
			v.normal = vec3( 0.0f, 0.0f, 1.0f);
			v.tex    = vec4( 1.0f, 0.0f, 0.0f, 0.0f);
			vertex(v);

			v.pos    = vec4(-0.5f*ixsize,-0.5f*iysize, 0.5f*izsize, 0.0f);
			v.normal = vec3( 0.0f, 0.0f, 1.0f);
			v.tex    = vec4( 0.0f, 0.0f, 0.0f, 0.0f);
			vertex(v);

			//Back
			v.pos    = vec4( 0.5f*ixsize, 0.5f*iysize,-0.5f*izsize, 0.0f);
			v.normal = vec3( 0.0f, 0.0f,-1.0f);
			v.tex    = vec4( 0.0f, 1.0f, 0.0f, 0.0f);
			vertex(v);

			v.pos    = vec4(-0.5f*ixsize, 0.5f*iysize,-0.5f*izsize, 0.0f);
			v.normal = vec3( 0.0f, 0.0f,-1.0f);
			v.tex    = vec4( 1.0f, 1.0f, 0.0f, 0.0f);
			vertex(v);

			v.pos    = vec4(-0.5f*ixsize,-0.5f*iysize,-0.5f*izsize, 0.0f);
			v.normal = vec3( 0.0f, 0.0f,-1.0f);
			v.tex    = vec4( 1.0f, 0.0f, 0.0f, 0.0f);
			vertex(v);

			v.pos    = vec4( 0.5f*ixsize,-0.5f*iysize,-0.5f*izsize, 0.0f);
			v.normal = vec3( 0.0f, 0.0f,-1.0f);
			v.tex    = vec4( 0.0f, 0.0f, 0.0f, 0.0f);
			vertex(v);

			//Top
			quad(3, 2, 1, 0);

			//Bottom
			quad(7, 6, 5, 4);

			//Left
			quad(11,10, 9, 8);

			//Right
			quad(15,14,13,12);

			//Front
			quad(19,18,17,16);

			//Back
			quad(23,22,21,20);
		}

		void Mesh::plane(float ixsize, float izsize, float itxsize, float itysize) {
			clear();
			_format = Format(3,2,0,3,0);

			ixsize = fabs(ixsize);
			izsize = fabs(izsize);
			itxsize = fabs(itxsize);
			itysize = fabs(itysize);

			Vertex v;

			v.pos    = vec4(-0.5f*ixsize, 0.0f, 0.5f*izsize, 0.0f);
			v.normal = vec3( 0.0f, 1.0f, 0.0f);
			v.tex    = vec4( 1.0f*itxsize, 1.0f*itysize, 0.0f, 0.0f);
			vertex(v);

			v.pos    = vec4( 0.5f*ixsize, 0.0f, 0.5f*izsize, 0.0f);
			v.normal = vec3( 0.0f, 1.0f, 0.0f);
			v.tex    = vec4( 0.0f, 1.0f*itysize, 0.0f, 0.0f);
			vertex(v);

			v.pos    = vec4( 0.5f*ixsize, 0.0f,-0.5f*izsize, 0.0f);
			v.normal = vec3( 0.0f, 1.0f, 0.0f);
			v.tex    = vec4( 0.0f, 0.0f, 0.0f, 0.0f);
			vertex(v);

			v.pos    = vec4(-0.5f*ixsize, 0.0f,-0.5f*izsize, 0.0f);
			v.normal = vec3( 0.0f, 1.0f, 0.0f);
			v.tex    = vec4( 1.0f*itxsize, 0.0f, 0.0f, 0.0f);
			vertex(v);

			quad(0, 1, 2, 3);
		}
	}  // namespace data
}  // namespace cb
