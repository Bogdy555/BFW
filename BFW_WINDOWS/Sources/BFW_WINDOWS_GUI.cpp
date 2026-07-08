#include "../Headers/BFW_WINDOWS.hpp"



const float BFW_WINDOWS::GUI::MouseCaptureScrollSpeed = 30.0f;
const size_t BFW_WINDOWS::GUI::MouseCaptureScrollScale = 10;

const size_t BFW_WINDOWS::GUI::MainWindowMinX = 700;
const size_t BFW_WINDOWS::GUI::MainWindowMinY = 400;
const size_t BFW_WINDOWS::GUI::ChildWindowMinX = 200;
const size_t BFW_WINDOWS::GUI::ChildWindowMinY = 200;

const size_t BFW_WINDOWS::GUI::ResizeSize = 5;
const size_t BFW_WINDOWS::GUI::ScrollSize = 15;
const size_t BFW_WINDOWS::GUI::TopPadding = 45;
const size_t BFW_WINDOWS::GUI::Padding = 30;
const size_t BFW_WINDOWS::GUI::ScrollTopPadding = 25;
const size_t BFW_WINDOWS::GUI::ScrollPadding = 10;

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



BFW_WINDOWS::GUI::WindowData::WindowData() : LayoutMutex(nullptr), Layout(), LCapture(false), LCapturePath(), LCaptureMouseX(0), LCaptureMouseY(0), LCaptureMouseXLastFrame(0), LCaptureMouseYLastFrame(0), ScrollAccumulationX(0), ScrollAccumulationY(0), MCapture(false), MCapturePath(), MCaptureMouseX(0), MCaptureMouseY(0), MCaptureMouseXLastFrame(0), MCaptureMouseYLastFrame(0), RCapture(false), RCapturePath(), RCaptureMouseX(0), RCaptureMouseY(0), RCaptureMouseXLastFrame(0), RCaptureMouseYLastFrame(0), X1Capture(false), X1CapturePath(), X1CaptureMouseX(0), X1CaptureMouseY(0), X1CaptureMouseXLastFrame(0), X1CaptureMouseYLastFrame(0), X2Capture(false), X2CapturePath(), X2CaptureMouseX(0), X2CaptureMouseY(0), X2CaptureMouseXLastFrame(0), X2CaptureMouseYLastFrame(0)
{

}

BFW_WINDOWS::GUI::WindowData::WindowData(WindowData&& _Other) noexcept : LayoutMutex(_Other.LayoutMutex), Layout((BFW::GUI::PopUp&&)(_Other.Layout)), LCapture(_Other.LCapture), LCapturePath((BFW::Vector<BFW::GUI::SafePopUpPointer>)(_Other.LCapturePath)), LCaptureMouseX(_Other.LCaptureMouseX), LCaptureMouseY(_Other.LCaptureMouseY), LCaptureMouseXLastFrame(_Other.LCaptureMouseXLastFrame), LCaptureMouseYLastFrame(_Other.LCaptureMouseYLastFrame), ScrollAccumulationX(_Other.ScrollAccumulationX), ScrollAccumulationY(_Other.ScrollAccumulationY), MCapture(_Other.MCapture), MCapturePath((BFW::Vector<BFW::GUI::SafePopUpPointer>)(_Other.MCapturePath)), MCaptureMouseX(_Other.MCaptureMouseX), MCaptureMouseY(_Other.MCaptureMouseY), MCaptureMouseXLastFrame(_Other.MCaptureMouseXLastFrame), MCaptureMouseYLastFrame(_Other.MCaptureMouseYLastFrame), RCapture(_Other.RCapture), RCapturePath((BFW::Vector<BFW::GUI::SafePopUpPointer>)(_Other.RCapturePath)), RCaptureMouseX(_Other.RCaptureMouseX), RCaptureMouseY(_Other.RCaptureMouseY), RCaptureMouseXLastFrame(_Other.RCaptureMouseXLastFrame), RCaptureMouseYLastFrame(_Other.RCaptureMouseYLastFrame), X1Capture(_Other.X1Capture), X1CapturePath((BFW::Vector<BFW::GUI::SafePopUpPointer>)(_Other.X1CapturePath)), X1CaptureMouseX(_Other.X1CaptureMouseX), X1CaptureMouseY(_Other.X1CaptureMouseY), X1CaptureMouseXLastFrame(_Other.X1CaptureMouseXLastFrame), X1CaptureMouseYLastFrame(_Other.X1CaptureMouseYLastFrame), X2Capture(_Other.X2Capture), X2CapturePath((BFW::Vector<BFW::GUI::SafePopUpPointer>)(_Other.X2CapturePath)), X2CaptureMouseX(_Other.X2CaptureMouseX), X2CaptureMouseY(_Other.X2CaptureMouseY), X2CaptureMouseXLastFrame(_Other.X2CaptureMouseXLastFrame), X2CaptureMouseYLastFrame(_Other.X2CaptureMouseYLastFrame)
{
	_Other.LayoutMutex = nullptr;
	_Other.LCapture = false;
	_Other.LCaptureMouseX = 0;
	_Other.LCaptureMouseY = 0;
	_Other.LCaptureMouseXLastFrame = 0;
	_Other.LCaptureMouseYLastFrame = 0;
	_Other.ScrollAccumulationX = 0;
	_Other.ScrollAccumulationY = 0;
	_Other.MCapture = false;
	_Other.MCaptureMouseX = 0;
	_Other.MCaptureMouseY = 0;
	_Other.MCaptureMouseXLastFrame = 0;
	_Other.MCaptureMouseYLastFrame = 0;
	_Other.RCapture = false;
	_Other.RCaptureMouseX = 0;
	_Other.RCaptureMouseY = 0;
	_Other.RCaptureMouseXLastFrame = 0;
	_Other.RCaptureMouseYLastFrame = 0;
	_Other.X1Capture = false;
	_Other.X1CaptureMouseX = 0;
	_Other.X1CaptureMouseY = 0;
	_Other.X1CaptureMouseXLastFrame = 0;
	_Other.X1CaptureMouseYLastFrame = 0;
	_Other.X2Capture = false;
	_Other.X2CaptureMouseX = 0;
	_Other.X2CaptureMouseY = 0;
	_Other.X2CaptureMouseXLastFrame = 0;
	_Other.X2CaptureMouseYLastFrame = 0;
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
	LCapturePath = (BFW::Vector<BFW::GUI::SafePopUpPointer>)(_Other.LCapturePath);
	LCaptureMouseX = _Other.LCaptureMouseX;
	LCaptureMouseY = _Other.LCaptureMouseY;
	LCaptureMouseXLastFrame = _Other.LCaptureMouseXLastFrame;
	LCaptureMouseYLastFrame = _Other.LCaptureMouseYLastFrame;
	ScrollAccumulationX = _Other.ScrollAccumulationX;
	ScrollAccumulationY = _Other.ScrollAccumulationY;
	MCapture = _Other.MCapture;
	MCapturePath = (BFW::Vector<BFW::GUI::SafePopUpPointer>)(_Other.MCapturePath);
	MCaptureMouseX = _Other.MCaptureMouseX;
	MCaptureMouseY = _Other.MCaptureMouseY;
	MCaptureMouseXLastFrame = _Other.MCaptureMouseXLastFrame;
	MCaptureMouseYLastFrame = _Other.MCaptureMouseYLastFrame;
	RCapture = _Other.RCapture;
	RCapturePath = (BFW::Vector<BFW::GUI::SafePopUpPointer>)(_Other.RCapturePath);
	RCaptureMouseX = _Other.RCaptureMouseX;
	RCaptureMouseY = _Other.RCaptureMouseY;
	RCaptureMouseXLastFrame = _Other.RCaptureMouseXLastFrame;
	RCaptureMouseYLastFrame = _Other.RCaptureMouseYLastFrame;
	X1Capture = _Other.X1Capture;
	X1CapturePath = (BFW::Vector<BFW::GUI::SafePopUpPointer>)(_Other.X1CapturePath);
	X1CaptureMouseX = _Other.X1CaptureMouseX;
	X1CaptureMouseY = _Other.X1CaptureMouseY;
	X1CaptureMouseXLastFrame = _Other.X1CaptureMouseXLastFrame;
	X1CaptureMouseYLastFrame = _Other.X1CaptureMouseYLastFrame;
	X2Capture = _Other.X2Capture;
	X2CapturePath = (BFW::Vector<BFW::GUI::SafePopUpPointer>)(_Other.X2CapturePath);
	X2CaptureMouseX = _Other.X2CaptureMouseX;
	X2CaptureMouseY = _Other.X2CaptureMouseY;
	X2CaptureMouseXLastFrame = _Other.X2CaptureMouseXLastFrame;
	X2CaptureMouseYLastFrame = _Other.X2CaptureMouseYLastFrame;

	_Other.LayoutMutex = nullptr;
	_Other.LCapture = false;
	_Other.LCaptureMouseX = 0;
	_Other.LCaptureMouseY = 0;
	_Other.LCaptureMouseXLastFrame = 0;
	_Other.LCaptureMouseYLastFrame = 0;
	_Other.ScrollAccumulationX = 0;
	_Other.ScrollAccumulationY = 0;
	_Other.MCapture = false;
	_Other.MCaptureMouseX = 0;
	_Other.MCaptureMouseY = 0;
	_Other.MCaptureMouseXLastFrame = 0;
	_Other.MCaptureMouseYLastFrame = 0;
	_Other.RCapture = false;
	_Other.RCaptureMouseX = 0;
	_Other.RCaptureMouseY = 0;
	_Other.RCaptureMouseXLastFrame = 0;
	_Other.RCaptureMouseYLastFrame = 0;
	_Other.X1Capture = false;
	_Other.X1CaptureMouseX = 0;
	_Other.X1CaptureMouseY = 0;
	_Other.X1CaptureMouseXLastFrame = 0;
	_Other.X1CaptureMouseYLastFrame = 0;
	_Other.X2Capture = false;
	_Other.X2CaptureMouseX = 0;
	_Other.X2CaptureMouseY = 0;
	_Other.X2CaptureMouseXLastFrame = 0;
	_Other.X2CaptureMouseYLastFrame = 0;

	return *this;
}



LRESULT CALLBACK BFW_WINDOWS::GUI::MainWindowProc(HWND _hWnd, UINT _Msg, WPARAM _wParam, LPARAM _lParam)
{
	if (BFW::GUI::Window::IsDefaultMessage(_Msg))
	{
		return BFW::GUI::Window::HandleDefaultMessage(_hWnd, _Msg, _wParam, _lParam);
	}

	BFW::GUI::Window& _Wnd = *BFW::GUI::Window::GetWindowPtr(_hWnd);
	WindowData& _WndUserData = *(WindowData*)(_Wnd.GetUserData());
	PopUpData& _PopUpData = *(PopUpData*)(_WndUserData.Layout.GetUserData());

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

		_WndUserData.LayoutMutex->lock();

		HDC _HandleDC = CreateCompatibleDC(_WndDC);

		if (!_HandleDC)
		{
			_WndUserData.LayoutMutex->unlock();
			EndPaint(_hWnd, &_PaintStruct);
			break;
		}

		HBITMAP _HandleBmp = CreateCompatibleBitmap(_WndDC, (int32_t)(_PopUpData.Width), (int32_t)(_PopUpData.Height));

		if (!_HandleBmp)
		{
			DeleteDC(_HandleDC);
			_WndUserData.LayoutMutex->unlock();
			EndPaint(_hWnd, &_PaintStruct);
			break;
		}

		HBITMAP _HandleOld = (HBITMAP)(SelectObject(_HandleDC, _HandleBmp));

		SetBitmapBits(_HandleBmp, (uint32_t)(_PopUpData.Width * _PopUpData.Height * 4), _PopUpData.Pixels);
		StretchBlt(_WndDC, 0, 0, (int32_t)(_Width), (int32_t)(_Height), _HandleDC, (int32_t)(_WndUserData.Layout.GetScrollX()), (int32_t)(_WndUserData.Layout.GetScrollY()), (int32_t)(_WndUserData.Layout.GetWidth()), (int32_t)(_WndUserData.Layout.GetHeight()), SRCCOPY);

		_WndUserData.LayoutMutex->unlock();

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

		RECT _WindowRect = { 0 };

		_WindowRect.right = MainWindowMinX;
		_WindowRect.bottom = MainWindowMinY;

		if (!AdjustWindowRectEx(&_WindowRect, _Style, GetMenu(_hWnd) != NULL, _ExStyle))
		{
			break;
		}

		LPMINMAXINFO _MinMaxInfo = (LPMINMAXINFO)(_lParam);

		_MinMaxInfo->ptMinTrackSize.x = _WindowRect.right - _WindowRect.left;
		_MinMaxInfo->ptMinTrackSize.y = _WindowRect.bottom - _WindowRect.top;

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
	WindowData& _WndUserData = *(WindowData*)(_Wnd->GetUserData());

	_WndUserData.LayoutMutex = new std::mutex;

	if (!_WndUserData.LayoutMutex)
	{
		return false;
	}

	BFW_HEAP_PROFILE_PUSH(sizeof(std::mutex), _WndUserData.LayoutMutex);

	PopUpData* _PopUpData = new PopUpData;

	if (!_PopUpData)
	{
		BFW_HEAP_PROFILE_POP(_WndUserData.LayoutMutex);
		delete _WndUserData.LayoutMutex;
		_WndUserData.LayoutMutex = nullptr;
		return false;
	}

	BFW_HEAP_PROFILE_PUSH(sizeof(PopUpData), _PopUpData);

	_WndUserData.Layout.SetUserData(_PopUpData);

	_PopUpData->Width = MainWindowMinX;
	_PopUpData->Height = MainWindowMinY;
	_PopUpData->Pixels = new uint8_t[_PopUpData->Width * _PopUpData->Height * 4];
	_PopUpData->Wnd = _Wnd;

	if (!_PopUpData->Pixels)
	{
		BFW_HEAP_PROFILE_POP(_WndUserData.LayoutMutex);
		delete _WndUserData.LayoutMutex;
		_WndUserData.LayoutMutex = nullptr;
		BFW_HEAP_PROFILE_POP(_WndUserData.Layout.GetUserData());
		delete _WndUserData.Layout.GetUserData();
		_WndUserData.Layout.SetUserData(nullptr);
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
			_PopUpData->Pixels[(_X + _Y * _PopUpData->Width) * 4 + 3] = 0;
		}
	}

	return true;
}

void BFW_WINDOWS::GUI::MainWindowCleanUp(BFW::GUI::Window* _Wnd)
{
	WindowData& _WndUserData = *(WindowData*)(_Wnd->GetUserData());
	PopUpData* _PopUpData = (PopUpData*)(_WndUserData.Layout.GetUserData());

	BFW_HEAP_PROFILE_POP(_WndUserData.LayoutMutex);
	delete _WndUserData.LayoutMutex;
	_WndUserData.LayoutMutex = nullptr;
	BFW_HEAP_PROFILE_POP(_PopUpData->Pixels);
	delete[] _PopUpData->Pixels;
	_PopUpData->Pixels = nullptr;
	BFW_HEAP_PROFILE_POP(_WndUserData.Layout.GetUserData());
	delete _WndUserData.Layout.GetUserData();
	_WndUserData.Layout.SetUserData(nullptr);
}



LRESULT CALLBACK BFW_WINDOWS::GUI::ChildWindowProc(HWND _hWnd, UINT _Msg, WPARAM _wParam, LPARAM _lParam)
{
	if (BFW::GUI::Window::IsDefaultMessage(_Msg))
	{
		return BFW::GUI::Window::HandleDefaultMessage(_hWnd, _Msg, _wParam, _lParam);
	}

	BFW::GUI::Window& _Wnd = *BFW::GUI::Window::GetWindowPtr(_hWnd);
	WindowData& _WndUserData = *(WindowData*)(_Wnd.GetUserData());
	PopUpData& _PopUpData = *(PopUpData*)(_WndUserData.Layout.GetUserData());

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

		_WndUserData.LayoutMutex->lock();

		HDC _HandleDC = CreateCompatibleDC(_WndDC);

		if (!_HandleDC)
		{
			_WndUserData.LayoutMutex->unlock();
			EndPaint(_hWnd, &_PaintStruct);
			break;
		}

		HBITMAP _HandleBmp = CreateCompatibleBitmap(_WndDC, (int32_t)(_PopUpData.Width), (int32_t)(_PopUpData.Height));

		if (!_HandleBmp)
		{
			DeleteDC(_HandleDC);
			_WndUserData.LayoutMutex->unlock();
			EndPaint(_hWnd, &_PaintStruct);
			break;
		}

		HBITMAP _HandleOld = (HBITMAP)(SelectObject(_HandleDC, _HandleBmp));

		SetBitmapBits(_HandleBmp, (uint32_t)(_PopUpData.Width * _PopUpData.Height * 4), _PopUpData.Pixels);
		StretchBlt(_WndDC, 0, 0, (int32_t)(_Width), (int32_t)(_Height), _HandleDC, (int32_t)(_WndUserData.Layout.GetScrollX()), (int32_t)(_WndUserData.Layout.GetScrollY()), (int32_t)(_WndUserData.Layout.GetWidth()), (int32_t)(_WndUserData.Layout.GetHeight()), SRCCOPY);

		_WndUserData.LayoutMutex->unlock();

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

		RECT _WindowRect = { 0 };

		_WindowRect.right = ChildWindowMinX;
		_WindowRect.bottom = ChildWindowMinY;

		if (!AdjustWindowRectEx(&_WindowRect, _Style, GetMenu(_hWnd) != NULL, _ExStyle))
		{
			break;
		}

		LPMINMAXINFO _MinMaxInfo = (LPMINMAXINFO)(_lParam);

		_MinMaxInfo->ptMinTrackSize.x = _WindowRect.right - _WindowRect.left;
		_MinMaxInfo->ptMinTrackSize.y = _WindowRect.bottom - _WindowRect.top;

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
			return _Result;
		}

		size_t _Width = 0, _Height = 0;

		if (_Wnd.GetClientSize(_Width, _Height))
		{
			if (_Cursor.x >= (int32_t)(_Width - ResizeSize) * (_Width > ResizeSize) && _Cursor.x < (int32_t)(_Width) && _Cursor.y >= (int32_t)(_Height - ResizeSize) * (_Height > ResizeSize) && _Cursor.y < (int32_t)(_Height))
			{
				return HTBOTTOMRIGHT;
			}

			if (_Cursor.x >= 0 && _Cursor.x < (int32_t)(ResizeSize) && _Cursor.y >= (int32_t)(_Height - ResizeSize) * (_Height > ResizeSize) && _Cursor.y < (int32_t)(_Height))
			{
				return HTBOTTOMLEFT;
			}

			if (_Cursor.x >= (int32_t)(_Width - ResizeSize) * (_Width > ResizeSize) && _Cursor.x < (int32_t)(_Width) && _Cursor.y >= 0 && _Cursor.y < (int32_t)(ResizeSize))
			{
				return HTTOPRIGHT;
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

		_WndUserData.LayoutMutex->lock();

		BFW::GUI::SafePopUpPointer _HoverPopUp = _WndUserData.Layout.GetChildFromMouse(_Cursor.x, _Cursor.y);

		if (_HoverPopUp)
		{
			switch (_HoverPopUp->GetId())
			{
			case _DebugWindowPopUpId:
			{
				_Result = HTCAPTION;
				break;
			}
			case BFW::GUI::_NodePopUpId:
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

		_WndUserData.LayoutMutex->unlock();

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
	WindowData& _WndUserData = *(WindowData*)(_Wnd->GetUserData());

	_WndUserData.LayoutMutex = new std::mutex;

	if (!_WndUserData.LayoutMutex)
	{
		return false;
	}

	BFW_HEAP_PROFILE_PUSH(sizeof(std::mutex), _WndUserData.LayoutMutex);

	PopUpData* _PopUpData = new PopUpData;

	if (!_PopUpData)
	{
		BFW_HEAP_PROFILE_POP(_WndUserData.LayoutMutex);
		delete _WndUserData.LayoutMutex;
		_WndUserData.LayoutMutex = nullptr;
		return false;
	}

	BFW_HEAP_PROFILE_PUSH(sizeof(PopUpData), _PopUpData);

	_WndUserData.Layout.SetUserData(_PopUpData);

	_PopUpData->Width = ChildWindowMinX;
	_PopUpData->Height = ChildWindowMinX;
	_PopUpData->Pixels = new uint8_t[_PopUpData->Width * _PopUpData->Height * 4];
	_PopUpData->Wnd = _Wnd;

	if (!_PopUpData->Pixels)
	{
		BFW_HEAP_PROFILE_POP(_WndUserData.LayoutMutex);
		delete _WndUserData.LayoutMutex;
		_WndUserData.LayoutMutex = nullptr;
		BFW_HEAP_PROFILE_POP(_WndUserData.Layout.GetUserData());
		delete _WndUserData.Layout.GetUserData();
		_WndUserData.Layout.SetUserData(nullptr);
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
			_PopUpData->Pixels[(_X + _Y * _PopUpData->Width) * 4 + 3] = 0;
		}
	}

	return true;
}

void BFW_WINDOWS::GUI::ChildWindowCleanUp(BFW::GUI::Window* _Wnd)
{
	WindowData& _WndUserData = *(WindowData*)(_Wnd->GetUserData());
	PopUpData* _PopUpData = (PopUpData*)(_WndUserData.Layout.GetUserData());

	BFW_HEAP_PROFILE_POP(_WndUserData.LayoutMutex);
	delete _WndUserData.LayoutMutex;
	_WndUserData.LayoutMutex = nullptr;
	BFW_HEAP_PROFILE_POP(_PopUpData->Pixels);
	delete[] _PopUpData->Pixels;
	_PopUpData->Pixels = nullptr;
	BFW_HEAP_PROFILE_POP(_WndUserData.Layout.GetUserData());
	delete _WndUserData.Layout.GetUserData();
	_WndUserData.Layout.SetUserData(nullptr);
}



void* BFW_WINDOWS::GUI::GenerateUserData(BFW::GUI::PopUp& _ParentWnd, void* _Global)
{
	return nullptr;
}

void BFW_WINDOWS::GUI::ReleaseUserData(BFW::GUI::PopUp& _Wnd, void* _Global)
{

}

void BFW_WINDOWS::GUI::SetupRenderData(BFW::GUI::PopUp& _Wnd, BFW::GUI::PopUp& _ParentWnd, void* _Global)
{
	PopUpData& _ParentWndPopUpData = *(PopUpData*)(_ParentWnd.GetUserData());

	if (_Wnd.GetTrueWidth() == 0 || _Wnd.GetTrueHeight() == 0 || _ParentWnd.GetUserData() == nullptr)
	{
		return;
	}

	PopUpData* _WndPopUpData = new PopUpData;

	if (!_WndPopUpData)
	{
		return;
	}

	BFW_HEAP_PROFILE_PUSH(sizeof(PopUpData), _WndPopUpData);

	_WndPopUpData->Width = _Wnd.GetTrueWidth();
	_WndPopUpData->Height = _Wnd.GetTrueHeight();
	_WndPopUpData->Pixels = new uint8_t[_WndPopUpData->Width * _WndPopUpData->Height * 4];
	_WndPopUpData->Wnd = _ParentWndPopUpData.Wnd;

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
	PopUpData& _WndPopUpData = *(PopUpData*)(_Wnd.GetUserData());

	if (!_Wnd.GetUserData())
	{
		return;
	}

	BFW_HEAP_PROFILE_POP(_WndPopUpData.Pixels);
	delete _WndPopUpData.Pixels;
	BFW_HEAP_PROFILE_POP(_Wnd.GetUserData());
	delete _Wnd.GetUserData();
	_Wnd.SetUserData(nullptr);
}

void BFW_WINDOWS::GUI::RenderGray25(BFW::GUI::PopUp& _Wnd, void* _Global)
{
	PopUpData& _WndPopUpData = *(PopUpData*)(_Wnd.GetUserData());

	if (!_Wnd.GetUserData())
	{
		return;
	}

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
	PopUpData& _WndPopUpData = *(PopUpData*)(_Wnd.GetUserData());

	if (!_Wnd.GetUserData())
	{
		return;
	}

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
	PopUpData& _WndPopUpData = *(PopUpData*)(_Wnd.GetUserData());

	if (!_Wnd.GetUserData())
	{
		return;
	}

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

void BFW_WINDOWS::GUI::Composit(BFW::GUI::PopUp& _ParentWnd, BFW::GUI::PopUp& _ChildWnd, void* _Global)
{
	PopUpData& _ParentWndPopUpData = *(PopUpData*)(_ParentWnd.GetUserData());
	PopUpData& _ChildWndPopUpData = *(PopUpData*)(_ChildWnd.GetUserData());

	if (!_ParentWnd.GetUserData() || !_ChildWnd.GetUserData())
	{
		return;
	}

	size_t _PositionX = _ChildWnd.GetPositionX();
	size_t _PositionY = _ChildWnd.GetPositionY();
	size_t _ScrollX = _ChildWnd.GetScrollX();
	size_t _ScrollY = _ChildWnd.GetScrollY();
	size_t _StartX = _ChildWnd.GetPositionX() * (_ChildWnd.GetPositionX() >= 0);
	size_t _StartY = _ChildWnd.GetPositionY() * (_ChildWnd.GetPositionY() >= 0);
	size_t _EndX = _ParentWndPopUpData.Width * (_ParentWndPopUpData.Width <= (_ChildWnd.GetPositionX() + _ChildWnd.GetWidth())) + (_ChildWnd.GetPositionX() + _ChildWnd.GetWidth()) * (_ParentWndPopUpData.Width > (_ChildWnd.GetPositionX() + _ChildWnd.GetWidth()));
	size_t _EndY = _ParentWndPopUpData.Height * (_ParentWndPopUpData.Height <= (_ChildWnd.GetPositionY() + _ChildWnd.GetHeight())) + (_ChildWnd.GetPositionY() + _ChildWnd.GetHeight()) * (_ParentWndPopUpData.Height > (_ChildWnd.GetPositionY() + _ChildWnd.GetHeight()));

#ifdef BFW_WINDOWS_ENABLE_ALPHA

	for (size_t _Y = _StartY; _Y < _EndY; _Y++)
	{
		for (size_t _X = _StartX; _X < _EndX; _X++)
		{
			_ParentWndPopUpData.Pixels[(_X + _Y * _ParentWndPopUpData.Width) * 4 + 0] = (uint8_t)(BFW::Math::Mix(_ParentWndPopUpData.Pixels[(_X + _Y * _ParentWndPopUpData.Width) * 4 + 0], _ChildWndPopUpData.Pixels[(_X - _PositionX + _ScrollX + (_Y - _PositionY + _ScrollY) * _ChildWndPopUpData.Width) * 4 + 0], (float)(_ChildWndPopUpData.Pixels[(_X - _PositionX + _ScrollX + (_Y - _PositionY + _ScrollY) * _ChildWndPopUpData.Width) * 4 + 3]) / 255.0f));
			_ParentWndPopUpData.Pixels[(_X + _Y * _ParentWndPopUpData.Width) * 4 + 1] = (uint8_t)(BFW::Math::Mix(_ParentWndPopUpData.Pixels[(_X + _Y * _ParentWndPopUpData.Width) * 4 + 1], _ChildWndPopUpData.Pixels[(_X - _PositionX + _ScrollX + (_Y - _PositionY + _ScrollY) * _ChildWndPopUpData.Width) * 4 + 1], (float)(_ChildWndPopUpData.Pixels[(_X - _PositionX + _ScrollX + (_Y - _PositionY + _ScrollY) * _ChildWndPopUpData.Width) * 4 + 3]) / 255.0f));
			_ParentWndPopUpData.Pixels[(_X + _Y * _ParentWndPopUpData.Width) * 4 + 2] = (uint8_t)(BFW::Math::Mix(_ParentWndPopUpData.Pixels[(_X + _Y * _ParentWndPopUpData.Width) * 4 + 2], _ChildWndPopUpData.Pixels[(_X - _PositionX + _ScrollX + (_Y - _PositionY + _ScrollY) * _ChildWndPopUpData.Width) * 4 + 2], (float)(_ChildWndPopUpData.Pixels[(_X - _PositionX + _ScrollX + (_Y - _PositionY + _ScrollY) * _ChildWndPopUpData.Width) * 4 + 3]) / 255.0f));
		}
	}

#endif

#ifndef BFW_WINDOWS_ENABLE_ALPHA

	for (size_t _Y = _StartY; _Y < _EndY; _Y++)
	{
		for (size_t _X = _StartX; _X < _EndX; _X++)
		{
			_ParentWndPopUpData.Pixels[(_X + _Y * _ParentWndPopUpData.Width) * 4 + 0] = _ChildWndPopUpData.Pixels[(_X - _PositionX + _ScrollX + (_Y - _PositionY + _ScrollY) * _ChildWndPopUpData.Width) * 4 + 0];
			_ParentWndPopUpData.Pixels[(_X + _Y * _ParentWndPopUpData.Width) * 4 + 1] = _ChildWndPopUpData.Pixels[(_X - _PositionX + _ScrollX + (_Y - _PositionY + _ScrollY) * _ChildWndPopUpData.Width) * 4 + 1];
			_ParentWndPopUpData.Pixels[(_X + _Y * _ParentWndPopUpData.Width) * 4 + 2] = _ChildWndPopUpData.Pixels[(_X - _PositionX + _ScrollX + (_Y - _PositionY + _ScrollY) * _ChildWndPopUpData.Width) * 4 + 2];
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
	case BFW::GUI::_NodePopUpId:
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
	case BFW::GUI::_NodePopUpId:
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

void BFW_WINDOWS::GUI::ResizePopUpLayer(BFW::GUI::PopUp& _Parent, const size_t _Layer, const BFW::GUI::GetMinFnc _GetMinX, const BFW::GUI::GetMinFnc _GetMinY, const size_t _ResizeSize, const BFW::GUI::ForceScrollFnc _ForceHScroll, const BFW::GUI::ForceScrollFnc _ForceVScroll, const size_t _ScrollSize, const size_t _ScrollTopPadding, const size_t _ScrollPadding, const BFW::GUI::SetupRenderDataFnc _SetupData, const BFW::GUI::CleanUpRenderDataFnc _CleanUpData, const BFW::GUI::RenderFnc _RenderBottomWindow, const BFW::GUI::RenderFnc _RenderMiddleWindow, const BFW::GUI::RenderFnc _RenderTopWindow, const BFW::GUI::RenderFnc _RenderBottomButton, const BFW::GUI::RenderFnc _RenderMiddleButton, const BFW::GUI::RenderFnc _RenderTopButton, const BFW::GUI::CompositFnc _Composit, const BFW::GUI::GenerateUserDataFnc _GenerateUserData, const BFW::GUI::ReleaseUserDataFnc _ReleaseUserData, void* _Global)
{
	for (size_t _Index = 0; _Index < _Parent.GetPopUps()[_Layer].GetSize(); _Index++)
	{
		BFW::GUI::PopUp& _PopUp = _Parent.GetPopUps()[_Layer][_Index];

		switch (_PopUp.GetId())
		{
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
	switch (_PopUpId)
	{
	case _DebugWindowPopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_ARROW));
		break;
	}
	case _SpawnButtonPopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_HAND));
		break;
	}
	case BFW::GUI::_NodePopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_ARROW));
		break;
	}
	case BFW::GUI::_LeftResizePopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_SIZEWE));
		break;
	}
	case BFW::GUI::_RightResizePopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_SIZEWE));
		break;
	}
	case BFW::GUI::_TopResizePopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_SIZENS));
		break;
	}
	case BFW::GUI::_BottomResizePopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_SIZENS));
		break;
	}
	case BFW::GUI::_LeftTopResizePopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_SIZENWSE));
		break;
	}
	case BFW::GUI::_LeftBottomResizePopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_SIZENESW));
		break;
	}
	case BFW::GUI::_RightTopResizePopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_SIZENESW));
		break;
	}
	case BFW::GUI::_RightBottomResizePopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_SIZENWSE));
		break;
	}
	case BFW::GUI::_HScrollWindowPopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_HAND));
		break;
	}
	case BFW::GUI::_HScrollButtonPopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_HAND));
		break;
	}
	case BFW::GUI::_VScrollWindowPopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_HAND));
		break;
	}
	case BFW::GUI::_VScrollButtonPopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_HAND));
		break;
	}
	case BFW::GUI::_ScrollCornerPopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_ARROW));
		break;
	}
	default:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_ARROW));
		break;
	}
	}
}
