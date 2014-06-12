/* 
 * - Cumulonimbus - ☁
 * File: String.h
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

#include <cstdlib>
#include <string>

namespace cb {
	/**
	 * 
	 * @author Douglas M. Freitas
	 */
	namespace base {
		typedef std::string string;
		typedef std::basic_string<char16_t> string16;
		typedef std::basic_string<char32_t> string32;

		/**
		 * Essa função funciona de forma semelhante à printf da stdio.h, só que a saida ela retorna como uma string.
		 * Ela foi criada para simplificar a formatação de texto com a utilização de variaveis de tipos diferentes
		 * na sua montagem.
		 *
		 * @param iformat String com a formatação, semelhante ao formato do printf.
		 * @param ... Parametros a serem usados para montar a string final.
		 * @return Uma string com o resultado da formatação.
		 */
		string CbAPI format(string iformat, ...);

		/**
		 * Converte o texto recebido por parametro de UTF8 para UTF16.
		 * @param itext Texto a ser convertido.
		 * @return Texto traduzido.
		 */
		string16 CbAPI utf16(string itext);

		/**
		 * Converte o texto recebido por parametro de UTF8 para UTF32.
		 * @param itext Texto a ser convertido.
		 * @return Texto traduzido.
		 */
		string32 CbAPI utf32(string itext);

		/**
		 * Converte o texto recebido por parametro de UTF16 para UTF8.
		 * @param itext Texto a ser convertido.
		 * @return Texto traduzido.
		 */
		string CbAPI utf8(string16 itext);

		/**
		 * Converte o texto recebido por parametro de UTF16 para UTF32.
		 * @param itext Texto a ser convertido.
		 * @return Texto traduzido.
		 */
		string32 CbAPI utf32(string16 itext);

		/**
		 * Converte o texto recebido por parametro de UTF32 para UTF8.
		 * @param itext Texto a ser convertido.
		 * @return Texto traduzido.
		 */
		string CbAPI utf8(string32 itext);

		/**
		 * Converte o texto recebido por parametro de UTF32 para UTF16.
		 * @param itext Texto a ser convertido.
		 * @return Texto traduzido.
		 */
		string16 CbAPI utf16(string32 itext);

		/**
		 * Função para converter uma string para caixa alta.
		 * @param istr String a ser convetida.
		 * @return String String em caixa alta.
		 */
		string CbAPI upper(string istr);

		/**
		 * Função para converter uma string para caixa baixa.
		 * @param istr String a ser convetida.
		 * @return String String em caixa baixa.
		 */
		string CbAPI lower(string istr);

		/**
		 * Determina o comportamento da função trim.
		 */
		typedef enum TrimFlags {
			TrimLeft	= 1<<1, //!< TrimLeft Remove caracteres brancos no inicio da string.
			TrimRight	= 1<<2,//!< TrimRight Remove caracteres brancos no final da string.
			TrimInner	= 1<<3 //!< TrimInner Remove caracteres brancos extras no meio da string.
		} TrimFlags;

		/**
		 * Remove caracteres brancos excessivos  da string passada por parametro.
		 * O comportamento dela é controlado pelo parametro iflags, de acordo com
		 * o enum TrimFlags.
		 *
		 * @param istr String a ser processada.
		 * @param iflags Comportamento a ser seguido pela função, por padrão as três remoções são executadas.
		 * @return String com os espaços removidos.
		 */
		string CbAPI trim(string istr, int iflags = TrimLeft | TrimRight | TrimInner);

		/**
		 * Função hash simples para string.
		 *
		 * @param istr String a ser processada.
		 * @return Resultado da função hash.
		 */
		unsigned int hash(string istr);
	}  // namespace base
}  // namespace cb
