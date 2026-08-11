#include "../Headers/BFW.hpp"



#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

#ifdef BFW_WINDOWS_PLATFORM

BFW::MultiProcessing::Process::Process() : Handle(NULL)
{

}

BFW::MultiProcessing::Process::Process(Process&& _Other) noexcept : Handle(_Other.Handle)
{
	_Other.Handle = NULL;
}

BFW::MultiProcessing::Process::~Process()
{
	Release();
}

#endif

#ifdef BFW_LINUX_PLATFORM

BFW::MultiProcessing::Process::Process() : Pid(0)
{

}

BFW::MultiProcessing::Process::Process(Process&& _Other) noexcept : Pid(_Other.Pid)
{
	_Other.Pid = 0;
}

BFW::MultiProcessing::Process::~Process()
{
	Destroy();
}

#endif

#ifdef BFW_WINDOWS_PLATFORM

const bool BFW::MultiProcessing::Process::Create(const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _WorkingDir, const BFW_CHAR_TYPE* _CmdLine, const int32_t _ShowCmd)
{
	Release();

	if (!_Path)
	{
		return false;
	}

	SHELLEXECUTEINFO _ShellExecuteInfo = { 0 };

	_ShellExecuteInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	_ShellExecuteInfo.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_FLAG_NO_UI;
	_ShellExecuteInfo.lpFile = _Path;
	_ShellExecuteInfo.lpDirectory = _WorkingDir;
	_ShellExecuteInfo.lpParameters = _CmdLine;
	_ShellExecuteInfo.nShow = _ShowCmd;

	if (!ShellExecuteEx(&_ShellExecuteInfo))
	{
		return false;
	}

	if (!_ShellExecuteInfo.hProcess)
	{
		return false;
	}

	Handle = _ShellExecuteInfo.hProcess;

	return true;
}

const bool BFW::MultiProcessing::Process::CreateElevated(const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _WorkingDir, const BFW_CHAR_TYPE* _CmdLine, const int32_t _ShowCmd)
{
	Release();

	if (!_Path)
	{
		return false;
	}

	SHELLEXECUTEINFO _ShellExecuteInfo = { 0 };

	_ShellExecuteInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	_ShellExecuteInfo.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_FLAG_NO_UI;
	_ShellExecuteInfo.lpVerb = BFW_STRING_PREFIX("runas");
	_ShellExecuteInfo.lpFile = _Path;
	_ShellExecuteInfo.lpDirectory = _WorkingDir;
	_ShellExecuteInfo.lpParameters = _CmdLine;
	_ShellExecuteInfo.nShow = _ShowCmd;

	if (!ShellExecuteEx(&_ShellExecuteInfo))
	{
		return false;
	}

	if (!_ShellExecuteInfo.hProcess)
	{
		return false;
	}

	Handle = _ShellExecuteInfo.hProcess;

	return true;
}

void BFW::MultiProcessing::Process::Destroy(const int32_t _ReturnValue)
{
	if (Handle)
	{
		TerminateProcess(Handle, _ReturnValue);
	}

	Release();
}

void BFW::MultiProcessing::Process::Release()
{
	if (Handle)
	{
		CloseHandle(Handle);
		Handle = NULL;
	}
}

const int32_t BFW::MultiProcessing::Process::UpdateState()
{
	if (!Handle)
	{
		return _UnknownErrorReturnValue;
	}

	int32_t _ReturnValue = _UnknownErrorReturnValue;

	if (!GetExitCodeProcess(Handle, (DWORD*)(&_ReturnValue)))
	{
		Release();
		return _UnknownErrorReturnValue;
	}

	if (_ReturnValue != _StillRunningReturnValue)
	{
		Release();
	}

	return _ReturnValue;
}

#endif

#ifdef BFW_LINUX_PLATFORM

const bool BFW::MultiProcessing::Process::Create(const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _WorkingDir, BFW_CHAR_TYPE** _CmdLine)
{
	Destroy();

	if (!_Path)
	{
		return false;
	}

	pid_t _Child = fork();

	if (_Child == -1)
	{
		return false;
	}

	if (_Child == 0)
	{
		if (_WorkingDir)
		{
			if (chdir(_WorkingDir) != 0)
			{
				exit(_UnknownErrorReturnValue);
			}
		}

		execvp(_Path, _CmdLine);

		exit(_UnknownErrorReturnValue);
	}

	Pid = _Child;

	return true;
}

void BFW::MultiProcessing::Process::Destroy()
{
	if (Pid != 0)
	{
		kill(Pid, SIGTERM);
		int32_t _WaitValue = _UnknownErrorReturnValue;
		waitpid(Pid, &_WaitValue, 0);
		Pid = 0;
	}
}

const bool BFW::MultiProcessing::Process::UpdateState(int32_t& _ReturnValue)
{
	if (Pid == 0)
	{
		_ReturnValue = _UnknownErrorReturnValue;
		return false;
	}

	int32_t _WaitValue = _UnknownErrorReturnValue;
	pid_t _Result = waitpid(Pid, &_WaitValue, WNOHANG);

	if (_Result == -1)
	{
		Pid = 0;
		_ReturnValue = _UnknownErrorReturnValue;
		return false;
	}

	if (_Result == 0)
	{
		_ReturnValue = _UnknownErrorReturnValue;
		return true;
	}

	if (!WIFEXITED(_WaitValue))
	{
		_ReturnValue = _UnknownErrorReturnValue;
		return true;
	}

	_ReturnValue = WEXITSTATUS(_WaitValue);

	Pid = 0;

	return true;
}

#endif

#ifdef BFW_WINDOWS_PLATFORM

const bool BFW::MultiProcessing::Process::CheckCreated() const
{
	return Handle != NULL;
}

#endif

#ifdef BFW_LINUX_PLATFORM

const bool BFW::MultiProcessing::Process::CheckCreated() const
{
	return Pid != 0;
}

#endif

#ifdef BFW_WINDOWS_PLATFORM

const HANDLE BFW::MultiProcessing::Process::GetHandle() const
{
	return Handle;
}

#endif

#ifdef BFW_LINUX_PLATFORM

const pid_t BFW::MultiProcessing::Process::GetPid() const
{
	return Pid;
}

#endif

#ifdef BFW_WINDOWS_PLATFORM

BFW::MultiProcessing::Process& BFW::MultiProcessing::Process::operator= (Process&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Release();

	Handle = _Other.Handle;

	_Other.Handle = NULL;

	return *this;
}

#endif

#ifdef BFW_LINUX_PLATFORM

BFW::MultiProcessing::Process& BFW::MultiProcessing::Process::operator= (Process&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Destroy();

	Pid = _Other.Pid;

	_Other.Pid = 0;

	return *this;
}

#endif

#ifdef BFW_WINDOWS_PLATFORM

const uint32_t BFW::MultiProcessing::Process::GetCurrentPid()
{
	return GetCurrentProcessId();
}

#endif

#ifdef BFW_LINUX_PLATFORM

const uint32_t BFW::MultiProcessing::Process::GetCurrentPid()
{
	return getpid();
}

#endif



#ifdef BFW_WINDOWS_PLATFORM

BFW::MultiProcessing::SharedMemory::SharedMemory() : Handle(NULL), Size(0), Data(nullptr)
{

}

BFW::MultiProcessing::SharedMemory::SharedMemory(SharedMemory&& _Other) noexcept : Handle(_Other.Handle), Size(_Other.Size), Data(_Other.Data)
{
	_Other.Handle = NULL;
	_Other.Size = 0;
	_Other.Data = nullptr;
}

#endif

#ifdef BFW_LINUX_PLATFORM

BFW::MultiProcessing::SharedMemory::SharedMemory() : File(-1), Size(0), Data(nullptr)
{

}

BFW::MultiProcessing::SharedMemory::SharedMemory(SharedMemory&& _Other) noexcept : File(_Other.File), Size(_Other.Size), Data(_Other.Data)
{
	_Other.File = -1;
	_Other.Size = 0;
	_Other.Data = nullptr;
}

#endif

BFW::MultiProcessing::SharedMemory::~SharedMemory()
{
	Destroy();
}

#ifdef BFW_WINDOWS_PLATFORM

const bool BFW::MultiProcessing::SharedMemory::Create(const BFW_CHAR_TYPE* _Name, const size_t _Size)
{
	Destroy();

	if (!_Name || !_Size)
	{
		return false;
	}

	BFW_X64_CALL(Handle = CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, _Size >> 32, _Size & 0b11111111111111111111111111111111, _Name));
	BFW_X86_CALL(Handle = CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, _Size, _Name));

	if (!Handle)
	{
		return false;
	}

	Data = (uint8_t*)(MapViewOfFile(Handle, FILE_MAP_ALL_ACCESS, 0, 0, 0));

	if (!Data)
	{
		Destroy();
		return false;
	}

	Size = _Size;

	return true;
}

void BFW::MultiProcessing::SharedMemory::Destroy()
{
	if (Data)
	{
		UnmapViewOfFile(Data);
		Data = nullptr;
	}

	if (Handle)
	{
		CloseHandle(Handle);
		Handle = NULL;
	}

	Size = 0;
}

const bool BFW::MultiProcessing::SharedMemory::CheckCreated() const
{
	return Handle != NULL;
}

#endif

#ifdef BFW_LINUX_PLATFORM

const bool BFW::MultiProcessing::SharedMemory::Create(const BFW_CHAR_TYPE* _Name, const size_t _Size)
{
	Destroy();

	if (!_Name || !_Size)
	{
		return false;
	}

	File = shm_open(_Name, O_CREAT | O_RDWR, 0666);

	if (File == -1)
	{
		return false;
	}

	if (ftruncate(File, _Size) != 0)
	{
		Destroy();
		return false;
	}

	Data = (uint8_t*)(mmap(nullptr, _Size, PROT_READ | PROT_WRITE, MAP_SHARED, File, 0));

	if (Data == MAP_FAILED)
	{
		Data = nullptr;
		Destroy();
		return false;
	}

	Size = _Size;

	return true;
}

void BFW::MultiProcessing::SharedMemory::Destroy()
{
	if (Data)
	{
		munmap(Data, Size);
		Data = nullptr;
	}

	if (File)
	{
		close(File);
		File = -1;
	}

	Size = 0;
}

const bool BFW::MultiProcessing::SharedMemory::CheckCreated() const
{
	return File != -1;
}

#endif

#ifdef BFW_WINDOWS_PLATFORM

const HANDLE BFW::MultiProcessing::SharedMemory::GetHandle() const
{
	return Handle;
}

#endif

#ifdef BFW_LINUX_PLATFORM

const int32_t BFW::MultiProcessing::SharedMemory::GetFile() const
{
	return File;
}

#endif

const size_t BFW::MultiProcessing::SharedMemory::GetSize() const
{
	return Size;
}

uint8_t* BFW::MultiProcessing::SharedMemory::GetData()
{
	return Data;
}

const uint8_t* BFW::MultiProcessing::SharedMemory::GetData() const
{
	return Data;
}

BFW::MultiProcessing::SharedMemory::operator uint8_t* ()
{
	return Data;
}

BFW::MultiProcessing::SharedMemory::operator const uint8_t* () const
{
	return Data;
}

uint8_t& BFW::MultiProcessing::SharedMemory::operator* ()
{
	return *Data;
}

const uint8_t& BFW::MultiProcessing::SharedMemory::operator* () const
{
	return *Data;
}

uint8_t& BFW::MultiProcessing::SharedMemory::operator[] (const size_t _Index)
{
	return Data[_Index];
}

const uint8_t& BFW::MultiProcessing::SharedMemory::operator[] (const size_t _Index) const
{
	return Data[_Index];
}

#ifdef BFW_WINDOWS_PLATFORM

BFW::MultiProcessing::SharedMemory& BFW::MultiProcessing::SharedMemory::operator= (SharedMemory&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Destroy();

	Handle = _Other.Handle;
	Size = _Other.Size;
	Data = _Other.Data;

	_Other.Handle = NULL;
	_Other.Size = 0;
	_Other.Data = nullptr;

	return *this;
}

#endif

#ifdef BFW_LINUX_PLATFORM

BFW::MultiProcessing::SharedMemory& BFW::MultiProcessing::SharedMemory::operator= (SharedMemory&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Destroy();

	File = _Other.File;
	Size = _Other.Size;
	Data = _Other.Data;

	_Other.File = -1;
	_Other.Size = 0;
	_Other.Data = nullptr;

	return *this;
}

#endif



#ifdef BFW_WINDOWS_PLATFORM

BFW::MultiProcessing::SharedMutex::SharedMutex() : Handle(NULL)
{

}

BFW::MultiProcessing::SharedMutex::SharedMutex(SharedMutex&& _Other) noexcept : Handle(_Other.Handle)
{
	_Other.Handle = NULL;
}

#endif

#ifdef BFW_LINUX_PLATFORM

BFW::MultiProcessing::SharedMutex::SharedMutex() : Semaphore(nullptr)
{

}

BFW::MultiProcessing::SharedMutex::SharedMutex(SharedMutex&& _Other) noexcept : Semaphore(_Other.Semaphore)
{
	_Other.Semaphore = nullptr;
}

#endif

BFW::MultiProcessing::SharedMutex::~SharedMutex()
{
	Destroy();
}

#ifdef BFW_WINDOWS_PLATFORM

const bool BFW::MultiProcessing::SharedMutex::Create(const BFW_CHAR_TYPE* _Name)
{
	Destroy();

	if (!_Name)
	{
		return false;
	}

	Handle = CreateMutex(nullptr, false, _Name);

	if (!Handle)
	{
		return false;
	}

	return true;
}

void BFW::MultiProcessing::SharedMutex::Destroy()
{
	if (Handle)
	{
		CloseHandle(Handle);
		Handle = NULL;
	}
}

void BFW::MultiProcessing::SharedMutex::Lock()
{
	if (!Handle)
	{
		return;
	}

	WaitForSingleObject(Handle, INFINITE);
}

void BFW::MultiProcessing::SharedMutex::Unlock()
{
	if (!Handle)
	{
		return;
	}

	ReleaseMutex(Handle);
}

const bool BFW::MultiProcessing::SharedMutex::CheckCreated() const
{
	return Handle != NULL;
}

#endif

#ifdef BFW_LINUX_PLATFORM

const bool BFW::MultiProcessing::SharedMutex::Create(const BFW_CHAR_TYPE* _Name)
{
	Destroy();

	if (!_Name)
	{
		return false;
	}

	Semaphore = sem_open(_Name, O_CREAT, 0666, 1);

	if (Semaphore == SEM_FAILED)
	{
		Semaphore = nullptr;
		return false;
	}

	return true;
}

void BFW::MultiProcessing::SharedMutex::Destroy()
{
	if (Semaphore != nullptr)
	{
		sem_close(Semaphore);
		Semaphore = nullptr;
	}
}

void BFW::MultiProcessing::SharedMutex::Lock()
{
	if (Semaphore == nullptr)
	{
		return;
	}

	sem_wait(Semaphore);
}

void BFW::MultiProcessing::SharedMutex::Unlock()
{
	if (Semaphore == nullptr)
	{
		return;
	}

	sem_post(Semaphore);
}

const bool BFW::MultiProcessing::SharedMutex::CheckCreated() const
{
	return Semaphore != nullptr;
}

#endif

#ifdef BFW_WINDOWS_PLATFORM

const HANDLE BFW::MultiProcessing::SharedMutex::GetHandle() const
{
	return Handle;
}

#endif

#ifdef BFW_LINUX_PLATFORM

const sem_t* BFW::MultiProcessing::SharedMutex::GetSemaphore() const
{
	return Semaphore;
}

#endif

#ifdef BFW_WINDOWS_PLATFORM

BFW::MultiProcessing::SharedMutex& BFW::MultiProcessing::SharedMutex::operator= (SharedMutex&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Destroy();

	Handle = _Other.Handle;

	_Other.Handle = NULL;

	return *this;
}

#endif

#ifdef BFW_LINUX_PLATFORM

BFW::MultiProcessing::SharedMutex& BFW::MultiProcessing::SharedMutex::operator= (SharedMutex&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Destroy();

	Semaphore = _Other.Semaphore;

	_Other.Semaphore = nullptr;

	return *this;
}

#endif

#endif
