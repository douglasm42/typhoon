/* 
 * - Cumulonimbus - ☁
 * File: Random.h
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

#include <cb/video/video.h>

#include <cb/base/String.h>

#include <vector>

namespace cb {
	namespace video {
		namespace msg {
			typedef enum Type {
				Error,
				Warning,
				Info
			} Type;
		}  // namespace msg

		class CbAPI Message {
		private:
			msg::Type _type;
			std::vector<base::string16> _message_lines;

			void show();

			void setMessage(base::string16 imessage) {
				_message_lines.clear();
				_message_lines.push_back(base::string16());
				for(size_t i=0 ; i<imessage.length() ; i++) {
					if(imessage[i] == L'\n') {
						_message_lines.push_back(base::string16());
					} else {
						_message_lines.back().push_back(imessage[i]);
					}
				}
			}

		public:
			Message(msg::Type itype, base::string16 imessage):_type(itype) {setMessage(imessage); show();}
			Message(msg::Type itype, base::string imessage):_type(itype) {setMessage(base::utf16(imessage)); show();}
			~Message() {}
		};
	}  // namespace video
}  // namespace cb
