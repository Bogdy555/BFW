#include "../Headers/BFW_LINUX.hpp"



int main(const int32_t _ArgC, const BFW_CHAR_TYPE** _ArgV)
{
	if (!BFW::String::Init())
	{
		int32_t _Result = system("notify-send \"Error!\" \"An unexpected error occurred!\"");
		return BFW::MultiProcessing::_UnknownErrorReturnValue;
	}

	BFW_DEBUG_CALL
	(
		if (!BFW::Log::Init())
		{
			int32_t _Result = system("notify-send \"Error!\" \"An unexpected error occurred!\"");
			BFW::String::Stop();
			return BFW::MultiProcessing::_UnknownErrorReturnValue;
		}
	);

	if (!BFW::Time::Init())
	{
		int32_t _Result = system("notify-send \"Error!\" \"An unexpected error occurred!\"");
		BFW_DEBUG_CALL(BFW::Log::Stop());
		BFW::String::Stop();
		return BFW::MultiProcessing::_UnknownErrorReturnValue;
	}

	BFW_LINUX::RunTime::Application _Application;

	int32_t _ReturnValue = _Application.Run(_ArgC, _ArgV, BFW_STRING_PREFIX("BFW_LINUX_Memory"), BFW_STRING_PREFIX("BFW_LINUX_Mutex"));

	if (_ReturnValue != BFW::MultiProcessing::_NoErrorReturnValue)
	{
		int32_t _Result = system("notify-send \"Error!\" \"An unexpected error occurred!\"");
	}

	BFW::Time::Stop();
	BFW_DEBUG_CALL(BFW::Log::Stop());
	BFW::String::Stop();

	return _ReturnValue;
}
