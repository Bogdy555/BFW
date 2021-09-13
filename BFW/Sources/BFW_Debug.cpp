#include "..\Headers\BFW.hpp"



BFW::Debug::HeapPointer::HeapPointer(const unsigned long _Size, const void* _Pointer) : Size(_Size), Pointer(_Pointer)
{
	if (!Size)
	{
		Pointer = nullptr;
		return;
	}
	if (!Pointer)
	{
		Size = 0;
		return;
	}
}

BFW::Debug::HeapPointer::HeapPointer(const HeapPointer& _Other) : Size(_Other.Size), Pointer(_Other.Pointer)
{

}

BFW::Debug::HeapPointer::HeapPointer(HeapPointer&& _Other) noexcept : Size(_Other.Size), Pointer(_Other.Pointer)
{
	_Other.Size = 0;
	_Other.Pointer = nullptr;
}

BFW::Debug::HeapPointer::~HeapPointer()
{

}

void BFW::Debug::HeapPointer::Bind(const unsigned long _Size, const void* _Pointer)
{
	Size = _Size;
	Pointer = _Pointer;

	if (!Size)
	{
		Pointer = nullptr;
		return;
	}
	if (!Pointer)
	{
		Size = 0;
		return;
	}
}

const unsigned long BFW::Debug::HeapPointer::GetSize() const
{
	return Size;
}

const void* BFW::Debug::HeapPointer::GetPointer() const
{
	return Pointer;
}

void BFW::Debug::HeapPointer::operator= (const HeapPointer& _Other)
{
	Size = _Other.Size;
	Pointer = _Other.Pointer;
}

void BFW::Debug::HeapPointer::operator= (HeapPointer&& _Other) noexcept
{
	Size = _Other.Size;
	Pointer = _Other.Pointer;

	_Other.Size = 0;
	_Other.Pointer = nullptr;
}



BFW::Debug::HeapTracker::HeapTracker() : HeapSize(0), HeapVector()
{

}

BFW::Debug::HeapTracker::HeapTracker(const HeapTracker& _Other) : HeapSize(_Other.HeapSize), HeapVector((const Vector<HeapPointer>&)(_Other.HeapVector))
{

}

BFW::Debug::HeapTracker::HeapTracker(HeapTracker&& _Other) noexcept : HeapSize(_Other.HeapSize), HeapVector((Vector<HeapPointer>&&)(_Other.HeapVector))
{
	_Other.HeapSize = 0;
}

BFW::Debug::HeapTracker::~HeapTracker()
{
	if (HeapVector.GetSize())
	{
		BFW_DEBUG_BREAK_MSG(BFW_STRING("Memory leak detected!"));
	}
}

void BFW::Debug::HeapTracker::Push(const unsigned long _Size, const void* _Pointer)
{
	if (!_Size || !_Pointer)
	{
		return;
	}

	HeapSize += _Size;

	HeapVector.MoveBack(HeapPointer(_Size, _Pointer));
}

void BFW::Debug::HeapTracker::Pop(const void* _Pointer)
{
	if (!_Pointer)
	{
		return;
	}

	for (unsigned long _Index = 0; _Index < HeapVector.GetSize(); _Index++)
	{
		if (HeapVector[_Index].GetPointer() == _Pointer)
		{
			HeapSize -= HeapVector[_Index].GetSize();
			HeapVector.Erase(_Index);
			return;
		}
	}
}

const unsigned long BFW::Debug::HeapTracker::GetBuffSize(const void* _Pointer) const
{
	if (!_Pointer)
	{
		return 0;
	}

	for (unsigned long _Index = 0; _Index < HeapVector.GetSize(); _Index++)
	{
		if (HeapVector[_Index].GetPointer() == _Pointer)
		{
			return HeapVector[_Index].GetSize();
		}
	}
	return 0;
}

const unsigned long BFW::Debug::HeapTracker::GetHeapSize() const
{
	return HeapSize;
}

const BFW::Vector<BFW::Debug::HeapPointer>& BFW::Debug::HeapTracker::GetHeapVector() const
{
	return HeapVector;
}

void BFW::Debug::HeapTracker::operator= (const HeapTracker& _Other)
{
	HeapSize = _Other.HeapSize;
	HeapVector = (const Vector<HeapPointer>&)(_Other.HeapVector);
}

void BFW::Debug::HeapTracker::operator= (HeapTracker&& _Other) noexcept
{
	HeapSize = _Other.HeapSize;
	HeapVector = (Vector<HeapPointer>&&)(_Other.HeapVector);

	_Other.HeapSize = 0;
}



BFW::Debug::HeapTracker BFW_API BFW::Debug::HeapProfile;



#ifdef BFW_WINDOWS_PLATFORM



void BFW_API BFW::Debug::Break(const wchar_t* _Msg)
{
	if (_Msg)
	{
		MessageBox(NULL, _Msg, L"", MB_OK | MB_ICONERROR);
	}
	__debugbreak();
}



#endif



#ifdef BFW_ARDUINO_PLATFORM



void BFW_API (*BFW::Debug::Break)(const unsigned long _Line, const char* _File, const char* _Msg) = nullptr;



#endif
