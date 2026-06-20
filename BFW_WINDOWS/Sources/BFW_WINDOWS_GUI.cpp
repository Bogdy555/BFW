#include "../Headers/BFW_WINDOWS.hpp"



const size_t BFW_WINDOWS::GUI::PixelResize = 10;
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



BFW_WINDOWS::GUI::WindowData::WindowData() : RenderingMutex(nullptr), Layout()
{

}

BFW_WINDOWS::GUI::WindowData::WindowData(WindowData&& _Other) noexcept : RenderingMutex(_Other.RenderingMutex), Layout((BFW::GUI::PopUp&&)(_Other.Layout))
{
	_Other.RenderingMutex = nullptr;
}

BFW_WINDOWS::GUI::WindowData& BFW_WINDOWS::GUI::WindowData::operator= (WindowData&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	RenderingMutex = _Other.RenderingMutex;
	Layout = (BFW::GUI::PopUp&&)(_Other.Layout);

	_Other.RenderingMutex = nullptr;

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
			DeleteDC(_WndDC);
			_WndUserData.RenderingMutex->unlock();
			EndPaint(_hWnd, &_PaintStruct);
			break;
		}

		HBITMAP _HandleOld = (HBITMAP)(SelectObject(_HandleDC, _HandleBmp));

		SetBitmapBits(_HandleBmp, (uint32_t)(_PopUpData.Width * _PopUpData.Height * 4), _PopUpData.Pixels);
		StretchBlt(_WndDC, 0, 0, (int32_t)(_Width), (int32_t)(_Height), _HandleDC, 0, 0, (int32_t)(_PopUpData.Width), (int32_t)(_PopUpData.Height), SRCCOPY);

		_WndUserData.RenderingMutex->unlock();

		SelectObject(_HandleDC, _HandleOld);
		DeleteDC(_WndDC);
		DeleteObject(_HandleBmp);

		EndPaint(_hWnd, &_PaintStruct);

		break;
	}
	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO _MinMaxInfo = (LPMINMAXINFO)(_lParam);

		_MinMaxInfo->ptMinTrackSize.x = 700;
		_MinMaxInfo->ptMinTrackSize.y = 400;

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

	PopUpData* _PopUpData = new PopUpData();

	if (!_PopUpData)
	{
		delete _WndUserData.RenderingMutex;
		_WndUserData.RenderingMutex = nullptr;
		return false;
	}

	_WndUserData.Layout.SetUserData(_PopUpData);

	_PopUpData->Width = 700;
	_PopUpData->Height = 400;
	_PopUpData->Pixels = new uint8_t[_PopUpData->Width * _PopUpData->Height * 4];

	if (!_PopUpData->Pixels)
	{
		delete _WndUserData.RenderingMutex;
		_WndUserData.RenderingMutex = nullptr;
		delete _WndUserData.Layout.GetUserData();
		_WndUserData.Layout.SetUserData(nullptr);
		return false;
	}

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

	delete _WndUserData.RenderingMutex;
	_WndUserData.RenderingMutex = nullptr;
	delete[] _PopUpData->Pixels;
	_PopUpData->Pixels = nullptr;
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
			DeleteDC(_WndDC);
			_WndUserData.RenderingMutex->unlock();
			EndPaint(_hWnd, &_PaintStruct);
			break;
		}

		HBITMAP _HandleOld = (HBITMAP)(SelectObject(_HandleDC, _HandleBmp));

		SetBitmapBits(_HandleBmp, (uint32_t)(_PopUpData.Width * _PopUpData.Height * 4), _PopUpData.Pixels);
		StretchBlt(_WndDC, 0, 0, (int32_t)(_Width), (int32_t)(_Height), _HandleDC, 0, 0, (int32_t)(_PopUpData.Width), (int32_t)(_PopUpData.Height), SRCCOPY);

		_WndUserData.RenderingMutex->unlock();

		SelectObject(_HandleDC, _HandleOld);
		DeleteDC(_WndDC);
		DeleteObject(_HandleBmp);

		EndPaint(_hWnd, &_PaintStruct);

		break;
	}
	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO _MinMaxInfo = (LPMINMAXINFO)(_lParam);

		_MinMaxInfo->ptMinTrackSize.x = 300;
		_MinMaxInfo->ptMinTrackSize.y = 300;

		break;
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

	PopUpData* _PopUpData = new PopUpData();

	if (!_PopUpData)
	{
		delete _WndUserData.RenderingMutex;
		_WndUserData.RenderingMutex = nullptr;
		return false;
	}

	_WndUserData.Layout.SetUserData(_PopUpData);

	_PopUpData->Width = 300;
	_PopUpData->Height = 300;
	_PopUpData->Pixels = new uint8_t[_PopUpData->Width * _PopUpData->Height * 4];

	if (!_PopUpData->Pixels)
	{
		delete _WndUserData.RenderingMutex;
		_WndUserData.RenderingMutex = nullptr;
		delete _WndUserData.Layout.GetUserData();
		_WndUserData.Layout.SetUserData(nullptr);
		return false;
	}

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

	delete _WndUserData.RenderingMutex;
	_WndUserData.RenderingMutex = nullptr;
	delete[] _PopUpData->Pixels;
	_PopUpData->Pixels = nullptr;
	delete _WndUserData.Layout.GetUserData();
	_WndUserData.Layout.SetUserData(nullptr);
}



void BFW_WINDOWS::GUI::SetupRenderData(void* _Wnd, void* _ParentWnd, void* _Global)
{
	BFW::GUI::PopUp& _WndPopUp = *(BFW::GUI::PopUp*)(_Wnd);
	BFW::GUI::PopUp& _ParentWndPopUp = *(BFW::GUI::PopUp*)(_ParentWnd);
	PopUpData& _ParentWndPopUpData = *(PopUpData*)(_ParentWndPopUp.GetUserData());

	PopUpData* _WndPopUpData = new PopUpData();

	if (!_WndPopUpData)
	{
		return;
	}

	_WndPopUpData->Width = _WndPopUp.GetTrueWidth() / PixelResize;
	_WndPopUpData->Height = _WndPopUp.GetTrueHeight() / PixelResize;
	_WndPopUpData->Pixels = new uint8_t[_WndPopUpData->Width * _WndPopUpData->Height * 4];
	_WndPopUpData->Wnd = _ParentWndPopUpData.Wnd;

	if (!_WndPopUpData->Pixels)
	{
		delete _WndPopUpData;
		return;
	}

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

	delete _WndPopUpData.Pixels;
	delete _WndPopUp.GetUserData();
	_WndPopUp.SetUserData(nullptr);
}

void BFW_WINDOWS::GUI::RenderGray20(void* _Wnd, void* _Global)
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
			_WndPopUpData.Pixels[(_X + _Y * _WndPopUpData.Width) * 4 + 0] = 20;
			_WndPopUpData.Pixels[(_X + _Y * _WndPopUpData.Width) * 4 + 1] = 20;
			_WndPopUpData.Pixels[(_X + _Y * _WndPopUpData.Width) * 4 + 2] = 20;
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

	for (size_t _Y = _ChildWndPopUp.GetPositionY() / (intptr_t)(PixelResize) * (_ChildWndPopUp.GetPositionY() / (intptr_t)(PixelResize) >= 0); _Y < _ParentWndPopUpData.Height * (_ParentWndPopUpData.Height <= (_ChildWndPopUp.GetPositionY() + _ChildWndPopUp.GetHeight()) / PixelResize) + (_ChildWndPopUp.GetPositionY() + _ChildWndPopUp.GetHeight()) / PixelResize * (_ParentWndPopUpData.Height > (_ChildWndPopUp.GetPositionY() + _ChildWndPopUp.GetHeight()) / PixelResize); _Y++)
	{
		for (size_t _X = _ChildWndPopUp.GetPositionX() / (intptr_t)(PixelResize) * (_ChildWndPopUp.GetPositionX() / (intptr_t)(PixelResize) >= 0); _X < _ParentWndPopUpData.Width * (_ParentWndPopUpData.Width <= (_ChildWndPopUp.GetPositionX() + _ChildWndPopUp.GetWidth()) / PixelResize) + (_ChildWndPopUp.GetPositionX() + _ChildWndPopUp.GetWidth()) / PixelResize * (_ParentWndPopUpData.Width > (_ChildWndPopUp.GetPositionX() + _ChildWndPopUp.GetWidth()) / PixelResize); _X++)
		{
			_ParentWndPopUpData.Pixels[(_X + _Y * _ParentWndPopUpData.Width) * 4 + 0] = _ChildWndPopUpData.Pixels[(_X - _ChildWndPopUp.GetPositionX() / (intptr_t)(PixelResize) + _ChildWndPopUp.GetScrollX() / (intptr_t)(PixelResize) + (_Y - _ChildWndPopUp.GetPositionY() / (intptr_t)(PixelResize) + _ChildWndPopUp.GetScrollY() / (intptr_t)(PixelResize)) * _ChildWndPopUpData.Width) * 4 + 0];
			_ParentWndPopUpData.Pixels[(_X + _Y * _ParentWndPopUpData.Width) * 4 + 1] = _ChildWndPopUpData.Pixels[(_X - _ChildWndPopUp.GetPositionX() / (intptr_t)(PixelResize) + _ChildWndPopUp.GetScrollX() / (intptr_t)(PixelResize) + (_Y - _ChildWndPopUp.GetPositionY() / (intptr_t)(PixelResize) + _ChildWndPopUp.GetScrollY() / (intptr_t)(PixelResize)) * _ChildWndPopUpData.Width) * 4 + 1];
			_ParentWndPopUpData.Pixels[(_X + _Y * _ParentWndPopUpData.Width) * 4 + 2] = _ChildWndPopUpData.Pixels[(_X - _ChildWndPopUp.GetPositionX() / (intptr_t)(PixelResize) + _ChildWndPopUp.GetScrollX() / (intptr_t)(PixelResize) + (_Y - _ChildWndPopUp.GetPositionY() / (intptr_t)(PixelResize) + _ChildWndPopUp.GetScrollY() / (intptr_t)(PixelResize)) * _ChildWndPopUpData.Width) * 4 + 2];
			_ParentWndPopUpData.Pixels[(_X + _Y * _ParentWndPopUpData.Width) * 4 + 3] = _ChildWndPopUpData.Pixels[(_X - _ChildWndPopUp.GetPositionX() / (intptr_t)(PixelResize) + _ChildWndPopUp.GetScrollX() / (intptr_t)(PixelResize) + (_Y - _ChildWndPopUp.GetPositionY() / (intptr_t)(PixelResize) + _ChildWndPopUp.GetScrollY() / (intptr_t)(PixelResize)) * _ChildWndPopUpData.Width) * 4 + 3];
		}
	}
}



void BFW_WINDOWS::GUI::GenerateWindow(BFW::GUI::PopUp& _NewLayout, BFW::GUI::PopUp& _OldLayout, const size_t _Width, const size_t _Height)
{
	switch (_NewLayout.GetId())
	{
	case GUI::_ExamplePopUpId:
	{
		_NewLayout.Begin(_OldLayout.GetId(), _OldLayout.GetPanelType(), _Width, _Height, _Width, _Height, _OldLayout.GetPositionX(), _OldLayout.GetPositionY(), _OldLayout.GetScrollX(), _OldLayout.GetScrollY(), _OldLayout.GetSetupData(), _OldLayout.GetCleanUpData(), _OldLayout.GetRenderBottom(), _OldLayout.GetRenderMiddle(), _OldLayout.GetRenderTop(), _OldLayout.GetComposit(), _OldLayout.GetUserData());
		break;
	}
	case BFW::GUI::_NodePopUpId:
	{
		_NewLayout.Begin(_OldLayout.GetId(), _OldLayout.GetPanelType(), _Width, _Height, _Width, _Height, _OldLayout.GetPositionX(), _OldLayout.GetPositionY(), _OldLayout.GetScrollX(), _OldLayout.GetScrollY(), _OldLayout.GetSetupData(), _OldLayout.GetCleanUpData(), _OldLayout.GetRenderBottom(), _OldLayout.GetRenderMiddle(), _OldLayout.GetRenderTop(), _OldLayout.GetComposit(), _OldLayout.GetUserData());
		break;
	}
	default:
	{
		_NewLayout.Begin(_OldLayout.GetId(), _OldLayout.GetPanelType(), _Width, _Height, _Width, _Height, _OldLayout.GetPositionX(), _OldLayout.GetPositionY(), _OldLayout.GetScrollX(), _OldLayout.GetScrollY(), _OldLayout.GetSetupData(), _OldLayout.GetCleanUpData(), _OldLayout.GetRenderBottom(), _OldLayout.GetRenderMiddle(), _OldLayout.GetRenderTop(), _OldLayout.GetComposit(), _OldLayout.GetUserData());
		break;
	}
	}

	//_NewLayout.Begin(_OldLayout.GetId(), _OldLayout.GetPanelType(), _Width, _Height, _Width, _Height, _OldLayout.GetPositionX(), _OldLayout.GetPositionY(), _OldLayout.GetScrollX(), _OldLayout.GetScrollY(), _OldLayout.GetSetupData(), _OldLayout.GetCleanUpData(), _OldLayout.GetRenderBottom(), _OldLayout.GetRenderMiddle(), _OldLayout.GetRenderTop(), _OldLayout.GetComposit(), _OldLayout.GetUserData());
}

void BFW_WINDOWS::GUI::GenerateExample(BFW::GUI::PopUp& _Parent)
{

}

void BFW_WINDOWS::GUI::RenderCursor(BFW::GUI::Window& _Wnd, const uint64_t _PopUpId)
{
	switch (_PopUpId)
	{
	case GUI::_ExamplePopUpId:
	{
		_Wnd.SetCursorIcon(LoadCursor(NULL, IDC_ARROW));
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
