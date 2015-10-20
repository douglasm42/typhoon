/* 
 * - Cumulonimbus - ☁
 * File: dBlob.cpp
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
#include <cb/data/Blob.hpp>

#include <cb/base/Log.hpp>
#include <cb/base/Exception.hpp>

#include <fstream>
#include <new>

namespace cb {
	namespace data {
		void Blob::load(size_t icapacity) {
			clear();
			capacity(icapacity);
		}

		void Blob::load(const base::string &ifilename) {
			clear();

			std::ifstream in(ifilename.c_str(), std::ios::binary);
			if(in.is_open()) {
				in.seekg (0, in.end);
				size_t cap = in.tellg();
				in.seekg (0, in.beg);

				capacity(cap);
				_size = cap;
				_put = _size;

				in.read(_data,_size);
			} else {
				ThrowDet(tokurei::OpenError, "Could not open file: %s", ifilename.c_str());
			}
		}

		void Blob::load(const char *idata, size_t isize) {
			clear();
			capacity(isize);
			memcpy(_data, idata, _size);
		}

		void Blob::load(char *idata, size_t icapacity, size_t isize) {
			clear();

			_data = idata;
			_capacity = icapacity;
			_size = isize;

			_get = 0;
			_put = _size;
		}

		void Blob::load(const Blob &ifile) {
			clear();
			capacity(ifile._size);
			memcpy(_data, ifile._data, _size);
		}

		void Blob::save(const base::string &ifilename) {
			std::ofstream out(ifilename.c_str(), std::ios::binary | std::ios::trunc);
			if(out.is_open()) {
				out.write(_data, (std::streamsize)_size);
			} else {
				ThrowDet(tokurei::OpenError, "Could not open file: %s", ifilename.c_str());
			}
		}

		void Blob::append(const base::string &ifilename) {
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
				_put = _size;

			} else {
				ThrowDet(tokurei::OpenError, "Could not open file: %s", ifilename.c_str());
			}
		}

		void Blob::append(const char *idata, size_t isize) {
			if(_size + isize > _capacity) {
				capacity(_size + isize);
			}

			char *end = _data + _size;
			memcpy(end, idata, isize);

			_size += isize;
			_put = _size;
		}

		void Blob::append(const Blob &ifile) {
			if(_size + ifile._size > _capacity) {
				capacity(_size + ifile._size);
			}

			char *end = _data + _size;
			memcpy(end, ifile._data, ifile._size);

			_size += ifile._size;
			_put = _size;
		}

		void Blob::capacity(size_t icapacity) {
			if(_capacity != icapacity) {
				if(_data) {
					if(icapacity) {
						char *new_data = new (std::nothrow) char[icapacity];
						if(!_data) {
							Throw(tokurei::OutOfMemory);
						}

						memcpy(new_data, _data, _size);
						delete[] _data;
						_data = new_data;
						_capacity = icapacity;

						if(_capacity < _size) {
							_size = _capacity;
							if(_capacity < _get) {
								_get = _capacity;
							}
							if(_capacity < _put) {
								_put = _capacity;
							}
						}
					} else {
						clear();
					}
				} else {
					_data = new (std::nothrow) char[icapacity];
					if(!_data) {
						Throw(tokurei::OutOfMemory);
					}

					_capacity = icapacity;
					_size = 0;
					_get = 0;
					_put = 0;
				}
			}
		}

		void Blob::size(size_t isize) {
			if(isize > _capacity) {
				capacity(isize);
			}
			_size = isize;
		}

	}  // namespace data
}  // namespace cb
