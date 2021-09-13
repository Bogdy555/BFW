#if !defined BFW_DLL_LINK && !defined BFW_STATIC_LINK && !defined BFW_VENDOR

#define BFW_VENDOR

#endif

#ifdef BFW_ARDUINO_PLATFORM

#error Only available on windows

#endif

#if !defined BFW_WINDOWS_PLATFORM

#define BFW_WINDOWS_PLATFORM

#endif



#include "..\..\BFW\Headers\BFW.hpp"



void BFW_Input_Example()
{
	BFW::Time::Init();

	BFW::Input::Key EscKey;

	BFW::Input::Controller Controller;

	Controller.SetID(0);

	EscKey.SetVKCode(VK_ESCAPE);

	BFW::Input::RumbleSequence RumbleSequence;

	RumbleSequence.GetRumbleStateVec().PushBack(BFW::Input::RumbleState(0, 0, 0.0f, 0.1f));
	RumbleSequence.GetRumbleStateVec().PushBack(BFW::Input::RumbleState(10000, 10000, 0.1f, 0.2f));

	while (!EscKey[BFW::Enums::_Current])
	{
		EscKey.UpdateState();

		BFW_PRINT(L"Press esc to exit\n");

		BFW::Input::Cursor::UpdatePosition();

		BFW_PRINT(L"Cursor pos: ");

		BFW_PRINT(BFW::Input::Cursor::CursorPosition.x);
		BFW_PRINT(L' ');
		BFW_PRINT(BFW::Input::Cursor::CursorPosition.y);
		BFW_PRINT(L'\n');

		if (Controller.UpdateState())
		{
			BFW_PRINT(L"Joystick pos: ");
			BFW_PRINT(Controller.XLeft[BFW::Enums::_Current]);
			BFW_PRINT(L' ');
			BFW_PRINT(Controller.YLeft[BFW::Enums::_Current]);
			BFW_PRINT(L'\n');

			Controller.SetRumbleSpeed(RumbleSequence.GetRumbleStateVec()[RumbleSequence.GetIndex()].RumbleSpeedLeft, RumbleSequence.GetRumbleStateVec()[RumbleSequence.GetIndex()].RumbleSpeedRight);
		}
		else
		{
			BFW_PRINT(L"No controller connected\n");
		}

		BFW::Time::SleepMilliSec(10);

		RumbleSequence.Update(10.0f * BFW::Time::MilliToSec);

		system("cls");
	}

	BFW::Time::Stop();
}
