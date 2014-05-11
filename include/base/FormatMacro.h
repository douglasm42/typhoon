/* 
 * - Cumulonimbus - ☁
 * File: FormatMacro.h
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

#include <cstdarg>
#include <cstdio>

#define BOLT_BASE_PRINTF_BUFFER_CHUNK_SIZE 1024

/**
 * Macro para a criação de funções baseadas na função printf, veja a função
 * print dos arquivos bString.h e bString.cpp para mais detalhes.
 */
#define CUMULONIMBUS_FORMAT(iresult, iformat) iresult.clear();\
for(size_t n = BOLT_BASE_PRINTF_BUFFER_CHUNK_SIZE ; iresult.empty() ; n+=BOLT_BASE_PRINTF_BUFFER_CHUNK_SIZE) {\
	char *buffer = new char[n];\
	\
	va_list args;\
	va_start(args, iformat);\
	size_t nf = vsnprintf(buffer, n, iformat.c_str(), args);\
	va_end(args);\
	\
	if(nf < n) {\
		iresult = buffer;\
	}\
	\
	delete [] buffer;\
}

