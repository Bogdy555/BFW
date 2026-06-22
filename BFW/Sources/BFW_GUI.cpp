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

BFW::GUI::Window::Window(Window&& _Other) noexcept : Handle(_Other.Handle), WndThread(_Other.WndThread), UserData(_Other.UserData), FullScreen(_Other.FullScreen), WndRect(_Other.WndRect), WndPlace(_Other.WndPlace), WindowMutex(_Other.WindowMutex), Cursor(_Other.Cursor), Close(_Other.Close), Focus(_Other.Focus), RawKeys(), Keys(), Tracking(_Other.Tracking), HasMouse(_Other.HasMouse), MouseX(_Other.MouseX), MouseY(_Other.MouseY), KeyEvents((Vector<uint8_t>&&)(_Other.KeyEvents)), LClicks((Vector<Input::ClickEvent>&&)(_Other.LClicks)), RClicks((Vector<Input::ClickEvent>&&)(_Other.RClicks)), MClicks((Vector<Input::ClickEvent>&&)(_Other.MClicks)), X1Clicks((Vector<Input::ClickEvent>&&)(_Other.X1Clicks)), X2Clicks((Vector<Input::ClickEvent>&&)(_Other.X2Clicks)), LDblClicks((Vector<Input::ClickEvent>&&)(_Other.LDblClicks)), RDblClicks((Vector<Input::ClickEvent>&&)(_Other.RDblClicks)), MDblClicks((Vector<Input::ClickEvent>&&)(_Other.MDblClicks)), X1DblClicks((Vector<Input::ClickEvent>&&)(_Other.X1DblClicks)), X2DblClicks((Vector<Input::ClickEvent>&&)(_Other.X2DblClicks)), WheelEvents((Vector<Input::WheelEvent>&&)(_Other.WheelEvents)), HWheelEvents((Vector<Input::WheelEvent>&&)(_Other.HWheelEvents)), CharEvents((Vector<BFW_CHAR_TYPE>&&)(_Other.CharEvents))
{
	for (size_t _Index = 0; _Index < 256; _Index++)
	{
		RawKeys[_Index] = _Other.RawKeys[_Index];
	}
	for (size_t _Index = 0; _Index < 256; _Index++)
	{
		Keys[_Index] = (Input::Key&&)(_Other.Keys[_Index]);
	}

	_Other.Handle = NULL;
	_Other.WndThread = nullptr;
	_Other.UserData = nullptr;
	_Other.FullScreen = false;
	_Other.WndRect = { 0 };
	_Other.WndPlace = { 0 };
	_Other.WindowMutex = nullptr;
	_Other.Cursor = LoadCursor(NULL, IDC_ARROW);
	_Other.Close = false;
	_Other.Focus = false;
	for (size_t _Index = 0; _Index < 256; _Index++)
	{
		_Other.RawKeys[_Index] = false;
	}
	_Other.Tracking = false;
	_Other.HasMouse = false;
	_Other.MouseX = 0;
	_Other.MouseY = 0;
}

BFW::GUI::Window::~Window()
{
	Destroy();
}

const bool BFW::GUI::Window::Create(const uint32_t _ExStyle, const BFW_CHAR_TYPE* _ClassName, const BFW_CHAR_TYPE* _WindowName, const uint32_t _Style, const int32_t _X, const int32_t _Y, const int32_t _Width, const int32_t _Height, const HWND _ParentHandle, const HMENU _MenuHandle, const HINSTANCE _InstanceHandle, void* _Param, const HACCEL _AccelHandle, const bool (*_ThreadInitFnc)(void* _UserData), void (*_ThreadCleanUpFnc)(void* _UserData), const bool (*_WndInitFnc)(Window* _Wnd), void (*_WndCleanUpFnc)(Window* _Wnd), void* _UserData)
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

	bool _Done = false;
	bool _Fail = false;

	WndThread = new std::thread(WndThreadFnc, std::ref(_Done), std::ref(_Fail), this, _ExStyle, _ClassName, _WindowName, _Style, _X, _Y, _Width, _Height, _ParentHandle, _MenuHandle, _InstanceHandle, _Param, _AccelHandle, _ThreadInitFnc, _ThreadCleanUpFnc, _WndInitFnc, _WndCleanUpFnc, _UserData);

	if (!WndThread)
	{
		delete WindowMutex;
		WindowMutex = nullptr;
		return false;
	}

	while (!_Done)
	{
		Time::Sleep(1);
	}

	if (_Fail)
	{
		WndThread->join();
		delete WndThread;
		WndThread = nullptr;
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
	delete WndThread;
	WndThread = nullptr;
	FullScreen = false;
	WndRect = { 0 };
	WndPlace = { 0 };
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

	return InvalidateRect(Handle, nullptr, false);
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

BFW::GUI::Window& BFW::GUI::Window::operator= (Window&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Destroy();

	Handle = _Other.Handle;
	WndThread = _Other.WndThread;
	UserData = _Other.UserData;
	FullScreen = _Other.FullScreen;
	WndRect = _Other.WndRect;
	WndPlace = _Other.WndPlace;
	WindowMutex = _Other.WindowMutex;
	Cursor = _Other.Cursor;
	Close = _Other.Close;
	Focus = _Other.Focus;
	for (size_t _Index = 0; _Index < 256; _Index++)
	{
		RawKeys[_Index] = _Other.RawKeys[_Index];
	}
	for (size_t _Index = 0; _Index < 256; _Index++)
	{
		Keys[_Index] = (Input::Key&&)(_Other.Keys[_Index]);
	}
	Tracking = _Other.Tracking;
	HasMouse = _Other.HasMouse;
	MouseX = _Other.MouseX;
	MouseY = _Other.MouseY;
	KeyEvents = (Vector<uint8_t>&&)(_Other.KeyEvents);
	LClicks = (Vector<Input::ClickEvent>&&)(_Other.LClicks);
	RClicks = (Vector<Input::ClickEvent>&&)(_Other.RClicks);
	MClicks = (Vector<Input::ClickEvent>&&)(_Other.MClicks);
	X1Clicks = (Vector<Input::ClickEvent>&&)(_Other.X1Clicks);
	X2Clicks = (Vector<Input::ClickEvent>&&)(_Other.X2Clicks);
	LDblClicks = (Vector<Input::ClickEvent>&&)(_Other.LDblClicks);
	RDblClicks = (Vector<Input::ClickEvent>&&)(_Other.RDblClicks);
	MDblClicks = (Vector<Input::ClickEvent>&&)(_Other.MDblClicks);
	X1DblClicks = (Vector<Input::ClickEvent>&&)(_Other.X1DblClicks);
	X2DblClicks = (Vector<Input::ClickEvent>&&)(_Other.X2DblClicks);
	WheelEvents = (Vector<Input::WheelEvent>&&)(_Other.WheelEvents);
	HWheelEvents = (Vector<Input::WheelEvent>&&)(_Other.HWheelEvents);
	CharEvents = (Vector<BFW_CHAR_TYPE>&&)(_Other.CharEvents);

	_Other.Handle = NULL;
	_Other.WndThread = nullptr;
	_Other.UserData = nullptr;
	_Other.FullScreen = false;
	_Other.WndRect = { 0 };
	_Other.WndPlace = { 0 };
	_Other.WindowMutex = nullptr;
	_Other.Cursor = LoadCursor(NULL, IDC_ARROW);
	_Other.Close = false;
	_Other.Focus = false;
	for (size_t _Index = 0; _Index < 256; _Index++)
	{
		_Other.RawKeys[_Index] = false;
	}
	_Other.Tracking = false;
	_Other.HasMouse = false;
	_Other.MouseX = 0;
	_Other.MouseY = 0;

	return *this;
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
		_Wnd->LClicks.PushBack(Input::ClickEvent((size_t)(LOWORD(_lParam)), (size_t)(HIWORD(_lParam)), (LOWORD(_wParam) & MK_CONTROL) != 0, (LOWORD(_wParam) & MK_SHIFT) != 0));
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
		_Wnd->RClicks.PushBack(Input::ClickEvent((size_t)(LOWORD(_lParam)), (size_t)(HIWORD(_lParam)), (LOWORD(_wParam) & MK_CONTROL) != 0, (LOWORD(_wParam) & MK_SHIFT) != 0));
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
		_Wnd->MClicks.PushBack(Input::ClickEvent((size_t)(LOWORD(_lParam)), (size_t)(HIWORD(_lParam)), (LOWORD(_wParam) & MK_CONTROL) != 0, (LOWORD(_wParam) & MK_SHIFT) != 0));
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
			_Wnd->X1Clicks.PushBack(Input::ClickEvent((size_t)(LOWORD(_lParam)), (size_t)(HIWORD(_lParam)), (LOWORD(_wParam) & MK_CONTROL) != 0, (LOWORD(_wParam) & MK_SHIFT) != 0));
			if (!_Wnd->RawKeys[VK_LBUTTON] && !_Wnd->RawKeys[VK_RBUTTON] && !_Wnd->RawKeys[VK_MBUTTON] && !_Wnd->RawKeys[VK_XBUTTON1] && !_Wnd->RawKeys[VK_XBUTTON2])
			{
				ReleaseCapture();
			}
		}
		else
		{
			_Wnd->RawKeys[VK_XBUTTON2] = false;
			_Wnd->X2Clicks.PushBack(Input::ClickEvent((size_t)(LOWORD(_lParam)), (size_t)(HIWORD(_lParam)), (LOWORD(_wParam) & MK_CONTROL) != 0, (LOWORD(_wParam) & MK_SHIFT) != 0));
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
		_Wnd->LDblClicks.PushBack(Input::ClickEvent((size_t)(LOWORD(_lParam)), (size_t)(HIWORD(_lParam)), (LOWORD(_wParam) & MK_CONTROL) != 0, (LOWORD(_wParam) & MK_SHIFT) != 0));
		_Wnd->WindowMutex->unlock();

		break;
	}
	case WM_RBUTTONDBLCLK:
	{
		_Wnd->WindowMutex->lock();
		_Wnd->RDblClicks.PushBack(Input::ClickEvent((size_t)(LOWORD(_lParam)), (size_t)(HIWORD(_lParam)), (LOWORD(_wParam) & MK_CONTROL) != 0, (LOWORD(_wParam) & MK_SHIFT) != 0));
		_Wnd->WindowMutex->unlock();

		break;
	}
	case WM_MBUTTONDBLCLK:
	{
		_Wnd->WindowMutex->lock();
		_Wnd->MDblClicks.PushBack(Input::ClickEvent((size_t)(LOWORD(_lParam)), (size_t)(HIWORD(_lParam)), (LOWORD(_wParam) & MK_CONTROL) != 0, (LOWORD(_wParam) & MK_SHIFT) != 0));
		_Wnd->WindowMutex->unlock();

		break;
	}
	case WM_XBUTTONDBLCLK:
	{
		_Wnd->WindowMutex->lock();
		if (HIWORD(_wParam) == XBUTTON1)
		{
			_Wnd->X1DblClicks.PushBack(Input::ClickEvent((size_t)(LOWORD(_lParam)), (size_t)(HIWORD(_lParam)), (LOWORD(_wParam) & MK_CONTROL) != 0, (LOWORD(_wParam) & MK_SHIFT) != 0));
		}
		else
		{
			_Wnd->X2DblClicks.PushBack(Input::ClickEvent((size_t)(LOWORD(_lParam)), (size_t)(HIWORD(_lParam)), (LOWORD(_wParam) & MK_CONTROL) != 0, (LOWORD(_wParam) & MK_SHIFT) != 0));
		}
		_Wnd->WindowMutex->unlock();

		break;
	}
	case WM_MOUSEWHEEL:
	{
		_Wnd->WindowMutex->lock();
		_Wnd->WheelEvents.PushBack(Input::WheelEvent((intptr_t)(-(int16_t)(HIWORD(_wParam))), (size_t)(LOWORD(_lParam)), (size_t)(HIWORD(_lParam)), (LOWORD(_wParam) & MK_CONTROL) != 0, (LOWORD(_wParam) & MK_SHIFT) != 0));
		_Wnd->WindowMutex->unlock();

		break;
	}
	case WM_MOUSEHWHEEL:
	{
		_Wnd->WindowMutex->lock();
		_Wnd->HWheelEvents.PushBack(Input::WheelEvent((intptr_t)((int16_t)(HIWORD(_wParam))), (size_t)(LOWORD(_lParam)), (size_t)(HIWORD(_lParam)), (LOWORD(_wParam) & MK_CONTROL) != 0, (LOWORD(_wParam) & MK_SHIFT) != 0));
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
		_Wnd->MouseX = LOWORD(_lParam);
		_Wnd->MouseY = HIWORD(_lParam);
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

void BFW::GUI::Window::WndThreadFnc(bool& _Done, bool& _Fail, Window* _Wnd, const uint32_t _ExStyle, const BFW_CHAR_TYPE* _ClassName, const BFW_CHAR_TYPE* _WindowName, const uint32_t _Style, const int32_t _X, const int32_t _Y, const int32_t _Width, const int32_t _Height, const HWND _ParentHandle, const HMENU _MenuHandle, const HINSTANCE _InstanceHandle, void* _Param, const HACCEL _AccelHandle, const bool (*_ThreadInitFnc)(void* _UserData), void (*_ThreadCleanUpFnc)(void* _UserData), const bool (*_WndInitFnc)(Window* _Wnd), void (*_WndCleanUpFnc)(Window* _Wnd), void* _UserData)
{
	if (_ThreadInitFnc)
	{
		if (!_ThreadInitFnc(_UserData))
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

		if (_ThreadCleanUpFnc)
		{
			_ThreadCleanUpFnc(_UserData);
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

			if (_ThreadCleanUpFnc)
			{
				_ThreadCleanUpFnc(_UserData);
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

	if (_WndInitFnc)
	{
		if (!_WndInitFnc(_Wnd))
		{
			DestroyWindow(_Wnd->Handle);
			_Wnd->Handle = NULL;
			_Wnd->UserData = nullptr;

			if (_ThreadCleanUpFnc)
			{
				_ThreadCleanUpFnc(_UserData);
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

	if (_WndCleanUpFnc)
	{
		_WndCleanUpFnc(_Wnd);
	}

	_Wnd->UserData = nullptr;

	if (_ThreadCleanUpFnc)
	{
		_ThreadCleanUpFnc(_UserData);
	}

	if (_AccelHandle)
	{
		DestroyAcceleratorTable(_AccelHandle);
	}
}

#endif



BFW::GUI::PopUp::PopUp() : FocusedPanel(0), Panels(), Node(nullptr), FocusedPopUps(), PopUps(), Id(_NodePopUpId), PanelType(_NullPanelType), TrueWidth(0), TrueHeight(0), Width(0), Height(0), PositionX(0), PositionY(0), ScrollX(0), ScrollY(0), UserData(nullptr), SetupData(nullptr), CleanUpData(nullptr), RenderBottom(nullptr), RenderMiddle(nullptr), RenderTop(nullptr), Composit(nullptr)
{

}

BFW::GUI::PopUp::PopUp(const PopUp& _Other) : FocusedPanel(0), Panels(), Node(nullptr), FocusedPopUps(), PopUps(), Id(_NodePopUpId), PanelType(_NullPanelType), TrueWidth(0), TrueHeight(0), Width(0), Height(0), PositionX(0), PositionY(0), ScrollX(0), ScrollY(0), UserData(nullptr), SetupData(nullptr), CleanUpData(nullptr), RenderBottom(nullptr), RenderMiddle(nullptr), RenderTop(nullptr), Composit(nullptr)
{
	if (_Other.Node != nullptr)
	{
		Node = new PopUp;

		if (!Node)
		{
			throw nullptr;
		}

		*Node = *_Other.Node;
	}

	FocusedPanel = _Other.FocusedPanel;
	Panels = _Other.Panels;
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
	UserData = _Other.UserData;
	SetupData = _Other.SetupData;
	CleanUpData = _Other.CleanUpData;
	RenderBottom = _Other.RenderBottom;
	RenderMiddle = _Other.RenderMiddle;
	RenderTop = _Other.RenderTop;
	Composit = _Other.Composit;
}

BFW::GUI::PopUp::PopUp(PopUp&& _Other) noexcept : FocusedPanel(_Other.FocusedPanel), Panels((Vector<PopUp>&&)(_Other.Panels)), Node(_Other.Node), FocusedPopUps((Vector<size_t>&&)(_Other.FocusedPopUps)), PopUps((Vector<Vector<PopUp>>&&)(_Other.PopUps)), Id(_Other.Id), PanelType(_Other.PanelType), TrueWidth(_Other.TrueWidth), TrueHeight(_Other.TrueHeight), Width(_Other.Width), Height(_Other.Height), PositionX(_Other.PositionX), PositionY(_Other.PositionY), ScrollX(_Other.ScrollX), ScrollY(_Other.ScrollY), UserData(_Other.UserData), SetupData(_Other.SetupData), CleanUpData(_Other.CleanUpData), RenderBottom(_Other.RenderBottom), RenderMiddle(_Other.RenderMiddle), RenderTop(_Other.RenderTop), Composit(_Other.Composit)
{
	_Other.FocusedPanel = 0;
	_Other.Node = nullptr;
	_Other.Id = _NodePopUpId;
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
	_Other.SetupData = nullptr;
	_Other.CleanUpData = nullptr;
	_Other.RenderBottom = nullptr;
	_Other.RenderMiddle = nullptr;
	_Other.RenderTop = nullptr;
	_Other.Composit = nullptr;
}

BFW::GUI::PopUp::~PopUp()
{
	delete Node;
}

BFW::GUI::PopUp& BFW::GUI::PopUp::Begin(const uint64_t _Id, const uint8_t _PanelType, const size_t _TrueWidth, const size_t _TrueHeight, const size_t _Width, const size_t _Height, const intptr_t _PositionX, const intptr_t _PositionY, const size_t _ScrollX, const size_t _ScrollY, const SetupRenderDataFnc _SetupData, const CleanUpRenderDataFnc _CleanUpData, const RenderFnc _RenderBottom, const RenderFnc _RenderMiddle, const RenderFnc _RenderTop, const CompositFnc _Composit, void* _UserData)
{
	FocusedPanel = 0;
	Panels.Clear();
	delete Node;
	Node = nullptr;
	FocusedPopUps.Clear();
	PopUps.Clear();

	if (_Width > _TrueWidth || _Height > _TrueHeight || _ScrollX > _TrueWidth - _Width || _ScrollY > _TrueHeight - _Height)
	{
		throw nullptr;
	}

	Id = _Id;
	PanelType = _PanelType;
	TrueWidth = _TrueWidth;
	TrueHeight = _TrueHeight;
	Width = _Width;
	Height = _Height;
	PositionX = _PositionX;
	PositionY = _PositionY;
	ScrollX = _ScrollX;
	ScrollY = _ScrollY;
	UserData = _UserData;
	SetupData = _SetupData;
	CleanUpData = _CleanUpData;
	RenderBottom = _RenderBottom;
	RenderMiddle = _RenderMiddle;
	RenderTop = _RenderTop;
	Composit = _Composit;

	return *this;
}

BFW::GUI::PopUp& BFW::GUI::PopUp::PushLeftPanel(const uint64_t _Id, const size_t _TrueWidth, const size_t _TrueHeight, const size_t _Width, const size_t _ScrollX, const size_t _ScrollY, const SetupRenderDataFnc _SetupData, const CleanUpRenderDataFnc _CleanUpData, const RenderFnc _RenderBottom, const RenderFnc _RenderMiddle, const RenderFnc _RenderTop, const CompositFnc _Composit, void* _UserData, const bool _Focused)
{
	if (Panels.GetSize() != 0 && Panels[0].PanelType != _LeftPanelType)
	{
		BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Only constant panel types are supported!"));
		throw nullptr;
	}

	Panels.PushBack(PopUp());
	Panels[Panels.GetSize() - 1].Begin(_Id, _LeftPanelType, _TrueWidth, _TrueHeight, _Width, TrueHeight, 0, 0, _ScrollX, _ScrollY, _SetupData, _CleanUpData, _RenderBottom, _RenderMiddle, _RenderTop, _Composit, _UserData);

	if (_Focused)
	{
		FocusedPanel = Panels.GetSize() - 1;
	}

	if (Node == nullptr)
	{
		Node = new PopUp;

		if (Node == nullptr)
		{
			throw nullptr;
		}

		if (_Width <= TrueWidth)
		{
			Node->TrueWidth = TrueWidth - _Width;
			Node->TrueHeight = TrueHeight;
			Node->Width = TrueWidth - _Width;
			Node->Height = TrueHeight;
			Node->PositionX = _Width;
			Node->PositionY = 0;
		}
		else
		{
			Node->TrueWidth = 0;
			Node->TrueHeight = TrueHeight;
			Node->Width = 0;
			Node->Height = TrueHeight;
			Node->PositionX = _Width;
			Node->PositionY = 0;
		}
	}

	return Panels[Panels.GetSize() - 1];
}

BFW::GUI::PopUp& BFW::GUI::PopUp::PushRightPanel(const uint64_t _Id, const size_t _TrueWidth, const size_t _TrueHeight, const size_t _Width, const size_t _ScrollX, const size_t _ScrollY, const SetupRenderDataFnc _SetupData, const CleanUpRenderDataFnc _CleanUpData, const RenderFnc _RenderBottom, const RenderFnc _RenderMiddle, const RenderFnc _RenderTop, const CompositFnc _Composit, void* _UserData, const bool _Focused)
{
	if (Panels.GetSize() != 0 && Panels[0].PanelType != _RightPanelType)
	{
		BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Only constant panel types are supported!"));
		throw nullptr;
	}

	Panels.PushBack(PopUp());
	Panels[Panels.GetSize() - 1].Begin(_Id, _RightPanelType, _TrueWidth, _TrueHeight, _Width, TrueHeight, TrueWidth - _Width, 0, _ScrollX, _ScrollY, _SetupData, _CleanUpData, _RenderBottom, _RenderMiddle, _RenderTop, _Composit, _UserData);

	if (_Focused)
	{
		FocusedPanel = Panels.GetSize() - 1;
	}

	if (Node == nullptr)
	{
		Node = new PopUp;

		if (Node == nullptr)
		{
			throw nullptr;
		}

		if (_Width <= TrueWidth)
		{
			Node->TrueWidth = TrueWidth - _Width;
			Node->TrueHeight = TrueHeight;
			Node->Width = TrueWidth - _Width;
			Node->Height = TrueHeight;
			Node->PositionX = 0;
			Node->PositionY = 0;
		}
		else
		{
			Node->TrueWidth = 0;
			Node->TrueHeight = TrueHeight;
			Node->Width = 0;
			Node->Height = TrueHeight;
			Node->PositionX = 0;
			Node->PositionY = 0;
		}
	}

	return Panels[Panels.GetSize() - 1];
}

BFW::GUI::PopUp& BFW::GUI::PopUp::PushTopPanel(const uint64_t _Id, const size_t _TrueWidth, const size_t _TrueHeight, const size_t _Height, const size_t _ScrollX, const size_t _ScrollY, const SetupRenderDataFnc _SetupData, const CleanUpRenderDataFnc _CleanUpData, const RenderFnc _RenderBottom, const RenderFnc _RenderMiddle, const RenderFnc _RenderTop, const CompositFnc _Composit, void* _UserData, const bool _Focused)
{
	if (Panels.GetSize() != 0 && Panels[0].PanelType != _TopPanelType)
	{
		BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Only constant panel types are supported!"));
		throw nullptr;
	}

	Panels.PushBack(PopUp());
	Panels[Panels.GetSize() - 1].Begin(_Id, _TopPanelType, _TrueWidth, _TrueHeight, TrueWidth, _Height, 0, 0, _ScrollX, _ScrollY, _SetupData, _CleanUpData, _RenderBottom, _RenderMiddle, _RenderTop, _Composit, _UserData);

	if (_Focused)
	{
		FocusedPanel = Panels.GetSize() - 1;
	}

	if (Node == nullptr)
	{
		Node = new PopUp;

		if (Node == nullptr)
		{
			throw nullptr;
		}

		if (_Height <= TrueHeight)
		{
			Node->TrueWidth = TrueWidth;
			Node->TrueHeight = TrueHeight - _Height;
			Node->Width = TrueWidth;
			Node->Height = TrueHeight - _Height;
			Node->PositionX = 0;
			Node->PositionY = _Height;
		}
		else
		{
			Node->TrueWidth = TrueWidth;
			Node->TrueHeight = 0;
			Node->Width = TrueWidth;
			Node->Height = 0;
			Node->PositionX = 0;
			Node->PositionY = _Height;
		}
	}

	return Panels[Panels.GetSize() - 1];
}

BFW::GUI::PopUp& BFW::GUI::PopUp::PushBottomPanel(const uint64_t _Id, const size_t _TrueWidth, const size_t _TrueHeight, const size_t _Height, const size_t _ScrollX, const size_t _ScrollY, const SetupRenderDataFnc _SetupData, const CleanUpRenderDataFnc _CleanUpData, const RenderFnc _RenderBottom, const RenderFnc _RenderMiddle, const RenderFnc _RenderTop, const CompositFnc _Composit, void* _UserData, const bool _Focused)
{
	if (Panels.GetSize() != 0 && Panels[0].PanelType != _BottomPanelType)
	{
		BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Only constant panel types are supported!"));
		throw nullptr;
	}

	Panels.PushBack(PopUp());
	Panels[Panels.GetSize() - 1].Begin(_Id, _BottomPanelType, _TrueWidth, _TrueHeight, TrueWidth, _Height, 0, TrueHeight - _Height, _ScrollX, _ScrollY, _SetupData, _CleanUpData, _RenderBottom, _RenderMiddle, _RenderTop, _Composit, _UserData);

	if (_Focused)
	{
		FocusedPanel = Panels.GetSize() - 1;
	}

	if (Node == nullptr)
	{
		Node = new PopUp;

		if (Node == nullptr)
		{
			throw nullptr;
		}

		if (_Height <= TrueHeight)
		{
			Node->TrueWidth = TrueWidth;
			Node->TrueHeight = TrueHeight - _Height;
			Node->Width = TrueWidth;
			Node->Height = TrueHeight - _Height;
			Node->PositionX = 0;
			Node->PositionY = 0;
		}
		else
		{
			Node->TrueWidth = TrueWidth;
			Node->TrueHeight = 0;
			Node->Width = TrueWidth;
			Node->Height = 0;
			Node->PositionX = 0;
			Node->PositionY = 0;
		}
	}

	return Panels[Panels.GetSize() - 1];
}

const size_t BFW::GUI::PopUp::PushPopUpLayer()
{
	FocusedPopUps.PushBack(0);
	PopUps.PushBack(Vector<PopUp>());

	return PopUps.GetSize() - 1;
}

BFW::GUI::PopUp& BFW::GUI::PopUp::PushPopUp(const size_t _Layer, const uint64_t _Id, const size_t _TrueWidth, const size_t _TrueHeight, const size_t _Width, const size_t _Height, const intptr_t _PositionX, const intptr_t _PositionY, const size_t _ScrollX, const size_t _ScrollY, const SetupRenderDataFnc _SetupData, const CleanUpRenderDataFnc _CleanUpData, const RenderFnc _RenderBottom, const RenderFnc _RenderMiddle, const RenderFnc _RenderTop, const CompositFnc _Composit, void* _UserData, const bool _Focused)
{
	if (_Layer >= PopUps.GetSize())
	{
		throw nullptr;
	}

	PopUps[_Layer].PushBack(PopUp());
	PopUps[_Layer][PopUps[_Layer].GetSize() - 1].Begin(_Id, _NullPanelType, _TrueWidth, _TrueHeight, _Width, _Height, _PositionX, _PositionY, _ScrollX, _ScrollY, _SetupData, _CleanUpData, _RenderBottom, _RenderMiddle, _RenderTop, _Composit, _UserData);

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
		throw nullptr;
	}

	if (RenderBottom)
	{
		RenderBottom(this, _Global);
	}

	if (Panels.GetSize())
	{
		if (Panels[FocusedPanel].SetupData)
		{
			Panels[FocusedPanel].SetupData(&Panels[FocusedPanel], this, _Global);
		}

		Panels[FocusedPanel].Render(_Global);
		Composit(this, &Panels[FocusedPanel], _Global);

		if (Panels[FocusedPanel].CleanUpData)
		{
			Panels[FocusedPanel].CleanUpData(&Panels[FocusedPanel], _Global);
		}
	}

	if (Node != nullptr)
	{
		if (Node->SetupData)
		{
			Node->SetupData(Node, this, _Global);
		}

		Node->Render(_Global);
		Composit(this, Node, _Global);

		if (Node->CleanUpData)
		{
			Node->CleanUpData(Node, _Global);
		}
	}

	if (RenderMiddle)
	{
		RenderMiddle(this, _Global);
	}

	for (size_t _Index = 0; _Index < PopUps.GetSize(); _Index++)
	{
		if (PopUps[_Index].GetSize())
		{
			if (PopUps[_Index][FocusedPopUps[_Index]].SetupData)
			{
				PopUps[_Index][FocusedPopUps[_Index]].SetupData(&PopUps[_Index][FocusedPopUps[_Index]], this, _Global);
			}

			PopUps[_Index][FocusedPopUps[_Index]].Render(_Global);
			Composit(this, &PopUps[_Index][FocusedPopUps[_Index]], _Global);

			if (PopUps[_Index][FocusedPopUps[_Index]].CleanUpData)
			{
				PopUps[_Index][FocusedPopUps[_Index]].CleanUpData(&PopUps[_Index][FocusedPopUps[_Index]], _Global);
			}
		}
	}

	if (RenderTop)
	{
		RenderTop(this, _Global);
	}
}

void BFW::GUI::PopUp::SetFocusedPanel(const size_t _FocusedPanel)
{
	FocusedPanel = _FocusedPanel;
}

void BFW::GUI::PopUp::SetId(const uint64_t _Id)
{
	Id = _Id;
}

void BFW::GUI::PopUp::SetPanelType(const uint8_t _PanelType)
{
	PanelType = _PanelType;
}

void BFW::GUI::PopUp::SetTrueWidth(const size_t _TrueWidth)
{
	TrueWidth = _TrueWidth;
}

void BFW::GUI::PopUp::SetTrueHeight(const size_t _TrueHeight)
{
	TrueHeight = _TrueHeight;
}

void BFW::GUI::PopUp::SetWidth(const size_t _Width)
{
	Width = _Width;
}

void BFW::GUI::PopUp::SetHeight(const size_t _Height)
{
	Height = _Height;
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
	ScrollX = _ScrollX;
}

void BFW::GUI::PopUp::SetScrollY(const size_t _ScrollY)
{
	ScrollY = _ScrollY;
}

void BFW::GUI::PopUp::SetUserData(void* _UserData)
{
	UserData = _UserData;
}

void BFW::GUI::PopUp::SetSetupData(const SetupRenderDataFnc _SetupData)
{
	SetupData = _SetupData;
}

void BFW::GUI::PopUp::SetCleanUpData(const CleanUpRenderDataFnc _CleanUpData)
{
	CleanUpData = _CleanUpData;
}

void BFW::GUI::PopUp::SetRenderBottom(const RenderFnc _RenderBottom)
{
	RenderBottom = _RenderBottom;
}

void BFW::GUI::PopUp::SetRenderMiddle(const RenderFnc _RenderMiddle)
{
	RenderMiddle = _RenderMiddle;
}

void BFW::GUI::PopUp::SetRenderTop(const RenderFnc _RenderTop)
{
	RenderTop = _RenderTop;
}

void BFW::GUI::PopUp::SetComposit(const CompositFnc _Composit)
{
	Composit = _Composit;
}

BFW::GUI::PopUp* BFW::GUI::PopUp::GetChildFromMouse(const intptr_t _MouseX, const intptr_t _MouseY, Vector<PopUp*>* _Path)
{
	if (_MouseX < 0 || (size_t)(_MouseX) >= Width || _MouseY < 0 || (size_t)(_MouseY) >= Height)
	{
		return nullptr;
	}

	for (size_t _Index = 0; _Index < PopUps.GetSize(); _Index++)
	{
		PopUp& _PopUp = PopUps[PopUps.GetSize() - 1 - _Index][FocusedPopUps[PopUps.GetSize() - 1 - _Index]];

		PopUp* _Result = _PopUp.GetChildFromMouse(_MouseX - _PopUp.PositionX, _MouseY - _PopUp.PositionY, _Path);

		if (_Result != nullptr)
		{
			if (_Path)
			{
				_Path->PushBack(this);
			}

			return _Result;
		}
	}

	if (Node != nullptr)
	{
		PopUp* _Result = Node->GetChildFromMouse(_MouseX - Node->PositionX, _MouseY - Node->PositionY, _Path);

		if (_Result != nullptr)
		{
			if (_Path)
			{
				_Path->PushBack(this);
			}

			return _Result;
		}
	}

	if (Panels.GetSize() != 0)
	{
		PopUp& _Panel = Panels[FocusedPanel];

		PopUp* _Result = _Panel.GetChildFromMouse(_MouseX - _Panel.PositionX, _MouseY - _Panel.PositionY, _Path);

		if (_Result != nullptr)
		{
			if (_Path)
			{
				_Path->PushBack(this);
			}

			return _Result;
		}
	}

	if (_Path)
	{
		_Path->PushBack(this);
	}

	return this;
}

const BFW::GUI::PopUp* BFW::GUI::PopUp::GetChildFromMouse(const intptr_t _MouseX, const intptr_t _MouseY, Vector<const PopUp*>* _Path) const
{
	if (_MouseX < 0 || (size_t)(_MouseX) >= Width || _MouseY < 0 || (size_t)(_MouseY) >= Height)
	{
		return nullptr;
	}

	for (size_t _Index = 0; _Index < PopUps.GetSize(); _Index++)
	{
		const PopUp& _PopUp = PopUps[PopUps.GetSize() - 1 - _Index][FocusedPopUps[PopUps.GetSize() - 1 - _Index]];

		const PopUp* _Result = _PopUp.GetChildFromMouse(_MouseX - _PopUp.PositionX, _MouseY - _PopUp.PositionY, _Path);

		if (_Result != nullptr)
		{
			if (_Path)
			{
				_Path->PushBack(this);
			}

			return _Result;
		}
	}

	if (Node != nullptr)
	{
		const PopUp* _Result = Node->GetChildFromMouse(_MouseX - Node->PositionX, _MouseY - Node->PositionY, _Path);

		if (_Result != nullptr)
		{
			if (_Path)
			{
				_Path->PushBack(this);
			}

			return _Result;
		}
	}

	if (Panels.GetSize() != 0)
	{
		const PopUp& _Panel = Panels[FocusedPanel];

		const PopUp* _Result = _Panel.GetChildFromMouse(_MouseX - _Panel.PositionX, _MouseY - _Panel.PositionY, _Path);

		if (_Result != nullptr)
		{
			if (_Path)
			{
				_Path->PushBack(this);
			}

			return _Result;
		}
	}

	if (_Path)
	{
		_Path->PushBack(this);
	}

	return this;
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

BFW::GUI::PopUp* BFW::GUI::PopUp::GetNode()
{
	return Node;
}

const BFW::GUI::PopUp* BFW::GUI::PopUp::GetNode() const
{
	return Node;
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

const BFW::GUI::SetupRenderDataFnc BFW::GUI::PopUp::GetSetupData() const
{
	return SetupData;
}

const BFW::GUI::CleanUpRenderDataFnc BFW::GUI::PopUp::GetCleanUpData() const
{
	return CleanUpData;
}

const BFW::GUI::RenderFnc BFW::GUI::PopUp::GetRenderBottom() const
{
	return RenderBottom;
}

const BFW::GUI::RenderFnc BFW::GUI::PopUp::GetRenderMiddle() const
{
	return RenderMiddle;
}

const BFW::GUI::RenderFnc BFW::GUI::PopUp::GetRenderTop() const
{
	return RenderTop;
}

const BFW::GUI::CompositFnc BFW::GUI::PopUp::GetComposit() const
{
	return Composit;
}

BFW::GUI::PopUp& BFW::GUI::PopUp::operator= (const PopUp& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	delete Node;
	Node = nullptr;

	if (_Other.Node != nullptr)
	{
		Node = new PopUp;

		if (!Node)
		{
			throw nullptr;
		}

		*Node = *_Other.Node;
	}

	FocusedPanel = _Other.FocusedPanel;
	Panels = _Other.Panels;
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
	UserData = _Other.UserData;
	SetupData = _Other.SetupData;
	CleanUpData = _Other.CleanUpData;
	RenderBottom = _Other.RenderBottom;
	RenderMiddle = _Other.RenderMiddle;
	RenderTop = _Other.RenderTop;
	Composit = _Other.Composit;

	return *this;
}

BFW::GUI::PopUp& BFW::GUI::PopUp::operator= (PopUp&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	delete Node;
	Node = nullptr;

	FocusedPanel = _Other.FocusedPanel;
	Panels = (Vector<PopUp>&&)(_Other.Panels);
	Node = _Other.Node;
	FocusedPopUps = (Vector<size_t>&&)(_Other.FocusedPopUps);
	PopUps = (Vector<Vector<PopUp>>&&)(_Other.PopUps);
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
	SetupData = _Other.SetupData;
	CleanUpData = _Other.CleanUpData;
	RenderBottom = _Other.RenderBottom;
	RenderMiddle = _Other.RenderMiddle;
	RenderTop = _Other.RenderTop;
	Composit = _Other.Composit;

	_Other.FocusedPanel = 0;
	_Other.Node = nullptr;
	_Other.Id = _NodePopUpId;
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
	_Other.SetupData = nullptr;
	_Other.CleanUpData = nullptr;
	_Other.RenderBottom = nullptr;
	_Other.RenderMiddle = nullptr;
	_Other.RenderTop = nullptr;
	_Other.Composit = nullptr;

	return *this;
}
