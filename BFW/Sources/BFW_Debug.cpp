#include "../Headers/BFW.hpp"



static std::mutex& GetHeapTrackerMutex()
{
	static std::mutex _HeapTrackerMutex;
	return _HeapTrackerMutex;
}



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
	GetHeapTrackerMutex().lock();

	HeapSize = _Other.HeapSize;
	HeapVector = _Other.HeapVector;

	GetHeapTrackerMutex().unlock();
}

BFW::Debug::HeapTracker::HeapTracker(HeapTracker&& _Other) noexcept : HeapSize(0), HeapVector()
{
	GetHeapTrackerMutex().lock();

	HeapSize = _Other.HeapSize;
	HeapVector = (Vector<HeapPointer>&&)(_Other.HeapVector);

	_Other.HeapSize = 0;

	GetHeapTrackerMutex().unlock();
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

	GetHeapTrackerMutex().lock();

	HeapSize += _Size;
	HeapVector.PushBack(HeapPointer(_Size, _Pointer, _File, _Line, _Function));

	GetHeapTrackerMutex().unlock();
}

void BFW::Debug::HeapTracker::Pop(const void* _Pointer)
{
	if (!_Pointer)
	{
		return;
	}

	GetHeapTrackerMutex().lock();

	for (size_t _Index = 0; _Index < HeapVector.GetSize(); _Index++)
	{
		if (HeapVector[_Index].Pointer == _Pointer)
		{
			HeapSize -= HeapVector[_Index].Size;
			HeapVector.Erase(_Index);

			GetHeapTrackerMutex().unlock();

			return;
		}
	}

	GetHeapTrackerMutex().unlock();
}

const size_t BFW::Debug::HeapTracker::GetHeapSize() const
{
	GetHeapTrackerMutex().lock();

	size_t _HeapSize = HeapSize;

	GetHeapTrackerMutex().unlock();

	return _HeapSize;
}

const BFW::Vector<BFW::Debug::HeapPointer> BFW::Debug::HeapTracker::GetHeapVector() const
{
	GetHeapTrackerMutex().lock();

	Vector<HeapPointer> _HeapVector = HeapVector;

	GetHeapTrackerMutex().unlock();

	return HeapVector;
}

BFW::Debug::HeapTracker& BFW::Debug::HeapTracker::operator= (const HeapTracker& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	GetHeapTrackerMutex().lock();

	HeapSize = _Other.HeapSize;
	HeapVector = _Other.HeapVector;

	GetHeapTrackerMutex().unlock();

	return *this;
}

BFW::Debug::HeapTracker& BFW::Debug::HeapTracker::operator= (HeapTracker&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	GetHeapTrackerMutex().lock();

	HeapSize = _Other.HeapSize;
	HeapVector = (Vector<HeapPointer>&&)(_Other.HeapVector);

	_Other.HeapSize = 0;

	GetHeapTrackerMutex().unlock();

	return *this;
}
