/* 
 * - Cumulonimbus - ☁
 * File: dMFile.cpp
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

#include <vector>

#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/positioning.hpp>

namespace io = boost::iostreams;

namespace cb {
	namespace data {
		class MDevice {
		private:
			std::vector<char> _data;
			size_t _position;

		public:
			typedef char char_type;
			typedef io::seekable_device_tag category;

			MDevice(const char *idata, size_t isize) : _data(idata, idata+isize), _position(0) {}

			std::streamsize read(char* s, std::streamsize n) {
				size_t i;
				std::streamsize j=0;
				for(; _position<_data.size() && j<n ; _position++,j++) {
					s[j] = _data[_position];
				}

				return j!=0?j:-1;
			}

			std::streamsize write(const char* s, std::streamsize n)
			{
				size_t i;
				std::streamsize j;
				for(i=_position,j=0; i<_data.size() && j<n ; i++,j++) {
					_data[i] = s[j];
				}
				if(j < n) {
					_data.insert(_data.end(), s+j, s+n);
				}

				return n;
			}

			io::stream_offset seek(io::stream_offset off, std::ios_base::seekdir way) {
				if(way == std::ios_base::beg) {
					_position = (size_t)off;
				} else if(way == std::ios_base::cur) {
					_position = _position + (size_t)off;
				} else if(way == std::ios_base::end) {
					_position = _data.size() - (size_t)off;
				}

				if(_position > _data.size()) {
					_position = _data.size();
				}

				return _position;
			}

			const char *data() const {return _data.data();}
			size_t size() const {return _data.size();}
		};

		typedef io::stream_buffer<MDevice>	MStreamBuf;

		KinKey(FileMemoryDevice, MDevice);
		KinKeyErase(FileMemoryDevice, MDevice);
		KinKey(FileMemoryStreamBuf, MStreamBuf);
		KinKeyErase(FileMemoryStreamBuf, MStreamBuf);

		//MFile -------------------------------------------------------------

		MFile::MFile() :iostream(nullptr) {
			_stream_buf << new MStreamBuf();
		}

		MFile::MFile(const base::string &ifilename) :iostream(nullptr) {
			_stream_buf << new MStreamBuf();
			open(ifilename);
		}

		MFile::MFile(const char *idata, size_t isize) :iostream(nullptr) {
			_stream_buf << new MStreamBuf();
			open(idata, isize);
		}

		MFile::~MFile() {
			close();
			rdbuf(NULL);
			kin::erase(_stream_buf);
		}

		bool MFile::open(const base::string &ifilename) {
			close();

			iFile file(ifilename);
			if(!file.isOpen()) {
				return false;
			}

			file.seekg(0, std::ios::end);
			std::streamsize size = file.tellg();

			char *data = new char[size];

			file.seekg(0, std::ios::beg);
			file.read(data, size);

			if(file.gcount() != size) {
				delete [] data;
				return false;
			}

			bool ret = open(data, size);
			delete [] data;
			return ret;
		}

		bool MFile::open(const char *idata, size_t isize) {
			close();
			_mdevice << new MDevice(idata, isize);
			(*_stream_buf).open(*_mdevice);
			rdbuf(&_stream_buf);

			return true;
		}

		bool MFile::isOpen() {
			return (*_stream_buf).is_open();
		}

		void MFile::close() {
			if((*_stream_buf).is_open()) {
				(*_stream_buf).close();
				_mdevice << nullptr;
				rdbuf(nullptr);
			}
		}

		const char *MFile::data() const {
			return kin::pt(_mdevice)->data();
		}

		size_t MFile::size() const {
			return kin::pt(_mdevice)->size();
		}
	}  // namespace data
}  // namespace cb
