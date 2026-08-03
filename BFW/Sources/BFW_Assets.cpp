#include "../Headers/BFW.hpp"



#pragma pack(push, 1)

struct BitMapFileHeader
{
	char Type[2] = { '\0', '\0'};
	uint32_t Size = 0;
	uint16_t Reserved1 = 0;
	uint16_t Reserved2 = 0;
	uint32_t Offset = 0;
};

struct BitMapInfoHeader
{
	uint32_t Size = 0;
	uint32_t Width = 0;
	int32_t Height = 0;
	uint16_t Planes = 0;
	uint16_t BitCount = 0;
	uint32_t Compression = 0;
	uint32_t ImageSize = 0;
	uint32_t DPIX = 0;
	uint32_t DPIY = 0;
	uint32_t ColorsUsed = 0;
	uint32_t ColorsImportant = 0;
};

#pragma pack(pop)



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

void BFW::Assets::FileContent::Destroy()
{
	delete[] Data;
	Data = nullptr;
	Length = 0;
}

const bool BFW::Assets::FileContent::Load(std::ifstream& _File)
{
	Destroy();

	if (!_File.is_open())
	{
		return false;
	}

	size_t _CurrentPos = _File.tellg();

	_File.seekg(0, std::ios::end);

	size_t _Length = (size_t)(_File.tellg()) + 1;

	uint8_t* _Data = new uint8_t[_Length];

	if (!_Data)
	{
		_File.seekg(_CurrentPos, std::ios::beg);
		return false;
	}

	_File.seekg(0, std::ios::beg);

	_File.read((char*)(_Data), _Length - 1);

	if (_File.gcount() != _Length - 1)
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

	size_t _CurrentPos = _File.tellg();

	_File.seekg(0, std::ios::end);

	size_t _Length = (size_t)(_File.tellg()) + 1;

	uint8_t* _Data = new uint8_t[_Length];

	if (!_Data)
	{
		_File.seekg(_CurrentPos, std::ios::beg);
		return false;
	}

	_File.seekg(0, std::ios::beg);

	_File.read((char*)(_Data), _Length - 1);

	if (_File.gcount() != _Length - 1)
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

	size_t _Length = SizeofResource(_InstanceHandle, _ResourceHandle) + 1;

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

const bool BFW::Assets::FileContent::Save(std::ofstream& _File) const
{
	if (!Data || Length <= 1 || !_File.is_open())
	{
		return false;
	}

	_File.write((const char*)(Data), Length - 1);

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

	_File.write((const char*)(Data), Length - 1);

	if (!_File)
	{
		return false;
	}

	return true;
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

	const BitMapFileHeader& _RawFileHeader = *(const BitMapFileHeader*)(_FileContent.GetData());
	const BitMapInfoHeader& _RawInfoHeader = *(const BitMapInfoHeader*)(_FileContent.GetData() + sizeof(BitMapFileHeader));

	BitMapFileHeader _FileHeader = _RawFileHeader;
	BitMapInfoHeader _InfoHeader = _RawInfoHeader;

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

	const size_t _RowPadding = (4 - (_InfoHeader.Width * _InfoHeader.BitCount / 8) % 4) % 4;

	if (_FileHeader.Type[0] != 'B' || _FileHeader.Type[1] != 'M')
	{
		return false;
	}

	if (_FileHeader.Size + 1 != _FileContent.GetLength())
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

	if (_InfoHeader.Width == 0 || _InfoHeader.Height == 0 || _InfoHeader.Width * _InfoHeader.Height * _InfoHeader.BitCount / 8 + _RowPadding * _InfoHeader.Height + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader) != _FileHeader.Size)
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

	if (_InfoHeader.ImageSize != 0 && _InfoHeader.ImageSize != _InfoHeader.Width * _InfoHeader.Height * _InfoHeader.BitCount / 8 + _RowPadding * _InfoHeader.Height)
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

	if (_Flip && _AlreadyFlipped || !_Flip && !_AlreadyFlipped)
	{
		if (_InfoHeader.BitCount == 32)
		{
			for (size_t _Y = 0; _Y < Height; _Y++)
			{
				for (size_t _X = 0; _X < Width; _X++)
				{
					Data[(_X + _Y * Width) * ChannelsCount + 0] = _FileContent[_X * 4 + (Height - 1 - _Y) * (Width * 4 + _RowPadding) + 2 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)];
					Data[(_X + _Y * Width) * ChannelsCount + 1] = _FileContent[_X * 4 + (Height - 1 - _Y) * (Width * 4 + _RowPadding) + 1 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)];
					Data[(_X + _Y * Width) * ChannelsCount + 2] = _FileContent[_X * 4 + (Height - 1 - _Y) * (Width * 4 + _RowPadding) + 0 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)];
					Data[(_X + _Y * Width) * ChannelsCount + 3] = _FileContent[_X * 4 + (Height - 1 - _Y) * (Width * 4 + _RowPadding) + 3 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)];
				}
			}
		}

		if (_InfoHeader.BitCount == 24)
		{
			for (size_t _Y = 0; _Y < Height; _Y++)
			{
				for (size_t _X = 0; _X < Width; _X++)
				{
					Data[(_X + _Y * Width) * ChannelsCount + 0] = _FileContent[_X * 3 + (Height - 1 - _Y) * (Width * 3 + _RowPadding) + 2 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)];
					Data[(_X + _Y * Width) * ChannelsCount + 1] = _FileContent[_X * 3 + (Height - 1 - _Y) * (Width * 3 + _RowPadding) + 1 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)];
					Data[(_X + _Y * Width) * ChannelsCount + 2] = _FileContent[_X * 3 + (Height - 1 - _Y) * (Width * 3 + _RowPadding) + 0 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)];
					Data[(_X + _Y * Width) * ChannelsCount + 3] = 255;
				}
			}
		}
	}
	else
	{
		if (_InfoHeader.BitCount == 32)
		{
			for (size_t _Y = 0; _Y < Height; _Y++)
			{
				for (size_t _X = 0; _X < Width; _X++)
				{
					Data[(_X + _Y * Width) * ChannelsCount + 0] = _FileContent[_X * 4 + _Y * (Width * 4 + _RowPadding) + 2 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)];
					Data[(_X + _Y * Width) * ChannelsCount + 1] = _FileContent[_X * 4 + _Y * (Width * 4 + _RowPadding) + 1 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)];
					Data[(_X + _Y * Width) * ChannelsCount + 2] = _FileContent[_X * 4 + _Y * (Width * 4 + _RowPadding) + 0 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)];
					Data[(_X + _Y * Width) * ChannelsCount + 3] = _FileContent[_X * 4 + _Y * (Width * 4 + _RowPadding) + 3 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)];
				}
			}
		}

		if (_InfoHeader.BitCount == 24)
		{
			for (size_t _Y = 0; _Y < Height; _Y++)
			{
				for (size_t _X = 0; _X < Width; _X++)
				{
					Data[(_X + _Y * Width) * ChannelsCount + 0] = _FileContent[_X * 3 + _Y * (Width * 3 + _RowPadding) + 2 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)];
					Data[(_X + _Y * Width) * ChannelsCount + 1] = _FileContent[_X * 3 + _Y * (Width * 3 + _RowPadding) + 1 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)];
					Data[(_X + _Y * Width) * ChannelsCount + 2] = _FileContent[_X * 3 + _Y * (Width * 3 + _RowPadding) + 0 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)];
					Data[(_X + _Y * Width) * ChannelsCount + 3] = 255;
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
	_FileHeader.Size = (uint32_t)(sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader) + Width * Height * 4);
	_FileHeader.Reserved1 = 0;
	_FileHeader.Reserved2 = 0;
	_FileHeader.Offset = sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader);

	BitMapInfoHeader _InfoHeader;
	uint8_t* _InfoHeaderPtr = (uint8_t*)(&_InfoHeader);

	_InfoHeader.Size = sizeof(BitMapInfoHeader);
	_InfoHeader.Width = (uint32_t)(Width);
	_InfoHeader.Height = (int32_t)(Height);
	_InfoHeader.Planes = 1;
	_InfoHeader.BitCount = 32;
	_InfoHeader.Compression = 0;
	_InfoHeader.ImageSize = (uint32_t)(Width * Height * 4);
	_InfoHeader.DPIX = 0;
	_InfoHeader.DPIY = 0;
	_InfoHeader.ColorsUsed = 0;
	_InfoHeader.ColorsImportant = 0;

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
			for (size_t _Y = 0; _Y < Height; _Y++)
			{
				for (size_t _X = 0; _X < Width; _X++)
				{
					_FileContent[(_X + _Y * Width) * 4 + 2 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_X + _Y * Width) * ChannelsCount + 0];
					_FileContent[(_X + _Y * Width) * 4 + 1 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = 0;
					_FileContent[(_X + _Y * Width) * 4 + 0 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = 0;
					_FileContent[(_X + _Y * Width) * 4 + 3 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = 255;
				}
			}
		}

		if (ChannelsCount == 2)
		{
			for (size_t _Y = 0; _Y < Height; _Y++)
			{
				for (size_t _X = 0; _X < Width; _X++)
				{
					_FileContent[(_X + _Y * Width) * 4 + 2 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_X + _Y * Width) * ChannelsCount + 0];
					_FileContent[(_X + _Y * Width) * 4 + 1 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_X + _Y * Width) * ChannelsCount + 1];
					_FileContent[(_X + _Y * Width) * 4 + 0 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = 0;
					_FileContent[(_X + _Y * Width) * 4 + 3 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = 255;
				}
			}
		}

		if (ChannelsCount == 3)
		{
			for (size_t _Y = 0; _Y < Height; _Y++)
			{
				for (size_t _X = 0; _X < Width; _X++)
				{
					_FileContent[(_X + _Y * Width) * 4 + 2 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_X + _Y * Width) * ChannelsCount + 0];
					_FileContent[(_X + _Y * Width) * 4 + 1 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_X + _Y * Width) * ChannelsCount + 1];
					_FileContent[(_X + _Y * Width) * 4 + 0 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_X + _Y * Width) * ChannelsCount + 2];
					_FileContent[(_X + _Y * Width) * 4 + 3 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = 255;
				}
			}
		}

		if (ChannelsCount == 4)
		{
			for (size_t _Y = 0; _Y < Height; _Y++)
			{
				for (size_t _X = 0; _X < Width; _X++)
				{
					_FileContent[(_X + _Y * Width) * 4 + 2 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_X + _Y * Width) * ChannelsCount + 0];
					_FileContent[(_X + _Y * Width) * 4 + 1 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_X + _Y * Width) * ChannelsCount + 1];
					_FileContent[(_X + _Y * Width) * 4 + 0 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_X + _Y * Width) * ChannelsCount + 2];
					_FileContent[(_X + _Y * Width) * 4 + 3 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_X + _Y * Width) * ChannelsCount + 3];
				}
			}
		}
	}
	else
	{
		if (ChannelsCount == 1)
		{
			for (size_t _Y = 0; _Y < Height; _Y++)
			{
				for (size_t _X = 0; _X < Width; _X++)
				{
					_FileContent[(_X + _Y * Width) * 4 + 2 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_X + (Height - 1 - _Y) * Width) * ChannelsCount + 0];
					_FileContent[(_X + _Y * Width) * 4 + 1 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = 0;
					_FileContent[(_X + _Y * Width) * 4 + 0 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = 0;
					_FileContent[(_X + _Y * Width) * 4 + 3 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = 255;
				}
			}
		}

		if (ChannelsCount == 2)
		{
			for (size_t _Y = 0; _Y < Height; _Y++)
			{
				for (size_t _X = 0; _X < Width; _X++)
				{
					_FileContent[(_X + _Y * Width) * 4 + 2 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_X + (Height - 1 - _Y) * Width) * ChannelsCount + 0];
					_FileContent[(_X + _Y * Width) * 4 + 1 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_X + (Height - 1 - _Y) * Width) * ChannelsCount + 1];
					_FileContent[(_X + _Y * Width) * 4 + 0 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = 0;
					_FileContent[(_X + _Y * Width) * 4 + 3 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = 255;
				}
			}
		}

		if (ChannelsCount == 3)
		{
			for (size_t _Y = 0; _Y < Height; _Y++)
			{
				for (size_t _X = 0; _X < Width; _X++)
				{
					_FileContent[(_X + _Y * Width) * 4 + 2 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_X + (Height - 1 - _Y) * Width) * ChannelsCount + 0];
					_FileContent[(_X + _Y * Width) * 4 + 1 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_X + (Height - 1 - _Y) * Width) * ChannelsCount + 1];
					_FileContent[(_X + _Y * Width) * 4 + 0 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_X + (Height - 1 - _Y) * Width) * ChannelsCount + 2];
					_FileContent[(_X + _Y * Width) * 4 + 3 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = 255;
				}
			}
		}

		if (ChannelsCount == 4)
		{
			for (size_t _Y = 0; _Y < Height; _Y++)
			{
				for (size_t _X = 0; _X < Width; _X++)
				{
					_FileContent[(_X + _Y * Width) * 4 + 2 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_X + (Height - 1 - _Y) * Width) * ChannelsCount + 0];
					_FileContent[(_X + _Y * Width) * 4 + 1 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_X + (Height - 1 - _Y) * Width) * ChannelsCount + 1];
					_FileContent[(_X + _Y * Width) * 4 + 0 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_X + (Height - 1 - _Y) * Width) * ChannelsCount + 2];
					_FileContent[(_X + _Y * Width) * 4 + 3 + sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)] = Data[(_X + (Height - 1 - _Y) * Width) * ChannelsCount + 3];
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

uint8_t* BFW::Assets::BitMap::operator[] (const size_t _Y)
{
	return Data + _Y * Width * ChannelsCount;
}

const uint8_t* BFW::Assets::BitMap::operator* (const size_t _Y) const
{
	return Data + _Y * Width * ChannelsCount;
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
