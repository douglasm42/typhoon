/*
 * bException.h
 *
 *  Created on: 13/12/2012
 *      Author: Douglas M. Freitas
 * 
 *   Copyright: Staff 42 © 2013
 */
#pragma once

#include <base/base.h>

#include <base/bString.h>
#include <stdio.h>

namespace cb {
	namespace base {
		/**
		 * Classe base para as exceções. Toda exceção deriva dessa classe e todas as exceções lançadas deve ser
		 * um objeto dessa classe ou de uma derivada dela.
		 */
		class CbAPI Exception {
		private:
			///Tipo da exceção.
			string _type;

			///Motivo da exceção.
			string _what;

		public:
			/**
			 * Construtor da exceção, deve receber o motivo da mesma por parametro.
			 * @param iwhat Motivo da exceção.
			 */
			Exception(string iwhat) : _type("Exception"), _what(iwhat) {}

			/**
			 * Construtor da exceção, deve receber o motivo da mesma por parametro e o tipo.
			 * @param itype Tipo da exceção.
			 * @param iwhat Motivo da exceção.
			 */
			Exception(string itype, string iwhat) : _type(itype), _what(iwhat) {}

			/**
			 * Destrutor da exceção.
			 */
			virtual ~Exception() {}

			/**
			 * Retorna o motivo da exceção precedido por seu tipo.
			 * @return O motivo da exceção precedido por seu tipo.
			 */
			virtual string what() const {return _type + " : " + _what;}
		};

		/**
		 * Modelo de exceções.
		 */
#define ExceptionTemplate(Name)\
		class CbAPI Name : public base::Exception {\
		public:\
			Name(base::string iwhat) : Exception(#Name, iwhat) {}\
		};

		ExceptionTemplate(FatalException)
#define	ThrowFatalException(msg) throw FatalException(base::print("%s() : %s", __func__, msg))

		ExceptionTemplate(LogException)
#define	ThrowLogException(msg) throw LogException(base::print("%s() : %s", __func__, msg))
	}  // namespace base

	namespace core {
		ExceptionTemplate(CoreException)
#define	ThrowCoreException(msg) throw CoreException(base::print("%s() : %s", __func__, msg))
	}  // namespace core

	namespace data {
		ExceptionTemplate(DataException)
#define	ThrowDataException(msg) throw DataException(base::print("%s() : %s", __func__, msg))
	}  // namespace date
}  // namespace cb
