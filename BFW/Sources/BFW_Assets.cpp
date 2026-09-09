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

struct HdrFileHeader
{

	BFW_CHAR_TYPE_A MagicNumbers[11];

	HdrFileHeader();
	HdrFileHeader(const HdrFileHeader& _Other) = default;
	HdrFileHeader(HdrFileHeader&& _Other) noexcept;
	~HdrFileHeader();
	HdrFileHeader& operator= (const HdrFileHeader& _Other) = default;
	HdrFileHeader& operator= (HdrFileHeader&& _Other) noexcept;

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



HdrFileHeader::HdrFileHeader() : MagicNumbers()
{
	for (size_t _Index = 0; _Index < 11; _Index++)
	{
		MagicNumbers[_Index] = 0;
	}
}

HdrFileHeader::HdrFileHeader(HdrFileHeader&& _Other) noexcept : MagicNumbers()
{
	for (size_t _Index = 0; _Index < 11; _Index++)
	{
		MagicNumbers[_Index] = _Other.MagicNumbers[_Index];
		_Other.MagicNumbers[_Index] = 0;
	}
}

HdrFileHeader::~HdrFileHeader()
{

}

HdrFileHeader& HdrFileHeader::operator= (HdrFileHeader&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	for (size_t _Index = 0; _Index < 11; _Index++)
	{
		MagicNumbers[_Index] = _Other.MagicNumbers[_Index];
		_Other.MagicNumbers[_Index] = 0;
	}

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



static const float HdrConvertComponent(const uint8_t _Component, const uint8_t _Exponent)
{
	return ldexpf(_Component + 0.5f, _Exponent - (128 + 8));
}

static const float HdrGetRFromXYZ(const float _X, const float _Y, const float _Z)
{
	return BFW::Math::Vec3::Dot(BFW::Math::Vec3(_X, _Y, _Z), BFW::Math::Vec3(3.2406f, -1.5372f, -0.4986f));
}

static const float HdrGetGFromXYZ(const float _X, const float _Y, const float _Z)
{
	return BFW::Math::Vec3::Dot(BFW::Math::Vec3(_X, _Y, _Z), BFW::Math::Vec3(-0.9689f, 1.8758f, 0.0415f));
}

static const float HdrGetBFromXYZ(const float _X, const float _Y, const float _Z)
{
	return BFW::Math::Vec3::Dot(BFW::Math::Vec3(_X, _Y, _Z), BFW::Math::Vec3(0.0557f, -0.2040f, 1.0570f));
}

static const bool HdrSimpleDecodeScanLine(const BFW::Assets::FileContent& _FileContent, size_t& _FileIndex, uint8_t* _ScanLine, const size_t _Width)
{
	size_t _Length = 0;
	size_t _LeftShift = 0;

	while (_Length < _Width)
	{
		if (_FileContent.GetLength() - 1 == _FileIndex)
		{
			return false;
		}

		uint8_t _R = _FileContent[_FileIndex];

		_FileIndex++;

		if (_FileContent.GetLength() - 1 == _FileIndex)
		{
			return false;
		}

		uint8_t _G = _FileContent[_FileIndex];

		_FileIndex++;

		if (_FileContent.GetLength() - 1 == _FileIndex)
		{
			return false;
		}

		uint8_t _B = _FileContent[_FileIndex];

		_FileIndex++;

		if (_FileContent.GetLength() - 1 == _FileIndex)
		{
			return false;
		}

		uint8_t _E = _FileContent[_FileIndex];

		_FileIndex++;

		if (_R != 1 || _G != 1 || _B != 1)
		{
			_ScanLine[_Length * 4 + 0] = _R;
			_ScanLine[_Length * 4 + 1] = _G;
			_ScanLine[_Length * 4 + 2] = _B;
			_ScanLine[_Length * 4 + 3] = _E;

			_Length++;
			_LeftShift = 0;

			continue;
		}

		for (size_t _Index = 0; _Index < (size_t)(_E) << _LeftShift; _Index++)
		{
			if (_Length == _Width || _Length == 0)
			{
				return false;
			}

			_ScanLine[_Length * 4 + 0] = _ScanLine[(_Length - 1) * 4 + 0];
			_ScanLine[_Length * 4 + 1] = _ScanLine[(_Length - 1) * 4 + 1];
			_ScanLine[_Length * 4 + 2] = _ScanLine[(_Length - 1) * 4 + 2];
			_ScanLine[_Length * 4 + 3] = _ScanLine[(_Length - 1) * 4 + 3];

			_Length++;
		}

		_LeftShift += 8;
	}

	return true;
}

static const bool HdrDecodeScanLine(const BFW::Assets::FileContent& _FileContent, size_t& _FileIndex, uint8_t* _ScanLine, const size_t _Width)
{
	if (_Width < 8 || _Width > std::numeric_limits<int16_t>::max())
	{
		return HdrSimpleDecodeScanLine(_FileContent, _FileIndex, _ScanLine, _Width);
	}

	if (_FileContent.GetLength() - 1 == _FileIndex || _FileContent.GetLength() - 1 == _FileIndex + 1 || _FileContent.GetLength() - 1 == _FileIndex + 2 || _FileContent.GetLength() - 1 == _FileIndex + 3)
	{
		return false;
	}

	if (_FileContent[_FileIndex] != 2 || _FileContent[_FileIndex + 1] != 2 || _FileContent[_FileIndex + 2] & 0b10000000)
	{
		return HdrSimpleDecodeScanLine(_FileContent, _FileIndex, _ScanLine, _Width);
	}

	if (((uint16_t)(_FileContent[_FileIndex + 2]) << 8) + _FileContent[_FileIndex + 3] != _Width)
	{
		return false;
	}

	_FileIndex += 4;

	for (size_t _Channel = 0; _Channel < 4; _Channel++)
	{
		size_t _X = 0;

		while (_X < _Width)
		{
			if (_FileContent.GetLength() - 1 == _FileIndex)
			{
				return false;
			}

			uint8_t _Length = _FileContent[_FileIndex];

			_FileIndex++;

			if (_Length <= 128)
			{
				if (_Length + _X > _Width)
				{
					return false;
				}

				while (_Length)
				{
					if (_FileContent.GetLength() - 1 == _FileIndex)
					{
						return false;
					}

					_ScanLine[_X * 4 + _Channel] = _FileContent[_FileIndex];

					_FileIndex++;
					_X++;

					_Length--;
				}

				continue;
			}

			_Length -= 128;

			if (_Length + _X > _Width)
			{
				return false;
			}

			if (_FileContent.GetLength() - 1 == _FileIndex)
			{
				return false;
			}

			uint8_t _Value = _FileContent[_FileIndex];

			_FileIndex++;

			while (_Length)
			{
				_ScanLine[_X * 4 + _Channel] = _Value;

				_X++;

				_Length--;
			}
		}
	}

	return true;
}

static void HdrPlaceScanLine(float* _Data, const uint8_t* _ScanLine, const size_t _Width, const size_t _Y)
{
	for (size_t _X = 0; _X < _Width; _X++)
	{
		_Data[(_X + _Y * _Width) * 4 + 0] = HdrConvertComponent(_ScanLine[_X * 4 + 0], _ScanLine[_X * 4 + 3]);
		_Data[(_X + _Y * _Width) * 4 + 1] = HdrConvertComponent(_ScanLine[_X * 4 + 1], _ScanLine[_X * 4 + 3]);
		_Data[(_X + _Y * _Width) * 4 + 2] = HdrConvertComponent(_ScanLine[_X * 4 + 2], _ScanLine[_X * 4 + 3]);
		_Data[(_X + _Y * _Width) * 4 + 3] = 1.0f;
	}
}



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

static const bool LoadJsonArray(const BFW::Assets::FileContent& _FileContent, size_t& _CurrentPos, BFW::Assets::Json& _Json)
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



BFW::Assets::FileContent::FileContent() : Data(nullptr), Length(0)
{

}

BFW::Assets::FileContent::FileContent(const FileContent& _Other) : Data(nullptr), Length(0)
{
	if (!_Other.Length)
	{
		return;
	}

	Data = new uint8_t[_Other.Length];

	if (!Data)
	{
		throw nullptr;
	}

	Length = _Other.Length;

	for (size_t _Index = 0; _Index < Length; _Index++)
	{
		Data[_Index] = _Other.Data[_Index];
	}
}

BFW::Assets::FileContent::FileContent(FileContent&& _Other) noexcept : Data(_Other.Data), Length(_Other.Length)
{
	_Other.Data = nullptr;
	_Other.Length = 0;
}

BFW::Assets::FileContent::~FileContent()
{
	delete[] Data;
}

const bool BFW::Assets::FileContent::Create(const size_t _Length)
{
	Destroy();

	if (!_Length)
	{
		return false;
	}

	Data = new uint8_t[_Length];

	if (!Data)
	{
		return false;
	}

	Length = _Length;

	for (size_t _Index = 0; _Index < Length; _Index++)
	{
		Data[_Index] = 0;
	}

	return true;
}

const bool BFW::Assets::FileContent::Load(std::ifstream& _File)
{
	Destroy();

	if (!_File.is_open())
	{
		return false;
	}

	size_t _CurrentPos = (size_t)(_File.tellg());

	_File.seekg(0, std::ios::end);

	size_t _Length = (size_t)(_File.tellg()) + 1;

	uint8_t* _Data = new uint8_t[_Length];

	if (!_Data)
	{
		_File.seekg(_CurrentPos, std::ios::beg);
		return false;
	}

	_File.seekg(0, std::ios::beg);

	_File.read((BFW_CHAR_TYPE_A*)(_Data), _Length - 1);

	if ((size_t)(_File.gcount()) != _Length - 1)
	{
		delete[] _Data;
		_File.seekg(_CurrentPos, std::ios::beg);
		return false;
	}

	_Data[_Length - 1] = '\0';

	Data = _Data;
	Length = _Length;

	_File.seekg(_CurrentPos, std::ios::beg);

	return true;
}

const bool BFW::Assets::FileContent::Load(std::fstream& _File)
{
	Destroy();

	if (!_File.is_open())
	{
		return false;
	}

	size_t _CurrentPos = (size_t)(_File.tellg());

	_File.seekg(0, std::ios::end);

	size_t _Length = (size_t)(_File.tellg()) + 1;

	uint8_t* _Data = new uint8_t[_Length];

	if (!_Data)
	{
		_File.seekg(_CurrentPos, std::ios::beg);
		return false;
	}

	_File.seekg(0, std::ios::beg);

	_File.read((BFW_CHAR_TYPE_A*)(_Data), _Length - 1);

	if ((size_t)(_File.gcount()) != _Length - 1)
	{
		delete[] _Data;
		_File.seekg(_CurrentPos, std::ios::beg);
		return false;
	}

	_Data[_Length - 1] = '\0';

	Data = _Data;
	Length = _Length;

	_File.seekg(_CurrentPos, std::ios::beg);

	return true;
}

#ifdef BFW_WINDOWS_PLATFORM

const bool BFW::Assets::FileContent::Load(const size_t _ResourceType, const size_t _ResourceId)
{
	HINSTANCE _InstanceHandle = GetModuleHandle(nullptr);

	if (!_InstanceHandle)
	{
		return false;
	}

	HRSRC _ResourceHandle = FindResource(_InstanceHandle, MAKEINTRESOURCE(_ResourceId), MAKEINTRESOURCE(_ResourceType));

	if (!_ResourceHandle)
	{
		return false;
	}

	size_t _Length = (size_t)(SizeofResource(_InstanceHandle, _ResourceHandle)) + 1;

	const uint8_t* _ResourceMemory = (const uint8_t*)(LoadResource(_InstanceHandle, _ResourceHandle));

	if (!_ResourceMemory)
	{
		return false;
	}

	uint8_t* _Data = new uint8_t[_Length];

	if (!_Data)
	{
		FreeResource((HGLOBAL)(_ResourceMemory));
		return false;
	}

	for (size_t _Index = 0; _Index < _Length - 1; _Index++)
	{
		_Data[_Index] = _ResourceMemory[_Index];
	}

	_Data[_Length - 1] = '\0';

	Data = _Data;
	Length = _Length;

	FreeResource((HGLOBAL)(_ResourceMemory));

	return true;
}

#endif

void BFW::Assets::FileContent::Destroy()
{
	delete[] Data;
	Data = nullptr;
	Length = 0;
}

const bool BFW::Assets::FileContent::Save(std::ofstream& _File) const
{
	if (!Data || Length <= 1 || !_File.is_open())
	{
		return false;
	}

	_File.write((const BFW_CHAR_TYPE_A*)(Data), Length - 1);

	if (!_File)
	{
		return false;
	}

	return true;
}

const bool BFW::Assets::FileContent::Save(std::fstream& _File) const
{
	if (!Data || Length <= 1 || !_File.is_open())
	{
		return false;
	}

	_File.write((const BFW_CHAR_TYPE_A*)(Data), Length - 1);

	if (!_File)
	{
		return false;
	}

	return true;
}

const uint64_t BFW::Assets::FileContent::Hash() const
{
	if (!Length)
	{
		return BFW::Cryptography::HashA(nullptr, 0);
	}

	return BFW::Cryptography::HashA((const BFW_CHAR_TYPE_A*)(Data), Length - 1);
}

uint8_t* BFW::Assets::FileContent::GetData()
{
	return Data;
}

const uint8_t* BFW::Assets::FileContent::GetData() const
{
	return Data;
}

const size_t BFW::Assets::FileContent::GetLength() const
{
	return Length;
}

BFW::Assets::FileContent::operator uint8_t* ()
{
	return Data;
}

BFW::Assets::FileContent::operator const uint8_t* () const
{
	return Data;
}

uint8_t& BFW::Assets::FileContent::operator* ()
{
	return *Data;
}

const uint8_t& BFW::Assets::FileContent::operator* () const
{
	return *Data;
}

uint8_t& BFW::Assets::FileContent::operator[] (const size_t _Index)
{
	return Data[_Index];
}

const uint8_t& BFW::Assets::FileContent::operator[] (const size_t _Index) const
{
	return Data[_Index];
}

BFW::Assets::FileContent& BFW::Assets::FileContent::operator= (const FileContent& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Destroy();

	if (!_Other.Length)
	{
		return *this;
	}

	Data = new uint8_t[_Other.Length];

	if (!Data)
	{
		throw nullptr;
	}

	Length = _Other.Length;

	for (size_t _Index = 0; _Index < Length; _Index++)
	{
		Data[_Index] = _Other.Data[_Index];
	}

	return *this;
}

BFW::Assets::FileContent& BFW::Assets::FileContent::operator= (FileContent&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Destroy();

	Data = _Other.Data;
	Length = _Other.Length;

	_Other.Data = nullptr;
	_Other.Length = 0;

	return *this;
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

const bool BFW::Assets::BitMap::Load(const FileContent& _FileContent, const bool _Flip)
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

BFW::Assets::FileContent BFW::Assets::BitMap::Save(const bool _Flip) const
{
	if (!Data)
	{
		return FileContent();
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

	FileContent _FileContent;

	if (!_FileContent.Create(sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader) + Width * Height * 4 + 1))
	{
		return FileContent();
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



BFW::Assets::Hdr::Hdr() : Data(nullptr), ChannelsCount(0), Width(0), Height(0)
{

}

BFW::Assets::Hdr::Hdr(const Hdr& _Other) : Data(nullptr), ChannelsCount(0), Width(0), Height(0)
{
	if (!_Other.Data)
	{
		return;
	}

	Data = new float[_Other.Width * _Other.Height * _Other.ChannelsCount];

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

BFW::Assets::Hdr::Hdr(Hdr&& _Other) noexcept : Data(_Other.Data), ChannelsCount(_Other.ChannelsCount), Width(_Other.Width), Height(_Other.Height)
{
	_Other.Data = nullptr;
	_Other.ChannelsCount = 0;
	_Other.Width = 0;
	_Other.Height = 0;
}

BFW::Assets::Hdr::~Hdr()
{
	delete[] Data;
}

const bool BFW::Assets::Hdr::Create(const size_t _Width, const size_t _Height, const size_t _ChannelsCount)
{
	Destroy();

	if (!_Width || !_Height || !_ChannelsCount || _ChannelsCount >= 4)
	{
		return false;
	}

	Data = new float[_Width * _Height * _ChannelsCount];

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

const bool BFW::Assets::Hdr::Load(const FileContent& _FileContent, const bool _Flip)
{
	Destroy();

	if (!_FileContent.GetData() || _FileContent.GetLength() < sizeof(HdrFileHeader) + BFW_STRING_TYPE_A("FORMAT=32-bit_rle_rgbe\x0A\x0A").length() + BFW_STRING_TYPE_A("-Y  +X \x0A").length() + 1)
	{
		return false;
	}

	HdrFileHeader _FileHeader = *(const HdrFileHeader*)(_FileContent.GetData());

	if (_FileHeader.MagicNumbers[0] != '#' || _FileHeader.MagicNumbers[1] != '?' || _FileHeader.MagicNumbers[2] != 'R' || _FileHeader.MagicNumbers[3] != 'A' || _FileHeader.MagicNumbers[4] != 'D' || _FileHeader.MagicNumbers[5] != 'I' || _FileHeader.MagicNumbers[6] != 'A' || _FileHeader.MagicNumbers[7] != 'N' || _FileHeader.MagicNumbers[8] != 'C' || _FileHeader.MagicNumbers[9] != 'E' || _FileHeader.MagicNumbers[10] != '\x0A')
	{
		return false;
	}

	size_t _FileIndex = 11;

	bool _IsXYZE = false;

	{
		size_t _FormatRGBECount = 0;
		size_t _FormatXYZECount = 0;

		if (_FileContent[_FileIndex] == '\x0A')
		{
			return false;
		}

		while (_FileContent[_FileIndex] != '\x0A')
		{
			if (_FileContent[_FileIndex] == 0)
			{
				return false;
			}

			size_t _StringStart = _FileIndex;

			while (_FileContent[_FileIndex] != '\x0A')
			{
				if (_FileContent[_FileIndex] == 0)
				{
					return false;
				}

				_FileIndex++;
			}

			_FileIndex++;

			BFW_STRING_VIEW_TYPE_A _HeaderTag = BFW_STRING_VIEW_TYPE_A((const BFW_CHAR_TYPE_A*)(_FileContent.GetData()) + _StringStart, _FileIndex - 1 - _StringStart);

			if (_HeaderTag == "FORMAT=32-bit_rle_rgbe")
			{
				_FormatRGBECount++;
			}

			if (_HeaderTag == "FORMAT=32-bit_rle_xyze")
			{
				_FormatXYZECount++;
			}
		}

		_FileIndex++;

		if (_FormatRGBECount > 1 || _FormatXYZECount > 1 || (!_FormatRGBECount && !_FormatXYZECount) || (_FormatRGBECount && _FormatXYZECount))
		{
			return false;
		}

		_IsXYZE = _FormatXYZECount;
	}

	size_t _Width = 0;
	size_t _Height = 0;
	bool _FlippedX = false;
	bool _FlippedY = false;
	bool _ColumnMajor = false;

	{
		while (_FileContent[_FileIndex] == ' ' || _FileContent[_FileIndex] == '\t')
		{
			_FileIndex++;
		}

		size_t _Flip1Index = _FileIndex;

		if (_FileContent[_FileIndex] != '+' && _FileContent[_FileIndex] != '-')
		{
			return false;
		}

		_FileIndex++;

		size_t _Axis1Index = _FileIndex;

		if (_FileContent[_FileIndex] != 'X' && _FileContent[_FileIndex] != 'Y')
		{
			return false;
		}

		_FileIndex++;

		if (_FileContent[_FileIndex] != ' ' && _FileContent[_FileIndex] != '\t')
		{
			return false;
		}

		while (_FileContent[_FileIndex] == ' ' || _FileContent[_FileIndex] == '\t')
		{
			_FileIndex++;
		}

		size_t _Number1Index = _FileIndex;

		if (BFW_STRING_TYPE_A("0123456789").find(_FileContent[_FileIndex]) == BFW_STRING_TYPE_A::npos || _FileContent[_FileIndex] == 0)
		{
			return false;
		}

		while (BFW_STRING_TYPE_A("0123456789").find(_FileContent[_FileIndex]) != BFW_STRING_TYPE_A::npos && _FileContent[_FileIndex] != 0)
		{
			_FileIndex++;
		}

		size_t _Number1EndIndex = _FileIndex;

		if (_FileContent[_FileIndex] != ' ' && _FileContent[_FileIndex] != '\t')
		{
			return false;
		}

		while (_FileContent[_FileIndex] == ' ' || _FileContent[_FileIndex] == '\t')
		{
			_FileIndex++;
		}

		size_t _Flip2Index = _FileIndex;

		if (_FileContent[_FileIndex] != '+' && _FileContent[_FileIndex] != '-')
		{
			return false;
		}

		_FileIndex++;

		size_t _Axis2Index = _FileIndex;

		if (_FileContent[_FileIndex] != 'X' && _FileContent[_FileIndex] != 'Y')
		{
			return false;
		}

		_FileIndex++;

		if (_FileContent[_FileIndex] != ' ' && _FileContent[_FileIndex] != '\t')
		{
			return false;
		}

		while (_FileContent[_FileIndex] == ' ' || _FileContent[_FileIndex] == '\t')
		{
			_FileIndex++;
		}

		size_t _Number2Index = _FileIndex;

		if (BFW_STRING_TYPE_A("0123456789").find(_FileContent[_FileIndex]) == BFW_STRING_TYPE_A::npos || _FileContent[_FileIndex] == 0)
		{
			return false;
		}

		while (BFW_STRING_TYPE_A("0123456789").find(_FileContent[_FileIndex]) != BFW_STRING_TYPE_A::npos && _FileContent[_FileIndex] != 0)
		{
			_FileIndex++;
		}

		size_t _Number2EndIndex = _FileIndex;

		while (_FileContent[_FileIndex] == ' ' || _FileContent[_FileIndex] == '\t')
		{
			_FileIndex++;
		}

		if (_FileContent[_FileIndex] != '\x0A')
		{
			return false;
		}

		_FileIndex++;

		if (_FileContent[_Axis1Index] == _FileContent[_Axis2Index])
		{
			return false;
		}

		if (_FileContent[_Axis1Index] == 'Y')
		{
			_FlippedX = _FileContent[_Flip2Index] == '-';
			_FlippedY = _FileContent[_Flip1Index] == '-';
		}
		else
		{
			_ColumnMajor = true;
			_FlippedX = _FileContent[_Flip1Index] == '-';
			_FlippedY = _FileContent[_Flip2Index] == '-';
		}

		{
			BFW_STRING_STREAM_TYPE_A _Stream;
			_Stream << BFW_STRING_VIEW_TYPE_A((const BFW_CHAR_TYPE_A*)(_FileContent.GetData()) + _Number1Index, _Number1EndIndex - _Number1Index);
			_Stream >> _Height;
		}

		{
			BFW_STRING_STREAM_TYPE_A _Stream;
			_Stream << BFW_STRING_VIEW_TYPE_A((const BFW_CHAR_TYPE_A*)(_FileContent.GetData()) + _Number2Index, _Number2EndIndex - _Number2Index);
			_Stream >> _Width;
		}
	}

	if (!_Width || !_Height)
	{
		return false;
	}

	uint8_t* _ScanLine = new uint8_t[_Width * 4];

	if (!_ScanLine)
	{
		return false;
	}

	Data = new float[_Width * _Height * 4];

	if (!Data)
	{
		delete[] _ScanLine;
		return false;
	}

	for (size_t _Y = 0; _Y < _Height; _Y++)
	{
		if (!HdrDecodeScanLine(_FileContent, _FileIndex, _ScanLine, _Width))
		{
			delete[] _ScanLine;
			delete[] Data;
			Data = nullptr;
			return false;
		}

		HdrPlaceScanLine(Data, _ScanLine, _Width, _Y);
	}

	if (_FileContent.GetLength() - 1 != _FileIndex)
	{
		delete[] _ScanLine;
		delete[] Data;
		Data = nullptr;
		return false;
	}

	if (_IsXYZE)
	{
		for (size_t _Index = 0; _Index < _Width * _Height; _Index++)
		{
			float _X = Data[_Index * 4 + 0];
			float _Y = Data[_Index * 4 + 1];
			float _Z = Data[_Index * 4 + 2];

			Data[_Index * 4 + 0] = HdrGetRFromXYZ(_X, _Y, _Z);
			Data[_Index * 4 + 1] = HdrGetGFromXYZ(_X, _Y, _Z);
			Data[_Index * 4 + 2] = HdrGetBFromXYZ(_X, _Y, _Z);
		}
	}

	if (_ColumnMajor)
	{
		float* _NewData = new float[_Width * _Height * 4];

		if (!_NewData)
		{
			delete[] _ScanLine;
			delete[] Data;
			Data = nullptr;
			return false;
		}

		{
			size_t _Aux = _Width;
			_Width = _Height;
			_Height = _Aux;
		}

		for (size_t _Y = 0; _Y < _Height; _Y++)
		{
			for (size_t _X = 0; _X < _Width; _X++)
			{
				_NewData[(_X + _Y * _Width) * 4 + 0] = Data[(_Y + _X * _Height) * 4 + 0];
				_NewData[(_X + _Y * _Width) * 4 + 1] = Data[(_Y + _X * _Height) * 4 + 1];
				_NewData[(_X + _Y * _Width) * 4 + 2] = Data[(_Y + _X * _Height) * 4 + 2];
				_NewData[(_X + _Y * _Width) * 4 + 3] = Data[(_Y + _X * _Height) * 4 + 3];
			}
		}

		delete[] Data;
		Data = _NewData;
	}

	if (_FlippedX)
	{
		for (size_t _Y = 0; _Y < _Height; _Y++)
		{
			for (size_t _X = 0; _X < _Width / 2; _X++)
			{
				float _R = Data[(_X + _Y * _Width) * 4 + 0];
				float _G = Data[(_X + _Y * _Width) * 4 + 1];
				float _B = Data[(_X + _Y * _Width) * 4 + 2];
				float _A = Data[(_X + _Y * _Width) * 4 + 3];

				Data[(_X + _Y * _Width) * 4 + 0] = Data[((_Width - 1 - _X) + _Y * _Width) * 4 + 0];
				Data[(_X + _Y * _Width) * 4 + 1] = Data[((_Width - 1 - _X) + _Y * _Width) * 4 + 1];
				Data[(_X + _Y * _Width) * 4 + 2] = Data[((_Width - 1 - _X) + _Y * _Width) * 4 + 2];
				Data[(_X + _Y * _Width) * 4 + 3] = Data[((_Width - 1 - _X) + _Y * _Width) * 4 + 3];

				Data[((_Width - 1 - _X) + _Y * _Width) * 4 + 0] = _R;
				Data[((_Width - 1 - _X) + _Y * _Width) * 4 + 1] = _G;
				Data[((_Width - 1 - _X) + _Y * _Width) * 4 + 2] = _B;
				Data[((_Width - 1 - _X) + _Y * _Width) * 4 + 3] = _A;
			}
		}
	}

	if (_FlippedY != _Flip)
	{
		for (size_t _Y = 0; _Y < _Height / 2; _Y++)
		{
			for (size_t _X = 0; _X < _Width; _X++)
			{
				float _R = Data[(_X + _Y * _Width) * 4 + 0];
				float _G = Data[(_X + _Y * _Width) * 4 + 1];
				float _B = Data[(_X + _Y * _Width) * 4 + 2];
				float _A = Data[(_X + _Y * _Width) * 4 + 3];

				Data[(_X + _Y * _Width) * 4 + 0] = Data[(_X + (_Height - 1 - _Y) * _Width) * 4 + 0];
				Data[(_X + _Y * _Width) * 4 + 1] = Data[(_X + (_Height - 1 - _Y) * _Width) * 4 + 1];
				Data[(_X + _Y * _Width) * 4 + 2] = Data[(_X + (_Height - 1 - _Y) * _Width) * 4 + 2];
				Data[(_X + _Y * _Width) * 4 + 3] = Data[(_X + (_Height - 1 - _Y) * _Width) * 4 + 3];

				Data[(_X + (_Height - 1 - _Y) * _Width) * 4 + 0] = _R;
				Data[(_X + (_Height - 1 - _Y) * _Width) * 4 + 1] = _G;
				Data[(_X + (_Height - 1 - _Y) * _Width) * 4 + 2] = _B;
				Data[(_X + (_Height - 1 - _Y) * _Width) * 4 + 3] = _A;
			}
		}
	}

	delete[] _ScanLine;

	ChannelsCount = 4;
	Width = _Width;
	Height = _Height;

	return true;
}

void BFW::Assets::Hdr::Destroy()
{
	delete[] Data;
	Data = nullptr;
	ChannelsCount = 0;
	Width = 0;
	Height = 0;
}

BFW::Assets::FileContent BFW::Assets::Hdr::Save(const bool _Flip) const
{
	return FileContent();
}

float* BFW::Assets::Hdr::GetData()
{
	return Data;
}

const float* BFW::Assets::Hdr::GetData() const
{
	return Data;
}

const size_t BFW::Assets::Hdr::GetChannelsCount() const
{
	return ChannelsCount;
}

const size_t BFW::Assets::Hdr::GetWidth() const
{
	return Width;
}

const size_t BFW::Assets::Hdr::GetHeight() const
{
	return Height;
}

BFW::Assets::Hdr::operator float* ()
{
	return Data;
}

BFW::Assets::Hdr::operator const float* () const
{
	return Data;
}

float& BFW::Assets::Hdr::operator* ()
{
	return *Data;
}

const float& BFW::Assets::Hdr::operator* () const
{
	return *Data;
}

float* BFW::Assets::Hdr::operator[] (const size_t _PositionY)
{
	return Data + _PositionY * Width * ChannelsCount;
}

const float* BFW::Assets::Hdr::operator* (const size_t _PositionY) const
{
	return Data + _PositionY * Width * ChannelsCount;
}

BFW::Assets::Hdr& BFW::Assets::Hdr::operator= (const Hdr& _Other)
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

	Data = new float[_Other.Width * _Other.Height * _Other.ChannelsCount];

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

BFW::Assets::Hdr& BFW::Assets::Hdr::operator= (Hdr&& _Other) noexcept
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

const bool BFW::Assets::Wave::Load(const FileContent& _FileContent)
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

BFW::Assets::FileContent BFW::Assets::Wave::Save() const
{
	if (!Data)
	{
		return FileContent();
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

	FileContent _FileContent;

	if (!_FileContent.Create(sizeof(WaveFileHeader) + sizeof(WaveChunkHeader) + sizeof(WaveFormat) + sizeof(WaveChunkHeader) + Size + 1))
	{
		return FileContent();
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

void BFW::Assets::Json::SetString(const BFW_STRING_TYPE_A _StringValue)
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



#ifdef BFW_WINDOWS_PLATFORM

BFW::Assets::Manager::Manager() : QueuedBitMaps(), QueuedHdrs(), QueuedWaves(), QueuedJsons(), QueuedResourceBitMaps(), QueuedResourceHdrs(), QueuedResourceWaves(), QueuedResourceJsons(), LoadedBitMaps(), LoadedHdrs(), LoadedWaves(), LoadedJsons(), LoadedResourceBitMaps(), LoadedResourceHdrs(), LoadedResourceWaves(), LoadedResourceJsons(), CachedBitMapNames(), CachedHdrNames(), CachedWaveNames(), CachedJsonNames(), CachedBitMaps(), CachedHdrs(), CachedWaves(), CachedJsons(), LastWriteBitMaps(), LastWriteHdrs(), LastWriteWaves(), LastWriteJsons(), CachedResourceBitMapNames(), CachedResourceHdrNames(), CachedResourceWaveNames(), CachedResourceJsonNames(), CachedResourceBitMaps(), CachedResourceHdrs(), CachedResourceWaves(), CachedResourceJsons()
{

}

BFW::Assets::Manager::Manager(Manager&& _Other) noexcept : QueuedBitMaps((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedBitMaps)), QueuedHdrs((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedHdrs)), QueuedWaves((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedWaves)), QueuedJsons((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedJsons)), QueuedResourceBitMaps((Vector<size_t>&&)(_Other.QueuedResourceBitMaps)), QueuedResourceHdrs((Vector<size_t>&&)(_Other.QueuedResourceHdrs)), QueuedResourceWaves((Vector<size_t>&&)(_Other.QueuedResourceWaves)), QueuedResourceJsons((Vector<size_t>&&)(_Other.QueuedResourceJsons)), LoadedBitMaps((Trie<SharedPointer<BitMap>>&&)(_Other.LoadedBitMaps)), LoadedHdrs((Trie<SharedPointer<Hdr>>&&)(_Other.LoadedHdrs)), LoadedWaves((Trie<SharedPointer<Wave>>&&)(_Other.LoadedWaves)), LoadedJsons((Trie<SharedPointer<Json>>&&)(_Other.LoadedJsons)), LoadedResourceBitMaps((Trie<SharedPointer<BitMap>>&&)(_Other.LoadedResourceBitMaps)), LoadedResourceHdrs((Trie<SharedPointer<Hdr>>&&)(_Other.LoadedResourceHdrs)), LoadedResourceWaves((Trie<SharedPointer<Wave>>&&)(_Other.LoadedResourceWaves)), LoadedResourceJsons((Trie<SharedPointer<Json>>&&)(_Other.LoadedResourceJsons)), CachedBitMapNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedBitMapNames)), CachedHdrNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedHdrNames)), CachedWaveNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedWaveNames)), CachedJsonNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedJsonNames)), CachedBitMaps((Trie<WeakPointer<BitMap>>&&)(_Other.CachedBitMaps)), CachedHdrs((Trie<WeakPointer<Hdr>>&&)(_Other.CachedHdrs)), CachedWaves((Trie<WeakPointer<Wave>>&&)(_Other.CachedWaves)), CachedJsons((Trie<WeakPointer<Json>>&&)(_Other.CachedJsons)), LastWriteBitMaps((Trie<uint64_t>&&)(_Other.LastWriteBitMaps)), LastWriteHdrs((Trie<uint64_t>&&)(_Other.LastWriteHdrs)), LastWriteWaves((Trie<uint64_t>&&)(_Other.LastWriteWaves)), LastWriteJsons((Trie<uint64_t>&&)(_Other.LastWriteJsons)), CachedResourceBitMapNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceBitMapNames)), CachedResourceHdrNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceHdrNames)), CachedResourceWaveNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceWaveNames)), CachedResourceJsonNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceJsonNames)), CachedResourceBitMaps((Trie<WeakPointer<BitMap>>&&)(_Other.CachedResourceBitMaps)), CachedResourceHdrs((Trie<WeakPointer<Hdr>>&&)(_Other.CachedResourceHdrs)), CachedResourceWaves((Trie<WeakPointer<Wave>>&&)(_Other.CachedResourceWaves)), CachedResourceJsons((Trie<WeakPointer<Json>>&&)(_Other.CachedResourceJsons))
{

}

#endif

#if defined BFW_LINUX_PLATFORM || defined BFW_ESP32_PLATFORM

BFW::Assets::Manager::Manager() : QueuedBitMaps(), QueuedHdrs(), QueuedWaves(), QueuedJsons(), LoadedBitMaps(), LoadedHdrs(), LoadedWaves(), LoadedJsons(), CachedBitMapNames(), CachedHdrNames(), CachedWaveNames(), CachedJsonNames(), CachedBitMaps(), CachedHdrs(), CachedWaves(), CachedJsons(), LastWriteBitMaps(), LastWriteHdrs(), LastWriteWaves(), LastWriteJsons()
{

}

BFW::Assets::Manager::Manager(Manager&& _Other) noexcept : QueuedBitMaps((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedBitMaps)), QueuedHdrs((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedHdrs)), QueuedWaves((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedWaves)), QueuedJsons((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedJsons)), LoadedBitMaps((Trie<SharedPointer<BitMap>>&&)(_Other.LoadedBitMaps)), LoadedHdrs((Trie<SharedPointer<Hdr>>&&)(_Other.LoadedHdrs)), LoadedWaves((Trie<SharedPointer<Wave>>&&)(_Other.LoadedWaves)), LoadedJsons((Trie<SharedPointer<Json>>&&)(_Other.LoadedJsons)), CachedBitMapNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedBitMapNames)), CachedHdrNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedHdrNames)), CachedWaveNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedWaveNames)), CachedJsonNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedJsonNames)), CachedBitMaps((Trie<WeakPointer<BitMap>>&&)(_Other.CachedBitMaps)), CachedHdrs((Trie<WeakPointer<Hdr>>&&)(_Other.CachedHdrs)), CachedWaves((Trie<WeakPointer<Wave>>&&)(_Other.CachedWaves)), CachedJsons((Trie<WeakPointer<Json>>&&)(_Other.CachedJsons)), LastWriteBitMaps((Trie<uint64_t>&&)(_Other.LastWriteBitMaps)), LastWriteHdrs((Trie<uint64_t>&&)(_Other.LastWriteHdrs)), LastWriteWaves((Trie<uint64_t>&&)(_Other.LastWriteWaves)), LastWriteJsons((Trie<uint64_t>&&)(_Other.LastWriteJsons))
{

}

#endif

BFW::Assets::Manager::~Manager()
{

}

void BFW::Assets::Manager::QueueBitMap(const BFW_CHAR_TYPE* _Name)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) == BFW_STRING_PREFIX("Dynamic/"))
	{
		throw nullptr;
	}

	bool _Found = false;

	for (size_t _Index = 0; _Index < QueuedBitMaps.GetSize(); _Index++)
	{
		if (QueuedBitMaps[_Index] == _Name)
		{
			_Found = true;
		}
	}

	if (_Found)
	{
		return;
	}

	QueuedBitMaps.EmplaceBack(_Name);
}

void BFW::Assets::Manager::QueueHdr(const BFW_CHAR_TYPE* _Name)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) == BFW_STRING_PREFIX("Dynamic/"))
	{
		throw nullptr;
	}

	bool _Found = false;

	for (size_t _Index = 0; _Index < QueuedHdrs.GetSize(); _Index++)
	{
		if (QueuedHdrs[_Index] == _Name)
		{
			_Found = true;
		}
	}

	if (_Found)
	{
		return;
	}

	QueuedHdrs.EmplaceBack(_Name);
}

void BFW::Assets::Manager::QueueWave(const BFW_CHAR_TYPE* _Name)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) == BFW_STRING_PREFIX("Dynamic/"))
	{
		throw nullptr;
	}

	bool _Found = false;

	for (size_t _Index = 0; _Index < QueuedWaves.GetSize(); _Index++)
	{
		if (QueuedWaves[_Index] == _Name)
		{
			_Found = true;
		}
	}

	if (_Found)
	{
		return;
	}

	QueuedWaves.EmplaceBack(_Name);
}

void BFW::Assets::Manager::QueueJson(const BFW_CHAR_TYPE* _Name)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) == BFW_STRING_PREFIX("Dynamic/"))
	{
		throw nullptr;
	}

	bool _Found = false;

	for (size_t _Index = 0; _Index < QueuedJsons.GetSize(); _Index++)
	{
		if (QueuedJsons[_Index] == _Name)
		{
			_Found = true;
		}
	}

	if (_Found)
	{
		return;
	}

	QueuedJsons.EmplaceBack(_Name);
}

#ifdef BFW_WINDOWS_PLATFORM

void BFW::Assets::Manager::QueueResourceBitMap(const size_t _Id)
{
	bool _Found = false;

	for (size_t _Index = 0; _Index < QueuedResourceBitMaps.GetSize(); _Index++)
	{
		if (QueuedResourceBitMaps[_Index] == _Id)
		{
			_Found = true;
		}
	}

	if (_Found)
	{
		return;
	}

	QueuedResourceBitMaps.PushBack(_Id);
}

void BFW::Assets::Manager::QueueResourceHdr(const size_t _Id)
{
	bool _Found = false;

	for (size_t _Index = 0; _Index < QueuedResourceHdrs.GetSize(); _Index++)
	{
		if (QueuedResourceHdrs[_Index] == _Id)
		{
			_Found = true;
		}
	}

	if (_Found)
	{
		return;
	}

	QueuedResourceHdrs.PushBack(_Id);
}

void BFW::Assets::Manager::QueueResourceWave(const size_t _Id)
{
	bool _Found = false;

	for (size_t _Index = 0; _Index < QueuedResourceWaves.GetSize(); _Index++)
	{
		if (QueuedResourceWaves[_Index] == _Id)
		{
			_Found = true;
		}
	}

	if (_Found)
	{
		return;
	}

	QueuedResourceWaves.PushBack(_Id);
}

void BFW::Assets::Manager::QueueResourceJson(const size_t _Id)
{
	bool _Found = false;

	for (size_t _Index = 0; _Index < QueuedResourceJsons.GetSize(); _Index++)
	{
		if (QueuedResourceJsons[_Index] == _Id)
		{
			_Found = true;
		}
	}

	if (_Found)
	{
		return;
	}

	QueuedResourceJsons.PushBack(_Id);
}

#endif

void BFW::Assets::Manager::Flush()
{
	RefreshCache();

	bool _Fail = false;
	Vector<std::thread> _Threads;

	for (size_t _Index = 0; _Index < QueuedBitMaps.GetSize(); _Index++)
	{
		if (LoadedBitMaps.GetData(QueuedBitMaps[_Index].c_str()))
		{
			QueuedBitMaps.Erase(_Index);
			_Index--;
			continue;
		}

		{
			WeakPointer<BitMap>* _CachedWeak = CachedBitMaps.GetData(QueuedBitMaps[_Index].c_str());

			if (_CachedWeak)
			{
				SharedPointer<BitMap> _CachedShared = _CachedWeak->Lock();

				if ((BitMap*)(_CachedShared))
				{
					LoadedBitMaps.Emplace(QueuedBitMaps[_Index].c_str(), (SharedPointer<BitMap>&&)(_CachedShared));
					QueuedBitMaps.Erase(_Index);
					_Index--;
					continue;
				}
			}
		}

		SharedPointer<BitMap> _Asset = SharedPointer<BitMap>::MakeShared(BitMap());

		CachedBitMaps.Emplace(QueuedBitMaps[_Index].c_str(), _Asset);
		LastWriteBitMaps.Push(QueuedBitMaps[_Index].c_str(), 0);
		LoadedBitMaps.Emplace(QueuedBitMaps[_Index].c_str(), (SharedPointer<BitMap>&&)(_Asset));

		bool _Found = false;

		for (size_t _NameIndex = 0; _NameIndex < CachedBitMapNames.GetSize(); _NameIndex++)
		{
			if (CachedBitMapNames[_NameIndex] == QueuedBitMaps[_Index])
			{
				_Found = true;
				break;
			}
		}

		if (!_Found)
		{
			CachedBitMapNames.PushBack(QueuedBitMaps[_Index]);
		}
	}

	for (size_t _Index = 0; _Index < QueuedBitMaps.GetSize(); _Index++)
	{
		_Threads.EmplaceBack
		(
			std::thread
			(
				[](bool& _Fail, const BFW_CHAR_TYPE* _Name, SharedPointer<BitMap> _Asset, uint64_t& _LastWrite)
				{
					std::ifstream _InStream;

					_InStream.open(_Name, std::ios::binary);

					if (!_InStream.is_open())
					{
						_Fail = true;
						return;
					}

					try
					{
						_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
					}
					catch (...)
					{
						_Fail = true;
						return;
					}

					FileContent _FileContent;

					if (!_FileContent.Load(_InStream))
					{
						_Fail = true;
						return;
					}

					if (!_Asset->Load(_FileContent))
					{
						_Fail = true;
						return;
					}
				},
				std::ref(_Fail),
				QueuedBitMaps[_Index].c_str(),
				*LoadedBitMaps.GetData(QueuedBitMaps[_Index].c_str()),
				std::ref(*LastWriteBitMaps.GetData(QueuedBitMaps[_Index].c_str()))
			)
		);
	}

	for (size_t _Index = 0; _Index < QueuedHdrs.GetSize(); _Index++)
	{
		if (LoadedHdrs.GetData(QueuedHdrs[_Index].c_str()))
		{
			QueuedHdrs.Erase(_Index);
			_Index--;
			continue;
		}

		{
			WeakPointer<Hdr>* _CachedWeak = CachedHdrs.GetData(QueuedHdrs[_Index].c_str());

			if (_CachedWeak)
			{
				SharedPointer<Hdr> _CachedShared = _CachedWeak->Lock();

				if ((Hdr*)(_CachedShared))
				{
					LoadedHdrs.Emplace(QueuedHdrs[_Index].c_str(), (SharedPointer<Hdr>&&)(_CachedShared));
					QueuedHdrs.Erase(_Index);
					_Index--;
					continue;
				}
			}
		}

		SharedPointer<Hdr> _Asset = SharedPointer<Hdr>::MakeShared(Hdr());

		CachedHdrs.Emplace(QueuedHdrs[_Index].c_str(), _Asset);
		LastWriteHdrs.Push(QueuedHdrs[_Index].c_str(), 0);
		LoadedHdrs.Emplace(QueuedHdrs[_Index].c_str(), (SharedPointer<Hdr>&&)(_Asset));

		bool _Found = false;

		for (size_t _NameIndex = 0; _NameIndex < CachedHdrNames.GetSize(); _NameIndex++)
		{
			if (CachedHdrNames[_NameIndex] == QueuedHdrs[_Index])
			{
				_Found = true;
				break;
			}
		}

		if (!_Found)
		{
			CachedHdrNames.PushBack(QueuedHdrs[_Index]);
		}
	}

	for (size_t _Index = 0; _Index < QueuedHdrs.GetSize(); _Index++)
	{
		_Threads.EmplaceBack
		(
			std::thread
			(
				[](bool& _Fail, const BFW_CHAR_TYPE* _Name, SharedPointer<Hdr> _Asset, uint64_t& _LastWrite)
				{
					std::ifstream _InStream;

					_InStream.open(_Name, std::ios::binary);

					if (!_InStream.is_open())
					{
						_Fail = true;
						return;
					}

					try
					{
						_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
					}
					catch (...)
					{
						_Fail = true;
						return;
					}

					FileContent _FileContent;

					if (!_FileContent.Load(_InStream))
					{
						_Fail = true;
						return;
					}

					if (!_Asset->Load(_FileContent))
					{
						_Fail = true;
						return;
					}
				},
				std::ref(_Fail),
				QueuedHdrs[_Index].c_str(),
				*LoadedHdrs.GetData(QueuedHdrs[_Index].c_str()),
				std::ref(*LastWriteHdrs.GetData(QueuedHdrs[_Index].c_str()))
			)
		);
	}

	for (size_t _Index = 0; _Index < QueuedWaves.GetSize(); _Index++)
	{
		if (LoadedWaves.GetData(QueuedWaves[_Index].c_str()))
		{
			QueuedWaves.Erase(_Index);
			_Index--;
			continue;
		}

		{
			WeakPointer<Wave>* _CachedWeak = CachedWaves.GetData(QueuedWaves[_Index].c_str());

			if (_CachedWeak)
			{
				SharedPointer<Wave> _CachedShared = _CachedWeak->Lock();

				if ((Wave*)(_CachedShared))
				{
					LoadedWaves.Emplace(QueuedWaves[_Index].c_str(), (SharedPointer<Wave>&&)(_CachedShared));
					QueuedWaves.Erase(_Index);
					_Index--;
					continue;
				}
			}
		}

		SharedPointer<Wave> _Asset = SharedPointer<Wave>::MakeShared(Wave());

		CachedWaves.Emplace(QueuedWaves[_Index].c_str(), _Asset);
		LastWriteWaves.Push(QueuedWaves[_Index].c_str(), 0);
		LoadedWaves.Emplace(QueuedWaves[_Index].c_str(), (SharedPointer<Wave>&&)(_Asset));

		bool _Found = false;

		for (size_t _NameIndex = 0; _NameIndex < CachedWaveNames.GetSize(); _NameIndex++)
		{
			if (CachedWaveNames[_NameIndex] == QueuedWaves[_Index])
			{
				_Found = true;
				break;
			}
		}

		if (!_Found)
		{
			CachedWaveNames.PushBack(QueuedWaves[_Index]);
		}
	}

	for (size_t _Index = 0; _Index < QueuedWaves.GetSize(); _Index++)
	{
		_Threads.EmplaceBack
		(
			std::thread
			(
				[](bool& _Fail, const BFW_CHAR_TYPE* _Name, SharedPointer<Wave> _Asset, uint64_t& _LastWrite)
				{
					std::ifstream _InStream;

					_InStream.open(_Name, std::ios::binary);

					if (!_InStream.is_open())
					{
						_Fail = true;
						return;
					}

					try
					{
						_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
					}
					catch (...)
					{
						_Fail = true;
						return;
					}

					FileContent _FileContent;

					if (!_FileContent.Load(_InStream))
					{
						_Fail = true;
						return;
					}

					if (!_Asset->Load(_FileContent))
					{
						_Fail = true;
						return;
					}
				},
				std::ref(_Fail),
				QueuedWaves[_Index].c_str(),
				*LoadedWaves.GetData(QueuedWaves[_Index].c_str()),
				std::ref(*LastWriteWaves.GetData(QueuedWaves[_Index].c_str()))
			)
		);
	}

	for (size_t _Index = 0; _Index < QueuedJsons.GetSize(); _Index++)
	{
		if (LoadedJsons.GetData(QueuedJsons[_Index].c_str()))
		{
			QueuedJsons.Erase(_Index);
			_Index--;
			continue;
		}

		{
			WeakPointer<Json>* _CachedWeak = CachedJsons.GetData(QueuedJsons[_Index].c_str());

			if (_CachedWeak)
			{
				SharedPointer<Json> _CachedShared = _CachedWeak->Lock();

				if ((Json*)(_CachedShared))
				{
					LoadedJsons.Emplace(QueuedJsons[_Index].c_str(), (SharedPointer<Json>&&)(_CachedShared));
					QueuedJsons.Erase(_Index);
					_Index--;
					continue;
				}
			}
		}

		SharedPointer<Json> _Asset = SharedPointer<Json>::MakeShared(Json());

		CachedJsons.Emplace(QueuedJsons[_Index].c_str(), _Asset);
		LastWriteJsons.Push(QueuedJsons[_Index].c_str(), 0);
		LoadedJsons.Emplace(QueuedJsons[_Index].c_str(), (SharedPointer<Json>&&)(_Asset));

		bool _Found = false;

		for (size_t _NameIndex = 0; _NameIndex < CachedJsonNames.GetSize(); _NameIndex++)
		{
			if (CachedJsonNames[_NameIndex] == QueuedJsons[_Index])
			{
				_Found = true;
				break;
			}
		}

		if (!_Found)
		{
			CachedJsonNames.PushBack(QueuedJsons[_Index]);
		}
	}

	for (size_t _Index = 0; _Index < QueuedJsons.GetSize(); _Index++)
	{
		_Threads.EmplaceBack
		(
			std::thread
			(
				[](bool& _Fail, const BFW_CHAR_TYPE* _Name, SharedPointer<Json> _Asset, uint64_t& _LastWrite)
				{
					std::ifstream _InStream;

					_InStream.open(_Name, std::ios::binary);

					if (!_InStream.is_open())
					{
						_Fail = true;
						return;
					}

					try
					{
						_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
					}
					catch (...)
					{
						_Fail = true;
						return;
					}

					FileContent _FileContent;

					if (!_FileContent.Load(_InStream))
					{
						_Fail = true;
						return;
					}

					if (!_Asset->Load(_FileContent))
					{
						_Fail = true;
						return;
					}
				},
				std::ref(_Fail),
				QueuedJsons[_Index].c_str(),
				*LoadedJsons.GetData(QueuedJsons[_Index].c_str()),
				std::ref(*LastWriteJsons.GetData(QueuedJsons[_Index].c_str()))
			)
		);
	}

#ifdef BFW_WINDOWS_PLATFORM

	for (size_t _Index = 0; _Index < QueuedResourceBitMaps.GetSize(); _Index++)
	{
		if (LoadedResourceBitMaps.GetData(BFW_TO_STRING_PTR(QueuedResourceBitMaps[_Index])))
		{
			QueuedResourceBitMaps.Erase(_Index);
			_Index--;
			continue;
		}

		{
			WeakPointer<BitMap>* _CachedWeak = CachedResourceBitMaps.GetData(BFW_TO_STRING_PTR(QueuedResourceBitMaps[_Index]));

			if (_CachedWeak)
			{
				SharedPointer<BitMap> _CachedShared = _CachedWeak->Lock();

				if ((BitMap*)(_CachedShared))
				{
					LoadedResourceBitMaps.Emplace(BFW_TO_STRING_PTR(QueuedResourceBitMaps[_Index]), (SharedPointer<BitMap>&&)(_CachedShared));
					QueuedResourceBitMaps.Erase(_Index);
					_Index--;
					continue;
				}
			}
		}

		SharedPointer<BitMap> _Asset = SharedPointer<BitMap>::MakeShared(BitMap());

		CachedResourceBitMaps.Emplace(BFW_TO_STRING_PTR(QueuedResourceBitMaps[_Index]), _Asset);
		LoadedResourceBitMaps.Emplace(BFW_TO_STRING_PTR(QueuedResourceBitMaps[_Index]), (SharedPointer<BitMap>&&)(_Asset));

		bool _Found = false;

		for (size_t _NameIndex = 0; _NameIndex < CachedResourceBitMapNames.GetSize(); _NameIndex++)
		{
			if (CachedResourceBitMapNames[_NameIndex] == BFW_TO_STRING_PTR(QueuedResourceBitMaps[_Index]))
			{
				_Found = true;
				break;
			}
		}

		if (!_Found)
		{
			CachedResourceBitMapNames.PushBack(BFW_TO_STRING_PTR(QueuedResourceBitMaps[_Index]));
		}
	}

	for (size_t _Index = 0; _Index < QueuedResourceBitMaps.GetSize(); _Index++)
	{
		_Threads.EmplaceBack
		(
			std::thread
			(
				[](bool& _Fail, const size_t _Id, SharedPointer<BitMap> _Asset)
				{
					FileContent _FileContent;

					if (!_FileContent.Load(BFW_BMP_RESOURCE, _Id))
					{
						_Fail = true;
						return;
					}

					if (!_Asset->Load(_FileContent))
					{
						_Fail = true;
						return;
					}
				},
				std::ref(_Fail),
				QueuedResourceBitMaps[_Index],
				*LoadedResourceBitMaps.GetData(BFW_TO_STRING_PTR(QueuedResourceBitMaps[_Index]))
			)
		);
	}

	for (size_t _Index = 0; _Index < QueuedResourceHdrs.GetSize(); _Index++)
	{
		if (LoadedResourceHdrs.GetData(BFW_TO_STRING_PTR(QueuedResourceHdrs[_Index])))
		{
			QueuedResourceHdrs.Erase(_Index);
			_Index--;
			continue;
		}

		{
			WeakPointer<Hdr>* _CachedWeak = CachedResourceHdrs.GetData(BFW_TO_STRING_PTR(QueuedResourceHdrs[_Index]));

			if (_CachedWeak)
			{
				SharedPointer<Hdr> _CachedShared = _CachedWeak->Lock();

				if ((Hdr*)(_CachedShared))
				{
					LoadedResourceHdrs.Emplace(BFW_TO_STRING_PTR(QueuedResourceHdrs[_Index]), (SharedPointer<Hdr>&&)(_CachedShared));
					QueuedResourceHdrs.Erase(_Index);
					_Index--;
					continue;
				}
			}
		}

		SharedPointer<Hdr> _Asset = SharedPointer<Hdr>::MakeShared(Hdr());

		CachedResourceHdrs.Emplace(BFW_TO_STRING_PTR(QueuedResourceHdrs[_Index]), _Asset);
		LoadedResourceHdrs.Emplace(BFW_TO_STRING_PTR(QueuedResourceHdrs[_Index]), (SharedPointer<Hdr>&&)(_Asset));

		bool _Found = false;

		for (size_t _NameIndex = 0; _NameIndex < CachedResourceHdrNames.GetSize(); _NameIndex++)
		{
			if (CachedResourceHdrNames[_NameIndex] == BFW_TO_STRING_PTR(QueuedResourceHdrs[_Index]))
			{
				_Found = true;
				break;
			}
		}

		if (!_Found)
		{
			CachedResourceHdrNames.PushBack(BFW_TO_STRING_PTR(QueuedResourceHdrs[_Index]));
		}
	}

	for (size_t _Index = 0; _Index < QueuedResourceHdrs.GetSize(); _Index++)
	{
		_Threads.EmplaceBack
		(
			std::thread
			(
				[](bool& _Fail, const size_t _Id, SharedPointer<Hdr> _Asset)
				{
					FileContent _FileContent;

					if (!_FileContent.Load(BFW_HDR_RESOURCE, _Id))
					{
						_Fail = true;
						return;
					}

					if (!_Asset->Load(_FileContent))
					{
						_Fail = true;
						return;
					}
				},
				std::ref(_Fail),
				QueuedResourceHdrs[_Index],
				*LoadedResourceHdrs.GetData(BFW_TO_STRING_PTR(QueuedResourceHdrs[_Index]))
			)
		);
	}

	for (size_t _Index = 0; _Index < QueuedResourceWaves.GetSize(); _Index++)
	{
		if (LoadedResourceWaves.GetData(BFW_TO_STRING_PTR(QueuedResourceWaves[_Index])))
		{
			QueuedResourceWaves.Erase(_Index);
			_Index--;
			continue;
		}

		{
			WeakPointer<Wave>* _CachedWeak = CachedResourceWaves.GetData(BFW_TO_STRING_PTR(QueuedResourceWaves[_Index]));

			if (_CachedWeak)
			{
				SharedPointer<Wave> _CachedShared = _CachedWeak->Lock();

				if ((Wave*)(_CachedShared))
				{
					LoadedResourceWaves.Emplace(BFW_TO_STRING_PTR(QueuedResourceWaves[_Index]), (SharedPointer<Wave>&&)(_CachedShared));
					QueuedResourceWaves.Erase(_Index);
					_Index--;
					continue;
				}
			}
		}

		SharedPointer<Wave> _Asset = SharedPointer<Wave>::MakeShared(Wave());

		CachedResourceWaves.Emplace(BFW_TO_STRING_PTR(QueuedResourceWaves[_Index]), _Asset);
		LoadedResourceWaves.Emplace(BFW_TO_STRING_PTR(QueuedResourceWaves[_Index]), (SharedPointer<Wave>&&)(_Asset));

		bool _Found = false;

		for (size_t _NameIndex = 0; _NameIndex < CachedResourceWaveNames.GetSize(); _NameIndex++)
		{
			if (CachedResourceWaveNames[_NameIndex] == BFW_TO_STRING_PTR(QueuedResourceWaves[_Index]))
			{
				_Found = true;
				break;
			}
		}

		if (!_Found)
		{
			CachedResourceWaveNames.PushBack(BFW_TO_STRING_PTR(QueuedResourceWaves[_Index]));
		}
	}

	for (size_t _Index = 0; _Index < QueuedResourceWaves.GetSize(); _Index++)
	{
		_Threads.EmplaceBack
		(
			std::thread
			(
				[](bool& _Fail, const size_t _Id, SharedPointer<Wave> _Asset)
				{
					FileContent _FileContent;

					if (!_FileContent.Load(BFW_WAV_RESOURCE, _Id))
					{
						_Fail = true;
						return;
					}

					if (!_Asset->Load(_FileContent))
					{
						_Fail = true;
						return;
					}
				},
				std::ref(_Fail),
				QueuedResourceWaves[_Index],
				*LoadedResourceWaves.GetData(BFW_TO_STRING_PTR(QueuedResourceWaves[_Index]))
			)
		);
	}

	for (size_t _Index = 0; _Index < QueuedResourceJsons.GetSize(); _Index++)
	{
		if (LoadedResourceJsons.GetData(BFW_TO_STRING_PTR(QueuedResourceJsons[_Index])))
		{
			QueuedResourceJsons.Erase(_Index);
			_Index--;
			continue;
		}

		{
			WeakPointer<Json>* _CachedWeak = CachedResourceJsons.GetData(BFW_TO_STRING_PTR(QueuedResourceJsons[_Index]));

			if (_CachedWeak)
			{
				SharedPointer<Json> _CachedShared = _CachedWeak->Lock();

				if ((Json*)(_CachedShared))
				{
					LoadedResourceJsons.Emplace(BFW_TO_STRING_PTR(QueuedResourceJsons[_Index]), (SharedPointer<Json>&&)(_CachedShared));
					QueuedResourceJsons.Erase(_Index);
					_Index--;
					continue;
				}
			}
		}

		SharedPointer<Json> _Asset = SharedPointer<Json>::MakeShared(Json());

		CachedResourceJsons.Emplace(BFW_TO_STRING_PTR(QueuedResourceJsons[_Index]), _Asset);
		LoadedResourceJsons.Emplace(BFW_TO_STRING_PTR(QueuedResourceJsons[_Index]), (SharedPointer<Json>&&)(_Asset));

		bool _Found = false;

		for (size_t _NameIndex = 0; _NameIndex < CachedResourceJsonNames.GetSize(); _NameIndex++)
		{
			if (CachedResourceJsonNames[_NameIndex] == BFW_TO_STRING_PTR(QueuedResourceJsons[_Index]))
			{
				_Found = true;
				break;
			}
		}

		if (!_Found)
		{
			CachedResourceJsonNames.PushBack(BFW_TO_STRING_PTR(QueuedResourceJsons[_Index]));
		}
	}

	for (size_t _Index = 0; _Index < QueuedResourceJsons.GetSize(); _Index++)
	{
		_Threads.EmplaceBack
		(
			std::thread
			(
				[](bool& _Fail, const size_t _Id, SharedPointer<Json> _Asset)
				{
					FileContent _FileContent;

					if (!_FileContent.Load(BFW_JSON_RESOURCE, _Id))
					{
						_Fail = true;
						return;
					}

					if (!_Asset->Load(_FileContent))
					{
						_Fail = true;
						return;
					}
				},
				std::ref(_Fail),
				QueuedResourceJsons[_Index],
				*LoadedResourceJsons.GetData(BFW_TO_STRING_PTR(QueuedResourceJsons[_Index]))
			)
		);
	}

	for (size_t _Index = 0; _Index < _Threads.GetSize(); _Index++)
	{
		_Threads[_Index].join();
	}

	if (_Fail)
	{
		throw nullptr;
	}

#endif

	QueuedBitMaps.Clear();
	QueuedHdrs.Clear();
	QueuedWaves.Clear();
	QueuedJsons.Clear();

#ifdef BFW_WINDOWS_PLATFORM

	QueuedResourceBitMaps.Clear();
	QueuedResourceHdrs.Clear();
	QueuedResourceWaves.Clear();
	QueuedResourceJsons.Clear();

#endif
}

void BFW::Assets::Manager::AddDynamicBitMap(const BFW_CHAR_TYPE* _Name, SharedPointer<BitMap>& _Asset)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) != BFW_STRING_PREFIX("Dynamic/") || (BitMap*)(_Asset))
	{
		throw nullptr;
	}

	LoadedBitMaps.Push(_Name, _Asset);
	CachedBitMaps.Emplace(_Name, _Asset);

	bool _Found = false;

	for (size_t _Index = 0; _Index < CachedBitMapNames.GetSize(); _Index++)
	{
		if (CachedBitMapNames[_Index] == _Name)
		{
			_Found = true;
			break;
		}
	}

	if (!_Found)
	{
		CachedBitMapNames.PushBack(_Name);
	}
}

void BFW::Assets::Manager::AddDynamicHdr(const BFW_CHAR_TYPE* _Name, SharedPointer<Hdr>& _Asset)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) != BFW_STRING_PREFIX("Dynamic/") || (Hdr*)(_Asset))
	{
		throw nullptr;
	}

	LoadedHdrs.Push(_Name, _Asset);
	CachedHdrs.Emplace(_Name, _Asset);

	bool _Found = false;

	for (size_t _Index = 0; _Index < CachedHdrNames.GetSize(); _Index++)
	{
		if (CachedHdrNames[_Index] == _Name)
		{
			_Found = true;
			break;
		}
	}

	if (!_Found)
	{
		CachedHdrNames.PushBack(_Name);
	}
}

void BFW::Assets::Manager::AddDynamicWave(const BFW_CHAR_TYPE* _Name, SharedPointer<Wave>& _Asset)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) != BFW_STRING_PREFIX("Dynamic/") || (Wave*)(_Asset))
	{
		throw nullptr;
	}

	LoadedWaves.Push(_Name, _Asset);
	CachedWaves.Emplace(_Name, _Asset);

	bool _Found = false;

	for (size_t _Index = 0; _Index < CachedWaveNames.GetSize(); _Index++)
	{
		if (CachedWaveNames[_Index] == _Name)
		{
			_Found = true;
			break;
		}
	}

	if (!_Found)
	{
		CachedWaveNames.PushBack(_Name);
	}
}

void BFW::Assets::Manager::AddDynamicJson(const BFW_CHAR_TYPE* _Name, SharedPointer<Json>& _Asset)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) != BFW_STRING_PREFIX("Dynamic/") || (Json*)(_Asset))
	{
		throw nullptr;
	}

	LoadedJsons.Push(_Name, _Asset);
	CachedJsons.Emplace(_Name, _Asset);

	bool _Found = false;

	for (size_t _Index = 0; _Index < CachedJsonNames.GetSize(); _Index++)
	{
		if (CachedJsonNames[_Index] == _Name)
		{
			_Found = true;
			break;
		}
	}

	if (!_Found)
	{
		CachedJsonNames.PushBack(_Name);
	}
}

void BFW::Assets::Manager::AddDynamicBitMapRef(const BFW_CHAR_TYPE* _Name, SharedPointer<BitMap>& _Asset)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) != BFW_STRING_PREFIX("Dynamic/") || (BitMap*)(_Asset))
	{
		throw nullptr;
	}

	CachedBitMaps.Emplace(_Name, _Asset);

	bool _Found = false;

	for (size_t _Index = 0; _Index < CachedBitMapNames.GetSize(); _Index++)
	{
		if (CachedBitMapNames[_Index] == _Name)
		{
			_Found = true;
			break;
		}
	}

	if (!_Found)
	{
		CachedBitMapNames.PushBack(_Name);
	}
}

void BFW::Assets::Manager::AddDynamicHdrRef(const BFW_CHAR_TYPE* _Name, SharedPointer<Hdr>& _Asset)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) != BFW_STRING_PREFIX("Dynamic/") || (Hdr*)(_Asset))
	{
		throw nullptr;
	}

	CachedHdrs.Emplace(_Name, _Asset);

	bool _Found = false;

	for (size_t _Index = 0; _Index < CachedHdrNames.GetSize(); _Index++)
	{
		if (CachedHdrNames[_Index] == _Name)
		{
			_Found = true;
			break;
		}
	}

	if (!_Found)
	{
		CachedHdrNames.PushBack(_Name);
	}
}

void BFW::Assets::Manager::AddDynamicWaveRef(const BFW_CHAR_TYPE* _Name, SharedPointer<Wave>& _Asset)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) != BFW_STRING_PREFIX("Dynamic/") || (Wave*)(_Asset))
	{
		throw nullptr;
	}

	CachedWaves.Emplace(_Name, _Asset);

	bool _Found = false;

	for (size_t _Index = 0; _Index < CachedWaveNames.GetSize(); _Index++)
	{
		if (CachedWaveNames[_Index] == _Name)
		{
			_Found = true;
			break;
		}
	}

	if (!_Found)
	{
		CachedWaveNames.PushBack(_Name);
	}
}

void BFW::Assets::Manager::AddDynamicJsonRef(const BFW_CHAR_TYPE* _Name, SharedPointer<Json>& _Asset)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) != BFW_STRING_PREFIX("Dynamic/") || (Json*)(_Asset))
	{
		throw nullptr;
	}

	CachedJsons.Emplace(_Name, _Asset);

	bool _Found = false;

	for (size_t _Index = 0; _Index < CachedJsonNames.GetSize(); _Index++)
	{
		if (CachedJsonNames[_Index] == _Name)
		{
			_Found = true;
			break;
		}
	}

	if (!_Found)
	{
		CachedJsonNames.PushBack(_Name);
	}
}

void BFW::Assets::Manager::Update()
{
	RefreshCache();

	Vector<std::thread> _Threads;

	for (size_t _Index = 0; _Index < CachedBitMapNames.GetSize(); _Index++)
	{
		if (CachedBitMapNames[_Index].substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) == BFW_STRING_PREFIX("Dynamic/"))
		{
			continue;
		}

		uint64_t _LastWrite = 0;

		try
		{
			_LastWrite = std::filesystem::directory_entry(CachedBitMapNames[_Index]).last_write_time().time_since_epoch().count();
		}
		catch (...)
		{
			continue;
		}

		uint64_t& _OldLastWrite = *LastWriteBitMaps.GetData(CachedBitMapNames[_Index].c_str());

		if (_LastWrite == _OldLastWrite)
		{
			continue;
		}

		SharedPointer<BitMap> _CachedShared = CachedBitMaps.GetData(CachedBitMapNames[_Index].c_str())->Lock();

		if (!(BitMap*)(_CachedShared))
		{
			continue;
		}

		_Threads.EmplaceBack
		(
			std::thread
			(
				[](const BFW_CHAR_TYPE* _Name, SharedPointer<BitMap> _CachedShared, uint64_t& _OldLastWrite, const uint64_t _LastWrite)
				{
					std::ifstream _InStream;

					_InStream.open(_Name, std::ios::binary);

					if (!_InStream.is_open())
					{
						return;
					}

					FileContent _FileContent;

					if (!_FileContent.Load(_InStream))
					{
						return;
					}

					if (!_CachedShared->Load(_FileContent))
					{
						return;
					}

					_OldLastWrite = _LastWrite;
				},
				CachedBitMapNames[_Index].c_str(),
				_CachedShared,
				std::ref(_OldLastWrite),
				_LastWrite
			)
		);
	}

	for (size_t _Index = 0; _Index < CachedHdrNames.GetSize(); _Index++)
	{
		if (CachedHdrNames[_Index].substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) == BFW_STRING_PREFIX("Dynamic/"))
		{
			continue;
		}

		uint64_t _LastWrite = 0;

		try
		{
			_LastWrite = std::filesystem::directory_entry(CachedHdrNames[_Index]).last_write_time().time_since_epoch().count();
		}
		catch (...)
		{
			continue;
		}

		uint64_t& _OldLastWrite = *LastWriteHdrs.GetData(CachedHdrNames[_Index].c_str());

		if (_LastWrite == _OldLastWrite)
		{
			continue;
		}

		SharedPointer<Hdr> _CachedShared = CachedHdrs.GetData(CachedHdrNames[_Index].c_str())->Lock();

		if (!(Hdr*)(_CachedShared))
		{
			continue;
		}

		_Threads.EmplaceBack
		(
			std::thread
			(
				[](const BFW_CHAR_TYPE* _Name, SharedPointer<Hdr> _CachedShared, uint64_t& _OldLastWrite, const uint64_t _LastWrite)
				{
					std::ifstream _InStream;

					_InStream.open(_Name, std::ios::binary);

					if (!_InStream.is_open())
					{
						return;
					}

					FileContent _FileContent;

					if (!_FileContent.Load(_InStream))
					{
						return;
					}

					if (!_CachedShared->Load(_FileContent))
					{
						return;
					}

					_OldLastWrite = _LastWrite;
				},
				CachedHdrNames[_Index].c_str(),
				_CachedShared,
				std::ref(_OldLastWrite),
				_LastWrite
			)
		);
	}

	for (size_t _Index = 0; _Index < CachedWaveNames.GetSize(); _Index++)
	{
		if (CachedWaveNames[_Index].substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) == BFW_STRING_PREFIX("Dynamic/"))
		{
			continue;
		}

		uint64_t _LastWrite = 0;

		try
		{
			_LastWrite = std::filesystem::directory_entry(CachedWaveNames[_Index]).last_write_time().time_since_epoch().count();
		}
		catch (...)
		{
			continue;
		}

		uint64_t& _OldLastWrite = *LastWriteWaves.GetData(CachedWaveNames[_Index].c_str());

		if (_LastWrite == _OldLastWrite)
		{
			continue;
		}

		SharedPointer<Wave> _CachedShared = CachedWaves.GetData(CachedWaveNames[_Index].c_str())->Lock();

		if (!(Wave*)(_CachedShared))
		{
			continue;
		}

		_Threads.EmplaceBack
		(
			std::thread
			(
				[](const BFW_CHAR_TYPE* _Name, SharedPointer<Wave> _CachedShared, uint64_t& _OldLastWrite, const uint64_t _LastWrite)
				{
					std::ifstream _InStream;

					_InStream.open(_Name, std::ios::binary);

					if (!_InStream.is_open())
					{
						return;
					}

					FileContent _FileContent;

					if (!_FileContent.Load(_InStream))
					{
						return;
					}

					if (!_CachedShared->Load(_FileContent))
					{
						return;
					}

					_OldLastWrite = _LastWrite;
				},
				CachedWaveNames[_Index].c_str(),
				_CachedShared,
				std::ref(_OldLastWrite),
				_LastWrite
			)
		);
	}

	for (size_t _Index = 0; _Index < CachedJsonNames.GetSize(); _Index++)
	{
		if (CachedJsonNames[_Index].substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) == BFW_STRING_PREFIX("Dynamic/"))
		{
			continue;
		}

		uint64_t _LastWrite = 0;

		try
		{
			_LastWrite = std::filesystem::directory_entry(CachedJsonNames[_Index]).last_write_time().time_since_epoch().count();
		}
		catch (...)
		{
			continue;
		}

		uint64_t& _OldLastWrite = *LastWriteJsons.GetData(CachedJsonNames[_Index].c_str());

		if (_LastWrite == _OldLastWrite)
		{
			continue;
		}

		SharedPointer<Json> _CachedShared = CachedJsons.GetData(CachedJsonNames[_Index].c_str())->Lock();

		if (!(Json*)(_CachedShared))
		{
			continue;
		}

		_Threads.EmplaceBack
		(
			std::thread
			(
				[](const BFW_CHAR_TYPE* _Name, SharedPointer<Json> _CachedShared, uint64_t& _OldLastWrite, const uint64_t _LastWrite)
				{
					std::ifstream _InStream;

					_InStream.open(_Name, std::ios::binary);

					if (!_InStream.is_open())
					{
						return;
					}

					FileContent _FileContent;

					if (!_FileContent.Load(_InStream))
					{
						return;
					}

					if (!_CachedShared->Load(_FileContent))
					{
						return;
					}

					_OldLastWrite = _LastWrite;
				},
				CachedJsonNames[_Index].c_str(),
				_CachedShared,
				std::ref(_OldLastWrite),
				_LastWrite
			)
		);
	}

	for (size_t _Index = 0; _Index < _Threads.GetSize(); _Index++)
	{
		_Threads[_Index].join();
	}
}

void BFW::Assets::Manager::ReleaseBitMap(const BFW_CHAR_TYPE* _Name)
{
	LoadedBitMaps.Erase(_Name);
	CachedBitMaps.Erase(_Name);
	LastWriteBitMaps.Erase(_Name);

	for (size_t _Index = 0; _Index < CachedBitMapNames.GetSize(); _Index++)
	{
		if (CachedBitMapNames[_Index] == _Name)
		{
			CachedBitMapNames.Erase(_Index);
			break;
		}
	}
}

void BFW::Assets::Manager::ReleaseHdr(const BFW_CHAR_TYPE* _Name)
{
	LoadedHdrs.Erase(_Name);
	CachedHdrs.Erase(_Name);
	LastWriteHdrs.Erase(_Name);

	for (size_t _Index = 0; _Index < CachedHdrNames.GetSize(); _Index++)
	{
		if (CachedHdrNames[_Index] == _Name)
		{
			CachedHdrNames.Erase(_Index);
			break;
		}
	}
}

void BFW::Assets::Manager::ReleaseWave(const BFW_CHAR_TYPE* _Name)
{
	LoadedWaves.Erase(_Name);
	CachedWaves.Erase(_Name);
	LastWriteWaves.Erase(_Name);

	for (size_t _Index = 0; _Index < CachedWaveNames.GetSize(); _Index++)
	{
		if (CachedWaveNames[_Index] == _Name)
		{
			CachedWaveNames.Erase(_Index);
			break;
		}
	}
}

void BFW::Assets::Manager::ReleaseJson(const BFW_CHAR_TYPE* _Name)
{
	LoadedJsons.Erase(_Name);
	CachedJsons.Erase(_Name);
	LastWriteJsons.Erase(_Name);

	for (size_t _Index = 0; _Index < CachedJsonNames.GetSize(); _Index++)
	{
		if (CachedJsonNames[_Index] == _Name)
		{
			CachedJsonNames.Erase(_Index);
			break;
		}
	}
}

#ifdef BFW_WINDOWS_PLATFORM

void BFW::Assets::Manager::ReleaseResourceBitMap(const size_t _Id)
{
	LoadedResourceBitMaps.Erase(BFW_TO_STRING_PTR(_Id));
	CachedResourceBitMaps.Erase(BFW_TO_STRING_PTR(_Id));

	for (size_t _Index = 0; _Index < CachedResourceBitMapNames.GetSize(); _Index++)
	{
		if (CachedResourceBitMapNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			CachedResourceBitMapNames.Erase(_Index);
			break;
		}
	}
}

void BFW::Assets::Manager::ReleaseResourceHdr(const size_t _Id)
{
	LoadedResourceHdrs.Erase(BFW_TO_STRING_PTR(_Id));
	CachedResourceHdrs.Erase(BFW_TO_STRING_PTR(_Id));

	for (size_t _Index = 0; _Index < CachedResourceHdrNames.GetSize(); _Index++)
	{
		if (CachedResourceHdrNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			CachedResourceHdrNames.Erase(_Index);
			break;
		}
	}
}

void BFW::Assets::Manager::ReleaseResourceWave(const size_t _Id)
{
	LoadedResourceWaves.Erase(BFW_TO_STRING_PTR(_Id));
	CachedResourceWaves.Erase(BFW_TO_STRING_PTR(_Id));

	for (size_t _Index = 0; _Index < CachedResourceWaveNames.GetSize(); _Index++)
	{
		if (CachedResourceWaveNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			CachedResourceWaveNames.Erase(_Index);
			break;
		}
	}
}

void BFW::Assets::Manager::ReleaseResourceJson(const size_t _Id)
{
	LoadedResourceJsons.Erase(BFW_TO_STRING_PTR(_Id));
	CachedResourceJsons.Erase(BFW_TO_STRING_PTR(_Id));

	for (size_t _Index = 0; _Index < CachedResourceJsonNames.GetSize(); _Index++)
	{
		if (CachedResourceJsonNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			CachedResourceJsonNames.Erase(_Index);
			break;
		}
	}
}

#endif

BFW::SharedPointer<BFW::Assets::BitMap> BFW::Assets::Manager::GetBitMap(const BFW_CHAR_TYPE* _Name)
{
	WeakPointer<BitMap>* _CachedWeak = CachedBitMaps.GetData(_Name);

	if (_CachedWeak)
	{
		SharedPointer<BitMap> _CachedShared = _CachedWeak->Lock();

		if ((BitMap*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	std::ifstream _InStream;

	_InStream.open(_Name, std::ios::binary);

	if (!_InStream.is_open())
	{
		throw nullptr;
	}

	uint64_t _LastWrite = 0;

	try
	{
		_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
	}
	catch (...)
	{
		throw nullptr;
	}

	FileContent _FileContent;

	if (!_FileContent.Load(_InStream))
	{
		throw nullptr;
	}

	SharedPointer<BitMap> _Shared = SharedPointer<BitMap>::MakeShared(BitMap());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedBitMaps.Emplace(_Name, _Shared);
	LastWriteBitMaps.Push(_Name, _LastWrite);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedBitMapNames.GetSize(); _Index++)
	{
		if (CachedBitMapNames[_Index] == _Name)
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedBitMapNames.PushBack(_Name);
	}

	return _Shared;
}

const BFW::SharedPointer<BFW::Assets::BitMap> BFW::Assets::Manager::GetBitMap(const BFW_CHAR_TYPE* _Name) const
{
	WeakPointer<BitMap>* _CachedWeak = CachedBitMaps.GetData(_Name);

	if (_CachedWeak)
	{
		SharedPointer<BitMap> _CachedShared = _CachedWeak->Lock();

		if ((BitMap*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	std::ifstream _InStream;

	_InStream.open(_Name, std::ios::binary);

	if (!_InStream.is_open())
	{
		throw nullptr;
	}

	uint64_t _LastWrite = 0;

	try
	{
		_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
	}
	catch (...)
	{
		throw nullptr;
	}

	FileContent _FileContent;

	if (!_FileContent.Load(_InStream))
	{
		throw nullptr;
	}

	SharedPointer<BitMap> _Shared = SharedPointer<BitMap>::MakeShared(BitMap());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedBitMaps.Emplace(_Name, _Shared);
	LastWriteBitMaps.Push(_Name, _LastWrite);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedBitMapNames.GetSize(); _Index++)
	{
		if (CachedBitMapNames[_Index] == _Name)
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedBitMapNames.PushBack(_Name);
	}

	return _Shared;
}

BFW::SharedPointer<BFW::Assets::Hdr> BFW::Assets::Manager::GetHdr(const BFW_CHAR_TYPE* _Name)
{
	WeakPointer<Hdr>* _CachedWeak = CachedHdrs.GetData(_Name);

	if (_CachedWeak)
	{
		SharedPointer<Hdr> _CachedShared = _CachedWeak->Lock();

		if ((Hdr*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	std::ifstream _InStream;

	_InStream.open(_Name, std::ios::binary);

	if (!_InStream.is_open())
	{
		throw nullptr;
	}

	uint64_t _LastWrite = 0;

	try
	{
		_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
	}
	catch (...)
	{
		throw nullptr;
	}

	FileContent _FileContent;

	if (!_FileContent.Load(_InStream))
	{
		throw nullptr;
	}

	SharedPointer<Hdr> _Shared = SharedPointer<Hdr>::MakeShared(Hdr());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedHdrs.Emplace(_Name, _Shared);
	LastWriteHdrs.Push(_Name, _LastWrite);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedHdrNames.GetSize(); _Index++)
	{
		if (CachedHdrNames[_Index] == _Name)
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedHdrNames.PushBack(_Name);
	}

	return _Shared;
}

const BFW::SharedPointer<BFW::Assets::Hdr> BFW::Assets::Manager::GetHdr(const BFW_CHAR_TYPE* _Name) const
{
	WeakPointer<Hdr>* _CachedWeak = CachedHdrs.GetData(_Name);

	if (_CachedWeak)
	{
		SharedPointer<Hdr> _CachedShared = _CachedWeak->Lock();

		if ((Hdr*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	std::ifstream _InStream;

	_InStream.open(_Name, std::ios::binary);

	if (!_InStream.is_open())
	{
		throw nullptr;
	}

	uint64_t _LastWrite = 0;

	try
	{
		_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
	}
	catch (...)
	{
		throw nullptr;
	}

	FileContent _FileContent;

	if (!_FileContent.Load(_InStream))
	{
		throw nullptr;
	}

	SharedPointer<Hdr> _Shared = SharedPointer<Hdr>::MakeShared(Hdr());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedHdrs.Emplace(_Name, _Shared);
	LastWriteHdrs.Push(_Name, _LastWrite);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedHdrNames.GetSize(); _Index++)
	{
		if (CachedHdrNames[_Index] == _Name)
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedHdrNames.PushBack(_Name);
	}

	return _Shared;
}

BFW::SharedPointer<BFW::Assets::Wave> BFW::Assets::Manager::GetWave(const BFW_CHAR_TYPE* _Name)
{
	WeakPointer<Wave>* _CachedWeak = CachedWaves.GetData(_Name);

	if (_CachedWeak)
	{
		SharedPointer<Wave> _CachedShared = _CachedWeak->Lock();

		if ((Wave*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	std::ifstream _InStream;

	_InStream.open(_Name, std::ios::binary);

	if (!_InStream.is_open())
	{
		throw nullptr;
	}

	uint64_t _LastWrite = 0;

	try
	{
		_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
	}
	catch (...)
	{
		throw nullptr;
	}

	FileContent _FileContent;

	if (!_FileContent.Load(_InStream))
	{
		throw nullptr;
	}

	SharedPointer<Wave> _Shared = SharedPointer<Wave>::MakeShared(Wave());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedWaves.Emplace(_Name, _Shared);
	LastWriteWaves.Push(_Name, _LastWrite);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedWaveNames.GetSize(); _Index++)
	{
		if (CachedWaveNames[_Index] == _Name)
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedWaveNames.PushBack(_Name);
	}

	return _Shared;
}

const BFW::SharedPointer<BFW::Assets::Wave> BFW::Assets::Manager::GetWave(const BFW_CHAR_TYPE* _Name) const
{
	WeakPointer<Wave>* _CachedWeak = CachedWaves.GetData(_Name);

	if (_CachedWeak)
	{
		SharedPointer<Wave> _CachedShared = _CachedWeak->Lock();

		if ((Wave*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	std::ifstream _InStream;

	_InStream.open(_Name, std::ios::binary);

	if (!_InStream.is_open())
	{
		throw nullptr;
	}

	uint64_t _LastWrite = 0;

	try
	{
		_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
	}
	catch (...)
	{
		throw nullptr;
	}

	FileContent _FileContent;

	if (!_FileContent.Load(_InStream))
	{
		throw nullptr;
	}

	SharedPointer<Wave> _Shared = SharedPointer<Wave>::MakeShared(Wave());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedWaves.Emplace(_Name, _Shared);
	LastWriteWaves.Push(_Name, _LastWrite);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedWaveNames.GetSize(); _Index++)
	{
		if (CachedWaveNames[_Index] == _Name)
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedWaveNames.PushBack(_Name);
	}

	return _Shared;
}

BFW::SharedPointer<BFW::Assets::Json> BFW::Assets::Manager::GetJson(const BFW_CHAR_TYPE* _Name)
{
	WeakPointer<Json>* _CachedWeak = CachedJsons.GetData(_Name);

	if (_CachedWeak)
	{
		SharedPointer<Json> _CachedShared = _CachedWeak->Lock();

		if ((Json*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	std::ifstream _InStream;

	_InStream.open(_Name, std::ios::binary);

	if (!_InStream.is_open())
	{
		throw nullptr;
	}

	uint64_t _LastWrite = 0;

	try
	{
		_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
	}
	catch (...)
	{
		throw nullptr;
	}

	FileContent _FileContent;

	if (!_FileContent.Load(_InStream))
	{
		throw nullptr;
	}

	SharedPointer<Json> _Shared = SharedPointer<Json>::MakeShared(Json());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedJsons.Emplace(_Name, _Shared);
	LastWriteJsons.Push(_Name, _LastWrite);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedJsonNames.GetSize(); _Index++)
	{
		if (CachedJsonNames[_Index] == _Name)
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedJsonNames.PushBack(_Name);
	}

	return _Shared;
}

const BFW::SharedPointer<BFW::Assets::Json> BFW::Assets::Manager::GetJson(const BFW_CHAR_TYPE* _Name) const
{
	WeakPointer<Json>* _CachedWeak = CachedJsons.GetData(_Name);

	if (_CachedWeak)
	{
		SharedPointer<Json> _CachedShared = _CachedWeak->Lock();

		if ((Json*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	std::ifstream _InStream;

	_InStream.open(_Name, std::ios::binary);

	if (!_InStream.is_open())
	{
		throw nullptr;
	}

	uint64_t _LastWrite = 0;

	try
	{
		_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
	}
	catch (...)
	{
		throw nullptr;
	}

	FileContent _FileContent;

	if (!_FileContent.Load(_InStream))
	{
		throw nullptr;
	}

	SharedPointer<Json> _Shared = SharedPointer<Json>::MakeShared(Json());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedJsons.Emplace(_Name, _Shared);
	LastWriteJsons.Push(_Name, _LastWrite);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedJsonNames.GetSize(); _Index++)
	{
		if (CachedJsonNames[_Index] == _Name)
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedJsonNames.PushBack(_Name);
	}

	return _Shared;
}

#ifdef BFW_WINDOWS_PLATFORM

BFW::SharedPointer<BFW::Assets::BitMap> BFW::Assets::Manager::GetResourceBitMap(const size_t _Id)
{
	WeakPointer<BitMap>* _CachedWeak = CachedResourceBitMaps.GetData(BFW_TO_STRING_PTR(_Id));

	if (_CachedWeak)
	{
		SharedPointer<BitMap> _CachedShared = _CachedWeak->Lock();

		if ((BitMap*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	FileContent _FileContent;

	if (!_FileContent.Load(BFW_BMP_RESOURCE, _Id))
	{
		throw nullptr;
	}

	SharedPointer<BitMap> _Shared = SharedPointer<BitMap>::MakeShared(BitMap());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedResourceBitMaps.Emplace(BFW_TO_STRING_PTR(_Id), _Shared);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedResourceBitMapNames.GetSize(); _Index++)
	{
		if (CachedResourceBitMapNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedResourceBitMapNames.PushBack(BFW_TO_STRING_PTR(_Id));
	}

	return _Shared;
}

const BFW::SharedPointer<BFW::Assets::BitMap> BFW::Assets::Manager::GetResourceBitMap(const size_t _Id) const
{
	WeakPointer<BitMap>* _CachedWeak = CachedResourceBitMaps.GetData(BFW_TO_STRING_PTR(_Id));

	if (_CachedWeak)
	{
		SharedPointer<BitMap> _CachedShared = _CachedWeak->Lock();

		if ((BitMap*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	FileContent _FileContent;

	if (!_FileContent.Load(BFW_BMP_RESOURCE, _Id))
	{
		throw nullptr;
	}

	SharedPointer<BitMap> _Shared = SharedPointer<BitMap>::MakeShared(BitMap());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedResourceBitMaps.Emplace(BFW_TO_STRING_PTR(_Id), _Shared);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedResourceBitMapNames.GetSize(); _Index++)
	{
		if (CachedResourceBitMapNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedResourceBitMapNames.PushBack(BFW_TO_STRING_PTR(_Id));
	}

	return _Shared;
}

BFW::SharedPointer<BFW::Assets::Hdr> BFW::Assets::Manager::GetResourceHdr(const size_t _Id)
{
	WeakPointer<Hdr>* _CachedWeak = CachedResourceHdrs.GetData(BFW_TO_STRING_PTR(_Id));

	if (_CachedWeak)
	{
		SharedPointer<Hdr> _CachedShared = _CachedWeak->Lock();

		if ((Hdr*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	FileContent _FileContent;

	if (!_FileContent.Load(BFW_HDR_RESOURCE, _Id))
	{
		throw nullptr;
	}

	SharedPointer<Hdr> _Shared = SharedPointer<Hdr>::MakeShared(Hdr());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedResourceHdrs.Emplace(BFW_TO_STRING_PTR(_Id), _Shared);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedResourceHdrNames.GetSize(); _Index++)
	{
		if (CachedResourceHdrNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedResourceHdrNames.PushBack(BFW_TO_STRING_PTR(_Id));
	}

	return _Shared;
}

const BFW::SharedPointer<BFW::Assets::Hdr> BFW::Assets::Manager::GetResourceHdr(const size_t _Id) const
{
	WeakPointer<Hdr>* _CachedWeak = CachedResourceHdrs.GetData(BFW_TO_STRING_PTR(_Id));

	if (_CachedWeak)
	{
		SharedPointer<Hdr> _CachedShared = _CachedWeak->Lock();

		if ((Hdr*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	FileContent _FileContent;

	if (!_FileContent.Load(BFW_HDR_RESOURCE, _Id))
	{
		throw nullptr;
	}

	SharedPointer<Hdr> _Shared = SharedPointer<Hdr>::MakeShared(Hdr());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedResourceHdrs.Emplace(BFW_TO_STRING_PTR(_Id), _Shared);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedResourceHdrNames.GetSize(); _Index++)
	{
		if (CachedResourceHdrNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedResourceHdrNames.PushBack(BFW_TO_STRING_PTR(_Id));
	}

	return _Shared;
}

BFW::SharedPointer<BFW::Assets::Wave> BFW::Assets::Manager::GetResourceWave(const size_t _Id)
{
	WeakPointer<Wave>* _CachedWeak = CachedResourceWaves.GetData(BFW_TO_STRING_PTR(_Id));

	if (_CachedWeak)
	{
		SharedPointer<Wave> _CachedShared = _CachedWeak->Lock();

		if ((Wave*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	FileContent _FileContent;

	if (!_FileContent.Load(BFW_WAV_RESOURCE, _Id))
	{
		throw nullptr;
	}

	SharedPointer<Wave> _Shared = SharedPointer<Wave>::MakeShared(Wave());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedResourceWaves.Emplace(BFW_TO_STRING_PTR(_Id), _Shared);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedResourceWaveNames.GetSize(); _Index++)
	{
		if (CachedResourceWaveNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedResourceWaveNames.PushBack(BFW_TO_STRING_PTR(_Id));
	}

	return _Shared;
}

const BFW::SharedPointer<BFW::Assets::Wave> BFW::Assets::Manager::GetResourceWave(const size_t _Id) const
{
	WeakPointer<Wave>* _CachedWeak = CachedResourceWaves.GetData(BFW_TO_STRING_PTR(_Id));

	if (_CachedWeak)
	{
		SharedPointer<Wave> _CachedShared = _CachedWeak->Lock();

		if ((Wave*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	FileContent _FileContent;

	if (!_FileContent.Load(BFW_WAV_RESOURCE, _Id))
	{
		throw nullptr;
	}

	SharedPointer<Wave> _Shared = SharedPointer<Wave>::MakeShared(Wave());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedResourceWaves.Emplace(BFW_TO_STRING_PTR(_Id), _Shared);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedResourceWaveNames.GetSize(); _Index++)
	{
		if (CachedResourceWaveNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedResourceWaveNames.PushBack(BFW_TO_STRING_PTR(_Id));
	}

	return _Shared;
}

BFW::SharedPointer<BFW::Assets::Json> BFW::Assets::Manager::GetResourceJson(const size_t _Id)
{
	WeakPointer<Json>* _CachedWeak = CachedResourceJsons.GetData(BFW_TO_STRING_PTR(_Id));

	if (_CachedWeak)
	{
		SharedPointer<Json> _CachedShared = _CachedWeak->Lock();

		if ((Json*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	FileContent _FileContent;

	if (!_FileContent.Load(BFW_JSON_RESOURCE, _Id))
	{
		throw nullptr;
	}

	SharedPointer<Json> _Shared = SharedPointer<Json>::MakeShared(Json());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedResourceJsons.Emplace(BFW_TO_STRING_PTR(_Id), _Shared);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedResourceJsonNames.GetSize(); _Index++)
	{
		if (CachedResourceJsonNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedResourceJsonNames.PushBack(BFW_TO_STRING_PTR(_Id));
	}

	return _Shared;
}

const BFW::SharedPointer<BFW::Assets::Json> BFW::Assets::Manager::GetResourceJson(const size_t _Id) const
{
	WeakPointer<Json>* _CachedWeak = CachedResourceJsons.GetData(BFW_TO_STRING_PTR(_Id));

	if (_CachedWeak)
	{
		SharedPointer<Json> _CachedShared = _CachedWeak->Lock();

		if ((Json*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	FileContent _FileContent;

	if (!_FileContent.Load(BFW_JSON_RESOURCE, _Id))
	{
		throw nullptr;
	}

	SharedPointer<Json> _Shared = SharedPointer<Json>::MakeShared(Json());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedResourceJsons.Emplace(BFW_TO_STRING_PTR(_Id), _Shared);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedResourceJsonNames.GetSize(); _Index++)
	{
		if (CachedResourceJsonNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedResourceJsonNames.PushBack(BFW_TO_STRING_PTR(_Id));
	}

	return _Shared;
}

#endif

#ifdef BFW_WINDOWS_PLATFORM

BFW::Assets::Manager& BFW::Assets::Manager::operator= (Manager&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	QueuedBitMaps = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedBitMaps);
	QueuedHdrs = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedHdrs);
	QueuedWaves = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedWaves);
	QueuedJsons = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedJsons);
	QueuedResourceBitMaps = (Vector<size_t>&&)(_Other.QueuedResourceBitMaps);
	QueuedResourceHdrs = (Vector<size_t>&&)(_Other.QueuedResourceHdrs);
	QueuedResourceWaves = (Vector<size_t>&&)(_Other.QueuedResourceWaves);
	QueuedResourceJsons = (Vector<size_t>&&)(_Other.QueuedResourceJsons);
	LoadedBitMaps = (Trie<SharedPointer<BitMap>>&&)(_Other.LoadedBitMaps);
	LoadedHdrs = (Trie<SharedPointer<Hdr>>&&)(_Other.LoadedHdrs);
	LoadedWaves = (Trie<SharedPointer<Wave>>&&)(_Other.LoadedWaves);
	LoadedJsons = (Trie<SharedPointer<Json>>&&)(_Other.LoadedJsons);
	LoadedResourceBitMaps = (Trie<SharedPointer<BitMap>>&&)(_Other.LoadedResourceBitMaps);
	LoadedResourceHdrs = (Trie<SharedPointer<Hdr>>&&)(_Other.LoadedResourceHdrs);
	LoadedResourceWaves = (Trie<SharedPointer<Wave>>&&)(_Other.LoadedResourceWaves);
	LoadedResourceJsons = (Trie<SharedPointer<Json>>&&)(_Other.LoadedResourceJsons);
	CachedBitMapNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedBitMapNames);
	CachedHdrNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedHdrNames);
	CachedWaveNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedWaveNames);
	CachedJsonNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedJsonNames);
	CachedBitMaps = (Trie<WeakPointer<BitMap>>&&)(_Other.CachedBitMaps);
	CachedHdrs = (Trie<WeakPointer<Hdr>>&&)(_Other.CachedHdrs);
	CachedWaves = (Trie<WeakPointer<Wave>>&&)(_Other.CachedWaves);
	CachedJsons = (Trie<WeakPointer<Json>>&&)(_Other.CachedJsons);
	LastWriteBitMaps = (Trie<uint64_t>&&)(_Other.LastWriteBitMaps);
	LastWriteHdrs = (Trie<uint64_t>&&)(_Other.LastWriteHdrs);
	LastWriteWaves = (Trie<uint64_t>&&)(_Other.LastWriteWaves);
	LastWriteJsons = (Trie<uint64_t>&&)(_Other.LastWriteJsons);
	CachedResourceBitMapNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceBitMapNames);
	CachedResourceHdrNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceHdrNames);
	CachedResourceWaveNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceWaveNames);
	CachedResourceJsonNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceJsonNames);
	CachedResourceBitMaps = (Trie<WeakPointer<BitMap>>&&)(_Other.CachedResourceBitMaps);
	CachedResourceHdrs = (Trie<WeakPointer<Hdr>>&&)(_Other.CachedResourceHdrs);
	CachedResourceWaves = (Trie<WeakPointer<Wave>>&&)(_Other.CachedResourceWaves);
	CachedResourceJsons = (Trie<WeakPointer<Json>>&&)(_Other.CachedResourceJsons);

	return *this;
}

#endif

#if defined BFW_LINUX_PLATFORM || defined BFW_ESP32_PLATFORM

BFW::Assets::Manager& BFW::Assets::Manager::operator= (Manager&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	QueuedBitMaps = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedBitMaps);
	QueuedHdrs = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedHdrs);
	QueuedWaves = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedWaves);
	QueuedJsons = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedJsons);
	LoadedBitMaps = (Trie<SharedPointer<BitMap>>&&)(_Other.LoadedBitMaps);
	LoadedHdrs = (Trie<SharedPointer<Hdr>>&&)(_Other.LoadedHdrs);
	LoadedWaves = (Trie<SharedPointer<Wave>>&&)(_Other.LoadedWaves);
	LoadedJsons = (Trie<SharedPointer<Json>>&&)(_Other.LoadedJsons);
	CachedBitMapNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedBitMapNames);
	CachedHdrNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedHdrNames);
	CachedWaveNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedWaveNames);
	CachedJsonNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedJsonNames);
	CachedBitMaps = (Trie<WeakPointer<BitMap>>&&)(_Other.CachedBitMaps);
	CachedHdrs = (Trie<WeakPointer<Hdr>>&&)(_Other.CachedHdrs);
	CachedWaves = (Trie<WeakPointer<Wave>>&&)(_Other.CachedWaves);
	CachedJsons = (Trie<WeakPointer<Json>>&&)(_Other.CachedJsons);
	LastWriteBitMaps = (Trie<uint64_t>&&)(_Other.LastWriteBitMaps);
	LastWriteHdrs = (Trie<uint64_t>&&)(_Other.LastWriteHdrs);
	LastWriteWaves = (Trie<uint64_t>&&)(_Other.LastWriteWaves);
	LastWriteJsons = (Trie<uint64_t>&&)(_Other.LastWriteJsons);

	return *this;
}

#endif

void BFW::Assets::Manager::RefreshCache()
{
	for (size_t _Index = 0; _Index < CachedBitMapNames.GetSize(); _Index++)
	{
		WeakPointer<BitMap>* _CachedWeak = CachedBitMaps.GetData(CachedBitMapNames[_Index].c_str());

		if (!_CachedWeak)
		{
			LastWriteBitMaps.Erase(CachedBitMapNames[_Index].c_str());
			CachedBitMapNames.Erase(_Index);
			_Index--;
			continue;
		}

		SharedPointer<BitMap> _CachedShared = _CachedWeak->Lock();

		if ((BitMap*)(_CachedShared) == nullptr)
		{
			CachedBitMaps.Erase(CachedBitMapNames[_Index].c_str());
			LastWriteBitMaps.Erase(CachedBitMapNames[_Index].c_str());
			CachedBitMapNames.Erase(_Index);
			_Index--;
			continue;
		}
	}

	for (size_t _Index = 0; _Index < CachedHdrNames.GetSize(); _Index++)
	{
		WeakPointer<Hdr>* _CachedWeak = CachedHdrs.GetData(CachedHdrNames[_Index].c_str());

		if (!_CachedWeak)
		{
			LastWriteHdrs.Erase(CachedHdrNames[_Index].c_str());
			CachedHdrNames.Erase(_Index);
			_Index--;
			continue;
		}

		SharedPointer<Hdr> _CachedShared = _CachedWeak->Lock();

		if ((Hdr*)(_CachedShared) == nullptr)
		{
			CachedHdrs.Erase(CachedHdrNames[_Index].c_str());
			LastWriteHdrs.Erase(CachedHdrNames[_Index].c_str());
			CachedHdrNames.Erase(_Index);
			_Index--;
			continue;
		}
	}

	for (size_t _Index = 0; _Index < CachedWaveNames.GetSize(); _Index++)
	{
		WeakPointer<Wave>* _CachedWeak = CachedWaves.GetData(CachedWaveNames[_Index].c_str());

		if (!_CachedWeak)
		{
			LastWriteWaves.Erase(CachedWaveNames[_Index].c_str());
			CachedWaveNames.Erase(_Index);
			_Index--;
			continue;
		}

		SharedPointer<Wave> _CachedShared = _CachedWeak->Lock();

		if ((Wave*)(_CachedShared) == nullptr)
		{
			CachedWaves.Erase(CachedWaveNames[_Index].c_str());
			LastWriteWaves.Erase(CachedWaveNames[_Index].c_str());
			CachedWaveNames.Erase(_Index);
			_Index--;
			continue;
		}
	}

	for (size_t _Index = 0; _Index < CachedJsonNames.GetSize(); _Index++)
	{
		WeakPointer<Json>* _CachedWeak = CachedJsons.GetData(CachedJsonNames[_Index].c_str());

		if (!_CachedWeak)
		{
			LastWriteJsons.Erase(CachedJsonNames[_Index].c_str());
			CachedJsonNames.Erase(_Index);
			_Index--;
			continue;
		}

		SharedPointer<Json> _CachedShared = _CachedWeak->Lock();

		if ((Json*)(_CachedShared) == nullptr)
		{
			CachedJsons.Erase(CachedJsonNames[_Index].c_str());
			LastWriteJsons.Erase(CachedJsonNames[_Index].c_str());
			CachedJsonNames.Erase(_Index);
			_Index--;
			continue;
		}
	}

#ifdef BFW_WINDOWS_PLATFORM

	for (size_t _Index = 0; _Index < CachedResourceBitMapNames.GetSize(); _Index++)
	{
		WeakPointer<BitMap>* _CachedWeak = CachedResourceBitMaps.GetData(CachedResourceBitMapNames[_Index].c_str());

		if (!_CachedWeak)
		{
			CachedResourceBitMapNames.Erase(_Index);
			_Index--;
			continue;
		}

		SharedPointer<BitMap> _CachedShared = _CachedWeak->Lock();

		if ((BitMap*)(_CachedShared) == nullptr)
		{
			CachedResourceBitMaps.Erase(CachedResourceBitMapNames[_Index].c_str());
			CachedResourceBitMapNames.Erase(_Index);
			_Index--;
			continue;
		}
	}

	for (size_t _Index = 0; _Index < CachedResourceHdrNames.GetSize(); _Index++)
	{
		WeakPointer<Hdr>* _CachedWeak = CachedResourceHdrs.GetData(CachedResourceHdrNames[_Index].c_str());

		if (!_CachedWeak)
		{
			CachedResourceHdrNames.Erase(_Index);
			_Index--;
			continue;
		}

		SharedPointer<Hdr> _CachedShared = _CachedWeak->Lock();

		if ((Hdr*)(_CachedShared) == nullptr)
		{
			CachedResourceHdrs.Erase(CachedResourceHdrNames[_Index].c_str());
			CachedResourceHdrNames.Erase(_Index);
			_Index--;
			continue;
		}
	}

	for (size_t _Index = 0; _Index < CachedResourceWaveNames.GetSize(); _Index++)
	{
		WeakPointer<Wave>* _CachedWeak = CachedResourceWaves.GetData(CachedResourceWaveNames[_Index].c_str());

		if (!_CachedWeak)
		{
			CachedResourceWaveNames.Erase(_Index);
			_Index--;
			continue;
		}

		SharedPointer<Wave> _CachedShared = _CachedWeak->Lock();

		if ((Wave*)(_CachedShared) == nullptr)
		{
			CachedResourceWaves.Erase(CachedResourceWaveNames[_Index].c_str());
			CachedResourceWaveNames.Erase(_Index);
			_Index--;
			continue;
		}
	}

	for (size_t _Index = 0; _Index < CachedResourceJsonNames.GetSize(); _Index++)
	{
		WeakPointer<Json>* _CachedWeak = CachedResourceJsons.GetData(CachedResourceJsonNames[_Index].c_str());

		if (!_CachedWeak)
		{
			CachedResourceJsonNames.Erase(_Index);
			_Index--;
			continue;
		}

		SharedPointer<Json> _CachedShared = _CachedWeak->Lock();

		if ((Json*)(_CachedShared) == nullptr)
		{
			CachedResourceJsons.Erase(CachedResourceJsonNames[_Index].c_str());
			CachedResourceJsonNames.Erase(_Index);
			_Index--;
			continue;
		}
	}

#endif
}
