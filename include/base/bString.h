/*
 * bString.h
 *
 *  Created on: 13/12/2012
 *      Author: Douglas M. Freitas
 * 
 *   Copyright: Staff 42 © 2013
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
		typedef std::wstring wstring;
		typedef std::basic_string<unsigned int> lstring;

		/**
		 * Essa função funciona de forma semelhante à printf da stdio.h, só que a saida ela retorna como uma string.
		 * Ela foi criada para simplificar a formatação de texto com a utilização de variaveis de tipos diferentes
		 * na sua montagem.
		 *
		 * @param iformat String com a formatação, semelhante ao formato do printf.
		 * @param ... Parametros a serem usados para montar a string final.
		 * @return Uma string com o resultado da formatação.
		 */
		string CbAPI print(string iformat, ...);

		/**
		 * Converte o texto recebido por parametro de UTF8 para a codificação aceita pelo sistema.
		 * no caso do windows é ISO-8859-1.
		 * @param itext Texto a ser traduzido.
		 * @return Texto traduzido.
		 */
		wstring CbAPI sysEncode(string itext);

		/**
		 * Converte o texto recebido por parametro de UTF8 para UTF16.
		 * @param itext Texto a ser convertido.
		 * @return Texto traduzido.
		 */
		wstring CbAPI utf16(string itext);

		/**
		 * Converte o texto recebido por parametro de UTF8 para UTF32.
		 * @param itext Texto a ser convertido.
		 * @return Texto traduzido.
		 */
		lstring CbAPI utf32(string itext);

		/**
		 * Converte o texto recebido por parametro de UTF16 para UTF8.
		 * @param itext Texto a ser convertido.
		 * @return Texto traduzido.
		 */
		string CbAPI utf8(wstring itext);

		/**
		 * Converte o texto recebido por parametro de UTF16 para UTF32.
		 * @param itext Texto a ser convertido.
		 * @return Texto traduzido.
		 */
		lstring CbAPI utf32(wstring itext);

		/**
		 * Converte o texto recebido por parametro de UTF32 para UTF8.
		 * @param itext Texto a ser convertido.
		 * @return Texto traduzido.
		 */
		string CbAPI utf8(lstring itext);

		/**
		 * Converte o texto recebido por parametro de UTF32 para UTF16.
		 * @param itext Texto a ser convertido.
		 * @return Texto traduzido.
		 */
		wstring CbAPI utf16(lstring itext);

		/**
		 * Converte o texto recebido por parametro de UTF8 para a codificação passada por parametro.
		 * @param itext Texto a ser traduzido.
		 * @param iencoding Codificação alvo. Por padrão é passada a codificação do sistema.
		 * @return Texto traduzido.
		 */
		string CbAPI encode(string itext, string iencoding);

		/**
		 * Converte o texto recebido por parametro de UTF8 para a codificação passada por parametro.
		 * @param itext Texto a ser traduzido.
		 * @param iencoding Codificação alvo. Por padrão é passada a codificação do sistema.
		 * @return Texto traduzido.
		 */
		string CbAPI encode(wstring itext, string iencoding);

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

		/**
		 * Função para conversão de um inteiro para string.
		 * @param ivalue Valor a ser convertido.
		 * @return String representando o valor passado por parametro.
		 */
		string CbAPI tostr(int ivalue);

		/**
		 * Função para conversão de um inteiro sem sinal para string.
		 * @param ivalue Valor a ser convertido.
		 * @return String representando o valor passado por parametro.
		 */
		string CbAPI tostr(unsigned int ivalue);

		/**
		 * Função para conversão de um ponto flutuante para string.
		 * @param ivalue Valor a ser convertido.
		 * @return String representando o valor passado por parametro.
		 */
		string CbAPI tostr(float ivalue);

		/**
		 * Função para conversão de um ponto flutuante de precisão dupla para string.
		 * @param ivalue Valor a ser convertido.
		 * @return String representando o valor passado por parametro.
		 */
		string CbAPI tostr(double ivalue);

		/**
		 * Função para conversão de um booleano para string.
		 * @param ivalue Valor a ser convertido.
		 * @return String representando o valor passado por parametro.
		 */
		string CbAPI tostr(bool ivalue);

		/**
		 * Função para conversão de uma string para inteiro.
		 * @param istr String a ser convertida.
		 * @return Valor convertido.
		 */
		int CbAPI toint(string istr);

		/**
		 * Função para conversão de uma string para inteiro sem sinal.
		 * @param istr String a ser convertida.
		 * @return Valor convertido.
		 */
		unsigned int CbAPI touint(string istr);

		/**
		 * Função para conversão de uma string para ponto flutuante.
		 * @param istr String a ser convertida.
		 * @return Valor convertido.
		 */
		float CbAPI tofloat(string istr);

		/**
		 * Função para conversão de uma string para ponto flutuante de precisão dupla.
		 * @param istr String a ser convertida.
		 * @return Valor convertido.
		 */
		double CbAPI todouble(string istr);

		/**
		 * Função para conversão de uma string para booleano.
		 * @param istr String a ser convertida.
		 * @return Valor convertido.
		 */
		bool CbAPI tobool(string istr);

		/**
		 * Função para verificar se a string passada por parametro representa um inteiro.
		 * @param istr String a ser verificada.
		 * @return True indica que a string indica a informação esperada.
		 */
		bool CbAPI isint(string istr);

		/**
		 * Função para verificar se a string passada por parametro representa um inteiro sem sinal.
		 * @param istr String a ser verificada.
		 * @return True indica que a string indica a informação esperada.
		 */
		bool CbAPI isuint(string istr);

		/**
		 * Função para verificar se a string passada por parametro representa um ponto flutuante.
		 * @param istr String a ser verificada.
		 * @return True indica que a string indica a informação esperada.
		 */
		bool CbAPI isfloat(string istr);

		/**
		 * Função para verificar se a string passada por parametro representa um ponto flutuante de precisão dupla.
		 * @param istr String a ser verificada.
		 * @return True indica que a string indica a informação esperada.
		 */
		bool CbAPI isdouble(string istr);

		/**
		 * Função para verificar se a string passada por parametro representa um booleano.
		 * @param istr String a ser verificada.
		 * @return True indica que a string indica a informação esperada.
		 */
		bool CbAPI isbool(string istr);
	}  // namespace base
}  // namespace cb
