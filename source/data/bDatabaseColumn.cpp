/*
 * bDatabase.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: douglas
 */

#include <data/Database.h>

#include <sqlite3.h>

namespace cb {
	namespace data {
		KinKey(DBStatement, sqlite3_stmt);

		const char *errmsgs(const kin::DBStatement &istatement) {
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

		namespace db {
			real_t column::real() const {
				real_t result = sqlite3_column_double((sqlite3_stmt*)kin::pt(_statement), _column_id);
				if(sqlite3_errcode(sqlite3_db_handle((sqlite3_stmt*)kin::pt(_statement))) != SQLITE_OK) {
					ThrowDet(tokurei::GetFailed, "Error: %s", errmsgs(_statement));
				}
				return result;
			}

			integer_t column::integer() const {
				integer_t result = sqlite3_column_int((sqlite3_stmt*)kin::pt(_statement), _column_id);
				if(sqlite3_errcode(sqlite3_db_handle((sqlite3_stmt*)kin::pt(_statement))) != SQLITE_OK) {
					ThrowDet(tokurei::GetFailed, "Error: %s", errmsgs(_statement));
				}
				return result;
			}

			linteger_t column::linteger() const {
				linteger_t result = sqlite3_column_int64((sqlite3_stmt*)kin::pt(_statement), _column_id);
				if(sqlite3_errcode(sqlite3_db_handle((sqlite3_stmt*)kin::pt(_statement))) != SQLITE_OK) {
					ThrowDet(tokurei::GetFailed, "Error: %s", errmsgs(_statement));
				}
				return result;
			}

			string column::str() const {
				string result = (const char *)sqlite3_column_text((sqlite3_stmt*)kin::pt(_statement), _column_id);
				if(sqlite3_errcode(sqlite3_db_handle((sqlite3_stmt*)kin::pt(_statement))) != SQLITE_OK) {
					ThrowDet(tokurei::GetFailed, "Error: %s", errmsgs(_statement));
				}
				return result;
			}

			wstring column::wstr() const {
				wstring result = (const wchar_t *)sqlite3_column_text16((sqlite3_stmt*)kin::pt(_statement), _column_id);
				if(sqlite3_errcode(sqlite3_db_handle((sqlite3_stmt*)kin::pt(_statement))) != SQLITE_OK) {
					ThrowDet(tokurei::GetFailed, "Error: %s", errmsgs(_statement));
				}
				return result;
			}

			blob_t column::blob() const {
				const char *data = (const char *)sqlite3_column_blob((sqlite3_stmt*)kin::pt(_statement), _column_id);
				if(sqlite3_errcode(sqlite3_db_handle((sqlite3_stmt*)kin::pt(_statement))) != SQLITE_OK) {
					ThrowDet(tokurei::GetFailed, "Error: %s", errmsgs(_statement));
				}

				int size = sqlite3_column_bytes((sqlite3_stmt*)kin::pt(_statement), _column_id);
				if(sqlite3_errcode(sqlite3_db_handle((sqlite3_stmt*)kin::pt(_statement))) != SQLITE_OK) {
					ThrowDet(tokurei::GetFailed, "Error: %s", errmsgs(_statement));
				}
				return blob_t(data, size);
			}

			base::string column::name() const {
				string result = (const char *)sqlite3_column_name((sqlite3_stmt*)kin::pt(_statement), _column_id);
				if(sqlite3_errcode(sqlite3_db_handle((sqlite3_stmt*)kin::pt(_statement))) != SQLITE_OK) {
					ThrowDet(tokurei::GetFailed, "Error: %s", errmsgs(_statement));
				}
				return result;
			}
			type_t column::type() const {
				int ctype = sqlite3_column_type((sqlite3_stmt*)kin::pt(_statement), _column_id);
				if(sqlite3_errcode(sqlite3_db_handle((sqlite3_stmt*)kin::pt(_statement))) != SQLITE_OK) {
					ThrowDet(tokurei::GetFailed, "Error: %s", errmsgs(_statement));
				}

				switch(ctype) {
				case SQLITE_FLOAT:
					return Real;
				case SQLITE_INTEGER:
					return Integer;
				case SQLITE_TEXT:
					return String;
				case SQLITE_BLOB:
					return BLOB;
				case SQLITE_NULL:
					return Null;
				}
				Throw(tokurei::GetFailed);
			}
		}  // namespace db
	}  // namespace data
}  // namespace cb

