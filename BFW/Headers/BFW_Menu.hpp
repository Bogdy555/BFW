#ifndef BFW_Menu_hpp

#define BFW_Menu_hpp



#include "BFW.hpp"



namespace BFW
{

	class BFW_API Menu
	{

	public:

		Menu();
		Menu(const Menu& _Other) = delete;
		Menu(Menu&& _Other) noexcept = delete;
		virtual ~Menu();

		const bool CheckOn() const;
		const unsigned long GetNextMenu() const;
		const unsigned long GetQueuedMenu() const;

		Application* GetApplicationObj();
		const Application* GetApplicationObj() const;

		Menu* GetPreviousMenuObj();
		const Menu* GetPreviousMenuObj() const;

		Time::Timer& GetFrameTime(const unsigned long _Index);
		const Time::Timer& GetFrameTime(const unsigned long _Index) const;

		const float GetTimeStep() const;

		const float GetTimeStepRatio() const;

		const unsigned long GetSync() const;

		void TurnOn();
		void Close(const unsigned long _NextMenu = Enums::_NullMenu);
		void SetQueuedMenu(const unsigned long _QueuedMenu);

		void BindApplication(Application* _ApplicationObj);

		void UpdateCurrentFrameTime();
		void SetTimeStep(const float _TimeStep = 1.0f / 60.0f);
		void SetSync(const unsigned long _Sync = 60);

		void Run(Application* _ApplicationObj);

		virtual void Setup() = 0;
		virtual void Update() = 0;
		virtual void Stop() = 0;

		void operator= (const Menu& _Other) = delete;
		void operator= (Menu&& _Other) noexcept = delete;

	protected:

		virtual void Input() = 0;
		virtual void DeleteInputs() = 0;
		virtual void Keys() = 0;
		virtual void Mouse() = 0;
		virtual void Controller() = 0;
		virtual void Engine() = 0;
		virtual void Sound() = 0;
		virtual void Rumble() = 0;
		virtual void Animations() = 0;
		virtual void FrameBuild() = 0;
		virtual void QueuedMenus() = 0;

	private:

		bool On;
		unsigned long NextMenu;
		unsigned long QueuedMenu;

		Application* ApplicationObj;
		Menu* PreviousMenuObj;

	};

}



#endif
