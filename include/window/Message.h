/*
 * sMessage.h
 *
 *  Created on: Apr 30, 2014
 *      Author: douglas
 */

#pragma once

#include <window/window.h>

#include <base/String.h>

#include <vector>

namespace cb {
	namespace window {
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
			std::vector<base::wstring> _message_lines;

			void show();

			void setMessage(base::wstring imessage) {
				_message_lines.clear();
				_message_lines.push_back(base::wstring());
				for(size_t i=0 ; i<imessage.length() ; i++) {
					if(imessage[i] == L'\n') {
						_message_lines.push_back(base::wstring());
					} else {
						_message_lines.back().push_back(imessage[i]);
					}
				}
			}

		public:
			Message(msg::Type itype, base::wstring imessage):_type(itype) {setMessage(imessage); show();}
			Message(msg::Type itype, base::string imessage):_type(itype) {setMessage(base::utf16(imessage)); show();}
			~Message() {}
		};
	}  // namespace window
}  // namespace cb
