#ifdef _MSVC_LANG

#define _CRT_SECURE_NO_WARNINGS

#endif

#include "../Headers/BFW.hpp"



static const BFW_CHAR_TYPE_A* DefaultLocale = nullptr;



const bool BFW_API BFW::String::Init()
{
	if (DefaultLocale)
	{
		return true;
	}

	DefaultLocale = std::setlocale(LC_ALL, nullptr);

	if (!DefaultLocale)
	{
		return false;
	}

	if (!std::setlocale(LC_ALL, "en_US.UTF-8"))
	{
		DefaultLocale = nullptr;
		return false;
	}

	return true;
}

void BFW_API BFW::String::Stop()
{
	if (!DefaultLocale)
	{
		return;
	}

	std::setlocale(LC_ALL, DefaultLocale);

	DefaultLocale = nullptr;
}

const BFW_CHAR_TYPE_A* BFW_API BFW::String::GetDefaultLocale()
{
	return DefaultLocale;
}

const BFW_STRING_TYPE_W BFW_API BFW::String::FromUTF8ToUnicode(const BFW_STRING_VIEW_TYPE_A& _String, bool* _Error)
{
	if (_Error)
	{
		*_Error = false;
	}

	BFW_STRING_TYPE_A _TempString = BFW_STRING_TYPE_A(_String.data(), _String.size());

	BFW_STRING_TYPE_W _Result;

	size_t _Size = std::mbstowcs(nullptr, _TempString.data(), 0);

	if (_Size == std::numeric_limits<size_t>::max())
	{
		if (_Error)
		{
			*_Error = true;
		}

		return L"";
	}

	_Result.resize(_Size);

	std::mbstowcs(_Result.data(), _TempString.data(), _Result.size());

	_Result[_Result.size()] = '\0';

	return _Result;
}

const BFW_STRING_TYPE_A BFW_API BFW::String::FromUnicodeToUTF8(const BFW_STRING_VIEW_TYPE_W& _String, bool* _Error)
{
	if (_Error)
	{
		*_Error = false;
	}

	BFW_STRING_TYPE_W _TempString = BFW_STRING_TYPE_W(_String.data(), _String.size());

	BFW_STRING_TYPE_A _Result;

	size_t _Size = std::wcstombs(nullptr, _TempString.data(), 0);

	if (_Size == std::numeric_limits<size_t>::max())
	{
		if (_Error)
		{
			*_Error = true;
		}

		return "";
	}

	_Result.resize(_Size);

	std::wcstombs(_Result.data(), _TempString.data(), _Result.size());

	_Result[_Result.size()] = '\0';

	return _Result;
}
