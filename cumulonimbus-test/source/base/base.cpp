#include <UnitTest.h>

#include <cb/base/Timer.hpp>
#include <cb/base/String.hpp>
#include <cb/base/Date.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace cb;

namespace cumulonimbustest
{
	TEST_CLASS(Base) {
	public:
		TEST_METHOD(BaseDate) {
			base::Date d;

			Logger::WriteMessage((const wchar_t *)base::utf16(base::format("Segundos: %d", d.seconds())).c_str());
			Logger::WriteMessage((const wchar_t *)base::utf16(base::format("Minutos: %d", d.minutes())).c_str());
			Logger::WriteMessage((const wchar_t *)base::utf16(base::format("Horas: %d", d.hour())).c_str());
			Logger::WriteMessage((const wchar_t *)base::utf16(base::format("Dia do mês: %d", d.mday())).c_str());
			Logger::WriteMessage((const wchar_t *)base::utf16(base::format("Dia da semana: %d", d.wday())).c_str());
			Logger::WriteMessage((const wchar_t *)base::utf16(base::format("Dia do ano: %d", d.yday())).c_str());
			Logger::WriteMessage((const wchar_t *)base::utf16(base::format("Mês: %d", d.mon())).c_str());
			Logger::WriteMessage((const wchar_t *)base::utf16(base::format("Ano: %d", d.year())).c_str());

			Logger::WriteMessage(d.str("Now it's %I:%M%p.").c_str());

			d = base::Date();
		}

		TEST_METHOD(BaseString) {
			base::string str = "☁ OLá Mundo! ☁";
			base::wstring wstr = base::wstr("☁ OLá Mundo! ☁");
			base::string16 str16 = base::utf16("☁ OLá Mundo! ☁");
			base::string32 str32 = base::utf32("☁ OLá Mundo! ☁");

			base::string space = "    Hello    World!      ";
			base::wstring wspace = L"    Hello    World!      ";
			base::string16 space16 = base::utf16("    Hello    World!      ");
			base::string32 space32 = base::utf32("    Hello    World!      ");

			base::string str_w = base::utf8(wstr);
			base::string str_16 = base::utf8(str16);
			base::string str_32 = base::utf8(str32);

			base::wstring wstr_8 = base::wstr(str);
			base::wstring wstr_16 = base::wstr(str16);
			base::wstring wstr_32 = base::wstr(str32);

			base::string16 str16_8 = base::utf16(str);
			base::string16 str16_w = base::utf16(wstr);
			base::string16 str16_32 = base::utf16(str32);

			base::string32 str32_8 = base::utf32(str);
			base::string32 str32_w = base::utf32(wstr);
			base::string32 str32_16 = base::utf32(str16);

			Logger::WriteMessage(base::wstr(base::format("UTF8  - str  : %s - Up[ %s ] - Lo[ %s ]", str.c_str(), base::lower(str).c_str(), base::upper(str).c_str() )).c_str());
			Logger::WriteMessage(base::wstr(base::format("UTF8  - wstr : %s - Up[ %s ] - Lo[ %s ]", str_w.c_str(), base::lower(str_w).c_str(), base::upper(str_w).c_str() )).c_str());
			Logger::WriteMessage(base::wstr(base::format("UTF8  - str16: %s - Up[ %s ] - Lo[ %s ]", str_16.c_str(), base::lower(str_16).c_str(), base::upper(str_16).c_str() )).c_str());
			Logger::WriteMessage(base::wstr(base::format("UTF8  - str32: %s - Up[ %s ] - Lo[ %s ]", str_32.c_str(), base::lower(str_32).c_str(), base::upper(str_32).c_str() )).c_str());

			Logger::WriteMessage(base::wstr(base::format("WCHAR - str  : %s - Up[ %s ] - Lo[ %s ]", base::utf8(wstr_8).c_str(), base::utf8(base::lower(wstr_8)).c_str(), base::utf8(base::upper(wstr_8)).c_str() )).c_str());
			Logger::WriteMessage(base::wstr(base::format("WCHAR - wstr : %s - Up[ %s ] - Lo[ %s ]", base::utf8(wstr).c_str(), base::utf8(base::lower(wstr)).c_str(), base::utf8(base::upper(wstr)).c_str() )).c_str());
			Logger::WriteMessage(base::wstr(base::format("WCHAR - str16: %s - Up[ %s ] - Lo[ %s ]", base::utf8(wstr_16).c_str(), base::utf8(base::lower(wstr_16)).c_str(), base::utf8(base::upper(wstr_16)).c_str() )).c_str());
			Logger::WriteMessage(base::wstr(base::format("WCHAR - str32: %s - Up[ %s ] - Lo[ %s ]", base::utf8(wstr_32).c_str(), base::utf8(base::lower(wstr_32)).c_str(), base::utf8(base::upper(wstr_32)).c_str() )).c_str());

			Logger::WriteMessage(base::wstr(base::format("UTF16 - str  : %s - Up[ %s ] - Lo[ %s ]", base::utf8(str16_8).c_str(), base::utf8(base::lower(str16_8)).c_str(), base::utf8(base::upper(str16_8)).c_str() )).c_str());
			Logger::WriteMessage(base::wstr(base::format("UTF16 - wstr : %s - Up[ %s ] - Lo[ %s ]", base::utf8(str16_w).c_str(), base::utf8(base::lower(str16_w)).c_str(), base::utf8(base::upper(str16_w)).c_str() )).c_str());
			Logger::WriteMessage(base::wstr(base::format("UTF16 - str16: %s - Up[ %s ] - Lo[ %s ]", base::utf8(str16).c_str(), base::utf8(base::lower(str16)).c_str(), base::utf8(base::upper(str16)).c_str() )).c_str());
			Logger::WriteMessage(base::wstr(base::format("UTF16 - str32: %s - Up[ %s ] - Lo[ %s ]", base::utf8(str16_32).c_str(), base::utf8(base::lower(str16_32)).c_str(), base::utf8(base::upper(str16_32)).c_str() )).c_str());

			Logger::WriteMessage(base::wstr(base::format("UTF32 - str  : %s - Up[ %s ] - Lo[ %s ]", base::utf8(str32_8).c_str(), base::utf8(base::lower(str32_8)).c_str(), base::utf8(base::upper(str32_8)).c_str() )).c_str());
			Logger::WriteMessage(base::wstr(base::format("UTF32 - wstr : %s - Up[ %s ] - Lo[ %s ]", base::utf8(str32_w).c_str(), base::utf8(base::lower(str32_w)).c_str(), base::utf8(base::upper(str32_w)).c_str() )).c_str());
			Logger::WriteMessage(base::wstr(base::format("UTF32 - str16: %s - Up[ %s ] - Lo[ %s ]", base::utf8(str32_16).c_str(), base::utf8(base::lower(str32_16)).c_str(), base::utf8(base::upper(str32_16)).c_str() )).c_str());
			Logger::WriteMessage(base::wstr(base::format("UTF32 - str32: %s - Up[ %s ] - Lo[ %s ]", base::utf8(str32).c_str(), base::utf8(base::lower(str32)).c_str(), base::utf8(base::upper(str32)).c_str() )).c_str());

			Assert::AreEqual(base::upper("Upper"), base::string("UPPER"), L"base::upper Falhou!", LINE_INFO());
			Assert::AreEqual(base::lower("Lower"), base::string("lower"), L"base::lower Falhou!", LINE_INFO());

			Assert::AreEqual(base::trim(" \n \v \f \r \t Hello \n \v \f \r \t  World! \n \v \f \r \t "), base::string("Hello World!"), L"base::trim Falhou!", LINE_INFO());

			Assert::AreEqual(base::trim(" \n \v \f \r \t Hello   World!  ", base::TrimLeft), base::string("Hello   World!  "), L"base::trimLeft Falhou!", LINE_INFO());
			Assert::AreEqual(base::trim("  Hello \n \v \f \r \t  World!  ", base::TrimInner), base::string("  Hello World!  "), L"base::trimInner Falhou!", LINE_INFO());
			Assert::AreEqual(base::trim("  Hello   World! \n \v \f \r \t ", base::TrimRight), base::string("  Hello   World!"), L"base::trimRight Falhou!", LINE_INFO());

			Logger::WriteMessage(base::format("Hash: %p", base::hash(str)).c_str());
		}
	};
}
