#include "../Headers/BFW_WINDOWS.hpp"



static const BFW::GUI::RenderingDescriptor RenderFunctionsNodeWindow = BFW::GUI::RenderingDescriptor(BFW_WINDOWS::GUI::SetupRenderData, BFW_WINDOWS::GUI::CleanUpRenderData, BFW_WINDOWS::GUI::RenderGray25, nullptr, nullptr, BFW_WINDOWS::GUI::Composit);
static const BFW::GUI::RenderingDescriptor RenderFunctionsPanelWindow = BFW::GUI::RenderingDescriptor(BFW_WINDOWS::GUI::SetupRenderData, BFW_WINDOWS::GUI::CleanUpRenderData, BFW_WINDOWS::GUI::RenderGray30, nullptr, nullptr, BFW_WINDOWS::GUI::Composit);
static const BFW::GUI::RenderingDescriptor RenderFunctionsButton = BFW::GUI::RenderingDescriptor(BFW_WINDOWS::GUI::SetupRenderData, BFW_WINDOWS::GUI::CleanUpRenderData, BFW_WINDOWS::GUI::RenderGray40, nullptr, nullptr, BFW_WINDOWS::GUI::Composit);
static const BFW::GUI::RenderingDescriptor RenderFunctionsResizeBar = BFW::GUI::RenderingDescriptor(BFW_WINDOWS::GUI::SetupRenderData, BFW_WINDOWS::GUI::CleanUpRenderData, BFW_WINDOWS::GUI::RenderGray40, nullptr, nullptr, BFW_WINDOWS::GUI::Composit);
static const BFW::GUI::RenderingDescriptor RenderFunctionsScrollWindow = BFW::GUI::RenderingDescriptor(BFW_WINDOWS::GUI::SetupRenderData, BFW_WINDOWS::GUI::CleanUpRenderData, BFW_WINDOWS::GUI::RenderGray25, nullptr, nullptr, BFW_WINDOWS::GUI::Composit);
static const BFW::GUI::RenderingDescriptor RenderFunctionsScrollButton = BFW::GUI::RenderingDescriptor(BFW_WINDOWS::GUI::SetupRenderData, BFW_WINDOWS::GUI::CleanUpRenderData, BFW_WINDOWS::GUI::RenderGray40, nullptr, nullptr, BFW_WINDOWS::GUI::Composit);
static const BFW::GUI::RenderingDescriptor RenderFunctionsScrollCorner = BFW::GUI::RenderingDescriptor(BFW_WINDOWS::GUI::SetupRenderData, BFW_WINDOWS::GUI::CleanUpRenderData, BFW_WINDOWS::GUI::RenderGray25, nullptr, nullptr, BFW_WINDOWS::GUI::Composit);
static const BFW::GUI::RenderingDescriptor RenderFunctionsDefault = BFW::GUI::RenderingDescriptor(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);



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



static const bool DefaultHitBox(const intptr_t _PositionX, const intptr_t _PositionY, const size_t _Width, const size_t _Height)
{
	return true;
}



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
	LCapture(_Other.LCapture), LCapturePath((BFW::Vector<BFW::SafePointer<BFW::GUI::PopUp>>&&)(_Other.LCapturePath)), LCaptureMouseX(_Other.LCaptureMouseX), LCaptureMouseY(_Other.LCaptureMouseY), LCaptureMouseXLastFrame(_Other.LCaptureMouseXLastFrame), LCaptureMouseYLastFrame(_Other.LCaptureMouseYLastFrame), LAccumulationX(_Other.LAccumulationX), LAccumulationY(_Other.LAccumulationY),
	MCapture(_Other.MCapture), MCapturePath((BFW::Vector<BFW::SafePointer<BFW::GUI::PopUp>>&&)(_Other.MCapturePath)), MCaptureMouseX(_Other.MCaptureMouseX), MCaptureMouseY(_Other.MCaptureMouseY), MCaptureMouseXLastFrame(_Other.MCaptureMouseXLastFrame), MCaptureMouseYLastFrame(_Other.MCaptureMouseYLastFrame), MAccumulationX(_Other.MAccumulationX), MAccumulationY(_Other.MAccumulationY),
	RCapture(_Other.RCapture), RCapturePath((BFW::Vector<BFW::SafePointer<BFW::GUI::PopUp>>&&)(_Other.RCapturePath)), RCaptureMouseX(_Other.RCaptureMouseX), RCaptureMouseY(_Other.RCaptureMouseY), RCaptureMouseXLastFrame(_Other.RCaptureMouseXLastFrame), RCaptureMouseYLastFrame(_Other.RCaptureMouseYLastFrame), RAccumulationX(_Other.RAccumulationX), RAccumulationY(_Other.RAccumulationY),
	X1Capture(_Other.X1Capture), X1CapturePath((BFW::Vector<BFW::SafePointer<BFW::GUI::PopUp>>&&)(_Other.X1CapturePath)), X1CaptureMouseX(_Other.X1CaptureMouseX), X1CaptureMouseY(_Other.X1CaptureMouseY), X1CaptureMouseXLastFrame(_Other.X1CaptureMouseXLastFrame), X1CaptureMouseYLastFrame(_Other.X1CaptureMouseYLastFrame), X1AccumulationX(_Other.X1AccumulationX), X1AccumulationY(_Other.X1AccumulationY),
	X2Capture(_Other.X2Capture), X2CapturePath((BFW::Vector<BFW::SafePointer<BFW::GUI::PopUp>>&&)(_Other.X2CapturePath)), X2CaptureMouseX(_Other.X2CaptureMouseX), X2CaptureMouseY(_Other.X2CaptureMouseY), X2CaptureMouseXLastFrame(_Other.X2CaptureMouseXLastFrame), X2CaptureMouseYLastFrame(_Other.X2CaptureMouseYLastFrame), X2AccumulationX(_Other.X2AccumulationX), X2AccumulationY(_Other.X2AccumulationY)
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
	LCapturePath = (BFW::Vector<BFW::SafePointer<BFW::GUI::PopUp>>&&)(_Other.LCapturePath);
	LCaptureMouseX = _Other.LCaptureMouseX;
	LCaptureMouseY = _Other.LCaptureMouseY;
	LCaptureMouseXLastFrame = _Other.LCaptureMouseXLastFrame;
	LCaptureMouseYLastFrame = _Other.LCaptureMouseYLastFrame;
	LAccumulationX = _Other.LAccumulationX;
	LAccumulationY = _Other.LAccumulationY;
	MCapture = _Other.MCapture;
	MCapturePath = (BFW::Vector<BFW::SafePointer<BFW::GUI::PopUp>>&&)(_Other.MCapturePath);
	MCaptureMouseX = _Other.MCaptureMouseX;
	MCaptureMouseY = _Other.MCaptureMouseY;
	MCaptureMouseXLastFrame = _Other.MCaptureMouseXLastFrame;
	MCaptureMouseYLastFrame = _Other.MCaptureMouseYLastFrame;
	MAccumulationX = _Other.MAccumulationX;
	MAccumulationY = _Other.MAccumulationY;
	RCapture = _Other.RCapture;
	RCapturePath = (BFW::Vector<BFW::SafePointer<BFW::GUI::PopUp>>&&)(_Other.RCapturePath);
	RCaptureMouseX = _Other.RCaptureMouseX;
	RCaptureMouseY = _Other.RCaptureMouseY;
	RCaptureMouseXLastFrame = _Other.RCaptureMouseXLastFrame;
	RCaptureMouseYLastFrame = _Other.RCaptureMouseYLastFrame;
	RAccumulationX = _Other.RAccumulationX;
	RAccumulationY = _Other.RAccumulationY;
	X1Capture = _Other.X1Capture;
	X1CapturePath = (BFW::Vector<BFW::SafePointer<BFW::GUI::PopUp>>&&)(_Other.X1CapturePath);
	X1CaptureMouseX = _Other.X1CaptureMouseX;
	X1CaptureMouseY = _Other.X1CaptureMouseY;
	X1CaptureMouseXLastFrame = _Other.X1CaptureMouseXLastFrame;
	X1CaptureMouseYLastFrame = _Other.X1CaptureMouseYLastFrame;
	X1AccumulationX = _Other.X1AccumulationX;
	X1AccumulationY = _Other.X1AccumulationY;
	X2Capture = _Other.X2Capture;
	X2CapturePath = (BFW::Vector<BFW::SafePointer<BFW::GUI::PopUp>>&&)(_Other.X2CapturePath);
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

	BFW_HEAP_PROFILE_PUSH(_WndData.LayoutMutex, sizeof(std::mutex));

	_WndData.Layout.SetUserData(GenerateUserData(BFW::GUI::_NodeWindowPopUpId, nullptr));

	size_t _WndWidth = 0, _WndHeight = 0;

	_Wnd->GetClientSize(_WndWidth, _WndHeight);

	if (_WndWidth == 0 || _WndHeight == 0)
	{
		_WndWidth = MainWindowMinX;
		_WndHeight = MainWindowMinY;
	}

	PopUpData* _PopUpData = (PopUpData*)(_WndData.Layout.GetUserData());

	_PopUpData->Width = _WndWidth;
	_PopUpData->Height = _WndHeight;
	_PopUpData->Pixels = new uint8_t[_PopUpData->Width * _PopUpData->Height * 4];
	_PopUpData->Wnd = _Wnd;

	if (!_PopUpData->Pixels)
	{
		BFW_HEAP_PROFILE_POP(_WndData.LayoutMutex);
		delete _WndData.LayoutMutex;
		_WndData.LayoutMutex = nullptr;
		ReleaseUserData(_WndData.Layout.GetUserData());
		_WndData.Layout.SetUserData(nullptr);
		return false;
	}

	BFW_HEAP_PROFILE_PUSH(_PopUpData->Pixels, sizeof(uint8_t) * _PopUpData->Width * _PopUpData->Height * 4);

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

	ReleaseAllChilds(_WndData.Layout);

	BFW_HEAP_PROFILE_POP(_WndData.LayoutMutex);
	delete _WndData.LayoutMutex;
	_WndData.LayoutMutex = nullptr;
	BFW_HEAP_PROFILE_POP(_PopUpData->Pixels);
	delete[] _PopUpData->Pixels;
	_PopUpData->Pixels = nullptr;
	ReleaseUserData(_WndData.Layout.GetUserData());
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
			return _Result;
		}

		_WndData.LayoutMutex->lock();

		BFW::Vector<BFW::SafePointer<BFW::GUI::PopUp>> _Path;

		BFW::SafePointer<BFW::GUI::PopUp> _HoverPopUp = _WndData.Layout.GetChildFromMouse(_Cursor.x, _Cursor.y, &_Path);

		size_t _MovableIndex = 0;

		if ((BFW::GUI::PopUp*)(_HoverPopUp) && (IsMovable(_HoverPopUp->GetId()) || _HoverPopUp->GetId() == BFW::GUI::_NodeWindowPopUpId) && !BFW::GUI::PopUp::FindMovableWindow(IsMovable, _MovableIndex, _Path))
		{
			_Result = HTCAPTION;
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

	BFW_HEAP_PROFILE_PUSH(_WndData.LayoutMutex, sizeof(std::mutex));

	_WndData.Layout.SetUserData(GenerateUserData(BFW::GUI::_NodeWindowPopUpId, nullptr));

	size_t _WndWidth = 0, _WndHeight = 0;

	_Wnd->GetClientSize(_WndWidth, _WndHeight);

	if (_WndWidth == 0 || _WndHeight == 0)
	{
		_WndWidth = ChildWindowMinX;
		_WndHeight = ChildWindowMinY;
	}

	PopUpData* _PopUpData = (PopUpData*)(_WndData.Layout.GetUserData());

	_PopUpData->Width = _WndWidth;
	_PopUpData->Height = _WndHeight;
	_PopUpData->Pixels = new uint8_t[_PopUpData->Width * _PopUpData->Height * 4];
	_PopUpData->Wnd = _Wnd;

	if (!_PopUpData->Pixels)
	{
		BFW_HEAP_PROFILE_POP(_WndData.LayoutMutex);
		delete _WndData.LayoutMutex;
		_WndData.LayoutMutex = nullptr;
		ReleaseUserData(_WndData.Layout.GetUserData());
		_WndData.Layout.SetUserData(nullptr);
		return false;
	}

	BFW_HEAP_PROFILE_PUSH(_PopUpData->Pixels, sizeof(uint8_t) * _PopUpData->Width * _PopUpData->Height * 4);

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

	ReleaseAllChilds(_WndData.Layout);

	BFW_HEAP_PROFILE_POP(_WndData.LayoutMutex);
	delete _WndData.LayoutMutex;
	_WndData.LayoutMutex = nullptr;
	BFW_HEAP_PROFILE_POP(_PopUpData->Pixels);
	delete[] _PopUpData->Pixels;
	_PopUpData->Pixels = nullptr;
	ReleaseUserData(_WndData.Layout.GetUserData());
	_WndData.Layout.SetUserData(nullptr);
}



void* BFW_WINDOWS::GUI::GenerateUserData(const uint64_t _PopUpId, void* _Global)
{
	if (_PopUpId == BFW::GUI::_NodeWindowPopUpId)
	{
		PopUpData* _PopUpData = new PopUpData;

		if (!_PopUpData)
		{
			throw nullptr;
		}

		BFW_HEAP_PROFILE_PUSH(_PopUpData, sizeof(PopUpData));

		return _PopUpData;
	}

	BFW::RunTime::Menu* _Menu = (BFW::RunTime::Menu*)(_Global);

	PopUpData* _PopUpData = new PopUpData;

	if (!_PopUpData)
	{
		throw nullptr;
	}

	BFW_HEAP_PROFILE_PUSH(_PopUpData, sizeof(PopUpData));

	return _PopUpData;
}

void BFW_WINDOWS::GUI::ReleaseUserData(void* _PopUpUserData)
{
	PopUpData* _PopUpData = (PopUpData*)(_PopUpUserData);

	BFW_HEAP_PROFILE_POP(_PopUpData);
	delete _PopUpData;
}

void BFW_WINDOWS::GUI::SetupRenderData(BFW::GUI::PopUp& _Wnd, BFW::GUI::PopUp& _Parent, void* _Global)
{
	PopUpData& _WndPopUpData = *(PopUpData*)(_Wnd.GetUserData());
	PopUpData& _ParentPopUpData = *(PopUpData*)(_Parent.GetUserData());

	if (_Wnd.GetTrueWidth() == 0 || _Wnd.GetTrueHeight() == 0 || _ParentPopUpData.Pixels == nullptr)
	{
		return;
	}

	_WndPopUpData.Width = _Wnd.GetTrueWidth();
	_WndPopUpData.Height = _Wnd.GetTrueHeight();
	_WndPopUpData.Pixels = new uint8_t[_WndPopUpData.Width * _WndPopUpData.Height * 4];
	_WndPopUpData.Wnd = _ParentPopUpData.Wnd;

	if (!_WndPopUpData.Pixels)
	{
		_WndPopUpData.Width = 0;
		_WndPopUpData.Height = 0;
		_WndPopUpData.Wnd = nullptr;
		return;
	}

	BFW_HEAP_PROFILE_PUSH(_WndPopUpData.Pixels, sizeof(uint8_t) * _WndPopUpData.Width * _WndPopUpData.Height * 4);
}

void BFW_WINDOWS::GUI::CleanUpRenderData(BFW::GUI::PopUp& _Wnd, void* _Global)
{
	PopUpData& _WndPopUpData = *(PopUpData*)(_Wnd.GetUserData());

	_WndPopUpData.Width = 0;
	_WndPopUpData.Height = 0;
	BFW_HEAP_PROFILE_POP(_WndPopUpData.Pixels);
	delete[] _WndPopUpData.Pixels;
	_WndPopUpData.Pixels = nullptr;
	_WndPopUpData.Wnd = nullptr;
}

void BFW_WINDOWS::GUI::RenderGray25(BFW::GUI::PopUp& _Wnd, void* _Global)
{
	PopUpData& _WndPopUpData = *(PopUpData*)(_Wnd.GetUserData());

	if (!_WndPopUpData.Pixels)
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

	if (!_WndPopUpData.Pixels)
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

	if (!_WndPopUpData.Pixels)
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

void BFW_WINDOWS::GUI::Composit(BFW::GUI::PopUp& _Parent, BFW::GUI::PopUp& _Child, void* _Global)
{
	PopUpData& _ParentPopUpData = *(PopUpData*)(_Parent.GetUserData());
	PopUpData& _ChildPopUpData = *(PopUpData*)(_Child.GetUserData());

	if (!_ParentPopUpData.Pixels || !_ChildPopUpData.Pixels)
	{
		return;
	}

	size_t _Width = _Child.GetWidth();
	size_t _Height = _Child.GetHeight();
	intptr_t _PositionX = _Child.GetPositionX();
	intptr_t _PositionY = _Child.GetPositionY();
	size_t _ScrollX = _Child.GetScrollX();
	size_t _ScrollY = _Child.GetScrollY();
	size_t _StartX = _PositionX * (_PositionX > 0);
	size_t _StartY = _PositionY * (_PositionY > 0);
	size_t _EndX = (_ParentPopUpData.Width * (_ParentPopUpData.Width <= _PositionX + _Width) + (_PositionX + _Width) * (_ParentPopUpData.Width > _PositionX + _Width)) * ((intptr_t)(_Width) > -_PositionX);
	size_t _EndY = (_ParentPopUpData.Height * (_ParentPopUpData.Height <= _PositionY + _Height) + (_PositionY + _Height) * (_ParentPopUpData.Height > _PositionY + _Height)) * ((intptr_t)(_Height) > -_PositionY);

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



const size_t BFW_WINDOWS::GUI::GetMinX(const BFW::GUI::PopUp& _PopUp)
{
	size_t _Min = 0;

	switch (_PopUp.GetId())
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

const size_t BFW_WINDOWS::GUI::GetMinY(const BFW::GUI::PopUp& _PopUp)
{
	size_t _Min = 0;

	switch (_PopUp.GetId())
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

const bool BFW_WINDOWS::GUI::IgnoreHScroll(const uint64_t _PopUpId)
{
	bool _Ignore = false;

	switch (_PopUpId)
	{
	case _SpawnButtonPopUpId:
	{
		break;
	}
	default:
	{
		break;
	}
	}

	return _Ignore;
}

const bool BFW_WINDOWS::GUI::IgnoreVScroll(const uint64_t _PopUpId)
{
	bool _Ignore = false;

	switch (_PopUpId)
	{
	case _SpawnButtonPopUpId:
	{
		break;
	}
	default:
	{
		break;
	}
	}

	return _Ignore;
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

const bool BFW_WINDOWS::GUI::IsMovable(const uint64_t _PopUpId)
{
	bool _Movable = 0;

	switch (_PopUpId)
	{
	case _DebugWindowPopUpId:
	{
		_Movable = true;
		break;
	}
	default:
	{
		break;
	}
	}

	return _Movable;
}

const bool BFW_WINDOWS::GUI::IsScrollable(const uint64_t _PopUpId)
{
	bool _Scrollable = 0;

	switch (_PopUpId)
	{
	case _DebugWindowPopUpId:
	{
		_Scrollable = true;
		break;
	}
	default:
	{
		break;
	}
	}

	return _Scrollable;
}

const BFW::GUI::HitBoxFnc BFW_WINDOWS::GUI::GetHitBox(const uint64_t _PopUpId)
{
	return DefaultHitBox;
}

const BFW::GUI::RenderingDescriptor& BFW_WINDOWS::GUI::GetRenderingDescriptor(const uint64_t _PopUpId)
{
	switch (_PopUpId)
	{
	case _DebugWindowPopUpId:
	{
		return RenderFunctionsPanelWindow;
	}
	case _SpawnButtonPopUpId:
	{
		return RenderFunctionsButton;
	}
	case BFW::GUI::_NodeWindowPopUpId:
	{
		return RenderFunctionsNodeWindow;
	}
	case BFW::GUI::_LeftResizePopUpId:
	{
		return RenderFunctionsResizeBar;
	}
	case BFW::GUI::_RightResizePopUpId:
	{
		return RenderFunctionsResizeBar;
	}
	case BFW::GUI::_TopResizePopUpId:
	{
		return RenderFunctionsResizeBar;
	}
	case BFW::GUI::_BottomResizePopUpId:
	{
		return RenderFunctionsResizeBar;
	}
	case BFW::GUI::_LeftTopResizePopUpId:
	{
		return RenderFunctionsResizeBar;
	}
	case BFW::GUI::_LeftBottomResizePopUpId:
	{
		return RenderFunctionsResizeBar;
	}
	case BFW::GUI::_RightTopResizePopUpId:
	{
		return RenderFunctionsResizeBar;
	}
	case BFW::GUI::_RightBottomResizePopUpId:
	{
		return RenderFunctionsResizeBar;
	}
	case BFW::GUI::_HScrollWindowPopUpId:
	{
		return RenderFunctionsScrollWindow;
	}
	case BFW::GUI::_HScrollButtonPopUpId:
	{
		return RenderFunctionsScrollButton;
	}
	case BFW::GUI::_VScrollWindowPopUpId:
	{
		return RenderFunctionsScrollWindow;
	}
	case BFW::GUI::_VScrollButtonPopUpId:
	{
		return RenderFunctionsScrollButton;
	}
	case BFW::GUI::_ScrollCornerPopUpId:
	{
		return RenderFunctionsScrollCorner;
	}
	default:
	{
		break;
	}
	}

	return RenderFunctionsDefault;
}

void BFW_WINDOWS::GUI::ResizePopUpLayer(BFW::GUI::PopUp& _Parent, const size_t _Layer, const BFW::GUI::GetMinFnc _GetMinX, const BFW::GUI::GetMinFnc _GetMinY, const size_t _ResizeSize, const BFW::GUI::ForceScrollFnc _ForceHScroll, const BFW::GUI::ForceScrollFnc _ForceVScroll, const size_t _ScrollSize, const size_t _ScrollTopPadding, const size_t _ScrollPadding, const BFW::GUI::GetRenderingDescriptorFnc _GetRenderingDescriptor, const BFW::GUI::GetHitBoxFnc _GetHitBox, const BFW::GUI::GenerateUserDataFnc _GenerateUserData, const BFW::GUI::ReleaseUserDataFnc _ReleaseUserData, void* _Global)
{
	for (size_t _Index = 0; _Index < _Parent.GetPopUps()[_Layer].GetSize(); _Index++)
	{
		BFW::GUI::PopUp& _PopUp = _Parent.GetPopUps()[_Layer][_Index];

		switch (_PopUp.GetId())
		{
		case _DebugWindowPopUpId:
		{
			_PopUp.ResizeChilds
			(
				ResizePopUpLayer,
				_GetMinX, _GetMinY,
				_ResizeSize,
				_ForceHScroll, _ForceVScroll,
				_ScrollSize, _ScrollTopPadding, _ScrollPadding,
				_GetRenderingDescriptor,
				_GetHitBox,
				_GenerateUserData, _ReleaseUserData,
				_Global
			);

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



void BFW_WINDOWS::GUI::ReleaseAllChilds(BFW::GUI::PopUp& _Wnd)
{
	for (size_t _Index = 0; _Index < _Wnd.GetPanels().GetSize(); _Index++)
	{
		ReleaseAllChilds(_Wnd.GetPanels()[_Index]);
		ReleaseUserData(_Wnd.GetPanels()[_Index].GetUserData());
		_Wnd.GetPanels()[_Index].SetUserData(nullptr);
	}

	for (size_t _Index = 0; _Index < _Wnd.GetNodes().GetSize(); _Index++)
	{
		ReleaseAllChilds(_Wnd.GetNodes()[_Index]);
		ReleaseUserData(_Wnd.GetNodes()[_Index].GetUserData());
		_Wnd.GetNodes()[_Index].SetUserData(nullptr);
	}

	for (size_t _Layer = 0; _Layer < _Wnd.GetPopUps().GetSize(); _Layer++)
	{
		for (size_t _Index = 0; _Index < _Wnd.GetPopUps()[_Layer].GetSize(); _Index++)
		{
			ReleaseAllChilds(_Wnd.GetPopUps()[_Layer][_Index]);
			ReleaseUserData(_Wnd.GetPopUps()[_Layer][_Index].GetUserData());
			_Wnd.GetPopUps()[_Layer][_Index].SetUserData(nullptr);
		}
	}
}

const bool BFW_WINDOWS::GUI::HandleDefaultLCaptureDrag(const intptr_t _MouseX, const intptr_t _MouseY, const intptr_t _MouseDeltaX, const intptr_t _MouseDeltaY, RunTime::Application& _ApplicationObj, BFW::RunTime::Menu* _Menu, BFW::GUI::Window& _Wnd, WindowData& _WndData, const bool _IsMainWindow)
{
	if (!_WndData.LCapturePath.GetSize())
	{
		return true;
	}

	size_t _WindowIndex = 0;

	if (BFW::GUI::PopUp::FindMovableWindow(IsMovable, _WindowIndex, _WndData.LCapturePath))
	{
		size_t _Layer = 0;
		_WndData.LCapturePath[_WindowIndex + 1]->FindFocusedPopUpLayer(_Layer, *_WndData.LCapturePath[_WindowIndex]);
		_WndData.LCapturePath[_WindowIndex + 1]->SetForegroundLayer(_Layer);
	}

	if (_WndData.LCapturePath[0]->GetId() == BFW::GUI::_LeftResizePopUpId || _WndData.LCapturePath[0]->GetId() == BFW::GUI::_RightResizePopUpId || _WndData.LCapturePath[0]->GetId() == BFW::GUI::_TopResizePopUpId || _WndData.LCapturePath[0]->GetId() == BFW::GUI::_BottomResizePopUpId || _WndData.LCapturePath[0]->GetId() == BFW::GUI::_LeftTopResizePopUpId || _WndData.LCapturePath[0]->GetId() == BFW::GUI::_LeftBottomResizePopUpId || _WndData.LCapturePath[0]->GetId() == BFW::GUI::_RightTopResizePopUpId || _WndData.LCapturePath[0]->GetId() == BFW::GUI::_RightBottomResizePopUpId)
	{
		_WndData.LCapturePath[1]->ResizeWithMouse
		(
			_WndData.LCapturePath[0]->GetId(), *_WndData.LCapturePath[2],
			_MouseDeltaX, _MouseDeltaY,
			_WndData.LAccumulationX, _WndData.LAccumulationY,
			ResizePopUpLayer,
			GetMinX, GetMinY,
			ResizeSize,
			ForceHScroll, ForceVScroll,
			ScrollSize, ScrollTopPadding, ScrollPadding,
			GetRenderingDescriptor,
			GetHitBox,
			GenerateUserData, ReleaseUserData,
			_Menu
		);

		return  true;
	}

	if (_WndData.LCapturePath[0]->GetId() == BFW::GUI::_HScrollWindowPopUpId)
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

		if (_Wnd.GetKeys()[BFW::Input::_MouseLKeyId].JustPressed())
		{
			_WndData.LCapturePath[2]->ScrollWithMouseH(_LocalMouseX - _WndData.LCapturePath[0]->GetPositionX() - _WndData.LCapturePath[0]->GetWidth() / 2, _WndData.LAccumulationX, IgnoreHScroll);
		}
		else
		{
			_WndData.LCapturePath[2]->ScrollWithMouseH(_MouseDeltaX, _WndData.LAccumulationX, IgnoreHScroll);
		}

		_WndData.LCapturePath.Erase(0);

		return true;
	}

	if (_WndData.LCapturePath[0]->GetId() == BFW::GUI::_HScrollButtonPopUpId)
	{
		_WndData.LCapturePath[2]->ScrollWithMouseH(_MouseDeltaX, _WndData.LAccumulationX, IgnoreHScroll);

		return true;
	}

	if (_WndData.LCapturePath[0]->GetId() == BFW::GUI::_VScrollWindowPopUpId)
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

		if (_Wnd.GetKeys()[BFW::Input::_MouseLKeyId].JustPressed())
		{
			_WndData.LCapturePath[2]->ScrollWithMouseV(_LocalMouseY - _WndData.LCapturePath[0]->GetPositionY() - _WndData.LCapturePath[0]->GetHeight() / 2, _WndData.LAccumulationY, IgnoreVScroll);
		}
		else
		{
			_WndData.LCapturePath[2]->ScrollWithMouseV(_MouseDeltaY, _WndData.LAccumulationY, IgnoreVScroll);
		}

		_WndData.LCapturePath.Erase(0);

		return true;
	}

	if (_WndData.LCapturePath[0]->GetId() == BFW::GUI::_VScrollButtonPopUpId)
	{
		_WndData.LCapturePath[2]->ScrollWithMouseV(_MouseDeltaY, _WndData.LAccumulationY, IgnoreVScroll);

		return true;
	}

	_WindowIndex = 0;

	if (BFW::GUI::PopUp::FindMovableWindow(IsMovable, _WindowIndex, _WndData.LCapturePath) && (IsMovable(_WndData.LCapturePath[0]->GetId()) || _WndData.LCapturePath[0]->GetId() == BFW::GUI::_NodeWindowPopUpId))
	{
		size_t _Layer = 0;
		_WndData.LCapturePath[_WindowIndex + 1]->FindFocusedPopUpLayer(_Layer, *_WndData.LCapturePath[_WindowIndex]);
		_WndData.LCapturePath[_WindowIndex + 1]->MoveLayerWithMouse(_Layer, _MouseDeltaX, _MouseDeltaY);

		return true;
	}

	return false;
}

const bool BFW_WINDOWS::GUI::HandleDefaultMCaptureDrag(const intptr_t _MouseX, const intptr_t _MouseY, const intptr_t _MouseDeltaX, const intptr_t _MouseDeltaY, RunTime::Application& _ApplicationObj, BFW::RunTime::Menu* _Menu, BFW::GUI::Window& _Wnd, WindowData& _WndData, const bool _IsMainWindow)
{
	if (!_WndData.MCapturePath.GetSize())
	{
		return true;
	}

	size_t _WindowIndex = 0;

	if (BFW::GUI::PopUp::FindMovableWindow(IsMovable, _WindowIndex, _WndData.MCapturePath))
	{
		size_t _Layer = 0;
		_WndData.MCapturePath[_WindowIndex + 1]->FindFocusedPopUpLayer(_Layer, *_WndData.MCapturePath[_WindowIndex]);
		_WndData.MCapturePath[_WindowIndex + 1]->SetForegroundLayer(_Layer);
	}

	_WindowIndex = 0;

	if (BFW::GUI::PopUp::FindScrollableWindow(IsScrollable, _WindowIndex, _WndData.MCapturePath))
	{
		_WndData.MCapturePath[_WindowIndex]->ScrollH((intptr_t)((float)((_MouseX - _WndData.MCaptureMouseX) / (intptr_t)(MouseCaptureScrollScale)) * MouseCaptureScrollSpeed * _ApplicationObj.GetUITimeStep()), IgnoreHScroll);
		_WndData.MCapturePath[_WindowIndex]->ScrollV((intptr_t)((float)((_MouseY - _WndData.MCaptureMouseY) / (intptr_t)(MouseCaptureScrollScale)) * MouseCaptureScrollSpeed * _ApplicationObj.GetUITimeStep()), IgnoreVScroll);

		return true;
	}

	return false;
}

const bool BFW_WINDOWS::GUI::HandleDefaultRCaptureDrag(const intptr_t _MouseX, const intptr_t _MouseY, const intptr_t _MouseDeltaX, const intptr_t _MouseDeltaY, RunTime::Application& _ApplicationObj, BFW::RunTime::Menu* _Menu, BFW::GUI::Window& _Wnd, WindowData& _WndData, const bool _IsMainWindow)
{
	if (!_WndData.RCapturePath.GetSize())
	{
		return true;
	}

	size_t _WindowIndex = 0;

	if (BFW::GUI::PopUp::FindMovableWindow(IsMovable, _WindowIndex, _WndData.RCapturePath))
	{
		size_t _Layer = 0;
		_WndData.RCapturePath[_WindowIndex + 1]->FindFocusedPopUpLayer(_Layer, *_WndData.RCapturePath[_WindowIndex]);
		_WndData.RCapturePath[_WindowIndex + 1]->SetForegroundLayer(_Layer);
	}

	return false;
}

const bool BFW_WINDOWS::GUI::HandleDefaultX1CaptureDrag(const intptr_t _MouseX, const intptr_t _MouseY, const intptr_t _MouseDeltaX, const intptr_t _MouseDeltaY, RunTime::Application& _ApplicationObj, BFW::RunTime::Menu* _Menu, BFW::GUI::Window& _Wnd, WindowData& _WndData, const bool _IsMainWindow)
{
	if (!_WndData.X1CapturePath.GetSize())
	{
		return true;
	}

	size_t _WindowIndex = 0;

	if (BFW::GUI::PopUp::FindMovableWindow(IsMovable, _WindowIndex, _WndData.X1CapturePath))
	{
		size_t _Layer = 0;
		_WndData.X1CapturePath[_WindowIndex + 1]->FindFocusedPopUpLayer(_Layer, *_WndData.X1CapturePath[_WindowIndex]);
		_WndData.X1CapturePath[_WindowIndex + 1]->SetForegroundLayer(_Layer);
	}

	return false;
}

const bool BFW_WINDOWS::GUI::HandleDefaultX2CaptureDrag(const intptr_t _MouseX, const intptr_t _MouseY, const intptr_t _MouseDeltaX, const intptr_t _MouseDeltaY, RunTime::Application& _ApplicationObj, BFW::RunTime::Menu* _Menu, BFW::GUI::Window& _Wnd, WindowData& _WndData, const bool _IsMainWindow)
{
	if (!_WndData.X2CapturePath.GetSize())
	{
		return true;
	}

	size_t _WindowIndex = 0;

	if (BFW::GUI::PopUp::FindMovableWindow(IsMovable, _WindowIndex, _WndData.X2CapturePath))
	{
		size_t _Layer = 0;
		_WndData.X2CapturePath[_WindowIndex + 1]->FindFocusedPopUpLayer(_Layer, *_WndData.X2CapturePath[_WindowIndex]);
		_WndData.X2CapturePath[_WindowIndex + 1]->SetForegroundLayer(_Layer);
	}

	return false;
}

void BFW_WINDOWS::GUI::HandleDefaultHWheelEvent(const BFW::Input::WheelEvent& _Event, BFW::Vector<BFW::SafePointer<BFW::GUI::PopUp>>& _Path, RunTime::Application& _ApplicationObj, BFW::RunTime::Menu* _Menu, BFW::GUI::Window& _Wnd, WindowData& _WndData, const bool _IsMainWindow)
{
	size_t _ScrollableWindowIndex = 0;

	if (!BFW::GUI::PopUp::FindScrollableWindow(IsScrollable, _ScrollableWindowIndex, _Path))
	{
		return;
	}

	_Path[_ScrollableWindowIndex]->ScrollH(_Event.Delta, IgnoreHScroll);
}

void BFW_WINDOWS::GUI::HandleDefaultVWheelEvent(const BFW::Input::WheelEvent& _Event, BFW::Vector<BFW::SafePointer<BFW::GUI::PopUp>>& _Path, RunTime::Application& _ApplicationObj, BFW::RunTime::Menu* _Menu, BFW::GUI::Window& _Wnd, WindowData& _WndData, const bool _IsMainWindow)
{
	size_t _ScrollableWindowIndex = 0;

	if (!BFW::GUI::PopUp::FindScrollableWindow(IsScrollable, _ScrollableWindowIndex, _Path))
	{
		return;
	}

	_Path[_ScrollableWindowIndex]->ScrollV(_Event.Delta, IgnoreVScroll);
}

void BFW_WINDOWS::GUI::HandleDefaultKeys(RunTime::Application& _ApplicationObj, BFW::RunTime::Menu* _Menu, BFW::GUI::Window& _Wnd, WindowData& _WndData, const bool _IsMainWindow)
{
	if (_Wnd.GetKeys()[BFW::Input::_F11KeyId].JustPressed())
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

void BFW_WINDOWS::GUI::HandleDefaultControllers(RunTime::Application& _ApplicationObj, BFW::RunTime::Menu* _Menu, BFW::GUI::Window& _Wnd, WindowData& _WndData, const bool _IsMainWindow)
{
	if (!_Wnd.HasFocus())
	{
		return;
	}

	if (_ApplicationObj.GetController(0).GetStart().JustPressed() || _ApplicationObj.GetController(1).GetStart().JustPressed() || _ApplicationObj.GetController(2).GetStart().JustPressed() || _ApplicationObj.GetController(3).GetStart().JustPressed())
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

void BFW_WINDOWS::GUI::RenderWindow(RunTime::Application& _ApplicationObj, BFW::RunTime::Menu* _Menu, BFW::GUI::Window& _Wnd, WindowData& _WndData, const bool _IsMainWindow)
{
	_WndData.LayoutMutex->lock();

	size_t _WndWidth = 0, _WndHeight = 0;

	_Wnd.GetClientSize(_WndWidth, _WndHeight);

	PopUpData& _WndPopUpData = *(PopUpData*)(_WndData.Layout.GetUserData());

	if (_WndWidth == 0 || _WndHeight == 0)
	{
		_WndWidth = _WndPopUpData.Width;
		_WndHeight = _WndPopUpData.Height;
	}

	size_t _TrueWidth = _WndWidth, _TrueHeight = _WndHeight;

	if (_TrueWidth < GetMinX(_WndData.Layout))
	{
		_TrueWidth = GetMinX(_WndData.Layout);
	}

	if (_TrueHeight < GetMinY(_WndData.Layout))
	{
		_TrueHeight = GetMinY(_WndData.Layout);
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
				BFW_HEAP_PROFILE_PUSH(_Pixels, sizeof(uint8_t) * _WndWidth * _WndHeight * 4);

				BFW_HEAP_PROFILE_POP(_WndPopUpData.Pixels);
				delete[] _WndPopUpData.Pixels;

				_WndPopUpData.Width = _TrueWidth;
				_WndPopUpData.Height = _TrueHeight;
				_WndPopUpData.Pixels = _Pixels;
			}

			_WndData.Layout.SetWidth(_WndWidth);
			_WndData.Layout.SetHeight(_WndHeight);
			_WndData.Layout.SetTrueWidth(GetMinX(_WndData.Layout));
			_WndData.Layout.SetTrueHeight(GetMinY(_WndData.Layout));

			_WndData.Layout.ResizeChilds
			(
				ResizePopUpLayer,
				GetMinX, GetMinY,
				ResizeSize,
				ForceHScroll, ForceVScroll,
				ScrollSize, ScrollTopPadding, ScrollPadding,
				GetRenderingDescriptor,
				GetHitBox,
				GenerateUserData, ReleaseUserData,
				_Menu
			);
		}
	}

	_WndData.Layout.Render(_Menu);

	intptr_t _MouseX = 0, _MouseY = 0;

	if (_Wnd.GetMousePosition(_MouseX, _MouseY))
	{
		bool _CursorSet = false;

		if (!_CursorSet && _WndData.MCapture && BFW::GUI::PopUp::IsValidPath(_WndData.MCapturePath))
		{
			size_t _WindowIndex = 0;

			if (BFW::GUI::PopUp::FindScrollableWindow(IsScrollable, _WindowIndex, _WndData.MCapturePath))
			{
				_CursorSet = true;
				_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_SIZEALL));
			}
		}

		if (!_CursorSet && _WndData.LCapture && BFW::GUI::PopUp::IsValidPath(_WndData.LCapturePath))
		{
			if (_WndData.LCapturePath.GetSize())
			{
				_CursorSet = true;
				RenderCursor(_Wnd, _WndData.LCapturePath[0]->GetId());
			}
		}

		if (!_CursorSet)
		{
			BFW::SafePointer<BFW::GUI::PopUp> _HoverPopUp = _WndData.Layout.GetChildFromMouse(_MouseX, _MouseY);

			if ((BFW::GUI::PopUp*)(_HoverPopUp))
			{
				_CursorSet = true;
				RenderCursor(_Wnd, _HoverPopUp->GetId());
			}
		}

		if (!_CursorSet)
		{
			_CursorSet = true;
			RenderCursor(_Wnd, BFW::GUI::_NodeWindowPopUpId);
		}
	}

	_WndData.LayoutMutex->unlock();

	_Wnd.UpdateContent();
}
