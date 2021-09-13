#include "..\Headers\BFW_APP.hpp"



BFW_APP::MainMenu::MainMenu() : BFW::Menu(), EscKey()
{

}

BFW_APP::MainMenu::~MainMenu()
{

}

void BFW_APP::MainMenu::Input()
{
	EscKey.UpdateState();
}

void BFW_APP::MainMenu::DeleteInputs()
{
	EscKey.DeleteState();
}

void BFW_APP::MainMenu::Keys()
{
	if (EscKey[BFW::Enums::_Previous] && !EscKey[BFW::Enums::_Current])
	{
		GetApplicationObj()->Close(BFW::Enums::_ReturnNoError);
	}
}

void BFW_APP::MainMenu::Mouse()
{

}

void BFW_APP::MainMenu::Controller()
{

}

void BFW_APP::MainMenu::Engine()
{

}

void BFW_APP::MainMenu::Sound()
{

}

void BFW_APP::MainMenu::Rumble()
{

}

void BFW_APP::MainMenu::Animations()
{

}

void BFW_APP::MainMenu::FrameBuild()
{

}

void BFW_APP::MainMenu::QueuedMenus()
{
	switch (GetQueuedMenu())
	{
	case Enums::_MainMenu:
	{
		MainMenu _MenuObj;
		_MenuObj.Run(GetApplicationObj());
		break;
	}
	case BFW::Enums::_NullMenu:
	{
		break;
	}
	default:
	{
		break;
	}
	}
}

void BFW_APP::MainMenu::Setup()
{
	EscKey.SetVKCode(VK_ESCAPE);
	TurnOn();
}

void BFW_APP::MainMenu::Update()
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

void BFW_APP::MainMenu::Stop()
{

}
