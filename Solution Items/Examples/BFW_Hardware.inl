#if !defined BFW_DLL_LINK && !defined BFW_STATIC_LINK && !defined BFW_VENDOR

#define BFW_VENDOR

#endif

#if !defined BFW_WINDOWS_PLATFORM && !defined BFW_ARDUINO_PLATFORM

#define BFW_WINDOWS_PLATFORM

#endif



#include "..\..\BFW\Headers\BFW.hpp"



#ifdef BFW_WINDOWS_PLATFORM



void BFW_Hardware_Example_SerialPort()
{
	BFW::Hardware::SerialPort Sp;

	Sp.Open(L"\\\\.\\COM7", 9600);

	while (Sp.CheckConnected())
	{
		Sp.Update();
		char Buff;
		if (Sp.Read(&Buff, 1))
		{
			BFW_PRINT(Buff);
		}
	}
}



bool Exit = false;
int ReturnValue;

BFW::Hardware::Webcam WebCam;
BFW::Hardware::Microphone Microphone;

constexpr unsigned long long ImageWidth = 160, ImageHeight = 90;
unsigned char Image[ImageWidth * ImageHeight * 4];

LRESULT CALLBACK BFW_Hardware_WndProc_Capture(_In_ HWND _hWnd, _In_ UINT _Msg, _In_ WPARAM _wParam, _In_ LPARAM _lParam)
{
	switch (_Msg)
	{
	case WM_CLOSE:
	{
		Exit = true;
		ReturnValue = 0;
		break;
	}
	case WM_DESTROY:
	{
		Exit = true;
		ReturnValue = 0;
		break;
	}
	case WM_KEYDOWN:
	{
		switch (_wParam)
		{
		case VK_ESCAPE:
		{
			Exit = true;
			ReturnValue = 0;
			break;
		}
		case VK_F11:
		{
			static bool _Fullscreen = false;
			static WINDOWPLACEMENT _WndPlace = { 0 };

			_Fullscreen = 1 - _Fullscreen;

			if (_Fullscreen)
			{
				GetWindowPlacement(_hWnd, &_WndPlace);

				HMONITOR _hMonit = MonitorFromWindow(_hWnd, MONITOR_DEFAULTTOPRIMARY);

				MONITORINFO _MonitInfo = { 0 };

				_MonitInfo.cbSize = sizeof(MONITORINFO);

				GetMonitorInfo(_hMonit, &_MonitInfo);

				ShowWindow(_hWnd, SW_HIDE);

				SetWindowLongPtr(_hWnd, GWL_STYLE, WS_POPUP);
				SetWindowPos(_hWnd, HWND_TOP, _MonitInfo.rcMonitor.left, _MonitInfo.rcMonitor.top, _MonitInfo.rcMonitor.right - _MonitInfo.rcMonitor.left, _MonitInfo.rcMonitor.bottom - _MonitInfo.rcMonitor.top, NULL);

				ShowWindow(_hWnd, SW_MAXIMIZE);
			}
			else
			{
				ShowWindow(_hWnd, SW_HIDE);

				SetWindowLongPtr(_hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
				SetWindowPos(_hWnd, HWND_TOP, _WndPlace.rcNormalPosition.left, _WndPlace.rcNormalPosition.top, _WndPlace.rcNormalPosition.right - _WndPlace.rcNormalPosition.left, _WndPlace.rcNormalPosition.bottom - _WndPlace.rcNormalPosition.top, NULL);

				ShowWindow(_hWnd, _WndPlace.showCmd);
			}
			break;
		}
		default:
		{
			return DefWindowProc(_hWnd, _Msg, _wParam, _lParam);
		}
		}
		break;
	}
	case WM_PAINT:
	{
		if (!WebCam.Capture(Image, ImageWidth, ImageHeight))
		{
			Exit = true;
			ReturnValue = 0;
			return 0;
		}

		if (!Microphone.Capture())
		{
			Exit = true;
			ReturnValue = 0;
			return 0;
		}

		unsigned long _BarWidth = ImageWidth / 40;
		unsigned long _BarHeight = 0;

		if (Microphone.GetAudioInfo().wBitsPerSample == 8)
		{
			for (unsigned long _Index = 0; _Index < Microphone.GetBuffSize(); _Index++)
			{
				unsigned long _New = BFW::Math::lModule(((char*)(Microphone.GetBuff()))[_Index]);
				_BarHeight = _BarHeight * (_New <= _BarHeight) + _New * (_New > _BarHeight);
			}
			_BarHeight = BFW::Math::lMap(_BarHeight, 0, 127, 0, ImageHeight);
		}
		if (Microphone.GetAudioInfo().wBitsPerSample == 16)
		{
			for (unsigned long _Index = 0; _Index < Microphone.GetBuffSize() / 2; _Index++)
			{
				unsigned long _New = BFW::Math::lModule(((short*)(Microphone.GetBuff()))[_Index]);
				_BarHeight = _BarHeight * (_New <= _BarHeight) + _New * (_New > _BarHeight);
			}
			_BarHeight = BFW::Math::lMap(_BarHeight, 0, 32767, 0, ImageHeight);
		}

		for (unsigned long _X = ImageWidth - 1 - _BarWidth; _X < ImageWidth; _X++)
		{
			for (unsigned long _Y = ImageHeight - _BarHeight; _Y < ImageHeight; _Y++)
			{
				Image[(_X + _Y * ImageWidth) * 4 + 0] = 0;
				Image[(_X + _Y * ImageWidth) * 4 + 1] = 255;
				Image[(_X + _Y * ImageWidth) * 4 + 2] = 0;
				Image[(_X + _Y * ImageWidth) * 4 + 3] = 255;
			}
		}

		RECT _ClientRect = { 0 };

		GetClientRect(_hWnd, &_ClientRect);

		unsigned int _Width = _ClientRect.right - _ClientRect.left;
		unsigned int _Height = _ClientRect.bottom - _ClientRect.top;

		PAINTSTRUCT _PaintStruct = { 0 };

		HDC _WndDC = BeginPaint(_hWnd, &_PaintStruct);

		HDC _hDC = CreateCompatibleDC(_WndDC);
		HBITMAP _hBmp = CreateBitmap(ImageWidth, ImageHeight, 1, 32, Image);
		HBITMAP _hOldBmp = (HBITMAP)(SelectObject(_hDC, _hBmp));

		StretchBlt(_WndDC, 0, 0, _Width, _Height, _hDC, 0, 0, ImageWidth, ImageHeight, SRCCOPY);

		SelectObject(_hDC, _hOldBmp);
		DeleteDC(_hDC);
		DeleteObject(_hBmp);

		EndPaint(_hWnd, &_PaintStruct);

		InvalidateRect(_hWnd, nullptr, false);

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

int WINAPI BFW_Hardware_Example_Capture(_In_ HINSTANCE _hInstance, _In_opt_ HINSTANCE _hPrevInstance, _In_ LPWSTR _CmdLine, _In_ int _ShowCmd)
{
	if (!BFW::Time::Init())
	{
		return BFW::Enums::_ReturnError;
	}

	if (!BFW::Log::Init())
	{
		BFW::Time::Stop();
		return BFW::Enums::_ReturnError;
	}

	if (CoInitializeEx(nullptr, COINIT_MULTITHREADED) != S_OK)
	{
		BFW::Log::Stop();
		BFW::Time::Stop();
		return BFW::Enums::_ReturnError;
	}

	if (!WebCam.Connect())
	{
		CoUninitialize();
		BFW::Log::Stop();
		BFW::Time::Stop();
		return BFW::Enums::_ReturnError;
	}

	if (!Microphone.Connect())
	{
		WebCam.Disconnect();
		CoUninitialize();
		BFW::Log::Stop();
		BFW::Time::Stop();
		return BFW::Enums::_ReturnError;
	}

	BFW::Log::SetTextAttribute(BFW::Enums::_ConsoleTxtTurquoise);

	BFW_PRINT(WebCam.GetName());
	BFW_PRINT(L'\n');

	BFW_PRINT(WebCam.GetWidth());
	BFW_PRINT(L' ');
	BFW_PRINT(WebCam.GetHeight());
	BFW_PRINT(L'\n');

	BFW_PRINT(WebCam.GetRefreshRate());
	BFW_PRINT(L'\n');

	BFW_PRINT(BFW::Hardware::Webcam::GetCount());
	BFW_PRINT(L'\n');

	BFW_PRINT(L'\n');

	BFW_PRINT(Microphone.GetName());
	BFW_PRINT(L'\n');

	BFW_PRINT(Microphone.GetID());
	BFW_PRINT(L'\n');

	BFW_PRINT(BFW::Hardware::Microphone::GetCount());
	BFW_PRINT(L'\n');

	if (!WebCam.StartRecording())
	{
		Microphone.Disconnect();
		WebCam.Disconnect();
		CoUninitialize();
		BFW::Log::Stop();
		BFW::Time::Stop();
		return BFW::Enums::_ReturnError;
	}

	if (!Microphone.StartRecording())
	{
		Microphone.Disconnect();
		WebCam.StopRecording();
		WebCam.Disconnect();
		CoUninitialize();
		BFW::Log::Stop();
		BFW::Time::Stop();
		return BFW::Enums::_ReturnError;
	}

	WNDCLASSEX _WndClass = { 0 };

	_WndClass.cbSize = sizeof(WNDCLASSEX);
	_WndClass.style = CS_HREDRAW | CS_VREDRAW;
	_WndClass.lpfnWndProc = BFW_Hardware_WndProc_Capture;
	_WndClass.cbClsExtra = 0;
	_WndClass.cbWndExtra = 0;
	_WndClass.hInstance = _hInstance;
	_WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	_WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	_WndClass.hbrBackground = NULL;
	_WndClass.lpszMenuName = NULL;
	_WndClass.lpszClassName = L"WndClass";
	_WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&_WndClass))
	{
		Microphone.StopRecording();
		Microphone.Disconnect();
		WebCam.StopRecording();
		WebCam.Disconnect();
		CoUninitialize();
		BFW::Log::Stop();
		BFW::Time::Stop();
		return BFW::Enums::_ReturnError;
	}

	HWND _hWnd = CreateWindowEx(NULL, _WndClass.lpszClassName, L"Wnd", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, _hInstance, nullptr);

	if (!_hWnd)
	{
		UnregisterClass(_WndClass.lpszClassName, _hInstance);
		Microphone.StopRecording();
		Microphone.Disconnect();
		WebCam.StopRecording();
		WebCam.Disconnect();
		CoUninitialize();
		BFW::Log::Stop();
		BFW::Time::Stop();
		return BFW::Enums::_ReturnError;
	}

	Exit = false;

	MSG _Msg = { 0 };

	ShowWindow(_hWnd, _ShowCmd);

	while (!Exit)
	{
		if (PeekMessage(&_Msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&_Msg);
			DispatchMessage(&_Msg);
		}
		else
		{
			UpdateWindow(_hWnd);
		}
		BFW::Time::SleepMicroSec((unsigned long)(BFW::Time::SecToMicro) / WebCam.GetRefreshRate());
	}

	DestroyWindow(_hWnd);
	UnregisterClass(_WndClass.lpszClassName, _hInstance);

	Microphone.StopRecording();
	Microphone.Disconnect();

	WebCam.StopRecording();
	WebCam.Disconnect();

	CoUninitialize();
	BFW::Log::Stop();
	BFW::Time::Stop();

	return BFW::Enums::_ReturnNoError;
}



#endif



#ifdef BFW_ARDUINO_PLATFORM



void BFW_Hardware_Example()
{
	BFW::Log::Init();

	{
		BFW::Hardware::DigitalOutputPin LedPin;

		LedPin.Bind(3);

		for (unsigned int _Index = 0; _Index < 10; _Index++)
		{
			LedPin.Write(1 - LedPin.GetState());
			BFW::Time::SleepMilliSec(100);
		}
	}

	{
		BFW::Hardware::AnalogOutputPin LedPin;

		LedPin.Bind(3);

		for (unsigned int _Index = 0; _Index < 256; _Index++)
		{
			LedPin.Write(_Index);
			BFW::Time::SleepMilliSec(10);
		}

		for (unsigned int _Index = 254; _Index > 0; _Index--)
		{
			LedPin.Write(_Index);
			BFW::Time::SleepMilliSec(10);
		}

		LedPin.Write(0);
	}

	{
		BFW::Hardware::DigitalInputPullupPin SwitchPin;

		SwitchPin.Bind(4);

		BFW_PRINT("Press the first button!\n");

		while (!SwitchPin[BFW::Enums::_Current])
		{
			SwitchPin.Update();
		}
	}

	{
		BFW::Hardware::DigitalInputPin SwitchPin;

		SwitchPin.Bind(5);

		BFW_PRINT("Press the second button!\n");

		while (!SwitchPin[BFW::Enums::_Current])
		{
			SwitchPin.Update();
		}
	}

	{
		BFW::Hardware::AnalogInputPin JoystickX;
		BFW::Hardware::AnalogInputPin JoystickY;

		JoystickX.Bind(0);
		JoystickY.Bind(1);

		BFW::Hardware::DigitalOutputPin SwitchPin;

		SwitchPin.Bind(6);
		SwitchPin.Write(true);

		BFW_PRINT("Press the joystick button to exit!\n");

		BFW::Time::SleepSec(5);

		while (SwitchPin.Read())
		{
			JoystickX.Update();
			JoystickY.Update();

			BFW_PRINT(JoystickX[BFW::Enums::_Current]);
			BFW_PRINT(' ');
			BFW_PRINT(JoystickY[BFW::Enums::_Current]);
			BFW_PRINT('\n');
		}
	}

	BFW::Log::Stop();
}



#endif
