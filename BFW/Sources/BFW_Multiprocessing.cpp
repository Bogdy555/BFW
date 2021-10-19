#include "..\Headers\BFW.hpp"



#ifdef BFW_WINDOWS_PLATFORM



BFW::Multiprocessing::SharedMemory::SharedMemory() : Created(false), hFile(NULL), Name(nullptr), Size(0), Buff(nullptr)
{

}

BFW::Multiprocessing::SharedMemory::SharedMemory(const SharedMemory& _Other) : Created(false), hFile(NULL), Name(nullptr), Size(0), Buff(nullptr)
{
	if (!_Other.Name || !_Other.Size)
	{
		return;
	}

	Name = _Other.Name;
	Size = _Other.Size;

	hFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, Size, Name);

	if (!hFile)
	{
		Created = false;
		Size = 0;
		return;
	}

	Buff = (unsigned char*)(MapViewOfFile(hFile, FILE_MAP_ALL_ACCESS, 0, 0, Size));

	if (!Buff)
	{
		CloseHandle(hFile);
		hFile = NULL;
		Created = false;
		Size = 0;
		return;
	}

	Created = true;
}

BFW::Multiprocessing::SharedMemory::SharedMemory(SharedMemory&& _Other) noexcept :
	Created(_Other.Created), hFile(_Other.hFile), Name(_Other.Name), Size(_Other.Size), Buff(_Other.Buff)
{
	_Other.Created = false;
	_Other.hFile = NULL;
	_Other.Name = nullptr;
	_Other.Size = 0;
	_Other.Buff = nullptr;
}

BFW::Multiprocessing::SharedMemory::~SharedMemory()
{
	if (Created)
	{
		Destroy();
	}
}

bool BFW::Multiprocessing::SharedMemory::Create(const wchar_t* _Name, const unsigned long _Size)
{
	if (Buff)
	{
		UnmapViewOfFile(Buff);
		Buff = nullptr;
	}
	if (hFile)
	{
		CloseHandle(hFile);
		hFile = NULL;
	}
	Created = false;
	Name = nullptr;
	Size = 0;

	if (!_Name || !_Size)
	{
		BFW_DEBUG_BREAK_MSG(L"Shared memory creation attempt with invalid parameters!");
		return false;
	}

	Name = _Name;
	Size = _Size;

	hFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, Size, Name);

	if (!hFile)
	{
		Created = false;
		Size = 0;
		return false;
	}

	Buff = (unsigned char*)(MapViewOfFile(hFile, FILE_MAP_ALL_ACCESS, 0, 0, Size));

	if (!Buff)
	{
		CloseHandle(hFile);
		hFile = NULL;
		Created = false;
		Size = 0;
		return false;
	}

	Created = true;

	return true;
}

void BFW::Multiprocessing::SharedMemory::Destroy()
{
	if (Buff)
	{
		UnmapViewOfFile(Buff);
		Buff = nullptr;
	}
	if (hFile)
	{
		CloseHandle(hFile);
		hFile = NULL;
	}
	Created = false;
	Name = nullptr;
	Size = 0;
}

const bool BFW::Multiprocessing::SharedMemory::CheckCreated() const
{
	return Created;
}

const wchar_t* BFW::Multiprocessing::SharedMemory::GetName() const
{
	return Name;
}

const unsigned long BFW::Multiprocessing::SharedMemory::GetSize() const
{
	return Size;
}

unsigned char* BFW::Multiprocessing::SharedMemory::Data()
{
	return Buff;
}

const unsigned char* BFW::Multiprocessing::SharedMemory::Data() const
{
	return Buff;
}

BFW::Multiprocessing::SharedMemory::operator unsigned char* ()
{
	return Buff;
}

BFW::Multiprocessing::SharedMemory::operator const unsigned char* ()
{
	return Buff;
}

unsigned char& BFW::Multiprocessing::SharedMemory::operator* ()
{
	return *Buff;
}

const unsigned char& BFW::Multiprocessing::SharedMemory::operator* () const
{
	return *Buff;
}

unsigned char& BFW::Multiprocessing::SharedMemory::operator[] (const unsigned long _Index)
{
	return Buff[_Index];
}

const unsigned char& BFW::Multiprocessing::SharedMemory::operator[] (const unsigned long _Index) const
{
	return Buff[_Index];
}

void BFW::Multiprocessing::SharedMemory::operator= (const SharedMemory& _Other)
{
	if (Buff)
	{
		UnmapViewOfFile(Buff);
		Buff = nullptr;
	}
	if (hFile)
	{
		CloseHandle(hFile);
		hFile = NULL;
	}
	Created = false;
	Name = nullptr;
	Size = 0;

	if (!_Other.Name || !_Other.Size)
	{
		return;
	}

	Name = _Other.Name;
	Size = _Other.Size;

	hFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, Size, Name);

	if (!hFile)
	{
		Created = false;
		Size = 0;
		return;
	}

	Buff = (unsigned char*)(MapViewOfFile(hFile, FILE_MAP_ALL_ACCESS, 0, 0, Size));

	if (!Buff)
	{
		CloseHandle(hFile);
		hFile = NULL;
		Created = false;
		Size = 0;
		return;
	}

	Created = true;
}

void BFW::Multiprocessing::SharedMemory::operator= (SharedMemory&& _Other) noexcept
{
	hFile = _Other.hFile;
	Created = _Other.Created;
	Name = _Other.Name;
	Buff = _Other.Buff;
	Size = _Other.Size;

	_Other.hFile = NULL;
	_Other.Created = false;
	_Other.Name = nullptr;
	_Other.Buff = nullptr;
	_Other.Size = 0;
}



BFW::Multiprocessing::Process::Process() : ProcessInfo({ 0 }), Path(nullptr), Created(false), ReturnValue(Enums::_ReturnStillRunning)
{

}

BFW::Multiprocessing::Process::Process(const Process& _Other) :
	ProcessInfo(_Other.ProcessInfo), Path(_Other.Path), Created(_Other.Created), ReturnValue(_Other.ReturnValue)
{

}

BFW::Multiprocessing::Process::Process(Process&& _Other) noexcept :
	ProcessInfo(_Other.ProcessInfo), Path(_Other.Path), Created(_Other.Created), ReturnValue(_Other.ReturnValue)
{
	_Other.ProcessInfo = { 0 };
	_Other.Path = nullptr;
	_Other.Created = false;
	_Other.ReturnValue = Enums::_ReturnStillRunning;
}

BFW::Multiprocessing::Process::~Process()
{

}

bool BFW::Multiprocessing::Process::Create(const wchar_t* _Path, STARTUPINFO* _StartInfo, const wchar_t* _WorkingDir, wchar_t* _CmdLine, unsigned long _Flags)
{
	ProcessInfo = { 0 };
	Created = false;
	ReturnValue = Enums::_ReturnStillRunning;
	Path = _Path;

	if (!_Path)
	{
		BFW_DEBUG_BREAK_MSG(L"Process creation attempt with invalid parameters!");
		return false;
	}

	if (_StartInfo)
	{
		Created = CreateProcess(Path, _CmdLine, NULL, NULL, FALSE, _Flags, NULL, _WorkingDir, _StartInfo, &ProcessInfo);
	}
	else
	{
		STARTUPINFO _DefaultStartInfo = { 0 };
		_DefaultStartInfo.dwFlags = STARTF_FORCEOFFFEEDBACK;
		Created = CreateProcess(Path, _CmdLine, NULL, NULL, FALSE, _Flags, NULL, _WorkingDir, &_DefaultStartInfo, &ProcessInfo);
	}

	ReturnValue = Enums::_ReturnStillRunning;

	if (!Created)
	{
		ProcessInfo = { 0 };
		return false;
	}

	return true;
}

bool BFW::Multiprocessing::Process::CreateElevated(const wchar_t* _Path, const int _ShowCmd, const wchar_t* _WorkingDir, wchar_t* _CmdLine)
{
	ProcessInfo = { 0 };
	Created = false;
	ReturnValue = Enums::_ReturnStillRunning;
	Path = _Path;

	if (!_Path)
	{
		BFW_DEBUG_BREAK_MSG(L"Elevated process creation attempt with invalid parameters!");
		return false;
	}

	SHELLEXECUTEINFO _ShellExInfo = { 0 };

	_ShellExInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	_ShellExInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	_ShellExInfo.lpVerb = L"runas";
	_ShellExInfo.lpFile = _Path;
	_ShellExInfo.lpParameters = _CmdLine;
	_ShellExInfo.lpDirectory = _WorkingDir;
	_ShellExInfo.nShow = _ShowCmd;

	Created = ShellExecuteEx(&_ShellExInfo);

	ReturnValue = Enums::_ReturnStillRunning;

	if (Created)
	{
		if (_ShellExInfo.hProcess != NULL && _ShellExInfo.hProcess != INVALID_HANDLE_VALUE)
		{
			ProcessInfo.hProcess = _ShellExInfo.hProcess;
			ProcessInfo.dwProcessId = GetProcessId(_ShellExInfo.hProcess);
		}
	}
	else
	{
		ProcessInfo = { 0 };
		return false;
	}

	return true;
}

void BFW::Multiprocessing::Process::Destroy(const unsigned long _ReturnValue)
{
	if (ProcessInfo.hProcess)
	{
		if (TerminateProcess(ProcessInfo.hProcess, _ReturnValue))
		{
			ReturnValue = _ReturnValue;
		}
		else
		{
			ReturnValue = Enums::_ReturnStillRunning;
		}
	}
	else
	{
		ReturnValue = Enums::_ReturnStillRunning;
	}

	ProcessInfo = { 0 };
	Path = nullptr;
	Created = false;
}

bool BFW::Multiprocessing::Process::UpdateStatus()
{
	if (!ProcessInfo.hProcess)
	{
		return false;
	}

	if (!GetExitCodeProcess(ProcessInfo.hProcess, &ReturnValue))
	{
		ProcessInfo = { 0 };
		ReturnValue = Enums::_ReturnStillRunning;
		Created = false;
		return false;
	}

	if (ReturnValue != Enums::_ReturnStillRunning)
	{
		ProcessInfo = { 0 };
		Created = false;
	}

	return true;
}

const PROCESS_INFORMATION& BFW::Multiprocessing::Process::GetProcessInfo() const
{
	return ProcessInfo;
}

const wchar_t* BFW::Multiprocessing::Process::GetPath() const
{
	return Path;
}

const bool BFW::Multiprocessing::Process::CheckCreated() const
{
	return Created;
}

const unsigned long BFW::Multiprocessing::Process::GetReturnValue() const
{
	return ReturnValue;
}

void BFW::Multiprocessing::Process::operator= (const Process& _Other)
{
	ProcessInfo = _Other.ProcessInfo;
	Path = _Other.Path;
	Created = _Other.Created;
	ReturnValue = _Other.ReturnValue;
}

void BFW::Multiprocessing::Process::operator= (Process&& _Other) noexcept
{
	ProcessInfo = _Other.ProcessInfo;
	Path = _Other.Path;
	Created = _Other.Created;
	ReturnValue = _Other.ReturnValue;

	_Other.ProcessInfo = { 0 };
	_Other.Path = nullptr;
	_Other.Created = false;
	_Other.ReturnValue = Enums::_ReturnStillRunning;
}



#endif
