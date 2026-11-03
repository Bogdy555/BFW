#include "../Headers/BFW_WINDOWS.hpp"



int WINAPI wWinMain(_In_ HINSTANCE _hInstance, _In_opt_ HINSTANCE _hPrevInstance, _In_ LPWSTR _CmdLine, _In_ int _ShowCmd)
{
	if (!BFW::String::Init())
	{
		BFW_MESSAGE_BOX_ERROR(NULL, BFW_STRING_PREFIX("Error!"), BFW_STRING_PREFIX("An unexpected error occurred!"));
		return BFW::MultiProcessing::_UnknownErrorReturnValue;
	}

	BFW_DEBUG_CALL
	(
		if (!BFW::Log::Init())
		{
			BFW_MESSAGE_BOX_ERROR(NULL, BFW_STRING_PREFIX("Error!"), BFW_STRING_PREFIX("An unexpected error occurred!"));
			BFW::String::Stop();
			return BFW::MultiProcessing::_UnknownErrorReturnValue;
		}
	);

	if (!BFW::Time::Init())
	{
		BFW_MESSAGE_BOX_ERROR(NULL, BFW_STRING_PREFIX("Error!"), BFW_STRING_PREFIX("An unexpected error occurred!"));
		BFW_DEBUG_CALL(BFW::Log::Stop());
		BFW::String::Stop();
		return BFW::MultiProcessing::_UnknownErrorReturnValue;
	}

	BFW_WINDOWS::RunTime::Application _Application;

	int32_t _ReturnValue = _Application.Run(_hInstance, _CmdLine, _ShowCmd, BFW_STRING_PREFIX("BFW_WINDOWS_Memory"), BFW_STRING_PREFIX("BFW_WINDOWS_Mutex"));

	if (_ReturnValue != BFW::MultiProcessing::_NoErrorReturnValue)
	{
		BFW_MESSAGE_BOX_ERROR(NULL, BFW_STRING_PREFIX("Error!"), BFW_STRING_PREFIX("An unexpected error occurred!"));
	}

	BFW::Time::Stop();
	BFW_DEBUG_CALL(BFW::Log::Stop());
	BFW::String::Stop();

	return _ReturnValue;
}
