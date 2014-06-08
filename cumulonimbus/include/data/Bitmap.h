/* 
 * - Cumulonimbus - ☁
 * File: Bitmap.h
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

#include <data/data.h>

#include <math/math.h>
#include <data/File.h>

namespace cb {
	namespace data {
		namespace bmp {
			typedef enum Format {
				FormatVoid = 0,

				Luminance,
				LA,
				RGB,
				RGBA,
			} Format;

			typedef enum Type {
				TypeVoid = 0,

				Byte,
				UByte,

				Int16,
				UInt16,

				Int32,
				UInt32,

				Float,
				Double,
			} Type;

			template<typename T, math::precision P>
			struct CbAPI tLA {
				T l;
				T a;

				math::detail::tvec2<T, P> vec() {return math::detail::tvec2<T, P>(l, a);}
				tLA &operator=(const math::detail::tvec2<T, P> &ivec) {l = ivec.r; a = ivec.g; return *this;}
			};

			template<typename T, math::precision P>
			struct CbAPI tRGB {
				T r;
				T g;
				T b;

				math::detail::tvec3<T, P> vec() {return math::detail::tvec3<T, P>(r, g, b);}
				tRGB &operator=(const math::detail::tvec3<T, P> &ivec) {r = ivec.r; g = ivec.g; b = ivec.b; return *this;}
			};

			template<typename T, math::precision P>
			struct CbAPI tRGBA {
				T r;
				T g;
				T b;
				T a;

				math::detail::tvec4<T, P> vec() {return math::detail::tvec4<T, P>(r, g, b, a);}
				tRGBA &operator=(const math::detail::tvec4<T, P> &ivec) {r = ivec.r; g = ivec.g; b = ivec.b; a = ivec.a; return *this;}
			};

			typedef struct tLA<math::int8, math::defaultp> bLA;
			typedef struct tRGB<math::int8, math::defaultp> bRGB;
			typedef struct tRGBA<math::int8, math::defaultp> bRGBA;

			typedef struct tLA<math::int16, math::defaultp> sLA;
			typedef struct tRGB<math::int16, math::defaultp> sRGB;
			typedef struct tRGBA<math::int16, math::defaultp> sRGBA;

			typedef struct tLA<math::int32, math::defaultp> lLA;
			typedef struct tRGB<math::int32, math::defaultp> lRGB;
			typedef struct tRGBA<math::int32, math::defaultp> lRGBA;

			typedef struct tLA<math::uint8, math::defaultp> ubLA;
			typedef struct tRGB<math::uint8, math::defaultp> ubRGB;
			typedef struct tRGBA<math::uint8, math::defaultp> ubRGBA;

			typedef struct tLA<math::uint16, math::defaultp> usLA;
			typedef struct tRGB<math::uint16, math::defaultp> usRGB;
			typedef struct tRGBA<math::uint16, math::defaultp> usRGBA;

			typedef struct tLA<math::uint32, math::defaultp> ulLA;
			typedef struct tRGB<math::uint32, math::defaultp> ulRGB;
			typedef struct tRGBA<math::uint32, math::defaultp> ulRGBA;

			typedef struct tLA<float, math::defaultp> fLA;
			typedef struct tRGB<float, math::defaultp> fRGB;
			typedef struct tRGBA<float, math::defaultp> fRGBA;

			typedef struct tLA<double, math::defaultp> dLA;
			typedef struct tRGB<double, math::defaultp> dRGB;
			typedef struct tRGBA<double, math::defaultp> dRGBA;
		}  // namespace bmp

		class CbAPI Bitmap {
		protected:
			size_t _width;
			size_t _height;
			size_t _pitch;

			size_t _bytes_per_pixel;
			bmp::Format _format;
			bmp::Type _type;

			void *_data;

		public:
			Bitmap()
			: _width(0), _height(0), _pitch(0), _bytes_per_pixel(0), _format(bmp::FormatVoid), _type(bmp::TypeVoid), _data(NULL) {
			}

			Bitmap(size_t iwidth, size_t iheight, bmp::Format iformat, bmp::Type itype)
			: _width(0), _height(0), _pitch(0), _bytes_per_pixel(0), _format(bmp::FormatVoid), _type(bmp::TypeVoid), _data(NULL) {
				load(iwidth, iheight, iformat, itype);
			}

			Bitmap(istream &istream, bmp::Format iformat, bmp::Type itype)
			: _width(0), _height(0), _pitch(0), _bytes_per_pixel(0), _format(bmp::FormatVoid), _type(bmp::TypeVoid), _data(NULL) {
				load(istream, iformat, itype);
			}

			Bitmap(const Bitmap &isrc)
			: _width(0), _height(0), _pitch(0), _bytes_per_pixel(0), _format(bmp::FormatVoid), _type(bmp::TypeVoid), _data(NULL) {
				load(isrc);
			}

			virtual ~Bitmap() {clear();}

			virtual size_t width() const {return _width;}
			virtual size_t height() const {return _height;}
			virtual size_t pitch() const {return _pitch;}

			virtual size_t bpp() const {return _bytes_per_pixel;}
			virtual bmp::Format format() const {return _format;}
			virtual bmp::Type type() const {return _type;}

			virtual void *data() {return _data;}
			virtual const void *data() const {return _data;}

			virtual bool empty() const {return !_data;}
			virtual void clear() {
				if(_data) {
					free(_data);
					_width = 0;
					_height = 0;
					_pitch = 0;

					_bytes_per_pixel = 0;
					_format = bmp::FormatVoid;
					_type = bmp::TypeVoid;

					_data = NULL;
				}
			}

			void load(size_t iwidth, size_t iheight, bmp::Format iformat, bmp::Type itype);
			void load(istream &istream, bmp::Format iformat, bmp::Type itype);
			void load(const Bitmap &iimg);

			virtual void save(const base::string &ifilename);
		};

		template<typename T, bmp::Format f, bmp::Type t>
		class BitmapBase : private Bitmap {
		public:
			BitmapBase()
			: Bitmap() {
			}

			BitmapBase(size_t iwidth, size_t iheight)
			: Bitmap(iwidth, iheight, f, t) {
			}

			inline BitmapBase(istream &istream)
			: Bitmap(istream, f, t) {
			}

			BitmapBase(const BitmapBase<T,f,t> &isrc)
			: Bitmap(isrc) {
			}

			virtual ~BitmapBase() {}

			virtual size_t width() const {return Bitmap::width();}
			virtual size_t height() const {return Bitmap::height();}
			virtual size_t pitch() const {return Bitmap::pitch();}

			virtual size_t bpp() const {return Bitmap::bpp();}
			virtual bmp::Format format() const {return Bitmap::format();}
			virtual bmp::Type type() const {return Bitmap::type();}

			virtual T *row(size_t ir) {return (T*)((char*)_data + pitch()*ir);}
			virtual const T *row(size_t ir) const {return (T*)((char*)_data + pitch()*ir);}

			virtual bool empty() const {return !Bitmap::data();}
			virtual void clear() {Bitmap::clear();}

			void load(size_t iwidth, size_t iheight) {Bitmap::load(iwidth, iheight, f, t);}
			void load(istream &istream) {Bitmap::load(istream, f, t);}
			void load(const BitmapBase<T,f,t> &iimg) {Bitmap::load(iimg);}

			virtual void save(const base::string &ifilename) {Bitmap::save(ifilename);}

			T &operator()(size_t ix, size_t iy) {
				return *((T*)((char *)data() + pitch()*iy) + ix);
			}

			const T &operator()(size_t ix, size_t iy) const {
				return *((T*)((char *)data() + pitch()*iy) + ix);
			}
		};

		//Signed Byte
		typedef BitmapBase<math::int8, bmp::Luminance, bmp::Byte> bBitmapL;
		typedef BitmapBase<bmp::bLA, bmp::LA, bmp::Byte> bBitmapLA;
		typedef BitmapBase<bmp::bRGB, bmp::RGB, bmp::Byte> bBitmapRGB;
		typedef BitmapBase<bmp::bRGBA, bmp::RGBA, bmp::Byte> bBitmapRGBA;

		//Unsigned Byte
		typedef BitmapBase<math::uint8, bmp::Luminance, bmp::UByte> ubBitmapL;
		typedef BitmapBase<bmp::ubLA, bmp::LA, bmp::UByte> ubBitmapLA;
		typedef BitmapBase<bmp::ubRGB, bmp::RGB, bmp::UByte> ubBitmapRGB;
		typedef BitmapBase<bmp::ubRGBA, bmp::RGBA, bmp::UByte> ubBitmapRGBA;

		//Signed Short
		typedef BitmapBase<math::int16, bmp::Luminance, bmp::Int16> sBitmapL;
		typedef BitmapBase<bmp::sLA, bmp::LA, bmp::Int16> sBitmapLA;
		typedef BitmapBase<bmp::sRGB, bmp::RGB, bmp::Int16> sBitmapRGB;
		typedef BitmapBase<bmp::sRGBA, bmp::RGBA, bmp::Int16> sBitmapRGBA;

		//Unsigned Short
		typedef BitmapBase<math::uint16, bmp::Luminance, bmp::UInt16> usBitmapL;
		typedef BitmapBase<bmp::usLA, bmp::LA, bmp::UInt16> usBitmapLA;
		typedef BitmapBase<bmp::usRGB, bmp::RGB, bmp::UInt16> usBitmapRGB;
		typedef BitmapBase<bmp::usRGBA, bmp::RGBA, bmp::UInt16> usBitmapRGBA;

		//Signed Int
		typedef BitmapBase<math::int32, bmp::Luminance, bmp::Int32> lBitmapL;
		typedef BitmapBase<bmp::lLA, bmp::LA, bmp::Int32> lBitmapLA;
		typedef BitmapBase<bmp::lRGB, bmp::RGB, bmp::Int32> lBitmapRGB;
		typedef BitmapBase<bmp::lRGBA, bmp::RGBA, bmp::Int32> lBitmapRGBA;

		//Unsigned Int
		typedef BitmapBase<math::uint32, bmp::Luminance, bmp::UInt32> ulBitmapL;
		typedef BitmapBase<bmp::ulLA, bmp::LA, bmp::UInt32> ulBitmapLA;
		typedef BitmapBase<bmp::ulRGB, bmp::RGB, bmp::UInt32> ulBitmapRGB;
		typedef BitmapBase<bmp::ulRGBA, bmp::RGBA, bmp::UInt32> ulBitmapRGBA;

		//Float
		typedef BitmapBase<float, bmp::Luminance, bmp::Float> fBitmapL;
		typedef BitmapBase<bmp::fLA, bmp::LA, bmp::Float> fBitmapLA;
		typedef BitmapBase<bmp::fRGB, bmp::RGB, bmp::Float> fBitmapRGB;
		typedef BitmapBase<bmp::fRGBA, bmp::RGBA, bmp::Float> fBitmapRGBA;

		//Double
		typedef BitmapBase<double, bmp::Luminance, bmp::Double> dBitmapL;
		typedef BitmapBase<bmp::dLA, bmp::LA, bmp::Double> dBitmapLA;
		typedef BitmapBase<bmp::dRGB, bmp::RGB, bmp::Double> dBitmapRGB;
		typedef BitmapBase<bmp::dRGBA, bmp::RGBA, bmp::Double> dBitmapRGBA;
	}  // namespace data
}  // namespace cb
