#include "..\Headers\BFW.hpp"



#ifdef BFW_WINDOWS_PLATFORM



BFW::Application::Application() :
	On(false), ReturnValue(Enums::_ReturnError),
	CurrentMenu(Enums::_NullMenu), CurrentMenuObj(nullptr),
	SharedInstance(),
	FrameTime(), TimeStep(1.0f / 60.0f), Sync(60),
	hInstance(NULL), CmdLine(nullptr), ShowCmd(SW_HIDE)
{

}

BFW::Application::~Application()
{

}

const bool BFW::Application::CheckOn() const
{
	return On;
}

const long BFW::Application::GetReturnValue() const
{
	return ReturnValue;
}

const unsigned long BFW::Application::GetCurrentMenu() const
{
	return CurrentMenu;
}

BFW::Menu* BFW::Application::GetCurrentMenuObj()
{
	return CurrentMenuObj;
}

const BFW::Menu* BFW::Application::GetCurrentMenuObj() const
{
	return CurrentMenuObj;
}

BFW::Multiprocessing::SharedMemory& BFW::Application::GetSharedInstance()
{
	return SharedInstance;
}

const BFW::Multiprocessing::SharedMemory& BFW::Application::GetSharedInstance() const
{
	return SharedInstance;
}

BFW::Time::Timer& BFW::Application::GetFrameTime(const unsigned long _Index)
{
	return FrameTime[_Index];
}

const BFW::Time::Timer& BFW::Application::GetFrameTime(const unsigned long _Index) const
{
	return FrameTime[_Index];
}

BFW::Time::Timer* BFW::Application::GetFrameTimePtr()
{
	return FrameTime;
}

const BFW::Time::Timer* BFW::Application::GetFrameTimePtr() const
{
	return FrameTime;
}

const float BFW::Application::GetTimeStep() const
{
	return TimeStep;
}

float* BFW::Application::GetTimeStepPtr()
{
	return &TimeStep;
}

const float* BFW::Application::GetTimeStepPtr() const
{
	return &TimeStep;
}

const float BFW::Application::GetTimeStepRatio() const
{
	return FrameTime[Enums::_Previous] / TimeStep;
}

const unsigned long BFW::Application::GetSync() const
{
	return Sync;
}

unsigned long* BFW::Application::GetSyncPtr()
{
	return &Sync;
}

const unsigned long* BFW::Application::GetSyncPtr() const
{
	return &Sync;
}

const HINSTANCE BFW::Application::GetHInstance() const
{
	return hInstance;
}

const LPWSTR BFW::Application::GetCmdLine() const
{
	return CmdLine;
}

const long BFW::Application::GetShowCmd() const
{
	return ShowCmd;
}

const unsigned long BFW::Application::GetArgC() const
{
	return __argc;
}

const wchar_t* BFW::Application::GetWArgV(const unsigned long _Index) const
{
	return __wargv[_Index];
}

void BFW::Application::TurnOn()
{
	On = true;
}

void BFW::Application::Close(const long _ReturnValue)
{
	On = false;
	ReturnValue = _ReturnValue;
}

void BFW::Application::SetCurrentMenu(const unsigned long _CurrentMenu)
{
	CurrentMenu = _CurrentMenu;
}

void BFW::Application::SetCurrentMenuObj(Menu* _CurrentMenuObj)
{
	CurrentMenuObj = _CurrentMenuObj;
}

void BFW::Application::UpdateCurrentFrameTime()
{
	FrameTime[Enums::_Current].Stop();
}

void BFW::Application::SetTimeStep(const float _TimeStep)
{
	TimeStep = _TimeStep;
}

void BFW::Application::SetSync(const unsigned long _Sync)
{
	Sync = _Sync;
}

long BFW::Application::Run(const HINSTANCE _hInstance, const LPWSTR _CmdLine, const long _ShowCmd, const wchar_t* _SharedMemoryName)
{
	if (!_SharedMemoryName)
	{
		BFW_DEBUG_BREAK_MSG(L"A shared memory name is required!");
		BFW_RELEASE_CALL(MessageBox(NULL, L"An unexpected error occurred!", L"Error", MB_OK | MB_ICONERROR));
		return Enums::_ReturnError;
	}

	if (!Time::Initialized)
	{
		MessageBox(NULL, L"An unexpected error occurred!", L"Error", MB_OK | MB_ICONERROR);
		return Enums::_ReturnError;
	}

	hInstance = _hInstance;
	CmdLine = _CmdLine;
	ShowCmd = _ShowCmd;

	if (!SharedInstance.Create(_SharedMemoryName, 1))
	{
		MessageBox(NULL, L"An unexpected error occurred!", L"Error", MB_OK | MB_ICONERROR);
		return Enums::_ReturnError;
	}

	*SharedInstance = *SharedInstance + 1;

	Setup();
	while (On)
	{
		Update();
	}
	Stop();

	*SharedInstance = *SharedInstance - 1;

	SharedInstance.Destroy();

	if (ReturnValue == Enums::_ReturnError)
	{
		MessageBox(NULL, L"An unexpected error occurred!", L"Error", MB_OK | MB_ICONERROR);
	}

	return ReturnValue;
}



#endif



#ifdef BFW_ARDUINO_PLATFORM



BFW::Application::Application() :
	On(false), ReturnValue(Enums::_ReturnError),
	CurrentMenu(Enums::_NullMenu), CurrentMenuObj(nullptr),
	FrameTime(), TimeStep(1.0f / 60.0f), Sync(60)
{

}

BFW::Application::~Application()
{

}

const bool BFW::Application::CheckOn() const
{
	return On;
}

const long BFW::Application::GetReturnValue() const
{
	return ReturnValue;
}

const unsigned long BFW::Application::GetCurrentMenu() const
{
	return CurrentMenu;
}

BFW::Menu* BFW::Application::GetCurrentMenuObj()
{
	return CurrentMenuObj;
}

const BFW::Menu* BFW::Application::GetCurrentMenuObj() const
{
	return CurrentMenuObj;
}

BFW::Time::Timer& BFW::Application::GetFrameTime(const unsigned long _Index)
{
	return FrameTime[_Index];
}

const BFW::Time::Timer& BFW::Application::GetFrameTime(const unsigned long _Index) const
{
	return FrameTime[_Index];
}

BFW::Time::Timer* BFW::Application::GetFrameTimePtr()
{
	return FrameTime;
}

const BFW::Time::Timer* BFW::Application::GetFrameTimePtr() const
{
	return FrameTime;
}

const float BFW::Application::GetTimeStep() const
{
	return TimeStep;
}

float* BFW::Application::GetTimeStepPtr()
{
	return &TimeStep;
}

const float* BFW::Application::GetTimeStepPtr() const
{
	return &TimeStep;
}

const float BFW::Application::GetTimeStepRatio() const
{
	return FrameTime[Enums::_Previous] / TimeStep;
}

const unsigned long BFW::Application::GetSync() const
{
	return Sync;
}

unsigned long* BFW::Application::GetSyncPtr()
{
	return &Sync;
}

const unsigned long* BFW::Application::GetSyncPtr() const
{
	return &Sync;
}

void BFW::Application::TurnOn()
{
	On = true;
}

void BFW::Application::Close(const long _ReturnValue)
{
	On = false;
	ReturnValue = _ReturnValue;
}

void BFW::Application::SetCurrentMenu(const unsigned long _CurrentMenu)
{
	CurrentMenu = _CurrentMenu;
}

void BFW::Application::SetCurrentMenuObj(Menu* _CurrentMenuObj)
{
	CurrentMenuObj = _CurrentMenuObj;
}

void BFW::Application::UpdateCurrentFrameTime()
{
	FrameTime[Enums::_Current].Stop();
}

void BFW::Application::SetTimeStep(const float _TimeStep)
{
	TimeStep = _TimeStep;
}

void BFW::Application::SetSync(const unsigned long _Sync)
{
	Sync = _Sync;
}

long BFW::Application::Run()
{
	Setup();
	while (On)
	{
		Update();
	}
	Stop();

	return ReturnValue;
}



#endif
