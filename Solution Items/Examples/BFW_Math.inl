#if !defined BFW_DLL_LINK && !defined BFW_STATIC_LINK && !defined BFW_VENDOR

#define BFW_VENDOR

#endif

#if !defined BFW_WINDOWS_PLATFORM && !defined BFW_ARDUINO_PLATFORM

#define BFW_WINDOWS_PLATFORM

#endif



#include "..\..\BFW\Headers\BFW.hpp"



long BFW_Math_Example()
{
	BFW::Log::Init();

	BFW_PRINT(BFW::Math::fMap(100.0f, 0.0f, 100.0f, 0.0f, 1.0f));
	BFW_PRINT('\n');

	BFW_PRINT(BFW::Math::fPeriod(1.5f, 0.0f, 1.0f));
	BFW_PRINT('\n');

	BFW_PRINT(BFW::Math::fAdjustValue(101.0f, 0.0f, 100.0f));
	BFW_PRINT('\n');

#ifdef BFW_WINDOWS_PLATFORM

	BFW::Math::RandomLongLong _Rng(0, 10000000000, 3093839);

	BFW_PRINT(_Rng());
	BFW_PRINT(' ');

	BFW_PRINT(_Rng());
	BFW_PRINT(' ');

	BFW_PRINT(_Rng());
	BFW_PRINT(' ');

	BFW_PRINT(_Rng());
	BFW_PRINT(' ');

	BFW_PRINT(_Rng());
	BFW_PRINT('\n');

	BFW::Math::NoiseFloat _Noise(0, 1000000, 398274, 0.0f, 2.0f, 7374243);

	float _Value = 5.0f;
	_Value = _Noise(_Value);
	BFW_PRINT(_Value);
	BFW_PRINT(' ');

	_Value = _Noise(_Value);
	BFW_PRINT(_Value);
	BFW_PRINT(' ');

	_Value = _Noise(_Value);
	BFW_PRINT(_Value);
	BFW_PRINT(' ');

	_Value = _Noise(_Value);
	BFW_PRINT(_Value);
	BFW_PRINT(' ');

	_Value = _Noise(_Value);
	BFW_PRINT(_Value);
	BFW_PRINT('\n');

	BFW::Math::Crypt MyCrypt;

	MyCrypt.Create(L"BFW_Math_Example_Crypt");

	if (MyCrypt.CheckCreated())
	{
		int a;
		unsigned char* aptr = (unsigned char*)(&a);

		MyCrypt.Get(aptr, sizeof(int));

		BFW_PRINT(a);
		BFW_PRINT(L'\n');

		MyCrypt.Destroy();
	}
	else
	{
		BFW_PRINT(L"Could not create Crypt object!\n");
	}

#endif

#ifdef BFW_ARDUINO_PLATFORM

	float _Noise = BFW::Math::fNoise(1.0f, 0.0f, 0.1f);

	BFW_PRINT(_Noise);
	BFW_PRINT(' ');

	_Noise = BFW::Math::fNoise(1.0f, 0.0f, 0.1f);

	BFW_PRINT(_Noise);
	BFW_PRINT(' ');

	_Noise = BFW::Math::fNoise(1.0f, 0.0f, 0.1f);

	BFW_PRINT(_Noise);
	BFW_PRINT(' ');

	_Noise = BFW::Math::fNoise(1.0f, 0.0f, 0.1f);

	BFW_PRINT(_Noise);
	BFW_PRINT(' ');

	_Noise = BFW::Math::fNoise(1.0f, 0.0f, 0.1f);

	BFW_PRINT(_Noise);
	BFW_PRINT('\n');

#endif

	BFW::Log::Stop();

	return BFW::Enums::_ReturnNoError;
}
