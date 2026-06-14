#ifndef BFW_LINUX_RunTime_hpp

#define BFW_LINUX_RunTime_hpp



#include "BFW_LINUX.hpp"



namespace BFW_LINUX
{

	namespace RunTime
	{

		class Application : public BFW::RunTime::Application
		{

		public:

			Application();
			Application(const Application& _Other) = delete;
			Application(Application&& _Other) noexcept;
			~Application();

			BFW::Input::Controller& GetController(const size_t _Index);
			const BFW::Input::Controller& GetController(const size_t _Index) const;

			Application& operator= (const Application& _Other) = delete;
			Application& operator= (Application&& _Other) noexcept;

		private:

			void Setup() override;
			void Update() override;
			void Stop() override;

			const bool InitInstance();

			BFW::Input::Controller Controllers[4];

		};

		enum Menus : const uint64_t
		{
			_MainMenu = 1
		};

		class MainMenu : public BFW::RunTime::Menu
		{

		public:

			MainMenu();
			MainMenu(const MainMenu& _Other) = delete;
			MainMenu(MainMenu&& _Other) noexcept;
			~MainMenu();

			const uint64_t GetType() const override;

			MainMenu& operator= (const MainMenu& _Other) = delete;
			MainMenu& operator= (MainMenu&& _Other) noexcept;

		private:

			void SpawnQueuedMenu(const uint64_t _QueuedMenu) override;
			void Setup() override;
			void Update() override;
			void Stop() override;

			void Input();
			void DeleteInputs();
			void Engine();
			void FrameBuild();

		};

	}

}



#endif
