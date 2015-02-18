/* 
 * - Cumulonimbus - ☁
 * File: gShader.cpp
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
#include <cb/graphic/Shader.h>

#include <cb/graphic/GLEWmx.h>

#include <cb/base/Exception.h>

namespace cb {
	namespace graphic {
		GLenum translateType(Shader::Type itype) {
			GLenum types[] = {
				GL_VERTEX_SHADER,	//Vertex
				GL_FRAGMENT_SHADER	//Fragment
			};

			return types[(int)itype];
		}

		Shader::Shader(const data::File &ifile, Type itype)
		:_type(itype), _id(0) {
			const GLchar *vert_source[] = {
				ifile.data()
			};

			const GLint vert_source_length[] = {
				(GLint)ifile.size()
			};


			_id = glCreateShader(translateType(_type));
			glShaderSource(_id, 1, vert_source, vert_source_length);
			glCompileShader(_id);

			int compile_status;
			glGetShaderiv(_id, GL_COMPILE_STATUS, &compile_status);

			if(compile_status) {
			} else {
				int infolog_length = 0;
				base::string info_log;

				glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &infolog_length);
				if(infolog_length > 0) {
					int chars_written = 0;
					char *info_log_buffer = new char [infolog_length];
					glGetShaderInfoLog(_id, infolog_length, &chars_written, info_log_buffer);
					info_log = info_log_buffer;
					delete [] info_log_buffer;

					ThrowDet(tokurei::LoadFailed, "Shader failed to compile:\n%s", info_log.c_str());
				} else {
					Throw(tokurei::LoadFailed);
				}
			}

			glCheckError;
		}

		Shader::Shader(const std::vector<data::File *> &ifiles, Type itype) {
			size_t size = ifiles.size();
			const GLchar **vert_source = new const char *[size];
			for(size_t i=0 ; i<size ; i++) {
				vert_source[i] = ifiles.at(i)->data();
			}

			GLint *vert_source_length = new GLint[size];
			for(size_t i=0 ; i<size ; i++) {
				vert_source_length[i] = (GLint)ifiles.at(i)->size();
			}

			_id = glCreateShader(translateType(_type));
			glShaderSource(_id, (GLsizei)size, vert_source, vert_source_length);
			glCompileShader(_id);

			int compile_status;
			glGetShaderiv(_id, GL_COMPILE_STATUS, &compile_status);

			if(compile_status) {
			} else {
				int infolog_length = 0;
				base::string info_log;

				glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &infolog_length);
				if(infolog_length > 0) {
					int chars_written = 0;
					char *info_log_buffer = new char [infolog_length];
					glGetShaderInfoLog(_id, infolog_length, &chars_written, info_log_buffer);
					info_log = info_log_buffer;
					delete [] info_log_buffer;

					ThrowDet(tokurei::LoadFailed, "Shader failed to compile:\n%s", info_log.c_str());
				} else {
					Throw(tokurei::LoadFailed);
				}
			}

			glCheckError;
		}

		Shader::~Shader() {
			glDeleteShader(_id);
		}
	}  // namespace graphic
}  // namespace cb
