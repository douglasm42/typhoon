/* 
 * - Cumulonimbus - ☁
 * File: Database.h
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

#include <cb/data/data.hpp>

#include <cb/base/String.hpp>

#include <cb/base/Exception.hpp>
#include <cb/data/Blob.hpp>

#include <sqlite3.h>

namespace cb {
	namespace data {
		namespace db {
			typedef enum type_t {
				Null,
				Real,
				Integer,
				String,
				BLOB
			} type_t;

			class CbAPI querry;

			typedef double			real_t;
			typedef int				integer_t;
			typedef long long		linteger_t;
			typedef base::string	string;
			typedef base::string16	string16;
			typedef Blob			blob_t;

			class CbAPI column {
			private:
				int _column_id;
				sqlite3_stmt *_statement;

				column();
				column(const int icolumnid, sqlite3_stmt *istatement) : _column_id(icolumnid), _statement(istatement) {}

			public:
				column(const column &icolumn) : _column_id(icolumn._column_id), _statement(icolumn._statement) {}
				~column() {}

				column &operator=(const column &icolumn) {
					_column_id = icolumn._column_id;
					_statement = icolumn._statement;

					return *this;
				}

				operator real_t() const		{return real();}
				operator integer_t() const	{return integer();}
				operator linteger_t() const	{return linteger();}
				operator string() const		{return str();}
				operator string16() const	{return wstr();}
				operator blob_t() const		{return blob();}

				operator char() const		{return		 (char)integer();}
				operator short() const		{return		(short)integer();}
				operator long() const		{return		 (long)integer();}
				operator float() const		{return		(float)real();}

				operator unsigned char() const		{return		 (unsigned char)integer();}
				operator unsigned short() const		{return		(unsigned short)integer();}
				operator unsigned int() const		{return		  (unsigned int)linteger();}
				operator unsigned long() const		{return		 (unsigned long)linteger();}
				operator unsigned long long() const	{return	(unsigned long long)linteger();}

				bool isNull() const;
				bool isReal() const;
				bool isInteger() const;
				bool isString() const;
				bool isBLOB() const;

				real_t real() const;
				integer_t integer() const;
				linteger_t linteger() const;
				string str() const;
				string16 wstr() const;
				blob_t blob() const;

				bool empty() const {return isNull();}
				base::string name() const;
				type_t type() const;

				friend class CbAPI querry;
			};

			inline bool column::isNull()		const {return type()==Null;}
			inline bool column::isReal()		const {return type()==Real;}
			inline bool column::isInteger()		const {return type()==Integer;}
			inline bool column::isString()		const {return type()==String;}
			inline bool column::isBLOB()		const {return type()==BLOB;}

			class CbAPI querry {
			private:
				sqlite3_stmt *_statement;
				bool _rows;

			public:
				querry();
				querry(const querry &iquerry);
				~querry();

				querry &operator=(const querry &iquerry);

				void close();
				bool isOpen();

				bool step();
				bool eor();

				void reset();

				void param(const base::string &iparameter);
				void param(const base::string &iparameter, const real_t ireal);
				void param(const base::string &iparameter, const integer_t iinteger);
				void param(const base::string &iparameter, const linteger_t ilinteger);
				void param(const base::string &iparameter, const base::string &istring);
				void param(const base::string &iparameter, const base::string16 &istring16);
				void param(const base::string &iparameter, const blob_t &iblob);

				int columnCount() const;
				int columnID(const base::string &icolumn) const;

				column operator[](const base::string &icolumn) const {return column(columnID(icolumn), _statement);}
				column operator[](const int icolumn) const {
					if(icolumn >= columnCount()) {
						ThrowDet(tokurei::OutOfRange, "Position: %d and Range: %d", icolumn, columnCount());
					}
					return column(icolumn, _statement);
				}

				friend class CbAPI cb::data::Database;
			};
		}  // namespace db

		class CbAPI Database {
		private:
			sqlite3 *_handler;

		public:
			Database();
			Database(const base::string &ifilename);
			~Database();

			void open(const base::string &ifilename);
			void close();
			bool isOpen();

			db::querry querry(const base::string &iquerry);
		};
	}  // namespace data
}  // namespace cb
