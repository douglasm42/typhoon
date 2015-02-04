/* 
 * - Cumulonimbus - ☁
 * File: Serializable.h
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

#include <cb/base/base.h>

#include <cb/base/String.h>

namespace cb {
	namespace base {
		class CbAPI Serializable {
		public:
			virtual ~Serializable() {};

			virtual void deserialize(string iobj)=0;
			virtual string serialize()=0;
		};
	}  // namespace base
}  // namespace cb
