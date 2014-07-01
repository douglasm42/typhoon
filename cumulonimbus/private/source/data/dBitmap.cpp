/* 
 * - Cumulonimbus - ☁
 * File: dBitmap.cpp
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
#include <data/Bitmap.h>

#include <base/Log.h>
#include <base/Exception.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stb_image.h>
#include <stb_image_write.h>
#include <png.h>

#include <climits>

#include <thread>
#include <mutex>

#define CHANNELS(x) (int(x))

#define PITCH(bytes_per_pixel, width) ((( (bytes_per_pixel) * (width) + 3) >> 2) << 2)

#define PAGE_SIZE(pitch, height) ((pitch) * (height));
#define DATA_SIZE(pitch, height, depth) (PAGE_SIZE(pitch, height) * (depth));

#define POSITION3D(x,y,z,c,pitch,page_size,channels) ((page_size)*(z) + (y)*(pitch) + (x)*(channels)+(c))
#define POSITION2D(x,y,c,pitch,channels) ((y)*(pitch) + (x)*(channels)+(c))

namespace cb {
	namespace data {
		std::mutex data_bmp_guard;

		size_t sizeType(bmp::Type itype) {
			size_t sizes[] = {
					0,				// Void

					sizeof(int8),	//Byte
					sizeof(uint8),	//UByte

					sizeof(uint16),	//Int16
					sizeof(uint16),	//UInt16

					sizeof(uint32),	//Int32
					sizeof(uint32),	//UInt32

					sizeof(float32),//Float
					sizeof(float64)	//Double
			};

			return sizes[(size_t)itype];
		}

		size_t bytesPerPixel(bmp::Format iformat, bmp::Type itype) {
			return sizeType(itype) * CHANNELS(iformat);
		}

		void Bitmap::load(size_t iwidth, size_t iheight, size_t idepth, bmp::Format iformat, bmp::Type itype) {
			clear();
			if(iformat != bmp::Format::Void && itype != bmp::Type::Void) {
				_bytes_per_pixel = bytesPerPixel(iformat, itype);
				_format = iformat;
				_type = itype;

				_width = iwidth;
				_height = iheight;
				_depth = idepth;
				_pitch = PITCH(_bytes_per_pixel,_width);

				_data = malloc(_pitch * _height * _depth);
				if(!_data) {
					Throw(tokurei::OutOfMemory);
				}
			} else {
				Throw(tokurei::LoadFailed);
			}
		}

		template<class T>
		T castByteNormalized(uint8 ibyte);

		template<>
		inline uint8 castByteNormalized<uint8>(uint8 ibyte) {
			return ibyte;
		}

		template<>
		inline int8 castByteNormalized<int8>(uint8 ibyte) {
			return uint8(int16(ibyte) + INT8_MIN);
		}

		template<>
		inline uint16 castByteNormalized<uint16>(uint8 ibyte) {
			return uint16(ibyte) * (UINT16_MAX/UINT8_MAX);
		}

		template<>
		inline int16 castByteNormalized<int16>(uint8 ibyte) {
			return int16(int32(ibyte) * (UINT16_MAX/UINT8_MAX) + INT16_MIN);
		}

		template<>
		inline uint32 castByteNormalized<uint32>(uint8 ibyte) {
			return uint32(ibyte) * (UINT32_MAX/UINT8_MAX);
		}

		template<>
		inline int32 castByteNormalized<int32>(uint8 ibyte) {
			return int32(int64(ibyte) * (UINT32_MAX/UINT8_MAX) + INT32_MIN);
		}

		template<>
		inline float castByteNormalized<float>(uint8 ibyte) {
			return float(ibyte) / float(UINT8_MAX);
		}

		template<class T>
		void copyImageLoaded(uint8 *idata, void *odata, size_t iwidth, size_t iheight, size_t ipitch, size_t ichannels) {
			size_t pitch = iwidth * ichannels;

			for(size_t y=0 ; y<iheight ; y++) {
				T *oscanline = reinterpret_cast<T *>(reinterpret_cast<uint8 *>(odata) + y * ipitch);
				uint8 *iscanline = idata + (iheight - y - 1) * pitch;

				for(size_t i=0 ; i<iwidth * ichannels ; i++) {
					(*oscanline) = castByteNormalized<T>(*iscanline);

					oscanline++;
					iscanline++;
				}
			}
		}

		template<class T>
		T castFloatNormalized(float ifloat);

		template<>
		inline uint8 castFloatNormalized<uint8>(float ifloat) {
			return uint8(ifloat * UINT8_MAX);
		}

		template<>
		inline int8 castFloatNormalized<int8>(float ifloat) {
			return uint8(int16(ifloat * UINT8_MAX) + INT8_MIN);
		}

		template<>
		inline uint16 castFloatNormalized<uint16>(float ifloat) {
			return uint16(ifloat * UINT16_MAX);
		}

		template<>
		inline int16 castFloatNormalized<int16>(float ifloat) {
			return int16(int32(ifloat * UINT16_MAX) + INT16_MIN);
		}

		template<>
		inline uint32 castFloatNormalized<uint32>(float ifloat) {
			return uint32(double(ifloat) * UINT32_MAX);
		}

		template<>
		inline int32 castFloatNormalized<int32>(float ifloat) {
			return int32(int64(double(ifloat) * UINT32_MAX) + INT32_MIN);
		}

		template<>
		inline float castFloatNormalized<float>(float ifloat) {
			return ifloat;
		}

		template<class T>
		void copyImageLoaded(float *idata, void *odata, size_t iwidth, size_t iheight, size_t ipitch, size_t ichannels) {
			size_t pitch = iwidth * ichannels;

			for(size_t y=0 ; y<iheight ; y++) {
				T *oscanline = reinterpret_cast<T *>(reinterpret_cast<uint8 *>(odata) + y * ipitch);
				float *iscanline = idata + (iheight - y - 1) * pitch;

				for(size_t i=0 ; i<iwidth * ichannels ; i++) {
					(*oscanline) = castFloatNormalized<T>(*iscanline);

					oscanline++;
					iscanline++;
				}
			}
		}

		void Bitmap::load(const File &ifile, bmp::Format iformat, bmp::Type itype) {
			if(iformat == bmp::Format::Void) {
				Throw(tokurei::LoadFailed);
			}

			if(itype == bmp::Type::Void) {
				Throw(tokurei::LoadFailed);
			}

			int w;
			int h;
			int d = 1;
			int c;

			if(!stbi_is_hdr_from_memory(reinterpret_cast<const stbi_uc *>(ifile.data()), (int)ifile.size())) {
				uint8 *stbidata = stbi_load_from_memory(reinterpret_cast<const stbi_uc *>(ifile.data()), (int)ifile.size(), &w, &h, &c, CHANNELS(iformat));

				if(!stbidata) {
					ThrowDet(tokurei::LoadFailed, "Reason: %s", stbi_failure_reason());
				}

				c = CHANNELS(iformat);

				load((size_t)w, (size_t)h, (size_t)d, iformat, itype);

				switch(itype) {
				case bmp::Type::Byte:
					copyImageLoaded<int8>(stbidata, _data, w, h, _pitch, c);
					break;
				case bmp::Type::UByte:
					copyImageLoaded<uint8>(stbidata, _data, w, h, _pitch, c);
					break;

				case bmp::Type::Int16:
					copyImageLoaded<int16>(stbidata, _data, w, h, _pitch, c);
					break;
				case bmp::Type::UInt16:
					copyImageLoaded<uint16>(stbidata, _data, w, h, _pitch, c);
					break;

				case bmp::Type::Int32:
					copyImageLoaded<int32>(stbidata, _data, w, h, _pitch, c);
					break;
				case bmp::Type::UInt32:
					copyImageLoaded<uint32>(stbidata, _data, w, h, _pitch, c);
					break;

				case bmp::Type::Float:
					copyImageLoaded<float>(stbidata, _data, w, h, _pitch, c);
					break;

				default:
					Throw(tokurei::LoadFailed);
				}

				stbi_image_free(stbidata);
			} else {

				float *stbidata = stbi_loadf_from_memory(reinterpret_cast<const stbi_uc *>(ifile.data()), (int)ifile.size(), &w, &h, &c, CHANNELS(iformat));

				if(!stbidata) {
					ThrowDet(tokurei::LoadFailed, "Reason: %s", stbi_failure_reason());
				}

				c = CHANNELS(iformat);

				load((size_t)w, (size_t)h, (size_t)d, iformat, itype);

				switch(itype) {
				case bmp::Type::Byte:
					copyImageLoaded<int8>(stbidata, _data, w, h, _pitch, c);
					break;
				case bmp::Type::UByte:
					copyImageLoaded<uint8>(stbidata, _data, w, h, _pitch, c);
					break;

				case bmp::Type::Int16:
					copyImageLoaded<int16>(stbidata, _data, w, h, _pitch, c);
					break;
				case bmp::Type::UInt16:
					copyImageLoaded<uint16>(stbidata, _data, w, h, _pitch, c);
					break;

				case bmp::Type::Int32:
					copyImageLoaded<int32>(stbidata, _data, w, h, _pitch, c);
					break;
				case bmp::Type::UInt32:
					copyImageLoaded<uint32>(stbidata, _data, w, h, _pitch, c);
					break;

				case bmp::Type::Float:
					copyImageLoaded<float>(stbidata, _data, w, h, _pitch, c);
					break;

				default:
					Throw(tokurei::LoadFailed);
				}

				stbi_image_free(stbidata);
			}
		}

		void Bitmap::load(const Bitmap &iimg) {
			clear();

			if(iimg.empty()) {
				return;
			}

			load(iimg._width, iimg._height, iimg._depth, iimg._format, iimg._type);
			size_t size = _pitch * _height * _depth;

			size = size >> 2;
			size_t *ldata = reinterpret_cast<size_t *>(_data);
			size_t *lidata = reinterpret_cast<size_t *>(iimg._data);

			for(size_t i=0 ; i<size ; ++i) {
				ldata[i] = lidata[i];
			}
		}

		void Bitmap::loadPage(const File &ifile, size_t iz) {
			if(_format == bmp::Format::Void) {
				Throw(tokurei::LoadFailed);
			}

			if(_type == bmp::Type::Void) {
				Throw(tokurei::LoadFailed);
			}

			int w;
			int h;
			int d = 1;
			int c;

			if(iz >= _depth) {
				Throw(tokurei::OutOfRange);
			}

			if(!stbi_is_hdr_from_memory(reinterpret_cast<const stbi_uc *>(ifile.data()), (int)ifile.size())) {
				uint8 *stbidata = stbi_load_from_memory(reinterpret_cast<const stbi_uc *>(ifile.data()), (int)ifile.size(), &w, &h, &c, CHANNELS(_format));

				if(_width != w || _height != h) {
					ThrowDet(tokurei::LoadFailed, "Image loaded size (%dx%d) incompatible with this image size (%dx%d)", w, h, _width, _height);
				}

				if(!stbidata) {
					ThrowDet(tokurei::LoadFailed, "Reason: %s", stbi_failure_reason());
				}

				c = CHANNELS(_format);

				switch(_type) {
				case bmp::Type::Byte:
					copyImageLoaded<int8>(stbidata, page(iz), w, h, _pitch, c);
					break;
				case bmp::Type::UByte:
					copyImageLoaded<uint8>(stbidata, page(iz), w, h, _pitch, c);
					break;

				case bmp::Type::Int16:
					copyImageLoaded<int16>(stbidata, page(iz), w, h, _pitch, c);
					break;
				case bmp::Type::UInt16:
					copyImageLoaded<uint16>(stbidata, page(iz), w, h, _pitch, c);
					break;

				case bmp::Type::Int32:
					copyImageLoaded<int32>(stbidata, page(iz), w, h, _pitch, c);
					break;
				case bmp::Type::UInt32:
					copyImageLoaded<uint32>(stbidata, page(iz), w, h, _pitch, c);
					break;

				case bmp::Type::Float:
					copyImageLoaded<float>(stbidata, page(iz), w, h, _pitch, c);
					break;

				default:
					Throw(tokurei::LoadFailed);
				}

				stbi_image_free(stbidata);
			} else {
				float *stbidata = stbi_loadf_from_memory(reinterpret_cast<const stbi_uc *>(ifile.data()), (int)ifile.size(), &w, &h, &c, CHANNELS(_format));

				if(_width != w || _height != h) {
					ThrowDet(tokurei::LoadFailed, "Image loaded size (%dx%d) incompatible with this image size (%dx%d)", w, h, _width, _height);
				}

				if(!stbidata) {
					ThrowDet(tokurei::LoadFailed, "Reason: %s", stbi_failure_reason());
				}

				c = CHANNELS(_format);

				switch(_type) {
				case bmp::Type::Byte:
					copyImageLoaded<int8>(stbidata, page(iz), w, h, _pitch, c);
					break;
				case bmp::Type::UByte:
					copyImageLoaded<uint8>(stbidata, page(iz), w, h, _pitch, c);
					break;

				case bmp::Type::Int16:
					copyImageLoaded<int16>(stbidata, page(iz), w, h, _pitch, c);
					break;
				case bmp::Type::UInt16:
					copyImageLoaded<uint16>(stbidata, page(iz), w, h, _pitch, c);
					break;

				case bmp::Type::Int32:
					copyImageLoaded<int32>(stbidata, page(iz), w, h, _pitch, c);
					break;
				case bmp::Type::UInt32:
					copyImageLoaded<uint32>(stbidata, page(iz), w, h, _pitch, c);
					break;

				case bmp::Type::Float:
					copyImageLoaded<float>(stbidata, page(iz), w, h, _pitch, c);
					break;

				default:
					Throw(tokurei::LoadFailed);
				}

				stbi_image_free(stbidata);
			}
		}

		void Bitmap::save(const base::string &ifilename) {
			if(empty()) {
				Throw(tokurei::EmptyObject);
			}
			std::lock_guard<std::mutex> lock(data_bmp_guard);

			base::log.warning("%s() : Use it only for debug.", __func__);

			if(_type == bmp::Type::Byte || _type == bmp::Type::UByte) {
				if(!stbi_write_png(ifilename.c_str(), (int)_width, (int)_height, (int)CHANNELS(_format), _data, (int)_pitch)) {
					Throw(tokurei::SaveFailed);
				}
			}
		}
	}  // namespace data
}  // namespace cb
