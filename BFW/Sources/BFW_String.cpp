#ifdef _MSVC_LANG

#define _CRT_SECURE_NO_WARNINGS

#endif

#include "../Headers/BFW.hpp"



const BFW_STRING_TYPE_W BFW_API BFW::String::FromUTF8ToUnicode(const BFW_STRING_VIEW_TYPE_A& _String)
{
	BFW_STRING_TYPE_A _TempString = BFW_STRING_TYPE_A(_String.data(), _String.size());

	BFW_STRING_TYPE_W _Result;

	size_t _Size = std::mbstowcs(nullptr, _TempString.data(), 0);

	if (_Size == std::numeric_limits<size_t>::max())
	{
		return L"";
	}

	_Result.resize(_Size);

	std::mbstowcs(_Result.data(), _TempString.data(), _Result.size());

	_Result[_Result.size()] = '\0';

	return _Result;
}

const BFW_STRING_TYPE_A BFW_API BFW::String::FromUnicodeToUTF8(const BFW_STRING_VIEW_TYPE_W& _String)
{
	BFW_STRING_TYPE_W _TempString = BFW_STRING_TYPE_W(_String.data(), _String.size());

	BFW_STRING_TYPE_A _Result;

	size_t _Size = std::wcstombs(nullptr, _TempString.data(), 0);

	if (_Size == std::numeric_limits<size_t>::max())
	{
		return "";
	}

	_Result.resize(_Size);

	std::wcstombs(_Result.data(), _TempString.data(), _Result.size());

	_Result[_Result.size()] = '\0';

	return _Result;
}
