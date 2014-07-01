/* 
 * - Cumulonimbus - ☁
 * File: File.h
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

#include <data/data.h>

#include <base/String.h>
#include <base/Kin.h>

#include <base/Exception.h>

namespace cb {
	namespace data {
		class CbAPI File {
		private:
			char *_data;

			size_t _capacity;
			size_t _size;

		public:
			File();
			File(size_t icapacity);
			File(const base::string &ifilename);
			File(const char *idata, size_t isize);
			File(char *idata, size_t icapacity, size_t isize);
			File(const File &ifile);
			~File();

			void load(size_t icapacity);
			void load(const base::string &ifilename);
			void load(const char *idata, size_t isize);
			void load(char *idata, size_t icapacity, size_t isize);
			void load(const File &ifile);

			void save(const base::string &ifilename);

			void append(const base::string &ifilename);
			void append(const char *idata, size_t isize);
			void append(const File &ifile);

			void clear();

			char *data();
			const char *data() const;

			size_t capacity() const;
			void capacity(size_t icapacity);

			size_t size() const;
			void size(size_t isize);

			char &operator[](size_t iposition);
			const char &operator[](size_t iposition) const;
		};

		inline File::File()												: _data(nullptr), _capacity(0), _size(0) {}
		inline File::File(size_t icapacity)								: _data(nullptr), _capacity(0), _size(0) {load(icapacity);}
		inline File::File(const base::string &ifilename)				: _data(nullptr), _capacity(0), _size(0) {load(ifilename);}
		inline File::File(const char *idata, size_t isize)				: _data(nullptr), _capacity(0), _size(0) {load(idata, isize);}
		inline File::File(char *idata, size_t icapacity, size_t isize)	: _data(nullptr), _capacity(0), _size(0) {load(idata, icapacity, isize);}
		inline File::File(const File &ifile)							: _data(nullptr), _capacity(0), _size(0) {load(ifile);}
		inline File::~File() { clear(); }

		inline void File::clear() {
			if(_data) {
				delete [] _data;
				_data = nullptr;
				_capacity = 0;
				_size = 0;
			}
		}

		inline char *File::data() { return _data; }
		inline const char *File::data() const { return _data; }
		inline size_t File::capacity() const { return _capacity; }
		inline size_t File::size() const { return _size; }

		inline char &File::operator[](size_t iposition) {
			Assert(iposition<_size,tokurei::OutOfRange);
			return _data[iposition];
		}
		inline const char &File::operator[](size_t iposition) const {
			Assert(iposition<_size,tokurei::OutOfRange);
			return _data[iposition];
		}
	}  // namespace data
}  // namespace cb
