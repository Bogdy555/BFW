#include "../Headers/BFW.hpp"



#pragma pack(push, 1)

struct WaveFileHeader
{

	BFW_CHAR_TYPE_A RIFF[4];
	uint32_t FileSize;
	BFW_CHAR_TYPE_A WAVE[4];

	WaveFileHeader();
	WaveFileHeader(const WaveFileHeader& _Other) = default;
	WaveFileHeader(WaveFileHeader&& _Other) noexcept;
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
	WaveChunkHeader& operator= (const WaveChunkHeader& _Other) = default;
	WaveChunkHeader& operator= (WaveChunkHeader& _Other) noexcept;

};

#pragma pack(pop)



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
