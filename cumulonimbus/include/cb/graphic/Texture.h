/* 
 * - Cumulonimbus - ☁
 * File: Texture.h
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

#include <cb/graphic/GLEWmx.h>

#include <cb/data/Bitmap.h>

#include <cstdint>
#include <vector>

namespace cb {
	namespace graphic {
		class CbAPI Texture {
		public:
			enum class Wrap : GLenum {
				Repeat			= GL_REPEAT,
				Mirror			= GL_MIRRORED_REPEAT,
				Clamp			= GL_CLAMP_TO_EDGE
			};

			enum class MinFilter : GLenum {
				Nearest					= GL_NEAREST,
				Linear					= GL_LINEAR,
				NearestMipMapNearest	= GL_NEAREST_MIPMAP_NEAREST,
				NearestMipMapLinear		= GL_NEAREST_MIPMAP_LINEAR,
				LinearMipMapNearest		= GL_LINEAR_MIPMAP_NEAREST,
				LinearMipMapLinear		= GL_LINEAR_MIPMAP_LINEAR
			};

			enum class MagFilter : GLenum {
				Nearest					= GL_NEAREST,
				Linear					= GL_LINEAR
			};

			enum class Format : GLenum {
				Void = 0,

				Depth			= GL_DEPTH_COMPONENT16,
				Depth16			= GL_DEPTH_COMPONENT16,
				Depth24			= GL_DEPTH_COMPONENT24,
				Depth32			= GL_DEPTH_COMPONENT32,
				Depth32f		= GL_DEPTH_COMPONENT32F,

				Red8			= GL_R8,
				Red8s			= GL_R8_SNORM,
				Red16			= GL_R16,
				Red16s			= GL_R16_SNORM,
				RG8				= GL_RG8,
				RG8s			= GL_RG8_SNORM,
				RG16			= GL_RG16,
				RG16s			= GL_RG16_SNORM,
				R3G3B2			= GL_R3_G3_B2,
				RGB4			= GL_RGB4,
				RGB5			= GL_RGB5,
				RGB8			= GL_RGB8,
				RGB8s			= GL_RGB8_SNORM,
				RGB10			= GL_RGB10,
				RGB12			= GL_RGB12,
				RGB16s			= GL_RGB16_SNORM,
				RGBA2			= GL_RGBA2,
				RGBA4			= GL_RGBA4,
				RGB5A1			= GL_RGB5_A1,
				RGBA8			= GL_RGBA8,
				RGBA8s			= GL_RGBA8_SNORM,
				RGB10A2			= GL_RGB10_A2,
				RGB10A2ui		= GL_RGB10_A2UI,
				RGBA12			= GL_RGBA12,
				RGBA16			= GL_RGBA16,
				SRGB8			= GL_SRGB8,
				SRGB8A8			= GL_SRGB8_ALPHA8,
				Red16f			= GL_R16F,
				RG16f			= GL_RG16F,
				RGB16f			= GL_RGB16F,
				RGBA16f			= GL_RGBA16F,
				Red32f			= GL_R32F,
				RG32f			= GL_RG32F,
				RGB32f			= GL_RGB32F,
				RGBA32f			= GL_RGBA32F,
				R11fG11fB10f	= GL_R11F_G11F_B10F,
				RGB9E5			= GL_RGB9_E5,
				Red8i			= GL_R8I,
				Red8ui			= GL_R8UI,
				Red16i			= GL_R16I,
				Red16ui			= GL_R16UI,
				Red32i			= GL_R32I,
				Red32ui			= GL_R32UI,
				RG8i			= GL_RG8I,
				RG8ui			= GL_RG8UI,
				RG16i			= GL_RG16I,
				RG16ui			= GL_RG16UI,
				RG32i			= GL_RG32I,
				RG32ui			= GL_RG32UI,
				RGB8i			= GL_RGB8I,
				RGB8ui			= GL_RGB8UI,
				RGB16i			= GL_RGB16I,
				RGB16ui			= GL_RGB16UI,
				RGB32i			= GL_RGB32I,
				RGB32ui			= GL_RGB32UI,
				RGBA8i			= GL_RGBA8I,
				RGBA8ui			= GL_RGBA8UI,
				RGBA16i			= GL_RGBA16I,
				RGBA16ui		= GL_RGBA16UI,
				RGBA32i			= GL_RGBA32I,
				RGBA32ui		= GL_RGBA32UI,

				CompRed			= GL_COMPRESSED_RED,
				CompRG			= GL_COMPRESSED_RG,
				CompRGB			= GL_COMPRESSED_RGB,
				CompRGBA		= GL_COMPRESSED_RGBA,
				CompSRGB		= GL_COMPRESSED_SRGB,
				CompSRGBA		= GL_COMPRESSED_SRGB_ALPHA
			};

			enum class Target : GLenum {
				Void		= 0,

				Tex1D		= GL_TEXTURE_1D,
				Tex2D		= GL_TEXTURE_2D,
				Tex3D		= GL_TEXTURE_3D,

				Tex1DArray	= GL_TEXTURE_1D_ARRAY,
				Tex2DArray	= GL_TEXTURE_2D_ARRAY,

				Rectangle	= GL_TEXTURE_RECTANGLE,

				CubeMap		= GL_TEXTURE_CUBE_MAP
			};

			enum class CubeMapFace : GLenum {
				Void		= 0,

				CubeMapXp	= GL_TEXTURE_CUBE_MAP_POSITIVE_X,
				CubeMapXm	= GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
				CubeMapYp	= GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
				CubeMapYm	= GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
				CubeMapZp	= GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
				CubeMapZm	= GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
			};

		private:
			GLuint _id;
			Format _format;
			Target _target;

			Wrap _wrap_s;
			Wrap _wrap_t;
			Wrap _wrap_r;

			MinFilter _min_filter;
			MagFilter _mag_filter;

			uint32 _width;
			uint32 _height;
			uint32 _depth;

			uint32 _lod_count;
			uint32 _lod_base;
			uint32 _lod_max;

		public:
			Texture(Target itarget, Format iformat);
			virtual ~Texture();

			void loadBlank(uint32 ilod, uint32 iwidth, uint32 iheight, uint32 idepth);
			void loadImage(uint32 ilod, const data::Bitmap &ibmp);
			void loadCubeMap(uint32 ilod, CubeMapFace iface, const data::Bitmap &ibmp);
			void loadCubeMap(uint32 ilod, const data::Bitmap &ibmp_xp, const data::Bitmap &ibmp_xm, const data::Bitmap &ibmp_yp, const data::Bitmap &ibmp_ym, const data::Bitmap &ibmp_zp, const data::Bitmap &ibmp_zm);

			void loadSubImage(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset);
			void loadSubImage(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset);
			void loadSubImage(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset, uint32 izoffset);

			void loadSubCubeMap(uint32 ilod, CubeMapFace iface, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset);

			void addBlankLOD();
			void addImageLOD(const data::Bitmap &ibmp);
			void addCubeMapLOD(const data::Bitmap &ibmp_xp, const data::Bitmap &ibmp_xm, const data::Bitmap &ibmp_yp, const data::Bitmap &ibmp_ym, const data::Bitmap &ibmp_zp, const data::Bitmap &ibmp_zm);

			void bind() const;
			void unbind() const;

			void setWrap(Wrap iwrap);
			void setWrapS(Wrap iwrap);
			void setWrapT(Wrap iwrap);
			void setWrapR(Wrap iwrap);

			void setMinFilter(MinFilter ifilter);
			void setMagFilter(MagFilter ifilter);

			Wrap getWrapS() const;
			Wrap getWrapT() const;
			Wrap getWrapR() const;

			MinFilter getMinFilter() const;
			MagFilter getMagFilter() const;

			bool isEmpty() const;

			GLuint getID() const;
			Format getFormat() const;
			Target getTarget() const;

			uint32 width() const;
			uint32 height() const;
			uint32 depth() const;

			uint32 lodWidth(uint32 ilod) const;
			uint32 lodHeight(uint32 ilod) const;
			uint32 lodDepth(uint32 ilod) const;

			void setLODBase(uint32 ilod);
			void setLODMax(uint32 ilod);

			uint32 getLODCount() const;
			uint32 getLODBase() const;
			uint32 getLODMax() const;
		};

		inline Texture::Wrap Texture::getWrapS() const {return _wrap_s;}
		inline Texture::Wrap Texture::getWrapT() const {return _wrap_t;}
		inline Texture::Wrap Texture::getWrapR() const {return _wrap_r;}

		inline Texture::MinFilter Texture::getMinFilter() const {return _min_filter;}
		inline Texture::MagFilter Texture::getMagFilter() const {return _mag_filter;}

		inline bool Texture::isEmpty() const {return _target == Texture::Target::Void;}

		inline GLuint Texture::getID() const { return _id; }
		inline Texture::Format Texture::getFormat() const {return _format;}
		inline Texture::Target Texture::getTarget() const {return _target;}

		inline uint32 Texture::width() const {return _width;}
		inline uint32 Texture::height() const {return _height;}
		inline uint32 Texture::depth() const {return _depth;}

		inline uint32 Texture::lodWidth(uint32 ilod) const {return max(1u, (uint32)floor( float(_width) / float(2^ilod) ));}
		inline uint32 Texture::lodHeight(uint32 ilod) const {return max(1u, (uint32)floor( float(_height) / float(2^ilod) ));}
		inline uint32 Texture::lodDepth(uint32 ilod) const {return max(1u, (uint32)floor( float(_depth) / float(2^ilod) ));}

		inline uint32 Texture::getLODCount() const {return _lod_count;}
		inline uint32 Texture::getLODBase() const {return _lod_base;}
		inline uint32 Texture::getLODMax() const {return _lod_max;}

		class CbAPI Texture1D : public Texture {
		private:
			Wrap _wrap_s;

			uint32 _width;

		public:
			Texture1D(Texture::Format iformat);
			virtual ~Texture1D();

			void loadBlank(uint32 ilod, uint32 iwidth);
			void loadImage(uint32 ilod, const data::Bitmap &ibmp);

			void loadSubImage(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset);

			void addBlankLOD();
			void addImageLOD(const data::Bitmap &ibmp);

			void setWrap(Wrap iwrap);
			Wrap getWrap() const;

			uint32 width() const;

			uint32 lodWidth(uint32 ilod) const;
		};

		inline Texture::Wrap Texture1D::getWrap() const {return _wrap_s;}
		inline uint32 Texture1D::width() const {return _width;}
		inline uint32 Texture1D::lodWidth(uint32 ilod) const {return max(1u, (uint32)floor( float(_width) / float(2^ilod) ));}

		class CbAPI Texture2D : public Texture {
		private:
			Wrap _wrap_s;
			Wrap _wrap_t;

			uint32 _width;
			uint32 _height;

		public:
			Texture2D(Texture::Format iformat);
			virtual ~Texture2D();

			void loadBlank(uint32 ilod, uint32 iwidth, uint32 iheight);
			void loadImage(uint32 ilod, const data::Bitmap &ibmp);

			void loadSubImage(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset);

			void addBlankLOD();
			void addImageLOD(const data::Bitmap &ibmp);

			void setWrap(Wrap iwrap);
			void setWrapS(Wrap iwrap);
			void setWrapT(Wrap iwrap);

			Wrap getWrapS() const;
			Wrap getWrapT() const;

			uint32 width() const;
			uint32 height() const;

			uint32 lodWidth(uint32 ilod) const;
			uint32 lodHeight(uint32 ilod) const;
		};

		inline Texture::Wrap Texture2D::getWrapS() const {return _wrap_s;}
		inline Texture::Wrap Texture2D::getWrapT() const {return _wrap_t;}

		inline uint32 Texture2D::width() const {return _width;}
		inline uint32 Texture2D::height() const {return _height;}

		inline uint32 Texture2D::lodWidth(uint32 ilod) const {return max(1u, (uint32)floor( float(_width) / float(2^ilod) ));}
		inline uint32 Texture2D::lodHeight(uint32 ilod) const {return max(1u, (uint32)floor( float(_height) / float(2^ilod) ));}

		class CbAPI Texture3D : public Texture {
		private:
			Wrap _wrap_s;
			Wrap _wrap_t;
			Wrap _wrap_r;

			uint32 _width;
			uint32 _height;
			uint32 _depth;

		public:
			Texture3D(Texture::Format iformat);
			virtual ~Texture3D();

			void loadBlank(uint32 ilod, uint32 iwidth, uint32 iheight, uint32 idepth);
			void loadImage(uint32 ilod, const data::Bitmap &ibmp);

			void loadSubImage(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset, uint32 izoffset);

			void addBlankLOD();
			void addImageLOD(const data::Bitmap &ibmp);

			void setWrap(Wrap iwrap);
			void setWrapS(Wrap iwrap);
			void setWrapT(Wrap iwrap);
			void setWrapR(Wrap iwrap);

			Wrap getWrapS() const;
			Wrap getWrapT() const;
			Wrap getWrapR() const;

			uint32 width() const;
			uint32 height() const;
			uint32 depth() const;

			uint32 lodWidth(uint32 ilod) const;
			uint32 lodHeight(uint32 ilod) const;
			uint32 lodDepth(uint32 ilod) const;
		};

		inline Texture::Wrap Texture3D::getWrapS() const {return _wrap_s;}
		inline Texture::Wrap Texture3D::getWrapT() const {return _wrap_t;}
		inline Texture::Wrap Texture3D::getWrapR() const {return _wrap_r;}

		inline uint32 Texture3D::width() const {return _width;}
		inline uint32 Texture3D::height() const {return _height;}
		inline uint32 Texture3D::depth() const {return _depth;}

		inline uint32 Texture3D::lodWidth(uint32 ilod) const {return max(1u, (uint32)floor( float(_width) / float(2^ilod) ));}
		inline uint32 Texture3D::lodHeight(uint32 ilod) const {return max(1u, (uint32)floor( float(_height) / float(2^ilod) ));}
		inline uint32 Texture3D::lodDepth(uint32 ilod) const {return max(1u, (uint32)floor( float(_depth) / float(2^ilod) ));}

		class CbAPI Texture1DArray : public Texture {
		private:
			Wrap _wrap_s;

			uint32 _width;
			uint32 _layers;

		public:
			Texture1DArray(Texture::Format iformat);
			virtual ~Texture1DArray();

			void loadBlank(uint32 ilod, uint32 iwidth, uint32 ilayers);
			void loadImage(uint32 ilod, const data::Bitmap &ibmp);

			void loadSubImage(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 ilayer_offset);

			void addBlankLOD();
			void addImageLOD(const data::Bitmap &ibmp);

			void setWrap(Wrap iwrap);
			Wrap getWrap() const;

			uint32 width() const;
			uint32 layers() const;

			uint32 lodWidth(uint32 ilod) const;
		};

		inline Texture::Wrap Texture1DArray::getWrap() const {return _wrap_s;}

		inline uint32 Texture1DArray::width() const {return _width;}
		inline uint32 Texture1DArray::layers() const {return _layers;}

		inline uint32 Texture1DArray::lodWidth(uint32 ilod) const {return max(1u, (uint32)floor( float(_width) / float(2^ilod) ));}

		class CbAPI Texture2DArray : public Texture {
		private:
			Wrap _wrap_s;
			Wrap _wrap_t;
			Wrap _wrap_r;

			uint32 _width;
			uint32 _height;
			uint32 _layers;

		public:
			Texture2DArray(Texture::Format iformat);
			virtual ~Texture2DArray();

			void loadBlank(uint32 ilod, uint32 iwidth, uint32 iheight, uint32 ilayers);
			void loadImage(uint32 ilod, const data::Bitmap &ibmp);

			void loadSubImage(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset, uint32 ilayer_offset);

			void addBlankLOD();
			void addImageLOD(const data::Bitmap &ibmp);

			void setWrap(Wrap iwrap);
			void setWrapS(Wrap iwrap);
			void setWrapT(Wrap iwrap);

			Wrap getWrapS() const;
			Wrap getWrapT() const;

			uint32 width() const;
			uint32 height() const;
			uint32 layers() const;

			uint32 lodWidth(uint32 ilod) const;
			uint32 lodHeight(uint32 ilod) const;
		};

		inline Texture::Wrap Texture2DArray::getWrapS() const {return _wrap_s;}
		inline Texture::Wrap Texture2DArray::getWrapT() const {return _wrap_t;}

		inline uint32 Texture2DArray::width() const {return _width;}
		inline uint32 Texture2DArray::height() const {return _height;}
		inline uint32 Texture2DArray::layers() const {return _layers;}

		inline uint32 Texture2DArray::lodWidth(uint32 ilod) const {return max(1u, (uint32)floor( float(_width) / float(2^ilod) ));}
		inline uint32 Texture2DArray::lodHeight(uint32 ilod) const {return max(1u, (uint32)floor( float(_height) / float(2^ilod) ));}

		class CbAPI CubeMap : public Texture {
		private:
			Wrap _wrap_s;
			Wrap _wrap_t;

			uint32 _width;
			uint32 _height;

		public:
			CubeMap(Format iformat);
			virtual ~CubeMap();

			void loadBlank(uint32 ilod, uint32 iwidth, uint32 iheight);

			void loadBlankXp(uint32 ilod, uint32 iwidth, uint32 iheight);
			void loadBlankXm(uint32 ilod, uint32 iwidth, uint32 iheight);
			void loadBlankYp(uint32 ilod, uint32 iwidth, uint32 iheight);
			void loadBlankYm(uint32 ilod, uint32 iwidth, uint32 iheight);
			void loadBlankZp(uint32 ilod, uint32 iwidth, uint32 iheight);
			void loadBlankZm(uint32 ilod, uint32 iwidth, uint32 iheight);

			void loadImage(uint32 ilod, CubeMapFace iface, const data::Bitmap &ibmp);
			void loadImage(uint32 ilod, const data::Bitmap &ibmp_xp, const data::Bitmap &ibmp_xm, const data::Bitmap &ibmp_yp, const data::Bitmap &ibmp_ym, const data::Bitmap &ibmp_zp, const data::Bitmap &ibmp_zm);

			void loadImageXp(uint32 ilod, const data::Bitmap &ibmp);
			void loadImageXm(uint32 ilod, const data::Bitmap &ibmp);
			void loadImageYp(uint32 ilod, const data::Bitmap &ibmp);
			void loadImageYm(uint32 ilod, const data::Bitmap &ibmp);
			void loadImageZp(uint32 ilod, const data::Bitmap &ibmp);
			void loadImageZm(uint32 ilod, const data::Bitmap &ibmp);

			void loadSubImage(uint32 ilod, CubeMapFace iface, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset);

			void loadSubImageXp(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset);
			void loadSubImageXm(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset);
			void loadSubImageYp(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset);
			void loadSubImageYm(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset);
			void loadSubImageZp(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset);
			void loadSubImageZm(uint32 ilod, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset);

			void addBlankLOD();

			void addBlankXpLOD();
			void addBlankXmLOD();
			void addBlankYpLOD();
			void addBlankYmLOD();
			void addBlankZpLOD();
			void addBlankZmLOD();

			void addImageLOD(CubeMapFace iface, const data::Bitmap &ibmp);
			void addImageLOD(const data::Bitmap &ibmp_xp, const data::Bitmap &ibmp_xm, const data::Bitmap &ibmp_yp, const data::Bitmap &ibmp_ym, const data::Bitmap &ibmp_zp, const data::Bitmap &ibmp_zm);

			void addImageXpLOD(const data::Bitmap &ibmp);
			void addImageXmLOD(const data::Bitmap &ibmp);
			void addImageYpLOD(const data::Bitmap &ibmp);
			void addImageYmLOD(const data::Bitmap &ibmp);
			void addImageZpLOD(const data::Bitmap &ibmp);
			void addImageZmLOD(const data::Bitmap &ibmp);

			void addSubImageLOD(CubeMapFace iface, const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset);

			void addSubImageXpLOD(const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset);
			void addSubImageXmLOD(const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset);
			void addSubImageYpLOD(const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset);
			void addSubImageYmLOD(const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset);
			void addSubImageZpLOD(const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset);
			void addSubImageZmLOD(const data::Bitmap &ibmp, uint32 ixoffset, uint32 iyoffset);

			void setWrap(Wrap iwrap);
			void setWrapS(Wrap iwrap);
			void setWrapT(Wrap iwrap);

			Wrap getWrapS() const;
			Wrap getWrapT() const;

			uint32 width() const;
			uint32 height() const;

			uint32 lodWidth(uint32 ilod) const;
			uint32 lodHeight(uint32 ilod) const;
		};

		inline Texture::Wrap CubeMap::getWrapS() const {return _wrap_s;}
		inline Texture::Wrap CubeMap::getWrapT() const {return _wrap_t;}

		inline uint32 Texture::width() const {return _width;}
		inline uint32 Texture::height() const {return _height;}

		inline uint32 Texture::lodWidth(uint32 ilod) const {return max(1u, (uint32)floor( float(_width) / float(2^ilod) ));}
		inline uint32 Texture::lodHeight(uint32 ilod) const {return max(1u, (uint32)floor( float(_height) / float(2^ilod) ));}
	}  // namespace graphic
}  // namespace cb
