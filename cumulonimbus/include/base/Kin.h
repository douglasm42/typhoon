/* 
 * - Cumulonimbus - ☁
 * File: Kin.h
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

#include <cstdlib>

/**
 * Cria uma classe para encapsular um ponteiro void.
 * O ponteiro é publico, o construtor padrão zera o ponteiro
 * o de copia copia o endereço do ponteiro
 * a função empty verifica se o ponteiro é nulo.
 *
 * Qualquer alteração a ser feita no ponteiro deve ser feita usando
 * as funções da macro KinKey.
 */
#define KinLock(LockName)\
	namespace kin {\
		class LockName {\
		public:\
			void *_pointer;\
			LockName():_pointer(NULL) {}\
			LockName(const LockName &iseal):_pointer(iseal._pointer) {}\
			bool empty() const {return !_pointer;}\
		};\
	}

/**
 * Esta macro define as funções a serem usadas na manipulação do
 * ponteiro encapsulado por KinLock.
 *
 *     operator<< - Atribui um novo valor ao ponteiro.
 *     operator>> - Obtém o valor do ponteiro encapsulado.
 *     operator*  - Obtém a referência do objeto apontado pelo ponteiro encapsulado.
 *     operator&  - Obtém o valor do ponteiro encapsulado.
 */
#define KinKeyOperator(LockName, type)\
	inline LockName &operator<<(LockName &ileft, type *iright) {\
		ileft._pointer = static_cast<void *>(iright);\
		return ileft;\
	}\
	inline LockName &operator>>(LockName &ileft, type *iright) {\
		iright = static_cast<type *>(ileft._pointer);\
		return ileft;\
	}\
	inline type &operator*(LockName &iright) {\
		return *static_cast<type *>(iright._pointer);\
	}\
	inline type *operator&(LockName &iright) {\
		return static_cast<type *>(iright._pointer);\
	}

/**
 * Esta macro define as funções a serem usadas na manipulação do
 * ponteiro encapsulado por KinLock.
 *
 *     kin::pt    - Obtém o valor do ponteiro encapsulado, também disponivel na versão constante.
 *     kin::erase - Deleta o objeto apontado e zera o ponteiro encapsulado.
 */
#define KinKeyPt(LockName, type)\
	namespace kin {\
		inline type *pt(LockName &iright) {\
			return static_cast<type *>(iright._pointer);\
		}\
		inline const type *pt(const LockName &iright) {\
			return static_cast<type *>(iright._pointer);\
		}\
	}

/**
 * Esta macro define as funções a serem usadas na manipulação do
 * ponteiro encapsulado por KinLock.
 *
 *     kin::erase - Deleta o objeto apontado e zera o ponteiro encapsulado.
 */
#define KinKeyErase(LockName, type)\
	namespace kin {\
		inline void erase(LockName &iright) {\
			if(!iright.empty()) {\
				delete static_cast<type *>(iright._pointer);\
				iright._pointer = NULL;\
			}\
		}\
	}

/**
 * Esta macro define as funções a serem usadas na manipulação do
 * ponteiro encapsulado por KinLock.
 *
 *     operator<< - Atribui um novo valor ao ponteiro.
 *     operator>> - Obtém o valor do ponteiro encapsulado.
 *     operator*  - Obtém a referência do objeto apontado pelo ponteiro encapsulado.
 *     operator&  - Obtém o valor do ponteiro encapsulado.
 *     kin::pt    - Obtém o valor do ponteiro encapsulado, também disponivel na versão constante.
 */
#define KinKey(LockName, type)\
	KinKeyOperator(LockName, type)\
	KinKeyPt(LockName, type)
