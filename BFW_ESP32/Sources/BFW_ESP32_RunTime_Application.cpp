#include "../Headers/BFW_ESP32.hpp"



BFW_ESP32::RunTime::Application::Application() : BFW::RunTime::Application()
{

}

BFW_ESP32::RunTime::Application::~Application()
{

}

void BFW_ESP32::RunTime::Application::Setup()
{
	TurnOn();
	SetCurrentMenu(_MainMenu);
}

void BFW_ESP32::RunTime::Application::Update()
{
	switch (GetCurrentMenu())
	{
	case _MainMenu:
	{
		MainMenu _Menu;

		uint64_t _NextMenu = _Menu.Run(this);

		SetCurrentMenu(_NextMenu);

		break;
	}
	case BFW::RunTime::_NullMenu:
	{
		Close(BFW::MultiProcessing::_UnknownErrorReturnValue);
		break;
	}
	default:
	{
		Close(BFW::MultiProcessing::_UnknownErrorReturnValue);
		break;
	}
	}
}

void BFW_ESP32::RunTime::Application::Stop()
{

}
