/*
 * dFile.h
 *
 *  Created on: 29/01/2014
 *      Author: Douglas
 */

#pragma once

#include <data/data.h>

#include <base/bString.h>

#include <istream>
#include <ostream>

#include <sstream>
#include <fstream>

namespace cb {
	namespace data {
		KinLock(FileHandle);
		KinLock(FilePhysFSIStreamBuf);
		KinLock(FilePhysFSOStreamBuf);

		KinLock(FileMemoryDevice);
		KinLock(FileMemoryStreamBuf);

		namespace file {
			void init(string argv0);
			void writedir(string idirectory);
			void mount(string idirectory, string imountpoint);
		}  // namespace file

		typedef std::istream istream;
		typedef std::ostream ostream;
		typedef std::iostream iostream;

		class CbAPI iFile : public istream {
		private:
			kin::FileHandle _file_handle;
			kin::FilePhysFSIStreamBuf _stream_buf;

		public:
			iFile();
			iFile(string ifilename);
			virtual ~iFile();

			bool open(string ifilename);
			bool isOpen();
			void close();
		};

		class CbAPI oFile : public ostream {
		private:
			kin::FileHandle _file_handle;
			kin::FilePhysFSOStreamBuf _stream_buf;

		public:
			oFile();
			oFile(string ifilename, bool iappend = false);
			virtual ~oFile();

			bool open(string ifilename, bool iappend = false);
			bool isOpen();
			void close();
		};

		class CbAPI iMFile : public istream {
		private:
			kin::FileMemoryDevice _mdevice;
			kin::FileMemoryStreamBuf _stream_buf;

		public:
			iMFile();
			iMFile(string ifilename);
			iMFile(const char *idata, size_t isize);
			iMFile(const iMFile &iimfile) {open(iimfile.data(), iimfile.size());}
			virtual ~iMFile();

			bool open(string ifilename);
			bool open(const char *idata, size_t isize);
			bool isOpen();
			void close();

			const char *data() const;
			size_t size() const;
		};

		class CbAPI oMFile : public ostream {
		private:
			kin::FileMemoryDevice _mdevice;
			kin::FileMemoryStreamBuf _stream_buf;

		public:
			oMFile();
			oMFile(string ifilename);
			oMFile(const char *idata, size_t isize);
			oMFile(const oMFile &iomfile) {open(iomfile.data(), iomfile.size());}
			virtual ~oMFile();

			bool open(string ifilename);
			bool open(const char *idata, size_t isize);
			bool isOpen();
			void close();

			const char *data() const;
			size_t size() const;
		};

		class CbAPI MFile : public iostream {
		private:
			kin::FileMemoryDevice _mdevice;
			kin::FileMemoryStreamBuf _stream_buf;

		public:
			MFile();
			MFile(string ifilename);
			MFile(const char *idata, size_t isize);
			MFile(const MFile &imfile) {open(imfile.data(), imfile.size());}
			virtual ~MFile();

			bool open(string ifilename);
			bool open(const char *idata, size_t isize);
			bool isOpen();
			void close();

			const char *data() const;
			size_t size() const;
		};
	}  // namespace data
}  // namespace cb
