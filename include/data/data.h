/*
 * data.h
 *
 *  Created on: 13/12/2012
 *      Author: Douglas M. Freitas
 * 
 *   Copyright: Staff 42 © 2013
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
		class CbAPI BinStream;

		class CbAPI File;
		class CbAPI Archiver;

		class CbAPI Database;

		class CbAPI XML;

		class CbAPI Bitmap;
		class CbAPI Font;
		class CbAPI Mesh;
	}  // namespace data
}  // namespace cb
