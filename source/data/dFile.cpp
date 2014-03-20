/*
 * dFile.cpp
 *
 *  Created on: Feb 23, 2014
 *      Author: douglas
 */

#include <data/dFile.h>

#include <base/bLog.h>

#include <physfs.h>

#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/positioning.hpp>

namespace io = boost::iostreams;

namespace cb {
	namespace data {
		KinKey(FileHandle, PHYSFS_File)

		struct seekable_source_tag : io::device_tag, io::input_seekable { };
		struct seekable_sink_tag : io::device_tag, io::output_seekable { };

		class PhysFSSource {
		private:
			PHYSFS_File *_file;

		public:
			typedef char char_type;
			typedef struct seekable_source_tag category;

			PhysFSSource(PHYSFS_File *ifile) : _file(ifile) {}

			std::streamsize read(char* s, std::streamsize n) {
				std::streamsize result = PHYSFS_read(_file, s, sizeof(char_type), n);
				if(result == n) {
					return result;
				} else {
					if(PHYSFS_eof(_file)) {
						return result;
					} else {
						return -1;
					}
				}
			}

			io::stream_offset seek(io::stream_offset off, std::ios_base::seekdir way) {
				io::stream_offset pos = 0;
				if(way == std::ios_base::beg) {
					pos = off;
				} else if(way == std::ios_base::cur) {
					pos = PHYSFS_tell(_file) + off;
				} else if(way == std::ios_base::end) {
					pos = PHYSFS_fileLength(_file) - off;
				}

				PHYSFS_seek(_file, pos);
				return PHYSFS_tell(_file);
			}

			void setFile(PHYSFS_File *ifile) {_file = ifile;}
			PHYSFS_File *getFile() {return _file;}
		};

		class PhysFSSink {
		private:
			PHYSFS_File *_file;

		public:
			typedef char char_type;
			typedef struct seekable_sink_tag category;

			PhysFSSink(PHYSFS_File *ifile) : _file(ifile) {}
			~PhysFSSink() {}

			std::streamsize write(const char* s, std::streamsize n)
			{
				return PHYSFS_write(_file, s, sizeof(char_type), n);
			}

			io::stream_offset seek(io::stream_offset off, std::ios_base::seekdir way) {
				io::stream_offset pos = 0;
				if(way == std::ios_base::beg) {
					pos = off;
				} else if(way == std::ios_base::cur) {
					pos = PHYSFS_tell(_file) + off;
				} else if(way == std::ios_base::end) {
					pos = PHYSFS_fileLength(_file) - off;
				}

				PHYSFS_seek(_file, pos);
				return PHYSFS_tell(_file);
			}

			void setFile(PHYSFS_File *ifile) {_file = ifile;}
			PHYSFS_File *getFile() {return _file;}
		};

		typedef io::stream_buffer<PhysFSSource>	PhysFSInputBuf;
		typedef io::stream_buffer<PhysFSSink>	PhysFSOutputBuf;

		KinKey(FilePhysFSIStreamBuf, PhysFSInputBuf);
		KinKey(FilePhysFSOStreamBuf, PhysFSOutputBuf);

		void initPhysFS(const char *argv0) {
			PHYSFS_init(argv0);
			PHYSFS_setWriteDir(".");
			PHYSFS_mount(".", NULL, true);
		}

		//iFileFS -------------------------------------------------------------

		iFile::iFile() {
			_stream_buf << new PhysFSInputBuf();
			rdbuf(&_stream_buf);
		}
		iFile::iFile(string ifilename) {
			_stream_buf << new PhysFSInputBuf();
			rdbuf(&_stream_buf);
			open(ifilename);
		}
		iFile::~iFile() {
			close();
			rdbuf(NULL);
			kin::erase(_stream_buf);
		}

		bool iFile::open(string ifilename) {
			close();
			_file_handle << PHYSFS_openRead(ifilename.c_str());
			if(_file_handle.empty()) {
				base::log.info("Não foi possivel abrir o arquivo '%s': %s", ifilename.c_str(), PHYSFS_getLastError());
				return false;
			}
			(*_stream_buf).open(*(new PhysFSSource(&_file_handle)));
			rdbuf(&_stream_buf);

			return true;
		}

		bool iFile::isOpen() {
			return !_file_handle.empty() && (*_stream_buf).is_open();
		}

		void iFile::close() {
			if((*_stream_buf).is_open()) {
				(*_stream_buf).close();
			}
			if(!_file_handle.empty()) {
				PHYSFS_close(&_file_handle);
				_file_handle << NULL;
			}
		}

		//oFileFS -------------------------------------------------------------

		oFile::oFile() {
			_stream_buf << new PhysFSOutputBuf();
			rdbuf(&_stream_buf);
		}

		oFile::oFile(string ifilename) {
			_stream_buf << new PhysFSOutputBuf();
			rdbuf(&_stream_buf);
			open(ifilename);
		}

		oFile::~oFile() {
			close();
			rdbuf(NULL);
			kin::erase(_stream_buf);
		}

		bool oFile::open(string ifilename) {
			close();
			_file_handle << PHYSFS_openWrite(ifilename.c_str());
			if(_file_handle.empty()) {
				base::log.info("Não foi possivel abrir o arquivo '%s': %s", ifilename.c_str(), PHYSFS_getLastError());
				return false;
			}
			(*_stream_buf).open(*(new PhysFSSink(&_file_handle)));
			rdbuf(&_stream_buf);

			return true;
		}

		bool oFile::isOpen() {
			return !_file_handle.empty() && (*_stream_buf).is_open();
		}

		void oFile::close() {
			if((*_stream_buf).is_open()) {
				(*_stream_buf).close();
			}
			if(!_file_handle.empty()) {
				PHYSFS_close(&_file_handle);
				_file_handle << NULL;
			}
		}
	}  // namespace data
}  // namespace cb