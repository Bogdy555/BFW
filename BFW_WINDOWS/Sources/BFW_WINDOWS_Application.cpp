#include "../Headers/BFW_WINDOWS.hpp"



BFW_WINDOWS::RunTime::Application::Application() : BFW::RunTime::Application(), Controllers(), MainWindow(), MainWindowData(), ChildWindows(), ChildWindowsData()
{

}

BFW_WINDOWS::RunTime::Application::~Application()
{

}

const bool BFW_WINDOWS::RunTime::Application::AddChildWindow()
{
	ChildWindowsData.PushBack(new GUI::WindowData());

	if (ChildWindowsData[ChildWindowsData.GetSize() - 1] == nullptr)
	{
		ChildWindowsData.Erase(ChildWindowsData.GetSize() - 1);
		return false;
	}

	BFW_HEAP_PROFILE_PUSH(sizeof(GUI::WindowData), ChildWindowsData[ChildWindowsData.GetSize() - 1]);

	ChildWindows.PushBack(new BFW::GUI::Window());

	if (ChildWindows[ChildWindows.GetSize() - 1] == nullptr)
	{
		BFW_HEAP_PROFILE_POP(ChildWindowsData[ChildWindowsData.GetSize() - 1]);
		delete ChildWindowsData[ChildWindowsData.GetSize() - 1];
		ChildWindowsData.Erase(ChildWindowsData.GetSize() - 1);
		ChildWindows.Erase(ChildWindows.GetSize() - 1);
		return false;
	}

	BFW_HEAP_PROFILE_PUSH(sizeof(BFW::GUI::Window), ChildWindows[ChildWindows.GetSize() - 1]);

	return true;
}

void BFW_WINDOWS::RunTime::Application::RemoveChildWindow(const size_t _Index)
{
	ChildWindows[_Index]->Destroy();
	BFW_HEAP_PROFILE_POP(ChildWindows[_Index]);
	delete ChildWindows[_Index];
	BFW_HEAP_PROFILE_POP(ChildWindowsData[_Index]);
	delete ChildWindowsData[_Index];
	ChildWindows.Erase(_Index);
	ChildWindowsData.Erase(_Index);
}

BFW::Input::Controller& BFW_WINDOWS::RunTime::Application::GetController(const size_t _Index)
{
	return Controllers[_Index];
}

const BFW::Input::Controller& BFW_WINDOWS::RunTime::Application::GetController(const size_t _Index) const
{
	return Controllers[_Index];
}

BFW::GUI::Window& BFW_WINDOWS::RunTime::Application::GetMainWindow()
{
	return MainWindow;
}

const BFW::GUI::Window& BFW_WINDOWS::RunTime::Application::GetMainWindow() const
{
	return MainWindow;
}

BFW_WINDOWS::GUI::WindowData& BFW_WINDOWS::RunTime::Application::GetMainWindowData()
{
	return MainWindowData;
}

const BFW_WINDOWS::GUI::WindowData& BFW_WINDOWS::RunTime::Application::GetMainWindowData() const
{
	return MainWindowData;
}

BFW::Vector<BFW::GUI::Window*>& BFW_WINDOWS::RunTime::Application::GetChildWindows()
{
	return ChildWindows;
}

const BFW::Vector<BFW::GUI::Window*>& BFW_WINDOWS::RunTime::Application::GetChildWindows() const
{
	return ChildWindows;
}

BFW::Vector<BFW_WINDOWS::GUI::WindowData*>& BFW_WINDOWS::RunTime::Application::GetChildWindowsData()
{
	return ChildWindowsData;
}

const BFW::Vector<BFW_WINDOWS::GUI::WindowData*>& BFW_WINDOWS::RunTime::Application::GetChildWindowsData() const
{
	return ChildWindowsData;
}

void BFW_WINDOWS::RunTime::Application::Setup()
{
	if (GetArgC() != 1)
	{
		Close(BFW::MultiProcessing::_UnknownErrorReturnValue);
		return;
	}

	if (!InitInstance())
	{
		Close(BFW::MultiProcessing::_NoErrorReturnValue);
		return;
	}

	if (!InitWindows())
	{
		Close(BFW::MultiProcessing::_UnknownErrorReturnValue);
		return;
	}

	if (!MainWindow.Show(GetShowCmd()))
	{
		Close(BFW::MultiProcessing::_UnknownErrorReturnValue);
		return;
	}

	TurnOn();
	SetCurrentMenu(_MainMenu);
}

void BFW_WINDOWS::RunTime::Application::Update()
{
	switch (GetCurrentMenu())
	{
	case _MainMenu:
	{
		MainMenu _Menu;

		uint64_t _NextMenu = _Menu.Run(this);

		SetCurrentMenu(_NextMenu);

		break;
	}
	case BFW::RunTime::_NullMenu:
	{
		Close(BFW::MultiProcessing::_UnknownErrorReturnValue);
		break;
	}
	default:
	{
		Close(BFW::MultiProcessing::_UnknownErrorReturnValue);
		break;
	}
	}
}

void BFW_WINDOWS::RunTime::Application::Stop()
{
	CleanUpWindows();
}

const bool BFW_WINDOWS::RunTime::Application::InitInstance()
{
	GetSharedInstanceMutex().Lock();

	uint64_t& _SharedInstanceMemory = *(uint64_t*)(GetSharedInstanceMemory().GetData());

	if (_SharedInstanceMemory != 1)
	{
		HWND _Handle = FindWindow(BFW_WINDOWS_MAIN_WINDOW_CLASS, BFW_STRING_PREFIX("BFW_WINDOWS"));

		if (_Handle != NULL)
		{
			if (IsIconic(_Handle))
			{
				ShowWindow(_Handle, SW_RESTORE);
			}

			SetForegroundWindow(_Handle);
		}

		GetSharedInstanceMutex().Unlock();

		return false;
	}

	GetSharedInstanceMutex().Unlock();

	return true;
}

const bool BFW_WINDOWS::RunTime::Application::InitWindows()
{
	WNDCLASSEX _WndClass = { 0 };

	_WndClass.cbSize = sizeof(WNDCLASSEX);
	_WndClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	_WndClass.lpfnWndProc = GUI::MainWindowProc;
	_WndClass.cbClsExtra = 0;
	_WndClass.cbWndExtra = 0;
	_WndClass.hInstance = GetInstanceHandle();
	_WndClass.hIcon = LoadIcon(GetInstanceHandle(), MAKEINTRESOURCE(BFW_WINDOWS_IDI_MAIN_ICON));
	_WndClass.hCursor = NULL;
	_WndClass.hbrBackground = NULL;
	_WndClass.lpszMenuName = nullptr;
	_WndClass.lpszClassName = BFW_WINDOWS_MAIN_WINDOW_CLASS;
	_WndClass.hIconSm = LoadIcon(GetInstanceHandle(), MAKEINTRESOURCE(BFW_WINDOWS_IDI_MAIN_ICON));

	if (!RegisterClassEx(&_WndClass))
	{
		return false;
	}

	_WndClass.cbSize = sizeof(WNDCLASSEX);
	_WndClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	_WndClass.lpfnWndProc = GUI::ChildWindowProc;
	_WndClass.cbClsExtra = 0;
	_WndClass.cbWndExtra = 0;
	_WndClass.hInstance = GetInstanceHandle();
	_WndClass.hIcon = LoadIcon(GetInstanceHandle(), MAKEINTRESOURCE(BFW_WINDOWS_IDI_MAIN_ICON));
	_WndClass.hCursor = NULL;
	_WndClass.hbrBackground = NULL;
	_WndClass.lpszMenuName = nullptr;
	_WndClass.lpszClassName = BFW_WINDOWS_CHILD_WINDOW_CLASS;
	_WndClass.hIconSm = LoadIcon(GetInstanceHandle(), MAKEINTRESOURCE(BFW_WINDOWS_IDI_MAIN_ICON));

	if (!RegisterClassEx(&_WndClass))
	{
		UnregisterClass(BFW_WINDOWS_MAIN_WINDOW_CLASS, GetInstanceHandle());
		return false;
	}

	if (!MainWindow.Create(NULL, BFW_WINDOWS_MAIN_WINDOW_CLASS, BFW_STRING_PREFIX("BFW_WINDOWS"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, GetInstanceHandle(), nullptr, NULL, GUI::MainWindowThreadInit, GUI::MainWindowThreadCleanUp, GUI::MainWindowInit, GUI::MainWindowCleanUp, &MainWindowData))
	{
		UnregisterClass(BFW_WINDOWS_MAIN_WINDOW_CLASS, GetInstanceHandle());
		UnregisterClass(BFW_WINDOWS_CHILD_WINDOW_CLASS, GetInstanceHandle());
		return false;
	}

	return true;
}

void BFW_WINDOWS::RunTime::Application::CleanUpWindows()
{
	if (!MainWindow.CheckOn())
	{
		return;
	}

	while (ChildWindows.GetSize())
	{
		RemoveChildWindow(0);
	}

	MainWindow.Destroy();

	UnregisterClass(BFW_WINDOWS_MAIN_WINDOW_CLASS, GetInstanceHandle());
	UnregisterClass(BFW_WINDOWS_CHILD_WINDOW_CLASS, GetInstanceHandle());
}
