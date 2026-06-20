#ifndef BFW_Debug_hpp

#define BFW_Debug_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace Debug
	{

		struct BFW_API HeapPointer
		{

			size_t Size;
			const void* Pointer;

			HeapPointer();
			HeapPointer(const size_t _Size, const void* _Pointer);
			HeapPointer(const HeapPointer& _Other) = default;
			HeapPointer(HeapPointer&& _Other) noexcept;
			HeapPointer& operator= (const HeapPointer& _Other) = default;
			HeapPointer& operator= (HeapPointer&& _Other) noexcept;

		};

		class BFW_API HeapTracker
		{

		public:

			HeapTracker();
			HeapTracker(const HeapTracker& _Other);
			HeapTracker(HeapTracker&& _Other) noexcept;
			~HeapTracker();

			void Push(const size_t _Size, const void* _Pointer);
			void Pop(const void* _Pointer);

			const size_t GetHeapSize() const;
			const Vector<HeapPointer>& GetHeapVector() const;

			HeapTracker& operator= (const HeapTracker& _Other);
			HeapTracker& operator= (HeapTracker&& _Other) noexcept;

		private:

			size_t HeapSize;
			Vector<HeapPointer> HeapVector;

		};

		extern HeapTracker BFW_API HeapProfile;

	}

}



#endif
