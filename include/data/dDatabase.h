/*
 * dDatabase.h
 *
 *  Created on: 05/01/2014
 *      Author: Douglas
 *
 *   Copyright: Staff 42 © 2013
 */

#pragma once

#include <data/data.h>

#include <base/bString.h>

#include <data/dFile.h>

namespace cb {
	namespace data {
		KinLock(DBHandler);
		KinLock(DBStatement);

		namespace db {
			class CbAPI querry {
			private:
				kin::DBStatement _statement;
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
				void param(const base::string &iparameter, const double ireal);
				void param(const base::string &iparameter, const int iint);
				void param(const base::string &iparameter, const long long ill);
				void param(const base::string &iparameter, const base::string &istring);
				void param(const base::string &iparameter, const base::wstring &iwstring);
				void param(const base::string &iparameter, const void *iblob, const size_t in);

				double			gReal(const base::string &iparameter);
				int				gInt(const base::string &iparameter);
				long long		gInt64(const base::string &iparameter);
				base::string	gString(const base::string &iparameter);
				base::string	gWString(const base::string &iparameter);
				void			blob(const base::string &iparameter, void *&iblob, size_t &in);

				friend class CbAPI cb::data::Database;
			};
		}  // namespace db

		class CbAPI Database {
		private:
			kin::DBHandler _handler;

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
