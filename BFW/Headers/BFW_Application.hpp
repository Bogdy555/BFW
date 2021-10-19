#ifndef BFW_Application_hpp

#define BFW_Application_hpp



#include "BFW.hpp"



namespace BFW
{

#ifdef BFW_WINDOWS_PLATFORM

	class BFW_API Application
	{

	public:

		Application();
		Application(const Application& _Other) = delete;
		Application(Application&& _Other) noexcept = delete;
		virtual ~Application();

		const bool CheckOn() const;
		const long GetReturnValue() const;

		const unsigned long GetCurrentMenu() const;
		Menu* GetCurrentMenuObj();
		const Menu* GetCurrentMenuObj() const;

		Multiprocessing::SharedMemory& GetSharedInstance();
		const Multiprocessing::SharedMemory& GetSharedInstance() const;

		Time::Timer& GetFrameTime(const unsigned long _Index);
		const Time::Timer& GetFrameTime(const unsigned long _Index) const;

		const float GetTimeStep() const;

		const float GetTimeStepRatio() const;

		const unsigned long GetSync() const;

		const HINSTANCE GetHInstance() const;
		const LPWSTR GetCmdLine() const;
		const long GetShowCmd() const;
		const unsigned long GetArgC() const;
		const wchar_t* GetWArgV(const unsigned long _Index) const;

		void TurnOn();
		void Close(const long _ReturnValue);

		void SetCurrentMenu(const unsigned long _CurrentMenu);
		void SetCurrentMenuObj(Menu* _CurrentMenuObj);

		void UpdateCurrentFrameTime();
		void SetTimeStep(const float _TimeStep = 1.0f / 60.0f);
		void SetSync(const unsigned long _Sync = 60);

		long Run(const HINSTANCE _hInstance, const LPWSTR _CmdLine, const long _ShowCmd, const wchar_t* _SharedMemoryName);

		virtual void Setup() = 0;
		virtual void Update() = 0;
		virtual void Stop() = 0;

		void operator= (const Application& _Other) = delete;
		void operator= (Application&& _Other) noexcept = delete;

	private:

		bool On;
		long ReturnValue;

		unsigned long CurrentMenu;
		Menu* CurrentMenuObj;

		Multiprocessing::SharedMemory SharedInstance;

		Time::Timer FrameTime[2];
		float TimeStep;
		unsigned long Sync;

		HINSTANCE hInstance;
		LPWSTR CmdLine;
		long ShowCmd;

	};

#endif

#ifdef BFW_ARDUINO_PLATFORM

	class BFW_API Application
	{

	public:

		Application();
		Application(const Application& _Other) = delete;
		Application(Application&& _Other) noexcept = delete;
		virtual ~Application();

		const bool CheckOn() const;
		const long GetReturnValue() const;

		const unsigned long GetCurrentMenu() const;
		Menu* GetCurrentMenuObj();
		const Menu* GetCurrentMenuObj() const;

		Time::Timer& GetFrameTime(const unsigned long _Index);
		const Time::Timer& GetFrameTime(const unsigned long _Index) const;

		const float GetTimeStep() const;

		const float GetTimeStepRatio() const;

		const unsigned long GetSync() const;

		void TurnOn();
		void Close(const long _ReturnValue);

		void SetCurrentMenu(const unsigned long _CurrentMenu);
		void SetCurrentMenuObj(Menu* _CurrentMenuObj);

		void UpdateCurrentFrameTime();
		void SetTimeStep(const float _TimeStep = 1.0f / 60.0f);
		void SetSync(const unsigned long _Sync = 60);

		long Run();

		virtual void Setup() = 0;
		virtual void Update() = 0;
		virtual void Stop() = 0;

		void operator= (const Application& _Other) = delete;
		void operator= (Application&& _Other) noexcept = delete;

	private:

		bool On;
		long ReturnValue;

		unsigned long CurrentMenu;
		Menu* CurrentMenuObj;

		Time::Timer FrameTime[2];
		float TimeStep;
		unsigned long Sync;

	};

#endif

}



#endif
