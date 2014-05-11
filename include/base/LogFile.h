/* 
 * - Cumulonimbus - ☁
 * File: LogFile.h
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
#pragma once

#include <base/base.h>

#include <base/Log.h>

#include <base/Date.h>
#include <base/String.h>

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
