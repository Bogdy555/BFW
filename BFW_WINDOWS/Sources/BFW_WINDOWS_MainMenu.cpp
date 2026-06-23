#include "../Headers/BFW_WINDOWS.hpp"



BFW_WINDOWS::RunTime::MainMenu::MainMenu() : BFW::RunTime::Menu()
{

}

BFW_WINDOWS::RunTime::MainMenu::MainMenu(MainMenu&& _Other) noexcept : BFW::RunTime::Menu((BFW::RunTime::Menu&&)(_Other))
{

}

BFW_WINDOWS::RunTime::MainMenu::~MainMenu()
{

}

const uint64_t BFW_WINDOWS::RunTime::MainMenu::GetType() const
{
	return _MainMenu;
}

BFW_WINDOWS::RunTime::MainMenu& BFW_WINDOWS::RunTime::MainMenu::operator= (MainMenu&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	*(BFW::RunTime::Menu*)(this) = (BFW::RunTime::Menu&&)(_Other);

	return *this;
}

void BFW_WINDOWS::RunTime::MainMenu::SpawnQueuedMenu(const uint64_t _QueuedMenu)
{
	Application& _ApplicationObj = *(Application*)(GetApplicationObj());
	BFW::GUI::Window& _MainWindow = _ApplicationObj.GetMainWindow();
	GUI::WindowData& _MainWindowData = _ApplicationObj.GetMainWindowData();
	BFW::Vector<BFW::GUI::Window>& _ChildWindows = _ApplicationObj.GetChildWindows();
	BFW::Vector<GUI::WindowData*>& _ChildWindowsData = _ApplicationObj.GetChildWindowsData();

	CleanUpGUI();

	switch (_QueuedMenu)
	{
	case BFW::RunTime::_NullMenu:
	{
		GetApplicationObj()->Close(BFW::MultiProcessing::_UnknownErrorReturnValue);
		break;
	}
	default:
	{
		GetApplicationObj()->Close(BFW::MultiProcessing::_UnknownErrorReturnValue);
		break;
	}
	}

	_MainWindow.CleanInputState();
	_MainWindow.CleanEvents();
	for (size_t _Index = 0; _Index < _ChildWindows.GetSize(); _Index++)
	{
		_ChildWindows[_Index].CleanInputState();
		_ChildWindows[_Index].CleanEvents();
	}
	DeleteInputs();

	InitGUI();
}

void BFW_WINDOWS::RunTime::MainMenu::Setup()
{
	Application& _ApplicationObj = *(Application*)(GetApplicationObj());
	BFW::GUI::Window& _MainWindow = _ApplicationObj.GetMainWindow();
	GUI::WindowData& _MainWindowData = _ApplicationObj.GetMainWindowData();
	BFW::Vector<BFW::GUI::Window>& _ChildWindows = _ApplicationObj.GetChildWindows();
	BFW::Vector<GUI::WindowData*>& _ChildWindowsData = _ApplicationObj.GetChildWindowsData();

	_MainWindow.CleanInputState();
	_MainWindow.CleanEvents();
	for (size_t _Index = 0; _Index < _ChildWindows.GetSize(); _Index++)
	{
		_ChildWindows[_Index].CleanInputState();
		_ChildWindows[_Index].CleanEvents();
	}
	DeleteInputs();

	InitGUI();

	TurnOn();
}

void BFW_WINDOWS::RunTime::MainMenu::Update()
{
	Input();
	Engine();
	FrameBuild();
}

void BFW_WINDOWS::RunTime::MainMenu::Stop()
{
	CleanUpGUI();
}

void BFW_WINDOWS::RunTime::MainMenu::InitGUI()
{
	Application& _ApplicationObj = *(Application*)(GetApplicationObj());
	BFW::GUI::Window& _MainWindow = _ApplicationObj.GetMainWindow();
	GUI::WindowData& _MainWindowData = _ApplicationObj.GetMainWindowData();
	BFW::Vector<BFW::GUI::Window>& _ChildWindows = _ApplicationObj.GetChildWindows();
	BFW::Vector<GUI::WindowData*>& _ChildWindowsData = _ApplicationObj.GetChildWindowsData();

	_MainWindowData.RenderingMutex->lock();

	GUI::PopUpData& _MainWindowPopUpData = *(GUI::PopUpData*)(_MainWindowData.Layout.GetUserData());

	BFW::GUI::PopUp _NewLayout;

	_NewLayout.Begin
	(
		BFW::GUI::_NodePopUpId, BFW::GUI::_NullPanelType,
		_MainWindowPopUpData.Width, _MainWindowPopUpData.Height,
		_MainWindowPopUpData.Width, _MainWindowPopUpData.Height,
		0, 0,
		0, 0,
		nullptr, nullptr,
		GUI::RenderGray20, nullptr, nullptr,
		GUI::Composit,
		_MainWindowData.Layout.GetUserData()
	);

	GUI::GenerateExample
	(
		_NewLayout.PushLeftPanel
		(
			GUI::_ExamplePopUpId,
			GUI::ExampleMinX, GUI::ExampleMinY * (GUI::ExampleMinY >= _NewLayout.GetTrueHeight()) + _NewLayout.GetTrueHeight() * (GUI::ExampleMinY < _NewLayout.GetTrueHeight()),
			GUI::ExampleMinX,
			0, 0,
			GUI::SetupRenderData, GUI::CleanUpRenderData,
			GUI::RenderGray30, nullptr, nullptr,
			GUI::Composit,
			nullptr,
			true
		),
		this
	);

	_NewLayout.GetNode()->Begin
	(
		BFW::GUI::_NodePopUpId, BFW::GUI::_NullPanelType,
		_NewLayout.GetNode()->GetTrueWidth(), _NewLayout.GetNode()->GetTrueHeight(),
		_NewLayout.GetNode()->GetWidth(), _NewLayout.GetNode()->GetHeight(),
		_NewLayout.GetNode()->GetPositionX(), _NewLayout.GetNode()->GetPositionY(),
		0, 0,
		GUI::SetupRenderData, GUI::CleanUpRenderData,
		GUI::RenderGray20, nullptr, nullptr,
		GUI::Composit,
		_MainWindowData.Layout.GetUserData()
	);

	GUI::GenerateExample
	(
		_NewLayout.GetNode()->PushBottomPanel
		(
			GUI::_ExamplePopUpId,
			GUI::ExampleMinX * (GUI::ExampleMinX >= _NewLayout.GetNode()->GetTrueWidth()) + _NewLayout.GetNode()->GetTrueWidth() * (GUI::ExampleMinX < _NewLayout.GetNode()->GetTrueWidth()), GUI::ExampleMinY,
			GUI::ExampleMinY,
			0, 0,
			GUI::SetupRenderData, GUI::CleanUpRenderData,
			GUI::RenderGray30, nullptr, nullptr,
			GUI::Composit,
			nullptr,
			true
		),
		this
	);

	_MainWindowData.Layout = _NewLayout;

	_MainWindowData.RenderingMutex->unlock();
}

void BFW_WINDOWS::RunTime::MainMenu::CleanUpGUI()
{
	Application& _ApplicationObj = *(Application*)(GetApplicationObj());
	BFW::GUI::Window& _MainWindow = _ApplicationObj.GetMainWindow();
	GUI::WindowData& _MainWindowData = _ApplicationObj.GetMainWindowData();
	BFW::Vector<BFW::GUI::Window>& _ChildWindows = _ApplicationObj.GetChildWindows();
	BFW::Vector<GUI::WindowData*>& _ChildWindowsData = _ApplicationObj.GetChildWindowsData();

	_MainWindowData.RenderingMutex->lock();

	BFW::GUI::PopUp _NewLayout;
	_NewLayout.SetUserData(_MainWindowData.Layout.GetUserData());
	_MainWindowData.Layout = _NewLayout;

	_MainWindowData.RenderingMutex->unlock();

	while (_ChildWindows.GetSize())
	{
		_ApplicationObj.RemoveChildWindow(0);
	}
}

void BFW_WINDOWS::RunTime::MainMenu::RenderWindow(BFW::GUI::Window& _Wnd, GUI::WindowData& _WndData)
{
	Application& _ApplicationObj = *(Application*)(GetApplicationObj());

	_WndData.RenderingMutex->lock();

	size_t _WndWidth = 0, _WndHeight = 0;

	_Wnd.GetClientSize(_WndWidth, _WndHeight);

	GUI::PopUpData& _WndPopUpData = *(GUI::PopUpData*)(_WndData.Layout.GetUserData());

	if (_WndWidth == 0 || _WndHeight == 0)
	{
		_WndWidth = _WndPopUpData.Width;
		_WndHeight = _WndPopUpData.Height;
	}

	if (_WndWidth != _WndPopUpData.Width || _WndHeight != _WndPopUpData.Height)
	{
		uint8_t* _Pixels = new uint8_t[(_WndWidth) * (_WndHeight) * 4];

		if (_Pixels)
		{
			delete[] _WndPopUpData.Pixels;

			_WndPopUpData.Width = _WndWidth;
			_WndPopUpData.Height = _WndHeight;
			_WndPopUpData.Pixels = _Pixels;

			switch (_WndData.Layout.GetId())
			{
			case GUI::_ExamplePopUpId:
			{
				_WndData.Layout.SetTrueWidth(_WndWidth * (_WndWidth >= GUI::ExampleMinX) + GUI::ExampleMinX * (_WndWidth < GUI::ExampleMinX));
				_WndData.Layout.SetTrueHeight(_WndHeight * (_WndHeight >= GUI::ExampleMinY) + GUI::ExampleMinY * (_WndHeight < GUI::ExampleMinY));
				_WndData.Layout.SetWidth(_WndWidth);
				_WndData.Layout.SetHeight(_WndHeight);
				_WndData.Layout.SetScrollX(_WndData.Layout.GetScrollX() * (_WndData.Layout.GetScrollX() <= _WndData.Layout.GetTrueWidth() - _WndData.Layout.GetWidth()) + (_WndData.Layout.GetTrueWidth() - _WndData.Layout.GetWidth()) * (_WndData.Layout.GetScrollX() > _WndData.Layout.GetTrueWidth() - _WndData.Layout.GetWidth()));
				_WndData.Layout.SetScrollY(_WndData.Layout.GetScrollY() * (_WndData.Layout.GetScrollY() <= _WndData.Layout.GetTrueHeight() - _WndData.Layout.GetHeight()) + (_WndData.Layout.GetTrueHeight() - _WndData.Layout.GetHeight()) * (_WndData.Layout.GetScrollY() > _WndData.Layout.GetTrueHeight() - _WndData.Layout.GetHeight()));

				break;
			}
			case BFW::GUI::_NodePopUpId:
			{
				_WndData.Layout.SetTrueWidth(_WndWidth);
				_WndData.Layout.SetTrueHeight(_WndHeight);
				_WndData.Layout.SetWidth(_WndWidth);
				_WndData.Layout.SetHeight(_WndHeight);
				_WndData.Layout.SetScrollX(_WndData.Layout.GetScrollX() * (_WndData.Layout.GetScrollX() <= _WndData.Layout.GetTrueWidth() - _WndData.Layout.GetWidth()) + (_WndData.Layout.GetTrueWidth() - _WndData.Layout.GetWidth()) * (_WndData.Layout.GetScrollX() > _WndData.Layout.GetTrueWidth() - _WndData.Layout.GetWidth()));
				_WndData.Layout.SetScrollY(_WndData.Layout.GetScrollY() * (_WndData.Layout.GetScrollY() <= _WndData.Layout.GetTrueHeight() - _WndData.Layout.GetHeight()) + (_WndData.Layout.GetTrueHeight() - _WndData.Layout.GetHeight()) * (_WndData.Layout.GetScrollY() > _WndData.Layout.GetTrueHeight() - _WndData.Layout.GetHeight()));

				break;
			}
			default:
			{
				throw nullptr;
			}
			}

			GUI::ResizeChilds(_WndData.Layout, this);
		}
	}

	_WndData.Layout.Render(this);

	intptr_t _WndMouseX = 0, _WndMouseY = 0;

	if (_Wnd.GetMousePosition(_WndMouseX, _WndMouseY))
	{
		BFW::GUI::PopUp* _HoverPopUp = _WndData.Layout.GetChildFromMouse(_WndMouseX, _WndMouseY);

		if (_HoverPopUp)
		{
			GUI::RenderCursor(_Wnd, _HoverPopUp->GetId());
		}
		else
		{
			GUI::RenderCursor(_Wnd, BFW::GUI::_NodePopUpId);
		}
	}

	_WndData.RenderingMutex->unlock();

	_Wnd.UpdateContent();
}

void BFW_WINDOWS::RunTime::MainMenu::Input()
{
	Application& _ApplicationObj = *(Application*)(GetApplicationObj());
	BFW::GUI::Window& _MainWindow = _ApplicationObj.GetMainWindow();
	GUI::WindowData& _MainWindowData = _ApplicationObj.GetMainWindowData();
	BFW::Vector<BFW::GUI::Window>& _ChildWindows = _ApplicationObj.GetChildWindows();
	BFW::Vector<GUI::WindowData*>& _ChildWindowsData = _ApplicationObj.GetChildWindowsData();

	_MainWindow.UpdateInputState();

	for (size_t _Index = 0; _Index < _ChildWindows.GetSize(); _Index++)
	{
		_ChildWindows[_Index].UpdateInputState();
	}

	_ApplicationObj.GetController(0).UpdateState(0);
	_ApplicationObj.GetController(1).UpdateState(1);
	_ApplicationObj.GetController(2).UpdateState(2);
	_ApplicationObj.GetController(3).UpdateState(3);

	bool _Focus = _MainWindow.HasFocus();

	for (size_t _Index = 0; _Index < _ChildWindows.GetSize(); _Index++)
	{
		if (_ChildWindows[_Index].HasFocus())
		{
			_Focus = true;
		}
	}

	if (!_Focus)
	{
		DeleteInputs();
	}
}

void BFW_WINDOWS::RunTime::MainMenu::DeleteInputs()
{
	Application& _ApplicationObj = *(Application*)(GetApplicationObj());
	BFW::GUI::Window& _MainWindow = _ApplicationObj.GetMainWindow();
	GUI::WindowData& _MainWindowData = _ApplicationObj.GetMainWindowData();
	BFW::Vector<BFW::GUI::Window>& _ChildWindows = _ApplicationObj.GetChildWindows();
	BFW::Vector<GUI::WindowData*>& _ChildWindowsData = _ApplicationObj.GetChildWindowsData();

	_ApplicationObj.GetController(0).CleanState();
	_ApplicationObj.GetController(1).CleanState();
	_ApplicationObj.GetController(2).CleanState();
	_ApplicationObj.GetController(3).CleanState();
}

void BFW_WINDOWS::RunTime::MainMenu::Engine()
{
	Application& _ApplicationObj = *(Application*)(GetApplicationObj());
	BFW::GUI::Window& _MainWindow = _ApplicationObj.GetMainWindow();
	GUI::WindowData& _MainWindowData = _ApplicationObj.GetMainWindowData();
	BFW::Vector<BFW::GUI::Window>& _ChildWindows = _ApplicationObj.GetChildWindows();
	BFW::Vector<GUI::WindowData*>& _ChildWindowsData = _ApplicationObj.GetChildWindowsData();

	if (_MainWindow.ShouldClose())
	{
		_ApplicationObj.Close(BFW::MultiProcessing::_NoErrorReturnValue);
	}

	for (size_t _Index = 0; _Index < _ChildWindows.GetSize(); _Index++)
	{
		if (_ChildWindows[_Index].ShouldClose())
		{
			_ApplicationObj.RemoveChildWindow(_Index);
			_Index--;
		}
	}

	if (_MainWindow.GetKeys()[VK_F11].JustPressed())
	{
		if (_MainWindow.IsFullScreen())
		{
			_MainWindow.GoWindowed();
		}
		else
		{
			_MainWindow.GoFullScreen();
		}
	}

	_MainWindow.CleanEvents();

	for (size_t _Index = 0; _Index < _ChildWindows.GetSize(); _Index++)
	{
		_ChildWindows[_Index].CleanEvents();
	}

	BFW::Input::Controller::SetRumble(0, 0.0f, 0.0f);
	BFW::Input::Controller::SetRumble(1, 0.0f, 0.0f);
	BFW::Input::Controller::SetRumble(2, 0.0f, 0.0f);
	BFW::Input::Controller::SetRumble(3, 0.0f, 0.0f);

	uint64_t _Sync = _MainWindow.GetRefreshRate();

	for (size_t _Index = 0; _Index < _ChildWindows.GetSize(); _Index++)
	{
		uint64_t _LocalSync = _ChildWindows[_Index].GetRefreshRate();

		if (_LocalSync > _Sync)
		{
			_Sync = _LocalSync;
		}
	}

	SetSync(_Sync);
}

void BFW_WINDOWS::RunTime::MainMenu::FrameBuild()
{
	Application& _ApplicationObj = *(Application*)(GetApplicationObj());
	BFW::GUI::Window& _MainWindow = _ApplicationObj.GetMainWindow();
	GUI::WindowData& _MainWindowData = _ApplicationObj.GetMainWindowData();
	BFW::Vector<BFW::GUI::Window>& _ChildWindows = _ApplicationObj.GetChildWindows();
	BFW::Vector<GUI::WindowData*>& _ChildWindowsData = _ApplicationObj.GetChildWindowsData();

	RenderWindow(_MainWindow, _MainWindowData);

	for (size_t _Index = 0; _Index < _ChildWindows.GetSize(); _Index++)
	{
		RenderWindow(_ChildWindows[_Index], *_ChildWindowsData[_Index]);
	}
}
