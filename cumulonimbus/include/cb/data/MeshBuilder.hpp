/*
* - Cumulonimbus - ☁
* File: cb/data/MeshBuilder.h
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
#include <cb/data/data.hpp>

#include <cb/data/Mesh.hpp>

namespace cb {
	namespace data {
		namespace mesh {
			typedef struct {
				vec3 position;
				vec2 texCoord;
				vec3 normal;
				vec4 color;
			} BasicVertex;

			enum class Mode {
				Points,
				Lines,
				Triangles,
				Quads
			};
		}  // namespace mesh

		class MeshBuilder {
		private:
			mesh::Mode _mode;

			uint32 _missing_vertices;

			vec2 _tex_coord;
			vec3 _normal;
			vec4 _color;

			Mesh _mesh;

		public:
			MeshBuilder();
			~MeshBuilder();

			MeshBuilder &begin(mesh::Mode imode);

			MeshBuilder &texCoord(vec2 itex_coord);
			MeshBuilder &normal(vec3 inormal);
			MeshBuilder &color(vec4 icolor);
			MeshBuilder &vertex(vec3 iposition);

			void end();
			const Mesh &mesh() const;

			void sphere(float iradius, uint32 irings, uint32 isectors);
			void dome(float iradius, uint32 irings, uint32 isectors, float ifraction);
			void box(float ixsize, float iysize, float izsize);
			void plane(float ixsize, float izsize, float itxsize, float itysize);
		};
	}  // namespace data
}  // namespace cb
