/*
 * - Cumulonimbus - ☁
 * File: cb/data/inl/Blob.inl
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
#include <cb/data/Blob.hpp>

#include <cstring>

namespace cb {
	namespace data {
		inline Blob::Blob()
		:_data(nullptr)
		,_capacity(0)
		,_size(0)
		,_get(0)
		,_put(0) {
		}

		inline Blob::Blob(size_t icapacity)
		:_data(nullptr)
		,_capacity(0)
		,_size(0)
		,_get(0)
		,_put(0) {
			load(icapacity);
		}

		inline Blob::Blob(const base::string &ifilename)
		:_data(nullptr)
		,_capacity(0)
		,_size(0)
		,_get(0)
		,_put(0) {
			load(ifilename);
		}

		inline Blob::Blob(const char *idata, size_t isize)
		:_data(nullptr)
		,_capacity(0)
		,_size(0)
		,_get(0)
		,_put(0) {
			load(idata, isize);
		}

		inline Blob::Blob(char *idata, size_t icapacity, size_t isize)
		:_data(nullptr)
		,_capacity(0)
		,_size(0)
		,_get(0)
		,_put(0) {
			load(idata, icapacity, isize);
		}

		inline Blob::Blob(const Blob &ifile)
		:_data(nullptr)
		,_capacity(0)
		,_size(0)
		,_get(0)
		,_put(0) {
			load(ifile);
		}

		inline Blob::~Blob() {
			clear();
		}

		inline void Blob::clear() {
			if(_data) {
				delete[] _data;
				_data = nullptr;
				_capacity = 0;
				_size = 0;
				_get = 0;
				_put = 0;
			}
		}

		inline char *Blob::data() { return _data; }
		inline const char *Blob::data() const { return _data; }
		inline size_t Blob::capacity() const { return _capacity; }
		inline size_t Blob::size() const { return _size; }

		inline char &Blob::operator[](size_t iposition) {
			Assert(iposition<_size, tokurei::OutOfRange);
			return _data[iposition];
		}
		inline const char &Blob::operator[](size_t iposition) const {
			Assert(iposition<_size, tokurei::OutOfRange);
			return _data[iposition];
		}

		//------------------------------------------------------------------------------
		// - Output -
		//------------------------------------------------------------------------------

		inline size_t Blob::tellp() const {
			return _put;
		}

		inline void Blob::seekp(size_t ipos) {
			_put = ipos;
		}

		inline void Blob::seekp(size_t ioffset, rdata::SeekDir idir) {
			if(idir == rdata::SeekDir::Cur) {
				_put += ioffset;
			} else if(idir == rdata::SeekDir::End) {
				if(ioffset < _size) {
					_put = _size - ioffset;
				} else {
					_put = 0;
				}
			} else if(idir == rdata::SeekDir::Beg) {
				_put = ioffset;
			}

			if(_put >= _size) {
				_put = _size;
			}
		}

		//------------------------------------------------------------------------------
		// - Output templates -
		//------------------------------------------------------------------------------

		template<class T>
		inline void Blob::put(const T &ivalue) {
			size_t new_size = _put + sizeof(T);

			CriticAssert(_put + sizeof(T) <= _capacity, tokurei::OutOfMemory);
			memcpy(_data + _put, reinterpret_cast<const void*>(&ivalue), sizeof(T));
			_put += sizeof(T);
			_size = max(_size, _put);
		}

		template<class T>
		inline void Blob::write(const T *ivalue, size_t in) {
			CriticAssert(_put + in * sizeof(T) <= _capacity, tokurei::OutOfMemory);
			memcpy(_data + _put, reinterpret_cast<const void*>(ivalue), in * sizeof(T));
			_put += in * sizeof(T);
			_size = max(_size, _put);
		}

		template<class T>
		inline Blob &Blob::operator<<(const T &ivalue) {
			put(ivalue);
			return *this;
		}
		
		//------------------------------------------------------------------------------
		// - Output templates - base::string -
		//------------------------------------------------------------------------------

		template<>
		inline void Blob::put(const base::string &ivalue) {
			CriticAssert(_put + ivalue.size() + 1 <= _capacity, tokurei::OutOfMemory);
			memcpy(_data + _put, reinterpret_cast<const void*>(ivalue.c_str()), ivalue.size() + 1);
			_put += ivalue.size() + 1;
			_size = max(_size, _put);
		}

		template<>
		inline void Blob::write(const base::string *ivalue, size_t in) {
			size_t size_sum = 0;
			for(size_t i = 0; i < in; i++) {
				size_sum = ivalue[i].size() + 1;
			}
			CriticAssert(_put + size_sum <= _capacity, tokurei::OutOfMemory);
			for(size_t i = 0; i < in; i++) {
				memcpy(_data + _put, reinterpret_cast<const void*>(ivalue[i].c_str()), ivalue[i].size() + 1);
				_put += ivalue[i].size() + 1;
			}
			_size = max(_size, _put);
		}

		//------------------------------------------------------------------------------
		// - Input -
		//------------------------------------------------------------------------------

		inline bool Blob::eof() {
			return _size == _get;
		}

		inline size_t Blob::tellg() const {
			return _get;
		}
		inline void Blob::seekg(size_t ipos) {
			_get = ipos;
		}
		inline void Blob::seekg(size_t ioffset, rdata::SeekDir idir) {
			if(idir == rdata::SeekDir::Cur) {
				_get += ioffset;
			} else if(idir == rdata::SeekDir::End) {
				if(ioffset < _size) {
					_get = _size - ioffset;
				} else {
					_get = 0;
				}
			} else if(idir == rdata::SeekDir::Beg) {
				_get = ioffset;
			}

			if(_get >= _size) {
				_get = _size;
			}
		}

		//------------------------------------------------------------------------------
		// - Input templates -
		//------------------------------------------------------------------------------

		template<class T>
		inline void Blob::get(T &ivalue) {
			CriticAssert(_get + sizeof(T) <= _size, tokurei::OutOfMemory);
			memcpy(reinterpret_cast<void*>(&ivalue), _data + _get, sizeof(T));
			_get += sizeof(T);
		}

		template<class T>
		inline void Blob::read(T *ivalue, size_t in) {
			CriticAssert(_get + in * sizeof(T) <= _size, tokurei::OutOfMemory);
			memcpy(reinterpret_cast<void*>(ivalue), _data + _get, in * sizeof(T));
			_get += in * sizeof(T);
		}

		template<class T>
		inline Blob &Blob::operator>>(T &ivalue) {
			get(ivalue);
			return *this;
		}

		//------------------------------------------------------------------------------
		// - Output templates - base::string -
		//------------------------------------------------------------------------------
		template<>
		inline void Blob::get(base::string &ivalue) {
			size_t end = _get;
			while(end < _size && _data[end] != char(0)) {
				end++;
			}
			CriticAssert(end < _size && _data[end] == 0, tokurei::OutOfMemory);
			ivalue = (_data + _get);

			_get += ivalue.size() + 1;
		}

		template<>
		inline void Blob::read(base::string *ivalue, size_t in) {
			size_t end = _get;
			for(size_t i = 0; i < in; i++) {
				while(end < _size && _data[end] != char(0)) {
					end++;
				}
				CriticAssert(end < _size && _data[end] == 0, tokurei::OutOfMemory);
				end++;
			}
			
			for(size_t i = 0; i < in; i++) {
				ivalue[i] = (_data + _get);
				_get += ivalue[i].size() + 1;
			}
		}
	}  // namespace data
}  // namespace cb
