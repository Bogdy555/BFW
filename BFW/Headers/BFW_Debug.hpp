#ifndef BFW_Debug_hpp

#define BFW_Debug_hpp



#include "BFW.hpp"



#ifndef BFW_DEBUG



#define BFW_HEAP_PROFILE_PUSH(Size, Pointer)

#define BFW_HEAP_PROFILE_POP(Pointer)



#ifdef BFW_WINDOWS_PLATFORM

#define BFW_DEBUG_BREAK()

#define BFW_ASSERT(Condition)

#define BFW_DEBUG_BREAK_MSG(Msg)

#define BFW_ASSERT_MSG(Condition, Msg)

#endif



#ifdef BFW_ARDUINO_PLATFORM

#define BFW_DEBUG_BREAK()

#define BFW_ASSERT(Condition)

#define BFW_DEBUG_BREAK_MSG(Msg)

#define BFW_ASSERT_MSG(Condition, Msg)

#endif



#endif



#ifdef BFW_DEBUG



#define BFW_HEAP_PROFILE_PUSH(Size, Pointer) BFW::Debug::HeapProfile.Push(Size, Pointer)

#define BFW_HEAP_PROFILE_POP(Pointer) BFW::Debug::HeapProfile.Pop(Pointer)



#ifdef BFW_WINDOWS_PLATFORM

#define BFW_DEBUG_BREAK() BFW::Debug::Break(nullptr)

#define BFW_ASSERT(Condition) if(!(Condition))\
{\
	BFW_DEBUG_BREAK();\
}

#define BFW_DEBUG_BREAK_MSG(Msg) BFW::Debug::Break(Msg)

#define BFW_ASSERT_MSG(Condition, Msg) if(!(Condition))\
{\
	BFW_DEBUG_BREAK_MSG(Msg);\
}

#endif



#ifdef BFW_ARDUINO_PLATFORM

#define BFW_DEBUG_BREAK() if (BFW::Debug::Break)\
{\
	BFW::Debug::Break(__LINE__, __FILE__, nullptr);\
}

#define BFW_ASSERT(Condition) if(!(Condition))\
{\
	BFW_DEBUG_BREAK();\
}

#define BFW_DEBUG_BREAK_MSG(Msg) if (BFW::Debug::Break)\
{\
	BFW::Debug::Break(__LINE__, __FILE__, Msg);\
}

#define BFW_ASSERT_MSG(Condition, Msg) if(!(Condition))\
{\
	BFW_DEBUG_BREAK_MSG(Msg);\
}

#endif



#endif



namespace BFW
{

	namespace Debug
	{

		class BFW_API HeapPointer
		{

		public:

			HeapPointer(const unsigned long _Size = 0, const void* _Pointer = nullptr);
			HeapPointer(const HeapPointer& _Other);
			HeapPointer(HeapPointer&& _Other) noexcept;
			~HeapPointer();

			void Bind(const unsigned long _Size, const void* _Pointer);

			const unsigned long GetSize() const;
			const void* GetPointer() const;

			void operator= (const HeapPointer& _Other);
			void operator= (HeapPointer&& _Other) noexcept;

		private:

			unsigned long Size;
			const void* Pointer;

		};

		class BFW_API HeapTracker
		{

		public:

			HeapTracker();
			HeapTracker(const HeapTracker& _Other);
			HeapTracker(HeapTracker&& _Other) noexcept;
			~HeapTracker();

			void Push(const unsigned long _Size, const void* _Pointer);
			void Pop(const void* _Pointer);

			const unsigned long GetBuffSize(const void* _Pointer) const;

			const unsigned long GetHeapSize() const;
			const Vector<HeapPointer>& GetHeapVector() const;

			void operator= (const HeapTracker& _Other);
			void operator= (HeapTracker&& _Other) noexcept;

		private:

			unsigned long HeapSize;
			Vector<HeapPointer> HeapVector;

		};



		extern HeapTracker BFW_API HeapProfile;



#ifdef BFW_WINDOWS_PLATFORM

		void BFW_API Break(const wchar_t* _Msg = nullptr);

#endif

#ifdef BFW_ARDUINO_PLATFORM

		extern void BFW_API (*Break)(const unsigned long _Line, const char* _File, const char* _Msg = nullptr);

#endif

	}

}



#endif
