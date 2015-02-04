/* 
 * - Cumulonimbus - ☁
 * File: JSON.h
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

#include <cb/data/data.h>

#include <cb/base/String.h>
#include <cb/base/Exception.h>

#include <cb/data/File.h>

#include <map>
#include <vector>

namespace cb {
	namespace data {
		namespace json {
			typedef enum type {
				Null,
				Object,
				Array,
				String,
				Number,
				Boolean
			} type;

			class CbAPI value;

			typedef std::nullptr_t			null;
			typedef bool					boolean;
			typedef long double				number;
			typedef base::string			string;
			typedef std::vector<value>		array;
			typedef std::map<string, value>	object;

			union value_data {
				null	_null;
				object	*_object;
				array	*_array;
				string	*_string;
				number	_number;
				boolean	_boolean;
			};

			class CbAPI value {
			private:
				type _type;
				union value_data _data;

				void set();
				void set(const object &iobj);
				void set(const array &iarray);
				void set(const string &istr);
				void set(const number inum);
				void set(const boolean ibool);
				void set(const value &ivalue);

			public:
				value()						:_type(Null), _data() {set();}
				value(object iobj)			:_type(Null), _data() {set(iobj);}
				value(array iarray)			:_type(Null), _data() {set(iarray);}
				value(string istr)			:_type(Null), _data() {set(istr);}
				value(number inum)			:_type(Null), _data() {set(inum);}
				value(boolean ibool)		:_type(Null), _data() {set(ibool);}
				value(const value &ivalue)	:_type(Null), _data() {set(ivalue);}
				~value() {set();}

				value &operator=(const null inull)		{set();			return *this;}
				value &operator=(const object &iobj)	{set(iobj);		return *this;}
				value &operator=(const array &iarray)	{set(iarray);	return *this;}
				value &operator=(const string &istr)	{set(istr);		return *this;}
				value &operator=(const number inum)		{set(inum);		return *this;}
				value &operator=(const boolean ibool)	{set(ibool);	return *this;}
				value &operator=(const value &ivalue)	{set(ivalue);	return *this;}

				value &operator=(const char inum)		{set(number(inum));		return *this;}
				value &operator=(const short inum)		{set(number(inum));		return *this;}
				value &operator=(const int inum)		{set(number(inum));		return *this;}
				value &operator=(const long inum)		{set(number(inum));		return *this;}
				value &operator=(const long long inum)	{set(number(inum));		return *this;}
				value &operator=(const float inum)		{set(number(inum));		return *this;}
				value &operator=(const double inum)		{set(number(inum));		return *this;}

				value &operator=(const unsigned char inum)		{set(number(inum));		return *this;}
				value &operator=(const unsigned short inum)		{set(number(inum));		return *this;}
				value &operator=(const unsigned int inum)		{set(number(inum));		return *this;}
				value &operator=(const unsigned long inum)		{set(number(inum));		return *this;}
				value &operator=(const unsigned long long inum)	{set(number(inum));		return *this;}

				operator null() const		{return nil();}
				operator object() const		{return obj();}
				operator array() const		{return arr();}
				operator string() const		{return str();}
				operator number() const		{return num();}
				operator boolean() const	{return boo();}

				operator char() const		{return		 (char)num();}
				operator short() const		{return		(short)num();}
				operator int() const		{return		  (int)num();}
				operator long() const		{return		 (long)num();}
				operator long long() const	{return	(long long)num();}
				operator float() const		{return		(float)num();}
				operator double() const		{return	   (double)num();}

				operator unsigned char() const		{return		 (unsigned char)num();}
				operator unsigned short() const		{return		(unsigned short)num();}
				operator unsigned int() const		{return		  (unsigned int)num();}
				operator unsigned long() const		{return		 (unsigned long)num();}
				operator unsigned long long() const	{return	(unsigned long long)num();}

				bool isNull() const;
				bool isObject() const;
				bool isArray() const;
				bool isString() const;
				bool isNumber() const;
				bool isBoolean() const;

				const null &nil() const;
				const object &obj() const;
				const array &arr() const;
				const string &str() const;
				const number &num() const;
				const boolean &boo() const;

				null &nil();
				object &obj();
				array &arr();
				string &str();
				number &num();
				boolean &boo();

				value &operator[](const int ipos);
				value &operator[](const base::string &ikey);
				value &operator[](const char *ikey);

				bool empty() const;
			};

			inline bool value::isNull()		const {return _type==Null;}
			inline bool value::isObject()	const {return _type==Object;}
			inline bool value::isArray()	const {return _type==Array;}
			inline bool value::isString()	const {return _type==String;}
			inline bool value::isNumber()	const {return _type==Number;}
			inline bool value::isBoolean()	const {return _type==Boolean;}

			inline const null		&value::nil()	const {if(_type!=Null)		{Throw(tokurei::GetFailed);}	return _data._null;}
			inline const object		&value::obj()	const {if(_type!=Object)	{Throw(tokurei::GetFailed);}	return *_data._object;}
			inline const array		&value::arr()	const {if(_type!=Array)		{Throw(tokurei::GetFailed);}	return *_data._array;}
			inline const string		&value::str()	const {if(_type!=String)	{Throw(tokurei::GetFailed);}	return *_data._string;}
			inline const number		&value::num()	const {if(_type!=Number)	{Throw(tokurei::GetFailed);}	return _data._number;}
			inline const boolean	&value::boo()	const {if(_type!=Boolean)	{Throw(tokurei::GetFailed);}	return _data._boolean;}

			inline null		&value::nil()	{if(_type!=Null)	{Throw(tokurei::GetFailed);}	return _data._null;}
			inline object	&value::obj()	{if(_type!=Object)	{Throw(tokurei::GetFailed);}	return *_data._object;}
			inline array	&value::arr()	{if(_type!=Array)	{Throw(tokurei::GetFailed);}	return *_data._array;}
			inline string	&value::str()	{if(_type!=String)	{Throw(tokurei::GetFailed);}	return *_data._string;}
			inline number	&value::num()	{if(_type!=Number)	{Throw(tokurei::GetFailed);}	return _data._number;}
			inline boolean	&value::boo()	{if(_type!=Boolean)	{Throw(tokurei::GetFailed);}	return _data._boolean;}

			inline value &value::operator[](const int ipos)			{return arr()[ipos];}
			inline value &value::operator[](const base::string &ikey)	{return obj()[ikey];}
			inline value &value::operator[](const char *ikey)			{return obj()[ikey];}

			inline bool value::empty() const {return isNull();}
		}  // namespace json

		class CbAPI JSON {
		public:
			json::value value;

			JSON() {}
			JSON(File &ifile) {load(ifile);}
			JSON(const JSON &ijson) :value(ijson.value) {}
			~JSON() {}

			void load(File &ifile);

			void save(File &ofile);
		};
	}  // namespace data
}  // namespace cb
