/* 
 * - Cumulonimbus - ☁
 * File: origin.h
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

#include "./custom/origin.h"

namespace glm {
	typedef detail::torigin<float, highp>		highp_origin;
	typedef detail::torigin<float, mediump>		mediump_origin;
	typedef detail::torigin<float, lowp>		lowp_origin;
	typedef detail::torigin<double, highp>		highp_dorigin;
	typedef detail::torigin<double, mediump>	mediump_dorigin;
	typedef detail::torigin<double, lowp>		lowp_dorigin;

#if(defined(GLM_PRECISION_LOWP_FLOAT))
	typedef lowp_origin			origin;
#elif(defined(GLM_PRECISION_MEDIUMP_FLOAT))
	typedef mediump_origin		origin;
#else //defined(GLM_PRECISION_HIGHP_FLOAT)
	typedef highp_origin			origin;
#endif//GLM_PRECISION

#if(defined(GLM_PRECISION_LOWP_DOUBLE))
	typedef lowp_dorigin			dorigin;
#elif(defined(GLM_PRECISION_MEDIUMP_DOUBLE))
	typedef mediump_dorigin		dorigin;
#else //defined(GLM_PRECISION_HIGHP_DOUBLE)
	typedef highp_dorigin			dorigin;
#endif//GLM_PRECISION

	typedef detail::ttransf<float, highp>		highp_transf;
	typedef detail::ttransf<float, mediump>		mediump_transf;
	typedef detail::ttransf<float, lowp>		lowp_transf;
	typedef detail::ttransf<double, highp>		highp_dtransf;
	typedef detail::ttransf<double, mediump>	mediump_dtransf;
	typedef detail::ttransf<double, lowp>		lowp_dtransf;

#if(defined(GLM_PRECISION_LOWP_FLOAT))
	typedef lowp_transf			transf;
#elif(defined(GLM_PRECISION_MEDIUMP_FLOAT))
	typedef mediump_transf		transf;
#else //defined(GLM_PRECISION_HIGHP_FLOAT)
	typedef highp_transf			transf;
#endif//GLM_PRECISION

#if(defined(GLM_PRECISION_LOWP_DOUBLE))
	typedef lowp_dtransf			dtransf;
#elif(defined(GLM_PRECISION_MEDIUMP_DOUBLE))
	typedef mediump_dtransf		dtransf;
#else //defined(GLM_PRECISION_HIGHP_DOUBLE)
	typedef highp_dtransf			dtransf;
#endif//GLM_PRECISION
}  // namespace glm
