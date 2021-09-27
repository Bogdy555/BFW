#if !defined BFW_DLL_LINK && !defined BFW_STATIC_LINK && !defined BFW_VENDOR

#define BFW_VENDOR

#endif

#if !defined BFW_WINDOWS_PLATFORM && !defined BFW_ARDUINO_PLATFORM

#define BFW_WINDOWS_PLATFORM

#endif



#include "..\..\BFW\Headers\BFW.hpp"



#ifdef BFW_ARDUINO_PLATFORM



void BFW_Debug_Break(const unsigned long _Line, const char* _File, const char* _Msg)
{
	if (_Msg)
	{
		BFW_LOG(_Msg);
		BFW_LOG('\n');
	}
	BFW_LOG(_Line);
	BFW_LOG('\n');

	BFW_LOG(_File);
	BFW_LOG('\n');
}



#endif



long BFW_Debug_Example()
{
	BFW::Log::Init();
	BFW_ARDUINO_CALL(BFW::Debug::Break = BFW_Debug_Break);

	int* a = new int[100];
	BFW_HEAP_PROFILE_PUSH(sizeof(int) * 100, a);
	BFW_HEAP_PROFILE_POP(a);
	delete[] a;

	BFW_DEBUG_BREAK();

	BFW_DEBUG_BREAK_MSG(BFW_STRING("Example break msg"));

	BFW_ASSERT(0);

	BFW_ASSERT_MSG(0, BFW_STRING("Example assert msg"));

	{
		BFW_DEBUG_CALL(BFW::Debug::HeapTracker A);

		int* b = new int[100];
		BFW_DEBUG_CALL(A.Push(100 * sizeof(int), b));

		BFW_LOG(A.GetHeapSize());
		BFW_LOG(BFW_STRING('\n'));

		//BFW_DEBUG_CALL(A.Pop(b));
		//delete[] b;

		//BFW_LOG(A.GetHeapSize());
		//BFW_LOG(BFW_STRING('\n'));
	}

	BFW_ARDUINO_CALL(BFW::Debug::Break = nullptr);
	BFW::Log::Stop();

	return BFW::Enums::_ReturnNoError;
}
