#include "../Headers/BFW_WINDOWS.hpp"



int WINAPI wWinMain(_In_ HINSTANCE _hInstance, _In_opt_ HINSTANCE _hPrevInstance, _In_ LPWSTR _CmdLine, _In_ int _ShowCmd)
{
	if (!BFW::String::Init())
	{
		MessageBox(NULL, BFW_STRING_PREFIX("An unexpected error occurred!"), BFW_STRING_PREFIX("Error!"), MB_OK | MB_ICONERROR);
		return BFW::MultiProcessing::_UnknownErrorReturnValue;
	}

	BFW_DEBUG_CALL
	(
		if (!BFW::Log::Init())
		{
			MessageBox(NULL, BFW_STRING_PREFIX("An unexpected error occurred!"), BFW_STRING_PREFIX("Error!"), MB_OK | MB_ICONERROR);
			BFW::String::Stop();
			return BFW::MultiProcessing::_UnknownErrorReturnValue;
		}
	);

	if (!BFW::Time::Init())
	{
		MessageBox(NULL, BFW_STRING_PREFIX("An unexpected error occurred!"), BFW_STRING_PREFIX("Error!"), MB_OK | MB_ICONERROR);
		BFW_DEBUG_CALL(BFW::Log::Stop());
		BFW::String::Stop();
		return BFW::MultiProcessing::_UnknownErrorReturnValue;
	}

	BFW_WINDOWS::RunTime::Application _Application;

	int32_t _ReturnValue = _Application.Run(_hInstance, _CmdLine, _ShowCmd, BFW_STRING_PREFIX("BFW_WINDOWS_Memory"), BFW_STRING_PREFIX("BFW_WINDOWS_Mutex"));

	if (_ReturnValue != BFW::MultiProcessing::_NoErrorReturnValue)
	{
		MessageBox(NULL, BFW_STRING_PREFIX("An unexpected error occurred!"), BFW_STRING_PREFIX("Error!"), MB_OK | MB_ICONERROR);
	}

	BFW::Time::Stop();
	BFW_DEBUG_CALL(BFW::Log::Stop());
	BFW::String::Stop();

	return _ReturnValue;
}
