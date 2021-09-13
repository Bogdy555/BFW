#include "..\Headers\BFW_APP.hpp"



int WINAPI wWinMain(_In_ HINSTANCE _hInstance, _In_opt_ HINSTANCE _hPrevInstance, _In_ LPWSTR _CmdLine, _In_ int _ShowCmd)
{
	if (!BFW::Time::Init())
	{
		MessageBox(NULL, L"An unexpected error occurred!", L"Error", MB_OK | MB_ICONERROR);
		return BFW::Enums::_ReturnError;
	}

	BFW_DEBUG_CALL
	(
		if (!BFW::Log::Init())
		{
			MessageBox(NULL, L"An unexpected error occurred!", L"Error", MB_OK | MB_ICONERROR);
			return BFW::Enums::_ReturnError;
		}
	);

	BFW_APP::Application _ApplicationObj;

	unsigned int _ReturnValue = _ApplicationObj.Run(_hInstance, _CmdLine, _ShowCmd, L"BFW_APP");

	BFW_DEBUG_CALL(BFW::Log::Stop());

	BFW::Time::Stop();

	return _ReturnValue;
}
