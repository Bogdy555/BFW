#include "../Headers/BFW.hpp"



#ifdef BFW_WINDOWS_PLATFORM

BFW::RunTime::Application::Application() : On(false), ReturnValue(MultiProcessing::_UnknownErrorReturnValue), CurrentMenu(_NullMenu), FrameTime(), LagTime(1.0f / 10.0f), SimulationSpeed(1.0f), Sync(60), WorkingDirectory(), WorkingDirectoryDiff(), AssetsDirectory(), AssetsDirectoryDiff(), Resources(), SharedInstanceMemory(), SharedInstanceMutex(), InstanceHandle(NULL), CmdLine(nullptr), ShowCmd(SW_HIDE)
{

}

#endif

#ifdef BFW_LINUX_PLATFORM

BFW::RunTime::Application::Application() : On(false), ReturnValue(MultiProcessing::_UnknownErrorReturnValue), CurrentMenu(_NullMenu), FrameTime(), LagTime(1.0f / 10.0f), SimulationSpeed(1.0f), Sync(60), WorkingDirectory(), WorkingDirectoryDiff(), AssetsDirectory(), AssetsDirectoryDiff(), SharedInstanceMemory(), SharedInstanceMutex(), ArgC(0), ArgV(nullptr)
{

}

#endif

#ifdef BFW_ESP32_PLATFORM

BFW::RunTime::Application::Application() : On(false), ReturnValue(MultiProcessing::_UnknownErrorReturnValue), CurrentMenu(_NullMenu), FrameTime(), LagTime(1.0f / 10.0f), SimulationSpeed(1.0f), Sync(60), WorkingDirectory(), WorkingDirectoryDiff(), AssetsDirectory(), AssetsDirectoryDiff(), SDCardPath()
{

}

#endif

BFW::RunTime::Application::~Application()
{

}

#ifdef BFW_WINDOWS_PLATFORM

const int32_t BFW::RunTime::Application::Run(const HINSTANCE _InstanceHandle, const BFW_CHAR_TYPE* _CmdLine, const int32_t _ShowCmd, const BFW_CHAR_TYPE* _SharedInstanceMemoryName, const BFW_CHAR_TYPE* _SharedInstanceMutexName, const bool _EnforceWorkingDirectory)
{
	if (_InstanceHandle == NULL || _CmdLine == nullptr || _SharedInstanceMemoryName == nullptr || _SharedInstanceMutexName == nullptr)
	{
		return MultiProcessing::_UnknownErrorReturnValue;
	}

	if (_EnforceWorkingDirectory)
	{
		BFW_UNICODE_CALL(FileSystem::File _Binary = FileSystem::File::Load(__wargv[0]));
		BFW_NON_UNICODE_CALL(FileSystem::File _Binary = FileSystem::File::Load(__argv[0]));

		if (_Binary.GetParentPath() != FileSystem::GetWorkingDirectory())
		{
			return MultiProcessing::_UnknownErrorReturnValue;
		}
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

	WorkingDirectory = FileSystem::Directory::Load(FileSystem::GetWorkingDirectory());

	{
		BFW_UNICODE_CALL(FileSystem::File _Binary = FileSystem::File::Load(__wargv[0]));
		BFW_NON_UNICODE_CALL(FileSystem::File _Binary = FileSystem::File::Load(__argv[0]));

		AssetsDirectory = FileSystem::Directory::Load(_Binary.GetParentPath());
	}

	Resources.Emplace(BFW_TO_STRING(BFW_BMP_RESOURCE).c_str(), Trie<FileSystem::FileContent>());
	Resources.Emplace(BFW_TO_STRING(BFW_HDR_RESOURCE).c_str(), Trie<FileSystem::FileContent>());
	Resources.Emplace(BFW_TO_STRING(BFW_WAV_RESOURCE).c_str(), Trie<FileSystem::FileContent>());
	Resources.Emplace(BFW_TO_STRING(BFW_WFOBJ_RESOURCE).c_str(), Trie<FileSystem::FileContent>());
	Resources.Emplace(BFW_TO_STRING(BFW_MTL_RESOURCE).c_str(), Trie<FileSystem::FileContent>());
	Resources.Emplace(BFW_TO_STRING(BFW_GLSL_RESOURCE).c_str(), Trie<FileSystem::FileContent>());
	Resources.Emplace(BFW_TO_STRING(BFW_JSON_RESOURCE).c_str(), Trie<FileSystem::FileContent>());

	for (size_t _ResourceId = 0; _ResourceId < (size_t)(std::numeric_limits<uint16_t>::max()) + 1; _ResourceId++)
	{
		FileSystem::FileContent _FileContent;

		if (_FileContent.Load(BFW_BMP_RESOURCE, _ResourceId))
		{
			Resources.GetData(BFW_TO_STRING(BFW_BMP_RESOURCE).c_str())->Emplace(BFW_TO_STRING(_ResourceId).c_str(), (FileSystem::FileContent&&)(_FileContent));
		}

		if (_FileContent.Load(BFW_HDR_RESOURCE, _ResourceId))
		{
			Resources.GetData(BFW_TO_STRING(BFW_HDR_RESOURCE).c_str())->Emplace(BFW_TO_STRING(_ResourceId).c_str(), (FileSystem::FileContent&&)(_FileContent));
		}

		if (_FileContent.Load(BFW_WAV_RESOURCE, _ResourceId))
		{
			Resources.GetData(BFW_TO_STRING(BFW_WAV_RESOURCE).c_str())->Emplace(BFW_TO_STRING(_ResourceId).c_str(), (FileSystem::FileContent&&)(_FileContent));
		}

		if (_FileContent.Load(BFW_WFOBJ_RESOURCE, _ResourceId))
		{
			Resources.GetData(BFW_TO_STRING(BFW_WFOBJ_RESOURCE).c_str())->Emplace(BFW_TO_STRING(_ResourceId).c_str(), (FileSystem::FileContent&&)(_FileContent));
		}

		if (_FileContent.Load(BFW_MTL_RESOURCE, _ResourceId))
		{
			Resources.GetData(BFW_TO_STRING(BFW_MTL_RESOURCE).c_str())->Emplace(BFW_TO_STRING(_ResourceId).c_str(), (FileSystem::FileContent&&)(_FileContent));
		}

		if (_FileContent.Load(BFW_GLSL_RESOURCE, _ResourceId))
		{
			Resources.GetData(BFW_TO_STRING(BFW_GLSL_RESOURCE).c_str())->Emplace(BFW_TO_STRING(_ResourceId).c_str(), (FileSystem::FileContent&&)(_FileContent));
		}

		if (_FileContent.Load(BFW_JSON_RESOURCE, _ResourceId))
		{
			Resources.GetData(BFW_TO_STRING(BFW_JSON_RESOURCE).c_str())->Emplace(BFW_TO_STRING(_ResourceId).c_str(), (FileSystem::FileContent&&)(_FileContent));
		}
	}

	Setup();
	while (On)
	{
		Update();
	}
	Stop();

	CurrentMenu = _NullMenu;

	FrameTime[_PreviousState].Reset();
	FrameTime[_CurrentState].Reset();
	LagTime = 1.0f / 10.0f;
	SimulationSpeed = 1.0f;
	Sync = 60;

	WorkingDirectory = FileSystem::Directory();
	WorkingDirectoryDiff = FileSystem::DirectoryDiff();
	AssetsDirectory = FileSystem::Directory();
	AssetsDirectoryDiff = FileSystem::DirectoryDiff();

	Resources = Trie<Trie<FileSystem::FileContent>>();

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

const int32_t BFW::RunTime::Application::Run(const size_t _ArgC, const BFW_CHAR_TYPE** _ArgV, const BFW_CHAR_TYPE* _SharedInstanceMemoryName, const BFW_CHAR_TYPE* _SharedInstanceMutexName, const bool _EnforceWorkingDirectory)
{
	if (_ArgC == 0 || _ArgV == nullptr || _SharedInstanceMemoryName == nullptr || _SharedInstanceMutexName == nullptr)
	{
		return MultiProcessing::_UnknownErrorReturnValue;
	}

	if (_EnforceWorkingDirectory)
	{
		FileSystem::File _Binary = FileSystem::File::Load(_ArgV[0]);

		if (_Binary.GetParentPath() != FileSystem::GetWorkingDirectory())
		{
			return MultiProcessing::_UnknownErrorReturnValue;
		}
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

	WorkingDirectory = FileSystem::Directory::Load(FileSystem::GetWorkingDirectory());

	{
		FileSystem::File _Binary = FileSystem::File::Load(_ArgV[0]);

		AssetsDirectory = FileSystem::Directory::Load(_Binary.GetParentPath());
	}

	Setup();
	while (On)
	{
		Update();
	}
	Stop();

	CurrentMenu = _NullMenu;

	FrameTime[_PreviousState].Reset();
	FrameTime[_CurrentState].Reset();
	LagTime = 1.0f / 10.0f;
	SimulationSpeed = 1.0f;
	Sync = 60;

	WorkingDirectory = FileSystem::Directory();
	WorkingDirectoryDiff = FileSystem::DirectoryDiff();
	AssetsDirectory = FileSystem::Directory();
	AssetsDirectoryDiff = FileSystem::DirectoryDiff();

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

const int32_t BFW::RunTime::Application::Run(const BFW_STRING_TYPE& _SDCardPath)
{
	SDCardPath = _SDCardPath;

	WorkingDirectory = FileSystem::Directory::Load(FileSystem::GetWorkingDirectory(SDCardPath));
	AssetsDirectory = FileSystem::Directory::Load(FileSystem::GetWorkingDirectory(SDCardPath));

	Setup();
	while (On)
	{
		Update();
	}
	Stop();

	CurrentMenu = _NullMenu;

	FrameTime[_PreviousState].Reset();
	FrameTime[_CurrentState].Reset();
	LagTime = 1.0f / 10.0f;
	SimulationSpeed = 1.0f;
	Sync = 60;

	SDCardPath = BFW_STRING_TYPE();

	WorkingDirectory = FileSystem::Directory();
	WorkingDirectoryDiff = FileSystem::DirectoryDiff();
	AssetsDirectory = FileSystem::Directory();
	AssetsDirectoryDiff = FileSystem::DirectoryDiff();

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

void BFW::RunTime::Application::UpdateWorkingDirectory()
{
	FileSystem::Directory _NewWorkingDirectory = FileSystem::Directory::Load(FileSystem::GetWorkingDirectory(BFW_ESP32_PLATFORM_CALL(SDCardPath)));

	if (_NewWorkingDirectory.Path != WorkingDirectory.Path)
	{
		WorkingDirectory = FileSystem::Directory::Load(FileSystem::GetWorkingDirectory(BFW_ESP32_PLATFORM_CALL(SDCardPath)));
		WorkingDirectoryDiff = FileSystem::DirectoryDiff();
		WorkingDirectoryDiff += WorkingDirectory;
		return;
	}

	WorkingDirectoryDiff = FileSystem::DirectoryDiff::Get(WorkingDirectory, _NewWorkingDirectory);

	if (WorkingDirectoryDiff.Empty())
	{
		return;
	}

	WorkingDirectory = WorkingDirectoryDiff.Apply(WorkingDirectory);
}

#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

void BFW::RunTime::Application::UpdateAssetsDirectory()
{
	FileSystem::File _Binary = FileSystem::File::Load(GetArgV(0));

	FileSystem::Directory _NewAssetsDirectory = FileSystem::Directory::Load(_Binary.GetParentPath());

	AssetsDirectoryDiff = FileSystem::DirectoryDiff::Get(AssetsDirectory, _NewAssetsDirectory);

	if (AssetsDirectoryDiff.Empty())
	{
		return;
	}

	AssetsDirectory = AssetsDirectoryDiff.Apply(AssetsDirectory);
}

#endif

#ifdef BFW_ESP32_PLATFORM

void BFW::RunTime::Application::UpdateAssetsDirectory()
{
	FileSystem::Directory _NewAssetsDirectory = FileSystem::Directory::Load(FileSystem::GetWorkingDirectory(SDCardPath));

	if (_NewAssetsDirectory.Path != AssetsDirectory.Path)
	{
		AssetsDirectory = FileSystem::Directory::Load(FileSystem::GetWorkingDirectory(SDCardPath));
		AssetsDirectoryDiff = FileSystem::DirectoryDiff();
		AssetsDirectoryDiff += AssetsDirectory;
		return;
	}

	AssetsDirectoryDiff = FileSystem::DirectoryDiff::Get(AssetsDirectory, _NewAssetsDirectory);

	if (AssetsDirectoryDiff.Empty())
	{
		return;
	}

	AssetsDirectory = AssetsDirectoryDiff.Apply(AssetsDirectory);
}

#endif

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

const BFW::FileSystem::Directory& BFW::RunTime::Application::GetWorkingDirectory() const
{
	return WorkingDirectory;
}

const BFW::FileSystem::DirectoryDiff& BFW::RunTime::Application::GetWorkingDirectoryDiff() const
{
	return WorkingDirectoryDiff;
}

const BFW::FileSystem::Directory& BFW::RunTime::Application::GetAssetsDirectory() const
{
	return AssetsDirectory;
}

const BFW::FileSystem::DirectoryDiff& BFW::RunTime::Application::GetAssetsDirectoryDiff() const
{
	return AssetsDirectoryDiff;
}

#ifdef BFW_WINDOWS_PLATFORM

const BFW::Trie<BFW::Trie<BFW::FileSystem::FileContent>>& BFW::RunTime::Application::GetResources() const
{
	return Resources;
}

#endif

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



BFW::RunTime::Menu::Menu() : On(false), NextMenu(_NullMenu), QueuedMenu(_NullMenu), ApplicationObj(nullptr), ParentMenu(nullptr)
{

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
		UpdateWorkingDirectory();
		UpdateAssetsDirectory();

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

void BFW::RunTime::Menu::UpdateWorkingDirectory()
{
	ApplicationObj->UpdateWorkingDirectory();
}

void BFW::RunTime::Menu::UpdateAssetsDirectory()
{
	ApplicationObj->UpdateAssetsDirectory();
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

const BFW::FileSystem::Directory& BFW::RunTime::Menu::GetWorkingDirectory() const
{
	return ApplicationObj->GetWorkingDirectory();
}

const BFW::FileSystem::DirectoryDiff& BFW::RunTime::Menu::GetWorkingDirectoryDiff() const
{
	return ApplicationObj->GetWorkingDirectoryDiff();
}

const BFW::FileSystem::Directory& BFW::RunTime::Menu::GetAssetsDirectory() const
{
	return ApplicationObj->GetAssetsDirectory();
}

const BFW::FileSystem::DirectoryDiff& BFW::RunTime::Menu::GetAssetsDirectoryDiff() const
{
	return ApplicationObj->GetAssetsDirectoryDiff();
}

#ifdef BFW_WINDOWS_PLATFORM

const BFW::Trie<BFW::Trie<BFW::FileSystem::FileContent>>& BFW::RunTime::Menu::GetResources() const
{
	return ApplicationObj->GetResources();
}

#endif
