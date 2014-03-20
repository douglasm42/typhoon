/*
 * dbinstream.h
 *
 *  Created on: 13/12/2012
 *      Author: Douglas M. Freitas
 * 
 *   Copyright: Staff 42 © 2013
 */
#pragma once

#include <data/data.h>

#include <base/bString.h>

#include <data/dFile.h>

namespace cb {
	namespace data {
		class CbAPI obinstream {
		private:
			ostream &_stream;

		public:
			obinstream(ostream &iout);

			//Output
			obinstream &operator<<(const base::string &istr);

			obinstream &operator<<(const bool &ivalue);

			obinstream &operator<<(const char &ivalue);
			obinstream &operator<<(const short int &ivalue);
			obinstream &operator<<(const int &ivalue);
			obinstream &operator<<(const long int &ivalue);
			obinstream &operator<<(const long long int &ivalue);

			obinstream &operator<<(const unsigned char &ivalue);
			obinstream &operator<<(const unsigned short int &ivalue);
			obinstream &operator<<(const unsigned int &ivalue);
			obinstream &operator<<(const unsigned long int &ivalue);
			obinstream &operator<<(const unsigned long long int &ivalue);

			obinstream &operator<<(const float &ivalue);
			obinstream &operator<<(const double &ivalue);
			obinstream &operator<<(const long double &ivalue);

			//Output arrays
			void write(const base::string *istr, const size_t in);

			void write(const bool *ivalue, const size_t in);

			void write(const char *ivalue, const size_t in);
			void write(const short int *ivalue, const size_t in);
			void write(const int *ivalue, const size_t in);
			void write(const long int *ivalue, const size_t in);
			void write(const long long int *ivalue, const size_t in);

			void write(const unsigned char *ivalue, const size_t in);
			void write(const unsigned short int *ivalue, const size_t in);
			void write(const unsigned int *ivalue, const size_t in);
			void write(const unsigned long int *ivalue, const size_t in);
			void write(const unsigned long long int *ivalue, const size_t in);

			void write(const float *ivalue, const size_t in);
			void write(const double *ivalue, const size_t in);
			void write(const long double *ivalue, const size_t in);
		};

		class CbAPI ibinstream {
		private:
			istream &_stream;

		public:
			ibinstream(istream &iout);

			//Input
			ibinstream &operator>>(base::string &ostr);

			ibinstream &operator>>(bool &ovalue);

			ibinstream &operator>>(char &ovalue);
			ibinstream &operator>>(short int &ovalue);
			ibinstream &operator>>(int &ovalue);
			ibinstream &operator>>(long int &ovalue);
			ibinstream &operator>>(long long int &ovalue);

			ibinstream &operator>>(unsigned char &ovalue);
			ibinstream &operator>>(unsigned short int &ovalue);
			ibinstream &operator>>(unsigned int &ovalue);
			ibinstream &operator>>(unsigned long int &ovalue);
			ibinstream &operator>>(unsigned long long int &ovalue);

			ibinstream &operator>>(float &ovalue);
			ibinstream &operator>>(double &ovalue);
			ibinstream &operator>>(long double &ovalue);

			//Input arrays
			void read(base::string *ostr, const size_t in);

			void read(bool *ovalue, const size_t in);

			void read(char *ovalue, const size_t in);
			void read(short int *ovalue, const size_t in);
			void read(int *ovalue, const size_t in);
			void read(long int *ovalue, const size_t in);
			void read(long long int *ovalue, const size_t in);

			void read(unsigned char *ovalue, const size_t in);
			void read(unsigned short int *ovalue, const size_t in);
			void read(unsigned int *ovalue, const size_t in);
			void read(unsigned long int *ovalue, const size_t in);
			void read(unsigned long long int *ovalue, const size_t in);

			void read(float *ovalue, const size_t in);
			void read(double *ovalue, const size_t in);
			void read(long double *ovalue, const size_t in);
		};
	}  // namespace data
}  // namespace cb
