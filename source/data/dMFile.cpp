/*
 * dFile.cpp
 *
 *  Created on: Feb 23, 2014
 *      Author: douglas
 */

#include <data/dFile.h>

#include <base/bLog.h>

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
					_position = off;
				} else if(way == std::ios_base::cur) {
					_position = _position + off;
				} else if(way == std::ios_base::end) {
					_position = _data.size() - off;
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
		KinKey(FileMemoryStreamBuf, MStreamBuf);

		//iMFile -------------------------------------------------------------

		iMFile::iMFile() {
			_stream_buf << new MStreamBuf();
		}

		iMFile::iMFile(string ifilename) {
			_stream_buf << new MStreamBuf();
			open(ifilename);
		}

		iMFile::iMFile(const char *idata, size_t isize) {
			_stream_buf << new MStreamBuf();
			open(idata, isize);
		}

		iMFile::~iMFile() {
			close();
			rdbuf(nullptr);
			kin::erase(_stream_buf);
		}

		bool iMFile::open(string ifilename) {
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

		bool iMFile::open(const char *idata, size_t isize) {
			close();
			_mdevice << new MDevice(idata, isize);
			(*_stream_buf).open(*_mdevice);

			rdbuf(&_stream_buf);
			return true;
		}

		bool iMFile::isOpen() {
			return (*_stream_buf).is_open();
		}

		void iMFile::close() {
			if((*_stream_buf).is_open()) {
				(*_stream_buf).close();
				_mdevice << nullptr;
				rdbuf(nullptr);
			}
		}

		const char *iMFile::data() const {
			return kin::pt(_mdevice)->data();
		}

		size_t iMFile::size() const {
			return kin::pt(_mdevice)->size();
		}

		//oMFile -------------------------------------------------------------

		oMFile::oMFile() {
			_stream_buf << new MStreamBuf();
		}

		oMFile::oMFile(string ifilename) {
			_stream_buf << new MStreamBuf();
			open(ifilename);
		}

		oMFile::oMFile(const char *idata, size_t isize) {
			_stream_buf << new MStreamBuf();
			open(idata, isize);
		}

		oMFile::~oMFile() {
			close();
			rdbuf(nullptr);
			kin::erase(_stream_buf);
		}

		bool oMFile::open(string ifilename) {
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

		bool oMFile::open(const char *idata, size_t isize) {
			close();
			_mdevice << new MDevice(idata, isize);
			(*_stream_buf).open(*_mdevice);
			rdbuf(&_stream_buf);

			return true;
		}

		bool oMFile::isOpen() {
			return (*_stream_buf).is_open();
		}

		void oMFile::close() {
			if((*_stream_buf).is_open()) {
				(*_stream_buf).close();
				_mdevice << nullptr;
				rdbuf(nullptr);
			}
		}

		const char *oMFile::data() const {
			return kin::pt(_mdevice)->data();
		}

		size_t oMFile::size() const {
			return kin::pt(_mdevice)->size();
		}

		//MFile -------------------------------------------------------------

		MFile::MFile() {
			_stream_buf << new MStreamBuf();
		}

		MFile::MFile(string ifilename) {
			_stream_buf << new MStreamBuf();
			open(ifilename);
		}

		MFile::MFile(const char *idata, size_t isize) {
			_stream_buf << new MStreamBuf();
			open(idata, isize);
		}

		MFile::~MFile() {
			close();
			rdbuf(NULL);
			kin::erase(_stream_buf);
		}

		bool MFile::open(string ifilename) {
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
