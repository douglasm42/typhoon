/*
 * base.h
 *
 *  Created on: 13/12/2012
 *      Author: Douglas M. Freitas
 * 
 *   Copyright: Staff 42 © 2013
 */
#pragma once

#include <base/Setup.h>

namespace cb {
	/**
	 * @defgroup base Base
	 *
	 */

	/**
	 * @ingroup base
	 *
	 * Este namespace contém funções e classes que são utilizadas por todos os componentes do sistema,
	 * como por exemplo a função #format() ou as classes Exception, Timer e Date.
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
}  // namespace cb
