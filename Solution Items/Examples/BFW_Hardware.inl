#if !defined BFW_DLL_LINK && !defined BFW_STATIC_LINK && !defined BFW_VENDOR

#define BFW_VENDOR

#endif

#if !defined BFW_WINDOWS_PLATFORM && !defined BFW_ARDUINO_PLATFORM

#define BFW_WINDOWS_PLATFORM

#endif



#include "..\..\BFW\Headers\BFW.hpp"



#ifdef BFW_WINDOWS_PLATFORM



void BFW_Hardware_Example()
{
	BFW::Hardware::SerialPort Sp;

	Sp.Open(L"\\\\.\\COM7", 9600);

	while (Sp.CheckConnected())
	{
		Sp.Update();
		char Buff;
		if (Sp.Read(&Buff, 1))
		{
			BFW_PRINT(Buff);
		}
	}
}



#endif



#ifdef BFW_ARDUINO_PLATFORM



void BFW_Hardware_Example()
{
	BFW::Log::Init();

	{
		BFW::Hardware::DigitalOutputPin LedPin;

		LedPin.Bind(3);

		for (unsigned int _Index = 0; _Index < 10; _Index++)
		{
			LedPin.Write(1 - LedPin.GetState());
			BFW::Time::SleepMilliSec(100);
		}
	}

	{
		BFW::Hardware::AnalogOutputPin LedPin;

		LedPin.Bind(3);

		for (unsigned int _Index = 0; _Index < 256; _Index++)
		{
			LedPin.Write(_Index);
			BFW::Time::SleepMilliSec(10);
		}

		for (unsigned int _Index = 254; _Index > 0; _Index--)
		{
			LedPin.Write(_Index);
			BFW::Time::SleepMilliSec(10);
		}

		LedPin.Write(0);
	}

	{
		BFW::Hardware::DigitalInputPullupPin SwitchPin;

		SwitchPin.Bind(4);

		BFW_PRINT("Press the first button!\n");

		while (!SwitchPin[BFW::Enums::_Current])
		{
			SwitchPin.Update();
		}
	}

	{
		BFW::Hardware::DigitalInputPin SwitchPin;

		SwitchPin.Bind(5);

		BFW_PRINT("Press the second button!\n");

		while (!SwitchPin[BFW::Enums::_Current])
		{
			SwitchPin.Update();
		}
	}

	{
		BFW::Hardware::AnalogInputPin JoystickX;
		BFW::Hardware::AnalogInputPin JoystickY;

		JoystickX.Bind(0);
		JoystickY.Bind(1);

		BFW::Hardware::DigitalOutputPin SwitchPin;

		SwitchPin.Bind(6);
		SwitchPin.Write(true);

		BFW_PRINT("Press the joystick button to exit!\n");

		BFW::Time::SleepSec(5);

		while (SwitchPin.Read())
		{
			JoystickX.Update();
			JoystickY.Update();

			BFW_PRINT(JoystickX[BFW::Enums::_Current]);
			BFW_PRINT(' ');
			BFW_PRINT(JoystickY[BFW::Enums::_Current]);
			BFW_PRINT('\n');
		}
	}

	BFW::Log::Stop();
}



#endif
