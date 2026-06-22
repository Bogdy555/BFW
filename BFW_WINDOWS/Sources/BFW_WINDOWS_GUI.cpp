#include "../Headers/BFW_WINDOWS.hpp"



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
		StretchBlt(_WndDC, 0, 0, (int32_t)(_Width), (int32_t)(_Height), _HandleDC, (int32_t)(_WndUserData.Layout.GetScrollX()), (int32_t)(_WndUserData.Layout.GetScrollY()), (int32_t)(_WndUserData.Layout.GetWidth()), (int32_t)(_WndUserData.Layout.GetHeight()), SRCCOPY);

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
		StretchBlt(_WndDC, 0, 0, (int32_t)(_Width), (int32_t)(_Height), _HandleDC, (int32_t)(_WndUserData.Layout.GetScrollX()), (int32_t)(_WndUserData.Layout.GetScrollY()), (int32_t)(_WndUserData.Layout.GetWidth()), (int32_t)(_WndUserData.Layout.GetHeight()), SRCCOPY);

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

	_WndPopUpData->Width = _WndPopUp.GetTrueWidth();
	_WndPopUpData->Height = _WndPopUp.GetTrueHeight();
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

	size_t _PositionX = _ChildWndPopUp.GetPositionX();
	size_t _PositionY = _ChildWndPopUp.GetPositionY();
	size_t _ScrollX = _ChildWndPopUp.GetScrollX();
	size_t _ScrollY = _ChildWndPopUp.GetScrollY();
	size_t _StartX = _PositionX * (_PositionX >= 0);
	size_t _StartY = _ChildWndPopUp.GetPositionY() * (_ChildWndPopUp.GetPositionY() >= 0);
	size_t _EndX = _ParentWndPopUpData.Width * (_ParentWndPopUpData.Width <= (_PositionX + _ChildWndPopUp.GetWidth())) + (_PositionX + _ChildWndPopUp.GetWidth()) * (_ParentWndPopUpData.Width > (_PositionX + _ChildWndPopUp.GetWidth()));
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



void BFW_WINDOWS::GUI::ResizeChilds(BFW::GUI::PopUp& _Layout)
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
				_Panels[_Index].SetTrueHeight(_Layout.GetTrueHeight() * (_Layout.GetTrueHeight() >= ExampleMinY) + ExampleMinY * (_Layout.GetTrueHeight() < ExampleMinY));
				_Panels[_Index].SetScrollY(_Panels[_Index].GetScrollY() * (_Panels[_Index].GetScrollY() <= _Panels[_Index].GetTrueHeight() - _Panels[_Index].GetHeight()) + (_Panels[_Index].GetTrueHeight() - _Panels[_Index].GetHeight()) * (_Panels[_Index].GetScrollY() > _Panels[_Index].GetTrueHeight() - _Panels[_Index].GetHeight()));
				ResizeChilds(_Panels[_Index]);
				break;
			}
			case BFW::GUI::_NodePopUpId:
			{
				_Panels[_Index].SetHeight(_Layout.GetTrueHeight());
				_Panels[_Index].SetTrueHeight(_Layout.GetTrueHeight());
				_Panels[_Index].SetScrollY(_Panels[_Index].GetScrollY() * (_Panels[_Index].GetScrollY() <= _Panels[_Index].GetTrueHeight() - _Panels[_Index].GetHeight()) + (_Panels[_Index].GetTrueHeight() - _Panels[_Index].GetHeight()) * (_Panels[_Index].GetScrollY() > _Panels[_Index].GetTrueHeight() - _Panels[_Index].GetHeight()));
				ResizeChilds(_Panels[_Index]);
				break;
			}
			default:
			{
				throw nullptr;
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
				_Panels[_Index].SetTrueHeight(_Layout.GetTrueHeight() * (_Layout.GetTrueHeight() >= ExampleMinY) + ExampleMinY * (_Layout.GetTrueHeight() < ExampleMinY));
				_Panels[_Index].SetScrollY(_Panels[_Index].GetScrollY() * (_Panels[_Index].GetScrollY() <= _Panels[_Index].GetTrueHeight() - _Panels[_Index].GetHeight()) + (_Panels[_Index].GetTrueHeight() - _Panels[_Index].GetHeight()) * (_Panels[_Index].GetScrollY() > _Panels[_Index].GetTrueHeight() - _Panels[_Index].GetHeight()));
				_Panels[_Index].SetPositionX(_Layout.GetTrueWidth() - _Panels[_Index].GetWidth());
				ResizeChilds(_Panels[_Index]);
				break;
			}
			case BFW::GUI::_NodePopUpId:
			{
				_Panels[_Index].SetHeight(_Layout.GetTrueHeight());
				_Panels[_Index].SetTrueHeight(_Layout.GetTrueHeight());
				_Panels[_Index].SetScrollY(_Panels[_Index].GetScrollY() * (_Panels[_Index].GetScrollY() <= _Panels[_Index].GetTrueHeight() - _Panels[_Index].GetHeight()) + (_Panels[_Index].GetTrueHeight() - _Panels[_Index].GetHeight()) * (_Panels[_Index].GetScrollY() > _Panels[_Index].GetTrueHeight() - _Panels[_Index].GetHeight()));
				_Panels[_Index].SetPositionX(_Layout.GetTrueWidth() - _Panels[_Index].GetWidth());
				ResizeChilds(_Panels[_Index]);
				break;
			}
			default:
			{
				throw nullptr;
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
				_Panels[_Index].SetTrueWidth(_Layout.GetTrueWidth() * (_Layout.GetTrueWidth() >= ExampleMinX) + ExampleMinX * (_Layout.GetTrueWidth() < ExampleMinX));
				_Panels[_Index].SetScrollX(_Panels[_Index].GetScrollX() * (_Panels[_Index].GetScrollX() <= _Panels[_Index].GetTrueWidth() - _Panels[_Index].GetWidth()) + (_Panels[_Index].GetTrueWidth() - _Panels[_Index].GetWidth()) * (_Panels[_Index].GetScrollX() > _Panels[_Index].GetTrueWidth() - _Panels[_Index].GetWidth()));
				ResizeChilds(_Panels[_Index]);
				break;
			}
			case BFW::GUI::_NodePopUpId:
			{
				_Panels[_Index].SetWidth(_Layout.GetTrueWidth());
				_Panels[_Index].SetTrueWidth(_Layout.GetTrueWidth());
				_Panels[_Index].SetScrollX(_Panels[_Index].GetScrollX() * (_Panels[_Index].GetScrollX() <= _Panels[_Index].GetTrueWidth() - _Panels[_Index].GetWidth()) + (_Panels[_Index].GetTrueWidth() - _Panels[_Index].GetWidth()) * (_Panels[_Index].GetScrollX() > _Panels[_Index].GetTrueWidth() - _Panels[_Index].GetWidth()));
				ResizeChilds(_Panels[_Index]);
				break;
			}
			default:
			{
				throw nullptr;
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
				_Panels[_Index].SetTrueWidth(_Layout.GetTrueWidth() * (_Layout.GetTrueWidth() >= ExampleMinX) + ExampleMinX * (_Layout.GetTrueWidth() < ExampleMinX));
				_Panels[_Index].SetScrollX(_Panels[_Index].GetScrollX() * (_Panels[_Index].GetScrollX() <= _Panels[_Index].GetTrueWidth() - _Panels[_Index].GetWidth()) + (_Panels[_Index].GetTrueWidth() - _Panels[_Index].GetWidth()) * (_Panels[_Index].GetScrollX() > _Panels[_Index].GetTrueWidth() - _Panels[_Index].GetWidth()));
				_Panels[_Index].SetPositionY(_Layout.GetTrueHeight() - _Panels[_Index].GetHeight());
				ResizeChilds(_Panels[_Index]);
				break;
			}
			case BFW::GUI::_NodePopUpId:
			{
				_Panels[_Index].SetWidth(_Layout.GetTrueWidth());
				_Panels[_Index].SetTrueWidth(_Layout.GetTrueWidth());
				_Panels[_Index].SetScrollX(_Panels[_Index].GetScrollX() * (_Panels[_Index].GetScrollX() <= _Panels[_Index].GetTrueWidth() - _Panels[_Index].GetWidth()) + (_Panels[_Index].GetTrueWidth() - _Panels[_Index].GetWidth()) * (_Panels[_Index].GetScrollX() > _Panels[_Index].GetTrueWidth() - _Panels[_Index].GetWidth()));
				_Panels[_Index].SetPositionY(_Layout.GetTrueHeight() - _Panels[_Index].GetHeight());
				ResizeChilds(_Panels[_Index]);
				break;
			}
			default:
			{
				throw nullptr;
			}
			}

			break;
		}
		default:
		{
			throw nullptr;
		}
		}
	}

	BFW::GUI::PopUp* _Node = _Layout.GetNode();

	if (_Node != nullptr)
	{
		switch (_Panels[0].GetPanelType())
		{
		case BFW::GUI::_LeftPanelType:
		{
			switch (_Node->GetId())
			{
			case _ExamplePopUpId:
			{
				if (_Panels[0].GetWidth() < _Layout.GetTrueWidth())
				{
					_Node->SetWidth(_Layout.GetTrueWidth() - _Panels[0].GetWidth());
					_Node->SetTrueWidth(_Layout.GetTrueWidth() - _Panels[0].GetWidth());
				}
				else
				{
					_Node->SetWidth(0);
					_Node->SetTrueWidth(0);
				}

				_Node->SetHeight(_Layout.GetTrueHeight());
				_Node->SetTrueHeight(_Layout.GetTrueHeight() * (_Layout.GetTrueHeight() >= ExampleMinY) + ExampleMinY * (_Layout.GetTrueHeight() < ExampleMinY));
				_Node->SetScrollX(_Node->GetScrollX() * (_Node->GetScrollX() <= _Node->GetTrueWidth() - _Node->GetWidth()) + (_Node->GetTrueWidth() - _Node->GetWidth()) * (_Node->GetScrollX() > _Node->GetTrueWidth() - _Node->GetWidth()));
				_Node->SetScrollY(_Node->GetScrollY() * (_Node->GetScrollY() <= _Node->GetTrueHeight() - _Node->GetHeight()) + (_Node->GetTrueHeight() - _Node->GetHeight()) * (_Node->GetScrollY() > _Node->GetTrueHeight() - _Node->GetHeight()));
				_Node->SetPositionX(_Layout.GetTrueWidth() - _Node->GetWidth());
				ResizeChilds(*_Node);
				break;
			}
			case BFW::GUI::_NodePopUpId:
			{
				if (_Panels[0].GetWidth() < _Layout.GetTrueWidth())
				{
					_Node->SetWidth(_Layout.GetTrueWidth() - _Panels[0].GetWidth());
					_Node->SetTrueWidth(_Layout.GetTrueWidth() - _Panels[0].GetWidth());
				}
				else
				{
					_Node->SetWidth(0);
					_Node->SetTrueWidth(0);
				}

				_Node->SetHeight(_Layout.GetTrueHeight());
				_Node->SetTrueHeight(_Layout.GetTrueHeight());
				_Node->SetScrollX(_Node->GetScrollX() * (_Node->GetScrollX() <= _Node->GetTrueWidth() - _Node->GetWidth()) + (_Node->GetTrueWidth() - _Node->GetWidth()) * (_Node->GetScrollX() > _Node->GetTrueWidth() - _Node->GetWidth()));
				_Node->SetScrollY(_Node->GetScrollY() * (_Node->GetScrollY() <= _Node->GetTrueHeight() - _Node->GetHeight()) + (_Node->GetTrueHeight() - _Node->GetHeight()) * (_Node->GetScrollY() > _Node->GetTrueHeight() - _Node->GetHeight()));
				_Node->SetPositionX(_Layout.GetTrueWidth() - _Node->GetWidth());
				ResizeChilds(*_Node);
				break;
			}
			default:
			{
				throw nullptr;
			}
			}

			break;
		}
		case BFW::GUI::_RightPanelType:
		{
			switch (_Node->GetId())
			{
			case _ExamplePopUpId:
			{
				if (_Panels[0].GetWidth() < _Layout.GetTrueWidth())
				{
					_Node->SetWidth(_Layout.GetTrueWidth() - _Panels[0].GetWidth());
					_Node->SetTrueWidth(_Layout.GetTrueWidth() - _Panels[0].GetWidth());
				}
				else
				{
					_Node->SetWidth(0);
					_Node->SetTrueWidth(0);
				}

				_Node->SetHeight(_Layout.GetTrueHeight());
				_Node->SetTrueHeight(_Layout.GetTrueHeight() * (_Layout.GetTrueHeight() >= ExampleMinY) + ExampleMinY * (_Layout.GetTrueHeight() < ExampleMinY));
				_Node->SetScrollX(_Node->GetScrollX() * (_Node->GetScrollX() <= _Node->GetTrueWidth() - _Node->GetWidth()) + (_Node->GetTrueWidth() - _Node->GetWidth()) * (_Node->GetScrollX() > _Node->GetTrueWidth() - _Node->GetWidth()));
				_Node->SetScrollY(_Node->GetScrollY() * (_Node->GetScrollY() <= _Node->GetTrueHeight() - _Node->GetHeight()) + (_Node->GetTrueHeight() - _Node->GetHeight()) * (_Node->GetScrollY() > _Node->GetTrueHeight() - _Node->GetHeight()));
				ResizeChilds(*_Node);
				break;
			}
			case BFW::GUI::_NodePopUpId:
			{
				if (_Panels[0].GetWidth() < _Layout.GetTrueWidth())
				{
					_Node->SetWidth(_Layout.GetTrueWidth() - _Panels[0].GetWidth());
					_Node->SetTrueWidth(_Layout.GetTrueWidth() - _Panels[0].GetWidth());
				}
				else
				{
					_Node->SetWidth(0);
					_Node->SetTrueWidth(0);
				}

				_Node->SetHeight(_Layout.GetTrueHeight());
				_Node->SetTrueHeight(_Layout.GetTrueHeight());
				_Node->SetScrollX(_Node->GetScrollX() * (_Node->GetScrollX() <= _Node->GetTrueWidth() - _Node->GetWidth()) + (_Node->GetTrueWidth() - _Node->GetWidth()) * (_Node->GetScrollX() > _Node->GetTrueWidth() - _Node->GetWidth()));
				_Node->SetScrollY(_Node->GetScrollY() * (_Node->GetScrollY() <= _Node->GetTrueHeight() - _Node->GetHeight()) + (_Node->GetTrueHeight() - _Node->GetHeight()) * (_Node->GetScrollY() > _Node->GetTrueHeight() - _Node->GetHeight()));
				ResizeChilds(*_Node);
				break;
			}
			default:
			{
				throw nullptr;
			}
			}

			break;
		}
		case BFW::GUI::_TopPanelType:
		{
			switch (_Node->GetId())
			{
			case _ExamplePopUpId:
			{
				if (_Panels[0].GetHeight() < _Layout.GetTrueHeight())
				{
					_Node->SetHeight(_Layout.GetTrueHeight() - _Panels[0].GetHeight());
					_Node->SetTrueHeight(_Layout.GetTrueHeight() - _Panels[0].GetHeight());
				}
				else
				{
					_Node->SetHeight(0);
					_Node->SetTrueHeight(0);
				}

				_Node->SetWidth(_Layout.GetTrueWidth());
				_Node->SetTrueWidth(_Layout.GetTrueWidth() * (_Layout.GetTrueWidth() >= ExampleMinX) + ExampleMinX * (_Layout.GetTrueWidth() < ExampleMinX));
				_Node->SetScrollX(_Node->GetScrollX() * (_Node->GetScrollX() <= _Node->GetTrueWidth() - _Node->GetWidth()) + (_Node->GetTrueWidth() - _Node->GetWidth()) * (_Node->GetScrollX() > _Node->GetTrueWidth() - _Node->GetWidth()));
				_Node->SetScrollY(_Node->GetScrollY() * (_Node->GetScrollY() <= _Node->GetTrueHeight() - _Node->GetHeight()) + (_Node->GetTrueHeight() - _Node->GetHeight()) * (_Node->GetScrollY() > _Node->GetTrueHeight() - _Node->GetHeight()));
				_Node->SetPositionY(_Layout.GetTrueHeight() - _Node->GetHeight());
				ResizeChilds(*_Node);
				break;
			}
			case BFW::GUI::_NodePopUpId:
			{
				if (_Panels[0].GetHeight() < _Layout.GetTrueHeight())
				{
					_Node->SetHeight(_Layout.GetTrueHeight() - _Panels[0].GetHeight());
					_Node->SetTrueHeight(_Layout.GetTrueHeight() - _Panels[0].GetHeight());
				}
				else
				{
					_Node->SetHeight(0);
					_Node->SetTrueHeight(0);
				}

				_Node->SetWidth(_Layout.GetTrueWidth());
				_Node->SetTrueWidth(_Layout.GetTrueWidth());
				_Node->SetScrollX(_Node->GetScrollX() * (_Node->GetScrollX() <= _Node->GetTrueWidth() - _Node->GetWidth()) + (_Node->GetTrueWidth() - _Node->GetWidth()) * (_Node->GetScrollX() > _Node->GetTrueWidth() - _Node->GetWidth()));
				_Node->SetScrollY(_Node->GetScrollY() * (_Node->GetScrollY() <= _Node->GetTrueHeight() - _Node->GetHeight()) + (_Node->GetTrueHeight() - _Node->GetHeight()) * (_Node->GetScrollY() > _Node->GetTrueHeight() - _Node->GetHeight()));
				_Node->SetPositionY(_Layout.GetTrueHeight() - _Node->GetHeight());
				ResizeChilds(*_Node);
				break;
			}
			default:
			{
				throw nullptr;
			}
			}

			break;
		}
		case BFW::GUI::_BottomPanelType:
		{
			switch (_Node->GetId())
			{
			case _ExamplePopUpId:
			{
				if (_Panels[0].GetHeight() < _Layout.GetTrueHeight())
				{
					_Node->SetHeight(_Layout.GetTrueHeight() - _Panels[0].GetHeight());
					_Node->SetTrueHeight(_Layout.GetTrueHeight() - _Panels[0].GetHeight());
				}
				else
				{
					_Node->SetHeight(0);
					_Node->SetTrueHeight(0);
				}

				_Node->SetWidth(_Layout.GetTrueWidth());
				_Node->SetTrueWidth(_Layout.GetTrueWidth() * (_Layout.GetTrueWidth() >= ExampleMinX) + ExampleMinX * (_Layout.GetTrueWidth() < ExampleMinX));
				_Node->SetScrollX(_Node->GetScrollX() * (_Node->GetScrollX() <= _Node->GetTrueWidth() - _Node->GetWidth()) + (_Node->GetTrueWidth() - _Node->GetWidth()) * (_Node->GetScrollX() > _Node->GetTrueWidth() - _Node->GetWidth()));
				_Node->SetScrollY(_Node->GetScrollY() * (_Node->GetScrollY() <= _Node->GetTrueHeight() - _Node->GetHeight()) + (_Node->GetTrueHeight() - _Node->GetHeight()) * (_Node->GetScrollY() > _Node->GetTrueHeight() - _Node->GetHeight()));
				ResizeChilds(*_Node);
				break;
			}
			case BFW::GUI::_NodePopUpId:
			{
				if (_Panels[0].GetHeight() < _Layout.GetTrueHeight())
				{
					_Node->SetHeight(_Layout.GetTrueHeight() - _Panels[0].GetHeight());
					_Node->SetTrueHeight(_Layout.GetTrueHeight() - _Panels[0].GetHeight());
				}
				else
				{
					_Node->SetHeight(0);
					_Node->SetTrueHeight(0);
				}

				_Node->SetWidth(_Layout.GetTrueWidth());
				_Node->SetTrueWidth(_Layout.GetTrueWidth());
				_Node->SetScrollX(_Node->GetScrollX() * (_Node->GetScrollX() <= _Node->GetTrueWidth() - _Node->GetWidth()) + (_Node->GetTrueWidth() - _Node->GetWidth()) * (_Node->GetScrollX() > _Node->GetTrueWidth() - _Node->GetWidth()));
				_Node->SetScrollY(_Node->GetScrollY()* (_Node->GetScrollY() <= _Node->GetTrueHeight() - _Node->GetHeight()) + (_Node->GetTrueHeight() - _Node->GetHeight()) * (_Node->GetScrollY() > _Node->GetTrueHeight() - _Node->GetHeight()));
				ResizeChilds(*_Node);
				break;
			}
			default:
			{
				throw nullptr;
			}
			}

			break;
		}
		}
	}
}

void BFW_WINDOWS::GUI::GenerateExample(BFW::GUI::PopUp& _Parent, BFW::RunTime::Menu* _Menu)
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
