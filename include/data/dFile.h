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

		KinLock(FileMemoryStreamBuf);

		void initPhysFS(const char *argv0);

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
			oFile(string ifilename);
			virtual ~oFile();

			bool open(string ifilename);
			bool isOpen();
			void close();
		};

		class CbAPI iMFile : public istream {
		private:
			kin::FileMemoryStreamBuf _stream_buf;

		public:
			iMFile();
			iMFile(const char *idata, size_t isize);
			virtual ~iMFile();

			bool open(const char *idata, size_t isize);
			bool isOpen();
			void close();

			const char *data();
			size_t size();
		};

		class CbAPI oMFile : public ostream {
		private:
			kin::FileMemoryStreamBuf _stream_buf;

		public:
			oMFile();
			oMFile(const char *idata, size_t isize);
			virtual ~oMFile();

			bool open(const char *idata, size_t isize);
			bool isOpen();
			void close();

			const char *data();
			size_t size();
		};

		class CbAPI MFile : public iostream {
		private:
			kin::FileMemoryStreamBuf _stream_buf;

		public:
			MFile();
			MFile(const char *idata, size_t isize);
			virtual ~MFile();

			bool open(const char *idata, size_t isize);
			bool isOpen();
			void close();

			const char *data();
			size_t size();
		};
	}  // namespace data
}  // namespace cb
