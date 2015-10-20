/* 
 * - Cumulonimbus - ☁
 * Mesh: cb/data/Mesh.h
 * 
 * Licence:
 * ============================================================================
 * Copyright (C) Staff 42 Entertainment LTDA ME - All Rights Reserved
 * Unauthorized copying of this Mesh, via any medium is strictly prohibited
 * Proprietary and confidential
 * 
 * Written by Douglas Machado de Freitas <douglas@staff42.com>, May 2014
 * ============================================================================
 */
#pragma once
#include <cb/data/data.hpp>

#include <cb/data/Blob.hpp>
#include <cb/base/Exception.hpp>
#include <cb/math/math.hpp>

#include <vector>

namespace cb {
	namespace data {
		namespace mesh {
			enum class Type {
				Bool,
				Int,
				UInt,
				Float,
				Double
			};

			//------------------------------------------------------------------------------
			// - Mesh::Attribute - definition -
			//------------------------------------------------------------------------------

			class CbAPI Attribute {
			private:
				static const size_t _size[];

			public:
				base::string name;
				Type type;
				size_t components;
				size_t offset;

				Attribute(base::string iname, Type itype, size_t components, size_t ioffset);
				Attribute(const Attribute &iattr);
				~Attribute();

				size_t size() const;

				Attribute &operator=(const Attribute &iattr);
				bool operator==(const Attribute &iattr) const;
			};

			//------------------------------------------------------------------------------
			// - Mesh::Format - definition -
			//------------------------------------------------------------------------------

			class CbAPI Format {
			private:
				size_t _size;
				std::vector<Attribute> _attributes;

			public:
				Format();
				Format(const Format &iformat);
				~Format();

				void add(base::string iname, Type itype, size_t icomponents);

				const std::vector<Attribute> &attr() const;

				size_t size() const;

				Format &operator=(const Format &iformat);
				bool operator==(const Format &iformat) const;

				friend class CbAPI Mesh;
			};

		}  // namespace mesh

		//------------------------------------------------------------------------------
		// - Mesh -
		//------------------------------------------------------------------------------

		class CbAPI Mesh {
		private:
			std::vector<uint8> _vertices;

			mesh::Format _format;

			std::vector<uint32> _quads;
			std::vector<uint32> _triangles;
			std::vector<uint32> _lines;
			std::vector<uint32> _points;

		public:
			Mesh();
			Mesh(const mesh::Format &iformat);
			Mesh(const Mesh &imesh);
			virtual ~Mesh();

			void load(const mesh::Format &iformat);
			void load(const Mesh &imesh);

			void append(const Mesh &imesh);

			void clear();
			void compact();

			const mesh::Format &getFormat() const;

			const std::vector<uint8> &getVerticesData() const;

			const std::vector<uint32> &getQuadsData() const;
			const std::vector<uint32> &getTrianglesData() const;
			const std::vector<uint32> &getLinesData() const;
			const std::vector<uint32> &getPointsData() const;

			void load(Blob &ifile);
			void save(Blob &ifile) const;

			friend class CbAPI MeshBuilder;
		};
	}  // namespace data
}  // namespace cb

#include <cb/data/inl/Mesh.inl>
