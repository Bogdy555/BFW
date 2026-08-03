#include "../Headers/BFW.hpp"



#pragma pack(push, 1)

struct BitMapFileHeader
{

	char Type[2];
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

	char RIFF[4];
	uint32_t FileSize;
	char WAVE[4];

	WaveFileHeader();
	WaveFileHeader(const WaveFileHeader& _Other) = default;
	WaveFileHeader(WaveFileHeader&& _Other) noexcept;
	~WaveFileHeader();

	WaveFileHeader& operator= (const WaveFileHeader& _Other) = default;
	WaveFileHeader& operator= (WaveFileHeader&& _Other) noexcept;

};

struct WaveChunkHeader
{

	char ID[4];
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

	if (!_Size || _Size % (_Info.Channels * _Info.BitsPerSample / 8) != 0)
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

	if (_FileHeader.FileSize + 1 != _FileContent.GetLength() - 8)
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

	if (Size % (Info.Channels * Info.BitsPerSample / 8) != 0)
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
	_FileHeader.FileSize = BFW_MACHINE_TO_LITTLE_ENDIAN_32(sizeof(WaveFileHeader) + sizeof(WaveChunkHeader) + sizeof(WaveFormat) + sizeof(WaveChunkHeader) + Size - 8);
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
	_DataHeader.Size = BFW_MACHINE_TO_LITTLE_ENDIAN_32(Size);

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
