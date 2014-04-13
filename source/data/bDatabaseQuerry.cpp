/*
 * bDatabase.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: douglas
 */

#include <data/dDatabase.h>

#include <base/bException.h>

#include <sqlite3.h>

namespace cb {
	namespace data {
		KinKeyWOErase(DBStatement, sqlite3_stmt);

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
						ThrowDataException(base::print("Erro ao finalizar querry no banco de dados: '%s'", sqlite3_errmsg(sqlite3_db_handle(&_statement))).c_str());
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
					ThrowDataException("Tentou usar uma querry vazia.");
				}

				int result = sqlite3_step(&_statement);
				if(result == SQLITE_DONE) {
					_rows = false;
				} else if(result == SQLITE_ROW) {
					_rows = true;
				} else {
					ThrowDataException(base::print("Erro ao obter próximo resultado da querry: '%s'", sqlite3_errmsg(sqlite3_db_handle(&_statement))).c_str());
				}
				return _rows;
			}

			bool querry::eor() {
				if(!isOpen()) {
					ThrowDataException("Tentou usar uma querry vazia.");
				}
				return _rows;
			}

			void querry::reset() {
				if(!isOpen()) {
					ThrowDataException("Tentou usar uma querry vazia.");
				}

				int result = sqlite3_reset(&_statement);
				if(result != SQLITE_OK) {
					ThrowDataException(base::print("Erro ao resetar querry: '%s'", sqlite3_errmsg(sqlite3_db_handle(&_statement))).c_str());
				}

				result = sqlite3_clear_bindings(&_statement);
				if(result != SQLITE_OK) {
					ThrowDataException(base::print("Erro ao resetar querry: '%s'", sqlite3_errmsg(sqlite3_db_handle(&_statement))).c_str());
				}
			}

#			define QPARAMIND sqlite3_bind_parameter_index(&_statement, iparameter.c_str())

			void querry::param(const base::string &iparameter) {
				if(!isOpen()) {
					ThrowDataException("Tentou usar uma querry vazia.");
				}

				int result = sqlite3_bind_null(&_statement, QPARAMIND);
				if(result != SQLITE_OK) {
					ThrowDataException(base::print("Erro ao modificar parametro da querry: '%s'", sqlite3_errmsg(sqlite3_db_handle(&_statement))).c_str());
				}
			}
			void querry::param(const base::string &iparameter, const double ireal) {
				if(!isOpen()) {
					ThrowDataException("Tentou usar uma querry vazia.");
				}

				int result = sqlite3_bind_double(&_statement, QPARAMIND, ireal);
				if(result != SQLITE_OK) {
					ThrowDataException(base::print("Erro ao modificar parametro da querry: '%s'", sqlite3_errmsg(sqlite3_db_handle(&_statement))).c_str());
				}
			}

			void querry::param(const base::string &iparameter, const int iint) {
				if(!isOpen()) {
					ThrowDataException("Tentou usar uma querry vazia.");
				}

				int result = sqlite3_bind_int(&_statement, QPARAMIND, iint);
				if(result != SQLITE_OK) {
					ThrowDataException(base::print("Erro ao modificar parametro da querry: '%s'", sqlite3_errmsg(sqlite3_db_handle(&_statement))).c_str());
				}
			}
			void querry::param(const base::string &iparameter, const long long ill) {
				if(!isOpen()) {
					ThrowDataException("Tentou usar uma querry vazia.");
				}

				int result = sqlite3_bind_int64(&_statement, QPARAMIND, ill);
				if(result != SQLITE_OK) {
					ThrowDataException(base::print("Erro ao modificar parametro da querry: '%s'", sqlite3_errmsg(sqlite3_db_handle(&_statement))).c_str());
				}
			}

			void querry::param(const base::string &iparameter, const base::string &istring) {
				if(!isOpen()) {
					ThrowDataException("Tentou usar uma querry vazia.");
				}

				int result = sqlite3_bind_text(&_statement, QPARAMIND, istring.c_str(), -1, SQLITE_TRANSIENT);
				if(result != SQLITE_OK) {
					ThrowDataException(base::print("Erro ao modificar parametro da querry: '%s'", sqlite3_errmsg(sqlite3_db_handle(&_statement))).c_str());
				}
			}
			void querry::param(const base::string &iparameter, const base::wstring &iwstring) {
				if(!isOpen()) {
					ThrowDataException("Tentou usar uma querry vazia.");
				}

				int result = sqlite3_bind_text16(&_statement, QPARAMIND, iwstring.c_str(), -1, SQLITE_TRANSIENT);
				if(result != SQLITE_OK) {
					ThrowDataException(base::print("Erro ao modificar parametro da querry: '%s'", sqlite3_errmsg(sqlite3_db_handle(&_statement))).c_str());
				}
			}
			void querry::param(const base::string &iparameter, const void *iblob, const size_t in) {
				if(!isOpen()) {
					ThrowDataException("Tentou usar uma querry vazia.");
				}

				int result = sqlite3_bind_blob(&_statement, QPARAMIND, iblob, in, SQLITE_TRANSIENT);
				if(result != SQLITE_OK) {
					ThrowDataException(base::print("Erro ao modificar parametro da querry: '%s'", sqlite3_errmsg(sqlite3_db_handle(&_statement))).c_str());
				}
			}
		}  // namespace db
	}  // namespace data
}  // namespace cb

