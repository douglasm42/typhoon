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
				std::streamsize j;
				for(i=_position,j=0; i<_data.size() && j<n ; i++,j++) {
					s[j] = _data[i];
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

				return 0;
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

			const char *data() {return _data.data();}
			size_t size() {return _data.size();}
		};

		typedef io::stream_buffer<MDevice>	MStreamBuf;

		KinKey(FileMemoryStreamBuf, MStreamBuf);

		//iMFile -------------------------------------------------------------

		iMFile::iMFile() {
			_stream_buf << new MStreamBuf();
			rdbuf(&_stream_buf);
		}
		iMFile::iMFile(const char *idata, size_t isize) {
			_stream_buf << new MStreamBuf();
			rdbuf(&_stream_buf);
			open(idata, isize);
		}
		iMFile::~iMFile() {
			close();
			rdbuf(NULL);
			kin::erase(_stream_buf);
		}

		bool iMFile::open(const char *idata, size_t isize) {
			close();
			(*_stream_buf).open(*(new MDevice(idata, isize)));

			return true;
		}

		bool iMFile::isOpen() {
			return (*_stream_buf).is_open();
		}

		void iMFile::close() {
			if((*_stream_buf).is_open()) {
				(*_stream_buf).close();
			}
		}

		const char *iMFile::data() {
			return (*_stream_buf)->data();
		}

		size_t iMFile::size() {
			return (*_stream_buf)->size();
		}

		//oMFile -------------------------------------------------------------

		oMFile::oMFile() {
			_stream_buf << new MStreamBuf();
			rdbuf(&_stream_buf);
		}

		oMFile::oMFile(const char *idata, size_t isize) {
			_stream_buf << new MStreamBuf();
			rdbuf(&_stream_buf);
			open(idata, isize);
		}

		oMFile::~oMFile() {
			close();
			rdbuf(NULL);
			kin::erase(_stream_buf);
		}

		bool oMFile::open(const char *idata, size_t isize) {
			close();
			(*_stream_buf).open(*(new MDevice(idata, isize)));

			return true;
		}

		bool oMFile::isOpen() {
			return (*_stream_buf).is_open();
		}

		void oMFile::close() {
			if((*_stream_buf).is_open()) {
				(*_stream_buf).close();
			}
		}

		const char *oMFile::data() {
			return (*_stream_buf)->data();
		}

		size_t oMFile::size() {
			return (*_stream_buf)->size();
		}

		//MFile -------------------------------------------------------------

		MFile::MFile() {
			_stream_buf << new MStreamBuf();
			rdbuf(&_stream_buf);
		}

		MFile::MFile(const char *idata, size_t isize) {
			_stream_buf << new MStreamBuf();
			rdbuf(&_stream_buf);
			open(idata, isize);
		}

		MFile::~MFile() {
			close();
			rdbuf(NULL);
			kin::erase(_stream_buf);
		}

		bool MFile::open(const char *idata, size_t isize) {
			close();
			(*_stream_buf).open(*(new MDevice(idata, isize)));

			return true;
		}

		bool MFile::isOpen() {
			return (*_stream_buf).is_open();
		}

		void MFile::close() {
			if((*_stream_buf).is_open()) {
				(*_stream_buf).close();
			}
		}

		const char *MFile::data() {
			return (*_stream_buf)->data();
		}

		size_t MFile::size() {
			return (*_stream_buf)->size();
		}
	}  // namespace data
}  // namespace cb
