/* 
 * - Cumulonimbus - ☁
 * File: KeyCode.h
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

namespace cb {
	namespace input {
		typedef enum KeyCodeType {
			KeyCodeTypeMask	= 0xFF00000,

			Keyboard		= 0x0100000,
			Mouse			= 0x0200000,
			XBoxController	= 0x0300000,
			Controller		= 0x0400000
		} KeyCodeType;

		typedef enum ControllerID {
			ControllerIDMask	= 0xFF000,
			Controller1			= 0x00000,
			Controller2			= 0x01000,
			Controller3			= 0x02000,
			Controller4			= 0x03000,
			Controller5			= 0x04000,
			Controller6			= 0x05000,
			Controller7			= 0x06000,
			Controller8			= 0x07000
		} ControllerID;

		/**
		 * Códigos de teclas virtuais. Cada tecla do teclado possui uma representação nessa lista, assim como o
		 * mouse e qualquer outro dispositivo de entrada.
		 */
		typedef enum KeyCode {
			Null = 0,         //!< Tecla nula.

			//Teclado
			KBEsc = Keyboard,  //!< Escape;

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
			MouseHu = Mouse,//!< Eixo positivo horizontal do mouse;
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
			XbA = XBoxController,
			XbB,
			XbX,
			XbY,

			XbStart,
			XbBack,

			XbLeft,
			XbUp,
			XbRight,
			XbDown,

			XbLThumbLeft,
			XbLThumbUp,
			XbLThumbRight,
			XbLThumbDown,

			XbRThumbLeft,
			XbRThumbUp,
			XbRThumbRight,
			XbRThumbDown,

			XbLTrigger,
			XbLB,

			XbRTrigger,
			XbRB,

			//XBox Controller 1
			Xb1A = XBoxController | Controller1,
			Xb1B,
			Xb1X,
			Xb1Y,

			Xb1Start,
			Xb1Back,

			Xb1Left,
			Xb1Up,
			Xb1Right,
			Xb1Down,

			Xb1LThumbLeft,
			Xb1LThumbUp,
			Xb1LThumbRight,
			Xb1LThumbDown,

			Xb1RThumbLeft,
			Xb1RThumbUp,
			Xb1RThumbRight,
			Xb1RThumbDown,

			Xb1LTrigger,
			Xb1LB,

			Xb1RTrigger,
			Xb1RB,

			//XBox Controller 2
			Xb2A = 0x301000,
			Xb2B,
			Xb2X,
			Xb2Y,

			Xb2Start,
			Xb2Back,

			Xb2Left,
			Xb2Up,
			Xb2Right,
			Xb2Down,

			Xb2LThumbLeft,
			Xb2LThumbUp,
			Xb2LThumbRight,
			Xb2LThumbDown,

			Xb2RThumbLeft,
			Xb2RThumbUp,
			Xb2RThumbRight,
			Xb2RThumbDown,

			Xb2LTrigger,
			Xb2LB,

			Xb2RTrigger,
			Xb2RB,

			//XBox Controller 3
			Xb3A = XBoxController | Controller3,
			Xb3B,
			Xb3X,
			Xb3Y,

			Xb3Start,
			Xb3Back,

			Xb3Left,
			Xb3Up,
			Xb3Right,
			Xb3Down,

			Xb3LThumbLeft,
			Xb3LThumbUp,
			Xb3LThumbRight,
			Xb3LThumbDown,

			Xb3RThumbLeft,
			Xb3RThumbUp,
			Xb3RThumbRight,
			Xb3RThumbDown,

			Xb3LTrigger,
			Xb3LB,

			Xb3RTrigger,
			Xb3RB,

			//XBox Controller 4
			Xb4A = XBoxController | Controller4,
			Xb4B,
			Xb4X,
			Xb4Y,

			Xb4Start,
			Xb4Back,

			Xb4Left,
			Xb4Up,
			Xb4Right,
			Xb4Down,

			Xb4LThumbLeft,
			Xb4LThumbUp,
			Xb4LThumbRight,
			Xb4LThumbDown,

			Xb4RThumbLeft,
			Xb4RThumbUp,
			Xb4RThumbRight,
			Xb4RThumbDown,

			Xb4LTrigger,
			Xb4LB,

			Xb4RTrigger,
			Xb4RB,

			//Controller
			CButton01 = Controller,
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

			//Controller 1
			C1Button01 = Controller | Controller1,
			C1Button02,
			C1Button03,
			C1Button04,
			C1Button05,
			C1Button06,
			C1Button07,
			C1Button08,

			C1Button09,
			C1Button10,
			C1Button11,
			C1Button12,
			C1Button13,
			C1Button14,
			C1Button15,
			C1Button16,

			C1Button17,
			C1Button18,
			C1Button19,
			C1Button20,
			C1Button21,
			C1Button22,
			C1Button23,
			C1Button24,

			C1Button25,
			C1Button26,
			C1Button27,
			C1Button28,
			C1Button29,
			C1Button30,
			C1Button31,
			C1Button32,

			C1AxisXp,
			C1AxisXm,
			C1AxisYp,
			C1AxisYm,
			C1AxisZp,
			C1AxisZm,

			C1AxisRXp,
			C1AxisRXm,
			C1AxisRYp,
			C1AxisRYm,
			C1AxisRZp,
			C1AxisRZm,

			C1SliderUp,
			C1SliderUm,
			C1SliderVp,
			C1SliderVm,

			C1POV1Left,
			C1POV1Up,
			C1POV1Right,
			C1POV1Down,

			C1POV2Left,
			C1POV2Up,
			C1POV2Right,
			C1POV2Down,

			C1POV3Left,
			C1POV3Up,
			C1POV3Right,
			C1POV3Down,

			C1POV4Left,
			C1POV4Up,
			C1POV4Right,
			C1POV4Down,

			//Controller 2
			C2Button01 = Controller | Controller2,
			C2Button02,
			C2Button03,
			C2Button04,
			C2Button05,
			C2Button06,
			C2Button07,
			C2Button08,

			C2Button09,
			C2Button10,
			C2Button11,
			C2Button12,
			C2Button13,
			C2Button14,
			C2Button15,
			C2Button16,

			C2Button17,
			C2Button18,
			C2Button19,
			C2Button20,
			C2Button21,
			C2Button22,
			C2Button23,
			C2Button24,

			C2Button25,
			C2Button26,
			C2Button27,
			C2Button28,
			C2Button29,
			C2Button30,
			C2Button31,
			C2Button32,

			C2AxisXp,
			C2AxisXm,
			C2AxisYp,
			C2AxisYm,
			C2AxisZp,
			C2AxisZm,

			C2AxisRXp,
			C2AxisRXm,
			C2AxisRYp,
			C2AxisRYm,
			C2AxisRZp,
			C2AxisRZm,

			C2SliderUp,
			C2SliderUm,
			C2SliderVp,
			C2SliderVm,

			C2POV1Left,
			C2POV1Up,
			C2POV1Right,
			C2POV1Down,

			C2POV2Left,
			C2POV2Up,
			C2POV2Right,
			C2POV2Down,

			C2POV3Left,
			C2POV3Up,
			C2POV3Right,
			C2POV3Down,

			C2POV4Left,
			C2POV4Up,
			C2POV4Right,
			C2POV4Down,

			//Controller 3
			C3Button01 = Controller | Controller3,
			C3Button02,
			C3Button03,
			C3Button04,
			C3Button05,
			C3Button06,
			C3Button07,
			C3Button08,

			C3Button09,
			C3Button10,
			C3Button11,
			C3Button12,
			C3Button13,
			C3Button14,
			C3Button15,
			C3Button16,

			C3Button17,
			C3Button18,
			C3Button19,
			C3Button20,
			C3Button21,
			C3Button22,
			C3Button23,
			C3Button24,

			C3Button25,
			C3Button26,
			C3Button27,
			C3Button28,
			C3Button29,
			C3Button30,
			C3Button31,
			C3Button32,

			C3AxisXp,
			C3AxisXm,
			C3AxisYp,
			C3AxisYm,
			C3AxisZp,
			C3AxisZm,

			C3AxisRXp,
			C3AxisRXm,
			C3AxisRYp,
			C3AxisRYm,
			C3AxisRZp,
			C3AxisRZm,

			C3SliderUp,
			C3SliderUm,
			C3SliderVp,
			C3SliderVm,

			C3POV1Left,
			C3POV1Up,
			C3POV1Right,
			C3POV1Down,

			C3POV2Left,
			C3POV2Up,
			C3POV2Right,
			C3POV2Down,

			C3POV3Left,
			C3POV3Up,
			C3POV3Right,
			C3POV3Down,

			C3POV4Left,
			C3POV4Up,
			C3POV4Right,
			C3POV4Down,

			//Controller 4
			C4Button01 = Controller | Controller4,
			C4Button02,
			C4Button03,
			C4Button04,
			C4Button05,
			C4Button06,
			C4Button07,
			C4Button08,

			C4Button09,
			C4Button10,
			C4Button11,
			C4Button12,
			C4Button13,
			C4Button14,
			C4Button15,
			C4Button16,

			C4Button17,
			C4Button18,
			C4Button19,
			C4Button20,
			C4Button21,
			C4Button22,
			C4Button23,
			C4Button24,

			C4Button25,
			C4Button26,
			C4Button27,
			C4Button28,
			C4Button29,
			C4Button30,
			C4Button31,
			C4Button32,

			C4AxisXp,
			C4AxisXm,
			C4AxisYp,
			C4AxisYm,
			C4AxisZp,
			C4AxisZm,

			C4AxisRXp,
			C4AxisRXm,
			C4AxisRYp,
			C4AxisRYm,
			C4AxisRZp,
			C4AxisRZm,

			C4SliderUp,
			C4SliderUm,
			C4SliderVp,
			C4SliderVm,

			C4POV1Left,
			C4POV1Up,
			C4POV1Right,
			C4POV1Down,

			C4POV2Left,
			C4POV2Up,
			C4POV2Right,
			C4POV2Down,

			C4POV3Left,
			C4POV3Up,
			C4POV3Right,
			C4POV3Down,

			C4POV4Left,
			C4POV4Up,
			C4POV4Right,
			C4POV4Down,
		} KeyCode;

		inline KeyCodeType CbAPI type(KeyCode ikey) {
			return (KeyCodeType)(ikey & KeyCodeTypeMask);
		}

		inline ControllerID CbAPI controllerid(KeyCode ikey) {
			return (ControllerID)(ikey & ControllerIDMask);
		}

		base::string CbAPI keyname(KeyCode ikey);
	}  // namespace video
}  // namespace cb
