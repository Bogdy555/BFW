#ifdef _MSVC_LANG

#define _CRT_SECURE_NO_WARNINGS

#endif

#include "../Headers/BFW.hpp"



static BFW_STRING_TYPE_A DefaultLocale = "";



const bool BFW_API BFW::String::Init()
{
	if (DefaultLocale.size())
	{
		return true;
	}

	const BFW_CHAR_TYPE_A* _Ptr = std::setlocale(LC_ALL, nullptr);

	if (!_Ptr)
	{
		return false;
	}

	DefaultLocale = _Ptr;

	if (!std::setlocale(LC_ALL, "en_US.UTF-8"))
	{
		DefaultLocale = "";
		return false;
	}

	return true;
}

void BFW_API BFW::String::Stop()
{
	if (!DefaultLocale.size())
	{
		return;
	}

	std::setlocale(LC_ALL, DefaultLocale.c_str());

	DefaultLocale = "";
}

BFW_API const BFW_CHAR_TYPE_A* BFW::String::GetDefaultLocale()
{
	return DefaultLocale.c_str();
}

const BFW_STRING_TYPE_W BFW_API BFW::String::FromUTF8ToUnicode(const BFW_STRING_VIEW_TYPE_A& _String, bool* _Error)
{
	if (!IsValidUTF8String(_String))
	{
		if (_Error)
		{
			*_Error = true;
		}

		return L"";
	}

	BFW_STRING_TYPE_A _TempString = BFW_STRING_TYPE_A(_String.data(), _String.size());

	size_t _Size = std::mbstowcs(nullptr, _TempString.data(), 0);

	if (_Size == std::numeric_limits<size_t>::max())
	{
		if (_Error)
		{
			*_Error = true;
		}

		return L"";
	}

	BFW_STRING_TYPE_W _Result;

	_Result.resize(_Size);

	std::mbstowcs(_Result.data(), _TempString.data(), _Result.size());

	_Result[_Result.size()] = '\0';

	if (!IsValidUnicodeString(_Result))
	{
		if (_Error)
		{
			*_Error = true;
		}

		return L"";
	}

	if (_Error)
	{
		*_Error = false;
	}

	return _Result;
}

const BFW_STRING_TYPE_A BFW_API BFW::String::FromUnicodeToUTF8(const BFW_STRING_VIEW_TYPE_W& _String, bool* _Error)
{
	if (!IsValidUnicodeString(_String))
	{
		if (_Error)
		{
			*_Error = true;
		}

		return "";
	}

	BFW_STRING_TYPE_W _TempString = BFW_STRING_TYPE_W(_String.data(), _String.size());

	size_t _Size = std::wcstombs(nullptr, _TempString.data(), 0);

	if (_Size == std::numeric_limits<size_t>::max())
	{
		if (_Error)
		{
			*_Error = true;
		}

		return "";
	}

	BFW_STRING_TYPE_A _Result;

	_Result.resize(_Size);

	std::wcstombs(_Result.data(), _TempString.data(), _Result.size());

	_Result[_Result.size()] = '\0';

	if (!IsValidUTF8String(_Result))
	{
		if (_Error)
		{
			*_Error = true;
		}

		return "";
	}

	if (_Error)
	{
		*_Error = false;
	}

	return _Result;
}

const bool BFW_API BFW::String::IsHexA(const BFW_CHAR_TYPE_A _Char)
{
	return (_Char >= '0' && _Char <= '9') || (_Char >= 'A' && _Char <= 'F') || (_Char >= 'a' && _Char <= 'f');
}

const bool BFW_API BFW::String::IsHexW(const BFW_CHAR_TYPE_W _Char)
{
	return (_Char >= L'0' && _Char <= L'9') || (_Char >= L'A' && _Char <= L'F') || (_Char >= L'a' && _Char <= L'f');
}

const bool BFW_API BFW::String::IsHex(const BFW_CHAR_TYPE _Char)
{
	BFW_UNICODE_CALL(return IsHexW(_Char));
	BFW_NON_UNICODE_CALL(return IsHexA(_Char));
}

const uint8_t BFW_API BFW::String::HexCharToNibbleA(const BFW_CHAR_TYPE_A _Char)
{
	if (_Char >= 'A' && _Char <= 'F')
	{
		return _Char - 'A' + 10;
	}

	if (_Char >= 'a' && _Char <= 'f')
	{
		return _Char - 'a' + 10;
	}

	return _Char - '0';
}

const uint8_t BFW_API BFW::String::HexCharToNibbleW(const BFW_CHAR_TYPE_W _Char)
{
	if (_Char >= L'A' && _Char <= L'F')
	{
		return _Char - L'A' + 10;
	}

	if (_Char >= L'a' && _Char <= L'f')
	{
		return _Char - L'a' + 10;
	}

	return _Char - L'0';
}

const uint8_t BFW_API BFW::String::HexCharToNibble(const BFW_CHAR_TYPE _Char)
{
	BFW_UNICODE_CALL(return HexCharToNibbleW(_Char));
	BFW_NON_UNICODE_CALL(return HexCharToNibbleA(_Char));
}

const bool BFW_API BFW::String::IsUTF8MultiByte2(const BFW_CHAR_TYPE_A _Char)
{
	return (_Char & 0b11100000) == 0b11000000;
}

const bool BFW_API BFW::String::IsUTF8MultiByte3(const BFW_CHAR_TYPE_A _Char)
{
	return (_Char & 0b11110000) == 0b11100000;
}

const bool BFW_API BFW::String::IsUTF8MultiByte4(const BFW_CHAR_TYPE_A _Char)
{
	return (_Char & 0b11111000) == 0b11110000;
}

const bool BFW_API BFW::String::IsValidUTF8MultiByte2(const BFW_CHAR_TYPE_A _Char)
{
	return _Char >= 0xC2;
}

const bool BFW_API BFW::String::IsValidUTF8MultiByte3(const BFW_CHAR_TYPE_A _Char)
{
	return true;
}

const bool BFW_API BFW::String::IsValidUTF8MultiByte4(const BFW_CHAR_TYPE_A _Char)
{
	return _Char <= 0xF4;
}

const bool BFW_API BFW::String::IsUTF8MultiByteContinuation(const BFW_CHAR_TYPE_A _Char)
{
	return (_Char & 0b11000000) == 0b10000000;
}

const bool BFW_API BFW::String::IsValidUTF8MultiByte3FirstContinuation(const BFW_CHAR_TYPE_A _Char1, const BFW_CHAR_TYPE_A _Char2)
{
	return (_Char1 != 0xE0 && _Char1 != 0xED) || (_Char1 == 0xE0 && _Char2 >= 0xA0) || (_Char1 == 0xED && _Char2 <= 0x9F);
}

const bool BFW_API BFW::String::IsValidUTF8MultiByte4FirstContinuation(const BFW_CHAR_TYPE_A _Char1, const BFW_CHAR_TYPE_A _Char2)
{
	return (_Char1 != 0xF0 && _Char1 != 0xF4) || (_Char1 == 0xF0 && _Char2 >= 0x90) || (_Char1 == 0xF4 && _Char2 <= 0x8F);
}

const bool BFW_API BFW::String::IsUnicodeSurrogated(const uint32_t _Char)
{
	return _Char >= 0xD800 && _Char <= 0xDBFF;
}

const bool BFW_API BFW::String::IsUnicodeSurrogatedContinuation(const uint32_t _Char)
{
	return _Char >= 0xDC00 && _Char <= 0xDFFF;
}

const bool BFW_API BFW::String::IsValidUnicodePoint1A(const uint32_t _Char)
{
	return _Char <= 0x7F;
}

const bool BFW_API BFW::String::IsValidUnicodePoint2A(const uint32_t _Char)
{
	return _Char >= 0x80 && _Char <= 0x7FF;
}

const bool BFW_API BFW::String::IsValidUnicodePoint3A(const uint32_t _Char)
{
	return _Char >= 0x800 && _Char <= 0xFFFF;
}

const bool BFW_API BFW::String::IsValidUnicodePoint4A(const uint32_t _Char)
{
	return _Char >= 0x10000 && _Char <= 0x10FFFF;
}

const bool BFW_API BFW::String::IsValidUnicodePointW(const uint32_t _Char)
{
	return _Char <= 0x10FFFF && (_Char & 0xFFFE) != 0xFFFE && (_Char < 0xFDD0 || _Char > 0xFDEF);
}

const uint32_t BFW_API BFW::String::ConstructUnicodePointA(const BFW_CHAR_TYPE_A _Char)
{
	return _Char;
}

const uint32_t BFW_API BFW::String::ConstructUnicodePointA(const BFW_CHAR_TYPE_A _Char1, const BFW_CHAR_TYPE_A _Char2)
{
	return ((uint32_t)(_Char1 & 0x1F) << 6) | (uint32_t)(_Char2 & 0x3F);
}

const uint32_t BFW_API BFW::String::ConstructUnicodePointA(const BFW_CHAR_TYPE_A _Char1, const BFW_CHAR_TYPE_A _Char2, const BFW_CHAR_TYPE_A _Char3)
{
	return ((uint32_t)(_Char1 & 0x0F) << 12) | ((uint32_t)(_Char2 & 0x3F) << 6) | (uint32_t)(_Char3 & 0x3F);
}

const uint32_t BFW_API BFW::String::ConstructUnicodePointA(const BFW_CHAR_TYPE_A _Char1, const BFW_CHAR_TYPE_A _Char2, const BFW_CHAR_TYPE_A _Char3, const BFW_CHAR_TYPE_A _Char4)
{
	return ((uint32_t)(_Char1 & 0x07) << 18) | ((uint32_t)(_Char2 & 0x3F) << 12) | ((uint32_t)(_Char3 & 0x3F) << 6) | (uint32_t)(_Char4 & 0x3F);
}

#ifdef BFW_WINDOWS_PLATFORM

const uint32_t BFW_API BFW::String::ConstructUnicodePointW(const BFW_CHAR_TYPE_W _Char1, const BFW_CHAR_TYPE_W _Char2)
{
	return 0x10000 + ((uint32_t)(_Char1 - 0xD800) << 10) + (uint32_t)(_Char2 - 0xDC00);
}

#endif

const bool BFW_API BFW::String::IsValidUTF8String(const BFW_STRING_VIEW_TYPE_A& _String)
{
	for (size_t _Index = 0; _Index < _String.size(); _Index++)
	{
		if (IsUTF8MultiByte2(_String[_Index]))
		{
			if (!IsValidUTF8MultiByte2(_String[_Index]))
			{
				return false;
			}

			_Index++;

			if (_Index >= _String.size())
			{
				return false;
			}

			if (!IsUTF8MultiByteContinuation(_String[_Index]))
			{
				return false;
			}

			uint32_t _CodePoint = ConstructUnicodePointA(_String[_Index - 1], _String[_Index]);

			if (!IsValidUnicodePoint2A(_CodePoint) || IsUnicodeSurrogated(_CodePoint) || IsUnicodeSurrogatedContinuation(_CodePoint))
			{
				return false;
			}

			continue;
		}

		if (IsUTF8MultiByte3(_String[_Index]))
		{
			if (!IsValidUTF8MultiByte3(_String[_Index]))
			{
				return false;
			}

			_Index++;

			if (_Index >= _String.size())
			{
				return false;
			}

			if (!IsUTF8MultiByteContinuation(_String[_Index]) || !IsValidUTF8MultiByte3FirstContinuation(_String[_Index - 1], _String[_Index]))
			{
				return false;
			}

			_Index++;

			if (_Index >= _String.size())
			{
				return false;
			}

			if (!IsUTF8MultiByteContinuation(_String[_Index]))
			{
				return false;
			}

			uint32_t _CodePoint = ConstructUnicodePointA(_String[_Index - 2], _String[_Index - 1], _String[_Index]);

			if (!IsValidUnicodePoint3A(_CodePoint) || IsUnicodeSurrogated(_CodePoint) || IsUnicodeSurrogatedContinuation(_CodePoint))
			{
				return false;
			}

			continue;
		}

		if (IsUTF8MultiByte4(_String[_Index]))
		{
			if (!IsValidUTF8MultiByte4(_String[_Index]))
			{
				return false;
			}

			_Index++;

			if (_Index >= _String.size())
			{
				return false;
			}

			if (!IsUTF8MultiByteContinuation(_String[_Index]) || !IsValidUTF8MultiByte4FirstContinuation(_String[_Index - 1], _String[_Index]))
			{
				return false;
			}

			_Index++;

			if (_Index >= _String.size())
			{
				return false;
			}

			if (!IsUTF8MultiByteContinuation(_String[_Index]))
			{
				return false;
			}

			_Index++;

			if (_Index >= _String.size())
			{
				return false;
			}

			if (!IsUTF8MultiByteContinuation(_String[_Index]))
			{
				return false;
			}

			uint32_t _CodePoint = ConstructUnicodePointA(_String[_Index - 3], _String[_Index - 2], _String[_Index - 1], _String[_Index]);

			if (!IsValidUnicodePoint4A(_CodePoint) || IsUnicodeSurrogated(_CodePoint) || IsUnicodeSurrogatedContinuation(_CodePoint))
			{
				return false;
			}

			continue;
		}

		if (IsUTF8MultiByteContinuation(_String[_Index]))
		{
			return false;
		}

		uint32_t _CodePoint = ConstructUnicodePointA(_String[_Index]);

		if (!IsValidUnicodePoint1A(_CodePoint) || IsUnicodeSurrogated(_CodePoint) || IsUnicodeSurrogatedContinuation(_CodePoint))
		{
			return false;
		}
	}

	return true;
}

const bool BFW_API BFW::String::IsValidUnicodeString(const BFW_STRING_VIEW_TYPE_W& _String)
{
	for (size_t _Index = 0; _Index < _String.size(); _Index++)
	{
#ifdef BFW_WINDOWS_PLATFORM

		if (IsUnicodeSurrogated(_String[_Index]))
		{
			_Index++;

			if (_Index >= _String.size())
			{
				return false;
			}

			if (!IsUnicodeSurrogatedContinuation(_String[_Index]))
			{
				return false;
			}

			if (!IsValidUnicodePointW(ConstructUnicodePointW(_String[_Index - 1], _String[_Index])))
			{
				return false;
			}

			continue;
		}

#endif

#if defined BFW_LINUX_PLATFORM || defined BFW_ESP32_PLATFORM

		if (IsUnicodeSurrogated(_String[_Index]))
		{
			return false;
		}

#endif

		if (IsUnicodeSurrogatedContinuation(_String[_Index]))
		{
			return false;
		}

		if (!IsValidUnicodePointW(_String[_Index]))
		{
			return false;
		}
	}

	return true;
}

const bool BFW_API BFW::String::IsControlCharacter(const BFW_CHAR_TYPE_A _Char)
{
	return (unsigned BFW_CHAR_TYPE_A)(_Char) < 0x20;
}

const bool BFW_API BFW::String::IsControlCharacter(const BFW_CHAR_TYPE_W _Char)
{
	return _Char < 0x20;
}

const bool BFW_API BFW::String::IsExtendedControlCharacter(const BFW_CHAR_TYPE_A _Char)
{
	return _Char >= 0x80 && _Char <= 0x9F;
}

const bool BFW_API BFW::String::IsExtendedControlCharacter(const BFW_CHAR_TYPE_W _Char)
{
	return _Char >= 0x80 && _Char <= 0x9F;
}
