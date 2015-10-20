/* 
 * - Cumulonimbus - ☁
 * File: cb/data/Blob.h
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

#include <cb/base/String.hpp>
#include <cb/base/Exception.hpp>

#include <cb/math/math.hpp>

namespace cb {
	namespace data {
		namespace rdata {
			enum class SeekDir {
				Beg,
				Cur,
				End
			};
		}  // namespace file

		class CbAPI Blob {
		private:
			char *_data;

			size_t _capacity;
			size_t _size;

			size_t _get;
			size_t _put;

		public:
			Blob();
			Blob(size_t icapacity);
			Blob(const base::string &ifilename);
			Blob(const char *idata, size_t isize);
			Blob(char *idata, size_t icapacity, size_t isize);
			Blob(const Blob &ifile);
			~Blob();

			void load(size_t icapacity);
			void load(const base::string &ifilename);
			void load(const char *idata, size_t isize);
			void load(char *idata, size_t icapacity, size_t isize);
			void load(const Blob &ifile);

			void save(const base::string &ifilename);

			void append(const base::string &ifilename);
			void append(const char *idata, size_t isize);
			void append(const Blob &ifile);

			void clear();

			char *data();
			const char *data() const;

			size_t capacity() const;
			void capacity(size_t icapacity);

			size_t size() const;
			void size(size_t isize);

			char &operator[](size_t iposition);
			const char &operator[](size_t iposition) const;

			//------------------------------------------------------------------------------
			// - Output -
			//------------------------------------------------------------------------------

			size_t tellp() const;
			void seekp(size_t ipos);
			void seekp(size_t ioffset, rdata::SeekDir idir);

			template<class T>
			void put(const T &ivalue);

			template<class T>
			void write(const T *ivalue, size_t in);

			template<class T>
			Blob &operator<<(const T &ivalue);

			//------------------------------------------------------------------------------
			// - Input -
			//------------------------------------------------------------------------------

			bool eof();

			size_t tellg() const;
			void seekg(size_t ipos);
			void seekg(size_t ioffset, rdata::SeekDir idir);

			template<class T>
			void get(T &ivalue);

			template<class T>
			void read(T *ivalue, size_t in);

			template<class T>
			Blob &operator>>(T &ivalue);
		};
	}  // namespace data
}  // namespace cb

#include <cb/data/inl/Blob.inl>
