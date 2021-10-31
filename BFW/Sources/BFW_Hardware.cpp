#include "..\Headers\BFW.hpp"



#ifdef BFW_WINDOWS_PLATFORM



BFW::Hardware::SerialPort::SerialPort() : FileHandle(NULL), Status({ 0 }), PortName(nullptr), Connected(false), BaudRate(0)
{

}

BFW::Hardware::SerialPort::SerialPort(SerialPort&& _Other) noexcept :
	FileHandle(_Other.FileHandle), Status(_Other.Status), PortName(_Other.PortName), Connected(_Other.Connected), BaudRate(_Other.BaudRate)
{
	_Other.FileHandle = NULL;
	_Other.Status = { 0 };
	_Other.PortName = nullptr;
	_Other.Connected = false;
	_Other.BaudRate = 0;
}

BFW::Hardware::SerialPort::~SerialPort()
{
	Close();
}

bool BFW::Hardware::SerialPort::Open(const wchar_t* _PortName, const unsigned long _BaudRate)
{
	Close();

	if (!_PortName || !_BaudRate)
	{
		BFW_DEBUG_BREAK_MSG(L"Can not open port because of invalid parameters!");
		return false;
	}

	PortName = _PortName;
	BaudRate = _BaudRate;

	FileHandle = CreateFile(PortName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (FileHandle == INVALID_HANDLE_VALUE || FileHandle == NULL)
	{
		Connected = false;
		Status = { 0 };
		return false;
	}

	DCB dcbSerialParameters = { 0 };

	if (!GetCommState(FileHandle, &dcbSerialParameters))
	{
		CloseHandle(FileHandle);
		FileHandle = NULL;
		Connected = false;
		Status = { 0 };
		return false;
	}

	dcbSerialParameters.BaudRate = BaudRate;
	dcbSerialParameters.ByteSize = 8;
	dcbSerialParameters.StopBits = ONESTOPBIT;
	dcbSerialParameters.Parity = NOPARITY;
	dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;

	if (!SetCommState(FileHandle, &dcbSerialParameters))
	{
		CloseHandle(FileHandle);
		FileHandle = NULL;
		Connected = false;
		Status = { 0 };
		return false;
	}

	Connected = true;

	return true;
}

bool BFW::Hardware::SerialPort::Update()
{
	if (Connected)
	{
		unsigned long _Error;

		if (!ClearCommError(FileHandle, &_Error, &Status))
		{
			if (FileHandle != NULL && FileHandle != INVALID_HANDLE_VALUE)
			{
				CloseHandle(FileHandle);
				FileHandle = NULL;
			}
			Connected = false;
			Status = { 0 };

			return false;
		}

		return true;
	}

	if (FileHandle != NULL && FileHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(FileHandle);
		FileHandle = NULL;
	}
	Connected = false;
	Status = { 0 };

	return Open(PortName, BaudRate);
}

void BFW::Hardware::SerialPort::Close()
{
	if (FileHandle != NULL && FileHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(FileHandle);
		FileHandle = NULL;
	}
	Connected = false;
	Status = { 0 };
	PortName = nullptr;
	BaudRate = 0;
}

unsigned long BFW::Hardware::SerialPort::Read(char* _Buff, const unsigned long _Size)
{
	if (!Connected)
	{
		return 0;
	}

	unsigned long _Error = 0;

	if (!ClearCommError(FileHandle, &_Error, &Status))
	{
		if (FileHandle != NULL && FileHandle != INVALID_HANDLE_VALUE)
		{
			CloseHandle(FileHandle);
			FileHandle = NULL;
		}
		Connected = false;
		Status = { 0 };

		return 0;
	}

	unsigned long _BytesRead = 0;

	if (!ReadFile(FileHandle, _Buff, _Size * (Status.cbInQue > _Size) + Status.cbInQue * (Status.cbInQue <= _Size), &_BytesRead, NULL))
	{
		if (!ClearCommError(FileHandle, &_Error, &Status))
		{
			if (FileHandle != NULL && FileHandle != INVALID_HANDLE_VALUE)
			{
				CloseHandle(FileHandle);
				FileHandle = NULL;
			}
			Connected = false;
			Status = { 0 };
		}
		return 0;
	}

	return _BytesRead;
}

unsigned long BFW::Hardware::SerialPort::Write(const unsigned char* _Buff, const unsigned long _Size)
{
	if (!Connected)
	{
		return 0;
	}

	unsigned long _Error = 0;

	if (!ClearCommError(FileHandle, &_Error, &Status))
	{
		if (FileHandle != NULL && FileHandle != INVALID_HANDLE_VALUE)
		{
			CloseHandle(FileHandle);
			FileHandle = NULL;
		}
		Connected = false;
		Status = { 0 };

		return 0;
	}

	unsigned long _BytesSent = 0;

	if (!WriteFile(FileHandle, _Buff, _Size, &_BytesSent, 0))
	{
		if (!ClearCommError(FileHandle, &_Error, &Status))
		{
			if (FileHandle != NULL && FileHandle != INVALID_HANDLE_VALUE)
			{
				CloseHandle(FileHandle);
				FileHandle = NULL;
			}
			Connected = false;
			Status = { 0 };
		}
		return 0;
	}

	return _BytesSent;
}

const bool BFW::Hardware::SerialPort::CheckConnected() const
{
	return Connected;
}

const wchar_t* BFW::Hardware::SerialPort::GetPortName() const
{
	return PortName;
}

const unsigned long BFW::Hardware::SerialPort::GetBaudRate() const
{
	return BaudRate;
}

void BFW::Hardware::SerialPort::operator= (SerialPort&& _Other) noexcept
{
	FileHandle = _Other.FileHandle;
	Status = _Other.Status;
	PortName = _Other.PortName;
	Connected = _Other.Connected;
	BaudRate = _Other.BaudRate;

	_Other.FileHandle = NULL;
	_Other.Status = { 0 };
	_Other.PortName = nullptr;
	_Other.Connected = false;
	_Other.BaudRate = 0;
}



BFW::Hardware::Webcam::Webcam() :
	Connected(false), Recording(false),
	Buff(nullptr), BuffSize(0),
	Width(0), Height(0), RefreshRate(0), Name(nullptr),
	CaptureGraphBuilder(nullptr), GraphBuilder(nullptr),
	CreateDevEnum(nullptr), EnumMoniker(nullptr), Moniker(nullptr),
	BindCtx(nullptr), BaseFilter(nullptr), SampleFilter(nullptr), SampleGrabber(nullptr),
	MediaControl(nullptr), MediaEvent(nullptr), RendererFilter(nullptr), PropertyBag(nullptr)
{

}

BFW::Hardware::Webcam::Webcam(Webcam&& _Other) noexcept :
	Connected(_Other.Connected), Recording(_Other.Recording),
	Buff(_Other.Buff), BuffSize(_Other.BuffSize),
	Width(_Other.Width), Height(_Other.Height), RefreshRate(_Other.RefreshRate), Name(_Other.Name),
	CaptureGraphBuilder(_Other.CaptureGraphBuilder), GraphBuilder(_Other.GraphBuilder),
	CreateDevEnum(_Other.CreateDevEnum), EnumMoniker(_Other.EnumMoniker), Moniker(_Other.Moniker),
	BindCtx(_Other.BindCtx), BaseFilter(_Other.BaseFilter), SampleFilter(_Other.SampleFilter), SampleGrabber(_Other.SampleGrabber),
	MediaControl(_Other.MediaControl), MediaEvent(_Other.MediaEvent), RendererFilter(_Other.RendererFilter), PropertyBag(_Other.PropertyBag)
{
	_Other.Connected = false;
	_Other.Recording = false;
	_Other.Buff = nullptr;
	_Other.BuffSize = 0;
	_Other.Width = 0;
	_Other.Height = 0;
	_Other.RefreshRate = 0;
	_Other.Name = nullptr;
	_Other.CaptureGraphBuilder = nullptr;
	_Other.GraphBuilder = nullptr;
	_Other.CreateDevEnum = nullptr;
	_Other.EnumMoniker = nullptr;
	_Other.Moniker = nullptr;
	_Other.BindCtx = nullptr;
	_Other.BaseFilter = nullptr;
	_Other.SampleFilter = nullptr;
	_Other.SampleGrabber = nullptr;
	_Other.MediaControl = nullptr;
	_Other.MediaEvent = nullptr;
	_Other.RendererFilter = nullptr;
	_Other.PropertyBag = nullptr;
}

BFW::Hardware::Webcam::~Webcam()
{
	Disconnect();
}

bool BFW::Hardware::Webcam::Connect(const unsigned long _Index)
{
	Disconnect();

	if (!_Index)
	{
		BFW_DEBUG_BREAK_MSG(L"Can not connect to webcam because of invalid index!");
		return false;
	}

	HRESULT hr = S_OK;

	hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, nullptr, CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, (void**)(&CaptureGraphBuilder));

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	CaptureGraphBuilder->AddRef();

	hr = CoCreateInstance(CLSID_FilterGraph, nullptr, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)(&GraphBuilder));

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	GraphBuilder->AddRef();

	hr = CaptureGraphBuilder->SetFiltergraph(GraphBuilder);

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	hr = CoCreateInstance(CLSID_SystemDeviceEnum, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&CreateDevEnum));

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	CreateDevEnum->AddRef();

	hr = CreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &EnumMoniker, NULL);

	BFW_COM_RELEASE(CreateDevEnum);

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	for (unsigned long _ForIndex = 0; _ForIndex < _Index; _ForIndex++)
	{
		hr = EnumMoniker->Next(1, &Moniker, nullptr);

		if (hr != S_OK)
		{
			Disconnect();
			return false;
		}
	}

	BFW_COM_RELEASE(EnumMoniker);

	hr = CreateBindCtx(NULL, &BindCtx);

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	if (!BindCtx)
	{
		Disconnect();
		return false;
	}

	hr = Moniker->BindToObject(BindCtx, nullptr, IID_IBaseFilter, (void**)(&BaseFilter));

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	hr = GraphBuilder->AddFilter(BaseFilter, L"BaseFilter");

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	hr = CoCreateInstance(CLSID_SampleGrabber, nullptr, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)(&SampleFilter));

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	SampleFilter->AddRef();

	hr = SampleFilter->QueryInterface(IID_ISampleGrabber, (void**)(&SampleGrabber));

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	{
		AM_MEDIA_TYPE _MediaType = { 0 };

		_MediaType.majortype = MEDIATYPE_Video;
		_MediaType.subtype = MEDIASUBTYPE_RGB32;

		hr = SampleGrabber->SetMediaType(&_MediaType);
	}

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	hr = SampleGrabber->SetOneShot(FALSE);

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	hr = SampleGrabber->SetBufferSamples(TRUE);

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	hr = GraphBuilder->AddFilter(SampleFilter, L"SampleFilter");

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	hr = GraphBuilder->QueryInterface(IID_IMediaControl, (void**)(&MediaControl));

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	hr = GraphBuilder->QueryInterface(IID_IMediaEventEx, (void**)(&MediaEvent));

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	hr = CoCreateInstance(CLSID_NullRenderer, nullptr, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)(&RendererFilter));

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	hr = GraphBuilder->AddFilter(RendererFilter, L"RendererFilter");

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	hr = Moniker->BindToStorage(BindCtx, nullptr, IID_IPropertyBag, (void**)(&PropertyBag));

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	{
		VARIANT _Variant = { 0 };

		VariantInit(&_Variant);

		hr = PropertyBag->Read(L"FriendlyName", &_Variant, nullptr);

		if (hr != S_OK)
		{
			Disconnect();
			return false;
		}

		size_t _StrLen = wcslen(_Variant.bstrVal);

		Name = new wchar_t[_StrLen + 1];

		if (!Name)
		{
			Disconnect();
			return false;
		}

		for (unsigned long _ForIndex = 0; _ForIndex < _StrLen + 1; _ForIndex++)
		{
			Name[_ForIndex] = _Variant.bstrVal[_ForIndex];
		}

		VariantClear(&_Variant);
	}

	hr = CaptureGraphBuilder->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video, BaseFilter, SampleFilter, RendererFilter);

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	{
		AM_MEDIA_TYPE _MediaType = { 0 };

		hr = SampleGrabber->GetConnectedMediaType(&_MediaType);

		if (hr != S_OK)
		{
			Disconnect();
			return false;
		}

		VIDEOINFOHEADER* _VideoInfo = (VIDEOINFOHEADER*)(_MediaType.pbFormat);

		if (!_VideoInfo)
		{
			Disconnect();
			return false;
		}

		Width = _VideoInfo->bmiHeader.biWidth;
		Height = _VideoInfo->bmiHeader.biHeight;
		RefreshRate = _VideoInfo->dwBitRate / (8 * 4 * Width * Height);

		if (_MediaType.cbFormat != 0)
		{
			CoTaskMemFree((PVOID)(_MediaType.pbFormat));
			_MediaType.cbFormat = 0;
			_MediaType.pbFormat = nullptr;
		}

		BFW_COM_RELEASE(_MediaType.pUnk);
	}

	Connected = true;

	return true;
}

void BFW::Hardware::Webcam::Disconnect()
{
	Connected = false;

	HRESULT hr = S_OK;

	if (Recording)
	{
		Recording = false;
		hr = MediaControl->Stop();
	}

	if (Buff)
	{
		BuffSize = 0;
		delete[] Buff;
		Buff = nullptr;
	}

	if (Name)
	{
		delete[] Name;
		Name = nullptr;
	}

	Width = 0;
	Height = 0;
	RefreshRate = 0;

	BFW_COM_RELEASE(PropertyBag);
	BFW_COM_RELEASE(RendererFilter);
	BFW_COM_RELEASE(MediaEvent);
	BFW_COM_RELEASE(MediaControl);
	BFW_COM_RELEASE(SampleGrabber);
	BFW_COM_RELEASE(SampleFilter);
	BFW_COM_RELEASE(BaseFilter);
	BFW_COM_RELEASE(BindCtx);
	BFW_COM_RELEASE(Moniker);
	BFW_COM_RELEASE(EnumMoniker);
	BFW_COM_RELEASE(CreateDevEnum);
	BFW_COM_RELEASE(GraphBuilder);
	BFW_COM_RELEASE(CaptureGraphBuilder);
}

bool BFW::Hardware::Webcam::StartRecording()
{
	if (!Connected)
	{
		return false;
	}

	HRESULT hr = S_OK;

	hr = MediaControl->Run();

	BuffSize = 0;

	while (!BuffSize)
	{
		hr = SampleGrabber->GetCurrentBuffer((long*)(&BuffSize), (long*)(nullptr));

		switch (hr)
		{
		case E_INVALIDARG:
		{
			break;
		}
		case E_OUTOFMEMORY:
		{
			break;
		}
		case E_POINTER:
		{
			break;
		}
		case S_OK:
		{
			break;
		}
		case VFW_E_WRONG_STATE:
		{
			break;
		}
		case VFW_E_NOT_CONNECTED:
		{
			Disconnect();
			return false;
		}
		default:
		{
			Disconnect();
			return false;
		}
		}
	}

	Buff = new unsigned char[BuffSize];

	if (!Buff)
	{
		Disconnect();
		return false;
	}

	Recording = true;

	return true;
}

void BFW::Hardware::Webcam::StopRecording()
{
	if (!Recording)
	{
		return;
	}

	Recording = false;

	if (Buff)
	{
		BuffSize = 0;
		delete[] Buff;
		Buff = nullptr;
	}

	HRESULT hr = S_OK;

	hr = MediaControl->Stop();

	if (hr != S_OK)
	{
		Disconnect();
		return;
	}
}

bool BFW::Hardware::Webcam::Capture(unsigned char* _Buff, const unsigned long _Width, const unsigned long _Height)
{
	if (!_Buff || !_Width || !_Height)
	{
		BFW_DEBUG_BREAK_MSG(L"Can not write webcam image to buffer because of invalid capture parameters!");
		return false;
	}

	if (!Recording)
	{
		return false;
	}

	HRESULT hr = S_OK;

	hr = SampleGrabber->GetCurrentBuffer((long*)(&BuffSize), (long*)(Buff));

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	for (unsigned long _X = 0; _X < _Width; _X++)
	{
		for (unsigned long _Y = 0; _Y < _Height; _Y++)
		{
			_Buff[(_X + _Y * _Width) * 4 + 0] = Buff[(Width * Height - 1 - Math::lMap(_X, 0, _Width, 0, Width) - Math::lMap(_Y, 0, _Height, 0, Height) * Width) * 4 + 0];
			_Buff[(_X + _Y * _Width) * 4 + 1] = Buff[(Width * Height - 1 - Math::lMap(_X, 0, _Width, 0, Width) - Math::lMap(_Y, 0, _Height, 0, Height) * Width) * 4 + 1];
			_Buff[(_X + _Y * _Width) * 4 + 2] = Buff[(Width * Height - 1 - Math::lMap(_X, 0, _Width, 0, Width) - Math::lMap(_Y, 0, _Height, 0, Height) * Width) * 4 + 2];
			_Buff[(_X + _Y * _Width) * 4 + 3] = Buff[(Width * Height - 1 - Math::lMap(_X, 0, _Width, 0, Width) - Math::lMap(_Y, 0, _Height, 0, Height) * Width) * 4 + 3];
		}
	}

	return true;
}

const bool BFW::Hardware::Webcam::CheckConnected() const
{
	return Connected;
}

const bool BFW::Hardware::Webcam::CheckRecording() const
{
	return Recording;
}

const unsigned long BFW::Hardware::Webcam::GetWidth() const
{
	return Width;
}

const unsigned long BFW::Hardware::Webcam::GetHeight() const
{
	return Height;
}

const unsigned long BFW::Hardware::Webcam::GetRefreshRate() const
{
	return RefreshRate;
}

const wchar_t* BFW::Hardware::Webcam::GetName() const
{
	return Name;
}

unsigned long BFW::Hardware::Webcam::GetCount()
{
	unsigned long _Index = 0;
	Webcam _Webcam;

	do
	{
		if (_Webcam.CheckConnected())
		{
			_Webcam.Disconnect();
		}
		if (_Webcam.Connect(_Index + 1))
		{
			_Index++;
		}
	} while (_Webcam.CheckConnected());

	return _Index;
}

void BFW::Hardware::Webcam::operator= (Webcam&& _Other) noexcept
{
	Connected = _Other.Connected;
	Recording = _Other.Recording;
	Buff = _Other.Buff;
	BuffSize = _Other.BuffSize;
	Width = _Other.Width;
	Height = _Other.Height;
	RefreshRate = _Other.RefreshRate;
	Name = _Other.Name;
	CaptureGraphBuilder = _Other.CaptureGraphBuilder;
	GraphBuilder = _Other.GraphBuilder;
	CreateDevEnum = _Other.CreateDevEnum;
	EnumMoniker = _Other.EnumMoniker;
	Moniker = _Other.Moniker;
	BindCtx = _Other.BindCtx;
	BaseFilter = _Other.BaseFilter;
	SampleFilter = _Other.SampleFilter;
	SampleGrabber = _Other.SampleGrabber;
	MediaControl = _Other.MediaControl;
	MediaEvent = _Other.MediaEvent;
	RendererFilter = _Other.RendererFilter;
	PropertyBag = _Other.PropertyBag;

	_Other.Connected = false;
	_Other.Recording = false;
	_Other.Buff = nullptr;
	_Other.BuffSize = 0;
	_Other.Width = 0;
	_Other.Height = 0;
	_Other.RefreshRate = 0;
	_Other.Name = nullptr;
	_Other.CaptureGraphBuilder = nullptr;
	_Other.GraphBuilder = nullptr;
	_Other.CreateDevEnum = nullptr;
	_Other.EnumMoniker = nullptr;
	_Other.Moniker = nullptr;
	_Other.BindCtx = nullptr;
	_Other.BaseFilter = nullptr;
	_Other.SampleFilter = nullptr;
	_Other.SampleGrabber = nullptr;
	_Other.MediaControl = nullptr;
	_Other.MediaEvent = nullptr;
	_Other.RendererFilter = nullptr;
	_Other.PropertyBag = nullptr;
}



BFW::Hardware::Microphone::Microphone() :
	Connected(false), Recording(false),
	Buff(nullptr), BuffSize(0),
	AudioInfo({ 0 }), Name(nullptr), ID(0),
	CaptureGraphBuilder(nullptr), GraphBuilder(nullptr),
	CreateDevEnum(nullptr), EnumMoniker(nullptr), Moniker(nullptr),
	BindCtx(nullptr), BaseFilter(nullptr), SampleFilter(nullptr), SampleGrabber(nullptr),
	MediaControl(nullptr), MediaEvent(nullptr), RendererFilter(nullptr), PropertyBag(nullptr)
{

}

BFW::Hardware::Microphone::Microphone(Microphone&& _Other) noexcept :
	Connected(_Other.Connected), Recording(_Other.Recording),
	Buff(_Other.Buff), BuffSize(_Other.BuffSize),
	AudioInfo(_Other.AudioInfo), Name(_Other.Name), ID(_Other.ID),
	CaptureGraphBuilder(_Other.CaptureGraphBuilder), GraphBuilder(_Other.GraphBuilder),
	CreateDevEnum(_Other.CreateDevEnum), EnumMoniker(_Other.EnumMoniker), Moniker(_Other.Moniker),
	BindCtx(_Other.BindCtx), BaseFilter(_Other.BaseFilter), SampleFilter(_Other.SampleFilter), SampleGrabber(_Other.SampleGrabber),
	MediaControl(_Other.MediaControl), MediaEvent(_Other.MediaEvent), RendererFilter(_Other.RendererFilter), PropertyBag(_Other.PropertyBag)
{
	_Other.Connected = false;
	_Other.Recording = false;
	_Other.Buff = nullptr;
	_Other.BuffSize = 0;
	_Other.AudioInfo = { 0 };
	_Other.Name = nullptr;
	_Other.ID = 0;
	_Other.CaptureGraphBuilder = nullptr;
	_Other.GraphBuilder = nullptr;
	_Other.CreateDevEnum = nullptr;
	_Other.EnumMoniker = nullptr;
	_Other.Moniker = nullptr;
	_Other.BindCtx = nullptr;
	_Other.BaseFilter = nullptr;
	_Other.SampleFilter = nullptr;
	_Other.SampleGrabber = nullptr;
	_Other.MediaControl = nullptr;
	_Other.MediaEvent = nullptr;
	_Other.RendererFilter = nullptr;
	_Other.PropertyBag = nullptr;
}

BFW::Hardware::Microphone::~Microphone()
{
	Disconnect();
}

bool BFW::Hardware::Microphone::Connect(const unsigned long _Index)
{
	Disconnect();

	if (!_Index)
	{
		BFW_DEBUG_BREAK_MSG(L"Can not connect to microphone because of invalid index!");
		return false;
	}

	HRESULT hr = S_OK;

	hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, nullptr, CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, (void**)(&CaptureGraphBuilder));

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	CaptureGraphBuilder->AddRef();

	hr = CoCreateInstance(CLSID_FilterGraph, nullptr, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)(&GraphBuilder));

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	GraphBuilder->AddRef();

	hr = CaptureGraphBuilder->SetFiltergraph(GraphBuilder);

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	hr = CoCreateInstance(CLSID_SystemDeviceEnum, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&CreateDevEnum));

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	CreateDevEnum->AddRef();

	hr = CreateDevEnum->CreateClassEnumerator(CLSID_AudioInputDeviceCategory, &EnumMoniker, NULL);

	BFW_COM_RELEASE(CreateDevEnum);

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	for (unsigned long _ForIndex = 0; _ForIndex < _Index; _ForIndex++)
	{
		hr = EnumMoniker->Next(1, &Moniker, nullptr);

		if (hr != S_OK)
		{
			Disconnect();
			return false;
		}
	}

	BFW_COM_RELEASE(EnumMoniker);

	hr = CreateBindCtx(NULL, &BindCtx);

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	if (!BindCtx)
	{
		Disconnect();
		return false;
	}

	hr = Moniker->BindToObject(BindCtx, nullptr, IID_IBaseFilter, (void**)(&BaseFilter));

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	hr = GraphBuilder->AddFilter(BaseFilter, L"BaseFilter");

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	hr = CoCreateInstance(CLSID_SampleGrabber, nullptr, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)(&SampleFilter));

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	SampleFilter->AddRef();

	hr = SampleFilter->QueryInterface(IID_ISampleGrabber, (void**)(&SampleGrabber));

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	{
		AM_MEDIA_TYPE _MediaType = { 0 };

		_MediaType.majortype = MEDIATYPE_Audio;
		_MediaType.subtype = MEDIASUBTYPE_PCM;

		hr = SampleGrabber->SetMediaType(&_MediaType);
	}

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	hr = SampleGrabber->SetOneShot(FALSE);

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	hr = SampleGrabber->SetBufferSamples(TRUE);

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	hr = GraphBuilder->AddFilter(SampleFilter, L"SampleFilter");

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	hr = GraphBuilder->QueryInterface(IID_IMediaControl, (void**)(&MediaControl));

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	hr = GraphBuilder->QueryInterface(IID_IMediaEventEx, (void**)(&MediaEvent));

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	hr = CoCreateInstance(CLSID_NullRenderer, nullptr, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)(&RendererFilter));

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	hr = GraphBuilder->AddFilter(RendererFilter, L"RendererFilter");

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	hr = Moniker->BindToStorage(BindCtx, nullptr, IID_IPropertyBag, (void**)(&PropertyBag));

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	{
		VARIANT _Variant = { 0 };

		VariantInit(&_Variant);

		hr = PropertyBag->Read(L"FriendlyName", &_Variant, nullptr);

		if (hr != S_OK)
		{
			Disconnect();
			return false;
		}

		size_t _StrLen = wcslen(_Variant.bstrVal);

		Name = new wchar_t[_StrLen + 1];

		if (!Name)
		{
			Disconnect();
			return false;
		}

		for (unsigned long _ForIndex = 0; _ForIndex < _StrLen + 1; _ForIndex++)
		{
			Name[_ForIndex] = _Variant.bstrVal[_ForIndex];
		}

		VariantClear(&_Variant);

		_Variant = { 0 };

		VariantInit(&_Variant);

		hr = PropertyBag->Read(L"WaveInID", &_Variant, nullptr);

		if (hr != S_OK)
		{
			Disconnect();
			return false;
		}

		ID = _Variant.lVal;

		VariantClear(&_Variant);
	}

	hr = CaptureGraphBuilder->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Audio, BaseFilter, SampleFilter, RendererFilter);

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	{
		AM_MEDIA_TYPE _MediaType = { 0 };

		hr = SampleGrabber->GetConnectedMediaType(&_MediaType);

		if (hr != S_OK)
		{
			Disconnect();
			return false;
		}

		WAVEFORMATEX* _AudioInfo = (WAVEFORMATEX*)(_MediaType.pbFormat);

		if (!_AudioInfo)
		{
			Disconnect();
			return false;
		}

		AudioInfo = *_AudioInfo;

		if (_MediaType.cbFormat != 0)
		{
			CoTaskMemFree((PVOID)(_MediaType.pbFormat));
			_MediaType.cbFormat = 0;
			_MediaType.pbFormat = nullptr;
		}

		BFW_COM_RELEASE(_MediaType.pUnk);
	}

	Connected = true;

	return true;
}

void BFW::Hardware::Microphone::Disconnect()
{
	Connected = false;

	HRESULT hr = S_OK;

	if (Recording)
	{
		Recording = false;
		hr = MediaControl->Stop();
	}

	if (Buff)
	{
		BuffSize = 0;
		delete[] Buff;
		Buff = nullptr;
	}

	if (Name)
	{
		delete[] Name;
		Name = nullptr;
	}

	AudioInfo = { 0 };
	ID = 0;

	BFW_COM_RELEASE(PropertyBag);
	BFW_COM_RELEASE(RendererFilter);
	BFW_COM_RELEASE(MediaEvent);
	BFW_COM_RELEASE(MediaControl);
	BFW_COM_RELEASE(SampleGrabber);
	BFW_COM_RELEASE(SampleFilter);
	BFW_COM_RELEASE(BaseFilter);
	BFW_COM_RELEASE(BindCtx);
	BFW_COM_RELEASE(Moniker);
	BFW_COM_RELEASE(EnumMoniker);
	BFW_COM_RELEASE(CreateDevEnum);
	BFW_COM_RELEASE(GraphBuilder);
	BFW_COM_RELEASE(CaptureGraphBuilder);
}

bool BFW::Hardware::Microphone::StartRecording()
{
	if (!Connected)
	{
		return false;
	}

	HRESULT hr = S_OK;

	hr = MediaControl->Run();

	BuffSize = 0;

	while (!BuffSize)
	{
		hr = SampleGrabber->GetCurrentBuffer((long*)(&BuffSize), (long*)(nullptr));

		switch (hr)
		{
		case E_INVALIDARG:
		{
			break;
		}
		case E_OUTOFMEMORY:
		{
			break;
		}
		case E_POINTER:
		{
			break;
		}
		case S_OK:
		{
			break;
		}
		case VFW_E_WRONG_STATE:
		{
			break;
		}
		case VFW_E_NOT_CONNECTED:
		{
			Disconnect();
			return false;
		}
		default:
		{
			Disconnect();
			return false;
		}
		}
	}

	Buff = new unsigned char[BuffSize];

	if (!Buff)
	{
		Disconnect();
		return false;
	}

	Recording = true;

	return true;
}

void BFW::Hardware::Microphone::StopRecording()
{
	if (!Recording)
	{
		return;
	}

	Recording = false;

	if (Buff)
	{
		BuffSize = 0;
		delete[] Buff;
		Buff = nullptr;
	}

	HRESULT hr = S_OK;

	hr = MediaControl->Stop();

	if (hr != S_OK)
	{
		Disconnect();
		return;
	}
}

bool BFW::Hardware::Microphone::Capture()
{
	if (!Recording)
	{
		return false;
	}

	HRESULT hr = S_OK;

	hr = SampleGrabber->GetCurrentBuffer((long*)(&BuffSize), (long*)(Buff));

	if (hr != S_OK)
	{
		Disconnect();
		return false;
	}

	return true;
}

const unsigned long BFW::Hardware::Microphone::GetBuffSize() const
{
	return BuffSize;
}

const unsigned char* BFW::Hardware::Microphone::GetBuff() const
{
	return Buff;
}

const bool BFW::Hardware::Microphone::CheckConnected() const
{
	return Connected;
}

const bool BFW::Hardware::Microphone::CheckRecording() const
{
	return Recording;
}

const WAVEFORMATEX BFW::Hardware::Microphone::GetAudioInfo() const
{
	return AudioInfo;
}

const wchar_t* BFW::Hardware::Microphone::GetName() const
{
	return Name;
}

const unsigned long BFW::Hardware::Microphone::GetID() const
{
	return ID;
}

unsigned long BFW::Hardware::Microphone::GetCount()
{
	unsigned long _Index = 0;
	Microphone _Microphone;

	do
	{
		if (_Microphone.CheckConnected())
		{
			_Microphone.Disconnect();
		}
		if (_Microphone.Connect(_Index + 1))
		{
			_Index++;
		}
	} while (_Microphone.CheckConnected());

	return _Index;
}

void BFW::Hardware::Microphone::operator= (Microphone&& _Other) noexcept
{
	Connected = _Other.Connected;
	Recording = _Other.Recording;
	Buff = _Other.Buff;
	BuffSize = _Other.BuffSize;
	AudioInfo = _Other.AudioInfo;
	Name = _Other.Name;
	ID = _Other.ID;
	CaptureGraphBuilder = _Other.CaptureGraphBuilder;
	GraphBuilder = _Other.GraphBuilder;
	CreateDevEnum = _Other.CreateDevEnum;
	EnumMoniker = _Other.EnumMoniker;
	Moniker = _Other.Moniker;
	BindCtx = _Other.BindCtx;
	BaseFilter = _Other.BaseFilter;
	SampleFilter = _Other.SampleFilter;
	SampleGrabber = _Other.SampleGrabber;
	MediaControl = _Other.MediaControl;
	MediaEvent = _Other.MediaEvent;
	RendererFilter = _Other.RendererFilter;
	PropertyBag = _Other.PropertyBag;

	_Other.Connected = false;
	_Other.Recording = false;
	_Other.Buff = nullptr;
	_Other.BuffSize = 0;
	_Other.AudioInfo = { 0 };
	_Other.Name = nullptr;
	_Other.ID = 0;
	_Other.CaptureGraphBuilder = nullptr;
	_Other.GraphBuilder = nullptr;
	_Other.CreateDevEnum = nullptr;
	_Other.EnumMoniker = nullptr;
	_Other.Moniker = nullptr;
	_Other.BindCtx = nullptr;
	_Other.BaseFilter = nullptr;
	_Other.SampleFilter = nullptr;
	_Other.SampleGrabber = nullptr;
	_Other.MediaControl = nullptr;
	_Other.MediaEvent = nullptr;
	_Other.RendererFilter = nullptr;
	_Other.PropertyBag = nullptr;
}



#endif



#ifdef BFW_ARDUINO_PLATFORM



BFW::Hardware::DigitalInputPullupPin::DigitalInputPullupPin() : Number((unsigned long)(-1)), HoldTimer(), State()
{
	State[Enums::_Previous] = false;
	State[Enums::_Current] = false;
}

BFW::Hardware::DigitalInputPullupPin::DigitalInputPullupPin(DigitalInputPullupPin&& _Other) noexcept :
	Number(_Other.Number), HoldTimer((Time::Timer&&)(_Other.Number)), State()
{
	State[Enums::_Previous] = _Other.State[Enums::_Previous];
	State[Enums::_Current] = _Other.State[Enums::_Previous];

	_Other.Number = (unsigned long)(-1);
	_Other.State[Enums::_Previous] = false;
	_Other.State[Enums::_Current] = false;
}

BFW::Hardware::DigitalInputPullupPin::~DigitalInputPullupPin()
{

}

void BFW::Hardware::DigitalInputPullupPin::Update()
{
	State[Enums::_Previous] = State[Enums::_Current];
	State[Enums::_Current] = digitalRead(Number);

	if (!State[Enums::_Previous] && !State[Enums::_Current])
	{
		HoldTimer.Reset();
	}

	if (!State[Enums::_Previous] && State[Enums::_Current])
	{
		HoldTimer.Start();
	}
	if (State[Enums::_Previous] && !State[Enums::_Current])
	{
		HoldTimer.Stop();
	}
}

void BFW::Hardware::DigitalInputPullupPin::DeleteState()
{
	State[Enums::_Previous] = false;
	State[Enums::_Current] = false;
	HoldTimer.Reset();
}

void BFW::Hardware::DigitalInputPullupPin::Bind(const unsigned long _Number)
{
	Number = _Number;
	State[Enums::_Previous] = false;
	State[Enums::_Current] = false;
	HoldTimer.Reset();

	if (Number == (unsigned long)(-1))
	{
		return;
	}

	pinMode(Number, INPUT_PULLUP);
}

const unsigned long BFW::Hardware::DigitalInputPullupPin::GetNumber() const
{
	return Number;
}

const BFW::Time::Timer& BFW::Hardware::DigitalInputPullupPin::GetHoldTimer() const
{
	return HoldTimer;
}

const bool BFW::Hardware::DigitalInputPullupPin::operator[] (const unsigned long _Index) const
{
	return State[_Index];
}

void BFW::Hardware::DigitalInputPullupPin::operator= (DigitalInputPullupPin&& _Other) noexcept
{
	Number = _Other.Number;
	HoldTimer = (Time::Timer&&)(_Other.Number);
	State[Enums::_Previous] = _Other.State[Enums::_Previous];
	State[Enums::_Current] = _Other.State[Enums::_Previous];

	_Other.Number = (unsigned long)(-1);
	_Other.State[Enums::_Previous] = false;
	_Other.State[Enums::_Current] = false;
}



BFW::Hardware::DigitalInputPin::DigitalInputPin() : Number((unsigned long)(-1)), HoldTimer(), State()
{
	State[Enums::_Previous] = false;
	State[Enums::_Current] = false;
}

BFW::Hardware::DigitalInputPin::DigitalInputPin(DigitalInputPin&& _Other) noexcept :
	Number(_Other.Number), HoldTimer((Time::Timer&&)(_Other.Number)), State()
{
	State[Enums::_Previous] = _Other.State[Enums::_Previous];
	State[Enums::_Current] = _Other.State[Enums::_Previous];

	_Other.Number = (unsigned long)(-1);
	_Other.State[Enums::_Previous] = false;
	_Other.State[Enums::_Current] = false;
}

BFW::Hardware::DigitalInputPin::~DigitalInputPin()
{

}

void BFW::Hardware::DigitalInputPin::Update()
{
	State[Enums::_Previous] = State[Enums::_Current];
	State[Enums::_Current] = digitalRead(Number);

	if (!State[Enums::_Previous] && !State[Enums::_Current])
	{
		HoldTimer.Reset();
	}

	if (!State[Enums::_Previous] && State[Enums::_Current])
	{
		HoldTimer.Start();
	}
	if (State[Enums::_Previous] && !State[Enums::_Current])
	{
		HoldTimer.Stop();
	}
}

void BFW::Hardware::DigitalInputPin::DeleteState()
{
	State[Enums::_Previous] = false;
	State[Enums::_Current] = false;
	HoldTimer.Reset();
}

void BFW::Hardware::DigitalInputPin::Bind(const unsigned long _Number)
{
	Number = _Number;
	State[Enums::_Previous] = false;
	State[Enums::_Current] = false;
	HoldTimer.Reset();

	if (Number == (unsigned long)(-1))
	{
		return;
	}

	pinMode(Number, INPUT);
}

const unsigned long BFW::Hardware::DigitalInputPin::GetNumber() const
{
	return Number;
}

const BFW::Time::Timer& BFW::Hardware::DigitalInputPin::GetHoldTimer() const
{
	return HoldTimer;
}

const bool BFW::Hardware::DigitalInputPin::operator[] (const unsigned long _Index) const
{
	return State[_Index];
}

void BFW::Hardware::DigitalInputPin::operator= (DigitalInputPin&& _Other) noexcept
{
	Number = _Other.Number;
	HoldTimer = (Time::Timer&&)(_Other.Number);
	State[Enums::_Previous] = _Other.State[Enums::_Previous];
	State[Enums::_Current] = _Other.State[Enums::_Previous];

	_Other.Number = (unsigned long)(-1);
	_Other.State[Enums::_Previous] = false;
	_Other.State[Enums::_Current] = false;
}



BFW::Hardware::DigitalOutputPin::DigitalOutputPin() : Number((unsigned long)(-1)), HoldTimer(), State(false)
{

}

BFW::Hardware::DigitalOutputPin::DigitalOutputPin(DigitalOutputPin&& _Other) noexcept :
	Number(_Other.Number), HoldTimer((Time::Timer&&)(_Other.HoldTimer)), State(_Other.State)
{
	_Other.Number = (unsigned long)(-1);
	_Other.State = false;
}

BFW::Hardware::DigitalOutputPin::~DigitalOutputPin()
{

}

void BFW::Hardware::DigitalOutputPin::Write(const bool _State)
{
	if (Number == (unsigned long)(-1))
	{
		return;
	}
	digitalWrite(Number, _State);
	State = _State;
}

const bool BFW::Hardware::DigitalOutputPin::Read() const
{
	return digitalRead(Number);
}

void BFW::Hardware::DigitalOutputPin::Bind(const unsigned long _Number)
{
	Number = _Number;
	State = false;
	HoldTimer.Reset();

	if (Number == (unsigned long)(-1))
	{
		return;
	}

	pinMode(Number, OUTPUT);
}

const unsigned long BFW::Hardware::DigitalOutputPin::GetNumber() const
{
	return Number;
}

const BFW::Time::Timer& BFW::Hardware::DigitalOutputPin::GetHoldTimer() const
{
	return HoldTimer;
}

const bool BFW::Hardware::DigitalOutputPin::GetState() const
{
	return State;
}

void BFW::Hardware::DigitalOutputPin::operator= (DigitalOutputPin&& _Other) noexcept
{
	Number = _Other.Number;
	HoldTimer = (Time::Timer&&)(_Other.HoldTimer);
	State = _Other.State;

	_Other.Number = (unsigned long)(-1);
	_Other.State = false;
}



BFW::Hardware::AnalogInputPin::AnalogInputPin() : Number((unsigned long)(-1)), State()
{
	State[Enums::_Previous] = 0;
	State[Enums::_Current] = 0;
}

BFW::Hardware::AnalogInputPin::AnalogInputPin(AnalogInputPin&& _Other) noexcept : Number(_Other.Number), State()
{
	State[Enums::_Previous] = _Other.State[Enums::_Previous];
	State[Enums::_Current] = _Other.State[Enums::_Current];

	_Other.Number = (unsigned long)(-1);
	_Other.State[Enums::_Previous] = 0;
	_Other.State[Enums::_Current] = 0;
}

BFW::Hardware::AnalogInputPin::~AnalogInputPin()
{

}

void BFW::Hardware::AnalogInputPin::Update()
{
	State[Enums::_Previous] = State[Enums::_Current];
	State[Enums::_Current] = analogRead(Number);
}

void BFW::Hardware::AnalogInputPin::DeleteState()
{
	State[Enums::_Previous] = 0;
	State[Enums::_Current] = 0;
}

void BFW::Hardware::AnalogInputPin::Bind(const unsigned long _Number)
{
	Number = _Number;
	State[Enums::_Previous] = 0;
	State[Enums::_Current] = 0;
}

const unsigned long BFW::Hardware::AnalogInputPin::GetNumber() const
{
	return Number;
}

const unsigned long BFW::Hardware::AnalogInputPin::operator[] (const unsigned long _Index) const
{
	return State[_Index];
}

void BFW::Hardware::AnalogInputPin::operator= (AnalogInputPin&& _Other) noexcept
{
	Number = _Other.Number;
	State[Enums::_Previous] = _Other.State[Enums::_Previous];
	State[Enums::_Current] = _Other.State[Enums::_Current];

	_Other.Number = (unsigned long)(-1);
	_Other.State[Enums::_Previous] = 0;
	_Other.State[Enums::_Current] = 0;
}



BFW::Hardware::AnalogOutputPin::AnalogOutputPin() : Number((unsigned long)(-1)), HoldTimer(), State(0)
{

}

BFW::Hardware::AnalogOutputPin::AnalogOutputPin(AnalogOutputPin&& _Other) noexcept :
	Number(_Other.Number), HoldTimer((Time::Timer&&)(_Other.HoldTimer)), State(_Other.State)
{
	_Other.Number = (unsigned long)(-1);
	_Other.State = 0;
}

BFW::Hardware::AnalogOutputPin::~AnalogOutputPin()
{

}

void BFW::Hardware::AnalogOutputPin::Write(const unsigned char _State)
{
	if (Number == (unsigned long)(-1))
	{
		return;
	}
	analogWrite(Number, _State);
	State = _State;
}

void BFW::Hardware::AnalogOutputPin::Bind(const unsigned long _Number)
{
	Number = _Number;
	State = 0;
	HoldTimer.Reset();

	if (Number == (unsigned long)(-1))
	{
		return;
	}

	pinMode(Number, OUTPUT);
}

const unsigned long BFW::Hardware::AnalogOutputPin::GetNumber() const
{
	return Number;
}

const BFW::Time::Timer& BFW::Hardware::AnalogOutputPin::GetHoldTimer() const
{
	return HoldTimer;
}

const unsigned char BFW::Hardware::AnalogOutputPin::GetState() const
{
	return State;
}

void BFW::Hardware::AnalogOutputPin::operator= (AnalogOutputPin&& _Other) noexcept
{
	Number = _Other.Number;
	HoldTimer = (Time::Timer&&)(_Other.HoldTimer);
	State = _Other.State;

	_Other.Number = (unsigned long)(-1);
	_Other.State = 0;
}



#endif
