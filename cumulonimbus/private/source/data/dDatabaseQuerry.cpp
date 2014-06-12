/* 
 * - Cumulonimbus - ☁
 * File: dDatabaseQuerry.cpp
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
#include <data/Database.h>

#include <sqlite3.h>

namespace cb {
	namespace data {
		KinKey(kin::DBStatement, sqlite3_stmt);

		const char *errmsgq(const kin::DBStatement &istatement) {
			sqlite3 *handler = sqlite3_db_handle((sqlite3_stmt*)kin::pt(istatement));
			{
				const char *msg = sqlite3_errmsg(handler);
				if(msg) {
					return msg;
				}
			}
			{
				const char *msg = sqlite3_errstr(sqlite3_errcode(handler));
				if(msg) {
					return msg;
				}
			}
			return "Unknown error";
		}

		const char *errmsgq(kin::DBStatement &istatement) {
			sqlite3 *handler = sqlite3_db_handle(&istatement);
			{
				const char *msg = sqlite3_errmsg(handler);
				if(msg) {
					return msg;
				}
			}
			{
				const char *msg = sqlite3_errstr(sqlite3_errcode(handler));
				if(msg) {
					return msg;
				}
			}
			return "Unknown error";
		}

		namespace db {
			querry::querry() :_rows(false) {
			}

			querry::querry(const querry &iquerry) {
				(*this) = iquerry;
			}

			querry::~querry() {
				close();
			}

			querry &querry::operator=(const querry &iquerry) {
				querry& q = const_cast<querry&>(iquerry);

				close();
				_statement._pointer = q._statement._pointer;
				_rows = q._rows;

				q._statement._pointer = nullptr;
				q._rows = false;

				return *this;
			}

			void querry::close() {
				if(isOpen()) {
					int result = sqlite3_finalize(&_statement);
					if(result != SQLITE_OK) {
						ThrowDet(tokurei::CloseError, "Error: %s", errmsgq(_statement));
					}
					_statement << nullptr;
					_rows = false;
				}
			}

			bool querry::isOpen() {
				return !_statement.empty();
			}

			bool querry::step() {
				if(!isOpen()) {
					Throw(tokurei::EmptyObject);
				}

				int result = sqlite3_step(&_statement);
				if(result == SQLITE_DONE) {
					_rows = false;
				} else if(result == SQLITE_ROW) {
					_rows = true;
				} else {
					ThrowDet(tokurei::AdvanceFailed, "Error: %s", errmsgq(_statement));
				}
				return _rows;
			}

			bool querry::eor() {
				if(!isOpen()) {
					Throw(tokurei::EmptyObject);
				}
				return _rows;
			}

			void querry::reset() {
				if(!isOpen()) {
					Throw(tokurei::EmptyObject);
				}

				int result = sqlite3_reset(&_statement);
				if(result != SQLITE_OK) {
					ThrowDet(tokurei::ClearFailed, "Error: %s", errmsgq(_statement));
				}

				result = sqlite3_clear_bindings(&_statement);
				if(result != SQLITE_OK) {
					ThrowDet(tokurei::ClearFailed, "Error: %s", errmsgq(_statement));
				}
			}

#			define QPARAMIND sqlite3_bind_parameter_index(&_statement, iparameter.c_str())

			void querry::param(const base::string &iparameter) {
				if(!isOpen()) {
					Throw(tokurei::EmptyObject);
				}

				int result = sqlite3_bind_null(&_statement, QPARAMIND);
				if(result != SQLITE_OK) {
					ThrowDet(tokurei::SetFailed, "Error: %s", errmsgq(_statement));
				}
			}
			void querry::param(const base::string &iparameter, const real_t ireal) {
				if(!isOpen()) {
					Throw(tokurei::EmptyObject);
				}

				int result = sqlite3_bind_double(&_statement, QPARAMIND, ireal);
				if(result != SQLITE_OK) {
					ThrowDet(tokurei::SetFailed, "Error: %s", errmsgq(_statement));
				}
			}

			void querry::param(const base::string &iparameter, const integer_t iinteger) {
				if(!isOpen()) {
					Throw(tokurei::EmptyObject);
				}

				int result = sqlite3_bind_int(&_statement, QPARAMIND, iinteger);
				if(result != SQLITE_OK) {
					ThrowDet(tokurei::SetFailed, "Error: %s", errmsgq(_statement));
				}
			}
			void querry::param(const base::string &iparameter, const linteger_t ilinteger) {
				if(!isOpen()) {
					Throw(tokurei::EmptyObject);
				}

				int result = sqlite3_bind_int64(&_statement, QPARAMIND, ilinteger);
				if(result != SQLITE_OK) {
					ThrowDet(tokurei::SetFailed, "Error: %s", errmsgq(_statement));
				}
			}

			void querry::param(const base::string &iparameter, const string &istring) {
				if(!isOpen()) {
					Throw(tokurei::EmptyObject);
				}

				int result = sqlite3_bind_text(&_statement, QPARAMIND, istring.c_str(), -1, SQLITE_TRANSIENT);
				if(result != SQLITE_OK) {
					ThrowDet(tokurei::SetFailed, "Error: %s", errmsgq(_statement));
				}
			}
			void querry::param(const base::string &iparameter, const string16 &istring16) {
				if(!isOpen()) {
					Throw(tokurei::EmptyObject);
				}

				int result = sqlite3_bind_text16(&_statement, QPARAMIND, istring16.c_str(), -1, SQLITE_TRANSIENT);
				if(result != SQLITE_OK) {
					ThrowDet(tokurei::SetFailed, "Error: %s", errmsgq(_statement));
				}
			}
			void querry::param(const base::string &iparameter, const blob_t &iblob) {
				if(!isOpen()) {
					Throw(tokurei::EmptyObject);
				}

				int result = sqlite3_bind_blob(&_statement, QPARAMIND, (const void *)iblob.data(), (int)iblob.size(), SQLITE_TRANSIENT);
				if(result != SQLITE_OK) {
					ThrowDet(tokurei::SetFailed, "Error: %s", errmsgq(_statement));
				}
			}

			int querry::columnID(const base::string &icolumn) const {
				int count = columnCount();
				for(int i=0 ; i<count ; i++) {
					if(icolumn == sqlite3_column_name((sqlite3_stmt*)kin::pt(_statement), i)) {
						return i;
					}
				}
				ThrowDet(tokurei::NotFound, "Column name: %s", icolumn.c_str());
			}

			int querry::columnCount() const {
				int count = sqlite3_column_count((sqlite3_stmt*)kin::pt(_statement));
				if(sqlite3_errcode(sqlite3_db_handle((sqlite3_stmt*)kin::pt(_statement))) != SQLITE_OK) {
					ThrowDet(tokurei::SetFailed, "Error: %s", errmsgq(_statement));
				}
				return count;
			}
		}  // namespace db
	}  // namespace data
}  // namespace cb

