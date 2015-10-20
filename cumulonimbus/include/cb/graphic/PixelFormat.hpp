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
#include <cb/graphic/graphic.hpp>

#include <cb/math/math.hpp>

#ifdef CbWindows
#	include <cb/video/win32/Windows.hpp>
#endif

namespace cb {
	namespace graphic {
		enum class ColorBits : uint8 {
			c16 = 16,
			c24 = 24
		};

		enum class AlphaBits : uint8 {
			c0 = 0,
			c8 = 8
		};

		enum class DepthBits : uint8 {
			d16 = 16,
			d24 = 24
		};

		class CbAPI PixelFormat {
		private:

#			ifdef CbWindows
				int _w_pixel_format_id;
				PIXELFORMATDESCRIPTOR _w_pfd;
#			endif

			bool _valid;
			ColorBits _color_bits;
			AlphaBits _alpha_bits;
			DepthBits _depth_bits;
			bool _double_buffer;
			bool _multisample;
			uint32 _samples;

		public:
			PixelFormat();
			PixelFormat(ColorBits icolor_bits, AlphaBits ialpha_bits, DepthBits idepth_bits, bool idouble_buffer);
			PixelFormat(ColorBits icolor_bits, AlphaBits ialpha_bits, DepthBits idepth_bits, bool idouble_buffer, bool imultisample, uint32 isamples);
			~PixelFormat();

			bool validate();
			bool isValid() const;

			void setColorBits(ColorBits icolor_bits);
			ColorBits getColorBits() const;

			void setAlphaBits(AlphaBits ialpha_bits);
			AlphaBits getAlphaBits() const;

			void setDepthBits(DepthBits idepth_bits);
			DepthBits getDepthBits() const;

			void setDoubleBuffer(bool idouble_buffer);
			bool isDoubleBuffer() const;

			void setMultisample(bool imultisample);
			bool isMultisample() const;

			void setSamples(uint32 isamples);
			uint32 getSamples() const;

#			ifdef CbWindows
				int wGetPixelFormatId() const;
				PIXELFORMATDESCRIPTOR &wGetPFD();
#			endif
		};

		inline bool PixelFormat::isValid() const {return _valid;}

		inline void PixelFormat::setColorBits(ColorBits icolor_bits) {_color_bits = icolor_bits;}
		inline ColorBits PixelFormat::getColorBits() const {return _color_bits;}

		inline void PixelFormat::setAlphaBits(AlphaBits ialpha_bits) {_alpha_bits = ialpha_bits;}
		inline AlphaBits PixelFormat::getAlphaBits() const {return _alpha_bits;}

		inline void PixelFormat::setDepthBits(DepthBits idepth_bits) {_depth_bits = idepth_bits;}
		inline DepthBits PixelFormat::getDepthBits() const {return _depth_bits;}

		inline void PixelFormat::setDoubleBuffer(bool idouble_buffer) {_double_buffer = idouble_buffer;}
		inline bool PixelFormat::isDoubleBuffer() const {return _double_buffer;}

		inline void PixelFormat::setMultisample(bool imultisample) {_multisample = imultisample;}
		inline bool PixelFormat::isMultisample() const {return _multisample;}

		inline void PixelFormat::setSamples(uint32 isamples) {_samples = isamples;}
		inline uint32 PixelFormat::getSamples() const {return _samples;}

#		ifdef CbWindows
			inline int PixelFormat::wGetPixelFormatId() const {return _w_pixel_format_id;}
			inline PIXELFORMATDESCRIPTOR &PixelFormat::wGetPFD() {return _w_pfd;}
#		endif
	}  // namespace graphic
}  // namespace cb
