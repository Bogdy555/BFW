#ifndef BFW_Multiprocessing_hpp

#define BFW_Multiprocessing_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace Multiprocessing
	{

#ifdef BFW_WINDOWS_PLATFORM

		class BFW_API SharedMemory
		{

		public:

			SharedMemory();
			SharedMemory(const SharedMemory& _Other);
			SharedMemory(SharedMemory&& _Other) noexcept;
			~SharedMemory();

			bool Create(const wchar_t* _Name, const unsigned long _Size);
			void Destroy();

			const bool CheckCreated() const;
			const wchar_t* GetName() const;
			const unsigned long GetSize() const;

			unsigned char* Data();
			const unsigned char* Data() const;

			operator unsigned char* ();
			operator const unsigned char* ();

			unsigned char& operator* ();
			const unsigned char& operator* () const;

			unsigned char& operator[] (const unsigned long _Index);
			const unsigned char& operator[] (const unsigned long _Index) const;

			void operator= (const SharedMemory& _Other);
			void operator= (SharedMemory&& _Other) noexcept;

		private:

			bool Created;

			HANDLE hFile;

			const wchar_t* Name;

			unsigned long Size;
			unsigned char* Buff;

		};

		class BFW_API Process
		{

		public:

			Process();
			Process(const Process& _Other);
			Process(Process&& _Other) noexcept;
			~Process();

			bool Create(const wchar_t* _Path, STARTUPINFO* _StartInfo = nullptr, const wchar_t* _WorkingDir = nullptr, wchar_t* _CmdLine = nullptr);
			bool CreateElevated(const wchar_t* _Path, const int _ShowCmd = SW_NORMAL, const wchar_t* _WorkingDir = nullptr, wchar_t* _CmdLine = nullptr);
			void Destroy(const unsigned long _ReturnValue);
			bool UpdateStatus();

			const PROCESS_INFORMATION& GetProcessInfo() const;
			const wchar_t* GetPath() const;
			const bool CheckCreated() const;
			const unsigned long GetReturnValue() const;

			void operator= (const Process& _Other);
			void operator= (Process&& _Other) noexcept;

		private:

			PROCESS_INFORMATION ProcessInfo;
			const wchar_t* Path;
			bool Created;
			unsigned long ReturnValue;

		};

#endif

	}

}



#endif
