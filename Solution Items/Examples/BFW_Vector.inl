#if !defined BFW_DLL_LINK && !defined BFW_STATIC_LINK && !defined BFW_VENDOR

#define BFW_VENDOR

#endif

#if !defined BFW_WINDOWS_PLATFORM && !defined BFW_ARDUINO_PLATFORM

#define BFW_WINDOWS_PLATFORM

#endif



#include "..\..\BFW\Headers\BFW.hpp"



template <typename T> class MyVec : public BFW::Vector<T>
{

public:

	MyVec() : BFW::Vector<T>()
	{

	}

	~MyVec()
	{

	}

private:

	const unsigned long GetResize(const unsigned long _Size) const override
	{
		if (!_Size)
		{
			return 0;
		}

		return _Size * 3;
	}

};



class MyClass
{

public:

	MyClass(unsigned int _Value = 0) : Value(_Value)
	{
		BFW_LOG(BFW_STRING("Created\n"));
	}

	MyClass(const MyClass& _Other) : Value(_Other.Value)
	{
		BFW_LOG(BFW_STRING("Copyed\n"));
	}

	MyClass(MyClass&& _Other) noexcept : Value(_Other.Value)
	{
		_Other.Value = 0;
		BFW_LOG(BFW_STRING("Moved\n"));
	}

	~MyClass()
	{
		BFW_LOG(BFW_STRING("Destroyed\n"));
	}

	void operator= (const MyClass& _Other)
	{
		Value = _Other.Value;
		BFW_LOG(BFW_STRING("Copyed\n"));
	}

	void operator= (MyClass&& _Other) noexcept
	{
		Value = _Other.Value;
		_Other.Value = 0;
		BFW_LOG(BFW_STRING("Moved\n"));
	}

private:

	unsigned int Value;

};



long BFW_Vector_Example()
{
	BFW::Log::Init();

	BFW::Vector<MyClass> Vec1;

	Vec1.PushBack((const MyClass&)(MyClass(2)));
	Vec1.MoveBack((MyClass&&)(MyClass(2)));

	Vec1.Clear();

	MyVec<MyClass> Vec2;

	Vec2.PushBack((const MyClass&)(MyClass(2)));
	Vec2.MoveBack((MyClass&&)(MyClass(2)));

	Vec2.Clear();

	BFW::Log::Stop();

	return BFW::Enums::_ReturnNoError;
}
