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
#include <input/Key.h>

namespace cb {
	namespace input {
		std::string Key::str(Key::Type itype) {
			switch(itype) {
			case Type::Keyboard:
				return "Keyboard";
			case Type::Mouse:
				return "Mouse";
			case Type::XController:
				return "XBox";
			case Type::Controller:
				return "Controller";
			}
		}
		
		std::string Key::str(Key::User iuser) {
			switch(iuser) {
			case User::Player0:
				return "Player 0";
			case User::Player1:
				return "Player 1";
			case User::Player2:
				return "Player 2";
			case User::Player3:
				return "Player 3";
			case User::Player4:
				return "Player 4";
			case User::Player5:
				return "Player 5";
			case User::Player6:
				return "Player 6";
			case User::Player7:
				return "Player 7";
			case User::Player8:
				return "Player 8";
			}
		}

		std::string Key::str(Key::Code ikey) {
			switch(ikey) {
			case Code::Null:
				return "Null";

			//Keyboard
			case Code::KBEsc:
				return "Escape";

			case Code::KBTab:
				return "Tab";
			case Code::KBEnter:
				return "Enter";
			case Code::KBSpace:
				return "Space";
			case Code::KBBackspace:
				return "Backspace";

			case Code::KBPageUp:
				return "Page Up";
			case Code::KBPageDown:
				return "Page Down";
			case Code::KBEnd:
				return "End";
			case Code::KBHome:
				return "Home";
			case Code::KBInsert:
				return "Insert";
			case Code::KBDelete:
				return "Delete";
			case Code::KBClear:
				return "Clear";

			case Code::KBPrintScreen:
				return "Print Screen";
			case Code::KBBreak:
				return "Pause/Break";
			case Code::KBSleep:
				return "Sleep";
			case Code::KBApplication:
				return "Application";

			case Code::KBCapsLock:
				return "Caps Lock";
			case Code::KBNumLock:
				return "Num Lock";
			case Code::KBScrollLock:
				return "Scroll Lock";

			case Code::KBLeft:
				return "Left";
			case Code::KBUp:
				return "Up";
			case Code::KBRight:
				return "Right";
			case Code::KBDown:
				return "Down";

			case Code::KB0:
				return "0";
			case Code::KB1:
				return "1";
			case Code::KB2:
				return "2";
			case Code::KB3:
				return "3";
			case Code::KB4:
				return "4";
			case Code::KB5:
				return "5";
			case Code::KB6:
				return "6";
			case Code::KB7:
				return "7";
			case Code::KB8:
				return "8";
			case Code::KB9:
				return "9";

			case Code::KBA:
				return "A";
			case Code::KBB:
				return "B";
			case Code::KBC:
				return "C";
			case Code::KBD:
				return "D";
			case Code::KBE:
				return "E";
			case Code::KBF:
				return "F";
			case Code::KBG:
				return "G";
			case Code::KBH:
				return "H";
			case Code::KBI:
				return "I";
			case Code::KBJ:
				return "J";
			case Code::KBK:
				return "K";
			case Code::KBL:
				return "L";
			case Code::KBM:
				return "M";
			case Code::KBN:
				return "N";
			case Code::KBO:
				return "O";
			case Code::KBP:
				return "P";
			case Code::KBQ:
				return "Q";
			case Code::KBR:
				return "R";
			case Code::KBS:
				return "S";
			case Code::KBT:
				return "T";
			case Code::KBU:
				return "U";
			case Code::KBV:
				return "V";
			case Code::KBW:
				return "W";
			case Code::KBX:
				return "X";
			case Code::KBY:
				return "Y";
			case Code::KBZ:
				return "Z";

			case Code::KBNum0:
				return "Num 0";
			case Code::KBNum1:
				return "Num 1";
			case Code::KBNum2:
				return "Num 2";
			case Code::KBNum3:
				return "Num 3";
			case Code::KBNum4:
				return "Num 4";
			case Code::KBNum5:
				return "Num 5";
			case Code::KBNum6:
				return "Num 6";
			case Code::KBNum7:
				return "Num 7";
			case Code::KBNum8:
				return "Num 8";
			case Code::KBNum9:
				return "Num 9";
			case Code::KBNumMult:
				return "Num *";
			case Code::KBNumPlus:
				return "Num +";
			case Code::KBNumMinus:
				return "Num -";
			case Code::KBNumDel:
				return "Num Delete";
			case Code::KBNumDiv:
				return "Num /";
			case Code::KBNumPeriod:
				return "Num .";

			case Code::KBF1:
				return "F1";
			case Code::KBF2:
				return "F2";
			case Code::KBF3:
				return "F3";
			case Code::KBF4:
				return "F4";
			case Code::KBF5:
				return "F5";
			case Code::KBF6:
				return "F6";
			case Code::KBF7:
				return "F7";
			case Code::KBF8:
				return "F8";
			case Code::KBF9:
				return "F9";
			case Code::KBF10:
				return "F10";
			case Code::KBF11:
				return "F11";
			case Code::KBF12:
				return "F12";

			case Code::KBLeftShift:
				return "Left Shift";
			case Code::KBRightShift:
				return "Right Shift";
			case Code::KBLeftCtrl:
				return "Left Ctrl";
			case Code::KBRightCtrl:
				return "Right Ctrl";
			case Code::KBLeftAlt:
				return "Left Alt";
			case Code::KBRightAlt:
				return "Right Alt";
			case Code::KBLeftSuper:
				return "Left Super";
			case Code::KBRightSuper:
				return "Right Super";

			case Code::KBCedille:
				return "Ç";
			case Code::KBEqual:
				return "=";
			case Code::KBComma:
				return ",";
			case Code::KBMinus:
				return "-";
			case Code::KBPeriod:
				return ".";
			case Code::KBSemicolon:
				return ";";
			case Code::KBApostrophe:
				return "";
			case Code::KBAgudo:
				return "´";
			case Code::KBBracketClose:
				return "]";
			case Code::KBBracketOpen:
				return "[";
			case Code::KBTil:
				return "~";
			case Code::KBSlash:
				return "/";
			case Code::KBBackslash:
				return "\\";

			//Mouse
			case Code::MouseHu:
				return "H+";
			case Code::MouseHd:
				return "H-";
			case Code::MouseVu:
				return "V+";
			case Code::MouseVd:
				return "V-";
			case Code::MouseMu:
				return "Scroll+";
			case Code::MouseMd:
				return "Scroll-";

			case Code::MouseLeft:
				return "Left";
			case Code::MouseRight:
				return "Right";
			case Code::MouseMiddle:
				return "Middle";
			case Code::MouseX1:
				return "X1";
			case Code::MouseX2:
				return "X2";
			case Code::MouseX3:
				return "X3";
			case Code::MouseX4:
				return "X4";
			case Code::MouseX5:
				return "X5";
			
			//XInput
			case Code::XbA:
				return "A";
			case Code::XbB:
				return "B";
			case Code::XbX:
				return "X";
			case Code::XbY:
				return "Y";

			case Code::XbStart:
				return "Start";
			case Code::XbBack:
				return "Back";

			case Code::XbLeft:
				return "Left";
			case Code::XbUp:
				return "Up";
			case Code::XbRight:
				return "Right";
			case Code::XbDown:
				return "Down";

			case Code::XbLThumb:
				return "LThumb";
			case Code::XbLThumbLeft:
				return "LThumb Left";
			case Code::XbLThumbUp:
				return "LThumb Up";
			case Code::XbLThumbRight:
				return "LThumb Right";
			case Code::XbLThumbDown:
				return "LThumb Down";

			case Code::XbLThumbUpLeft:
				return "LThumb Up Left";
			case Code::XbLThumbUpRight:
				return "LThumb Up Right";
			case Code::XbLThumbDownLeft:
				return "LThumb Down Left";
			case Code::XbLThumbDownRight:
				return "LThumb Down Right";

			case Code::XbRThumb:
				return "RThumb";
			case Code::XbRThumbLeft:
				return "RThumb Left";
			case Code::XbRThumbUp:
				return "RThumb Up";
			case Code::XbRThumbRight:
				return "RThumb Right";
			case Code::XbRThumbDown:
				return "RThumb Down";

			case Code::XbRThumbUpLeft:
				return "RThumb Up Left";
			case Code::XbRThumbUpRight:
				return "RThumb Up Right";
			case Code::XbRThumbDownLeft:
				return "RThumb Down Left";
			case Code::XbRThumbDownRight:
				return "RThumb Down Right";

			case Code::XbLTrigger:
				return "LTrigger";
			case Code::XbLShoulder:
				return "LButton";

			case Code::XbRTrigger:
				return "RTrigger";
			case Code::XbRShoulder:
				return "RButton";

			//Controller
			case Code::CButton01:
				return "Button 1";
			case Code::CButton02:
				return "Button 2";
			case Code::CButton03:
				return "Button 3";
			case Code::CButton04:
				return "Button 4";
			case Code::CButton05:
				return "Button 5";
			case Code::CButton06:
				return "Button 6";
			case Code::CButton07:
				return "Button 7";
			case Code::CButton08:
				return "Button 8";

			case Code::CButton09:
				return "Button 9";
			case Code::CButton10:
				return "Button 10";
			case Code::CButton11:
				return "Button 11";
			case Code::CButton12:
				return "Button 12";
			case Code::CButton13:
				return "Button 13";
			case Code::CButton14:
				return "Button 14";
			case Code::CButton15:
				return "Button 15";
			case Code::CButton16:
				return "Button 16";

			case Code::CButton17:
				return "Button 17";
			case Code::CButton18:
				return "Button 18";
			case Code::CButton19:
				return "Button 19";
			case Code::CButton20:
				return "Button 20";
			case Code::CButton21:
				return "Button 21";
			case Code::CButton22:
				return "Button 22";
			case Code::CButton23:
				return "Button 23";
			case Code::CButton24:
				return "Button 24";

			case Code::CButton25:
				return "Button 25";
			case Code::CButton26:
				return "Button 26";
			case Code::CButton27:
				return "Button 27";
			case Code::CButton28:
				return "Button 28";
			case Code::CButton29:
				return "Button 29";
			case Code::CButton30:
				return "Button 30";
			case Code::CButton31:
				return "Button 31";
			case Code::CButton32:
				return "Button 32";

			case Code::CAxisXp:
				return "X+";
			case Code::CAxisXm:
				return "X-";
			case Code::CAxisYp:
				return "Y+";
			case Code::CAxisYm:
				return "Y-";
			case Code::CAxisZp:
				return "Z+";
			case Code::CAxisZm:
				return "Z-";

			case Code::CAxisRXp:
				return "RX+";
			case Code::CAxisRXm:
				return "RX-";
			case Code::CAxisRYp:
				return "RY+";
			case Code::CAxisRYm:
				return "RY-";
			case Code::CAxisRZp:
				return "RZ+";
			case Code::CAxisRZm:
				return "RZ-";

			case Code::CSliderUp:
				return "SliderU+";
			case Code::CSliderUm:
				return "SliderU-";
			case Code::CSliderVp:
				return "SliderV+";
			case Code::CSliderVm:
				return "SliderV-";

			case Code::CPOV1Left:
				return "Left";
			case Code::CPOV1Up:
				return "Up";
			case Code::CPOV1Right:
				return "Right";
			case Code::CPOV1Down:
				return "Down";

			case Code::CPOV2Left:
				return "Left2";
			case Code::CPOV2Up:
				return "Up2";
			case Code::CPOV2Right:
				return "Right2";
			case Code::CPOV2Down:
				return "Down2";

			case Code::CPOV3Left:
				return "Left3";
			case Code::CPOV3Up:
				return "Up3";
			case Code::CPOV3Right:
				return "Right3";
			case Code::CPOV3Down:
				return "Down3";

			case Code::CPOV4Left:
				return "Left4";
			case Code::CPOV4Up:
				return "Up4";
			case Code::CPOV4Right:
				return "Right4";
			case Code::CPOV4Down:
				return "Down4";
				
			default:
				return "Unknown";
			}
		}
	}  // namespace input
}  // namespace cb

