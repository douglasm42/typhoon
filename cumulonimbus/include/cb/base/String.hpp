/* 
 * - Cumulonimbus - ☁
 * File: cb/base/String.h
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

#include <cb/base/base.hpp>

#include <cstdlib>
#include <string>

namespace cb {
	/**
	 * 
	 * @author Douglas M. Freitas
	 */
	namespace base {
		typedef std::string string;
		typedef std::wstring wstring;
		typedef std::u16string string16;
		typedef std::u32string string32;

		/**
		 * Essa função funciona de forma semelhante à printf da stdio.h, só que a saida ela retorna como uma string.
		 * Ela foi criada para simplificar a formatação de texto com a utilização de variaveis de tipos diferentes
		 * na sua montagem.
		 *
		 * @param iformat String com a formatação, semelhante ao formato do printf.
		 * @param ... Parametros a serem usados para montar a string final.
		 * @return Uma string com o resultado da formatação.
		 */
		string CbAPI format(const string &iformat, ...);

		/**
		 * Essa função funciona de forma semelhante à printf da stdio.h, só que a saida ela retorna como uma string.
		 * Ela foi criada para simplificar a formatação de texto com a utilização de variaveis de tipos diferentes
		 * na sua montagem.
		 * 
		 * Versão wstring.
		 * 
		 * @param iformat String com a formatação, semelhante ao formato do printf.
		 * @param ... Parametros a serem usados para montar a string final.
		 * @return Uma string com o resultado da formatação.
		 */
		wstring CbAPI format(const wstring &iformat, ...);

		/**
		 * Essa função funciona de forma semelhante à printf da stdio.h, só que a saida ela retorna como uma string.
		 * Ela foi criada para simplificar a formatação de texto com a utilização de variaveis de tipos diferentes
		 * na sua montagem.
		 * 
		 * Versão string16.
		 * 
		 * @param iformat String com a formatação, semelhante ao formato do printf.
		 * @param ... Parametros a serem usados para montar a string final.
		 * @return Uma string com o resultado da formatação.
		 */
		string16 CbAPI format(const string16 &iformat, ...);

		/**
		 * Essa função funciona de forma semelhante à printf da stdio.h, só que a saida ela retorna como uma string.
		 * Ela foi criada para simplificar a formatação de texto com a utilização de variaveis de tipos diferentes
		 * na sua montagem.
		 * 
		 * Versão string32.
		 * 
		 * @param iformat String com a formatação, semelhante ao formato do printf.
		 * @param ... Parametros a serem usados para montar a string final.
		 * @return Uma string com o resultado da formatação.
		 */
		string32 CbAPI format(const string32 &iformat, ...);

		/**
		 * Converte o texto recebido por parametro de WCHAR para UTF8.
		 * @param itext Texto a ser convertido.
		 * @return Texto convertido.
		 */
		string CbAPI utf8(const wstring &itext);

		/**
		 * Converte o texto recebido por parametro de UTF16 para UTF8.
		 * @param itext Texto a ser convertido.
		 * @return Texto convertido.
		 */
		string CbAPI utf8(const string16 &itext);

		/**
		 * Converte o texto recebido por parametro de UTF32 para UTF8.
		 * @param itext Texto a ser convertido.
		 * @return Texto convertido.
		 */
		string CbAPI utf8(const string32 &itext);

		/**
		 * Converte o texto recebido por parametro de UTF8 para WCHAR.
		 * @param itext Texto a ser convertido.
		 * @return Texto convertido.
		 */
		wstring CbAPI wstr(const string &itext);

		/**
		 * Converte o texto recebido por parametro de UTF16 para WCHAR.
		 * @param itext Texto a ser convertido.
		 * @return Texto convertido.
		 */
		wstring CbAPI wstr(const string16 &itext);

		/**
		 * Converte o texto recebido por parametro de UTF32 para WCHAR.
		 * @param itext Texto a ser convertido.
		 * @return Texto convertido.
		 */
		wstring CbAPI wstr(const string32 &itext);

		/**
		 * Converte o texto recebido por parametro de UTF8 para UTF16.
		 * @param itext Texto a ser convertido.
		 * @return Texto convertido.
		 */
		string16 CbAPI utf16(const string &itext);

		/**
		 * Converte o texto recebido por parametro de WCHAR para UTF16.
		 * @param itext Texto a ser convertido.
		 * @return Texto convertido.
		 */
		string16 CbAPI utf16(const wstring &itext);

		/**
		 * Converte o texto recebido por parametro de UTF32 para UTF16.
		 * @param itext Texto a ser convertido.
		 * @return Texto convertido.
		 */
		string16 CbAPI utf16(const string32 &itext);

		/**
		 * Converte o texto recebido por parametro de UTF8 para UTF32.
		 * @param itext Texto a ser convertido.
		 * @return Texto convertido.
		 */
		string32 CbAPI utf32(const string &itext);

		/**
		 * Converte o texto recebido por parametro de WCHAR para UTF32.
		 * @param itext Texto a ser convertido.
		 * @return Texto convertido.
		 */
		string32 CbAPI utf32(const wstring &itext);

		/**
		 * Converte o texto recebido por parametro de UTF16 para UTF32.
		 * @param itext Texto a ser convertido.
		 * @return Texto convertido.
		 */
		string32 CbAPI utf32(const string16 &itext);

		/**
		 * Função para converter uma string para caixa alta. Versão UTF8.
		 * @param istr String a ser convetida.
		 * @return String String em caixa alta.
		 */
		string CbAPI upper(const string &istr);

		/**
		 * Função para converter uma string para caixa alta. Versão WCHAR.
		 * @param istr String a ser convetida.
		 * @return String String em caixa alta.
		 */
		wstring CbAPI upper(const wstring &istr);

		/**
		 * Função para converter uma string para caixa alta. Versão UTF16.
		 * @param istr String a ser convetida.
		 * @return String String em caixa alta.
		 */
		string16 CbAPI upper(const string16 &istr);

		/**
		 * Função para converter uma string para caixa alta. Versão UTF32.
		 * @param istr String a ser convetida.
		 * @return String String em caixa alta.
		 */
		string32 CbAPI upper(const string32 &istr);

		/**
		 * Função para converter uma string para caixa baixa. Versão UTF8.
		 * @param istr String a ser convetida.
		 * @return String String em caixa baixa.
		 */
		string CbAPI lower(const string &istr);

		/**
		 * Função para converter uma string para caixa baixa. Versão WCHAR.
		 * @param istr String a ser convetida.
		 * @return String String em caixa baixa.
		 */
		wstring CbAPI lower(const wstring &istr);

		/**
		 * Função para converter uma string para caixa baixa. Versão UTF16.
		 * @param istr String a ser convetida.
		 * @return String String em caixa baixa.
		 */
		string16 CbAPI lower(const string16 &istr);

		/**
		 * Função para converter uma string para caixa baixa. Versão UTF32.
		 * @param istr String a ser convetida.
		 * @return String String em caixa baixa.
		 */
		string32 CbAPI lower(const string32 &istr);

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
		string CbAPI trim(const string &istr, int iflags = TrimLeft | TrimRight | TrimInner);

		/**
		 * Função hash simples para string.
		 *
		 * @param istr String a ser processada.
		 * @return Resultado da função hash.
		 */
		size_t CbAPI hash(const string &istr);
	}  // namespace base
}  // namespace cb
