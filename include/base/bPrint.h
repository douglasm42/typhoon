/*
 * bPrint.h
 *
 *  Created on: 13/12/2012
 *      Author: Douglas M. Freitas
 * 
 *   Copyright: Staff 42 © 2013
 */
#pragma once

#include <cstdarg>
#include <cstdio>

#define BOLT_BASE_PRINTF_BUFFER_CHUNK_SIZE 1024

/**
 * Macro para a criação de funções baseadas na função printf, veja a função
 * print dos arquivos bString.h e bString.cpp para mais detalhes.
 */
#define PRINT(iresult, iformat) iresult.clear();\
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

