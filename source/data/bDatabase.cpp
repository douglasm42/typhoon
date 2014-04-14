/*
 * bDatabase.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: douglas
 */

#include <data/dDatabase.h>

#include <base/bLog.h>

#include <sqlite3.h>

namespace cb {
	namespace data {
		KinKeyWOErase(DBHandler, sqlite3);
		KinKeyWOErase(DBStatement, sqlite3_stmt);

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
				ThrowDataException(base::print("Erro ao abrir o banco de dados: '%s'", sqlite3_errmsg(&_handler)).c_str());
			}

			_handler << dbhandler;
		}

		void Database::close() {
			if(isOpen()) {
				int result = sqlite3_close(&_handler);
				if(result != SQLITE_OK) {
					ThrowDataException(base::print("Erro ao fechar o banco de dados: '%s'", sqlite3_errmsg(&_handler)).c_str());
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
					ThrowDataException(base::print("Erro ao executar querry no banco de dados: '%s'", result, sqlite3_errmsg(&_handler)).c_str());
				}

				db::querry q;
				q._statement << stmt;

				return q;
			} else {
				ThrowDataException("Tentou usar um banco de dados fechado.");
			}
		}
	}  // namespace data
}  // namespace cb

