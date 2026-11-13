#include "../Headers/BFW_ESP32.hpp"



void setup()
{
	pinMode(10, OUTPUT);
	digitalWrite(10, HIGH);

	pinMode(38, OUTPUT);
	digitalWrite(38, HIGH);

	if (!SD_MMC.setPins(12, 11, 13))
	{
		BFW_MESSAGE_BOX_ERROR(NULL, BFW_STRING_PREFIX("Error!"), BFW_STRING_PREFIX("An unexpected error occurred!"));
	}

	if (!SD_MMC.begin("/sdcard", true))
	{
		BFW_MESSAGE_BOX_ERROR(NULL, BFW_STRING_PREFIX("Error!"), BFW_STRING_PREFIX("An unexpected error occurred!"));
	}

	esp_pthread_cfg_t cfg = esp_pthread_get_default_config();

	cfg.stack_size = 32768;

	if (esp_pthread_set_cfg(&cfg) != ESP_OK)
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
