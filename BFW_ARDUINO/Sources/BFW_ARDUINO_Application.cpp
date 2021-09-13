#include "..\Headers\BFW_ARDUINO.hpp"



BFW_ARDUINO::Application::Application() : BFW::Application()
{

}

BFW_ARDUINO::Application::~Application()
{

}

void BFW_ARDUINO::Application::Setup()
{
	TurnOn();
	SetCurrentMenu(Enums::_MainMenu);
}

void BFW_ARDUINO::Application::Update()
{
	switch (GetCurrentMenu())
	{
	case Enums::_MainMenu:
	{
		MainMenu _MenuObj;
		_MenuObj.Run(this);
		break;
	}
	case BFW::Enums::_NullMenu:
	{
		Close(BFW::Enums::_ReturnError);
		break;
	}
	default:
	{
		Close(BFW::Enums::_ReturnError);
		break;
	}
	}
}

void BFW_ARDUINO::Application::Stop()
{

}
