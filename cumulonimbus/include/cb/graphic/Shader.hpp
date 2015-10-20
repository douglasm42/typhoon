/* 
 * - Cumulonimbus - ☁
 * File: Shader.h
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

#include <cb/data/Blob.hpp>

#include <vector>

namespace cb {
	namespace graphic {
		class CbAPI Shader {
		public:
			enum class Type {
				Vertex = 0,
				Fragment
			};

		private:
			Type _type;
			GLuint _id;

			Shader(const Shader &);

		public:
			Shader(const data::Blob &ifile, Type itype);
			Shader(const std::vector<data::Blob *> &ifiles, Type itype);
			~Shader();

			GLuint getID() const;
		};

		inline GLuint Shader::getID() const {return _id;}
	}  // namespace graphic
}  // namespace cb
