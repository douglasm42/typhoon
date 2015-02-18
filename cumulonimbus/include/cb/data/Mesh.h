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
		class CbAPI Mesh {
		public:
			class CbAPI Channel {
			public:
				uint32 size;
				uint32 offset;
				void *byte_offset;

				Channel(uint32 isize, uint32 ioffset);
				Channel(const Channel &ichannel);
				~Channel();

				Channel operator=(const Channel &ichannel);
				bool operator==(const Channel &ichannel) const;
			};

			class CbAPI Format {
			public:
				uint32 stride;
				uint32 stride_byte;
				Channel position;
				Channel texcoord;
				Channel color;
				Channel normal;
				Channel tangent;

				Format();
				Format(uint32 iposition, uint32 itexcoord, uint32 icolor, uint32 inormal, uint32 itangent);
				Format(const Format &iformat);
				~Format();

				Format operator=(const Format &iformat);
				bool operator==(const Format &iformat) const;
			};

			class CbAPI Vertex {
			public:
				vec4 pos;
				vec4 tex;
				vec4 color;
				vec3 normal;
				vec3 tangent;
			};

		private:
			std::vector<float> _vertices;

			std::vector<uint32> _quads;
			std::vector<uint32> _triangles;
			std::vector<uint32> _lines;
			std::vector<uint32> _points;

			Format _format;

		public:
			Mesh(const Format &iformat);
			Mesh(const File &ifile);
			Mesh(const Mesh &imesh);
			~Mesh();

			void load(const Format &iformat);
			void load(const File &isize);
			void load(const Mesh &imesh);

			void append(const File &isize);
			void append(const Mesh &imesh);

			void clear();

			uint32 vertex(const Vertex &ivertex);
			uint32 uvertex(const Vertex &ivertex);
			void quad(uint32 iindex);
			void tri(uint32 iindex);
			void line(uint32 iindex);
			void point(uint32 iindex);

			void quad(uint32 iindex1, uint32 iindex2, uint32 iindex3, uint32 iindex4);
			void tri(uint32 iindex1, uint32 iindex2, uint32 iindex3);
			void line(uint32 iindex1, uint32 iindex2);

			void sphere(float iradius, uint32 irings, uint32 isectors);
			void dome(float iradius, uint32 irings, uint32 isectors, float ifraction);
			void box(float ixsize, float iysize, float izsize);
			void plane(float ixsize, float izsize, float itxsize, float itysize);

			const Format &format() const;

			const std::vector<float> &vertices() const;

			const std::vector<uint32> &quads() const;
			const std::vector<uint32> &triangles() const;
			const std::vector<uint32> &lines() const;
			const std::vector<uint32> &points() const;
		};

		inline Mesh::Channel::Channel(uint32 isize, uint32 ioffset) : size(isize), offset(ioffset), byte_offset(reinterpret_cast<void*>(sizeof(float)*ioffset)) {}
		inline Mesh::Channel::Channel(const Channel &ichannel) : size(ichannel.size), offset(ichannel.offset), byte_offset(ichannel.byte_offset) {}
		inline Mesh::Channel::~Channel() {}

		inline Mesh::Channel Mesh::Channel::operator=(const Channel &ichannel) {
			size = ichannel.size;
			offset = ichannel.offset;
			byte_offset = ichannel.byte_offset;
			return *this;
		}

		inline bool Mesh::Channel::operator==(const Channel &ichannel) const {
			return size == ichannel.size && offset == ichannel.offset && byte_offset == ichannel.byte_offset;
		}

		inline Mesh::Format::Format()
		:stride(0)
		,stride_byte(0)
		,position(0,0)
		,texcoord(0,0)
		,color(0,0)
		,normal(0,0)
		,tangent(0,0) {
		}

		inline Mesh::Format::Format(uint32 iposition, uint32 itexcoord, uint32 icolor, uint32 inormal, uint32 itangent)
		:stride(3 + itexcoord + icolor + inormal + itangent)
		,stride_byte(sizeof(float) * (3 + itexcoord + icolor + inormal + itangent))
		,position(iposition, 0)
		,texcoord(itexcoord,	iposition)
		,color(icolor,			iposition + itexcoord)
		,normal(inormal,		iposition + itexcoord + icolor)
		,tangent(itangent,		iposition + itexcoord + icolor + inormal) {
		}

		inline Mesh::Format::Format(const Format &iformat)
		:stride(iformat.stride)
		,stride_byte(iformat.stride_byte)
		,position(iformat.position)
		,texcoord(iformat.texcoord)
		,color(iformat.color)
		,normal(iformat.normal)
		,tangent(iformat.tangent) {
		}

		inline Mesh::Format::~Format() {}

		inline Mesh::Format Mesh::Format::operator=(const Mesh::Format &iformat) {
			stride = iformat.stride;
			stride_byte = iformat.stride_byte;
			position = iformat.position;
			texcoord = iformat.texcoord;
			color = iformat.color;
			normal = iformat.normal;
			tangent = iformat.tangent;
			return *this;
		}

		inline bool Mesh::Format::operator==(const Format &iformat) const {
			return stride == iformat.stride && stride_byte == iformat.stride_byte && position == iformat.position && texcoord == iformat.texcoord && color == iformat.color && normal == iformat.normal && tangent == iformat.tangent;
		}

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

		inline const std::vector<float> &Mesh::vertices() const {
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
