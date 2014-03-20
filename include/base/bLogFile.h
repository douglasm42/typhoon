/*
 * bLogFile.h
 *
 *  Created on: 19/12/2012
 *      Author: Douglas M. Freitas
 * 
 *   Copyright: Staff 42 © 2013
 */
#pragma once

#include <base/base.h>

#include <base/bException.h>
#include <base/bLog.h>

#include <base/bDate.h>
#include <base/bString.h>
#include <ctime>

namespace cb {
	namespace base {

		/**
		 * Classe responsavel por registrar os eventos do log no arquivo de texto. Ela é utilizada pela classe Log.
		 *
		 * @author Douglas M. Freitas
		 */
		class CbAPI LogFile {
		private:
			///Nome do arquivo de log.
			string _filename;

		public:
			/**
			 * Inicializa o arquivo de log com o cabeçalho contendo o horario de inicio passado por parametro
			 * e o título.
			 *
			 * @param ifilename Nome do arquivo de log.
			 * @param ititle Título do arquivo de log.
			 * @param idate Horario da criação do arquivo.
			 */
			LogFile(string ifilename, string ititle, Date idate);

			/**
			 * Escreve o rodapé do arquivo de log.
			 */
			~LogFile();

			/**
			 * Registra um evento com o tipo, horario e mensagem passados por parametro.
			 *
			 * @param itype Tipo do evento.
			 * @param idate Horario em que o evento ocorreu.
			 * @param iline Mensagem a ser registrada no arquivo.
			 */
			void write(Log::Type itype, Date idate, string iline);
		};

	}  // namespace base
}  // namespace cb
