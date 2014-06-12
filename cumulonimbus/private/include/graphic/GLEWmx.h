/* 
 * - Cumulonimbus - ☁
 * File: GLEWmx.h
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

#include <graphic/graphic.h>

#include <GL/glew.h>

#ifdef CbWindows
	#include <GL/wglew.h>
#endif

#include <GL/GL.h>
#include <GL/GLU.h>

#include <base/Exception.h>

GLEWContext *glewGetContext();
void activateGLEW(GLEWContext *icontext);

#ifdef CbWindows
	WGLEWContext *wglewGetContext();
	void activateWGLEW(WGLEWContext *iwcontext);
#endif

const char *glErrorStr(GLenum error);
const char *glErrorStrDescription(GLenum error);

void glCheckError();
