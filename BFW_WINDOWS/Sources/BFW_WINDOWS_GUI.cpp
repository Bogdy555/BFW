#include "../Headers/BFW_WINDOWS.hpp"



const float BFW_WINDOWS::GUI::MouseCaptureScrollSpeed = 30.0f;
const size_t BFW_WINDOWS::GUI::MouseCaptureScrollScale = 10;

const size_t BFW_WINDOWS::GUI::MainWindowMinX = 700;
const size_t BFW_WINDOWS::GUI::MainWindowMinY = 400;
const size_t BFW_WINDOWS::GUI::ChildWindowMinX = 200;
const size_t BFW_WINDOWS::GUI::ChildWindowMinY = 200;

const size_t BFW_WINDOWS::GUI::ResizeSize = 5;
const size_t BFW_WINDOWS::GUI::ScrollSize = 15;
const size_t BFW_WINDOWS::GUI::ScrollTopPadding = 25;
const size_t BFW_WINDOWS::GUI::ScrollPadding = 10;
const size_t BFW_WINDOWS::GUI::TopPadding = 45;
const size_t BFW_WINDOWS::GUI::Padding = 30;

const size_t BFW_WINDOWS::GUI::DebugWindowMinX = 200;
const size_t BFW_WINDOWS::GUI::DebugWindowMinY = 200;



BFW_WINDOWS::GUI::PopUpData::PopUpData() : Width(0), Height(0), Pixels(nullptr), Wnd(nullptr)
{

}

BFW_WINDOWS::GUI::PopUpData::PopUpData(PopUpData&& _Other) noexcept : Width(_Other.Width), Height(_Other.Height), Pixels(_Other.Pixels), Wnd(_Other.Wnd)
{
	_Other.Width = 0;
	_Other.Height = 0;
	_Other.Pixels = nullptr;
	_Other.Wnd = nullptr;
}

BFW_WINDOWS::GUI::PopUpData& BFW_WINDOWS::GUI::PopUpData::operator= (PopUpData&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Width = _Other.Width;
	Height = _Other.Height;
	Pixels = _Other.Pixels;
	Wnd = _Other.Wnd;

	_Other.Width = 0;
	_Other.Height = 0;
	_Other.Pixels = nullptr;
	_Other.Wnd = nullptr;

	return *this;
}



BFW_WINDOWS::GUI::WindowData::WindowData() :
	LayoutMutex(nullptr), Layout(),
	LCapture(false), LCapturePath(), LCaptureMouseX(0), LCaptureMouseY(0), LCaptureMouseXLastFrame(0), LCaptureMouseYLastFrame(0), LAccumulationX(0), LAccumulationY(0),
	MCapture(false), MCapturePath(), MCaptureMouseX(0), MCaptureMouseY(0), MCaptureMouseXLastFrame(0), MCaptureMouseYLastFrame(0), MAccumulationX(0), MAccumulationY(0),
	RCapture(false), RCapturePath(), RCaptureMouseX(0), RCaptureMouseY(0), RCaptureMouseXLastFrame(0), RCaptureMouseYLastFrame(0), RAccumulationX(0), RAccumulationY(0),
	X1Capture(false), X1CapturePath(), X1CaptureMouseX(0), X1CaptureMouseY(0), X1CaptureMouseXLastFrame(0), X1CaptureMouseYLastFrame(0), X1AccumulationX(0), X1AccumulationY(0),
	X2Capture(false), X2CapturePath(), X2CaptureMouseX(0), X2CaptureMouseY(0), X2CaptureMouseXLastFrame(0), X2CaptureMouseYLastFrame(0), X2AccumulationX(0), X2AccumulationY(0)
{

}

BFW_WINDOWS::GUI::WindowData::WindowData(WindowData&& _Other) noexcept :
	LayoutMutex(_Other.LayoutMutex), Layout((BFW::GUI::PopUp&&)(_Other.Layout)),
	LCapture(_Other.LCapture), LCapturePath((BFW::Vector<BFW::GUI::SafePopUpPointer>&&)(_Other.LCapturePath)), LCaptureMouseX(_Other.LCaptureMouseX), LCaptureMouseY(_Other.LCaptureMouseY), LCaptureMouseXLastFrame(_Other.LCaptureMouseXLastFrame), LCaptureMouseYLastFrame(_Other.LCaptureMouseYLastFrame), LAccumulationX(_Other.LAccumulationX), LAccumulationY(_Other.LAccumulationY),
	MCapture(_Other.MCapture), MCapturePath((BFW::Vector<BFW::GUI::SafePopUpPointer>&&)(_Other.MCapturePath)), MCaptureMouseX(_Other.MCaptureMouseX), MCaptureMouseY(_Other.MCaptureMouseY), MCaptureMouseXLastFrame(_Other.MCaptureMouseXLastFrame), MCaptureMouseYLastFrame(_Other.MCaptureMouseYLastFrame), MAccumulationX(_Other.MAccumulationX), MAccumulationY(_Other.MAccumulationY),
	RCapture(_Other.RCapture), RCapturePath((BFW::Vector<BFW::GUI::SafePopUpPointer>&&)(_Other.RCapturePath)), RCaptureMouseX(_Other.RCaptureMouseX), RCaptureMouseY(_Other.RCaptureMouseY), RCaptureMouseXLastFrame(_Other.RCaptureMouseXLastFrame), RCaptureMouseYLastFrame(_Other.RCaptureMouseYLastFrame), RAccumulationX(_Other.RAccumulationX), RAccumulationY(_Other.RAccumulationY),
	X1Capture(_Other.X1Capture), X1CapturePath((BFW::Vector<BFW::GUI::SafePopUpPointer>&&)(_Other.X1CapturePath)), X1CaptureMouseX(_Other.X1CaptureMouseX), X1CaptureMouseY(_Other.X1CaptureMouseY), X1CaptureMouseXLastFrame(_Other.X1CaptureMouseXLastFrame), X1CaptureMouseYLastFrame(_Other.X1CaptureMouseYLastFrame), X1AccumulationX(_Other.X1AccumulationX), X1AccumulationY(_Other.X1AccumulationY),
	X2Capture(_Other.X2Capture), X2CapturePath((BFW::Vector<BFW::GUI::SafePopUpPointer>&&)(_Other.X2CapturePath)), X2CaptureMouseX(_Other.X2CaptureMouseX), X2CaptureMouseY(_Other.X2CaptureMouseY), X2CaptureMouseXLastFrame(_Other.X2CaptureMouseXLastFrame), X2CaptureMouseYLastFrame(_Other.X2CaptureMouseYLastFrame), X2AccumulationX(_Other.X2AccumulationX), X2AccumulationY(_Other.X2AccumulationY)
{
	_Other.LayoutMutex = nullptr;
	_Other.LCapture = false;
	_Other.LCaptureMouseX = 0;
	_Other.LCaptureMouseY = 0;
	_Other.LCaptureMouseXLastFrame = 0;
	_Other.LCaptureMouseYLastFrame = 0;
	_Other.LAccumulationX = 0;
	_Other.LAccumulationY = 0;
	_Other.MCapture = false;
	_Other.MCaptureMouseX = 0;
	_Other.MCaptureMouseY = 0;
	_Other.MCaptureMouseXLastFrame = 0;
	_Other.MCaptureMouseYLastFrame = 0;
	_Other.MAccumulationX = 0;
	_Other.MAccumulationY = 0;
	_Other.RCapture = false;
	_Other.RCaptureMouseX = 0;
	_Other.RCaptureMouseY = 0;
	_Other.RCaptureMouseXLastFrame = 0;
	_Other.RCaptureMouseYLastFrame = 0;
	_Other.RAccumulationX = 0;
	_Other.RAccumulationY = 0;
	_Other.X1Capture = false;
	_Other.X1CaptureMouseX = 0;
	_Other.X1CaptureMouseY = 0;
	_Other.X1CaptureMouseXLastFrame = 0;
	_Other.X1CaptureMouseYLastFrame = 0;
	_Other.X1AccumulationX = 0;
	_Other.X1AccumulationY = 0;
	_Other.X2Capture = false;
	_Other.X2CaptureMouseX = 0;
	_Other.X2CaptureMouseY = 0;
	_Other.X2CaptureMouseXLastFrame = 0;
	_Other.X2CaptureMouseYLastFrame = 0;
	_Other.X2AccumulationX = 0;
	_Other.X2AccumulationY = 0;
}

BFW_WINDOWS::GUI::WindowData& BFW_WINDOWS::GUI::WindowData::operator= (WindowData&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	LayoutMutex = _Other.LayoutMutex;
	Layout = (BFW::GUI::PopUp&&)(_Other.Layout);
	LCapture = _Other.LCapture;
	LCapturePath = (BFW::Vector<BFW::GUI::SafePopUpPointer>&&)(_Other.LCapturePath);
	LCaptureMouseX = _Other.LCaptureMouseX;
	LCaptureMouseY = _Other.LCaptureMouseY;
	LCaptureMouseXLastFrame = _Other.LCaptureMouseXLastFrame;
	LCaptureMouseYLastFrame = _Other.LCaptureMouseYLastFrame;
	LAccumulationX = _Other.LAccumulationX;
	LAccumulationY = _Other.LAccumulationY;
	MCapture = _Other.MCapture;
	MCapturePath = (BFW::Vector<BFW::GUI::SafePopUpPointer>&&)(_Other.MCapturePath);
	MCaptureMouseX = _Other.MCaptureMouseX;
	MCaptureMouseY = _Other.MCaptureMouseY;
	MCaptureMouseXLastFrame = _Other.MCaptureMouseXLastFrame;
	MCaptureMouseYLastFrame = _Other.MCaptureMouseYLastFrame;
	MAccumulationX = _Other.MAccumulationX;
	MAccumulationY = _Other.MAccumulationY;
	RCapture = _Other.RCapture;
	RCapturePath = (BFW::Vector<BFW::GUI::SafePopUpPointer>&&)(_Other.RCapturePath);
	RCaptureMouseX = _Other.RCaptureMouseX;
	RCaptureMouseY = _Other.RCaptureMouseY;
	RCaptureMouseXLastFrame = _Other.RCaptureMouseXLastFrame;
	RCaptureMouseYLastFrame = _Other.RCaptureMouseYLastFrame;
	RAccumulationX = _Other.RAccumulationX;
	RAccumulationY = _Other.RAccumulationY;
	X1Capture = _Other.X1Capture;
	X1CapturePath = (BFW::Vector<BFW::GUI::SafePopUpPointer>&&)(_Other.X1CapturePath);
	X1CaptureMouseX = _Other.X1CaptureMouseX;
	X1CaptureMouseY = _Other.X1CaptureMouseY;
	X1CaptureMouseXLastFrame = _Other.X1CaptureMouseXLastFrame;
	X1CaptureMouseYLastFrame = _Other.X1CaptureMouseYLastFrame;
	X1AccumulationX = _Other.X1AccumulationX;
	X1AccumulationY = _Other.X1AccumulationY;
	X2Capture = _Other.X2Capture;
	X2CapturePath = (BFW::Vector<BFW::GUI::SafePopUpPointer>&&)(_Other.X2CapturePath);
	X2CaptureMouseX = _Other.X2CaptureMouseX;
	X2CaptureMouseY = _Other.X2CaptureMouseY;
	X2CaptureMouseXLastFrame = _Other.X2CaptureMouseXLastFrame;
	X2CaptureMouseYLastFrame = _Other.X2CaptureMouseYLastFrame;
	X2AccumulationX = _Other.X2AccumulationX;
	X2AccumulationY = _Other.X2AccumulationY;

	_Other.LayoutMutex = nullptr;
	_Other.LCapture = false;
	_Other.LCaptureMouseX = 0;
	_Other.LCaptureMouseY = 0;
	_Other.LCaptureMouseXLastFrame = 0;
	_Other.LCaptureMouseYLastFrame = 0;
	_Other.LAccumulationX = 0;
	_Other.LAccumulationY = 0;
	_Other.MCapture = false;
	_Other.MCaptureMouseX = 0;
	_Other.MCaptureMouseY = 0;
	_Other.MCaptureMouseXLastFrame = 0;
	_Other.MCaptureMouseYLastFrame = 0;
	_Other.MAccumulationX = 0;
	_Other.MAccumulationY = 0;
	_Other.RCapture = false;
	_Other.RCaptureMouseX = 0;
	_Other.RCaptureMouseY = 0;
	_Other.RCaptureMouseXLastFrame = 0;
	_Other.RCaptureMouseYLastFrame = 0;
	_Other.RAccumulationX = 0;
	_Other.RAccumulationY = 0;
	_Other.X1Capture = false;
	_Other.X1CaptureMouseX = 0;
	_Other.X1CaptureMouseY = 0;
	_Other.X1CaptureMouseXLastFrame = 0;
	_Other.X1CaptureMouseYLastFrame = 0;
	_Other.X1AccumulationX = 0;
	_Other.X1AccumulationY = 0;
	_Other.X2Capture = false;
	_Other.X2CaptureMouseX = 0;
	_Other.X2CaptureMouseY = 0;
	_Other.X2CaptureMouseXLastFrame = 0;
	_Other.X2CaptureMouseYLastFrame = 0;
	_Other.X2AccumulationX = 0;
	_Other.X2AccumulationY = 0;

	return *this;
}



LRESULT CALLBACK BFW_WINDOWS::GUI::MainWindowProc(HWND _hWnd, UINT _Msg, WPARAM _wParam, LPARAM _lParam)
{
	if (BFW::GUI::Window::IsDefaultMessage(_Msg))
	{
		return BFW::GUI::Window::HandleDefaultMessage(_hWnd, _Msg, _wParam, _lParam);
	}

	BFW::GUI::Window& _Wnd = *BFW::GUI::Window::GetWindowPtr(_hWnd);
	WindowData& _WndData = *(WindowData*)(_Wnd.GetUserData());
	PopUpData& _PopUpData = *(PopUpData*)(_WndData.Layout.GetUserData());

	switch (_Msg)
	{
	case WM_ERASEBKGND:
	{
		break;
	}
	case WM_PAINT:
	{
		size_t _Width = 0, _Height = 0;

		if (!_Wnd.GetClientSize(_Width, _Height))
		{
			break;
		}

		PAINTSTRUCT _PaintStruct = { 0 };

		HDC _WndDC = BeginPaint(_hWnd, &_PaintStruct);

		if (!_WndDC)
		{
			break;
		}

		_WndData.LayoutMutex->lock();

		HDC _HandleDC = CreateCompatibleDC(_WndDC);

		if (!_HandleDC)
		{
			_WndData.LayoutMutex->unlock();
			EndPaint(_hWnd, &_PaintStruct);
			break;
		}

		HBITMAP _HandleBmp = CreateCompatibleBitmap(_WndDC, (int32_t)(_PopUpData.Width), (int32_t)(_PopUpData.Height));

		if (!_HandleBmp)
		{
			DeleteDC(_HandleDC);
			_WndData.LayoutMutex->unlock();
			EndPaint(_hWnd, &_PaintStruct);
			break;
		}

		HBITMAP _HandleOld = (HBITMAP)(SelectObject(_HandleDC, _HandleBmp));

		SetBitmapBits(_HandleBmp, (uint32_t)(_PopUpData.Width * _PopUpData.Height * 4), _PopUpData.Pixels);
		StretchBlt(_WndDC, 0, 0, (int32_t)(_Width), (int32_t)(_Height), _HandleDC, (int32_t)(_WndData.Layout.GetScrollX()), (int32_t)(_WndData.Layout.GetScrollY()), (int32_t)(_WndData.Layout.GetWidth()), (int32_t)(_WndData.Layout.GetHeight()), SRCCOPY);

		_WndData.LayoutMutex->unlock();

		SelectObject(_HandleDC, _HandleOld);
		DeleteDC(_HandleDC);
		DeleteObject(_HandleBmp);

		EndPaint(_hWnd, &_PaintStruct);

		break;
	}
	case WM_GETMINMAXINFO:
	{
		uint32_t _Style = GetWindowLong(_hWnd, GWL_STYLE);

		if (!_Style)
		{
			break;
		}

		uint32_t _ExStyle = GetWindowLong(_hWnd, GWL_EXSTYLE);

		RECT _WndRect = { 0 };

		_WndRect.right = MainWindowMinX;
		_WndRect.bottom = MainWindowMinY;

		if (!AdjustWindowRectEx(&_WndRect, _Style, GetMenu(_hWnd) != NULL, _ExStyle))
		{
			break;
		}

		LPMINMAXINFO _MinMaxInfo = (LPMINMAXINFO)(_lParam);

		_MinMaxInfo->ptMinTrackSize.x = _WndRect.right - _WndRect.left;
		_MinMaxInfo->ptMinTrackSize.y = _WndRect.bottom - _WndRect.top;

		break;
	}
	default:
	{
		return DefWindowProc(_hWnd, _Msg, _wParam, _lParam);
	}
	}

	return 0;
}

const bool BFW_WINDOWS::GUI::MainWindowThreadInit(void* _UserData)
{
	return true;
}

void BFW_WINDOWS::GUI::MainWindowThreadCleanUp(void* _UserData)
{

}

const bool BFW_WINDOWS::GUI::MainWindowInit(BFW::GUI::Window* _Wnd)
{
	WindowData& _WndData = *(WindowData*)(_Wnd->GetUserData());

	_WndData.LayoutMutex = new std::mutex;

	if (!_WndData.LayoutMutex)
	{
		return false;
	}

	BFW_HEAP_PROFILE_PUSH(sizeof(std::mutex), _WndData.LayoutMutex);

	PopUpData* _PopUpData = new PopUpData;

	if (!_PopUpData)
	{
		BFW_HEAP_PROFILE_POP(_WndData.LayoutMutex);
		delete _WndData.LayoutMutex;
		_WndData.LayoutMutex = nullptr;
		return false;
	}

	BFW_HEAP_PROFILE_PUSH(sizeof(PopUpData), _PopUpData);

	_WndData.Layout.SetUserData(_PopUpData);

	size_t _WndWidth = 0, _WndHeight = 0;

	_Wnd->GetClientSize(_WndWidth, _WndHeight);

	if (_WndWidth == 0 || _WndHeight == 0)
	{
		_WndWidth = MainWindowMinX;
		_WndHeight = MainWindowMinY;
	}

	_PopUpData->Width = _WndWidth;
	_PopUpData->Height = _WndHeight;
	_PopUpData->Pixels = new uint8_t[_PopUpData->Width * _PopUpData->Height * 4];
	_PopUpData->Wnd = _Wnd;

	if (!_PopUpData->Pixels)
	{
		BFW_HEAP_PROFILE_POP(_WndData.LayoutMutex);
		delete _WndData.LayoutMutex;
		_WndData.LayoutMutex = nullptr;
		BFW_HEAP_PROFILE_POP(_WndData.Layout.GetUserData());
		delete _WndData.Layout.GetUserData();
		_WndData.Layout.SetUserData(nullptr);
		return false;
	}

	BFW_HEAP_PROFILE_PUSH(sizeof(uint8_t) * _PopUpData->Width * _PopUpData->Height * 4, _PopUpData->Pixels);

	for (size_t _Y = 0; _Y < _PopUpData->Height; _Y++)
	{
		for (size_t _X = 0; _X < _PopUpData->Width; _X++)
		{
			_PopUpData->Pixels[(_X + _Y * _PopUpData->Width) * 4 + 0] = 0;
			_PopUpData->Pixels[(_X + _Y * _PopUpData->Width) * 4 + 1] = 0;
			_PopUpData->Pixels[(_X + _Y * _PopUpData->Width) * 4 + 2] = 0;
			_PopUpData->Pixels[(_X + _Y * _PopUpData->Width) * 4 + 3] = 255;
		}
	}

	return true;
}

void BFW_WINDOWS::GUI::MainWindowCleanUp(BFW::GUI::Window* _Wnd)
{
	WindowData& _WndData = *(WindowData*)(_Wnd->GetUserData());
	PopUpData* _PopUpData = (PopUpData*)(_WndData.Layout.GetUserData());

	BFW_HEAP_PROFILE_POP(_WndData.LayoutMutex);
	delete _WndData.LayoutMutex;
	_WndData.LayoutMutex = nullptr;
	BFW_HEAP_PROFILE_POP(_PopUpData->Pixels);
	delete[] _PopUpData->Pixels;
	_PopUpData->Pixels = nullptr;
	BFW_HEAP_PROFILE_POP(_WndData.Layout.GetUserData());
	delete _WndData.Layout.GetUserData();
	_WndData.Layout.SetUserData(nullptr);
}



LRESULT CALLBACK BFW_WINDOWS::GUI::ChildWindowProc(HWND _hWnd, UINT _Msg, WPARAM _wParam, LPARAM _lParam)
{
	if (BFW::GUI::Window::IsDefaultMessage(_Msg))
	{
		return BFW::GUI::Window::HandleDefaultMessage(_hWnd, _Msg, _wParam, _lParam);
	}

	BFW::GUI::Window& _Wnd = *BFW::GUI::Window::GetWindowPtr(_hWnd);
	WindowData& _WndData = *(WindowData*)(_Wnd.GetUserData());
	PopUpData& _PopUpData = *(PopUpData*)(_WndData.Layout.GetUserData());

	switch (_Msg)
	{
	case WM_ERASEBKGND:
	{
		break;
	}
	case WM_PAINT:
	{
		size_t _Width = 0, _Height = 0;

		if (!_Wnd.GetClientSize(_Width, _Height))
		{
			break;
		}

		PAINTSTRUCT _PaintStruct = { 0 };

		HDC _WndDC = BeginPaint(_hWnd, &_PaintStruct);

		if (!_WndDC)
		{
			break;
		}

		_WndData.LayoutMutex->lock();

		HDC _HandleDC = CreateCompatibleDC(_WndDC);

		if (!_HandleDC)
		{
			_WndData.LayoutMutex->unlock();
			EndPaint(_hWnd, &_PaintStruct);
			break;
		}

		HBITMAP _HandleBmp = CreateCompatibleBitmap(_WndDC, (int32_t)(_PopUpData.Width), (int32_t)(_PopUpData.Height));

		if (!_HandleBmp)
		{
			DeleteDC(_HandleDC);
			_WndData.LayoutMutex->unlock();
			EndPaint(_hWnd, &_PaintStruct);
			break;
		}

		HBITMAP _HandleOld = (HBITMAP)(SelectObject(_HandleDC, _HandleBmp));

		SetBitmapBits(_HandleBmp, (uint32_t)(_PopUpData.Width * _PopUpData.Height * 4), _PopUpData.Pixels);
		StretchBlt(_WndDC, 0, 0, (int32_t)(_Width), (int32_t)(_Height), _HandleDC, (int32_t)(_WndData.Layout.GetScrollX()), (int32_t)(_WndData.Layout.GetScrollY()), (int32_t)(_WndData.Layout.GetWidth()), (int32_t)(_WndData.Layout.GetHeight()), SRCCOPY);

		_WndData.LayoutMutex->unlock();

		SelectObject(_HandleDC, _HandleOld);
		DeleteDC(_HandleDC);
		DeleteObject(_HandleBmp);

		EndPaint(_hWnd, &_PaintStruct);

		break;
	}
	case WM_GETMINMAXINFO:
	{
		uint32_t _Style = GetWindowLong(_hWnd, GWL_STYLE);

		if (!_Style)
		{
			break;
		}

		uint32_t _ExStyle = GetWindowLong(_hWnd, GWL_EXSTYLE);

		RECT _WndRect = { 0 };

		_WndRect.right = ChildWindowMinX;
		_WndRect.bottom = ChildWindowMinY;

		if (!AdjustWindowRectEx(&_WndRect, _Style, GetMenu(_hWnd) != NULL, _ExStyle))
		{
			break;
		}

		LPMINMAXINFO _MinMaxInfo = (LPMINMAXINFO)(_lParam);

		_MinMaxInfo->ptMinTrackSize.x = _WndRect.right - _WndRect.left;
		_MinMaxInfo->ptMinTrackSize.y = _WndRect.bottom - _WndRect.top;

		break;
	}
	case WM_NCHITTEST:
	{
		LRESULT _Result = DefWindowProc(_hWnd, _Msg, _wParam, _lParam);

		if (_Result != HTCLIENT)
		{
			return _Result;
		}

		POINT _Cursor = { 0 };

		_Cursor.x = (int16_t)(LOWORD(_lParam));
		_Cursor.y = (int16_t)(HIWORD(_lParam));

		if (!ScreenToClient(_hWnd, &_Cursor))
		{
			break;
		}

		size_t _Width = 0, _Height = 0;

		if (_Wnd.GetClientSize(_Width, _Height))
		{
			if (_Cursor.x >= (int32_t)(_Width - ResizeSize) * (_Width > ResizeSize) && _Cursor.x < (int32_t)(_Width) && _Cursor.y >= (int32_t)(_Height - ResizeSize) * (_Height > ResizeSize) && _Cursor.y < (int32_t)(_Height))
			{
				return HTBOTTOMRIGHT;
			}

			if (_Cursor.x >= (int32_t)(_Width - ResizeSize) * (_Width > ResizeSize) && _Cursor.x < (int32_t)(_Width) && _Cursor.y >= 0 && _Cursor.y < (int32_t)(ResizeSize))
			{
				return HTTOPRIGHT;
			}

			if (_Cursor.x >= 0 && _Cursor.x < (int32_t)(ResizeSize) && _Cursor.y >= (int32_t)(_Height - ResizeSize) * (_Height > ResizeSize) && _Cursor.y < (int32_t)(_Height))
			{
				return HTBOTTOMLEFT;
			}

			if (_Cursor.x >= 0 && _Cursor.x < (int32_t)(ResizeSize) && _Cursor.y >= 0 && _Cursor.y < (int32_t)(ResizeSize))
			{
				return HTTOPLEFT;
			}

			if (_Cursor.x >= (int32_t)(ResizeSize) && _Cursor.x < (int32_t)(_Width - ResizeSize) * (_Width > ResizeSize) && _Cursor.y >= (int32_t)(_Height - ResizeSize) * (_Height > ResizeSize) && _Cursor.y < (int32_t)(_Height))
			{
				return HTBOTTOM;
			}

			if (_Cursor.x >= (int32_t)(ResizeSize) && _Cursor.x < (int32_t)(_Width - ResizeSize) * (_Width > ResizeSize) && _Cursor.y >= 0 && _Cursor.y < (int32_t)(ResizeSize))
			{
				return HTTOP;
			}

			if (_Cursor.x >= (int32_t)(_Width - ResizeSize) * (_Width > ResizeSize) && _Cursor.x < (int32_t)(_Width) && _Cursor.y >= (int32_t)(ResizeSize) && _Cursor.y < (int32_t)(_Height - ResizeSize) * (_Height > ResizeSize))
			{
				return HTRIGHT;
			}

			if (_Cursor.x >= 0 && _Cursor.x < (int32_t)(ResizeSize) && _Cursor.y >= (int32_t)(ResizeSize) && _Cursor.y < (int32_t)(_Height - ResizeSize) * (_Height > ResizeSize))
			{
				return HTLEFT;
			}
		}

		_WndData.LayoutMutex->lock();

		BFW::GUI::SafePopUpPointer _HoverPopUp = _WndData.Layout.GetChildFromMouse(_Cursor.x, _Cursor.y);

		if (_HoverPopUp)
		{
			switch (_HoverPopUp->GetId())
			{
			case _DebugWindowPopUpId:
			{
				_Result = HTCAPTION;
				break;
			}
			case BFW::GUI::_NodeWindowPopUpId:
			{
				_Result = HTCAPTION;
				break;
			}
			default:
			{
				break;
			}
			}
		}

		_WndData.LayoutMutex->unlock();

		return _Result;
	}
	default:
	{
		return DefWindowProc(_hWnd, _Msg, _wParam, _lParam);
	}
	}

	return 0;
}

const bool BFW_WINDOWS::GUI::ChildWindowThreadInit(void* _UserData)
{
	return true;
}

void BFW_WINDOWS::GUI::ChildWindowThreadCleanUp(void* _UserData)
{

}

const bool BFW_WINDOWS::GUI::ChildWindowInit(BFW::GUI::Window* _Wnd)
{
	WindowData& _WndData = *(WindowData*)(_Wnd->GetUserData());

	_WndData.LayoutMutex = new std::mutex;

	if (!_WndData.LayoutMutex)
	{
		return false;
	}

	BFW_HEAP_PROFILE_PUSH(sizeof(std::mutex), _WndData.LayoutMutex);

	PopUpData* _PopUpData = new PopUpData;

	if (!_PopUpData)
	{
		BFW_HEAP_PROFILE_POP(_WndData.LayoutMutex);
		delete _WndData.LayoutMutex;
		_WndData.LayoutMutex = nullptr;
		return false;
	}

	BFW_HEAP_PROFILE_PUSH(sizeof(PopUpData), _PopUpData);

	_WndData.Layout.SetUserData(_PopUpData);

	size_t _WndWidth = 0, _WndHeight = 0;

	_Wnd->GetClientSize(_WndWidth, _WndHeight);

	if (_WndWidth == 0 || _WndHeight == 0)
	{
		_WndWidth = ChildWindowMinX;
		_WndHeight = ChildWindowMinY;
	}

	_PopUpData->Width = _WndWidth;
	_PopUpData->Height = _WndHeight;
	_PopUpData->Pixels = new uint8_t[_PopUpData->Width * _PopUpData->Height * 4];
	_PopUpData->Wnd = _Wnd;

	if (!_PopUpData->Pixels)
	{
		BFW_HEAP_PROFILE_POP(_WndData.LayoutMutex);
		delete _WndData.LayoutMutex;
		_WndData.LayoutMutex = nullptr;
		BFW_HEAP_PROFILE_POP(_WndData.Layout.GetUserData());
		delete _WndData.Layout.GetUserData();
		_WndData.Layout.SetUserData(nullptr);
		return false;
	}

	BFW_HEAP_PROFILE_PUSH(sizeof(uint8_t) * _PopUpData->Width * _PopUpData->Height * 4, _PopUpData->Pixels);

	for (size_t _Y = 0; _Y < _PopUpData->Height; _Y++)
	{
		for (size_t _X = 0; _X < _PopUpData->Width; _X++)
		{
			_PopUpData->Pixels[(_X + _Y * _PopUpData->Width) * 4 + 0] = 0;
			_PopUpData->Pixels[(_X + _Y * _PopUpData->Width) * 4 + 1] = 0;
			_PopUpData->Pixels[(_X + _Y * _PopUpData->Width) * 4 + 2] = 0;
			_PopUpData->Pixels[(_X + _Y * _PopUpData->Width) * 4 + 3] = 255;
		}
	}

	return true;
}

void BFW_WINDOWS::GUI::ChildWindowCleanUp(BFW::GUI::Window* _Wnd)
{
	WindowData& _WndData = *(WindowData*)(_Wnd->GetUserData());
	PopUpData* _PopUpData = (PopUpData*)(_WndData.Layout.GetUserData());

	BFW_HEAP_PROFILE_POP(_WndData.LayoutMutex);
	delete _WndData.LayoutMutex;
	_WndData.LayoutMutex = nullptr;
	BFW_HEAP_PROFILE_POP(_PopUpData->Pixels);
	delete[] _PopUpData->Pixels;
	_PopUpData->Pixels = nullptr;
	BFW_HEAP_PROFILE_POP(_WndData.Layout.GetUserData());
	delete _WndData.Layout.GetUserData();
	_WndData.Layout.SetUserData(nullptr);
}



void* BFW_WINDOWS::GUI::GenerateUserData(BFW::GUI::PopUp& _Parent, const uint64_t _PopUpId, void* _Global)
{
	return nullptr;
}

void BFW_WINDOWS::GUI::ReleaseUserData(BFW::GUI::PopUp& _Wnd, void* _Global)
{

}

void BFW_WINDOWS::GUI::SetupRenderData(BFW::GUI::PopUp& _Wnd, BFW::GUI::PopUp& _Parent, void* _Global)
{
	if (_Wnd.GetTrueWidth() == 0 || _Wnd.GetTrueHeight() == 0 || _Parent.GetUserData() == nullptr)
	{
		return;
	}

	PopUpData& _ParentPopUpData = *(PopUpData*)(_Parent.GetUserData());

	PopUpData* _WndPopUpData = new PopUpData;

	if (!_WndPopUpData)
	{
		return;
	}

	BFW_HEAP_PROFILE_PUSH(sizeof(PopUpData), _WndPopUpData);

	_WndPopUpData->Width = _Wnd.GetTrueWidth();
	_WndPopUpData->Height = _Wnd.GetTrueHeight();
	_WndPopUpData->Pixels = new uint8_t[_WndPopUpData->Width * _WndPopUpData->Height * 4];
	_WndPopUpData->Wnd = _ParentPopUpData.Wnd;

	if (!_WndPopUpData->Pixels)
	{
		BFW_HEAP_PROFILE_POP(_WndPopUpData);
		delete _WndPopUpData;
		return;
	}

	BFW_HEAP_PROFILE_PUSH(sizeof(uint8_t) * _WndPopUpData->Width * _WndPopUpData->Height * 4, _WndPopUpData->Pixels);

	for (size_t _Y = 0; _Y < _WndPopUpData->Height; _Y++)
	{
		for (size_t _X = 0; _X < _WndPopUpData->Width; _X++)
		{
			_WndPopUpData->Pixels[(_X + _Y * _WndPopUpData->Width) * 4 + 0] = 0;
			_WndPopUpData->Pixels[(_X + _Y * _WndPopUpData->Width) * 4 + 1] = 0;
			_WndPopUpData->Pixels[(_X + _Y * _WndPopUpData->Width) * 4 + 2] = 0;
			_WndPopUpData->Pixels[(_X + _Y * _WndPopUpData->Width) * 4 + 3] = 255;
		}
	}

	_Wnd.SetUserData(_WndPopUpData);
}

void BFW_WINDOWS::GUI::CleanUpRenderData(BFW::GUI::PopUp& _Wnd, void* _Global)
{
	if (!_Wnd.GetUserData())
	{
		return;
	}

	PopUpData& _WndPopUpData = *(PopUpData*)(_Wnd.GetUserData());

	BFW_HEAP_PROFILE_POP(_WndPopUpData.Pixels);
	delete[] _WndPopUpData.Pixels;
	BFW_HEAP_PROFILE_POP(_Wnd.GetUserData());
	delete _Wnd.GetUserData();
	_Wnd.SetUserData(nullptr);
}

void BFW_WINDOWS::GUI::RenderGray25(BFW::GUI::PopUp& _Wnd, void* _Global)
{
	if (!_Wnd.GetUserData())
	{
		return;
	}

	PopUpData& _WndPopUpData = *(PopUpData*)(_Wnd.GetUserData());

	for (size_t _Y = 0; _Y < _WndPopUpData.Height; _Y++)
	{
		for (size_t _X = 0; _X < _WndPopUpData.Width; _X++)
		{
			_WndPopUpData.Pixels[(_X + _Y * _WndPopUpData.Width) * 4 + 0] = 25;
			_WndPopUpData.Pixels[(_X + _Y * _WndPopUpData.Width) * 4 + 1] = 25;
			_WndPopUpData.Pixels[(_X + _Y * _WndPopUpData.Width) * 4 + 2] = 25;
			_WndPopUpData.Pixels[(_X + _Y * _WndPopUpData.Width) * 4 + 3] = 255;
		}
	}
}

void BFW_WINDOWS::GUI::RenderGray30(BFW::GUI::PopUp& _Wnd, void* _Global)
{
	if (!_Wnd.GetUserData())
	{
		return;
	}

	PopUpData& _WndPopUpData = *(PopUpData*)(_Wnd.GetUserData());

	for (size_t _Y = 0; _Y < _WndPopUpData.Height; _Y++)
	{
		for (size_t _X = 0; _X < _WndPopUpData.Width; _X++)
		{
			_WndPopUpData.Pixels[(_X + _Y * _WndPopUpData.Width) * 4 + 0] = 30;
			_WndPopUpData.Pixels[(_X + _Y * _WndPopUpData.Width) * 4 + 1] = 30;
			_WndPopUpData.Pixels[(_X + _Y * _WndPopUpData.Width) * 4 + 2] = 30;
			_WndPopUpData.Pixels[(_X + _Y * _WndPopUpData.Width) * 4 + 3] = 255;
		}
	}
}

void BFW_WINDOWS::GUI::RenderGray40(BFW::GUI::PopUp& _Wnd, void* _Global)
{
	if (!_Wnd.GetUserData())
	{
		return;
	}

	PopUpData& _WndPopUpData = *(PopUpData*)(_Wnd.GetUserData());

	for (size_t _Y = 0; _Y < _WndPopUpData.Height; _Y++)
	{
		for (size_t _X = 0; _X < _WndPopUpData.Width; _X++)
		{
			_WndPopUpData.Pixels[(_X + _Y * _WndPopUpData.Width) * 4 + 0] = 40;
			_WndPopUpData.Pixels[(_X + _Y * _WndPopUpData.Width) * 4 + 1] = 40;
			_WndPopUpData.Pixels[(_X + _Y * _WndPopUpData.Width) * 4 + 2] = 40;
			_WndPopUpData.Pixels[(_X + _Y * _WndPopUpData.Width) * 4 + 3] = 255;
		}
	}
}

void BFW_WINDOWS::GUI::Composit(BFW::GUI::PopUp& _Parent, BFW::GUI::PopUp& _Child, void* _Global)
{
	if (!_Parent.GetUserData() || !_Child.GetUserData())
	{
		return;
	}

	PopUpData& _ParentPopUpData = *(PopUpData*)(_Parent.GetUserData());
	PopUpData& _ChildPopUpData = *(PopUpData*)(_Child.GetUserData());

	size_t _Width = _Child.GetWidth();
	size_t _Height = _Child.GetHeight();
	intptr_t _PositionX = _Child.GetPositionX();
	intptr_t _PositionY = _Child.GetPositionY();
	size_t _ScrollX = _Child.GetScrollX();
	size_t _ScrollY = _Child.GetScrollY();
	size_t _StartX = _PositionX * (_PositionX > 0);
	size_t _StartY = _PositionY * (_PositionY > 0);
	size_t _EndX = _ParentPopUpData.Width * (_ParentPopUpData.Width <= _PositionX + _Width) + (_PositionX + _Width) * (_ParentPopUpData.Width > _PositionX + _Width);
	size_t _EndY = _ParentPopUpData.Height * (_ParentPopUpData.Height <= _PositionY + _Height) + (_PositionY + _Height) * (_ParentPopUpData.Height > _PositionY + _Height);

#ifdef BFW_WINDOWS_ENABLE_ALPHA

	for (size_t _Y = _StartY; _Y < _EndY; _Y++)
	{
		for (size_t _X = _StartX; _X < _EndX; _X++)
		{
			_ParentPopUpData.Pixels[(_X + _Y * _ParentPopUpData.Width) * 4 + 0] = (uint8_t)(BFW::Math::Mix(_ParentPopUpData.Pixels[(_X + _Y * _ParentPopUpData.Width) * 4 + 0], _ChildPopUpData.Pixels[(_X - _PositionX + _ScrollX + (_Y - _PositionY + _ScrollY) * _ChildPopUpData.Width) * 4 + 0], (float)(_ChildPopUpData.Pixels[(_X - _PositionX + _ScrollX + (_Y - _PositionY + _ScrollY) * _ChildPopUpData.Width) * 4 + 3]) / 255.0f));
			_ParentPopUpData.Pixels[(_X + _Y * _ParentPopUpData.Width) * 4 + 1] = (uint8_t)(BFW::Math::Mix(_ParentPopUpData.Pixels[(_X + _Y * _ParentPopUpData.Width) * 4 + 1], _ChildPopUpData.Pixels[(_X - _PositionX + _ScrollX + (_Y - _PositionY + _ScrollY) * _ChildPopUpData.Width) * 4 + 1], (float)(_ChildPopUpData.Pixels[(_X - _PositionX + _ScrollX + (_Y - _PositionY + _ScrollY) * _ChildPopUpData.Width) * 4 + 3]) / 255.0f));
			_ParentPopUpData.Pixels[(_X + _Y * _ParentPopUpData.Width) * 4 + 2] = (uint8_t)(BFW::Math::Mix(_ParentPopUpData.Pixels[(_X + _Y * _ParentPopUpData.Width) * 4 + 2], _ChildPopUpData.Pixels[(_X - _PositionX + _ScrollX + (_Y - _PositionY + _ScrollY) * _ChildPopUpData.Width) * 4 + 2], (float)(_ChildPopUpData.Pixels[(_X - _PositionX + _ScrollX + (_Y - _PositionY + _ScrollY) * _ChildPopUpData.Width) * 4 + 3]) / 255.0f));
		}
	}

#endif

#ifndef BFW_WINDOWS_ENABLE_ALPHA

	for (size_t _Y = _StartY; _Y < _EndY; _Y++)
	{
		for (size_t _X = _StartX; _X < _EndX; _X++)
		{
			_ParentPopUpData.Pixels[(_X + _Y * _ParentPopUpData.Width) * 4 + 0] = _ChildPopUpData.Pixels[(_X - _PositionX + _ScrollX + (_Y - _PositionY + _ScrollY) * _ChildPopUpData.Width) * 4 + 0];
			_ParentPopUpData.Pixels[(_X + _Y * _ParentPopUpData.Width) * 4 + 1] = _ChildPopUpData.Pixels[(_X - _PositionX + _ScrollX + (_Y - _PositionY + _ScrollY) * _ChildPopUpData.Width) * 4 + 1];
			_ParentPopUpData.Pixels[(_X + _Y * _ParentPopUpData.Width) * 4 + 2] = _ChildPopUpData.Pixels[(_X - _PositionX + _ScrollX + (_Y - _PositionY + _ScrollY) * _ChildPopUpData.Width) * 4 + 2];
		}
	}

#endif
}



const size_t BFW_WINDOWS::GUI::GetMinX(const uint64_t _PopUpId)
{
	size_t _Min = 0;

	switch (_PopUpId)
	{
	case _DebugWindowPopUpId:
	{
		_Min = DebugWindowMinX;
		break;
	}
	default:
	{
		break;
	}
	}

	return _Min;
}

const size_t BFW_WINDOWS::GUI::GetMinY(const uint64_t _PopUpId)
{
	size_t _Min = 0;

	switch (_PopUpId)
	{
	case _DebugWindowPopUpId:
	{
		_Min = DebugWindowMinY;
		break;
	}
	default:
	{
		break;
	}
	}

	return _Min;
}

const bool BFW_WINDOWS::GUI::ForceHScroll(const uint64_t _PopUpId)
{
	bool _Force = false;

	switch (_PopUpId)
	{
	case BFW::GUI::_NodeWindowPopUpId:
	{
		break;
	}
	default:
	{
		break;
	}
	}

	return _Force;
}

const bool BFW_WINDOWS::GUI::ForceVScroll(const uint64_t _PopUpId)
{
	bool _Force = false;

	switch (_PopUpId)
	{
	case BFW::GUI::_NodeWindowPopUpId:
	{
		break;
	}
	default:
	{
		break;
	}
	}

	return _Force;
}

const bool BFW_WINDOWS::GUI::IgnoreHScroll(const uint64_t _PopUpId)
{
	return false;
}

const bool BFW_WINDOWS::GUI::IgnoreVScroll(const uint64_t _PopUpId)
{
	return false;
}



const bool BFW_WINDOWS::GUI::FindScrollableWindow(size_t& _Index, const BFW::Vector<BFW::GUI::SafePopUpPointer>& _Path)
{
	_Index = 0;

	if (!BFW::GUI::PopUp::IsValidPath(_Path))
	{
		return false;
	}

	while (_Index < _Path.GetSize())
	{
		switch (_Path[_Index]->GetId())
		{
		case _DebugWindowPopUpId:
		{
			return true;
		}
		default:
		{
			break;
		}
		}

		_Index++;
	}

	_Index = 0;

	return false;
}

const bool BFW_WINDOWS::GUI::FindScrollableWindow(size_t& _Index, const BFW::Vector<const BFW::GUI::SafePopUpPointer>& _Path)
{
	_Index = 0;

	if (!BFW::GUI::PopUp::IsValidPath(_Path))
	{
		return false;
	}

	while (_Index < _Path.GetSize())
	{
		switch (_Path[_Index]->GetId())
		{
		case _DebugWindowPopUpId:
		{
			return true;
		}
		default:
		{
			break;
		}
		}

		_Index++;
	}

	_Index = 0;

	return false;
}

void BFW_WINDOWS::GUI::ResizePopUpLayer(BFW::GUI::PopUp& _Parent, const size_t _Layer, const BFW::GUI::GetMinFnc _GetMinX, const BFW::GUI::GetMinFnc _GetMinY, const size_t _ResizeSize, const BFW::GUI::ForceScrollFnc _ForceHScroll, const BFW::GUI::ForceScrollFnc _ForceVScroll, const size_t _ScrollSize, const size_t _ScrollTopPadding, const size_t _ScrollPadding, const BFW::GUI::SetupRenderDataFnc _SetupData, const BFW::GUI::CleanUpRenderDataFnc _CleanUpData, const BFW::GUI::RenderFnc _RenderBottomWindow, const BFW::GUI::RenderFnc _RenderMiddleWindow, const BFW::GUI::RenderFnc _RenderTopWindow, const BFW::GUI::RenderFnc _RenderBottomButton, const BFW::GUI::RenderFnc _RenderMiddleButton, const BFW::GUI::RenderFnc _RenderTopButton, const BFW::GUI::CompositFnc _Composit, const BFW::GUI::GenerateUserDataFnc _GenerateUserData, const BFW::GUI::ReleaseUserDataFnc _ReleaseUserData, void* _Global)
{
	for (size_t _Index = 0; _Index < _Parent.GetPopUps()[_Layer].GetSize(); _Index++)
	{
		BFW::GUI::PopUp& _PopUp = _Parent.GetPopUps()[_Layer][_Index];

		switch (_PopUp.GetId())
		{
		case _DebugWindowPopUpId:
		{
			_PopUp.ResizeChilds(ResizePopUpLayer, _GetMinX, _GetMinY, _ResizeSize, _ForceHScroll, _ForceVScroll, _ScrollSize, _ScrollTopPadding, _ScrollPadding, _SetupData, _CleanUpData, _RenderBottomWindow, _RenderMiddleWindow, _RenderTopWindow, _RenderBottomButton, _RenderMiddleButton, _RenderTopButton, _Composit, _GenerateUserData, _ReleaseUserData, _Global);

			break;
		}
		case _SpawnButtonPopUpId:
		{
			_PopUp.SetWidth(_Parent.GetTrueWidth() - Padding * 2);

			break;
		}
		default:
		{
			break;
		}
		}
	}
}

void BFW_WINDOWS::GUI::RenderCursor(BFW::GUI::Window& _Wnd, const uint64_t _PopUpId)
{
	HCURSOR _Cursor = NULL;

	switch (_PopUpId)
	{
	case _SpawnButtonPopUpId:
	{
		_Cursor = LoadCursor(NULL, IDC_HAND);
		break;
	}
	case BFW::GUI::_LeftResizePopUpId:
	{
		_Cursor = LoadCursor(NULL, IDC_SIZEWE);
		break;
	}
	case BFW::GUI::_RightResizePopUpId:
	{
		_Cursor = LoadCursor(NULL, IDC_SIZEWE);
		break;
	}
	case BFW::GUI::_TopResizePopUpId:
	{
		_Cursor = LoadCursor(NULL, IDC_SIZENS);
		break;
	}
	case BFW::GUI::_BottomResizePopUpId:
	{
		_Cursor = LoadCursor(NULL, IDC_SIZENS);
		break;
	}
	case BFW::GUI::_LeftTopResizePopUpId:
	{
		_Cursor = LoadCursor(NULL, IDC_SIZENWSE);
		break;
	}
	case BFW::GUI::_LeftBottomResizePopUpId:
	{
		_Cursor = LoadCursor(NULL, IDC_SIZENESW);
		break;
	}
	case BFW::GUI::_RightTopResizePopUpId:
	{
		_Cursor = LoadCursor(NULL, IDC_SIZENESW);
		break;
	}
	case BFW::GUI::_RightBottomResizePopUpId:
	{
		_Cursor = LoadCursor(NULL, IDC_SIZENWSE);
		break;
	}
	case BFW::GUI::_HScrollWindowPopUpId:
	{
		_Cursor = LoadCursor(NULL, IDC_HAND);
		break;
	}
	case BFW::GUI::_HScrollButtonPopUpId:
	{
		_Cursor = LoadCursor(NULL, IDC_HAND);
		break;
	}
	case BFW::GUI::_VScrollWindowPopUpId:
	{
		_Cursor = LoadCursor(NULL, IDC_HAND);
		break;
	}
	case BFW::GUI::_VScrollButtonPopUpId:
	{
		_Cursor = LoadCursor(NULL, IDC_HAND);
		break;
	}
	default:
	{
		_Cursor = LoadCursor(NULL, IDC_ARROW);
		break;
	}
	}

	_Wnd.SetCursorIcon(_Cursor);
}
