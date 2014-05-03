/*
 * bRandom.h
 *
 *  Created on: 13/12/2012
 *      Author: Douglas M. Freitas
 * 
 *   Copyright: Staff 42 © 2013
 */
#pragma once

#include <base/base.h>

#include <base/String.h>
#include <base/Kin.h>

#include <vector>
#include <random>

namespace cb {
	namespace base {
		typedef std::seed_seq seed_seq;

		typedef std::mersenne_twister_engine< uint32_t, 32, 351, 175, 19, 0xccab8ee7, 11, 0xffffffff, 7, 0x31b6ab00, 15, 0xffe50000, 17, 1812433253 > mt11213b;

		typedef std::mt19937 mt19937;
		typedef std::mt19937_64 mt19937_64;

		typedef std::uniform_int_distribution<int> uniform_int_distribution;

		typedef std::uniform_real_distribution<float> uniform_float_distribution;
		typedef std::uniform_real_distribution<double> uniform_double_distribution;

		/**
		 * Classe responsavel por guardar a semente do gerador.
		 *
		 * A semente é composta somente por números inteiros sem sinal, mas
		 * pode receber strings também, que são convertidas em números por
		 * uma função hash presente no arquivo bString.h.
		 */
		class CbAPI seed {
		private:
			///Semente a ser utilizada no gerador.
			std::vector<unsigned int> _seed;

		public:
			/**
			 * Construtor padrão.
			 */
			seed();

			/**
			 * Construtor de cópia.
			 * @param iseed Semente a ser copiada.
			 */
			seed(const seed &iseed);

			/**
			 * Inicializa a semente com apenas um número.
			 * @param iseed Número a ser utilizado.
			 */
			seed(unsigned int iseed);

			/**
			 * Inicializa a semente com um vetor de números.
			 * @param ivseed Vetor contendo os números.
			 * @param in Número de elementos do vetor.
			 */
			seed(unsigned int ivseed[], size_t in);

			/**
			 * Inicializa a semente com dois números.
			 * @param iseed1 Primeiro número a ser utilizado.
			 * @param iseed2 Segundo número a ser utilizado.
			 */
			seed(unsigned int iseed1, unsigned int iseed2);

			/**
			 * Inicializa a semente com dois números.
			 * @param iseed1 Primeiro número a ser utilizado.
			 * @param iseed2 Segundo número a ser utilizado.
			 * @param iseed3 Terceiro número a ser utilizado.
			 */
			seed(unsigned int iseed1, unsigned int iseed2, unsigned int iseed3);

			/**
			 * Inicializa a semente com dois números.
			 * @param iseed1 Primeiro número a ser utilizado.
			 * @param iseed2 Segundo número a ser utilizado.
			 * @param iseed3 Terceiro número a ser utilizado.
			 * @param iseed4 Quarto número a ser utilizado.
			 */
			seed(unsigned int iseed1, unsigned int iseed2, unsigned int iseed3, unsigned int iseed4);

			/**
			 * Inicializa a semente com apenas uma string.
			 * @param iseed String a ser utilizada.
			 */
			seed(string iseed);

			/**
			 * Inicializa a semente com um vetor de strings.
			 * @param ivseed Vetor contendo as strings.
			 * @param in Número de elementos do vetor.
			 */
			seed(string ivseed[], size_t in);

			/**
			 * Inicializa a semente com duas strings.
			 * @param iseed1 Primeira string a ser utilizada.
			 * @param iseed2 Segunda string a ser utilizada.
			 */
			seed(string iseed1, string iseed2);

			/**
			 * Inicializa a semente com duas strings.
			 * @param iseed1 Primeira string a ser utilizada.
			 * @param iseed2 Segunda string a ser utilizada.
			 * @param iseed3 Terceira string a ser utilizada.
			 */
			seed(string iseed1, string iseed2, string iseed3);

			/**
			 * Inicializa a semente com duas strings.
			 * @param iseed1 Primeira string a ser utilizada.
			 * @param iseed2 Segunda string a ser utilizada.
			 * @param iseed3 Terceira string a ser utilizada.
			 * @param iseed4 Quarta string a ser utilizada.
			 */
			seed(string iseed1, string iseed2, string iseed3, string iseed4);

			/**
			 * Faiz nada!
			 */
			~seed();

			/**
			 * Cria um objeto seed_seq para ser utilizado no gerador.
			 * @return Objeto seed_seq para ser utilizado no gerador.
			 */
			seed_seq seq();

			/**
			 * Acessa o número da semente na posição passada por parametro.
			 * @param in Posição a ser acessada.
			 * @return Referência da posição do número da semente.
			 */
			unsigned int &operator[](size_t in);

			/**
			 * Acessa o número da semente na posição passada por parametro,
			 * porém não permite a alteração do mesmo.
			 * @param in Posição a ser acessada.
			 * @return Referência constante da posição do número da semente.
			 */
			const unsigned int &operator[](size_t in) const;

			/**
			 * Adiciona um número ao final do vetor de números da semente.
			 * @param iseed Número a ser adicionado.
			 */
			void add(unsigned int iseed);

			/**
			 * Adiciona o hash de uma string ao final do vetor de números da semente.
			 * @param iseed String a ser utilizada.
			 */
			void add(string iseed);

			/**
			 * Remove o número da semente na posição passada por parametro.
			 * @param in Posição a ser removida.
			 */
			void rem(size_t in);

			/**
			 * Obtém a quantidade de números da semente.
			 * @return Quantidade de números da semente.
			 */
			size_t size() const;

			/**
			 * Modifica a quantidade de elementos da semente.
			 * @param in Quantidade de elementos que a semente deve conter.
			 */
			void resize(size_t in);

			/**
			 * Remove todos os números da semente.
			 */
			void clear();

			friend class Random;
		};
	}  // namespace base
}  // namespace cb
