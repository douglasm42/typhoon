/* 
 * - Cumulonimbus - ☁
 * File: base.h
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
