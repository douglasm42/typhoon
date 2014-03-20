/*
 * bDate.h
 *
 *  Created on: 13/12/2012
 *      Author: Douglas M. Freitas
 * 
 *   Copyright: Staff 42 © 2013
 */
#pragma once

#include <base/base.h>

#include <base/bString.h>

#include <ctime>

namespace cb {
	namespace base {
		///Classe utilizada para verificação da data e hora do sistema.
		class CbAPI Date {
		private:
			///Informação sobre a data.
			struct tm _timeinfo;

			///Obtém a informação da data.
			static void getTimeInfo(struct tm *itimeinfo);

		public:
			///Inicializa com a data e hora atual.
			Date();
			///Copia a data passada por parametro.
			Date(const Date &idate);

			/**
			 * Obtém o segundo da data, entre 0 e 59.
			 * @return O segundo da data.
			 */
			int seconds()	{return _timeinfo.tm_sec;}

			/**
			 * Obtém o minuto da data, entre 0 e 59.
			 * @return O minuto da data.
			 */
			int minutes()	{return _timeinfo.tm_min;}

			/**
			 * Obtém a hora da data, entre 0 e 23.
			 * @return A hora da data.
			 */
			int hour()		{return _timeinfo.tm_hour;}

			/**
			 * Obtém o dia da data, entre 1 e 28, 29, 30 ou 31 dependendo do mês.
			 * @return O dia da data.
			 */
			int mday()		{return _timeinfo.tm_mday;}

			/**
			 * Obtém o dia da semana da data, entre 0 e 6.
			 * @return O dia da semana da data.
			 */
			int wday()		{return _timeinfo.tm_wday;}

			/**
			 * Obtém o dia do ano da data, entre 0 e 365.
			 * @return O dia do ano da data.
			 */
			int yday()		{return _timeinfo.tm_yday;}

			/**
			 * Obtém o mês da data, entre 0 e 11.
			 * @return o mês da data.
			 */
			int mon()		{return _timeinfo.tm_mon;}

			/**
			 * Obtém o ano da data.
			 * @return O ano da data.
			 */
			int year()		{return _timeinfo.tm_year + 1900;}

			/**
			 * Obtém a data formatada de acordo com o formato passado por parametro.
			 * Funciona da mesma forma que a função strftime:
			 * http://www.cplusplus.com/reference/ctime/strftime/
			 * @param iformat Formato da data.
			 * @return String da data formatada com o formato.
			 */
			string str(const char *iformat);

			/**
			 * Operador de atribuição, copia a data passada por parametro.
			 */
			Date &operator=(const Date &idate);
		};
	}  // namespace base
}  // namespace cb
