#include "../Headers/BFW.hpp"



static const bool LoadJsonNull(const BFW::Assets::FileContent& _FileContent, size_t& _CurrentPos, BFW::Assets::Json& _Json)
{
	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != 'n')
	{
		return false;
	}

	_CurrentPos++;

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != 'u')
	{
		return false;
	}

	_CurrentPos++;

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != 'l')
	{
		return false;
	}

	_CurrentPos++;

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != 'l')
	{
		return false;
	}

	_CurrentPos++;

	_Json.SetNull();

	return true;
}

static const bool LoadJsonBool(const BFW::Assets::FileContent& _FileContent, size_t& _CurrentPos, BFW::Assets::Json& _Json)
{
	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != 't' && (const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != 'f')
	{
		return false;
	}

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == 't')
	{
		_CurrentPos++;

		if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != 'r')
		{
			return false;
		}

		_CurrentPos++;

		if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != 'u')
		{
			return false;
		}

		_CurrentPos++;

		if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != 'e')
		{
			return false;
		}

		_CurrentPos++;

		_Json.SetBool(true);

		return true;
	}

	_CurrentPos++;

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != 'a')
	{
		return false;
	}

	_CurrentPos++;

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != 'l')
	{
		return false;
	}

	_CurrentPos++;

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != 's')
	{
		return false;
	}

	_CurrentPos++;

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != 'e')
	{
		return false;
	}

	_CurrentPos++;

	_Json.SetBool(false);

	return true;
}

static const bool LoadJsonNumber(const BFW::Assets::FileContent& _FileContent, size_t& _CurrentPos, BFW::Assets::Json& _Json)
{
	bool _Negative = false;

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == '-')
	{
		_Negative = true;
		_CurrentPos++;
	}
	else if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == '+')
	{
		_CurrentPos++;
	}

	if (BFW_STRING_TYPE_A("e.0123456789").find((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])) == BFW_STRING_TYPE_A::npos || (const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == '\0')
	{
		return false;
	}

	float _Number = 0.0f;

	bool _FoundDot = false;
	float _NumberExponent = 1.0f;

	while (BFW_STRING_TYPE_A(".0123456789").find((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])) != BFW_STRING_TYPE_A::npos && (const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != '\0')
	{
		if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == '.')
		{
			if (_FoundDot)
			{
				return false;
			}

			_FoundDot = true;

			_CurrentPos++;
			continue;
		}

		if (_FoundDot)
		{
			_NumberExponent /= 10.0f;
			_Number += _NumberExponent * ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) - '0');

			_CurrentPos++;
			continue;
		}

		_Number *= 10;
		_Number += (const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) - '0';

		_CurrentPos++;
	}

	float _Exponent = 0.0f;

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == 'e')
	{
		_CurrentPos++;

		bool _NegativeExponent = false;

		if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == '-')
		{
			_NegativeExponent = true;
			_CurrentPos++;
		}
		else if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == '+')
		{
			_CurrentPos++;
		}

		bool _FoundExponentDot = false;
		float _ExponentExponent = 1.0f;

		while (BFW_STRING_TYPE_A(".0123456789").find((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])) != BFW_STRING_TYPE_A::npos && (const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != '\0')
		{
			if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == '.')
			{
				if (_FoundExponentDot)
				{
					return false;
				}

				_FoundExponentDot = true;

				_CurrentPos++;
				continue;
			}

			if (_FoundExponentDot)
			{
				_ExponentExponent /= 10.0f;
				_Exponent += _ExponentExponent * ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) - '0');

				_CurrentPos++;
				continue;
			}

			_Exponent *= 10;
			_Exponent += (const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) - '0';

			_CurrentPos++;
		}

		if (_NegativeExponent)
		{
			_Exponent = -_Exponent;
		}
	}

	if (_Negative)
	{
		_Json.SetNumber(-_Number * powf(10.0f, _Exponent));
	}
	else
	{
		_Json.SetNumber(_Number * powf(10.0f, _Exponent));
	}

	return true;
}

static const bool LoadJsonString(const BFW::Assets::FileContent& _FileContent, size_t& _CurrentPos, BFW::Assets::Json& _Json)
{
	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != '\"')
	{
		return false;
	}

	_CurrentPos++;

	BFW_STRING_TYPE_A _String;

	BFW_WINDOWS_PLATFORM_CALL(_String.reserve(64));
	BFW_LINUX_PLATFORM_CALL(_String.reserve(64));

	while ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != '\"')
	{
		if (BFW::String::IsControlCharacter((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
		{
			return false;
		}

		if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == '\\')
		{
			_CurrentPos++;

			switch ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]))
			{
			case '\"':
			{
				_String += '\"';
				break;
			}
			case '\\':
			{
				_String += '\\';
				break;
			}
			case '/':
			{
				_String += '/';
				break;
			}
			case 'b':
			{
				_String += '\b';
				break;
			}
			case 'f':
			{
				_String += '\f';
				break;
			}
			case 'n':
			{
				_String += '\n';
				break;
			}
			case 'r':
			{
				_String += '\r';
				break;
			}
			case 't':
			{
				_String += '\t';
				break;
			}
			case 'u':
			{
				BFW_CHAR_TYPE_W _WChar = L'\0';

				for (size_t _Index = 0; _Index < 4; _Index++)
				{
					_CurrentPos++;

					if (!BFW::String::IsHexA((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
					{
						return false;
					}

					_WChar = (_WChar << 4) + BFW::String::HexCharToNibbleA((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]));
				}

				if (BFW::String::IsUnicodeSurrogated(_WChar))
				{
					_CurrentPos++;

					if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != '\\')
					{
						return false;
					}

					_CurrentPos++;

					if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != 'u')
					{
						return false;
					}

					BFW_CHAR_TYPE_W _WChar2 = L'\0';

					for (size_t _Index = 0; _Index < 4; _Index++)
					{
						_CurrentPos++;

						if (!BFW::String::IsHexA((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
						{
							return false;
						}

						_WChar2 = (_WChar2 << 4) + BFW::String::HexCharToNibbleA((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]));
					}

					if (!BFW::String::IsUnicodeSurrogatedContinuation(_WChar2))
					{
						return false;
					}

					BFW_STRING_TYPE_W _WString = L"";
					_WString += _WChar;
					_WString += _WChar2;

					if (!BFW::String::IsValidUnicodeString(_WString))
					{
						return false;
					}

					bool _Error = false;
					_String += BFW::String::FromUnicodeToUTF8(_WString, &_Error);

					if (_Error)
					{
						return false;
					}

					break;
				}

				BFW_STRING_TYPE_W _WString = L"";
				_WString += _WChar;

				if (!BFW::String::IsValidUnicodeString(_WString))
				{
					return false;
				}

				bool _Error = false;
				_String += BFW::String::FromUnicodeToUTF8(_WString, &_Error);

				if (_Error)
				{
					return false;
				}

				break;
			}
			default:
			{
				return false;
			}
			}

			_CurrentPos++;
			continue;
		}

		_String += (const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]);

		_CurrentPos++;
	}

	_CurrentPos++;

	if (!BFW::String::IsValidUTF8String(_String))
	{
		return false;
	}

	_Json.SetString(_String);

	return true;
}

static const bool LoadJsonArray(const BFW::Assets::FileContent& _FileContent, size_t& _CurrentPos, BFW::Assets::Json& _Json);

static const bool LoadJsonObject(const BFW::Assets::FileContent& _FileContent, size_t& _CurrentPos, BFW::Assets::Json& _Json)
{
	_Json.SetObject();

	BFW::Assets::JsonObjectData& _ObjectData = _Json.GetObjectData();

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != '{')
	{
		return false;
	}

	_CurrentPos++;

	while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
	{
		_CurrentPos++;
	}

	while ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != '}')
	{
		BFW::Assets::Json _Tag;

		if (!LoadJsonString(_FileContent, _CurrentPos, _Tag))
		{
			return false;
		}

		BFW::Assets::Json& _TagObject = _ObjectData.Object.PushBack(BFW::Assets::Json());
		_ObjectData.Tags.PushBack(_Tag.GetString());

		while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
		{
			_CurrentPos++;
		}

		if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != ':')
		{
			return false;
		}

		_CurrentPos++;

		while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
		{
			_CurrentPos++;
		}

		switch ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]))
		{
		case 'n':
		{
			if (!LoadJsonNull(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case 't':
		{
			if (!LoadJsonBool(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case 'f':
		{
			if (!LoadJsonBool(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case '.':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case '0':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case '1':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case '2':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case '3':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case '4':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case '5':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case '6':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case '7':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case '8':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case '9':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case '\"':
		{
			if (!LoadJsonString(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case '{':
		{
			if (!LoadJsonObject(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case '[':
		{
			if (!LoadJsonArray(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		default:
		{
			return false;
		}
		}

		while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
		{
			_CurrentPos++;
		}

		if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != ',' && (const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != '}')
		{
			return false;
		}

		if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == ',')
		{
			_CurrentPos++;

			while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
			{
				_CurrentPos++;
			}

			if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == '}')
			{
				return false;
			}

			continue;
		}
	}

	_CurrentPos++;

	return true;
}

static const bool LoadJsonArray(const BFW::Assets::FileContent& _FileContent, size_t& _CurrentPos, BFW::Assets::Json& _Json)
{
	_Json.SetArray();

	BFW::Vector<BFW::Assets::Json>& _Array = _Json.GetArray();

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != '[')
	{
		return false;
	}

	_CurrentPos++;

	while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
	{
		_CurrentPos++;
	}

	while ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != ']')
	{
		BFW::Assets::Json& _Object = _Array.EmplaceBack(BFW::Assets::Json());

		switch ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]))
		{
		case 'n':
		{
			if (!LoadJsonNull(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case 't':
		{
			if (!LoadJsonBool(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case 'f':
		{
			if (!LoadJsonBool(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case '.':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case '0':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case '1':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case '2':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case '3':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case '4':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case '5':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case '6':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case '7':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case '8':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case '9':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case '\"':
		{
			if (!LoadJsonString(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case '{':
		{
			if (!LoadJsonObject(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case '[':
		{
			if (!LoadJsonArray(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		default:
		{
			return false;
		}
		}

		while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
		{
			_CurrentPos++;
		}

		if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != ',' && (const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != ']')
		{
			return false;
		}

		if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == ',')
		{
			_CurrentPos++;

			while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
			{
				_CurrentPos++;
			}

			if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == ']')
			{
				return false;
			}

			continue;
		}
	}

	_CurrentPos++;

	return true;
}

static void SaveJsonNull(size_t& _TabLevel, BFW_STRING_STREAM_TYPE_A& _Stream, const BFW::Assets::Json& _Json)
{
	_Stream << "null";
}

static void SaveJsonBool(size_t& _TabLevel, BFW_STRING_STREAM_TYPE_A& _Stream, const BFW::Assets::Json& _Json)
{
	if (_Json.GetBool())
	{
		_Stream << "true";
	}
	else
	{
		_Stream << "false";
	}
}

static void SaveJsonNumber(size_t& _TabLevel, BFW_STRING_STREAM_TYPE_A& _Stream, const BFW::Assets::Json& _Json)
{
	if (std::isnan(_Json.GetNumber()))
	{
		_Stream << 0.0f;
		return;
	}

	if (!std::isfinite(_Json.GetNumber()) && _Json.GetNumber() < 0.0f)
	{
		_Stream << std::numeric_limits<float>::max();
		return;
	}

	if (!std::isfinite(_Json.GetNumber()) && _Json.GetNumber() > 0.0f)
	{
		_Stream << std::numeric_limits<float>::min();
		return;
	}

	_Stream << _Json.GetNumber();
}

static const bool SaveJsonString(size_t& _TabLevel, BFW_STRING_STREAM_TYPE_A& _Stream, const BFW::Assets::Json& _Json)
{
	_Stream << '\"';

	BFW_STRING_TYPE_A _String = _Json.GetString();

	if (!BFW::String::IsValidUTF8String(_String))
	{
		return false;
	}

	for (size_t _Index = 0; _Index < _String.size(); _Index++)
	{
		if (_String[_Index] == '\"')
		{
			_Stream << '\\' << '\"';
			continue;
		}

		if (_String[_Index] == '\\')
		{
			_Stream << '\\' << '\\';
			continue;
		}

		if (_String[_Index] == '\b')
		{
			_Stream << '\\' << 'b';
			continue;
		}

		if (_String[_Index] == '\f')
		{
			_Stream << '\\' << 'f';
			continue;
		}

		if (_String[_Index] == '\n')
		{
			_Stream << '\\' << 'n';
			continue;
		}

		if (_String[_Index] == '\r')
		{
			_Stream << '\\' << 'r';
			continue;
		}

		if (_String[_Index] == '\t')
		{
			_Stream << '\\' << 't';
			continue;
		}

		if (BFW::String::IsControlCharacter(_String[_Index]))
		{
			return false;
		}

		_Stream << _String[_Index];
	}

	_Stream << '\"';

	return true;
}

static const bool SaveJsonArray(size_t& _TabLevel, BFW_STRING_STREAM_TYPE_A& _Stream, const BFW::Assets::Json& _Json);

static const bool SaveJsonObject(size_t& _TabLevel, BFW_STRING_STREAM_TYPE_A& _Stream, const BFW::Assets::Json& _Json)
{
	_Stream << '{' BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';

	_TabLevel++;

	const BFW::Assets::JsonObjectData& _ObjectData = _Json.GetObjectData();

	for (size_t _Index = 0; _Index < _ObjectData.Tags.GetSize(); _Index++)
	{
		BFW::Assets::Json _Tag;

		_Tag.SetString(_ObjectData.Tags[_Index]);

		for (size_t _Index = 0; _Index < _TabLevel; _Index++)
		{
			_Stream << '\t';
		}

		if (!SaveJsonString(_TabLevel, _Stream, _Tag))
		{
			return false;
		}

		_Stream << ":";

		const BFW::Assets::Json& _CurrentJson = _ObjectData.Object[_Index];

		if (_CurrentJson.GetType() == BFW::Assets::_ObjectJsonType || _CurrentJson.GetType() == BFW::Assets::_ArrayJsonType)
		{
			_Stream BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';

			for (size_t _Index = 0; _Index < _TabLevel; _Index++)
			{
				_Stream << '\t';
			}
		}
		else
		{
			_Stream << ' ';
		}

		switch (_CurrentJson.GetType())
		{
		case BFW::Assets::_NullJsonType:
		{
			SaveJsonNull(_TabLevel, _Stream, _CurrentJson);
			break;
		}
		case BFW::Assets::_BoolJsonType:
		{
			SaveJsonBool(_TabLevel, _Stream, _CurrentJson);
			break;
		}
		case BFW::Assets::_NumberJsonType:
		{
			SaveJsonNumber(_TabLevel, _Stream, _CurrentJson);
			break;
		}
		case BFW::Assets::_StringJsonType:
		{
			if (!SaveJsonString(_TabLevel, _Stream, _CurrentJson))
			{
				return false;
			}

			break;
		}
		case BFW::Assets::_ObjectJsonType:
		{
			if (!SaveJsonObject(_TabLevel, _Stream, _CurrentJson))
			{
				return false;
			}

			break;
		}
		case BFW::Assets::_ArrayJsonType:
		{
			if (!SaveJsonArray(_TabLevel, _Stream, _CurrentJson))
			{
				return false;
			}

			break;
		}
		default:
		{
			break;
		}
		}

		if (_Index != _ObjectData.Tags.GetSize() - 1)
		{
			_Stream << ',';
		}

		_Stream BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
	}

	_TabLevel--;

	for (size_t _Index = 0; _Index < _TabLevel; _Index++)
	{
		_Stream << '\t';
	}

	_Stream << '}';

	return true;
}

static const bool SaveJsonArray(size_t& _TabLevel, BFW_STRING_STREAM_TYPE_A& _Stream, const BFW::Assets::Json& _Json)
{
	_Stream << '[' BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';

	_TabLevel++;

	const BFW::Vector<BFW::Assets::Json>& _Array = _Json.GetArray();

	for (size_t _Index = 0; _Index < _Array.GetSize(); _Index++)
	{
		for (size_t _Index = 0; _Index < _TabLevel; _Index++)
		{
			_Stream << '\t';
		}

		const BFW::Assets::Json& _CurrentJson = _Array[_Index];

		switch (_CurrentJson.GetType())
		{
		case BFW::Assets::_NullJsonType:
		{
			SaveJsonNull(_TabLevel, _Stream, _CurrentJson);
			break;
		}
		case BFW::Assets::_BoolJsonType:
		{
			SaveJsonBool(_TabLevel, _Stream, _CurrentJson);
			break;
		}
		case BFW::Assets::_NumberJsonType:
		{
			SaveJsonNumber(_TabLevel, _Stream, _CurrentJson);
			break;
		}
		case BFW::Assets::_StringJsonType:
		{
			if (!SaveJsonString(_TabLevel, _Stream, _CurrentJson))
			{
				return false;
			}

			break;
		}
		case BFW::Assets::_ObjectJsonType:
		{
			if (!SaveJsonObject(_TabLevel, _Stream, _CurrentJson))
			{
				return false;
			}

			break;
		}
		case BFW::Assets::_ArrayJsonType:
		{
			if (!SaveJsonArray(_TabLevel, _Stream, _CurrentJson))
			{
				return false;
			}

			break;
		}
		default:
		{
			break;
		}
		}

		if (_Index != _Array.GetSize() - 1)
		{
			_Stream << ',';
		}

		_Stream BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
	}

	_TabLevel--;

	for (size_t _Index = 0; _Index < _TabLevel; _Index++)
	{
		_Stream << '\t';
	}

	_Stream << ']';

	return true;
}



BFW::Assets::JsonObjectData::JsonObjectData() : Object(), Tags()
{

}

BFW::Assets::JsonObjectData::JsonObjectData(const JsonObjectData& _Other) : Object(_Other.Object), Tags(_Other.Tags)
{

}

BFW::Assets::JsonObjectData::JsonObjectData(JsonObjectData&& _Other) noexcept : Object((Vector<Json>&&)(_Other.Object)), Tags((Vector<BFW_STRING_TYPE_A>&&)(_Other.Tags))
{

}

BFW::Assets::JsonObjectData::~JsonObjectData()
{

}

BFW::Assets::Json& BFW::Assets::JsonObjectData::operator[] (const BFW_CHAR_TYPE_A* _Tag)
{
	for (size_t _Index = 0; _Index < Tags.GetSize(); _Index++)
	{
		if (Tags[_Index] == _Tag)
		{
			return Object[_Index];
		}
	}

	throw nullptr;
}

const BFW::Assets::Json& BFW::Assets::JsonObjectData::operator[] (const BFW_CHAR_TYPE_A* _Tag) const
{
	for (size_t _Index = 0; _Index < Tags.GetSize(); _Index++)
	{
		if (Tags[_Index] == _Tag)
		{
			return Object[_Index];
		}
	}

	throw nullptr;
}

BFW::Assets::JsonObjectData& BFW::Assets::JsonObjectData::operator= (const JsonObjectData& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Object = _Other.Object;
	Tags = _Other.Tags;

	return *this;
}

BFW::Assets::JsonObjectData& BFW::Assets::JsonObjectData::operator= (JsonObjectData&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Object = (Vector<Json>&&)(_Other.Object);
	Tags = (Vector<BFW_STRING_TYPE_A>&&)(_Other.Tags);

	return *this;
}



BFW::Assets::Json::Json() : Type(_NullJsonType), BoolValue(false), NumberValue(0.0f), StringValue(""), ArrayValue(), ObjectDataValue()
{

}

BFW::Assets::Json::Json(const Json& _Other) : Type(_Other.Type), BoolValue(_Other.BoolValue), NumberValue(_Other.NumberValue), StringValue(_Other.StringValue), ArrayValue(_Other.ArrayValue), ObjectDataValue(_Other.ObjectDataValue)
{

}

BFW::Assets::Json::Json(Json&& _Other) noexcept : Type(_Other.Type), BoolValue(_Other.BoolValue), NumberValue(_Other.NumberValue), StringValue(_Other.StringValue), ArrayValue((Vector<Json>&&)(_Other.ArrayValue)), ObjectDataValue((JsonObjectData&&)(_Other.ObjectDataValue))
{
	_Other.Type = _NullJsonType;
	_Other.BoolValue = false;
	_Other.NumberValue = 0.0f;
	_Other.StringValue = "";
}

BFW::Assets::Json::~Json()
{

}

const bool BFW::Assets::Json::Load(const FileContent& _FileContent)
{
	*this = Json();

	if (!_FileContent.GetData() || (const BFW_CHAR_TYPE_A)(_FileContent[_FileContent.GetLength() - 1]) != '\0')
	{
		return false;
	}

	size_t _CurrentPos = 0;

	while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
	{
		_CurrentPos++;
	}

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != '{' && (const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != '[')
	{
		return false;
	}

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == '{')
	{
		if (!LoadJsonObject(_FileContent, _CurrentPos, *this))
		{
			*this = Json();
			return false;
		}
	}

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == '[')
	{
		if (!LoadJsonArray(_FileContent, _CurrentPos, *this))
		{
			*this = Json();
			return false;
		}
	}

	while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
	{
		_CurrentPos++;
	}

	if (_CurrentPos != _FileContent.GetLength() - 1)
	{
		*this = Json();
		return false;
	}

	return true;
}

void BFW::Assets::Json::SetNull()
{
	Type = _NullJsonType;
	BoolValue = false;
	NumberValue = 0.0f;
	StringValue = "";
	ArrayValue = Vector<Json>();
	ObjectDataValue = JsonObjectData();
}

void BFW::Assets::Json::SetBool(const bool _BoolValue)
{
	Type = _BoolJsonType;
	BoolValue = _BoolValue;
	NumberValue = 0.0f;
	StringValue = "";
	ArrayValue = Vector<Json>();
	ObjectDataValue = JsonObjectData();
}

void BFW::Assets::Json::SetNumber(const float _NumberValue)
{
	Type = _NumberJsonType;
	BoolValue = false;
	NumberValue = _NumberValue;
	StringValue = "";
	ArrayValue = Vector<Json>();
	ObjectDataValue = JsonObjectData();
}

void BFW::Assets::Json::SetString(const BFW_STRING_VIEW_TYPE_A& _StringValue)
{
	Type = _StringJsonType;
	BoolValue = false;
	NumberValue = 0.0f;
	StringValue = _StringValue;
	ArrayValue = Vector<Json>();
	ObjectDataValue = JsonObjectData();
}

void BFW::Assets::Json::SetArray()
{
	Type = _ArrayJsonType;
	BoolValue = false;
	NumberValue = 0.0f;
	StringValue = "";
	ArrayValue = Vector<Json>();
	ObjectDataValue = JsonObjectData();
}

void BFW::Assets::Json::SetObject()
{
	Type = _ObjectJsonType;
	BoolValue = false;
	NumberValue = 0.0f;
	StringValue = "";
	ArrayValue = Vector<Json>();
	ObjectDataValue = JsonObjectData();
}

BFW::Assets::FileContent BFW::Assets::Json::Save() const
{
	if (Type != _ObjectJsonType && Type != _ArrayJsonType)
	{
		return FileContent();
	}

	size_t _TabLevel = 0;
	BFW_STRING_STREAM_TYPE_A _Stream;

	_Stream.imbue(std::locale::classic());

	if (Type == _ObjectJsonType)
	{
		if (!SaveJsonObject(_TabLevel, _Stream, *this))
		{
			return FileContent();
		}
	}

	if (Type == _ArrayJsonType)
	{
		if (!SaveJsonArray(_TabLevel, _Stream, *this))
		{
			return FileContent();
		}
	}

	_Stream BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';

	if (!_Stream)
	{
		return FileContent();
	}

	BFW_STRING_TYPE_A _String = _Stream.str();

	FileContent _FileContent;

	if (!_FileContent.Create(_String.size() + 1))
	{
		return FileContent();
	}

	_FileContent[_FileContent.GetLength() - 1] = '\0';

	for (size_t _Index = 0; _Index < _String.size(); _Index++)
	{
		_FileContent[_Index] = _String[_Index];
	}

	return _FileContent;
}

const uint8_t BFW::Assets::Json::GetType() const
{
	return Type;
}

const bool BFW::Assets::Json::GetBool() const
{
	if (Type != _BoolJsonType)
	{
		throw nullptr;
	}

	return BoolValue;
}

const float BFW::Assets::Json::GetNumber() const
{
	if (Type != _NumberJsonType)
	{
		throw nullptr;
	}

	return NumberValue;
}

const BFW_STRING_TYPE_A& BFW::Assets::Json::GetString() const
{
	if (Type != _StringJsonType)
	{
		throw nullptr;
	}

	return StringValue;
}

BFW::Vector<BFW::Assets::Json>& BFW::Assets::Json::GetArray()
{
	if (Type != _ArrayJsonType)
	{
		throw nullptr;
	}

	return ArrayValue;
}

const BFW::Vector<BFW::Assets::Json>& BFW::Assets::Json::GetArray() const
{
	if (Type != _ArrayJsonType)
	{
		throw nullptr;
	}

	return ArrayValue;
}

BFW::Assets::JsonObjectData& BFW::Assets::Json::GetObjectData()
{
	if (Type != _ObjectJsonType)
	{
		throw nullptr;
	}

	return ObjectDataValue;
}

const BFW::Assets::JsonObjectData& BFW::Assets::Json::GetObjectData() const
{
	if (Type != _ObjectJsonType)
	{
		throw nullptr;
	}

	return ObjectDataValue;
}

BFW::Assets::Json& BFW::Assets::Json::operator= (const Json& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Type = _Other.Type;
	BoolValue = _Other.BoolValue;
	NumberValue = _Other.NumberValue;
	StringValue = _Other.StringValue;
	ArrayValue = _Other.ArrayValue;
	ObjectDataValue = _Other.ObjectDataValue;

	return *this;
}

BFW::Assets::Json& BFW::Assets::Json::operator= (Json&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Type = _Other.Type;
	BoolValue = _Other.BoolValue;
	NumberValue = _Other.NumberValue;
	StringValue = _Other.StringValue;
	ArrayValue = (Vector<Json>&&)(_Other.ArrayValue);
	ObjectDataValue = (JsonObjectData&&)(_Other.ObjectDataValue);

	_Other.Type = _NullJsonType;
	_Other.BoolValue = false;
	_Other.NumberValue = 0.0f;
	_Other.StringValue = "";

	return *this;
}
