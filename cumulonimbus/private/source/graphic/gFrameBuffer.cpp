/* 
 * - Cumulonimbus - ☁
 * File: gFrameBuffer.cpp
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
#include <graphic/FrameBuffer.h>

#include <graphic/GLEWmx.h>

#include <graphic/TextureTranslate.h>

namespace cb {
	namespace graphic {
		FrameBuffer::FrameBuffer() :_id(0), _depth_buffer(nullptr) {
			_color_buffers.reserve(maxAttatchments());
			glGenFramebuffers(1, &_id);
		}

		FrameBuffer::~FrameBuffer() {
			glDeleteFramebuffers(1, &_id);
		}

		void FrameBuffer::bind() {
			glBindFramebuffer(GL_FRAMEBUFFER, _id);
		}

		void FrameBuffer::unbind() {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void FrameBuffer::validate() {
			glCheckError();

			GLuint attachments[] = {
					GL_COLOR_ATTACHMENT0,
					GL_COLOR_ATTACHMENT1,
					GL_COLOR_ATTACHMENT2,
					GL_COLOR_ATTACHMENT3,
					GL_COLOR_ATTACHMENT4,
					GL_COLOR_ATTACHMENT5,
					GL_COLOR_ATTACHMENT6,
					GL_COLOR_ATTACHMENT7,
					GL_COLOR_ATTACHMENT8,
					GL_COLOR_ATTACHMENT9,
					GL_COLOR_ATTACHMENT10,
					GL_COLOR_ATTACHMENT11,
					GL_COLOR_ATTACHMENT12,
					GL_COLOR_ATTACHMENT13,
					GL_COLOR_ATTACHMENT14,
					GL_COLOR_ATTACHMENT15
			};
			glDrawBuffers(_color_buffers.size(), attachments);

			if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
				Throw(tokurei::SetFailed);
			}

			glCheckError();
		}

		void FrameBuffer::clear() {
			_depth_buffer = NULL;
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 0, 0);

			for(size_t i=0 ; i<_color_buffers.size() ; ++i) {
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0+i, GL_TEXTURE_2D, 0, 0);
			}
			_color_buffers.clear();
		}

		void FrameBuffer::attatch(Texture *irendertarget, size_t ilayer) {
			if(!irendertarget) {
				Throw(tokurei::SetFailed);
			}

			GLenum attachment;
			if(irendertarget->format() != tex::Format::Depth && irendertarget->format() != tex::Format::Depth16 && irendertarget->format() != tex::Format::Depth24 && irendertarget->format() != tex::Format::Depth32f) {
				size_t next = _color_buffers.size();
				if(next == maxAttatchments()) {
					Throw(tokurei::SetFailed);
				}
				attachment = GL_COLOR_ATTACHMENT0+next;
				_color_buffers.push_back(irendertarget);
			} else {
				_depth_buffer = irendertarget;
				attachment = GL_DEPTH_ATTACHMENT;
			}

			tex::Target target = irendertarget->target();
			if(target == tex::Target::Tex1D) {
				glFramebufferTexture1D(GL_FRAMEBUFFER, attachment, translateTarget(irendertarget->target()), irendertarget->id(), 0);
			} else if(target == tex::Target::Tex2D || target == tex::Target::Tex1DArray || target == tex::Target::Rectangle) {
				glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, translateTarget(irendertarget->target()), irendertarget->id(), 0);
			} else if(target == tex::Target::Tex3D || target == tex::Target::Tex2DArray) {
				glFramebufferTexture3D(GL_FRAMEBUFFER, attachment, translateTarget(irendertarget->target()), irendertarget->id(), 0, ilayer);
			} else {
				Throw(tokurei::SetFailed);
			}
		}

		void FrameBuffer::attatch(Texture *irendertarget, tex::Target icube_face, size_t ilayer) {
			if(!irendertarget) {
				Throw(tokurei::SetFailed);
			}

			GLenum attachment;
			if(irendertarget->format() != tex::Format::Depth && irendertarget->format() != tex::Format::Depth16 && irendertarget->format() != tex::Format::Depth24 && irendertarget->format() != tex::Format::Depth32f) {
				size_t next = _color_buffers.size();
				if(next == maxAttatchments()) {
					Throw(tokurei::SetFailed);
				}
				attachment = GL_COLOR_ATTACHMENT0+next;
				_color_buffers.push_back(irendertarget);
			} else {
				_depth_buffer = irendertarget;
				attachment = GL_DEPTH_ATTACHMENT;
			}

			
			tex::Target target = irendertarget->target();
			if(target == tex::Target::CubeMap && (icube_face == tex::Target::CubeMapXm || icube_face == tex::Target::CubeMapXp || icube_face == tex::Target::CubeMapYm || icube_face == tex::Target::CubeMapYp || icube_face == tex::Target::CubeMapZm || icube_face == tex::Target::CubeMapZp)) {
				glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, translateTarget(icube_face), irendertarget->id(), 0);
			} else {
				Throw(tokurei::SetFailed);
			}
		}

		size_t FrameBuffer::maxAttatchments() {
			int maxattachments;
			glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &maxattachments);

			return (size_t)maxattachments;
		}
	}  // namespace graphic
}  // namespace cb
