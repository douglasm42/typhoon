/* 
 * - Cumulonimbus - ☁
 * File: Random.h
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

#include <base/Kin.h>

#include <vector>
#include <random>
#include <cstdint>

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
		 * A semente é composta somente por números inteiros de 32 bits sem sinal.
		 */
		class CbAPI seed {
		private:
			///Valores da semente a ser utilizada no gerador.
			std::vector<uint32_t> _seed_values;

			///Semente a ser utilizada no gerador.
			seed_seq _seed_seq;

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
			seed(uint32_t iseed);

			/**
			 * Inicializa a semente com um vetor de números.
			 * @param ivseed Vetor contendo os números.
			 * @param in Número de elementos do vetor.
			 */
			seed(uint32_t ivseed[], size_t in);

			/**
			 * Inicializa a semente com dois números.
			 * @param iseed1 Primeiro número a ser utilizado.
			 * @param iseed2 Segundo número a ser utilizado.
			 */
			seed(uint32_t iseed1, uint32_t iseed2);

			/**
			 * Inicializa a semente com dois números.
			 * @param iseed1 Primeiro número a ser utilizado.
			 * @param iseed2 Segundo número a ser utilizado.
			 * @param iseed3 Terceiro número a ser utilizado.
			 */
			seed(uint32_t iseed1, uint32_t iseed2, uint32_t iseed3);

			/**
			 * Inicializa a semente com dois números.
			 * @param iseed1 Primeiro número a ser utilizado.
			 * @param iseed2 Segundo número a ser utilizado.
			 * @param iseed3 Terceiro número a ser utilizado.
			 * @param iseed4 Quarto número a ser utilizado.
			 */
			seed(uint32_t iseed1, uint32_t iseed2, uint32_t iseed3, uint32_t iseed4);

			/**
			 * Faiz nada!
			 */
			~seed();

			/**
			 * Cria um objeto seed_seq para ser utilizado no gerador.
			 * @return Objeto seed_seq para ser utilizado no gerador.
			 */
			seed_seq &seq();

			/**
			 * Acessa o número da semente na posição passada por parametro.
			 * @param in Posição a ser acessada.
			 * @return Referência da posição do número da semente.
			 */
			uint32_t &operator[](size_t in);

			/**
			 * Acessa o número da semente na posição passada por parametro,
			 * porém não permite a alteração do mesmo.
			 * @param in Posição a ser acessada.
			 * @return Referência constante da posição do número da semente.
			 */
			const uint32_t &operator[](size_t in) const;

			/**
			 * Adiciona um número ao final do vetor de números da semente.
			 * @param iseed Número a ser adicionado.
			 */
			void add(uint32_t iseed);

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

		inline seed::seed() {
		}

		inline seed::seed(const seed &iseed) {
			_seed_values = iseed._seed_values;
		}

		inline seed::seed(uint32_t iseed) {
			_seed_values.clear();
			_seed_values.push_back(iseed);
		}

		inline seed::seed(uint32_t ivseed[], size_t in) {
			_seed_values.clear();
			_seed_values.insert(_seed_values.begin(), ivseed, ivseed+in);
		}

		inline seed::seed(uint32_t iseed1, uint32_t iseed2) {
			_seed_values.clear();
			_seed_values.push_back(iseed1);
			_seed_values.push_back(iseed2);
		}

		inline seed::seed(uint32_t iseed1, uint32_t iseed2, uint32_t iseed3) {
			_seed_values.clear();
			_seed_values.push_back(iseed1);
			_seed_values.push_back(iseed2);
			_seed_values.push_back(iseed3);
		}

		inline seed::seed(uint32_t iseed1, uint32_t iseed2, uint32_t iseed3, uint32_t iseed4) {
			_seed_values.clear();
			_seed_values.push_back(iseed1);
			_seed_values.push_back(iseed2);
			_seed_values.push_back(iseed3);
			_seed_values.push_back(iseed4);
		}

		inline seed::~seed() {
		}

		inline seed_seq &seed::seq() {
			_seed_seq.generate(_seed_values.begin(), _seed_values.end());
			return _seed_seq;
		}

		inline uint32_t &seed::operator[](size_t in) {
			return _seed_values[in];
		}

		inline const uint32_t &seed::operator[](size_t in) const {
			return _seed_values[in];
		}

		inline void seed::add(uint32_t iseed) {
			_seed_values.push_back(iseed);
		}

		inline void seed::rem(size_t in) {
			_seed_values.erase(_seed_values.begin()+in);
		}

		inline size_t seed::size() const {
			return _seed_values.size();
		}

		inline void seed::resize(size_t in) {
			_seed_values.resize(in);
		}

		inline void seed::clear() {
			_seed_values.clear();
		}
	}  // namespace base
}  // namespace cb
