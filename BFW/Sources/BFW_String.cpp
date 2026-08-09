#ifdef _MSVC_LANG

#define _CRT_SECURE_NO_WARNINGS

#endif

#include "../Headers/BFW.hpp"



const BFW_STRING_TYPE_W BFW_API BFW::String::FromUTF8ToUnicode(const BFW_STRING_VIEW_TYPE_A& _String)
{
	BFW_STRING_TYPE_W _Result;

	_Result.resize(std::mbstowcs(nullptr, _String.data(), 0) + 1);

	std::mbstowcs(_Result.data(), _String.data(), _Result.size() - 1);

	_Result[_Result.size() - 1] = '\0';

	return _Result;
}

const BFW_STRING_TYPE_A BFW_API BFW::String::FromUnicodeToUTF8(const BFW_STRING_VIEW_TYPE_W& _String)
{
	BFW_STRING_TYPE_A _Result;

	_Result.resize(std::wcstombs(nullptr, _String.data(), 0) + 1);

	std::wcstombs(_Result.data(), _String.data(), _Result.size() - 1);

	_Result[_Result.size() - 1] = '\0';

	return _Result;
}
