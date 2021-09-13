#include "..\Headers\BFW.hpp"



const double BFW_API BFW::Math::dPi = 3.14159265358979323846;
const double BFW_API BFW::Math::dDegreesToRadians = 3.14159265358979323846 / 180.0;
const double BFW_API BFW::Math::dRadiansToDegrees = 180.0 / 3.14159265358979323846;

const float BFW_API BFW::Math::fPi = 3.14159265358979323846f;
const float BFW_API BFW::Math::fDegreesToRadians = 3.14159265358979323846f / 180.0f;
const float BFW_API BFW::Math::fRadiansToDegrees = 180.0f / 3.14159265358979323846f;



#ifdef BFW_WINDOWS_PLATFORM



BFW::Math::RandomLong::RandomLong(const long _Min, const long _Max, const unsigned long _Seed) :
	Min(_Min), Max(_Max), Seed(_Seed), Count(0),
	Generator((std::mt19937&&)(std::mt19937(Seed))),
	Distribution((std::uniform_int_distribution<long>&&)(std::uniform_int_distribution<long>(Min, Max)))
{

}

BFW::Math::RandomLong::RandomLong(const RandomLong& _Other) :
	Min(_Other.Min), Max(_Other.Max), Seed(_Other.Seed), Count(_Other.Count),
	Generator((const std::mt19937&)(_Other.Generator)),
	Distribution((const std::uniform_int_distribution<long>&)(_Other.Distribution))
{

}

BFW::Math::RandomLong::RandomLong(RandomLong&& _Other) noexcept :
	Min(_Other.Min), Max(_Other.Max), Seed(_Other.Seed), Count(_Other.Count),
	Generator((std::mt19937&&)(_Other.Generator)), Distribution((std::uniform_int_distribution<long>&&)(_Other.Distribution))
{
	_Other.SetSeed(0, 1000000, 0);
}

BFW::Math::RandomLong::~RandomLong()
{

}

void BFW::Math::RandomLong::SetSeed(const long _Min, const long _Max, const unsigned long _Seed)
{
	Min = _Min;
	Max = _Max;
	Seed = _Seed;
	Count = 0;
	Generator = (std::mt19937&&)(std::mt19937(Seed));
	Distribution = (std::uniform_int_distribution<long>&&)(std::uniform_int_distribution<long>(Min, Max));
}

void BFW::Math::RandomLong::GetSeed(long* _Min, long* _Max, unsigned long* _Seed) const
{
	if (_Min)
	{
		*_Min = Min;
	}
	if (_Max)
	{
		*_Max = Max;
	}
	if (_Seed)
	{
		*_Seed = Seed;
	}
}

const unsigned long long BFW::Math::RandomLong::GetCount() const
{
	return Count;
}

long BFW::Math::RandomLong::operator() ()
{
	Count++;
	return Distribution(Generator);
}

void BFW::Math::RandomLong::operator= (const RandomLong& _Other)
{
	Min = _Other.Min;
	Max = _Other.Max;
	Seed = _Other.Seed;
	Count = _Other.Count;
	Generator = (const std::mt19937&)(_Other.Generator);
	Distribution = (const std::uniform_int_distribution<long>&)(_Other.Distribution);
}

void BFW::Math::RandomLong::operator= (RandomLong&& _Other) noexcept
{
	Min = _Other.Min;
	Max = _Other.Max;
	Seed = _Other.Seed;
	Count = _Other.Count;
	Generator = (std::mt19937&&)(_Other.Generator);
	Distribution = (std::uniform_int_distribution<long>&&)(_Other.Distribution);

	_Other.SetSeed(0, 1000000, 0);
}



BFW::Math::RandomLongLong::RandomLongLong(const long long _Min, const long long _Max, const unsigned long _Seed) :
	Min(_Min), Max(_Max), Seed(_Seed), Count(0),
	Generator((std::mt19937_64&&)(std::mt19937_64(Seed))),
	Distribution((std::uniform_int_distribution<long long>&&)(std::uniform_int_distribution<long long>(Min, Max)))
{

}

BFW::Math::RandomLongLong::RandomLongLong(const RandomLongLong& _Other) :
	Min(_Other.Min), Max(_Other.Max), Seed(_Other.Seed), Count(_Other.Count),
	Generator((const std::mt19937_64&)(_Other.Generator)),
	Distribution((const std::uniform_int_distribution<long long>&)(_Other.Distribution))
{

}

BFW::Math::RandomLongLong::RandomLongLong(RandomLongLong&& _Other) noexcept :
	Min(_Other.Min), Max(_Other.Max), Seed(_Other.Seed), Count(_Other.Count),
	Generator((std::mt19937_64&&)(_Other.Generator)), Distribution((std::uniform_int_distribution<long long>&&)(_Other.Distribution))
{
	_Other.SetSeed(0, 1000000, 0);
}

BFW::Math::RandomLongLong::~RandomLongLong()
{

}

void BFW::Math::RandomLongLong::SetSeed(const long long _Min, const long long _Max, const unsigned long _Seed)
{
	Min = _Min;
	Max = _Max;
	Seed = _Seed;
	Count = 0;
	Generator = (std::mt19937_64&&)(std::mt19937_64(Seed));
	Distribution = (std::uniform_int_distribution<long long>&&)(std::uniform_int_distribution<long long>(Min, Max));
}

void BFW::Math::RandomLongLong::GetSeed(long long* _Min, long long* _Max, unsigned long* _Seed) const
{
	if (_Min)
	{
		*_Min = Min;
	}
	if (_Max)
	{
		*_Max = Max;
	}
	if (_Seed)
	{
		*_Seed = Seed;
	}
}

const unsigned long long BFW::Math::RandomLongLong::GetCount() const
{
	return Count;
}

long long BFW::Math::RandomLongLong::operator() ()
{
	Count++;
	return Distribution(Generator);
}

void BFW::Math::RandomLongLong::operator= (const RandomLongLong& _Other)
{
	Min = _Other.Min;
	Max = _Other.Max;
	Seed = _Other.Seed;
	Count = _Other.Count;
	Generator = (const std::mt19937_64&)(_Other.Generator);
	Distribution = (const std::uniform_int_distribution<long long>&)(_Other.Distribution);
}

void BFW::Math::RandomLongLong::operator= (RandomLongLong&& _Other) noexcept
{
	Min = _Other.Min;
	Max = _Other.Max;
	Seed = _Other.Seed;
	Count = _Other.Count;
	Generator = (std::mt19937_64&&)(_Other.Generator);
	Distribution = (std::uniform_int_distribution<long long>&&)(_Other.Distribution);

	_Other.SetSeed(0, 1000000, 0);
}



BFW::Math::RandomFloat::RandomFloat(const float _Min, const float _Max, const unsigned long _Seed) :
	Min(_Min), Max(_Max), Seed(_Seed), Count(0),
	Generator((std::mt19937&&)(std::mt19937(Seed))),
	Distribution((std::uniform_real_distribution<float>&&)(std::uniform_real_distribution<float>(Min, Max)))
{

}

BFW::Math::RandomFloat::RandomFloat(const RandomFloat& _Other) :
	Min(_Other.Min), Max(_Other.Max), Seed(_Other.Seed), Count(_Other.Count),
	Generator((const std::mt19937&)(_Other.Generator)),
	Distribution((const std::uniform_real_distribution<float>&)(_Other.Distribution))
{

}

BFW::Math::RandomFloat::RandomFloat(RandomFloat&& _Other) noexcept :
	Min(_Other.Min), Max(_Other.Max), Seed(_Other.Seed), Count(_Other.Count),
	Generator((std::mt19937&&)(_Other.Generator)), Distribution((std::uniform_real_distribution<float>&&)(_Other.Distribution))
{
	_Other.SetSeed(0.0f, 1.0f, 0);
}

BFW::Math::RandomFloat::~RandomFloat()
{

}

void BFW::Math::RandomFloat::SetSeed(const float _Min, const float _Max, const unsigned long _Seed)
{
	Min = _Min;
	Max = _Max;
	Seed = _Seed;
	Count = 0;
	Generator = (std::mt19937&&)(std::mt19937(Seed));
	Distribution = (std::uniform_real_distribution<float>&&)(std::uniform_real_distribution<float>(Min, Max));
}

void BFW::Math::RandomFloat::GetSeed(float* _Min, float* _Max, unsigned long* _Seed) const
{
	if (_Min)
	{
		*_Min = Min;
	}
	if (_Max)
	{
		*_Max = Max;
	}
	if (_Seed)
	{
		*_Seed = Seed;
	}
}

const unsigned long long BFW::Math::RandomFloat::GetCount() const
{
	return Count;
}

float BFW::Math::RandomFloat::operator() ()
{
	Count++;
	return Distribution(Generator);
}

void BFW::Math::RandomFloat::operator= (const RandomFloat& _Other)
{
	Min = _Other.Min;
	Max = _Other.Max;
	Seed = _Other.Seed;
	Count = _Other.Count;
	Generator = (const std::mt19937&)(_Other.Generator);
	Distribution = (const std::uniform_real_distribution<float>&)(_Other.Distribution);
}

void BFW::Math::RandomFloat::operator= (RandomFloat&& _Other) noexcept
{
	Min = _Other.Min;
	Max = _Other.Max;
	Seed = _Other.Seed;
	Count = _Other.Count;
	Generator = (std::mt19937&&)(_Other.Generator);
	Distribution = (std::uniform_real_distribution<float>&&)(_Other.Distribution);

	_Other.SetSeed(0.0f, 1.0f, 0);
}



BFW::Math::RandomDouble::RandomDouble(const double _Min, const double _Max, const unsigned long _Seed) :
	Min(_Min), Max(_Max), Seed(_Seed), Count(0),
	Generator((std::mt19937_64&&)(std::mt19937_64(Seed))),
	Distribution((std::uniform_real_distribution<double>&&)(std::uniform_real_distribution<double>(Min, Max)))
{

}

BFW::Math::RandomDouble::RandomDouble(const RandomDouble& _Other) :
	Min(_Other.Min), Max(_Other.Max), Seed(_Other.Seed), Count(_Other.Count),
	Generator((const std::mt19937_64&)(_Other.Generator)),
	Distribution((const std::uniform_real_distribution<double>&)(_Other.Distribution))
{

}

BFW::Math::RandomDouble::RandomDouble(RandomDouble&& _Other) noexcept :
	Min(_Other.Min), Max(_Other.Max), Seed(_Other.Seed), Count(_Other.Count),
	Generator((std::mt19937_64&&)(_Other.Generator)), Distribution((std::uniform_real_distribution<double>&&)(_Other.Distribution))
{
	_Other.SetSeed(0.0, 1.0, 0);
}

BFW::Math::RandomDouble::~RandomDouble()
{

}

void BFW::Math::RandomDouble::SetSeed(const double _Min, const double _Max, const unsigned long _Seed)
{
	Min = _Min;
	Max = _Max;
	Seed = _Seed;
	Count = 0;
	Generator = (std::mt19937_64&&)(std::mt19937_64(Seed));
	Distribution = (std::uniform_real_distribution<double>&&)(std::uniform_real_distribution<double>(Min, Max));
}

void BFW::Math::RandomDouble::GetSeed(double* _Min, double* _Max, unsigned long* _Seed) const
{
	if (_Min)
	{
		*_Min = Min;
	}
	if (_Max)
	{
		*_Max = Max;
	}
	if (_Seed)
	{
		*_Seed = Seed;
	}
}

const unsigned long long BFW::Math::RandomDouble::GetCount() const
{
	return Count;
}

double BFW::Math::RandomDouble::operator() ()
{
	Count++;
	return Distribution(Generator);
}

void BFW::Math::RandomDouble::operator= (const RandomDouble& _Other)
{
	Min = _Other.Min;
	Max = _Other.Max;
	Seed = _Other.Seed;
	Count = _Other.Count;
	Generator = (const std::mt19937_64&)(_Other.Generator);
	Distribution = (const std::uniform_real_distribution<double>&)(_Other.Distribution);
}

void BFW::Math::RandomDouble::operator= (RandomDouble&& _Other) noexcept
{
	Min = _Other.Min;
	Max = _Other.Max;
	Seed = _Other.Seed;
	Count = _Other.Count;
	Generator = (std::mt19937_64&&)(_Other.Generator);
	Distribution = (std::uniform_real_distribution<double>&&)(_Other.Distribution);

	_Other.SetSeed(0.0, 1.0, 0);
}



BFW::Math::NoiseFloat::NoiseFloat(const long _MinL, const long _MaxL, const unsigned long _SeedL, const float _MinF, const float _MaxF, const unsigned long _SeedF) :
	RngLong(_MinL, _MaxL, _SeedL), RngFloat(_MinF, _MaxF, _SeedF)
{

}

BFW::Math::NoiseFloat::NoiseFloat(const NoiseFloat& _Other) :
	RngLong((const RandomLong&)(_Other.RngLong)), RngFloat((const RandomFloat&)(_Other.RngFloat))
{

}

BFW::Math::NoiseFloat::NoiseFloat(NoiseFloat&& _Other) noexcept :
	RngLong((RandomLong&&)(_Other.RngLong)), RngFloat((RandomFloat&&)(_Other.RngFloat))
{

}

BFW::Math::NoiseFloat::~NoiseFloat()
{

}

void BFW::Math::NoiseFloat::SetSeed(const long _MinL, const long _MaxL, const unsigned long _SeedL, const float _MinF, const float _MaxF, const unsigned long _SeedF)
{
	RngLong.SetSeed(_MinL, _MaxL, _SeedL);
	RngFloat.SetSeed(_MinF, _MaxF, _SeedF);
}

void BFW::Math::NoiseFloat::GetSeed(long* _MinL, long* _MaxL, unsigned long* _SeedL, float* _MinF, float* _MaxF, unsigned long* _SeedF) const
{
	RngLong.GetSeed(_MinL, _MaxL, _SeedL);
	RngFloat.GetSeed(_MinF, _MaxF, _SeedF);
}

const unsigned long long BFW::Math::NoiseFloat::GetCount() const
{
	return RngLong.GetCount();
}

float BFW::Math::NoiseFloat::operator() (const float _Value)
{
	bool _PositiveSign = (RngLong() % 2) != 0;
	float _Noise = RngFloat();
	return _Value + _Noise * _PositiveSign - _Noise * (!_PositiveSign);
}

void BFW::Math::NoiseFloat::operator= (const NoiseFloat& _Other)
{
	RngLong = (const RandomLong&)(_Other.RngLong);
	RngFloat = (const RandomFloat&)(_Other.RngFloat);
}

void BFW::Math::NoiseFloat::operator= (NoiseFloat&& _Other) noexcept
{
	RngLong = (RandomLong&&)(_Other.RngLong);
	RngFloat = (RandomFloat&&)(_Other.RngFloat);
}



BFW::Math::NoiseDouble::NoiseDouble(const long long _MinLL, const long long _MaxLL, const unsigned long _SeedLL, const double _MinD, const double _MaxD, const unsigned long _SeedD) :
	RngLongLong(_MinLL, _MaxLL, _SeedLL), RngDouble(_MinD, _MaxD, _SeedD)
{

}

BFW::Math::NoiseDouble::NoiseDouble(const NoiseDouble& _Other) :
	RngLongLong((const RandomLongLong&)(_Other.RngLongLong)), RngDouble((const RandomDouble&)(_Other.RngDouble))
{

}

BFW::Math::NoiseDouble::NoiseDouble(NoiseDouble&& _Other) noexcept :
	RngLongLong((RandomLongLong&&)(_Other.RngLongLong)), RngDouble((RandomDouble&&)(_Other.RngDouble))
{

}

BFW::Math::NoiseDouble::~NoiseDouble()
{

}

void BFW::Math::NoiseDouble::SetSeed(const long long _MinLL, const long long _MaxLL, const unsigned long _SeedLL, const double _MinD, const double _MaxD, const unsigned long _SeedD)
{
	RngLongLong.SetSeed(_MinLL, _MaxLL, _SeedLL);
	RngDouble.SetSeed(_MinD, _MaxD, _SeedD);
}

void BFW::Math::NoiseDouble::GetSeed(long long* _MinLL, long long* _MaxLL, unsigned long* _SeedLL, double* _MinD, double* _MaxD, unsigned long* _SeedD) const
{
	RngLongLong.GetSeed(_MinLL, _MaxLL, _SeedLL);
	RngDouble.GetSeed(_MinD, _MaxD, _SeedD);
}

const unsigned long long BFW::Math::NoiseDouble::GetCount() const
{
	return RngLongLong.GetCount();
}

double BFW::Math::NoiseDouble::operator() (const double _Value)
{
	bool _PositiveSign = (RngLongLong() % 2) != 0;
	double _Noise = RngDouble();
	return _Value + _Noise * _PositiveSign - _Noise * (!_PositiveSign);
}

void BFW::Math::NoiseDouble::operator= (const NoiseDouble& _Other)
{
	RngLongLong = (const RandomLongLong&)(_Other.RngLongLong);
	RngDouble = (const RandomDouble&)(_Other.RngDouble);
}

void BFW::Math::NoiseDouble::operator= (NoiseDouble&& _Other) noexcept
{
	RngLongLong = (RandomLongLong&&)(_Other.RngLongLong);
	RngDouble = (RandomDouble&&)(_Other.RngDouble);
}



BFW::Math::Crypt::Crypt() : hCrypt(NULL), Created(false), Name(nullptr)
{

}

BFW::Math::Crypt::Crypt(Crypt&& _Other) noexcept : hCrypt(_Other.hCrypt), Created(_Other.Created), Name(_Other.Name)
{
	_Other.hCrypt = NULL;
	_Other.Created = false;
	_Other.Name = nullptr;
}

BFW::Math::Crypt::~Crypt()
{

}

bool BFW::Math::Crypt::Create(const wchar_t* _Name)
{
	Destroy();

	if (!_Name)
	{
		BFW_DEBUG_BREAK_MSG(L"A name is required to create a Crypt object!");
		return false;
	}

	Name = _Name;

	Created = CryptAcquireContext(&hCrypt, Name, NULL, PROV_RSA_FULL, CRYPT_NEWKEYSET);

	if (Created)
	{
		return true;
	}

	Created = CryptAcquireContext(&hCrypt, Name, NULL, PROV_RSA_FULL, 0);

	if (Created)
	{
		return true;
	}

	hCrypt = NULL;
	Created = false;

	return false;
}

void BFW::Math::Crypt::Destroy()
{
	if (hCrypt)
	{
		CryptReleaseContext(hCrypt, 0);
		hCrypt = NULL;
	}
	Created = false;
	Name = nullptr;
}

bool BFW::Math::Crypt::Get(unsigned char* _Buff, const unsigned long _Size)
{
	return CryptGenRandom(hCrypt, _Size, _Buff);
}

const bool BFW::Math::Crypt::CheckCreated() const
{
	return Created;
}

const wchar_t* BFW::Math::Crypt::GetName() const
{
	return Name;
}

void BFW::Math::Crypt::operator= (Crypt&& _Other) noexcept
{
	hCrypt = _Other.hCrypt;
	Created = _Other.Created;
	Name = _Other.Name;

	_Other.hCrypt = NULL;
	_Other.Created = false;
	_Other.Name = nullptr;
}



#endif



#ifdef BFW_ARDUINO_PLATFORM



void BFW_API BFW::Math::SetRandomSeed(const unsigned long _Seed)
{
	randomSeed(_Seed);
}

long BFW_API BFW::Math::lRandom(const long _Min, const long _Max)
{
	return random(_Min, _Max);
}

long long BFW_API BFW::Math::llRandom(const long long _Min, const long long _Max)
{
	long long _Value = random() + (random() << 16);
	_Value = llAdjustValue(_Value, _Min, _Max);
	return _Value;
}

float BFW_API BFW::Math::fRandom(const float _Min, const float _Max)
{
	float _Value = (float)(lRandom(_Min, _Max));
	float _AfterVal = (float)(lRandom() % 100) / 100.0f;
	_Value = fAdjustValue(_Value + _AfterVal, _Min, _Max);
	return _Value;
}

double BFW_API BFW::Math::dRandom(const double _Min, const double _Max)
{
	double _Value = (double)(llRandom(_Min, _Max));
	double _AfterVal = (double)(llRandom() % 100) / 100.0;
	_Value = dAdjustValue(_Value + _AfterVal, _Min, _Max);
	return _Value;
}

float BFW_API BFW::Math::fNoise(const float _Value, const float _Min, const float _Max)
{
	bool _PositiveSign = (lRandom() % 2) != 0;
	float _Noise = fRandom(_Min, _Max);
	return _Value + _Noise * _PositiveSign - _Noise * (!_PositiveSign);
}

double BFW_API BFW::Math::dNoise(const double _Value, const double _Min, const double _Max)
{
	bool _PositiveSign = (llRandom() % 2) != 0;
	double _Noise = dRandom(_Min, _Max);
	return _Value + _Noise * _PositiveSign - _Noise * (!_PositiveSign);
}



#endif



float BFW_API BFW::Math::fSqrt(const float _Value)
{
	return sqrtf(_Value);
}

float BFW_API BFW::Math::fSin(const float _Value)
{
	return sinf(_Value);
}

float BFW_API BFW::Math::fCos(const float _Value)
{
	return cosf(_Value);
}

float BFW_API BFW::Math::fTan(const float _Value)
{
	return tanf(_Value);
}

float BFW_API BFW::Math::fCoTan(const float _Value)
{
	return 1.0f / tanf(_Value);
}

float BFW_API BFW::Math::fASin(const float _Value)
{
	return asinf(_Value);
}

float BFW_API BFW::Math::fACos(const float _Value)
{
	return acosf(_Value);
}

float BFW_API BFW::Math::fATan(const float _Value)
{
	return atanf(_Value);
}

float BFW_API BFW::Math::fACoTan(const float _Value)
{
	return atanf(1.0f / _Value);
}

double BFW_API BFW::Math::dSqrt(const double _Value)
{
	return sqrt(_Value);
}

double BFW_API BFW::Math::dSin(const double _Value)
{
	return sin(_Value);
}

double BFW_API BFW::Math::dCos(const double _Value)
{
	return cos(_Value);
}

double BFW_API BFW::Math::dTan(const double _Value)
{
	return tan(_Value);
}

double BFW_API BFW::Math::dCoTan(const double _Value)
{
	return 1.0 / tan(_Value);
}

double BFW_API BFW::Math::dASin(const double _Value)
{
	return asin(_Value);
}

double BFW_API BFW::Math::dACos(const double _Value)
{
	return acos(_Value);
}

double BFW_API BFW::Math::dATan(const double _Value)
{
	return atan(_Value);
}

double BFW_API BFW::Math::dACoTan(const double _Value)
{
	return atan(1.0 / _Value);
}

long BFW_API BFW::Math::lModule(const long _Value)
{
	return _Value * (_Value >= 0) - _Value * (_Value < 0);
}

long long BFW_API BFW::Math::llModule(const long long _Value)
{
	return _Value * (_Value >= 0) - _Value * (_Value < 0);
}

float BFW_API BFW::Math::fModule(const float _Value)
{
	return _Value * (_Value >= 0.0f) - _Value * (_Value < 0.0f);
}

double BFW_API BFW::Math::dModule(const double _Value)
{
	return _Value * (_Value >= 0.0) - _Value * (_Value < 0.0);
}

void BFW_API BFW::Math::lSwap(long& _A, long& _B)
{
	long _Aux = _A;
	_A = _B;
	_B = _Aux;
}

void BFW_API BFW::Math::llSwap(long long& _A, long long& _B)
{
	long long _Aux = _A;
	_A = _B;
	_B = _Aux;
}

void BFW_API BFW::Math::fSwap(float& _A, float& _B)
{
	float _Aux = _A;
	_A = _B;
	_B = _Aux;
}

void BFW_API BFW::Math::dSwap(double& _A, double& _B)
{
	double _Aux = _A;
	_A = _B;
	_B = _Aux;
}

long BFW_API BFW::Math::lPeriod(const long _Value, const long _Min, const long _Max)
{
	return
		(long)
		(
			_Value * (_Value >= _Min && _Value < _Max) +
			(_Value - (_Max - _Min) * (float)((long)((_Value - _Max) / (_Max - _Min)) + 1)) * (_Value >= _Max) +
			(_Value + (_Max - _Min) * (float)((long)((_Min - _Value) / (_Max - _Min)) + 1)) * (_Value < _Min)
		);
}

long long BFW_API BFW::Math::llPeriod(const long long _Value, const long long _Min, const long long _Max)
{
	return
		(long long)
		(
			_Value * (_Value >= _Min && _Value < _Max) +
			(_Value - (_Max - _Min) * (double)((long long)((_Value - _Max) / (_Max - _Min)) + 1)) * (_Value >= _Max) +
			(_Value + (_Max - _Min) * (double)((long long)((_Min - _Value) / (_Max - _Min)) + 1)) * (_Value < _Min)
		);
}

float BFW_API BFW::Math::fPeriod(const float _Value, const float _Min, const float _Max)
{
	return
		_Value * (_Value >= _Min && _Value < _Max) +
		(_Value - (_Max - _Min) * (float)((long)((_Value - _Max) / (_Max - _Min)) + 1)) * (_Value >= _Max) +
		(_Value + (_Max - _Min) * (float)((long)((_Min - _Value) / (_Max - _Min)) + 1)) * (_Value < _Min);
}

double BFW_API BFW::Math::dPeriod(const double _Value, const double _Min, const double _Max)
{
	return
		_Value * (_Value >= _Min && _Value < _Max) +
		(_Value - (_Max - _Min) * (double)((long long)((_Value - _Max) / (_Max - _Min)) + 1)) * (_Value >= _Max) +
		(_Value + (_Max - _Min) * (double)((long long)((_Min - _Value) / (_Max - _Min)) + 1)) * (_Value < _Min);
}

long BFW_API BFW::Math::lMap(const long _Value, const long _Min, const long _Max, const long _NewMin, const long _NewMax)
{
	return (_Value - _Min) * (_NewMax - _NewMin) / (_Max - _Min) + _NewMin;
}

long long BFW_API BFW::Math::llMap(const long long _Value, const long long _Min, const long long _Max, const long long _NewMin, const long long _NewMax)
{
	return (_Value - _Min) * (_NewMax - _NewMin) / (_Max - _Min) + _NewMin;
}

float BFW_API BFW::Math::fMap(const float _Value, const float _Min, const float _Max, const float _NewMin, const float _NewMax)
{
	return (_Value - _Min) * (_NewMax - _NewMin) / (_Max - _Min) + _NewMin;
}

double BFW_API BFW::Math::dMap(const double _Value, const double _Min, const double _Max, const double _NewMin, const double _NewMax)
{
	return (_Value - _Min) * (_NewMax - _NewMin) / (_Max - _Min) + _NewMin;
}

long BFW_API BFW::Math::lAdjustValue(const long _Value, const long _Min, const long _Max)
{
	return _Value * (_Value >= _Min && _Value <= _Max) + _Min * (_Value < _Min) + _Max * (_Value > _Max);
}

long long BFW_API BFW::Math::llAdjustValue(const long long _Value, const long long _Min, const long long _Max)
{
	return _Value * (_Value >= _Min && _Value <= _Max) + _Min * (_Value < _Min) + _Max * (_Value > _Max);
}

float BFW_API BFW::Math::fAdjustValue(const float _Value, const float _Min, const float _Max)
{
	return _Value * (_Value >= _Min && _Value <= _Max) + _Min * (_Value < _Min) + _Max * (_Value > _Max);
}

double BFW_API BFW::Math::dAdjustValue(const double _Value, const double _Min, const double _Max)
{
	return _Value * (_Value >= _Min && _Value <= _Max) + _Min * (_Value < _Min) + _Max * (_Value > _Max);
}
