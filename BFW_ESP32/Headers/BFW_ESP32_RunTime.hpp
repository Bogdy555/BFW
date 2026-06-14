#ifndef BFW_ESP32_RunTime_hpp

#define BFW_ESP32_RunTime_hpp



#include "BFW_ESP32.hpp"



namespace BFW_ESP32
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

			Application& operator= (const Application& _Other) = delete;
			Application& operator= (Application&& _Other) noexcept;

		private:

			void Setup() override;
			void Update() override;
			void Stop() override;

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
