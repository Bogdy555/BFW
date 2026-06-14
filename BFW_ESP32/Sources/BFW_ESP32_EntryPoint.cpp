#include "../Headers/BFW_ESP32.hpp"



void setup()
{
	BFW_DEBUG_CALL
	(
		if (!BFW::Log::Init())
		{
			BFW_LOG_LINE(BFW_STRING_PREFIX("An unexpected error occurred!"));
		}
	);

	if (!BFW::Time::Init())
	{
		BFW_LOG_LINE(BFW_STRING_PREFIX("An unexpected error occurred!"));
	}
}

void loop()
{
	BFW_ESP32::RunTime::Application _Application;

	int32_t _ReturnValue = _Application.Run();

	if (_ReturnValue != BFW::MultiProcessing::_NoErrorReturnValue)
	{
		BFW_LOG_LINE(BFW_STRING_PREFIX("An unexpected error occurred!"));
	}
}
