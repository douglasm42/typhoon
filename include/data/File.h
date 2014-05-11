/* 
 * - Cumulonimbus - ☁
 * File: File.h
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

#include <data/data.h>

#include <base/String.h>
#include <base/Kin.h>

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
			void init(const base::string &argv0);
			void writedir(const base::string &idirectory);
			void mount(const base::string &idirectory, const base::string &imountpoint);
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
			iFile(const base::string &ifilename);
			virtual ~iFile();

			bool open(const base::string &ifilename);
			bool isOpen();
			void close();
		};

		class CbAPI oFile : public ostream {
		private:
			kin::FileHandle _file_handle;
			kin::FilePhysFSOStreamBuf _stream_buf;

		public:
			oFile();
			oFile(const base::string &ifilename, bool iappend = false);
			virtual ~oFile();

			bool open(const base::string &ifilename, bool iappend = false);
			bool isOpen();
			void close();
		};

		class CbAPI MFile : public iostream {
		private:
			kin::FileMemoryDevice _mdevice;
			kin::FileMemoryStreamBuf _stream_buf;

		public:
			MFile();
			MFile(const base::string &ifilename);
			MFile(const char *idata, size_t isize);
			MFile(const MFile &imfile) :iostream(nullptr) {open(imfile.data(), imfile.size());}
			virtual ~MFile();

			bool open(const base::string &ifilename);
			bool open(const char *idata, size_t isize);
			bool isOpen();
			void close();

			const char *data() const;
			size_t size() const;
		};
	}  // namespace data
}  // namespace cb
