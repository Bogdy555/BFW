#include "../Headers/BFW.hpp"



#ifdef BFW_WINDOWS_PLATFORM

static HANDLE ConsoleHandle = INVALID_HANDLE_VALUE;
static uint16_t DefaultAttribute = BFW::Log::_TxtWhiteAttribute | BFW::Log::_BkgBlackAttribute;

#endif



#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

#ifdef BFW_WINDOWS_PLATFORM

const bool BFW_API BFW::Log::Init()
{
	if (ConsoleHandle != INVALID_HANDLE_VALUE)
	{
		return true;
	}

	ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	if (ConsoleHandle == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	CONSOLE_SCREEN_BUFFER_INFO _ConsoleInfo = { 0 };

	if (!GetConsoleScreenBufferInfo(ConsoleHandle, &_ConsoleInfo))
	{
		CloseHandle(ConsoleHandle);
		ConsoleHandle = INVALID_HANDLE_VALUE;
		return false;
	}

	DefaultAttribute = _ConsoleInfo.wAttributes;

	return true;
}

void BFW_API BFW::Log::Stop()
{
	if (ConsoleHandle == INVALID_HANDLE_VALUE)
	{
		return;
	}

	SetConsoleAttribute(DefaultAttribute);
	DefaultAttribute = BFW::Log::_TxtWhiteAttribute | BFW::Log::_BkgBlackAttribute;

	ConsoleHandle = INVALID_HANDLE_VALUE;
}

#endif

#ifdef BFW_LINUX_PLATFORM

const bool BFW_API BFW::Log::Init()
{
	return true;
}

void BFW_API BFW::Log::Stop()
{
	std::wcout << L"\033[0m";
}

#endif

#endif

#ifdef BFW_ESP32_PLATFORM

const bool BFW_API BFW::Log::Init(const size_t _BaudRate)
{
	Serial.begin(_BaudRate);

	while (!Serial)
	{

	}

	return true;
}

void BFW_API BFW::Log::Stop()
{
	Serial.end();
}

#endif

#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

#ifdef BFW_WINDOWS_PLATFORM

const bool BFW_API BFW::Log::SetConsoleAttribute(const uint16_t _Attribute)
{
	if (ConsoleHandle == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	return SetConsoleTextAttribute(ConsoleHandle, _Attribute);
}

#endif

#ifdef BFW_LINUX_PLATFORM

const bool BFW_API BFW::Log::SetConsoleAttribute(const uint16_t _Attribute)
{
	const uint16_t _Txt = _Attribute & 0b0000000000001111;
	const uint16_t _Bkg = _Attribute & 0b0000000011110000;

	switch (_Txt)
	{
	case _TxtBlackAttribute:
	{
		std::wcout << L"\033[38;2;0;0;0m";
		break;
	}
	case _TxtBlueAttribute:
	{
		std::wcout << L"\033[38;2;0;0;255m";
		break;
	}
	case _TxtGreenAttribute:
	{
		std::wcout << L"\033[38;2;0;255;0m";
		break;
	}
	case _TxtAquaAttribute:
	{
		std::wcout << L"\033[38;2;0;255;255m";
		break;
	}
	case _TxtRedAttribute:
	{
		std::wcout << L"\033[38;2;255;0;0m";
		break;
	}
	case _TxtPurpleAttribute:
	{
		std::wcout << L"\033[38;2;255;0;255m";
		break;
	}
	case _TxtYellowAttribute:
	{
		std::wcout << L"\033[38;2;255;255;0m";
		break;
	}
	case _TxtLightGrayAttribute:
	{
		std::wcout << L"\033[38;2;169;169;169m";
		break;
	}
	case _TxtGrayAttribute:
	{
		std::wcout << L"\033[38;2;84;84;84m";
		break;
	}
	case _TxtLightBlueAttribute:
	{
		std::wcout << L"\033[38;2;127;127;255m";
		break;
	}
	case _TxtLightGreenAttribute:
	{
		std::wcout << L"\033[38;2;127;255;127m";
		break;
	}
	case _TxtTurquoiseAttribute:
	{
		std::wcout << L"\033[38;2;127;255;255m";
		break;
	}
	case _TxtPinkAttribute:
	{
		std::wcout << L"\033[38;2;255;127;127m";
		break;
	}
	case _TxtLightPurpleAttribute:
	{
		std::wcout << L"\033[38;2;255;127;255m";
		break;
	}
	case _TxtLightYellowAttribute:
	{
		std::wcout << L"\033[38;2;255;255;127m";
		break;
	}
	case _TxtWhiteAttribute:
	{
		std::wcout << L"\033[38;2;255;255;255m";
		break;
	}
	default:
	{
		std::wcout << L"\033[38;2;255;255;255m";
		break;
	}
	}

	switch (_Bkg)
	{
	case _BkgBlackAttribute:
	{
		std::wcout << L"\033[48;2;0;0;0m";
		break;
	}
	case _BkgBlueAttribute:
	{
		std::wcout << L"\033[48;2;0;0;255m";
		break;
	}
	case _BkgGreenAttribute:
	{
		std::wcout << L"\033[48;2;0;255;0m";
		break;
	}
	case _BkgAquaAttribute:
	{
		std::wcout << L"\033[48;2;0;255;255m";
		break;
	}
	case _BkgRedAttribute:
	{
		std::wcout << L"\033[48;2;255;0;0m";
		break;
	}
	case _BkgPurpleAttribute:
	{
		std::wcout << L"\033[48;2;255;0;255m";
		break;
	}
	case _BkgYellowAttribute:
	{
		std::wcout << L"\033[48;2;255;255;0m";
		break;
	}
	case _BkgLightGrayAttribute:
	{
		std::wcout << L"\033[48;2;169;169;169m";
		break;
	}
	case _BkgGrayAttribute:
	{
		std::wcout << L"\033[48;2;84;84;84m";
		break;
	}
	case _BkgLightBlueAttribute:
	{
		std::wcout << L"\033[48;2;127;127;255m";
		break;
	}
	case _BkgLightGreenAttribute:
	{
		std::wcout << L"\033[48;2;127;255;127m";
		break;
	}
	case _BkgTurquoiseAttribute:
	{
		std::wcout << L"\033[48;2;127;255;255m";
		break;
	}
	case _BkgPinkAttribute:
	{
		std::wcout << L"\033[48;2;255;127;127m";
		break;
	}
	case _BkgLightPurpleAttribute:
	{
		std::wcout << L"\033[48;2;255;127;255m";
		break;
	}
	case _BkgLightYellowAttribute:
	{
		std::wcout << L"\033[48;2;255;255;127m";
		break;
	}
	case _BkgWhiteAttribute:
	{
		std::wcout << L"\033[48;2;255;255;255m";
		break;
	}
	default:
	{
		std::wcout << L"\033[48;2;255;255;255m";
		break;
	}
	}

	return true;
}

#endif

#endif

#ifdef BFW_WINDOWS_PLATFORM

const bool BFW_API BFW::Log::GetConsoleAttribute(uint16_t& _Attribute)
{
	if (ConsoleHandle == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	CONSOLE_SCREEN_BUFFER_INFO _ConsoleInfo = { 0 };

	if (!GetConsoleScreenBufferInfo(ConsoleHandle, &_ConsoleInfo))
	{
		return false;
	}

	_Attribute = _ConsoleInfo.wAttributes;

	return true;
}

const HANDLE BFW_API BFW::Log::GetConsoleHandle()
{
	return ConsoleHandle;
}

const uint16_t BFW_API BFW::Log::GetDefaultAttribute()
{
	return DefaultAttribute;
}

#endif
