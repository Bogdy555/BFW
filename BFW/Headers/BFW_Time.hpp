#ifndef BFW_Time_hpp

#define BFW_Time_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace Time
	{

		class BFW_API Timer
		{

		public:

			Timer();
			Timer(const Timer& _Other);
			Timer(Timer&& _Other) noexcept;
			~Timer();

			void Start();
			void Stop();
			void Reset();

			void SetBeginFromEnd(const uint64_t _MicroSeconds);
			void SetEndFromBegin(const uint64_t _MicroSeconds);

			void AddMicroSecondsToBegin(const uint64_t _MicroSeconds);
			void AddMicroSecondsToEnd(const uint64_t _MicroSeconds);
			void SubtractMicroSecondsFromBegin(const uint64_t _MicroSeconds);
			void SubtractMicroSecondsFromEnd(const uint64_t _MicroSeconds);

			const std::chrono::system_clock::time_point& GetBegin() const;
			const std::chrono::system_clock::time_point& GetEnd() const;

			operator const float () const;

			Timer& operator= (const Timer& _Other);
			Timer& operator= (Timer&& _Other) noexcept;

		private:

			std::chrono::system_clock::time_point Begin;
			std::chrono::system_clock::time_point End;

		};

		class BFW_API ScopeTimer
		{

		public:

			ScopeTimer(const LogScopeTimeFnc _LogFnc = nullptr, const BFW_CHAR_TYPE* _File = nullptr, const size_t _Line = 0, const BFW_CHAR_TYPE* _Name = nullptr);
			ScopeTimer(const ScopeTimer& _Other);
			ScopeTimer(ScopeTimer&& _Other) noexcept;
			~ScopeTimer();

			void SetLogFnc(const LogScopeTimeFnc _LogFnc);
			void SetFile(const BFW_CHAR_TYPE* _File);
			void SetLine(const size_t _Line);
			void SetName(const BFW_CHAR_TYPE* _Name);

			const LogScopeTimeFnc GetLogFnc() const;
			const BFW_CHAR_TYPE* GetFile() const;
			const size_t GetLine() const;
			const BFW_CHAR_TYPE* GetName() const;

			ScopeTimer& operator= (const ScopeTimer& _Other);
			ScopeTimer& operator= (ScopeTimer&& _Other) noexcept;

		private:

			Timer ScopeTime;
			LogScopeTimeFnc LogFnc;
			const BFW_CHAR_TYPE* File;
			size_t Line;
			BFW_STRING_TYPE Name;

		};

		const bool BFW_API Init();
		void BFW_API Stop();

		void BFW_API Sleep(const uint64_t _MicroSeconds);

		const uint64_t BFW_API GetTimeStamp(const std::chrono::system_clock::time_point& _Time = std::chrono::system_clock::now());

		const std::chrono::system_clock::time_point BFW_API GetTime();

		const tm BFW_API TimePointToUTC(const std::chrono::system_clock::time_point& _Time);
		const tm BFW_API TimePointToLocal(const std::chrono::system_clock::time_point& _Time);

#ifdef BFW_WINDOWS_PLATFORM

		const TIMECAPS BFW_API GetTimeCaps();

#endif

	}

}



#endif
