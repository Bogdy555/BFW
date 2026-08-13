#include "../Headers/BFW_ESP32.hpp"



void setup()
{
	if (!BFW::String::Init())
	{
		BFW_MESSAGE_BOX_ERROR(NULL, BFW_STRING_PREFIX("Error!"), BFW_STRING_PREFIX("An unexpected error occurred!"));
	}

	BFW_DEBUG_CALL
	(
		if (!BFW::Log::Init())
		{
			BFW_MESSAGE_BOX_ERROR(NULL, BFW_STRING_PREFIX("Error!"), BFW_STRING_PREFIX("An unexpected error occurred!"));
		}
	);

	if (!BFW::Time::Init())
	{
		BFW_MESSAGE_BOX_ERROR(NULL, BFW_STRING_PREFIX("Error!"), BFW_STRING_PREFIX("An unexpected error occurred!"));
	}
}

void loop()
{
	BFW_ESP32::RunTime::Application _Application;

	int32_t _ReturnValue = _Application.Run();

	if (_ReturnValue != BFW::MultiProcessing::_NoErrorReturnValue)
	{
		BFW_MESSAGE_BOX_ERROR(NULL, BFW_STRING_PREFIX("Error!"), BFW_STRING_PREFIX("An unexpected error occurred!"));
	}
}
