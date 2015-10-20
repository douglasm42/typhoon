/*
* - Cumulonimbus - ☁
* File: dMeshBuilder.cpp
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
#include <cb/data/MeshBuilder.hpp>

#define CB_DATA_MESHBUILDER_ADD_VERTEX(vertex) _vertices.insert(_mesh._vertices.end(), reinterpret_cast<uint8*>(&vertex), reinterpret_cast<uint8*>(&vertex) + sizeof(vertex))

namespace cb {
	namespace data {
		inline MeshBuilder::MeshBuilder() {
			mesh::Format f;
			f.add("position", mesh::Type::Float, 3);
			f.add("texCoord", mesh::Type::Float, 2);
			f.add("normal", mesh::Type::Float, 3);
			f.add("color", mesh::Type::Float, 4);

			_mesh.load(f);
		}

		inline MeshBuilder::~MeshBuilder() {
		}

		inline MeshBuilder &MeshBuilder::begin(mesh::Mode imode) {
			if(_missing_vertices != 0) {
				Throw(tokurei::AddFailed);
			}
			_mode = imode;

			return *this;
		}

		inline MeshBuilder &MeshBuilder::texCoord(vec2 itex_coord) {
			_tex_coord = itex_coord;

			return *this;
		}
		inline MeshBuilder &MeshBuilder::normal(vec3 inormal) {
			_normal = inormal;

			return *this;
		}
		inline MeshBuilder &MeshBuilder::color(vec4 icolor) {
			_color = icolor;

			return *this;
		}
		inline MeshBuilder &MeshBuilder::vertex(vec3 iposition) {
			mesh::BasicVertex v = {
				iposition,
				_tex_coord,
				_normal,
				_color
			};

			uint8 *begin_v = reinterpret_cast<uint8*>(&v);
			uint32 index = uint32(_mesh._vertices.size() / _mesh._format.size());
			_mesh._vertices.insert(_mesh._vertices.end(), begin_v, begin_v + _mesh._format.size());

			switch(_mode) {
			case mesh::Mode::Points:
				_mesh._points.push_back(index);

			case mesh::Mode::Lines:
				_mesh._lines.push_back(index);
				_missing_vertices = (0 == _missing_vertices ? 1 : _missing_vertices - 1);

			case mesh::Mode::Triangles:
				_mesh._triangles.push_back(index);
				_missing_vertices = (0 == _missing_vertices ? 2 : _missing_vertices - 1);

			case mesh::Mode::Quads:
				_mesh._quads.push_back(index);
				_missing_vertices = (0 == _missing_vertices ? 3 : _missing_vertices - 1);
			}

			return *this;
		}

		inline void MeshBuilder::end() {
			//Compactar as informações do mesh!
		}

		inline const Mesh &MeshBuilder::mesh() const {
			return _mesh;
		}

		inline void MeshBuilder::sphere(float iradius, uint32 irings, uint32 isectors) {
			_mesh.clear();
			const float R = 1.0f / (float)irings;
			const float S = 1.0f / (float)isectors;
			const float Pi = pi<float>();
			const float Pi2 = 2.0f * Pi;
			const float mhalfPi = -half_pi<float>();

			uint32 nv = (irings + 1) * (isectors + 1);
			mesh::BasicVertex v;
			v.color = _color;
			_mesh._vertices.reserve(nv * _mesh._format.size());

			for(uint32 r = 0; r < irings + 1; r++) {
				const float rR = (float)r * R;
				const float PirR = Pi * rR;
				const float sPirR = sin(PirR);

				const float y = sin(mhalfPi + PirR);

				for(uint32 s = 0; s < isectors + 1; s++) {
					const float Pi2sS = Pi2 * (float)(s%isectors) * S;

					float const x = cos(Pi2sS) * sPirR;
					float const z = sin(Pi2sS) * sPirR;

					v.texCoord.x = 1 - s * S;
					v.texCoord.y = r * R;

					v.position.x = x * iradius;
					v.position.y = y * iradius;
					v.position.z = z * iradius;

					v.normal.x = x;
					v.normal.y = y;
					v.normal.z = z;

					_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);
				}
			}

			uint32 ni = ((irings)* (isectors)) * 4;
			_mesh._quads.resize(ni);
			uint32 ii = 0;

			uint32 pitch = isectors + 1;
			for(uint32 r = 0; r < irings; r++) {
				for(uint32 s = 0; s < isectors; s++) {
					_mesh._quads[ii] = (r + 1) * pitch + s;
					_mesh._quads[ii + 1] = (r + 1) * pitch + (s + 1);
					_mesh._quads[ii + 2] = r * pitch + (s + 1);
					_mesh._quads[ii + 3] = r * pitch + s;
					ii += 4;
				}
			}
		}
		inline void MeshBuilder::dome(float iradius, uint32 irings, uint32 isectors, float ifraction) {
			_mesh.clear();

			const float R = 1.0f / (float)irings * ifraction;
			const float S = 1.0f / (float)isectors;
			const float Pi = pi<float>();
			const float Pi2 = 2.0f * Pi;
			const float mhalfPi = -half_pi<float>();

			const float offset = 1.0f - ifraction;

			uint32 nv = (irings + 1) * (isectors + 1);
			mesh::BasicVertex v;
			v.color = _color;
			_mesh._vertices.reserve(nv * _mesh._format.size());

			for(uint32 r = 0; r < irings + 1; r++) {
				const float rR = (float)r * R;
				const float PirR = Pi * rR + glm::pi<float>() * offset;
				const float sPirR = sin(PirR);

				float const y = sin(mhalfPi + PirR);

				for(uint32 s = 0; s < isectors + 1; s++) {
					const float Pi2sS = Pi2 * (float)(s%isectors) * S;

					float const x = cos(Pi2sS) * sPirR;
					float const z = sin(Pi2sS) * sPirR;

					v.texCoord.x = s * S;
					v.texCoord.y = r * R;

					v.position.x = x * iradius;
					v.position.y = y * iradius;
					v.position.z = z * iradius;

					v.normal.x = x;
					v.normal.y = y;
					v.normal.z = z;

					_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);
				}
			}

			uint32 ni = ((irings)* (isectors)) * 4;
			_mesh._quads.resize(ni);
			uint32 ii = 0;

			uint32 pitch = isectors + 1;
			for(uint32 r = 0; r < irings; r++) {
				for(uint32 s = 0; s < isectors; s++) {
					_mesh._quads[ii] = r * pitch + s;
					_mesh._quads[ii + 1] = r * pitch + (s + 1);
					_mesh._quads[ii + 2] = (r + 1) * pitch + (s + 1);
					_mesh._quads[ii + 3] = (r + 1) * pitch + s;
					ii += 4;
				}
			}
		}
		inline void MeshBuilder::box(float ixsize, float iysize, float izsize) {
			_mesh.clear();

			ixsize = fabs(ixsize);
			iysize = fabs(iysize);
			izsize = fabs(izsize);

			mesh::BasicVertex v;
			v.color = _color;

			//Top
			v.position = vec3(-0.5f*ixsize, 0.5f*iysize, -0.5f*izsize);
			v.normal = vec3(0.0f, 1.0f, 0.0f);
			v.texCoord = vec2(1.0f, 0.0f);
			_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);

			v.position = vec3(0.5f*ixsize, 0.5f*iysize, -0.5f*izsize);
			v.normal = vec3(0.0f, 1.0f, 0.0f);
			v.texCoord = vec2(0.0f, 0.0f);
			_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);

			v.position = vec3(0.5f*ixsize, 0.5f*iysize, 0.5f*izsize);
			v.normal = vec3(0.0f, 1.0f, 0.0f);
			v.texCoord = vec2(0.0f, 1.0f);
			_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);

			v.position = vec3(-0.5f*ixsize, 0.5f*iysize, 0.5f*izsize);
			v.normal = vec3(0.0f, 1.0f, 0.0f);
			v.texCoord = vec2(1.0f, 1.0f);
			_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);

			//Bottom
			v.position = vec3(-0.5f*ixsize, -0.5f*iysize, 0.5f*izsize);
			v.normal = vec3(0.0f, -1.0f, 0.0f);
			v.texCoord = vec2(0.0f, 1.0f);
			_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);

			v.position = vec3(0.5f*ixsize, -0.5f*iysize, 0.5f*izsize);
			v.normal = vec3(0.0f, -1.0f, 0.0f);
			v.texCoord = vec2(1.0f, 1.0f);
			_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);

			v.position = vec3(0.5f*ixsize, -0.5f*iysize, -0.5f*izsize);
			v.normal = vec3(0.0f, -1.0f, 0.0f);
			v.texCoord = vec2(1.0f, 0.0f);
			_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);

			v.position = vec3(-0.5f*ixsize, -0.5f*iysize, -0.5f*izsize);
			v.normal = vec3(0.0f, -1.0f, 0.0f);
			v.texCoord = vec2(0.0f, 0.0f);
			_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);

			//Left
			v.position = vec3(-0.5f*ixsize, 0.5f*iysize, -0.5f*izsize);
			v.normal = vec3(-1.0f, 0.0f, 0.0f);
			v.texCoord = vec2(0.0f, 1.0f);
			_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);

			v.position = vec3(-0.5f*ixsize, 0.5f*iysize, 0.5f*izsize);
			v.normal = vec3(-1.0f, 0.0f, 0.0f);
			v.texCoord = vec2(1.0f, 1.0f);
			_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);

			v.position = vec3(-0.5f*ixsize, -0.5f*iysize, 0.5f*izsize);
			v.normal = vec3(-1.0f, 0.0f, 0.0f);
			v.texCoord = vec2(1.0f, 0.0f);
			_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);

			v.position = vec3(-0.5f*ixsize, -0.5f*iysize, -0.5f*izsize);
			v.normal = vec3(-1.0f, 0.0f, 0.0f);
			v.texCoord = vec2(0.0f, 0.0f);
			_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);

			//Right
			v.position = vec3(0.5f*ixsize, 0.5f*iysize, 0.5f*izsize);
			v.normal = vec3(1.0f, 0.0f, 0.0f);
			v.texCoord = vec2(0.0f, 1.0f);
			_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);

			v.position = vec3(0.5f*ixsize, 0.5f*iysize, -0.5f*izsize);
			v.normal = vec3(1.0f, 0.0f, 0.0f);
			v.texCoord = vec2(1.0f, 1.0f);
			_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);

			v.position = vec3(0.5f*ixsize, -0.5f*iysize, -0.5f*izsize);
			v.normal = vec3(1.0f, 0.0f, 0.0f);
			v.texCoord = vec2(1.0f, 0.0f);
			_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);

			v.position = vec3(0.5f*ixsize, -0.5f*iysize, 0.5f*izsize);
			v.normal = vec3(1.0f, 0.0f, 0.0f);
			v.texCoord = vec2(0.0f, 0.0f);
			_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);

			//Front
			v.position = vec3(-0.5f*ixsize, 0.5f*iysize, 0.5f*izsize);
			v.normal = vec3(0.0f, 0.0f, 1.0f);
			v.texCoord = vec2(0.0f, 1.0f);
			_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);

			v.position = vec3(0.5f*ixsize, 0.5f*iysize, 0.5f*izsize);
			v.normal = vec3(0.0f, 0.0f, 1.0f);
			v.texCoord = vec2(1.0f, 1.0f);
			_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);

			v.position = vec3(0.5f*ixsize, -0.5f*iysize, 0.5f*izsize);
			v.normal = vec3(0.0f, 0.0f, 1.0f);
			v.texCoord = vec2(1.0f, 0.0f);
			_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);

			v.position = vec3(-0.5f*ixsize, -0.5f*iysize, 0.5f*izsize);
			v.normal = vec3(0.0f, 0.0f, 1.0f);
			v.texCoord = vec2(0.0f, 0.0f);
			_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);

			//Back
			v.position = vec3(0.5f*ixsize, 0.5f*iysize, -0.5f*izsize);
			v.normal = vec3(0.0f, 0.0f, -1.0f);
			v.texCoord = vec2(0.0f, 1.0f);
			_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);

			v.position = vec3(-0.5f*ixsize, 0.5f*iysize, -0.5f*izsize);
			v.normal = vec3(0.0f, 0.0f, -1.0f);
			v.texCoord = vec2(1.0f, 1.0f);
			_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);

			v.position = vec3(-0.5f*ixsize, -0.5f*iysize, -0.5f*izsize);
			v.normal = vec3(0.0f, 0.0f, -1.0f);
			v.texCoord = vec2(1.0f, 0.0f);
			_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);

			v.position = vec3(0.5f*ixsize, -0.5f*iysize, -0.5f*izsize);
			v.normal = vec3(0.0f, 0.0f, -1.0f);
			v.texCoord = vec2(0.0f, 0.0f);
			_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);

			uint32 q[24] = {
				//Top
				3, 2, 1, 0,
				//Bottom
				7, 6, 5, 4,
				//Left
				11, 10, 9, 8,
				//Right
				15, 14, 13, 12,
				//Front
				19, 18, 17, 16,
				//Back
				23, 22, 21, 20
			};
			_mesh._quads.insert(_mesh._quads.end(), q, q + 24);
		}

		inline void MeshBuilder::plane(float ixsize, float izsize, float itxsize, float itysize) {
			_mesh.clear();

			ixsize = fabs(ixsize);
			izsize = fabs(izsize);
			itxsize = fabs(itxsize);
			itysize = fabs(itysize);

			mesh::BasicVertex v;
			v.color = _color;

			v.position = vec3(-0.5f*ixsize, 0.0f, 0.5f*izsize);
			v.normal = vec3(0.0f, 1.0f, 0.0f);
			v.texCoord = vec2(1.0f*itxsize, 1.0f*itysize);
			_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);


			v.position = vec3(0.5f*ixsize, 0.0f, 0.5f*izsize);
			v.normal = vec3(0.0f, 1.0f, 0.0f);
			v.texCoord = vec2(0.0f, 1.0f*itysize);
			_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);

			v.position = vec3(0.5f*ixsize, 0.0f, -0.5f*izsize);
			v.normal = vec3(0.0f, 1.0f, 0.0f);
			v.texCoord = vec2(0.0f, 0.0f);
			_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);

			v.position = vec3(-0.5f*ixsize, 0.0f, -0.5f*izsize);
			v.normal = vec3(0.0f, 1.0f, 0.0f);
			v.texCoord = vec2(1.0f*itxsize, 0.0f);
			_mesh.CB_DATA_MESHBUILDER_ADD_VERTEX(v);

			uint32 q[4] = {
				0, 1, 2, 3
			};
			_mesh._quads.insert(_mesh._quads.end(), q, q + 4);
		}
	}  // namespace data
}  // namespace cb
