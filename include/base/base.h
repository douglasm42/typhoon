/*
 * base.h
 *
 *  Created on: 13/12/2012
 *      Author: Douglas M. Freitas
 * 
 *   Copyright: Staff 42 © 2013
 */
#pragma once

#include <base/bSetup.h>
#include <base/bKin.h>

namespace cb {
	/**
	 * @defgroup base Base
	 *
	 */

	/**
	 * @ingroup base
	 *
	 * Este namespace contém funções e classes que são utilizadas por todos os componentes do sistema.
	 * Como por exemplo a função #print() ou a classe Exception.
	 *
	 * @author Douglas Machado de Freitas
	 */
	namespace base {
		class CbAPI Log;
		class CbAPI LogFile;

		class CbAPI Timer;
		class CbAPI Date;

		class CbAPI Random;
	}  // namespace base

	using namespace base;
}  // namespace cb
