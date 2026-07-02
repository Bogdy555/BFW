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
	BFW::Vector<BFW::GUI::Window*>& _ChildWindows = _ApplicationObj.GetChildWindows();
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
		_ChildWindows[_Index]->CleanInputState();
		_ChildWindows[_Index]->CleanEvents();
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
	for (size_t _Index = 0; _Index < _ChildWindows.GetSize(); _Index++)
	{
		_ChildWindows[_Index]->CleanInputState();
		_ChildWindows[_Index]->CleanEvents();
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
	BFW::Vector<BFW::GUI::Window*>& _ChildWindows = _ApplicationObj.GetChildWindows();
	BFW::Vector<GUI::WindowData*>& _ChildWindowsData = _ApplicationObj.GetChildWindowsData();

	_MainWindowData.LayoutMutex->lock();

	size_t _WndWidth = 0, _WndHeight = 0;

	_MainWindow.GetClientSize(_WndWidth, _WndHeight);

	GUI::PopUpData& _MainWindowPopUpData = *(GUI::PopUpData*)(_MainWindowData.Layout.GetUserData());

	if (_WndWidth == 0 || _WndHeight == 0)
	{
		_WndWidth = _MainWindowPopUpData.Width;
		_WndHeight = _MainWindowPopUpData.Height;
	}

	_MainWindowData.Layout.Begin
	(
		BFW::GUI::_NodePopUpId, BFW::GUI::_NullPanelType,
		0, 0,
		_WndHeight, _WndWidth,
		0, 0,
		0, 0,
		GUI::SetupRenderData, GUI::CleanUpRenderData,
		GUI::RenderGray25, nullptr, nullptr,
		GUI::Composit,
		_MainWindowData.Layout.GetUserData()
	);

	GUI::GenerateDebugWindow
	(
		_MainWindowData.Layout.PushLeftPanel
		(
			GUI::_DebugWindowPopUpId,
			GUI::DebugWindowMinX, GUI::DebugWindowMinY,
			GUI::DebugWindowMinX,
			0, 0,
			GUI::SetupRenderData, GUI::CleanUpRenderData,
			GUI::RenderGray30, nullptr, nullptr,
			GUI::Composit,
			nullptr,
			true
		),
		this,
		false
	);

	_MainWindowData.Layout.PushNode
	(
		BFW::GUI::_NodePopUpId,
		0, 0,
		0, 0,
		GUI::SetupRenderData, GUI::CleanUpRenderData,
		GUI::RenderGray25, nullptr, nullptr,
		GUI::Composit,
		nullptr
	);

	GUI::GenerateDebugWindow
	(
		_MainWindowData.Layout.GetNodes()[0].PushBottomPanel
		(
			GUI::_DebugWindowPopUpId,
			GUI::DebugWindowMinX, GUI::DebugWindowMinY,
			GUI::DebugWindowMinY,
			0, 0,
			GUI::SetupRenderData, GUI::CleanUpRenderData,
			GUI::RenderGray30, nullptr, nullptr,
			GUI::Composit,
			nullptr,
			true
		),
		this,
		false
	);

	_MainWindowData.Layout.GetNodes()[0].PushNode
	(
		BFW::GUI::_NodePopUpId,
		0, 0,
		0, 0,
		GUI::SetupRenderData, GUI::CleanUpRenderData,
		GUI::RenderGray25, nullptr, nullptr,
		GUI::Composit,
		nullptr
	);

	GUI::GenerateDebugWindow
	(
		_MainWindowData.Layout.GetNodes()[0].GetNodes()[0].PushRightPanel
		(
			GUI::_DebugWindowPopUpId,
			GUI::DebugWindowMinX, GUI::DebugWindowMinY,
			GUI::DebugWindowMinX,
			0, 0,
			GUI::SetupRenderData, GUI::CleanUpRenderData,
			GUI::RenderGray30, nullptr, nullptr,
			GUI::Composit,
			nullptr,
			true
		),
		this,
		false
	);

	_MainWindowData.Layout.GetNodes()[0].GetNodes()[0].PushNode
	(
		BFW::GUI::_NodePopUpId,
		0, 0,
		0, 0,
		GUI::SetupRenderData, GUI::CleanUpRenderData,
		GUI::RenderGray25, nullptr, nullptr,
		GUI::Composit,
		nullptr
	);

	GUI::GenerateDebugWindow
	(
		_MainWindowData.Layout.GetNodes()[0].GetNodes()[0].GetNodes()[0].PushTopPanel
		(
			GUI::_DebugWindowPopUpId,
			GUI::DebugWindowMinX, GUI::DebugWindowMinY,
			GUI::DebugWindowMinY,
			0, 0,
			GUI::SetupRenderData, GUI::CleanUpRenderData,
			GUI::RenderGray30, nullptr, nullptr,
			GUI::Composit,
			nullptr,
			true
		),
		this,
		false
	);

	size_t _Layer = _MainWindowData.Layout.PushPopUpLayer();

	GUI::GenerateDebugWindow
	(
		_MainWindowData.Layout.PushPopUp
		(
			_Layer, GUI::_DebugWindowPopUpId,
			GUI::DebugWindowMinX, GUI::DebugWindowMinY,
			GUI::DebugWindowMinX, GUI::DebugWindowMinY,
			GUI::DebugWindowMinX * 2, GUI::DebugWindowMinY * 2,
			0, 0,
			GUI::SetupRenderData, GUI::CleanUpRenderData,
			GUI::RenderGray30, nullptr, nullptr,
			GUI::Composit,
			nullptr,
			true
		),
		this,
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

	GUI::PopUpData& _MainWindowPopUpData = *(GUI::PopUpData*)(_MainWindowData.Layout.GetUserData());

	_MainWindowData.Layout.Begin
	(
		BFW::GUI::_NodePopUpId, BFW::GUI::_NullPanelType,
		0, 0,
		_MainWindowPopUpData.Width, _MainWindowPopUpData.Height,
		0, 0,
		0, 0,
		nullptr, nullptr,
		nullptr, nullptr, nullptr,
		nullptr,
		_MainWindowData.Layout.GetUserData()
	);

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

	if (!_ChildWindows[_ChildWindows.GetSize() - 1]->Create(NULL, BFW_WINDOWS_CHILD_WINDOW_CLASS, nullptr, WS_POPUP, _Cursor.x - (int32_t)(GUI::ChildWindowMinX / 2), _Cursor.y - (int32_t)(GUI::ChildWindowMinY / 2), (int32_t)(GUI::ChildWindowMinX), (int32_t)(GUI::ChildWindowMinY), _MainWindow, NULL, _ApplicationObj.GetInstanceHandle(), nullptr, NULL, GUI::ChildWindowThreadInit, GUI::ChildWindowThreadCleanUp, GUI::ChildWindowInit, GUI::ChildWindowCleanUp, _ChildWindowsData[_ChildWindowsData.GetSize() - 1]))
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

	GUI::GenerateDebugWindow
	(
		_ChildWindowsData[_ChildWindowsData.GetSize() - 1]->Layout.Begin
		(
			GUI::_DebugWindowPopUpId, BFW::GUI::_NullPanelType,
			GUI::DebugWindowMinX, GUI::DebugWindowMinY,
			GUI::ChildWindowMinX, GUI::ChildWindowMinY,
			0, 0,
			0, 0,
			GUI::SetupRenderData, GUI::CleanUpRenderData,
			GUI::RenderGray30, nullptr, nullptr,
			GUI::Composit,
			_ChildWindowsData[_ChildWindowsData.GetSize() - 1]->Layout.GetUserData()
		),
		this,
		true
	);

	_ChildWindowsData[_ChildWindowsData.GetSize() - 1]->LayoutMutex->unlock();

	return true;
}

void BFW_WINDOWS::RunTime::MainMenu::MouseCaptureResize(BFW::GUI::Window& _Wnd, GUI::WindowData& _WndData, const uint64_t _ResizePopUpId, const intptr_t _MouseDeltaX, const intptr_t _MouseDeltaY)
{
	bool _IsPanel = false;

	for (size_t _Index = 0; _Index < _WndData.LCapturePath[2]->GetPanels().GetSize(); _Index++)
	{
		if (_WndData.LCapturePath[1] == &_WndData.LCapturePath[2]->GetPanels()[_Index])
		{
			_IsPanel = true;
		}
	}

	if (_IsPanel)
	{
		for (size_t _Index = 0; _Index < _WndData.LCapturePath[2]->GetPanels().GetSize(); _Index++)
		{
			switch (_WndData.LCapturePath[2]->GetPanels()[_Index].GetId())
			{
			case GUI::_DebugWindowPopUpId:
			{
				switch (_ResizePopUpId)
				{
				case GUI::_LeftResizePopUpId:
				{
					intptr_t _TrueMouseDeltaX = _MouseDeltaX;

					if (_MouseDeltaX > 0)
					{
						_TrueMouseDeltaX = (_WndData.ResizeAccumulationX + _MouseDeltaX) * (-_WndData.ResizeAccumulationX < _MouseDeltaX);
						_WndData.ResizeAccumulationX = (_WndData.ResizeAccumulationX + _MouseDeltaX) * (-_WndData.ResizeAccumulationX > _MouseDeltaX);
					}

					if (_TrueMouseDeltaX > 0 && (_WndData.LCapturePath[2]->GetPanels()[_Index].GetWidth() - GUI::ResizeSize) * (_WndData.LCapturePath[2]->GetPanels()[_Index].GetWidth() > GUI::ResizeSize) < (size_t)(_TrueMouseDeltaX))
					{
						intptr_t _OldMouseDeltaX = _TrueMouseDeltaX;
						_TrueMouseDeltaX = (_WndData.LCapturePath[2]->GetPanels()[_Index].GetWidth() - GUI::ResizeSize) * (_WndData.LCapturePath[2]->GetPanels()[_Index].GetWidth() > GUI::ResizeSize);
						_WndData.ResizeAccumulationX += _OldMouseDeltaX - _TrueMouseDeltaX;
					}

					if (_MouseDeltaX < 0)
					{
						_TrueMouseDeltaX = (_WndData.ResizeAccumulationX + _MouseDeltaX) * (_WndData.ResizeAccumulationX < -_MouseDeltaX);
						_WndData.ResizeAccumulationX = (_WndData.ResizeAccumulationX + _MouseDeltaX) * (_WndData.ResizeAccumulationX > -_MouseDeltaX);
					}

					if (_TrueMouseDeltaX < 0 && (_WndData.LCapturePath[2]->GetWidth() - _WndData.LCapturePath[2]->GetPanels()[_Index].GetWidth()) * (_WndData.LCapturePath[2]->GetWidth() > _WndData.LCapturePath[2]->GetPanels()[_Index].GetWidth()) < (size_t)(-_TrueMouseDeltaX))
					{
						intptr_t _OldMouseDeltaX = _TrueMouseDeltaX;
						_TrueMouseDeltaX = -(intptr_t)((_WndData.LCapturePath[2]->GetWidth() - _WndData.LCapturePath[2]->GetPanels()[_Index].GetWidth()) * (_WndData.LCapturePath[2]->GetWidth() > _WndData.LCapturePath[2]->GetPanels()[_Index].GetWidth()));
						_WndData.ResizeAccumulationX += _OldMouseDeltaX - _TrueMouseDeltaX;
					}

					_WndData.LCapturePath[2]->GetPanels()[_Index].SetWidth(_WndData.LCapturePath[2]->GetPanels()[_Index].GetWidth() - _TrueMouseDeltaX);
					_WndData.LCapturePath[2]->GetPanels()[_Index].SetTrueWidth(GUI::DebugWindowMinX);
					_WndData.LCapturePath[2]->GetPanels()[_Index].SetPositionX(_WndData.LCapturePath[2]->GetPanels()[_Index].GetPositionX() + _TrueMouseDeltaX);

					break;
				}
				case GUI::_RightResizePopUpId:
				{
					intptr_t _TrueMouseDeltaX = _MouseDeltaX;

					if (_MouseDeltaX < 0)
					{
						_TrueMouseDeltaX = (_WndData.ResizeAccumulationX + _MouseDeltaX) * (_WndData.ResizeAccumulationX < -_MouseDeltaX);
						_WndData.ResizeAccumulationX = (_WndData.ResizeAccumulationX + _MouseDeltaX) * (_WndData.ResizeAccumulationX > -_MouseDeltaX);
					}

					if (_TrueMouseDeltaX < 0 && (_WndData.LCapturePath[2]->GetPanels()[_Index].GetWidth() - GUI::ResizeSize) * (_WndData.LCapturePath[2]->GetPanels()[_Index].GetWidth() > GUI::ResizeSize) < (size_t)(-_TrueMouseDeltaX))
					{
						intptr_t _OldMouseDeltaX = _TrueMouseDeltaX;
						_TrueMouseDeltaX = -(intptr_t)((_WndData.LCapturePath[2]->GetPanels()[_Index].GetWidth() - GUI::ResizeSize) * (_WndData.LCapturePath[2]->GetPanels()[_Index].GetWidth() > GUI::ResizeSize));
						_WndData.ResizeAccumulationX += _OldMouseDeltaX - _TrueMouseDeltaX;
					}

					if (_MouseDeltaX > 0)
					{
						_TrueMouseDeltaX = (_WndData.ResizeAccumulationX + _MouseDeltaX) * (-_WndData.ResizeAccumulationX < _MouseDeltaX);
						_WndData.ResizeAccumulationX = (_WndData.ResizeAccumulationX + _MouseDeltaX) * (-_WndData.ResizeAccumulationX > _MouseDeltaX);
					}

					if (_TrueMouseDeltaX > 0 && (_WndData.LCapturePath[2]->GetWidth() - _WndData.LCapturePath[2]->GetPanels()[_Index].GetWidth()) * (_WndData.LCapturePath[2]->GetWidth() > _WndData.LCapturePath[2]->GetPanels()[_Index].GetWidth()) < (size_t)(_TrueMouseDeltaX))
					{
						intptr_t _OldMouseDeltaX = _TrueMouseDeltaX;
						_TrueMouseDeltaX = (_WndData.LCapturePath[2]->GetWidth() - _WndData.LCapturePath[2]->GetPanels()[_Index].GetWidth()) * (_WndData.LCapturePath[2]->GetWidth() > _WndData.LCapturePath[2]->GetPanels()[_Index].GetWidth());
						_WndData.ResizeAccumulationX += _OldMouseDeltaX - _TrueMouseDeltaX;
					}

					_WndData.LCapturePath[2]->GetPanels()[_Index].SetWidth(_WndData.LCapturePath[2]->GetPanels()[_Index].GetWidth() + _TrueMouseDeltaX);
					_WndData.LCapturePath[2]->GetPanels()[_Index].SetTrueWidth(GUI::DebugWindowMinX);

					break;
				}
				case GUI::_TopResizePopUpId:
				{
					intptr_t _TrueMouseDeltaY = _MouseDeltaY;

					if (_MouseDeltaY > 0)
					{
						_TrueMouseDeltaY = (_WndData.ResizeAccumulationY + _MouseDeltaY) * (-_WndData.ResizeAccumulationY < _MouseDeltaY);
						_WndData.ResizeAccumulationY = (_WndData.ResizeAccumulationY + _MouseDeltaY) * (-_WndData.ResizeAccumulationY > _MouseDeltaY);
					}

					if (_TrueMouseDeltaY > 0 && (_WndData.LCapturePath[2]->GetPanels()[_Index].GetHeight() - GUI::ResizeSize) * (_WndData.LCapturePath[2]->GetPanels()[_Index].GetHeight() > GUI::ResizeSize) < (size_t)(_TrueMouseDeltaY))
					{
						intptr_t _OldMouseDeltaY = _TrueMouseDeltaY;
						_TrueMouseDeltaY = (_WndData.LCapturePath[2]->GetPanels()[_Index].GetHeight() - GUI::ResizeSize) * (_WndData.LCapturePath[2]->GetPanels()[_Index].GetHeight() > GUI::ResizeSize);
						_WndData.ResizeAccumulationY += _OldMouseDeltaY - _TrueMouseDeltaY;
					}

					if (_MouseDeltaY < 0)
					{
						_TrueMouseDeltaY = (_WndData.ResizeAccumulationY + _MouseDeltaY) * (_WndData.ResizeAccumulationY < -_MouseDeltaY);
						_WndData.ResizeAccumulationY = (_WndData.ResizeAccumulationY + _MouseDeltaY) * (_WndData.ResizeAccumulationY > -_MouseDeltaY);
					}

					if (_TrueMouseDeltaY < 0 && (_WndData.LCapturePath[2]->GetHeight() - _WndData.LCapturePath[2]->GetPanels()[_Index].GetHeight()) * (_WndData.LCapturePath[2]->GetHeight() > _WndData.LCapturePath[2]->GetPanels()[_Index].GetHeight()) < (size_t)(-_TrueMouseDeltaY))
					{
						intptr_t _OldMouseDeltaY = _TrueMouseDeltaY;
						_TrueMouseDeltaY = -(intptr_t)((_WndData.LCapturePath[2]->GetHeight() - _WndData.LCapturePath[2]->GetPanels()[_Index].GetHeight()) * (_WndData.LCapturePath[2]->GetHeight() > _WndData.LCapturePath[2]->GetPanels()[_Index].GetHeight()));
						_WndData.ResizeAccumulationY += _OldMouseDeltaY - _TrueMouseDeltaY;
					}

					_WndData.LCapturePath[2]->GetPanels()[_Index].SetHeight(_WndData.LCapturePath[2]->GetPanels()[_Index].GetHeight() - _TrueMouseDeltaY);
					_WndData.LCapturePath[2]->GetPanels()[_Index].SetTrueHeight(GUI::DebugWindowMinY);
					_WndData.LCapturePath[2]->GetPanels()[_Index].SetPositionY(_WndData.LCapturePath[2]->GetPanels()[_Index].GetPositionY() + _TrueMouseDeltaY);

					break;
				}
				case GUI::_BottomResizePopUpId:
				{
					intptr_t _TrueMouseDeltaY = _MouseDeltaY;

					if (_MouseDeltaY < 0)
					{
						_TrueMouseDeltaY = (_WndData.ResizeAccumulationY + _MouseDeltaY) * (_WndData.ResizeAccumulationY < -_MouseDeltaY);
						_WndData.ResizeAccumulationY = (_WndData.ResizeAccumulationY + _MouseDeltaY) * (_WndData.ResizeAccumulationY > -_MouseDeltaY);
					}

					if (_TrueMouseDeltaY < 0 && (_WndData.LCapturePath[2]->GetPanels()[_Index].GetHeight() - GUI::ResizeSize) * (_WndData.LCapturePath[2]->GetPanels()[_Index].GetHeight() > GUI::ResizeSize) < (size_t)(-_TrueMouseDeltaY))
					{
						intptr_t _OldMouseDeltaY = _TrueMouseDeltaY;
						_TrueMouseDeltaY = -(intptr_t)((_WndData.LCapturePath[2]->GetPanels()[_Index].GetHeight() - GUI::ResizeSize) * (_WndData.LCapturePath[2]->GetPanels()[_Index].GetHeight() > GUI::ResizeSize));
						_WndData.ResizeAccumulationY += _OldMouseDeltaY - _TrueMouseDeltaY;
					}

					if (_MouseDeltaY > 0)
					{
						_TrueMouseDeltaY = (_WndData.ResizeAccumulationY + _MouseDeltaY) * (-_WndData.ResizeAccumulationY < _MouseDeltaY);
						_WndData.ResizeAccumulationY = (_WndData.ResizeAccumulationY + _MouseDeltaY) * (-_WndData.ResizeAccumulationY > _MouseDeltaY);
					}

					if (_TrueMouseDeltaY > 0 && (_WndData.LCapturePath[2]->GetHeight() - _WndData.LCapturePath[2]->GetPanels()[_Index].GetHeight()) * (_WndData.LCapturePath[2]->GetHeight() > _WndData.LCapturePath[2]->GetPanels()[_Index].GetHeight()) < (size_t)(_TrueMouseDeltaY))
					{
						intptr_t _OldMouseDeltaY = _TrueMouseDeltaY;
						_TrueMouseDeltaY = (_WndData.LCapturePath[2]->GetHeight() - _WndData.LCapturePath[2]->GetPanels()[_Index].GetHeight()) * (_WndData.LCapturePath[2]->GetHeight() > _WndData.LCapturePath[2]->GetPanels()[_Index].GetHeight());
						_WndData.ResizeAccumulationY += _OldMouseDeltaY - _TrueMouseDeltaY;
					}

					_WndData.LCapturePath[2]->GetPanels()[_Index].SetHeight(_WndData.LCapturePath[2]->GetPanels()[_Index].GetHeight() + _TrueMouseDeltaY);
					_WndData.LCapturePath[2]->GetPanels()[_Index].SetTrueHeight(GUI::DebugWindowMinY);

					break;
				}
				case GUI::_LeftTopResizePopUpId:
				{
					BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Corner resize is not allowed on a panel!"));
					break;
				}
				case GUI::_LeftBottomResizePopUpId:
				{
					BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Corner resize is not allowed on a panel!"));
					break;
				}
				case GUI::_RightTopResizePopUpId:
				{
					BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Corner resize is not allowed on a panel!"));
					break;
				}
				case GUI::_RightBottomResizePopUpId:
				{
					BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Corner resize is not allowed on a panel!"));
					break;
				}
				default:
				{
					break;
				}
				}

				break;
			}
			default:
			{
				BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Mouse capture style resize attempt on invalid window type!"));
				break;
			}
			}
		}

		GUI::ResizeChilds(*_WndData.LCapturePath[2], this);

		for (size_t _Index = 0; _Index < _WndData.LCapturePath[2]->GetPanels().GetSize(); _Index++)
		{
			if (_WndData.LCapturePath[1] == &_WndData.LCapturePath[2]->GetPanels()[_Index])
			{
				for (size_t _BarLayer = 0; _BarLayer < _WndData.LCapturePath[2]->GetPanels()[_Index].GetPopUps().GetSize(); _BarLayer++)
				{
					uint64_t _Id = _WndData.LCapturePath[2]->GetPanels()[_Index].GetPopUps()[_BarLayer][0].GetId();

					if (_Id == _ResizePopUpId)
					{
						_WndData.LCapturePath[0] = &_WndData.LCapturePath[2]->GetPanels()[_Index].GetPopUps()[_BarLayer][0];
					}
				}
			}
		}
	}

	bool _IsNode = false;

	for (size_t _Index = 0; _Index < _WndData.LCapturePath[2]->GetNodes().GetSize(); _Index++)
	{
		if (_WndData.LCapturePath[1] == &_WndData.LCapturePath[2]->GetNodes()[_Index])
		{
			_IsNode = true;
		}
	}

	if (_IsNode)
	{
		BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Mouse capture style resize attempt on invalid window type!"));
	}

	for (size_t _Layer = 0; _Layer < _WndData.LCapturePath[2]->GetPopUps().GetSize(); _Layer++)
	{
		bool _IsPopUp = false;

		for (size_t _Index = 0; _Index < _WndData.LCapturePath[2]->GetPopUps()[_Layer].GetSize(); _Index++)
		{
			if (_WndData.LCapturePath[1] == &_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index])
			{
				_IsPopUp = true;
			}
		}

		if (_IsPopUp)
		{
			for (size_t _Index = 0; _Index < _WndData.LCapturePath[2]->GetPopUps()[_Layer].GetSize(); _Index++)
			{
				switch (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetId())
				{
				case GUI::_DebugWindowPopUpId:
				{
					switch (_ResizePopUpId)
					{
					case GUI::_LeftResizePopUpId:
					{
						intptr_t _TrueMouseDeltaX = _MouseDeltaX;

						if (_MouseDeltaX > 0 && (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() - GUI::ResizeSize * 2) * (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() > GUI::ResizeSize * 2) < (size_t)(_MouseDeltaX))
						{
							_TrueMouseDeltaX = (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() - GUI::ResizeSize * 2) * (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() > GUI::ResizeSize * 2);
							_WndData.ResizeAccumulationX += _MouseDeltaX - _TrueMouseDeltaX;
						}

						if (_MouseDeltaX < 0)
						{
							_TrueMouseDeltaX = (_WndData.ResizeAccumulationX + _MouseDeltaX) * (_WndData.ResizeAccumulationX < -_MouseDeltaX);
							_WndData.ResizeAccumulationX = (_WndData.ResizeAccumulationX + _MouseDeltaX) * (_WndData.ResizeAccumulationX > -_MouseDeltaX);
						}

						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetWidth(_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() - _TrueMouseDeltaX);
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetTrueWidth(GUI::DebugWindowMinX);
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetPositionX(_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetPositionX() + _TrueMouseDeltaX);

						break;
					}
					case GUI::_RightResizePopUpId:
					{
						intptr_t _TrueMouseDeltaX = _MouseDeltaX;

						if (_MouseDeltaX < 0 && (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() - GUI::ResizeSize * 2) * (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() > GUI::ResizeSize * 2) < (size_t)(-_MouseDeltaX))
						{
							_TrueMouseDeltaX = -(intptr_t)((_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() - GUI::ResizeSize * 2) * (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() > GUI::ResizeSize * 2));
							_WndData.ResizeAccumulationX += _MouseDeltaX - _TrueMouseDeltaX;
						}

						if (_MouseDeltaX > 0)
						{
							_TrueMouseDeltaX = (_WndData.ResizeAccumulationX + _MouseDeltaX) * (-_WndData.ResizeAccumulationX < _MouseDeltaX);
							_WndData.ResizeAccumulationX = (_WndData.ResizeAccumulationX + _MouseDeltaX) * (-_WndData.ResizeAccumulationX > _MouseDeltaX);
						}

						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetWidth(_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() + _TrueMouseDeltaX);
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetTrueWidth(GUI::DebugWindowMinX);

						break;
					}
					case GUI::_TopResizePopUpId:
					{
						intptr_t _TrueMouseDeltaY = _MouseDeltaY;

						if (_MouseDeltaY > 0 && (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() - GUI::ResizeSize * 2) * (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() > GUI::ResizeSize * 2) < (size_t)(_MouseDeltaY))
						{
							_TrueMouseDeltaY = (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() - GUI::ResizeSize * 2) * (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() > GUI::ResizeSize * 2);
							_WndData.ResizeAccumulationY += _MouseDeltaY - _TrueMouseDeltaY;
						}

						if (_MouseDeltaY < 0)
						{
							_TrueMouseDeltaY = (_WndData.ResizeAccumulationY + _MouseDeltaY) * (_WndData.ResizeAccumulationY < -_MouseDeltaY);
							_WndData.ResizeAccumulationY = (_WndData.ResizeAccumulationY + _MouseDeltaY) * (_WndData.ResizeAccumulationY > -_MouseDeltaY);
						}

						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetHeight(_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() - _TrueMouseDeltaY);
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetTrueHeight(GUI::DebugWindowMinY);
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetPositionY(_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetPositionY() + _TrueMouseDeltaY);

						break;
					}
					case GUI::_BottomResizePopUpId:
					{
						intptr_t _TrueMouseDeltaY = _MouseDeltaY;

						if (_MouseDeltaY < 0 && (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() - GUI::ResizeSize * 2) * (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() > GUI::ResizeSize * 2) < (size_t)(-_MouseDeltaY))
						{
							_TrueMouseDeltaY = -(intptr_t)((_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() - GUI::ResizeSize * 2) * (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() > GUI::ResizeSize * 2));
							_WndData.ResizeAccumulationY += _MouseDeltaY - _TrueMouseDeltaY;
						}

						if (_MouseDeltaY > 0)
						{
							_TrueMouseDeltaY = (_WndData.ResizeAccumulationY + _MouseDeltaY) * (-_WndData.ResizeAccumulationY < _MouseDeltaY);
							_WndData.ResizeAccumulationY = (_WndData.ResizeAccumulationY + _MouseDeltaY) * (-_WndData.ResizeAccumulationY > _MouseDeltaY);
						}

						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetHeight(_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() + _TrueMouseDeltaY);
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetTrueHeight(GUI::DebugWindowMinY);

						break;
					}
					case GUI::_LeftTopResizePopUpId:
					{
						intptr_t _TrueMouseDeltaX = _MouseDeltaX;

						if (_MouseDeltaX > 0 && (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() - GUI::ResizeSize * 2) * (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() > GUI::ResizeSize * 2) < (size_t)(_MouseDeltaX))
						{
							_TrueMouseDeltaX = (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() - GUI::ResizeSize * 2) * (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() > GUI::ResizeSize * 2);
							_WndData.ResizeAccumulationX += _MouseDeltaX - _TrueMouseDeltaX;
						}

						if (_MouseDeltaX < 0)
						{
							_TrueMouseDeltaX = (_WndData.ResizeAccumulationX + _MouseDeltaX) * (_WndData.ResizeAccumulationX < -_MouseDeltaX);
							_WndData.ResizeAccumulationX = (_WndData.ResizeAccumulationX + _MouseDeltaX) * (_WndData.ResizeAccumulationX > -_MouseDeltaX);
						}

						intptr_t _TrueMouseDeltaY = _MouseDeltaY;

						if (_MouseDeltaY > 0 && (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() - GUI::ResizeSize * 2) * (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() > GUI::ResizeSize * 2) < (size_t)(_MouseDeltaY))
						{
							_TrueMouseDeltaY = (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() - GUI::ResizeSize * 2) * (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() > GUI::ResizeSize * 2);
							_WndData.ResizeAccumulationY += _MouseDeltaY - _TrueMouseDeltaY;
						}

						if (_MouseDeltaY < 0)
						{
							_TrueMouseDeltaY = (_WndData.ResizeAccumulationY + _MouseDeltaY) * (_WndData.ResizeAccumulationY < -_MouseDeltaY);
							_WndData.ResizeAccumulationY = (_WndData.ResizeAccumulationY + _MouseDeltaY) * (_WndData.ResizeAccumulationY > -_MouseDeltaY);
						}

						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetWidth(_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() - _TrueMouseDeltaX);
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetHeight(_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() - _TrueMouseDeltaY);
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetTrueWidth(GUI::DebugWindowMinX);
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetTrueHeight(GUI::DebugWindowMinY);
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetPositionX(_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetPositionX() + _TrueMouseDeltaX);
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetPositionY(_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetPositionY() + _TrueMouseDeltaY);

						break;
					}
					case GUI::_LeftBottomResizePopUpId:
					{
						intptr_t _TrueMouseDeltaX = _MouseDeltaX;

						if (_MouseDeltaX > 0 && (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() - GUI::ResizeSize * 2) * (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() > GUI::ResizeSize * 2) < (size_t)(_MouseDeltaX))
						{
							_TrueMouseDeltaX = (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() - GUI::ResizeSize * 2) * (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() > GUI::ResizeSize * 2);
							_WndData.ResizeAccumulationX += _MouseDeltaX - _TrueMouseDeltaX;
						}

						if (_MouseDeltaX < 0)
						{
							_TrueMouseDeltaX = (_WndData.ResizeAccumulationX + _MouseDeltaX) * (_WndData.ResizeAccumulationX < -_MouseDeltaX);
							_WndData.ResizeAccumulationX = (_WndData.ResizeAccumulationX + _MouseDeltaX) * (_WndData.ResizeAccumulationX > -_MouseDeltaX);
						}

						intptr_t _TrueMouseDeltaY = _MouseDeltaY;

						if (_MouseDeltaY < 0 && (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() - GUI::ResizeSize * 2) * (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() > GUI::ResizeSize * 2) < (size_t)(-_MouseDeltaY))
						{
							_TrueMouseDeltaY = -(intptr_t)((_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() - GUI::ResizeSize * 2) * (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() > GUI::ResizeSize * 2));
							_WndData.ResizeAccumulationY += _MouseDeltaY - _TrueMouseDeltaY;
						}

						if (_MouseDeltaY > 0)
						{
							_TrueMouseDeltaY = (_WndData.ResizeAccumulationY + _MouseDeltaY) * (-_WndData.ResizeAccumulationY < _MouseDeltaY);
							_WndData.ResizeAccumulationY = (_WndData.ResizeAccumulationY + _MouseDeltaY) * (-_WndData.ResizeAccumulationY > _MouseDeltaY);
						}

						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetWidth(_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() - _TrueMouseDeltaX);
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetHeight(_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() + _TrueMouseDeltaY);
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetTrueWidth(GUI::DebugWindowMinX);
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetTrueHeight(GUI::DebugWindowMinY);
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetPositionX(_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetPositionX() + _TrueMouseDeltaX);

						break;
					}
					case GUI::_RightTopResizePopUpId:
					{
						intptr_t _TrueMouseDeltaX = _MouseDeltaX;

						if (_MouseDeltaX < 0 && (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() - GUI::ResizeSize * 2) * (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() > GUI::ResizeSize * 2) < (size_t)(-_MouseDeltaX))
						{
							_TrueMouseDeltaX = -(intptr_t)((_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() - GUI::ResizeSize * 2) * (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() > GUI::ResizeSize * 2));
							_WndData.ResizeAccumulationX += _MouseDeltaX - _TrueMouseDeltaX;
						}

						if (_MouseDeltaX > 0)
						{
							_TrueMouseDeltaX = (_WndData.ResizeAccumulationX + _MouseDeltaX) * (-_WndData.ResizeAccumulationX < _MouseDeltaX);
							_WndData.ResizeAccumulationX = (_WndData.ResizeAccumulationX + _MouseDeltaX) * (-_WndData.ResizeAccumulationX > _MouseDeltaX);
						}

						intptr_t _TrueMouseDeltaY = _MouseDeltaY;

						if (_MouseDeltaY > 0 && (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() - GUI::ResizeSize * 2) * (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() > GUI::ResizeSize * 2) < (size_t)(_MouseDeltaY))
						{
							_TrueMouseDeltaY = (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() - GUI::ResizeSize * 2) * (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() > GUI::ResizeSize * 2);
							_WndData.ResizeAccumulationY += _MouseDeltaY - _TrueMouseDeltaY;
						}

						if (_MouseDeltaY < 0)
						{
							_TrueMouseDeltaY = (_WndData.ResizeAccumulationY + _MouseDeltaY) * (_WndData.ResizeAccumulationY < -_MouseDeltaY);
							_WndData.ResizeAccumulationY = (_WndData.ResizeAccumulationY + _MouseDeltaY) * (_WndData.ResizeAccumulationY > -_MouseDeltaY);
						}

						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetWidth(_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() + _TrueMouseDeltaX);
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetHeight(_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() - _TrueMouseDeltaY);
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetTrueHeight(GUI::DebugWindowMinY);
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetTrueWidth(GUI::DebugWindowMinX);
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetPositionY(_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetPositionY() + _TrueMouseDeltaY);

						break;
					}
					case GUI::_RightBottomResizePopUpId:
					{
						intptr_t _TrueMouseDeltaX = _MouseDeltaX;

						if (_MouseDeltaX < 0 && (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() - GUI::ResizeSize * 2) * (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() > GUI::ResizeSize * 2) < (size_t)(-_MouseDeltaX))
						{
							_TrueMouseDeltaX = -(intptr_t)((_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() - GUI::ResizeSize * 2) * (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() > GUI::ResizeSize * 2));
							_WndData.ResizeAccumulationX += _MouseDeltaX - _TrueMouseDeltaX;
						}

						if (_MouseDeltaX > 0)
						{
							_TrueMouseDeltaX = (_WndData.ResizeAccumulationX + _MouseDeltaX) * (-_WndData.ResizeAccumulationX < _MouseDeltaX);
							_WndData.ResizeAccumulationX = (_WndData.ResizeAccumulationX + _MouseDeltaX) * (-_WndData.ResizeAccumulationX > _MouseDeltaX);
						}

						intptr_t _TrueMouseDeltaY = _MouseDeltaY;

						if (_MouseDeltaY < 0 && (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() - GUI::ResizeSize * 2) * (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() > GUI::ResizeSize * 2) < (size_t)(-_MouseDeltaY))
						{
							_TrueMouseDeltaY = -(intptr_t)((_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() - GUI::ResizeSize * 2) * (_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() > GUI::ResizeSize * 2));
							_WndData.ResizeAccumulationY += _MouseDeltaY - _TrueMouseDeltaY;
						}

						if (_MouseDeltaY > 0)
						{
							_TrueMouseDeltaY = (_WndData.ResizeAccumulationY + _MouseDeltaY) * (-_WndData.ResizeAccumulationY < _MouseDeltaY);
							_WndData.ResizeAccumulationY = (_WndData.ResizeAccumulationY + _MouseDeltaY) * (-_WndData.ResizeAccumulationY > _MouseDeltaY);
						}

						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetWidth(_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetWidth() + _TrueMouseDeltaX);
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetHeight(_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetHeight() + _TrueMouseDeltaY);
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetTrueWidth(GUI::DebugWindowMinX);
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetTrueHeight(GUI::DebugWindowMinY);

						break;
					}
					default:
					{
						break;
					}
					}

					GUI::GenerateDebugWindow(_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index], this, false);

					break;
				}
				default:
				{
					BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Mouse capture style resize attempt on invalid window type!"));
					break;
				}
				}
			}

			for (size_t _Index = 0; _Index < _WndData.LCapturePath[2]->GetPopUps()[_Layer].GetSize(); _Index++)
			{
				if (_WndData.LCapturePath[1] == &_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index])
				{
					for (size_t _BarLayer = 0; _BarLayer < _WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetPopUps().GetSize(); _BarLayer++)
					{
						uint64_t _Id = _WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetPopUps()[_BarLayer][0].GetId();

						if (_Id == _ResizePopUpId)
						{
							_WndData.LCapturePath[0] = &_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetPopUps()[_BarLayer][0];
						}
					}
				}
			}
		}
	}
}

void BFW_WINDOWS::RunTime::MainMenu::MouseCaptureMove(BFW::GUI::Window& _Wnd, GUI::WindowData& _WndData, const intptr_t _MouseDeltaX, const intptr_t _MouseDeltaY)
{
	if (_WndData.LCapturePath.GetSize() < 2)
	{
		return;
	}

	for (size_t _Layer = 0; _Layer < _WndData.LCapturePath[1]->GetPopUps().GetSize(); _Layer++)
	{
		bool _IsPopUp = false;

		for (size_t _Index = 0; _Index < _WndData.LCapturePath[1]->GetPopUps()[_Layer].GetSize(); _Index++)
		{
			if (_WndData.LCapturePath[0] == &_WndData.LCapturePath[1]->GetPopUps()[_Layer][_Index])
			{
				_IsPopUp = true;
			}
		}

		if (_IsPopUp)
		{
			for (size_t _Index = 0; _Index < _WndData.LCapturePath[1]->GetPopUps()[_Layer].GetSize(); _Index++)
			{
				_WndData.LCapturePath[1]->GetPopUps()[_Layer][_Index].SetPositionX(_WndData.LCapturePath[1]->GetPopUps()[_Layer][_Index].GetPositionX() + _MouseDeltaX);
				_WndData.LCapturePath[1]->GetPopUps()[_Layer][_Index].SetPositionY(_WndData.LCapturePath[1]->GetPopUps()[_Layer][_Index].GetPositionY() + _MouseDeltaY);
			}
		}
	}
}

void BFW_WINDOWS::RunTime::MainMenu::MouseCaptureScroll(BFW::GUI::Window& _Wnd, GUI::WindowData& _WndData, const size_t _WindowIndex, const intptr_t _MouseX, const intptr_t _MouseY)
{
	BFW::GUI::PopUp& _ScrolledWindow = *_WndData.MCapturePath[_WindowIndex];

	bool _FoundHScrollWindow = false;
	size_t _HScrollWindowIndex = 0;

	while (_HScrollWindowIndex < _ScrolledWindow.GetPopUps().GetSize())
	{
		bool _ShouldBreak = false;

		if (_ScrolledWindow.GetPopUps()[_HScrollWindowIndex][0].GetId() == GUI::_HScrollWindowPopUpId)
		{
			_FoundHScrollWindow = true;
			_ShouldBreak = true;
		}

		if (_ShouldBreak)
		{
			break;
		}

		_HScrollWindowIndex++;
	}

	if (_FoundHScrollWindow)
	{
		BFW::GUI::PopUp& _HScrollWindow = _ScrolledWindow.GetPopUps()[_HScrollWindowIndex][0];
		BFW::GUI::PopUp& _HScrollButton = _HScrollWindow.GetPopUps()[0][0];

		intptr_t _TrueDelta = (intptr_t)((float)((_MouseX - _WndData.MCaptureMouseX) / (intptr_t)(GUI::MouseCaptureScrollScale)) * GUI::MouseCaptureScrollSpeed * GetTimeStep());

		if (_TrueDelta < 0 && _HScrollButton.GetPositionX() < -_TrueDelta)
		{
			_TrueDelta = -_HScrollButton.GetPositionX();
		}

		if (_TrueDelta > 0 && (_HScrollWindow.GetWidth() - (_HScrollButton.GetPositionX() + _HScrollButton.GetWidth())) * (_HScrollWindow.GetWidth() > _HScrollButton.GetPositionX() + _HScrollButton.GetWidth()) < (size_t)(_TrueDelta))
		{
			_TrueDelta = (_HScrollWindow.GetWidth() - (_HScrollButton.GetPositionX() + _HScrollButton.GetWidth())) * (_HScrollWindow.GetWidth() > _HScrollButton.GetPositionX() + _HScrollButton.GetWidth());
		}

		_HScrollButton.SetPositionX(_HScrollButton.GetPositionX() + _TrueDelta);

		intptr_t _ScrollDelta = _ScrolledWindow.GetScrollX();

		_ScrolledWindow.SetScrollX(_HScrollButton.GetPositionX() * (_ScrolledWindow.GetTrueWidth() - _ScrolledWindow.GetWidth()) / (_HScrollWindow.GetWidth() - _HScrollWindow.GetWidth() * _ScrolledWindow.GetWidth() / _ScrolledWindow.GetTrueWidth()));

		_ScrollDelta = _ScrolledWindow.GetScrollX() - _ScrollDelta;

		for (size_t _Layer = 0; _Layer < _ScrolledWindow.GetPopUps().GetSize(); _Layer++)
		{
			for (size_t _Index = 0; _Index < _ScrolledWindow.GetPopUps()[_Layer].GetSize(); _Index++)
			{
				uint64_t _Id = _ScrolledWindow.GetPopUps()[_Layer][_Index].GetId();

				if (_Id == GUI::_LeftResizePopUpId || _Id == GUI::_RightResizePopUpId || _Id == GUI::_TopResizePopUpId || _Id == GUI::_BottomResizePopUpId || _Id == GUI::_LeftTopResizePopUpId || _Id == GUI::_LeftBottomResizePopUpId || _Id == GUI::_RightTopResizePopUpId || _Id == GUI::_RightBottomResizePopUpId || _Id == GUI::_HScrollWindowPopUpId || _Id == GUI::_VScrollWindowPopUpId || _Id == GUI::_ScrollCornerPopUpId)
				{
					_ScrolledWindow.GetPopUps()[_Layer][_Index].SetPositionX(_ScrolledWindow.GetPopUps()[_Layer][_Index].GetPositionX() + _ScrollDelta);
				}
			}
		}
	}

	bool _FoundVScrollWindow = false;
	size_t _VScrollWindowIndex = 0;

	while (_VScrollWindowIndex < _ScrolledWindow.GetPopUps().GetSize())
	{
		bool _ShouldBreak = false;

		if (_ScrolledWindow.GetPopUps()[_VScrollWindowIndex][0].GetId() == GUI::_VScrollWindowPopUpId)
		{
			_FoundVScrollWindow = true;
			_ShouldBreak = true;
		}

		if (_ShouldBreak)
		{
			break;
		}

		_VScrollWindowIndex++;
	}

	if (_FoundVScrollWindow)
	{
		BFW::GUI::PopUp& _VScrollWindow = _ScrolledWindow.GetPopUps()[_VScrollWindowIndex][0];
		BFW::GUI::PopUp& _VScrollButton = _VScrollWindow.GetPopUps()[0][0];

		intptr_t _TrueDelta = (intptr_t)((float)((_MouseY - _WndData.MCaptureMouseY) / (intptr_t)(GUI::MouseCaptureScrollScale)) * GUI::MouseCaptureScrollSpeed * GetTimeStep());

		if (_TrueDelta < 0 && _VScrollButton.GetPositionY() < -_TrueDelta)
		{
			_TrueDelta = -_VScrollButton.GetPositionY();
		}

		if (_TrueDelta > 0 && (_VScrollWindow.GetHeight() - (_VScrollButton.GetPositionY() + _VScrollButton.GetHeight())) * (_VScrollWindow.GetHeight() > _VScrollButton.GetPositionY() + _VScrollButton.GetHeight()) < (size_t)(_TrueDelta))
		{
			_TrueDelta = (_VScrollWindow.GetHeight() - (_VScrollButton.GetPositionY() + _VScrollButton.GetHeight())) * (_VScrollWindow.GetHeight() > _VScrollButton.GetPositionY() + _VScrollButton.GetHeight());
		}

		_VScrollButton.SetPositionY(_VScrollButton.GetPositionY() + _TrueDelta);

		intptr_t _ScrollDelta = _ScrolledWindow.GetScrollY();

		_ScrolledWindow.SetScrollY(_VScrollButton.GetPositionY() * (_ScrolledWindow.GetTrueHeight() - _ScrolledWindow.GetHeight()) / (_VScrollWindow.GetHeight() - _VScrollWindow.GetHeight() * _ScrolledWindow.GetHeight() / _ScrolledWindow.GetTrueHeight()));

		_ScrollDelta = _ScrolledWindow.GetScrollY() - _ScrollDelta;

		for (size_t _Layer = 0; _Layer < _ScrolledWindow.GetPopUps().GetSize(); _Layer++)
		{
			for (size_t _Index = 0; _Index < _ScrolledWindow.GetPopUps()[_Layer].GetSize(); _Index++)
			{
				uint64_t _Id = _ScrolledWindow.GetPopUps()[_Layer][_Index].GetId();

				if (_Id == GUI::_LeftResizePopUpId || _Id == GUI::_RightResizePopUpId || _Id == GUI::_TopResizePopUpId || _Id == GUI::_BottomResizePopUpId || _Id == GUI::_LeftTopResizePopUpId || _Id == GUI::_LeftBottomResizePopUpId || _Id == GUI::_RightTopResizePopUpId || _Id == GUI::_RightBottomResizePopUpId || _Id == GUI::_HScrollWindowPopUpId || _Id == GUI::_VScrollWindowPopUpId || _Id == GUI::_ScrollCornerPopUpId)
				{
					_ScrolledWindow.GetPopUps()[_Layer][_Index].SetPositionY(_ScrolledWindow.GetPopUps()[_Layer][_Index].GetPositionY() + _ScrollDelta);
				}
			}
		}
	}
}

void BFW_WINDOWS::RunTime::MainMenu::MouseCaptureScrollX(BFW::GUI::Window& _Wnd, GUI::WindowData& _WndData, const intptr_t _MouseDeltaX)
{
	intptr_t _TrueMouseDeltaX = _MouseDeltaX;

	if (_MouseDeltaX < 0)
	{
		_TrueMouseDeltaX = (_WndData.ResizeAccumulationX + _MouseDeltaX) * (_WndData.ResizeAccumulationX < -_MouseDeltaX);
		_WndData.ResizeAccumulationX = (_WndData.ResizeAccumulationX + _MouseDeltaX) * (_WndData.ResizeAccumulationX > -_MouseDeltaX);
	}

	if (_TrueMouseDeltaX < 0 && _WndData.LCapturePath[0]->GetPositionX() < -_TrueMouseDeltaX)
	{
		intptr_t _OldMouseDeltaX = _TrueMouseDeltaX;
		_TrueMouseDeltaX = -_WndData.LCapturePath[0]->GetPositionX();
		_WndData.ResizeAccumulationX += _OldMouseDeltaX - _TrueMouseDeltaX;
	}

	if (_MouseDeltaX > 0)
	{
		_TrueMouseDeltaX = (_WndData.ResizeAccumulationX + _MouseDeltaX) * (-_WndData.ResizeAccumulationX < _MouseDeltaX);
		_WndData.ResizeAccumulationX = (_WndData.ResizeAccumulationX + _MouseDeltaX) * (-_WndData.ResizeAccumulationX > _MouseDeltaX);
	}

	if (_TrueMouseDeltaX > 0 && (_WndData.LCapturePath[1]->GetWidth() - (_WndData.LCapturePath[0]->GetPositionX() + _WndData.LCapturePath[0]->GetWidth())) * (_WndData.LCapturePath[1]->GetWidth() > _WndData.LCapturePath[0]->GetPositionX() + _WndData.LCapturePath[0]->GetWidth()) < (size_t)(_TrueMouseDeltaX))
	{
		intptr_t _OldMouseDeltaX = _TrueMouseDeltaX;
		_TrueMouseDeltaX = (_WndData.LCapturePath[1]->GetWidth() - (_WndData.LCapturePath[0]->GetPositionX() + _WndData.LCapturePath[0]->GetWidth())) * (_WndData.LCapturePath[1]->GetWidth() > _WndData.LCapturePath[0]->GetPositionX() + _WndData.LCapturePath[0]->GetWidth());
		_WndData.ResizeAccumulationX += _OldMouseDeltaX - _TrueMouseDeltaX;
	}

	_WndData.LCapturePath[0]->SetPositionX(_WndData.LCapturePath[0]->GetPositionX() + _TrueMouseDeltaX);

	intptr_t _ScrollDelta = _WndData.LCapturePath[2]->GetScrollX();

	_WndData.LCapturePath[2]->SetScrollX(_WndData.LCapturePath[0]->GetPositionX() * (_WndData.LCapturePath[2]->GetTrueWidth() - _WndData.LCapturePath[2]->GetWidth()) / (_WndData.LCapturePath[1]->GetWidth() - _WndData.LCapturePath[1]->GetWidth() * _WndData.LCapturePath[2]->GetWidth() / _WndData.LCapturePath[2]->GetTrueWidth()));

	_ScrollDelta = _WndData.LCapturePath[2]->GetScrollX() - _ScrollDelta;

	for (size_t _Layer = 0; _Layer < _WndData.LCapturePath[2]->GetPopUps().GetSize(); _Layer++)
	{
		for (size_t _Index = 0; _Index < _WndData.LCapturePath[2]->GetPopUps()[_Layer].GetSize(); _Index++)
		{
			uint64_t _Id = _WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetId();

			if (_Id == GUI::_LeftResizePopUpId || _Id == GUI::_RightResizePopUpId || _Id == GUI::_TopResizePopUpId || _Id == GUI::_BottomResizePopUpId || _Id == GUI::_LeftTopResizePopUpId || _Id == GUI::_LeftBottomResizePopUpId || _Id == GUI::_RightTopResizePopUpId || _Id == GUI::_RightBottomResizePopUpId || _Id == GUI::_HScrollWindowPopUpId || _Id == GUI::_VScrollWindowPopUpId || _Id == GUI::_ScrollCornerPopUpId)
			{
				_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetPositionX(_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetPositionX() + _ScrollDelta);
			}
		}
	}
}

void BFW_WINDOWS::RunTime::MainMenu::MouseCaptureScrollY(BFW::GUI::Window& _Wnd, GUI::WindowData& _WndData, const intptr_t _MouseDeltaY)
{
	intptr_t _TrueMouseDeltaY = _MouseDeltaY;

	if (_MouseDeltaY < 0)
	{
		_TrueMouseDeltaY = (_WndData.ResizeAccumulationY + _MouseDeltaY) * (_WndData.ResizeAccumulationY < -_MouseDeltaY);
		_WndData.ResizeAccumulationY = (_WndData.ResizeAccumulationY + _MouseDeltaY) * (_WndData.ResizeAccumulationY > -_MouseDeltaY);
	}

	if (_TrueMouseDeltaY < 0 && _WndData.LCapturePath[0]->GetPositionY() < -_TrueMouseDeltaY)
	{
		intptr_t _OldMouseDeltaY = _TrueMouseDeltaY;
		_TrueMouseDeltaY = -_WndData.LCapturePath[0]->GetPositionY();
		_WndData.ResizeAccumulationY += _OldMouseDeltaY - _TrueMouseDeltaY;
	}

	if (_MouseDeltaY > 0)
	{
		_TrueMouseDeltaY = (_WndData.ResizeAccumulationY + _MouseDeltaY) * (-_WndData.ResizeAccumulationY < _MouseDeltaY);
		_WndData.ResizeAccumulationY = (_WndData.ResizeAccumulationY + _MouseDeltaY) * (-_WndData.ResizeAccumulationY > _MouseDeltaY);
	}

	if (_TrueMouseDeltaY > 0 && (_WndData.LCapturePath[1]->GetHeight() - (_WndData.LCapturePath[0]->GetPositionY() + _WndData.LCapturePath[0]->GetHeight())) * (_WndData.LCapturePath[1]->GetHeight() > _WndData.LCapturePath[0]->GetPositionY() + _WndData.LCapturePath[0]->GetHeight()) < (size_t)(_TrueMouseDeltaY))
	{
		intptr_t _OldMouseDeltaY = _TrueMouseDeltaY;
		_TrueMouseDeltaY = (_WndData.LCapturePath[1]->GetHeight() - (_WndData.LCapturePath[0]->GetPositionY() + _WndData.LCapturePath[0]->GetHeight())) * (_WndData.LCapturePath[1]->GetHeight() > _WndData.LCapturePath[0]->GetPositionY() + _WndData.LCapturePath[0]->GetHeight());
		_WndData.ResizeAccumulationY += _OldMouseDeltaY - _TrueMouseDeltaY;
	}

	_WndData.LCapturePath[0]->SetPositionY(_WndData.LCapturePath[0]->GetPositionY() + _TrueMouseDeltaY);

	intptr_t _ScrollDelta = _WndData.LCapturePath[2]->GetScrollY();

	_WndData.LCapturePath[2]->SetScrollY(_WndData.LCapturePath[0]->GetPositionY() * (_WndData.LCapturePath[2]->GetTrueHeight() - _WndData.LCapturePath[2]->GetHeight()) / (_WndData.LCapturePath[1]->GetHeight() - _WndData.LCapturePath[1]->GetHeight() * _WndData.LCapturePath[2]->GetHeight() / _WndData.LCapturePath[2]->GetTrueHeight()));

	_ScrollDelta = _WndData.LCapturePath[2]->GetScrollY() - _ScrollDelta;

	for (size_t _Layer = 0; _Layer < _WndData.LCapturePath[2]->GetPopUps().GetSize(); _Layer++)
	{
		for (size_t _Index = 0; _Index < _WndData.LCapturePath[2]->GetPopUps()[_Layer].GetSize(); _Index++)
		{
			uint64_t _Id = _WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetId();

			if (_Id == GUI::_LeftResizePopUpId || _Id == GUI::_RightResizePopUpId || _Id == GUI::_TopResizePopUpId || _Id == GUI::_BottomResizePopUpId || _Id == GUI::_LeftTopResizePopUpId || _Id == GUI::_LeftBottomResizePopUpId || _Id == GUI::_RightTopResizePopUpId || _Id == GUI::_RightBottomResizePopUpId || _Id == GUI::_HScrollWindowPopUpId || _Id == GUI::_VScrollWindowPopUpId || _Id == GUI::_ScrollCornerPopUpId)
			{
				_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetPositionY(_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetPositionY() + _ScrollDelta);
			}
		}
	}
}

void BFW_WINDOWS::RunTime::MainMenu::WheelScrollX(BFW::GUI::Window& _Wnd, GUI::WindowData& _WndData, const intptr_t _MouseX, const intptr_t _MouseY, const intptr_t _Delta)
{
	BFW::Vector<BFW::GUI::PopUp*> _Path;

	_WndData.Layout.GetChildFromMouse(_MouseX, _MouseY, &_Path);

	bool _Found = false;
	size_t _ScrolledWindowIndex = 0;

	while (_ScrolledWindowIndex < _Path.GetSize())
	{
		bool _ShouldBreak = false;

		switch (_Path[_ScrolledWindowIndex]->GetId())
		{
		case GUI::_DebugWindowPopUpId:
		{
			_Found = true;
			_ShouldBreak = true;
			break;
		}
		default:
		{
			break;
		}
		}

		if (_ShouldBreak)
		{
			break;
		}

		_ScrolledWindowIndex++;
	}

	if (!_Found)
	{
		return;
	}

	BFW::GUI::PopUp& _ScrolledWindow = *_Path[_ScrolledWindowIndex];

	_Found = false;
	size_t _ScrollWindowIndex = 0;

	while (_ScrollWindowIndex < _ScrolledWindow.GetPopUps().GetSize())
	{
		bool _ShouldBreak = false;

		if (_ScrolledWindow.GetPopUps()[_ScrollWindowIndex][0].GetId() == GUI::_HScrollWindowPopUpId)
		{
			_Found = true;
			_ShouldBreak = true;
		}

		if (_ShouldBreak)
		{
			break;
		}

		_ScrollWindowIndex++;
	}

	if (!_Found)
	{
		return;
	}

	BFW::GUI::PopUp& _ScrollWindow = _ScrolledWindow.GetPopUps()[_ScrollWindowIndex][0];
	BFW::GUI::PopUp& _ScrollButton = _ScrollWindow.GetPopUps()[0][0];

	intptr_t _TrueDelta = _Delta;

	if (_TrueDelta < 0 && _ScrollButton.GetPositionX() < -_TrueDelta)
	{
		_TrueDelta = -_ScrollButton.GetPositionX();
	}

	if (_TrueDelta > 0 && (_ScrollWindow.GetWidth() - (_ScrollButton.GetPositionX() + _ScrollButton.GetWidth())) * (_ScrollWindow.GetWidth() > _ScrollButton.GetPositionX() + _ScrollButton.GetWidth()) < (size_t)(_TrueDelta))
	{
		_TrueDelta = (_ScrollWindow.GetWidth() - (_ScrollButton.GetPositionX() + _ScrollButton.GetWidth())) * (_ScrollWindow.GetWidth() > _ScrollButton.GetPositionX() + _ScrollButton.GetWidth());
	}

	_ScrollButton.SetPositionX(_ScrollButton.GetPositionX() + _TrueDelta);

	intptr_t _ScrollDelta = _ScrolledWindow.GetScrollX();

	_ScrolledWindow.SetScrollX(_ScrollButton.GetPositionX() * (_ScrolledWindow.GetTrueWidth() - _ScrolledWindow.GetWidth()) / (_ScrollWindow.GetWidth() - _ScrollWindow.GetWidth() * _ScrolledWindow.GetWidth() / _ScrolledWindow.GetTrueWidth()));

	_ScrollDelta = _ScrolledWindow.GetScrollX() - _ScrollDelta;

	for (size_t _Layer = 0; _Layer < _ScrolledWindow.GetPopUps().GetSize(); _Layer++)
	{
		for (size_t _Index = 0; _Index < _ScrolledWindow.GetPopUps()[_Layer].GetSize(); _Index++)
		{
			uint64_t _Id = _ScrolledWindow.GetPopUps()[_Layer][_Index].GetId();

			if (_Id == GUI::_LeftResizePopUpId || _Id == GUI::_RightResizePopUpId || _Id == GUI::_TopResizePopUpId || _Id == GUI::_BottomResizePopUpId || _Id == GUI::_LeftTopResizePopUpId || _Id == GUI::_LeftBottomResizePopUpId || _Id == GUI::_RightTopResizePopUpId || _Id == GUI::_RightBottomResizePopUpId || _Id == GUI::_HScrollWindowPopUpId || _Id == GUI::_VScrollWindowPopUpId || _Id == GUI::_ScrollCornerPopUpId)
			{
				_ScrolledWindow.GetPopUps()[_Layer][_Index].SetPositionX(_ScrolledWindow.GetPopUps()[_Layer][_Index].GetPositionX() + _ScrollDelta);
			}
		}
	}
}

void BFW_WINDOWS::RunTime::MainMenu::WheelScrollY(BFW::GUI::Window& _Wnd, GUI::WindowData& _WndData, const intptr_t _MouseX, const intptr_t _MouseY, const intptr_t _Delta)
{
	BFW::Vector<BFW::GUI::PopUp*> _Path;

	_WndData.Layout.GetChildFromMouse(_MouseX, _MouseY, &_Path);

	bool _Found = false;
	size_t _ScrolledWindowIndex = 0;

	while (_ScrolledWindowIndex < _Path.GetSize())
	{
		bool _ShouldBreak = false;

		switch (_Path[_ScrolledWindowIndex]->GetId())
		{
		case GUI::_DebugWindowPopUpId:
		{
			_Found = true;
			_ShouldBreak = true;
			break;
		}
		default:
		{
			break;
		}
		}

		if (_ShouldBreak)
		{
			break;
		}

		_ScrolledWindowIndex++;
	}

	if (!_Found)
	{
		return;
	}

	BFW::GUI::PopUp& _ScrolledWindow = *_Path[_ScrolledWindowIndex];

	_Found = false;
	size_t _ScrollWindowIndex = 0;

	while (_ScrollWindowIndex < _ScrolledWindow.GetPopUps().GetSize())
	{
		bool _ShouldBreak = false;

		if (_ScrolledWindow.GetPopUps()[_ScrollWindowIndex][0].GetId() == GUI::_VScrollWindowPopUpId)
		{
			_Found = true;
			_ShouldBreak = true;
		}

		if (_ShouldBreak)
		{
			break;
		}

		_ScrollWindowIndex++;
	}

	if (!_Found)
	{
		return;
	}

	BFW::GUI::PopUp& _ScrollWindow = _ScrolledWindow.GetPopUps()[_ScrollWindowIndex][0];
	BFW::GUI::PopUp& _ScrollButton = _ScrollWindow.GetPopUps()[0][0];

	intptr_t _TrueDelta = _Delta;

	if (_TrueDelta < 0 && _ScrollButton.GetPositionY() < -_TrueDelta)
	{
		_TrueDelta = -_ScrollButton.GetPositionY();
	}

	if (_TrueDelta > 0 && (_ScrollWindow.GetHeight() - (_ScrollButton.GetPositionY() + _ScrollButton.GetHeight())) * (_ScrollWindow.GetHeight() > _ScrollButton.GetPositionY() + _ScrollButton.GetHeight()) < (size_t)(_TrueDelta))
	{
		_TrueDelta = (_ScrollWindow.GetHeight() - (_ScrollButton.GetPositionY() + _ScrollButton.GetHeight())) * (_ScrollWindow.GetHeight() > _ScrollButton.GetPositionY() + _ScrollButton.GetHeight());
	}

	_ScrollButton.SetPositionY(_ScrollButton.GetPositionY() + _TrueDelta);

	intptr_t _ScrollDelta = _ScrolledWindow.GetScrollY();

	_ScrolledWindow.SetScrollY(_ScrollButton.GetPositionY() * (_ScrolledWindow.GetTrueHeight() - _ScrolledWindow.GetHeight()) / (_ScrollWindow.GetHeight() - _ScrollWindow.GetHeight() * _ScrolledWindow.GetHeight() / _ScrolledWindow.GetTrueHeight()));

	_ScrollDelta = _ScrolledWindow.GetScrollY() - _ScrollDelta;

	for (size_t _Layer = 0; _Layer < _ScrolledWindow.GetPopUps().GetSize(); _Layer++)
	{
		for (size_t _Index = 0; _Index < _ScrolledWindow.GetPopUps()[_Layer].GetSize(); _Index++)
		{
			uint64_t _Id = _ScrolledWindow.GetPopUps()[_Layer][_Index].GetId();

			if (_Id == GUI::_LeftResizePopUpId || _Id == GUI::_RightResizePopUpId || _Id == GUI::_TopResizePopUpId || _Id == GUI::_BottomResizePopUpId || _Id == GUI::_LeftTopResizePopUpId || _Id == GUI::_LeftBottomResizePopUpId || _Id == GUI::_RightTopResizePopUpId || _Id == GUI::_RightBottomResizePopUpId || _Id == GUI::_HScrollWindowPopUpId || _Id == GUI::_VScrollWindowPopUpId || _Id == GUI::_ScrollCornerPopUpId)
			{
				_ScrolledWindow.GetPopUps()[_Layer][_Index].SetPositionY(_ScrolledWindow.GetPopUps()[_Layer][_Index].GetPositionY() + _ScrollDelta);
			}
		}
	}
}

void BFW_WINDOWS::RunTime::MainMenu::MouseCaptureInputs(BFW::GUI::Window& _Wnd, GUI::WindowData& _WndData)
{
	Application& _ApplicationObj = *(Application*)(GetApplicationObj());
	BFW::GUI::Window& _MainWindow = _ApplicationObj.GetMainWindow();
	GUI::WindowData& _MainWindowData = _ApplicationObj.GetMainWindowData();
	BFW::Vector<BFW::GUI::Window*>& _ChildWindows = _ApplicationObj.GetChildWindows();
	BFW::Vector<GUI::WindowData*>& _ChildWindowsData = _ApplicationObj.GetChildWindowsData();

	intptr_t _MouseX = 0, _MouseY = 0;

	if (_Wnd.GetMousePosition(_MouseX, _MouseY))
	{
		if (_Wnd.GetKeys()[VK_LBUTTON].JustPressed() && !_WndData.MCapture && !_WndData.RCapture && !_WndData.X1Capture && !_WndData.X2Capture)
		{
			_WndData.LCapture = true;
			_WndData.LayoutMutex->lock();
			_WndData.Layout.GetChildFromMouse(_MouseX, _MouseY, &_WndData.LCapturePath);
			_WndData.LayoutMutex->unlock();
			_WndData.LCaptureMouseX = _MouseX;
			_WndData.LCaptureMouseY = _MouseY;
			_WndData.LCaptureMouseXLastFrame = _MouseX;
			_WndData.LCaptureMouseYLastFrame = _MouseY;
		}

		if (_Wnd.GetKeys()[VK_MBUTTON].JustPressed() && !_WndData.LCapture && !_WndData.RCapture && !_WndData.X1Capture && !_WndData.X2Capture)
		{
			_WndData.MCapture = true;
			_WndData.LayoutMutex->lock();
			_WndData.Layout.GetChildFromMouse(_MouseX, _MouseY, &_WndData.MCapturePath);
			_WndData.LayoutMutex->unlock();
			_WndData.MCaptureMouseX = _MouseX;
			_WndData.MCaptureMouseY = _MouseY;
			_WndData.MCaptureMouseXLastFrame = _MouseX;
			_WndData.MCaptureMouseYLastFrame = _MouseY;
		}

		if (_Wnd.GetKeys()[VK_RBUTTON].JustPressed() && !_WndData.LCapture && !_WndData.MCapture && !_WndData.X1Capture && !_WndData.X2Capture)
		{
			_WndData.RCapture = true;
			_WndData.LayoutMutex->lock();
			_WndData.Layout.GetChildFromMouse(_MouseX, _MouseY, &_WndData.RCapturePath);
			_WndData.LayoutMutex->unlock();
			_WndData.RCaptureMouseX = _MouseX;
			_WndData.RCaptureMouseY = _MouseY;
			_WndData.RCaptureMouseXLastFrame = _MouseX;
			_WndData.RCaptureMouseYLastFrame = _MouseY;
		}

		if (_Wnd.GetKeys()[VK_XBUTTON1].JustPressed() && !_WndData.LCapture && !_WndData.MCapture && !_WndData.RCapture && !_WndData.X2Capture)
		{
			_WndData.X1Capture = true;
			_WndData.LayoutMutex->lock();
			_WndData.Layout.GetChildFromMouse(_MouseX, _MouseY, &_WndData.X1CapturePath);
			_WndData.LayoutMutex->unlock();
			_WndData.X1CaptureMouseX = _MouseX;
			_WndData.X1CaptureMouseY = _MouseY;
			_WndData.X1CaptureMouseXLastFrame = _MouseX;
			_WndData.X1CaptureMouseYLastFrame = _MouseY;
		}

		if (_Wnd.GetKeys()[VK_XBUTTON2].JustPressed() && !_WndData.LCapture && !_WndData.MCapture && !_WndData.RCapture && !_WndData.X1Capture)
		{
			_WndData.X2Capture = true;
			_WndData.LayoutMutex->lock();
			_WndData.Layout.GetChildFromMouse(_MouseX, _MouseY, &_WndData.X2CapturePath);
			_WndData.LayoutMutex->unlock();
			_WndData.X2CaptureMouseX = _MouseX;
			_WndData.X2CaptureMouseY = _MouseY;
			_WndData.X2CaptureMouseXLastFrame = _MouseX;
			_WndData.X2CaptureMouseYLastFrame = _MouseY;
		}
	}
}

void BFW_WINDOWS::RunTime::MainMenu::DeleteMouseCaptureInputs(BFW::GUI::Window& _Wnd, GUI::WindowData& _WndData)
{
	Application& _ApplicationObj = *(Application*)(GetApplicationObj());
	BFW::GUI::Window& _MainWindow = _ApplicationObj.GetMainWindow();
	GUI::WindowData& _MainWindowData = _ApplicationObj.GetMainWindowData();
	BFW::Vector<BFW::GUI::Window*>& _ChildWindows = _ApplicationObj.GetChildWindows();
	BFW::Vector<GUI::WindowData*>& _ChildWindowsData = _ApplicationObj.GetChildWindowsData();

	_WndData.LCapture = false;
	_WndData.LCapturePath.Clear();
	_WndData.LCaptureMouseX = 0;
	_WndData.LCaptureMouseY = 0;
	_WndData.LCaptureMouseXLastFrame = 0;
	_WndData.LCaptureMouseYLastFrame = 0;

	_WndData.MCapture = false;
	_WndData.MCapturePath.Clear();
	_WndData.MCaptureMouseX = 0;
	_WndData.MCaptureMouseY = 0;
	_WndData.MCaptureMouseXLastFrame = 0;
	_WndData.MCaptureMouseYLastFrame = 0;

	_WndData.RCapture = false;
	_WndData.RCapturePath.Clear();
	_WndData.RCaptureMouseX = 0;
	_WndData.RCaptureMouseY = 0;
	_WndData.RCaptureMouseXLastFrame = 0;
	_WndData.RCaptureMouseYLastFrame = 0;

	_WndData.X1Capture = false;
	_WndData.X1CapturePath.Clear();
	_WndData.X1CaptureMouseX = 0;
	_WndData.X1CaptureMouseY = 0;
	_WndData.X1CaptureMouseXLastFrame = 0;
	_WndData.X1CaptureMouseYLastFrame = 0;

	_WndData.X2Capture = false;
	_WndData.X2CapturePath.Clear();
	_WndData.X2CaptureMouseX = 0;
	_WndData.X2CaptureMouseY = 0;
	_WndData.X2CaptureMouseXLastFrame = 0;
	_WndData.X2CaptureMouseYLastFrame = 0;
}

void BFW_WINDOWS::RunTime::MainMenu::HandleWindowInputs(BFW::GUI::Window& _Wnd, GUI::WindowData& _WndData, const bool _IsMainWindow)
{
	Application& _ApplicationObj = *(Application*)(GetApplicationObj());
	BFW::GUI::Window& _MainWindow = _ApplicationObj.GetMainWindow();
	GUI::WindowData& _MainWindowData = _ApplicationObj.GetMainWindowData();
	BFW::Vector<BFW::GUI::Window*>& _ChildWindows = _ApplicationObj.GetChildWindows();
	BFW::Vector<GUI::WindowData*>& _ChildWindowsData = _ApplicationObj.GetChildWindowsData();

	if (_Wnd.GetKeys()[VK_LBUTTON].IsPressed())
	{
		intptr_t _MouseX = 0, _MouseY = 0;

		if (_WndData.LCapture && _Wnd.GetMousePosition(_MouseX, _MouseY))
		{
			intptr_t _MouseDeltaX = _MouseX - _WndData.LCaptureMouseXLastFrame;
			intptr_t _MouseDeltaY = _MouseY - _WndData.LCaptureMouseYLastFrame;

			_WndData.LayoutMutex->lock();

			if (_WndData.LCapturePath.GetSize())
			{
				switch (_WndData.LCapturePath[0]->GetId())
				{
				case GUI::_LeftResizePopUpId:
				{
					MouseCaptureResize(_Wnd, _WndData, GUI::_LeftResizePopUpId, _MouseDeltaX, _MouseDeltaY);
					break;
				}
				case GUI::_RightResizePopUpId:
				{
					MouseCaptureResize(_Wnd, _WndData, GUI::_RightResizePopUpId, _MouseDeltaX, _MouseDeltaY);
					break;
				}
				case GUI::_TopResizePopUpId:
				{
					MouseCaptureResize(_Wnd, _WndData, GUI::_TopResizePopUpId, _MouseDeltaX, _MouseDeltaY);
					break;
				}
				case GUI::_BottomResizePopUpId:
				{
					MouseCaptureResize(_Wnd, _WndData, GUI::_BottomResizePopUpId, _MouseDeltaX, _MouseDeltaY);
					break;
				}
				case GUI::_LeftTopResizePopUpId:
				{
					MouseCaptureResize(_Wnd, _WndData, GUI::_LeftTopResizePopUpId, _MouseDeltaX, _MouseDeltaY);
					break;
				}
				case GUI::_LeftBottomResizePopUpId:
				{
					MouseCaptureResize(_Wnd, _WndData, GUI::_LeftBottomResizePopUpId, _MouseDeltaX, _MouseDeltaY);
					break;
				}
				case GUI::_RightTopResizePopUpId:
				{
					MouseCaptureResize(_Wnd, _WndData, GUI::_RightTopResizePopUpId, _MouseDeltaX, _MouseDeltaY);
					break;
				}
				case GUI::_RightBottomResizePopUpId:
				{
					MouseCaptureResize(_Wnd, _WndData, GUI::_RightBottomResizePopUpId, _MouseDeltaX, _MouseDeltaY);
					break;
				}
				case GUI::_HScrollWindowPopUpId:
				{
					intptr_t _LocalMouseX = _MouseX;
					intptr_t _LocalMouseY = _MouseY;

					BFW::GUI::PopUp::GlobalToLocal(_LocalMouseX, _LocalMouseY, _WndData.LCapturePath);

					_WndData.LCapturePath.PushBack(nullptr);

					for (size_t _Index = 0; _Index < _WndData.LCapturePath.GetSize() - 1; _Index++)
					{
						_WndData.LCapturePath[_WndData.LCapturePath.GetSize() - 1 - _Index] = _WndData.LCapturePath[_WndData.LCapturePath.GetSize() - 1 - _Index - 1];
					}

					_WndData.LCapturePath[0] = &_WndData.LCapturePath[1]->GetPopUps()[0][0];

					if (_Wnd.GetKeys()[VK_LBUTTON].JustPressed())
					{
						MouseCaptureScrollX(_Wnd, _WndData, _LocalMouseX - _WndData.LCapturePath[0]->GetPositionX() - _WndData.LCapturePath[0]->GetWidth() / 2);
					}
					else
					{
						MouseCaptureScrollX(_Wnd, _WndData, _MouseDeltaX);
					}

					_WndData.LCapturePath.Erase(0);

					break;
				}
				case GUI::_HScrollButtonPopUpId:
				{
					MouseCaptureScrollX(_Wnd, _WndData, _MouseDeltaX);
					break;
				}
				case GUI::_VScrollWindowPopUpId:
				{
					intptr_t _LocalMouseX = _MouseX;
					intptr_t _LocalMouseY = _MouseY;

					BFW::GUI::PopUp::GlobalToLocal(_LocalMouseX, _LocalMouseY, _WndData.LCapturePath);

					_WndData.LCapturePath.PushBack(nullptr);

					for (size_t _Index = 0; _Index < _WndData.LCapturePath.GetSize() - 1; _Index++)
					{
						_WndData.LCapturePath[_WndData.LCapturePath.GetSize() - 1 - _Index] = _WndData.LCapturePath[_WndData.LCapturePath.GetSize() - 1 - _Index - 1];
					}

					_WndData.LCapturePath[0] = &_WndData.LCapturePath[1]->GetPopUps()[0][0];

					if (_Wnd.GetKeys()[VK_LBUTTON].JustPressed())
					{
						MouseCaptureScrollY(_Wnd, _WndData, _LocalMouseY - _WndData.LCapturePath[0]->GetPositionY() - _WndData.LCapturePath[0]->GetHeight() / 2);
					}
					else
					{
						MouseCaptureScrollY(_Wnd, _WndData, _MouseDeltaY);
					}

					_WndData.LCapturePath.Erase(0);

					break;
				}
				case GUI::_VScrollButtonPopUpId:
				{
					MouseCaptureScrollY(_Wnd, _WndData, _MouseDeltaY);
					break;
				}
				case GUI::_DebugWindowPopUpId:
				{
					MouseCaptureMove(_Wnd, _WndData, _MouseDeltaX, _MouseDeltaY);
					break;
				}
				default:
				{
					break;
				}
				}
			}

			_WndData.LayoutMutex->unlock();

			_WndData.LCaptureMouseXLastFrame = _MouseX;
			_WndData.LCaptureMouseYLastFrame = _MouseY;
		}
	}

	if (_Wnd.GetKeys()[VK_MBUTTON].IsPressed())
	{
		intptr_t _MouseX = 0, _MouseY = 0;

		if (_WndData.MCapture && _Wnd.GetMousePosition(_MouseX, _MouseY))
		{
			intptr_t _MouseDeltaX = _MouseX - _WndData.MCaptureMouseXLastFrame;
			intptr_t _MouseDeltaY = _MouseY - _WndData.MCaptureMouseYLastFrame;

			_WndData.LayoutMutex->lock();

			bool _FoundScrolledWindow = false;

			size_t _WindowIndex = 0;

			while (_WindowIndex < _WndData.MCapturePath.GetSize())
			{
				bool _ShouldBreak = false;

				switch (_WndData.MCapturePath[_WindowIndex]->GetId())
				{
				case GUI::_DebugWindowPopUpId:
				{
					_FoundScrolledWindow = true;
					_ShouldBreak = true;
					break;
				}
				default:
				{
					break;
				}
				}

				if (_ShouldBreak)
				{
					break;
				}

				_WindowIndex++;
			}

			if (_FoundScrolledWindow)
			{
				MouseCaptureScroll(_Wnd, _WndData, _WindowIndex, _MouseX, _MouseY);
			}

			_WndData.LayoutMutex->unlock();

			_WndData.MCaptureMouseXLastFrame = _MouseX;
			_WndData.MCaptureMouseYLastFrame = _MouseY;
		}
	}

	if (_Wnd.GetKeys()[VK_RBUTTON].IsPressed())
	{
		intptr_t _MouseX = 0, _MouseY = 0;

		if (_WndData.RCapture && _Wnd.GetMousePosition(_MouseX, _MouseY))
		{
			intptr_t _MouseDeltaX = _MouseX - _WndData.RCaptureMouseXLastFrame;
			intptr_t _MouseDeltaY = _MouseY - _WndData.RCaptureMouseYLastFrame;

			_WndData.RCaptureMouseXLastFrame = _MouseX;
			_WndData.RCaptureMouseYLastFrame = _MouseY;
		}
	}

	if (_Wnd.GetKeys()[VK_XBUTTON1].IsPressed())
	{
		intptr_t _MouseX = 0, _MouseY = 0;

		if (_WndData.X1Capture && _Wnd.GetMousePosition(_MouseX, _MouseY))
		{
			intptr_t _MouseDeltaX = _MouseX - _WndData.X1CaptureMouseXLastFrame;
			intptr_t _MouseDeltaY = _MouseY - _WndData.X1CaptureMouseYLastFrame;

			_WndData.X1CaptureMouseXLastFrame = _MouseX;
			_WndData.X1CaptureMouseYLastFrame = _MouseY;
		}
	}

	if (_Wnd.GetKeys()[VK_XBUTTON2].IsPressed())
	{
		intptr_t _MouseX = 0, _MouseY = 0;

		if (_WndData.X2Capture && _Wnd.GetMousePosition(_MouseX, _MouseY))
		{
			intptr_t _MouseDeltaX = _MouseX - _WndData.X2CaptureMouseXLastFrame;
			intptr_t _MouseDeltaY = _MouseY - _WndData.X2CaptureMouseYLastFrame;

			_WndData.X2CaptureMouseXLastFrame = _MouseX;
			_WndData.X2CaptureMouseYLastFrame = _MouseY;
		}
	}

	if (_Wnd.GetKeys()[VK_LBUTTON].JustReleased())
	{
		intptr_t _MouseX = 0, _MouseY = 0;

		if (_WndData.LCapture && _Wnd.GetMousePosition(_MouseX, _MouseY))
		{
			intptr_t _MouseDeltaX = _MouseX - _WndData.LCaptureMouseXLastFrame;
			intptr_t _MouseDeltaY = _MouseY - _WndData.LCaptureMouseYLastFrame;

			_WndData.LayoutMutex->lock();

			BFW::GUI::PopUp* _ReleasePopUp = _WndData.Layout.GetChildFromMouse(_MouseX, _MouseY);

			if (_ReleasePopUp && _WndData.LCapturePath.GetSize() && _ReleasePopUp->GetId() == _WndData.LCapturePath[0]->GetId())
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

			_WndData.LayoutMutex->unlock();
		}

		_WndData.LCapture = false;
		_WndData.LCapturePath.Clear();
		_WndData.LCaptureMouseX = 0;
		_WndData.LCaptureMouseY = 0;
		_WndData.LCaptureMouseXLastFrame = 0;
		_WndData.LCaptureMouseYLastFrame = 0;
		_WndData.ResizeAccumulationX = 0;
		_WndData.ResizeAccumulationY = 0;
	}

	if (_Wnd.GetKeys()[VK_MBUTTON].JustReleased())
	{
		intptr_t _MouseX = 0, _MouseY = 0;

		if (_WndData.MCapture && _Wnd.GetMousePosition(_MouseX, _MouseY))
		{
			intptr_t _MouseDeltaX = _MouseX - _WndData.MCaptureMouseXLastFrame;
			intptr_t _MouseDeltaY = _MouseY - _WndData.MCaptureMouseYLastFrame;
		}

		_WndData.MCapture = false;
		_WndData.MCapturePath.Clear();
		_WndData.MCaptureMouseX = 0;
		_WndData.MCaptureMouseY = 0;
		_WndData.MCaptureMouseXLastFrame = 0;
		_WndData.MCaptureMouseYLastFrame = 0;
	}

	if (_Wnd.GetKeys()[VK_RBUTTON].JustReleased())
	{
		intptr_t _MouseX = 0, _MouseY = 0;

		if (_WndData.RCapture && _Wnd.GetMousePosition(_MouseX, _MouseY))
		{
			intptr_t _MouseDeltaX = _MouseX - _WndData.RCaptureMouseXLastFrame;
			intptr_t _MouseDeltaY = _MouseY - _WndData.RCaptureMouseYLastFrame;
		}

		_WndData.RCapture = false;
		_WndData.RCapturePath.Clear();
		_WndData.RCaptureMouseX = 0;
		_WndData.RCaptureMouseY = 0;
		_WndData.RCaptureMouseXLastFrame = 0;
		_WndData.RCaptureMouseYLastFrame = 0;
	}

	if (_Wnd.GetKeys()[VK_XBUTTON1].JustReleased())
	{
		intptr_t _MouseX = 0, _MouseY = 0;

		if (_WndData.X1Capture && _Wnd.GetMousePosition(_MouseX, _MouseY))
		{
			intptr_t _MouseDeltaX = _MouseX - _WndData.X1CaptureMouseXLastFrame;
			intptr_t _MouseDeltaY = _MouseY - _WndData.X1CaptureMouseYLastFrame;
		}

		_WndData.X1Capture = false;
		_WndData.X1CapturePath.Clear();
		_WndData.X1CaptureMouseX = 0;
		_WndData.X1CaptureMouseY = 0;
		_WndData.X1CaptureMouseXLastFrame = 0;
		_WndData.X1CaptureMouseYLastFrame = 0;
	}

	if (_Wnd.GetKeys()[VK_XBUTTON2].JustReleased())
	{
		intptr_t _MouseX = 0, _MouseY = 0;

		if (_WndData.X2Capture && _Wnd.GetMousePosition(_MouseX, _MouseY))
		{
			intptr_t _MouseDeltaX = _MouseX - _WndData.X2CaptureMouseXLastFrame;
			intptr_t _MouseDeltaY = _MouseY - _WndData.X2CaptureMouseYLastFrame;
		}

		_WndData.X2Capture = false;
		_WndData.X2CapturePath.Clear();
		_WndData.X2CaptureMouseX = 0;
		_WndData.X2CaptureMouseY = 0;
		_WndData.X2CaptureMouseXLastFrame = 0;
		_WndData.X2CaptureMouseYLastFrame = 0;
	}

	if (_IsMainWindow)
	{
		if (_Wnd.GetKeys()[VK_F11].JustPressed())
		{
			if (_Wnd.IsFullScreen())
			{
				_Wnd.GoWindowed();
			}
			else
			{
				_Wnd.GoFullScreen();
			}
		}
	}

	BFW::Vector<BFW::Input::WheelEvent> _WheelEventsX = _Wnd.GetHorizontalWheelEvents();

	for (size_t _Index = 0; _Index < _WheelEventsX.GetSize(); _Index++)
	{
		WheelScrollX(_Wnd, _WndData, _WheelEventsX[_Index].X, _WheelEventsX[_Index].Y, _WheelEventsX[_Index].Delta);
	}

	BFW::Vector<BFW::Input::WheelEvent> _WheelEventsY = _Wnd.GetWheelEvents();

	for (size_t _Index = 0; _Index < _WheelEventsY.GetSize(); _Index++)
	{
		WheelScrollY(_Wnd, _WndData, _WheelEventsY[_Index].X, _WheelEventsY[_Index].Y, _WheelEventsY[_Index].Delta);
	}

	_Wnd.CleanEvents();
}

void BFW_WINDOWS::RunTime::MainMenu::RenderWindow(BFW::GUI::Window& _Wnd, GUI::WindowData& _WndData)
{
	_WndData.LayoutMutex->lock();

	size_t _WndWidth = 0, _WndHeight = 0;

	_Wnd.GetClientSize(_WndWidth, _WndHeight);

	GUI::PopUpData& _WndPopUpData = *(GUI::PopUpData*)(_WndData.Layout.GetUserData());

	if (_WndWidth == 0 || _WndHeight == 0)
	{
		_WndWidth = _WndPopUpData.Width;
		_WndHeight = _WndPopUpData.Height;
	}

	size_t _TrueWidth = _WndWidth, _TrueHeight = _WndHeight;

	switch (_WndData.Layout.GetId())
	{
	case GUI::_DebugWindowPopUpId:
	{
		if (_TrueWidth < GUI::DebugWindowMinX)
		{
			_TrueWidth = GUI::DebugWindowMinX;
		}

		if (_TrueHeight < GUI::DebugWindowMinY)
		{
			_TrueHeight = GUI::DebugWindowMinY;
		}

		break;
	}
	case BFW::GUI::_NodePopUpId:
	{
		break;
	}
	default:
	{
		BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Can't resize unknown window type!"));
		break;
	}
	}

	if (_WndWidth != _WndData.Layout.GetWidth() || _WndHeight != _WndData.Layout.GetHeight() || _TrueWidth != _WndPopUpData.Width || _TrueHeight != _WndPopUpData.Height)
	{
		uint8_t* _Pixels = nullptr;

		if (_TrueWidth != _WndPopUpData.Width || _TrueHeight != _WndPopUpData.Height)
		{
			_Pixels = new uint8_t[_TrueWidth * _TrueHeight * 4];
		}
		else
		{
			_Pixels = _WndPopUpData.Pixels;
		}

		if (_Pixels)
		{
			if (_Pixels != _WndPopUpData.Pixels)
			{
				BFW_HEAP_PROFILE_PUSH(sizeof(uint8_t) * _WndWidth * _WndHeight * 4, _Pixels);

				BFW_HEAP_PROFILE_POP(_WndPopUpData.Pixels);
				delete[] _WndPopUpData.Pixels;

				_WndPopUpData.Width = _TrueWidth;
				_WndPopUpData.Height = _TrueHeight;
				_WndPopUpData.Pixels = _Pixels;
			}

			switch (_WndData.Layout.GetId())
			{
			case GUI::_DebugWindowPopUpId:
			{
				_WndData.Layout.SetWidth(_WndWidth);
				_WndData.Layout.SetHeight(_WndHeight);
				_WndData.Layout.SetTrueWidth(GUI::DebugWindowMinX);
				_WndData.Layout.SetTrueHeight(GUI::DebugWindowMinY);

				GUI::GenerateDebugWindow(_WndData.Layout, this, true);

				break;
			}
			case BFW::GUI::_NodePopUpId:
			{
				_WndData.Layout.SetWidth(_WndWidth);
				_WndData.Layout.SetHeight(_WndHeight);
				_WndData.Layout.SetTrueWidth(0);
				_WndData.Layout.SetTrueHeight(0);

				GUI::ResizeChilds(_WndData.Layout, this);

				break;
			}
			default:
			{
				BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Can't resize unknown window type!"));
				break;
			}
			}
		}
	}

	_WndData.Layout.Render(this);

	intptr_t _MouseX = 0, _MouseY = 0;

	if (_Wnd.GetMousePosition(_MouseX, _MouseY))
	{
		bool _CursorSet = false;

		if (!_CursorSet && _WndData.MCapture)
		{
			bool _FoundScrolledWindow = false;

			size_t _WindowIndex = 0;

			while (_WindowIndex < _WndData.MCapturePath.GetSize())
			{
				bool _ShouldBreak = false;

				switch (_WndData.MCapturePath[_WindowIndex]->GetId())
				{
				case GUI::_DebugWindowPopUpId:
				{
					_FoundScrolledWindow = true;
					_ShouldBreak = true;
					break;
				}
				default:
				{
					break;
				}
				}

				if (_ShouldBreak)
				{
					break;
				}

				_WindowIndex++;
			}

			if (_FoundScrolledWindow)
			{
				BFW::GUI::PopUp& _ScrolledWindow = *_WndData.MCapturePath[_WindowIndex];

				bool _FoundHScrollWindow = false;
				bool _FoundVScrollWindow = false;
				size_t _ScrollWindowIndex = 0;

				while (_ScrollWindowIndex < _ScrolledWindow.GetPopUps().GetSize())
				{
					bool _ShouldBreak = false;

					if (_ScrolledWindow.GetPopUps()[_ScrollWindowIndex][0].GetId() == GUI::_HScrollWindowPopUpId)
					{
						_FoundHScrollWindow = true;
						_ShouldBreak = true;
					}

					if (_ScrolledWindow.GetPopUps()[_ScrollWindowIndex][0].GetId() == GUI::_VScrollWindowPopUpId)
					{
						_FoundVScrollWindow = true;
						_ShouldBreak = true;
					}

					if (_ShouldBreak)
					{
						break;
					}

					_ScrollWindowIndex++;
				}

				if (_FoundHScrollWindow || _FoundVScrollWindow)
				{
					_CursorSet = true;
					_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_SIZEALL));
				}
			}
		}

		if (!_CursorSet && _WndData.LCapture && _WndData.LCapturePath.GetSize())
		{
			_CursorSet = true;
			GUI::RenderCursor(_Wnd, _WndData.LCapturePath[0]->GetId());
		}

		if (!_CursorSet)
		{
			_CursorSet = true;

			BFW::GUI::PopUp* _HoverPopUp = _WndData.Layout.GetChildFromMouse(_MouseX, _MouseY);

			if (_HoverPopUp)
			{
				GUI::RenderCursor(_Wnd, _HoverPopUp->GetId());
			}
			else
			{
				GUI::RenderCursor(_Wnd, BFW::GUI::_NodePopUpId);
			}
		}
	}

	_WndData.LayoutMutex->unlock();

	_Wnd.UpdateContent();
}

void BFW_WINDOWS::RunTime::MainMenu::Input()
{
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
	BFW::GUI::Window& _MainWindow = _ApplicationObj.GetMainWindow();
	GUI::WindowData& _MainWindowData = _ApplicationObj.GetMainWindowData();
	BFW::Vector<BFW::GUI::Window*>& _ChildWindows = _ApplicationObj.GetChildWindows();
	BFW::Vector<GUI::WindowData*>& _ChildWindowsData = _ApplicationObj.GetChildWindowsData();

	DeleteMouseCaptureInputs(_MainWindow, _MainWindowData);

	for (size_t _Index = 0; _Index < _ChildWindows.GetSize(); _Index++)
	{
		DeleteMouseCaptureInputs(*_ChildWindows[_Index], *_ChildWindowsData[_Index]);
	}

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
	BFW::Vector<BFW::GUI::Window*>& _ChildWindows = _ApplicationObj.GetChildWindows();
	BFW::Vector<GUI::WindowData*>& _ChildWindowsData = _ApplicationObj.GetChildWindowsData();

	if (_MainWindow.ShouldClose())
	{
		_ApplicationObj.Close(BFW::MultiProcessing::_NoErrorReturnValue);
	}

	for (size_t _Index = 0; _Index < _ChildWindows.GetSize(); _Index++)
	{
		if (_ChildWindows[_Index]->ShouldClose())
		{
			_ApplicationObj.RemoveChildWindow(_Index);
			_Index--;
		}
	}

	HandleWindowInputs(_MainWindow, _MainWindowData, true);

	for (size_t _Index = 0; _Index < _ChildWindows.GetSize(); _Index++)
	{
		HandleWindowInputs(*_ChildWindows[_Index], *_ChildWindowsData[_Index], false);
	}

	BFW::Input::Controller::SetRumble(0, 0.0f, 0.0f);
	BFW::Input::Controller::SetRumble(1, 0.0f, 0.0f);
	BFW::Input::Controller::SetRumble(2, 0.0f, 0.0f);
	BFW::Input::Controller::SetRumble(3, 0.0f, 0.0f);

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
	Application& _ApplicationObj = *(Application*)(GetApplicationObj());
	BFW::GUI::Window& _MainWindow = _ApplicationObj.GetMainWindow();
	GUI::WindowData& _MainWindowData = _ApplicationObj.GetMainWindowData();
	BFW::Vector<BFW::GUI::Window*>& _ChildWindows = _ApplicationObj.GetChildWindows();
	BFW::Vector<GUI::WindowData*>& _ChildWindowsData = _ApplicationObj.GetChildWindowsData();

	RenderWindow(_MainWindow, _MainWindowData);

	for (size_t _Index = 0; _Index < _ChildWindows.GetSize(); _Index++)
	{
		RenderWindow(*_ChildWindows[_Index], *_ChildWindowsData[_Index]);
	}
}
