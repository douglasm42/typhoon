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

#include <base/bString.h>

#include <vector>

namespace cb {
	namespace base {
		KinLock(RandomGenerator);
		KinLock(RandomDistUniformInt);
		KinLock(RandomDistUniformFloat);

		/**
		 * Classe responsavel por gerar números pseudo-aleatórios.
		 * Ela utiliza o Mersenne Twister 11213b da biblioteca Boost C++.
		 *
		 * A sub-classe Seed deve ser utilizada para configurar a semente e as
		 * sub-classes UniformInt e UniformFloat devem ser utilizadas para
		 * configurar a distribuição dos números gerados.
		 */
		class CbAPI Random {
		public:

			/**
			 * Classe responsavel por guardar a semente do gerador.
			 *
			 * A semente é composta somente por números inteiros sem sinal, mas
			 * pode receber strings também, que são convertidas em números por
			 * uma função hash presente no arquivo bString.h.
			 */
			class CbAPI Seed {
			private:
				///Semente a ser utilizada no gerador.
				std::vector<unsigned int> _seed;

			public:
				/**
				 * Construtor padrão.
				 */
				Seed();

				/**
				 * Construtor de cópia.
				 * @param iseed Semente a ser copiada.
				 */
				Seed(const Seed &iseed);

				/**
				 * Inicializa a semente com apenas um número.
				 * @param iseed Número a ser utilizado.
				 */
				Seed(unsigned int iseed);

				/**
				 * Inicializa a semente com um vetor de números.
				 * @param ivseed Vetor contendo os números.
				 * @param in Número de elementos do vetor.
				 */
				Seed(unsigned int ivseed[], size_t in);

				/**
				 * Inicializa a semente com dois números.
				 * @param iseed1 Primeiro número a ser utilizado.
				 * @param iseed2 Segundo número a ser utilizado.
				 */
				Seed(unsigned int iseed1, unsigned int iseed2);

				/**
				 * Inicializa a semente com dois números.
				 * @param iseed1 Primeiro número a ser utilizado.
				 * @param iseed2 Segundo número a ser utilizado.
				 * @param iseed3 Terceiro número a ser utilizado.
				 */
				Seed(unsigned int iseed1, unsigned int iseed2, unsigned int iseed3);

				/**
				 * Inicializa a semente com dois números.
				 * @param iseed1 Primeiro número a ser utilizado.
				 * @param iseed2 Segundo número a ser utilizado.
				 * @param iseed3 Terceiro número a ser utilizado.
				 * @param iseed4 Quarto número a ser utilizado.
				 */
				Seed(unsigned int iseed1, unsigned int iseed2, unsigned int iseed3, unsigned int iseed4);

				/**
				 * Inicializa a semente com apenas uma string.
				 * @param iseed String a ser utilizada.
				 */
				Seed(string iseed);

				/**
				 * Inicializa a semente com um vetor de strings.
				 * @param ivseed Vetor contendo as strings.
				 * @param in Número de elementos do vetor.
				 */
				Seed(string ivseed[], size_t in);

				/**
				 * Inicializa a semente com duas strings.
				 * @param iseed1 Primeira string a ser utilizada.
				 * @param iseed2 Segunda string a ser utilizada.
				 */
				Seed(string iseed1, string iseed2);

				/**
				 * Inicializa a semente com duas strings.
				 * @param iseed1 Primeira string a ser utilizada.
				 * @param iseed2 Segunda string a ser utilizada.
				 * @param iseed3 Terceira string a ser utilizada.
				 */
				Seed(string iseed1, string iseed2, string iseed3);

				/**
				 * Inicializa a semente com duas strings.
				 * @param iseed1 Primeira string a ser utilizada.
				 * @param iseed2 Segunda string a ser utilizada.
				 * @param iseed3 Terceira string a ser utilizada.
				 * @param iseed4 Quarta string a ser utilizada.
				 */
				Seed(string iseed1, string iseed2, string iseed3, string iseed4);

				/**
				 * Faiz nada!
				 */
				~Seed();

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

			/**
			 * Classe usada para distribuir os números gerados em um intervalo
			 * de números inteiros.
			 */
			class CbAPI UniformInt {
			private:
				///Objeto da boost responsavel pela distribuição.
				kin::RandomDistUniformInt _distribution;

			public:
				/**
				 * Inicializa a distribuição com o numero máximo e o mínimo
				 * passados por parametro.
				 * @param imin Menor número que pode ser gerado.
				 * @param imax Maior número que pode ser gerado.
				 */
				UniformInt(int imin, int imax);

				/**
				 * Copia uma distribuição existente.
				 * @param isrc Distribuição a ser copiada.
				 */
				UniformInt(const UniformInt &isrc);

				/**
				 * Apaga o objeto de distribuição.
				 */
				~UniformInt();

				/**
				 * Gera um número e aplica a distribuição.
				 * @param igenerator Gerador a ser utilizado.
				 * @return Número gerado.
				 */
				int operator()(Random &igenerator);

				/**
				 * Gera uma série de números e aplica a distribuição neles.
				 * @param igenerator Gerador a ser utilizado.
				 * @param ivet Endereço do vetor de números.
				 * @param in Número de números a ser gerado.
				 * @return Número gerado.
				 */
				void operator()(Random &igenerator, int *ivet, size_t in);
			};

			/**
			 * Classe usada para distribuir os números gerados em um intervalo
			 * de números de ponto flutuante.
			 */
			class CbAPI UniformFloat {
			private:
				///Objeto da boost responsavel pela distribuição.
				kin::RandomDistUniformFloat _distribution;

			public:
				/**
				 * Inicializa a distribuição com o numero máximo e o mínimo
				 * passados por parametro.
				 * @param imin Menor número que pode ser gerado.
				 * @param imax Maior número que pode ser gerado.
				 */
				UniformFloat(float imin, float imax);

				/**
				 * Copia uma distribuição existente.
				 * @param isrc Distribuição a ser copiada.
				 */
				UniformFloat(const UniformFloat &isrc);

				/**
				 * Apaga o objeto de distribuição.
				 */
				~UniformFloat();

				/**
				 * Gera um número e aplica a distribuição.
				 * @param igenerator Gerador a ser utilizado.
				 * @return Número gerado.
				 */
				float operator()(Random &igenerator);

				/**
				 * Gera uma série de números e aplica a distribuição neles.
				 * @param igenerator Gerador a ser utilizado.
				 * @param ivet Endereço do vetor de números.
				 * @param in Número de números a ser gerado.
				 * @return Número gerado.
				 */
				void operator()(Random &igenerator, float *ivet, size_t in);
			};

		private:
			///Gerador de números aleatórios da boost c++.
			kin::RandomGenerator _generator;

		public:
			/**
			 * Construtor padrão.
			 */
			Random();

			/**
			 * Inicializa o gerador com a semente passada por parametro.
			 * @param iseed Semente a ser utilizada na geração dos números.
			 */
			Random(Seed &iseed);

			/**
			 * Construtor de cópia.
			 * @param isrc Gerador a ser copiado.
			 */
			Random(const Random &isrc);

			/**
			 * Finaliza e libera a memória do gerador.
			 */
			~Random();

			/**
			 * Modifica a semente do gerador.
			 */
			void seed(Seed &iseed);

			/**
			 * Gera uma string aleatória de acordo com o formato passado por parametro.
			 * Pode ser útil para gerar nomes e senhas.
			 *
			 * O formato deve ser uma string e cada caractere representa um conjunto
			 * de caracteres a ser usado:
			 *  - <b><tt>*</tt></b> Qualquer caractere: números, letras maiúsculas e letras minusculas.
			 *  - <b><tt>d</tt></b> Caracteres de números.
			 *
			 *  - <b><tt>x</tt></b> Letras maiúsculas e letras minúsculas
			 *  - <b><tt>l</tt></b> Letras minúsculas.
			 *  - <b><tt>L</tt></b> Letras maiúsculas.
			 *
			 *  - <b><tt>a</tt></b> Qualquer vogal, minúsculas e maiúsculas.
			 *  - <b><tt>v</tt></b> Vogais minúsculas.
			 *  - <b><tt>V</tt></b> Vogais maiúsculas.
			 *
			 *  - <b><tt>b</tt></b> Qualquer consoante, minúsculas e maiúsculas.
			 *  - <b><tt>c</tt></b> Consoantes minúsculas.
			 *  - <b><tt>C</tt></b> Consoantes maiúsculas.
			 *
			 * Qualquer outro caractere utilizado no formato é copiado para a
			 * string final na mesma posição em q foi colocado.
			 * Por exemplo, "***g***" pode resultar em "5SugGsS" ou "O5Kgah6".
			 * E "Vcvc" pode ser "Olag", "Agal" ou "Ulav".
			 *
			 * @param iformat O formato a ser usado para gerar a string.
			 * @return String gerada a partir do formato.
			 */
			string str(string iformat);

			/**
			 * Funciona da mesma forma que a função str(string), mas em vez de
			 * retornar somente uma string, ela preenche um vetor de strings
			 * com as strings geradas em sequencia.
			 * @param ovet Ponteiro para o vetor de strings.
			 * @param in Quantidade de strings a serem geradas.
			 * @param iformat Formato a ser utilizado para gerar as strings.
			 */
			void str(string *ovet, size_t in, string iformat);

			friend class UniformInt;
			friend class UniformFloat;
		};
	}  // namespace base
}  // namespace cb
