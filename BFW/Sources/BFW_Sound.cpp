#include "..\Headers\BFW.hpp"



#ifdef BFW_WINDOWS_PLATFORM



BFW::Sound::SoundBuff::SoundBuff() : AudioInfo({ 0 }), BuffSize(0), Buff(nullptr)
{

}

BFW::Sound::SoundBuff::SoundBuff(const SoundBuff& _Other) : AudioInfo(_Other.AudioInfo), BuffSize(_Other.BuffSize), Buff(nullptr)
{
	if (!_Other.BuffSize)
	{
		AudioInfo = { 0 };
		return;
	}

	Buff = new unsigned char[_Other.BuffSize];

	if (!Buff)
	{
		BuffSize = 0;
		AudioInfo = { 0 };
		return;
	}

	for (unsigned long _Index = 0; _Index < BuffSize; _Index++)
	{
		Buff[_Index] = _Other[_Index];
	}
}

BFW::Sound::SoundBuff::SoundBuff(SoundBuff&& _Other) noexcept : AudioInfo(_Other.AudioInfo), BuffSize(_Other.BuffSize), Buff(_Other.Buff)
{
	_Other.AudioInfo = { 0 };
	_Other.BuffSize = 0;
	_Other.Buff = nullptr;
}

BFW::Sound::SoundBuff::~SoundBuff()
{
	if (Buff)
	{
		delete[] Buff;
	}
}

bool BFW::Sound::SoundBuff::Create(const unsigned long _BuffSize)
{
	if (Buff)
	{
		BuffSize = 0;
		delete[] Buff;
		Buff = nullptr;
	}

	Buff = new unsigned char[_BuffSize];

	if (!Buff)
	{
		return false;
	}

	BuffSize = _BuffSize;

	return true;
}

void BFW::Sound::SoundBuff::Destroy()
{
	if (Buff)
	{
		BuffSize = 0;
		delete[] Buff;
		Buff = nullptr;
	}
}

bool BFW::Sound::SoundBuff::LoadFromResource(const HINSTANCE _hInstance, const unsigned long _ResourceID)
{
	if (Buff)
	{
		BuffSize = 0;
		delete[] Buff;
		Buff = nullptr;
	}
	AudioInfo = { 0 };

	HRSRC _hResource = FindResource(_hInstance, MAKEINTRESOURCE(_ResourceID), MAKEINTRESOURCE(BFW_WAV_RESOURCE));

	if (!_hResource)
	{
		return false;
	}

	BuffSize = SizeofResource(_hInstance, _hResource) - 44;

	if (!BuffSize)
	{
		return false;
	}

	HGLOBAL _hGlobal = LoadResource(_hInstance, _hResource);

	if (!_hGlobal)
	{
		BuffSize = 0;
		return false;
	}

	const unsigned char* _ResourcePtr = (const unsigned char*)(LockResource(_hGlobal));

	if (!_ResourcePtr)
	{
		BuffSize = 0;
		FreeResource(_hGlobal);
		return false;
	}

	Buff = new unsigned char[BuffSize];

	if (!Buff)
	{
		UnlockResource(_hGlobal);
		FreeResource(_hGlobal);
		BuffSize = 0;
		return false;
	}

	AudioInfo.wFormatTag = *(const unsigned short*)(_ResourcePtr + 20);
	AudioInfo.nChannels = *(const unsigned short*)(_ResourcePtr + 22);
	AudioInfo.nSamplesPerSec = *(const unsigned long*)(_ResourcePtr + 24);
	AudioInfo.nAvgBytesPerSec = *(const unsigned long*)(_ResourcePtr + 28);
	AudioInfo.nBlockAlign = *(const unsigned short*)(_ResourcePtr + 32);
	AudioInfo.wBitsPerSample = *(const unsigned short*)(_ResourcePtr + 34);

	for (unsigned long _Index = 0; _Index < BuffSize; _Index++)
	{
		Buff[_Index] = _ResourcePtr[_Index + 44];
	}

	UnlockResource(_hGlobal);
	FreeResource(_hGlobal);

	return true;
}

bool BFW::Sound::SoundBuff::LoadFromFile(const wchar_t* _FilePath)
{
	if (Buff)
	{
		BuffSize = 0;
		delete[] Buff;
		Buff = nullptr;
	}
	AudioInfo = { 0 };

	if (!_FilePath)
	{
		BFW_DEBUG_BREAK_MSG(L"Can not load audio file because of invalid parameters!");
		return false;
	}

	FILE* _File = nullptr;

	_wfopen_s(&_File, _FilePath, L"rb");

	if (!_File)
	{
		return false;
	}

	fseek(_File, 20, SEEK_SET);

	if (fread_s(&AudioInfo.wFormatTag, 2, 2, 1, _File) != 1)
	{
		fclose(_File);
		AudioInfo = { 0 };
		return false;
	}
	if (fread_s(&AudioInfo.nChannels, 2, 2, 1, _File) != 1)
	{
		fclose(_File);
		AudioInfo = { 0 };
		return false;
	}
	if (fread_s(&AudioInfo.nSamplesPerSec, 4, 4, 1, _File) != 1)
	{
		fclose(_File);
		AudioInfo = { 0 };
		return false;
	}
	if (fread_s(&AudioInfo.nAvgBytesPerSec, 4, 4, 1, _File) != 1)
	{
		fclose(_File);
		AudioInfo = { 0 };
		return false;
	}
	if (fread_s(&AudioInfo.nBlockAlign, 2, 2, 1, _File) != 1)
	{
		fclose(_File);
		AudioInfo = { 0 };
		return false;
	}
	if (fread_s(&AudioInfo.wBitsPerSample, 2, 2, 1, _File) != 1)
	{
		fclose(_File);
		AudioInfo = { 0 };
		return false;
	}

	fseek(_File, 40, SEEK_SET);

	if (fread_s(&BuffSize, 4, 4, 1, _File) != 1)
	{
		fclose(_File);
		AudioInfo = { 0 };
		BuffSize = 0;
		return false;
	}

	if (!BuffSize)
	{
		fclose(_File);
		AudioInfo = { 0 };
		return false;
	}

	Buff = new unsigned char[BuffSize];

	if (!Buff)
	{
		fclose(_File);
		BuffSize = 0;
		AudioInfo = { 0 };
		return false;
	}

	if (fread_s(Buff, BuffSize, 1, BuffSize, _File) != BuffSize)
	{
		fclose(_File);
		BuffSize = 0;
		delete[] Buff;
		Buff = nullptr;
		AudioInfo = { 0 };
		return false;
	}

	fclose(_File);

	return true;
}

const bool BFW::Sound::SoundBuff::SaveToFile(const wchar_t* _FilePath) const
{
	if (!_FilePath)
	{
		BFW_DEBUG_BREAK_MSG(L"Can not save audio file because of invalid parameters!");
		return false;
	}

	if (!Buff || !BuffSize)
	{
		BFW_DEBUG_BREAK_MSG(L"Can not save audio file because of empty buffer!");
		return false;
	}

	FILE* _File = nullptr;

	_wfopen_s(&_File, _FilePath, L"wb");

	if (!_File)
	{
		return false;
	}

	if (fwrite("RIFF    WAVEfmt ", 1, 16, _File) != 16)
	{
		fclose(_File);
		_wremove(_FilePath);
		return false;
	}

	{
		unsigned long _SubChunkSize_1 = 16;
		if (fwrite(&_SubChunkSize_1, 4, 1, _File) != 1)
		{
			fclose(_File);
			_wremove(_FilePath);
			return false;
		}
	}

	if (fwrite(&AudioInfo.wFormatTag, 2, 1, _File) != 1)
	{
		fclose(_File);
		_wremove(_FilePath);
		return false;
	}
	if (fwrite(&AudioInfo.nChannels, 2, 1, _File) != 1)
	{
		fclose(_File);
		_wremove(_FilePath);
		return false;
	}
	if (fwrite(&AudioInfo.nSamplesPerSec, 4, 1, _File) != 1)
	{
		fclose(_File);
		_wremove(_FilePath);
		return false;
	}
	if (fwrite(&AudioInfo.nAvgBytesPerSec, 4, 1, _File) != 1)
	{
		fclose(_File);
		_wremove(_FilePath);
		return false;
	}
	if (fwrite(&AudioInfo.nBlockAlign, 2, 1, _File) != 1)
	{
		fclose(_File);
		_wremove(_FilePath);
		return false;
	}
	if (fwrite(&AudioInfo.wBitsPerSample, 2, 1, _File) != 1)
	{
		fclose(_File);
		_wremove(_FilePath);
		return false;
	}

	if (fwrite("data", 1, 4, _File) != 4)
	{
		fclose(_File);
		_wremove(_FilePath);
		return false;
	}

	if (fwrite(&BuffSize, 4, 1, _File) != 1)
	{
		fclose(_File);
		_wremove(_FilePath);
		return false;
	}

	if (fwrite(Buff, 1, BuffSize, _File) != BuffSize)
	{
		fclose(_File);
		_wremove(_FilePath);
		return false;
	}

	{
		unsigned long _FileSize = ftell(_File) - 8;

		fseek(_File, 4, SEEK_SET);

		if (fwrite(&_FileSize, 4, 1, _File) != 1)
		{
			fclose(_File);
			_wremove(_FilePath);
			return false;
		}
	}

	fclose(_File);

	return true;
}

const unsigned long BFW::Sound::SoundBuff::GetBuffSize() const
{
	return BuffSize;
}

WAVEFORMATEX& BFW::Sound::SoundBuff::GetAudioInfo()
{
	return AudioInfo;
}

const WAVEFORMATEX& BFW::Sound::SoundBuff::GetAudioInfo() const
{
	return AudioInfo;
}

BFW::Sound::SoundBuff::operator unsigned char* ()
{
	return Buff;
}

BFW::Sound::SoundBuff::operator const unsigned char* () const
{
	return Buff;
}

void BFW::Sound::SoundBuff::operator= (const SoundBuff& _Other)
{
	if (Buff)
	{
		delete[] Buff;
		Buff = nullptr;
	}

	AudioInfo = _Other.AudioInfo;
	BuffSize = _Other.BuffSize;

	if (!_Other.BuffSize)
	{
		AudioInfo = { 0 };
		return;
	}

	Buff = new unsigned char[_Other.BuffSize];

	if (!Buff)
	{
		BuffSize = 0;
		AudioInfo = { 0 };
		return;
	}

	for (unsigned long _Index = 0; _Index < BuffSize; _Index++)
	{
		Buff[_Index] = _Other[_Index];
	}
}

void BFW::Sound::SoundBuff::operator= (SoundBuff&& _Other) noexcept
{
	AudioInfo = _Other.AudioInfo;
	BuffSize = _Other.BuffSize;
	Buff = _Other.Buff;

	_Other.AudioInfo = { 0 };
	_Other.BuffSize = 0;
	_Other.Buff = nullptr;
}



BFW::Sound::ResourceInStream::ResourceInStream() : hGlobal(NULL), AudioInfo({ 0 }), ResourceBuffSize(0), ResourceBuff(nullptr), CurrentPoint(0)
{

}

BFW::Sound::ResourceInStream::ResourceInStream(ResourceInStream&& _Other) noexcept : hGlobal(_Other.hGlobal), AudioInfo(_Other.AudioInfo), ResourceBuffSize(_Other.ResourceBuffSize), ResourceBuff(_Other.ResourceBuff), CurrentPoint(_Other.CurrentPoint)
{
	_Other.hGlobal = NULL;
	_Other.AudioInfo = { 0 };
	_Other.ResourceBuffSize = 0;
	_Other.ResourceBuff = nullptr;
	_Other.CurrentPoint = 0;
}

BFW::Sound::ResourceInStream::~ResourceInStream()
{
	Stop();
}

const bool BFW::Sound::ResourceInStream::Started() const
{
	return ResourceBuff != nullptr;
}

bool BFW::Sound::ResourceInStream::Start(const HINSTANCE _hInstance, const unsigned long _ResourceID)
{
	Stop();

	HRSRC _hResource = FindResource(_hInstance, MAKEINTRESOURCE(_ResourceID), MAKEINTRESOURCE(BFW_WAV_RESOURCE));

	if (!_hResource)
	{
		return false;
	}

	ResourceBuffSize = SizeofResource(_hInstance, _hResource) - 44;

	if (!ResourceBuffSize)
	{
		return false;
	}

	hGlobal = LoadResource(_hInstance, _hResource);

	if (!hGlobal)
	{
		ResourceBuffSize = 0;
		return false;
	}

	ResourceBuff = (const unsigned char*)(LockResource(hGlobal));

	if (!ResourceBuff)
	{
		FreeResource(hGlobal);
		hGlobal = NULL;
		ResourceBuffSize = 0;
		return false;
	}

	AudioInfo.wFormatTag = ((const unsigned short*)(ResourceBuff + 20))[0];
	AudioInfo.nChannels = ((const unsigned short*)(ResourceBuff + 22))[0];
	AudioInfo.nSamplesPerSec = ((const unsigned int*)(ResourceBuff + 24))[0];
	AudioInfo.nAvgBytesPerSec = ((const unsigned int*)(ResourceBuff + 28))[0];
	AudioInfo.nBlockAlign = ((const unsigned short*)(ResourceBuff + 32))[0];
	AudioInfo.wBitsPerSample = ((const unsigned short*)(ResourceBuff + 34))[0];

	return true;
}

bool BFW::Sound::ResourceInStream::Stream(unsigned char* _Buff, const unsigned long _BuffSize, unsigned long& _ReadSize)
{
	if (!_Buff || !_BuffSize)
	{
		BFW_DEBUG_BREAK_MSG(L"Could not stream audio from resource because of invalid parameters!");
		return false;
	}

	if (!ResourceBuff)
	{
		return false;
	}

	if (ResourceBuffSize == CurrentPoint)
	{
		_ReadSize = 0;
		return true;
	}

	unsigned long _PrevPoint = CurrentPoint;

	for (unsigned long _Index = 0; _Index < _BuffSize; _Index++)
	{
		if (CurrentPoint == ResourceBuffSize)
		{
			break;
		}
		_Buff[_Index] = ResourceBuff[CurrentPoint + 44];
		CurrentPoint++;
	}

	_ReadSize = CurrentPoint - _PrevPoint;

	return true;
}

void BFW::Sound::ResourceInStream::Stop()
{
	if (!ResourceBuff)
	{
		return;
	}

	UnlockResource(hGlobal);
	FreeResource(hGlobal);

	hGlobal = NULL;
	AudioInfo = { 0 };
	ResourceBuffSize = 0;
	ResourceBuff = nullptr;
	CurrentPoint = 0;
}

const WAVEFORMATEX BFW::Sound::ResourceInStream::GetAudioInfo() const
{
	return AudioInfo;
}

const unsigned long BFW::Sound::ResourceInStream::GetBuffSize() const
{
	return ResourceBuffSize;
}

const unsigned long BFW::Sound::ResourceInStream::GetCurrentPoint() const
{
	return CurrentPoint;
}

void BFW::Sound::ResourceInStream::operator= (ResourceInStream&& _Other) noexcept
{
	hGlobal = _Other.hGlobal;
	AudioInfo = _Other.AudioInfo;
	ResourceBuffSize = _Other.ResourceBuffSize;
	ResourceBuff = _Other.ResourceBuff;
	CurrentPoint = _Other.CurrentPoint;

	_Other.hGlobal = NULL;
	_Other.AudioInfo = { 0 };
	_Other.ResourceBuffSize = 0;
	_Other.ResourceBuff = nullptr;
	_Other.CurrentPoint = 0;
}



BFW::Sound::FileInStream::FileInStream() : File(nullptr), AudioInfo({ 0 }), FileBuffSize(0), CurrentPoint(0)
{

}

BFW::Sound::FileInStream::FileInStream(FileInStream&& _Other) noexcept : File(_Other.File), AudioInfo(_Other.AudioInfo), FileBuffSize(_Other.FileBuffSize), CurrentPoint(_Other.CurrentPoint)
{
	_Other.File = nullptr;
	_Other.AudioInfo = { 0 };
	_Other.FileBuffSize = 0;
	_Other.CurrentPoint = 0;
}

BFW::Sound::FileInStream::~FileInStream()
{
	Stop();
}

const bool BFW::Sound::FileInStream::Started() const
{
	return File != nullptr;
}

bool BFW::Sound::FileInStream::Start(const wchar_t* _FileName)
{
	Stop();

	if (!_FileName)
	{
		BFW_DEBUG_BREAK_MSG(L"Can not start audio stream from file because of invalid parameters!");
		return false;
	}

	_wfopen_s(&File, _FileName, L"rb");

	if (!File)
	{
		return false;
	}

	fseek(File, 20, SEEK_SET);

	if (fread_s(&AudioInfo.wFormatTag, 2, 2, 1, File) != 1)
	{
		fclose(File);
		File = nullptr;
		AudioInfo = { 0 };
		return false;
	}
	if (fread_s(&AudioInfo.nChannels, 2, 2, 1, File) != 1)
	{
		fclose(File);
		File = nullptr;
		AudioInfo = { 0 };
		return false;
	}
	if (fread_s(&AudioInfo.nSamplesPerSec, 4, 4, 1, File) != 1)
	{
		fclose(File);
		File = nullptr;
		AudioInfo = { 0 };
		return false;
	}
	if (fread_s(&AudioInfo.nAvgBytesPerSec, 4, 4, 1, File) != 1)
	{
		fclose(File);
		File = nullptr;
		AudioInfo = { 0 };
		return false;
	}
	if (fread_s(&AudioInfo.nBlockAlign, 2, 2, 1, File) != 1)
	{
		fclose(File);
		File = nullptr;
		AudioInfo = { 0 };
		return false;
	}
	if (fread_s(&AudioInfo.wBitsPerSample, 2, 2, 1, File) != 1)
	{
		fclose(File);
		File = nullptr;
		AudioInfo = { 0 };
		return false;
	}

	fseek(File, 40, SEEK_SET);

	if (fread_s(&FileBuffSize, 4, 4, 1, File) != 1)
	{
		fclose(File);
		File = nullptr;
		AudioInfo = { 0 };
		FileBuffSize = 0;
		return false;
	}

	if (!FileBuffSize)
	{
		fclose(File);
		File = nullptr;
		AudioInfo = { 0 };
		return false;
	}

	return true;
}

bool BFW::Sound::FileInStream::Stream(unsigned char* _Buff, const unsigned long _BuffSize, unsigned long& _ReadSize)
{
	if (!_Buff || !_BuffSize)
	{
		BFW_DEBUG_BREAK_MSG(L"Can not stream audio from file because of invalid parameters!");
		return false;
	}

	if (!File)
	{
		return false;
	}

	_ReadSize = (unsigned long)(fread_s(_Buff, _BuffSize, 1, _BuffSize, File));

	CurrentPoint += _ReadSize;

	if (_ReadSize < _BuffSize && CurrentPoint < FileBuffSize)
	{
		fclose(File);
		File = nullptr;
		AudioInfo = { 0 };
		FileBuffSize = 0;
		CurrentPoint = 0;
		_ReadSize = 0;
		return false;
	}

	return true;
}

void BFW::Sound::FileInStream::Stop()
{
	if (!File)
	{
		return;
	}

	fclose(File);
	File = nullptr;
	AudioInfo = { 0 };
	FileBuffSize = 0;
	CurrentPoint = 0;
}

const WAVEFORMATEX BFW::Sound::FileInStream::GetAudioInfo() const
{
	return AudioInfo;
}

const unsigned long BFW::Sound::FileInStream::GetBuffSize() const
{
	return FileBuffSize;
}

const unsigned long BFW::Sound::FileInStream::GetCurrentPoint() const
{
	return CurrentPoint;
}

void BFW::Sound::FileInStream::operator= (FileInStream&& _Other) noexcept
{
	File = _Other.File;
	AudioInfo = _Other.AudioInfo;
	FileBuffSize = _Other.FileBuffSize;
	CurrentPoint = _Other.CurrentPoint;

	_Other.File = nullptr;
	_Other.AudioInfo = { 0 };
	_Other.FileBuffSize = 0;
	_Other.CurrentPoint = 0;
}



BFW::Sound::FileOutStream::FileOutStream() : File(nullptr), FileName(nullptr), AudioInfo({ 0 }), SavedSize(0)
{

}

BFW::Sound::FileOutStream::FileOutStream(FileOutStream&& _Other) noexcept : File(_Other.File), FileName(_Other.FileName), AudioInfo(_Other.AudioInfo), SavedSize(_Other.SavedSize)
{
	_Other.File = nullptr;
	_Other.FileName = nullptr;
	_Other.AudioInfo = { 0 };
	_Other.SavedSize = 0;
}

BFW::Sound::FileOutStream::~FileOutStream()
{
	Stop();
}

const bool BFW::Sound::FileOutStream::Started() const
{
	return File != nullptr;
}

bool BFW::Sound::FileOutStream::Start(const wchar_t* _FileName, const WAVEFORMATEX& _AudioInfo)
{
	Stop();

	if (!_FileName)
	{
		BFW_DEBUG_BREAK_MSG(L"Can not start audio stream to file because of invalid parameters!");
		return false;
	}

	size_t _StrLen = wcslen(_FileName) + 1;

	if (_StrLen < 2)
	{
		return false;
	}

	FileName = new wchar_t[_StrLen];

	if (!FileName)
	{
		return false;
	}

	for (size_t _Index = 0; _Index < _StrLen; _Index++)
	{
		FileName[_Index] = _FileName[_Index];
	}

	_wfopen_s(&File, FileName, L"wb");

	if (!File)
	{
		delete[] FileName;
		FileName = nullptr;
		return false;
	}

	if (fwrite("RIFF    WAVEfmt ", 1, 16, File) != 16)
	{
		fclose(File);
		File = nullptr;
		_wremove(FileName);
		delete[] FileName;
		FileName = nullptr;
		return false;
	}

	{
		unsigned long _SubChunkSize_1 = 16;
		if (fwrite(&_SubChunkSize_1, 4, 1, File) != 1)
		{
			fclose(File);
			File = nullptr;
			_wremove(FileName);
			delete[] FileName;
			FileName = nullptr;
			return false;
		}
	}

	if (fwrite(&_AudioInfo.wFormatTag, 2, 1, File) != 1)
	{
		fclose(File);
		File = nullptr;
		_wremove(FileName);
		delete[] FileName;
		FileName = nullptr;
		return false;
	}
	if (fwrite(&_AudioInfo.nChannels, 2, 1, File) != 1)
	{
		fclose(File);
		File = nullptr;
		_wremove(FileName);
		delete[] FileName;
		FileName = nullptr;
		return false;
	}
	if (fwrite(&_AudioInfo.nSamplesPerSec, 4, 1, File) != 1)
	{
		fclose(File);
		File = nullptr;
		_wremove(FileName);
		delete[] FileName;
		FileName = nullptr;
		return false;
	}
	if (fwrite(&_AudioInfo.nAvgBytesPerSec, 4, 1, File) != 1)
	{
		fclose(File);
		File = nullptr;
		_wremove(FileName);
		delete[] FileName;
		FileName = nullptr;
		return false;
	}
	if (fwrite(&_AudioInfo.nBlockAlign, 2, 1, File) != 1)
	{
		fclose(File);
		File = nullptr;
		_wremove(FileName);
		delete[] FileName;
		FileName = nullptr;
		return false;
	}
	if (fwrite(&_AudioInfo.wBitsPerSample, 2, 1, File) != 1)
	{
		fclose(File);
		File = nullptr;
		_wremove(FileName);
		delete[] FileName;
		FileName = nullptr;
		return false;
	}

	if (fwrite("data    ", 1, 8, File) != 8)
	{
		fclose(File);
		File = nullptr;
		_wremove(FileName);
		delete[] FileName;
		FileName = nullptr;
		return false;
	}

	AudioInfo = _AudioInfo;

	return true;
}

bool BFW::Sound::FileOutStream::Stream(const unsigned char* _Buff, const unsigned long _BuffSize)
{
	if (!_Buff || !_BuffSize)
	{
		BFW_DEBUG_BREAK_MSG(L"Can not stream audio to file because of invalid parameters!");
		return false;
	}

	if (!File || !FileName)
	{
		return false;
	}

	if (fwrite(_Buff, 1, _BuffSize, File) != _BuffSize)
	{
		fclose(File);
		File = nullptr;
		_wremove(FileName);
		delete[] FileName;
		FileName = nullptr;
		AudioInfo = { 0 };
		SavedSize = 0;
		return false;
	}

	SavedSize += _BuffSize;

	return true;
}

bool BFW::Sound::FileOutStream::Stop()
{
	if (!File || !FileName)
	{
		return false;
	}

	AudioInfo = { 0 };
	SavedSize = 0;

	unsigned long _FileSize = ftell(File);

	{
		unsigned long _NewFileSize = _FileSize - 8;

		fseek(File, 4, SEEK_SET);

		if (fwrite(&_NewFileSize, 4, 1, File) != 1)
		{
			fclose(File);
			File = nullptr;
			_wremove(FileName);
			delete[] FileName;
			FileName = nullptr;
			return false;
		}
	}

	fseek(File, 40, SEEK_SET);

	_FileSize -= 44;

	if (!_FileSize)
	{
		fclose(File);
		File = nullptr;
		_wremove(FileName);
		delete[] FileName;
		FileName = nullptr;
		return false;
	}

	if (fwrite(&_FileSize, 4, 1, File) != 1)
	{
		fclose(File);
		File = nullptr;
		_wremove(FileName);
		delete[] FileName;
		FileName = nullptr;
		return false;
	}

	fclose(File);
	File = nullptr;
	delete[] FileName;
	FileName = nullptr;

	return true;
}

const wchar_t* BFW::Sound::FileOutStream::GetFileName() const
{
	return FileName;
}

const WAVEFORMATEX BFW::Sound::FileOutStream::GetAudioInfo() const
{
	return AudioInfo;
}

const unsigned long BFW::Sound::FileOutStream::GetSavedSize() const
{
	return SavedSize;
}

void BFW::Sound::FileOutStream::operator= (FileOutStream&& _Other) noexcept
{
	File = _Other.File;
	FileName = _Other.FileName;
	AudioInfo = _Other.AudioInfo;
	SavedSize = _Other.SavedSize;

	_Other.File = nullptr;
	_Other.FileName = nullptr;
	_Other.AudioInfo = { 0 };
	_Other.SavedSize = 0;
}



#endif
