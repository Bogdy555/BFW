#include "..\Headers\BFW.hpp"



BFW::Menu::Menu() : On(false), NextMenu(Enums::_NullMenu), QueuedMenu(Enums::_NullMenu), ApplicationObj(nullptr), PreviousMenuObj(nullptr)
{

}

BFW::Menu::~Menu()
{

}

const bool BFW::Menu::CheckOn() const
{
	return On;
}

const unsigned long BFW::Menu::GetNextMenu() const
{
	return NextMenu;
}

const unsigned long BFW::Menu::GetQueuedMenu() const
{
	return QueuedMenu;
}

BFW::Application* BFW::Menu::GetApplicationObj()
{
	return ApplicationObj;
}

const BFW::Application* BFW::Menu::GetApplicationObj() const
{
	return ApplicationObj;
}

BFW::Menu* BFW::Menu::GetPreviousMenuObj()
{
	return PreviousMenuObj;
}

const BFW::Menu* BFW::Menu::GetPreviousMenuObj() const
{
	return PreviousMenuObj;
}

BFW::Time::Timer& BFW::Menu::GetFrameTime(const unsigned long _Index)
{
	return ApplicationObj->GetFrameTime(_Index);
}

const BFW::Time::Timer& BFW::Menu::GetFrameTime(const unsigned long _Index) const
{
	return ApplicationObj->GetFrameTime(_Index);
}

BFW::Time::Timer* BFW::Menu::GetFrameTimePtr()
{
	return ApplicationObj->GetFrameTimePtr();
}

const BFW::Time::Timer* BFW::Menu::GetFrameTimePtr() const
{
	return ApplicationObj->GetFrameTimePtr();
}

const float BFW::Menu::GetTimeStep() const
{
	return ApplicationObj->GetTimeStep();
}

float* BFW::Menu::GetTimeStepPtr()
{
	return ApplicationObj->GetTimeStepPtr();
}

const float* BFW::Menu::GetTimeStepPtr() const
{
	return ApplicationObj->GetTimeStepPtr();
}

const float BFW::Menu::GetTimeStepRatio() const
{
	return ApplicationObj->GetTimeStepRatio();
}

const unsigned long BFW::Menu::GetSync() const
{
	return ApplicationObj->GetSync();
}

unsigned long* BFW::Menu::GetSyncPtr()
{
	return ApplicationObj->GetSyncPtr();
}

const unsigned long* BFW::Menu::GetSyncPtr() const
{
	return ApplicationObj->GetSyncPtr();
}

void BFW::Menu::TurnOn()
{
	On = true;
}

void BFW::Menu::Close(const unsigned long _NextMenu)
{
	On = false;
	NextMenu = _NextMenu;
}

void BFW::Menu::SetQueuedMenu(const unsigned long _QueuedMenu)
{
	QueuedMenu = _QueuedMenu;
}

void BFW::Menu::BindApplication(Application* _ApplicationObj)
{
	ApplicationObj = _ApplicationObj;
}

void BFW::Menu::UpdateCurrentFrameTime()
{
	ApplicationObj->UpdateCurrentFrameTime();
}

void BFW::Menu::SetTimeStep(const float _TimeStep)
{
	ApplicationObj->SetTimeStep(_TimeStep);
}

void BFW::Menu::SetSync(const unsigned long _Sync)
{
	ApplicationObj->SetSync(_Sync);
}

void BFW::Menu::Run(Application* _ApplicationObj)
{
	if (!_ApplicationObj)
	{
		BFW_DEBUG_BREAK_MSG(BFW_STRING("An application object is required for menu object to run!"));
		return;
	}

	ApplicationObj = _ApplicationObj;

	PreviousMenuObj = ApplicationObj->GetCurrentMenuObj();

	ApplicationObj->SetCurrentMenuObj(this);

	Setup();
	FrameBuild();
	while (On)
	{
		GetFrameTime(Enums::_Current).Start();

		Update();

		if (GetSync())
		{
			GetFrameTime(Enums::_Current).Stop();

			unsigned long _SleepTime = (unsigned long)((1.0f * Time::SecToMicro) / (float)(GetSync()) - GetFrameTime(Enums::_Current) * Time::SecToMicro);

			if ((long)(_SleepTime) > 0)
			{
				Time::SleepMicroSec(_SleepTime);
			}
		}

		GetFrameTime(Enums::_Current).Stop();

		GetFrameTime(Enums::_Previous) = GetFrameTime(Enums::_Current);

		if (QueuedMenu != Enums::_NullMenu)
		{
			QueuedMenus();
			QueuedMenu = Enums::_NullMenu;
		}

		if (!ApplicationObj->CheckOn())
		{
			Close(Enums::_NullMenu);
		}
	}
	Stop();

	ApplicationObj->SetCurrentMenuObj(PreviousMenuObj);
	ApplicationObj->SetCurrentMenu(NextMenu);

	ApplicationObj = nullptr;
	PreviousMenuObj = nullptr;
}
