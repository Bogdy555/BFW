#include "../Headers/BFW_ESP32.hpp"



BFW_ESP32::RunTime::MainMenu::MainMenu() : BFW::RunTime::Menu()
{

}

BFW_ESP32::RunTime::MainMenu::~MainMenu()
{

}

const uint64_t BFW_ESP32::RunTime::MainMenu::GetType() const
{
	return _MainMenu;
}

void BFW_ESP32::RunTime::MainMenu::SpawnQueuedMenu(const uint64_t _QueuedMenu)
{
	switch (_QueuedMenu)
	{
	case BFW::RunTime::_NullMenu:
	{
		GetApplicationObj()->Close(BFW::MultiProcessing::_UnknownErrorReturnValue);
		break;
	}
	default:
	{
		GetApplicationObj()->Close(BFW::MultiProcessing::_UnknownErrorReturnValue);
		break;
	}
	}
}

void BFW_ESP32::RunTime::MainMenu::Setup()
{
	DeleteInputs();

	TurnOn();
}

void BFW_ESP32::RunTime::MainMenu::Update()
{
	BFW_PROFILE_FUNCTION();

	Input();
	Engine();
	FrameBuild();
}

void BFW_ESP32::RunTime::MainMenu::Stop()
{

}

void BFW_ESP32::RunTime::MainMenu::Input()
{
	BFW_PROFILE_FUNCTION();

	Application* _ApplicationObj = (Application*)(GetApplicationObj());
}

void BFW_ESP32::RunTime::MainMenu::DeleteInputs()
{
	Application* _ApplicationObj = (Application*)(GetApplicationObj());
}

void BFW_ESP32::RunTime::MainMenu::Engine()
{
	BFW_PROFILE_FUNCTION();

	Application* _ApplicationObj = (Application*)(GetApplicationObj());
}

void BFW_ESP32::RunTime::MainMenu::FrameBuild()
{
	BFW_PROFILE_FUNCTION();

	Application* _ApplicationObj = (Application*)(GetApplicationObj());
}
