/* 
 * - Cumulonimbus - ☁
 * File: PixelFormat.h
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
#include <cb/graphic/graphic.h>

#include <cb/base/Kin.h>

#include <cb/video/Window.h>

#include <cb/math/math.h>

namespace cb {
	namespace graphic {
		KinLock(PixelFormatInfo);

		enum class BPP : uint8 {
			c16,
			c24,
			c32
		};

		enum class Depth : uint8 {
			d16,
			d24
		};

		class PixelFormat {
		private:
			kin::PixelFormatInfo _info;

			BPP _bpp;
			Depth _depth_bits;
			bool _double_buffer;
			bool _multisample;
			size_t _samples;

		public:
			PixelFormat(video::Window &iwindow, BPP ibpp, Depth idepth_bits, bool idouble_buffer);
			PixelFormat(video::Window &iwindow, BPP ibpp, Depth idepth_bits, bool idouble_buffer, bool imultisample, size_t isamples);
			~PixelFormat();

			void set(video::Window &iwindow);

			BPP bpp() const;
			Depth depthBits() const;
			bool doublebuffer() const;
			bool multisample() const;
			size_t samples() const;
		};

		inline BPP PixelFormat::bpp() const {
			return _bpp;
		}

		inline Depth PixelFormat::depthBits() const {
			return _depth_bits;
		}

		inline bool PixelFormat::doublebuffer() const {
			return _double_buffer;
		}

		inline bool PixelFormat::multisample() const {
			return _multisample;
		}

		inline size_t PixelFormat::samples() const {
			return _samples;
		}
	}  // namespace graphic
}  // namespace cb
