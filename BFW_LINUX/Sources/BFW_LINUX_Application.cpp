#include "../Headers/BFW_LINUX.hpp"



BFW_LINUX::RunTime::Application::Application() : BFW::RunTime::Application(), Controllers()
{

}

BFW_LINUX::RunTime::Application::Application(Application&& _Other) noexcept : BFW::RunTime::Application((BFW::RunTime::Application&&)(_Other)), Controllers()
{
	Controllers[0] = (BFW::Input::Controller&&)(_Other.Controllers[0]);
	Controllers[1] = (BFW::Input::Controller&&)(_Other.Controllers[1]);
	Controllers[2] = (BFW::Input::Controller&&)(_Other.Controllers[2]);
	Controllers[3] = (BFW::Input::Controller&&)(_Other.Controllers[3]);
}

BFW_LINUX::RunTime::Application::~Application()
{

}

BFW::Input::Controller& BFW_LINUX::RunTime::Application::GetController(const size_t _Index)
{
	return Controllers[_Index];
}

const BFW::Input::Controller& BFW_LINUX::RunTime::Application::GetController(const size_t _Index) const
{
	return Controllers[_Index];
}

BFW_LINUX::RunTime::Application& BFW_LINUX::RunTime::Application::operator= (Application&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	*(BFW::RunTime::Application*)(this) = (BFW::RunTime::Application&&)(_Other);
	Controllers[0] = (BFW::Input::Controller&&)(_Other.Controllers[0]);
	Controllers[1] = (BFW::Input::Controller&&)(_Other.Controllers[1]);
	Controllers[2] = (BFW::Input::Controller&&)(_Other.Controllers[2]);
	Controllers[3] = (BFW::Input::Controller&&)(_Other.Controllers[3]);

	return *this;
}

void BFW_LINUX::RunTime::Application::Setup()
{
	if (GetArgC() != 1)
	{
		Close(BFW::MultiProcessing::_UnknownErrorReturnValue);
		return;
	}

	if (!InitInstance())
	{
		Close(BFW::MultiProcessing::_NoErrorReturnValue);
		return;
	}

	TurnOn();
	SetCurrentMenu(_MainMenu);
}

void BFW_LINUX::RunTime::Application::Update()
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

void BFW_LINUX::RunTime::Application::Stop()
{

}

const bool BFW_LINUX::RunTime::Application::InitInstance()
{
	GetSharedInstanceMutex().Lock();

	uint64_t& _SharedInstanceMemory = *(uint64_t*)(GetSharedInstanceMemory().GetData());

	if (_SharedInstanceMemory != 1)
	{
		GetSharedInstanceMutex().Unlock();

		return false;
	}

	GetSharedInstanceMutex().Unlock();

	return true;
}
