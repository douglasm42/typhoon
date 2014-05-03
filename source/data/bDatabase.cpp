/*
 * bDatabase.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: douglas
 */

#include <data/Database.h>

#include <base/Log.h>

#include <sqlite3.h>

namespace cb {
	namespace data {
		KinKey(DBHandler, sqlite3);
		KinKey(DBStatement, sqlite3_stmt);

		const char *errmsgd(kin::DBHandler &ihandler) {
			{
				const char *msg = sqlite3_errmsg(&ihandler);
				if(msg) {
					return msg;
				}
			}
			{
				const char *msg = sqlite3_errstr(sqlite3_errcode(&ihandler));
				if(msg) {
					return msg;
				}
			}
			return "Unknown error";
		}

		Database::Database() {
		}

		Database::Database(const base::string &ifilename) {
			open(ifilename);
		}

		Database::~Database() {
			close();
		}

		void Database::open(const base::string &ifilename) {
			close();

			sqlite3 *dbhandler;
			int result = sqlite3_open(ifilename.c_str(), &dbhandler);
			if(result != SQLITE_OK) {
				if(dbhandler) {
					sqlite3_close(dbhandler);
				}
				ThrowDet(tokurei::OpenError, "Filename: %s, Error: %s", ifilename.c_str(), errmsgd(_handler));
			}

			_handler << dbhandler;
		}

		void Database::close() {
			if(isOpen()) {
				int result = sqlite3_close(&_handler);
				if(result != SQLITE_OK) {
					ThrowDet(tokurei::CloseError, "Error: %s", errmsgd(_handler));
				}
			}
		}

		bool Database::isOpen() {
			return !_handler.empty();
		}

		db::querry Database::querry(const base::string &iquerry) {
			if(isOpen()) {
				sqlite3_stmt *stmt;

				int result = sqlite3_prepare_v2(&_handler, iquerry.c_str(), -1, &stmt, nullptr);
				if(result != SQLITE_OK) {
					ThrowDet(tokurei::CreateError, "Error: %s", errmsgd(_handler));
				}

				db::querry q;
				q._statement << stmt;

				return q;
			} else {
				Throw(tokurei::EmptyObject);
			}
		}
	}  // namespace data
}  // namespace cb

