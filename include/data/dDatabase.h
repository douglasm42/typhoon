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

namespace cb {
	namespace data {
		class CbAPI Database {
		public:

		private:

		public:
			Database();
			Database(string iaddress, string password);
			~Database();

			void open(string iaddress, string password);
			void close();

			bool isOpen();
		};
	}  // namespace data
}  // namespace cb
