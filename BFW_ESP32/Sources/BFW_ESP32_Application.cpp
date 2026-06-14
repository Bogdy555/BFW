#include "../Headers/BFW_ESP32.hpp"



BFW_ESP32::RunTime::Application::Application() : BFW::RunTime::Application()
{

}

BFW_ESP32::RunTime::Application::Application(Application&& _Other) noexcept : BFW::RunTime::Application((BFW::RunTime::Application&&)(_Other))
{

}

BFW_ESP32::RunTime::Application::~Application()
{

}

BFW_ESP32::RunTime::Application& BFW_ESP32::RunTime::Application::operator= (Application&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	*(BFW::RunTime::Application*)(this) = (BFW::RunTime::Application&&)(_Other);

	return *this;
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
