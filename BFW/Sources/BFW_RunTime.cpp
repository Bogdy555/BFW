#include "../Headers/BFW.hpp"



#ifdef BFW_WINDOWS_PLATFORM

BFW::RunTime::Application::Application() : On(false), ReturnValue(MultiProcessing::_UnknownErrorReturnValue), CurrentMenu(_NullMenu), FrameTime(), LagTime(0.0f), SimulationSpeed(1.0f), Sync(60), SharedInstanceMemory(), SharedInstanceMutex(), InstanceHandle(NULL), CmdLine(nullptr), ShowCmd(SW_HIDE)
{

}

BFW::RunTime::Application::Application(Application&& _Other) noexcept : On(_Other.On), ReturnValue(_Other.ReturnValue), CurrentMenu(_Other.CurrentMenu), FrameTime(), LagTime(_Other.LagTime), SimulationSpeed(_Other.SimulationSpeed), Sync(_Other.Sync), SharedInstanceMemory((MultiProcessing::SharedMemory&&)(_Other.SharedInstanceMemory)), SharedInstanceMutex((MultiProcessing::SharedMutex&&)(_Other.SharedInstanceMutex)), InstanceHandle(_Other.InstanceHandle), CmdLine(_Other.CmdLine), ShowCmd(_Other.ShowCmd)
{
	FrameTime[_PreviousState] = (Time::Timer&&)(_Other.FrameTime[_PreviousState]);
	FrameTime[_CurrentState] = (Time::Timer&&)(_Other.FrameTime[_CurrentState]);

	_Other.On = false;
	_Other.ReturnValue = MultiProcessing::_UnknownErrorReturnValue;
	_Other.CurrentMenu = _NullMenu;
	_Other.LagTime = 0.0f;
	_Other.SimulationSpeed = 1.0f;
	_Other.Sync = 60;
	_Other.InstanceHandle = NULL;
	_Other.CmdLine = nullptr;
	_Other.ShowCmd = SW_HIDE;
}

#endif

#ifdef BFW_LINUX_PLATFORM

BFW::RunTime::Application::Application() : On(false), ReturnValue(MultiProcessing::_UnknownErrorReturnValue), CurrentMenu(_NullMenu), FrameTime(), LagTime(0.0f), SimulationSpeed(1.0f), Sync(60), SharedInstanceMemory(), SharedInstanceMutex(), ArgC(0), ArgV(nullptr)
{

}

BFW::RunTime::Application::Application(Application&& _Other) noexcept : On(_Other.On), ReturnValue(_Other.ReturnValue), CurrentMenu(_Other.CurrentMenu), FrameTime(), LagTime(_Other.LagTime), SimulationSpeed(_Other.SimulationSpeed), Sync(_Other.Sync), SharedInstanceMemory((MultiProcessing::SharedMemory&&)(_Other.SharedInstanceMemory)), SharedInstanceMutex((MultiProcessing::SharedMutex&&)(_Other.SharedInstanceMutex)), ArgC(_Other.ArgC), ArgV(_Other.ArgV)
{
	FrameTime[_PreviousState] = (Time::Timer&&)(_Other.FrameTime[_PreviousState]);
	FrameTime[_CurrentState] = (Time::Timer&&)(_Other.FrameTime[_CurrentState]);

	_Other.On = false;
	_Other.ReturnValue = MultiProcessing::_UnknownErrorReturnValue;
	_Other.CurrentMenu = _NullMenu;
	_Other.LagTime = 0.0f;
	_Other.SimulationSpeed = 1.0f;
	_Other.Sync = 60;
	_Other.ArgC = 0;
	_Other.ArgV = nullptr;
}

#endif

#ifdef BFW_ESP32_PLATFORM

BFW::RunTime::Application::Application() : On(false), ReturnValue(MultiProcessing::_UnknownErrorReturnValue), CurrentMenu(_NullMenu), FrameTime(), LagTime(0.0f), SimulationSpeed(1.0f), Sync(60)
{

}

BFW::RunTime::Application::Application(Application&& _Other) noexcept : On(_Other.On), ReturnValue(_Other.ReturnValue), CurrentMenu(_Other.CurrentMenu), FrameTime(), LagTime(_Other.LagTime), SimulationSpeed(_Other.SimulationSpeed), Sync(_Other.Sync)
{
	FrameTime[_PreviousState] = (Time::Timer&&)(_Other.FrameTime[_PreviousState]);
	FrameTime[_CurrentState] = (Time::Timer&&)(_Other.FrameTime[_CurrentState]);

	_Other.On = false;
	_Other.ReturnValue = MultiProcessing::_UnknownErrorReturnValue;
	_Other.CurrentMenu = _NullMenu;
	_Other.LagTime = 0.0f;
	_Other.SimulationSpeed = 1.0f;
	_Other.Sync = 60;
}

#endif

BFW::RunTime::Application::~Application()
{

}

#ifdef BFW_WINDOWS_PLATFORM

const int32_t BFW::RunTime::Application::Run(const HINSTANCE _InstanceHandle, const BFW_CHAR_TYPE* _CmdLine, const int32_t _ShowCmd, const BFW_CHAR_TYPE* _SharedInstanceMemoryName, const BFW_CHAR_TYPE* _SharedInstanceMutexName)
{
	if (_InstanceHandle == NULL || _CmdLine == nullptr || _SharedInstanceMemoryName == nullptr || _SharedInstanceMutexName == nullptr)
	{
		return MultiProcessing::_UnknownErrorReturnValue;
	}

	if (!SharedInstanceMemory.Create(_SharedInstanceMemoryName, 8))
	{
		return MultiProcessing::_UnknownErrorReturnValue;
	}

	if (!SharedInstanceMutex.Create(_SharedInstanceMutexName))
	{
		SharedInstanceMemory.Destroy();
		return MultiProcessing::_UnknownErrorReturnValue;
	}

	SharedInstanceMutex.Lock();
	(*(uint64_t*)(SharedInstanceMemory.GetData()))++;
	SharedInstanceMutex.Unlock();

	InstanceHandle = _InstanceHandle;
	CmdLine = _CmdLine;
	ShowCmd = _ShowCmd;

	Setup();
	while (On)
	{
		Update();
	}
	Stop();

	CurrentMenu = _NullMenu;

	FrameTime[_PreviousState].Reset();
	FrameTime[_CurrentState].Reset();
	LagTime = 0.0f;
	SimulationSpeed = 1.0f;
	Sync = 60;

	InstanceHandle = NULL;
	CmdLine = nullptr;
	ShowCmd = SW_HIDE;

	SharedInstanceMutex.Lock();
	(*(uint64_t*)(SharedInstanceMemory.GetData()))--;
	SharedInstanceMutex.Unlock();

	SharedInstanceMemory.Destroy();
	SharedInstanceMutex.Destroy();

	int32_t _ReturnValue = ReturnValue;
	ReturnValue = MultiProcessing::_UnknownErrorReturnValue;

	return _ReturnValue;
}

#endif

#ifdef BFW_LINUX_PLATFORM

const int32_t BFW::RunTime::Application::Run(const size_t _ArgC, const BFW_CHAR_TYPE** _ArgV, const BFW_CHAR_TYPE* _SharedInstanceMemoryName, const BFW_CHAR_TYPE* _SharedInstanceMutexName)
{
	if (_ArgC == 0 || _ArgV == nullptr || _SharedInstanceMemoryName == nullptr || _SharedInstanceMutexName == nullptr)
	{
		return MultiProcessing::_UnknownErrorReturnValue;
	}

	if (!SharedInstanceMemory.Create(_SharedInstanceMemoryName, 8))
	{
		return MultiProcessing::_UnknownErrorReturnValue;
	}

	if (!SharedInstanceMutex.Create(_SharedInstanceMutexName))
	{
		SharedInstanceMemory.Destroy();
		return MultiProcessing::_UnknownErrorReturnValue;
	}

	SharedInstanceMutex.Lock();
	(*(uint64_t*)(SharedInstanceMemory.GetData()))++;
	SharedInstanceMutex.Unlock();

	ArgC = _ArgC;
	ArgV = _ArgV;

	Setup();
	while (On)
	{
		Update();
	}
	Stop();

	CurrentMenu = _NullMenu;

	FrameTime[_PreviousState].Reset();
	FrameTime[_CurrentState].Reset();
	LagTime = 0.0f;
	SimulationSpeed = 1.0f;
	Sync = 60;

	ArgC = 0;
	ArgV = nullptr;

	SharedInstanceMutex.Lock();
	(*(uint64_t*)(SharedInstanceMemory.GetData()))--;
	SharedInstanceMutex.Unlock();

	SharedInstanceMemory.Destroy();
	SharedInstanceMutex.Destroy();

	int32_t _ReturnValue = ReturnValue;
	ReturnValue = MultiProcessing::_UnknownErrorReturnValue;

	return _ReturnValue;
}

#endif

#ifdef BFW_ESP32_PLATFORM

const int32_t BFW::RunTime::Application::Run()
{
	Setup();
	while (On)
	{
		Update();
	}
	Stop();

	CurrentMenu = _NullMenu;

	FrameTime[_PreviousState].Reset();
	FrameTime[_CurrentState].Reset();
	LagTime = 0.0f;
	SimulationSpeed = 1.0f;
	Sync = 60;

	int32_t _ReturnValue = ReturnValue;
	ReturnValue = MultiProcessing::_UnknownErrorReturnValue;

	return _ReturnValue;
}

#endif

void BFW::RunTime::Application::TurnOn()
{
	On = true;
}

void BFW::RunTime::Application::Close(const int32_t _ReturnValue)
{
	On = false;
	ReturnValue = _ReturnValue;
}

void BFW::RunTime::Application::SetCurrentMenu(const uint64_t _CurrentMenu)
{
	CurrentMenu = _CurrentMenu;
}

void BFW::RunTime::Application::UpdateCurrentFrameTime()
{
	FrameTime[_CurrentState].Stop();
}

void BFW::RunTime::Application::SetLagTime(const float _LagTime)
{
	LagTime = _LagTime;
}

void BFW::RunTime::Application::SetSimulationSpeed(const float _SimulationSpeed)
{
	SimulationSpeed = _SimulationSpeed;
}

void BFW::RunTime::Application::SetSync(const uint64_t _Sync)
{
	Sync = _Sync;
}

const bool BFW::RunTime::Application::CheckOn() const
{
	return On;
}

const int32_t BFW::RunTime::Application::GetReturnValue() const
{
	return ReturnValue;
}

const uint64_t BFW::RunTime::Application::GetCurrentMenu() const
{
	return CurrentMenu;
}

BFW::Time::Timer& BFW::RunTime::Application::GetFrameTime(const size_t _Index)
{
	return FrameTime[_Index];
}

const BFW::Time::Timer& BFW::RunTime::Application::GetFrameTime(const size_t _Index) const
{
	return FrameTime[_Index];
}

const float BFW::RunTime::Application::GetTimeStep() const
{
	if (LagTime != 0.0f && FrameTime[_PreviousState] > LagTime)
	{
		return LagTime * SimulationSpeed;
	}

	return FrameTime[_PreviousState] * SimulationSpeed;
}

const float BFW::RunTime::Application::GetUITimeStep() const
{
	if (LagTime != 0.0f && FrameTime[_PreviousState] > LagTime)
	{
		return LagTime;
	}

	return FrameTime[_PreviousState];
}

const float BFW::RunTime::Application::GetLagTime() const
{
	return LagTime;
}

const float BFW::RunTime::Application::GetSimulationSpeed() const
{
	return SimulationSpeed;
}

const uint64_t BFW::RunTime::Application::GetSync() const
{
	return Sync;
}

#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

BFW::MultiProcessing::SharedMemory& BFW::RunTime::Application::GetSharedInstanceMemory()
{
	return SharedInstanceMemory;
}

const BFW::MultiProcessing::SharedMemory& BFW::RunTime::Application::GetSharedInstanceMemory() const
{
	return SharedInstanceMemory;
}

BFW::MultiProcessing::SharedMutex& BFW::RunTime::Application::GetSharedInstanceMutex()
{
	return SharedInstanceMutex;
}

const BFW::MultiProcessing::SharedMutex& BFW::RunTime::Application::GetSharedInstanceMutex() const
{
	return SharedInstanceMutex;
}

#ifdef BFW_WINDOWS_PLATFORM

const size_t BFW::RunTime::Application::GetArgC() const
{
	return __argc;
}

const BFW_CHAR_TYPE* BFW::RunTime::Application::GetArgV(const size_t _Index) const
{
#ifdef _UNICODE

	return __wargv[_Index];

#endif

#ifndef _UNICODE

	return __argv[_Index];

#endif
}

#endif

#ifdef BFW_LINUX_PLATFORM

const size_t BFW::RunTime::Application::GetArgC() const
{
	return ArgC;
}

const BFW_CHAR_TYPE* BFW::RunTime::Application::GetArgV(const size_t _Index) const
{
	return ArgV[_Index];
}

#endif

#endif

#ifdef BFW_WINDOWS_PLATFORM

const HINSTANCE BFW::RunTime::Application::GetInstanceHandle() const
{
	return InstanceHandle;
}

const BFW_CHAR_TYPE* BFW::RunTime::Application::GetCmdLine() const
{
	return CmdLine;
}

const int32_t BFW::RunTime::Application::GetShowCmd() const
{
	return ShowCmd;
}

#endif

#ifdef BFW_WINDOWS_PLATFORM

BFW::RunTime::Application& BFW::RunTime::Application::operator= (Application&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	On = _Other.On;
	ReturnValue = _Other.ReturnValue;
	CurrentMenu = _Other.CurrentMenu;
	FrameTime[_PreviousState] = (Time::Timer&&)(_Other.FrameTime[_PreviousState]);
	FrameTime[_CurrentState] = (Time::Timer&&)(_Other.FrameTime[_CurrentState]);
	LagTime = _Other.LagTime;
	SimulationSpeed = _Other.SimulationSpeed;
	Sync = _Other.Sync;
	SharedInstanceMemory = (MultiProcessing::SharedMemory&&)(_Other.SharedInstanceMemory);
	SharedInstanceMutex = (MultiProcessing::SharedMutex&&)(_Other.SharedInstanceMutex);
	InstanceHandle = _Other.InstanceHandle;
	CmdLine = _Other.CmdLine;
	ShowCmd = _Other.ShowCmd;

	_Other.On = false;
	_Other.ReturnValue = MultiProcessing::_UnknownErrorReturnValue;
	_Other.CurrentMenu = _NullMenu;
	_Other.LagTime = 0.0f;
	_Other.SimulationSpeed = 1.0f;
	_Other.Sync = 60;
	_Other.InstanceHandle = NULL;
	_Other.CmdLine = nullptr;
	_Other.ShowCmd = SW_HIDE;

	return *this;
}

#endif

#ifdef BFW_LINUX_PLATFORM

BFW::RunTime::Application& BFW::RunTime::Application::operator= (Application&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	On = _Other.On;
	ReturnValue = _Other.ReturnValue;
	CurrentMenu = _Other.CurrentMenu;
	FrameTime[_PreviousState] = (Time::Timer&&)(_Other.FrameTime[_PreviousState]);
	FrameTime[_CurrentState] = (Time::Timer&&)(_Other.FrameTime[_CurrentState]);
	LagTime = _Other.LagTime;
	SimulationSpeed = _Other.SimulationSpeed;
	Sync = _Other.Sync;
	SharedInstanceMemory = (MultiProcessing::SharedMemory&&)(_Other.SharedInstanceMemory);
	SharedInstanceMutex = (MultiProcessing::SharedMutex&&)(_Other.SharedInstanceMutex);
	ArgC = _Other.ArgC;
	ArgV = _Other.ArgV;

	_Other.On = false;
	_Other.ReturnValue = MultiProcessing::_UnknownErrorReturnValue;
	_Other.CurrentMenu = _NullMenu;
	_Other.LagTime = 0.0f;
	_Other.SimulationSpeed = 1.0f;
	_Other.Sync = 60;
	_Other.ArgC = 0;
	_Other.ArgV = nullptr;

	return *this;
}

#endif

#ifdef BFW_ESP32_PLATFORM

BFW::RunTime::Application& BFW::RunTime::Application::operator= (Application&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	On = _Other.On;
	ReturnValue = _Other.ReturnValue;
	CurrentMenu = _Other.CurrentMenu;
	FrameTime[_PreviousState] = (Time::Timer&&)(_Other.FrameTime[_PreviousState]);
	FrameTime[_CurrentState] = (Time::Timer&&)(_Other.FrameTime[_CurrentState]);
	LagTime = _Other.LagTime;
	SimulationSpeed = _Other.SimulationSpeed;
	Sync = _Other.Sync;

	_Other.On = false;
	_Other.ReturnValue = MultiProcessing::_UnknownErrorReturnValue;
	_Other.CurrentMenu = _NullMenu;
	_Other.LagTime = 0.0f;
	_Other.SimulationSpeed = 1.0f;
	_Other.Sync = 60;

	return *this;
}

#endif



BFW::RunTime::Menu::Menu() : On(false), NextMenu(_NullMenu), QueuedMenu(_NullMenu), ApplicationObj(nullptr), ParentMenu(nullptr)
{

}

BFW::RunTime::Menu::Menu(Menu&& _Other) noexcept : On(_Other.On), NextMenu(_Other.NextMenu), QueuedMenu(_Other.QueuedMenu), ApplicationObj(_Other.ApplicationObj), ParentMenu(_Other.ParentMenu)
{
	_Other.On = false;
	_Other.NextMenu = _NullMenu;
	_Other.QueuedMenu = _NullMenu;
	_Other.ApplicationObj = nullptr;
	_Other.ParentMenu = nullptr;
}

BFW::RunTime::Menu::~Menu()
{

}

const uint64_t BFW::RunTime::Menu::Run(Application* _ApplicationObj, Menu* _ParentMenu)
{
	if (!_ApplicationObj)
	{
		BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("An Application object is required in order to run a Menu!"));
		return _NullMenu;
	}

	ApplicationObj = _ApplicationObj;
	ParentMenu = _ParentMenu;

	GetFrameTime(_PreviousState).Reset();

	Setup();
	while (On)
	{
		GetFrameTime(_CurrentState).Start();

		Update();

		if (GetSync())
		{
			GetFrameTime(_CurrentState).Stop();

			if (GetFrameTime(_CurrentState) < 1.0f / (float)(GetSync()))
			{
				Time::Sleep((uint64_t)((1.0f / (float)(GetSync()) - GetFrameTime(_CurrentState)) * 1000000.0f));
			}
		}

		GetFrameTime(_CurrentState).Stop();

		GetFrameTime(_PreviousState) = GetFrameTime(_CurrentState);

		if (On && ApplicationObj->CheckOn() && QueuedMenu != _NullMenu)
		{
			SpawnQueuedMenu(QueuedMenu);
			QueuedMenu = _NullMenu;
			GetFrameTime(_PreviousState).Reset();
		}

		if (!ApplicationObj->CheckOn())
		{
			Close(_NullMenu);
		}
	}
	Stop();

	QueuedMenu = _NullMenu;
	ApplicationObj = nullptr;
	ParentMenu = nullptr;

	uint64_t _NextMenu = NextMenu;
	NextMenu = _NullMenu;

	return _NextMenu;
}

BFW::RunTime::Menu& BFW::RunTime::Menu::operator= (Menu&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	On = _Other.On;
	NextMenu = _Other.NextMenu;
	QueuedMenu = _Other.QueuedMenu;
	ApplicationObj = _Other.ApplicationObj;
	ParentMenu = _Other.ParentMenu;

	_Other.On = false;
	_Other.NextMenu = _NullMenu;
	_Other.QueuedMenu = _NullMenu;
	_Other.ApplicationObj = nullptr;
	_Other.ParentMenu = nullptr;

	return *this;
}

void BFW::RunTime::Menu::TurnOn()
{
	On = true;
}

void BFW::RunTime::Menu::Close(const uint64_t _NextMenu)
{
	On = false;
	NextMenu = _NextMenu;
}

void BFW::RunTime::Menu::QueueMenu(const uint64_t _QueuedMenu)
{
	QueuedMenu = _QueuedMenu;
}

void BFW::RunTime::Menu::UpdateCurrentFrameTime()
{
	ApplicationObj->UpdateCurrentFrameTime();
}

void BFW::RunTime::Menu::SetLagTime(const float _LagTime)
{
	ApplicationObj->SetLagTime(_LagTime);
}

void BFW::RunTime::Menu::SetSimulationSpeed(const float _SimulationSpeed)
{
	ApplicationObj->SetSimulationSpeed(_SimulationSpeed);
}

void BFW::RunTime::Menu::SetSync(const uint64_t _Sync)
{
	ApplicationObj->SetSync(_Sync);
}

const bool BFW::RunTime::Menu::CheckOn() const
{
	return On;
}

const uint64_t BFW::RunTime::Menu::GetNextMenu() const
{
	return NextMenu;
}

const uint64_t BFW::RunTime::Menu::GetQueuedMenu() const
{
	return QueuedMenu;
}

BFW::RunTime::Application* BFW::RunTime::Menu::GetApplicationObj()
{
	return ApplicationObj;
}

const BFW::RunTime::Application* BFW::RunTime::Menu::GetApplicationObj() const
{
	return ApplicationObj;
}

BFW::RunTime::Menu* BFW::RunTime::Menu::GetParentMenu()
{
	return ParentMenu;
}

const BFW::RunTime::Menu* BFW::RunTime::Menu::GetParentMenu() const
{
	return ParentMenu;
}

BFW::Time::Timer& BFW::RunTime::Menu::GetFrameTime(const size_t _Index)
{
	return ApplicationObj->GetFrameTime(_Index);
}

const BFW::Time::Timer& BFW::RunTime::Menu::GetFrameTime(const size_t _Index) const
{
	return ApplicationObj->GetFrameTime(_Index);
}

const float BFW::RunTime::Menu::GetTimeStep() const
{
	return ApplicationObj->GetTimeStep();
}

const float BFW::RunTime::Menu::GetUITimeStep() const
{
	return ApplicationObj->GetUITimeStep();
}

const float BFW::RunTime::Menu::GetLagTime() const
{
	return ApplicationObj->GetLagTime();
}

const float BFW::RunTime::Menu::GetSimulationSpeed() const
{
	return ApplicationObj->GetSimulationSpeed();
}

const uint64_t BFW::RunTime::Menu::GetSync() const
{
	return ApplicationObj->GetSync();
}
