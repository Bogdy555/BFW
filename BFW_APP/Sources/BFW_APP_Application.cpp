#include "..\Headers\BFW_APP.hpp"



BFW_APP::Application::Application() : BFW::Application()
{

}

BFW_APP::Application::~Application()
{

}

void BFW_APP::Application::Setup()
{
	TurnOn();
	SetCurrentMenu(Enums::_MainMenu);
}

void BFW_APP::Application::Update()
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

void BFW_APP::Application::Stop()
{

}
