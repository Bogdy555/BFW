#ifndef BFW_Time_hpp

#define BFW_Time_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace Time
	{

		extern const float BFW_API MicroToMilli;
		extern const float BFW_API MicroToSec;

		extern const float BFW_API MilliToMicro;
		extern const float BFW_API MilliToSec;

		extern const float BFW_API SecToMicro;
		extern const float BFW_API SecToMilli;

		void BFW_API SleepMicroSec(const unsigned long _MicroSec);
		void BFW_API SleepMilliSec(const unsigned long _MilliSec);
		void BFW_API SleepSec(const unsigned long _Sec);

		float BFW_API FramesPerMicroSec(const float _MicroSecPerFrame, bool* _Error = nullptr);
		float BFW_API FramesPerMilliSec(const float _MilliSecPerFrame, bool* _Error = nullptr);
		float BFW_API FramesPerSec(const float _SecPerFrame, bool* _Error = nullptr);

#ifdef BFW_WINDOWS_PLATFORM

		class BFW_API Timer
		{

		public:

			Timer(const long _MicroSec = 0, const bool _Feature = false);
			Timer(const Timer& _Other);
			Timer(Timer&& _Other) noexcept;
			~Timer();

			void Start();
			void Stop();
			void Reset();

			void SetMicroSec(const long _MicroSec, const bool _Feature = false);
			void SetMilliSec(const long _MilliSec, const bool _Feature = false);
			void SetSec(const long _Sec, const bool _Feature = false);

			void AddMicroSec(const long _MicroSec, const bool _Feature = false);
			void AddMilliSec(const long _MilliSec, const bool _Feature = false);
			void AddSec(const long _Sec, const bool _Feature = false);

			const tm GetUTCBegin() const;
			const tm GetUTCEnd() const;
			const tm GetLocalBegin() const;
			const tm GetLocalEnd() const;

			operator const float() const;

			void operator= (const Timer& _Other);
			void operator= (Timer&& _Other) noexcept;

		private:

			std::chrono::time_point<std::chrono::system_clock> Begin;
			std::chrono::time_point<std::chrono::system_clock> End;

		};

		extern const Typedef::TimeRef BFW_API UtcTime;
		extern const Typedef::TimeRef BFW_API LocalTime;

		extern const Typedef::BoolRef BFW_API Initialized;
		extern const Typedef::TimeCapsRef BFW_API TimeCaps;

		bool BFW_API Init();
		void BFW_API Stop();

		void BFW_API GetTime();
		void BFW_API GetUtcTime();
		void BFW_API GetLocalTime();

#endif

#ifdef BFW_ARDUINO_PLATFORM

		class BFW_API Timer
		{

		public:

			Timer(const long _MicroSec = 0, const bool _Feature = false);
			Timer(const Timer& _Other);
			Timer(Timer&& _Other) noexcept;
			~Timer();

			void Start();
			void Stop();
			void Reset();

			void SetMicroSec(const long _MicroSec, const bool _Feature = false);
			void SetMilliSec(const long _MilliSec, const bool _Feature = false);
			void SetSec(const long _Sec, const bool _Feature = false);

			void AddMicroSec(const long _MicroSec, const bool _Feature = false);
			void AddMilliSec(const long _MilliSec, const bool _Feature = false);
			void AddSec(const long _Sec, const bool _Feature = false);

			const unsigned long GetBeginMicroSec() const;
			const unsigned long GetBeginMilliSec() const;
			const unsigned long GetBeginSec() const;
			const unsigned long GetEndMicroSec() const;
			const unsigned long GetEndMilliSec() const;
			const unsigned long GetEndSec() const;

			operator const float() const;

			void operator= (const Timer& _Other);
			void operator= (Timer&& _Other) noexcept;

		private:

			unsigned long Begin;
			unsigned long End;

	};

#endif

	}

}



#endif
