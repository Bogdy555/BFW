#include "../Headers/BFW.hpp"



BFW::Math::RandomUInt64::RandomUInt64() : Engine(0)
{

}

BFW::Math::RandomUInt64::RandomUInt64(const uint32_t _Seed) : Engine(_Seed)
{

}

BFW::Math::RandomUInt64::RandomUInt64(const RandomUInt64& _Other) : Engine(_Other.Engine)
{

}

BFW::Math::RandomUInt64::RandomUInt64(RandomUInt64&& _Other) noexcept : Engine((std::mt19937_64&&)(_Other.Engine))
{

}

BFW::Math::RandomUInt64::~RandomUInt64()
{

}

void BFW::Math::RandomUInt64::SetSeed(const uint32_t _Seed)
{
	Engine = std::mt19937_64(_Seed);
}

const uint64_t BFW::Math::RandomUInt64::operator() (const uint64_t _Min, const uint64_t _Max)
{
	return std::uniform_int_distribution<uint64_t>(_Min, _Max)(Engine);
}

BFW::Math::RandomUInt64& BFW::Math::RandomUInt64::operator= (const RandomUInt64& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Engine = _Other.Engine;

	return *this;
}

BFW::Math::RandomUInt64& BFW::Math::RandomUInt64::operator= (RandomUInt64&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Engine = (std::mt19937_64&&)(_Other.Engine);

	return *this;
}



BFW::Math::RandomFloat::RandomFloat() : Engine(0)
{

}

BFW::Math::RandomFloat::RandomFloat(const uint32_t _Seed) : Engine(_Seed)
{

}

BFW::Math::RandomFloat::RandomFloat(const RandomFloat& _Other) : Engine(_Other.Engine)
{

}

BFW::Math::RandomFloat::RandomFloat(RandomFloat&& _Other) noexcept : Engine((std::mt19937&&)(_Other.Engine))
{

}

BFW::Math::RandomFloat::~RandomFloat()
{

}

void BFW::Math::RandomFloat::SetSeed(const uint32_t _Seed)
{
	Engine = std::mt19937(_Seed);
}

const float BFW::Math::RandomFloat::operator() (const float _Min, const float _Max)
{
	return std::uniform_real_distribution<float>(_Min, _Max)(Engine);
}

BFW::Math::RandomFloat& BFW::Math::RandomFloat::operator= (const RandomFloat& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Engine = _Other.Engine;

	return *this;
}

BFW::Math::RandomFloat& BFW::Math::RandomFloat::operator= (RandomFloat&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Engine = (std::mt19937&&)(_Other.Engine);

	return *this;
}
