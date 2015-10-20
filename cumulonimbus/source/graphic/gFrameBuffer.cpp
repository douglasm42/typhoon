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
#include <cb/graphic/FrameBuffer.hpp>

#include <cb/graphic/tex/TextureHelper.hpp>

namespace cb {
	namespace graphic {
		FrameBuffer::FrameBuffer() :_id(0), _depth_buffer(nullptr) {
			_color_buffers.reserve(getMaxAttatchments());
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
			glCheckError;

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
			glDrawBuffers((uint32)_color_buffers.size(), attachments);

			if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
				Throw(tokurei::SetFailed);
			}

			glCheckError;
		}

		void FrameBuffer::clear() {
			_depth_buffer = NULL;
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 0, 0);

			for(size_t i=0 ; i<_color_buffers.size() ; ++i) {
				glFramebufferTexture2D(GL_FRAMEBUFFER, uint32(GL_COLOR_ATTACHMENT0+i), GL_TEXTURE_2D, 0, 0);
			}
			_color_buffers.clear();
		}

		void FrameBuffer::attatch(Texture *irendertarget, uint32 ilayer) {
			if(!irendertarget) {
				Throw(tokurei::SetFailed);
			}

			GLenum attachment;
			if( !isDepth(irendertarget->getFormat()) ) {
				size_t next = _color_buffers.size();
				if(next == getMaxAttatchments()) {
					Throw(tokurei::SetFailed);
				}
				attachment = uint32(GL_COLOR_ATTACHMENT0+next);
				_color_buffers.push_back(irendertarget);
			} else {
				_depth_buffer = irendertarget;
				attachment = GL_DEPTH_ATTACHMENT;
			}

			tex::Target target = irendertarget->getTarget();
			if(target == tex::Target::Tex1D) {
				glFramebufferTexture1D(GL_FRAMEBUFFER, attachment, GLenum(irendertarget->getTarget()), irendertarget->getID(), 0);
			} else if(target == tex::Target::Tex2D || target == tex::Target::Tex1DArray || target == tex::Target::Rectangle) {
				glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GLenum(irendertarget->getTarget()), irendertarget->getID(), 0);
			} else if(target == tex::Target::Tex3D || target == tex::Target::Tex2DArray) {
				glFramebufferTexture3D(GL_FRAMEBUFFER, attachment, GLenum(irendertarget->getTarget()), irendertarget->getID(), 0, ilayer);
			} else {
				Throw(tokurei::SetFailed);
			}
		}

		void FrameBuffer::attatch(CubeMap *irendertarget, tex::CubeMapFace icube_face, uint32 ilayer) {
			if(!irendertarget) {
				Throw(tokurei::SetFailed);
			}

			GLenum attachment;
			if(tex::isDepth(irendertarget->getFormat())) {
				size_t next = _color_buffers.size();
				if(next == getMaxAttatchments()) {
					Throw(tokurei::SetFailed);
				}
				attachment = uint32(GL_COLOR_ATTACHMENT0+next);
				_color_buffers.push_back(irendertarget);
			} else {
				_depth_buffer = irendertarget;
				attachment = GL_DEPTH_ATTACHMENT;
			}

			
			tex::Target target = irendertarget->getTarget();
			glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GLenum(icube_face), irendertarget->getID(), 0);
		}

		uint32 FrameBuffer::getMaxAttatchments() {
			int maxattachments;
			glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &maxattachments);

			return (uint32)maxattachments;
		}
	}  // namespace graphic
}  // namespace cb
