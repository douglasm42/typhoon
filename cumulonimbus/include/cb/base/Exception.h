/* 
 * - Cumulonimbus - ☁
 * File: Exception.h
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

#include <cb/base/base.h>

#include <cb/base/String.h>
#include <cb/base/FormatMacro.h>

#include <exception>
#include <typeinfo>

namespace cb {
	/**
	 * Em japonês, tokurei ou 特例, significa caso especial, ou exceção. Usei este nome para não entrar em
	 * conflito com a classe exception. Esse namespace contém todas as exceções que podem ser lançadas
	 * pela cumulonimbus.
	 */
	namespace tokurei {
		/**
		 * Classe base para as exceções. Toda exceção deriva dessa classe e todas as exceções lançadas deve ser
		 * um objeto dessa classe ou de uma derivada dela.
		 */
		class CbAPI Exception : public std::exception {
		protected:
			///Motivo da exceção.
			base::string _what;

		public:
			/**
			 * Construtor da exceção, deve receber o motivo da mesma por parametro e o tipo.
			 * @param iwhere Local onde a exceção foi lançada.
			 * @param iwhat Motivo da exceção.
			 */
			Exception(const base::string &iwhere, const base::string &iwhat) : _what("Exception in " + iwhere + " : " + iwhat) {}

			/**
			 * Destrutor da exceção.
			 */
			virtual ~Exception() {}

			/**
			 * Retorna o motivo da exceção precedido por seu tipo.
			 * @return O motivo da exceção precedido por seu tipo.
			 */
			const char *what() const {return _what.c_str();}
		};

#define STR1(x) #x
#define STR2(x) STR1(x)
#define WHERE (__FILE__ ":" STR2(__LINE__))

#ifdef CbDebug
#	define Assert(exp, ExceptionClass) if(!(exp)) {throw ExceptionClass(WHERE);}
#	define AssertDet(exp, ExceptionClass, detail, ...) if(!(exp)) {throw ExceptionClass(WHERE, detail, ##__VA_ARGS__);}
#else
#	define Assert(exp, ExceptionClass)
#	define AssertDet(exp, ExceptionClass, detail, ...)
#endif

#define Throw(ExceptionClass) throw ExceptionClass(WHERE)
#define ThrowDet(ExceptionClass, detail, ...) throw ExceptionClass(WHERE, detail, ##__VA_ARGS__)

#define ModuleException(Module)\
		class CbAPI Module : public tokurei::Exception {\
		public:\
			Module(const base::string &iwhere, const base::string &iwhat) : Exception(iwhere, #Module":" + iwhat) {}\
		}

#define DetailedException(Base, Name, message)\
		class CbAPI Name : public Base {\
		public:\
			Name(const base::string &iwhere) : Base(iwhere, #Name " - " message) {}\
			Name(const base::string &iwhere, const base::string &idetailformat, ...) : Base(iwhere, #Name " - " message " - ") {\
				base::string msg;\
				CUMULONIMBUS_FORMAT(msg, idetailformat);\
				_what += msg;\
			}\
		}

		ModuleException(Log);
		ModuleException(Common);
		ModuleException(File);
		ModuleException(GL);

		DetailedException(Log, LogUninitialized, "Tried to use a uninitialized log system.");
		DetailedException(Log, LogCreateFileError, "Failed to create the log file.");
		DetailedException(Log, LogOpenFileError, "Failed to open the log file.");

		DetailedException(Common, NullObject, "Tried to use a null object.");
		DetailedException(Common, EmptyObject, "Tried to use a empty object.");
		DetailedException(Common, OutOfMemory, "Not enough memory to create object.");
		DetailedException(Common, CorruptedInfo, "Corrupted data or wrong format.");

		DetailedException(Common, SetFailed, "Failed to set an attribute of a object.");
		DetailedException(Common, GetFailed, "Failed to get an attribute of a object.");
		DetailedException(Common, BindFailed, "Failed to bind two objects.");
		DetailedException(Common, UnbindFailed, "Failed to unbind two objects.");
		DetailedException(Common, ClearFailed, "Failed to get an attribute of a object.");
		DetailedException(Common, AdvanceFailed, "Failed to get an attribute of a object.");
		DetailedException(Common, OutOfRange, "Tried to access a object out of a range.");
		DetailedException(Common, NotFound, "Failed to find object.");
		DetailedException(Common, ActivateFailed, "Failed to activate a object.");
		DetailedException(Common, DeactivateFailed, "Failed to deactivate a object.");

		DetailedException(Common, InitError, "Failed to initialize object.");
		DetailedException(Common, CreateError, "Failed to create object.");
		DetailedException(Common, DeleteError, "Failed to delete object.");
		DetailedException(Common, OpenError, "Failed to open object.");
		DetailedException(Common, CloseError, "Failed to close object.");

		DetailedException(Common, LoadFailed, "Failed to load object.");
		DetailedException(Common, SaveFailed, "Failed to save object.");

		DetailedException(File, FileReadOnly, "Read only.");
		DetailedException(File, FileWriteError, "Failed to write.");
		DetailedException(File, FileReadError, "Failed to write.");
		DetailedException(File, FileSerializeError, "Failed to serialize object.");

		DetailedException(GL, GLUnavailableExtension, "A required extension is unavailable.");
		DetailedException(GL, GLUninitialized, "The OpenGL was not initialized.");

		DetailedException(GL, GLInvalidEnum, "An unacceptable value is specified for an enumerated argument.");
		DetailedException(GL, GLInvalidValue, "A numeric argument is out of range.");
		DetailedException(GL, GLInvalidOperation, "The specified operation is not allowed in the current state.");
		DetailedException(GL, GLInvalidFramebufferOperation, "The framebuffer object is not complete.");
		DetailedException(GL, GLOutOfMemory, "There is not enough memory left to execute the command.");
		DetailedException(GL, GLStackUnderflow, "An attempt has been made to perform an operation that would cause an internal stack to underflow.");
		DetailedException(GL, GLStackOverflow, "An attempt has been made to perform an operation that would cause an internal stack to overflow.");
		DetailedException(GL, GLUnknown, "Unknown error code.");
	}  // namespace tokurei
}  // namespace cb
