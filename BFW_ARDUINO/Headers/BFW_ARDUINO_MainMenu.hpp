#ifndef BFW_ARDUINO_MainMenu_hpp

#define BFW_ARDUINO_MainMenu_hpp



#include "BFW_ARDUINO.hpp"



namespace BFW_ARDUINO
{

	class MainMenu : public BFW::Menu
	{

	public:

		MainMenu();
		MainMenu(const MainMenu& _Other) = delete;
		MainMenu(MainMenu&& _Other) noexcept = delete;
		~MainMenu();

		void Setup() override;
		void Update() override;
		void Stop() override;

		void operator= (const MainMenu& _Other) = delete;
		void operator= (MainMenu&& _Other) noexcept = delete;

	private:

		void Input() override;
		void DeleteInputs() override;
		void Keys() override;
		void Mouse() override;
		void Controller() override;
		void Engine() override;
		void Sound() override;
		void Rumble() override;
		void Animations() override;
		void FrameBuild() override;
		void QueuedMenus() override;

	};

}



#endif
