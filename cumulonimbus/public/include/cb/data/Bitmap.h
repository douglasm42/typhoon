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

#include <cb/data/data.h>

#include <cb/math/math.h>
#include <cb/data/File.h>

#include <vector>

namespace cb {
	namespace data {
		namespace bmp {
			enum class Format {
				Void = 0,

				Luminance,
				LA,
				RGB,
				RGBA,
			};

			enum class Type {
				Void = 0,

				Byte,
				UByte,

				Int16,
				UInt16,

				Int32,
				UInt32,

				Float,
			};

			template<typename T, precision P>
			struct tLA {
				T l;
				T a;

				detail::tvec2<T, P> vec() {return detail::tvec2<T, P>(l, a);}
				tLA &operator=(const detail::tvec2<T, P> &ivec) {l = ivec.r; a = ivec.g; return *this;}
			};

			template<typename T, precision P>
			struct tRGB {
				T r;
				T g;
				T b;

				detail::tvec3<T, P> vec() {return detail::tvec3<T, P>(r, g, b);}
				tRGB &operator=(const detail::tvec3<T, P> &ivec) {r = ivec.r; g = ivec.g; b = ivec.b; return *this;}
			};

			template<typename T, precision P>
			struct tRGBA {
				T r;
				T g;
				T b;
				T a;

				detail::tvec4<T, P> vec() {return detail::tvec4<T, P>(r, g, b, a);}
				tRGBA &operator=(const detail::tvec4<T, P> &ivec) {r = ivec.r; g = ivec.g; b = ivec.b; a = ivec.a; return *this;}
			};

			typedef struct tLA<int8, defaultp> bLA;
			typedef struct tRGB<int8, defaultp> bRGB;
			typedef struct tRGBA<int8, defaultp> bRGBA;

			typedef struct tLA<int16, defaultp> sLA;
			typedef struct tRGB<int16, defaultp> sRGB;
			typedef struct tRGBA<int16, defaultp> sRGBA;

			typedef struct tLA<int32, defaultp> lLA;
			typedef struct tRGB<int32, defaultp> lRGB;
			typedef struct tRGBA<int32, defaultp> lRGBA;

			typedef struct tLA<uint8, defaultp> ubLA;
			typedef struct tRGB<uint8, defaultp> ubRGB;
			typedef struct tRGBA<uint8, defaultp> ubRGBA;

			typedef struct tLA<uint16, defaultp> usLA;
			typedef struct tRGB<uint16, defaultp> usRGB;
			typedef struct tRGBA<uint16, defaultp> usRGBA;

			typedef struct tLA<uint32, defaultp> ulLA;
			typedef struct tRGB<uint32, defaultp> ulRGB;
			typedef struct tRGBA<uint32, defaultp> ulRGBA;

			typedef struct tLA<float, defaultp> fLA;
			typedef struct tRGB<float, defaultp> fRGB;
			typedef struct tRGBA<float, defaultp> fRGBA;

			CbTemplate template struct CbAPI tLA<int8, defaultp>;
			CbTemplate template struct CbAPI tRGB<int8, defaultp>;
			CbTemplate template struct CbAPI tRGBA<int8, defaultp>;

			CbTemplate template struct CbAPI tLA<int16, defaultp>;
			CbTemplate template struct CbAPI tRGB<int16, defaultp>;
			CbTemplate template struct CbAPI tRGBA<int16, defaultp>;

			CbTemplate template struct CbAPI tLA<int32, defaultp>;
			CbTemplate template struct CbAPI tRGB<int32, defaultp>;
			CbTemplate template struct CbAPI tRGBA<int32, defaultp>;

			CbTemplate template struct CbAPI tLA<uint8, defaultp>;
			CbTemplate template struct CbAPI tRGB<uint8, defaultp>;
			CbTemplate template struct CbAPI tRGBA<uint8, defaultp>;

			CbTemplate template struct CbAPI tLA<uint16, defaultp>;
			CbTemplate template struct CbAPI tRGB<uint16, defaultp>;
			CbTemplate template struct CbAPI tRGBA<uint16, defaultp>;

			CbTemplate template struct CbAPI tLA<uint32, defaultp>;
			CbTemplate template struct CbAPI tRGB<uint32, defaultp>;
			CbTemplate template struct CbAPI tRGBA<uint32, defaultp>;

			CbTemplate template struct CbAPI tLA<float, defaultp>;
			CbTemplate template struct CbAPI tRGB<float, defaultp>;
			CbTemplate template struct CbAPI tRGBA<float, defaultp>;
		}  // namespace bmp

		class CbAPI Bitmap {
		protected:
			size_t _width;
			size_t _height;
			size_t _depth;
			size_t _pitch;

			size_t _bytes_per_pixel;
			bmp::Format _format;
			bmp::Type _type;

			void *_data;

		public:
			Bitmap();
			Bitmap(size_t iwidth, size_t iheight, size_t idepth, bmp::Format iformat, bmp::Type itype);
			Bitmap(const File &ifile, bmp::Format iformat, bmp::Type itype);
			Bitmap(const Bitmap &isrc);

			~Bitmap();

			size_t width() const;
			size_t height() const;
			size_t depth() const;
			size_t pitch() const;

			size_t bpp() const;
			bmp::Format format() const;
			bmp::Type type() const;

			void *data();
			void *page(size_t iz);
			void *row(size_t iy, size_t iz);

			const void *data() const;
			const void *page(size_t iz) const;
			const void *row(size_t iy, size_t iz) const;

			bool empty() const;
			void clear();

			void load(size_t iwidth, size_t iheight, size_t idepth, bmp::Format iformat, bmp::Type itype);
			void load(const File &ifile, bmp::Format iformat, bmp::Type itype);
			void load(const Bitmap &iimg);

			void loadPage(const File &ifile, size_t iz);

			void save(const base::string &ifilename);
		};

		template<typename T, bmp::Format f, bmp::Type t>
		class BitmapBase {
		private:
			Bitmap _bitmap;

		public:
			BitmapBase();
			BitmapBase(size_t iwidth, size_t iheight, size_t idepth);
			BitmapBase(const File &ifile);
			BitmapBase(const BitmapBase<T,f,t> &isrc);
			~BitmapBase();

			size_t width() const;
			size_t height() const;
			size_t depth() const;

			size_t bpp() const;
			bmp::Format format() const;
			bmp::Type type() const;

			T *row(size_t iy, size_t iz);
			const T *row(size_t iy, size_t iz) const;

			bool empty() const;
			void clear();

			void load(size_t iwidth, size_t iheight, size_t idepth);
			void load(const File &ifile);
			void load(const BitmapBase<T,f,t> &iimg);

			void save(const base::string &ifilename);

			T &operator()(size_t ix, size_t iy, size_t iz);
			const T &operator()(size_t ix, size_t iy, size_t iz) const;

			const Bitmap &bitmap() const;
		};

		inline Bitmap::Bitmap()
		: _width(0), _height(0), _depth(0), _pitch(0), _bytes_per_pixel(0), _format(bmp::Format::Void), _type(bmp::Type::Void), _data(nullptr) {
		}

		inline Bitmap::Bitmap(size_t iwidth, size_t iheight, size_t idepth, bmp::Format iformat, bmp::Type itype)
		: _width(0), _height(0), _depth(0), _pitch(0), _bytes_per_pixel(0), _format(bmp::Format::Void), _type(bmp::Type::Void), _data(nullptr) {
			load(iwidth, iheight, idepth, iformat, itype);
		}

		inline Bitmap::Bitmap(const File &ifile, bmp::Format iformat, bmp::Type itype)
		: _width(0), _height(0), _depth(0), _pitch(0), _bytes_per_pixel(0), _format(bmp::Format::Void), _type(bmp::Type::Void), _data(nullptr) {
			load(ifile, iformat, itype);
		}

		inline Bitmap::Bitmap(const Bitmap &isrc)
		: _width(0), _height(0), _depth(0), _pitch(0), _bytes_per_pixel(0), _format(bmp::Format::Void), _type(bmp::Type::Void), _data(nullptr) {
			load(isrc);
		}

		inline Bitmap::~Bitmap() {clear();}

		inline size_t Bitmap::width() const {return _width;}
		inline size_t Bitmap::height() const {return _height;}
		inline size_t Bitmap::depth() const {return _depth;}
		inline size_t Bitmap::pitch() const {return _pitch;}

		inline size_t Bitmap::bpp() const {return _bytes_per_pixel;}
		inline bmp::Format Bitmap::format() const {return _format;}
		inline bmp::Type Bitmap::type() const {return _type;}

		inline void *Bitmap::data() {return _data;}
		inline void *Bitmap::page(size_t iz) {return reinterpret_cast<void*>(reinterpret_cast<uint8 *>(_data) + _pitch*_height*iz);}
		inline void *Bitmap::row(size_t iy, size_t iz) {return reinterpret_cast<void*>(reinterpret_cast<uint8 *>(_data) + _pitch*_height*iz + _pitch*iy);}

		inline const void *Bitmap::data() const {return _data;}
		inline const void *Bitmap::page(size_t iz) const {return reinterpret_cast<void*>(reinterpret_cast<uint8 *>(_data) + _pitch*_height*iz);}
		inline const void *Bitmap::row(size_t iy, size_t iz) const {return reinterpret_cast<void*>(reinterpret_cast<uint8 *>(_data) + _pitch*_height*iz + _pitch*iy);}

		inline bool Bitmap::empty() const {return !_data;}
		inline void Bitmap::clear() {
			if(_data) {
				free(_data);
				_width = 0;
				_height = 0;
				_depth = 0;
				_pitch = 0;

				_bytes_per_pixel = 0;
				_format = bmp::Format::Void;
				_type = bmp::Type::Void;

				_data = NULL;
			}
		}

		template<typename T, bmp::Format f, bmp::Type t>
		inline BitmapBase<T,f,t>::BitmapBase()
		: _bitmap() {
		}

		template<typename T, bmp::Format f, bmp::Type t>
		inline BitmapBase<T,f,t>::BitmapBase(size_t iwidth, size_t iheight, size_t idepth)
		: _bitmap(iwidth, iheight, idepth, f, t) {
		}

		template<typename T, bmp::Format f, bmp::Type t>
		inline BitmapBase<T,f,t>::BitmapBase(const File &ifile)
		: _bitmap(ifile, f, t) {
		}

		template<typename T, bmp::Format f, bmp::Type t>
		inline BitmapBase<T,f,t>::BitmapBase(const BitmapBase<T,f,t> &isrc)
		: _bitmap(isrc._bitmap) {
		}

		template<typename T, bmp::Format f, bmp::Type t>
		inline BitmapBase<T,f,t>::~BitmapBase() {
		}

		template<typename T, bmp::Format f, bmp::Type t> inline size_t BitmapBase<T,f,t>::width() const {return _bitmap.width();}
		template<typename T, bmp::Format f, bmp::Type t> inline size_t BitmapBase<T,f,t>::height() const {return _bitmap.height();}
		template<typename T, bmp::Format f, bmp::Type t> inline size_t BitmapBase<T,f,t>::depth() const {return _bitmap.depth();}

		template<typename T, bmp::Format f, bmp::Type t> inline size_t BitmapBase<T,f,t>::bpp() const {return _bitmap.bpp();}
		template<typename T, bmp::Format f, bmp::Type t> inline bmp::Format BitmapBase<T,f,t>::format() const {return f;}
		template<typename T, bmp::Format f, bmp::Type t> inline bmp::Type BitmapBase<T,f,t>::type() const {return t;}

		template<typename T, bmp::Format f, bmp::Type t> inline T *BitmapBase<T,f,t>::row(size_t iy, size_t iz) {return reinterpret_cast<T*>(_bitmap.row(iy, iz));}
		template<typename T, bmp::Format f, bmp::Type t> inline const T *BitmapBase<T,f,t>::row(size_t iy, size_t iz) const {return reinterpret_cast<const T*>(_bitmap.row(iy, iz));}

		template<typename T, bmp::Format f, bmp::Type t> inline bool BitmapBase<T,f,t>::empty() const {return _bitmap.empty();}
		template<typename T, bmp::Format f, bmp::Type t> inline void BitmapBase<T,f,t>::clear() {_bitmap.clear();}

		template<typename T, bmp::Format f, bmp::Type t> inline void BitmapBase<T,f,t>::load(size_t iwidth, size_t iheight, size_t idepth) {_bitmap.load(iwidth, iheight, idepth, f, t);}
		template<typename T, bmp::Format f, bmp::Type t> inline void BitmapBase<T,f,t>::load(const File &ifile) {_bitmap.load(ifile, f, t);}
		template<typename T, bmp::Format f, bmp::Type t> inline void BitmapBase<T,f,t>::load(const BitmapBase<T,f,t> &iimg) {_bitmap.load(iimg._bitmap);}

		template<typename T, bmp::Format f, bmp::Type t> inline void BitmapBase<T,f,t>::save(const base::string &ifilename) {_bitmap.save(ifilename);}

		template<typename T, bmp::Format f, bmp::Type t>
		inline T &BitmapBase<T,f,t>::operator()(size_t ix, size_t iy, size_t iz) {
			return reinterpret_cast<T*>(_bitmap.row(iy, iz))[ix];
		}

		template<typename T, bmp::Format f, bmp::Type t>
		inline const T &BitmapBase<T,f,t>::operator()(size_t ix, size_t iy, size_t iz) const {
			return reinterpret_cast<const T*>(_bitmap.row(iy, iz))[ix];
		}

		template<typename T, bmp::Format f, bmp::Type t>
		inline const Bitmap &BitmapBase<T,f,t>::bitmap() const {
			return _bitmap;
		}

		//Signed Byte
		typedef BitmapBase<int8, bmp::Format::Luminance, bmp::Type::Byte> bBitmapL;
		typedef BitmapBase<bmp::bLA, bmp::Format::LA, bmp::Type::Byte> bBitmapLA;
		typedef BitmapBase<bmp::bRGB, bmp::Format::RGB, bmp::Type::Byte> bBitmapRGB;
		typedef BitmapBase<bmp::bRGBA, bmp::Format::RGBA, bmp::Type::Byte> bBitmapRGBA;

		//Unsigned Byte
		typedef BitmapBase<uint8, bmp::Format::Luminance, bmp::Type::UByte> ubBitmapL;
		typedef BitmapBase<bmp::ubLA, bmp::Format::LA, bmp::Type::UByte> ubBitmapLA;
		typedef BitmapBase<bmp::ubRGB, bmp::Format::RGB, bmp::Type::UByte> ubBitmapRGB;
		typedef BitmapBase<bmp::ubRGBA, bmp::Format::RGBA, bmp::Type::UByte> ubBitmapRGBA;

		//Signed Short
		typedef BitmapBase<int16, bmp::Format::Luminance, bmp::Type::Int16> sBitmapL;
		typedef BitmapBase<bmp::sLA, bmp::Format::LA, bmp::Type::Int16> sBitmapLA;
		typedef BitmapBase<bmp::sRGB, bmp::Format::RGB, bmp::Type::Int16> sBitmapRGB;
		typedef BitmapBase<bmp::sRGBA, bmp::Format::RGBA, bmp::Type::Int16> sBitmapRGBA;

		//Unsigned Short
		typedef BitmapBase<uint16, bmp::Format::Luminance, bmp::Type::UInt16> usBitmapL;
		typedef BitmapBase<bmp::usLA, bmp::Format::LA, bmp::Type::UInt16> usBitmapLA;
		typedef BitmapBase<bmp::usRGB, bmp::Format::RGB, bmp::Type::UInt16> usBitmapRGB;
		typedef BitmapBase<bmp::usRGBA, bmp::Format::RGBA, bmp::Type::UInt16> usBitmapRGBA;

		//Signed Int
		typedef BitmapBase<int32, bmp::Format::Luminance, bmp::Type::Int32> lBitmapL;
		typedef BitmapBase<bmp::lLA, bmp::Format::LA, bmp::Type::Int32> lBitmapLA;
		typedef BitmapBase<bmp::lRGB, bmp::Format::RGB, bmp::Type::Int32> lBitmapRGB;
		typedef BitmapBase<bmp::lRGBA, bmp::Format::RGBA, bmp::Type::Int32> lBitmapRGBA;

		//Unsigned Int
		typedef BitmapBase<uint32, bmp::Format::Luminance, bmp::Type::UInt32> ulBitmapL;
		typedef BitmapBase<bmp::ulLA, bmp::Format::LA, bmp::Type::UInt32> ulBitmapLA;
		typedef BitmapBase<bmp::ulRGB, bmp::Format::RGB, bmp::Type::UInt32> ulBitmapRGB;
		typedef BitmapBase<bmp::ulRGBA, bmp::Format::RGBA, bmp::Type::UInt32> ulBitmapRGBA;

		//Float
		typedef BitmapBase<float, bmp::Format::Luminance, bmp::Type::Float> fBitmapL;
		typedef BitmapBase<bmp::fLA, bmp::Format::LA, bmp::Type::Float> fBitmapLA;
		typedef BitmapBase<bmp::fRGB, bmp::Format::RGB, bmp::Type::Float> fBitmapRGB;
		typedef BitmapBase<bmp::fRGBA, bmp::Format::RGBA, bmp::Type::Float> fBitmapRGBA;


		//Signed Byte
		CbTemplate template class CbAPI BitmapBase<int8, bmp::Format::Luminance, bmp::Type::Byte>;
		CbTemplate template class CbAPI BitmapBase<bmp::bLA, bmp::Format::LA, bmp::Type::Byte>;
		CbTemplate template class CbAPI BitmapBase<bmp::bRGB, bmp::Format::RGB, bmp::Type::Byte>;
		CbTemplate template class CbAPI BitmapBase<bmp::bRGBA, bmp::Format::RGBA, bmp::Type::Byte>;

		//Unsigned Byte
		CbTemplate template class CbAPI BitmapBase<uint8, bmp::Format::Luminance, bmp::Type::UByte>;
		CbTemplate template class CbAPI BitmapBase<bmp::ubLA, bmp::Format::LA, bmp::Type::UByte>;
		CbTemplate template class CbAPI BitmapBase<bmp::ubRGB, bmp::Format::RGB, bmp::Type::UByte>;
		CbTemplate template class CbAPI BitmapBase<bmp::ubRGBA, bmp::Format::RGBA, bmp::Type::UByte>;

		//Signed Short
		CbTemplate template class CbAPI BitmapBase<int16, bmp::Format::Luminance, bmp::Type::Int16>;
		CbTemplate template class CbAPI BitmapBase<bmp::sLA, bmp::Format::LA, bmp::Type::Int16>;
		CbTemplate template class CbAPI BitmapBase<bmp::sRGB, bmp::Format::RGB, bmp::Type::Int16>;
		CbTemplate template class CbAPI BitmapBase<bmp::sRGBA, bmp::Format::RGBA, bmp::Type::Int16>;

		//Unsigned Short
		CbTemplate template class CbAPI BitmapBase<uint16, bmp::Format::Luminance, bmp::Type::UInt16>;
		CbTemplate template class CbAPI BitmapBase<bmp::usLA, bmp::Format::LA, bmp::Type::UInt16>;
		CbTemplate template class CbAPI BitmapBase<bmp::usRGB, bmp::Format::RGB, bmp::Type::UInt16>;
		CbTemplate template class CbAPI BitmapBase<bmp::usRGBA, bmp::Format::RGBA, bmp::Type::UInt16>;

		//Signed Int
		CbTemplate template class CbAPI BitmapBase<int32, bmp::Format::Luminance, bmp::Type::Int32>;
		CbTemplate template class CbAPI BitmapBase<bmp::lLA, bmp::Format::LA, bmp::Type::Int32>;
		CbTemplate template class CbAPI BitmapBase<bmp::lRGB, bmp::Format::RGB, bmp::Type::Int32>;
		CbTemplate template class CbAPI BitmapBase<bmp::lRGBA, bmp::Format::RGBA, bmp::Type::Int32>;

		//Unsigned Int
		CbTemplate template class CbAPI BitmapBase<uint32, bmp::Format::Luminance, bmp::Type::UInt32>;
		CbTemplate template class CbAPI BitmapBase<bmp::ulLA, bmp::Format::LA, bmp::Type::UInt32>;
		CbTemplate template class CbAPI BitmapBase<bmp::ulRGB, bmp::Format::RGB, bmp::Type::UInt32>;
		CbTemplate template class CbAPI BitmapBase<bmp::ulRGBA, bmp::Format::RGBA, bmp::Type::UInt32>;

		//Float
		CbTemplate template class CbAPI BitmapBase<float, bmp::Format::Luminance, bmp::Type::Float>;
		CbTemplate template class CbAPI BitmapBase<bmp::fLA, bmp::Format::LA, bmp::Type::Float>;
		CbTemplate template class CbAPI BitmapBase<bmp::fRGB, bmp::Format::RGB, bmp::Type::Float>;
		CbTemplate template class CbAPI BitmapBase<bmp::fRGBA, bmp::Format::RGBA, bmp::Type::Float>;
	}  // namespace data
}  // namespace cb
