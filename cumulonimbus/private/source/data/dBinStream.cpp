/* 
 * - Cumulonimbus - ☁
 * File: dBinStream.cpp
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
#include <data/BinStream.h>

#define SingleOut(value) _stream.write((char *)&value, sizeof(value))
#define MultiOut(pvalue, n) _stream.write((char *)pvalue, n*sizeof(*pvalue))

#define SingleIn(value) _stream.read((char *)&value, sizeof(value))
#define MultiIn(pvalue, n) _stream.read((char *)pvalue, n*sizeof(*pvalue))

namespace cb {
	namespace data {
		//Output
		obinstream::obinstream(std::ostream &iout)
		:_stream(iout) {
		}

		obinstream &obinstream::operator<<(const base::string &istr) {
			(*this) << istr.size();
			write(istr.c_str(), istr.size());
			return *this;
		}

		obinstream &obinstream::operator<<(const bool &ivalue)					{SingleOut(ivalue); return *this;}

		obinstream &obinstream::operator<<(const char &ivalue)					{SingleOut(ivalue); return *this;}
		obinstream &obinstream::operator<<(const short int &ivalue)				{SingleOut(ivalue); return *this;}
		obinstream &obinstream::operator<<(const int &ivalue)					{SingleOut(ivalue); return *this;}
		obinstream &obinstream::operator<<(const long int &ivalue)				{SingleOut(ivalue); return *this;}
		obinstream &obinstream::operator<<(const long long int &ivalue)			{SingleOut(ivalue); return *this;}

		obinstream &obinstream::operator<<(const unsigned char &ivalue)			{SingleOut(ivalue); return *this;}
		obinstream &obinstream::operator<<(const unsigned short int &ivalue)	{SingleOut(ivalue); return *this;}
		obinstream &obinstream::operator<<(const unsigned int &ivalue)			{SingleOut(ivalue); return *this;}
		obinstream &obinstream::operator<<(const unsigned long int &ivalue)		{SingleOut(ivalue); return *this;}
		obinstream &obinstream::operator<<(const unsigned long long int &ivalue){SingleOut(ivalue); return *this;}

		obinstream &obinstream::operator<<(const float &ivalue)					{SingleOut(ivalue); return *this;}
		obinstream &obinstream::operator<<(const double &ivalue)				{SingleOut(ivalue); return *this;}
		obinstream &obinstream::operator<<(const long double &ivalue)			{SingleOut(ivalue); return *this;}

		//Output arrays
		void obinstream::write(const base::string *istr, const size_t in) {
			for(size_t i=0 ; i<in ; i++) {
				(*this) << istr[i];
			}
		}

		void obinstream::write(const bool *ivalue, const size_t in)						{MultiOut(ivalue, in);}

		void obinstream::write(const char *ivalue, const size_t in)						{MultiOut(ivalue, in);}
		void obinstream::write(const short int *ivalue, const size_t in)				{MultiOut(ivalue, in);}
		void obinstream::write(const int *ivalue, const size_t in)						{MultiOut(ivalue, in);}
		void obinstream::write(const long int *ivalue, const size_t in)					{MultiOut(ivalue, in);}
		void obinstream::write(const long long int *ivalue, const size_t in)			{MultiOut(ivalue, in);}

		void obinstream::write(const unsigned char *ivalue, const size_t in)			{MultiOut(ivalue, in);}
		void obinstream::write(const unsigned short int *ivalue, const size_t in)		{MultiOut(ivalue, in);}
		void obinstream::write(const unsigned int *ivalue, const size_t in)				{MultiOut(ivalue, in);}
		void obinstream::write(const unsigned long int *ivalue, const size_t in)		{MultiOut(ivalue, in);}
		void obinstream::write(const unsigned long long int *ivalue, const size_t in)	{MultiOut(ivalue, in);}

		void obinstream::write(const float *ivalue, const size_t in)					{MultiOut(ivalue, in);}
		void obinstream::write(const double *ivalue, const size_t in)					{MultiOut(ivalue, in);}
		void obinstream::write(const long double *ivalue, const size_t in)				{MultiOut(ivalue, in);}

		//Input
		ibinstream::ibinstream(std::istream &iout)
		:_stream(iout) {
		}

		ibinstream &ibinstream::operator>>(base::string &ostr) {
			base::string::size_type n;
			(*this) >> n;

			char *buffer = new char[n];
			read(buffer, n);

			ostr.assign(buffer, n);
			return *this;
		}

		ibinstream &ibinstream::operator>>(bool &ovalue)					{SingleIn(ovalue); return *this;}

		ibinstream &ibinstream::operator>>(char &ovalue)					{SingleIn(ovalue); return *this;}
		ibinstream &ibinstream::operator>>(short int &ovalue)				{SingleIn(ovalue); return *this;}
		ibinstream &ibinstream::operator>>(int &ovalue)						{SingleIn(ovalue); return *this;}
		ibinstream &ibinstream::operator>>(long int &ovalue)				{SingleIn(ovalue); return *this;}
		ibinstream &ibinstream::operator>>(long long int &ovalue)			{SingleIn(ovalue); return *this;}

		ibinstream &ibinstream::operator>>(unsigned char &ovalue)			{SingleIn(ovalue); return *this;}
		ibinstream &ibinstream::operator>>(unsigned short int &ovalue)		{SingleIn(ovalue); return *this;}
		ibinstream &ibinstream::operator>>(unsigned int &ovalue)			{SingleIn(ovalue); return *this;}
		ibinstream &ibinstream::operator>>(unsigned long int &ovalue)		{SingleIn(ovalue); return *this;}
		ibinstream &ibinstream::operator>>(unsigned long long int &ovalue)	{SingleIn(ovalue); return *this;}

		ibinstream &ibinstream::operator>>(float &ovalue)					{SingleIn(ovalue); return *this;}
		ibinstream &ibinstream::operator>>(double &ovalue)					{SingleIn(ovalue); return *this;}
		ibinstream &ibinstream::operator>>(long double &ovalue)				{SingleIn(ovalue); return *this;}

		//Input arrays
		void ibinstream::read(base::string *ostr, const size_t in) {
			for(size_t i=0 ; i<in ; i++) {
				(*this) >> ostr[i];
			}
		}

		void ibinstream::read(bool *ovalue, const size_t in)					{MultiIn(ovalue, in);}

		void ibinstream::read(char *ovalue, const size_t in)					{MultiIn(ovalue, in);}
		void ibinstream::read(short int *ovalue, const size_t in)				{MultiIn(ovalue, in);}
		void ibinstream::read(int *ovalue, const size_t in)						{MultiIn(ovalue, in);}
		void ibinstream::read(long int *ovalue, const size_t in)				{MultiIn(ovalue, in);}
		void ibinstream::read(long long int *ovalue, const size_t in)			{MultiIn(ovalue, in);}

		void ibinstream::read(unsigned char *ovalue, const size_t in)			{MultiIn(ovalue, in);}
		void ibinstream::read(unsigned short int *ovalue, const size_t in)		{MultiIn(ovalue, in);}
		void ibinstream::read(unsigned int *ovalue, const size_t in)			{MultiIn(ovalue, in);}
		void ibinstream::read(unsigned long int *ovalue, const size_t in)		{MultiIn(ovalue, in);}
		void ibinstream::read(unsigned long long int *ovalue, const size_t in)	{MultiIn(ovalue, in);}

		void ibinstream::read(float *ovalue, const size_t in)					{MultiIn(ovalue, in);}
		void ibinstream::read(double *ovalue, const size_t in)					{MultiIn(ovalue, in);}
		void ibinstream::read(long double *ovalue, const size_t in)				{MultiIn(ovalue, in);}
	}  // namespace data
}  // namespace cb
