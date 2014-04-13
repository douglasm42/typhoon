/*
 * bKin.h
 *
 *  Created on: 13/12/2012
 *      Author: Douglas M. Freitas
 * 
 *   Copyright: Staff 42 © 2013
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
 *     kin::pt    - Obtém o valor do ponteiro encapsulado, também disponivel na versão constante.
 *     kin::erase - Deleta o objeto apontado e zera o ponteiro encapsulado.
 */
#define KinKey(LockName, type)\
	inline kin::LockName &operator<<(kin::LockName &ileft, type *iright) {\
		ileft._pointer = static_cast<void *>(iright);\
		return ileft;\
	}\
	inline kin::LockName &operator>>(kin::LockName &ileft, type *iright) {\
		iright = static_cast<type *>(ileft._pointer);\
		return ileft;\
	}\
	inline type &operator*(kin::LockName &iright) {\
		return *static_cast<type *>(iright._pointer);\
	}\
	inline type *operator&(kin::LockName &iright) {\
		return static_cast<type *>(iright._pointer);\
	}\
	namespace kin {\
		inline type *pt(kin::LockName &iright) {\
			return static_cast<type *>(iright._pointer);\
		}\
		inline const type *pt(const kin::LockName &iright) {\
			return static_cast<type *>(iright._pointer);\
		}\
		inline void erase(LockName &iright) {\
			if(!iright.empty()) {\
				delete static_cast<type *>(iright._pointer);\
				iright._pointer = NULL;\
			}\
		}\
	}

/**
 * Esta macro define as funções a serem usadas na manipulação do
 * ponteiro encapsulado por KinLock sem a função erase.
 *
 *     operator<< - Atribui um novo valor ao ponteiro.
 *     operator>> - Obtém o valor do ponteiro encapsulado.
 *     operator*  - Obtém a referência do objeto apontado pelo ponteiro encapsulado.
 *     operator&  - Obtém o valor do ponteiro encapsulado.
 *     kin::pt    - Obtém o valor do ponteiro encapsulado, também disponivel na versão constante.
 */
#define KinKeyWOErase(LockName, type)\
	inline kin::LockName &operator<<(kin::LockName &ileft, type *iright) {\
		ileft._pointer = static_cast<void *>(iright);\
		return ileft;\
	}\
	inline kin::LockName &operator>>(kin::LockName &ileft, type *iright) {\
		iright = static_cast<type *>(ileft._pointer);\
		return ileft;\
	}\
	inline type &operator*(kin::LockName &iright) {\
		return *static_cast<type *>(iright._pointer);\
	}\
	inline type *operator&(kin::LockName &iright) {\
		return static_cast<type *>(iright._pointer);\
	}\
	namespace kin {\
		inline type *pt(kin::LockName &iright) {\
			return static_cast<type *>(iright._pointer);\
		}\
		inline const type *pt(const kin::LockName &iright) {\
			return static_cast<type *>(iright._pointer);\
		}\
	}
