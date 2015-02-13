/* 
 * - Cumulonimbus - ☁
 * File: gProgram.cpp
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
#include <cb/graphic/Program.h>

#include <graphic/GLEWmx.h>
#include <graphic/TextureTranslate.h>

#include <cb/base/Exception.h>

#ifdef CbDebug
#	define AssertProgramBind(programid) \
			{\
				GLObject program;\
				glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*)&program);\
				if(program != programid) {\
					Throw(tokurei::SetFailed);\
				}\
			}
#else
#	define AssertProgramBind(programid)
#endif

namespace cb {
	namespace graphic {
		Program::Program() :_id(0), _next_texture_position(0) {
			_id = glCreateProgram();
		}

		Program::~Program() {
			clear();
			glDeleteProgram(_id);
		}

		void Program::add(Shader *ishader) {
			_shaders.push_back(ishader);
			glAttachShader(_id, ishader->id());
		}

		void Program::clear() {
			for(size_t i=0 ; i<_shaders.size() ; i++) {
				glDetachShader(_id, _shaders[i]->id());
			}
			_shaders.clear();
		}

		void Program::link() {
			glLinkProgram(_id);

			int link_status;

			glGetProgramiv(_id, GL_LINK_STATUS, &link_status);

			if(link_status) {
			} else {
				int infolog_length = 0;
				base::string info_log;

				glGetProgramiv(_id, GL_INFO_LOG_LENGTH,&infolog_length);
				if (infolog_length > 0) {
					int chars_written = 0;
					char *info_log_buffer = new char [infolog_length];
					glGetProgramInfoLog(_id, infolog_length, &chars_written, info_log_buffer);
					info_log = info_log_buffer;
					delete [] info_log_buffer;

					ThrowDet(tokurei::LoadFailed, "Program failed to link:\n%s", info_log.c_str());
				} else {
					Throw(tokurei::LoadFailed);
				}
			}

			glCheckError();
		}

		void Program::bind() {
			glUseProgram(_id);
			_next_texture_position = 0;
		}

		void Program::unbind() {
			glUseProgram(0);
		}

		void Program::output(const base::string &iname, size_t iid) {
			glBindFragDataLocation(_id, iid, iname.c_str());
		}

		void Program::attribute(const base::string &iname, size_t iid) {
			glBindAttribLocation(_id, iid, iname.c_str());
		}

		void Program::uniform(const base::string &iname, float ix) {
			AssertProgramBind(_id);
			int location = glGetUniformLocation(_id, iname.c_str());
			glUniform1f(location, ix);
		}
		void Program::uniform(const base::string &iname, float ix, float iy) {
			AssertProgramBind(_id);
			int location = glGetUniformLocation(_id, iname.c_str());
			glUniform2f(location, ix, iy);
		}
		void Program::uniform(const base::string &iname, float ix, float iy, float iz) {
			AssertProgramBind(_id);
			int location = glGetUniformLocation(_id, iname.c_str());
			glUniform3f(location, ix, iy, iz);
		}
		void Program::uniform(const base::string &iname, float ix, float iy, float iz, float iw) {
			AssertProgramBind(_id);
			int location = glGetUniformLocation(_id, iname.c_str());
			glUniform4f(location, ix, iy, iz, iw);
		}

		void Program::uniform(const base::string &iname, int ix) {
			AssertProgramBind(_id);
			int location = glGetUniformLocation(_id, iname.c_str());
			glUniform1i(location, ix);
		}
		void Program::uniform(const base::string &iname, int ix, int iy) {
			AssertProgramBind(_id);
			int location = glGetUniformLocation(_id, iname.c_str());
			glUniform2i(location, ix, iy);
		}
		void Program::uniform(const base::string &iname, int ix, int iy, int iz) {
			AssertProgramBind(_id);
			int location = glGetUniformLocation(_id, iname.c_str());
			glUniform3i(location, ix, iy, iz);
		}
		void Program::uniform(const base::string &iname, int ix, int iy, int iz, int iw) {
			AssertProgramBind(_id);
			int location = glGetUniformLocation(_id, iname.c_str());
			glUniform4i(location, ix, iy, iz, iw);
		}

		void Program::uniform(const base::string &iname, const glm::vec2 &iv) {
			AssertProgramBind(_id);
			int location = glGetUniformLocation(_id, iname.c_str());
			glUniform2f(location, iv.x, iv.y);
		}
		void Program::uniform(const base::string &iname, const glm::vec3 &iv) {
			AssertProgramBind(_id);
			int location = glGetUniformLocation(_id, iname.c_str());
			glUniform3f(location, iv.x, iv.y, iv.z);
		}
		void Program::uniform(const base::string &iname, const glm::vec4 &iv) {
			AssertProgramBind(_id);
			int location = glGetUniformLocation(_id, iname.c_str());
			glUniform4f(location, iv.x, iv.y, iv.z, iv.w);
		}

		void Program::uniform(const base::string &iname, const glm::ivec2 &iv) {
			AssertProgramBind(_id);
			int location = glGetUniformLocation(_id, iname.c_str());
			glUniform2i(location, iv.x, iv.y);
		}
		void Program::uniform(const base::string &iname, const glm::ivec3 &iv) {
			AssertProgramBind(_id);
			int location = glGetUniformLocation(_id, iname.c_str());
			glUniform3i(location, iv.x, iv.y, iv.z);
		}
		void Program::uniform(const base::string &iname, const glm::ivec4 &iv) {
			AssertProgramBind(_id);
			int location = glGetUniformLocation(_id, iname.c_str());
			glUniform4i(location, iv.x, iv.y, iv.z, iv.w);
		}

		void Program::uniform(const base::string &iname, const glm::mat2 &im) {
			AssertProgramBind(_id);
			int location = glGetUniformLocation(_id, iname.c_str());
			glUniformMatrix2fv(location, 1, GL_FALSE, &im[0][0]);
		}

		void Program::uniform(const base::string &iname, const glm::mat3 &im) {
			AssertProgramBind(_id);
			int location = glGetUniformLocation(_id, iname.c_str());
			glUniformMatrix3fv(location, 1, GL_FALSE, &im[0][0]);
		}

		void Program::uniform(const base::string &iname, const glm::mat4 &im) {
			AssertProgramBind(_id);
			int location = glGetUniformLocation(_id, iname.c_str());
			glUniformMatrix4fv(location, 1, GL_FALSE, &im[0][0]);
		}

		void Program::uniform(const base::string &iname, Texture &itex) {
			AssertProgramBind(_id);
			int location = glGetUniformLocation(_id, iname.c_str());
			glActiveTexture(GL_TEXTURE0+_next_texture_position);
			itex.bind();
			glUniform1i(location, _next_texture_position);

			_next_texture_position++;
		}

		void Program::uniform(int ilocation, float ix) {
			AssertProgramBind(_id);
			glUniform1f(ilocation, ix);
		}
		void Program::uniform(int ilocation, float ix, float iy) {
			AssertProgramBind(_id);
			glUniform2f(ilocation, ix, iy);
		}
		void Program::uniform(int ilocation, float ix, float iy, float iz) {
			AssertProgramBind(_id);
			glUniform3f(ilocation, ix, iy, iz);
		}
		void Program::uniform(int ilocation, float ix, float iy, float iz, float iw) {
			AssertProgramBind(_id);
			glUniform4f(ilocation, ix, iy, iz, iw);
		}

		void Program::uniform(int ilocation, int ix) {
			AssertProgramBind(_id);
			glUniform1i(ilocation, ix);
		}
		void Program::uniform(int ilocation, int ix, int iy) {
			AssertProgramBind(_id);
			glUniform2i(ilocation, ix, iy);
		}
		void Program::uniform(int ilocation, int ix, int iy, int iz) {
			AssertProgramBind(_id);
			glUniform3i(ilocation, ix, iy, iz);
		}
		void Program::uniform(int ilocation, int ix, int iy, int iz, int iw) {
			AssertProgramBind(_id);
			glUniform4i(ilocation, ix, iy, iz, iw);
		}

		void Program::uniform(int ilocation, const glm::vec2 &iv) {
			AssertProgramBind(_id);
			glUniform2f(ilocation, iv.x, iv.y);
		}
		void Program::uniform(int ilocation, const glm::vec3 &iv) {
			AssertProgramBind(_id);
			glUniform3f(ilocation, iv.x, iv.y, iv.z);
		}
		void Program::uniform(int ilocation, const glm::vec4 &iv) {
			AssertProgramBind(_id);
			glUniform4f(ilocation, iv.x, iv.y, iv.z, iv.w);
		}

		void Program::uniform(int ilocation, const glm::ivec2 &iv) {
			AssertProgramBind(_id);
			glUniform2i(ilocation, iv.x, iv.y);
		}
		void Program::uniform(int ilocation, const glm::ivec3 &iv) {
			AssertProgramBind(_id);
			glUniform3i(ilocation, iv.x, iv.y, iv.z);
		}
		void Program::uniform(int ilocation, const glm::ivec4 &iv) {
			AssertProgramBind(_id);
			glUniform4i(ilocation, iv.x, iv.y, iv.z, iv.w);
		}

		void Program::uniform(int ilocation, const glm::mat2 &im) {
			AssertProgramBind(_id);
			glUniformMatrix2fv(ilocation, 1, GL_FALSE, &im[0][0]);
		}

		void Program::uniform(int ilocation, const glm::mat3 &im) {
			AssertProgramBind(_id);
			glUniformMatrix3fv(ilocation, 1, GL_FALSE, &im[0][0]);
		}

		void Program::uniform(int ilocation, const glm::mat4 &im) {
			AssertProgramBind(_id);
			glUniformMatrix4fv(ilocation, 1, GL_FALSE, &im[0][0]);
		}

		void Program::uniform(int ilocation, Texture &itex) {
			AssertProgramBind(_id);
			glActiveTexture(GL_TEXTURE0+_next_texture_position);
			itex.bind();
			glUniform1i(ilocation, _next_texture_position);

			_next_texture_position++;
		}

		int Program::uniform(const base::string &iname) {
			AssertProgramBind(_id);
			return glGetUniformLocation(_id, iname.c_str());
		}

		int Program::maxTextures() {
			GLint maxtextures;
			glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxtextures);

			return maxtextures;
		}

		int Program::maxOutput() {
			GLint maxoutput;
			glGetIntegerv(GL_MAX_DRAW_BUFFERS, &maxoutput);

			return maxoutput;
		}

		int Program::maxAttribute() {
			GLint maxattribute;
			glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxattribute);

			return maxattribute;
		}
	}  // namespace graphic
}  // namespace cb
