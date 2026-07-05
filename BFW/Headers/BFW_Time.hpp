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

			const tm GetUTCBegin() const;
			const tm GetUTCEnd() const;
			const tm GetLocalBegin() const;
			const tm GetLocalEnd() const;

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

			ScopeTimer(const LogScopeTimeFnc _LogFnc = nullptr);
			ScopeTimer(const ScopeTimer& _Other);
			ScopeTimer(ScopeTimer&& _Other) noexcept;
			~ScopeTimer();

			void SetLogFnc(const LogScopeTimeFnc _LogFnc);

			const LogScopeTimeFnc GetLogFnc() const;

			ScopeTimer& operator= (const ScopeTimer& _Other);
			ScopeTimer& operator= (ScopeTimer&& _Other) noexcept;

		private:

			Timer ScopeTime;
			LogScopeTimeFnc LogFnc;

		};

		const bool BFW_API Init();
		void BFW_API Stop();

		void BFW_API Sleep(const uint64_t _MicroSeconds);

		const tm BFW_API GetUTCTime();
		const tm BFW_API GetLocalTime();

#ifdef BFW_WINDOWS_PLATFORM

		const TIMECAPS BFW_API GetTimeCaps();

#endif

	}

}



#endif
