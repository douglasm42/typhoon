/*
 * - Cumulonimbus - ☁
 * File: cb/data/inl/Mesh.inl
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
#include <cb/data/Mesh.hpp>

namespace cb {
	namespace data {
		//------------------------------------------------------------------------------
		// - inline Mesh::Attribute -
		//------------------------------------------------------------------------------

		inline mesh::Attribute::Attribute(base::string iname, mesh::Type itype, size_t icomponents, size_t ioffset)
		:name(iname)
		,type(itype)
		,components(icomponents)
		,offset(ioffset) {
		}

		inline mesh::Attribute::Attribute(const Attribute &iattr)
		:name(iattr.name)
		,type(iattr.type)
		,components(iattr.components)
		,offset(iattr.offset) {
		}

		inline mesh::Attribute::~Attribute() {
		}

		inline size_t mesh::Attribute::size() const {
			return _size[(size_t)type];
		}

		inline mesh::Attribute &mesh::Attribute::operator=(const Attribute &iattr) {
			name = iattr.name;
			type = iattr.type;
			components = iattr.components;
			offset = iattr.offset;
			return *this;
		}

		inline bool mesh::Attribute::operator==(const Attribute &iattr) const {
			return iattr.name == name && iattr.type == type && iattr.components == components && iattr.offset == offset;
		}

		//------------------------------------------------------------------------------
		// - inline Mesh::Format -
		//------------------------------------------------------------------------------

		inline mesh::Format::Format()
		:_size(0)
		,_attributes() {
		}

		inline mesh::Format::Format(const Format &iformat)
		:_size(iformat.size())
		,_attributes(iformat._attributes) {
		}

		inline mesh::Format::~Format() {
		}

		inline void mesh::Format::add(base::string iname, mesh::Type itype, size_t icomponents) {
			for(auto at : _attributes) {
				if(at.name == iname) {
					Throw(tokurei::SetFailed);
				}
			}

			_attributes.push_back(Attribute(iname, itype, icomponents, _size));
			_size += _attributes[_attributes.size() - 1].size();
		}

		inline const std::vector<mesh::Attribute> &mesh::Format::attr() const {
			return _attributes;
		}

		inline size_t mesh::Format::size() const {
			return _size;
		}

		inline mesh::Format &mesh::Format::operator=(const Format &iformat) {
			_size = iformat._size;
			_attributes.clear();
			_attributes.insert(_attributes.begin(), iformat._attributes.begin(), iformat._attributes.end());

			return *this;
		}

		inline bool mesh::Format::operator==(const Format &iformat) const {
			if(_size == iformat._size && _attributes.size() == iformat.size()) {
				std::vector<Attribute>::const_iterator it, it_iformat;
				return std::equal(_attributes.begin(), _attributes.end(), iformat._attributes.begin());
			} else {
				return false;
			}
		}

		//------------------------------------------------------------------------------
		// - inline Mesh -
		//------------------------------------------------------------------------------

		inline Mesh::Mesh() { }
		inline Mesh::Mesh(const mesh::Format &iformat) { load(iformat); }
		inline Mesh::Mesh(const Mesh &imesh) { load(imesh); }
		inline Mesh::~Mesh() { clear(); }

		inline void Mesh::load(const mesh::Format &iformat) {
			clear();
			_format = iformat;
		}

		inline void Mesh::clear() {
			_format = mesh::Format();
			_vertices.clear();
			_quads.clear();
			_triangles.clear();
			_lines.clear();
		}

		inline const mesh::Format &Mesh::getFormat() const {
			return _format;
		}

		inline const std::vector<uint8> &Mesh::getVerticesData() const {
			return _vertices;
		}

		inline const std::vector<uint32> &Mesh::getQuadsData() const {
			return _quads;
		}

		inline const std::vector<uint32> &Mesh::getTrianglesData() const {
			return _triangles;
		}

		inline const std::vector<uint32> &Mesh::getLinesData() const {
			return _lines;
		}

		inline const std::vector<uint32> &Mesh::getPointsData() const {
			return _points;
		}
	}  // namespace data
}  // namespace cb
