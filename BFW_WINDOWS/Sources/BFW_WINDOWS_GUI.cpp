#include "../Headers/BFW_WINDOWS.hpp"



const size_t BFW_WINDOWS::GUI::MainWindowMinX = 700;
const size_t BFW_WINDOWS::GUI::MainWindowMinY = 400;
const size_t BFW_WINDOWS::GUI::ChildWindowMinX = 200;
const size_t BFW_WINDOWS::GUI::ChildWindowMinY = 200;
const size_t BFW_WINDOWS::GUI::ResizeSize = 5;
const size_t BFW_WINDOWS::GUI::ScrollSize = 15;
const size_t BFW_WINDOWS::GUI::Padding = 30;
const size_t BFW_WINDOWS::GUI::ScrollPadding = 10;
const size_t BFW_WINDOWS::GUI::ExampleMinX = 200;
const size_t BFW_WINDOWS::GUI::ExampleMinY = 200;



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



BFW_WINDOWS::GUI::WindowData::WindowData() : RenderingMutex(nullptr), Layout(), LCapture(false), LCapturePath(), LCaptureMouseX(0), LCaptureMouseY(0), LCaptureMouseXLastFrame(0), LCaptureMouseYLastFrame(0), ResizeAccumulationX(0), ResizeAccumulationY(0), MCapture(false), MCapturePath(), MCaptureMouseX(0), MCaptureMouseY(0), MCaptureMouseXLastFrame(0), MCaptureMouseYLastFrame(0), RCapture(false), RCapturePath(), RCaptureMouseX(0), RCaptureMouseY(0), RCaptureMouseXLastFrame(0), RCaptureMouseYLastFrame(0), X1Capture(false), X1CapturePopUp(), X1CaptureMouseX(0), X1CaptureMouseY(0), X1CaptureMouseXLastFrame(0), X1CaptureMouseYLastFrame(0), X2Capture(false), X2CapturePopUp(), X2CaptureMouseX(0), X2CaptureMouseY(0), X2CaptureMouseXLastFrame(0), X2CaptureMouseYLastFrame(0)
{

}

BFW_WINDOWS::GUI::WindowData::WindowData(WindowData&& _Other) noexcept : RenderingMutex(_Other.RenderingMutex), Layout((BFW::GUI::PopUp&&)(_Other.Layout)), LCapture(_Other.LCapture), LCapturePath((BFW::Vector<BFW::GUI::PopUp*>)(_Other.LCapturePath)), LCaptureMouseX(_Other.LCaptureMouseX), LCaptureMouseY(_Other.LCaptureMouseY), LCaptureMouseXLastFrame(_Other.LCaptureMouseXLastFrame), LCaptureMouseYLastFrame(_Other.LCaptureMouseYLastFrame), ResizeAccumulationX(_Other.ResizeAccumulationX), ResizeAccumulationY(_Other.ResizeAccumulationY), MCapture(_Other.MCapture), MCapturePath((BFW::Vector<BFW::GUI::PopUp*>)(_Other.MCapturePath)), MCaptureMouseX(_Other.MCaptureMouseX), MCaptureMouseY(_Other.MCaptureMouseY), MCaptureMouseXLastFrame(_Other.MCaptureMouseXLastFrame), MCaptureMouseYLastFrame(_Other.MCaptureMouseYLastFrame), RCapture(_Other.RCapture), RCapturePath((BFW::Vector<BFW::GUI::PopUp*>)(_Other.RCapturePath)), RCaptureMouseX(_Other.RCaptureMouseX), RCaptureMouseY(_Other.RCaptureMouseY), RCaptureMouseXLastFrame(_Other.RCaptureMouseXLastFrame), RCaptureMouseYLastFrame(_Other.RCaptureMouseYLastFrame), X1Capture(_Other.X1Capture), X1CapturePopUp((BFW::Vector<BFW::GUI::PopUp*>)(_Other.X1CapturePopUp)), X1CaptureMouseX(_Other.X1CaptureMouseX), X1CaptureMouseY(_Other.X1CaptureMouseY), X1CaptureMouseXLastFrame(_Other.X1CaptureMouseXLastFrame), X1CaptureMouseYLastFrame(_Other.X1CaptureMouseYLastFrame), X2Capture(_Other.X2Capture), X2CapturePopUp((BFW::Vector<BFW::GUI::PopUp*>)(_Other.X2CapturePopUp)), X2CaptureMouseX(_Other.X2CaptureMouseX), X2CaptureMouseY(_Other.X2CaptureMouseY), X2CaptureMouseXLastFrame(_Other.X2CaptureMouseXLastFrame), X2CaptureMouseYLastFrame(_Other.X2CaptureMouseYLastFrame)
{
	_Other.RenderingMutex = nullptr;
	_Other.LCapture = false;
	_Other.LCaptureMouseX = 0;
	_Other.LCaptureMouseY = 0;
	_Other.LCaptureMouseXLastFrame = 0;
	_Other.LCaptureMouseYLastFrame = 0;
	_Other.ResizeAccumulationX = 0;
	_Other.ResizeAccumulationY = 0;
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

	RenderingMutex = _Other.RenderingMutex;
	Layout = (BFW::GUI::PopUp&&)(_Other.Layout);
	LCapture = _Other.LCapture;
	LCapturePath = (BFW::Vector<BFW::GUI::PopUp*>)(_Other.LCapturePath);
	LCaptureMouseX = _Other.LCaptureMouseX;
	LCaptureMouseY = _Other.LCaptureMouseY;
	LCaptureMouseXLastFrame = _Other.LCaptureMouseXLastFrame;
	LCaptureMouseYLastFrame = _Other.LCaptureMouseYLastFrame;
	ResizeAccumulationX = _Other.ResizeAccumulationX;
	ResizeAccumulationY = _Other.ResizeAccumulationY;
	MCapture = _Other.MCapture;
	MCapturePath = (BFW::Vector<BFW::GUI::PopUp*>)(_Other.MCapturePath);
	MCaptureMouseX = _Other.MCaptureMouseX;
	MCaptureMouseY = _Other.MCaptureMouseY;
	MCaptureMouseXLastFrame = _Other.MCaptureMouseXLastFrame;
	MCaptureMouseYLastFrame = _Other.MCaptureMouseYLastFrame;
	RCapture = _Other.RCapture;
	RCapturePath = (BFW::Vector<BFW::GUI::PopUp*>)(_Other.RCapturePath);
	RCaptureMouseX = _Other.RCaptureMouseX;
	RCaptureMouseY = _Other.RCaptureMouseY;
	RCaptureMouseXLastFrame = _Other.RCaptureMouseXLastFrame;
	RCaptureMouseYLastFrame = _Other.RCaptureMouseYLastFrame;
	X1Capture = _Other.X1Capture;
	X1CapturePopUp = (BFW::Vector<BFW::GUI::PopUp*>)(_Other.X1CapturePopUp);
	X1CaptureMouseX = _Other.X1CaptureMouseX;
	X1CaptureMouseY = _Other.X1CaptureMouseY;
	X1CaptureMouseXLastFrame = _Other.X1CaptureMouseXLastFrame;
	X1CaptureMouseYLastFrame = _Other.X1CaptureMouseYLastFrame;
	X2Capture = _Other.X2Capture;
	X2CapturePopUp = (BFW::Vector<BFW::GUI::PopUp*>)(_Other.X2CapturePopUp);
	X2CaptureMouseX = _Other.X2CaptureMouseX;
	X2CaptureMouseY = _Other.X2CaptureMouseY;
	X2CaptureMouseXLastFrame = _Other.X2CaptureMouseXLastFrame;
	X2CaptureMouseYLastFrame = _Other.X2CaptureMouseYLastFrame;

	_Other.RenderingMutex = nullptr;
	_Other.LCapture = false;
	_Other.LCaptureMouseX = 0;
	_Other.LCaptureMouseY = 0;
	_Other.LCaptureMouseXLastFrame = 0;
	_Other.LCaptureMouseYLastFrame = 0;
	_Other.ResizeAccumulationX = 0;
	_Other.ResizeAccumulationY = 0;
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

		_WndUserData.RenderingMutex->lock();

		HDC _HandleDC = CreateCompatibleDC(_WndDC);

		if (!_HandleDC)
		{
			_WndUserData.RenderingMutex->unlock();
			EndPaint(_hWnd, &_PaintStruct);
			break;
		}

		HBITMAP _HandleBmp = CreateCompatibleBitmap(_WndDC, (int32_t)(_PopUpData.Width), (int32_t)(_PopUpData.Height));

		if (!_HandleBmp)
		{
			DeleteDC(_HandleDC);
			_WndUserData.RenderingMutex->unlock();
			EndPaint(_hWnd, &_PaintStruct);
			break;
		}

		HBITMAP _HandleOld = (HBITMAP)(SelectObject(_HandleDC, _HandleBmp));

		SetBitmapBits(_HandleBmp, (uint32_t)(_PopUpData.Width * _PopUpData.Height * 4), _PopUpData.Pixels);
		StretchBlt(_WndDC, 0, 0, (int32_t)(_Width), (int32_t)(_Height), _HandleDC, (int32_t)(_WndUserData.Layout.GetScrollX()), (int32_t)(_WndUserData.Layout.GetScrollY()), (int32_t)(_WndUserData.Layout.GetWidth()), (int32_t)(_WndUserData.Layout.GetHeight()), SRCCOPY);

		_WndUserData.RenderingMutex->unlock();

		SelectObject(_HandleDC, _HandleOld);
		DeleteDC(_HandleDC);
		DeleteObject(_HandleBmp);

		EndPaint(_hWnd, &_PaintStruct);

		break;
	}
	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO _MinMaxInfo = (LPMINMAXINFO)(_lParam);

		_MinMaxInfo->ptMinTrackSize.x = MainWindowMinX;
		_MinMaxInfo->ptMinTrackSize.y = MainWindowMinY;

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

	_WndUserData.RenderingMutex = new std::mutex();

	if (!_WndUserData.RenderingMutex)
	{
		return false;
	}

	BFW_HEAP_PROFILE_PUSH(sizeof(std::mutex), _WndUserData.RenderingMutex);

	PopUpData* _PopUpData = new PopUpData();

	if (!_PopUpData)
	{
		BFW_HEAP_PROFILE_POP(_WndUserData.RenderingMutex);
		delete _WndUserData.RenderingMutex;
		_WndUserData.RenderingMutex = nullptr;
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
		BFW_HEAP_PROFILE_POP(_WndUserData.RenderingMutex);
		delete _WndUserData.RenderingMutex;
		_WndUserData.RenderingMutex = nullptr;
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

	BFW_HEAP_PROFILE_POP(_WndUserData.RenderingMutex);
	delete _WndUserData.RenderingMutex;
	_WndUserData.RenderingMutex = nullptr;
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

		_WndUserData.RenderingMutex->lock();

		HDC _HandleDC = CreateCompatibleDC(_WndDC);

		if (!_HandleDC)
		{
			_WndUserData.RenderingMutex->unlock();
			EndPaint(_hWnd, &_PaintStruct);
			break;
		}

		HBITMAP _HandleBmp = CreateCompatibleBitmap(_WndDC, (int32_t)(_PopUpData.Width), (int32_t)(_PopUpData.Height));

		if (!_HandleBmp)
		{
			DeleteDC(_HandleDC);
			_WndUserData.RenderingMutex->unlock();
			EndPaint(_hWnd, &_PaintStruct);
			break;
		}

		HBITMAP _HandleOld = (HBITMAP)(SelectObject(_HandleDC, _HandleBmp));

		SetBitmapBits(_HandleBmp, (uint32_t)(_PopUpData.Width * _PopUpData.Height * 4), _PopUpData.Pixels);
		StretchBlt(_WndDC, 0, 0, (int32_t)(_Width), (int32_t)(_Height), _HandleDC, (int32_t)(_WndUserData.Layout.GetScrollX()), (int32_t)(_WndUserData.Layout.GetScrollY()), (int32_t)(_WndUserData.Layout.GetWidth()), (int32_t)(_WndUserData.Layout.GetHeight()), SRCCOPY);

		_WndUserData.RenderingMutex->unlock();

		SelectObject(_HandleDC, _HandleOld);
		DeleteDC(_HandleDC);
		DeleteObject(_HandleBmp);

		EndPaint(_hWnd, &_PaintStruct);

		break;
	}
	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO _MinMaxInfo = (LPMINMAXINFO)(_lParam);

		_MinMaxInfo->ptMinTrackSize.x = ChildWindowMinX;
		_MinMaxInfo->ptMinTrackSize.y = ChildWindowMinY;

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

		if (ScreenToClient(_hWnd, &_Cursor))
		{
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

			_WndUserData.RenderingMutex->lock();

			BFW::GUI::PopUp* _HoverPopUp = _WndUserData.Layout.GetChildFromMouse(_Cursor.x, _Cursor.y);

			if (_HoverPopUp)
			{
				switch (_HoverPopUp->GetId())
				{
				case _ExamplePopUpId:
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

			_WndUserData.RenderingMutex->unlock();
		}

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

	_WndUserData.RenderingMutex = new std::mutex();

	if (!_WndUserData.RenderingMutex)
	{
		return false;
	}

	BFW_HEAP_PROFILE_PUSH(sizeof(std::mutex), _WndUserData.RenderingMutex);

	PopUpData* _PopUpData = new PopUpData();

	if (!_PopUpData)
	{
		BFW_HEAP_PROFILE_POP(_WndUserData.RenderingMutex);
		delete _WndUserData.RenderingMutex;
		_WndUserData.RenderingMutex = nullptr;
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
		BFW_HEAP_PROFILE_POP(_WndUserData.RenderingMutex);
		delete _WndUserData.RenderingMutex;
		_WndUserData.RenderingMutex = nullptr;
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

	BFW_HEAP_PROFILE_POP(_WndUserData.RenderingMutex);
	delete _WndUserData.RenderingMutex;
	_WndUserData.RenderingMutex = nullptr;
	BFW_HEAP_PROFILE_POP(_PopUpData->Pixels);
	delete[] _PopUpData->Pixels;
	_PopUpData->Pixels = nullptr;
	BFW_HEAP_PROFILE_POP(_WndUserData.Layout.GetUserData());
	delete _WndUserData.Layout.GetUserData();
	_WndUserData.Layout.SetUserData(nullptr);
}



void BFW_WINDOWS::GUI::SetupRenderData(void* _Wnd, void* _ParentWnd, void* _Global)
{
	BFW::GUI::PopUp& _WndPopUp = *(BFW::GUI::PopUp*)(_Wnd);
	BFW::GUI::PopUp& _ParentWndPopUp = *(BFW::GUI::PopUp*)(_ParentWnd);
	PopUpData& _ParentWndPopUpData = *(PopUpData*)(_ParentWndPopUp.GetUserData());

	if (_WndPopUp.GetTrueWidth() == 0 || _WndPopUp.GetTrueHeight() == 0 || _ParentWndPopUp.GetUserData() == nullptr)
	{
		return;
	}

	PopUpData* _WndPopUpData = new PopUpData();

	if (!_WndPopUpData)
	{
		return;
	}

	BFW_HEAP_PROFILE_PUSH(sizeof(PopUpData), _WndPopUpData);

	_WndPopUpData->Width = _WndPopUp.GetTrueWidth();
	_WndPopUpData->Height = _WndPopUp.GetTrueHeight();
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

	_WndPopUp.SetUserData(_WndPopUpData);
}

void BFW_WINDOWS::GUI::CleanUpRenderData(void* _Wnd, void* _Global)
{
	BFW::GUI::PopUp& _WndPopUp = *(BFW::GUI::PopUp*)(_Wnd);
	PopUpData& _WndPopUpData = *(PopUpData*)(_WndPopUp.GetUserData());

	if (!_WndPopUp.GetUserData())
	{
		return;
	}

	BFW_HEAP_PROFILE_POP(_WndPopUpData.Pixels);
	delete _WndPopUpData.Pixels;
	BFW_HEAP_PROFILE_POP(_WndPopUp.GetUserData());
	delete _WndPopUp.GetUserData();
	_WndPopUp.SetUserData(nullptr);
}

void BFW_WINDOWS::GUI::RenderGray25(void* _Wnd, void* _Global)
{
	BFW::GUI::PopUp& _WndPopUp = *(BFW::GUI::PopUp*)(_Wnd);
	PopUpData& _WndPopUpData = *(PopUpData*)(_WndPopUp.GetUserData());

	if (!_WndPopUp.GetUserData())
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

void BFW_WINDOWS::GUI::RenderGray30(void* _Wnd, void* _Global)
{
	BFW::GUI::PopUp& _WndPopUp = *(BFW::GUI::PopUp*)(_Wnd);
	PopUpData& _WndPopUpData = *(PopUpData*)(_WndPopUp.GetUserData());

	if (!_WndPopUp.GetUserData())
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

void BFW_WINDOWS::GUI::RenderGray40(void* _Wnd, void* _Global)
{
	BFW::GUI::PopUp& _WndPopUp = *(BFW::GUI::PopUp*)(_Wnd);
	PopUpData& _WndPopUpData = *(PopUpData*)(_WndPopUp.GetUserData());

	if (!_WndPopUp.GetUserData())
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

void BFW_WINDOWS::GUI::Composit(void* _ParentWnd, void* _ChildWnd, void* _Global)
{
	BFW::GUI::PopUp& _ParentWndPopUp = *(BFW::GUI::PopUp*)(_ParentWnd);
	PopUpData& _ParentWndPopUpData = *(PopUpData*)(_ParentWndPopUp.GetUserData());
	BFW::GUI::PopUp& _ChildWndPopUp = *(BFW::GUI::PopUp*)(_ChildWnd);
	PopUpData& _ChildWndPopUpData = *(PopUpData*)(_ChildWndPopUp.GetUserData());

	if (!_ParentWndPopUp.GetUserData() || !_ChildWndPopUp.GetUserData())
	{
		return;
	}

	size_t _PositionX = _ChildWndPopUp.GetPositionX();
	size_t _PositionY = _ChildWndPopUp.GetPositionY();
	size_t _ScrollX = _ChildWndPopUp.GetScrollX();
	size_t _ScrollY = _ChildWndPopUp.GetScrollY();
	size_t _StartX = _ChildWndPopUp.GetPositionX() * (_ChildWndPopUp.GetPositionX() >= 0);
	size_t _StartY = _ChildWndPopUp.GetPositionY() * (_ChildWndPopUp.GetPositionY() >= 0);
	size_t _EndX = _ParentWndPopUpData.Width * (_ParentWndPopUpData.Width <= (_ChildWndPopUp.GetPositionX() + _ChildWndPopUp.GetWidth())) + (_ChildWndPopUp.GetPositionX() + _ChildWndPopUp.GetWidth()) * (_ParentWndPopUpData.Width > (_ChildWndPopUp.GetPositionX() + _ChildWndPopUp.GetWidth()));
	size_t _EndY = _ParentWndPopUpData.Height * (_ParentWndPopUpData.Height <= (_ChildWndPopUp.GetPositionY() + _ChildWndPopUp.GetHeight())) + (_ChildWndPopUp.GetPositionY() + _ChildWndPopUp.GetHeight()) * (_ParentWndPopUpData.Height > (_ChildWndPopUp.GetPositionY() + _ChildWndPopUp.GetHeight()));

	for (size_t _Y = _StartY; _Y < _EndY; _Y++)
	{
		for (size_t _X = _StartX; _X < _EndX; _X++)
		{
			_ParentWndPopUpData.Pixels[(_X + _Y * _ParentWndPopUpData.Width) * 4 + 0] = _ChildWndPopUpData.Pixels[(_X - _PositionX + _ScrollX + (_Y - _PositionY + _ScrollY) * _ChildWndPopUpData.Width) * 4 + 0];
			_ParentWndPopUpData.Pixels[(_X + _Y * _ParentWndPopUpData.Width) * 4 + 1] = _ChildWndPopUpData.Pixels[(_X - _PositionX + _ScrollX + (_Y - _PositionY + _ScrollY) * _ChildWndPopUpData.Width) * 4 + 1];
			_ParentWndPopUpData.Pixels[(_X + _Y * _ParentWndPopUpData.Width) * 4 + 2] = _ChildWndPopUpData.Pixels[(_X - _PositionX + _ScrollX + (_Y - _PositionY + _ScrollY) * _ChildWndPopUpData.Width) * 4 + 2];
			_ParentWndPopUpData.Pixels[(_X + _Y * _ParentWndPopUpData.Width) * 4 + 3] = _ChildWndPopUpData.Pixels[(_X - _PositionX + _ScrollX + (_Y - _PositionY + _ScrollY) * _ChildWndPopUpData.Width) * 4 + 3];
		}
	}
}



void BFW_WINDOWS::GUI::ResizeChilds(BFW::GUI::PopUp& _Layout, BFW::RunTime::Menu* _Menu)
{
	BFW::Vector<BFW::GUI::PopUp>& _Panels = _Layout.GetPanels();

	for (size_t _Index = 0; _Index < _Panels.GetSize(); _Index++)
	{
		switch (_Panels[_Index].GetPanelType())
		{
		case BFW::GUI::_LeftPanelType:
		{
			switch (_Panels[_Index].GetId())
			{
			case _ExamplePopUpId:
			{
				_Panels[_Index].SetHeight(_Layout.GetTrueHeight());
				_Panels[_Index].SetTrueHeight(ExampleMinY);
				GenerateExample(_Panels[_Index], _Menu, false);
				break;
			}
			case BFW::GUI::_NodePopUpId:
			{
				_Panels[_Index].SetHeight(_Layout.GetTrueHeight());
				_Panels[_Index].SetTrueHeight(0);
				ResizeChilds(_Panels[_Index], _Menu);
				break;
			}
			default:
			{
				BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Can't resize unknown window type!"));
				break;
			}
			}

			break;
		}
		case BFW::GUI::_RightPanelType:
		{
			switch (_Panels[_Index].GetId())
			{
			case _ExamplePopUpId:
			{
				_Panels[_Index].SetHeight(_Layout.GetTrueHeight());
				_Panels[_Index].SetTrueHeight(ExampleMinY);
				_Panels[_Index].SetPositionX(_Layout.GetTrueWidth() - _Panels[_Index].GetWidth());
				GenerateExample(_Panels[_Index], _Menu, false);
				break;
			}
			case BFW::GUI::_NodePopUpId:
			{
				_Panels[_Index].SetHeight(_Layout.GetTrueHeight());
				_Panels[_Index].SetTrueHeight(0);
				_Panels[_Index].SetPositionX(_Layout.GetTrueWidth() - _Panels[_Index].GetWidth());
				ResizeChilds(_Panels[_Index], _Menu);
				break;
			}
			default:
			{
				BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Can't resize unknown window type!"));
				break;
			}
			}

			break;
		}
		case BFW::GUI::_TopPanelType:
		{
			switch (_Panels[_Index].GetId())
			{
			case _ExamplePopUpId:
			{
				_Panels[_Index].SetWidth(_Layout.GetTrueWidth());
				_Panels[_Index].SetTrueWidth(ExampleMinX);
				GenerateExample(_Panels[_Index], _Menu, false);
				break;
			}
			case BFW::GUI::_NodePopUpId:
			{
				_Panels[_Index].SetWidth(_Layout.GetTrueWidth());
				_Panels[_Index].SetTrueWidth(0);
				ResizeChilds(_Panels[_Index], _Menu);
				break;
			}
			default:
			{
				BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Can't resize unknown window type!"));
				break;
			}
			}

			break;
		}
		case BFW::GUI::_BottomPanelType:
		{
			switch (_Panels[_Index].GetId())
			{
			case _ExamplePopUpId:
			{
				_Panels[_Index].SetWidth(_Layout.GetTrueWidth());
				_Panels[_Index].SetTrueWidth(ExampleMinX);
				_Panels[_Index].SetPositionY(_Layout.GetTrueHeight() - _Panels[_Index].GetHeight());
				GenerateExample(_Panels[_Index], _Menu, false);
				break;
			}
			case BFW::GUI::_NodePopUpId:
			{
				_Panels[_Index].SetWidth(_Layout.GetTrueWidth());
				_Panels[_Index].SetTrueWidth(0);
				_Panels[_Index].SetPositionY(_Layout.GetTrueHeight() - _Panels[_Index].GetHeight());
				ResizeChilds(_Panels[_Index], _Menu);
				break;
			}
			default:
			{
				BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Can't resize unknown window type!"));
				break;
			}
			}

			break;
		}
		default:
		{
			BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Can't resize unknown panel type!"));
			break;
		}
		}
	}

	BFW::Vector<BFW::GUI::PopUp>& _Nodes = _Layout.GetNodes();

	for (size_t _Index = 0; _Index < _Nodes.GetSize(); _Index++)
	{
		switch (_Nodes[_Index].GetPanelType())
		{
		case BFW::GUI::_LeftPanelType:
		{
			switch (_Nodes[_Index].GetId())
			{
			case _ExamplePopUpId:
			{
				if (_Panels[0].GetWidth() < _Layout.GetTrueWidth())
				{
					_Nodes[_Index].SetWidth(_Layout.GetTrueWidth() - _Panels[0].GetWidth());
				}
				else
				{
					_Nodes[_Index].SetWidth(0);
				}
				_Nodes[_Index].SetTrueWidth(ExampleMinX);

				_Nodes[_Index].SetHeight(_Layout.GetTrueHeight());
				_Nodes[_Index].SetTrueHeight(ExampleMinY);
				GenerateExample(_Nodes[_Index], _Menu, true);
				break;
			}
			case BFW::GUI::_NodePopUpId:
			{
				if (_Panels[0].GetWidth() < _Layout.GetTrueWidth())
				{
					_Nodes[_Index].SetWidth(_Layout.GetTrueWidth() - _Panels[0].GetWidth());
				}
				else
				{
					_Nodes[_Index].SetWidth(0);
				}
				_Nodes[_Index].SetTrueWidth(0);

				_Nodes[_Index].SetHeight(_Layout.GetTrueHeight());
				_Nodes[_Index].SetTrueHeight(0);
				ResizeChilds(_Nodes[_Index], _Menu);
				break;
			}
			default:
			{
				BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Can't resize unknown window type!"));
				break;
			}
			}

			break;
		}
		case BFW::GUI::_RightPanelType:
		{
			switch (_Nodes[_Index].GetId())
			{
			case _ExamplePopUpId:
			{
				if (_Panels[0].GetWidth() < _Layout.GetTrueWidth())
				{
					_Nodes[_Index].SetWidth(_Layout.GetTrueWidth() - _Panels[0].GetWidth());
				}
				else
				{
					_Nodes[_Index].SetWidth(0);
				}
				_Nodes[_Index].SetTrueWidth(ExampleMinX);

				_Nodes[_Index].SetHeight(_Layout.GetTrueHeight());
				_Nodes[_Index].SetTrueHeight(ExampleMinY);
				_Nodes[_Index].SetPositionX(_Layout.GetTrueWidth() - _Nodes[_Index].GetWidth());
				GenerateExample(_Nodes[_Index], _Menu, true);
				break;
			}
			case BFW::GUI::_NodePopUpId:
			{
				if (_Panels[0].GetWidth() < _Layout.GetTrueWidth())
				{
					_Nodes[_Index].SetWidth(_Layout.GetTrueWidth() - _Panels[0].GetWidth());
				}
				else
				{
					_Nodes[_Index].SetWidth(0);
				}
				_Nodes[_Index].SetTrueWidth(0);

				_Nodes[_Index].SetHeight(_Layout.GetTrueHeight());
				_Nodes[_Index].SetTrueHeight(0);
				_Nodes[_Index].SetPositionX(_Layout.GetTrueWidth() - _Nodes[_Index].GetWidth());
				ResizeChilds(_Nodes[_Index], _Menu);
				break;
			}
			default:
			{
				BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Can't resize unknown window type!"));
				break;
			}
			}

			break;
		}
		case BFW::GUI::_TopPanelType:
		{
			switch (_Nodes[_Index].GetId())
			{
			case _ExamplePopUpId:
			{
				if (_Panels[0].GetHeight() < _Layout.GetTrueHeight())
				{
					_Nodes[_Index].SetHeight(_Layout.GetTrueHeight() - _Panels[0].GetHeight());
				}
				else
				{
					_Nodes[_Index].SetHeight(0);
				}
				_Nodes[_Index].SetTrueHeight(ExampleMinY);

				_Nodes[_Index].SetWidth(_Layout.GetTrueWidth());
				_Nodes[_Index].SetTrueWidth(ExampleMinX);
				GenerateExample(_Nodes[_Index], _Menu, true);
				break;
			}
			case BFW::GUI::_NodePopUpId:
			{
				if (_Panels[0].GetHeight() < _Layout.GetTrueHeight())
				{
					_Nodes[_Index].SetHeight(_Layout.GetTrueHeight() - _Panels[0].GetHeight());
				}
				else
				{
					_Nodes[_Index].SetHeight(0);
				}
				_Nodes[_Index].SetTrueHeight(0);

				_Nodes[_Index].SetWidth(_Layout.GetTrueWidth());
				_Nodes[_Index].SetTrueWidth(0);
				ResizeChilds(_Nodes[_Index], _Menu);
				break;
			}
			default:
			{
				BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Can't resize unknown window type!"));
				break;
			}
			}

			break;
		}
		case BFW::GUI::_BottomPanelType:
		{
			switch (_Nodes[_Index].GetId())
			{
			case _ExamplePopUpId:
			{
				if (_Panels[0].GetHeight() < _Layout.GetTrueHeight())
				{
					_Nodes[_Index].SetHeight(_Layout.GetTrueHeight() - _Panels[0].GetHeight());
				}
				else
				{
					_Nodes[_Index].SetHeight(0);
				}
				_Nodes[_Index].SetTrueHeight(ExampleMinY);

				_Nodes[_Index].SetWidth(_Layout.GetTrueWidth());
				_Nodes[_Index].SetTrueWidth(ExampleMinX);
				_Nodes[_Index].SetPositionY(_Layout.GetTrueHeight() - _Nodes[_Index].GetHeight());
				GenerateExample(_Nodes[_Index], _Menu, true);
				break;
			}
			case BFW::GUI::_NodePopUpId:
			{
				if (_Panels[0].GetHeight() < _Layout.GetTrueHeight())
				{
					_Nodes[_Index].SetHeight(_Layout.GetTrueHeight() - _Panels[0].GetHeight());
				}
				else
				{
					_Nodes[_Index].SetHeight(0);
				}
				_Nodes[_Index].SetTrueHeight(0);

				_Nodes[_Index].SetWidth(_Layout.GetTrueWidth());
				_Nodes[_Index].SetTrueWidth(0);
				_Nodes[_Index].SetPositionY(_Layout.GetTrueHeight() - _Nodes[_Index].GetHeight());
				ResizeChilds(_Nodes[_Index], _Menu);
				break;
			}
			default:
			{
				BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Can't resize unknown window type!"));
				break;
			}
			}

			break;
		}
		default:
		{
			BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Can't resize unknown panel type!"));
			break;
		}
		}
	}
}

void BFW_WINDOWS::GUI::GenerateExample(BFW::GUI::PopUp& _Parent, BFW::RunTime::Menu* _Menu, const bool _IsNode)
{
	_Parent.Begin
	(
		_Parent.GetId(), _Parent.GetPanelType(),
		ExampleMinX, ExampleMinY,
		_Parent.GetWidth(), _Parent.GetHeight(),
		_Parent.GetPositionX(), _Parent.GetPositionY(),
		_Parent.GetScrollX(), _Parent.GetScrollY(),
		_Parent.GetSetupData(), _Parent.GetCleanUpData(),
		_Parent.GetRenderBottom(), _Parent.GetRenderMiddle(), _Parent.GetRenderTop(),
		_Parent.GetComposit(),
		_Parent.GetUserData()
	);

	if (!_IsNode)
	{
		if (_Parent.GetPanelType() == BFW::GUI::_NullPanelType)
		{
			size_t _Layer = _Parent.PushPopUpLayer();

			_Parent.PushPopUp
			(
				_Layer, _LeftResizePopUpId,
				0, 0,
				ResizeSize, (_Parent.GetHeight() - 2 * ResizeSize) * (_Parent.GetHeight() > 2 * ResizeSize),
				_Parent.GetScrollX(), ResizeSize + _Parent.GetScrollY(),
				0, 0,
				SetupRenderData, CleanUpRenderData,
				RenderGray40, nullptr, nullptr,
				Composit,
				nullptr,
				true
			);

			_Layer = _Parent.PushPopUpLayer();

			_Parent.PushPopUp
			(
				_Layer, _RightResizePopUpId,
				0, 0,
				ResizeSize, (_Parent.GetHeight() - 2 * ResizeSize) * (_Parent.GetHeight() > 2 * ResizeSize),
				(_Parent.GetWidth() - ResizeSize) * (_Parent.GetWidth() > ResizeSize) + _Parent.GetScrollX(), ResizeSize + _Parent.GetScrollY(),
				0, 0,
				SetupRenderData, CleanUpRenderData,
				RenderGray40, nullptr, nullptr,
				Composit,
				nullptr,
				true
			);

			_Layer = _Parent.PushPopUpLayer();

			_Parent.PushPopUp
			(
				_Layer, _TopResizePopUpId,
				0, 0,
				(_Parent.GetWidth() - 2 * ResizeSize) * (_Parent.GetWidth() > 2 * ResizeSize), ResizeSize,
				ResizeSize + _Parent.GetScrollX(), _Parent.GetScrollY(),
				0, 0,
				SetupRenderData, CleanUpRenderData,
				RenderGray40, nullptr, nullptr,
				Composit,
				nullptr,
				true
			);

			_Layer = _Parent.PushPopUpLayer();

			_Parent.PushPopUp
			(
				_Layer, _BottomResizePopUpId,
				0, 0,
				(_Parent.GetWidth() - 2 * ResizeSize) * (_Parent.GetWidth() > 2 * ResizeSize), ResizeSize,
				ResizeSize + _Parent.GetScrollX(), (_Parent.GetHeight() - ResizeSize) * (_Parent.GetHeight() > ResizeSize) + _Parent.GetScrollY(),
				0, 0,
				SetupRenderData, CleanUpRenderData,
				RenderGray40, nullptr, nullptr,
				Composit,
				nullptr,
				true
			);

			_Layer = _Parent.PushPopUpLayer();

			_Parent.PushPopUp
			(
				_Layer, _LeftTopResizePopUpId,
				0, 0,
				ResizeSize, ResizeSize,
				_Parent.GetScrollX(), _Parent.GetScrollY(),
				0, 0,
				SetupRenderData, CleanUpRenderData,
				RenderGray40, nullptr, nullptr,
				Composit,
				nullptr,
				true
			);

			_Layer = _Parent.PushPopUpLayer();

			_Parent.PushPopUp
			(
				_Layer, _LeftBottomResizePopUpId,
				0, 0,
				ResizeSize, ResizeSize,
				_Parent.GetScrollX(), (_Parent.GetHeight() - ResizeSize) * (_Parent.GetHeight() > ResizeSize) + _Parent.GetScrollY(),
				0, 0,
				SetupRenderData, CleanUpRenderData,
				RenderGray40, nullptr, nullptr,
				Composit,
				nullptr,
				true
			);

			_Layer = _Parent.PushPopUpLayer();

			_Parent.PushPopUp
			(
				_Layer, _RightTopResizePopUpId,
				0, 0,
				ResizeSize, ResizeSize,
				(_Parent.GetWidth() - ResizeSize) * (_Parent.GetWidth() > ResizeSize) + _Parent.GetScrollX(), _Parent.GetScrollY(),
				0, 0,
				SetupRenderData, CleanUpRenderData,
				RenderGray40, nullptr, nullptr,
				Composit,
				nullptr,
				true
			);

			_Layer = _Parent.PushPopUpLayer();

			_Parent.PushPopUp
			(
				_Layer, _RightBottomResizePopUpId,
				0, 0,
				ResizeSize, ResizeSize,
				(_Parent.GetWidth() - ResizeSize) * (_Parent.GetWidth() > ResizeSize) + _Parent.GetScrollX(), (_Parent.GetHeight() - ResizeSize) * (_Parent.GetHeight() > ResizeSize) + _Parent.GetScrollY(),
				0, 0,
				SetupRenderData, CleanUpRenderData,
				RenderGray40, nullptr, nullptr,
				Composit,
				nullptr,
				true
			);
		}

		if (_Parent.GetPanelType() == BFW::GUI::_LeftPanelType)
		{
			size_t _Layer = _Parent.PushPopUpLayer();

			_Parent.PushPopUp
			(
				_Layer, _RightResizePopUpId,
				0, 0,
				ResizeSize, _Parent.GetHeight(),
				(_Parent.GetWidth() - ResizeSize) * (_Parent.GetWidth() > ResizeSize) + _Parent.GetScrollX(), _Parent.GetScrollY(),
				0, 0,
				SetupRenderData, CleanUpRenderData,
				RenderGray40, nullptr, nullptr,
				Composit,
				nullptr,
				true
			);
		}

		if (_Parent.GetPanelType() == BFW::GUI::_RightPanelType)
		{
			size_t _Layer = _Parent.PushPopUpLayer();

			_Parent.PushPopUp
			(
				_Layer, _LeftResizePopUpId,
				0, 0,
				ResizeSize, _Parent.GetHeight(),
				_Parent.GetScrollX(), _Parent.GetScrollY(),
				0, 0,
				SetupRenderData, CleanUpRenderData,
				RenderGray40, nullptr, nullptr,
				Composit,
				nullptr,
				true
			);
		}

		if (_Parent.GetPanelType() == BFW::GUI::_TopPanelType)
		{
			size_t _Layer = _Parent.PushPopUpLayer();

			_Parent.PushPopUp
			(
				_Layer, _BottomResizePopUpId,
				0, 0,
				_Parent.GetWidth(), ResizeSize,
				_Parent.GetScrollX(), (_Parent.GetHeight() - ResizeSize) * (_Parent.GetHeight() > ResizeSize) + _Parent.GetScrollY(),
				0, 0,
				SetupRenderData, CleanUpRenderData,
				RenderGray40, nullptr, nullptr,
				Composit,
				nullptr,
				true
			);
		}

		if (_Parent.GetPanelType() == BFW::GUI::_BottomPanelType)
		{
			size_t _Layer = _Parent.PushPopUpLayer();

			_Parent.PushPopUp
			(
				_Layer, _TopResizePopUpId,
				0, 0,
				_Parent.GetWidth(), ResizeSize,
				_Parent.GetScrollX(), _Parent.GetScrollY(),
				0, 0,
				SetupRenderData, CleanUpRenderData,
				RenderGray40, nullptr, nullptr,
				Composit,
				nullptr,
				true
			);
		}
	}

	{
		size_t _Layer = _Parent.PushPopUpLayer();

		_Parent.PushPopUp
		(
			_Layer, _SpawnButtonPopUpId,
			0, 0,
			_Parent.GetTrueWidth() - Padding * 2, 20,
			Padding, Padding,
			0, 0,
			SetupRenderData, CleanUpRenderData,
			RenderGray40, nullptr, nullptr,
			Composit,
			nullptr,
			true
		);
	}

	if (_Parent.GetWidth() < _Parent.GetTrueWidth())
	{
		size_t _Layer = _Parent.PushPopUpLayer();

		BFW::GUI::PopUp& _ScrollWindow = _Parent.PushPopUp
		(
			_Layer, _HScrollWindowPopUpId,
			0, 0,
			(_Parent.GetWidth() - (ScrollPadding * 2 + ScrollSize)) * (_Parent.GetWidth() > ScrollPadding * 2 + ScrollSize), ScrollSize,
			ScrollPadding + _Parent.GetScrollX(), _Parent.GetHeight() - (ScrollPadding + ScrollSize) + _Parent.GetScrollY(),
			0, 0,
			SetupRenderData, CleanUpRenderData,
			RenderGray25, nullptr, nullptr,
			Composit,
			nullptr,
			true
		);

		_Layer = _ScrollWindow.PushPopUpLayer();

		_ScrollWindow.PushPopUp
		(
			_Layer, _HScrollButtonPopUpId,
			0, 0,
			_ScrollWindow.GetWidth() * _Parent.GetWidth() / _Parent.GetTrueWidth(), ScrollSize,
			_Parent.GetScrollX() * (_ScrollWindow.GetWidth() - _ScrollWindow.GetWidth() * _Parent.GetWidth() / _Parent.GetTrueWidth()) / (_Parent.GetTrueWidth() - _Parent.GetWidth()), 0,
			0, 0,
			SetupRenderData, CleanUpRenderData,
			RenderGray40, nullptr, nullptr,
			Composit,
			nullptr,
			true
		);
	}

	if (_Parent.GetHeight() < _Parent.GetTrueHeight())
	{
		size_t _Layer = _Parent.PushPopUpLayer();

		BFW::GUI::PopUp& _ScrollWindow = _Parent.PushPopUp
		(
			_Layer, _VScrollWindowPopUpId,
			0, 0,
			ScrollSize, (_Parent.GetHeight() - (ScrollPadding * 2 + ScrollSize)) * (_Parent.GetHeight() > ScrollPadding * 2 + ScrollSize),
			_Parent.GetWidth() - (ScrollPadding + ScrollSize) + _Parent.GetScrollX(), ScrollPadding + _Parent.GetScrollY(),
			0, 0,
			SetupRenderData, CleanUpRenderData,
			RenderGray25, nullptr, nullptr,
			Composit,
			nullptr,
			true
		);

		_Layer = _ScrollWindow.PushPopUpLayer();

		_ScrollWindow.PushPopUp
		(
			_Layer, _VScrollButtonPopUpId,
			0, 0,
			ScrollSize, _ScrollWindow.GetHeight() * _Parent.GetHeight() / _Parent.GetTrueHeight(),
			0, _Parent.GetScrollY() * (_ScrollWindow.GetHeight() - _ScrollWindow.GetHeight() * _Parent.GetHeight() / _Parent.GetTrueHeight()) / (_Parent.GetTrueHeight() - _Parent.GetHeight()),
			0, 0,
			SetupRenderData, CleanUpRenderData,
			RenderGray40, nullptr, nullptr,
			Composit,
			nullptr,
			true
		);
	}

	if (_Parent.GetWidth() < _Parent.GetTrueWidth() || _Parent.GetHeight() < _Parent.GetTrueHeight())
	{
		size_t _Layer = _Parent.PushPopUpLayer();

		_Parent.PushPopUp
		(
			_Layer, _ScrollCornerPopUpId,
			0, 0,
			ScrollSize, ScrollSize,
			_Parent.GetWidth() - (ScrollPadding + ScrollSize) + _Parent.GetScrollX(), _Parent.GetHeight() - (ScrollPadding + ScrollSize) + _Parent.GetScrollY(),
			0, 0,
			SetupRenderData, CleanUpRenderData,
			RenderGray25, nullptr, nullptr,
			Composit,
			nullptr,
			true
		);
	}
}

void BFW_WINDOWS::GUI::RenderCursor(BFW::GUI::Window& _Wnd, const uint64_t _PopUpId)
{
	switch (_PopUpId)
	{
	case _LeftResizePopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_SIZEWE));
		break;
	}
	case _RightResizePopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_SIZEWE));
		break;
	}
	case _TopResizePopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_SIZENS));
		break;
	}
	case _BottomResizePopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_SIZENS));
		break;
	}
	case _LeftTopResizePopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_SIZENWSE));
		break;
	}
	case _LeftBottomResizePopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_SIZENESW));
		break;
	}
	case _RightTopResizePopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_SIZENESW));
		break;
	}
	case _RightBottomResizePopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_SIZENWSE));
		break;
	}
	case _HScrollWindowPopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_HAND));
		break;
	}
	case _HScrollButtonPopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_HAND));
		break;
	}
	case _VScrollWindowPopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_HAND));
		break;
	}
	case _VScrollButtonPopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_HAND));
		break;
	}
	case _ScrollCornerPopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_ARROW));
		break;
	}
	case _ExamplePopUpId:
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
	default:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_ARROW));
		break;
	}
	}
}
