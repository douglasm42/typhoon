/*
 * bLog.h
 *
 *  Created on: 19/12/2012
 *      Author: Douglas M. Freitas
 * 
 *   Copyright: Staff 42 © 2013
 */
#pragma once

#include <base/base.h>

#include <base/Date.h>
#include <base/String.h>

#include <thread>
#include <mutex>

namespace cb {
	namespace base {
		class CbAPI LogFile;

		/**
		 * Classe responsavel pelos arquivos de log, ela deve ser inicializada antes de qualquer registro de evento.
		 * Antes da finalização do programa ela deve ser finalizada.
		 *
		 * O registro de eventos é feito pela função #log(), que é separada dessa classe.
		 */
		class CbAPI Log {
		public:
			/**
			 * Tipos de mensagens de erro. São usados ao criar uma nova mensagem com a função #log().
			 */
			typedef enum Type {
				Error,	//!< Mensagem de erro.
				Warning,//!< Mensagem de aviso.
				Info,	//!< Mensagem de informação.
				Nothing	//!< Mensagem insignificante.
			} Type;

		private:
			///Arquivo no qual as mensagens devem ser guardadas.
			LogFile *_file;

			///Indica se as mensagens de erro devem ser mostradas em uma caixa de mensagem.
			bool _error;
			///Indica se as mensagens de aviso devem ser mostradas em uma caixa de mensagem.
			bool _warning;
			///Indica se as mensagens de informação devem ser mostradas em uma caixa de mensagem.
			bool _info;

			std::mutex _log_write_guard;

			/**
			 * Registra uma mensagem de log passada por parametro junto com o tipo e horario.
			 *
			 * @param itype Tipo da mensagem.
			 * @param idate Horario da ocorrência.
			 * @param imsg Mensagem a ser registrada.
			 */
			void write(Type itype, Date idate, string imsg);

		public:
			/**
			 * Construtor padrão, inicializa o log com valores nulos.
			 * Antes de ser utilizado deve ser inizializado pelo método init.
			 */
			Log();

			/**
			 * Finaliza a instância atual e os arquivos de log.
			 */
			~Log();

			/**
			 * Inicializa o log.
			 * @param ifilename Arquivo que deve conter os registros de eventos.
			 * @param ititle Título do registro de eventos.
			 */
			void init(string ifilename, string ititle);

			/**
			 * Exibe uma caixa de mensagem com a mensagem de log.
			 *
			 * @param itype Tipo da mensagem.
			 * @param imsg Mensagem a ser registrada.
			 */
			void show(Type itype, string imsg);

			/**
			 * Esta função é responsavel por registrar os eventos utilizando a instância atual da classe Log.
			 * Ela funciona da mesma forma que a função printf da stdio.h.
			 *
			 * @param itype Tipo da mensagem.
			 * @param iformat Formato da mesma forma do utilizado na função printf.
			 * @param ... Parametros a serem usados na mensagem, assim como usados na função printf.
			 */
			void log(Type itype, string iformat, ...);

			/**
			 * Registra um evento do tipo Error.
			 *
			 * @param iformat Formato da mesma forma do utilizado na função printf.
			 * @param ... Parametros a serem usados na mensagem, assim como usados na função printf.
			 */
			void error(string iformat, ...);

			/**
			 * Registra um evento do tipo Warning.
			 *
			 * @param iformat Formato da mesma forma do utilizado na função printf.
			 * @param ... Parametros a serem usados na mensagem, assim como usados na função printf.
			 */
			void warning(string iformat, ...);

			/**
			 * Registra um evento do tipo Info.
			 *
			 * @param iformat Formato da mesma forma do utilizado na função printf.
			 * @param ... Parametros a serem usados na mensagem, assim como usados na função printf.
			 */
			void info(string iformat, ...);

			/**
			 * Registra um evento do tipo Nothing.
			 *
			 * @param iformat Formato da mesma forma do utilizado na função printf.
			 * @param ... Parametros a serem usados na mensagem, assim como usados na função printf.
			 */
			void nothing(string iformat, ...);

			/**
			 * Esta função é responsavel por registrar os eventos utilizando a instância atual da classe Log.
			 * Ela funciona da mesma forma que a função printf da stdio.h.
			 *
			 * @param itype Tipo da mensagem.
			 * @param iformat Formato da mesma forma do utilizado na função printf.
			 * @param ... Parametros a serem usados na mensagem, assim como usados na função printf.
			 */
			void operator()(Type itype, string iformat, ...);
		};

		extern CbAPI Log log;
	}  // namespace base
}  // namespace cb
