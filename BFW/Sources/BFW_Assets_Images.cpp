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
	BitMapInfoHeader& operator= (const BitMapInfoHeader& _Other) = default;
	BitMapInfoHeader& operator= (BitMapInfoHeader& _Other) noexcept;

};

struct HdrFileHeader
{

	BFW_CHAR_TYPE_A MagicNumbers[11];

	HdrFileHeader();
	HdrFileHeader(const HdrFileHeader& _Other) = default;
	HdrFileHeader(HdrFileHeader&& _Other) noexcept;
	HdrFileHeader& operator= (const HdrFileHeader& _Other) = default;
	HdrFileHeader& operator= (HdrFileHeader&& _Other) noexcept;

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

		uint8_t _RByte = _FileContent[_FileIndex];

		_FileIndex++;

		if (_FileContent.GetLength() - 1 == _FileIndex)
		{
			return false;
		}

		uint8_t _GByte = _FileContent[_FileIndex];

		_FileIndex++;

		if (_FileContent.GetLength() - 1 == _FileIndex)
		{
			return false;
		}

		uint8_t _BByte = _FileContent[_FileIndex];

		_FileIndex++;

		if (_FileContent.GetLength() - 1 == _FileIndex)
		{
			return false;
		}

		uint8_t _EByte = _FileContent[_FileIndex];

		_FileIndex++;

		if (_RByte != 1 || _GByte != 1 || _BByte != 1)
		{
			_ScanLine[_Length * 4 + 0] = _RByte;
			_ScanLine[_Length * 4 + 1] = _GByte;
			_ScanLine[_Length * 4 + 2] = _BByte;
			_ScanLine[_Length * 4 + 3] = _EByte;

			_Length++;
			_LeftShift = 0;

			continue;
		}

		for (size_t _Index = 0; _Index < (size_t)(_EByte) << _LeftShift; _Index++)
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
	if (_Width < 8 || _Width > (size_t)(std::numeric_limits<int16_t>::max()))
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

	if (((int16_t)(_FileContent[_FileIndex + 2]) << 8) + _FileContent[_FileIndex + 3] != (int16_t)(_Width))
	{
		return false;
	}

	_FileIndex += 4;

	for (size_t _Channel = 0; _Channel < 4; _Channel++)
	{
		size_t _PositionX = 0;

		while (_PositionX < _Width)
		{
			if (_FileContent.GetLength() - 1 == _FileIndex)
			{
				return false;
			}

			uint8_t _Length = _FileContent[_FileIndex];

			_FileIndex++;

			if (_Length <= 128)
			{
				if (_Length + _PositionX > _Width)
				{
					return false;
				}

				while (_Length)
				{
					if (_FileContent.GetLength() - 1 == _FileIndex)
					{
						return false;
					}

					_ScanLine[_PositionX * 4 + _Channel] = _FileContent[_FileIndex];

					_FileIndex++;
					_PositionX++;

					_Length--;
				}

				continue;
			}

			_Length -= 128;

			if (_Length + _PositionX > _Width)
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
				_ScanLine[_PositionX * 4 + _Channel] = _Value;

				_PositionX++;

				_Length--;
			}
		}
	}

	return true;
}

static void HdrPlaceScanLine(float* _Data, const uint8_t* _ScanLine, const size_t _Width, const size_t _PositionY)
{
	for (size_t _PositionX = 0; _PositionX < _Width; _PositionX++)
	{
		_Data[(_PositionX + _PositionY * _Width) * 4 + 0] = ldexpf((float)(_ScanLine[_PositionX * 4 + 0]) + 0.5f, (uint16_t)(_ScanLine[_PositionX * 4 + 3]) - (128 + 8));
		_Data[(_PositionX + _PositionY * _Width) * 4 + 1] = ldexpf((float)(_ScanLine[_PositionX * 4 + 1]) + 0.5f, (uint16_t)(_ScanLine[_PositionX * 4 + 3]) - (128 + 8));
		_Data[(_PositionX + _PositionY * _Width) * 4 + 2] = ldexpf((float)(_ScanLine[_PositionX * 4 + 2]) + 0.5f, (uint16_t)(_ScanLine[_PositionX * 4 + 3]) - (128 + 8));
		_Data[(_PositionX + _PositionY * _Width) * 4 + 3] = 1.0f;
	}
}

static void HdrEncodeRGBE(const float _RValue, const float _GValue, const float _BValue, uint8_t& _ResultR, uint8_t& _ResultG, uint8_t& _ResultB, uint8_t& _ResultE)
{
	float _Min = _RValue;

	if (_GValue < _Min)
	{
		_Min = _GValue;
	}

	if (_BValue < _Min)
	{
		_Min = _BValue;
	}

	if (_Min < 1e-32f)
	{
		_ResultR = 0;
		_ResultG = 0;
		_ResultB = 0;
		_ResultE = 0;

		return;
	}

	int32_t _Exponent = 0;
	float _Mantissa = std::frexp(_Min, (int*)(&_Exponent));

	float _Scale = _Mantissa * 256.0f / _Min;

	_ResultR = (uint8_t)(_RValue * _Scale);
	_ResultG = (uint8_t)(_GValue * _Scale);
	_ResultB = (uint8_t)(_BValue * _Scale);
	_ResultE = (uint8_t)(_Exponent + 128);
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

	if (!_FileContent.GetData() || _FileContent.GetLength() < sizeof(HdrFileHeader) + BFW_STRING_TYPE_A("FORMAT=32-bit_rle_rgbe\x0A\x0A").size() + BFW_STRING_TYPE_A("-Y  +X \x0A").size() + 1)
	{
		return false;
	}

	HdrFileHeader _FileHeader = *(const HdrFileHeader*)(_FileContent.GetData());

	if (_FileHeader.MagicNumbers[0] != '#' || _FileHeader.MagicNumbers[1] != '?' || _FileHeader.MagicNumbers[2] != 'R' || _FileHeader.MagicNumbers[3] != 'A' || _FileHeader.MagicNumbers[4] != 'D' || _FileHeader.MagicNumbers[5] != 'I' || _FileHeader.MagicNumbers[6] != 'A' || _FileHeader.MagicNumbers[7] != 'N' || _FileHeader.MagicNumbers[8] != 'C' || _FileHeader.MagicNumbers[9] != 'E' || _FileHeader.MagicNumbers[10] != '\x0A')
	{
		return false;
	}

	size_t _FileIndex = sizeof(HdrFileHeader);

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
			_Stream.imbue(std::locale::classic());
			_Stream << BFW_STRING_VIEW_TYPE_A((const BFW_CHAR_TYPE_A*)(_FileContent.GetData()) + _Number1Index, _Number1EndIndex - _Number1Index);
			_Stream >> _Height;

			if (!_Stream || !_Stream.eof())
			{
				return false;
			}
		}

		{
			BFW_STRING_STREAM_TYPE_A _Stream;
			_Stream.imbue(std::locale::classic());
			_Stream << BFW_STRING_VIEW_TYPE_A((const BFW_CHAR_TYPE_A*)(_FileContent.GetData()) + _Number2Index, _Number2EndIndex - _Number2Index);
			_Stream >> _Width;

			if (!_Stream || !_Stream.eof())
			{
				return false;
			}
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
			float _XValue = Data[_Index * 4 + 0];
			float _YValue = Data[_Index * 4 + 1];
			float _ZValue = Data[_Index * 4 + 2];

			Data[_Index * 4 + 0] = _XValue * 3.2406f - _YValue * 1.5372f - _ZValue * 0.4986f;
			Data[_Index * 4 + 1] = -_XValue * 0.9689f + _YValue * 1.8758f + _ZValue * 0.0415f;
			Data[_Index * 4 + 2] = _XValue * 0.0557f - _YValue * 0.2040f + _ZValue * 1.0570f;
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

		for (size_t _PositionY = 0; _PositionY < _Height; _PositionY++)
		{
			for (size_t _PositionX = 0; _PositionX < _Width; _PositionX++)
			{
				_NewData[(_PositionX + _PositionY * _Width) * 4 + 0] = Data[(_PositionY + _PositionX * _Height) * 4 + 0];
				_NewData[(_PositionX + _PositionY * _Width) * 4 + 1] = Data[(_PositionY + _PositionX * _Height) * 4 + 1];
				_NewData[(_PositionX + _PositionY * _Width) * 4 + 2] = Data[(_PositionY + _PositionX * _Height) * 4 + 2];
				_NewData[(_PositionX + _PositionY * _Width) * 4 + 3] = Data[(_PositionY + _PositionX * _Height) * 4 + 3];
			}
		}

		delete[] Data;
		Data = _NewData;
	}

	if (_FlippedX)
	{
		for (size_t _PositionY = 0; _PositionY < _Height; _PositionY++)
		{
			for (size_t _PositionX = 0; _PositionX < _Width / 2; _PositionX++)
			{
				float _RValue = Data[(_PositionX + _PositionY * _Width) * 4 + 0];
				float _GValue = Data[(_PositionX + _PositionY * _Width) * 4 + 1];
				float _BValue = Data[(_PositionX + _PositionY * _Width) * 4 + 2];
				float _AValue = Data[(_PositionX + _PositionY * _Width) * 4 + 3];

				Data[(_PositionX + _PositionY * _Width) * 4 + 0] = Data[((_Width - 1 - _PositionX) + _PositionY * _Width) * 4 + 0];
				Data[(_PositionX + _PositionY * _Width) * 4 + 1] = Data[((_Width - 1 - _PositionX) + _PositionY * _Width) * 4 + 1];
				Data[(_PositionX + _PositionY * _Width) * 4 + 2] = Data[((_Width - 1 - _PositionX) + _PositionY * _Width) * 4 + 2];
				Data[(_PositionX + _PositionY * _Width) * 4 + 3] = Data[((_Width - 1 - _PositionX) + _PositionY * _Width) * 4 + 3];

				Data[((_Width - 1 - _PositionX) + _PositionY * _Width) * 4 + 0] = _RValue;
				Data[((_Width - 1 - _PositionX) + _PositionY * _Width) * 4 + 1] = _GValue;
				Data[((_Width - 1 - _PositionX) + _PositionY * _Width) * 4 + 2] = _BValue;
				Data[((_Width - 1 - _PositionX) + _PositionY * _Width) * 4 + 3] = _AValue;
			}
		}
	}

	if (_FlippedY != _Flip)
	{
		for (size_t _PositionY = 0; _PositionY < _Height / 2; _PositionY++)
		{
			for (size_t _PositionX = 0; _PositionX < _Width; _PositionX++)
			{
				float _RValue = Data[(_PositionX + _PositionY * _Width) * 4 + 0];
				float _GValue = Data[(_PositionX + _PositionY * _Width) * 4 + 1];
				float _BValue = Data[(_PositionX + _PositionY * _Width) * 4 + 2];
				float _AValue = Data[(_PositionX + _PositionY * _Width) * 4 + 3];

				Data[(_PositionX + _PositionY * _Width) * 4 + 0] = Data[(_PositionX + (_Height - 1 - _PositionY) * _Width) * 4 + 0];
				Data[(_PositionX + _PositionY * _Width) * 4 + 1] = Data[(_PositionX + (_Height - 1 - _PositionY) * _Width) * 4 + 1];
				Data[(_PositionX + _PositionY * _Width) * 4 + 2] = Data[(_PositionX + (_Height - 1 - _PositionY) * _Width) * 4 + 2];
				Data[(_PositionX + _PositionY * _Width) * 4 + 3] = Data[(_PositionX + (_Height - 1 - _PositionY) * _Width) * 4 + 3];

				Data[(_PositionX + (_Height - 1 - _PositionY) * _Width) * 4 + 0] = _RValue;
				Data[(_PositionX + (_Height - 1 - _PositionY) * _Width) * 4 + 1] = _GValue;
				Data[(_PositionX + (_Height - 1 - _PositionY) * _Width) * 4 + 2] = _BValue;
				Data[(_PositionX + (_Height - 1 - _PositionY) * _Width) * 4 + 3] = _AValue;
			}
		}
	}

	for (size_t _PositionY = 0; _PositionY < _Height; _PositionY++)
	{
		for (size_t _PositionX = 0; _PositionX < _Width; _PositionX++)
		{
			if (!std::isfinite(Data[(_PositionX + _PositionY * _Width) * 4 + 0]) ||
				!std::isfinite(Data[(_PositionX + _PositionY * _Width) * 4 + 1]) ||
				!std::isfinite(Data[(_PositionX + _PositionY * _Width) * 4 + 2]) ||
				!std::isfinite(Data[(_PositionX + _PositionY * _Width) * 4 + 3]))
			{
				delete[] _ScanLine;
				delete[] Data;
				Data = nullptr;
				return false;
			}

			if (Data[(_PositionX + _PositionY * _Width) * 4 + 0] < 0.0f)
			{
				Data[(_PositionX + _PositionY * _Width) * 4 + 0] = 0.0f;
			}

			if (Data[(_PositionX + _PositionY * _Width) * 4 + 1] < 0.0f)
			{
				Data[(_PositionX + _PositionY * _Width) * 4 + 1] = 0.0f;
			}

			if (Data[(_PositionX + _PositionY * _Width) * 4 + 2] < 0.0f)
			{
				Data[(_PositionX + _PositionY * _Width) * 4 + 2] = 0.0f;
			}

			if (Data[(_PositionX + _PositionY * _Width) * 4 + 3] < 0.0f)
			{
				Data[(_PositionX + _PositionY * _Width) * 4 + 3] = 0.0f;
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
	if (!Data)
	{
		return FileContent();
	}

	BFW_STRING_STREAM_TYPE_A _Stream;

	_Stream.imbue(std::locale::classic());

	_Stream << "#?RADIANCE\x0A" << "FORMAT=32-bit_rle_rgbe\x0A\x0A+Y " << Height << " +X " << Width << "\x0A";

	if (!_Stream)
	{
		return FileContent();
	}

	BFW_STRING_TYPE_A _StreamStr = _Stream.str();

	FileContent _FileContent;

	if (!_FileContent.Create(_StreamStr.size() + Width * Height * 4 + 1))
	{
		return FileContent();
	}

	_FileContent[_FileContent.GetLength() - 1] = '\0';

	for (size_t _Index = 0; _Index < _StreamStr.size(); _Index++)
	{
		_FileContent[_Index] = _StreamStr[_Index];
	}

	if (_Flip)
	{
		if (ChannelsCount == 1)
		{
			for (size_t _PositionY = 0; _PositionY < Height; _PositionY++)
			{
				for (size_t _PositionX = 0; _PositionX < Width; _PositionX++)
				{
					HdrEncodeRGBE
					(
						Data[(_PositionX + (Height - 1 - _PositionY) * Width) * ChannelsCount + 0],
						0.0f,
						0.0f,
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 0 + _StreamStr.size()],
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 1 + _StreamStr.size()],
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 2 + _StreamStr.size()],
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 3 + _StreamStr.size()]
					);
				}
			}
		}

		if (ChannelsCount == 2)
		{
			for (size_t _PositionY = 0; _PositionY < Height; _PositionY++)
			{
				for (size_t _PositionX = 0; _PositionX < Width; _PositionX++)
				{
					HdrEncodeRGBE
					(
						Data[(_PositionX + (Height - 1 - _PositionY) * Width) * ChannelsCount + 0],
						Data[(_PositionX + (Height - 1 - _PositionY) * Width) * ChannelsCount + 1],
						0.0f,
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 0 + _StreamStr.size()],
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 1 + _StreamStr.size()],
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 2 + _StreamStr.size()],
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 3 + _StreamStr.size()]
					);
				}
			}
		}

		if (ChannelsCount == 3)
		{
			for (size_t _PositionY = 0; _PositionY < Height; _PositionY++)
			{
				for (size_t _PositionX = 0; _PositionX < Width; _PositionX++)
				{
					HdrEncodeRGBE
					(
						Data[(_PositionX + (Height - 1 - _PositionY) * Width) * ChannelsCount + 0],
						Data[(_PositionX + (Height - 1 - _PositionY) * Width) * ChannelsCount + 1],
						Data[(_PositionX + (Height - 1 - _PositionY) * Width) * ChannelsCount + 2],
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 0 + _StreamStr.size()],
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 1 + _StreamStr.size()],
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 2 + _StreamStr.size()],
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 3 + _StreamStr.size()]
					);
				}
			}
		}

		if (ChannelsCount == 4)
		{
			for (size_t _PositionY = 0; _PositionY < Height; _PositionY++)
			{
				for (size_t _PositionX = 0; _PositionX < Width; _PositionX++)
				{
					HdrEncodeRGBE
					(
						Data[(_PositionX + (Height - 1 - _PositionY) * Width) * ChannelsCount + 0],
						Data[(_PositionX + (Height - 1 - _PositionY) * Width) * ChannelsCount + 1],
						Data[(_PositionX + (Height - 1 - _PositionY) * Width) * ChannelsCount + 2],
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 0 + _StreamStr.size()],
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 1 + _StreamStr.size()],
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 2 + _StreamStr.size()],
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 3 + _StreamStr.size()]
					);
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
					HdrEncodeRGBE
					(
						Data[(_PositionX + _PositionY * Width) * ChannelsCount + 0],
						0.0f,
						0.0f,
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 0 + _StreamStr.size()],
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 1 + _StreamStr.size()],
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 2 + _StreamStr.size()],
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 3 + _StreamStr.size()]
					);
				}
			}
		}

		if (ChannelsCount == 2)
		{
			for (size_t _PositionY = 0; _PositionY < Height; _PositionY++)
			{
				for (size_t _PositionX = 0; _PositionX < Width; _PositionX++)
				{
					HdrEncodeRGBE
					(
						Data[(_PositionX + _PositionY * Width) * ChannelsCount + 0],
						Data[(_PositionX + _PositionY * Width) * ChannelsCount + 1],
						0.0f,
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 0 + _StreamStr.size()],
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 1 + _StreamStr.size()],
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 2 + _StreamStr.size()],
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 3 + _StreamStr.size()]
					);
				}
			}
		}

		if (ChannelsCount == 3)
		{
			for (size_t _PositionY = 0; _PositionY < Height; _PositionY++)
			{
				for (size_t _PositionX = 0; _PositionX < Width; _PositionX++)
				{
					HdrEncodeRGBE
					(
						Data[(_PositionX + _PositionY * Width) * ChannelsCount + 0],
						Data[(_PositionX + _PositionY * Width) * ChannelsCount + 1],
						Data[(_PositionX + _PositionY * Width) * ChannelsCount + 2],
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 0 + _StreamStr.size()],
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 1 + _StreamStr.size()],
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 2 + _StreamStr.size()],
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 3 + _StreamStr.size()]
					);
				}
			}
		}

		if (ChannelsCount == 4)
		{
			for (size_t _PositionY = 0; _PositionY < Height; _PositionY++)
			{
				for (size_t _PositionX = 0; _PositionX < Width; _PositionX++)
				{
					HdrEncodeRGBE
					(
						Data[(_PositionX + _PositionY * Width) * ChannelsCount + 0],
						Data[(_PositionX + _PositionY * Width) * ChannelsCount + 1],
						Data[(_PositionX + _PositionY * Width) * ChannelsCount + 2],
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 0 + _StreamStr.size()],
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 1 + _StreamStr.size()],
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 2 + _StreamStr.size()],
						_FileContent[(_PositionX + _PositionY * Width) * 4 + 3 + _StreamStr.size()]
					);
				}
			}
		}
	}

	return _FileContent;
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
