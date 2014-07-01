/* 
 * - Cumulonimbus - ☁
 * File: XML.h
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

#include <data/data.h>

#include <base/String.h>
#include <data/File.h>

namespace cb {
	namespace data {
//		namespace xml {
//			typedef enum Type {
//				Element,
//				Attribute,
//				Comment,
//				PCData,
//				CData,
//				PI
//			} Type;
//
//			KinLock(Attribute);
//			KinLock(Node);
//			KinLock(Element);
//			KinLock(Comment);
//			KinLock(PCData);
//			KinLock(CData);
//			KinLock(PI);
//
//			class CbAPI Attribute {
//			private:
//				kin::Attribute _attribute;
//
//			public:
//				Attribute(void *iattribute);
//
//				bool empty();
//				Attribute next();
//				Attribute previous();
//
//				bool name(base::string iname);
//				base::string name();
//
//				bool value(base::string ivalue);
//				bool value(int ivalue);
//				bool value(unsigned int ivalue);
//				bool value(float ivalue);
//				bool value(double ivalue);
//				bool value(bool ivalue);
//				base::string value();
//
//				bool isInt();
//				bool isUInt();
//				bool isFloat();
//				bool isDouble();
//				bool isBool();
//
//				int asInt();
//				unsigned int asUInt();
//				float asFloat();
//				double asDouble();
//				bool asBool();
//
//				Attribute operator=(base::string istring);
//				Attribute operator=(int iint);
//				Attribute operator=(unsigned int iuint);
//				Attribute operator=(float ifloat);
//				Attribute operator=(double idouble);
//				Attribute operator=(bool ibool);
//			};
//
//			class CbAPI Node {
//			private:
//				kin::Node _node;
//
//			public:
//				Node(void *inode);
//
//				Node operator[](base::string ikey);
//				Attribute attr(base::string ikey);
//
//				bool empty();
//				Node parent();
//				Node firstChild();
//				Node lastChild();
//				Node next();
//				Node previous();
//
//				Type type();
//
//				Attribute firstAttr();
//				Attribute lastAttr();
//
//				bool name(base::string iname);
//				base::string name();
//
//				bool value(base::string ivalue);
//				base::string value();
//			};
//
//		}  // namespace xml


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

			void load(File &ifile);
			void save(File &ifile);

			Node operator[](base::string ikey);

			bool empty();
			Node firstChild();
			Node lastChild();
		};
	}  // namespace data
}  // namespace cb
