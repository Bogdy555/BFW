#include "../Headers/BFW.hpp"



const float BFW_API BFW::Math::Pi = 3.14159265f;
const float BFW_API BFW::Math::DegreesToRadians = 3.14159265f / 180.0f;
const float BFW_API BFW::Math::RadiansToDegrees = 180.0f / 3.14159265f;



const float BFW_API BFW::Math::Mix(const float& _AVal, const float& _BVal, const float _Percentage)
{
	return _AVal * (1.0f - _Percentage) + _BVal * _Percentage;
}

const float BFW_API BFW::Math::Clamp(const float& _Value, const float& _Min, const float& _Max)
{
	return _Value * (_Min <= _Value && _Value <= _Max) + _Min * (_Value < _Min) + _Max * (_Value > _Max);
}

const float BFW_API BFW::Math::Min(const float& _AVal, const float& _BVal)
{
	return _AVal * (_AVal <= _BVal) + _BVal * (_AVal > _BVal);
}

const float BFW_API BFW::Math::Max(const float& _AVal, const float& _BVal)
{
	return _AVal * (_AVal >= _BVal) + _BVal * (_AVal < _BVal);
}
