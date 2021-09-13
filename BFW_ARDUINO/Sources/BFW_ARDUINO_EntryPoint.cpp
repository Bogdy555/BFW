#include "..\Headers\BFW_ARDUINO.hpp"



void setup()
{

}



void loop()
{
	BFW_DEBUG_CALL(BFW::Log::Init());

	BFW_ARDUINO::Application _ApplicationObj;

	unsigned long _ReturnValue = _ApplicationObj.Run();

	BFW_DEBUG_CALL(BFW::Log::Stop());
}
