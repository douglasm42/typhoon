/* 
 * - Cumulonimbus - ☁
 * File: iKeyCode.cpp
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
#include <cb/input/Key.h>

#include <cb/base/Exception.h>

namespace cb {
	namespace input {
		std::map<base::string, Key::Code> Key::_serialized_to_code;
		std::map<Key::Code, base::string> Key::_code_to_serialized;
		std::map<Key::Code, base::string> Key::_code_to_str;
		std::mutex Key::_map_init;

#		define mapCode(code, code_str) _code_to_str[code] = code_str;	_code_to_serialized[code] = #code;	_serialized_to_code[#code] = code;

		void Key::initConversionMaps() {
			std::lock_guard<std::mutex> lock(_map_init);
			if(!_serialized_to_code.empty()) {
				return;
			}

			mapCode(Null, "Null");

			//Keyboard
			mapCode(KBEsc, "Escape");

			mapCode(KBTab, "Tab");
			mapCode(KBEnter, "Enter");
			mapCode(KBSpace, "Space");
			mapCode(KBBackspace, "Backspace");

			mapCode(KBPageUp, "Page Up");
			mapCode(KBPageDown, "Page Down");
			mapCode(KBEnd, "End");
			mapCode(KBHome, "Home");
			mapCode(KBInsert, "Insert");
			mapCode(KBDelete, "Delete");
			mapCode(KBClear, "Clear");

			mapCode(KBPrintScreen, "Print Screen");
			mapCode(KBBreak, "Pause/Break");
			mapCode(KBSleep, "Sleep");
			mapCode(KBApplication, "Application");

			mapCode(KBCapsLock, "Caps Lock");
			mapCode(KBNumLock, "Num Lock");
			mapCode(KBScrollLock, "Scroll Lock");

			mapCode(KBLeft, "Left");
			mapCode(KBUp, "Up");
			mapCode(KBRight, "Right");
			mapCode(KBDown, "Down");

			mapCode(KB0, "0");
			mapCode(KB1, "1");
			mapCode(KB2, "2");
			mapCode(KB3, "3");
			mapCode(KB4, "4");
			mapCode(KB5, "5");
			mapCode(KB6, "6");
			mapCode(KB7, "7");
			mapCode(KB8, "8");
			mapCode(KB9, "9");

			mapCode(KBA, "A");
			mapCode(KBB, "B");
			mapCode(KBC, "C");
			mapCode(KBD, "D");
			mapCode(KBE, "E");
			mapCode(KBF, "F");
			mapCode(KBG, "G");
			mapCode(KBH, "H");
			mapCode(KBI, "I");
			mapCode(KBJ, "J");
			mapCode(KBK, "K");
			mapCode(KBL, "L");
			mapCode(KBM, "M");
			mapCode(KBN, "N");
			mapCode(KBO, "O");
			mapCode(KBP, "P");
			mapCode(KBQ, "Q");
			mapCode(KBR, "R");
			mapCode(KBS, "S");
			mapCode(KBT, "T");
			mapCode(KBU, "U");
			mapCode(KBV, "V");
			mapCode(KBW, "W");
			mapCode(KBX, "X");
			mapCode(KBY, "Y");
			mapCode(KBZ, "Z");

			mapCode(KBNum0, "Num 0");
			mapCode(KBNum1, "Num 1");
			mapCode(KBNum2, "Num 2");
			mapCode(KBNum3, "Num 3");
			mapCode(KBNum4, "Num 4");
			mapCode(KBNum5, "Num 5");
			mapCode(KBNum6, "Num 6");
			mapCode(KBNum7, "Num 7");
			mapCode(KBNum8, "Num 8");
			mapCode(KBNum9, "Num 9");
			mapCode(KBNumMult, "Num *");
			mapCode(KBNumPlus, "Num +");
			mapCode(KBNumMinus, "Num -");
			mapCode(KBNumDel, "Num Delete");
			mapCode(KBNumDiv, "Num /");
			mapCode(KBNumPeriod, "Num .");

			mapCode(KBF1, "F1");
			mapCode(KBF2, "F2");
			mapCode(KBF3, "F3");
			mapCode(KBF4, "F4");
			mapCode(KBF5, "F5");
			mapCode(KBF6, "F6");
			mapCode(KBF7, "F7");
			mapCode(KBF8, "F8");
			mapCode(KBF9, "F9");
			mapCode(KBF10, "F10");
			mapCode(KBF11, "F11");
			mapCode(KBF12, "F12");

			mapCode(KBLeftShift, "Left Shift");
			mapCode(KBRightShift, "Right Shift");
			mapCode(KBLeftCtrl, "Left Ctrl");
			mapCode(KBRightCtrl, "Right Ctrl");
			mapCode(KBLeftAlt, "Left Alt");
			mapCode(KBRightAlt, "Right Alt");
			mapCode(KBLeftSuper, "Left Super");
			mapCode(KBRightSuper, "Right Super");

			mapCode(KBCedille, "Ç");
			mapCode(KBEqual, "=");
			mapCode(KBComma, ",");
			mapCode(KBMinus, "-");
			mapCode(KBPeriod, ".");
			mapCode(KBSemicolon, ";");
			mapCode(KBApostrophe, "");
			mapCode(KBAgudo, "´");
			mapCode(KBBracketClose, "]");
			mapCode(KBBracketOpen, "[");
			mapCode(KBTil, "~");
			mapCode(KBSlash, "/");
			mapCode(KBBackslash, "\\");

			//Mouse
			mapCode(MouseHu, "H+");
			mapCode(MouseHd, "H-");
			mapCode(MouseVu, "V+");
			mapCode(MouseVd, "V-");
			mapCode(MouseMu, "Scroll+");
			mapCode(MouseMd, "Scroll-");

			mapCode(MouseLeft, "Mouse Left");
			mapCode(MouseRight, "Mouse Right");
			mapCode(MouseMiddle, "Mouse Middle");
			mapCode(MouseX1, "Mouse X1");
			mapCode(MouseX2, "Mouse X2");
			mapCode(MouseX3, "Mouse X3");
			mapCode(MouseX4, "Mouse X4");
			mapCode(MouseX5, "Mouse X5");
			
			//XInput
			mapCode(XbA, "A");
			mapCode(XbB, "B");
			mapCode(XbX, "X");
			mapCode(XbY, "Y");

			mapCode(XbStart, "Start");
			mapCode(XbBack, "Back");

			mapCode(XbLeft, "Left");
			mapCode(XbUp, "Up");
			mapCode(XbRight, "Right");
			mapCode(XbDown, "Down");

			mapCode(XbLThumb, "LThumb");
			mapCode(XbLThumbLeft, "LThumb Left");
			mapCode(XbLThumbUp, "LThumb Up");
			mapCode(XbLThumbRight, "LThumb Right");
			mapCode(XbLThumbDown, "LThumb Down");

			mapCode(XbLThumbUpLeft, "LThumb Up Left");
			mapCode(XbLThumbUpRight, "LThumb Up Right");
			mapCode(XbLThumbDownLeft, "LThumb Down Left");
			mapCode(XbLThumbDownRight, "LThumb Down Right");

			mapCode(XbRThumb, "RThumb");
			mapCode(XbRThumbLeft, "RThumb Left");
			mapCode(XbRThumbUp, "RThumb Up");
			mapCode(XbRThumbRight, "RThumb Right");
			mapCode(XbRThumbDown, "RThumb Down");

			mapCode(XbRThumbUpLeft, "RThumb Up Left");
			mapCode(XbRThumbUpRight, "RThumb Up Right");
			mapCode(XbRThumbDownLeft, "RThumb Down Left");
			mapCode(XbRThumbDownRight, "RThumb Down Right");

			mapCode(XbLTrigger, "LTrigger");
			mapCode(XbLShoulder, "LButton");

			mapCode(XbRTrigger, "RTrigger");
			mapCode(XbRShoulder, "RButton");

			//Controller
			mapCode(CButton01, "Button 1");
			mapCode(CButton02, "Button 2");
			mapCode(CButton03, "Button 3");
			mapCode(CButton04, "Button 4");
			mapCode(CButton05, "Button 5");
			mapCode(CButton06, "Button 6");
			mapCode(CButton07, "Button 7");
			mapCode(CButton08, "Button 8");

			mapCode(CButton09, "Button 9");
			mapCode(CButton10, "Button 10");
			mapCode(CButton11, "Button 11");
			mapCode(CButton12, "Button 12");
			mapCode(CButton13, "Button 13");
			mapCode(CButton14, "Button 14");
			mapCode(CButton15, "Button 15");
			mapCode(CButton16, "Button 16");

			mapCode(CButton17, "Button 17");
			mapCode(CButton18, "Button 18");
			mapCode(CButton19, "Button 19");
			mapCode(CButton20, "Button 20");
			mapCode(CButton21, "Button 21");
			mapCode(CButton22, "Button 22");
			mapCode(CButton23, "Button 23");
			mapCode(CButton24, "Button 24");

			mapCode(CButton25, "Button 25");
			mapCode(CButton26, "Button 26");
			mapCode(CButton27, "Button 27");
			mapCode(CButton28, "Button 28");
			mapCode(CButton29, "Button 29");
			mapCode(CButton30, "Button 30");
			mapCode(CButton31, "Button 31");
			mapCode(CButton32, "Button 32");

			mapCode(CAxisXp, "X+");
			mapCode(CAxisXm, "X-");
			mapCode(CAxisYp, "Y+");
			mapCode(CAxisYm, "Y-");
			mapCode(CAxisZp, "Z+");
			mapCode(CAxisZm, "Z-");

			mapCode(CAxisRXp, "RX+");
			mapCode(CAxisRXm, "RX-");
			mapCode(CAxisRYp, "RY+");
			mapCode(CAxisRYm, "RY-");
			mapCode(CAxisRZp, "RZ+");
			mapCode(CAxisRZm, "RZ-");

			mapCode(CSliderUp, "SliderU+");
			mapCode(CSliderUm, "SliderU-");
			mapCode(CSliderVp, "SliderV+");
			mapCode(CSliderVm, "SliderV-");

			mapCode(CPOV1Left, "Left");
			mapCode(CPOV1Up, "Up");
			mapCode(CPOV1Right, "Right");
			mapCode(CPOV1Down, "Down");

			mapCode(CPOV2Left, "Left2");
			mapCode(CPOV2Up, "Up2");
			mapCode(CPOV2Right, "Right2");
			mapCode(CPOV2Down, "Down2");

			mapCode(CPOV3Left, "Left3");
			mapCode(CPOV3Up, "Up3");
			mapCode(CPOV3Right, "Right3");
			mapCode(CPOV3Down, "Down3");

			mapCode(CPOV4Left, "Left4");
			mapCode(CPOV4Up, "Up4");
			mapCode(CPOV4Right, "Right4");
			mapCode(CPOV4Down, "Down4");
		}

		base::string Key::toStr(Code icode) {
			initConversionMaps();
			std::map<Key::Code, base::string>::iterator it = _code_to_serialized.find(icode);
			if(it != _code_to_serialized.end()) {
				return it->second;
			} else {
				ThrowDet(tokurei::FileSerializeError, "Key code not found.");
			}
		}

		base::string Key::toStr(int iplayer) {
			return std::to_string(iplayer);
		}

		Key::Code Key::toCode(base::string icode) {
			initConversionMaps();
			std::map<base::string, Key::Code>::iterator it = _serialized_to_code.find(icode);
			if(it != _serialized_to_code.end()) {
				return it->second;
			} else {
				ThrowDet(tokurei::FileSerializeError, "Key serialized code not found.");
			}
		}

		int Key::toPlayer(base::string iplayer) {
			return std::stoi(iplayer);
		}

		std::string Key::str(Key::Code ikey) {
			initConversionMaps();
			std::map<Key::Code, base::string>::iterator it = _code_to_str.find(ikey);
			if(it != _code_to_str.end()) {
				return it->second;
			} else {
				return "Unknown";
			}
		}
	}  // namespace input
}  // namespace cb

