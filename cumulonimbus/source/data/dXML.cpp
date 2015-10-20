/* 
 * - Cumulonimbus - ☁
 * File: dXML.cpp
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
#include <cb/data/XML.hpp>

#include <cb/base/Exception.hpp>

#include <pugixml.hpp>

#include <stdexcept>

#define ENCODE(x) (static_cast<void *>(x))
#define DECODE(type, x) (static_cast<type *>(x))

#define ENCNODE(x) XML::Node(ENCODE(x.internal_object()))
#define ENCATTR(x) XML::Attribute(ENCODE(x.internal_object()))

#define DECNODE(obj, x) pugi::xml_node obj(DECODE(pugi::xml_node_struct, x));
#define DECATTR(obj, x) pugi::xml_attribute obj(DECODE(pugi::xml_attribute_struct, x));

namespace cb {
	namespace data {
		//======================================================================
		// class XML::Attribute
		//======================================================================
		XML::Attribute::Attribute(void *iattribute)
		:_attribute(iattribute) {
		}

		bool XML::Attribute::empty() {
			DECATTR(attr, _attribute);
			return attr.empty();
		}

		XML::Attribute XML::Attribute::next() {
			DECATTR(attr, _attribute);
			return ENCATTR(attr.next_attribute());
		}

		XML::Attribute XML::Attribute::previous() {
			DECATTR(attr, _attribute);
			return ENCATTR(attr.previous_attribute());
		}

		bool XML::Attribute::name(base::string iname) {
			DECATTR(attr, _attribute);
			return attr.set_name(iname.c_str());
		}

		base::string XML::Attribute::name() {
			DECATTR(attr, _attribute);
			return base::string(attr.name());
		}

		bool XML::Attribute::value(base::string ivalue) {
			DECATTR(attr, _attribute);
			return attr.set_value(ivalue.c_str());
		}

		base::string XML::Attribute::value() {
			DECATTR(attr, _attribute);
			return base::string(attr.value());
		}

		bool XML::Attribute::isInt() {
			try {
				std::stoi(value());
				return true;
			} catch (std::out_of_range &) {
			} catch (std::invalid_argument &) {
			}
			return false;
		}
		bool XML::Attribute::isUInt() {
			try {
				std::stoul(value());
				return true;
			} catch (std::out_of_range &) {
			} catch (std::invalid_argument &) {
			}
			return false;
		}
		bool XML::Attribute::isFloat() {
			try {
				std::stof(value());
				return true;
			} catch (std::out_of_range &) {
			} catch (std::invalid_argument &) {
			}
			return false;
		}
		bool XML::Attribute::isDouble() {
			try {
				std::stod(value());
				return true;
			} catch (std::out_of_range &) {
			} catch (std::invalid_argument &) {
			}
			return false;
		}
		bool XML::Attribute::isBool() {
			return base::lower(value()) == "true" || base::lower(value()) == "false";
		}

		int XML::Attribute::asInt() {
			DECATTR(attr, _attribute);
			return attr.as_int();
		}
		unsigned int XML::Attribute::asUInt() {
			DECATTR(attr, _attribute);
			return attr.as_uint();
		}
		float XML::Attribute::asFloat() {
			DECATTR(attr, _attribute);
			return attr.as_float();
		}
		double XML::Attribute::asDouble() {
			DECATTR(attr, _attribute);
			return attr.as_double();
		}
		bool XML::Attribute::asBool() {
			DECATTR(attr, _attribute);
			return attr.as_bool();
		}

		XML::Attribute XML::Attribute::operator=(base::string istring) {
			DECATTR(attr, _attribute);
			attr.set_value(istring.c_str());
			return *this;
		}
		XML::Attribute XML::Attribute::operator=(int iint) {
			DECATTR(attr, _attribute);
			attr.set_value(iint);
			return *this;
		}
		XML::Attribute XML::Attribute::operator=(unsigned int iuint) {
			DECATTR(attr, _attribute);
			attr.set_value(iuint);
			return *this;
		}
		XML::Attribute XML::Attribute::operator=(float ifloat) {
			DECATTR(attr, _attribute);
			attr.set_value((double)ifloat);
			return *this;
		}
		XML::Attribute XML::Attribute::operator=(double idouble) {
			DECATTR(attr, _attribute);
			attr.set_value(idouble);
			return *this;
		}
		XML::Attribute XML::Attribute::operator=(bool ibool) {
			DECATTR(attr, _attribute);
			attr.set_value(ibool);
			return *this;
		}

		//======================================================================
		// class XML::Node
		//======================================================================
		XML::Node::Node(void *inode)
		:_node(inode) {
		}

		XML::Node XML::Node::operator[](base::string ikey) {
			DECNODE(node, _node);

			pugi::xml_node newnode = node.child(ikey.c_str());
			if(newnode.empty()) {
				newnode = node.append_child(ikey.c_str());
			}

			return ENCNODE(newnode);
		}

		XML::Attribute XML::Node::attr(base::string ikey) {
			DECNODE(node, _node);

			pugi::xml_attribute attr = node.attribute(ikey.c_str());
			if(attr.empty()) {
				attr = node.append_attribute(ikey.c_str());
			}

			return ENCATTR(attr);
		}

		bool XML::Node::empty() {
			DECNODE(node, _node);
			return node.empty();
		}

		XML::Node XML::Node::parent() {
			DECNODE(node, _node);
			return ENCNODE(node.parent());
		}

		XML::Node XML::Node::firstChild() {
			DECNODE(node, _node);
			return ENCNODE(node.first_child());
		}

		XML::Node XML::Node::lastChild() {
			DECNODE(node, _node);
			return ENCNODE(node.last_child());
		}

		XML::Node XML::Node::next() {
			DECNODE(node, _node);
			return ENCNODE(node.next_sibling());
		}

		XML::Node XML::Node::previous() {
			DECNODE(node, _node);
			return ENCNODE(node.previous_sibling());
		}

		XML::Attribute XML::Node::firstAttr() {
			DECNODE(node, _node);
			return ENCATTR(node.first_attribute());
		}

		XML::Attribute XML::Node::lastAttr() {
			DECNODE(node, _node);
			return ENCATTR(node.last_attribute());
		}

		bool XML::Node::name(base::string iname) {
			DECNODE(node, _node);
			return node.set_name(iname.c_str());
		}

		base::string XML::Node::name() {
			DECNODE(node, _node);
			return base::string(node.name());
		}

		bool XML::Node::value(base::string ivalue) {
			DECNODE(node, _node);
			return node.set_value(ivalue.c_str());
		}

		base::string XML::Node::value() {
			DECNODE(node, _node);
			return base::string(node.value());
		}

		bool XML::Node::text(base::string ivalue) {
			DECNODE(node, _node);
			return node.text().set(ivalue.c_str());
		}

		base::string XML::Node::text() {
			DECNODE(node, _node);
			return base::trim(base::string(node.text().get()));
		}

		//======================================================================
		// class XML
		//======================================================================
		XML::XML() {
			_document = ENCODE(new pugi::xml_document);
			//pugi::xml_document &doc = *DECODE(pugi::xml_document, _document);
		}

		XML::~XML() {
			delete DECODE(pugi::xml_document, _document);
		}

		void XML::load(Blob &ifile) {
			pugi::xml_document &doc = *DECODE(pugi::xml_document, _document);

			pugi::xml_parse_result result = doc.load_buffer(ifile.data(), ifile.size());
			if(!result) {
				ThrowDet(tokurei::LoadFailed, "Error: %s", result.description());
			}
		}

		class FileWriter : public pugi::xml_writer {
		private:
			Blob &_file;

		public:
			FileWriter(Blob &ifile) : _file(ifile) {}

			virtual void write(const void* idata, size_t isize);
		};

		void FileWriter::write(const void* idata, size_t isize) {
			_file.append(reinterpret_cast<const char *>(idata), isize);
		}

		void XML::save(Blob &ifile) {
			pugi::xml_document &doc = *DECODE(pugi::xml_document, _document);

			ifile.clear();
			FileWriter writer(ifile);

			doc.save(writer, "\t", 1U, pugi::encoding_utf8);
		}

		XML::Node XML::operator[](base::string ikey) {
			pugi::xml_document &doc = *DECODE(pugi::xml_document, _document);

			pugi::xml_node newnode = doc.child(ikey.c_str());
			if(newnode.empty()) {
				newnode = doc.append_child(ikey.c_str());
			}

			return ENCNODE(newnode);
		}

		bool XML::empty() {
			pugi::xml_document &doc = *DECODE(pugi::xml_document, _document);
			return doc.empty();
		}
		XML::Node XML::firstChild() {
			pugi::xml_document &doc = *DECODE(pugi::xml_document, _document);
			return ENCNODE(doc.first_child());
		}
		XML::Node XML::lastChild() {
			pugi::xml_document &doc = *DECODE(pugi::xml_document, _document);
			return ENCNODE(doc.last_child());
		}
	}  // namespace data
}  // namespace cb
