/* 
 * - Cumulonimbus - ☁
 * File: dJSON.cpp
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
#include <data/JSON.h>

#include <base/Log.h>

#include <limits>
#include <sstream>

namespace cb {
	namespace data {
		namespace json {
			void value::set() {
				switch(_type) {
				case Null:
					break;

				case Object:
					delete _data._object;
					break;

				case Array:
					delete _data._array;
					break;

				case String:
					delete _data._string;
					break;

				case Number:
				case Boolean:
					break;

				default:
					Throw(tokurei::SetFailed);
				}
				_data._null = nullptr;
				_type = Null;
			}

			void value::set(const object &iobj) {
				if(isObject()) {
					(*_data._object) = iobj;
				} else {
					set();
					_data._object = new object(iobj);
					_type = Object;
				}
			}

			void value::set(const array &iarray) {
				if(isArray()) {
					(*_data._array) = iarray;
				} else {
					set();
					_data._array = new array(iarray);
					_type = Array;
				}
			}

			void value::set(const string &istr) {
				if(isString()) {
					(*_data._string) = istr;
				} else {
					set();
					_data._string = new string(istr);
					_type = String;
				}
			}

			void value::set(number inum) {
				if(isNumber()) {
					_data._number = inum;
				} else {
					set();
					_data._number = inum;
					_type = Number;
				}
			}

			void value::set(boolean ibool) {
				if(isBoolean()) {
					_data._boolean = ibool;
				} else {
					set();
					_data._boolean = ibool;
					_type = Boolean;
				}
			}

			void value::set(const value &ivalue) {
				switch(ivalue._type) {
				case Null:
					set();
					break;

				case Object:
					set(*ivalue._data._object);
					break;

				case Array:
					set(*ivalue._data._array);
					break;

				case String:
					set(*ivalue._data._string);
					break;

				case Number:
					set(ivalue._data._number);
					break;

				case Boolean:
					set(ivalue._data._boolean);
					break;

				default:
					Throw(tokurei::SetFailed);
				}
			}

			class StreamSerializer {
			private:
				std::ostringstream &_file;

			public:
				StreamSerializer(std::ostringstream &ifile) : _file(ifile) {}

				void serializeValue(const value &ovalue, string iident) {
					if(ovalue.isObject()) {
						serializeObject(ovalue.obj(), iident);
					} else if(ovalue.isArray()) {
						serializeArray(ovalue.arr(), iident);
					} else if(ovalue.isString()) {
						serializeString(ovalue.str());
					} else if(ovalue.isNumber()) {
						serializeNumber(ovalue.num());
					} else if(ovalue.isBoolean()) {
						serializeBoolean(ovalue.boo());
					} else if(ovalue.isNull()) {
						serializeNull(ovalue.nil());
					} else {
						Throw(tokurei::SaveFailed);
					}
				}

				void serializeObject(const object &oobject, string iident) {
					object::const_iterator it = oobject.begin();
					_file << "{" << std::endl;
					while(it != oobject.end()) {
						_file << iident << "\t";
						serializeString(it->first);
						_file << " : ";
						serializeValue(it->second, iident + "\t");
						it++;
						if(it != oobject.end()) {
							_file << "," << std::endl;
						} else {
							_file << std::endl;
						}
					}
					_file << iident << "}";
				}

				void serializeArray(const array &oarray, string iident) {
					array::const_iterator it = oarray.begin();
					_file << "[" << std::endl;
					while(it != oarray.end()) {
						_file << iident << "\t";
						serializeValue(*it, iident + "\t");
						it++;
						if(it != oarray.end()) {
							_file << "," << std::endl;
						} else {
							_file << std::endl;
						}
					}
					_file << iident << "]";
				}

				void serializeString(const string &ostring) {
					string::const_iterator it = ostring.begin();
					_file.put('\"');
					while(it != ostring.end()) {
						if((*it) == '\"') {
							_file << "\\\"";

						} else if((*it) == '\\') {
							_file << "\\\\";

						} else if((*it) == '/') {
							_file << "\\/";

						} else if((*it) == '\b') {
							_file << "\\b";

						} else if((*it) == '\f') {
							_file << "\\f";

						} else if((*it) == '\n') {
							_file << "\\n";

						} else if((*it) == '\r') {
							_file << "\\r";

						} else if((*it) == '\t') {
							_file << "\\t";

						} else {
							_file.put(*it);
						}
						it++;
					}
					_file.put('\"');
				}

				void serializeNumber(const number &onumber) {
					_file << onumber;
				}

				void serializeBoolean(const boolean &oboolean) {
					_file << (oboolean?"true":"false");
				}

				void serializeNull(const null &onull) {
					_file << "null";
				}
			};

			class StreamParser {
			private:
				std::istringstream &_file;
				size_t _line;
				size_t _column;

				int get(bool ijumpspaces = true);
				int peek(bool ijumpspaces = true);
				void checkEOF() {
					if(_file.eof()) {
						ThrowDet(tokurei::LoadFailed, "JSON : Unexpected end of file : %d.%d", _line, _column);
					}
				}

			public:
				StreamParser(std::istringstream &ifile) : _file(ifile), _line(0), _column(0) {}

				void parseValue(value &ovalue);
				void parseObject(object &oobject);
				void parseArray(array &oarray);
				void parseString(string &ostring);
				void parseNumber(number &onumber);
				void parseBoolean(boolean &oboolean);
				void parseNull(null &onull);
			};

			int StreamParser::get(bool ijumpspaces) {
				int c = _file.get();
				_column++;
				if(c == '\n') {
					_line++;
					_column = 0;
				}

				while(isspace(c) && !_file.eof() && ijumpspaces) {
					c = _file.get();
					_column++;
					if(c == '\n') {
						_line++;
						_column = 0;
					}
				}
				return c;
			}
			int StreamParser::peek(bool ijumpspaces) {
				int c = _file.peek();
				while(isspace(c) && !_file.eof() && ijumpspaces) {
					_file.get();
					_column++;
					if(c == '\n') {
						_line++;
						_column = 0;
					}
					c = _file.peek();
				}
				return c;
			}

			void StreamParser::parseValue(value &ovalue) {
				char c = peek();
				checkEOF();

				if(c == '{') {
					ovalue = object();
					parseObject(ovalue.obj());

				} else if(c == '[') {
					ovalue = array();
					parseArray(ovalue.arr());

				} else if(c == '\"') {
					ovalue = string();
					parseString(ovalue.str());

				} else if(isdigit(c) || c=='-' || c=='+') {
					ovalue = number();
					parseNumber(ovalue.num());

				} else if(c == 't' || c == 'f' || c == 'T' || c == 'F') {
					ovalue = boolean();
					parseBoolean(ovalue.boo());

				} else if(c == 'n' || c == 'N') {
					ovalue = null();
					parseNull(ovalue.nil());

				} else {
					ThrowDet(tokurei::LoadFailed, "JSON : Invalid value, unexpected character : %d.%d", _line, _column);
				}
			}

			void StreamParser::parseObject(object &oobject) {
				oobject.clear();
				char c = get();
				checkEOF();

				if(c == '{') {
					do {
						string key;
						parseString(key);

						c = get();
						checkEOF();
						if(c == ':') {
							parseValue(oobject[key]);
						} else {
							ThrowDet(tokurei::LoadFailed, "JSON : Invalid object, unexpected character : %d.%d : (Expected ':')", _line, _column);
						}

						c = get();
						checkEOF();
					} while(c == ',');
					if(c != '}') {
						ThrowDet(tokurei::LoadFailed, "JSON : Invalid object, unexpected character : %d.%d : (Expected '}')", _line, _column);
					}
				} else {
					ThrowDet(tokurei::LoadFailed, "JSON : Invalid object, unexpected character : %d.%d : (Expected '{')", _line, _column);
				}
			}

			void StreamParser::parseArray(array &oarray) {
				oarray.clear();
				char c = get();
				checkEOF();

				if(c == '[') {
					do {
						oarray.push_back(value());
						parseValue(oarray.back());

						c = get();
						checkEOF();
					} while(c == ',');

					if(c != ']') {
						ThrowDet(tokurei::LoadFailed, "JSON : Invalid array, unexpected character : %d.%d : (Expected ']')", _line, _column);
					}
				} else {
					ThrowDet(tokurei::LoadFailed, "JSON : Invalid array, unexpected character : %d.%d : (Expected '[')", _line, _column);
				}
			}

			void StreamParser::parseString(string &ostring) {
				ostring.clear();
				char c = get();
				checkEOF();

				if(c == '\"') {
					c = get(false);
					checkEOF();

					while(c != '\"') {
						if(c == '\n' || c == '\r') {
							ThrowDet(tokurei::LoadFailed, "JSON : Invalid string, unexpected character : %d.%d : (Expected '\"')", _line, _column);
						} else if(c == '\\') {
							c = get(false);
							checkEOF();
							if(c == '\"') {
								ostring.push_back('\"');
							} else if(c == '\\') {
								ostring.push_back('\\');
							} else if(c == '/') {
								ostring.push_back('/');
							} else if(c == 'b') {
								ostring.push_back('\b');
							} else if(c == 'f') {
								ostring.push_back('\f');
							} else if(c == 'n') {
								ostring.push_back('\n');
							} else if(c == 'r') {
								ostring.push_back('\r');
							} else if(c == 't') {
								ostring.push_back('\t');
							} else if(c == 'u') {
								char cv[5] = {0,0,0,0,0};
								cv[0] = get(false);
								checkEOF();
								if(!isxdigit(cv[0])) {
									ThrowDet(tokurei::LoadFailed, "JSON : Invalid string, unexpected character : %d.%d : (Expected 'hex digit')", _line, _column);
								}
								cv[1] = get(false);
								checkEOF();
								if(!isxdigit(cv[1])) {
									ThrowDet(tokurei::LoadFailed, "JSON : Invalid string, unexpected character : %d.%d : (Expected 'hex digit')", _line, _column);
								}
								cv[2] = get(false);
								checkEOF();
								if(!isxdigit(cv[2])) {
									ThrowDet(tokurei::LoadFailed, "JSON : Invalid string, unexpected character : %d.%d : (Expected 'hex digit')", _line, _column);
								}
								cv[3] = get(false);
								checkEOF();
								if(!isxdigit(cv[3])) {
									ThrowDet(tokurei::LoadFailed, "JSON : Invalid string, unexpected character : %d.%d : (Expected 'hex digit')", _line, _column);
								}

								base::string32 lstr;
								lstr.push_back(strtoul(cv, NULL, 16));

								ostring += base::utf8(lstr);

							} else {
								ThrowDet(tokurei::LoadFailed, "JSON : Invalid string, unexpected character : %d.%d : (Expected '\"', '\\', '/', 'b', 'f', 'n', 'r', 't' or 'u')", _line, _column);
							}

						} else {
							ostring.push_back(c);
						}

						c = get(false);
						checkEOF();
					}

					if(c != '\"') {
						ThrowDet(tokurei::LoadFailed, "JSON : Invalid string, unexpected character : %d.%d : (Expected '\"')", _line, _column);
					}
				} else {
					ThrowDet(tokurei::LoadFailed, "JSON : Invalid string, unexpected character : %d.%d : (Expected '\"')", _line, _column);
				}
			}

			void StreamParser::parseNumber(number &onumber) {
				char c;
				string strnum;
				c = (get());
				checkEOF();
				if(c!='-' && c!='+' && !isdigit(c)) {
					ThrowDet(tokurei::LoadFailed, "JSON : Invalid number, unexpected character : %d.%d : (Expected '-', '+' or a digit)", _line, _column);
				}
				strnum.push_back(c);

				c = (peek(false));
				while(c=='-' || c=='+' || c=='.' || c=='e' || c=='E' || isdigit(c)) {
					c = (get(false));
					checkEOF();

					strnum.push_back(c);

					c = (peek(false));
				}

				try {
					onumber = std::stold(strnum);
				} catch (std::out_of_range &e) {
					ThrowDet(tokurei::LoadFailed, "JSON : Invalid number, too many digits : %d.%d : Error: %s", _line, _column, e.what());
				} catch (std::invalid_argument &e) {
					ThrowDet(tokurei::LoadFailed, "JSON : Invalid number : %d.%d : Error: %s", _line, _column, e.what());
				}
			}

			void StreamParser::parseBoolean(boolean &oboolean) {
				char c;
				c = (get());
				checkEOF();
				if(c == 'f') {
					c = (get(false));
					checkEOF();
					if(c != 'a') {
						ThrowDet(tokurei::LoadFailed, "JSON : Invalid boolean, unexpected character : %d.%d : (Expected 'a')", _line, _column);
					}
					c = (get(false));
					checkEOF();
					if(c != 'l') {
						ThrowDet(tokurei::LoadFailed, "JSON : Invalid boolean, unexpected character : %d.%d : (Expected 'l')", _line, _column);
					}
					c = (get(false));
					checkEOF();
					if(c != 's') {
						ThrowDet(tokurei::LoadFailed, "JSON : Invalid boolean, unexpected character : %d.%d : (Expected 's')", _line, _column);
					}
					c = (get(false));
					checkEOF();
					if(c != 'e') {
						ThrowDet(tokurei::LoadFailed, "JSON : Invalid boolean, unexpected character : %d.%d : (Expected 'e')", _line, _column);
					}
					oboolean = false;
				} else if(c == 't') {
					c = (get(false));
					checkEOF();
					if(c != 'r') {
						ThrowDet(tokurei::LoadFailed, "JSON : Invalid boolean, unexpected character : %d.%d : (Expected 'r')", _line, _column);
					}
					c = (get(false));
					checkEOF();
					if(c != 'u') {
						ThrowDet(tokurei::LoadFailed, "JSON : Invalid boolean, unexpected character : %d.%d : (Expected 'u')", _line, _column);
					}
					c = (get(false));
					checkEOF();
					if(c != 'e') {
						ThrowDet(tokurei::LoadFailed, "JSON : Invalid boolean, unexpected character : %d.%d : (Expected 'e')", _line, _column);
					}
					oboolean = true;
				} else {
					ThrowDet(tokurei::LoadFailed, "JSON : Invalid boolean, unexpected character : %d.%d : (Expected 't' or 'f')", _line, _column);
				}
			}

			void StreamParser::parseNull(null &onull) {
				char c;
				c = (get());
				checkEOF();
				if(c == 'n') {
					c = (get(false));
					checkEOF();
					if(c != 'u') {
						ThrowDet(tokurei::LoadFailed, "JSON : Invalid null, unexpected character : %d.%d : (Expected 'u')", _line, _column);
					}
					c = (get(false));
					checkEOF();
					if(c != 'l') {
						ThrowDet(tokurei::LoadFailed, "JSON : Invalid null, unexpected character : %d.%d : (Expected 'l')", _line, _column);
					}
					c = (get(false));
					checkEOF();
					if(c != 'l') {
						ThrowDet(tokurei::LoadFailed, "JSON : Invalid null, unexpected character : %d.%d : (Expected 'l')", _line, _column);
					}
				} else {
					ThrowDet(tokurei::LoadFailed, "JSON : Invalid null, unexpected character : %d.%d : (Expected 'n')", _line, _column);
				}
			}
		}  // namespace json

		void JSON::load(File &ifile) {
			base::string strfile(ifile.data(), ifile.size());
			std::istringstream instream;

			json::StreamParser parser(instream);
			parser.parseValue(value);
		}

		void JSON::save(File &ofile) {
			ofile.clear();
			std::ostringstream out;

			json::StreamSerializer ser(out);
			ser.serializeValue(value, "");
			out << std::endl;

			ofile.append(out.str().c_str(), out.str().size());
		}
	}  // namespace data
}  // namespace cb

