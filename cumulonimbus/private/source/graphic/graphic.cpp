/* 
 * - Cumulonimbus - ☁
 * File: graphic.cpp
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
#include <graphic/graphic.h>

namespace cb {
	namespace graphic {
		namespace color {
			const vec4 black			( 46.0f/256.0f,		 52.0f/256.0f,		 54.0f/256.0f,		256.0f/256.0f);
			const vec4 white			(238.0f/256.0f,		238.0f/256.0f,		236.0f/256.0f,		256.0f/256.0f);
			const vec4 red			(204.0f/256.0f,		  0.0f/256.0f,		  0.0f/256.0f,		256.0f/256.0f);
			const vec4 green			(115.0f/256.0f,		210.0f/256.0f,		 22.0f/256.0f,		256.0f/256.0f);
			const vec4 blue			( 52.0f/256.0f,		101.0f/256.0f,		164.0f/256.0f,		256.0f/256.0f);

			//Cores da paleta de cores Tango: http://tango.freedesktop.org/Tango_Icon_Theme_Guidelines
			const vec4 butter1		(252.0f/256.0f,		233.0f/256.0f,		 79.0f/256.0f,		256.0f/256.0f);
			const vec4 butter2		(237.0f/256.0f,		212.0f/256.0f,		  0.0f/256.0f,		256.0f/256.0f);
			const vec4 butter3		(196.0f/256.0f,		160.0f/256.0f,		  0.0f/256.0f,		256.0f/256.0f);

			const vec4 chameleon1		(138.0f/256.0f,		226.0f/256.0f,		 52.0f/256.0f,		256.0f/256.0f);
			const vec4 chameleon2		(115.0f/256.0f,		210.0f/256.0f,		 22.0f/256.0f,		256.0f/256.0f);
			const vec4 chameleon3		( 78.0f/256.0f,		154.0f/256.0f,		  6.0f/256.0f,		256.0f/256.0f);

			const vec4 orange1		(252.0f/256.0f,		175.0f/256.0f,		 62.0f/256.0f,		256.0f/256.0f);
			const vec4 orange2		(245.0f/256.0f,		121.0f/256.0f,		  0.0f/256.0f,		256.0f/256.0f);
			const vec4 orange3		(206.0f/256.0f,		 92.0f/256.0f,		  0.0f/256.0f,		256.0f/256.0f);
		
			const vec4 sky1			(114.0f/256.0f,		159.0f/256.0f,		207.0f/256.0f,		256.0f/256.0f);
			const vec4 sky2			( 52.0f/256.0f,		101.0f/256.0f,		164.0f/256.0f,		256.0f/256.0f);
			const vec4 sky3			( 32.0f/256.0f,		 74.0f/256.0f,		135.0f/256.0f,		256.0f/256.0f);
		
			const vec4 plum1			(173.0f/256.0f,		127.0f/256.0f,		168.0f/256.0f,		256.0f/256.0f);
			const vec4 plum2			(117.0f/256.0f,		 80.0f/256.0f,		123.0f/256.0f,		256.0f/256.0f);
			const vec4 plum3			( 92.0f/256.0f,		 53.0f/256.0f,		102.0f/256.0f,		256.0f/256.0f);
		
			const vec4 chocolate1		(233.0f/256.0f,		185.0f/256.0f,		110.0f/256.0f,		256.0f/256.0f);
			const vec4 chocolate2		(193.0f/256.0f,		125.0f/256.0f,		 17.0f/256.0f,		256.0f/256.0f);
			const vec4 chocolate3		(143.0f/256.0f,		 89.0f/256.0f,		  2.0f/256.0f,		256.0f/256.0f);
		
			const vec4 scarlet1		(239.0f/256.0f,		 41.0f/256.0f,		 41.0f/256.0f,		256.0f/256.0f);
			const vec4 scarlet2		(204.0f/256.0f,		  0.0f/256.0f,		  0.0f/256.0f,		256.0f/256.0f);
			const vec4 scarlet3		(164.0f/256.0f,		  0.0f/256.0f,		  0.0f/256.0f,		256.0f/256.0f);
		
			const vec4 aluminium1		(238.0f/256.0f,		238.0f/256.0f,		236.0f/256.0f,		256.0f/256.0f);
			const vec4 aluminium2		(211.0f/256.0f,		215.0f/256.0f,		207.0f/256.0f,		256.0f/256.0f);
			const vec4 aluminium3		(186.0f/256.0f,		189.0f/256.0f,		182.0f/256.0f,		256.0f/256.0f);
			const vec4 aluminium4		(136.0f/256.0f,		138.0f/256.0f,		133.0f/256.0f,		256.0f/256.0f);
			const vec4 aluminium5		( 85.0f/256.0f,		 87.0f/256.0f,		 83.0f/256.0f,		256.0f/256.0f);
			const vec4 aluminium6		( 46.0f/256.0f,		 52.0f/256.0f,		 54.0f/256.0f,		256.0f/256.0f);
		}  // namespace color
	}  // namespace graphic
}  // namespace cb
