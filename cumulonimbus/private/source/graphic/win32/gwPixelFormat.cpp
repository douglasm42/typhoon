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
#include <cb/graphic/PixelFormat.h>

#include <video/win32/WindowInfo.h>

#include <graphic/GLEWmx.h>

namespace cb {
	namespace graphic {
		class CbAPI w32PixelFormat {
		public:
			int _pixel_format_id;
			PIXELFORMATDESCRIPTOR _pixel_format;
		};

		KinKey(video::kin::WindowInfo, video::w32WindowInfo);
		KinKey(kin::PixelFormatInfo, w32PixelFormat);

		PixelFormat::PixelFormat(video::Window &iwindow, BPP ibpp, Depth idepth_bits, bool idouble_buffer) {
			_info << new w32PixelFormat;
			_bpp = ibpp;
			_depth_bits = idepth_bits;
			_double_buffer = idouble_buffer;
			_multisample = false;
			_samples = 0;

			//Cria uma descrição de formato de pixel para a criação do contexto do OpenGL.
			memset(&(*_info)._pixel_format, 0, sizeof(PIXELFORMATDESCRIPTOR));
			(*_info)._pixel_format.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			(*_info)._pixel_format.nVersion = 1;
			(*_info)._pixel_format.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
			(*_info)._pixel_format.iPixelType = PFD_TYPE_RGBA;

			switch(_bpp) {
			case BPP::c16:
				(*_info)._pixel_format.cColorBits = 16;
				break;
			case BPP::c24:
				(*_info)._pixel_format.cColorBits = 24;
				break;
			case BPP::c32:
				(*_info)._pixel_format.cColorBits = 32;
				break;
			}

			switch(_depth_bits) {
			case Depth::d16:
				(*_info)._pixel_format.cDepthBits = 16;
				break;
			case Depth::d24:
				(*_info)._pixel_format.cDepthBits = 24;
				break;
			}

			if(_double_buffer) {
				(*_info)._pixel_format.dwFlags = (*_info)._pixel_format.dwFlags | PFD_DOUBLEBUFFER;
			}

			//Ativa e verifica se o formato de pixel escolhido é valido.
			int pixel_format_id = ChoosePixelFormat(GetDC((*iwindow.info()).window), &(*_info)._pixel_format);
			if(pixel_format_id == 0) {
				char *lpMsgBuf;
				DWORD dw = GetLastError(); 

				FormatMessageA(
					FORMAT_MESSAGE_ALLOCATE_BUFFER | 
					FORMAT_MESSAGE_FROM_SYSTEM |
					FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL,
					dw,
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					(LPSTR)&lpMsgBuf,
					0, NULL );
				ThrowDet(tokurei::CreateError, "Error: %s", lpMsgBuf);
			}
			(*_info)._pixel_format_id = pixel_format_id;
		}

		PixelFormat::PixelFormat(video::Window &iwindow, BPP ibpp, Depth idepth_bits, bool idouble_buffer, bool imultisample, size_t isamples) {
			_info << new w32PixelFormat;
			_bpp = ibpp;
			_depth_bits = idepth_bits;
			_double_buffer = idouble_buffer;
			_multisample = imultisample;
			_samples = isamples;

			memset(&(*_info)._pixel_format, 0, sizeof(PIXELFORMATDESCRIPTOR));
			(*_info)._pixel_format.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			(*_info)._pixel_format.nVersion = 1;
			(*_info)._pixel_format.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
			(*_info)._pixel_format.iPixelType = PFD_TYPE_RGBA;

			switch(_bpp) {
			case BPP::c16:
				(*_info)._pixel_format.cColorBits = 16;
				break;
			case BPP::c24:
				(*_info)._pixel_format.cColorBits = 24;
				break;
			case BPP::c32:
				(*_info)._pixel_format.cColorBits = 32;
				break;
			}

			switch(_depth_bits) {
			case Depth::d16:
				(*_info)._pixel_format.cDepthBits = 16;
				break;
			case Depth::d24:
				(*_info)._pixel_format.cDepthBits = 24;
				break;
			}

			if(_double_buffer) {
				(*_info)._pixel_format.dwFlags |= PFD_DOUBLEBUFFER;
			}

			if(!glewGetContext()) {
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
					WGL_COLOR_BITS_ARB,0,									//6 7
					WGL_ALPHA_BITS_ARB,0,									//8 9
					WGL_DEPTH_BITS_ARB,0,									//10 11
					WGL_STENCIL_BITS_ARB,0,									//12 13
					WGL_DOUBLE_BUFFER_ARB,idouble_buffer?GL_TRUE:GL_FALSE,	//14 15
					0,0,													//16 17
					0,0,													//18 19
					0,0
				};

				switch(_bpp) {
				case BPP::c16:
					i_attributes[7] = 16;
					i_attributes[9] = 0;
					break;
				case BPP::c24:
					i_attributes[7] = 24;
					i_attributes[9] = 0;
					break;
				case BPP::c32:
					i_attributes[7] = 24;
					i_attributes[9] = 8;
					break;
				}

				switch(_depth_bits) {
				case Depth::d16:
					i_attributes[11] = 16;
					break;
				case Depth::d24:
					i_attributes[11] = 24;
					break;
				}

				if(_multisample) {
					if(WGLEW_ARB_multisample) {
						i_attributes[16] = WGL_SAMPLE_BUFFERS_ARB;
						i_attributes[17] = GL_TRUE;
						i_attributes[18] = WGL_SAMPLES_ARB;
						i_attributes[19] = isamples;
					}
				}

				valid = wglChoosePixelFormatARB(GetDC((*iwindow.info()).window), i_attributes, f_attributes, 1, &pixel_format_id, &n_formats);
				if (valid && n_formats >= 1) {
					(*_info)._pixel_format_id = pixel_format_id;
				} else {
					ThrowDet(tokurei::CreateError, "Error: Failed to get a pixel format.");
				}

			} else {
				ThrowDet(tokurei::GLUnavailableExtension, "Error: WGL_ARB_pixel_format not available.");
			}
		}

		PixelFormat::~PixelFormat() {
			delete &_info;
		}

		void PixelFormat::set(video::Window &iwindow) {
			if(SetPixelFormat(GetDC((*iwindow.info()).window), (*_info)._pixel_format_id, &(*_info)._pixel_format) == FALSE) {
				ThrowDet(tokurei::CreateError, "Error: %d", GetLastError());
			}
		}
	}  // namespace graphic
}  // namespace cb
