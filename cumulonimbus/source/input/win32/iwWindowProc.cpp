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
#include <base/Setup.h>
#ifdef CbWindows

#include <win32/input/WindowProc.h>

#include <video/Window.h>

#include <base/Log.h>
#include <base/Exception.h>

#include <input/KeyCode.h>

#include <map>

namespace cb {
	namespace input {
		KeyCode keycode(size_t ivk) {
			static KeyCode table[] = {
				Null, //00
				Null, //01
				Null, //02
				Null, //03
				Null, //04
				Null, //05
				Null, //06
				Null, //07
				KBBackspace, //08
				KBTab, //09
				Null, //0a
				Null, //0b
				KBClear, //0c
				KBEnter, //0d
				Null, //0e
				Null, //0f
				KBLeftShift, //10
				KBLeftCtrl, //11
				KBLeftAlt, //12
				KBBreak, //13
				KBCapsLock, //14
				Null, //15
				Null, //16
				Null, //17
				Null, //18
				Null, //19
				Null, //1a
				KBEsc, //1b
				Null, //1c
				Null, //1d
				Null, //1e
				Null, //1f
				KBSpace, //20
				KBPageUp, //21
				KBPageDown, //22
				KBEnd, //23
				KBHome, //24
				KBLeft, //25
				KBUp, //26
				KBRight, //27
				KBDown, //28
				Null, //29
				Null, //2a
				Null, //2b
				KBPrintScreen, //2c
				KBInsert, //2d
				KBDelete, //2e
				Null, //2f
				KB0, //30
				KB1, //31
				KB2, //32
				KB3, //33
				KB4, //34
				KB5, //35
				KB6, //36
				KB7, //37
				KB8, //38
				KB9, //39
				Null, //3a
				Null, //3b
				Null, //3c
				Null, //3d
				Null, //3e
				Null, //3f
				Null, //40
				KBA, //41
				KBB, //42
				KBC, //43
				KBD, //44
				KBE, //45
				KBF, //46
				KBG, //47
				KBH, //48
				KBI, //49
				KBJ, //4a
				KBK, //4b
				KBL, //4c
				KBM, //4d
				KBN, //4e
				KBO, //4f
				KBP, //50
				KBQ, //51
				KBR, //52
				KBS, //53
				KBT, //54
				KBU, //55
				KBV, //56
				KBW, //57
				KBX, //58
				KBY, //59
				KBZ, //5a
				KBLeftSuper, //5b
				KBRightSuper, //5c
				KBApplication, //5d
				Null, //5e
				KBSleep, //5f
				KBNum0, //60
				KBNum1, //61
				KBNum2, //62
				KBNum3, //63
				KBNum4, //64
				KBNum5, //65
				KBNum6, //66
				KBNum7, //67
				KBNum8, //68
				KBNum9, //69
				KBNumMult, //6a
				KBNumPlus, //6b
				Null, //6c
				KBNumMinus, //6d
				KBNumDel, //6e
				KBNumDiv, //6f
				KBF1, //70
				KBF2, //71
				KBF3, //72
				KBF4, //73
				KBF5, //74
				KBF6, //75
				KBF7, //76
				KBF8, //77
				KBF9, //78
				KBF10, //79
				KBF11, //7a
				KBF12, //7b
				Null, //7c
				Null, //7d
				Null, //7e
				Null, //7f
				Null, //80
				Null, //81
				Null, //82
				Null, //83
				Null, //84
				Null, //85
				Null, //86
				Null, //87
				Null, //88
				Null, //89
				Null, //8a
				Null, //8b
				Null, //8c
				Null, //8d
				Null, //8e
				Null, //8f
				KBNumLock, //90
				KBScrollLock, //91
				Null, //92
				Null, //93
				Null, //94
				Null, //95
				Null, //96
				Null, //97
				Null, //98
				Null, //99
				Null, //9a
				Null, //9b
				Null, //9c
				Null, //9d
				Null, //9e
				Null, //9f
				KBLeftShift, //a0
				KBRightShift, //a1
				KBLeftCtrl, //a2
				KBRightCtrl, //a3
				KBLeftAlt, //a4
				KBRightAlt, //a5
				Null, //a6
				Null, //a7
				Null, //a8
				Null, //a9
				Null, //aa
				Null, //ab
				Null, //ac
				Null, //ad
				Null, //ae
				Null, //af
				Null, //b0
				Null, //b1
				Null, //b2
				Null, //b3
				Null, //b4
				Null, //b5
				Null, //b6
				Null, //b7
				Null, //b8
				Null, //b9
				KBCedille, //ba
				KBEqual, //bb
				KBComma, //bc
				KBMinus, //bd
				KBPeriod, //be
				KBSemicolon, //bf
				KBApostrophe, //c0
				KBSlash, //c1
				KBNumPeriod, //c2
				Null, //c3
				Null, //c4
				Null, //c5
				Null, //c6
				Null, //c7
				Null, //c8
				Null, //c9
				Null, //ca
				Null, //cb
				Null, //cc
				Null, //cd
				Null, //ce
				Null, //cf
				Null, //d0
				Null, //d1
				Null, //d2
				Null, //d3
				Null, //d4
				Null, //d5
				Null, //d6
				Null, //d7
				Null, //d8
				Null, //d9
				Null, //da
				KBAgudo, //db
				KBBracketClose, //dc
				KBBracketOpen, //dd
				KBTil, //de
				Null, //df
				Null, //e0
				Null, //e1
				KBBackslash, //e2
				Null, //e3
				Null, //e4
				Null, //e5
				Null, //e6
				Null, //e7
				Null, //e8
				Null, //e9
				Null, //ea
				Null, //eb
				Null, //ec
				Null, //ed
				Null, //ee
				Null, //ef
				Null, //f0
				Null, //f1
				Null, //f2
				Null, //f3
				Null, //f4
				Null, //f5
				Null, //f6
				Null, //f7
				Null, //f8
				Null, //f9
				Null, //fa
				Null, //fb
				Null, //fc
				Null, //fd
				Null //fe
			};

			return table[ivk];
		}

		size_t virtualkey(KeyCode ikey) {
			switch(ikey) {
			case Null: //07
				return 0x07;

			case KBEsc: //0x1b
				return 0x1b;

			case KBTab: //0x09
				return 0x09;
			case KBEnter: //0x0d
				return 0x0d;
			case KBSpace: //0x20
				return 0x20;
			case KBBackspace: //0x08
				return 0x08;

			case KBPageUp: //0x21
				return 0x21;
			case KBPageDown: //0x22
				return 0x22;
			case KBEnd: //0x23
				return 0x23;
			case KBHome: //0x24
				return 0x24;
			case KBInsert: //0x2d
				return 0x2d;
			case KBDelete: //0x2e
				return 0x2e;
			case KBClear: //0x0c
				return 0x0c;

			case KBPrintScreen: //0x2c
				return 0x2c;
			case KBBreak: //0x13
				return 0x13;
			case KBSleep:
				return 0x5f;
			case KBApplication:
				return 0x5d;

			case KBCapsLock: //0x14
				return 0x14;
			case KBNumLock: //0x90
				return 0x90;
			case KBScrollLock: //0x91
				return 0x91;

			case KBLeft: //0x25
				return 0x25;
			case KBUp: //0x26
				return 0x26;
			case KBRight: //0x27
				return 0x27;
			case KBDown: //0x28
				return 0x28;

			case KB0: //0x30
				return 0x30;
			case KB1: //0x31
				return 0x31;
			case KB2: //0x32
				return 0x32;
			case KB3: //0x33
				return 0x33;
			case KB4: //0x34
				return 0x34;
			case KB5: //0x35
				return 0x35;
			case KB6: //0x36
				return 0x36;
			case KB7: //0x37
				return 0x37;
			case KB8: //0x38
				return 0x38;
			case KB9: //0x39
				return 0x39;

			case KBA: //0x41
				return 0x41;
			case KBB: //0x42
				return 0x42;
			case KBC: //0x43
				return 0x43;
			case KBD: //0x44
				return 0x44;
			case KBE: //0x45
				return 0x45;
			case KBF: //0x46
				return 0x46;
			case KBG: //0x47
				return 0x47;
			case KBH: //0x48
				return 0x48;
			case KBI: //0x49
				return 0x49;
			case KBJ: //0x4a
				return 0x4a;
			case KBK: //0x4b
				return 0x4b;
			case KBL: //0x4c
				return 0x4c;
			case KBM: //0x4d
				return 0x4d;
			case KBN: //0x4e
				return 0x4e;
			case KBO: //0x4f
				return 0x4f;
			case KBP: //0x50
				return 0x50;
			case KBQ: //0x51
				return 0x51;
			case KBR: //0x52
				return 0x52;
			case KBS: //0x53
				return 0x53;
			case KBT: //0x54
				return 0x54;
			case KBU: //0x55
				return 0x55;
			case KBV: //0x56
				return 0x56;
			case KBW: //0x57
				return 0x57;
			case KBX: //0x58
				return 0x58;
			case KBY: //0x59
				return 0x59;
			case KBZ: //0x5a
				return 0x5a;

			case KBNum0: //0x60
				return 0x60;
			case KBNum1: //0x61
				return 0x61;
			case KBNum2: //0x62
				return 0x62;
			case KBNum3: //0x63
				return 0x63;
			case KBNum4: //0x64
				return 0x64;
			case KBNum5: //0x65
				return 0x65;
			case KBNum6: //0x66
				return 0x66;
			case KBNum7: //0x67
				return 0x67;
			case KBNum8: //0x68
				return 0x68;
			case KBNum9: //0x69
				return 0x69;
			case KBNumMult: //0x6a
				return 0x6a;
			case KBNumPlus: //0x6b
				return 0x6b;
			case KBNumMinus: //0x6d
				return 0x6d;
			case KBNumDel: //0x6e
				return 0x6e;
			case KBNumDiv: //0x6f
				return 0x6f;
			case KBNumPeriod: //0xc2
				return 0xc2;

			case KBF1: //0x70
				return 0x70;
			case KBF2: //0x71
				return 0x71;
			case KBF3: //0x72
				return 0x72;
			case KBF4: //0x73
				return 0x73;
			case KBF5: //0x74
				return 0x74;
			case KBF6: //0x75
				return 0x75;
			case KBF7: //0x76
				return 0x76;
			case KBF8: //0x77
				return 0x77;
			case KBF9: //0x78
				return 0x78;
			case KBF10: //0x79
				return 0x79;
			case KBF11: //0x7a
				return 0x7a;
			case KBF12: //0x7b
				return 0x7b;

			case KBLeftShift: //0xa0
				return 0xa0;
			case KBRightShift: //0xa1
				return 0xa1;
			case KBLeftCtrl: //0xa2
				return 0xa2;
			case KBRightCtrl: //0xa3
				return 0xa3;
			case KBLeftAlt: //0xa4
				return 0xa4;
			case KBRightAlt: //0xa5
				return 0xa5;
			case KBLeftSuper:
				return 0x5b;
			case KBRightSuper:
				return 0x5c;

			case KBCedille: //0xba
				return 0xba;
			case KBEqual: //0xbb
				return 0xbb;
			case KBComma: //0xbc
				return 0xbc;
			case KBMinus: //0xbd
				return 0xbd;
			case KBPeriod: //0xbe
				return 0xbe;
			case KBSemicolon: //0xbf
				return 0xbf;
			case KBApostrophe: //0xc0
				return 0xc0;
			case KBAgudo: //0xdb
				return 0xdb;
			case KBBracketClose: //0xdc
				return 0xdc;
			case KBBracketOpen: //0xdd
				return 0xdd;
			case KBTil: //0xde
				return 0xde;
			case KBSlash: //0xc1
				return 0xc1;
			case KBBackslash: //0xe2
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
						translateWin32Text(iwparam, char1, char2);
						window->events().onKeyPress(keycode(iwparam));
						if(char1) {
							window->events().onChar(char1);
							if(char2) {
								window->events().onChar(char2);
							}
						}
					} return 0;
				case WM_KEYUP:
					window->events().onKeyRelease(keycode(iwparam));
					return 0;

				//Eventos relacionados à janela
				case WM_ACTIVATE:
					if(iwparam == WA_INACTIVE) {
						window->events().onActivate();
						base::log.nothing("w32WindowProc() : Mensagem recebida: WM_ACTIVATE. Janela desativada.");
					} else {
						window->events().onDeactivate();
						base::log.nothing("w32WindowProc() : Mensagem recebida: WM_ACTIVATE. Janela ativada.");
					}
					return 0;
				case WM_CLOSE:
					base::log.nothing("w32WindowProc() : Mensagem recebida: WM_CLOSE. Janela fechada.");
					window->events().onClose();
					return 0;
				case WM_SIZE:
					if(LOWORD(ilparam) && HIWORD(ilparam)) {
						window->events().onResize(LOWORD(ilparam), HIWORD(ilparam));
					}
					return 0;

				//Eventos do sistema
				case WM_NCDESTROY:
					base::log.nothing("w32WindowProc() : Mensagem recebida: WM_NCDESTROY. Janela destruida.");
					return 0;

				case WM_LBUTTONDOWN:
					window->cursor().select("hand.click");
					return 0;

				case WM_LBUTTONUP:
					window->cursor().select("hand.point");
					return 0;

				case WM_SETCURSOR:
					if(LOWORD(ilparam) == HTCLIENT) {
						window->cursor().set();
						return TRUE;
					}
				}
			} else {
				switch(imessage) {
				//Mensagens recebidas durante a criação da janela.
				case WM_CREATE:
					base::log.nothing("w32WindowProc() : Mensagem recebida: WM_CREATE.");
					break;
				case WM_NCCREATE:
					base::log.nothing("w32WindowProc() : Mensagem recebida: WM_NCCREATE.");
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

#endif
