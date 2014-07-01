/* 
 * - Cumulonimbus - ☁
 * File: Key.h
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

#include <input/input.h>

#include <base/String.h>

#include <cstdint>

namespace cb {
	namespace input {
		class CbAPI Key {
		public:
			enum Type {
				Keyboard,
				Mouse,
				XController,
				Controller
			};

			enum User {
				Player0,
				Player1,
				Player2,
				Player3,
				Player4,
				Player5,
				Player6,
				Player7,
				Player8
			};

			/**
			 * Códigos de teclas virtuais. Cada tecla do teclado possui uma representação nessa lista, assim como o
			 * mouse e qualquer outro dispositivo de entrada.
			 */
			enum Code {
				Null,             //!< Tecla nula.

				//Teclado
				KBEsc,            //!< Escape;

				KBTab,            //!< Tab;
				KBEnter,          //!< Enter/Return;
				KBSpace,          //!< Space;
				KBBackspace,      //!< Backspace;

				KBPageUp,         //!< PageUp;
				KBPageDown,       //!< PageDown;
				KBEnd,            //!< End;
				KBHome,           //!< Home;
				KBInsert,         //!< Insert;
				KBDelete,         //!< Delete;
				KBClear,          //!< Clear;

				KBPrintScreen,    //!< PrintScreen/Sys Req;
				KBBreak,          //!< Pause/Break;
				KBSleep,          //!< Sleep;
				KBApplication,    //!< Application;

				KBCapsLock,       //!< Caps Lock;
				KBNumLock,        //!< Num Lock;
				KBScrollLock,     //!< Scroll Lock;

				KBLeft,           //!< Ceta para Esquerda;
				KBUp,             //!< Ceta para Cima;
				KBRight,          //!< Ceta para Direita;
				KBDown,           //!< Ceta para Baixo;

				KB0,              //!< Número 0;
				KB1,              //!< Número 1;
				KB2,              //!< Número 2;
				KB3,              //!< Número 3;
				KB4,              //!< Número 4;
				KB5,              //!< Número 5;
				KB6,              //!< Número 6;
				KB7,              //!< Número 7;
				KB8,              //!< Número 8;
				KB9,              //!< Número 9;

				KBA,              //!< Letra A;
				KBB,              //!< Letra B;
				KBC,              //!< Letra C;
				KBD,              //!< Letra D;
				KBE,              //!< Letra E;
				KBF,              //!< Letra F;
				KBG,              //!< Letra G;
				KBH,              //!< Letra H;
				KBI,              //!< Letra I;
				KBJ,              //!< Letra J;
				KBK,              //!< Letra K;
				KBL,              //!< Letra L;
				KBM,              //!< Letra M;
				KBN,              //!< Letra N;
				KBO,              //!< Letra O;
				KBP,              //!< Letra P;
				KBQ,              //!< Letra Q;
				KBR,              //!< Letra R;
				KBS,              //!< Letra S;
				KBT,              //!< Letra T;
				KBU,              //!< Letra U;
				KBV,              //!< Letra V;
				KBW,              //!< Letra W;
				KBX,              //!< Letra X;
				KBY,              //!< Letra Y;
				KBZ,              //!< Letra Z;

				KBNum0,           //!< Teclado numérico: 0;
				KBNum1,           //!< Teclado numérico: 1;
				KBNum2,           //!< Teclado numérico: 2;
				KBNum3,           //!< Teclado numérico: 3;
				KBNum4,           //!< Teclado numérico: 4;
				KBNum5,           //!< Teclado numérico: 5;
				KBNum6,           //!< Teclado numérico: 6;
				KBNum7,           //!< Teclado numérico: 7;
				KBNum8,           //!< Teclado numérico: 8;
				KBNum9,           //!< Teclado numérico: 9;
				KBNumMult,        //!< Teclado numérico: */Vezes;
				KBNumPlus,        //!< Teclado numérico: +/Mais;
				KBNumMinus,       //!< Teclado numérico: -/Menos;
				KBNumDel,         //!< Teclado numérico: Del/Delete;
				KBNumDiv,         //!< Teclado numérico: / /Dividir;
				KBNumPeriod,      //!< Teclado numérico: ./Ponto;

				KBF1,             //!< F1;
				KBF2,             //!< F2;
				KBF3,             //!< F3;
				KBF4,             //!< F4;
				KBF5,             //!< F5;
				KBF6,             //!< F6;
				KBF7,             //!< F7;
				KBF8,             //!< F8;
				KBF9,             //!< F9;
				KBF10,            //!< F10;
				KBF11,            //!< F11;
				KBF12,            //!< F12;

				KBLeftShift,      //!< Left Shift;
				KBRightShift,     //!< Right Shift;
				KBLeftCtrl,       //!< Left Ctrl;
				KBRightCtrl,      //!< Right Ctrl;
				KBLeftAlt,        //!< Left Alt;
				KBRightAlt,       //!< Right Alt;
				KBLeftSuper,      //!< Left Super/Windows;
				KBRightSuper,     //!< Right Super/Windows;

				KBCedille,        //!< Ç/Cedilha;
				KBEqual,          //!< =/Igual;
				KBComma,          //!< ,/Virgula;
				KBMinus,          //!< -/Menos;
				KBPeriod ,        //!< ./Ponto;
				KBSemicolon,      //!< ;/Ponto e virgula;
				KBApostrophe,     //!< '/Aspas;
				KBAgudo,          //!< ´/Agudo;
				KBBracketClose,   //!< ]/Fecha colchetes;
				KBBracketOpen,    //!< [/Abre colchetes;
				KBTil,            //!< ~/Til;
				KBSlash,          //!< / /Barra;
				KBBackslash,      //!< \ /Barra invertida;

				//Mouse
				MouseHu,          //!< Eixo positivo horizontal do mouse;
				MouseHd,          //!< Eixo negativo horizontal do mouse;
				MouseVu,          //!< Eixo positivo vertical do mouse;
				MouseVd,          //!< Eixo negativo vertical do mouse;
				MouseMu,          //!< Roda do mouse, movimentação positiva;
				MouseMd,          //!< Roda do mouse, movimentação negativa;

				MouseLeft,        //!< Botão esquerdo do mouse;
				MouseRight,       //!< Botão direito do mouse;
				MouseMiddle,      //!< Botão do meio do mouse;
				MouseX1,          //!< Primeiro botão extra do mouse;
				MouseX2,          //!< Segundo botão extra do mouse;
				MouseX3,          //!< Terceiro botão extra do mouse;
				MouseX4,          //!< Quarto botão extra do mouse;
				MouseX5,          //!< Quinto botão extra do mouse;

				//XBox Controller
				XbA,
				XbB,
				XbX,
				XbY,

				XbStart,
				XbBack,

				XbLeft,
				XbUp,
				XbRight,
				XbDown,

				XbLThumb,
				XbLThumbLeft,
				XbLThumbUp,
				XbLThumbRight,
				XbLThumbDown,

				XbLThumbUpLeft,
				XbLThumbUpRight,
				XbLThumbDownLeft,
				XbLThumbDownRight,

				XbRThumb,
				XbRThumbLeft,
				XbRThumbUp,
				XbRThumbRight,
				XbRThumbDown,

				XbRThumbUpLeft,
				XbRThumbUpRight,
				XbRThumbDownLeft,
				XbRThumbDownRight,

				XbLTrigger,
				XbLShoulder,

				XbRTrigger,
				XbRShoulder,

				//Controller
				CButton01,
				CButton02,
				CButton03,
				CButton04,
				CButton05,
				CButton06,
				CButton07,
				CButton08,

				CButton09,
				CButton10,
				CButton11,
				CButton12,
				CButton13,
				CButton14,
				CButton15,
				CButton16,

				CButton17,
				CButton18,
				CButton19,
				CButton20,
				CButton21,
				CButton22,
				CButton23,
				CButton24,

				CButton25,
				CButton26,
				CButton27,
				CButton28,
				CButton29,
				CButton30,
				CButton31,
				CButton32,

				CAxisXp,
				CAxisXm,
				CAxisYp,
				CAxisYm,
				CAxisZp,
				CAxisZm,

				CAxisRXp,
				CAxisRXm,
				CAxisRYp,
				CAxisRYm,
				CAxisRZp,
				CAxisRZm,

				CSliderUp,
				CSliderUm,
				CSliderVp,
				CSliderVm,

				CPOV1Left,
				CPOV1Up,
				CPOV1Right,
				CPOV1Down,

				CPOV2Left,
				CPOV2Up,
				CPOV2Right,
				CPOV2Down,

				CPOV3Left,
				CPOV3Up,
				CPOV3Right,
				CPOV3Down,

				CPOV4Left,
				CPOV4Up,
				CPOV4Right,
				CPOV4Down,
			};

			User user;
			Code code;

			Key();
			Key(User iuser, Code icode);
			Key(Code icode);
			Key(const Key &ikey);

			static Type type(Code ikey);

			static base::string str(Type itype);
			static base::string str(User iuser);
			static base::string str(Code icode);

			Type type();
			base::string str();

			Key &operator=(const Key &ikey);

			bool operator==(const Type itype);
			bool operator==(const User iuser);
			bool operator==(const Code icode);
		};

		inline Key::Key() : user(User::Player0), code(Null) {}
		inline Key::Key(User iuser, Code icode) : user(iuser), code(icode) {}
		inline Key::Key(Code ikey) : user(User::Player0), code(ikey) {}
		inline Key::Key(const Key &ikey) : user(ikey.user), code(ikey.code) {}

		inline Key::Type Key::type(Code icode) {
			if(icode >= Code::KBEsc && icode <= Code::KBBackslash) {
				return Type::Keyboard;
			}
			if(icode >= Code::MouseHu && icode <= Code::MouseX5) {
				return Type::Mouse;
			}
			if(icode >= Code::XbA && icode <= Code::XbRShoulder) {
				return Type::XController;
			}
			if(icode >= Code::CButton01 && icode <= Code::CPOV4Down) {
				return Type::Controller;
			}
		}

		inline Key::Type Key::type() {
			if(code >= Code::KBEsc && code <= Code::KBBackslash) {
				return Type::Keyboard;
			}
			if(code >= Code::MouseHu && code <= Code::MouseX5) {
				return Type::Mouse;
			}
			if(code >= Code::XbA && code <= Code::XbRShoulder) {
				return Type::XController;
			}
			if(code >= Code::CButton01 && code <= Code::CPOV4Down) {
				return Type::Controller;
			}
		}

		inline base::string Key::str() {
			return "[" + str(user) + " : " + str(type()) + " : " + str(code) + "]";
		}

		inline Key &Key::operator=(const Key &ikey) {
			user = ikey.user;
			code = ikey.code;
			return *this;
		}

		inline bool Key::operator==(const Type itype) {return itype == type();}
		inline bool Key::operator==(const User iuser) {return iuser == user;}
		inline bool Key::operator==(const Code icode) {return icode == code;}
	}  // namespace video
}  // namespace cb
