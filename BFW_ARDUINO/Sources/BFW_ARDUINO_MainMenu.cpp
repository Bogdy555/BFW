#include "..\Headers\BFW_ARDUINO.hpp"



BFW_ARDUINO::MainMenu::MainMenu() : BFW::Menu()
{

}

BFW_ARDUINO::MainMenu::~MainMenu()
{

}

void BFW_ARDUINO::MainMenu::Input()
{

}

void BFW_ARDUINO::MainMenu::DeleteInputs()
{

}

void BFW_ARDUINO::MainMenu::Keys()
{

}

void BFW_ARDUINO::MainMenu::Mouse()
{

}

void BFW_ARDUINO::MainMenu::Controller()
{

}

void BFW_ARDUINO::MainMenu::Engine()
{

}

void BFW_ARDUINO::MainMenu::Sound()
{

}

void BFW_ARDUINO::MainMenu::Rumble()
{

}

void BFW_ARDUINO::MainMenu::Animations()
{

}

void BFW_ARDUINO::MainMenu::FrameBuild()
{

}

void BFW_ARDUINO::MainMenu::QueuedMenus()
{
	switch (GetQueuedMenu())
	{
	case Enums::_MainMenu:
	{
		GetApplicationObj()->Close(BFW::Enums::_ReturnError);
		break;
	}
	case BFW::Enums::_NullMenu:
	{
		GetApplicationObj()->Close(BFW::Enums::_ReturnError);
		break;
	}
	default:
	{
		GetApplicationObj()->Close(BFW::Enums::_ReturnError);
		break;
	}
	}
}

void BFW_ARDUINO::MainMenu::Setup()
{
	TurnOn();
}

void BFW_ARDUINO::MainMenu::Update()
{
	Input();
	Keys();
	Mouse();
	Controller();
	Engine();
	Sound();
	Rumble();
	Animations();
	FrameBuild();
}

void BFW_ARDUINO::MainMenu::Stop()
{

}
