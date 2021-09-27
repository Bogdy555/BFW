#include "..\Headers\BFW.hpp"



#ifdef BFW_WINDOWS_PLATFORM



bool BFW_API BFW::Sound::LoadFromFile(const wchar_t* _FilePath, unsigned char** _Buff, unsigned __int32* _BuffSize, WAVEFORMATEX* _AudioInfo)
{
	if (!_FilePath || !_Buff || !_BuffSize || !_AudioInfo)
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

	if (fread_s(&_AudioInfo->wFormatTag, 2, 2, 1, _File) != 1)
	{
		fclose(_File);
		return false;
	}
	if (fread_s(&_AudioInfo->nChannels, 2, 2, 1, _File) != 1)
	{
		fclose(_File);
		return false;
	}
	if (fread_s(&_AudioInfo->nSamplesPerSec, 4, 4, 1, _File) != 1)
	{
		fclose(_File);
		return false;
	}
	if (fread_s(&_AudioInfo->nAvgBytesPerSec, 4, 4, 1, _File) != 1)
	{
		fclose(_File);
		return false;
	}
	if (fread_s(&_AudioInfo->nBlockAlign, 2, 2, 1, _File) != 1)
	{
		fclose(_File);
		return false;
	}
	if (fread_s(&_AudioInfo->wBitsPerSample, 2, 2, 1, _File) != 1)
	{
		fclose(_File);
		return false;
	}

	fseek(_File, 40, SEEK_SET);

	if (fread_s(_BuffSize, 4, 4, 1, _File) != 1)
	{
		fclose(_File);
		return false;
	}

	*_Buff = new unsigned char[*_BuffSize];

	if (!(*_Buff))
	{
		fclose(_File);
		return false;
	}

	if (fread_s(*_Buff, *_BuffSize, 1, *_BuffSize, _File) != *_BuffSize)
	{
		fclose(_File);
		delete[] *_Buff;
		*_Buff = nullptr;
		return false;
	}

	fclose(_File);

	return true;
}

void BFW_API BFW::Sound::ReleaseLoadedBuff(const unsigned char* _Buff)
{
	if (!_Buff)
	{
		BFW_DEBUG_BREAK_MSG(L"No audio buffer to be deleted!");
		return;
	}
	delete[] _Buff;
}

bool BFW_API BFW::Sound::StartStreamFromFile(const wchar_t* _FilePath, FILE** _File, WAVEFORMATEX* _AudioInfo, unsigned __int32* _BuffSize)
{
	if (!_FilePath || !_File || !_AudioInfo || !_BuffSize)
	{
		BFW_DEBUG_BREAK_MSG(L"Can not start audio stream from file because of invalid parameters!");
		return false;
	}

	_wfopen_s(_File, _FilePath, L"rb");

	if (!(*_File))
	{
		return false;
	}

	fseek(*_File, 20, SEEK_SET);

	if (fread_s(&_AudioInfo->wFormatTag, 2, 2, 1, *_File) != 1)
	{
		fclose(*_File);
		*_File = nullptr;
		return false;
	}
	if (fread_s(&_AudioInfo->nChannels, 2, 2, 1, *_File) != 1)
	{
		fclose(*_File);
		*_File = nullptr;
		return false;
	}
	if (fread_s(&_AudioInfo->nSamplesPerSec, 4, 4, 1, *_File) != 1)
	{
		fclose(*_File);
		*_File = nullptr;
		return false;
	}
	if (fread_s(&_AudioInfo->nAvgBytesPerSec, 4, 4, 1, *_File) != 1)
	{
		fclose(*_File);
		*_File = nullptr;
		return false;
	}
	if (fread_s(&_AudioInfo->nBlockAlign, 2, 2, 1, *_File) != 1)
	{
		fclose(*_File);
		*_File = nullptr;
		return false;
	}
	if (fread_s(&_AudioInfo->wBitsPerSample, 2, 2, 1, *_File) != 1)
	{
		fclose(*_File);
		*_File = nullptr;
		return false;
	}

	fseek(*_File, 40, SEEK_SET);

	if (fread_s(_BuffSize, 4, 4, 1, *_File) != 1)
	{
		fclose(*_File);
		*_File = nullptr;
		return false;
	}

	return true;
}

bool BFW_API BFW::Sound::StreamFromFile(FILE** _File, unsigned char* _Buff, const unsigned __int32 _BuffSize, unsigned __int32* _ReadSize)
{
	if (!_File || !_Buff || !_BuffSize || !_ReadSize)
	{
		BFW_DEBUG_BREAK_MSG(L"Can not stream audio from file because of invalid parameters!");
		return false;
	}

	*_ReadSize = (unsigned __int32)(fread_s(_Buff, _BuffSize, 1, _BuffSize, *_File));

	return true;
}

bool BFW_API BFW::Sound::StopStreamFromFile(FILE** _File)
{
	if (!_File)
	{
		BFW_DEBUG_BREAK_MSG(L"Can not stop audio stream from file because of invalid parameters!");
		return false;
	}

	fclose(*_File);
	*_File = nullptr;

	return true;
}

bool BFW_API BFW::Sound::SaveToFile(const wchar_t* _FilePath, const unsigned char* _Buff, const unsigned __int32 _BuffSize, const WAVEFORMATEX _AudioInfo)
{
	if (!_FilePath || !_Buff || !_BuffSize)
	{
		BFW_DEBUG_BREAK_MSG(L"Can not save audio file because of invalid parameters!");
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
		unsigned __int32 _SubChunkSize_1 = 16;
		if (fwrite(&_SubChunkSize_1, 4, 1, _File) != 1)
		{
			fclose(_File);
			_wremove(_FilePath);
			return false;
		}
	}

	if (fwrite(&_AudioInfo.wFormatTag, 2, 1, _File) != 1)
	{
		fclose(_File);
		_wremove(_FilePath);
		return false;
	}
	if (fwrite(&_AudioInfo.nChannels, 2, 1, _File) != 1)
	{
		fclose(_File);
		_wremove(_FilePath);
		return false;
	}
	if (fwrite(&_AudioInfo.nSamplesPerSec, 4, 1, _File) != 1)
	{
		fclose(_File);
		_wremove(_FilePath);
		return false;
	}
	if (fwrite(&_AudioInfo.nAvgBytesPerSec, 4, 1, _File) != 1)
	{
		fclose(_File);
		_wremove(_FilePath);
		return false;
	}
	if (fwrite(&_AudioInfo.nBlockAlign, 2, 1, _File) != 1)
	{
		fclose(_File);
		_wremove(_FilePath);
		return false;
	}
	if (fwrite(&_AudioInfo.wBitsPerSample, 2, 1, _File) != 1)
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

	if (fwrite(&_BuffSize, 4, 1, _File) != 1)
	{
		fclose(_File);
		_wremove(_FilePath);
		return false;
	}

	if (fwrite(_Buff, 1, _BuffSize, _File) != _BuffSize)
	{
		fclose(_File);
		_wremove(_FilePath);
		return false;
	}

	{
		unsigned __int32 _FileSize = ftell(_File) - 8;

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

bool BFW_API BFW::Sound::StartStreamToFile(const wchar_t* _FilePath, FILE** _File, const WAVEFORMATEX _AudioInfo)
{
	if (!_FilePath || !_File)
	{
		BFW_DEBUG_BREAK_MSG(L"Can not start audio stream to file because of invalid parameters!");
		return false;
	}

	_wfopen_s(_File, _FilePath, L"wb");

	if (!(*_File))
	{
		return false;
	}

	if (fwrite("RIFF    WAVEfmt ", 1, 16, *_File) != 16)
	{
		fclose(*_File);
		*_File = nullptr;
		_wremove(_FilePath);
		return false;
	}

	{
		unsigned __int32 _SubChunkSize_1 = 16;
		if (fwrite(&_SubChunkSize_1, 4, 1, *_File) != 1)
		{
			fclose(*_File);
			*_File = nullptr;
			_wremove(_FilePath);
			return false;
		}
	}

	if (fwrite(&_AudioInfo.wFormatTag, 2, 1, *_File) != 1)
	{
		fclose(*_File);
		*_File = nullptr;
		_wremove(_FilePath);
		return false;
	}
	if (fwrite(&_AudioInfo.nChannels, 2, 1, *_File) != 1)
	{
		fclose(*_File);
		*_File = nullptr;
		_wremove(_FilePath);
		return false;
	}
	if (fwrite(&_AudioInfo.nSamplesPerSec, 4, 1, *_File) != 1)
	{
		fclose(*_File);
		*_File = nullptr;
		_wremove(_FilePath);
		return false;
	}
	if (fwrite(&_AudioInfo.nAvgBytesPerSec, 4, 1, *_File) != 1)
	{
		fclose(*_File);
		*_File = nullptr;
		_wremove(_FilePath);
		return false;
	}
	if (fwrite(&_AudioInfo.nBlockAlign, 2, 1, *_File) != 1)
	{
		fclose(*_File);
		*_File = nullptr;
		_wremove(_FilePath);
		return false;
	}
	if (fwrite(&_AudioInfo.wBitsPerSample, 2, 1, *_File) != 1)
	{
		fclose(*_File);
		*_File = nullptr;
		_wremove(_FilePath);
		return false;
	}

	if (fwrite("data    ", 1, 8, *_File) != 8)
	{
		fclose(*_File);
		*_File = nullptr;
		_wremove(_FilePath);
		return false;
	}

	return true;
}

bool BFW_API BFW::Sound::StreamToFile(const wchar_t* _FilePath, FILE** _File, const unsigned char* _Buff, const unsigned __int32 _BuffSize)
{
	if (!_FilePath || !_File || !_Buff || !_BuffSize)
	{
		BFW_DEBUG_BREAK_MSG(L"Can not stream audio to file because of invalid parameters!");
		return false;
	}

	if (fwrite(_Buff, 1, _BuffSize, *_File) != _BuffSize)
	{
		fclose(*_File);
		*_File = nullptr;
		_wremove(_FilePath);
		return false;
	}

	return true;
}

bool BFW_API BFW::Sound::StopStreamToFile(const wchar_t* _FilePath, FILE** _File)
{
	if (!_FilePath || !_File)
	{
		BFW_DEBUG_BREAK_MSG(L"Can not stop audio stream to file because of invalid parameters!");
		return false;
	}

	unsigned __int32 _FileSize = ftell(*_File);

	{
		unsigned __int32 _NewFileSize = _FileSize - 8;

		fseek(*_File, 4, SEEK_SET);

		if (fwrite(&_NewFileSize, 4, 1, *_File) != 1)
		{
			fclose(*_File);
			*_File = nullptr;
			_wremove(_FilePath);
			return false;
		}
	}

	fseek(*_File, 40, SEEK_SET);

	_FileSize -= 44;

	if (fwrite(&_FileSize, 4, 1, *_File) != 1)
	{
		fclose(*_File);
		*_File = nullptr;
		_wremove(_FilePath);
		return false;
	}

	fclose(*_File);
	*_File = nullptr;

	return true;
}



#endif
