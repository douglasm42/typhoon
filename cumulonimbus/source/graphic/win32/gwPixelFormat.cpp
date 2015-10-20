/* 
 * - Cumulonimbus - ☁
 * File: gwPixelFormat.cpp
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
#include <cb/graphic/PixelFormat.hpp>

#include <cb/graphic/GLEWmx.hpp>
#include <cb/graphic/DummyGLContext.hpp>

namespace cb {
	namespace graphic {
		PixelFormat::PixelFormat(ColorBits icolor_bits, AlphaBits ialpha_bits, DepthBits idepth_bits, bool idouble_buffer)
		:_w_pixel_format_id(0)
		,_valid(false)
		,_color_bits(icolor_bits)
		,_alpha_bits(ialpha_bits)
		,_depth_bits(idepth_bits)
		,_double_buffer(idouble_buffer)
		,_multisample(false)
		,_samples(0) {
		}


		PixelFormat::PixelFormat(ColorBits icolor_bits, AlphaBits ialpha_bits, DepthBits idepth_bits, bool idouble_buffer, bool imultisample, uint32 isamples)
		:_w_pixel_format_id(0)
		,_valid(false)
		,_color_bits(icolor_bits)
		,_alpha_bits(ialpha_bits)
		,_depth_bits(idepth_bits)
		,_double_buffer(idouble_buffer)
		,_multisample(imultisample)
		,_samples(isamples) {
		}

		PixelFormat::~PixelFormat() {
		}

		bool PixelFormat::validate() {
			_valid  = true;

			DummyGLContext *gl_context = nullptr;
			video::DummyWindow *window = nullptr;
			if(!glewGetContext()) {
				gl_context = new DummyGLContext();
				window = &gl_context->getWindow();
			} else {
				window = new video::DummyWindow();
			}

			memset(&_w_pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
			_w_pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			_w_pfd.nVersion = 1;
			_w_pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
			_w_pfd.iPixelType = PFD_TYPE_RGBA;
			_w_pfd.cColorBits = int(_color_bits) + int(_alpha_bits);
			_w_pfd.cDepthBits = int(_depth_bits);

			if(_double_buffer) {
				_w_pfd.dwFlags |= PFD_DOUBLEBUFFER;
			}

			if(!glewGetContext()) {
				if(gl_context) {
					delete gl_context;
				} else {
					delete window;
				}

				Throw(tokurei::GLUninitialized);
			}
			if(WGLEW_ARB_pixel_format) {
				int pixel_format_id;
				UINT n_formats = 1;
				int valid;

				float f_attributes[] = {0,0};

				int i_attributes[] =	{
					WGL_DRAW_TO_WINDOW_ARB,GL_TRUE,							//0 1
					WGL_SUPPORT_OPENGL_ARB,GL_TRUE,							//2 3
					WGL_ACCELERATION_ARB,WGL_FULL_ACCELERATION_ARB,			//4 5
					WGL_COLOR_BITS_ARB, int(_color_bits),					//6 7
					WGL_ALPHA_BITS_ARB, int(_alpha_bits),					//8 9
					WGL_DEPTH_BITS_ARB, int(_depth_bits),					//10 11
					WGL_STENCIL_BITS_ARB,0,									//12 13
					WGL_DOUBLE_BUFFER_ARB,_double_buffer?GL_TRUE:GL_FALSE,	//14 15
					0,0,													//16 17
					0,0,													//18 19
					0,0
				};

				if(_multisample) {
					if(WGLEW_ARB_multisample) {
						i_attributes[16] = WGL_SAMPLE_BUFFERS_ARB;
						i_attributes[17] = GL_TRUE;
						i_attributes[18] = WGL_SAMPLES_ARB;
						i_attributes[19] = _samples;
					}
				}

				valid = wglChoosePixelFormatARB(GetDC(window->wGetHWND()), i_attributes, f_attributes, 1, &pixel_format_id, &n_formats);
				if (valid && n_formats >= 1) {
					_w_pixel_format_id = pixel_format_id;
				} else {
					_valid = false;
				}

			} else {
				if(_multisample) {
					_valid = false;
				} else {
					//Ativa e verifica se o formato de pixel escolhido é valido.
					int pixel_format_id = ChoosePixelFormat(GetDC(window->wGetHWND()), &_w_pfd);
					if(pixel_format_id == 0) {
						_valid = false;
					}
					_w_pixel_format_id = pixel_format_id;
				}
			}

			if(gl_context) {
				delete gl_context;
			} else {
				delete window;
			}

			return _valid;
		}
	}  // namespace graphic
}  // namespace cb
