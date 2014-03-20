/*
 * dXML.h
 *
 *  Created on: 13/12/2012
 *      Author: Douglas M. Freitas
 * 
 *   Copyright: Staff 42 © 2013
 */
#pragma once

#include <data/data.h>

#include <base/bException.h>
#include <base/bString.h>

namespace cb {
	namespace data {
		class CbAPI XML {
		public:
			class CbAPI Attribute {
			private:
				void *_attribute;

			public:
				Attribute(void *iattribute);

				bool empty();
				Attribute next();
				Attribute previous();

				bool name(base::string iname);
				base::string name();

				bool value(base::string ivalue);
				bool value(int ivalue);
				bool value(unsigned int ivalue);
				bool value(float ivalue);
				bool value(double ivalue);
				bool value(bool ivalue);
				base::string value();

				bool isInt();
				bool isUInt();
				bool isFloat();
				bool isDouble();
				bool isBool();

				int asInt();
				unsigned int asUInt();
				float asFloat();
				double asDouble();
				bool asBool();

				Attribute operator=(base::string istring);
				Attribute operator=(int iint);
				Attribute operator=(unsigned int iuint);
				Attribute operator=(float ifloat);
				Attribute operator=(double idouble);
				Attribute operator=(bool ibool);
			};

			class CbAPI Node {
			private:
				void *_node;

			public:
				Node(void *inode);

				Node operator[](base::string ikey);
				Attribute attr(base::string ikey);

				bool empty();
				Node parent();
				Node firstChild();
				Node lastChild();
				Node next();
				Node previous();

				Attribute firstAttr();
				Attribute lastAttr();

				bool name(base::string iname);
				base::string name();

				bool value(base::string ivalue);
				base::string value();

				bool text(base::string ivalue);
				base::string text();
			};

		private:
			void *_document;

		public:
			XML();
			~XML();

			void load(base::string ifilename);
			void save(base::string ifilename);

			Node operator[](base::string ikey);

			bool empty();
			Node firstChild();
			Node lastChild();
		};
	}  // namespace data
}  // namespace cb
