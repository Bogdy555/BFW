#include "../Headers/BFW.hpp"



#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

static BFW::GUI::Window* LastWnd = nullptr;
static std::mutex LastWndMutex;

#endif



#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

BFW::GUI::Window::Window() : Handle(NULL), WndThread(nullptr), UserData(nullptr), FullScreen(false), WndRect({ 0 }), WndPlace({ 0 }), WindowMutex(nullptr), Cursor(LoadCursor(NULL, IDC_ARROW)), Close(false), Focus(false), RawKeys(), Keys(), Tracking(false), HasMouse(false), MouseX(0), MouseY(0), KeyEvents(), LClicks(), RClicks(), MClicks(), X1Clicks(), X2Clicks(), LDblClicks(), RDblClicks(), MDblClicks(), X1DblClicks(), X2DblClicks(), WheelEvents(), HWheelEvents(), CharEvents()
{
	for (size_t _Index = 0; _Index < 256; _Index++)
	{
		RawKeys[_Index] = false;
	}
}

BFW::GUI::Window::~Window()
{
	Destroy();
}

const bool BFW::GUI::Window::Create(const uint32_t _ExStyle, const BFW_CHAR_TYPE* _ClassName, const BFW_CHAR_TYPE* _WindowName, const uint32_t _Style, const int32_t _X, const int32_t _Y, const int32_t _Width, const int32_t _Height, const HWND _ParentHandle, const HMENU _MenuHandle, const HINSTANCE _InstanceHandle, void* _Param, const HACCEL _AccelHandle, const ThreadInitFnc _ThreadInit, const ThreadCleanUpFnc _ThreadCleanUp, const WndInitFnc _WndInit, const WndCleanUpFnc _WndCleanUp, void* _UserData)
{
	Destroy();

	if (!_ClassName)
	{
		return false;
	}

	WindowMutex = new std::mutex;

	if (!WindowMutex)
	{
		return false;
	}

	BFW_HEAP_PROFILE_PUSH(sizeof(std::mutex), WindowMutex);

	bool _Done = false;
	bool _Fail = false;

	WndThread = new std::thread(WndThreadFnc, std::ref(_Done), std::ref(_Fail), this, _ExStyle, _ClassName, _WindowName, _Style, _X, _Y, _Width, _Height, _ParentHandle, _MenuHandle, _InstanceHandle, _Param, _AccelHandle, _ThreadInit, _ThreadCleanUp, _WndInit, _WndCleanUp, _UserData);

	if (!WndThread)
	{
		BFW_HEAP_PROFILE_POP(WindowMutex);
		delete WindowMutex;
		WindowMutex = nullptr;
		return false;
	}

	BFW_HEAP_PROFILE_PUSH(sizeof(std::thread), WndThread);

	while (!_Done)
	{
		Time::Sleep(1);
	}

	if (_Fail)
	{
		WndThread->join();
		BFW_HEAP_PROFILE_POP(WndThread);
		delete WndThread;
		WndThread = nullptr;
		BFW_HEAP_PROFILE_POP(WindowMutex);
		delete WindowMutex;
		WindowMutex = nullptr;
		return false;
	}

	return true;
}

void BFW::GUI::Window::Destroy()
{
	if (!Handle)
	{
		return;
	}

	PostMessage(Handle, WM_QUIT, 0, 0);
	WndThread->join();
	BFW_HEAP_PROFILE_POP(WndThread);
	delete WndThread;
	WndThread = nullptr;
	FullScreen = false;
	WndRect = { 0 };
	WndPlace = { 0 };
	BFW_HEAP_PROFILE_POP(WindowMutex);
	delete WindowMutex;
	WindowMutex = nullptr;
	Cursor = LoadCursor(NULL, IDC_ARROW);
	Close = false;
	Focus = false;
	for (size_t _Index = 0; _Index < 256; _Index++)
	{
		RawKeys[_Index] = false;
	}
	for (size_t _Index = 0; _Index < 256; _Index++)
	{
		Keys[_Index].CleanState();
	}
	Tracking = false;
	HasMouse = false;
	MouseX = 0;
	MouseY = 0;
	KeyEvents.Clear();
	LClicks.Clear();
	MClicks.Clear();
	RClicks.Clear();
	X1Clicks.Clear();
	X2Clicks.Clear();
	LDblClicks.Clear();
	MDblClicks.Clear();
	RDblClicks.Clear();
	X1DblClicks.Clear();
	X2DblClicks.Clear();
	WheelEvents.Clear();
	HWheelEvents.Clear();
	CharEvents.Clear();
}

const bool BFW::GUI::Window::GoFullScreen(const HWND _InsertAfter, const uint32_t _Flags)
{
	if (!Handle)
	{
		return false;
	}

	if (FullScreen)
	{
		return true;
	}

	if (!GetWindowRect(Handle, &WndRect))
	{
		return false;
	}

	if (!GetWindowPlacement(Handle, &WndPlace))
	{
		WndRect = { 0 };
		return false;
	}

	HMONITOR _MonitorHandle = MonitorFromWindow(Handle, MONITOR_DEFAULTTOPRIMARY);

	if (!_MonitorHandle)
	{
		WndRect = { 0 };
		WndPlace = { 0 };
		return false;
	}

	MONITORINFOEX _MonitorInfo = { 0 };

	_MonitorInfo.cbSize = sizeof(MONITORINFOEX);

	if (!GetMonitorInfo(_MonitorHandle, &_MonitorInfo))
	{
		WndRect = { 0 };
		WndPlace = { 0 };
		return false;
	}

	if (!SetWindowLong(Handle, GWL_STYLE, WS_POPUP))
	{
		WndRect = { 0 };
		WndPlace = { 0 };
		return false;
	}

	if (!SetWindowPos(Handle, _InsertAfter, _MonitorInfo.rcMonitor.left, _MonitorInfo.rcMonitor.top, _MonitorInfo.rcMonitor.right - _MonitorInfo.rcMonitor.left, _MonitorInfo.rcMonitor.bottom - _MonitorInfo.rcMonitor.top, _Flags))
	{
		WndRect = { 0 };
		WndPlace = { 0 };
		return false;
	}

	Show(SW_SHOW);

	FullScreen = true;

	return true;
}

const bool BFW::GUI::Window::GoWindowed(const uint32_t _Style, const HWND _InsertAfter, const uint32_t _Flags)
{
	if (!Handle)
	{
		return false;
	}

	if (!FullScreen)
	{
		return true;
	}

	if (!SetWindowLong(Handle, GWL_STYLE, _Style))
	{
		return false;
	}

	if (WndPlace.showCmd == SW_NORMAL)
	{
		if (!SetWindowPos(Handle, _InsertAfter, WndRect.left, WndRect.top, WndRect.right - WndRect.left, WndRect.bottom - WndRect.top, _Flags))
		{
			return false;
		}

		Show(SW_SHOW);

		FullScreen = false;
		WndRect = { 0 };
		WndPlace = { 0 };

		return true;
	}

	if (!SetWindowPos(Handle, _InsertAfter, WndPlace.rcNormalPosition.left, WndPlace.rcNormalPosition.top, WndPlace.rcNormalPosition.right - WndPlace.rcNormalPosition.left, WndPlace.rcNormalPosition.bottom - WndPlace.rcNormalPosition.top, _Flags))
	{
		return false;
	}

	Show(WndPlace.showCmd);

	FullScreen = false;
	WndRect = { 0 };
	WndPlace = { 0 };

	return true;
}

void BFW::GUI::Window::SetCursorIcon(const HCURSOR _Cursor)
{
	if (!Handle)
	{
		return;
	}

	WindowMutex->lock();
	Cursor = _Cursor;
	WindowMutex->unlock();

	PostMessage(Handle, WM_SETCURSOR, (WPARAM)(Handle), MAKELPARAM(HTCLIENT, WM_MOUSEMOVE));
}

void BFW::GUI::Window::UpdateInputState()
{
	if (!Handle)
	{
		return;
	}

	WindowMutex->lock();

	for (size_t _Index = 0; _Index < 256; _Index++)
	{
		Keys[_Index].UpdateState(RawKeys[_Index]);
	}

	if (!Focus)
	{
		CleanInputState();
	}

	WindowMutex->unlock();
}

void BFW::GUI::Window::CleanInputState()
{
	for (size_t _Index = 0; _Index < 256; _Index++)
	{
		Keys[_Index].CleanState();
	}
}

void BFW::GUI::Window::CleanEvents()
{
	if (!Handle)
	{
		return;
	}

	WindowMutex->lock();

	Close = false;
	KeyEvents.Clear();
	LClicks.Clear();
	MClicks.Clear();
	RClicks.Clear();
	X1Clicks.Clear();
	X2Clicks.Clear();
	LDblClicks.Clear();
	MDblClicks.Clear();
	RDblClicks.Clear();
	X1DblClicks.Clear();
	X2DblClicks.Clear();
	WheelEvents.Clear();
	HWheelEvents.Clear();
	CharEvents.Clear();

	WindowMutex->unlock();
}

const bool BFW::GUI::Window::Show(const int32_t _ShowCmd)
{
	if (!Handle)
	{
		return false;
	}

	return ShowWindowAsync(Handle, _ShowCmd);
}

const bool BFW::GUI::Window::UpdateContent()
{
	if (!Handle)
	{
		return false;
	}

	if (!InvalidateRect(Handle, nullptr, false))
	{
		return false;
	}

	return UpdateWindow(Handle);
}

const bool BFW::GUI::Window::CheckOn() const
{
	return Handle != NULL;
}

const HWND BFW::GUI::Window::GetHandle() const
{
	return Handle;
}

void* BFW::GUI::Window::GetUserData()
{
	return UserData;
}

const void* BFW::GUI::Window::GetUserData() const
{
	return UserData;
}

const bool BFW::GUI::Window::IsFullScreen() const
{
	return FullScreen;
}

const HCURSOR BFW::GUI::Window::GetCursorIcon() const
{
	if (!Handle)
	{
		return NULL;
	}

	WindowMutex->lock();
	HCURSOR _Cursor = Cursor;
	WindowMutex->unlock();

	return _Cursor;
}

const bool BFW::GUI::Window::ShouldClose() const
{
	if (!Handle)
	{
		return false;
	}

	WindowMutex->lock();
	bool _Close = Close;
	WindowMutex->unlock();

	return _Close;
}

const bool BFW::GUI::Window::HasFocus() const
{
	if (!Handle)
	{
		return false;
	}

	WindowMutex->lock();
	bool _Focus = Focus;
	WindowMutex->unlock();

	return _Focus;
}

const BFW::Input::Key* BFW::GUI::Window::GetKeys() const
{
	return Keys;
}

const bool BFW::GUI::Window::GetMousePosition(intptr_t& _MouseX, intptr_t& _MouseY) const
{
	_MouseX = 0;
	_MouseY = 0;

	if (!Handle)
	{
		return false;
	}

	WindowMutex->lock();
	bool _HasMouse = HasMouse;
	_MouseX = MouseX;
	_MouseY = MouseY;
	WindowMutex->unlock();

	return _HasMouse;
}

const BFW::Vector<uint8_t> BFW::GUI::Window::GetKeyEvents() const
{
	Vector<uint8_t> _KeyEvents;

	if (!Handle)
	{
		return _KeyEvents;
	}

	WindowMutex->lock();
	_KeyEvents = KeyEvents;
	WindowMutex->unlock();

	return _KeyEvents;
}

const BFW::Vector<BFW::Input::ClickEvent> BFW::GUI::Window::GetLeftClicks() const
{
	Vector<Input::ClickEvent> _Clicks;

	if (!Handle)
	{
		return _Clicks;
	}

	WindowMutex->lock();
	_Clicks = LClicks;
	WindowMutex->unlock();

	return _Clicks;
}

const BFW::Vector<BFW::Input::ClickEvent> BFW::GUI::Window::GetRightClicks() const
{
	Vector<Input::ClickEvent> _Clicks;

	if (!Handle)
	{
		return _Clicks;
	}

	WindowMutex->lock();
	_Clicks = RClicks;
	WindowMutex->unlock();

	return _Clicks;
}

const BFW::Vector<BFW::Input::ClickEvent> BFW::GUI::Window::GetMiddleClicks() const
{
	Vector<Input::ClickEvent> _Clicks;

	if (!Handle)
	{
		return _Clicks;
	}

	WindowMutex->lock();
	_Clicks = MClicks;
	WindowMutex->unlock();

	return _Clicks;
}

const BFW::Vector<BFW::Input::ClickEvent> BFW::GUI::Window::GetX1Clicks() const
{
	Vector<Input::ClickEvent> _Clicks;

	if (!Handle)
	{
		return _Clicks;
	}

	WindowMutex->lock();
	_Clicks = X1Clicks;
	WindowMutex->unlock();

	return _Clicks;
}

const BFW::Vector<BFW::Input::ClickEvent> BFW::GUI::Window::GetX2Clicks() const
{
	Vector<Input::ClickEvent> _Clicks;

	if (!Handle)
	{
		return _Clicks;
	}

	WindowMutex->lock();
	_Clicks = X2Clicks;
	WindowMutex->unlock();

	return _Clicks;
}

const BFW::Vector<BFW::Input::ClickEvent> BFW::GUI::Window::GetLeftDoubleClicks() const
{
	Vector<Input::ClickEvent> _Clicks;

	if (!Handle)
	{
		return _Clicks;
	}

	WindowMutex->lock();
	_Clicks = LDblClicks;
	WindowMutex->unlock();

	return _Clicks;
}

const BFW::Vector<BFW::Input::ClickEvent> BFW::GUI::Window::GetRightDoubleClicks() const
{
	Vector<Input::ClickEvent> _Clicks;

	if (!Handle)
	{
		return _Clicks;
	}

	WindowMutex->lock();
	_Clicks = RDblClicks;
	WindowMutex->unlock();

	return _Clicks;
}

const BFW::Vector<BFW::Input::ClickEvent> BFW::GUI::Window::GetMiddleDoubleClicks() const
{
	Vector<Input::ClickEvent> _Clicks;

	if (!Handle)
	{
		return _Clicks;
	}

	WindowMutex->lock();
	_Clicks = MDblClicks;
	WindowMutex->unlock();

	return _Clicks;
}

const BFW::Vector<BFW::Input::ClickEvent> BFW::GUI::Window::GetX1DoubleClicks() const
{
	Vector<Input::ClickEvent> _Clicks;

	if (!Handle)
	{
		return _Clicks;
	}

	WindowMutex->lock();
	_Clicks = X1DblClicks;
	WindowMutex->unlock();

	return _Clicks;
}

const BFW::Vector<BFW::Input::ClickEvent> BFW::GUI::Window::GetX2DoubleClicks() const
{
	Vector<Input::ClickEvent> _Clicks;

	if (!Handle)
	{
		return _Clicks;
	}

	WindowMutex->lock();
	_Clicks = X2DblClicks;
	WindowMutex->unlock();

	return _Clicks;
}

const BFW::Vector<BFW::Input::WheelEvent> BFW::GUI::Window::GetWheelEvents() const
{
	Vector<Input::WheelEvent> _WheelEvents;

	if (!Handle)
	{
		return _WheelEvents;
	}

	WindowMutex->lock();
	_WheelEvents = WheelEvents;
	WindowMutex->unlock();

	return _WheelEvents;
}

const BFW::Vector<BFW::Input::WheelEvent> BFW::GUI::Window::GetHorizontalWheelEvents() const
{
	Vector<Input::WheelEvent> _HWheelEvents;

	if (!Handle)
	{
		return _HWheelEvents;
	}

	WindowMutex->lock();
	_HWheelEvents = HWheelEvents;
	WindowMutex->unlock();

	return _HWheelEvents;
}

const BFW::Vector<BFW_CHAR_TYPE> BFW::GUI::Window::GetCharEvents() const
{
	Vector<BFW_CHAR_TYPE> _CharEvents;

	if (!Handle)
	{
		return _CharEvents;
	}

	WindowMutex->lock();
	_CharEvents = CharEvents;
	WindowMutex->unlock();

	return _CharEvents;
}

const bool BFW::GUI::Window::GetClientSize(size_t& _Width, size_t& _Height) const
{
	_Width = 0;
	_Height = 0;

	if (!Handle)
	{
		return false;
	}

	RECT _ClientRect = { 0 };

	if (!GetClientRect(Handle, &_ClientRect))
	{
		return false;
	}

	_Width = (size_t)(_ClientRect.right - _ClientRect.left);
	_Height = (size_t)(_ClientRect.bottom - _ClientRect.top);

	return true;
}

const bool BFW::GUI::Window::GetWindowSize(size_t& _Width, size_t& _Height) const
{
	_Width = 0;
	_Height = 0;

	if (!Handle)
	{
		return false;
	}

	RECT _WndRect = { 0 };

	if (!GetWindowRect(Handle, &_WndRect))
	{
		return false;
	}

	_Width = (size_t)(_WndRect.right - _WndRect.left);
	_Height = (size_t)(_WndRect.bottom - _WndRect.top);

	return true;
}

const uint64_t BFW::GUI::Window::GetRefreshRate() const
{
	if (!Handle)
	{
		return 0;
	}

	HMONITOR _MonitorHandle = MonitorFromWindow(Handle, MONITOR_DEFAULTTOPRIMARY);

	if (!_MonitorHandle)
	{
		return 0;
	}

	MONITORINFOEX _MonitorInfo = { 0 };

	_MonitorInfo.cbSize = sizeof(MONITORINFOEX);

	if (!GetMonitorInfo(_MonitorHandle, &_MonitorInfo))
	{
		return false;
	}

	DEVMODE _DevMode = { 0 };

	_DevMode.dmSize = sizeof(DEVMODE);

	if (!EnumDisplaySettingsEx(_MonitorInfo.szDevice, ENUM_CURRENT_SETTINGS, &_DevMode, 0))
	{
		return 0;
	}

	return (uint64_t)(_DevMode.dmDisplayFrequency);
}

BFW::GUI::Window::operator const HWND () const
{
	return Handle;
}

BFW::GUI::Window* BFW::GUI::Window::GetWindowPtr(const HWND _Handle)
{
	if (!_Handle)
	{
		return nullptr;
	}

	Window* _WndPtr = (Window*)(GetWindowLongPtr(_Handle, GWLP_USERDATA));

	if (!_WndPtr)
	{
		return LastWnd;
	}

	return _WndPtr;
}

const bool BFW::GUI::Window::IsDefaultMessage(const UINT _Msg)
{
	if (_Msg == WM_CLOSE)
	{
		return true;
	}

	if (_Msg == WM_SETFOCUS)
	{
		return true;
	}

	if (_Msg == WM_KILLFOCUS)
	{
		return true;
	}

	if (_Msg == WM_KEYDOWN)
	{
		return true;
	}

	if (_Msg == WM_KEYUP)
	{
		return true;
	}

	if (_Msg == WM_SYSCOMMAND)
	{
		return true;
	}

	if (_Msg == WM_SYSKEYDOWN)
	{
		return true;
	}

	if (_Msg == WM_SYSKEYUP)
	{
		return true;
	}

	if (_Msg == WM_LBUTTONDOWN)
	{
		return true;
	}

	if (_Msg == WM_LBUTTONUP)
	{
		return true;
	}

	if (_Msg == WM_RBUTTONDOWN)
	{
		return true;
	}

	if (_Msg == WM_RBUTTONUP)
	{
		return true;
	}

	if (_Msg == WM_MBUTTONDOWN)
	{
		return true;
	}

	if (_Msg == WM_MBUTTONUP)
	{
		return true;
	}

	if (_Msg == WM_XBUTTONDOWN)
	{
		return true;
	}

	if (_Msg == WM_XBUTTONUP)
	{
		return true;
	}

	if (_Msg == WM_LBUTTONDBLCLK)
	{
		return true;
	}

	if (_Msg == WM_RBUTTONDBLCLK)
	{
		return true;
	}

	if (_Msg == WM_MBUTTONDBLCLK)
	{
		return true;
	}

	if (_Msg == WM_XBUTTONDBLCLK)
	{
		return true;
	}

	if (_Msg == WM_MOUSEWHEEL)
	{
		return true;
	}

	if (_Msg == WM_MOUSEHWHEEL)
	{
		return true;
	}

	if (_Msg == WM_MOUSEMOVE)
	{
		return true;
	}

	if (_Msg == WM_MOUSELEAVE)
	{
		return true;
	}

	if (_Msg == WM_CHAR)
	{
		return true;
	}

	if (_Msg == WM_SETCURSOR)
	{
		return true;
	}

	return false;
}

LRESULT BFW::GUI::Window::HandleDefaultMessage(HWND _hWnd, UINT _Msg, WPARAM _wParam, LPARAM _lParam)
{
	Window* _Wnd = GetWindowPtr(_hWnd);

	switch (_Msg)
	{
	case WM_CLOSE:
	{
		_Wnd->WindowMutex->lock();
		_Wnd->Close = true;
		_Wnd->WindowMutex->unlock();

		break;
	}
	case WM_SETFOCUS:
	{
		_Wnd->WindowMutex->lock();
		_Wnd->Focus = true;
		_Wnd->WindowMutex->unlock();

		break;
	}
	case WM_KILLFOCUS:
	{
		_Wnd->WindowMutex->lock();
		_Wnd->Focus = false;
		for (size_t _Index = 0; _Index < 256; _Index++)
		{
			_Wnd->RawKeys[_Index] = false;
		}
		_Wnd->WindowMutex->unlock();

		break;
	}
	case WM_KEYDOWN:
	{
		_Wnd->WindowMutex->lock();
		_Wnd->RawKeys[_wParam] = true;
		for (size_t _Index = 0; _Index < (size_t)(_lParam & 0b1111111111111111); _Index++)
		{
			_Wnd->KeyEvents.PushBack((uint8_t)(_wParam));
		}
		_Wnd->WindowMutex->unlock();

		break;
	}
	case WM_KEYUP:
	{
		_Wnd->WindowMutex->lock();
		_Wnd->RawKeys[_wParam] = false;
		_Wnd->WindowMutex->unlock();

		break;
	}
	case WM_SYSCOMMAND:
	{
		_Wnd->WindowMutex->lock();
		for (size_t _Index = 0; _Index < 256; _Index++)
		{
			_Wnd->RawKeys[_Index] = false;
		}
		_Wnd->WindowMutex->unlock();

		return DefWindowProc(_hWnd, _Msg, _wParam, _lParam);
	}
	case WM_SYSKEYDOWN:
	{
		_Wnd->WindowMutex->lock();
		_Wnd->RawKeys[_wParam] = true;
		for (size_t _Index = 0; _Index < (size_t)(_lParam & 0b1111111111111111); _Index++)
		{
			_Wnd->KeyEvents.PushBack((uint8_t)(_wParam));
		}
		_Wnd->WindowMutex->unlock();

		return DefWindowProc(_hWnd, _Msg, _wParam, _lParam);
	}
	case WM_SYSKEYUP:
	{
		_Wnd->WindowMutex->lock();
		_Wnd->RawKeys[_wParam] = false;
		_Wnd->WindowMutex->unlock();

		return DefWindowProc(_hWnd, _Msg, _wParam, _lParam);
	}
	case WM_LBUTTONDOWN:
	{
		_Wnd->WindowMutex->lock();
		if (!_Wnd->RawKeys[VK_LBUTTON] && !_Wnd->RawKeys[VK_RBUTTON] && !_Wnd->RawKeys[VK_MBUTTON] && !_Wnd->RawKeys[VK_XBUTTON1] && !_Wnd->RawKeys[VK_XBUTTON2])
		{
			SetCapture(_hWnd);
		}
		_Wnd->RawKeys[VK_LBUTTON] = true;
		_Wnd->WindowMutex->unlock();

		break;
	}
	case WM_LBUTTONUP:
	{
		_Wnd->WindowMutex->lock();
		_Wnd->RawKeys[VK_LBUTTON] = false;
		_Wnd->LClicks.PushBack(Input::ClickEvent((int16_t)(LOWORD(_lParam)), (int16_t)(HIWORD(_lParam)), (LOWORD(_wParam) & MK_CONTROL) != 0, (LOWORD(_wParam) & MK_SHIFT) != 0));
		if (!_Wnd->RawKeys[VK_LBUTTON] && !_Wnd->RawKeys[VK_RBUTTON] && !_Wnd->RawKeys[VK_MBUTTON] && !_Wnd->RawKeys[VK_XBUTTON1] && !_Wnd->RawKeys[VK_XBUTTON2])
		{
			ReleaseCapture();
		}
		_Wnd->WindowMutex->unlock();

		break;
	}
	case WM_RBUTTONDOWN:
	{
		_Wnd->WindowMutex->lock();
		if (!_Wnd->RawKeys[VK_LBUTTON] && !_Wnd->RawKeys[VK_RBUTTON] && !_Wnd->RawKeys[VK_MBUTTON] && !_Wnd->RawKeys[VK_XBUTTON1] && !_Wnd->RawKeys[VK_XBUTTON2])
		{
			SetCapture(_hWnd);
		}
		_Wnd->RawKeys[VK_RBUTTON] = true;
		_Wnd->WindowMutex->unlock();

		break;
	}
	case WM_RBUTTONUP:
	{
		_Wnd->WindowMutex->lock();
		_Wnd->RawKeys[VK_RBUTTON] = false;
		_Wnd->RClicks.PushBack(Input::ClickEvent((int16_t)(LOWORD(_lParam)), (int16_t)(HIWORD(_lParam)), (LOWORD(_wParam) & MK_CONTROL) != 0, (LOWORD(_wParam) & MK_SHIFT) != 0));
		if (!_Wnd->RawKeys[VK_LBUTTON] && !_Wnd->RawKeys[VK_RBUTTON] && !_Wnd->RawKeys[VK_MBUTTON] && !_Wnd->RawKeys[VK_XBUTTON1] && !_Wnd->RawKeys[VK_XBUTTON2])
		{
			ReleaseCapture();
		}
		_Wnd->WindowMutex->unlock();

		break;
	}
	case WM_MBUTTONDOWN:
	{
		_Wnd->WindowMutex->lock();
		if (!_Wnd->RawKeys[VK_LBUTTON] && !_Wnd->RawKeys[VK_RBUTTON] && !_Wnd->RawKeys[VK_MBUTTON] && !_Wnd->RawKeys[VK_XBUTTON1] && !_Wnd->RawKeys[VK_XBUTTON2])
		{
			SetCapture(_hWnd);
		}
		_Wnd->RawKeys[VK_MBUTTON] = true;
		_Wnd->WindowMutex->unlock();

		break;
	}
	case WM_MBUTTONUP:
	{
		_Wnd->WindowMutex->lock();
		_Wnd->RawKeys[VK_MBUTTON] = false;
		_Wnd->MClicks.PushBack(Input::ClickEvent((int16_t)(LOWORD(_lParam)), (int16_t)(HIWORD(_lParam)), (LOWORD(_wParam) & MK_CONTROL) != 0, (LOWORD(_wParam) & MK_SHIFT) != 0));
		if (!_Wnd->RawKeys[VK_LBUTTON] && !_Wnd->RawKeys[VK_RBUTTON] && !_Wnd->RawKeys[VK_MBUTTON] && !_Wnd->RawKeys[VK_XBUTTON1] && !_Wnd->RawKeys[VK_XBUTTON2])
		{
			ReleaseCapture();
		}
		_Wnd->WindowMutex->unlock();

		break;
	}
	case WM_XBUTTONDOWN:
	{
		_Wnd->WindowMutex->lock();
		if (HIWORD(_wParam) == XBUTTON1)
		{
			if (!_Wnd->RawKeys[VK_LBUTTON] && !_Wnd->RawKeys[VK_RBUTTON] && !_Wnd->RawKeys[VK_MBUTTON] && !_Wnd->RawKeys[VK_XBUTTON1] && !_Wnd->RawKeys[VK_XBUTTON2])
			{
				SetCapture(_hWnd);
			}
			_Wnd->RawKeys[VK_XBUTTON1] = true;
		}
		else
		{
			if (!_Wnd->RawKeys[VK_LBUTTON] && !_Wnd->RawKeys[VK_RBUTTON] && !_Wnd->RawKeys[VK_MBUTTON] && !_Wnd->RawKeys[VK_XBUTTON1] && !_Wnd->RawKeys[VK_XBUTTON2])
			{
				SetCapture(_hWnd);
			}
			_Wnd->RawKeys[VK_XBUTTON2] = true;
		}
		_Wnd->WindowMutex->unlock();

		break;
	}
	case WM_XBUTTONUP:
	{
		_Wnd->WindowMutex->lock();
		if (HIWORD(_wParam) == XBUTTON1)
		{
			_Wnd->RawKeys[VK_XBUTTON1] = false;
			_Wnd->X1Clicks.PushBack(Input::ClickEvent((int16_t)(LOWORD(_lParam)), (int16_t)(HIWORD(_lParam)), (LOWORD(_wParam) & MK_CONTROL) != 0, (LOWORD(_wParam) & MK_SHIFT) != 0));
			if (!_Wnd->RawKeys[VK_LBUTTON] && !_Wnd->RawKeys[VK_RBUTTON] && !_Wnd->RawKeys[VK_MBUTTON] && !_Wnd->RawKeys[VK_XBUTTON1] && !_Wnd->RawKeys[VK_XBUTTON2])
			{
				ReleaseCapture();
			}
		}
		else
		{
			_Wnd->RawKeys[VK_XBUTTON2] = false;
			_Wnd->X2Clicks.PushBack(Input::ClickEvent((int16_t)(LOWORD(_lParam)), (int16_t)(HIWORD(_lParam)), (LOWORD(_wParam) & MK_CONTROL) != 0, (LOWORD(_wParam) & MK_SHIFT) != 0));
			if (!_Wnd->RawKeys[VK_LBUTTON] && !_Wnd->RawKeys[VK_RBUTTON] && !_Wnd->RawKeys[VK_MBUTTON] && !_Wnd->RawKeys[VK_XBUTTON1] && !_Wnd->RawKeys[VK_XBUTTON2])
			{
				ReleaseCapture();
			}
		}
		_Wnd->WindowMutex->unlock();

		break;
	}
	case WM_LBUTTONDBLCLK:
	{
		_Wnd->WindowMutex->lock();
		_Wnd->LDblClicks.PushBack(Input::ClickEvent((int16_t)(LOWORD(_lParam)), (int16_t)(HIWORD(_lParam)), (LOWORD(_wParam) & MK_CONTROL) != 0, (LOWORD(_wParam) & MK_SHIFT) != 0));
		_Wnd->WindowMutex->unlock();

		break;
	}
	case WM_RBUTTONDBLCLK:
	{
		_Wnd->WindowMutex->lock();
		_Wnd->RDblClicks.PushBack(Input::ClickEvent((int16_t)(LOWORD(_lParam)), (int16_t)(HIWORD(_lParam)), (LOWORD(_wParam) & MK_CONTROL) != 0, (LOWORD(_wParam) & MK_SHIFT) != 0));
		_Wnd->WindowMutex->unlock();

		break;
	}
	case WM_MBUTTONDBLCLK:
	{
		_Wnd->WindowMutex->lock();
		_Wnd->MDblClicks.PushBack(Input::ClickEvent((int16_t)(LOWORD(_lParam)), (int16_t)(HIWORD(_lParam)), (LOWORD(_wParam) & MK_CONTROL) != 0, (LOWORD(_wParam) & MK_SHIFT) != 0));
		_Wnd->WindowMutex->unlock();

		break;
	}
	case WM_XBUTTONDBLCLK:
	{
		_Wnd->WindowMutex->lock();
		if (HIWORD(_wParam) == XBUTTON1)
		{
			_Wnd->X1DblClicks.PushBack(Input::ClickEvent((int16_t)(LOWORD(_lParam)), (int16_t)(HIWORD(_lParam)), (LOWORD(_wParam) & MK_CONTROL) != 0, (LOWORD(_wParam) & MK_SHIFT) != 0));
		}
		else
		{
			_Wnd->X2DblClicks.PushBack(Input::ClickEvent((int16_t)(LOWORD(_lParam)), (int16_t)(HIWORD(_lParam)), (LOWORD(_wParam) & MK_CONTROL) != 0, (LOWORD(_wParam) & MK_SHIFT) != 0));
		}
		_Wnd->WindowMutex->unlock();

		break;
	}
	case WM_MOUSEWHEEL:
	{
		POINT _Cursor = { 0 };

		_Cursor.x = (int16_t)(LOWORD(_lParam));
		_Cursor.y = (int16_t)(HIWORD(_lParam));

		if (!ScreenToClient(_hWnd, &_Cursor))
		{
			break;
		}

		_Wnd->WindowMutex->lock();
		_Wnd->WheelEvents.PushBack(Input::WheelEvent((intptr_t)(-(int16_t)(HIWORD(_wParam))), _Cursor.x, _Cursor.y, (LOWORD(_wParam) & MK_CONTROL) != 0, (LOWORD(_wParam) & MK_SHIFT) != 0));
		_Wnd->WindowMutex->unlock();

		break;
	}
	case WM_MOUSEHWHEEL:
	{
		POINT _Cursor = { 0 };

		_Cursor.x = (int16_t)(LOWORD(_lParam));
		_Cursor.y = (int16_t)(HIWORD(_lParam));

		if (!ScreenToClient(_hWnd, &_Cursor))
		{
			break;
		}

		_Wnd->WindowMutex->lock();
		_Wnd->HWheelEvents.PushBack(Input::WheelEvent((intptr_t)((int16_t)(HIWORD(_wParam))), _Cursor.x, _Cursor.y, (LOWORD(_wParam) & MK_CONTROL) != 0, (LOWORD(_wParam) & MK_SHIFT) != 0));
		_Wnd->WindowMutex->unlock();

		break;
	}
	case WM_MOUSEMOVE:
	{
		if (!_Wnd->Tracking)
		{
			TRACKMOUSEEVENT _TrackMouse = { 0 };

			_TrackMouse.cbSize = sizeof(TRACKMOUSEEVENT);
			_TrackMouse.dwFlags = TME_LEAVE;
			_TrackMouse.hwndTrack = _hWnd;

			TrackMouseEvent(&_TrackMouse);

			_Wnd->Tracking = true;
		}

		_Wnd->WindowMutex->lock();
		_Wnd->HasMouse = true;
		_Wnd->MouseX = (int16_t)(LOWORD(_lParam));
		_Wnd->MouseY = (int16_t)(HIWORD(_lParam));
		_Wnd->WindowMutex->unlock();

		break;
	}
	case WM_MOUSELEAVE:
	{
		_Wnd->Tracking = false;

		_Wnd->WindowMutex->lock();
		_Wnd->HasMouse = false;
		_Wnd->MouseX = 0;
		_Wnd->MouseY = 0;
		_Wnd->WindowMutex->unlock();

		break;
	}
	case WM_CHAR:
	{
		_Wnd->WindowMutex->lock();
		for (size_t _Index = 0; _Index < (size_t)(_lParam & 0b1111111111111111); _Index++)
		{
			_Wnd->CharEvents.PushBack((BFW_CHAR_TYPE)(_wParam));
		}
		_Wnd->WindowMutex->unlock();

		break;
	}
	case WM_SETCURSOR:
	{
		if (LOWORD(_lParam) != HTCLIENT)
		{
			return DefWindowProc(_hWnd, _Msg, _wParam, _lParam);
		}

		_Wnd->WindowMutex->lock();
		SetCursor(_Wnd->Cursor);
		_Wnd->WindowMutex->unlock();

		return TRUE;
	}
	default:
	{
		BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Unknown default message!"));
		break;
	}
	}

	return 0;
}

void BFW::GUI::Window::WndThreadFnc(bool& _Done, bool& _Fail, Window* _Wnd, const uint32_t _ExStyle, const BFW_CHAR_TYPE* _ClassName, const BFW_CHAR_TYPE* _WindowName, const uint32_t _Style, const int32_t _X, const int32_t _Y, const int32_t _Width, const int32_t _Height, const HWND _ParentHandle, const HMENU _MenuHandle, const HINSTANCE _InstanceHandle, void* _Param, const HACCEL _AccelHandle, const ThreadInitFnc _ThreadInit, const ThreadCleanUpFnc _ThreadCleanUp, const WndInitFnc _WndInit, const WndCleanUpFnc _WndCleanUp, void* _UserData)
{
	if (_ThreadInit)
	{
		if (!_ThreadInit(_UserData))
		{
			if (_MenuHandle)
			{
				DestroyMenu(_MenuHandle);
			}

			if (_AccelHandle)
			{
				DestroyAcceleratorTable(_AccelHandle);
			}

			_Fail = true;
			_Done = true;

			return;
		}
	}

	_Wnd->UserData = _UserData;

	LastWndMutex.lock();

	LastWnd = _Wnd;

	_Wnd->Handle = CreateWindowEx(_ExStyle, _ClassName, _WindowName, _Style, _X, _Y, _Width, _Height, _ParentHandle, _MenuHandle, _InstanceHandle, _Param);

	LastWnd = nullptr;

	LastWndMutex.unlock();

	if (!_Wnd->Handle)
	{
		_Wnd->UserData = nullptr;

		if (_ThreadCleanUp)
		{
			_ThreadCleanUp(_UserData);
		}

		if (_MenuHandle)
		{
			DestroyMenu(_MenuHandle);
		}

		if (_AccelHandle)
		{
			DestroyAcceleratorTable(_AccelHandle);
		}

		_Fail = true;
		_Done = true;

		return;
	}

	SetLastError(0);

	if (!SetWindowLongPtr(_Wnd->Handle, GWLP_USERDATA, (LONG_PTR)(_Wnd)))
	{
		if (GetLastError())
		{
			DestroyWindow(_Wnd->Handle);
			_Wnd->Handle = NULL;
			_Wnd->UserData = nullptr;

			if (_ThreadCleanUp)
			{
				_ThreadCleanUp(_UserData);
			}

			if (_AccelHandle)
			{
				DestroyAcceleratorTable(_AccelHandle);
			}

			_Fail = true;
			_Done = true;

			return;
		}
	}

	if (_WndInit)
	{
		if (!_WndInit(_Wnd))
		{
			DestroyWindow(_Wnd->Handle);
			_Wnd->Handle = NULL;
			_Wnd->UserData = nullptr;

			if (_ThreadCleanUp)
			{
				_ThreadCleanUp(_UserData);
			}

			if (_AccelHandle)
			{
				DestroyAcceleratorTable(_AccelHandle);
			}

			_Fail = true;
			_Done = true;

			return;
		}
	}

	MSG _Msg = { 0 };

	_Fail = false;
	_Done = true;

	while (GetMessage(&_Msg, NULL, 0, 0) > 0)
	{
		if (_AccelHandle)
		{
			if (TranslateAccelerator(_Wnd->Handle, _AccelHandle, &_Msg))
			{
				continue;
			}
		}

		TranslateMessage(&_Msg);
		DispatchMessage(&_Msg);
	}

	DestroyWindow(_Wnd->Handle);
	_Wnd->Handle = NULL;

	if (_WndCleanUp)
	{
		_WndCleanUp(_Wnd);
	}

	_Wnd->UserData = nullptr;

	if (_ThreadCleanUp)
	{
		_ThreadCleanUp(_UserData);
	}

	if (_AccelHandle)
	{
		DestroyAcceleratorTable(_AccelHandle);
	}
}

#endif



BFW::GUI::RenderingDescriptor::RenderingDescriptor() : SetupData(nullptr), CleanUpData(nullptr), RenderBottom(nullptr), RenderMiddle(nullptr), RenderTop(nullptr), Composit(nullptr)
{

}

BFW::GUI::RenderingDescriptor::RenderingDescriptor(const SetupRenderDataFnc& _SetupData, const CleanUpRenderDataFnc& _CleanUpData, const RenderFnc& _RenderBottom, const RenderFnc& _RenderMiddle, const RenderFnc& _RenderTop, const CompositFnc& _Composit) : SetupData(_SetupData), CleanUpData(_CleanUpData), RenderBottom(_RenderBottom), RenderMiddle(_RenderMiddle), RenderTop(_RenderTop), Composit(_Composit)
{

}

BFW::GUI::RenderingDescriptor::RenderingDescriptor(RenderingDescriptor&& _Other) noexcept : SetupData(_Other.SetupData), CleanUpData(_Other.CleanUpData), RenderBottom(_Other.RenderBottom), RenderMiddle(_Other.RenderMiddle), RenderTop(_Other.RenderTop), Composit(_Other.Composit)
{
	_Other.SetupData = nullptr;
	_Other.CleanUpData = nullptr;
	_Other.RenderBottom = nullptr;
	_Other.RenderMiddle = nullptr;
	_Other.RenderTop = nullptr;
	_Other.Composit = nullptr;
}

BFW::GUI::RenderingDescriptor& BFW::GUI::RenderingDescriptor::operator= (RenderingDescriptor&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	SetupData = _Other.SetupData;
	CleanUpData = _Other.CleanUpData;
	RenderBottom = _Other.RenderBottom;
	RenderMiddle = _Other.RenderMiddle;
	RenderTop = _Other.RenderTop;
	Composit = _Other.Composit;

	_Other.SetupData = nullptr;
	_Other.CleanUpData = nullptr;
	_Other.RenderBottom = nullptr;
	_Other.RenderMiddle = nullptr;
	_Other.RenderTop = nullptr;
	_Other.Composit = nullptr;

	return *this;
}



BFW::GUI::SafePopUpPointer::SafePopUpPointer() : Pointer(nullptr)
{

}

BFW::GUI::SafePopUpPointer::SafePopUpPointer(PopUp* _Pointer) : Pointer(_Pointer)
{
	if (Pointer)
	{
		Pointer->SafePointers.PushBack(this);
	}
}

BFW::GUI::SafePopUpPointer::SafePopUpPointer(const SafePopUpPointer& _Other) : Pointer(_Other.Pointer)
{
	if (Pointer)
	{
		Pointer->SafePointers.PushBack(this);
	}
}

BFW::GUI::SafePopUpPointer::SafePopUpPointer(SafePopUpPointer&& _Other) noexcept : Pointer(_Other.Pointer)
{
	if (Pointer)
	{
		for (size_t _Index = 0; _Index < Pointer->SafePointers.GetSize(); _Index++)
		{
			if (Pointer->SafePointers[_Index] == &_Other)
			{
				Pointer->SafePointers[_Index] = this;
				break;
			}
		}
	}

	_Other.Pointer = nullptr;
}

BFW::GUI::SafePopUpPointer::~SafePopUpPointer()
{
	if (Pointer)
	{
		for (size_t _Index = 0; _Index < Pointer->SafePointers.GetSize(); _Index++)
		{
			if (Pointer->SafePointers[_Index] == this)
			{
				Pointer->SafePointers.Erase(_Index);
				break;
			}
		}
	}
}

BFW::GUI::SafePopUpPointer::operator BFW::GUI::PopUp* ()
{
	return Pointer;
}

BFW::GUI::SafePopUpPointer::operator const BFW::GUI::PopUp* () const
{
	return Pointer;
}

BFW::GUI::PopUp* BFW::GUI::SafePopUpPointer::operator-> ()
{
	return Pointer;
}

const BFW::GUI::PopUp* BFW::GUI::SafePopUpPointer::operator-> () const
{
	return Pointer;
}

BFW::GUI::PopUp& BFW::GUI::SafePopUpPointer::operator* ()
{
	return *Pointer;
}

const BFW::GUI::PopUp& BFW::GUI::SafePopUpPointer::operator* () const
{
	return *Pointer;
}

BFW::GUI::SafePopUpPointer& BFW::GUI::SafePopUpPointer::operator= (PopUp* _Pointer)
{
	if (Pointer)
	{
		for (size_t _Index = 0; _Index < Pointer->SafePointers.GetSize(); _Index++)
		{
			if (Pointer->SafePointers[_Index] == this)
			{
				Pointer->SafePointers.Erase(_Index);
				break;
			}
		}
	}

	Pointer = _Pointer;

	if (Pointer)
	{
		Pointer->SafePointers.PushBack(this);
	}

	return *this;
}

BFW::GUI::SafePopUpPointer& BFW::GUI::SafePopUpPointer::operator= (const SafePopUpPointer& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	if (Pointer)
	{
		for (size_t _Index = 0; _Index < Pointer->SafePointers.GetSize(); _Index++)
		{
			if (Pointer->SafePointers[_Index] == this)
			{
				Pointer->SafePointers.Erase(_Index);
				break;
			}
		}
	}

	Pointer = _Other.Pointer;

	if (Pointer)
	{
		Pointer->SafePointers.PushBack(this);
	}

	return *this;
}

BFW::GUI::SafePopUpPointer& BFW::GUI::SafePopUpPointer::operator= (SafePopUpPointer&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	if (Pointer)
	{
		for (size_t _Index = 0; _Index < Pointer->SafePointers.GetSize(); _Index++)
		{
			if (Pointer->SafePointers[_Index] == this)
			{
				Pointer->SafePointers.Erase(_Index);
				break;
			}
		}
	}

	Pointer = _Other.Pointer;

	if (Pointer)
	{
		for (size_t _Index = 0; _Index < Pointer->SafePointers.GetSize(); _Index++)
		{
			if (Pointer->SafePointers[_Index] == &_Other)
			{
				Pointer->SafePointers[_Index] = this;
				break;
			}
		}
	}

	_Other.Pointer = nullptr;

	return *this;
}



BFW::GUI::PopUp::PopUp() : FocusedPanel(0), Panels(), FocusedNode(0), Nodes(), FocusedPopUps(), PopUps(), SafePointers(), Id(_NodeWindowPopUpId), PanelType(_NullPanelType), TrueWidth(0), TrueHeight(0), Width(0), Height(0), PositionX(0), PositionY(0), ScrollX(0), ScrollY(0), UserData(nullptr), RenderFunctions()
{

}

BFW::GUI::PopUp::PopUp(const PopUp& _Other) : FocusedPanel(_Other.FocusedPanel), Panels(_Other.Panels), FocusedNode(_Other.FocusedNode), Nodes(_Other.Nodes), FocusedPopUps(_Other.FocusedPopUps), PopUps(_Other.PopUps), SafePointers(), Id(_Other.Id), PanelType(_Other.PanelType), TrueWidth(_Other.TrueWidth), TrueHeight(_Other.TrueHeight), Width(_Other.Width), Height(_Other.Height), PositionX(_Other.PositionX), PositionY(_Other.PositionY), ScrollX(_Other.ScrollX), ScrollY(_Other.ScrollY), UserData(nullptr), RenderFunctions(_Other.RenderFunctions)
{

}

BFW::GUI::PopUp::PopUp(PopUp&& _Other) noexcept : FocusedPanel(_Other.FocusedPanel), Panels((Vector<PopUp>&&)(_Other.Panels)), FocusedNode(_Other.FocusedNode), Nodes((Vector<PopUp>&&)(_Other.Nodes)), FocusedPopUps((Vector<size_t>&&)(_Other.FocusedPopUps)), PopUps((Vector<Vector<PopUp>>&&)(_Other.PopUps)), SafePointers((Vector<SafePopUpPointer*>&&)(_Other.SafePointers)), Id(_Other.Id), PanelType(_Other.PanelType), TrueWidth(_Other.TrueWidth), TrueHeight(_Other.TrueHeight), Width(_Other.Width), Height(_Other.Height), PositionX(_Other.PositionX), PositionY(_Other.PositionY), ScrollX(_Other.ScrollX), ScrollY(_Other.ScrollY), UserData(_Other.UserData), RenderFunctions((RenderingDescriptor&&)(_Other.RenderFunctions))
{
	for (size_t _Index = 0; _Index < SafePointers.GetSize(); _Index++)
	{
		SafePointers[_Index]->Pointer = this;
	}

	_Other.FocusedPanel = 0;
	_Other.FocusedNode = 0;
	_Other.Id = _NodeWindowPopUpId;
	_Other.PanelType = _NullPanelType;
	_Other.TrueWidth = 0;
	_Other.TrueHeight = 0;
	_Other.Width = 0;
	_Other.Height = 0;
	_Other.PositionX = 0;
	_Other.PositionY = 0;
	_Other.ScrollX = 0;
	_Other.ScrollY = 0;
	_Other.UserData = nullptr;
}

BFW::GUI::PopUp::~PopUp()
{
	for (size_t _Index = 0; _Index < SafePointers.GetSize(); _Index++)
	{
		SafePointers[_Index]->Pointer = nullptr;
	}
}

BFW::GUI::PopUp& BFW::GUI::PopUp::Begin(const uint64_t _Id, const uint8_t _PanelType, const size_t _MinWidth, const size_t _MinHeight, const size_t _Width, const size_t _Height, const intptr_t _PositionX, const intptr_t _PositionY, const size_t _ScrollX, const size_t _ScrollY, const RenderingDescriptor& _RenderFunctions, void* _UserData)
{
	FocusedPanel = 0;
	Panels.Clear();
	FocusedNode = 0;
	Nodes.Clear();
	FocusedPopUps.Clear();
	PopUps.Clear();

	Id = _Id;
	PanelType = _PanelType;
	Width = _Width;
	Height = _Height;
	SetTrueWidth(_MinWidth);
	SetTrueHeight(_MinHeight);
	PositionX = _PositionX;
	PositionY = _PositionY;
	SetScrollX(_ScrollX);
	SetScrollY(_ScrollY);
	UserData = _UserData;
	RenderFunctions = _RenderFunctions;

	return *this;
}

BFW::GUI::PopUp& BFW::GUI::PopUp::PushLeftPanel(const uint64_t _Id, const size_t _MinWidth, const size_t _MinHeight, const size_t _Width, const size_t _ScrollX, const size_t _ScrollY, const RenderingDescriptor& _RenderFunctions, void* _UserData, const bool _Focused)
{
	if (Panels.GetSize() != 0 && Panels[0].PanelType != _LeftPanelType)
	{
		BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Only constant panel types are supported!"));
		return *(PopUp*)(nullptr);
	}

	if (Panels.GetSize() && (Panels[0].Width != _Width))
	{
		BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("PopUp size does not respect sibling size!"));
		return *(PopUp*)(nullptr);
	}

	Panels.PushBack(PopUp());
	Panels[Panels.GetSize() - 1].Begin(_Id, _LeftPanelType, _MinWidth, _MinHeight, _Width, TrueHeight, 0, 0, _ScrollX, _ScrollY, _RenderFunctions, _UserData);

	if (_Focused)
	{
		FocusedPanel = Panels.GetSize() - 1;
	}

	return Panels[Panels.GetSize() - 1];
}

BFW::GUI::PopUp& BFW::GUI::PopUp::PushRightPanel(const uint64_t _Id, const size_t _MinWidth, const size_t _MinHeight, const size_t _Width, const size_t _ScrollX, const size_t _ScrollY, const RenderingDescriptor& _RenderFunctions, void* _UserData, const bool _Focused)
{
	if (Panels.GetSize() != 0 && Panels[0].PanelType != _RightPanelType)
	{
		BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Only constant panel types are supported!"));
		return *(PopUp*)(nullptr);
	}

	if (Panels.GetSize() && (Panels[0].Width != _Width))
	{
		BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("PopUp size does not respect sibling size!"));
		return *(PopUp*)(nullptr);
	}

	Panels.PushBack(PopUp());
	Panels[Panels.GetSize() - 1].Begin(_Id, _RightPanelType, _MinWidth, _MinHeight, _Width, TrueHeight, TrueWidth - _Width, 0, _ScrollX, _ScrollY, _RenderFunctions, _UserData);

	if (_Focused)
	{
		FocusedPanel = Panels.GetSize() - 1;
	}

	return Panels[Panels.GetSize() - 1];
}

BFW::GUI::PopUp& BFW::GUI::PopUp::PushTopPanel(const uint64_t _Id, const size_t _MinWidth, const size_t _MinHeight, const size_t _Height, const size_t _ScrollX, const size_t _ScrollY, const RenderingDescriptor& _RenderFunctions, void* _UserData, const bool _Focused)
{
	if (Panels.GetSize() != 0 && Panels[0].PanelType != _TopPanelType)
	{
		BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Only constant panel types are supported!"));
		return *(PopUp*)(nullptr);
	}

	if (Panels.GetSize() && (Panels[0].Height != _Height))
	{
		BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("PopUp size does not respect sibling size!"));
		return *(PopUp*)(nullptr);
	}

	Panels.PushBack(PopUp());
	Panels[Panels.GetSize() - 1].Begin(_Id, _TopPanelType, _MinWidth, _MinHeight, TrueWidth, _Height, 0, 0, _ScrollX, _ScrollY, _RenderFunctions, _UserData);

	if (_Focused)
	{
		FocusedPanel = Panels.GetSize() - 1;
	}

	return Panels[Panels.GetSize() - 1];
}

BFW::GUI::PopUp& BFW::GUI::PopUp::PushBottomPanel(const uint64_t _Id, const size_t _MinWidth, const size_t _MinHeight, const size_t _Height, const size_t _ScrollX, const size_t _ScrollY, const RenderingDescriptor& _RenderFunctions, void* _UserData, const bool _Focused)
{
	if (Panels.GetSize() != 0 && Panels[0].PanelType != _BottomPanelType)
	{
		BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Only constant panel types are supported!"));
		return *(PopUp*)(nullptr);
	}

	if (Panels.GetSize() && (Panels[0].Height != _Height))
	{
		BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("PopUp size does not respect sibling size!"));
		return *(PopUp*)(nullptr);
	}

	Panels.PushBack(PopUp());
	Panels[Panels.GetSize() - 1].Begin(_Id, _BottomPanelType, _MinWidth, _MinHeight, TrueWidth, _Height, 0, TrueHeight - _Height, _ScrollX, _ScrollY, _RenderFunctions, _UserData);

	if (_Focused)
	{
		FocusedPanel = Panels.GetSize() - 1;
	}

	return Panels[Panels.GetSize() - 1];
}

BFW::GUI::PopUp& BFW::GUI::PopUp::PushNode(const uint64_t _Id, const size_t _MinWidth, const size_t _MinHeight, const size_t _ScrollX, const size_t _ScrollY, const RenderingDescriptor& _RenderFunctions, void* _UserData, const bool _Focused)
{
	if (Panels.GetSize() == 0)
	{
		BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Can't push node with no side window!"));
		return *(PopUp*)(nullptr);
	}

	Nodes.PushBack(PopUp());

	switch (Panels[0].GetPanelType())
	{
	case _LeftPanelType:
	{
		size_t _Remainder = (TrueWidth - Panels[0].Width) * (Panels[0].Width <= TrueWidth);
		Nodes[Nodes.GetSize() - 1].Begin(_Id, _RightPanelType, _MinWidth, _MinHeight, _Remainder, TrueHeight, Panels[0].Width, 0, _ScrollX, _ScrollY, _RenderFunctions, _UserData);
		break;
	}
	case _RightPanelType:
	{
		size_t _Remainder = (TrueWidth - Panels[0].Width) * (Panels[0].Width <= TrueWidth);
		Nodes[Nodes.GetSize() - 1].Begin(_Id, _LeftPanelType, _MinWidth, _MinHeight, _Remainder, TrueHeight, 0, 0, _ScrollX, _ScrollY, _RenderFunctions, _UserData);
		break;
	}
	case _TopPanelType:
	{
		size_t _Remainder = (TrueHeight - Panels[0].Height) * (Panels[0].Height <= TrueHeight);
		Nodes[Nodes.GetSize() - 1].Begin(_Id, _BottomPanelType, _MinWidth, _MinHeight, TrueWidth, _Remainder, 0, Panels[0].Height, _ScrollX, _ScrollY, _RenderFunctions, _UserData);
		break;
	}
	case _BottomPanelType:
	{
		size_t _Remainder = (TrueHeight - Panels[0].Height) * (Panels[0].Height <= TrueHeight);
		Nodes[Nodes.GetSize() - 1].Begin(_Id, _TopPanelType, _MinWidth, _MinHeight, TrueWidth, _Remainder, 0, 0, _ScrollX, _ScrollY, _RenderFunctions, _UserData);
		break;
	}
	default:
	{
		BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Detected a panel with no panel type!"));
		Nodes.Erase(Nodes.GetSize() - 1);
		return *(PopUp*)(nullptr);
	}
	}

	if (_Focused)
	{
		FocusedNode = Nodes.GetSize() - 1;
	}

	return Nodes[Nodes.GetSize() - 1];
}

const size_t BFW::GUI::PopUp::PushPopUpLayer()
{
	FocusedPopUps.PushBack(0);
	PopUps.PushBack(Vector<PopUp>());

	return PopUps.GetSize() - 1;
}

BFW::GUI::PopUp& BFW::GUI::PopUp::PushPopUp(const size_t _Layer, const uint64_t _Id, const size_t _MinWidth, const size_t _MinHeight, const size_t _Width, const size_t _Height, const intptr_t _PositionX, const intptr_t _PositionY, const size_t _ScrollX, const size_t _ScrollY, const RenderingDescriptor& _RenderFunctions, void* _UserData, const bool _Focused)
{
	if (_Layer >= PopUps.GetSize())
	{
		BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("PopUp layer out of bounds!"));
		return *(PopUp*)(nullptr);
	}

	if (PopUps[_Layer].GetSize() && (PopUps[_Layer][0].Width != _Width || PopUps[_Layer][0].Height != _Height))
	{
		BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("PopUp size does not respect sibling size!"));
		return *(PopUp*)(nullptr);
	}

	PopUps[_Layer].PushBack(PopUp());
	PopUps[_Layer][PopUps[_Layer].GetSize() - 1].Begin(_Id, _NullPanelType, _MinWidth, _MinHeight, _Width, _Height, _PositionX, _PositionY, _ScrollX, _ScrollY, _RenderFunctions, _UserData);

	if (_Focused)
	{
		FocusedPopUps[_Layer] = PopUps[_Layer].GetSize() - 1;
	}

	return PopUps[_Layer][PopUps[_Layer].GetSize() - 1];
}

void BFW::GUI::PopUp::Render(void* _Global)
{
	if (Width > TrueWidth || Height > TrueHeight || ScrollX > TrueWidth - Width || ScrollY > TrueHeight - Height)
	{
		BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Attempt to render invalid PopUp layout!"));
		return;
	}

	if (RenderFunctions.RenderBottom)
	{
		RenderFunctions.RenderBottom(*this, _Global);
	}

	if (Panels.GetSize())
	{
		if (Panels[FocusedPanel].RenderFunctions.SetupData)
		{
			Panels[FocusedPanel].RenderFunctions.SetupData(Panels[FocusedPanel], *this, _Global);
		}

		Panels[FocusedPanel].Render(_Global);
		RenderFunctions.Composit(*this, Panels[FocusedPanel], _Global);

		if (Panels[FocusedPanel].RenderFunctions.CleanUpData)
		{
			Panels[FocusedPanel].RenderFunctions.CleanUpData(Panels[FocusedPanel], _Global);
		}
	}

	if (Nodes.GetSize())
	{
		if (Nodes[FocusedNode].RenderFunctions.SetupData)
		{
			Nodes[FocusedNode].RenderFunctions.SetupData(Nodes[FocusedNode], *this, _Global);
		}

		Nodes[FocusedNode].Render(_Global);
		RenderFunctions.Composit(*this, Nodes[FocusedNode], _Global);

		if (Nodes[FocusedNode].RenderFunctions.CleanUpData)
		{
			Nodes[FocusedNode].RenderFunctions.CleanUpData(Nodes[FocusedNode], _Global);
		}
	}

	if (RenderFunctions.RenderMiddle)
	{
		RenderFunctions.RenderMiddle(*this, _Global);
	}

	for (size_t _Index = 0; _Index < PopUps.GetSize(); _Index++)
	{
		if (PopUps[_Index].GetSize())
		{
			if (PopUps[_Index][FocusedPopUps[_Index]].RenderFunctions.SetupData)
			{
				PopUps[_Index][FocusedPopUps[_Index]].RenderFunctions.SetupData(PopUps[_Index][FocusedPopUps[_Index]], *this, _Global);
			}

			PopUps[_Index][FocusedPopUps[_Index]].Render(_Global);
			RenderFunctions.Composit(*this, PopUps[_Index][FocusedPopUps[_Index]], _Global);

			if (PopUps[_Index][FocusedPopUps[_Index]].RenderFunctions.CleanUpData)
			{
				PopUps[_Index][FocusedPopUps[_Index]].RenderFunctions.CleanUpData(PopUps[_Index][FocusedPopUps[_Index]], _Global);
			}
		}
	}

	if (RenderFunctions.RenderTop)
	{
		RenderFunctions.RenderTop(*this, _Global);
	}
}

void BFW::GUI::PopUp::ScrollH(const intptr_t _Delta, const IgnoreScrollFnc _IgnoreScroll)
{
	if (TrueWidth == Width)
	{
		return;
	}

	size_t _ScrollWindowIndex = 0;

	if (!FindFocusedPopUpLayer(_ScrollWindowIndex, _HScrollWindowPopUpId))
	{
		return;
	}

	BFW::GUI::PopUp& _ScrollWindow = PopUps[_ScrollWindowIndex][0];
	BFW::GUI::PopUp& _ScrollButton = _ScrollWindow.PopUps[0][0];

	intptr_t _TrueDelta = _Delta;

	if (_TrueDelta < 0 && _ScrollButton.PositionX < -_TrueDelta)
	{
		_TrueDelta = -_ScrollButton.PositionX;
	}

	if (_TrueDelta > 0 && (_ScrollWindow.Width - (_ScrollButton.PositionX + _ScrollButton.Width)) * (_ScrollWindow.Width > _ScrollButton.PositionX + _ScrollButton.Width) < (size_t)(_TrueDelta))
	{
		_TrueDelta = (_ScrollWindow.Width - (_ScrollButton.PositionX + _ScrollButton.Width)) * (_ScrollWindow.Width > _ScrollButton.PositionX + _ScrollButton.Width);
	}

	_ScrollButton.SetPositionX(_ScrollButton.PositionX + _TrueDelta);

	intptr_t _ScrollDelta = ScrollX;

	SetScrollX(_ScrollButton.PositionX * (TrueWidth - Width) / (_ScrollWindow.Width - _ScrollWindow.Width * Width / TrueWidth));

	_ScrollDelta = ScrollX - _ScrollDelta;

	for (size_t _Layer = 0; _Layer < PopUps.GetSize(); _Layer++)
	{
		for (size_t _Index = 0; _Index < PopUps[_Layer].GetSize(); _Index++)
		{
			uint64_t _Id = PopUps[_Layer][_Index].Id;

			if (_Id == _LeftResizePopUpId || _Id == _RightResizePopUpId || _Id == _TopResizePopUpId || _Id == _BottomResizePopUpId || _Id == _LeftTopResizePopUpId || _Id == _LeftBottomResizePopUpId || _Id == _RightTopResizePopUpId || _Id == _RightBottomResizePopUpId || _Id == _HScrollWindowPopUpId || _Id == _VScrollWindowPopUpId || _Id == _ScrollCornerPopUpId || _IgnoreScroll(_Id))
			{
				PopUps[_Layer][_Index].SetPositionX(PopUps[_Layer][_Index].PositionX + _ScrollDelta);
			}
		}
	}
}

void BFW::GUI::PopUp::ScrollV(const intptr_t _Delta, const IgnoreScrollFnc _IgnoreScroll)
{
	if (TrueHeight == Height)
	{
		return;
	}

	size_t _ScrollWindowIndex = 0;

	if (!FindFocusedPopUpLayer(_ScrollWindowIndex, _VScrollWindowPopUpId))
	{
		return;
	}

	BFW::GUI::PopUp& _ScrollWindow = PopUps[_ScrollWindowIndex][0];
	BFW::GUI::PopUp& _ScrollButton = _ScrollWindow.PopUps[0][0];

	intptr_t _TrueDelta = _Delta;

	if (_TrueDelta < 0 && _ScrollButton.PositionY < -_TrueDelta)
	{
		_TrueDelta = -_ScrollButton.PositionY;
	}

	if (_TrueDelta > 0 && (_ScrollWindow.Height - (_ScrollButton.PositionY + _ScrollButton.Height)) * (_ScrollWindow.Height > _ScrollButton.PositionY + _ScrollButton.Height) < (size_t)(_TrueDelta))
	{
		_TrueDelta = (_ScrollWindow.Height - (_ScrollButton.PositionY + _ScrollButton.Height)) * (_ScrollWindow.Height > _ScrollButton.PositionY + _ScrollButton.Height);
	}

	_ScrollButton.SetPositionY(_ScrollButton.PositionY + _TrueDelta);

	intptr_t _ScrollDelta = ScrollY;

	SetScrollY(_ScrollButton.PositionY * (TrueHeight - Height) / (_ScrollWindow.Height - _ScrollWindow.Height * Height / TrueHeight));

	_ScrollDelta = ScrollY - _ScrollDelta;

	for (size_t _Layer = 0; _Layer < PopUps.GetSize(); _Layer++)
	{
		for (size_t _Index = 0; _Index < PopUps[_Layer].GetSize(); _Index++)
		{
			uint64_t _Id = PopUps[_Layer][_Index].Id;

			if (_Id == _LeftResizePopUpId || _Id == _RightResizePopUpId || _Id == _TopResizePopUpId || _Id == _BottomResizePopUpId || _Id == _LeftTopResizePopUpId || _Id == _LeftBottomResizePopUpId || _Id == _RightTopResizePopUpId || _Id == _RightBottomResizePopUpId || _Id == _HScrollWindowPopUpId || _Id == _VScrollWindowPopUpId || _Id == _ScrollCornerPopUpId || _IgnoreScroll(_Id))
			{
				PopUps[_Layer][_Index].SetPositionY(PopUps[_Layer][_Index].PositionY + _ScrollDelta);
			}
		}
	}
}

void BFW::GUI::PopUp::ScrollWithMouseH(const intptr_t _Delta, intptr_t& _Accumulation, const IgnoreScrollFnc _IgnoreScroll)
{
	if (TrueWidth == Width)
	{
		return;
	}

	size_t _ScrollWindowIndex = 0;

	if (!FindFocusedPopUpLayer(_ScrollWindowIndex, _HScrollWindowPopUpId))
	{
		return;
	}

	BFW::GUI::PopUp& _ScrollWindow = PopUps[_ScrollWindowIndex][0];
	BFW::GUI::PopUp& _ScrollButton = _ScrollWindow.PopUps[0][0];

	intptr_t _TrueMouseDeltaX = _Delta;

	if (_Delta < 0)
	{
		_TrueMouseDeltaX = (_Accumulation + _Delta) * (_Accumulation < -_Delta);
		_Accumulation = (_Accumulation + _Delta) * (_Accumulation > -_Delta);
	}

	if (_TrueMouseDeltaX < 0 && _ScrollButton.PositionX < -_TrueMouseDeltaX)
	{
		intptr_t _OldDelta = _TrueMouseDeltaX;
		_TrueMouseDeltaX = -_ScrollButton.PositionX;
		_Accumulation += _OldDelta - _TrueMouseDeltaX;
	}

	if (_Delta > 0)
	{
		_TrueMouseDeltaX = (_Accumulation + _Delta) * (-_Accumulation < _Delta);
		_Accumulation = (_Accumulation + _Delta) * (-_Accumulation > _Delta);
	}

	if (_TrueMouseDeltaX > 0 && (_ScrollWindow.Width - (_ScrollButton.PositionX + _ScrollButton.Width)) * (_ScrollWindow.Width > _ScrollButton.PositionX + _ScrollButton.Width) < (size_t)(_TrueMouseDeltaX))
	{
		intptr_t _OldDelta = _TrueMouseDeltaX;
		_TrueMouseDeltaX = (_ScrollWindow.Width - (_ScrollButton.PositionX + _ScrollButton.Width)) * (_ScrollWindow.Width > _ScrollButton.PositionX + _ScrollButton.Width);
		_Accumulation += _OldDelta - _TrueMouseDeltaX;
	}

	_ScrollButton.SetPositionX(_ScrollButton.PositionX + _TrueMouseDeltaX);

	intptr_t _ScrollDelta = ScrollX;

	SetScrollX(_ScrollButton.PositionX * (TrueWidth - Width) / (_ScrollWindow.Width - _ScrollWindow.Width * Width / TrueWidth));

	_ScrollDelta = ScrollX - _ScrollDelta;

	for (size_t _Layer = 0; _Layer < PopUps.GetSize(); _Layer++)
	{
		for (size_t _Index = 0; _Index < PopUps[_Layer].GetSize(); _Index++)
		{
			uint64_t _Id = PopUps[_Layer][_Index].Id;

			if (_Id == _LeftResizePopUpId || _Id == _RightResizePopUpId || _Id == _TopResizePopUpId || _Id == _BottomResizePopUpId || _Id == _LeftTopResizePopUpId || _Id == _LeftBottomResizePopUpId || _Id == _RightTopResizePopUpId || _Id == _RightBottomResizePopUpId || _Id == _HScrollWindowPopUpId || _Id == _VScrollWindowPopUpId || _Id == _ScrollCornerPopUpId || _IgnoreScroll(_Id))
			{
				PopUps[_Layer][_Index].SetPositionX(PopUps[_Layer][_Index].PositionX + _ScrollDelta);
			}
		}
	}
}

void BFW::GUI::PopUp::ScrollWithMouseV(const intptr_t _Delta, intptr_t& _Accumulation, const IgnoreScrollFnc _IgnoreScroll)
{
	if (TrueHeight == Height)
	{
		return;
	}

	size_t _ScrollWindowIndex = 0;

	if (!FindFocusedPopUpLayer(_ScrollWindowIndex, _VScrollWindowPopUpId))
	{
		return;
	}

	BFW::GUI::PopUp& _ScrollWindow = PopUps[_ScrollWindowIndex][0];
	BFW::GUI::PopUp& _ScrollButton = _ScrollWindow.PopUps[0][0];

	intptr_t _TrueMouseDeltaY = _Delta;

	if (_Delta < 0)
	{
		_TrueMouseDeltaY = (_Accumulation + _Delta) * (_Accumulation < -_Delta);
		_Accumulation = (_Accumulation + _Delta) * (_Accumulation > -_Delta);
	}

	if (_TrueMouseDeltaY < 0 && _ScrollButton.PositionY < -_TrueMouseDeltaY)
	{
		intptr_t _OldDelta = _TrueMouseDeltaY;
		_TrueMouseDeltaY = -_ScrollButton.PositionY;
		_Accumulation += _OldDelta - _TrueMouseDeltaY;
	}

	if (_Delta > 0)
	{
		_TrueMouseDeltaY = (_Accumulation + _Delta) * (-_Accumulation < _Delta);
		_Accumulation = (_Accumulation + _Delta) * (-_Accumulation > _Delta);
	}

	if (_TrueMouseDeltaY > 0 && (_ScrollWindow.Height - (_ScrollButton.PositionY + _ScrollButton.Height)) * (_ScrollWindow.Height > _ScrollButton.PositionY + _ScrollButton.Height) < (size_t)(_TrueMouseDeltaY))
	{
		intptr_t _OldDelta = _TrueMouseDeltaY;
		_TrueMouseDeltaY = (_ScrollWindow.Height - (_ScrollButton.PositionY + _ScrollButton.Height)) * (_ScrollWindow.Height > _ScrollButton.PositionY + _ScrollButton.Height);
		_Accumulation += _OldDelta - _TrueMouseDeltaY;
	}

	_ScrollButton.SetPositionY(_ScrollButton.PositionY + _TrueMouseDeltaY);

	intptr_t _ScrollDelta = ScrollY;

	SetScrollY(_ScrollButton.PositionY * (TrueHeight - Height) / (_ScrollWindow.Height - _ScrollWindow.Height * Height / TrueHeight));

	_ScrollDelta = ScrollY - _ScrollDelta;

	for (size_t _Layer = 0; _Layer < PopUps.GetSize(); _Layer++)
	{
		for (size_t _Index = 0; _Index < PopUps[_Layer].GetSize(); _Index++)
		{
			uint64_t _Id = PopUps[_Layer][_Index].Id;

			if (_Id == _LeftResizePopUpId || _Id == _RightResizePopUpId || _Id == _TopResizePopUpId || _Id == _BottomResizePopUpId || _Id == _LeftTopResizePopUpId || _Id == _LeftBottomResizePopUpId || _Id == _RightTopResizePopUpId || _Id == _RightBottomResizePopUpId || _Id == _HScrollWindowPopUpId || _Id == _VScrollWindowPopUpId || _Id == _ScrollCornerPopUpId || _IgnoreScroll(_Id))
			{
				PopUps[_Layer][_Index].SetPositionY(PopUps[_Layer][_Index].PositionY + _ScrollDelta);
			}
		}
	}
}

void BFW::GUI::PopUp::ResizeWithMouse(const uint64_t _ResizePopUpId, PopUp& _Parent, const intptr_t _MouseDeltaX, const intptr_t _MouseDeltaY, intptr_t& _AccumulationX, intptr_t& _AccumulationY, const ResizePopUpLayerFnc _ResizePopUpLayer, const GetMinFnc _GetMinX, const GetMinFnc _GetMinY, const size_t _ResizeSize, const ForceScrollFnc _ForceHScroll, const ForceScrollFnc _ForceVScroll, const size_t _ScrollSize, const size_t _ScrollTopPadding, const size_t _ScrollPadding, const GetRenderingDescriptorFnc _GetRenderingDescriptor, const GenerateUserDataFnc _GenerateUserData, const ReleaseUserDataFnc _ReleaseUserData, void* _Global)
{
	bool _Found = false;

	for (size_t _Index = 0; _Index < _Parent.Nodes.GetSize(); _Index++)
	{
		if (this == &_Parent.Nodes[_Index])
		{
			_Found = true;
			break;
		}
	}

	if (_Found)
	{
		BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Mouse capture style resize attempt on node window is not allowed!"));
		return;
	}

	for (size_t _Index = 0; _Index < _Parent.Panels.GetSize(); _Index++)
	{
		if (this == &_Parent.Panels[_Index])
		{
			_Found = true;
			break;
		}
	}

	if (_Found)
	{
		for (size_t _Index = 0; _Index < _Parent.Panels.GetSize(); _Index++)
		{
			switch (_ResizePopUpId)
			{
			case _LeftResizePopUpId:
			{
				intptr_t _TrueMouseDeltaX = _MouseDeltaX;

				if (_MouseDeltaX > 0)
				{
					_TrueMouseDeltaX = (_AccumulationX + _MouseDeltaX) * (-_AccumulationX < _MouseDeltaX);
					_AccumulationX = (_AccumulationX + _MouseDeltaX) * (-_AccumulationX > _MouseDeltaX);
				}

				if (_TrueMouseDeltaX > 0 && (_Parent.Panels[_Index].Width - _ResizeSize) * (_Parent.Panels[_Index].Width > _ResizeSize) < (size_t)(_TrueMouseDeltaX))
				{
					intptr_t _OldMouseDeltaX = _TrueMouseDeltaX;
					_TrueMouseDeltaX = (_Parent.Panels[_Index].Width - _ResizeSize) * (_Parent.Panels[_Index].Width > _ResizeSize);
					_AccumulationX += _OldMouseDeltaX - _TrueMouseDeltaX;
				}

				if (_MouseDeltaX < 0)
				{
					_TrueMouseDeltaX = (_AccumulationX + _MouseDeltaX) * (_AccumulationX < -_MouseDeltaX);
					_AccumulationX = (_AccumulationX + _MouseDeltaX) * (_AccumulationX > -_MouseDeltaX);
				}

				if (_TrueMouseDeltaX < 0 && (_Parent.Width - _Parent.Panels[_Index].Width) * (_Parent.Width > _Parent.Panels[_Index].Width) < (size_t)(-_TrueMouseDeltaX))
				{
					intptr_t _OldMouseDeltaX = _TrueMouseDeltaX;
					_TrueMouseDeltaX = -(intptr_t)((_Parent.Width - _Parent.Panels[_Index].Width) * (_Parent.Width > _Parent.Panels[_Index].Width));
					_AccumulationX += _OldMouseDeltaX - _TrueMouseDeltaX;
				}

				_Parent.Panels[_Index].SetWidth(_Parent.Panels[_Index].Width - _TrueMouseDeltaX);
				_Parent.Panels[_Index].SetTrueWidth(_GetMinX(_Parent.Panels[_Index]));
				_Parent.Panels[_Index].SetPositionX(_Parent.Panels[_Index].PositionX + _TrueMouseDeltaX);

				break;
			}
			case _RightResizePopUpId:
			{
				intptr_t _TrueMouseDeltaX = _MouseDeltaX;

				if (_MouseDeltaX < 0)
				{
					_TrueMouseDeltaX = (_AccumulationX + _MouseDeltaX) * (_AccumulationX < -_MouseDeltaX);
					_AccumulationX = (_AccumulationX + _MouseDeltaX) * (_AccumulationX > -_MouseDeltaX);
				}

				if (_TrueMouseDeltaX < 0 && (_Parent.Panels[_Index].Width - _ResizeSize) * (_Parent.Panels[_Index].Width > _ResizeSize) < (size_t)(-_TrueMouseDeltaX))
				{
					intptr_t _OldMouseDeltaX = _TrueMouseDeltaX;
					_TrueMouseDeltaX = -(intptr_t)((_Parent.Panels[_Index].Width - _ResizeSize) * (_Parent.Panels[_Index].Width > _ResizeSize));
					_AccumulationX += _OldMouseDeltaX - _TrueMouseDeltaX;
				}

				if (_MouseDeltaX > 0)
				{
					_TrueMouseDeltaX = (_AccumulationX + _MouseDeltaX) * (-_AccumulationX < _MouseDeltaX);
					_AccumulationX = (_AccumulationX + _MouseDeltaX) * (-_AccumulationX > _MouseDeltaX);
				}

				if (_TrueMouseDeltaX > 0 && (_Parent.Width - _Parent.Panels[_Index].Width) * (_Parent.Width > _Parent.Panels[_Index].Width) < (size_t)(_TrueMouseDeltaX))
				{
					intptr_t _OldMouseDeltaX = _TrueMouseDeltaX;
					_TrueMouseDeltaX = (_Parent.Width - _Parent.Panels[_Index].Width) * (_Parent.Width > _Parent.Panels[_Index].Width);
					_AccumulationX += _OldMouseDeltaX - _TrueMouseDeltaX;
				}

				_Parent.Panels[_Index].SetWidth(_Parent.Panels[_Index].Width + _TrueMouseDeltaX);
				_Parent.Panels[_Index].SetTrueWidth(_GetMinX(_Parent.Panels[_Index]));

				break;
			}
			case _TopResizePopUpId:
			{
				intptr_t _TrueMouseDeltaY = _MouseDeltaY;

				if (_MouseDeltaY > 0)
				{
					_TrueMouseDeltaY = (_AccumulationY + _MouseDeltaY) * (-_AccumulationY < _MouseDeltaY);
					_AccumulationY = (_AccumulationY + _MouseDeltaY) * (-_AccumulationY > _MouseDeltaY);
				}

				if (_TrueMouseDeltaY > 0 && (_Parent.Panels[_Index].Height - _ResizeSize) * (_Parent.Panels[_Index].Height > _ResizeSize) < (size_t)(_TrueMouseDeltaY))
				{
					intptr_t _OldMouseDeltaY = _TrueMouseDeltaY;
					_TrueMouseDeltaY = (_Parent.Panels[_Index].Height - _ResizeSize) * (_Parent.Panels[_Index].Height > _ResizeSize);
					_AccumulationY += _OldMouseDeltaY - _TrueMouseDeltaY;
				}

				if (_MouseDeltaY < 0)
				{
					_TrueMouseDeltaY = (_AccumulationY + _MouseDeltaY) * (_AccumulationY < -_MouseDeltaY);
					_AccumulationY = (_AccumulationY + _MouseDeltaY) * (_AccumulationY > -_MouseDeltaY);
				}

				if (_TrueMouseDeltaY < 0 && (_Parent.Height - _Parent.Panels[_Index].Height) * (_Parent.Height > _Parent.Panels[_Index].Height) < (size_t)(-_TrueMouseDeltaY))
				{
					intptr_t _OldMouseDeltaY = _TrueMouseDeltaY;
					_TrueMouseDeltaY = -(intptr_t)((_Parent.Height - _Parent.Panels[_Index].Height) * (_Parent.Height > _Parent.Panels[_Index].Height));
					_AccumulationY += _OldMouseDeltaY - _TrueMouseDeltaY;
				}

				_Parent.Panels[_Index].SetHeight(_Parent.Panels[_Index].Height - _TrueMouseDeltaY);
				_Parent.Panels[_Index].SetTrueHeight(_GetMinY(_Parent.Panels[_Index]));
				_Parent.Panels[_Index].SetPositionY(_Parent.Panels[_Index].PositionY + _TrueMouseDeltaY);

				break;
			}
			case _BottomResizePopUpId:
			{
				intptr_t _TrueMouseDeltaY = _MouseDeltaY;

				if (_MouseDeltaY < 0)
				{
					_TrueMouseDeltaY = (_AccumulationY + _MouseDeltaY) * (_AccumulationY < -_MouseDeltaY);
					_AccumulationY = (_AccumulationY + _MouseDeltaY) * (_AccumulationY > -_MouseDeltaY);
				}

				if (_TrueMouseDeltaY < 0 && (_Parent.Panels[_Index].Height - _ResizeSize) * (_Parent.Panels[_Index].Height > _ResizeSize) < (size_t)(-_TrueMouseDeltaY))
				{
					intptr_t _OldMouseDeltaY = _TrueMouseDeltaY;
					_TrueMouseDeltaY = -(intptr_t)((_Parent.Panels[_Index].Height - _ResizeSize) * (_Parent.Panels[_Index].Height > _ResizeSize));
					_AccumulationY += _OldMouseDeltaY - _TrueMouseDeltaY;
				}

				if (_MouseDeltaY > 0)
				{
					_TrueMouseDeltaY = (_AccumulationY + _MouseDeltaY) * (-_AccumulationY < _MouseDeltaY);
					_AccumulationY = (_AccumulationY + _MouseDeltaY) * (-_AccumulationY > _MouseDeltaY);
				}

				if (_TrueMouseDeltaY > 0 && (_Parent.Height - _Parent.Panels[_Index].Height) * (_Parent.Height > _Parent.Panels[_Index].Height) < (size_t)(_TrueMouseDeltaY))
				{
					intptr_t _OldMouseDeltaY = _TrueMouseDeltaY;
					_TrueMouseDeltaY = (_Parent.Height - _Parent.Panels[_Index].Height) * (_Parent.Height > _Parent.Panels[_Index].Height);
					_AccumulationY += _OldMouseDeltaY - _TrueMouseDeltaY;
				}

				_Parent.Panels[_Index].SetHeight(_Parent.Panels[_Index].Height + _TrueMouseDeltaY);
				_Parent.Panels[_Index].SetTrueHeight(_GetMinY(_Parent.Panels[_Index]));

				break;
			}
			case _LeftTopResizePopUpId:
			{
				BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Can't resize panel with this resize popup id!"));
				return;
			}
			case _LeftBottomResizePopUpId:
			{
				BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Can't resize panel with this resize popup id!"));
				return;
			}
			case _RightTopResizePopUpId:
			{
				BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Can't resize panel with this resize popup id!"));
				return;
			}
			case _RightBottomResizePopUpId:
			{
				BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Can't resize panel with this resize popup id!"));
				return;
			}
			default:
			{
				BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Can't resize panel with this resize popup id!"));
				return;
			}
			}
		}

		_Parent.ResizeChilds(_ResizePopUpLayer, _GetMinX, _GetMinY, _ResizeSize, _ForceHScroll, _ForceVScroll, _ScrollSize, _ScrollTopPadding, _ScrollPadding, _GetRenderingDescriptor, _GenerateUserData, _ReleaseUserData, _Global);

		return;
	}

	for (size_t _Layer = 0; _Layer < _Parent.PopUps.GetSize(); _Layer++)
	{
		for (size_t _Index = 0; _Index < _Parent.PopUps[_Layer].GetSize(); _Index++)
		{
			if (this == &_Parent.PopUps[_Layer][_Index])
			{
				_Found = true;
				break;
			}
		}

		if (_Found)
		{
			for (size_t _Index = 0; _Index < _Parent.PopUps[_Layer].GetSize(); _Index++)
			{
				switch (_ResizePopUpId)
				{
				case _LeftResizePopUpId:
				{
					intptr_t _TrueMouseDeltaX = _MouseDeltaX;

					if (_MouseDeltaX > 0 && (_Parent.PopUps[_Layer][_Index].Width - _ResizeSize * 2) * (_Parent.PopUps[_Layer][_Index].Width > _ResizeSize * 2) < (size_t)(_MouseDeltaX))
					{
						_TrueMouseDeltaX = (_Parent.PopUps[_Layer][_Index].Width - _ResizeSize * 2) * (_Parent.PopUps[_Layer][_Index].Width > _ResizeSize * 2);
						_AccumulationX += _MouseDeltaX - _TrueMouseDeltaX;
					}

					if (_MouseDeltaX < 0)
					{
						_TrueMouseDeltaX = (_AccumulationX + _MouseDeltaX) * (_AccumulationX < -_MouseDeltaX);
						_AccumulationX = (_AccumulationX + _MouseDeltaX) * (_AccumulationX > -_MouseDeltaX);
					}

					_Parent.PopUps[_Layer][_Index].SetWidth(_Parent.PopUps[_Layer][_Index].Width - _TrueMouseDeltaX);
					_Parent.PopUps[_Layer][_Index].SetTrueWidth(_GetMinX(_Parent.PopUps[_Layer][_Index]));
					_Parent.PopUps[_Layer][_Index].SetPositionX(_Parent.PopUps[_Layer][_Index].PositionX + _TrueMouseDeltaX);

					break;
				}
				case _RightResizePopUpId:
				{
					intptr_t _TrueMouseDeltaX = _MouseDeltaX;

					if (_MouseDeltaX < 0 && (_Parent.PopUps[_Layer][_Index].Width - _ResizeSize * 2) * (_Parent.PopUps[_Layer][_Index].Width > _ResizeSize * 2) < (size_t)(-_MouseDeltaX))
					{
						_TrueMouseDeltaX = -(intptr_t)((_Parent.PopUps[_Layer][_Index].Width - _ResizeSize * 2) * (_Parent.PopUps[_Layer][_Index].Width > _ResizeSize * 2));
						_AccumulationX += _MouseDeltaX - _TrueMouseDeltaX;
					}

					if (_MouseDeltaX > 0)
					{
						_TrueMouseDeltaX = (_AccumulationX + _MouseDeltaX) * (-_AccumulationX < _MouseDeltaX);
						_AccumulationX = (_AccumulationX + _MouseDeltaX) * (-_AccumulationX > _MouseDeltaX);
					}

					_Parent.PopUps[_Layer][_Index].SetWidth(_Parent.PopUps[_Layer][_Index].Width + _TrueMouseDeltaX);
					_Parent.PopUps[_Layer][_Index].SetTrueWidth(_GetMinX(_Parent.PopUps[_Layer][_Index]));

					break;
				}
				case _TopResizePopUpId:
				{
					intptr_t _TrueMouseDeltaY = _MouseDeltaY;

					if (_MouseDeltaY > 0 && (_Parent.PopUps[_Layer][_Index].Height - _ResizeSize * 2) * (_Parent.PopUps[_Layer][_Index].Height > _ResizeSize * 2) < (size_t)(_MouseDeltaY))
					{
						_TrueMouseDeltaY = (_Parent.PopUps[_Layer][_Index].Height - _ResizeSize * 2) * (_Parent.PopUps[_Layer][_Index].Height > _ResizeSize * 2);
						_AccumulationY += _MouseDeltaY - _TrueMouseDeltaY;
					}

					if (_MouseDeltaY < 0)
					{
						_TrueMouseDeltaY = (_AccumulationY + _MouseDeltaY) * (_AccumulationY < -_MouseDeltaY);
						_AccumulationY = (_AccumulationY + _MouseDeltaY) * (_AccumulationY > -_MouseDeltaY);
					}

					_Parent.PopUps[_Layer][_Index].SetHeight(_Parent.PopUps[_Layer][_Index].Height - _TrueMouseDeltaY);
					_Parent.PopUps[_Layer][_Index].SetTrueHeight(_GetMinY(_Parent.PopUps[_Layer][_Index]));
					_Parent.PopUps[_Layer][_Index].SetPositionY(_Parent.PopUps[_Layer][_Index].PositionY + _TrueMouseDeltaY);

					break;
				}
				case _BottomResizePopUpId:
				{
					intptr_t _TrueMouseDeltaY = _MouseDeltaY;

					if (_MouseDeltaY < 0 && (_Parent.PopUps[_Layer][_Index].Height - _ResizeSize * 2) * (_Parent.PopUps[_Layer][_Index].Height > _ResizeSize * 2) < (size_t)(-_MouseDeltaY))
					{
						_TrueMouseDeltaY = -(intptr_t)((_Parent.PopUps[_Layer][_Index].Height - _ResizeSize * 2) * (_Parent.PopUps[_Layer][_Index].Height > _ResizeSize * 2));
						_AccumulationY += _MouseDeltaY - _TrueMouseDeltaY;
					}

					if (_MouseDeltaY > 0)
					{
						_TrueMouseDeltaY = (_AccumulationY + _MouseDeltaY) * (-_AccumulationY < _MouseDeltaY);
						_AccumulationY = (_AccumulationY + _MouseDeltaY) * (-_AccumulationY > _MouseDeltaY);
					}

					_Parent.PopUps[_Layer][_Index].SetHeight(_Parent.PopUps[_Layer][_Index].Height + _TrueMouseDeltaY);
					_Parent.PopUps[_Layer][_Index].SetTrueHeight(_GetMinY(_Parent.PopUps[_Layer][_Index]));

					break;
				}
				case _LeftTopResizePopUpId:
				{
					intptr_t _TrueMouseDeltaX = _MouseDeltaX;

					if (_MouseDeltaX > 0 && (_Parent.PopUps[_Layer][_Index].Width - _ResizeSize * 2) * (_Parent.PopUps[_Layer][_Index].Width > _ResizeSize * 2) < (size_t)(_MouseDeltaX))
					{
						_TrueMouseDeltaX = (_Parent.PopUps[_Layer][_Index].Width - _ResizeSize * 2) * (_Parent.PopUps[_Layer][_Index].Width > _ResizeSize * 2);
						_AccumulationX += _MouseDeltaX - _TrueMouseDeltaX;
					}

					if (_MouseDeltaX < 0)
					{
						_TrueMouseDeltaX = (_AccumulationX + _MouseDeltaX) * (_AccumulationX < -_MouseDeltaX);
						_AccumulationX = (_AccumulationX + _MouseDeltaX) * (_AccumulationX > -_MouseDeltaX);
					}

					intptr_t _TrueMouseDeltaY = _MouseDeltaY;

					if (_MouseDeltaY > 0 && (_Parent.PopUps[_Layer][_Index].Height - _ResizeSize * 2) * (_Parent.PopUps[_Layer][_Index].Height > _ResizeSize * 2) < (size_t)(_MouseDeltaY))
					{
						_TrueMouseDeltaY = (_Parent.PopUps[_Layer][_Index].Height - _ResizeSize * 2) * (_Parent.PopUps[_Layer][_Index].Height > _ResizeSize * 2);
						_AccumulationY += _MouseDeltaY - _TrueMouseDeltaY;
					}

					if (_MouseDeltaY < 0)
					{
						_TrueMouseDeltaY = (_AccumulationY + _MouseDeltaY) * (_AccumulationY < -_MouseDeltaY);
						_AccumulationY = (_AccumulationY + _MouseDeltaY) * (_AccumulationY > -_MouseDeltaY);
					}

					_Parent.PopUps[_Layer][_Index].SetWidth(_Parent.PopUps[_Layer][_Index].Width - _TrueMouseDeltaX);
					_Parent.PopUps[_Layer][_Index].SetHeight(_Parent.PopUps[_Layer][_Index].Height - _TrueMouseDeltaY);
					_Parent.PopUps[_Layer][_Index].SetTrueWidth(_GetMinX(_Parent.PopUps[_Layer][_Index]));
					_Parent.PopUps[_Layer][_Index].SetTrueHeight(_GetMinY(_Parent.PopUps[_Layer][_Index]));
					_Parent.PopUps[_Layer][_Index].SetPositionX(_Parent.PopUps[_Layer][_Index].PositionX + _TrueMouseDeltaX);
					_Parent.PopUps[_Layer][_Index].SetPositionY(_Parent.PopUps[_Layer][_Index].PositionY + _TrueMouseDeltaY);

					break;
				}
				case _LeftBottomResizePopUpId:
				{
					intptr_t _TrueMouseDeltaX = _MouseDeltaX;

					if (_MouseDeltaX > 0 && (_Parent.PopUps[_Layer][_Index].Width - _ResizeSize * 2) * (_Parent.PopUps[_Layer][_Index].Width > _ResizeSize * 2) < (size_t)(_MouseDeltaX))
					{
						_TrueMouseDeltaX = (_Parent.PopUps[_Layer][_Index].Width - _ResizeSize * 2) * (_Parent.PopUps[_Layer][_Index].Width > _ResizeSize * 2);
						_AccumulationX += _MouseDeltaX - _TrueMouseDeltaX;
					}

					if (_MouseDeltaX < 0)
					{
						_TrueMouseDeltaX = (_AccumulationX + _MouseDeltaX) * (_AccumulationX < -_MouseDeltaX);
						_AccumulationX = (_AccumulationX + _MouseDeltaX) * (_AccumulationX > -_MouseDeltaX);
					}

					intptr_t _TrueMouseDeltaY = _MouseDeltaY;

					if (_MouseDeltaY < 0 && (_Parent.PopUps[_Layer][_Index].Height - _ResizeSize * 2) * (_Parent.PopUps[_Layer][_Index].Height > _ResizeSize * 2) < (size_t)(-_MouseDeltaY))
					{
						_TrueMouseDeltaY = -(intptr_t)((_Parent.PopUps[_Layer][_Index].Height - _ResizeSize * 2) * (_Parent.PopUps[_Layer][_Index].Height > _ResizeSize * 2));
						_AccumulationY += _MouseDeltaY - _TrueMouseDeltaY;
					}

					if (_MouseDeltaY > 0)
					{
						_TrueMouseDeltaY = (_AccumulationY + _MouseDeltaY) * (-_AccumulationY < _MouseDeltaY);
						_AccumulationY = (_AccumulationY + _MouseDeltaY) * (-_AccumulationY > _MouseDeltaY);
					}

					_Parent.PopUps[_Layer][_Index].SetWidth(_Parent.PopUps[_Layer][_Index].Width - _TrueMouseDeltaX);
					_Parent.PopUps[_Layer][_Index].SetHeight(_Parent.PopUps[_Layer][_Index].Height + _TrueMouseDeltaY);
					_Parent.PopUps[_Layer][_Index].SetTrueWidth(_GetMinX(_Parent.PopUps[_Layer][_Index]));
					_Parent.PopUps[_Layer][_Index].SetTrueHeight(_GetMinY(_Parent.PopUps[_Layer][_Index]));
					_Parent.PopUps[_Layer][_Index].SetPositionX(_Parent.PopUps[_Layer][_Index].PositionX + _TrueMouseDeltaX);

					break;
				}
				case _RightTopResizePopUpId:
				{
					intptr_t _TrueMouseDeltaX = _MouseDeltaX;

					if (_MouseDeltaX < 0 && (_Parent.PopUps[_Layer][_Index].Width - _ResizeSize * 2) * (_Parent.PopUps[_Layer][_Index].Width > _ResizeSize * 2) < (size_t)(-_MouseDeltaX))
					{
						_TrueMouseDeltaX = -(intptr_t)((_Parent.PopUps[_Layer][_Index].Width - _ResizeSize * 2) * (_Parent.PopUps[_Layer][_Index].Width > _ResizeSize * 2));
						_AccumulationX += _MouseDeltaX - _TrueMouseDeltaX;
					}

					if (_MouseDeltaX > 0)
					{
						_TrueMouseDeltaX = (_AccumulationX + _MouseDeltaX) * (-_AccumulationX < _MouseDeltaX);
						_AccumulationX = (_AccumulationX + _MouseDeltaX) * (-_AccumulationX > _MouseDeltaX);
					}

					intptr_t _TrueMouseDeltaY = _MouseDeltaY;

					if (_MouseDeltaY > 0 && (_Parent.PopUps[_Layer][_Index].Height - _ResizeSize * 2) * (_Parent.PopUps[_Layer][_Index].Height > _ResizeSize * 2) < (size_t)(_MouseDeltaY))
					{
						_TrueMouseDeltaY = (_Parent.PopUps[_Layer][_Index].Height - _ResizeSize * 2) * (_Parent.PopUps[_Layer][_Index].Height > _ResizeSize * 2);
						_AccumulationY += _MouseDeltaY - _TrueMouseDeltaY;
					}

					if (_MouseDeltaY < 0)
					{
						_TrueMouseDeltaY = (_AccumulationY + _MouseDeltaY) * (_AccumulationY < -_MouseDeltaY);
						_AccumulationY = (_AccumulationY + _MouseDeltaY) * (_AccumulationY > -_MouseDeltaY);
					}

					_Parent.PopUps[_Layer][_Index].SetWidth(_Parent.PopUps[_Layer][_Index].Width + _TrueMouseDeltaX);
					_Parent.PopUps[_Layer][_Index].SetHeight(_Parent.PopUps[_Layer][_Index].Height - _TrueMouseDeltaY);
					_Parent.PopUps[_Layer][_Index].SetTrueHeight(_GetMinY(_Parent.PopUps[_Layer][_Index]));
					_Parent.PopUps[_Layer][_Index].SetTrueWidth(_GetMinX(_Parent.PopUps[_Layer][_Index]));
					_Parent.PopUps[_Layer][_Index].SetPositionY(_Parent.PopUps[_Layer][_Index].PositionY + _TrueMouseDeltaY);

					break;
				}
				case _RightBottomResizePopUpId:
				{
					intptr_t _TrueMouseDeltaX = _MouseDeltaX;

					if (_MouseDeltaX < 0 && (_Parent.PopUps[_Layer][_Index].Width - _ResizeSize * 2) * (_Parent.PopUps[_Layer][_Index].Width > _ResizeSize * 2) < (size_t)(-_MouseDeltaX))
					{
						_TrueMouseDeltaX = -(intptr_t)((_Parent.PopUps[_Layer][_Index].Width - _ResizeSize * 2) * (_Parent.PopUps[_Layer][_Index].Width > _ResizeSize * 2));
						_AccumulationX += _MouseDeltaX - _TrueMouseDeltaX;
					}

					if (_MouseDeltaX > 0)
					{
						_TrueMouseDeltaX = (_AccumulationX + _MouseDeltaX) * (-_AccumulationX < _MouseDeltaX);
						_AccumulationX = (_AccumulationX + _MouseDeltaX) * (-_AccumulationX > _MouseDeltaX);
					}

					intptr_t _TrueMouseDeltaY = _MouseDeltaY;

					if (_MouseDeltaY < 0 && (_Parent.PopUps[_Layer][_Index].Height - _ResizeSize * 2) * (_Parent.PopUps[_Layer][_Index].Height > _ResizeSize * 2) < (size_t)(-_MouseDeltaY))
					{
						_TrueMouseDeltaY = -(intptr_t)((_Parent.PopUps[_Layer][_Index].Height - _ResizeSize * 2) * (_Parent.PopUps[_Layer][_Index].Height > _ResizeSize * 2));
						_AccumulationY += _MouseDeltaY - _TrueMouseDeltaY;
					}

					if (_MouseDeltaY > 0)
					{
						_TrueMouseDeltaY = (_AccumulationY + _MouseDeltaY) * (-_AccumulationY < _MouseDeltaY);
						_AccumulationY = (_AccumulationY + _MouseDeltaY) * (-_AccumulationY > _MouseDeltaY);
					}

					_Parent.PopUps[_Layer][_Index].SetWidth(_Parent.PopUps[_Layer][_Index].Width + _TrueMouseDeltaX);
					_Parent.PopUps[_Layer][_Index].SetHeight(_Parent.PopUps[_Layer][_Index].Height + _TrueMouseDeltaY);
					_Parent.PopUps[_Layer][_Index].SetTrueWidth(_GetMinX(_Parent.PopUps[_Layer][_Index]));
					_Parent.PopUps[_Layer][_Index].SetTrueHeight(_GetMinY(_Parent.PopUps[_Layer][_Index]));

					break;
				}
				default:
				{
					BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Can't resize popup with this resize popup id!"));
					return;
				}
				}

				_Parent.PopUps[_Layer][_Index].ResizeChilds(_ResizePopUpLayer, _GetMinX, _GetMinY, _ResizeSize, _ForceHScroll, _ForceVScroll, _ScrollSize, _ScrollTopPadding, _ScrollPadding, _GetRenderingDescriptor, _GenerateUserData, _ReleaseUserData, _Global);
			}

			return;
		}
	}

	BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Can't find the popup in the parent!"));
}

void BFW::GUI::PopUp::MoveLayerWithMouse(const size_t _Layer, const intptr_t _MouseDeltaX, const intptr_t _MouseDeltaY)
{
	for (size_t _Index = 0; _Index < PopUps[_Layer].GetSize(); _Index++)
	{
		PopUps[_Layer][_Index].PositionX += _MouseDeltaX;
		PopUps[_Layer][_Index].PositionY += _MouseDeltaY;
	}
}

void BFW::GUI::PopUp::GenerateResizeBars(const bool _IsNode, const size_t _ResizeSize, const RenderingDescriptor& _RenderFunctions, const GenerateUserDataFnc _GenerateUserData, void* _Global)
{
	if (_IsNode)
	{
		return;
	}

	if (PanelType == _NullPanelType)
	{
		size_t _Layer = PushPopUpLayer();

		PushPopUp
		(
			_Layer, _LeftResizePopUpId,
			0, 0,
			_ResizeSize, (Height - 2 * _ResizeSize) * (Height > 2 * _ResizeSize),
			ScrollX, _ResizeSize + ScrollY,
			0, 0,
			_RenderFunctions,
			_GenerateUserData(*this, _LeftResizePopUpId, _Global),
			true
		);

		_Layer = PushPopUpLayer();

		PushPopUp
		(
			_Layer, _RightResizePopUpId,
			0, 0,
			_ResizeSize, (Height - 2 * _ResizeSize) * (Height > 2 * _ResizeSize),
			(Width - _ResizeSize) * (Width > _ResizeSize) + ScrollX, _ResizeSize + ScrollY,
			0, 0,
			_RenderFunctions,
			_GenerateUserData(*this, _RightResizePopUpId, _Global),
			true
		);

		_Layer = PushPopUpLayer();

		PushPopUp
		(
			_Layer, _TopResizePopUpId,
			0, 0,
			(Width - 2 * _ResizeSize) * (Width > 2 * _ResizeSize), _ResizeSize,
			_ResizeSize + ScrollX, ScrollY,
			0, 0,
			_RenderFunctions,
			_GenerateUserData(*this, _TopResizePopUpId, _Global),
			true
		);

		_Layer = PushPopUpLayer();

		PushPopUp
		(
			_Layer, _BottomResizePopUpId,
			0, 0,
			(Width - 2 * _ResizeSize) * (Width > 2 * _ResizeSize), _ResizeSize,
			_ResizeSize + ScrollX, (Height - _ResizeSize) * (Height > _ResizeSize) + ScrollY,
			0, 0,
			_RenderFunctions,
			_GenerateUserData(*this, _BottomResizePopUpId, _Global),
			true
		);

		_Layer = PushPopUpLayer();

		PushPopUp
		(
			_Layer, _LeftTopResizePopUpId,
			0, 0,
			_ResizeSize, _ResizeSize,
			ScrollX, ScrollY,
			0, 0,
			_RenderFunctions,
			_GenerateUserData(*this, _LeftTopResizePopUpId, _Global),
			true
		);

		_Layer = PushPopUpLayer();

		PushPopUp
		(
			_Layer, _LeftBottomResizePopUpId,
			0, 0,
			_ResizeSize, _ResizeSize,
			ScrollX, (Height - _ResizeSize) * (Height > _ResizeSize) + ScrollY,
			0, 0,
			_RenderFunctions,
			_GenerateUserData(*this, _LeftBottomResizePopUpId, _Global),
			true
		);

		_Layer = PushPopUpLayer();

		PushPopUp
		(
			_Layer, _RightTopResizePopUpId,
			0, 0,
			_ResizeSize, _ResizeSize,
			(Width - _ResizeSize) * (Width > _ResizeSize) + ScrollX, ScrollY,
			0, 0,
			_RenderFunctions,
			_GenerateUserData(*this, _RightTopResizePopUpId, _Global),
			true
		);

		_Layer = PushPopUpLayer();

		PushPopUp
		(
			_Layer, _RightBottomResizePopUpId,
			0, 0,
			_ResizeSize, _ResizeSize,
			(Width - _ResizeSize) * (Width > _ResizeSize) + ScrollX, (Height - _ResizeSize) * (Height > _ResizeSize) + ScrollY,
			0, 0,
			_RenderFunctions,
			_GenerateUserData(*this, _RightBottomResizePopUpId, _Global),
			true
		);
	}

	if (PanelType == _LeftPanelType)
	{
		size_t _Layer = PushPopUpLayer();

		PushPopUp
		(
			_Layer, _RightResizePopUpId,
			0, 0,
			_ResizeSize, Height,
			(Width - _ResizeSize) * (Width > _ResizeSize) + ScrollX, ScrollY,
			0, 0,
			_RenderFunctions,
			_GenerateUserData(*this, _RightResizePopUpId, _Global),
			true
		);
	}

	if (PanelType == _RightPanelType)
	{
		size_t _Layer = PushPopUpLayer();

		PushPopUp
		(
			_Layer, _LeftResizePopUpId,
			0, 0,
			_ResizeSize, Height,
			ScrollX, ScrollY,
			0, 0,
			_RenderFunctions,
			_GenerateUserData(*this, _LeftResizePopUpId, _Global),
			true
		);
	}

	if (PanelType == _TopPanelType)
	{
		size_t _Layer = PushPopUpLayer();

		PushPopUp
		(
			_Layer, _BottomResizePopUpId,
			0, 0,
			Width, _ResizeSize,
			ScrollX, (Height - _ResizeSize) * (Height > _ResizeSize) + ScrollY,
			0, 0,
			_RenderFunctions,
			_GenerateUserData(*this, _BottomResizePopUpId, _Global),
			true
		);
	}

	if (PanelType == _BottomPanelType)
	{
		size_t _Layer = PushPopUpLayer();

		PushPopUp
		(
			_Layer, _TopResizePopUpId,
			0, 0,
			Width, _ResizeSize,
			ScrollX, ScrollY,
			0, 0,
			_RenderFunctions,
			_GenerateUserData(*this, _TopResizePopUpId, _Global),
			true
		);
	}
}

void BFW::GUI::PopUp::GenerateScrollBars(const bool _HasHScroll, const bool _HasVScroll, const bool _ForceHScroll, const bool _ForceVScroll, const size_t _ScrollSize, const size_t _ScrollTopPadding, const size_t _ScrollPadding, const GetRenderingDescriptorFnc _GetRenderingDescriptor, const GenerateUserDataFnc _GenerateUserData, void* _Global)
{
	if (Width < TrueWidth && !_HasHScroll)
	{
		size_t _Layer = PushPopUpLayer();

		PopUp& _ScrollWindow = PushPopUp
		(
			_Layer, _HScrollWindowPopUpId,
			0, 0,
			(Width - (_ScrollPadding * 2 + _ScrollSize)) * (Width > _ScrollPadding * 2 + _ScrollSize), _ScrollSize,
			_ScrollPadding + ScrollX, Height - (_ScrollPadding + _ScrollSize) + ScrollY,
			0, 0,
			_GetRenderingDescriptor(_HScrollWindowPopUpId),
			_GenerateUserData(*this, _HScrollWindowPopUpId, _Global),
			true
		);

		_Layer = _ScrollWindow.PushPopUpLayer();

		_ScrollWindow.PushPopUp
		(
			_Layer, _HScrollButtonPopUpId,
			0, 0,
			_ScrollWindow.Width * Width / TrueWidth, _ScrollSize,
			ScrollX * (_ScrollWindow.Width - _ScrollWindow.Width * Width / TrueWidth) / (TrueWidth - Width), 0,
			0, 0,
			_GetRenderingDescriptor(_HScrollButtonPopUpId),
			_GenerateUserData(_ScrollWindow, _HScrollButtonPopUpId, _Global),
			true
		);
	}
	else if (_ForceHScroll && !_HasHScroll)
	{
		size_t _Layer = PushPopUpLayer();

		PopUp& _ScrollWindow = PushPopUp
		(
			_Layer, _HScrollWindowPopUpId,
			0, 0,
			(Width - (_ScrollPadding * 2 + _ScrollSize)) * (Width > _ScrollPadding * 2 + _ScrollSize), _ScrollSize,
			_ScrollPadding + ScrollX, Height - (_ScrollPadding + _ScrollSize) + ScrollY,
			0, 0,
			_GetRenderingDescriptor(_HScrollWindowPopUpId),
			_GenerateUserData(*this, _HScrollWindowPopUpId, _Global),
			true
		);

		_Layer = _ScrollWindow.PushPopUpLayer();

		_ScrollWindow.PushPopUp
		(
			_Layer, _HScrollButtonPopUpId,
			0, 0,
			_ScrollWindow.Width, _ScrollSize,
			0, 0,
			0, 0,
			_GetRenderingDescriptor(_HScrollButtonPopUpId),
			_GenerateUserData(_ScrollWindow, _HScrollButtonPopUpId, _Global),
			true
		);
	}

	if (Height < TrueHeight && !_HasVScroll)
	{
		size_t _Layer = PushPopUpLayer();

		PopUp& _ScrollWindow = PushPopUp
		(
			_Layer, _VScrollWindowPopUpId,
			0, 0,
			_ScrollSize, (Height - (_ScrollTopPadding + _ScrollPadding + _ScrollSize)) * (Height > _ScrollTopPadding + _ScrollPadding + _ScrollSize),
			Width - (_ScrollPadding + _ScrollSize) + ScrollX, _ScrollTopPadding + ScrollY,
			0, 0,
			_GetRenderingDescriptor(_VScrollWindowPopUpId),
			_GenerateUserData(*this, _VScrollWindowPopUpId, _Global),
			true
		);

		_Layer = _ScrollWindow.PushPopUpLayer();

		_ScrollWindow.PushPopUp
		(
			_Layer, _VScrollButtonPopUpId,
			0, 0,
			_ScrollSize, _ScrollWindow.Height * Height / TrueHeight,
			0, ScrollY * (_ScrollWindow.Height - _ScrollWindow.Height * Height / TrueHeight) / (TrueHeight - Height),
			0, 0,
			_GetRenderingDescriptor(_VScrollButtonPopUpId),
			_GenerateUserData(_ScrollWindow, _VScrollButtonPopUpId, _Global),
			true
		);
	}
	else if (_ForceVScroll && !_HasVScroll)
	{
		size_t _Layer = PushPopUpLayer();

		PopUp& _ScrollWindow = PushPopUp
		(
			_Layer, _VScrollWindowPopUpId,
			0, 0,
			_ScrollSize, (Height - (_ScrollTopPadding + _ScrollPadding + _ScrollSize)) * (Height > _ScrollTopPadding + _ScrollPadding + _ScrollSize),
			Width - (_ScrollPadding + _ScrollSize) + ScrollX, _ScrollTopPadding + ScrollY,
			0, 0,
			_GetRenderingDescriptor(_VScrollWindowPopUpId),
			_GenerateUserData(*this, _VScrollWindowPopUpId, _Global),
			true
		);

		_Layer = _ScrollWindow.PushPopUpLayer();

		_ScrollWindow.PushPopUp
		(
			_Layer, _VScrollButtonPopUpId,
			0, 0,
			_ScrollSize, _ScrollWindow.Height,
			0, 0,
			0, 0,
			_GetRenderingDescriptor(_VScrollButtonPopUpId),
			_GenerateUserData(_ScrollWindow, _VScrollButtonPopUpId, _Global),
			true
		);
	}

	if ((Width < TrueWidth || Height < TrueHeight) && (!_HasHScroll && !_HasVScroll))
	{
		size_t _Layer = PushPopUpLayer();

		PushPopUp
		(
			_Layer, _ScrollCornerPopUpId,
			0, 0,
			_ScrollSize, _ScrollSize,
			Width - (_ScrollPadding + _ScrollSize) + ScrollX, Height - (_ScrollPadding + _ScrollSize) + ScrollY,
			0, 0,
			_GetRenderingDescriptor(_ScrollCornerPopUpId),
			_GenerateUserData(*this, _ScrollCornerPopUpId, _Global),
			true
		);
	}
	else if ((_ForceHScroll || _ForceVScroll) && (!_HasHScroll && !_HasVScroll))
	{
		size_t _Layer = PushPopUpLayer();

		PushPopUp
		(
			_Layer, _ScrollCornerPopUpId,
			0, 0,
			_ScrollSize, _ScrollSize,
			Width - (_ScrollPadding + _ScrollSize) + ScrollX, Height - (_ScrollPadding + _ScrollSize) + ScrollY,
			0, 0,
			_GetRenderingDescriptor(_ScrollCornerPopUpId),
			_GenerateUserData(*this, _ScrollCornerPopUpId, _Global),
			true
		);
	}
}

void BFW::GUI::PopUp::ResizeChilds(const ResizePopUpLayerFnc _ResizePopUpLayer, const GetMinFnc _GetMinX, const GetMinFnc _GetMinY, const size_t _ResizeSize, const ForceScrollFnc _ForceHScroll, const ForceScrollFnc _ForceVScroll, const size_t _ScrollSize, const size_t _ScrollTopPadding, const size_t _ScrollPadding, const GetRenderingDescriptorFnc _GetRenderingDescriptor, const GenerateUserDataFnc _GenerateUserData, const ReleaseUserDataFnc _ReleaseUserData, void* _Global)
{
	for (size_t _Index = 0; _Index < Panels.GetSize(); _Index++)
	{
		switch (Panels[_Index].PanelType)
		{
		case _LeftPanelType:
		{
			Panels[_Index].SetHeight(TrueHeight);
			Panels[_Index].SetTrueHeight(_GetMinY(Panels[_Index]));

			break;
		}
		case _RightPanelType:
		{
			Panels[_Index].SetHeight(TrueHeight);
			Panels[_Index].SetTrueHeight(_GetMinY(Panels[_Index]));
			Panels[_Index].SetPositionX(TrueWidth - Panels[_Index].Width);

			break;
		}
		case _TopPanelType:
		{
			Panels[_Index].SetWidth(TrueWidth);
			Panels[_Index].SetTrueWidth(_GetMinX(Panels[_Index]));

			break;
		}
		case _BottomPanelType:
		{
			Panels[_Index].SetWidth(TrueWidth);
			Panels[_Index].SetTrueWidth(_GetMinX(Panels[_Index]));
			Panels[_Index].SetPositionY(TrueHeight - Panels[_Index].Height);

			break;
		}
		default:
		{
			BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Detected a panel with no panel type!"));
			break;
		}
		}

		Panels[_Index].ResizeChilds(_ResizePopUpLayer, _GetMinX, _GetMinY, _ResizeSize, _ForceHScroll, _ForceVScroll, _ScrollSize, _ScrollTopPadding, _ScrollPadding, _GetRenderingDescriptor, _GenerateUserData, _ReleaseUserData, _Global);
	}

	for (size_t _Index = 0; _Index < Nodes.GetSize(); _Index++)
	{
		switch (Nodes[_Index].PanelType)
		{
		case _LeftPanelType:
		{
			if (Panels[0].Width < TrueWidth)
			{
				Nodes[_Index].SetWidth(TrueWidth - Panels[0].Width);
			}
			else
			{
				Nodes[_Index].SetWidth(0);
			}

			Nodes[_Index].SetTrueWidth(_GetMinX(Nodes[_Index]));
			Nodes[_Index].SetHeight(TrueHeight);
			Nodes[_Index].SetTrueHeight(_GetMinY(Nodes[_Index]));

			break;
		}
		case _RightPanelType:
		{
			if (Panels[0].Width < TrueWidth)
			{
				Nodes[_Index].SetWidth(TrueWidth - Panels[0].Width);
			}
			else
			{
				Nodes[_Index].SetWidth(0);
			}

			Nodes[_Index].SetTrueWidth(_GetMinX(Nodes[_Index]));
			Nodes[_Index].SetHeight(TrueHeight);
			Nodes[_Index].SetTrueHeight(_GetMinY(Nodes[_Index]));
			Nodes[_Index].SetPositionX(TrueWidth - Nodes[_Index].Width);

			break;
		}
		case _TopPanelType:
		{
			if (Panels[0].Height < TrueHeight)
			{
				Nodes[_Index].SetHeight(TrueHeight - Panels[0].Height);
			}
			else
			{
				Nodes[_Index].SetHeight(0);
			}

			Nodes[_Index].SetTrueHeight(_GetMinY(Nodes[_Index]));
			Nodes[_Index].SetWidth(TrueWidth);
			Nodes[_Index].SetTrueWidth(_GetMinX(Nodes[_Index]));

			break;
		}
		case _BottomPanelType:
		{
			if (Panels[0].Height < TrueHeight)
			{
				Nodes[_Index].SetHeight(TrueHeight - Panels[0].Height);
			}
			else
			{
				Nodes[_Index].SetHeight(0);
			}

			Nodes[_Index].SetTrueHeight(_GetMinY(Nodes[_Index]));
			Nodes[_Index].SetWidth(TrueWidth);
			Nodes[_Index].SetTrueWidth(_GetMinX(Nodes[_Index]));
			Nodes[_Index].SetPositionY(TrueHeight - Nodes[_Index].Height);

			break;
		}
		default:
		{
			BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Detected a node with no panel type!"));
			break;
		}
		}

		Nodes[_Index].ResizeChilds(_ResizePopUpLayer, _GetMinX, _GetMinY, _ResizeSize, _ForceHScroll, _ForceVScroll, _ScrollSize, _ScrollTopPadding, _ScrollPadding, _GetRenderingDescriptor, _GenerateUserData, _ReleaseUserData, _Global);
	}

	bool _HasHScroll = false, _HasVScroll = false;

	for (size_t _Layer = 0; _Layer < PopUps.GetSize(); _Layer++)
	{
		switch (PopUps[_Layer][0].Id)
		{
		case _LeftResizePopUpId:
		{
			if (PanelType == _NullPanelType)
			{
				PopUps[_Layer][0].SetHeight((Height - 2 * _ResizeSize) * (Height > 2 * _ResizeSize));
				PopUps[_Layer][0].SetPositionX(ScrollX);
				PopUps[_Layer][0].SetPositionY(_ResizeSize + ScrollY);
			}
			else
			{
				PopUps[_Layer][0].SetHeight(Height);
				PopUps[_Layer][0].SetPositionX(ScrollX);
				PopUps[_Layer][0].SetPositionY(ScrollY);
			}

			break;
		}
		case _RightResizePopUpId:
		{
			if (PanelType == _NullPanelType)
			{
				PopUps[_Layer][0].SetHeight((Height - 2 * _ResizeSize) * (Height > 2 * _ResizeSize));
				PopUps[_Layer][0].SetPositionX((Width - _ResizeSize) * (Width > _ResizeSize) + ScrollX);
				PopUps[_Layer][0].SetPositionY(_ResizeSize + ScrollY);
			}
			else
			{
				PopUps[_Layer][0].SetHeight(Height);
				PopUps[_Layer][0].SetPositionX((Width - _ResizeSize) * (Width > _ResizeSize) + ScrollX);
				PopUps[_Layer][0].SetPositionY(ScrollY);
			}

			break;
		}
		case _TopResizePopUpId:
		{
			if (PanelType == _NullPanelType)
			{
				PopUps[_Layer][0].SetWidth((Width - 2 * _ResizeSize) * (Width > 2 * _ResizeSize));
				PopUps[_Layer][0].SetPositionX(_ResizeSize + ScrollX);
				PopUps[_Layer][0].SetPositionY(ScrollY);
			}
			else
			{
				PopUps[_Layer][0].SetWidth(Width);
				PopUps[_Layer][0].SetPositionX(ScrollX);
				PopUps[_Layer][0].SetPositionY(ScrollY);
			}

			break;
		}
		case _BottomResizePopUpId:
		{
			if (PanelType == _NullPanelType)
			{
				PopUps[_Layer][0].SetWidth((Width - 2 * _ResizeSize) * (Width > 2 * _ResizeSize));
				PopUps[_Layer][0].SetPositionX(_ResizeSize + ScrollX);
				PopUps[_Layer][0].SetPositionY((Height - _ResizeSize) * (Height > _ResizeSize) + ScrollY);
			}
			else
			{
				PopUps[_Layer][0].SetWidth(Width);
				PopUps[_Layer][0].SetPositionX(ScrollX);
				PopUps[_Layer][0].SetPositionY((Height - _ResizeSize) * (Height > _ResizeSize) + ScrollY);
			}

			break;
		}
		case _LeftTopResizePopUpId:
		{
			PopUps[_Layer][0].SetPositionX(ScrollX);
			PopUps[_Layer][0].SetPositionY(ScrollY);

			break;
		}
		case _LeftBottomResizePopUpId:
		{
			PopUps[_Layer][0].SetPositionX(ScrollX);
			PopUps[_Layer][0].SetPositionY((Height - _ResizeSize) * (Height > _ResizeSize) + ScrollY);

			break;
		}
		case _RightTopResizePopUpId:
		{
			PopUps[_Layer][0].SetPositionX((Width - _ResizeSize) * (Width > _ResizeSize) + ScrollX);
			PopUps[_Layer][0].SetPositionY(ScrollY);

			break;
		}
		case _RightBottomResizePopUpId:
		{
			PopUps[_Layer][0].SetPositionX((Width - _ResizeSize) * (Width > _ResizeSize) + ScrollX);
			PopUps[_Layer][0].SetPositionY((Height - _ResizeSize) * (Height > _ResizeSize) + ScrollY);

			break;
		}
		case _HScrollWindowPopUpId:
		{
			_HasHScroll = true;

			if (Width < TrueWidth)
			{
				PopUps[_Layer][0].SetWidth((Width - (_ScrollPadding * 2 + _ScrollSize)) * (Width > _ScrollPadding * 2 + _ScrollSize));
				PopUps[_Layer][0].SetPositionX(_ScrollPadding + ScrollX);
				PopUps[_Layer][0].SetPositionY(Height - (_ScrollPadding + _ScrollSize) + ScrollY);

				PopUps[_Layer][0].PopUps[0][0].SetWidth(PopUps[_Layer][0].Width * Width / TrueWidth);
				PopUps[_Layer][0].PopUps[0][0].SetPositionX(ScrollX * (PopUps[_Layer][0].Width - PopUps[_Layer][0].Width * Width / TrueWidth) / (TrueWidth - Width));
			}
			else if (_ForceHScroll(Id))
			{
				PopUps[_Layer][0].SetWidth((Width - (_ScrollPadding * 2 + _ScrollSize)) * (Width > _ScrollPadding * 2 + _ScrollSize));
				PopUps[_Layer][0].SetPositionX(_ScrollPadding + ScrollX);
				PopUps[_Layer][0].SetPositionY(Height - (_ScrollPadding + _ScrollSize) + ScrollY);

				PopUps[_Layer][0].PopUps[0][0].SetWidth(PopUps[_Layer][0].Width);
				PopUps[_Layer][0].PopUps[0][0].SetPositionX(0);
			}
			else
			{
				_ReleaseUserData(PopUps[_Layer][0].PopUps[0][0], _Global);
				_ReleaseUserData(PopUps[_Layer][0], _Global);
				PopUps.Erase(_Layer);
				_Layer--;
			}

			break;
		}
		case _VScrollWindowPopUpId:
		{
			_HasVScroll = true;

			if (Height < TrueHeight)
			{
				PopUps[_Layer][0].SetHeight((Height - (_ScrollTopPadding + _ScrollPadding + _ScrollSize)) * (Height > _ScrollTopPadding + _ScrollPadding + _ScrollSize));
				PopUps[_Layer][0].SetPositionX(Width - (_ScrollPadding + _ScrollSize) + ScrollX);
				PopUps[_Layer][0].SetPositionY(_ScrollTopPadding + ScrollY);

				PopUps[_Layer][0].PopUps[0][0].SetHeight(PopUps[_Layer][0].Height * Height / TrueHeight);
				PopUps[_Layer][0].PopUps[0][0].SetPositionY(ScrollY * (PopUps[_Layer][0].Height - PopUps[_Layer][0].Height * Height / TrueHeight) / (TrueHeight - Height));
			}
			else if (_ForceVScroll(Id))
			{
				PopUps[_Layer][0].SetHeight((Height - (_ScrollTopPadding + _ScrollPadding + _ScrollSize)) * (Height > _ScrollTopPadding + _ScrollPadding + _ScrollSize));
				PopUps[_Layer][0].SetPositionX(Width - (_ScrollPadding + _ScrollSize) + ScrollX);
				PopUps[_Layer][0].SetPositionY(_ScrollTopPadding + ScrollY);

				PopUps[_Layer][0].PopUps[0][0].SetHeight(PopUps[_Layer][0].Height);
				PopUps[_Layer][0].PopUps[0][0].SetPositionY(0);
			}
			else
			{
				_ReleaseUserData(PopUps[_Layer][0].PopUps[0][0], _Global);
				_ReleaseUserData(PopUps[_Layer][0], _Global);
				PopUps.Erase(_Layer);
				_Layer--;
			}

			break;
		}
		case _ScrollCornerPopUpId:
		{
			if (Width < TrueWidth || Height < TrueHeight)
			{
				PopUps[_Layer][0].SetPositionX(Width - (_ScrollPadding + _ScrollSize) + ScrollX);
				PopUps[_Layer][0].SetPositionY(Height - (_ScrollPadding + _ScrollSize) + ScrollY);
			}
			else if (_ForceHScroll(Id) || _ForceVScroll(Id))
			{
				PopUps[_Layer][0].SetPositionX(Width - (_ScrollPadding + _ScrollSize) + ScrollX);
				PopUps[_Layer][0].SetPositionY(Height - (_ScrollPadding + _ScrollSize) + ScrollY);
			}
			else
			{
				_ReleaseUserData(PopUps[_Layer][0], _Global);
				PopUps.Erase(_Layer);
				_Layer--;
			}

			break;
		}
		default:
		{
			_ResizePopUpLayer(*this, _Layer, _GetMinX, _GetMinY, _ResizeSize, _ForceHScroll, _ForceVScroll, _ScrollSize, _ScrollTopPadding, _ScrollPadding, _GetRenderingDescriptor, _GenerateUserData, _ReleaseUserData, _Global);

			break;
		}
		}
	}

	GenerateScrollBars(_HasHScroll, _HasVScroll, _ForceHScroll(Id), _ForceVScroll(Id), _ScrollSize, _ScrollTopPadding, _ScrollPadding, _GetRenderingDescriptor, _GenerateUserData, _Global);
	MoveControlsOnTop();
}

void BFW::GUI::PopUp::SetForegroundLayer(const size_t _Layer)
{
	size_t _OldFocusedPopUps = (size_t&&)(FocusedPopUps[_Layer]);
	Vector<PopUp> _OldPopUps = (Vector<PopUp>&&)(PopUps[_Layer]);

	FocusedPopUps.EmplaceBack((size_t&&)(_OldFocusedPopUps));
	PopUps.EmplaceBack((Vector<PopUp>&&)(_OldPopUps));

	FocusedPopUps.Erase(_Layer);
	PopUps.Erase(_Layer);

	MoveControlsOnTop();
}

void BFW::GUI::PopUp::MoveControlsOnTop()
{
	size_t _HScrollWindowIndex = 0;

	if (FindFocusedPopUpLayer(_HScrollWindowIndex, _HScrollWindowPopUpId))
	{
		size_t _OldFocusedPopUps = (size_t&&)(FocusedPopUps[_HScrollWindowIndex]);
		Vector<PopUp> _OldPopUps = (Vector<PopUp>&&)(PopUps[_HScrollWindowIndex]);

		FocusedPopUps.EmplaceBack((size_t&&)(_OldFocusedPopUps));
		PopUps.EmplaceBack((Vector<PopUp>&&)(_OldPopUps));

		FocusedPopUps.Erase(_HScrollWindowIndex);
		PopUps.Erase(_HScrollWindowIndex);
	}

	size_t _VScrollWindowIndex = 0;

	if (FindFocusedPopUpLayer(_VScrollWindowIndex, _VScrollWindowPopUpId))
	{
		size_t _OldFocusedPopUps = (size_t&&)(FocusedPopUps[_VScrollWindowIndex]);
		Vector<PopUp> _OldPopUps = (Vector<PopUp>&&)(PopUps[_VScrollWindowIndex]);

		FocusedPopUps.EmplaceBack((size_t&&)(_OldFocusedPopUps));
		PopUps.EmplaceBack((Vector<PopUp>&&)(_OldPopUps));

		FocusedPopUps.Erase(_VScrollWindowIndex);
		PopUps.Erase(_VScrollWindowIndex);
	}

	size_t _ScrollCornerIndex = 0;

	if (FindFocusedPopUpLayer(_ScrollCornerIndex, _ScrollCornerPopUpId))
	{
		size_t _OldFocusedPopUps = (size_t&&)(FocusedPopUps[_ScrollCornerIndex]);
		Vector<PopUp> _OldPopUps = (Vector<PopUp>&&)(PopUps[_ScrollCornerIndex]);

		FocusedPopUps.EmplaceBack((size_t&&)(_OldFocusedPopUps));
		PopUps.EmplaceBack((Vector<PopUp>&&)(_OldPopUps));

		FocusedPopUps.Erase(_ScrollCornerIndex);
		PopUps.Erase(_ScrollCornerIndex);
	}

	size_t _LeftResizeIndex = 0;

	if (FindFocusedPopUpLayer(_LeftResizeIndex, _LeftResizePopUpId))
	{
		size_t _OldFocusedPopUps = (size_t&&)(FocusedPopUps[_LeftResizeIndex]);
		Vector<PopUp> _OldPopUps = (Vector<PopUp>&&)(PopUps[_LeftResizeIndex]);

		FocusedPopUps.EmplaceBack((size_t&&)(_OldFocusedPopUps));
		PopUps.EmplaceBack((Vector<PopUp>&&)(_OldPopUps));

		FocusedPopUps.Erase(_LeftResizeIndex);
		PopUps.Erase(_LeftResizeIndex);
	}

	size_t _RightResizeIndex = 0;

	if (FindFocusedPopUpLayer(_RightResizeIndex, _RightResizePopUpId))
	{
		size_t _OldFocusedPopUps = (size_t&&)(FocusedPopUps[_RightResizeIndex]);
		Vector<PopUp> _OldPopUps = (Vector<PopUp>&&)(PopUps[_RightResizeIndex]);

		FocusedPopUps.EmplaceBack((size_t&&)(_OldFocusedPopUps));
		PopUps.EmplaceBack((Vector<PopUp>&&)(_OldPopUps));

		FocusedPopUps.Erase(_RightResizeIndex);
		PopUps.Erase(_RightResizeIndex);
	}

	size_t _TopResizeIndex = 0;

	if (FindFocusedPopUpLayer(_TopResizeIndex, _TopResizePopUpId))
	{
		size_t _OldFocusedPopUps = (size_t&&)(FocusedPopUps[_TopResizeIndex]);
		Vector<PopUp> _OldPopUps = (Vector<PopUp>&&)(PopUps[_TopResizeIndex]);

		FocusedPopUps.EmplaceBack((size_t&&)(_OldFocusedPopUps));
		PopUps.EmplaceBack((Vector<PopUp>&&)(_OldPopUps));

		FocusedPopUps.Erase(_TopResizeIndex);
		PopUps.Erase(_TopResizeIndex);
	}

	size_t _BottomResizeIndex = 0;

	if (FindFocusedPopUpLayer(_BottomResizeIndex, _BottomResizePopUpId))
	{
		size_t _OldFocusedPopUps = (size_t&&)(FocusedPopUps[_BottomResizeIndex]);
		Vector<PopUp> _OldPopUps = (Vector<PopUp>&&)(PopUps[_BottomResizeIndex]);

		FocusedPopUps.EmplaceBack((size_t&&)(_OldFocusedPopUps));
		PopUps.EmplaceBack((Vector<PopUp>&&)(_OldPopUps));

		FocusedPopUps.Erase(_BottomResizeIndex);
		PopUps.Erase(_BottomResizeIndex);
	}

	size_t _LeftTopResizeIndex = 0;

	if (FindFocusedPopUpLayer(_LeftTopResizeIndex, _LeftTopResizePopUpId))
	{
		size_t _OldFocusedPopUps = (size_t&&)(FocusedPopUps[_LeftTopResizeIndex]);
		Vector<PopUp> _OldPopUps = (Vector<PopUp>&&)(PopUps[_LeftTopResizeIndex]);

		FocusedPopUps.EmplaceBack((size_t&&)(_OldFocusedPopUps));
		PopUps.EmplaceBack((Vector<PopUp>&&)(_OldPopUps));

		FocusedPopUps.Erase(_LeftTopResizeIndex);
		PopUps.Erase(_LeftTopResizeIndex);
	}

	size_t _LeftBottomResizeIndex = 0;

	if (FindFocusedPopUpLayer(_LeftBottomResizeIndex, _LeftBottomResizePopUpId))
	{
		size_t _OldFocusedPopUps = (size_t&&)(FocusedPopUps[_LeftBottomResizeIndex]);
		Vector<PopUp> _OldPopUps = (Vector<PopUp>&&)(PopUps[_LeftBottomResizeIndex]);

		FocusedPopUps.EmplaceBack((size_t&&)(_OldFocusedPopUps));
		PopUps.EmplaceBack((Vector<PopUp>&&)(_OldPopUps));

		FocusedPopUps.Erase(_LeftBottomResizeIndex);
		PopUps.Erase(_LeftBottomResizeIndex);
	}

	size_t _RightTopResizeIndex = 0;

	if (FindFocusedPopUpLayer(_RightTopResizeIndex, _RightTopResizePopUpId))
	{
		size_t _OldFocusedPopUps = (size_t&&)(FocusedPopUps[_RightTopResizeIndex]);
		Vector<PopUp> _OldPopUps = (Vector<PopUp>&&)(PopUps[_RightTopResizeIndex]);

		FocusedPopUps.EmplaceBack((size_t&&)(_OldFocusedPopUps));
		PopUps.EmplaceBack((Vector<PopUp>&&)(_OldPopUps));

		FocusedPopUps.Erase(_RightTopResizeIndex);
		PopUps.Erase(_RightTopResizeIndex);
	}

	size_t _RightBottomResizeIndex = 0;

	if (FindFocusedPopUpLayer(_RightBottomResizeIndex, _RightBottomResizePopUpId))
	{
		size_t _OldFocusedPopUps = (size_t&&)(FocusedPopUps[_RightBottomResizeIndex]);
		Vector<PopUp> _OldPopUps = (Vector<PopUp>&&)(PopUps[_RightBottomResizeIndex]);

		FocusedPopUps.EmplaceBack((size_t&&)(_OldFocusedPopUps));
		PopUps.EmplaceBack((Vector<PopUp>&&)(_OldPopUps));

		FocusedPopUps.Erase(_RightBottomResizeIndex);
		PopUps.Erase(_RightBottomResizeIndex);
	}
}

void BFW::GUI::PopUp::SetFocusedPanel(const size_t _FocusedPanel)
{
	FocusedPanel = _FocusedPanel;
}

void BFW::GUI::PopUp::SetFocusedNode(const size_t _FocusedNode)
{
	FocusedNode = _FocusedNode;
}

void BFW::GUI::PopUp::SetId(const uint64_t _Id)
{
	Id = _Id;
}

void BFW::GUI::PopUp::SetPanelType(const uint8_t _PanelType)
{
	PanelType = _PanelType;
}

void BFW::GUI::PopUp::SetTrueWidth(const size_t _MinWidth)
{
	if (_MinWidth > Width)
	{
		TrueWidth = _MinWidth;
	}
	else
	{
		TrueWidth = Width;
	}

	SetScrollX(ScrollX);
}

void BFW::GUI::PopUp::SetTrueHeight(const size_t _MinHeight)
{
	if (_MinHeight > Height)
	{
		TrueHeight = _MinHeight;
	}
	else
	{
		TrueHeight = Height;
	}

	SetScrollY(ScrollY);
}

void BFW::GUI::PopUp::SetWidth(const size_t _Width)
{
	Width = _Width;

	if (TrueWidth < Width)
	{
		TrueWidth = Width;
	}

	SetScrollX(ScrollX);
}

void BFW::GUI::PopUp::SetHeight(const size_t _Height)
{
	Height = _Height;

	if (TrueHeight < Height)
	{
		TrueHeight = Height;
	}

	SetScrollY(ScrollY);
}

void BFW::GUI::PopUp::SetPositionX(const intptr_t _PositionX)
{
	PositionX = _PositionX;
}

void BFW::GUI::PopUp::SetPositionY(const intptr_t _PositionY)
{
	PositionY = _PositionY;
}

void BFW::GUI::PopUp::SetScrollX(const size_t _ScrollX)
{
	if (_ScrollX < TrueWidth - Width)
	{
		ScrollX = _ScrollX;
	}
	else
	{
		ScrollX = TrueWidth - Width;
	}
}

void BFW::GUI::PopUp::SetScrollY(const size_t _ScrollY)
{
	if (_ScrollY < TrueHeight - Height)
	{
		ScrollY = _ScrollY;
	}
	else
	{
		ScrollY = TrueHeight - Height;
	}
}

void BFW::GUI::PopUp::SetUserData(void* _UserData)
{
	UserData = _UserData;
}

void BFW::GUI::PopUp::SetRenderFunctions(const RenderingDescriptor& _RenderFunctions)
{
	RenderFunctions = _RenderFunctions;
}

void BFW::GUI::PopUp::SetSetupData(const SetupRenderDataFnc _SetupData)
{
	RenderFunctions.SetupData = _SetupData;
}

void BFW::GUI::PopUp::SetCleanUpData(const CleanUpRenderDataFnc _CleanUpData)
{
	RenderFunctions.CleanUpData = _CleanUpData;
}

void BFW::GUI::PopUp::SetRenderBottom(const RenderFnc _RenderBottom)
{
	RenderFunctions.RenderBottom = _RenderBottom;
}

void BFW::GUI::PopUp::SetRenderMiddle(const RenderFnc _RenderMiddle)
{
	RenderFunctions.RenderMiddle = _RenderMiddle;
}

void BFW::GUI::PopUp::SetRenderTop(const RenderFnc _RenderTop)
{
	RenderFunctions.RenderTop = _RenderTop;
}

void BFW::GUI::PopUp::SetComposit(const CompositFnc _Composit)
{
	RenderFunctions.Composit = _Composit;
}

BFW::GUI::SafePopUpPointer BFW::GUI::PopUp::GetChildFromMouse(const intptr_t _MouseX, const intptr_t _MouseY, Vector<SafePopUpPointer>* _Path)
{
	if (_MouseX < 0 || (size_t)(_MouseX) >= Width || _MouseY < 0 || (size_t)(_MouseY) >= Height)
	{
		return SafePopUpPointer(nullptr);
	}

	for (size_t _Index = 0; _Index < PopUps.GetSize(); _Index++)
	{
		PopUp& _PopUp = PopUps[PopUps.GetSize() - 1 - _Index][FocusedPopUps[PopUps.GetSize() - 1 - _Index]];

		SafePopUpPointer _Result = _PopUp.GetChildFromMouse(_MouseX + ScrollX - _PopUp.PositionX, _MouseY + ScrollY - _PopUp.PositionY, _Path);

		if (_Result != nullptr)
		{
			if (_Path)
			{
				_Path->EmplaceBack(SafePopUpPointer(this));
			}

			return _Result;
		}
	}

	if (Nodes.GetSize() != 0)
	{
		PopUp& _Node = Nodes[FocusedNode];

		SafePopUpPointer _Result = _Node.GetChildFromMouse(_MouseX + ScrollX - _Node.PositionX, _MouseY + ScrollY - _Node.PositionY, _Path);

		if (_Result != nullptr)
		{
			if (_Path)
			{
				_Path->EmplaceBack(SafePopUpPointer(this));
			}

			return _Result;
		}
	}

	if (Panels.GetSize() != 0)
	{
		PopUp& _Panel = Panels[FocusedPanel];

		SafePopUpPointer _Result = _Panel.GetChildFromMouse(_MouseX + ScrollX - _Panel.PositionX, _MouseY + ScrollY - _Panel.PositionY, _Path);

		if (_Result != nullptr)
		{
			if (_Path)
			{
				_Path->EmplaceBack(SafePopUpPointer(this));
			}

			return _Result;
		}
	}

	if (_Path)
	{
		_Path->EmplaceBack(SafePopUpPointer(this));
	}

	return SafePopUpPointer(this);
}

const BFW::GUI::SafePopUpPointer BFW::GUI::PopUp::GetChildFromMouse(const intptr_t _MouseX, const intptr_t _MouseY, Vector<const SafePopUpPointer>* _Path) const
{
	if (_MouseX < 0 || (size_t)(_MouseX) >= Width || _MouseY < 0 || (size_t)(_MouseY) >= Height)
	{
		return SafePopUpPointer(nullptr);
	}

	for (size_t _Index = 0; _Index < PopUps.GetSize(); _Index++)
	{
		const PopUp& _PopUp = PopUps[PopUps.GetSize() - 1 - _Index][FocusedPopUps[PopUps.GetSize() - 1 - _Index]];

		const SafePopUpPointer _Result = _PopUp.GetChildFromMouse(_MouseX + ScrollX - _PopUp.PositionX, _MouseY + ScrollY - _PopUp.PositionY, _Path);

		if (_Result != nullptr)
		{
			if (_Path)
			{
				_Path->EmplaceBack(SafePopUpPointer((PopUp*)(this)));
			}

			return _Result;
		}
	}

	if (Nodes.GetSize() != 0)
	{
		const PopUp& _Node = Nodes[FocusedNode];

		const SafePopUpPointer _Result = _Node.GetChildFromMouse(_MouseX + ScrollX - _Node.PositionX, _MouseY + ScrollY - _Node.PositionY, _Path);

		if (_Result != nullptr)
		{
			if (_Path)
			{
				_Path->EmplaceBack(SafePopUpPointer((PopUp*)(this)));
			}

			return _Result;
		}
	}

	if (Panels.GetSize() != 0)
	{
		const PopUp& _Panel = Panels[FocusedPanel];

		const SafePopUpPointer _Result = _Panel.GetChildFromMouse(_MouseX + ScrollX - _Panel.PositionX, _MouseY + ScrollY - _Panel.PositionY, _Path);

		if (_Result != nullptr)
		{
			if (_Path)
			{
				_Path->EmplaceBack(SafePopUpPointer((PopUp*)(this)));
			}

			return _Result;
		}
	}

	if (_Path)
	{
		_Path->EmplaceBack(SafePopUpPointer((PopUp*)(this)));
	}

	return SafePopUpPointer((PopUp*)(this));
}

const bool BFW::GUI::PopUp::FindFocusedPopUpLayer(size_t& _Layer, const PopUp& _PopUp) const
{
	_Layer = 0;

	while (_Layer < PopUps.GetSize())
	{
		if (&PopUps[_Layer][FocusedPopUps[_Layer]] == &_PopUp)
		{
			return true;
		}

		_Layer++;
	}

	_Layer = 0;

	return false;
}

const bool BFW::GUI::PopUp::FindFocusedPopUpLayer(size_t& _Layer, const uint64_t _PopUpId) const
{
	_Layer = 0;

	while (_Layer < PopUps.GetSize())
	{
		if (PopUps[_Layer][FocusedPopUps[_Layer]].Id == _PopUpId)
		{
			return true;
		}

		_Layer++;
	}

	_Layer = 0;

	return false;
}

const size_t BFW::GUI::PopUp::GetFocusedPanel() const
{
	return FocusedPanel;
}

BFW::Vector<BFW::GUI::PopUp>& BFW::GUI::PopUp::GetPanels()
{
	return Panels;
}

const BFW::Vector<BFW::GUI::PopUp>& BFW::GUI::PopUp::GetPanels() const
{
	return Panels;
}

const size_t BFW::GUI::PopUp::GetFocusedNode() const
{
	return FocusedNode;
}

BFW::Vector<BFW::GUI::PopUp>& BFW::GUI::PopUp::GetNodes()
{
	return Nodes;
}

const BFW::Vector<BFW::GUI::PopUp>& BFW::GUI::PopUp::GetNodes() const
{
	return Nodes;
}

BFW::Vector<size_t>& BFW::GUI::PopUp::GetFocusedPopUps()
{
	return FocusedPopUps;
}

const BFW::Vector<size_t>& BFW::GUI::PopUp::GetFocusedPopUps() const
{
	return FocusedPopUps;
}

BFW::Vector<BFW::Vector<BFW::GUI::PopUp>>& BFW::GUI::PopUp::GetPopUps()
{
	return PopUps;
}

const BFW::Vector<BFW::Vector<BFW::GUI::PopUp>>& BFW::GUI::PopUp::GetPopUps() const
{
	return PopUps;
}

const uint64_t BFW::GUI::PopUp::GetId() const
{
	return Id;
}

const uint8_t BFW::GUI::PopUp::GetPanelType() const
{
	return PanelType;
}

const size_t BFW::GUI::PopUp::GetTrueWidth() const
{
	return TrueWidth;
}

const size_t BFW::GUI::PopUp::GetTrueHeight() const
{
	return TrueHeight;
}

const size_t BFW::GUI::PopUp::GetWidth() const
{
	return Width;
}

const size_t BFW::GUI::PopUp::GetHeight() const
{
	return Height;
}

const intptr_t BFW::GUI::PopUp::GetPositionX() const
{
	return PositionX;
}

const intptr_t BFW::GUI::PopUp::GetPositionY() const
{
	return PositionY;
}

const size_t BFW::GUI::PopUp::GetScrollX() const
{
	return ScrollX;
}

const size_t BFW::GUI::PopUp::GetScrollY() const
{
	return ScrollY;
}

void* BFW::GUI::PopUp::GetUserData()
{
	return UserData;
}

const void* BFW::GUI::PopUp::GetUserData() const
{
	return UserData;
}

const BFW::GUI::RenderingDescriptor& BFW::GUI::PopUp::GetRenderFunctions()
{
	return RenderFunctions;
}

const BFW::GUI::SetupRenderDataFnc BFW::GUI::PopUp::GetSetupData() const
{
	return RenderFunctions.SetupData;
}

const BFW::GUI::CleanUpRenderDataFnc BFW::GUI::PopUp::GetCleanUpData() const
{
	return RenderFunctions.CleanUpData;
}

const BFW::GUI::RenderFnc BFW::GUI::PopUp::GetRenderBottom() const
{
	return RenderFunctions.RenderBottom;
}

const BFW::GUI::RenderFnc BFW::GUI::PopUp::GetRenderMiddle() const
{
	return RenderFunctions.RenderMiddle;
}

const BFW::GUI::RenderFnc BFW::GUI::PopUp::GetRenderTop() const
{
	return RenderFunctions.RenderTop;
}

const BFW::GUI::CompositFnc BFW::GUI::PopUp::GetComposit() const
{
	return RenderFunctions.Composit;
}

BFW::GUI::PopUp& BFW::GUI::PopUp::operator= (const PopUp& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	FocusedPanel = _Other.FocusedPanel;
	Panels = _Other.Panels;
	FocusedNode = _Other.FocusedNode;
	Nodes = _Other.Nodes;
	FocusedPopUps = _Other.FocusedPopUps;
	PopUps = _Other.PopUps;
	Id = _Other.Id;
	PanelType = _Other.PanelType;
	TrueWidth = _Other.TrueWidth;
	TrueHeight = _Other.TrueHeight;
	Width = _Other.Width;
	Height = _Other.Height;
	PositionX = _Other.PositionX;
	PositionY = _Other.PositionY;
	ScrollX = _Other.ScrollX;
	ScrollY = _Other.ScrollY;
	UserData = nullptr;
	RenderFunctions = _Other.RenderFunctions;

	return *this;
}

BFW::GUI::PopUp& BFW::GUI::PopUp::operator= (PopUp&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	FocusedPanel = _Other.FocusedPanel;
	Panels = (Vector<PopUp>&&)(_Other.Panels);
	FocusedNode = _Other.FocusedNode;
	Nodes = (Vector<PopUp>&&)(_Other.Nodes);
	FocusedPopUps = (Vector<size_t>&&)(_Other.FocusedPopUps);
	PopUps = (Vector<Vector<PopUp>>&&)(_Other.PopUps);
	SafePointers = (Vector<SafePopUpPointer*>&&)(_Other.SafePointers);
	Id = _Other.Id;
	PanelType = _Other.PanelType;
	TrueWidth = _Other.TrueWidth;
	TrueHeight = _Other.TrueHeight;
	Width = _Other.Width;
	Height = _Other.Height;
	PositionX = _Other.PositionX;
	PositionY = _Other.PositionY;
	ScrollX = _Other.ScrollX;
	ScrollY = _Other.ScrollY;
	UserData = _Other.UserData;
	RenderFunctions = (RenderingDescriptor&&)(_Other.RenderFunctions);

	for (size_t _Index = 0; _Index < SafePointers.GetSize(); _Index++)
	{
		SafePointers[_Index]->Pointer = this;
	}

	_Other.FocusedPanel = 0;
	_Other.FocusedNode = 0;
	_Other.Id = _NodeWindowPopUpId;
	_Other.PanelType = _NullPanelType;
	_Other.TrueWidth = 0;
	_Other.TrueHeight = 0;
	_Other.Width = 0;
	_Other.Height = 0;
	_Other.PositionX = 0;
	_Other.PositionY = 0;
	_Other.ScrollX = 0;
	_Other.ScrollY = 0;
	_Other.UserData = nullptr;

	return *this;
}

void BFW::GUI::PopUp::GlobalToLocal(intptr_t& _PositionX, intptr_t& _PositionY, const Vector<SafePopUpPointer>& _Path)
{
	for (size_t _Index = 1; _Index < _Path.GetSize(); _Index++)
	{
		_PositionX += _Path[_Path.GetSize() - 1 - _Index]->ScrollX - _Path[_Path.GetSize() - 1 - _Index]->PositionX;
		_PositionY += _Path[_Path.GetSize() - 1 - _Index]->ScrollY - _Path[_Path.GetSize() - 1 - _Index]->PositionY;
	}
}

void BFW::GUI::PopUp::GlobalToLocal(intptr_t& _PositionX, intptr_t& _PositionY, const Vector<const SafePopUpPointer>& _Path)
{
	for (size_t _Index = 1; _Index < _Path.GetSize(); _Index++)
	{
		_PositionX += _Path[_Path.GetSize() - 1 - _Index]->ScrollX - _Path[_Path.GetSize() - 1 - _Index]->PositionX;
		_PositionY += _Path[_Path.GetSize() - 1 - _Index]->ScrollY - _Path[_Path.GetSize() - 1 - _Index]->PositionY;
	}
}

void BFW::GUI::PopUp::LocalToGlobal(intptr_t& _PositionX, intptr_t& _PositionY, const Vector<SafePopUpPointer>& _Path)
{
	for (size_t _Index = 0; _Index < _Path.GetSize() - 1; _Index++)
	{
		_PositionX -= _Path[_Index]->ScrollX - _Path[_Index]->PositionX;
		_PositionY -= _Path[_Index]->ScrollY - _Path[_Index]->PositionY;
	}
}

void BFW::GUI::PopUp::LocalToGlobal(intptr_t& _PositionX, intptr_t& _PositionY, const Vector<const SafePopUpPointer>& _Path)
{
	for (size_t _Index = 0; _Index < _Path.GetSize() - 1; _Index++)
	{
		_PositionX -= _Path[_Index]->ScrollX - _Path[_Index]->PositionX;
		_PositionY -= _Path[_Index]->ScrollY - _Path[_Index]->PositionY;
	}
}

const bool BFW::GUI::PopUp::IsValidPath(const Vector<SafePopUpPointer>& _Path)
{
	for (size_t _Index = 0; _Index < _Path.GetSize(); _Index++)
	{
		if (!_Path[_Index])
		{
			return false;
		}
	}

	if (!_Path.GetSize())
	{
		return true;
	}

	for (size_t _Index = 0; _Index < _Path.GetSize() - 1; _Index++)
	{
		bool _Found = false;

		for (size_t _Layer = 0; _Layer < _Path[_Index + 1]->PopUps.GetSize(); _Layer++)
		{
			if (_Path[_Index] == &_Path[_Index + 1]->PopUps[_Layer][_Path[_Index + 1]->FocusedPopUps[_Layer]])
			{
				_Found = true;
				break;
			}
		}

		if (_Found)
		{
			continue;
		}

		if (_Path[_Index] == &_Path[_Index + 1]->Nodes[_Path[_Index + 1]->FocusedNode])
		{
			continue;
		}

		if (_Path[_Index] == &_Path[_Index + 1]->Panels[_Path[_Index + 1]->FocusedPanel])
		{
			continue;
		}

		return false;
	}

	return true;
}

const bool BFW::GUI::PopUp::IsValidPath(const Vector<const SafePopUpPointer>& _Path)
{
	for (size_t _Index = 0; _Index < _Path.GetSize(); _Index++)
	{
		if (!_Path[_Index])
		{
			return false;
		}
	}

	if (!_Path.GetSize())
	{
		return true;
	}

	for (size_t _Index = 0; _Index < _Path.GetSize() - 1; _Index++)
	{
		bool _Found = false;

		for (size_t _Layer = 0; _Layer < _Path[_Index + 1]->PopUps.GetSize(); _Layer++)
		{
			if (_Path[_Index] == &_Path[_Index + 1]->PopUps[_Layer][_Path[_Index + 1]->FocusedPopUps[_Layer]])
			{
				_Found = true;
				break;
			}
		}

		if (_Found)
		{
			continue;
		}

		if (_Path[_Index] == &_Path[_Index + 1]->Nodes[_Path[_Index + 1]->FocusedNode])
		{
			continue;
		}

		if (_Path[_Index] == &_Path[_Index + 1]->Panels[_Path[_Index + 1]->FocusedPanel])
		{
			continue;
		}

		return false;
	}

	return true;
}

const bool BFW::GUI::PopUp::FindMovableWindow(const IsMovableFnc _IsMovable, size_t& _Index, const Vector<SafePopUpPointer>& _Path)
{
	_Index = 0;

	if (!IsValidPath(_Path))
	{
		return false;
	}

	while (_Index < _Path.GetSize())
	{
		if ((_IsMovable(_Path[_Index]->Id) || _Path[_Index]->Id == _NodeWindowPopUpId) && _Index + 1 < _Path.GetSize())
		{
			for (size_t _Layer = 0; _Layer < _Path[_Index + 1]->PopUps.GetSize(); _Layer++)
			{
				if (&_Path[_Index + 1]->PopUps[_Layer][_Path[_Index + 1]->FocusedPopUps[_Layer]] == _Path[_Index])
				{
					return true;
				}
			}
		}

		_Index++;
	}

	_Index = 0;

	return false;
}

const bool BFW::GUI::PopUp::FindMovableWindow(const IsMovableFnc _IsMovable, size_t& _Index, const Vector<const SafePopUpPointer>& _Path)
{
	_Index = 0;

	if (!IsValidPath(_Path))
	{
		return false;
	}

	while (_Index < _Path.GetSize())
	{
		if ((_IsMovable(_Path[_Index]->Id) || _Path[_Index]->Id == _NodeWindowPopUpId) && _Index + 1 < _Path.GetSize())
		{
			for (size_t _Layer = 0; _Layer < _Path[_Index + 1]->PopUps.GetSize(); _Layer++)
			{
				if (&_Path[_Index + 1]->PopUps[_Layer][_Path[_Index + 1]->FocusedPopUps[_Layer]] == _Path[_Index])
				{
					return true;
				}
			}
		}

		_Index++;
	}

	_Index = 0;

	return false;
}

const bool BFW::GUI::PopUp::FindScrollableWindow(const IsScrollableFnc _IsScrollable, size_t& _Index, const Vector<SafePopUpPointer>& _Path)
{
	_Index = 0;

	if (!IsValidPath(_Path))
	{
		return false;
	}

	while (_Index < _Path.GetSize())
	{
		size_t _Layer = 0;

		if (_IsScrollable(_Path[_Index]->Id) && _Path[_Index]->FindFocusedPopUpLayer(_Layer, _ScrollCornerPopUpId))
		{
			return true;
		}

		_Index++;
	}

	_Index = 0;

	return false;
}

const bool BFW::GUI::PopUp::FindScrollableWindow(const IsScrollableFnc _IsScrollable, size_t& _Index, const Vector<const SafePopUpPointer>& _Path)
{
	_Index = 0;

	if (!IsValidPath(_Path))
	{
		return false;
	}

	while (_Index < _Path.GetSize())
	{
		size_t _Layer = 0;

		if (_IsScrollable(_Path[_Index]->Id) && _Path[_Index]->FindFocusedPopUpLayer(_Layer, _ScrollCornerPopUpId))
		{
			return true;
		}

		_Index++;
	}

	_Index = 0;

	return false;
}
