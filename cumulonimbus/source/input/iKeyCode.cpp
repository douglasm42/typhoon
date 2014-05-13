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
#include <input/KeyCode.h>

namespace cb {
	namespace input {
		std::string keyname(KeyCode ikey) {
			switch(ikey) {
			case Null:
				return "Null";

			//Keyboard
			case KBEsc:
				return "Escape";

			case KBTab:
				return "Tab";
			case KBEnter:
				return "Enter";
			case KBSpace:
				return "Space";
			case KBBackspace:
				return "Backspace";

			case KBPageUp:
				return "Page Up";
			case KBPageDown:
				return "Page Down";
			case KBEnd:
				return "End";
			case KBHome:
				return "Home";
			case KBInsert:
				return "Insert";
			case KBDelete:
				return "Delete";
			case KBClear:
				return "Clear";

			case KBPrintScreen:
				return "Print Screen";
			case KBBreak:
				return "Pause/Break";
			case KBSleep:
				return "Sleep";
			case KBApplication:
				return "Application";

			case KBCapsLock:
				return "Caps Lock";
			case KBNumLock:
				return "Num Lock";
			case KBScrollLock:
				return "Scroll Lock";

			case KBLeft:
				return "Left";
			case KBUp:
				return "Up";
			case KBRight:
				return "Right";
			case KBDown:
				return "Down";

			case KB0:
				return "0";
			case KB1:
				return "1";
			case KB2:
				return "2";
			case KB3:
				return "3";
			case KB4:
				return "4";
			case KB5:
				return "5";
			case KB6:
				return "6";
			case KB7:
				return "7";
			case KB8:
				return "8";
			case KB9:
				return "9";

			case KBA:
				return "A";
			case KBB:
				return "B";
			case KBC:
				return "C";
			case KBD:
				return "D";
			case KBE:
				return "E";
			case KBF:
				return "F";
			case KBG:
				return "G";
			case KBH:
				return "H";
			case KBI:
				return "I";
			case KBJ:
				return "J";
			case KBK:
				return "K";
			case KBL:
				return "L";
			case KBM:
				return "M";
			case KBN:
				return "N";
			case KBO:
				return "O";
			case KBP:
				return "P";
			case KBQ:
				return "Q";
			case KBR:
				return "R";
			case KBS:
				return "S";
			case KBT:
				return "T";
			case KBU:
				return "U";
			case KBV:
				return "V";
			case KBW:
				return "W";
			case KBX:
				return "X";
			case KBY:
				return "Y";
			case KBZ:
				return "Z";

			case KBNum0:
				return "Num 0";
			case KBNum1:
				return "Num 1";
			case KBNum2:
				return "Num 2";
			case KBNum3:
				return "Num 3";
			case KBNum4:
				return "Num 4";
			case KBNum5:
				return "Num 5";
			case KBNum6:
				return "Num 6";
			case KBNum7:
				return "Num 7";
			case KBNum8:
				return "Num 8";
			case KBNum9:
				return "Num 9";
			case KBNumMult:
				return "Num *";
			case KBNumPlus:
				return "Num +";
			case KBNumMinus:
				return "Num -";
			case KBNumDel:
				return "Num Delete";
			case KBNumDiv:
				return "Num /";
			case KBNumPeriod:
				return "Num .";

			case KBF1:
				return "F1";
			case KBF2:
				return "F2";
			case KBF3:
				return "F3";
			case KBF4:
				return "F4";
			case KBF5:
				return "F5";
			case KBF6:
				return "F6";
			case KBF7:
				return "F7";
			case KBF8:
				return "F8";
			case KBF9:
				return "F9";
			case KBF10:
				return "F10";
			case KBF11:
				return "F11";
			case KBF12:
				return "F12";

			case KBLeftShift:
				return "Left Shift";
			case KBRightShift:
				return "Right Shift";
			case KBLeftCtrl:
				return "Left Ctrl";
			case KBRightCtrl:
				return "Right Ctrl";
			case KBLeftAlt:
				return "Left Alt";
			case KBRightAlt:
				return "Right Alt";
			case KBLeftSuper:
				return "Left Super";
			case KBRightSuper:
				return "Right Super";

			case KBCedille:
				return "Ç";
			case KBEqual:
				return "=";
			case KBComma:
				return ",";
			case KBMinus:
				return "-";
			case KBPeriod:
				return ".";
			case KBSemicolon:
				return ";";
			case KBApostrophe:
				return "";
			case KBAgudo:
				return "´";
			case KBBracketClose:
				return "]";
			case KBBracketOpen:
				return "[";
			case KBTil:
				return "~";
			case KBSlash:
				return "/";
			case KBBackslash:
				return "\\";

			//Mouse
			case MouseHu:
				return "Mouse H+";
			case MouseHd:
				return "Mouse H-";
			case MouseVu:
				return "Mouse V+";
			case MouseVd:
				return "Mouse V-";
			case MouseMu:
				return "Mouse Scroll+";
			case MouseMd:
				return "Mouse Scroll-";

			case MouseLeft:
				return "Mouse Left";
			case MouseRight:
				return "Mouse Right";
			case MouseMiddle:
				return "Mouse Middle";
			case MouseX1:
				return "Mouse X1";
			case MouseX2:
				return "Mouse X2";
			case MouseX3:
				return "Mouse X3";
			case MouseX4:
				return "Mouse X4";
			case MouseX5:
				return "Mouse X5";
			}

			std::string name;
			if(type(ikey) == XBoxController) {
				switch(ikey - controllerid(ikey)) {
				case XbA:
					name = "XBox# A";
					break;
				case XbB:
					name = "XBox# B";
					break;
				case XbX:
					name = "XBox# X";
					break;
				case XbY:
					name = "XBox# Y";
					break;

				case XbStart:
					name = "XBox# Start";
					break;
				case XbBack:
					name = "XBox# Back";
					break;

				case XbLeft:
					name = "XBox# Left";
					break;
				case XbUp:
					name = "XBox# Up";
					break;
				case XbRight:
					name = "XBox# Right";
					break;
				case XbDown:
					name = "XBox# Down";
					break;

				case XbLThumbLeft:
					name = "XBox# LThumb Left";
					break;
				case XbLThumbUp:
					name = "XBox# LThumb Up";
					break;
				case XbLThumbRight:
					name = "XBox# LThumb Right";
					break;
				case XbLThumbDown:
					name = "XBox# LThumb Down";
					break;

				case XbRThumbLeft:
					name = "XBox# RThumb Left";
					break;
				case XbRThumbUp:
					name = "XBox# RThumb Up";
					break;
				case XbRThumbRight:
					name = "XBox# RThumb Right";
					break;
				case XbRThumbDown:
					name = "XBox# RThumb Down";
					break;

				case XbLTrigger:
					name = "XBox# LTrigger";
					break;
				case XbLB:
					name = "XBox# LButton";
					break;

				case XbRTrigger:
					name = "XBox# RTrigger";
					break;
				case XbRB:
					name = "XBox# RButton";
					break;
				}

				switch(controllerid(ikey)) {
				case Controller1:
					name[4] = '1';
					return name;
				case Controller2:
					name[4] = '2';
					return name;
				case Controller3:
					name[4] = '3';
					return name;
				case Controller4:
					name[4] = '4';
					return name;
				}
			} else if(type(ikey) == Controller) {
				switch(ikey - controllerid(ikey)) {
				case CButton01:
					name = "P# Button 1";
					break;
				case CButton02:
					name = "P# Button 2";
					break;
				case CButton03:
					name = "P# Button 3";
					break;
				case CButton04:
					name = "P# Button 4";
					break;
				case CButton05:
					name = "P# Button 5";
					break;
				case CButton06:
					name = "P# Button 6";
					break;
				case CButton07:
					name = "P# Button 7";
					break;
				case CButton08:
					name = "P# Button 8";
					break;

				case CButton09:
					name = "P# Button 9";
					break;
				case CButton10:
					name = "P# Button 10";
					break;
				case CButton11:
					name = "P# Button 11";
					break;
				case CButton12:
					name = "P# Button 12";
					break;
				case CButton13:
					name = "P# Button 13";
					break;
				case CButton14:
					name = "P# Button 14";
					break;
				case CButton15:
					name = "P# Button 15";
					break;
				case CButton16:
					name = "P# Button 16";
					break;

				case CButton17:
					name = "P# Button 17";
					break;
				case CButton18:
					name = "P# Button 18";
					break;
				case CButton19:
					name = "P# Button 19";
					break;
				case CButton20:
					name = "P# Button 20";
					break;
				case CButton21:
					name = "P# Button 21";
					break;
				case CButton22:
					name = "P# Button 22";
					break;
				case CButton23:
					name = "P# Button 23";
					break;
				case CButton24:
					name = "P# Button 24";
					break;

				case CButton25:
					name = "P# Button 25";
					break;
				case CButton26:
					name = "P# Button 26";
					break;
				case CButton27:
					name = "P# Button 27";
					break;
				case CButton28:
					name = "P# Button 28";
					break;
				case CButton29:
					name = "P# Button 29";
					break;
				case CButton30:
					name = "P# Button 30";
					break;
				case CButton31:
					name = "P# Button 31";
					break;
				case CButton32:
					name = "P# Button 32";
					break;

				case CAxisXp:
					name = "P# X+";
					break;
				case CAxisXm:
					name = "P# X-";
					break;
				case CAxisYp:
					name = "P# Y+";
					break;
				case CAxisYm:
					name = "P# Y-";
					break;
				case CAxisZp:
					name = "P# Z+";
					break;
				case CAxisZm:
					name = "P# Z-";
					break;

				case CAxisRXp:
					name = "P# RX+";
					break;
				case CAxisRXm:
					name = "P# RX-";
					break;
				case CAxisRYp:
					name = "P# RY+";
					break;
				case CAxisRYm:
					name = "P# RY-";
					break;
				case CAxisRZp:
					name = "P# RZ+";
					break;
				case CAxisRZm:
					name = "P# RZ-";
					break;

				case CSliderUp:
					name = "P# SliderU+";
					break;
				case CSliderUm:
					name = "P# SliderU-";
					break;
				case CSliderVp:
					name = "P# SliderV+";
					break;
				case CSliderVm:
					name = "P# SliderV-";
					break;

				case CPOV1Left:
					name = "P# Left";
					break;
				case CPOV1Up:
					name = "P# Up";
					break;
				case CPOV1Right:
					name = "P# Right";
					break;
				case CPOV1Down:
					name = "P# Down";
					break;

				case CPOV2Left:
					name = "P# Left2";
					break;
				case CPOV2Up:
					name = "P# Up2";
					break;
				case CPOV2Right:
					name = "P# Right2";
					break;
				case CPOV2Down:
					name = "P# Down2";
					break;

				case CPOV3Left:
					name = "P# Left3";
					break;
				case CPOV3Up:
					name = "P# Up3";
					break;
				case CPOV3Right:
					name = "P# Right3";
					break;
				case CPOV3Down:
					name = "P# Down3";
					break;

				case CPOV4Left:
					name = "P# Left4";
					break;
				case CPOV4Up:
					name = "P# Up4";
					break;
				case CPOV4Right:
					name = "P# Right4";
					break;
				case CPOV4Down:
					name = "P# Down4";
					break;
				}

				switch(controllerid(ikey)) {
				case Controller1:
					name[1] = '1';
					return name;
				case Controller2:
					name[1] = '2';
					return name;
				case Controller3:
					name[1] = '3';
					return name;
				case Controller4:
					name[1] = '4';
					return name;
				case Controller5:
					name[1] = '5';
					return name;
				case Controller6:
					name[1] = '6';
					return name;
				case Controller7:
					name[1] = '7';
					return name;
				case Controller8:
					name[1] = '8';
					return name;
				}
			}

			return "Unknown";
		}
	}  // namespace input
}  // namespace cb

