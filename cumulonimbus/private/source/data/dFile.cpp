/* 
 * - Cumulonimbus - ☁
 * File: dFile.cpp
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
#include <data/File.h>

#include <base/Log.h>
#include <base/Exception.h>

#include <fstream>
#include <new>

namespace cb {
	namespace data {
		void File::load(size_t icapacity) {
			if(_data) {clear();}

			_data = new (std::nothrow) char[icapacity];
			if(!_data) {
				Throw(tokurei::OutOfMemory);
			}

			_capacity = icapacity;
			_size = 0;
		}

		void File::load(const base::string &ifilename) {
			if(_data) {clear();}

			std::ifstream in(ifilename.c_str(), std::ios::binary);
			if(in.is_open()) {
				in.seekg (0, in.end);
				_size = _capacity = in.tellg();
				in.seekg (0, in.beg);

				_data = new char[_capacity];

				in.read(_data,_size);

			} else {
				ThrowDet(tokurei::OpenError, "Could not open file: %s", ifilename.c_str());
			}
		}

		void File::load(const char *idata, size_t isize) {
			if(_data) {clear();}

			_data = new (std::nothrow) char[isize];
			if(!_data) {
				Throw(tokurei::OutOfMemory);
			}

			_capacity = isize;
			_size = isize;

			for(size_t i=0 ; i<_size ; i++) {
				_data[i] = idata[i];
			}
		}

		void File::load(char *idata, size_t icapacity, size_t isize) {
			if(_data) {clear();}

			_data = idata;
			_capacity = icapacity;
			_size = isize;
		}

		void File::load(const File &ifile) {
			if(_data) {clear();}

			_data = new (std::nothrow) char[ifile._capacity];
			if(!_data) {
				Throw(tokurei::OutOfMemory);
			}

			_capacity = ifile._capacity;
			_size = ifile._size;

			for(size_t i=0 ; i<_size ; i++) {
				_data[i] = ifile._data[i];
			}
		}

		void File::save(const base::string &ifilename) {
			std::ofstream out(ifilename.c_str(), std::ios::binary | std::ios::trunc);
			if(out.is_open()) {
				out.write(_data, (std::streamsize)_size);
			} else {
				ThrowDet(tokurei::OpenError, "Could not open file: %s", ifilename.c_str());
			}
		}

		void File::append(const base::string &ifilename) {
			std::ifstream in(ifilename.c_str(), std::ios::binary);
			if(in.is_open()) {
				in.seekg (0, in.end);
				size_t file_size = in.tellg();
				in.seekg (0, in.beg);

				if(_size + file_size > _capacity) {
					capacity(_size + file_size);
				}

				in.read(_data + _size, file_size);
				_size += file_size;

			} else {
				ThrowDet(tokurei::OpenError, "Could not open file: %s", ifilename.c_str());
			}
		}

		void File::append(const char *idata, size_t isize) {
			if(_size + isize > _capacity) {
				capacity(_size + isize);
			}

			for(size_t i=_size, j=0 ; j<isize ; i++, j++) {
				_data[i] = idata[j];
			}
			_size += isize;
		}

		void File::append(const File &ifile) {
			if(_size + ifile._size > _capacity) {
				capacity(_size + ifile._size);
			}

			for(size_t i=_size, j=0 ; j<ifile._size ; i++, j++) {
				_data[i] = ifile._data[j];
			}
			_size += ifile._size;
		}

		void File::capacity(size_t icapacity) {
			if(_capacity != icapacity) {
				char *new_data = new (std::nothrow) char[icapacity];
				if(!_data) {
					Throw(tokurei::OutOfMemory);
				}

				for(size_t i=0 ; i<_size ; i++) {
					new_data[i] = _data[i];
				}
				delete [] _data;
				_data = new_data;
				_capacity = icapacity;
			}
		}

		void File::size(size_t isize) {
			if(isize > _capacity) {
				capacity(isize);
			}
			_size = isize;
		}

	}  // namespace data
}  // namespace cb
