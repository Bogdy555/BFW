#include "../Headers/BFW.hpp"



#pragma pack(push, 1)

struct BitMapFileHeader
{

	BFW_CHAR_TYPE_A Type[2];
	uint32_t Size;
	uint16_t Reserved1;
	uint16_t Reserved2;
	uint32_t Offset;

	BitMapFileHeader();
	BitMapFileHeader(const BitMapFileHeader& _Other) = default;
	BitMapFileHeader(BitMapFileHeader&& _Other) noexcept;
	~BitMapFileHeader();
	BitMapFileHeader& operator= (const BitMapFileHeader& _Other) = default;
	BitMapFileHeader& operator= (BitMapFileHeader&& _Other) noexcept;

};

struct BitMapInfoHeader
{

	uint32_t Size;
	uint32_t Width;
	int32_t Height;
	uint16_t Planes;
	uint16_t BitCount;
	uint32_t Compression;
	uint32_t ImageSize;
	uint32_t DPIX;
	uint32_t DPIY;
	uint32_t ColorsUsed;
	uint32_t ColorsImportant;

	BitMapInfoHeader();
	BitMapInfoHeader(const BitMapInfoHeader& _Other) = default;
	BitMapInfoHeader(BitMapInfoHeader& _Other) noexcept;
	~BitMapInfoHeader();
	BitMapInfoHeader& operator= (const BitMapInfoHeader& _Other) = default;
	BitMapInfoHeader& operator= (BitMapInfoHeader& _Other) noexcept;

};

struct WaveFileHeader
{

	BFW_CHAR_TYPE_A RIFF[4];
	uint32_t FileSize;
	BFW_CHAR_TYPE_A WAVE[4];

	WaveFileHeader();
	WaveFileHeader(const WaveFileHeader& _Other) = default;
	WaveFileHeader(WaveFileHeader&& _Other) noexcept;
	~WaveFileHeader();
	WaveFileHeader& operator= (const WaveFileHeader& _Other) = default;
	WaveFileHeader& operator= (WaveFileHeader&& _Other) noexcept;

};

struct WaveChunkHeader
{

	BFW_CHAR_TYPE_A ID[4];
	uint32_t Size;

	WaveChunkHeader();
	WaveChunkHeader(const WaveChunkHeader& _Other) = default;
	WaveChunkHeader(WaveChunkHeader& _Other) noexcept;
	~WaveChunkHeader();
	WaveChunkHeader& operator= (const WaveChunkHeader& _Other) = default;
	WaveChunkHeader& operator= (WaveChunkHeader& _Other) noexcept;

};

#pragma pack(pop)



BitMapFileHeader::BitMapFileHeader() : Type(), Size(0), Reserved1(0), Reserved2(0), Offset(0)
{
	Type[0] = '\0';
	Type[1] = '\0';
}

BitMapFileHeader::BitMapFileHeader(BitMapFileHeader&& _Other) noexcept : Type(), Size(_Other.Size), Reserved1(_Other.Reserved1), Reserved2(_Other.Reserved2), Offset(_Other.Offset)
{
	Type[0] = _Other.Type[0];
	Type[1] = _Other.Type[1];

	_Other.Type[0] = '\0';
	_Other.Type[1] = '\0';
	_Other.Size = 0;
	_Other.Reserved1 = 0;
	_Other.Reserved2 = 0;
	_Other.Offset = 0;
}

BitMapFileHeader::~BitMapFileHeader()
{

}

BitMapFileHeader& BitMapFileHeader::operator= (BitMapFileHeader&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Type[0] = _Other.Type[0];
	Type[1] = _Other.Type[1];
	Size = _Other.Size;
	Reserved1 = _Other.Reserved1;
	Reserved2 = _Other.Reserved2;
	Offset = _Other.Offset;

	_Other.Type[0] = '\0';
	_Other.Type[1] = '\0';
	_Other.Size = 0;
	_Other.Reserved1 = 0;
	_Other.Reserved2 = 0;
	_Other.Offset = 0;

	return *this;
}



BitMapInfoHeader::BitMapInfoHeader() : Size(0), Width(0), Height(0), Planes(0), BitCount(0), Compression(0), ImageSize(0), DPIX(0), DPIY(0), ColorsUsed(0), ColorsImportant(0)
{

}

BitMapInfoHeader::BitMapInfoHeader(BitMapInfoHeader& _Other) noexcept : Size(_Other.Size), Width(_Other.Width), Height(_Other.Height), Planes(_Other.Planes), BitCount(_Other.BitCount), Compression(_Other.Compression), ImageSize(_Other.ImageSize), DPIX(_Other.DPIX), DPIY(_Other.DPIY), ColorsUsed(_Other.ColorsUsed), ColorsImportant(_Other.ColorsImportant)
{
	_Other.Size = 0;
	_Other.Width = 0;
	_Other.Height = 0;
	_Other.Planes = 0;
	_Other.BitCount = 0;
	_Other.Compression = 0;
	_Other.ImageSize = 0;
	_Other.DPIX = 0;
	_Other.DPIY = 0;
	_Other.ColorsUsed = 0;
	_Other.ColorsImportant = 0;
}

BitMapInfoHeader::~BitMapInfoHeader()
{

}

BitMapInfoHeader& BitMapInfoHeader::operator= (BitMapInfoHeader& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Size = _Other.Size;
	Width = _Other.Width;
	Height = _Other.Height;
	Planes = _Other.Planes;
	BitCount = _Other.BitCount;
	Compression = _Other.Compression;
	ImageSize = _Other.ImageSize;
	DPIX = _Other.DPIX;
	DPIY = _Other.DPIY;
	ColorsUsed = _Other.ColorsUsed;
	ColorsImportant = _Other.ColorsImportant;

	_Other.Size = 0;
	_Other.Width = 0;
	_Other.Height = 0;
	_Other.Planes = 0;
	_Other.BitCount = 0;
	_Other.Compression = 0;
	_Other.ImageSize = 0;
	_Other.DPIX = 0;
	_Other.DPIY = 0;
	_Other.ColorsUsed = 0;
	_Other.ColorsImportant = 0;

	return *this;
}



WaveFileHeader::WaveFileHeader() : RIFF(), FileSize(0), WAVE()
{
	RIFF[0] = '\0';
	RIFF[1] = '\0';
	RIFF[2] = '\0';
	RIFF[3] = '\0';
	WAVE[0] = '\0';
	WAVE[1] = '\0';
	WAVE[2] = '\0';
	WAVE[3] = '\0';
}

WaveFileHeader::WaveFileHeader(WaveFileHeader&& _Other) noexcept : RIFF(), FileSize(_Other.FileSize), WAVE()
{
	RIFF[0] = _Other.RIFF[0];
	RIFF[1] = _Other.RIFF[1];
	RIFF[2] = _Other.RIFF[2];
	RIFF[3] = _Other.RIFF[3];
	WAVE[0] = _Other.WAVE[0];
	WAVE[1] = _Other.WAVE[1];
	WAVE[2] = _Other.WAVE[2];
	WAVE[3] = _Other.WAVE[3];

	_Other.RIFF[0] = '\0';
	_Other.RIFF[1] = '\0';
	_Other.RIFF[2] = '\0';
	_Other.RIFF[3] = '\0';
	_Other.FileSize = 0;
	_Other.WAVE[0] = '\0';
	_Other.WAVE[1] = '\0';
	_Other.WAVE[2] = '\0';
	_Other.WAVE[3] = '\0';
}

WaveFileHeader::~WaveFileHeader()
{

}

WaveFileHeader& WaveFileHeader::operator= (WaveFileHeader&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	RIFF[0] = _Other.RIFF[0];
	RIFF[1] = _Other.RIFF[1];
	RIFF[2] = _Other.RIFF[2];
	RIFF[3] = _Other.RIFF[3];
	FileSize = _Other.FileSize;
	WAVE[0] = _Other.WAVE[0];
	WAVE[1] = _Other.WAVE[1];
	WAVE[2] = _Other.WAVE[2];
	WAVE[3] = _Other.WAVE[3];

	_Other.RIFF[0] = '\0';
	_Other.RIFF[1] = '\0';
	_Other.RIFF[2] = '\0';
	_Other.RIFF[3] = '\0';
	_Other.FileSize = 0;
	_Other.WAVE[0] = '\0';
	_Other.WAVE[1] = '\0';
	_Other.WAVE[2] = '\0';
	_Other.WAVE[3] = '\0';

	return *this;
}



WaveChunkHeader::WaveChunkHeader() : ID(), Size(0)
{
	ID[0] = '\0';
	ID[1] = '\0';
	ID[2] = '\0';
	ID[3] = '\0';
}

WaveChunkHeader::WaveChunkHeader(WaveChunkHeader& _Other) noexcept : ID(), Size(_Other.Size)
{
	ID[0] = _Other.ID[0];
	ID[1] = _Other.ID[1];
	ID[2] = _Other.ID[2];
	ID[3] = _Other.ID[3];

	_Other.ID[0] = '\0';
	_Other.ID[1] = '\0';
	_Other.ID[2] = '\0';
	_Other.ID[3] = '\0';
	_Other.Size = 0;
}

WaveChunkHeader::~WaveChunkHeader()
{

}

WaveChunkHeader& WaveChunkHeader::operator= (WaveChunkHeader& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	ID[0] = _Other.ID[0];
	ID[1] = _Other.ID[1];
	ID[2] = _Other.ID[2];
	ID[3] = _Other.ID[3];
	Size = _Other.Size;

	_Other.ID[0] = '\0';
	_Other.ID[1] = '\0';
	_Other.ID[2] = '\0';
	_Other.ID[3] = '\0';
	_Other.Size = 0;

	return *this;
}



static const bool LoadJsonNull(const BFW::FileSystem::FileContent& _FileContent, size_t& _CurrentPos, BFW::Assets::Json& _Json)
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

static const bool LoadJsonBool(const BFW::FileSystem::FileContent& _FileContent, size_t& _CurrentPos, BFW::Assets::Json& _Json)
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

static const bool LoadJsonNumber(const BFW::FileSystem::FileContent& _FileContent, size_t& _CurrentPos, BFW::Assets::Json& _Json)
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

static const bool LoadJsonString(const BFW::FileSystem::FileContent& _FileContent, size_t& _CurrentPos, BFW::Assets::Json& _Json)
{
	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != '\"')
	{
		return false;
	}

	_CurrentPos++;

	BFW_STRING_TYPE_W _String;

	while ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != '\"')
	{
		if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) <= 0x1F)
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
				_String += L'\"';
				break;
			}
			case '\\':
			{
				_String += L'\\';
				break;
			}
			case '/':
			{
				_String += L'/';
				break;
			}
			case 'b':
			{
				_String += L'\b';
				break;
			}
			case 'f':
			{
				_String += L'\f';
				break;
			}
			case 'n':
			{
				_String += L'\n';
				break;
			}
			case 'r':
			{
				_String += L'\r';
				break;
			}
			case 't':
			{
				_String += L'\t';
				break;
			}
			case 'u':
			{
				BFW_CHAR_TYPE_W _WChar = L'\0';

				_CurrentPos++;

				if (BFW_STRING_TYPE_A("0123456789ABCDEFabcdef").find((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])) == BFW_STRING_TYPE_A::npos || (const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == '\0')
				{
					return false;
				}

				if (BFW_STRING_TYPE_A("ABCDEF").find((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])) != BFW_STRING_TYPE_A::npos)
				{
					_WChar = (_WChar << 4) + ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) - 'A' + 10);
				}
				else if (BFW_STRING_TYPE_A("abcdef").find((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])) != BFW_STRING_TYPE_A::npos)
				{
					_WChar = (_WChar << 4) + ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) - 'a' + 10);
				}
				else
				{
					_WChar = (_WChar << 4) + ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) - '0');
				}

				_CurrentPos++;

				if (BFW_STRING_TYPE_A("0123456789ABCDEFabcdef").find((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])) == BFW_STRING_TYPE_A::npos || (const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == '\0')
				{
					return false;
				}

				if (BFW_STRING_TYPE_A("ABCDEF").find((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])) != BFW_STRING_TYPE_A::npos)
				{
					_WChar = (_WChar << 4) + ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) - 'A' + 10);
				}
				else if (BFW_STRING_TYPE_A("abcdef").find((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])) != BFW_STRING_TYPE_A::npos)
				{
					_WChar = (_WChar << 4) + ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) - 'a' + 10);
				}
				else
				{
					_WChar = (_WChar << 4) + ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) - '0');
				}

				_CurrentPos++;

				if (BFW_STRING_TYPE_A("0123456789ABCDEFabcdef").find((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])) == BFW_STRING_TYPE_A::npos || (const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == '\0')
				{
					return false;
				}

				if (BFW_STRING_TYPE_A("ABCDEF").find((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])) != BFW_STRING_TYPE_A::npos)
				{
					_WChar = (_WChar << 4) + ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) - 'A' + 10);
				}
				else if (BFW_STRING_TYPE_A("abcdef").find((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])) != BFW_STRING_TYPE_A::npos)
				{
					_WChar = (_WChar << 4) + ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) - 'a' + 10);
				}
				else
				{
					_WChar = (_WChar << 4) + ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) - '0');
				}

				_CurrentPos++;

				if (BFW_STRING_TYPE_A("0123456789ABCDEFabcdef").find((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])) == BFW_STRING_TYPE_A::npos || (const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == '\0')
				{
					return false;
				}

				if (BFW_STRING_TYPE_A("ABCDEF").find((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])) != BFW_STRING_TYPE_A::npos)
				{
					_WChar = (_WChar << 4) + ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) - 'A' + 10);
				}
				else if (BFW_STRING_TYPE_A("abcdef").find((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])) != BFW_STRING_TYPE_A::npos)
				{
					_WChar = (_WChar << 4) + ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) - 'a' + 10);
				}
				else
				{
					_WChar = (_WChar << 4) + ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) - '0');
				}

				_String += _WChar;

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

		_String += (const BFW_CHAR_TYPE_W)((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]));

		_CurrentPos++;
	}

	_CurrentPos++;

	bool _Error = false;
	BFW_STRING_TYPE_A _FinalString = BFW::String::FromUnicodeToUTF8(_String, &_Error);

	if (_Error)
	{
		return false;
	}

	_Json.SetString(_FinalString);

	return true;
}

static const bool LoadJsonArray(const BFW::FileSystem::FileContent& _FileContent, size_t& _CurrentPos, BFW::Assets::Json& _Json);

static const bool LoadJsonObject(const BFW::FileSystem::FileContent& _FileContent, size_t& _CurrentPos, BFW::Assets::Json& _Json)
{
	_Json.SetObject();

	BFW::Assets::JsonObjectData& _ObjectData = _Json.GetObjectData();

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != '{')
	{
		return false;
	}

	_CurrentPos++;

	while (std::isspace((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
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

		while (std::isspace((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
		{
			_CurrentPos++;
		}

		if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != ':')
		{
			return false;
		}

		_CurrentPos++;

		while (std::isspace((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
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

		while (std::isspace((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
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

			while (std::isspace((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
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

static const bool LoadJsonArray(const BFW::FileSystem::FileContent& _FileContent, size_t& _CurrentPos, BFW::Assets::Json& _Json)
{
	_Json.SetArray();

	BFW::Vector<BFW::Assets::Json>& _Array = _Json.GetArray();

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != '[')
	{
		return false;
	}

	_CurrentPos++;

	while (std::isspace((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
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

		while (std::isspace((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
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

			while (std::isspace((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
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

static void SaveJsonString(size_t& _TabLevel, BFW_STRING_STREAM_TYPE_A& _Stream, const BFW::Assets::Json& _Json)
{
	_Stream << '\"';

	BFW_STRING_TYPE_A _String = _Json.GetString();

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

		if (_String[_Index] <= 0x1F)
		{
			continue;
		}

		_Stream << _String[_Index];
	}

	_Stream << '\"';
}

static void SaveJsonArray(size_t& _TabLevel, BFW_STRING_STREAM_TYPE_A& _Stream, const BFW::Assets::Json& _Json);

static void SaveJsonObject(size_t& _TabLevel, BFW_STRING_STREAM_TYPE_A& _Stream, const BFW::Assets::Json& _Json)
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

		SaveJsonString(_TabLevel, _Stream, _Tag);

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
			SaveJsonString(_TabLevel, _Stream, _CurrentJson);
			break;
		}
		case BFW::Assets::_ObjectJsonType:
		{
			SaveJsonObject(_TabLevel, _Stream, _CurrentJson);
			break;
		}
		case BFW::Assets::_ArrayJsonType:
		{
			SaveJsonArray(_TabLevel, _Stream, _CurrentJson);
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
}

static void SaveJsonArray(size_t& _TabLevel, BFW_STRING_STREAM_TYPE_A& _Stream, const BFW::Assets::Json& _Json)
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
			SaveJsonString(_TabLevel, _Stream, _CurrentJson);
			break;
		}
		case BFW::Assets::_ObjectJsonType:
		{
			SaveJsonObject(_TabLevel, _Stream, _CurrentJson);
			break;
		}
		case BFW::Assets::_ArrayJsonType:
		{
			SaveJsonArray(_TabLevel, _Stream, _CurrentJson);
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
}



BFW::Assets::BitMap::BitMap() : Data(nullptr), ChannelsCount(0), Width(0), Height(0)
{

}

BFW::Assets::BitMap::BitMap(const BitMap& _Other) : Data(nullptr), ChannelsCount(0), Width(0), Height(0)
{
	if (!_Other.Data)
	{
		return;
	}

	Data = new uint8_t[_Other.Width * _Other.Height * _Other.ChannelsCount];

	if (!Data)
	{
		throw nullptr;
	}

	ChannelsCount = _Other.ChannelsCount;
	Width = _Other.Width;
	Height = _Other.Height;

	for (size_t _Index = 0; _Index < Width * Height * ChannelsCount; _Index++)
	{
		Data[_Index] = _Other.Data[_Index];
	}
}

BFW::Assets::BitMap::BitMap(BitMap&& _Other) noexcept : Data(_Other.Data), ChannelsCount(_Other.ChannelsCount), Width(_Other.Width), Height(_Other.Height)
{
	_Other.Data = nullptr;
	_Other.ChannelsCount = 0;
	_Other.Width = 0;
	_Other.Height = 0;
}

BFW::Assets::BitMap::~BitMap()
{
	delete[] Data;
}

const bool BFW::Assets::BitMap::Create(const size_t _Width, const size_t _Height, const size_t _ChannelsCount)
{
	Destroy();

	if (!_Width || !_Height || !_ChannelsCount || _ChannelsCount >= 4)
	{
		return false;
	}

	Data = new uint8_t[_Width * _Height * _ChannelsCount];

	if (!Data)
	{
		return false;
	}

	ChannelsCount = _ChannelsCount;
	Width = _Width;
	Height = _Height;

	for (size_t _Index = 0; _Index < Width * Height * ChannelsCount; _Index++)
	{
		Data[_Index] = 0;
	}

	return true;
}

const bool BFW::Assets::BitMap::Load(const FileSystem::FileContent& _FileContent, const bool _Flip)
{
	Destroy();

	if (!_FileContent.GetData() || _FileContent.GetLength() < sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader) + 1)
	{
		return false;
	}

	BitMapFileHeader _FileHeader = *(const BitMapFileHeader*)(_FileContent.GetData());
	BitMapInfoHeader _InfoHeader = *(const BitMapInfoHeader*)(_FileContent.GetData() + sizeof(BitMapFileHeader));

	_FileHeader.Size = BFW_LITTLE_ENDIAN_TO_MACHINE_32(_FileHeader.Size);
	_FileHeader.Reserved1 = BFW_LITTLE_ENDIAN_TO_MACHINE_16(_FileHeader.Reserved1);
	_FileHeader.Reserved2 = BFW_LITTLE_ENDIAN_TO_MACHINE_16(_FileHeader.Reserved2);
	_FileHeader.Offset = BFW_LITTLE_ENDIAN_TO_MACHINE_32(_FileHeader.Offset);

	_InfoHeader.Size = BFW_LITTLE_ENDIAN_TO_MACHINE_32(_InfoHeader.Size);
	_InfoHeader.Width = BFW_LITTLE_ENDIAN_TO_MACHINE_32(_InfoHeader.Width);
	_InfoHeader.Height = BFW_LITTLE_ENDIAN_TO_MACHINE_32(_InfoHeader.Height);
	_InfoHeader.Planes = BFW_LITTLE_ENDIAN_TO_MACHINE_16(_InfoHeader.Planes);
	_InfoHeader.BitCount = BFW_LITTLE_ENDIAN_TO_MACHINE_16(_InfoHeader.BitCount);
	_InfoHeader.Compression = BFW_LITTLE_ENDIAN_TO_MACHINE_32(_InfoHeader.Compression);
	_InfoHeader.ImageSize = BFW_LITTLE_ENDIAN_TO_MACHINE_32(_InfoHeader.ImageSize);
	_InfoHeader.DPIX = BFW_LITTLE_ENDIAN_TO_MACHINE_32(_InfoHeader.DPIX);
	_InfoHeader.DPIY = BFW_LITTLE_ENDIAN_TO_MACHINE_32(_InfoHeader.DPIY);
	_InfoHeader.ColorsUsed = BFW_LITTLE_ENDIAN_TO_MACHINE_32(_InfoHeader.ColorsUsed);
	_InfoHeader.ColorsImportant = BFW_LITTLE_ENDIAN_TO_MACHINE_32(_InfoHeader.ColorsImportant);

	bool _AlreadyFlipped = false;

	if (_InfoHeader.Height < 0)
	{
		_InfoHeader.Height = -_InfoHeader.Height;
		_AlreadyFlipped = true;
	}

	const size_t _RowPadding = (4 - (_InfoHeader.Width * (size_t)(_InfoHeader.BitCount) / 8) % 4) % 4;

	if (_FileHeader.Type[0] != 'B' || _FileHeader.Type[1] != 'M')
	{
		return false;
	}

	if ((size_t)(_FileHeader.Size) + 1 != _FileContent.GetLength())
	{
		return false;
	}

	if (_FileHeader.Offset != sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader))
	{
		return false;
	}

	if (_InfoHeader.Size != sizeof(BitMapInfoHeader))
	{
		return false;
	}

	if (_InfoHeader.Width == 0 || _InfoHeader.Height == 0 || (uint32_t)(_InfoHeader.Width * _InfoHeader.Height * (size_t)(_InfoHeader.BitCount / 8) + _RowPadding * _InfoHeader.Height + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)) != _FileHeader.Size)
	{
		return false;
	}

	if (_InfoHeader.Planes != 1)
	{
		return false;
	}

	if (_InfoHeader.BitCount != 24 && _InfoHeader.BitCount != 32)
	{
		return false;
	}

	if (_InfoHeader.Compression != 0)
	{
		return false;
	}

	if (_InfoHeader.ImageSize != 0 && _InfoHeader.ImageSize != (uint32_t)(_InfoHeader.Width * _InfoHeader.Height * (size_t)(_InfoHeader.BitCount / 8) + _RowPadding * _InfoHeader.Height))
	{
		return false;
	}

	if (_InfoHeader.ColorsUsed != 0)
	{
		return false;
	}

	if (_InfoHeader.ColorsImportant != 0)
	{
		return false;
	}

	Data = new uint8_t[_InfoHeader.Width * _InfoHeader.Height * 4];

	if (!Data)
	{
		return false;
	}

	ChannelsCount = 4;
	Width = _InfoHeader.Width;
	Height = _InfoHeader.Height;

	if ((_Flip && _AlreadyFlipped) || (!_Flip && !_AlreadyFlipped))
	{
		if (_InfoHeader.BitCount == 32)
		{
			for (size_t _PositionY = 0; _PositionY < Height; _PositionY++)
			{
				for (size_t _PositionX = 0; _PositionX < Width; _PositionX++)
				{
					Data[(_PositionX + _PositionY * Width) * ChannelsCount + 0] = _FileContent[_PositionX * 4 + (Height - 1 - _PositionY) * (Width * 4 + _RowPadding) + 2 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)];
					Data[(_PositionX + _PositionY * Width) * ChannelsCount + 1] = _FileContent[_PositionX * 4 + (Height - 1 - _PositionY) * (Width * 4 + _RowPadding) + 1 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)];
					Data[(_PositionX + _PositionY * Width) * ChannelsCount + 2] = _FileContent[_PositionX * 4 + (Height - 1 - _PositionY) * (Width * 4 + _RowPadding) + 0 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)];
					Data[(_PositionX + _PositionY * Width) * ChannelsCount + 3] = _FileContent[_PositionX * 4 + (Height - 1 - _PositionY) * (Width * 4 + _RowPadding) + 3 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)];
				}
			}
		}

		if (_InfoHeader.BitCount == 24)
		{
			for (size_t _PositionY = 0; _PositionY < Height; _PositionY++)
			{
				for (size_t _PositionX = 0; _PositionX < Width; _PositionX++)
				{
					Data[(_PositionX + _PositionY * Width) * ChannelsCount + 0] = _FileContent[_PositionX * 3 + (Height - 1 - _PositionY) * (Width * 3 + _RowPadding) + 2 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)];
					Data[(_PositionX + _PositionY * Width) * ChannelsCount + 1] = _FileContent[_PositionX * 3 + (Height - 1 - _PositionY) * (Width * 3 + _RowPadding) + 1 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)];
					Data[(_PositionX + _PositionY * Width) * ChannelsCount + 2] = _FileContent[_PositionX * 3 + (Height - 1 - _PositionY) * (Width * 3 + _RowPadding) + 0 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)];
					Data[(_PositionX + _PositionY * Width) * ChannelsCount + 3] = 255;
				}
			}
		}
	}
	else
	{
		if (_InfoHeader.BitCount == 32)
		{
			for (size_t _PositionY = 0; _PositionY < Height; _PositionY++)
			{
				for (size_t _PositionX = 0; _PositionX < Width; _PositionX++)
				{
					Data[(_PositionX + _PositionY * Width) * ChannelsCount + 0] = _FileContent[_PositionX * 4 + _PositionY * (Width * 4 + _RowPadding) + 2 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)];
					Data[(_PositionX + _PositionY * Width) * ChannelsCount + 1] = _FileContent[_PositionX * 4 + _PositionY * (Width * 4 + _RowPadding) + 1 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)];
					Data[(_PositionX + _PositionY * Width) * ChannelsCount + 2] = _FileContent[_PositionX * 4 + _PositionY * (Width * 4 + _RowPadding) + 0 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)];
					Data[(_PositionX + _PositionY * Width) * ChannelsCount + 3] = _FileContent[_PositionX * 4 + _PositionY * (Width * 4 + _RowPadding) + 3 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)];
				}
			}
		}

		if (_InfoHeader.BitCount == 24)
		{
			for (size_t _PositionY = 0; _PositionY < Height; _PositionY++)
			{
				for (size_t _PositionX = 0; _PositionX < Width; _PositionX++)
				{
					Data[(_PositionX + _PositionY * Width) * ChannelsCount + 0] = _FileContent[_PositionX * 3 + _PositionY * (Width * 3 + _RowPadding) + 2 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)];
					Data[(_PositionX + _PositionY * Width) * ChannelsCount + 1] = _FileContent[_PositionX * 3 + _PositionY * (Width * 3 + _RowPadding) + 1 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)];
					Data[(_PositionX + _PositionY * Width) * ChannelsCount + 2] = _FileContent[_PositionX * 3 + _PositionY * (Width * 3 + _RowPadding) + 0 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)];
					Data[(_PositionX + _PositionY * Width) * ChannelsCount + 3] = 255;
				}
			}
		}
	}

	return true;
}

void BFW::Assets::BitMap::Destroy()
{
	delete[] Data;
	Data = nullptr;
	ChannelsCount = 0;
	Width = 0;
	Height = 0;
}

BFW::FileSystem::FileContent BFW::Assets::BitMap::Save(const bool _Flip) const
{
	if (!Data)
	{
		return FileSystem::FileContent();
	}

	BitMapFileHeader _FileHeader;
	uint8_t* _FileHeaderPtr = (uint8_t*)(&_FileHeader);

	_FileHeader.Type[0] = 'B';
	_FileHeader.Type[1] = 'M';
	_FileHeader.Size = BFW_MACHINE_TO_LITTLE_ENDIAN_32((uint32_t)(sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader) + Width * Height * 4));
	_FileHeader.Reserved1 = BFW_MACHINE_TO_LITTLE_ENDIAN_16(0);
	_FileHeader.Reserved2 = BFW_MACHINE_TO_LITTLE_ENDIAN_16(0);
	_FileHeader.Offset = BFW_MACHINE_TO_LITTLE_ENDIAN_32(sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader));

	BitMapInfoHeader _InfoHeader;
	uint8_t* _InfoHeaderPtr = (uint8_t*)(&_InfoHeader);

	_InfoHeader.Size = BFW_MACHINE_TO_LITTLE_ENDIAN_32(sizeof(BitMapInfoHeader));
	_InfoHeader.Width = BFW_MACHINE_TO_LITTLE_ENDIAN_32((uint32_t)(Width));
	_InfoHeader.Height = BFW_MACHINE_TO_LITTLE_ENDIAN_32((int32_t)(Height));
	_InfoHeader.Planes = BFW_MACHINE_TO_LITTLE_ENDIAN_16(1);
	_InfoHeader.BitCount = BFW_MACHINE_TO_LITTLE_ENDIAN_16(32);
	_InfoHeader.Compression = BFW_MACHINE_TO_LITTLE_ENDIAN_32(0);
	_InfoHeader.ImageSize = BFW_MACHINE_TO_LITTLE_ENDIAN_32((uint32_t)(Width * Height * 4));
	_InfoHeader.DPIX = BFW_MACHINE_TO_LITTLE_ENDIAN_32(0);
	_InfoHeader.DPIY = BFW_MACHINE_TO_LITTLE_ENDIAN_32(0);
	_InfoHeader.ColorsUsed = BFW_MACHINE_TO_LITTLE_ENDIAN_32(0);
	_InfoHeader.ColorsImportant = BFW_MACHINE_TO_LITTLE_ENDIAN_32(0);

	FileSystem::FileContent _FileContent;

	if (!_FileContent.Create(sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader) + Width * Height * 4 + 1))
	{
		return FileSystem::FileContent();
	}

	_FileContent[_FileContent.GetLength() - 1] = '\0';

	for (size_t _Index = 0; _Index < sizeof(BitMapFileHeader); _Index++)
	{
		_FileContent[_Index] = _FileHeaderPtr[_Index];
	}

	for (size_t _Index = 0; _Index < sizeof(BitMapInfoHeader); _Index++)
	{
		_FileContent[sizeof(BitMapFileHeader) + _Index] = _InfoHeaderPtr[_Index];
	}

	if (_Flip)
	{
		if (ChannelsCount == 1)
		{
			for (size_t _PositionY = 0; _PositionY < Height; _PositionY++)
			{
				for (size_t _PositionX = 0; _PositionX < Width; _PositionX++)
				{
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 2 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_PositionX + _PositionY * Width) * ChannelsCount + 0];
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 1 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = 0;
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 0 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = 0;
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 3 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = 255;
				}
			}
		}

		if (ChannelsCount == 2)
		{
			for (size_t _PositionY = 0; _PositionY < Height; _PositionY++)
			{
				for (size_t _PositionX = 0; _PositionX < Width; _PositionX++)
				{
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 2 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_PositionX + _PositionY * Width) * ChannelsCount + 0];
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 1 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_PositionX + _PositionY * Width) * ChannelsCount + 1];
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 0 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = 0;
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 3 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = 255;
				}
			}
		}

		if (ChannelsCount == 3)
		{
			for (size_t _PositionY = 0; _PositionY < Height; _PositionY++)
			{
				for (size_t _PositionX = 0; _PositionX < Width; _PositionX++)
				{
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 2 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_PositionX + _PositionY * Width) * ChannelsCount + 0];
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 1 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_PositionX + _PositionY * Width) * ChannelsCount + 1];
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 0 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_PositionX + _PositionY * Width) * ChannelsCount + 2];
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 3 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = 255;
				}
			}
		}

		if (ChannelsCount == 4)
		{
			for (size_t _PositionY = 0; _PositionY < Height; _PositionY++)
			{
				for (size_t _PositionX = 0; _PositionX < Width; _PositionX++)
				{
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 2 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_PositionX + _PositionY * Width) * ChannelsCount + 0];
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 1 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_PositionX + _PositionY * Width) * ChannelsCount + 1];
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 0 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_PositionX + _PositionY * Width) * ChannelsCount + 2];
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 3 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_PositionX + _PositionY * Width) * ChannelsCount + 3];
				}
			}
		}
	}
	else
	{
		if (ChannelsCount == 1)
		{
			for (size_t _PositionY = 0; _PositionY < Height; _PositionY++)
			{
				for (size_t _PositionX = 0; _PositionX < Width; _PositionX++)
				{
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 2 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_PositionX + (Height - 1 - _PositionY) * Width) * ChannelsCount + 0];
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 1 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = 0;
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 0 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = 0;
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 3 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = 255;
				}
			}
		}

		if (ChannelsCount == 2)
		{
			for (size_t _PositionY = 0; _PositionY < Height; _PositionY++)
			{
				for (size_t _PositionX = 0; _PositionX < Width; _PositionX++)
				{
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 2 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_PositionX + (Height - 1 - _PositionY) * Width) * ChannelsCount + 0];
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 1 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_PositionX + (Height - 1 - _PositionY) * Width) * ChannelsCount + 1];
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 0 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = 0;
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 3 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = 255;
				}
			}
		}

		if (ChannelsCount == 3)
		{
			for (size_t _PositionY = 0; _PositionY < Height; _PositionY++)
			{
				for (size_t _PositionX = 0; _PositionX < Width; _PositionX++)
				{
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 2 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_PositionX + (Height - 1 - _PositionY) * Width) * ChannelsCount + 0];
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 1 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_PositionX + (Height - 1 - _PositionY) * Width) * ChannelsCount + 1];
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 0 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_PositionX + (Height - 1 - _PositionY) * Width) * ChannelsCount + 2];
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 3 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = 255;
				}
			}
		}

		if (ChannelsCount == 4)
		{
			for (size_t _PositionY = 0; _PositionY < Height; _PositionY++)
			{
				for (size_t _PositionX = 0; _PositionX < Width; _PositionX++)
				{
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 2 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_PositionX + (Height - 1 - _PositionY) * Width) * ChannelsCount + 0];
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 1 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_PositionX + (Height - 1 - _PositionY) * Width) * ChannelsCount + 1];
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 0 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_PositionX + (Height - 1 - _PositionY) * Width) * ChannelsCount + 2];
					_FileContent[(_PositionX + _PositionY * Width) * 4 + 3 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_PositionX + (Height - 1 - _PositionY) * Width) * ChannelsCount + 3];
				}
			}
		}
	}

	return _FileContent;
}

uint8_t* BFW::Assets::BitMap::GetData()
{
	return Data;
}

const uint8_t* BFW::Assets::BitMap::GetData() const
{
	return Data;
}

const size_t BFW::Assets::BitMap::GetChannelsCount() const
{
	return ChannelsCount;
}

const size_t BFW::Assets::BitMap::GetWidth() const
{
	return Width;
}

const size_t BFW::Assets::BitMap::GetHeight() const
{
	return Height;
}

BFW::Assets::BitMap::operator uint8_t* ()
{
	return Data;
}

BFW::Assets::BitMap::operator const uint8_t* () const
{
	return Data;
}

uint8_t& BFW::Assets::BitMap::operator* ()
{
	return *Data;
}

const uint8_t& BFW::Assets::BitMap::operator* () const
{
	return *Data;
}

uint8_t* BFW::Assets::BitMap::operator[] (const size_t _PositionY)
{
	return Data + _PositionY * Width * ChannelsCount;
}

const uint8_t* BFW::Assets::BitMap::operator* (const size_t _PositionY) const
{
	return Data + _PositionY * Width * ChannelsCount;
}

BFW::Assets::BitMap& BFW::Assets::BitMap::operator= (const BitMap& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Destroy();

	if (!_Other.Data)
	{
		return *this;
	}

	Data = new uint8_t[_Other.Width * _Other.Height * _Other.ChannelsCount];

	if (!Data)
	{
		throw nullptr;
	}

	ChannelsCount = _Other.ChannelsCount;
	Width = _Other.Width;
	Height = _Other.Height;

	for (size_t _Index = 0; _Index < Width * Height * ChannelsCount; _Index++)
	{
		Data[_Index] = _Other.Data[_Index];
	}

	return *this;
}

BFW::Assets::BitMap& BFW::Assets::BitMap::operator= (BitMap&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Destroy();

	Data = _Other.Data;
	ChannelsCount = _Other.ChannelsCount;
	Width = _Other.Width;
	Height = _Other.Height;

	_Other.Data = nullptr;
	_Other.ChannelsCount = 0;
	_Other.Width = 0;
	_Other.Height = 0;

	return *this;
}



BFW::Assets::WaveFormat::WaveFormat() : FormatTag(0), Channels(0), SamplesPerSec(0), AvgBytesPerSec(0), BlockAlign(0), BitsPerSample(0)
{

}

BFW::Assets::WaveFormat::WaveFormat(WaveFormat&& _Other) noexcept : FormatTag(_Other.FormatTag), Channels(_Other.Channels), SamplesPerSec(_Other.SamplesPerSec), AvgBytesPerSec(_Other.AvgBytesPerSec), BlockAlign(_Other.BlockAlign), BitsPerSample(_Other.BitsPerSample)
{
	_Other.FormatTag = 0;
	_Other.Channels = 0;
	_Other.SamplesPerSec = 0;
	_Other.AvgBytesPerSec = 0;
	_Other.BlockAlign = 0;
	_Other.BitsPerSample = 0;
}

BFW::Assets::WaveFormat::~WaveFormat()
{

}

BFW::Assets::WaveFormat& BFW::Assets::WaveFormat::operator= (WaveFormat&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	FormatTag = _Other.FormatTag;
	Channels = _Other.Channels;
	SamplesPerSec = _Other.SamplesPerSec;
	AvgBytesPerSec = _Other.AvgBytesPerSec;
	BlockAlign = _Other.BlockAlign;
	BitsPerSample = _Other.BitsPerSample;

	_Other.FormatTag = 0;
	_Other.Channels = 0;
	_Other.SamplesPerSec = 0;
	_Other.AvgBytesPerSec = 0;
	_Other.BlockAlign = 0;
	_Other.BitsPerSample = 0;

	return *this;
}



BFW::Assets::Wave::Wave() : Info(), Data(nullptr), Size(0)
{

}

BFW::Assets::Wave::Wave(const Wave& _Other) : Info(), Data(nullptr), Size(0)
{
	if (!_Other.Data)
	{
		return;
	}

	Data = new uint8_t[_Other.Size];

	if (!Data)
	{
		throw nullptr;
	}

	Info = _Other.Info;
	Size = _Other.Size;

	for (size_t _Index = 0; _Index < Size; _Index++)
	{
		Data[_Index] = _Other.Data[_Index];
	}
}

BFW::Assets::Wave::Wave(Wave&& _Other) noexcept : Info((WaveFormat&&)(_Other.Info)), Data(_Other.Data), Size(_Other.Size)
{
	_Other.Data = nullptr;
	_Other.Size = 0;
}

BFW::Assets::Wave::~Wave()
{
	delete[] Data;
}

const bool BFW::Assets::Wave::Create(const WaveFormat& _Info, const size_t _Size)
{
	Destroy();

	if (_Info.FormatTag != 1)
	{
		return false;
	}

	if (_Info.Channels != 1 && _Info.Channels != 2)
	{
		return false;
	}

	if (!_Info.SamplesPerSec)
	{
		return false;
	}

	if (_Info.BitsPerSample != 8 && _Info.BitsPerSample != 16)
	{
		return false;
	}

	if (_Info.AvgBytesPerSec != _Info.SamplesPerSec * _Info.Channels * _Info.BitsPerSample / 8)
	{
		return false;
	}

	if (_Info.BlockAlign != _Info.Channels * _Info.BitsPerSample / 8)
	{
		return false;
	}

	if (!_Size || _Size % ((size_t)(_Info.Channels) * (size_t)(_Info.BitsPerSample) / 8) != 0)
	{
		return false;
	}

	Data = new uint8_t[_Size];

	if (!Data)
	{
		return false;
	}

	Info = _Info;
	Size = _Size;

	for (size_t _Index = 0; _Index < Size; _Index++)
	{
		Data[_Index] = 0;
	}

	return true;
}

const bool BFW::Assets::Wave::Load(const FileSystem::FileContent& _FileContent)
{
	Destroy();

	if (!_FileContent.GetData() || _FileContent.GetLength() < sizeof(WaveFileHeader) + sizeof(WaveChunkHeader) * 2 + 1)
	{
		return false;
	}

	WaveFileHeader _FileHeader = *(const WaveFileHeader*)(_FileContent.GetData());

	_FileHeader.FileSize = BFW_LITTLE_ENDIAN_TO_MACHINE_32(_FileHeader.FileSize);

	if (_FileHeader.RIFF[0] != 'R' || _FileHeader.RIFF[1] != 'I' || _FileHeader.RIFF[2] != 'F' || _FileHeader.RIFF[3] != 'F')
	{
		return false;
	}

	if ((size_t)(_FileHeader.FileSize) + 1 != _FileContent.GetLength() - 8)
	{
		return false;
	}

	if (_FileHeader.WAVE[0] != 'W' || _FileHeader.WAVE[1] != 'A' || _FileHeader.WAVE[2] != 'V' || _FileHeader.WAVE[3] != 'E')
	{
		return false;
	}

	size_t _CurrentPosition = sizeof(WaveFileHeader);

	bool _FoundFMT = false;
	bool _FoundData = false;

	while (_CurrentPosition + 1 < _FileContent.GetLength())
	{
		WaveChunkHeader _ChunkHeader = *(const WaveChunkHeader*)(_FileContent.GetData() + _CurrentPosition);

		_ChunkHeader.Size = BFW_LITTLE_ENDIAN_TO_MACHINE_32(_ChunkHeader.Size);

		if (_CurrentPosition + sizeof(WaveChunkHeader) + _ChunkHeader.Size + 1 > _FileContent.GetLength())
		{
			Destroy();
			return false;
		}

		if (_ChunkHeader.ID[0] == 'f' && _ChunkHeader.ID[1] == 'm' && _ChunkHeader.ID[2] == 't' && _ChunkHeader.ID[3] == ' ')
		{
			if (_FoundFMT)
			{
				Destroy();
				return false;
			}

			if (_ChunkHeader.Size < sizeof(WaveFormat))
			{
				Destroy();
				return false;
			}

			_FoundFMT = true;

			Info = *(const WaveFormat*)(_FileContent.GetData() + _CurrentPosition + sizeof(WaveChunkHeader));

			Info.FormatTag = BFW_LITTLE_ENDIAN_TO_MACHINE_16(Info.FormatTag);
			Info.Channels = BFW_LITTLE_ENDIAN_TO_MACHINE_16(Info.Channels);
			Info.SamplesPerSec = BFW_LITTLE_ENDIAN_TO_MACHINE_32(Info.SamplesPerSec);
			Info.AvgBytesPerSec = BFW_LITTLE_ENDIAN_TO_MACHINE_32(Info.AvgBytesPerSec);
			Info.BlockAlign = BFW_LITTLE_ENDIAN_TO_MACHINE_16(Info.BlockAlign);
			Info.BitsPerSample = BFW_LITTLE_ENDIAN_TO_MACHINE_16(Info.BitsPerSample);

			if (Info.FormatTag != 1)
			{
				Destroy();
				return false;
			}

			if (Info.Channels != 1 && Info.Channels != 2)
			{
				Destroy();
				return false;
			}

			if (!Info.SamplesPerSec)
			{
				Destroy();
				return false;
			}

			if (Info.BitsPerSample != 8 && Info.BitsPerSample != 16)
			{
				Destroy();
				return false;
			}

			if (Info.AvgBytesPerSec != Info.SamplesPerSec * Info.Channels * Info.BitsPerSample / 8)
			{
				Destroy();
				return false;
			}

			if (Info.BlockAlign != Info.Channels * Info.BitsPerSample / 8)
			{
				Destroy();
				return false;
			}
		}

		if (_ChunkHeader.ID[0] == 'd' && _ChunkHeader.ID[1] == 'a' && _ChunkHeader.ID[2] == 't' && _ChunkHeader.ID[3] == 'a')
		{
			if (_FoundData)
			{
				Destroy();
				return false;
			}

			if (!_ChunkHeader.Size)
			{
				Destroy();
				return false;
			}

			_FoundData = true;

			Size = _ChunkHeader.Size;
			Data = new uint8_t[Size];

			if (!Data)
			{
				Destroy();
				return false;
			}

			for (size_t _Index = 0; _Index < Size; _Index++)
			{
				Data[_Index] = _FileContent[_CurrentPosition + sizeof(WaveChunkHeader) + _Index];
			}
		}

		_CurrentPosition += sizeof(WaveChunkHeader) + _ChunkHeader.Size;

		if (_ChunkHeader.Size % 2 == 1)
		{
			_CurrentPosition++;
		}
	}

	if (!_FoundFMT || !_FoundData)
	{
		Destroy();
		return false;
	}

	if (Size % ((size_t)(Info.Channels) * (size_t)(Info.BitsPerSample) / 8) != 0)
	{
		Destroy();
		return false;
	}

	if (Info.BitsPerSample == 16)
	{
		int16_t* _Data = (int16_t*)(Data);

		for (size_t _Index = 0; _Index < Size / 2; _Index++)
		{
			_Data[_Index] = BFW_LITTLE_ENDIAN_TO_MACHINE_16(_Data[_Index]);
		}
	}

	return true;
}

void BFW::Assets::Wave::Destroy()
{
	Info = WaveFormat();
	delete[] Data;
	Data = nullptr;
	Size = 0;
}

BFW::FileSystem::FileContent BFW::Assets::Wave::Save() const
{
	if (!Data)
	{
		return FileSystem::FileContent();
	}

	WaveFileHeader _FileHeader;
	uint8_t* _FileHeaderPtr = (uint8_t*)(&_FileHeader);

	_FileHeader.RIFF[0] = 'R';
	_FileHeader.RIFF[1] = 'I';
	_FileHeader.RIFF[2] = 'F';
	_FileHeader.RIFF[3] = 'F';
	_FileHeader.FileSize = BFW_MACHINE_TO_LITTLE_ENDIAN_32((uint32_t)(sizeof(WaveFileHeader) + sizeof(WaveChunkHeader) + sizeof(WaveFormat) + sizeof(WaveChunkHeader) + Size - 8));
	_FileHeader.WAVE[0] = 'W';
	_FileHeader.WAVE[1] = 'A';
	_FileHeader.WAVE[2] = 'V';
	_FileHeader.WAVE[3] = 'E';

	WaveChunkHeader _FMTHeader;
	uint8_t* _FMTHeaderPtr = (uint8_t*)(&_FMTHeader);

	_FMTHeader.ID[0] = 'f';
	_FMTHeader.ID[1] = 'm';
	_FMTHeader.ID[2] = 't';
	_FMTHeader.ID[3] = ' ';
	_FMTHeader.Size = BFW_MACHINE_TO_LITTLE_ENDIAN_32(sizeof(WaveFormat));

	WaveFormat _Info = Info;
	uint8_t* _InfoPtr = (uint8_t*)(&_Info);

	_Info.FormatTag = BFW_MACHINE_TO_LITTLE_ENDIAN_16(_Info.FormatTag);
	_Info.Channels = BFW_MACHINE_TO_LITTLE_ENDIAN_16(_Info.Channels);
	_Info.SamplesPerSec = BFW_MACHINE_TO_LITTLE_ENDIAN_32(_Info.SamplesPerSec);
	_Info.AvgBytesPerSec = BFW_MACHINE_TO_LITTLE_ENDIAN_32(_Info.AvgBytesPerSec);
	_Info.BlockAlign = BFW_MACHINE_TO_LITTLE_ENDIAN_16(_Info.BlockAlign);
	_Info.BitsPerSample = BFW_MACHINE_TO_LITTLE_ENDIAN_16(_Info.BitsPerSample);

	WaveChunkHeader _DataHeader;
	uint8_t* _DataHeaderPtr = (uint8_t*)(&_DataHeader);

	_DataHeader.ID[0] = 'd';
	_DataHeader.ID[1] = 'a';
	_DataHeader.ID[2] = 't';
	_DataHeader.ID[3] = 'a';
	_DataHeader.Size = BFW_MACHINE_TO_LITTLE_ENDIAN_32((uint32_t)(Size));

	FileSystem::FileContent _FileContent;

	if (!_FileContent.Create(sizeof(WaveFileHeader) + sizeof(WaveChunkHeader) + sizeof(WaveFormat) + sizeof(WaveChunkHeader) + Size + 1))
	{
		return FileSystem::FileContent();
	}

	_FileContent[_FileContent.GetLength() - 1] = '\0';

	for (size_t _Index = 0; _Index < sizeof(WaveFileHeader); _Index++)
	{
		_FileContent[_Index] = _FileHeaderPtr[_Index];
	}

	for (size_t _Index = 0; _Index < sizeof(WaveChunkHeader); _Index++)
	{
		_FileContent[sizeof(WaveFileHeader) + _Index] = _FMTHeaderPtr[_Index];
	}

	for (size_t _Index = 0; _Index < sizeof(WaveFormat); _Index++)
	{
		_FileContent[sizeof(WaveFileHeader) + sizeof(WaveChunkHeader) + _Index] = _InfoPtr[_Index];
	}

	for (size_t _Index = 0; _Index < sizeof(WaveChunkHeader); _Index++)
	{
		_FileContent[sizeof(WaveFileHeader) + sizeof(WaveChunkHeader) + sizeof(WaveFormat) + _Index] = _DataHeaderPtr[_Index];
	}

	for (size_t _Index = 0; _Index < Size; _Index++)
	{
		_FileContent[sizeof(WaveFileHeader) + sizeof(WaveChunkHeader) + sizeof(WaveFormat) + sizeof(WaveChunkHeader) + _Index] = Data[_Index];
	}

	if (Info.BitsPerSample == 16)
	{
		int16_t* _Data = (int16_t*)(_FileContent.GetData() + sizeof(WaveFileHeader) + sizeof(WaveChunkHeader) + sizeof(WaveFormat) + sizeof(WaveChunkHeader));

		for (size_t _Index = 0; _Index < Size / 2; _Index++)
		{
			_Data[_Index] = BFW_MACHINE_TO_LITTLE_ENDIAN_16(_Data[_Index]);
		}
	}

	return _FileContent;
}

const BFW::Assets::WaveFormat BFW::Assets::Wave::GetInfo() const
{
	return Info;
}

uint8_t* BFW::Assets::Wave::GetData8()
{
	return Data;
}

const uint8_t* BFW::Assets::Wave::GetData8() const
{
	return Data;
}

int16_t* BFW::Assets::Wave::GetData16()
{
	return (int16_t*)(Data);
}

const int16_t* BFW::Assets::Wave::GetData16() const
{
	return (int16_t*)(Data);
}

const size_t BFW::Assets::Wave::GetSize() const
{
	return Size;
}

BFW::Assets::Wave::operator uint8_t* ()
{
	return Data;
}

BFW::Assets::Wave::operator const uint8_t* () const
{
	return Data;
}

uint8_t& BFW::Assets::Wave::operator* ()
{
	return *Data;
}

const uint8_t& BFW::Assets::Wave::operator* () const
{
	return *Data;
}

uint8_t& BFW::Assets::Wave::operator[] (const size_t _Index)
{
	return Data[_Index];
}

const uint8_t& BFW::Assets::Wave::operator[] (const size_t _Index) const
{
	return Data[_Index];
}

BFW::Assets::Wave& BFW::Assets::Wave::operator= (const Wave& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Destroy();

	if (!_Other.Data)
	{
		return *this;
	}

	Data = new uint8_t[_Other.Size];

	if (!Data)
	{
		throw nullptr;
	}

	Info = _Other.Info;
	Size = _Other.Size;

	for (size_t _Index = 0; _Index < Size; _Index++)
	{
		Data[_Index] = _Other.Data[_Index];
	}

	return *this;
}

BFW::Assets::Wave& BFW::Assets::Wave::operator= (Wave&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Destroy();

	Info = (WaveFormat&&)(_Other.Info);
	Data = _Other.Data;
	Size = _Other.Size;

	_Other.Data = nullptr;
	_Other.Size = 0;

	return *this;
}



BFW::Assets::JsonObjectData::JsonObjectData() : Object(), Tags()
{

}

BFW::Assets::JsonObjectData::JsonObjectData(JsonObjectData&& _Other) noexcept : Object((Vector<Json>&&)(_Other.Object)), Tags((Vector<BFW_STRING_TYPE_A>&&)(_Other.Tags))
{

}

BFW::Assets::JsonObjectData::~JsonObjectData()
{

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



BFW::Assets::Json::Json() : Type(_NullJsonType), Bool(false), Number(0.0f), String(""), Array(), ObjectData()
{

}

BFW::Assets::Json::Json(const Json& _Other) : Type(_Other.Type), Bool(_Other.Bool), Number(_Other.Number), String(_Other.String), Array(_Other.Array), ObjectData(_Other.ObjectData)
{

}

BFW::Assets::Json::Json(Json&& _Other) noexcept : Type(_Other.Type), Bool(_Other.Bool), Number(_Other.Number), String(_Other.String), Array((Vector<Json>&&)(_Other.Array)), ObjectData((JsonObjectData&&)(_Other.ObjectData))
{
	_Other.Type = _NullJsonType;
	_Other.Bool = false;
	_Other.Number = 0.0f;
	_Other.String = "";
}

BFW::Assets::Json::~Json()
{

}

const bool BFW::Assets::Json::Load(const FileSystem::FileContent& _FileContent)
{
	*this = Json();

	if (!_FileContent.GetData() || (const BFW_CHAR_TYPE_A)(_FileContent[_FileContent.GetLength() - 1]) != '\0')
	{
		return false;
	}

	size_t _CurrentPos = 0;

	while (std::isspace((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
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

	while (std::isspace((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
	{
		_CurrentPos++;
	}

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != '\0')
	{
		*this = Json();
		return false;
	}

	return true;
}

void BFW::Assets::Json::SetNull()
{
	Type = _NullJsonType;
	Bool = false;
	Number = 0.0f;
	String = "";
	Array = Vector<Json>();
	ObjectData = JsonObjectData();
}

void BFW::Assets::Json::SetBool(const bool _Bool)
{
	Type = _BoolJsonType;
	Bool = _Bool;
	Number = 0.0f;
	String = "";
	Array = Vector<Json>();
	ObjectData = JsonObjectData();
}

void BFW::Assets::Json::SetNumber(const float _Number)
{
	Type = _NumberJsonType;
	Bool = false;
	Number = _Number;
	String = "";
	Array = Vector<Json>();
	ObjectData = JsonObjectData();
}

void BFW::Assets::Json::SetString(const BFW_STRING_TYPE_A _String)
{
	Type = _StringJsonType;
	Bool = false;
	Number = 0.0f;
	String = _String;
	Array = Vector<Json>();
	ObjectData = JsonObjectData();
}

void BFW::Assets::Json::SetArray()
{
	Type = _ArrayJsonType;
	Bool = false;
	Number = 0.0f;
	String = "";
	Array = Vector<Json>();
	ObjectData = JsonObjectData();
}

void BFW::Assets::Json::SetObject()
{
	Type = _ObjectJsonType;
	Bool = false;
	Number = 0.0f;
	String = "";
	Array = Vector<Json>();
	ObjectData = JsonObjectData();
}

BFW::FileSystem::FileContent BFW::Assets::Json::Save() const
{
	if (Type != _ObjectJsonType && Type != _ArrayJsonType)
	{
		return FileSystem::FileContent();
	}

	size_t _TabLevel = 0;
	BFW_STRING_STREAM_TYPE_A _Stream;

	if (Type == _ObjectJsonType)
	{
		SaveJsonObject(_TabLevel, _Stream, *this);
	}

	if (Type == _ArrayJsonType)
	{
		SaveJsonArray(_TabLevel, _Stream, *this);
	}

	_Stream BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';

	BFW_STRING_TYPE_A _String = _Stream.str();

	FileSystem::FileContent _FileContent;

	if (!_FileContent.Create(_String.size() + 1))
	{
		return FileSystem::FileContent();
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

	return Bool;
}

const float BFW::Assets::Json::GetNumber() const
{
	if (Type != _NumberJsonType)
	{
		throw nullptr;
	}

	return Number;
}

const BFW_STRING_TYPE_A& BFW::Assets::Json::GetString() const
{
	if (Type != _StringJsonType)
	{
		throw nullptr;
	}

	return String;
}

BFW::Vector<BFW::Assets::Json>& BFW::Assets::Json::GetArray()
{
	if (Type != _ArrayJsonType)
	{
		throw nullptr;
	}

	return Array;
}

const BFW::Vector<BFW::Assets::Json>& BFW::Assets::Json::GetArray() const
{
	if (Type != _ArrayJsonType)
	{
		throw nullptr;
	}

	return Array;
}

BFW::Assets::JsonObjectData& BFW::Assets::Json::GetObjectData()
{
	if (Type != _ObjectJsonType)
	{
		throw nullptr;
	}

	return ObjectData;
}

const BFW::Assets::JsonObjectData& BFW::Assets::Json::GetObjectData() const
{
	if (Type != _ObjectJsonType)
	{
		throw nullptr;
	}

	return ObjectData;
}

BFW::Assets::Json& BFW::Assets::Json::operator= (const Json& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Type = _Other.Type;
	Bool = _Other.Bool;
	Number = _Other.Number;
	String = _Other.String;
	Array = _Other.Array;
	ObjectData = _Other.ObjectData;

	return *this;
}

BFW::Assets::Json& BFW::Assets::Json::operator= (Json&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Type = _Other.Type;
	Bool = _Other.Bool;
	Number = _Other.Number;
	String = _Other.String;
	Array = (Vector<Json>&&)(_Other.Array);
	ObjectData = (JsonObjectData&&)(_Other.ObjectData);

	_Other.Type = _NullJsonType;
	_Other.Bool = false;
	_Other.Number = 0.0f;
	_Other.String = "";

	return *this;
}
