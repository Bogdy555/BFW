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

	_MainWindowData.RenderingMutex->lock();

	GUI::PopUpData& _MainWindowPopUpData = *(GUI::PopUpData*)(_MainWindowData.Layout.GetUserData());

	_MainWindowData.Layout.Begin
	(
		BFW::GUI::_NodePopUpId, BFW::GUI::_NullPanelType,
		0, 0,
		_MainWindowPopUpData.Width, _MainWindowPopUpData.Height,
		0, 0,
		0, 0,
		GUI::SetupRenderData, GUI::CleanUpRenderData,
		GUI::RenderGray25, nullptr, nullptr,
		GUI::Composit,
		_MainWindowData.Layout.GetUserData()
	);

	GUI::GenerateExample
	(
		_MainWindowData.Layout.PushLeftPanel
		(
			GUI::_ExamplePopUpId,
			GUI::ExampleMinX, GUI::ExampleMinY,
			GUI::ExampleMinX,
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

	GUI::GenerateExample
	(
		_MainWindowData.Layout.GetNodes()[0].PushBottomPanel
		(
			GUI::_ExamplePopUpId,
			GUI::ExampleMinX, GUI::ExampleMinY,
			GUI::ExampleMinY,
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

	GUI::GenerateExample
	(
		_MainWindowData.Layout.GetNodes()[0].GetNodes()[0].PushRightPanel
		(
			GUI::_ExamplePopUpId,
			GUI::ExampleMinX, GUI::ExampleMinY,
			GUI::ExampleMinX,
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

	GUI::GenerateExample
	(
		_MainWindowData.Layout.GetNodes()[0].GetNodes()[0].GetNodes()[0].PushTopPanel
		(
			GUI::_ExamplePopUpId,
			GUI::ExampleMinX, GUI::ExampleMinY,
			GUI::ExampleMinY,
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

	GUI::GenerateExample
	(
		_MainWindowData.Layout.PushPopUp
		(
			_Layer, GUI::_ExamplePopUpId,
			GUI::ExampleMinX, GUI::ExampleMinY,
			GUI::ExampleMinX, GUI::ExampleMinY,
			GUI::ExampleMinX * 2, GUI::ExampleMinY * 2,
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

	_MainWindowData.RenderingMutex->unlock();
}

void BFW_WINDOWS::RunTime::MainMenu::CleanUpGUI()
{
	Application& _ApplicationObj = *(Application*)(GetApplicationObj());
	BFW::GUI::Window& _MainWindow = _ApplicationObj.GetMainWindow();
	GUI::WindowData& _MainWindowData = _ApplicationObj.GetMainWindowData();
	BFW::Vector<BFW::GUI::Window*>& _ChildWindows = _ApplicationObj.GetChildWindows();
	BFW::Vector<GUI::WindowData*>& _ChildWindowsData = _ApplicationObj.GetChildWindowsData();

	_MainWindowData.RenderingMutex->lock();

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

	_MainWindowData.RenderingMutex->unlock();

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

	if (!_ChildWindows[_ChildWindows.GetSize() - 1]->Create(NULL, BFW_WINDOWS_CHILD_WINDOW_CLASS, nullptr, WS_POPUP, _Cursor.x - (int32_t)(GUI::ChildMinX / 2), _Cursor.y - (int32_t)(GUI::ChildMinY / 2), (int32_t)(GUI::ChildMinX), (int32_t)(GUI::ChildMinY), _MainWindow, NULL, _ApplicationObj.GetInstanceHandle(), nullptr, NULL, GUI::ChildWindowThreadInit, GUI::ChildWindowThreadCleanUp, GUI::ChildWindowInit, GUI::ChildWindowCleanUp, _ChildWindowsData[_ChildWindowsData.GetSize() - 1]))
	{
		_ApplicationObj.RemoveChildWindow(_ChildWindows.GetSize() - 1);
		return false;
	}

	if (!_ChildWindows[_ChildWindows.GetSize() - 1]->Show(SW_SHOW))
	{
		_ApplicationObj.RemoveChildWindow(_ChildWindows.GetSize() - 1);
		return false;
	}

	_ChildWindowsData[_ChildWindowsData.GetSize() - 1]->RenderingMutex->lock();

	GUI::GenerateExample
	(
		_ChildWindowsData[_ChildWindowsData.GetSize() - 1]->Layout.Begin
		(
			GUI::_ExamplePopUpId, BFW::GUI::_NullPanelType,
			GUI::ExampleMinX, GUI::ExampleMinY,
			GUI::ExampleMinX, GUI::ExampleMinY,
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

	_ChildWindowsData[_ChildWindowsData.GetSize() - 1]->RenderingMutex->unlock();

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
			case GUI::_ExamplePopUpId:
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
					_WndData.LCapturePath[2]->GetPanels()[_Index].SetTrueWidth(GUI::ExampleMinX);
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
					_WndData.LCapturePath[2]->GetPanels()[_Index].SetTrueWidth(GUI::ExampleMinX);

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
					_WndData.LCapturePath[2]->GetPanels()[_Index].SetTrueHeight(GUI::ExampleMinY);
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
					_WndData.LCapturePath[2]->GetPanels()[_Index].SetTrueHeight(GUI::ExampleMinY);

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
				_WndData.LCapturePath[0] = &_WndData.LCapturePath[2]->GetPanels()[_Index].GetPopUps()[0][0];
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
				case GUI::_ExamplePopUpId:
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
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetTrueWidth(GUI::ExampleMinX);
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
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetTrueWidth(GUI::ExampleMinX);

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
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetTrueHeight(GUI::ExampleMinY);
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
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetTrueHeight(GUI::ExampleMinY);

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
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetTrueWidth(GUI::ExampleMinX);
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetTrueHeight(GUI::ExampleMinY);
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
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetTrueWidth(GUI::ExampleMinX);
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetTrueHeight(GUI::ExampleMinY);
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
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetTrueHeight(GUI::ExampleMinY);
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetTrueWidth(GUI::ExampleMinX);
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
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetTrueWidth(GUI::ExampleMinX);
						_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].SetTrueHeight(GUI::ExampleMinY);

						break;
					}
					default:
					{
						break;
					}
					}

					GUI::GenerateExample(_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index], this, false);

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
					switch (_ResizePopUpId)
					{
					case GUI::_LeftResizePopUpId:
					{
						_WndData.LCapturePath[0] = &_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetPopUps()[0][0];
						break;
					}
					case GUI::_RightResizePopUpId:
					{
						_WndData.LCapturePath[0] = &_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetPopUps()[1][0];
						break;
					}
					case GUI::_TopResizePopUpId:
					{
						_WndData.LCapturePath[0] = &_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetPopUps()[2][0];
						break;
					}
					case GUI::_BottomResizePopUpId:
					{
						_WndData.LCapturePath[0] = &_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetPopUps()[3][0];
						break;
					}
					case GUI::_LeftTopResizePopUpId:
					{
						_WndData.LCapturePath[0] = &_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetPopUps()[4][0];
						break;
					}
					case GUI::_LeftBottomResizePopUpId:
					{
						_WndData.LCapturePath[0] = &_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetPopUps()[5][0];
						break;
					}
					case GUI::_RightTopResizePopUpId:
					{
						_WndData.LCapturePath[0] = &_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetPopUps()[6][0];
						break;
					}
					case GUI::_RightBottomResizePopUpId:
					{
						_WndData.LCapturePath[0] = &_WndData.LCapturePath[2]->GetPopUps()[_Layer][_Index].GetPopUps()[7][0];
						break;
					}
					default:
					{
						break;
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
		if (_Wnd.GetKeys()[VK_LBUTTON].JustPressed())
		{
			_WndData.LCapture = true;
			_WndData.RenderingMutex->lock();
			_WndData.Layout.GetChildFromMouse(_MouseX, _MouseY, &_WndData.LCapturePath);
			_WndData.RenderingMutex->unlock();
			_WndData.LCaptureMouseX = _MouseX;
			_WndData.LCaptureMouseY = _MouseY;
			_WndData.LCaptureMouseXLastFrame = _MouseX;
			_WndData.LCaptureMouseYLastFrame = _MouseY;
		}

		if (_Wnd.GetKeys()[VK_MBUTTON].JustPressed())
		{
			_WndData.MCapture = true;
			_WndData.RenderingMutex->lock();
			_WndData.Layout.GetChildFromMouse(_MouseX, _MouseY, &_WndData.MCapturePath);
			_WndData.RenderingMutex->unlock();
			_WndData.MCaptureMouseX = _MouseX;
			_WndData.MCaptureMouseY = _MouseY;
			_WndData.MCaptureMouseXLastFrame = _MouseX;
			_WndData.MCaptureMouseYLastFrame = _MouseY;
		}

		if (_Wnd.GetKeys()[VK_RBUTTON].JustPressed())
		{
			_WndData.RCapture = true;
			_WndData.RenderingMutex->lock();
			_WndData.Layout.GetChildFromMouse(_MouseX, _MouseY, &_WndData.RCapturePath);
			_WndData.RenderingMutex->unlock();
			_WndData.RCaptureMouseX = _MouseX;
			_WndData.RCaptureMouseY = _MouseY;
			_WndData.RCaptureMouseXLastFrame = _MouseX;
			_WndData.RCaptureMouseYLastFrame = _MouseY;
		}

		if (_Wnd.GetKeys()[VK_XBUTTON1].JustPressed())
		{
			_WndData.X1Capture = true;
			_WndData.RenderingMutex->lock();
			_WndData.Layout.GetChildFromMouse(_MouseX, _MouseY, &_WndData.X1CapturePopUp);
			_WndData.RenderingMutex->unlock();
			_WndData.X1CaptureMouseX = _MouseX;
			_WndData.X1CaptureMouseY = _MouseY;
			_WndData.X1CaptureMouseXLastFrame = _MouseX;
			_WndData.X1CaptureMouseYLastFrame = _MouseY;
		}

		if (_Wnd.GetKeys()[VK_XBUTTON2].JustPressed())
		{
			_WndData.X2Capture = true;
			_WndData.RenderingMutex->lock();
			_WndData.Layout.GetChildFromMouse(_MouseX, _MouseY, &_WndData.X2CapturePopUp);
			_WndData.RenderingMutex->unlock();
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
	_WndData.X1CapturePopUp.Clear();
	_WndData.X1CaptureMouseX = 0;
	_WndData.X1CaptureMouseY = 0;
	_WndData.X1CaptureMouseXLastFrame = 0;
	_WndData.X1CaptureMouseYLastFrame = 0;

	_WndData.X2Capture = false;
	_WndData.X2CapturePopUp.Clear();
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

	if (_Wnd.GetKeys()[VK_LBUTTON].IsPressed())
	{
		intptr_t _MouseX = 0, _MouseY = 0;

		if (_WndData.LCapture && _Wnd.GetMousePosition(_MouseX, _MouseY))
		{
			intptr_t _MouseDeltaX = _MouseX - _WndData.LCaptureMouseXLastFrame;
			intptr_t _MouseDeltaY = _MouseY - _WndData.LCaptureMouseYLastFrame;

			_WndData.RenderingMutex->lock();

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
			case GUI::_ExamplePopUpId:
			{
				MouseCaptureMove(_Wnd, _WndData, _MouseDeltaX, _MouseDeltaY);
				break;
			}
			default:
			{
				break;
			}
			}

			_WndData.RenderingMutex->unlock();

			_WndData.LCaptureMouseXLastFrame = _MouseX;
			_WndData.LCaptureMouseYLastFrame = _MouseY;
		}
	}

	if (_Wnd.GetKeys()[VK_MBUTTON].IsPressed())
	{
		intptr_t _MouseX = 0, _MouseY = 0;

		if (_WndData.MCapture && _Wnd.GetMousePosition(_MouseX, _MouseY))
		{
			_WndData.MCaptureMouseXLastFrame = _MouseX;
			_WndData.MCaptureMouseYLastFrame = _MouseY;
		}
	}

	if (_Wnd.GetKeys()[VK_RBUTTON].IsPressed())
	{
		intptr_t _MouseX = 0, _MouseY = 0;

		if (_WndData.RCapture && _Wnd.GetMousePosition(_MouseX, _MouseY))
		{
			_WndData.RCaptureMouseXLastFrame = _MouseX;
			_WndData.RCaptureMouseYLastFrame = _MouseY;
		}
	}

	if (_Wnd.GetKeys()[VK_XBUTTON1].IsPressed())
	{
		intptr_t _MouseX = 0, _MouseY = 0;

		if (_WndData.X1Capture && _Wnd.GetMousePosition(_MouseX, _MouseY))
		{
			_WndData.X1CaptureMouseXLastFrame = _MouseX;
			_WndData.X1CaptureMouseYLastFrame = _MouseY;
		}
	}

	if (_Wnd.GetKeys()[VK_XBUTTON2].IsPressed())
	{
		intptr_t _MouseX = 0, _MouseY = 0;

		if (_WndData.X2Capture && _Wnd.GetMousePosition(_MouseX, _MouseY))
		{
			_WndData.X2CaptureMouseXLastFrame = _MouseX;
			_WndData.X2CaptureMouseYLastFrame = _MouseY;
		}
	}

	if (_Wnd.GetKeys()[VK_LBUTTON].JustReleased())
	{
		intptr_t _MouseX = 0, _MouseY = 0;

		if (_WndData.LCapture && _Wnd.GetMousePosition(_MouseX, _MouseY))
		{
			_WndData.RenderingMutex->lock();

			BFW::GUI::PopUp* _ReleasePopUp = _WndData.Layout.GetChildFromMouse(_MouseX, _MouseY);

			if (_ReleasePopUp && _ReleasePopUp->GetId() == _WndData.LCapturePath[0]->GetId())
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

			_WndData.RenderingMutex->unlock();
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
		_WndData.MCapture = false;
		_WndData.MCapturePath.Clear();
		_WndData.MCaptureMouseX = 0;
		_WndData.MCaptureMouseY = 0;
		_WndData.MCaptureMouseXLastFrame = 0;
		_WndData.MCaptureMouseYLastFrame = 0;
	}

	if (_Wnd.GetKeys()[VK_RBUTTON].JustReleased())
	{
		_WndData.RCapture = false;
		_WndData.RCapturePath.Clear();
		_WndData.RCaptureMouseX = 0;
		_WndData.RCaptureMouseY = 0;
		_WndData.RCaptureMouseXLastFrame = 0;
		_WndData.RCaptureMouseYLastFrame = 0;
	}

	if (_Wnd.GetKeys()[VK_XBUTTON1].JustReleased())
	{
		_WndData.X1Capture = false;
		_WndData.X1CapturePopUp.Clear();
		_WndData.X1CaptureMouseX = 0;
		_WndData.X1CaptureMouseY = 0;
		_WndData.X1CaptureMouseXLastFrame = 0;
		_WndData.X1CaptureMouseYLastFrame = 0;
	}

	if (_Wnd.GetKeys()[VK_XBUTTON2].JustReleased())
	{
		_WndData.X2Capture = false;
		_WndData.X2CapturePopUp.Clear();
		_WndData.X2CaptureMouseX = 0;
		_WndData.X2CaptureMouseY = 0;
		_WndData.X2CaptureMouseXLastFrame = 0;
		_WndData.X2CaptureMouseYLastFrame = 0;
	}

	_Wnd.CleanEvents();
}

void BFW_WINDOWS::RunTime::MainMenu::RenderWindow(BFW::GUI::Window& _Wnd, GUI::WindowData& _WndData)
{
	Application& _ApplicationObj = *(Application*)(GetApplicationObj());
	BFW::GUI::Window& _MainWindow = _ApplicationObj.GetMainWindow();
	GUI::WindowData& _MainWindowData = _ApplicationObj.GetMainWindowData();
	BFW::Vector<BFW::GUI::Window*>& _ChildWindows = _ApplicationObj.GetChildWindows();
	BFW::Vector<GUI::WindowData*>& _ChildWindowsData = _ApplicationObj.GetChildWindowsData();

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
		uint8_t* _Pixels = new uint8_t[_WndWidth * _WndHeight * 4];

		if (_Pixels)
		{
			BFW_HEAP_PROFILE_PUSH(sizeof(uint8_t) * _WndWidth * _WndHeight * 4, _Pixels);

			BFW_HEAP_PROFILE_POP(_WndPopUpData.Pixels);
			delete[] _WndPopUpData.Pixels;

			_WndPopUpData.Width = _WndWidth;
			_WndPopUpData.Height = _WndHeight;
			_WndPopUpData.Pixels = _Pixels;

			switch (_WndData.Layout.GetId())
			{
			case GUI::_ExamplePopUpId:
			{
				_WndData.Layout.SetWidth(_WndWidth);
				_WndData.Layout.SetHeight(_WndHeight);
				_WndData.Layout.SetTrueWidth(GUI::ExampleMinX);
				_WndData.Layout.SetTrueHeight(GUI::ExampleMinY);

				GUI::GenerateExample(_WndData.Layout, this, true);

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
		if (_WndData.LCapture)
		{
			GUI::RenderCursor(_Wnd, _WndData.LCapturePath[0]->GetId());
		}
		else
		{
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

	_WndData.RenderingMutex->unlock();

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

	bool _Focus = _MainWindow.HasFocus();

	for (size_t _Index = 0; _Index < _ChildWindows.GetSize(); _Index++)
	{
		if (_ChildWindows[_Index]->HasFocus())
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
