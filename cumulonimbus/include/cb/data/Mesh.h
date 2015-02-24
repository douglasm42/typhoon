/* 
 * - Cumulonimbus - ☁
 * Mesh: Mesh.h
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
#include <cb/data/data.h>

#include <cb/data/File.h>
#include <cb/base/Exception.h>
#include <cb/math/math.h>

#include <vector>

namespace cb {
	namespace data {
		namespace mesh {
			enum class Type {
				Bool,
				Int,
				Float,
				Double
			};
		}  // namespace mesh

		//------------------------------------------------------------------------------
		// - Mesh -
		//------------------------------------------------------------------------------

		class CbAPI Mesh {
		public:
			class CbAPI Format;

			//------------------------------------------------------------------------------
			// - Mesh::Attribute - definition -
			//------------------------------------------------------------------------------

			class CbAPI Attribute {
			private:
				static const size_t _size[];
				static const size_t _components[];

			public:
				base::string name;
				mesh::Type type;
				size_t components;
				size_t offset;

				Attribute(base::string iname, mesh::Type itype, size_t components, size_t ioffset);
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
				Format(size_t iattributes);
				Format(const Format &iformat);
				~Format();

				void add(base::string iname, mesh::Type itype, size_t icomponents);

				const std::vector<Attribute> &attr() const;

				size_t size() const;

				Format &operator=(const Format &iformat);
				bool operator==(const Format &iformat) const;

				friend class CbAPI Mesh;
			};

			//------------------------------------------------------------------------------
			// - Mesh - definition -
			//------------------------------------------------------------------------------

		private:
			std::vector<uint8> _vertices;

			Format _format;

			std::vector<uint32> _quads;
			std::vector<uint32> _triangles;
			std::vector<uint32> _lines;
			std::vector<uint32> _points;

		public:
			Mesh(const Format &iformat);
			Mesh(const File &ifile);
			Mesh(const Mesh &imesh);
			virtual ~Mesh();

			void load(const Format &iformat);
			void load(const File &isize);
			void load(const Mesh &imesh);

			File &save() const;
			void save(File &) const;

			void append(const File &isize);
			void append(const Mesh &imesh);

			void clear();

			void *vertex(uint32 iindex);
			const void *vertex(uint32 iindex) const;

			const Format &format() const;

			void vertex(void *ivertex);

			void quad(uint32 iindex1, uint32 iindex2, uint32 iindex3, uint32 iindex4);
			void tri(uint32 iindex1, uint32 iindex2, uint32 iindex3);
			void line(uint32 iindex1, uint32 iindex2);

			void sphere(float iradius, uint32 irings, uint32 isectors);
			void dome(float iradius, uint32 irings, uint32 isectors, float ifraction);
			void box(float ixsize, float iysize, float izsize);
			void plane(float ixsize, float izsize, float itxsize, float itysize);

			const std::vector<uint8> &vertices() const;

			const std::vector<uint32> &quads() const;
			const std::vector<uint32> &triangles() const;
			const std::vector<uint32> &lines() const;
			const std::vector<uint32> &points() const;
		};
		
		//------------------------------------------------------------------------------
		// - inline Mesh::Attribute -
		//------------------------------------------------------------------------------

		inline Mesh::Attribute::Attribute(base::string iname, mesh::Type itype, size_t icomponents, size_t ioffset) :name(iname), type(itype), components(icomponents), offset(ioffset) {}
		inline Mesh::Attribute::Attribute(const Attribute &iattr) : name(iattr.name), type(iattr.type), components(iattr.components), offset(iattr.offset) {}
		inline Mesh::Attribute::~Attribute() {}

		inline size_t Mesh::Attribute::size() const { return _size[(size_t)type]; }

		inline Mesh::Attribute &Mesh::Attribute::operator=(const Attribute &iattr) {
			name = iattr.name;
			type = iattr.type;
			components = iattr.components;
			offset = iattr.offset;
			return *this;
		}

		inline bool Mesh::Attribute::operator==(const Attribute &iattr) const {
			return iattr.name == name && iattr.type == type && iattr.components == components && iattr.offset == offset;
		}

		//------------------------------------------------------------------------------
		// - inline Mesh::Format -
		//------------------------------------------------------------------------------

		inline Mesh::Format::Format() {}
		inline Mesh::Format::Format(size_t iattributes) {}
		inline Mesh::Format::Format(const Format &iformat) {}
		inline Mesh::Format::~Format() {}

		inline void Mesh::Format::add(base::string iname, mesh::Type itype, size_t icomponents) {
			std::vector<Attribute>::iterator it;
			for(it = _attributes.begin(); it != _attributes.end(); ++it) {
				if(it->name == iname) {
					Throw(tokurei::SetFailed);
				}
			}

			_attributes.push_back(Attribute(iname, itype, icomponents, _size));
			_size += _attributes[_attributes.size() - 1].size();
		}
		
		const std::vector<Mesh::Attribute> &Mesh::Format::attr() const {
			return _attributes;
		}

		inline Mesh::Format &Mesh::Format::operator=(const Format &iformat) {
			_size = iformat._size;
			_attributes.clear();
			_attributes.insert(_attributes.begin(), iformat._attributes.begin(), iformat._attributes.end());
		}

		inline bool Mesh::Format::operator==(const Format &iformat) const {
			if(_size == iformat._size && _attributes.size() == iformat.size()) {
				std::vector<Attribute>::const_iterator it, it_iformat;
				std::equal(_attributes.begin(), _attributes.end(), iformat._attributes.begin());
			} else {
				return false;
			}
		}

		//------------------------------------------------------------------------------
		// - inline Mesh -
		//------------------------------------------------------------------------------

		inline Mesh::Mesh(const Format &iformat)	{load(iformat);}
		inline Mesh::Mesh(const File &ifile)		{load(ifile);}
		inline Mesh::Mesh(const Mesh &imesh)		{load(imesh);}
		inline Mesh::~Mesh() { clear(); }

		inline void Mesh::clear() {
			_format = Format();
			_vertices.clear();
			_quads.clear();
			_triangles.clear();
			_lines.clear();
		}

		inline const Mesh::Format &Mesh::format() const {
			return _format;
		}

		inline const std::vector<uint8> &Mesh::vertices() const {
			return _vertices;
		}

		inline const std::vector<uint32> &Mesh::quads() const {
			return _quads;
		}

		inline const std::vector<uint32> &Mesh::triangles() const {
			return _triangles;
		}

		inline const std::vector<uint32> &Mesh::lines() const {
			return _lines;
		}

		inline const std::vector<uint32> &Mesh::points() const {
			return _points;
		}
	}  // namespace data
}  // namespace cb
