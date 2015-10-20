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

#include <cb/graphic/graphic.hpp>

#include <cb/graphic/GLEWmx.hpp>

#include <cb/data/Bitmap.hpp>

#include <cstdint>
#include <vector>

namespace cb {
	namespace graphic {
		namespace tex {
#			define cbTexLODSize(isize, ilod) max(1u, (uint32)floor( float(isize) / float(pow(2,ilod)) ))

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
				Tex1D		= GL_TEXTURE_1D,
				Tex2D		= GL_TEXTURE_2D,
				Tex3D		= GL_TEXTURE_3D,

				Tex1DArray	= GL_TEXTURE_1D_ARRAY,
				Tex2DArray	= GL_TEXTURE_2D_ARRAY,

				Rectangle	= GL_TEXTURE_RECTANGLE,
				CubeMap		= GL_TEXTURE_CUBE_MAP
			};

			enum class CubeMapFace : GLenum {
				CubeMapXp	= GL_TEXTURE_CUBE_MAP_POSITIVE_X,
				CubeMapXm	= GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
				CubeMapYp	= GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
				CubeMapYm	= GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
				CubeMapZp	= GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
				CubeMapZm	= GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
			};
		}  // namespace tex

		class CbAPI Texture {
		private:
			Texture(const Texture &) {}

		protected:
			GLuint _id;
			tex::Format _format;
			tex::Target _target;

			tex::MinFilter _min_filter;
			tex::MagFilter _mag_filter;

			uint32 _lod_count;
			uint32 _lod_base;
			uint32 _lod_max;

			Texture(tex::Target itarget, tex::Format iformat);
			virtual ~Texture();

			bool isFormatValid(data::bmp::Format ibmp_format);
			virtual bool isSizeValid(uint32 ibmp_width, uint32 ibmp_height, uint32 ibmp_depth, uint32 ilod) = 0;
			bool isValid(data::bmp::Format ibmp_format, uint32 ibmp_width, uint32 ibmp_height, uint32 ibmp_depth, uint32 ilod);

			void texImage1D(uint32 ilod, uint32 ibmp_width, uint32 ibmp_height, uint32 ibmp_depth, data::bmp::Format ibmp_format, data::bmp::Type ibmp_type, const void *ibmp_data);
			void texImage2D(uint32 ilod, uint32 ibmp_width, uint32 ibmp_height, uint32 ibmp_depth, data::bmp::Format ibmp_format, data::bmp::Type ibmp_type, const void *ibmp_data);
			void texImage3D(uint32 ilod, uint32 ibmp_width, uint32 ibmp_height, uint32 ibmp_depth, data::bmp::Format ibmp_format, data::bmp::Type ibmp_type, const void *ibmp_data);

			void texSubImage1D(uint32 ilod, uint32 ixoffset,									uint32 ibmp_width, data::bmp::Format ibmp_format, data::bmp::Type ibmp_type, const void *ibmp_data);
			void texSubImage2D(uint32 ilod, uint32 ixoffset, uint32 iyoffset,					uint32 ibmp_width, uint32 ibmp_height, data::bmp::Format ibmp_format, data::bmp::Type ibmp_type, const void *ibmp_data);
			void texSubImage3D(uint32 ilod, uint32 ixoffset, uint32 iyoffset, uint32 izoffset,	uint32 ibmp_width, uint32 ibmp_height, uint32 ibmp_depth, data::bmp::Format ibmp_format, data::bmp::Type ibmp_type, const void *ibmp_data);

			void texImageCubeMap(tex::CubeMapFace iface, uint32 ilod, uint32 ibmp_width, uint32 ibmp_height, uint32 ibmp_depth, data::bmp::Format ibmp_format, data::bmp::Type ibmp_type, const void *ibmp_data);
			void texSubImageCubeMap(tex::CubeMapFace iface, uint32 ilod, uint32 ixoffset, uint32 iyoffset, uint32 ibmp_width, uint32 ibmp_height, data::bmp::Format ibmp_format, data::bmp::Type ibmp_type, const void *ibmp_data);

		public:
			void bind() const;
			void unbind() const;

			void setMinFilter(tex::MinFilter ifilter);
			void setMagFilter(tex::MagFilter ifilter);

			tex::MinFilter getMinFilter() const;
			tex::MagFilter getMagFilter() const;

			GLuint getID() const;
			tex::Format getFormat() const;
			tex::Target getTarget() const;

			void setLODBase(uint32 ilod);
			void setLODMax(uint32 ilod);

			uint32 getLODCount() const;
			uint32 getLODBase() const;
			uint32 getLODMax() const;
		};

		inline tex::MinFilter Texture::getMinFilter() const {return _min_filter;}
		inline tex::MagFilter Texture::getMagFilter() const {return _mag_filter;}

		inline GLuint Texture::getID() const { return _id; }
		inline tex::Format Texture::getFormat() const {return _format;}
		inline tex::Target Texture::getTarget() const {return _target;}

		inline uint32 Texture::getLODCount() const {return _lod_count;}
		inline uint32 Texture::getLODBase() const {return _lod_base;}
		inline uint32 Texture::getLODMax() const {return _lod_max;}
	}  // namespace graphic
}  // namespace cb
