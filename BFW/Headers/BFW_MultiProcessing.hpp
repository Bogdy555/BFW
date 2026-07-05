#ifndef BFW_MultiProcessing_hpp

#define BFW_MultiProcessing_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace MultiProcessing
	{

#ifdef BFW_WINDOWS_PLATFORM

		enum BFW_API ReturnValues : const int32_t
		{
			_NoErrorReturnValue = 0,
			_UnknownErrorReturnValue = -1,
			_StillRunningReturnValue = 259
		};

#endif

#ifdef BFW_LINUX_PLATFORM

		enum BFW_API ReturnValues : const int32_t
		{
			_NoErrorReturnValue = 0,
			_UnknownErrorReturnValue = -1
		};

#endif

#ifdef BFW_ESP32_PLATFORM

		enum BFW_API ReturnValues : const int32_t
		{
			_NoErrorReturnValue = 0,
			_UnknownErrorReturnValue = -1
		};

#endif

#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

		class BFW_API Process
		{

		public:

			Process();
			Process(const Process& _Other) = delete;
			Process(Process&& _Other) noexcept;
			~Process();

#ifdef BFW_WINDOWS_PLATFORM

			const bool Create(const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _WorkingDir, const BFW_CHAR_TYPE* _CmdLine, const int32_t _ShowCmd);
			const bool CreateElevated(const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _WorkingDir, const BFW_CHAR_TYPE* _CmdLine, const int32_t _ShowCmd);
			void Destroy(const int32_t _ReturnValue);
			void Release();
			const int32_t UpdateState();

#endif

#ifdef BFW_LINUX_PLATFORM

			const bool Create(const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _WorkingDir, BFW_CHAR_TYPE** _CmdLine);
			void Destroy();
			const bool UpdateState(int32_t& _ReturnValue);

#endif

			const bool CheckCreated() const;

#ifdef BFW_WINDOWS_PLATFORM

			const HANDLE GetHandle() const;

#endif

#ifdef BFW_LINUX_PLATFORM

			const pid_t GetPid() const;

#endif

			Process& operator= (const Process& _Other) = delete;
			Process& operator= (Process&& _Other) noexcept;

		private:

#ifdef BFW_WINDOWS_PLATFORM

			HANDLE Handle;

#endif

#ifdef BFW_LINUX_PLATFORM

			pid_t Pid;

#endif

		};

		class BFW_API SharedMemory
		{

		public:

			SharedMemory();
			SharedMemory(const SharedMemory& _Other) = delete;
			SharedMemory(SharedMemory&& _Other) noexcept;
			~SharedMemory();

			const bool Create(const BFW_CHAR_TYPE* _Name, const size_t _Size);
			void Destroy();

			const bool CheckCreated() const;

#ifdef BFW_WINDOWS_PLATFORM

			const HANDLE GetHandle() const;

#endif

#ifdef BFW_LINUX_PLATFORM

			const int32_t GetFile() const;

#endif

			const size_t GetSize() const;
			uint8_t* GetData();
			const uint8_t* GetData() const;

			operator uint8_t* ();
			operator const uint8_t* () const;

			uint8_t& operator* ();
			const uint8_t& operator* () const;

			uint8_t& operator[] (const size_t _Index);
			const uint8_t& operator[] (const size_t _Index) const;

			SharedMemory& operator= (const SharedMemory& _Other) = delete;
			SharedMemory& operator= (SharedMemory&& _Other) noexcept;

		private:

#ifdef BFW_WINDOWS_PLATFORM

			HANDLE Handle;

#endif

#ifdef BFW_LINUX_PLATFORM

			int32_t File;

#endif

			size_t Size;
			uint8_t* Data;

		};

		class BFW_API SharedMutex
		{

		public:

			SharedMutex();
			SharedMutex(const SharedMutex& _Other) = delete;
			SharedMutex(SharedMutex&& _Other) noexcept;
			~SharedMutex();

			const bool Create(const BFW_CHAR_TYPE* _Name);
			void Destroy();

			void Lock();
			void Unlock();

			const bool CheckCreated() const;

#ifdef BFW_WINDOWS_PLATFORM

			const HANDLE GetHandle() const;

#endif

#ifdef BFW_LINUX_PLATFORM

			const sem_t* GetSemaphore() const;

#endif

			SharedMutex& operator= (const SharedMutex& _Other) = delete;
			SharedMutex& operator= (SharedMutex&& _Other) noexcept;

		private:

#ifdef BFW_WINDOWS_PLATFORM

			HANDLE Handle;

#endif

#ifdef BFW_LINUX_PLATFORM

			sem_t* Semaphore;

#endif

		};

#endif

	}

}



#endif
