#ifdef _MSVC_LANG

#define _CRT_SECURE_NO_WARNINGS

#endif

#include "../Headers/BFW.hpp"



const BFW_STRING_TYPE_W BFW_API BFW::String::FromUTF8ToUnicode(const BFW_STRING_VIEW_TYPE_A& _String, bool* _Error)
{
	BFW_STRING_TYPE_W _Result;
	_Result.reserve(_String.size());

	for (size_t _Index = 0; _Index < _String.size(); _Index++)
	{
		if (IsUTF8MultiByte2(_String[_Index]))
		{
			if (!IsValidUTF8MultiByte2(_String[_Index]))
			{
				if (_Error)
				{
					*_Error = true;
				}

				return L"";
			}

			_Index++;

			if (_Index >= _String.size())
			{
				if (_Error)
				{
					*_Error = true;
				}

				return L"";
			}

			if (!IsUTF8MultiByteContinuation(_String[_Index]))
			{
				if (_Error)
				{
					*_Error = true;
				}

				return L"";
			}

			uint32_t _CodePoint = ConstructUnicodePointA(_String[_Index - 1], _String[_Index]);

			if (!IsValidUnicodePoint2A(_CodePoint) || IsUnicodeSurrogated(_CodePoint) || IsUnicodeSurrogatedContinuation(_CodePoint))
			{
				if (_Error)
				{
					*_Error = true;
				}

				return L"";
			}

#if defined BFW_WINDOWS_PLATFORM || defined BFW_ESP32_PLATFORM

			Vector<BFW_CHAR_TYPE_W> _Chars = DeconstructUnicodePointW(_CodePoint);

			for (size_t _CharIndex = 0; _CharIndex < _Chars.GetSize(); _CharIndex++)
			{
				_Result += _Chars[_CharIndex];
			}

#endif

#ifdef BFW_LINUX_PLATFORM

			_Result += _CodePoint;

#endif

			continue;
		}

		if (IsUTF8MultiByte3(_String[_Index]))
		{
			if (!IsValidUTF8MultiByte3(_String[_Index]))
			{
				if (_Error)
				{
					*_Error = true;
				}

				return L"";
			}

			_Index++;

			if (_Index >= _String.size())
			{
				if (_Error)
				{
					*_Error = true;
				}

				return L"";
			}

			if (!IsUTF8MultiByteContinuation(_String[_Index]) || !IsValidUTF8MultiByte3FirstContinuation(_String[_Index - 1], _String[_Index]))
			{
				if (_Error)
				{
					*_Error = true;
				}

				return L"";
			}

			_Index++;

			if (_Index >= _String.size())
			{
				if (_Error)
				{
					*_Error = true;
				}

				return L"";
			}

			if (!IsUTF8MultiByteContinuation(_String[_Index]))
			{
				if (_Error)
				{
					*_Error = true;
				}

				return L"";
			}

			uint32_t _CodePoint = ConstructUnicodePointA(_String[_Index - 2], _String[_Index - 1], _String[_Index]);

			if (!IsValidUnicodePoint3A(_CodePoint) || IsUnicodeSurrogated(_CodePoint) || IsUnicodeSurrogatedContinuation(_CodePoint))
			{
				if (_Error)
				{
					*_Error = true;
				}

				return L"";
			}

#if defined BFW_WINDOWS_PLATFORM || defined BFW_ESP32_PLATFORM

			Vector<BFW_CHAR_TYPE_W> _Chars = DeconstructUnicodePointW(_CodePoint);

			for (size_t _CharIndex = 0; _CharIndex < _Chars.GetSize(); _CharIndex++)
			{
				_Result += _Chars[_CharIndex];
			}

#endif

#ifdef BFW_LINUX_PLATFORM

			_Result += _CodePoint;

#endif

			continue;
		}

		if (IsUTF8MultiByte4(_String[_Index]))
		{
			if (!IsValidUTF8MultiByte4(_String[_Index]))
			{
				if (_Error)
				{
					*_Error = true;
				}

				return L"";
			}

			_Index++;

			if (_Index >= _String.size())
			{
				if (_Error)
				{
					*_Error = true;
				}

				return L"";
			}

			if (!IsUTF8MultiByteContinuation(_String[_Index]) || !IsValidUTF8MultiByte4FirstContinuation(_String[_Index - 1], _String[_Index]))
			{
				if (_Error)
				{
					*_Error = true;
				}

				return L"";
			}

			_Index++;

			if (_Index >= _String.size())
			{
				if (_Error)
				{
					*_Error = true;
				}

				return L"";
			}

			if (!IsUTF8MultiByteContinuation(_String[_Index]))
			{
				if (_Error)
				{
					*_Error = true;
				}

				return L"";
			}

			_Index++;

			if (_Index >= _String.size())
			{
				if (_Error)
				{
					*_Error = true;
				}

				return L"";
			}

			if (!IsUTF8MultiByteContinuation(_String[_Index]))
			{
				if (_Error)
				{
					*_Error = true;
				}

				return L"";
			}

			uint32_t _CodePoint = ConstructUnicodePointA(_String[_Index - 3], _String[_Index - 2], _String[_Index - 1], _String[_Index]);

			if (!IsValidUnicodePoint4A(_CodePoint) || IsUnicodeSurrogated(_CodePoint) || IsUnicodeSurrogatedContinuation(_CodePoint))
			{
				if (_Error)
				{
					*_Error = true;
				}

				return L"";
			}

#if defined BFW_WINDOWS_PLATFORM || defined BFW_ESP32_PLATFORM

			Vector<BFW_CHAR_TYPE_W> _Chars = DeconstructUnicodePointW(_CodePoint);

			for (size_t _CharIndex = 0; _CharIndex < _Chars.GetSize(); _CharIndex++)
			{
				_Result += _Chars[_CharIndex];
			}

#endif

#ifdef BFW_LINUX_PLATFORM

			_Result += _CodePoint;

#endif

			continue;
		}

		if (IsUTF8MultiByteContinuation(_String[_Index]))
		{
			if (_Error)
			{
				*_Error = true;
			}

			return L"";
		}

		uint32_t _CodePoint = ConstructUnicodePointA(_String[_Index]);

		if (!IsValidUnicodePoint1A(_CodePoint) || IsUnicodeSurrogated(_CodePoint) || IsUnicodeSurrogatedContinuation(_CodePoint))
		{
			if (_Error)
			{
				*_Error = true;
			}

			return L"";
		}

#if defined BFW_WINDOWS_PLATFORM || defined BFW_ESP32_PLATFORM

		Vector<BFW_CHAR_TYPE_W> _Chars = DeconstructUnicodePointW(_CodePoint);

		for (size_t _CharIndex = 0; _CharIndex < _Chars.GetSize(); _CharIndex++)
		{
			_Result += _Chars[_CharIndex];
		}

#endif

#ifdef BFW_LINUX_PLATFORM

		_Result += _CodePoint;

#endif
	}

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
	BFW_STRING_TYPE_A _Result;
	_Result.reserve(_String.size() * 4);

	for (size_t _Index = 0; _Index < _String.size(); _Index++)
	{
#if defined BFW_WINDOWS_PLATFORM || defined BFW_ESP32_PLATFORM

		if (IsUnicodeSurrogated(_String[_Index]))
		{
			_Index++;

			if (_Index >= _String.size())
			{
				if (_Error)
				{
					*_Error = true;
				}

				return "";
			}

			if (!IsUnicodeSurrogatedContinuation(_String[_Index]))
			{
				if (_Error)
				{
					*_Error = true;
				}

				return "";
			}

			uint32_t _CodePoint = CompositUnicodeSurrogates(_String[_Index - 1], _String[_Index]);

			if (!IsValidUnicodePointW(_CodePoint))
			{
				if (_Error)
				{
					*_Error = true;
				}

				return "";
			}

			Vector<BFW_CHAR_TYPE_A> _Chars = DeconstructUnicodePointA(_CodePoint);

			for (size_t _CharIndex = 0; _CharIndex < _Chars.GetSize(); _CharIndex++)
			{
				_Result += _Chars[_CharIndex];
			}

			continue;
		}

#endif

#ifdef BFW_LINUX_PLATFORM

		if (IsUnicodeSurrogated(_String[_Index]))
		{
			if (_Error)
			{
				*_Error = true;
			}

			return "";
		}

#endif

		if (IsUnicodeSurrogatedContinuation(_String[_Index]))
		{
			if (_Error)
			{
				*_Error = true;
			}

			return "";
		}

		if (!IsValidUnicodePointW(_String[_Index]))
		{
			if (_Error)
			{
				*_Error = true;
			}

			return "";
		}

		Vector<BFW_CHAR_TYPE_A> _Chars = DeconstructUnicodePointA(_String[_Index]);

		for (size_t _CharIndex = 0; _CharIndex < _Chars.GetSize(); _CharIndex++)
		{
			_Result += _Chars[_CharIndex];
		}
	}

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
	return (uint8_t)(_Char) >= 0xC2;
}

const bool BFW_API BFW::String::IsValidUTF8MultiByte3(const BFW_CHAR_TYPE_A _Char)
{
	return true;
}

const bool BFW_API BFW::String::IsValidUTF8MultiByte4(const BFW_CHAR_TYPE_A _Char)
{
	return (uint8_t)(_Char) <= 0xF4;
}

const bool BFW_API BFW::String::IsUTF8MultiByteContinuation(const BFW_CHAR_TYPE_A _Char)
{
	return (_Char & 0b11000000) == 0b10000000;
}

const bool BFW_API BFW::String::IsValidUTF8MultiByte3FirstContinuation(const BFW_CHAR_TYPE_A _Char1, const BFW_CHAR_TYPE_A _Char2)
{
	return (_Char1 != 0xE0 && _Char1 != 0xED) || (_Char1 == 0xE0 && (uint8_t)(_Char2) >= 0xA0) || (_Char1 == 0xED && (uint8_t)(_Char2) <= 0x9F);
}

const bool BFW_API BFW::String::IsValidUTF8MultiByte4FirstContinuation(const BFW_CHAR_TYPE_A _Char1, const BFW_CHAR_TYPE_A _Char2)
{
	return (_Char1 != 0xF0 && _Char1 != 0xF4) || (_Char1 == 0xF0 && (uint8_t)(_Char2) >= 0x90) || (_Char1 == 0xF4 && (uint8_t)(_Char2) <= 0x8F);
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

const uint32_t BFW_API BFW::String::CompositUnicodeSurrogates(const uint32_t _Char1, const uint32_t _Char2)
{
	return 0x10000 + ((uint32_t)(_Char1 - 0xD800) << 10) + (uint32_t)(_Char2 - 0xDC00);
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

BFW::Vector<BFW_CHAR_TYPE_A> BFW_API BFW::String::DeconstructUnicodePointA(const uint32_t _Char)
{
	Vector<BFW_CHAR_TYPE_A> _Chars;
	_Chars.Reserve(4);

	if (_Char <= 0x7F)
	{
		_Chars.PushBack((BFW_CHAR_TYPE_A)(_Char));
		return _Chars;
	}

	if (_Char <= 0x7FF)
	{
		_Chars.PushBack((BFW_CHAR_TYPE_A)(0xC0 | (_Char >> 6)));
		_Chars.PushBack((BFW_CHAR_TYPE_A)(0x80 | (_Char & 0x3F)));
		return _Chars;
	}

	if (_Char <= 0xFFFF)
	{
		_Chars.PushBack((BFW_CHAR_TYPE_A)(0xE0 | (_Char >> 12)));
		_Chars.PushBack((BFW_CHAR_TYPE_A)(0x80 | ((_Char >> 6) & 0x3F)));
		_Chars.PushBack((BFW_CHAR_TYPE_A)(0x80 | (_Char & 0x3F)));
		return _Chars;
	}

	_Chars.PushBack((BFW_CHAR_TYPE_A)(0xF0 | (_Char >> 18)));
	_Chars.PushBack((BFW_CHAR_TYPE_A)(0x80 | ((_Char >> 12) & 0x3F)));
	_Chars.PushBack((BFW_CHAR_TYPE_A)(0x80 | ((_Char >> 6) & 0x3F)));
	_Chars.PushBack((BFW_CHAR_TYPE_A)(0x80 | (_Char & 0x3F)));

	return _Chars;
}

#if defined BFW_WINDOWS_PLATFORM || defined BFW_ESP32_PLATFORM

BFW::Vector<BFW_CHAR_TYPE_W> BFW_API BFW::String::DeconstructUnicodePointW(const uint32_t _Char)
{
	Vector<BFW_CHAR_TYPE_W> _Chars;
	_Chars.Reserve(2);

	if (_Char <= 0xFFFF)
	{
		_Chars.PushBack((BFW_CHAR_TYPE_W)(_Char));
		return _Chars;
	}

	_Chars.PushBack((BFW_CHAR_TYPE_W)(0xD800 + ((_Char - 0x10000) >> 10)));
	_Chars.PushBack((BFW_CHAR_TYPE_W)(0xDC00 + ((_Char - 0x10000) & 0x3FF)));

	return _Chars;
}

#endif

#ifdef BFW_LINUX_PLATFORM

BFW::Vector<BFW_CHAR_TYPE_W> BFW_API BFW::String::DeconstructUnicodePointW(const uint32_t _Char)
{
	Vector<BFW_CHAR_TYPE_W> _Chars;
	_Chars.Reserve(2);

	_Chars.PushBack((BFW_CHAR_TYPE_W)(_Char));

	return _Chars;
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
#if defined BFW_WINDOWS_PLATFORM || defined BFW_ESP32_PLATFORM

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

			if (!IsValidUnicodePointW(CompositUnicodeSurrogates(_String[_Index - 1], _String[_Index])))
			{
				return false;
			}

			continue;
		}

#endif

#ifdef BFW_LINUX_PLATFORM

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
	return (uint8_t)(_Char) < 0x20;
}

const bool BFW_API BFW::String::IsControlCharacter(const BFW_CHAR_TYPE_W _Char)
{
	return (uint32_t)(_Char) < 0x20;
}

const bool BFW_API BFW::String::IsExtendedControlCharacter(const BFW_CHAR_TYPE_A _Char)
{
	return (uint8_t)(_Char) >= 0x80 && (uint8_t)(_Char) <= 0x9F;
}

const bool BFW_API BFW::String::IsExtendedControlCharacter(const BFW_CHAR_TYPE_W _Char)
{
	return (uint32_t)(_Char) >= 0x80 && (uint32_t)(_Char) <= 0x9F;
}
