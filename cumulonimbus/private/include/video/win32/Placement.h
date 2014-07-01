/* 
 * - Cumulonimbus - ☁
 * File: Placement.h
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
#include <video/video.h>

#include <video/win32/Windows.h>

#include <video/Placement.h>

namespace cb {
	namespace video {
		void getPlacement(const Placement &iplacement, WINDOWPLACEMENT &oplacement);
		void getPlacement(const WINDOWPLACEMENT &iplacement, Border iborder, Placement &oplacement);
	}  // namespace video
}  // namespace cb
