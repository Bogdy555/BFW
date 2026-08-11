#include "../Headers/BFW_WINDOWS.hpp"



BFW_WINDOWS::RunTime::MainMenu::MainMenu() : BFW::RunTime::Menu()
{

}

BFW_WINDOWS::RunTime::MainMenu::~MainMenu()
{

}

const uint64_t BFW_WINDOWS::RunTime::MainMenu::GetType() const
{
	return _MainMenu;
}

void BFW_WINDOWS::RunTime::MainMenu::SpawnQueuedMenu(const uint64_t _QueuedMenu)
{
	Application& _ApplicationObj = *(Application*)(GetApplicationObj());
	BFW::GUI::Window& _MainWindow = _ApplicationObj.GetMainWindow();
	GUI::WindowData& _MainWindowData = _ApplicationObj.GetMainWindowData();
	BFW::Vector<BFW::GUI::Window*>& _ChildWindows = _ApplicationObj.GetChildWindows();
	BFW::Vector<GUI::WindowData*>& _ChildWindowsData = _ApplicationObj.GetChildWindowsData();

	CleanUpGUI();

	switch (_QueuedMenu)
	{
	case BFW::RunTime::_NullMenu:
	{
		_ApplicationObj.Close(BFW::MultiProcessing::_UnknownErrorReturnValue);
		break;
	}
	default:
	{
		_ApplicationObj.Close(BFW::MultiProcessing::_UnknownErrorReturnValue);
		break;
	}
	}

	_MainWindow.CleanInputState();
	_MainWindow.CleanEvents();
	DeleteMouseCaptureInputs(_MainWindow, _MainWindowData);
	for (size_t _Index = 0; _Index < _ChildWindows.GetSize(); _Index++)
	{
		_ChildWindows[_Index]->CleanInputState();
		_ChildWindows[_Index]->CleanEvents();
		DeleteMouseCaptureInputs(*_ChildWindows[_Index], *_ChildWindowsData[_Index]);
	}
	DeleteInputs();

	InitGUI();
}

void BFW_WINDOWS::RunTime::MainMenu::Setup()
{
	Application& _ApplicationObj = *(Application*)(GetApplicationObj());
	BFW::GUI::Window& _MainWindow = _ApplicationObj.GetMainWindow();
	GUI::WindowData& _MainWindowData = _ApplicationObj.GetMainWindowData();
	BFW::Vector<BFW::GUI::Window*>& _ChildWindows = _ApplicationObj.GetChildWindows();
	BFW::Vector<GUI::WindowData*>& _ChildWindowsData = _ApplicationObj.GetChildWindowsData();

	_MainWindow.CleanInputState();
	_MainWindow.CleanEvents();
	DeleteMouseCaptureInputs(_MainWindow, _MainWindowData);
	for (size_t _Index = 0; _Index < _ChildWindows.GetSize(); _Index++)
	{
		_ChildWindows[_Index]->CleanInputState();
		_ChildWindows[_Index]->CleanEvents();
		DeleteMouseCaptureInputs(*_ChildWindows[_Index], *_ChildWindowsData[_Index]);
	}
	DeleteInputs();

	InitGUI();

	TurnOn();
}

void BFW_WINDOWS::RunTime::MainMenu::Update()
{
	BFW_PROFILE_FUNCTION();

	Input();
	Engine();
	FrameBuild();
}

void BFW_WINDOWS::RunTime::MainMenu::Stop()
{
	CleanUpGUI();
}

void BFW_WINDOWS::RunTime::MainMenu::GenerateNodeWindow(BFW::GUI::PopUp& _Parent)
{
	_Parent.Begin
	(
		BFW::GUI::_NodeWindowPopUpId, _Parent.GetPanelType(),
		0, 0,
		_Parent.GetWidth(), _Parent.GetHeight(),
		_Parent.GetPositionX(), _Parent.GetPositionY(),
		_Parent.GetScrollX(), _Parent.GetScrollY(),
		GUI::GetRenderingDescriptor(BFW::GUI::_NodeWindowPopUpId),
		GUI::GetHitBox(BFW::GUI::_NodeWindowPopUpId),
		GUI::GenerateUserData(BFW::GUI::_NodeWindowPopUpId, this)
	);
}

void BFW_WINDOWS::RunTime::MainMenu::GenerateDebugWindow(BFW::GUI::PopUp& _Parent, const bool _IsNode)
{
	_Parent.Begin
	(
		GUI::_DebugWindowPopUpId, _Parent.GetPanelType(),
		GUI::DebugWindowMinX, GUI::DebugWindowMinY,
		_Parent.GetWidth(), _Parent.GetHeight(),
		_Parent.GetPositionX(), _Parent.GetPositionY(),
		_Parent.GetScrollX(), _Parent.GetScrollY(),
		GUI::GetRenderingDescriptor(GUI::_DebugWindowPopUpId),
		GUI::GetHitBox(GUI::_DebugWindowPopUpId),
		GUI::GenerateUserData(GUI::_DebugWindowPopUpId, this)
	);

	size_t _Layer = _Parent.PushPopUpLayer();

	_Parent.PushPopUp
	(
		_Layer, GUI::_SpawnButtonPopUpId,
		0, 0,
		_Parent.GetTrueWidth() - GUI::Padding * 2, 20,
		GUI::Padding, GUI::TopPadding,
		0, 0,
		GUI::GetRenderingDescriptor(GUI::_SpawnButtonPopUpId),
		GUI::GetHitBox(GUI::_SpawnButtonPopUpId),
		GUI::GenerateUserData(GUI::_SpawnButtonPopUpId, this),
		true
	);

	_Parent.GenerateScrollBars
	(
		false, false,
		GUI::ForceHScroll(_Parent.GetId()), GUI::ForceVScroll(_Parent.GetId()),
		GUI::ScrollSize, GUI::ScrollTopPadding, GUI::ScrollPadding,
		GUI::GetRenderingDescriptor,
		GUI::GetHitBox,
		GUI::GenerateUserData, this
	);

	_Parent.GenerateResizeBars
	(
		_IsNode,
		GUI::ResizeSize,
		GUI::GetRenderingDescriptor,
		GUI::GetHitBox,
		GUI::GenerateUserData, this
	);
}

void BFW_WINDOWS::RunTime::MainMenu::InitGUI()
{
	Application& _ApplicationObj = *(Application*)(GetApplicationObj());
	BFW::GUI::Window& _MainWindow = _ApplicationObj.GetMainWindow();
	GUI::WindowData& _MainWindowData = _ApplicationObj.GetMainWindowData();
	BFW::Vector<BFW::GUI::Window*>& _ChildWindows = _ApplicationObj.GetChildWindows();
	BFW::Vector<GUI::WindowData*>& _ChildWindowsData = _ApplicationObj.GetChildWindowsData();

	_MainWindowData.LayoutMutex->lock();

	GUI::ReleaseAllChilds(_MainWindowData.Layout);

	GUI::PopUpData* _MainWindowOldPopUpData = (GUI::PopUpData*)(_MainWindowData.Layout.GetUserData());

	GenerateNodeWindow
	(
		_MainWindowData.Layout.Begin
		(
			BFW::GUI::_NodeWindowPopUpId, BFW::GUI::_NullPanelType,
			0, 0,
			_MainWindowOldPopUpData->Width, _MainWindowOldPopUpData->Height,
			0, 0,
			0, 0,
			BFW::GUI::RenderingDescriptor(),
			nullptr,
			nullptr
		)
	);

	GUI::PopUpData& _MainWindowPopUpData = *(GUI::PopUpData*)(_MainWindowData.Layout.GetUserData());

	_MainWindowPopUpData = *_MainWindowOldPopUpData;

	GUI::ReleaseUserData(_MainWindowOldPopUpData);

	GenerateDebugWindow
	(
		_MainWindowData.Layout.PushLeftPanel
		(
			GUI::_DebugWindowPopUpId,
			0, 0,
			GUI::DebugWindowMinX,
			0, 0,
			BFW::GUI::RenderingDescriptor(),
			nullptr,
			nullptr,
			true
		),
		false
	);

	GenerateNodeWindow
	(
		_MainWindowData.Layout.PushNode
		(
			BFW::GUI::_NodeWindowPopUpId,
			0, 0,
			0, 0,
			BFW::GUI::RenderingDescriptor(),
			nullptr,
			nullptr
		)
	);

	GenerateDebugWindow
	(
		_MainWindowData.Layout.GetNodes()[0].PushBottomPanel
		(
			GUI::_DebugWindowPopUpId,
			0, 0,
			GUI::DebugWindowMinY,
			0, 0,
			BFW::GUI::RenderingDescriptor(),
			nullptr,
			nullptr,
			true
		),
		false
	);

	GenerateNodeWindow
	(
		_MainWindowData.Layout.GetNodes()[0].PushNode
		(
			BFW::GUI::_NodeWindowPopUpId,
			0, 0,
			0, 0,
			BFW::GUI::RenderingDescriptor(),
			nullptr,
			nullptr
		)
	);

	GenerateDebugWindow
	(
		_MainWindowData.Layout.GetNodes()[0].GetNodes()[0].PushRightPanel
		(
			GUI::_DebugWindowPopUpId,
			0, 0,
			GUI::DebugWindowMinX,
			0, 0,
			BFW::GUI::RenderingDescriptor(),
			nullptr,
			nullptr,
			true
		),
		false
	);

	GenerateNodeWindow
	(
		_MainWindowData.Layout.GetNodes()[0].GetNodes()[0].PushNode
		(
			BFW::GUI::_NodeWindowPopUpId,
			0, 0,
			0, 0,
			BFW::GUI::RenderingDescriptor(),
			nullptr,
			nullptr
		)
	);

	GenerateDebugWindow
	(
		_MainWindowData.Layout.GetNodes()[0].GetNodes()[0].GetNodes()[0].PushTopPanel
		(
			GUI::_DebugWindowPopUpId,
			0, 0,
			GUI::DebugWindowMinY,
			0, 0,
			BFW::GUI::RenderingDescriptor(),
			nullptr,
			nullptr,
			true
		),
		false
	);

	GenerateNodeWindow
	(
		_MainWindowData.Layout.GetNodes()[0].GetNodes()[0].GetNodes()[0].PushNode
		(
			BFW::GUI::_NodeWindowPopUpId,
			0, 0,
			0, 0,
			BFW::GUI::RenderingDescriptor(),
			nullptr,
			nullptr
		)
	);

	size_t _Layer = _MainWindowData.Layout.PushPopUpLayer();

	GenerateDebugWindow
	(
		_MainWindowData.Layout.PushPopUp
		(
			_Layer, GUI::_DebugWindowPopUpId,
			0, 0,
			GUI::DebugWindowMinX, GUI::DebugWindowMinY,
			GUI::DebugWindowMinX + GUI::DebugWindowMinX / 2, GUI::DebugWindowMinY + GUI::DebugWindowMinY / 2,
			0, 0,
			BFW::GUI::RenderingDescriptor(),
			nullptr,
			nullptr,
			true
		),
		false
	);

	_Layer = _MainWindowData.Layout.PushPopUpLayer();

	GenerateDebugWindow
	(
		_MainWindowData.Layout.PushPopUp
		(
			_Layer, GUI::_DebugWindowPopUpId,
			0, 0,
			GUI::DebugWindowMinX, GUI::DebugWindowMinY,
			GUI::DebugWindowMinX * 3, GUI::DebugWindowMinY + GUI::DebugWindowMinY / 2,
			0, 0,
			BFW::GUI::RenderingDescriptor(),
			nullptr,
			nullptr,
			true
		),
		false
	);

	_MainWindowData.LayoutMutex->unlock();
}

void BFW_WINDOWS::RunTime::MainMenu::CleanUpGUI()
{
	Application& _ApplicationObj = *(Application*)(GetApplicationObj());
	BFW::GUI::Window& _MainWindow = _ApplicationObj.GetMainWindow();
	GUI::WindowData& _MainWindowData = _ApplicationObj.GetMainWindowData();
	BFW::Vector<BFW::GUI::Window*>& _ChildWindows = _ApplicationObj.GetChildWindows();
	BFW::Vector<GUI::WindowData*>& _ChildWindowsData = _ApplicationObj.GetChildWindowsData();

	_MainWindowData.LayoutMutex->lock();

	GUI::ReleaseAllChilds(_MainWindowData.Layout);

	GUI::PopUpData* _MainWindowOldPopUpData = (GUI::PopUpData*)(_MainWindowData.Layout.GetUserData());

	GenerateNodeWindow
	(
		_MainWindowData.Layout.Begin
		(
			BFW::GUI::_NodeWindowPopUpId, BFW::GUI::_NullPanelType,
			0, 0,
			_MainWindowOldPopUpData->Width, _MainWindowOldPopUpData->Height,
			0, 0,
			0, 0,
			BFW::GUI::RenderingDescriptor(),
			nullptr,
			nullptr
		)
	);

	GUI::PopUpData& _MainWindowPopUpData = *(GUI::PopUpData*)(_MainWindowData.Layout.GetUserData());

	_MainWindowPopUpData = *_MainWindowOldPopUpData;

	GUI::ReleaseUserData(_MainWindowOldPopUpData);

	_MainWindowData.LayoutMutex->unlock();

	while (_ChildWindows.GetSize())
	{
		_ApplicationObj.RemoveChildWindow(0);
	}
}

const bool BFW_WINDOWS::RunTime::MainMenu::SpawnButtonCallBack()
{
	Application& _ApplicationObj = *(Application*)(GetApplicationObj());
	BFW::GUI::Window& _MainWindow = _ApplicationObj.GetMainWindow();
	GUI::WindowData& _MainWindowData = _ApplicationObj.GetMainWindowData();
	BFW::Vector<BFW::GUI::Window*>& _ChildWindows = _ApplicationObj.GetChildWindows();
	BFW::Vector<GUI::WindowData*>& _ChildWindowsData = _ApplicationObj.GetChildWindowsData();

	POINT _Cursor = { 0 };

	if (!GetCursorPos(&_Cursor))
	{
		return false;
	}

	if (!_ApplicationObj.AddChildWindow())
	{
		return false;
	}

	if (!_ChildWindows[_ChildWindows.GetSize() - 1]->Create(NULL, BFW_WINDOWS_CHILD_WINDOW_CLASS, nullptr, WS_OVERLAPPEDWINDOW, _Cursor.x - (int32_t)(GUI::ChildWindowMinX / 2), _Cursor.y - (int32_t)(GUI::ChildWindowMinY / 2), (int32_t)(GUI::ChildWindowMinX), (int32_t)(GUI::ChildWindowMinY), _MainWindow, NULL, _ApplicationObj.GetInstanceHandle(), nullptr, NULL, GUI::ChildWindowThreadInit, GUI::ChildWindowThreadCleanUp, GUI::ChildWindowInit, GUI::ChildWindowCleanUp, _ChildWindowsData[_ChildWindowsData.GetSize() - 1]))
	{
		_ApplicationObj.RemoveChildWindow(_ChildWindows.GetSize() - 1);
		return false;
	}

	if (!_ChildWindows[_ChildWindows.GetSize() - 1]->Show(SW_SHOW))
	{
		_ApplicationObj.RemoveChildWindow(_ChildWindows.GetSize() - 1);
		return false;
	}

	_ChildWindowsData[_ChildWindowsData.GetSize() - 1]->LayoutMutex->lock();

	GUI::ReleaseAllChilds(_ChildWindowsData[_ChildWindowsData.GetSize() - 1]->Layout);

	GUI::PopUpData* _ChildWindowOldPopUpData = (GUI::PopUpData*)(_ChildWindowsData[_ChildWindowsData.GetSize() - 1]->Layout.GetUserData());

	GenerateDebugWindow
	(
		_ChildWindowsData[_ChildWindowsData.GetSize() - 1]->Layout.Begin
		(
			GUI::_DebugWindowPopUpId, BFW::GUI::_NullPanelType,
			0, 0,
			_ChildWindowOldPopUpData->Width, _ChildWindowOldPopUpData->Height,
			0, 0,
			0, 0,
			BFW::GUI::RenderingDescriptor(),
			nullptr,
			nullptr
		),
		true
	);

	GUI::PopUpData& _ChildWindowPopUpData = *(GUI::PopUpData*)(_ChildWindowsData[_ChildWindowsData.GetSize() - 1]->Layout.GetUserData());

	_ChildWindowPopUpData = *_ChildWindowOldPopUpData;

	GUI::ReleaseUserData(_ChildWindowOldPopUpData);

	_ChildWindowsData[_ChildWindowsData.GetSize() - 1]->LayoutMutex->unlock();

	return true;
}

void BFW_WINDOWS::RunTime::MainMenu::MouseCaptureInputs(BFW::GUI::Window& _Wnd, GUI::WindowData& _WndData)
{
	intptr_t _MouseX = 0, _MouseY = 0;

	if (!_Wnd.GetMousePosition(_MouseX, _MouseY))
	{
		return;
	}

	if (_Wnd.GetKeys()[BFW::Input::_MouseLKeyId].JustPressed())
	{
		_WndData.LCapture = true;
		_WndData.LayoutMutex->lock();
		_WndData.Layout.GetChildFromMouse(_MouseX, _MouseY, &_WndData.LCapturePath);
		_WndData.LayoutMutex->unlock();
		_WndData.LCaptureMouseX = _MouseX;
		_WndData.LCaptureMouseY = _MouseY;
		_WndData.LCaptureMouseXLastFrame = _MouseX;
		_WndData.LCaptureMouseYLastFrame = _MouseY;
		_WndData.LAccumulationX = 0;
		_WndData.LAccumulationY = 0;
	}

	if (_Wnd.GetKeys()[BFW::Input::_MouseMKeyId].JustPressed())
	{
		_WndData.MCapture = true;
		_WndData.LayoutMutex->lock();
		_WndData.Layout.GetChildFromMouse(_MouseX, _MouseY, &_WndData.MCapturePath);
		_WndData.LayoutMutex->unlock();
		_WndData.MCaptureMouseX = _MouseX;
		_WndData.MCaptureMouseY = _MouseY;
		_WndData.MCaptureMouseXLastFrame = _MouseX;
		_WndData.MCaptureMouseYLastFrame = _MouseY;
		_WndData.MAccumulationX = 0;
		_WndData.MAccumulationY = 0;
	}

	if (_Wnd.GetKeys()[BFW::Input::_MouseRKeyId].JustPressed())
	{
		_WndData.RCapture = true;
		_WndData.LayoutMutex->lock();
		_WndData.Layout.GetChildFromMouse(_MouseX, _MouseY, &_WndData.RCapturePath);
		_WndData.LayoutMutex->unlock();
		_WndData.RCaptureMouseX = _MouseX;
		_WndData.RCaptureMouseY = _MouseY;
		_WndData.RCaptureMouseXLastFrame = _MouseX;
		_WndData.RCaptureMouseYLastFrame = _MouseY;
		_WndData.RAccumulationX = 0;
		_WndData.RAccumulationY = 0;
	}

	if (_Wnd.GetKeys()[BFW::Input::_MouseX1KeyId].JustPressed())
	{
		_WndData.X1Capture = true;
		_WndData.LayoutMutex->lock();
		_WndData.Layout.GetChildFromMouse(_MouseX, _MouseY, &_WndData.X1CapturePath);
		_WndData.LayoutMutex->unlock();
		_WndData.X1CaptureMouseX = _MouseX;
		_WndData.X1CaptureMouseY = _MouseY;
		_WndData.X1CaptureMouseXLastFrame = _MouseX;
		_WndData.X1CaptureMouseYLastFrame = _MouseY;
		_WndData.X1AccumulationX = 0;
		_WndData.X1AccumulationY = 0;
	}

	if (_Wnd.GetKeys()[BFW::Input::_MouseX2KeyId].JustPressed())
	{
		_WndData.X2Capture = true;
		_WndData.LayoutMutex->lock();
		_WndData.Layout.GetChildFromMouse(_MouseX, _MouseY, &_WndData.X2CapturePath);
		_WndData.LayoutMutex->unlock();
		_WndData.X2CaptureMouseX = _MouseX;
		_WndData.X2CaptureMouseY = _MouseY;
		_WndData.X2CaptureMouseXLastFrame = _MouseX;
		_WndData.X2CaptureMouseYLastFrame = _MouseY;
		_WndData.X2AccumulationX = 0;
		_WndData.X2AccumulationY = 0;
	}
}

void BFW_WINDOWS::RunTime::MainMenu::DeleteMouseCaptureInputs(BFW::GUI::Window& _Wnd, GUI::WindowData& _WndData)
{
	_WndData.LCapture = false;
	_WndData.LayoutMutex->lock();
	_WndData.LCapturePath.Clear();
	_WndData.LayoutMutex->unlock();
	_WndData.LCaptureMouseX = 0;
	_WndData.LCaptureMouseY = 0;
	_WndData.LCaptureMouseXLastFrame = 0;
	_WndData.LCaptureMouseYLastFrame = 0;
	_WndData.LAccumulationX = 0;
	_WndData.LAccumulationY = 0;

	_WndData.MCapture = false;
	_WndData.LayoutMutex->lock();
	_WndData.MCapturePath.Clear();
	_WndData.LayoutMutex->unlock();
	_WndData.MCaptureMouseX = 0;
	_WndData.MCaptureMouseY = 0;
	_WndData.MCaptureMouseXLastFrame = 0;
	_WndData.MCaptureMouseYLastFrame = 0;
	_WndData.MAccumulationX = 0;
	_WndData.MAccumulationY = 0;

	_WndData.RCapture = false;
	_WndData.LayoutMutex->lock();
	_WndData.RCapturePath.Clear();
	_WndData.LayoutMutex->unlock();
	_WndData.RCaptureMouseX = 0;
	_WndData.RCaptureMouseY = 0;
	_WndData.RCaptureMouseXLastFrame = 0;
	_WndData.RCaptureMouseYLastFrame = 0;
	_WndData.RAccumulationX = 0;
	_WndData.RAccumulationY = 0;

	_WndData.X1Capture = false;
	_WndData.LayoutMutex->lock();
	_WndData.X1CapturePath.Clear();
	_WndData.LayoutMutex->unlock();
	_WndData.X1CaptureMouseX = 0;
	_WndData.X1CaptureMouseY = 0;
	_WndData.X1CaptureMouseXLastFrame = 0;
	_WndData.X1CaptureMouseYLastFrame = 0;
	_WndData.X1AccumulationX = 0;
	_WndData.X1AccumulationY = 0;

	_WndData.X2Capture = false;
	_WndData.LayoutMutex->lock();
	_WndData.X2CapturePath.Clear();
	_WndData.LayoutMutex->unlock();
	_WndData.X2CaptureMouseX = 0;
	_WndData.X2CaptureMouseY = 0;
	_WndData.X2CaptureMouseXLastFrame = 0;
	_WndData.X2CaptureMouseYLastFrame = 0;
	_WndData.X2AccumulationX = 0;
	_WndData.X2AccumulationY = 0;
}

const bool BFW_WINDOWS::RunTime::MainMenu::HandleWindowInputs(BFW::GUI::Window& _Wnd, GUI::WindowData& _WndData, const bool _IsMainWindow)
{
	Application& _ApplicationObj = *(Application*)(GetApplicationObj());

	if (_Wnd.GetKeys()[BFW::Input::_MouseLKeyId].IsPressed())
	{
		intptr_t _MouseX = 0, _MouseY = 0;

		_WndData.LayoutMutex->lock();

		if (_WndData.LCapture && BFW::GUI::PopUp::IsValidPath(_WndData.LCapturePath) && _Wnd.GetMousePosition(_MouseX, _MouseY))
		{
			intptr_t _MouseDeltaX = _MouseX - _WndData.LCaptureMouseXLastFrame;
			intptr_t _MouseDeltaY = _MouseY - _WndData.LCaptureMouseYLastFrame;

			GUI::HandleDefaultLCaptureDrag(_MouseX, _MouseY, _MouseDeltaX, _MouseDeltaY, _ApplicationObj, this, _Wnd, _WndData, _IsMainWindow);

			_WndData.LCaptureMouseXLastFrame = _MouseX;
			_WndData.LCaptureMouseYLastFrame = _MouseY;
		}

		_WndData.LayoutMutex->unlock();
	}

	if (_Wnd.GetKeys()[BFW::Input::_MouseMKeyId].IsPressed())
	{
		intptr_t _MouseX = 0, _MouseY = 0;

		_WndData.LayoutMutex->lock();

		if (_WndData.MCapture && BFW::GUI::PopUp::IsValidPath(_WndData.MCapturePath) && _Wnd.GetMousePosition(_MouseX, _MouseY))
		{
			intptr_t _MouseDeltaX = _MouseX - _WndData.MCaptureMouseXLastFrame;
			intptr_t _MouseDeltaY = _MouseY - _WndData.MCaptureMouseYLastFrame;

			GUI::HandleDefaultMCaptureDrag(_MouseX, _MouseY, _MouseDeltaX, _MouseDeltaY, _ApplicationObj, this, _Wnd, _WndData, _IsMainWindow);

			_WndData.MCaptureMouseXLastFrame = _MouseX;
			_WndData.MCaptureMouseYLastFrame = _MouseY;
		}

		_WndData.LayoutMutex->unlock();
	}

	if (_Wnd.GetKeys()[BFW::Input::_MouseRKeyId].IsPressed())
	{
		intptr_t _MouseX = 0, _MouseY = 0;

		_WndData.LayoutMutex->lock();

		if (_WndData.RCapture && BFW::GUI::PopUp::IsValidPath(_WndData.RCapturePath) && _Wnd.GetMousePosition(_MouseX, _MouseY))
		{
			intptr_t _MouseDeltaX = _MouseX - _WndData.RCaptureMouseXLastFrame;
			intptr_t _MouseDeltaY = _MouseY - _WndData.RCaptureMouseYLastFrame;

			GUI::HandleDefaultRCaptureDrag(_MouseX, _MouseY, _MouseDeltaX, _MouseDeltaY, _ApplicationObj, this, _Wnd, _WndData, _IsMainWindow);

			_WndData.RCaptureMouseXLastFrame = _MouseX;
			_WndData.RCaptureMouseYLastFrame = _MouseY;
		}

		_WndData.LayoutMutex->unlock();
	}

	if (_Wnd.GetKeys()[BFW::Input::_MouseX1KeyId].IsPressed())
	{
		intptr_t _MouseX = 0, _MouseY = 0;

		_WndData.LayoutMutex->lock();

		if (_WndData.X1Capture && BFW::GUI::PopUp::IsValidPath(_WndData.X1CapturePath) && _Wnd.GetMousePosition(_MouseX, _MouseY))
		{
			intptr_t _MouseDeltaX = _MouseX - _WndData.X1CaptureMouseXLastFrame;
			intptr_t _MouseDeltaY = _MouseY - _WndData.X1CaptureMouseYLastFrame;

			GUI::HandleDefaultX1CaptureDrag(_MouseX, _MouseY, _MouseDeltaX, _MouseDeltaY, _ApplicationObj, this, _Wnd, _WndData, _IsMainWindow);

			_WndData.X1CaptureMouseXLastFrame = _MouseX;
			_WndData.X1CaptureMouseYLastFrame = _MouseY;
		}

		_WndData.LayoutMutex->unlock();
	}

	if (_Wnd.GetKeys()[BFW::Input::_MouseX2KeyId].IsPressed())
	{
		intptr_t _MouseX = 0, _MouseY = 0;

		_WndData.LayoutMutex->lock();

		if (_WndData.X2Capture && BFW::GUI::PopUp::IsValidPath(_WndData.X2CapturePath) && _Wnd.GetMousePosition(_MouseX, _MouseY))
		{
			intptr_t _MouseDeltaX = _MouseX - _WndData.X2CaptureMouseXLastFrame;
			intptr_t _MouseDeltaY = _MouseY - _WndData.X2CaptureMouseYLastFrame;

			GUI::HandleDefaultX2CaptureDrag(_MouseX, _MouseY, _MouseDeltaX, _MouseDeltaY, _ApplicationObj, this, _Wnd, _WndData, _IsMainWindow);

			_WndData.X2CaptureMouseXLastFrame = _MouseX;
			_WndData.X2CaptureMouseYLastFrame = _MouseY;
		}

		_WndData.LayoutMutex->unlock();
	}

	if (_Wnd.GetKeys()[BFW::Input::_MouseLKeyId].JustReleased())
	{
		intptr_t _MouseX = 0, _MouseY = 0;

		_WndData.LayoutMutex->lock();

		if (_WndData.LCapture && BFW::GUI::PopUp::IsValidPath(_WndData.LCapturePath) && _Wnd.GetMousePosition(_MouseX, _MouseY))
		{
			intptr_t _MouseDeltaX = _MouseX - _WndData.LCaptureMouseXLastFrame;
			intptr_t _MouseDeltaY = _MouseY - _WndData.LCaptureMouseYLastFrame;

			BFW::GUI::SafePopUpPointer _ReleasePopUp = _WndData.Layout.GetChildFromMouse(_MouseX, _MouseY);

			if ((BFW::GUI::PopUp*)(_ReleasePopUp) && _WndData.LCapturePath.GetSize() && (BFW::GUI::PopUp*)(_ReleasePopUp) == (BFW::GUI::PopUp*)(_WndData.LCapturePath[0]))
			{
				switch (_ReleasePopUp->GetId())
				{
				case GUI::_SpawnButtonPopUpId:
				{
					SpawnButtonCallBack();
					break;
				}
				default:
				{
					break;
				}
				}
			}
		}

		_WndData.LayoutMutex->unlock();

		_WndData.LCapture = false;
		_WndData.LayoutMutex->lock();
		_WndData.LCapturePath.Clear();
		_WndData.LayoutMutex->unlock();
		_WndData.LCaptureMouseX = 0;
		_WndData.LCaptureMouseY = 0;
		_WndData.LCaptureMouseXLastFrame = 0;
		_WndData.LCaptureMouseYLastFrame = 0;
		_WndData.LAccumulationX = 0;
		_WndData.LAccumulationY = 0;
	}

	if (_Wnd.GetKeys()[BFW::Input::_MouseMKeyId].JustReleased())
	{
		intptr_t _MouseX = 0, _MouseY = 0;

		_WndData.LayoutMutex->lock();

		if (_WndData.MCapture && BFW::GUI::PopUp::IsValidPath(_WndData.MCapturePath) && _Wnd.GetMousePosition(_MouseX, _MouseY))
		{
			intptr_t _MouseDeltaX = _MouseX - _WndData.MCaptureMouseXLastFrame;
			intptr_t _MouseDeltaY = _MouseY - _WndData.MCaptureMouseYLastFrame;
		}

		_WndData.LayoutMutex->unlock();

		_WndData.MCapture = false;
		_WndData.LayoutMutex->lock();
		_WndData.MCapturePath.Clear();
		_WndData.LayoutMutex->unlock();
		_WndData.MCaptureMouseX = 0;
		_WndData.MCaptureMouseY = 0;
		_WndData.MCaptureMouseXLastFrame = 0;
		_WndData.MCaptureMouseYLastFrame = 0;
		_WndData.MAccumulationX = 0;
		_WndData.MAccumulationY = 0;
	}

	if (_Wnd.GetKeys()[BFW::Input::_MouseRKeyId].JustReleased())
	{
		intptr_t _MouseX = 0, _MouseY = 0;

		_WndData.LayoutMutex->lock();

		if (_WndData.RCapture && BFW::GUI::PopUp::IsValidPath(_WndData.RCapturePath) && _Wnd.GetMousePosition(_MouseX, _MouseY))
		{
			intptr_t _MouseDeltaX = _MouseX - _WndData.RCaptureMouseXLastFrame;
			intptr_t _MouseDeltaY = _MouseY - _WndData.RCaptureMouseYLastFrame;
		}

		_WndData.LayoutMutex->unlock();

		_WndData.RCapture = false;
		_WndData.LayoutMutex->lock();
		_WndData.RCapturePath.Clear();
		_WndData.LayoutMutex->unlock();
		_WndData.RCaptureMouseX = 0;
		_WndData.RCaptureMouseY = 0;
		_WndData.RCaptureMouseXLastFrame = 0;
		_WndData.RCaptureMouseYLastFrame = 0;
		_WndData.RAccumulationX = 0;
		_WndData.RAccumulationY = 0;
	}

	if (_Wnd.GetKeys()[BFW::Input::_MouseX1KeyId].JustReleased())
	{
		intptr_t _MouseX = 0, _MouseY = 0;

		_WndData.LayoutMutex->lock();

		if (_WndData.X1Capture && BFW::GUI::PopUp::IsValidPath(_WndData.X1CapturePath) && _Wnd.GetMousePosition(_MouseX, _MouseY))
		{
			intptr_t _MouseDeltaX = _MouseX - _WndData.X1CaptureMouseXLastFrame;
			intptr_t _MouseDeltaY = _MouseY - _WndData.X1CaptureMouseYLastFrame;
		}

		_WndData.LayoutMutex->unlock();

		_WndData.X1Capture = false;
		_WndData.LayoutMutex->lock();
		_WndData.X1CapturePath.Clear();
		_WndData.LayoutMutex->unlock();
		_WndData.X1CaptureMouseX = 0;
		_WndData.X1CaptureMouseY = 0;
		_WndData.X1CaptureMouseXLastFrame = 0;
		_WndData.X1CaptureMouseYLastFrame = 0;
		_WndData.X1AccumulationX = 0;
		_WndData.X1AccumulationY = 0;
	}

	if (_Wnd.GetKeys()[BFW::Input::_MouseX2KeyId].JustReleased())
	{
		intptr_t _MouseX = 0, _MouseY = 0;

		_WndData.LayoutMutex->lock();

		if (_WndData.X2Capture && BFW::GUI::PopUp::IsValidPath(_WndData.X2CapturePath) && _Wnd.GetMousePosition(_MouseX, _MouseY))
		{
			intptr_t _MouseDeltaX = _MouseX - _WndData.X2CaptureMouseXLastFrame;
			intptr_t _MouseDeltaY = _MouseY - _WndData.X2CaptureMouseYLastFrame;
		}

		_WndData.LayoutMutex->unlock();

		_WndData.X2Capture = false;
		_WndData.LayoutMutex->lock();
		_WndData.X2CapturePath.Clear();
		_WndData.LayoutMutex->unlock();
		_WndData.X2CaptureMouseX = 0;
		_WndData.X2CaptureMouseY = 0;
		_WndData.X2CaptureMouseXLastFrame = 0;
		_WndData.X2CaptureMouseYLastFrame = 0;
		_WndData.X2AccumulationX = 0;
		_WndData.X2AccumulationY = 0;
	}

	BFW::Vector<BFW::Input::WheelEvent> _WheelEventsX = _Wnd.GetHorizontalWheelEvents();

	for (size_t _Index = 0; _Index < _WheelEventsX.GetSize(); _Index++)
	{
		BFW::Vector<BFW::GUI::SafePopUpPointer> _Path;

		_WndData.LayoutMutex->lock();
		_WndData.Layout.GetChildFromMouse(_WheelEventsX[_Index].X, _WheelEventsX[_Index].Y, &_Path);
		GUI::HandleDefaultHWheelEvent(_WheelEventsX[_Index], _Path, _ApplicationObj, this, _Wnd, _WndData, _IsMainWindow);
		_WndData.LayoutMutex->unlock();
	}

	BFW::Vector<BFW::Input::WheelEvent> _WheelEventsY = _Wnd.GetWheelEvents();

	for (size_t _Index = 0; _Index < _WheelEventsY.GetSize(); _Index++)
	{
		BFW::Vector<BFW::GUI::SafePopUpPointer> _Path;

		_WndData.LayoutMutex->lock();
		_WndData.Layout.GetChildFromMouse(_WheelEventsY[_Index].X, _WheelEventsY[_Index].Y, &_Path);
		GUI::HandleDefaultVWheelEvent(_WheelEventsY[_Index], _Path, _ApplicationObj, this, _Wnd, _WndData, _IsMainWindow);
		_WndData.LayoutMutex->unlock();
	}

	_WndData.LayoutMutex->lock();
	GUI::HandleDefaultKeys(_ApplicationObj, this, _Wnd, _WndData, _IsMainWindow);
	_WndData.LayoutMutex->unlock();

	_WndData.LayoutMutex->lock();
	GUI::HandleDefaultControllers(_ApplicationObj, this, _Wnd, _WndData, _IsMainWindow);
	_WndData.LayoutMutex->unlock();

	if (_Wnd.ShouldClose())
	{
		_Wnd.CleanEvents();
		return false;
	}

	_Wnd.CleanEvents();
	return true;
}

void BFW_WINDOWS::RunTime::MainMenu::Input()
{
	BFW_PROFILE_FUNCTION();

	Application& _ApplicationObj = *(Application*)(GetApplicationObj());
	BFW::GUI::Window& _MainWindow = _ApplicationObj.GetMainWindow();
	GUI::WindowData& _MainWindowData = _ApplicationObj.GetMainWindowData();
	BFW::Vector<BFW::GUI::Window*>& _ChildWindows = _ApplicationObj.GetChildWindows();
	BFW::Vector<GUI::WindowData*>& _ChildWindowsData = _ApplicationObj.GetChildWindowsData();

	_MainWindow.UpdateInputState();
	MouseCaptureInputs(_MainWindow, _MainWindowData);

	for (size_t _Index = 0; _Index < _ChildWindows.GetSize(); _Index++)
	{
		_ChildWindows[_Index]->UpdateInputState();
		MouseCaptureInputs(*_ChildWindows[_Index], *_ChildWindowsData[_Index]);
	}

	_ApplicationObj.GetController(0).UpdateState(0);
	_ApplicationObj.GetController(1).UpdateState(1);
	_ApplicationObj.GetController(2).UpdateState(2);
	_ApplicationObj.GetController(3).UpdateState(3);

	bool _Focus = false;

	if (_MainWindow.HasFocus())
	{
		_Focus = true;
	}
	else
	{
		DeleteMouseCaptureInputs(_MainWindow, _MainWindowData);
	}

	for (size_t _Index = 0; _Index < _ChildWindows.GetSize(); _Index++)
	{
		if (_ChildWindows[_Index]->HasFocus())
		{
			_Focus = true;
		}
		else
		{
			DeleteMouseCaptureInputs(*_ChildWindows[_Index], *_ChildWindowsData[_Index]);
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

	_ApplicationObj.GetController(0).CleanState();
	_ApplicationObj.GetController(1).CleanState();
	_ApplicationObj.GetController(2).CleanState();
	_ApplicationObj.GetController(3).CleanState();
}

void BFW_WINDOWS::RunTime::MainMenu::Engine()
{
	BFW_PROFILE_FUNCTION();

	Application& _ApplicationObj = *(Application*)(GetApplicationObj());
	BFW::GUI::Window& _MainWindow = _ApplicationObj.GetMainWindow();
	GUI::WindowData& _MainWindowData = _ApplicationObj.GetMainWindowData();
	BFW::Vector<BFW::GUI::Window*>& _ChildWindows = _ApplicationObj.GetChildWindows();
	BFW::Vector<GUI::WindowData*>& _ChildWindowsData = _ApplicationObj.GetChildWindowsData();

	if (!HandleWindowInputs(_MainWindow, _MainWindowData, true))
	{
		_ApplicationObj.Close(BFW::MultiProcessing::_NoErrorReturnValue);
	}

	for (size_t _Index = 0; _Index < _ChildWindows.GetSize(); _Index++)
	{
		if (!HandleWindowInputs(*_ChildWindows[_Index], *_ChildWindowsData[_Index], false))
		{
			_ApplicationObj.RemoveChildWindow(_Index);
			_Index--;
		}
	}

	uint64_t _Sync = _MainWindow.GetRefreshRate();

	for (size_t _Index = 0; _Index < _ChildWindows.GetSize(); _Index++)
	{
		uint64_t _LocalSync = _ChildWindows[_Index]->GetRefreshRate();

		if (_LocalSync > _Sync)
		{
			_Sync = _LocalSync;
		}
	}

	SetSync(_Sync);
}

void BFW_WINDOWS::RunTime::MainMenu::FrameBuild()
{
	BFW_PROFILE_FUNCTION();

	Application& _ApplicationObj = *(Application*)(GetApplicationObj());
	BFW::GUI::Window& _MainWindow = _ApplicationObj.GetMainWindow();
	GUI::WindowData& _MainWindowData = _ApplicationObj.GetMainWindowData();
	BFW::Vector<BFW::GUI::Window*>& _ChildWindows = _ApplicationObj.GetChildWindows();
	BFW::Vector<GUI::WindowData*>& _ChildWindowsData = _ApplicationObj.GetChildWindowsData();

	GUI::RenderWindow(_ApplicationObj, this, _MainWindow, _MainWindowData, true);

	for (size_t _Index = 0; _Index < _ChildWindows.GetSize(); _Index++)
	{
		GUI::RenderWindow(_ApplicationObj, this, *_ChildWindows[_Index], *_ChildWindowsData[_Index], false);
	}
}
