#include "../Headers/BFW_ESP32.hpp"



BFW_ESP32::RunTime::MainMenu::MainMenu() : BFW::RunTime::Menu()
{

}

BFW_ESP32::RunTime::MainMenu::MainMenu(MainMenu&& _Other) noexcept : BFW::RunTime::Menu((BFW::RunTime::Menu&&)(_Other))
{

}

BFW_ESP32::RunTime::MainMenu::~MainMenu()
{

}

const uint64_t BFW_ESP32::RunTime::MainMenu::GetType() const
{
	return _MainMenu;
}

BFW_ESP32::RunTime::MainMenu& BFW_ESP32::RunTime::MainMenu::operator= (MainMenu&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	*(BFW::RunTime::Menu*)(this) = (BFW::RunTime::Menu&&)(_Other);

	return *this;
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
	Input();
	Engine();
	FrameBuild();
}

void BFW_ESP32::RunTime::MainMenu::Stop()
{

}

void BFW_ESP32::RunTime::MainMenu::Input()
{
	Application* _ApplicationObj = (Application*)(GetApplicationObj());
}

void BFW_ESP32::RunTime::MainMenu::DeleteInputs()
{
	Application* _ApplicationObj = (Application*)(GetApplicationObj());
}

void BFW_ESP32::RunTime::MainMenu::Engine()
{
	Application* _ApplicationObj = (Application*)(GetApplicationObj());
}

void BFW_ESP32::RunTime::MainMenu::FrameBuild()
{
	Application* _ApplicationObj = (Application*)(GetApplicationObj());
}
