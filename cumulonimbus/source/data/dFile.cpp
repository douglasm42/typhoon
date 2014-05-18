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

#include <physfs.h>

#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/positioning.hpp>

namespace io = boost::iostreams;

namespace cb {
	namespace data {
		namespace file {
			void init(const base::string &argv0) {
				PHYSFS_init(argv0.c_str());
			}

			void writedir(const base::string &idirectory) {
				PHYSFS_setWriteDir(idirectory.c_str());
			}

			void mount(const base::string &idirectory, const base::string &imountpoint) {
				PHYSFS_mount(idirectory.c_str(), imountpoint.c_str(), true);
			}
		}  // namespace file

		KinKey(kin::FileHandle, PHYSFS_File)
		KinKeyErase(kin::FileHandle, PHYSFS_File)

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

		KinKey(kin::FilePhysFSIStreamBuf, PhysFSInputBuf);
		KinKeyErase(kin::FilePhysFSIStreamBuf, PhysFSInputBuf);
		KinKey(kin::FilePhysFSOStreamBuf, PhysFSOutputBuf);
		KinKeyErase(kin::FilePhysFSOStreamBuf, PhysFSOutputBuf);

		//iFileFS -------------------------------------------------------------

		iFile::iFile() :istream(nullptr) {
			_stream_buf << new PhysFSInputBuf();
			rdbuf(&_stream_buf);
		}
		iFile::iFile(const base::string &ifilename) :istream(nullptr) {
			_stream_buf << new PhysFSInputBuf();
			rdbuf(&_stream_buf);
			open(ifilename);
		}
		iFile::~iFile() {
			close();
			rdbuf(NULL);
			kin::erase(_stream_buf);
		}

		bool iFile::open(const base::string &ifilename) {
			close();
			_file_handle << PHYSFS_openRead(ifilename.c_str());
			if(_file_handle.empty()) {
				base::log.warning("iFile::open() : Não foi possivel abrir o arquivo '%s': %s", ifilename.c_str(), PHYSFS_getLastError());
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

		oFile::oFile() :ostream(nullptr) {
			_stream_buf << new PhysFSOutputBuf();
			rdbuf(&_stream_buf);
		}

		oFile::oFile(const base::string &ifilename, bool iappend) :ostream(nullptr) {
			_stream_buf << new PhysFSOutputBuf();
			rdbuf(&_stream_buf);
			open(ifilename, iappend);
		}

		oFile::~oFile() {
			close();
			rdbuf(NULL);
			kin::erase(_stream_buf);
		}

		bool oFile::open(const base::string &ifilename, bool iappend) {
			close();
			if(iappend) {
				_file_handle << PHYSFS_openAppend(ifilename.c_str());
			} else {
				_file_handle << PHYSFS_openWrite(ifilename.c_str());
			}
			if(_file_handle.empty()) {
				base::log.info("Não foi possivel abrir o arquivo '%s': %s", ifilename.c_str(), PHYSFS_getLastError());
				return false;
			}
			(*_stream_buf).open(*(new PhysFSSink(&_file_handle)));
			rdbuf(&_stream_buf);

			seekp(0, std::ios::end);

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
