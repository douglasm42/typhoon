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

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stb_image.c>
#include <stb_image_write.h>
#include <png.h>

#include <climits>

#include <thread>
#include <mutex>

#define iFileToVoid(file) (static_cast<void *>(file))
#define voidToiFile(handle) (static_cast<cb::data::istream *>(handle))

#define oFileToVoid(file) (static_cast<void *>(file))
#define voidTooFile(handle) (static_cast<cb::data::istream *>(handle))

namespace cb {
	namespace data {
		std::mutex data_bmp_guard;

		namespace bmp {
			// fill 'data' with 'size' bytes.  return number of bytes actually read
			int read(void *ifile, char *idata, int isize) {
				return (int)voidToiFile(ifile)->read(idata, isize).gcount();
			}

			// skip the next 'n' bytes
			void skip(void *ifile, unsigned ioffset) {
				voidToiFile(ifile)->seekg(ioffset, std::ios::cur);
			}
			// returns nonzero if we are at end of file/data
			int eof(void *ifile) {
				return voidToiFile(ifile)->eof()?1:0;
			}
		}  // namespace data

		size_t sizeType(bmp::Type itype) {
			size_t sizes[] = {
					0,						// Void

					sizeof(math::int8),		//Byte
					sizeof(math::uint8),	//UByte

					sizeof(math::uint16),	//Int16
					sizeof(math::uint16),	//UInt16

					sizeof(math::uint32),	//Int32
					sizeof(math::uint32),	//UInt32

					sizeof(math::float32),	//Float
					sizeof(math::float64)	//Double
			};

			return sizes[(size_t)itype];
		}

		size_t channels(bmp::Format iformat) {
			size_t channelsv[] = {
					0,	// Void

					1,	//Luminance
					2,	//LA
					3,	//RGB
					4	//RGBA
			};

			return channelsv[(size_t)iformat];
		}

		size_t bytesPerPixel(bmp::Format iformat, bmp::Type itype) {
			return sizeType(itype) * channels(iformat);
		}

		void Bitmap::load(size_t iwidth, size_t iheight, bmp::Format iformat, bmp::Type itype) {
			clear();
			if(iformat != bmp::Format::Void && itype != bmp::Type::Void) {
				_bytes_per_pixel = bytesPerPixel(iformat, itype);
				_format = iformat;
				_type = itype;

				_width = iwidth;
				_height = iheight;
				_pitch = ((_bytes_per_pixel*_width + 3) >> 2) << 2;

				_data = malloc(_pitch * _height);
				if(!_data) {

				}
			} else {
				Throw(tokurei::LoadFailed);
			}
		}

		template<class T>
		void copyImageLoaded(math::uint8 *idata, T *odata, size_t iwidth, size_t iheight, size_t ipitch, size_t ichannels, T min, T max) {
			size_t bpp = sizeof(T) * ichannels;

			double range = max - min;

			for(size_t i=0 ; i<iheight ; i++) {
				for(size_t j=0 ; j<iwidth ; j++) {
					for(size_t k=0 ; k<ichannels ; k++) {
						odata[i*ipitch + j*bpp + sizeof(T)*k] = T(idata[i*iwidth*ichannels + j*ichannels+k]/255.0 * range + min);
					}
				}
			}
		}

		void Bitmap::load(istream &istream, bmp::Format iformat, bmp::Type itype) {
			if(iformat == bmp::Format::Void) {
				Throw(tokurei::LoadFailed);
			}

			if(itype == bmp::Type::Void) {
				Throw(tokurei::LoadFailed);
			}

			base::log.nothing("canais: %d -> %d", iformat, channels(iformat));

			std::lock_guard<std::mutex> lock(data_bmp_guard);

			int w;
			int h;
			int c;
			stbi_io_callbacks callbacks;
			callbacks.read = &bmp::read;
			callbacks.skip = &bmp::skip;
			callbacks.eof = &bmp::eof;

			base::log.nothing("canais: %d -> %d", (int)iformat, (int)channels(iformat));

			math::uint8 *stbidata = stbi_load_from_callbacks(&callbacks, iFileToVoid(&istream), &w, &h, &c, channels(iformat));

			base::log.nothing("canais: %d -> %d", c, channels(iformat));
			if(c != (int)channels(iformat) && false) {
				base::log.nothing("erro: %d -> %d", c, (int)channels(iformat));
				ThrowDet(tokurei::LoadFailed, "Wrong number of channels: %d from %d requested. %d", c, channels(iformat));
			}

			c = channels(iformat);

			load(w, h, iformat, itype);

			switch(itype) {
			case bmp::Type::Byte:
				copyImageLoaded(stbidata, static_cast<math::int8 *>(_data), w, h, _pitch, c, math::int8(SCHAR_MIN), math::int8(SCHAR_MAX));
				break;
			case bmp::Type::UByte:
				copyImageLoaded(stbidata, static_cast<math::uint8 *>(_data), w, h, _pitch, c, math::uint8(0), math::uint8(UCHAR_MAX));
				break;

			case bmp::Type::Int16:
				copyImageLoaded(stbidata, static_cast<math::int16 *>(_data), w, h, _pitch, c, math::int16(SHRT_MIN), math::int16(SHRT_MAX));
				break;
			case bmp::Type::UInt16:
				copyImageLoaded(stbidata, static_cast<math::uint16 *>(_data), w, h, _pitch, c, math::uint16(0), math::uint16(USHRT_MAX));
				break;

			case bmp::Type::Int32:
				copyImageLoaded(stbidata, static_cast<math::int32 *>(_data), w, h, _pitch, c, math::int32(LONG_MIN), math::int32(LONG_MAX));
				break;
			case bmp::Type::UInt32:
				copyImageLoaded(stbidata, static_cast<math::uint32 *>(_data), w, h, _pitch, c, math::uint32(0), math::uint32(ULONG_MAX));
				break;

			case bmp::Type::Float:
				copyImageLoaded(stbidata, static_cast<float *>(_data), w, h, _pitch, c, float(0.0f), float(1.0f));
				break;

			default:
				Throw(tokurei::LoadFailed);
			}

			stbi_image_free(stbidata);
		}

		void Bitmap::load(const Bitmap &iimg) {
			clear();

			if(iimg.empty()) {
				return;
			}

			load(iimg._width, iimg._height, iimg._format, iimg._type);
			size_t size = _pitch * _height;

			size = size >> 2;
			size_t *ldata = static_cast<size_t *>(_data);
			size_t *lidata = static_cast<size_t *>(iimg._data);

			for(size_t i=0 ; i<size ; ++i) {
				ldata[i] = lidata[i];
			}
		}

		void Bitmap::save(const base::string &ifilename) {
			if(empty()) {
				Throw(tokurei::EmptyObject);
			}
			std::lock_guard<std::mutex> lock(data_bmp_guard);

			base::log.warning("%s() : Use it only for debug.", __func__);

			if(_type == bmp::Type::Byte || _type == bmp::Type::UByte) {
				if(!stbi_write_png(ifilename.c_str(), _width, _height, channels(_format), _data, _pitch)) {
					Throw(tokurei::SaveFailed);
				}
			}
		}
	}  // namespace data
}  // namespace cb
