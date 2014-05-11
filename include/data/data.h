/* 
 * - Cumulonimbus - ☁
 * File: data.h
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

namespace cb {
	/**
	 * Este namespace contém o modulo responsavel pelo acesso a dados, como
	 * o banco de dados, arquivos binarios, XML, imagens e etc.
	 *
	 * @author Douglas Machado de Freitas
	 */
	namespace data {
		class CbAPI obinstream;
		class CbAPI ibinstream;

		class CbAPI File;
		class CbAPI Archiver;

		class CbAPI Database;

		class CbAPI JSON;
		class CbAPI XML;

		class CbAPI Bitmap;
		class CbAPI Font;
		class CbAPI Mesh;
	}  // namespace data
}  // namespace cb
