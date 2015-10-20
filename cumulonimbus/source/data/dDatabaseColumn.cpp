/* 
 * - Cumulonimbus - ☁
 * File: dDatabaseColumn.cpp
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
#include <cb/data/Database.hpp>

namespace cb {
	namespace data {
		const char *errmsgs(sqlite3_stmt *istatement) {
			sqlite3 *handler = sqlite3_db_handle(istatement);
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
				real_t result = sqlite3_column_double(_statement, _column_id);
				if(sqlite3_errcode(sqlite3_db_handle(_statement)) != SQLITE_OK) {
					ThrowDet(tokurei::GetFailed, "Error: %s", errmsgs(_statement));
				}
				return result;
			}

			integer_t column::integer() const {
				integer_t result = sqlite3_column_int(_statement, _column_id);
				if(sqlite3_errcode(sqlite3_db_handle(_statement)) != SQLITE_OK) {
					ThrowDet(tokurei::GetFailed, "Error: %s", errmsgs(_statement));
				}
				return result;
			}

			linteger_t column::linteger() const {
				linteger_t result = sqlite3_column_int64(_statement, _column_id);
				if(sqlite3_errcode(sqlite3_db_handle(_statement)) != SQLITE_OK) {
					ThrowDet(tokurei::GetFailed, "Error: %s", errmsgs(_statement));
				}
				return result;
			}

			string column::str() const {
				string result = (const char *)sqlite3_column_text(_statement, _column_id);
				if(sqlite3_errcode(sqlite3_db_handle(_statement)) != SQLITE_OK) {
					ThrowDet(tokurei::GetFailed, "Error: %s", errmsgs(_statement));
				}
				return result;
			}

			string16 column::wstr() const {
				string16 result = (const char16_t *)sqlite3_column_text16(_statement, _column_id);
				if(sqlite3_errcode(sqlite3_db_handle(_statement)) != SQLITE_OK) {
					ThrowDet(tokurei::GetFailed, "Error: %s", errmsgs(_statement));
				}
				return result;
			}

			blob_t column::blob() const {
				const char *data = (const char *)sqlite3_column_blob(_statement, _column_id);
				if(sqlite3_errcode(sqlite3_db_handle(_statement)) != SQLITE_OK) {
					ThrowDet(tokurei::GetFailed, "Error: %s", errmsgs(_statement));
				}

				int size = sqlite3_column_bytes(_statement, _column_id);
				if(sqlite3_errcode(sqlite3_db_handle(_statement)) != SQLITE_OK) {
					ThrowDet(tokurei::GetFailed, "Error: %s", errmsgs(_statement));
				}
				return blob_t(data, size);
			}

			base::string column::name() const {
				string result = (const char *)sqlite3_column_name(_statement, _column_id);
				if(sqlite3_errcode(sqlite3_db_handle(_statement)) != SQLITE_OK) {
					ThrowDet(tokurei::GetFailed, "Error: %s", errmsgs(_statement));
				}
				return result;
			}
			type_t column::type() const {
				int ctype = sqlite3_column_type(_statement, _column_id);
				if(sqlite3_errcode(sqlite3_db_handle(_statement)) != SQLITE_OK) {
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

