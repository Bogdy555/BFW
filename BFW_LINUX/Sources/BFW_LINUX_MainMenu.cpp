#include "../Headers/BFW_LINUX.hpp"



BFW_LINUX::RunTime::MainMenu::MainMenu() : BFW::RunTime::Menu()
{

}

BFW_LINUX::RunTime::MainMenu::MainMenu(MainMenu&& _Other) noexcept : BFW::RunTime::Menu((BFW::RunTime::Menu&&)(_Other))
{

}

BFW_LINUX::RunTime::MainMenu::~MainMenu()
{

}

const uint64_t BFW_LINUX::RunTime::MainMenu::GetType() const
{
	return _MainMenu;
}

BFW_LINUX::RunTime::MainMenu& BFW_LINUX::RunTime::MainMenu::operator= (MainMenu&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	*(BFW::RunTime::Menu*)(this) = (BFW::RunTime::Menu&&)(_Other);

	return *this;
}

void BFW_LINUX::RunTime::MainMenu::SpawnQueuedMenu(const uint64_t _QueuedMenu)
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

void BFW_LINUX::RunTime::MainMenu::Setup()
{
	DeleteInputs();

	TurnOn();
}

void BFW_LINUX::RunTime::MainMenu::Update()
{
	Input();
	Engine();
	FrameBuild();
}

void BFW_LINUX::RunTime::MainMenu::Stop()
{

}

void BFW_LINUX::RunTime::MainMenu::Input()
{
	Application* _ApplicationObj = (Application*)(GetApplicationObj());

	_ApplicationObj->GetController(0).UpdateState(0);
	_ApplicationObj->GetController(1).UpdateState(1);
	_ApplicationObj->GetController(2).UpdateState(2);
	_ApplicationObj->GetController(3).UpdateState(3);
}

void BFW_LINUX::RunTime::MainMenu::DeleteInputs()
{
	Application* _ApplicationObj = (Application*)(GetApplicationObj());

	_ApplicationObj->GetController(0).CleanState();
	_ApplicationObj->GetController(1).CleanState();
	_ApplicationObj->GetController(2).CleanState();
	_ApplicationObj->GetController(3).CleanState();
}

void BFW_LINUX::RunTime::MainMenu::Engine()
{
	Application* _ApplicationObj = (Application*)(GetApplicationObj());
}

void BFW_LINUX::RunTime::MainMenu::FrameBuild()
{
	Application* _ApplicationObj = (Application*)(GetApplicationObj());
}
