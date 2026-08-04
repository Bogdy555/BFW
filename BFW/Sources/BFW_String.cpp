#define _CRT_SECURE_NO_WARNINGS
#include "../Headers/BFW.hpp"



const std::wstring BFW_API BFW::String::FromUTF8ToUnicode(const std::string_view& _String)
{
	std::wstring _Result;

	_Result.resize(std::mbstowcs(nullptr, _String.data(), 0) + 1);

	std::mbstowcs(_Result.data(), _String.data(), _Result.size() - 1);

	_Result[_Result.size() - 1] = '\0';

	return _Result;
}

const std::string BFW_API BFW::String::FromUnicodeToUTF8(const std::wstring_view& _String)
{
	std::string _Result;

	_Result.resize(std::wcstombs(nullptr, _String.data(), 0) + 1);

	std::wcstombs(_Result.data(), _String.data(), _Result.size() - 1);

	_Result[_Result.size() - 1] = '\0';

	return _Result;
}
