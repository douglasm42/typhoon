/* 
 * - Cumulonimbus - ☁
 * File: iwWindows.cpp
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
#include <cb/input/win32/WindowProc.h>

#include <cb/video/Window.h>

#include <cb/base/Log.h>
#include <cb/base/Exception.h>

#include <cb/input/Key.h>

#include <map>

namespace cb {
	namespace input {
		Key keycode(size_t ivk) {
			static Key::Code table[] = {
				Key::Null, //00
				Key::Null, //01
				Key::Null, //02
				Key::Null, //03
				Key::Null, //04
				Key::Null, //05
				Key::Null, //06
				Key::Null, //07
				Key::KBBackspace, //08
				Key::KBTab, //09
				Key::Null, //0a
				Key::Null, //0b
				Key::KBClear, //0c
				Key::KBEnter, //0d
				Key::Null, //0e
				Key::Null, //0f
				Key::KBLeftShift, //10
				Key::KBLeftCtrl, //11
				Key::KBLeftAlt, //12
				Key::KBBreak, //13
				Key::KBCapsLock, //14
				Key::Null, //15
				Key::Null, //16
				Key::Null, //17
				Key::Null, //18
				Key::Null, //19
				Key::Null, //1a
				Key::KBEsc, //1b
				Key::Null, //1c
				Key::Null, //1d
				Key::Null, //1e
				Key::Null, //1f
				Key::KBSpace, //20
				Key::KBPageUp, //21
				Key::KBPageDown, //22
				Key::KBEnd, //23
				Key::KBHome, //24
				Key::KBLeft, //25
				Key::KBUp, //26
				Key::KBRight, //27
				Key::KBDown, //28
				Key::Null, //29
				Key::Null, //2a
				Key::Null, //2b
				Key::KBPrintScreen, //2c
				Key::KBInsert, //2d
				Key::KBDelete, //2e
				Key::Null, //2f
				Key::KB0, //30
				Key::KB1, //31
				Key::KB2, //32
				Key::KB3, //33
				Key::KB4, //34
				Key::KB5, //35
				Key::KB6, //36
				Key::KB7, //37
				Key::KB8, //38
				Key::KB9, //39
				Key::Null, //3a
				Key::Null, //3b
				Key::Null, //3c
				Key::Null, //3d
				Key::Null, //3e
				Key::Null, //3f
				Key::Null, //40
				Key::KBA, //41
				Key::KBB, //42
				Key::KBC, //43
				Key::KBD, //44
				Key::KBE, //45
				Key::KBF, //46
				Key::KBG, //47
				Key::KBH, //48
				Key::KBI, //49
				Key::KBJ, //4a
				Key::KBK, //4b
				Key::KBL, //4c
				Key::KBM, //4d
				Key::KBN, //4e
				Key::KBO, //4f
				Key::KBP, //50
				Key::KBQ, //51
				Key::KBR, //52
				Key::KBS, //53
				Key::KBT, //54
				Key::KBU, //55
				Key::KBV, //56
				Key::KBW, //57
				Key::KBX, //58
				Key::KBY, //59
				Key::KBZ, //5a
				Key::KBLeftSuper, //5b
				Key::KBRightSuper, //5c
				Key::KBApplication, //5d
				Key::Null, //5e
				Key::KBSleep, //5f
				Key::KBNum0, //60
				Key::KBNum1, //61
				Key::KBNum2, //62
				Key::KBNum3, //63
				Key::KBNum4, //64
				Key::KBNum5, //65
				Key::KBNum6, //66
				Key::KBNum7, //67
				Key::KBNum8, //68
				Key::KBNum9, //69
				Key::KBNumMult, //6a
				Key::KBNumPlus, //6b
				Key::Null, //6c
				Key::KBNumMinus, //6d
				Key::KBNumDel, //6e
				Key::KBNumDiv, //6f
				Key::KBF1, //70
				Key::KBF2, //71
				Key::KBF3, //72
				Key::KBF4, //73
				Key::KBF5, //74
				Key::KBF6, //75
				Key::KBF7, //76
				Key::KBF8, //77
				Key::KBF9, //78
				Key::KBF10, //79
				Key::KBF11, //7a
				Key::KBF12, //7b
				Key::Null, //7c
				Key::Null, //7d
				Key::Null, //7e
				Key::Null, //7f
				Key::Null, //80
				Key::Null, //81
				Key::Null, //82
				Key::Null, //83
				Key::Null, //84
				Key::Null, //85
				Key::Null, //86
				Key::Null, //87
				Key::Null, //88
				Key::Null, //89
				Key::Null, //8a
				Key::Null, //8b
				Key::Null, //8c
				Key::Null, //8d
				Key::Null, //8e
				Key::Null, //8f
				Key::KBNumLock, //90
				Key::KBScrollLock, //91
				Key::Null, //92
				Key::Null, //93
				Key::Null, //94
				Key::Null, //95
				Key::Null, //96
				Key::Null, //97
				Key::Null, //98
				Key::Null, //99
				Key::Null, //9a
				Key::Null, //9b
				Key::Null, //9c
				Key::Null, //9d
				Key::Null, //9e
				Key::Null, //9f
				Key::KBLeftShift, //a0
				Key::KBRightShift, //a1
				Key::KBLeftCtrl, //a2
				Key::KBRightCtrl, //a3
				Key::KBLeftAlt, //a4
				Key::KBRightAlt, //a5
				Key::Null, //a6
				Key::Null, //a7
				Key::Null, //a8
				Key::Null, //a9
				Key::Null, //aa
				Key::Null, //ab
				Key::Null, //ac
				Key::Null, //ad
				Key::Null, //ae
				Key::Null, //af
				Key::Null, //b0
				Key::Null, //b1
				Key::Null, //b2
				Key::Null, //b3
				Key::Null, //b4
				Key::Null, //b5
				Key::Null, //b6
				Key::Null, //b7
				Key::Null, //b8
				Key::Null, //b9
				Key::KBCedille, //ba
				Key::KBEqual, //bb
				Key::KBComma, //bc
				Key::KBMinus, //bd
				Key::KBPeriod, //be
				Key::KBSemicolon, //bf
				Key::KBApostrophe, //c0
				Key::KBSlash, //c1
				Key::KBNumPeriod, //c2
				Key::Null, //c3
				Key::Null, //c4
				Key::Null, //c5
				Key::Null, //c6
				Key::Null, //c7
				Key::Null, //c8
				Key::Null, //c9
				Key::Null, //ca
				Key::Null, //cb
				Key::Null, //cc
				Key::Null, //cd
				Key::Null, //ce
				Key::Null, //cf
				Key::Null, //d0
				Key::Null, //d1
				Key::Null, //d2
				Key::Null, //d3
				Key::Null, //d4
				Key::Null, //d5
				Key::Null, //d6
				Key::Null, //d7
				Key::Null, //d8
				Key::Null, //d9
				Key::Null, //da
				Key::KBAgudo, //db
				Key::KBBracketClose, //dc
				Key::KBBracketOpen, //dd
				Key::KBTil, //de
				Key::Null, //df
				Key::Null, //e0
				Key::Null, //e1
				Key::KBBackslash, //e2
				Key::Null, //e3
				Key::Null, //e4
				Key::Null, //e5
				Key::Null, //e6
				Key::Null, //e7
				Key::Null, //e8
				Key::Null, //e9
				Key::Null, //ea
				Key::Null, //eb
				Key::Null, //ec
				Key::Null, //ed
				Key::Null, //ee
				Key::Null, //ef
				Key::Null, //f0
				Key::Null, //f1
				Key::Null, //f2
				Key::Null, //f3
				Key::Null, //f4
				Key::Null, //f5
				Key::Null, //f6
				Key::Null, //f7
				Key::Null, //f8
				Key::Null, //f9
				Key::Null, //fa
				Key::Null, //fb
				Key::Null, //fc
				Key::Null, //fd
				Key::Null //fe
			};

			return Key(table[ivk]);
		}

		size_t virtualkey(Key::Code ikey) {
			switch(ikey) {
			case Key::Null: //07
				return 0x07;

			case Key::KBEsc: //0x1b
				return 0x1b;

			case Key::KBTab: //0x09
				return 0x09;
			case Key::KBEnter: //0x0d
				return 0x0d;
			case Key::KBSpace: //0x20
				return 0x20;
			case Key::KBBackspace: //0x08
				return 0x08;

			case Key::KBPageUp: //0x21
				return 0x21;
			case Key::KBPageDown: //0x22
				return 0x22;
			case Key::KBEnd: //0x23
				return 0x23;
			case Key::KBHome: //0x24
				return 0x24;
			case Key::KBInsert: //0x2d
				return 0x2d;
			case Key::KBDelete: //0x2e
				return 0x2e;
			case Key::KBClear: //0x0c
				return 0x0c;

			case Key::KBPrintScreen: //0x2c
				return 0x2c;
			case Key::KBBreak: //0x13
				return 0x13;
			case Key::KBSleep:
				return 0x5f;
			case Key::KBApplication:
				return 0x5d;

			case Key::KBCapsLock: //0x14
				return 0x14;
			case Key::KBNumLock: //0x90
				return 0x90;
			case Key::KBScrollLock: //0x91
				return 0x91;

			case Key::KBLeft: //0x25
				return 0x25;
			case Key::KBUp: //0x26
				return 0x26;
			case Key::KBRight: //0x27
				return 0x27;
			case Key::KBDown: //0x28
				return 0x28;

			case Key::KB0: //0x30
				return 0x30;
			case Key::KB1: //0x31
				return 0x31;
			case Key::KB2: //0x32
				return 0x32;
			case Key::KB3: //0x33
				return 0x33;
			case Key::KB4: //0x34
				return 0x34;
			case Key::KB5: //0x35
				return 0x35;
			case Key::KB6: //0x36
				return 0x36;
			case Key::KB7: //0x37
				return 0x37;
			case Key::KB8: //0x38
				return 0x38;
			case Key::KB9: //0x39
				return 0x39;

			case Key::KBA: //0x41
				return 0x41;
			case Key::KBB: //0x42
				return 0x42;
			case Key::KBC: //0x43
				return 0x43;
			case Key::KBD: //0x44
				return 0x44;
			case Key::KBE: //0x45
				return 0x45;
			case Key::KBF: //0x46
				return 0x46;
			case Key::KBG: //0x47
				return 0x47;
			case Key::KBH: //0x48
				return 0x48;
			case Key::KBI: //0x49
				return 0x49;
			case Key::KBJ: //0x4a
				return 0x4a;
			case Key::KBK: //0x4b
				return 0x4b;
			case Key::KBL: //0x4c
				return 0x4c;
			case Key::KBM: //0x4d
				return 0x4d;
			case Key::KBN: //0x4e
				return 0x4e;
			case Key::KBO: //0x4f
				return 0x4f;
			case Key::KBP: //0x50
				return 0x50;
			case Key::KBQ: //0x51
				return 0x51;
			case Key::KBR: //0x52
				return 0x52;
			case Key::KBS: //0x53
				return 0x53;
			case Key::KBT: //0x54
				return 0x54;
			case Key::KBU: //0x55
				return 0x55;
			case Key::KBV: //0x56
				return 0x56;
			case Key::KBW: //0x57
				return 0x57;
			case Key::KBX: //0x58
				return 0x58;
			case Key::KBY: //0x59
				return 0x59;
			case Key::KBZ: //0x5a
				return 0x5a;

			case Key::KBNum0: //0x60
				return 0x60;
			case Key::KBNum1: //0x61
				return 0x61;
			case Key::KBNum2: //0x62
				return 0x62;
			case Key::KBNum3: //0x63
				return 0x63;
			case Key::KBNum4: //0x64
				return 0x64;
			case Key::KBNum5: //0x65
				return 0x65;
			case Key::KBNum6: //0x66
				return 0x66;
			case Key::KBNum7: //0x67
				return 0x67;
			case Key::KBNum8: //0x68
				return 0x68;
			case Key::KBNum9: //0x69
				return 0x69;
			case Key::KBNumMult: //0x6a
				return 0x6a;
			case Key::KBNumPlus: //0x6b
				return 0x6b;
			case Key::KBNumMinus: //0x6d
				return 0x6d;
			case Key::KBNumDel: //0x6e
				return 0x6e;
			case Key::KBNumDiv: //0x6f
				return 0x6f;
			case Key::KBNumPeriod: //0xc2
				return 0xc2;

			case Key::KBF1: //0x70
				return 0x70;
			case Key::KBF2: //0x71
				return 0x71;
			case Key::KBF3: //0x72
				return 0x72;
			case Key::KBF4: //0x73
				return 0x73;
			case Key::KBF5: //0x74
				return 0x74;
			case Key::KBF6: //0x75
				return 0x75;
			case Key::KBF7: //0x76
				return 0x76;
			case Key::KBF8: //0x77
				return 0x77;
			case Key::KBF9: //0x78
				return 0x78;
			case Key::KBF10: //0x79
				return 0x79;
			case Key::KBF11: //0x7a
				return 0x7a;
			case Key::KBF12: //0x7b
				return 0x7b;

			case Key::KBLeftShift: //0xa0
				return 0xa0;
			case Key::KBRightShift: //0xa1
				return 0xa1;
			case Key::KBLeftCtrl: //0xa2
				return 0xa2;
			case Key::KBRightCtrl: //0xa3
				return 0xa3;
			case Key::KBLeftAlt: //0xa4
				return 0xa4;
			case Key::KBRightAlt: //0xa5
				return 0xa5;
			case Key::KBLeftSuper:
				return 0x5b;
			case Key::KBRightSuper:
				return 0x5c;

			case Key::KBCedille: //0xba
				return 0xba;
			case Key::KBEqual: //0xbb
				return 0xbb;
			case Key::KBComma: //0xbc
				return 0xbc;
			case Key::KBMinus: //0xbd
				return 0xbd;
			case Key::KBPeriod: //0xbe
				return 0xbe;
			case Key::KBSemicolon: //0xbf
				return 0xbf;
			case Key::KBApostrophe: //0xc0
				return 0xc0;
			case Key::KBAgudo: //0xdb
				return 0xdb;
			case Key::KBBracketClose: //0xdc
				return 0xdc;
			case Key::KBBracketOpen: //0xdd
				return 0xdd;
			case Key::KBTil: //0xde
				return 0xde;
			case Key::KBSlash: //0xc1
				return 0xc1;
			case Key::KBBackslash: //0xe2
				return 0xe2;

			default:
				return 0x07;
			}
		}

		void translateWin32Text(unsigned int ivirtualkey, unsigned int &ochar1, unsigned int &ochar2) {
			//deadkey armazenada para combinação com o próximo caractere.
			static WCHAR dead_key = 0;

			// Alguns códigos de caractere representam apenas parte de um caractere, como um acento.
			// Esses códigos possuem um código de combinação que deve ser mesclado com outro caractere para formar a versão final.
			// Abaixo está o mapa que liga o código do caractere com o seu código de combinação.
			// Os códigos de combinação vai de 0x300 até 0x36F, mas somente 6 foram mapeadas.
			// O link abaixo contém a lista de todos esses caracteres.
			// http://www.fileformat.info/info/unicode/block/combining_diacritical_marks/images.htm
			std::map<unsigned int, unsigned int> deadmap;
			deadmap[0x5E] = 0x302;	// Circumflex accent: ^
			deadmap[0x60] = 0x300;	// Grave accent: `
			deadmap[0x7E] = 0x303;	// Tilde: ~
			deadmap[0xA8] = 0x308;	// Diaeresis: ¨
			deadmap[0xB4] = 0x301;	// Acute accent: ´
			deadmap[0xB8] = 0x327;	// Cedilla: ç

			//Obtém o estado do teclado e o layout do mesmo.
			BYTE keystate[256];
			HKL layout = GetKeyboardLayout(0);

			//Caso não seja possivel obter o estado do teclado então não é possivel obter o caractere.
			if(GetKeyboardState(keystate) == 0) {
				ochar1 = 0;
				ochar2 = 0;
				return;
			}

			//Obtém o scancode da tecla e a tecla virtual a partir do scancode
			int code = MapVirtualKeyEx((UINT) ivirtualkey, MAPVK_VK_TO_VSC_EX, layout);
			ivirtualkey = MapVirtualKeyEx((UINT) code, MAPVK_VSC_TO_VK_EX, layout);

			//Caso a scancode seja 0 então não existe caracteres para retornar.
			if(ivirtualkey == 0) {
				ochar1 = 0;
				ochar2 = 0;
				return;
			}

			//buffer para os caracteres convertidos.
			WCHAR buff[3] = { 0, 0, 0 };

			//Obtém os caracteres gerados pelo scancode e o estado do teclado e os coloca em buff.
			//ascii é a quantidade de caracteres retornados.
			int ascii = ToUnicodeEx(ivirtualkey, (UINT) code, keystate, buff, 3, 0, layout);

			if(ascii == 1 && dead_key) {
				//Apenas um caractere foi retornado e existe uma deadkey para ser combinada.
				//Os dois caracteres são combinados para formar um só.

				//buffer é preenchido com o caractere e a deadkey.
				WCHAR wc_buff[3] = {buff[0], (WCHAR) deadmap[dead_key], '\0'};

				//buffer de saida.
				WCHAR out[3];

				//Os dois caracteres são combinados.
				if(FoldStringW(MAP_PRECOMPOSED, (LPWSTR) wc_buff, 3, (LPWSTR) out, 3)) {

					//Caso o primeiro char seja o espaço então só é retornada a deadkey.
					if(out[0] == ' ') {
						ochar1 = dead_key;
						ochar2 = 0;
						dead_key = 0;
						return;
					}

					//Caso contrario os dois possiveis caracteres são retornados.
					dead_key = 0;
					ochar1 = out[0];
					ochar2 = out[1];
					return;
				}
			} else if(ascii == 1) {
				//Apenas um caractere foi retornado e não existe deadkey para ser retornada.

				//É retornado então o caractere obtido da tecla.
				ochar1 = buff[0];
				ochar2 = 0;
				return;
			} else if(ascii >= 2 || ascii < 0) {
				//Dois ou mais caracteres foram retornados ou nenhum foi retornado.
				//Isso indica que uma deadkey foi retornada.

				//Caso uma deadkey voi retornada na última execução então ela é retornada junto com a que foi retornada na atual.
				//Isso é para quando você faz algo como: ^^, ~~, ou ^~.
				if(dead_key) {
					ochar1 = dead_key;
					ochar2 = buff[0];
					dead_key = 0;
					return;
				}

				//Caso contrario a deadkey é armazenada para combinação com o próximo char.
				if(deadmap.find(buff[0]) != deadmap.end()) {
					dead_key = buff[0];
				}
			}

			//Caso dê tudo errado retorne nada. ^^
			ochar1 = 0;
			ochar2 = 0;
		}

		LRESULT CALLBACK WindowProc(HWND iwindow_handler, UINT imessage, WPARAM iwparam, LPARAM ilparam) {
			video::Window *window = reinterpret_cast<video::Window *>(GetWindowLongPtr(iwindow_handler, GWLP_USERDATA));
			if(window) {
				input::EventHub *eventhub = window->getEventHub();

				switch(imessage) {
				//Eventos de entrada do usuário
				/*case WM_HOTKEY:
					if((int)iwparam == window->_fullscreen_hotkey && window->_active) {
						base::log(base::Nothing, "w32WindowProc() : Mensagem recebida: WM_HOTKEY. Atalho do teclado: fullscreen.");
						window->fullscreen(!window->_fullscreen);
						return 0;
					}
					return 0;*/

				//Eventos relacionados ao teclado
				case WM_KEYDOWN: {
						unsigned int char1;
						unsigned int char2;
						translateWin32Text((unsigned int)iwparam, char1, char2);
						eventhub?(eventhub->onKeyPress(keycode(iwparam))):0;
						if(char1) {
							eventhub?(eventhub->onChar(char1)):0;
							if(char2) {
								eventhub?(eventhub->onChar(char2)):0;
							}
						}
					} return 0;
				case WM_KEYUP:
					eventhub?(eventhub->onKeyRelease(keycode(iwparam))):0;
					return 0;

				//Eventos relacionados à janela
				case WM_ACTIVATE:
					if(iwparam == WA_INACTIVE) {
						eventhub?(eventhub->onDeactivate()):0;
						window->onDeactivate();
						base::log.nothing("w32WindowProc() : Mensagem recebida: WM_ACTIVATE. Janela desativada.");
					} else {
						eventhub?(eventhub->onActivate()):0;
						base::log.nothing("w32WindowProc() : Mensagem recebida: WM_ACTIVATE. Janela ativada.");
						window->onActivate();
					}
					return 0;
				case WM_CLOSE:
					base::log.nothing("w32WindowProc() : Mensagem recebida: WM_CLOSE. Janela fechada.");
					eventhub?(eventhub->onClose()):0;
					window->onClose();
					return 0;
				case WM_SIZE:
					if(LOWORD(ilparam) && HIWORD(ilparam)) {
						base::log.nothing("size: %dx%d", LOWORD(ilparam), HIWORD(ilparam));
						eventhub?(eventhub->onResize(LOWORD(ilparam), HIWORD(ilparam))):0;
						window->onResize(LOWORD(ilparam), HIWORD(ilparam));
					}
					return 0;

				//Eventos do mouse
				case WM_LBUTTONDOWN:
					eventhub?(eventhub->onButtonPress(input::Key(input::Key::MouseLeft), GET_X_LPARAM(ilparam), GET_Y_LPARAM(ilparam))):0;
					return 0;

				case WM_LBUTTONUP:
					eventhub?(eventhub->onButtonRelease(input::Key(input::Key::MouseLeft), GET_X_LPARAM(ilparam), GET_Y_LPARAM(ilparam))):0;
					return 0;

				case WM_RBUTTONDOWN:
					eventhub?(eventhub->onButtonPress(input::Key(input::Key::MouseRight), GET_X_LPARAM(ilparam), GET_Y_LPARAM(ilparam))):0;
					return 0;

				case WM_RBUTTONUP:
					eventhub?(eventhub->onButtonRelease(input::Key(input::Key::MouseRight), GET_X_LPARAM(ilparam), GET_Y_LPARAM(ilparam))):0;
					return 0;

				case WM_MBUTTONDOWN:
					eventhub?(eventhub->onButtonPress(input::Key(input::Key::MouseMiddle), GET_X_LPARAM(ilparam), GET_Y_LPARAM(ilparam))):0;
					return 0;

				case WM_MBUTTONUP:
					eventhub?(eventhub->onButtonRelease(input::Key(input::Key::MouseMiddle), GET_X_LPARAM(ilparam), GET_Y_LPARAM(ilparam))):0;
					return 0;

				case WM_XBUTTONDOWN: {
						if(HIWORD(iwparam) == XBUTTON1) {
							eventhub?(eventhub->onButtonPress(input::Key(input::Key::MouseX1), GET_X_LPARAM(ilparam), GET_Y_LPARAM(ilparam))):0;
						} else if(HIWORD(iwparam) == XBUTTON2) {
							eventhub?(eventhub->onButtonPress(input::Key(input::Key::MouseX2), GET_X_LPARAM(ilparam), GET_Y_LPARAM(ilparam))):0;
						}
						return 0;
					}

				case WM_XBUTTONUP: {
						if(HIWORD(iwparam) == XBUTTON1) {
							eventhub?(eventhub->onButtonRelease(input::Key(input::Key::MouseX1), GET_X_LPARAM(ilparam), GET_Y_LPARAM(ilparam))):0;
						} else if(HIWORD(iwparam) == XBUTTON2) {
							eventhub?(eventhub->onButtonRelease(input::Key(input::Key::MouseX2), GET_X_LPARAM(ilparam), GET_Y_LPARAM(ilparam))):0;
						}
						return 0;
					}

				case WM_MOUSEMOVE:
					eventhub?(eventhub->onMouseMove(GET_X_LPARAM(ilparam), GET_Y_LPARAM(ilparam))):0;
					return 0;

				case WM_MOUSEWHEEL:
					eventhub?(eventhub->onWheelMove(((short)HIWORD(iwparam))/(float)WHEEL_DELTA, 0.0f)):0;
					return 0;

				case WM_MOUSEHWHEEL:
					eventhub?(eventhub->onWheelMove(0.0f, ((short)HIWORD(iwparam))/(float)WHEEL_DELTA)):0;
					return 0;

				//Eventos do sistema
				case WM_NCDESTROY:
					base::log.nothing("w32WindowProc() : Mensagem recebida: WM_NCDESTROY. Janela destruida.");
					return 0;

				case WM_SETCURSOR:
					if(LOWORD(ilparam) == HTCLIENT) {
						video::Cursor::wSet(window->getCursor());
						return TRUE;
					}
				case WM_SETICON: {
						HICON icon = reinterpret_cast<HICON>(DefWindowProc(iwindow_handler,imessage,iwparam,ilparam));
						if(icon) {
							DestroyIcon(icon);
						}
						return 0;
					}
				case WM_NCCALCSIZE: {
						base::log.nothing("w32WindowProc() : Mensagem recebida: WM_NCCALCSIZE. %d", iwparam);
						if(window->getBorder() == video::Border::Empty) {
							if(iwparam == FALSE) {
								return 0;
							} else {
								return WVR_REDRAW;
							}
						} else {
							return DefWindowProc(iwindow_handler,imessage,iwparam,ilparam);
						}
					}
				}

			} else {
				switch(imessage) {
				//Mensagens recebidas durante a criação da janela.
				case WM_CREATE:
					base::log.nothing("w32WindowProc() : Mensagem recebida: WM_CREATE.");
					break;
				case WM_NCCREATE: {
						base::log.nothing("w32WindowProc() : Mensagem recebida: WM_NCCREATE.");
						CREATESTRUCT *createstruct = reinterpret_cast<CREATESTRUCT *>(ilparam);
						SetWindowLongPtr(iwindow_handler, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(createstruct->lpCreateParams));
					}
					break;
				case WM_NCCALCSIZE:
					base::log.nothing("w32WindowProc() : Mensagem recebida: WM_NCCALCSIZE.");
					break;
				case WM_GETMINMAXINFO:
					base::log.nothing("w32WindowProc() : Mensagem recebida: WM_GETMINMAXINFO.");
					break;
				default:
					base::log.nothing("w32WindowProc() : Mensagem inesperada recebida: %d.", imessage);
					break;
				}
			}

			return DefWindowProc(iwindow_handler,imessage,iwparam,ilparam);
		}
	}  // namespace input
}  // namespace cb
