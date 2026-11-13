#include "../Headers/BFW.hpp"



static std::mutex HeapTrackerMutex;



BFW::Debug::HeapTracker BFW_API BFW::Debug::HeapProfile;



BFW::Debug::HeapPointer::HeapPointer() : Size(0), Pointer(nullptr), File(nullptr), Line(0), Function(nullptr)
{

}

BFW::Debug::HeapPointer::HeapPointer(const size_t _Size, const void* _Pointer, const BFW_CHAR_TYPE* _File, const size_t _Line, const BFW_CHAR_TYPE* _Function) : Size(_Size), Pointer(_Pointer), File(_File), Line(_Line), Function(_Function)
{

}

BFW::Debug::HeapPointer::HeapPointer(HeapPointer&& _Other) noexcept : Size(_Other.Size), Pointer(_Other.Pointer), File(_Other.File), Line(_Other.Line), Function(_Other.Function)
{
	_Other.Size = 0;
	_Other.Pointer = nullptr;
	_Other.File = nullptr;
	_Other.Line = 0;
	_Other.Function = nullptr;
}

BFW::Debug::HeapPointer& BFW::Debug::HeapPointer::operator= (HeapPointer&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Size = _Other.Size;
	Pointer = _Other.Pointer;
	File = _Other.File;
	Line = _Other.Line;
	Function = _Other.Function;

	_Other.Size = 0;
	_Other.Pointer = nullptr;
	_Other.File = nullptr;
	_Other.Line = 0;
	_Other.Function = nullptr;

	return *this;
}



BFW::Debug::HeapTracker::HeapTracker() : HeapSize(0), HeapVector()
{

}

BFW::Debug::HeapTracker::HeapTracker(const HeapTracker& _Other) : HeapSize(0), HeapVector()
{
	HeapTrackerMutex.lock();

	HeapSize = _Other.HeapSize;
	HeapVector = _Other.HeapVector;

	HeapTrackerMutex.unlock();
}

BFW::Debug::HeapTracker::HeapTracker(HeapTracker&& _Other) noexcept : HeapSize(0), HeapVector()
{
	HeapTrackerMutex.lock();

	HeapSize = _Other.HeapSize;
	HeapVector = (Vector<HeapPointer>&&)(_Other.HeapVector);

	_Other.HeapSize = 0;

	HeapTrackerMutex.unlock();
}

BFW::Debug::HeapTracker::~HeapTracker()
{
	BFW_ASSERT_MSG(HeapSize == 0, BFW_STRING_PREFIX("Memory leak detected!"));
}

void BFW::Debug::HeapTracker::Push(const size_t _Size, const void* _Pointer, const BFW_CHAR_TYPE* _File, const size_t _Line, const BFW_CHAR_TYPE* _Function)
{
	if (!_Size || !_Pointer)
	{
		return;
	}

	HeapTrackerMutex.lock();

	HeapSize += _Size;
	HeapVector.PushBack(HeapPointer(_Size, _Pointer, _File, _Line, _Function));

	HeapTrackerMutex.unlock();
}

void BFW::Debug::HeapTracker::Pop(const void* _Pointer)
{
	if (!_Pointer)
	{
		return;
	}

	HeapTrackerMutex.lock();

	for (size_t _Index = 0; _Index < HeapVector.GetSize(); _Index++)
	{
		if (HeapVector[_Index].Pointer == _Pointer)
		{
			HeapSize -= HeapVector[_Index].Size;
			HeapVector.Erase(_Index);

			HeapTrackerMutex.unlock();

			return;
		}
	}

	HeapTrackerMutex.unlock();
}

const size_t BFW::Debug::HeapTracker::GetHeapSize() const
{
	HeapTrackerMutex.lock();

	size_t _HeapSize = HeapSize;

	HeapTrackerMutex.unlock();

	return _HeapSize;
}

const BFW::Vector<BFW::Debug::HeapPointer> BFW::Debug::HeapTracker::GetHeapVector() const
{
	HeapTrackerMutex.lock();

	Vector<HeapPointer> _HeapVector = HeapVector;

	HeapTrackerMutex.unlock();

	return HeapVector;
}

BFW::Debug::HeapTracker& BFW::Debug::HeapTracker::operator= (const HeapTracker& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	HeapTrackerMutex.lock();

	HeapSize = _Other.HeapSize;
	HeapVector = _Other.HeapVector;

	HeapTrackerMutex.unlock();

	return *this;
}

BFW::Debug::HeapTracker& BFW::Debug::HeapTracker::operator= (HeapTracker&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	HeapTrackerMutex.lock();

	HeapSize = _Other.HeapSize;
	HeapVector = (Vector<HeapPointer>&&)(_Other.HeapVector);

	_Other.HeapSize = 0;

	HeapTrackerMutex.unlock();

	return *this;
}
