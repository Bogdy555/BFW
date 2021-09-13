#include "..\Headers\BFW.hpp"



BFW::Math::Vec2f::Vec2f(const float _x, const float _y) : x(_x), y(_y)
{

}

BFW::Math::Vec2f::Vec2f(const Vec2f& _Other) : x(_Other.x), y(_Other.y)
{

}

BFW::Math::Vec2f::Vec2f(Vec2f&& _Other) noexcept : x(_Other.x), y(_Other.y)
{
	_Other.x = 0.0f;
	_Other.y = 0.0f;
}

BFW::Math::Vec2f::~Vec2f()
{

}

float* BFW::Math::Vec2f::Data()
{
	return &x;
}

const float* BFW::Math::Vec2f::Data() const
{
	return &x;
}

const float BFW::Math::Vec2f::Magnitude() const
{
	return fSqrt(x * x + y * y);
}

const float BFW::Math::Vec2f::DotProduct(const Vec2f& _Other) const
{
	return x * _Other.x + y * _Other.y;
}

const float BFW::Math::Vec2f::GetAngle(const Vec2f& _Center, const Vec2f& _Other) const
{
	Vec2f _V = *this - _Center;
	return fPeriod(fACos(_V.DotProduct(_Other) / (_V.Magnitude() * _Other.Magnitude())), 0.0f, fPi * 2.0f);
}

const BFW::Math::Vec2f BFW::Math::Vec2f::Rotated(const float _Angle, const Vec2f& _Center) const
{
	float _NewX = x - _Center.x;
	float _NewY = y - _Center.y;
	float _Sin = fSin(_Angle);
	float _Cos = fCos(_Angle);

	float _x = _Cos * _NewX - _Sin * _NewY + _Center.x;
	float _y = _Sin * _NewX + _Cos * _NewY + _Center.y;

	return Vec2f(_x, _y);
}

const BFW::Math::Vec2f& BFW::Math::Vec2f::Rotate(const float _Angle, const Vec2f& _Center)
{
	float _NewX = x - _Center.x;
	float _NewY = y - _Center.y;
	float _Sin = fSin(_Angle);
	float _Cos = fCos(_Angle);

	x = _Cos * _NewX - _Sin * _NewY + _Center.x;
	y = _Sin * _NewX + _Cos * _NewY + _Center.y;

	return *this;
}

const BFW::Math::Vec2f BFW::Math::Vec2f::Flipped(const Vec2f& _U, const Vec2f& _Center) const
{
	float _Angle = _U.GetAngle() * 2.0f;
	float _NewX = x - _Center.x;
	float _NewY = y - _Center.y;
	float _Sin = fSin(_Angle);
	float _Cos = fCos(_Angle);

	float _x = _Cos * _NewX + _Sin * _NewY + _Center.x;
	float _y = _Sin * _NewX - _Cos * _NewY + _Center.y;

	return Vec2f(_x, _y);
}

const BFW::Math::Vec2f& BFW::Math::Vec2f::Flip(const Vec2f& _U, const Vec2f& _Center)
{
	float _Angle = _U.GetAngle() * 2.0f;
	float _NewX = x - _Center.x;
	float _NewY = y - _Center.y;
	float _Sin = fSin(_Angle);
	float _Cos = fCos(_Angle);

	x = _Cos * _NewX + _Sin * _NewY + _Center.x;
	y = _Sin * _NewX - _Cos * _NewY + _Center.y;

	return *this;
}

const BFW::Math::Vec2f& BFW::Math::Vec2f::operator+ () const
{
	return *this;
}

const BFW::Math::Vec2f BFW::Math::Vec2f::operator- () const
{
	return Vec2f(-x, -y);
}

const BFW::Math::Vec2f BFW::Math::Vec2f::operator+ (const Vec2f& _Other) const
{
	float _x = x + _Other.x;
	float _y = y + _Other.y;

	return Vec2f(_x, _y);
}

const BFW::Math::Vec2f& BFW::Math::Vec2f::operator+= (const Vec2f& _Other)
{
	x += _Other.x;
	y += _Other.y;

	return *this;
}

const BFW::Math::Vec2f BFW::Math::Vec2f::operator+ (const float _Scale) const
{
	float _x = x + _Scale;
	float _y = y + _Scale;

	return Vec2f(_x, _y);
}

const BFW::Math::Vec2f& BFW::Math::Vec2f::operator+= (const float _Scale)
{
	x += _Scale;
	y += _Scale;

	return *this;
}

const BFW::Math::Vec2f BFW::Math::Vec2f::operator- (const Vec2f& _Other) const
{
	float _x = x - _Other.x;
	float _y = y - _Other.y;

	return Vec2f(_x, _y);
}

const BFW::Math::Vec2f& BFW::Math::Vec2f::operator-= (const Vec2f& _Other)
{
	x -= _Other.x;
	y -= _Other.y;

	return *this;
}

const BFW::Math::Vec2f BFW::Math::Vec2f::operator- (const float _Scale) const
{
	float _x = x - _Scale;
	float _y = y - _Scale;

	return Vec2f(_x, _y);
}

const BFW::Math::Vec2f& BFW::Math::Vec2f::operator-= (const float _Scale)
{
	x -= _Scale;
	y -= _Scale;

	return *this;
}

const BFW::Math::Vec2f BFW::Math::Vec2f::operator* (const Vec2f& _Other) const
{
	float _x = x * _Other.x;
	float _y = y * _Other.y;

	return Vec2f(_x, _y);
}

const BFW::Math::Vec2f& BFW::Math::Vec2f::operator*= (const Vec2f& _Other)
{
	x *= _Other.x;
	y *= _Other.y;

	return *this;
}

const BFW::Math::Vec2f BFW::Math::Vec2f::operator* (const float _Scale) const
{
	float _x = x * _Scale;
	float _y = y * _Scale;

	return Vec2f(_x, _y);
}

const BFW::Math::Vec2f& BFW::Math::Vec2f::operator*= (const float _Scale)
{
	x *= _Scale;
	y *= _Scale;

	return *this;
}

const BFW::Math::Vec2f BFW::Math::Vec2f::operator/ (const Vec2f& _Other) const
{
	float _x = x / _Other.x;
	float _y = y / _Other.y;

	return Vec2f(_x, _y);
}

const BFW::Math::Vec2f& BFW::Math::Vec2f::operator/= (const Vec2f& _Other)
{
	x /= _Other.x;
	y /= _Other.y;

	return *this;
}

const BFW::Math::Vec2f BFW::Math::Vec2f::operator/ (const float _Scale) const
{
	float _x = x / _Scale;
	float _y = y / _Scale;

	return Vec2f(_x, _y);
}

const BFW::Math::Vec2f& BFW::Math::Vec2f::operator/= (const float _Scale)
{
	x /= _Scale;
	y /= _Scale;

	return *this;
}

const bool BFW::Math::Vec2f::operator== (const Vec2f& _Other) const
{
	return x == _Other.x && y == _Other.y;
}

const bool BFW::Math::Vec2f::operator!= (const Vec2f& _Other) const
{
	return x != _Other.x || y != _Other.y;
}

const bool BFW::Math::Vec2f::operator> (const Vec2f& _Other) const
{
	return Magnitude() > _Other.Magnitude();
}

const bool BFW::Math::Vec2f::operator>= (const Vec2f& _Other) const
{
	return Magnitude() >= _Other.Magnitude();
}

const bool BFW::Math::Vec2f::operator< (const Vec2f& _Other) const
{
	return Magnitude() < _Other.Magnitude();
}

const bool BFW::Math::Vec2f::operator<= (const Vec2f& _Other) const
{
	return Magnitude() <= _Other.Magnitude();
}

float& BFW::Math::Vec2f::operator[] (const unsigned long _Index)
{
	return Data()[_Index];
}

const float& BFW::Math::Vec2f::operator[] (const unsigned long _Index) const
{
	return Data()[_Index];
}

const BFW::Math::Vec2f& BFW::Math::Vec2f::operator= (const Vec2f& _Other)
{
	x = _Other.x;
	y = _Other.y;

	return *this;
}

const BFW::Math::Vec2f& BFW::Math::Vec2f::operator= (Vec2f&& _Other) noexcept
{
	x = _Other.x;
	y = _Other.y;

	_Other.x = 0.0f;
	_Other.y = 0.0f;

	return *this;
}



BFW::Math::Vec3f::Vec3f(const float _x, const float _y, const float _z) : x(_x), y(_y), z(_z)
{

}

BFW::Math::Vec3f::Vec3f(const Vec3f& _Other) : x(_Other.x), y(_Other.y), z(_Other.z)
{

}

BFW::Math::Vec3f::Vec3f(Vec3f&& _Other) noexcept : x(_Other.x), y(_Other.y), z(_Other.z)
{
	_Other.x = 0.0f;
	_Other.y = 0.0f;
	_Other.z = 0.0f;
}

BFW::Math::Vec3f::~Vec3f()
{

}

float* BFW::Math::Vec3f::Data()
{
	return &x;
}

const float* BFW::Math::Vec3f::Data() const
{
	return &x;
}

const float BFW::Math::Vec3f::Magnitude() const
{
	return fSqrt(x * x + y * y + z * z);
}

const float BFW::Math::Vec3f::DotProduct(const Vec3f& _Other) const
{
	return x * _Other.x + y * _Other.y + z * _Other.z;
}

const BFW::Math::Vec3f BFW::Math::Vec3f::CrossProduct(const Vec3f& _Other) const
{
	float _x = y * _Other.z - z * _Other.y;
	float _y = z * _Other.x - x * _Other.z;
	float _z = x * _Other.y - y * _Other.x;
	return Vec3f(_x, _y, _z);
}

const float BFW::Math::Vec3f::GetAngle(const Vec3f& _Center, const Vec3f& _Other) const
{
	Vec3f _V = *this - _Center;
	return fPeriod(fACos(_V.DotProduct(_Other) / (_V.Magnitude() * _Other.Magnitude())), 0.0f, fPi * 2.0f);
}

const BFW::Math::Vec3f BFW::Math::Vec3f::Rotated(const float _Angle, const Vec3f& _Center, const Vec3f& _U) const
{
	float _NewX = x - _Center.x;
	float _NewY = y - _Center.y;
	float _NewZ = z - _Center.z;
	float _Sin = fSin(_Angle);
	float _Cos = fCos(_Angle);

	float _x = _NewX * (_Cos + _U.x * _U.x * (1.0f - _Cos)) + _NewY * (_U.x * _U.y * (1.0f - _Cos) - _U.z * _Sin) + _NewZ * (_U.x * _U.z * (1.0f - _Cos) + _U.y * _Sin) + _Center.x;
	float _y = _NewX * (_U.y * _U.x * (1.0f - _Cos) + _U.z * _Sin) + _NewY * (_Cos + _U.y * _U.y * (1.0f - _Cos)) + _NewZ * (_U.y * _U.z * (1.0f - _Cos) - _U.x * _Sin) + _Center.y;
	float _z = _NewX * (_U.z * _U.x * (1.0f - _Cos) - _U.y * _Sin) + _NewY * (_U.z * _U.y * (1.0f - _Cos) + _U.x * _Sin) + _NewZ * (_Cos + _U.z * _U.z * (1.0f - _Cos)) + _Center.z;

	return Vec3f(_x, _y, _z);
}

const BFW::Math::Vec3f& BFW::Math::Vec3f::Rotate(const float _Angle, const Vec3f& _Center, const Vec3f& _U)
{
	float _NewX = x - _Center.x;
	float _NewY = y - _Center.y;
	float _NewZ = z - _Center.z;
	float _Sin = fSin(_Angle);
	float _Cos = fCos(_Angle);

	x = _NewX * (_Cos + _U.x * _U.x * (1.0f - _Cos)) + _NewY * (_U.x * _U.y * (1.0f - _Cos) - _U.z * _Sin) + _NewZ * (_U.x * _U.z * (1.0f - _Cos) + _U.y * _Sin) + _Center.x;
	y = _NewX * (_U.y * _U.x * (1.0f - _Cos) + _U.z * _Sin) + _NewY * (_Cos + _U.y * _U.y * (1.0f - _Cos)) + _NewZ * (_U.y * _U.z * (1.0f - _Cos) - _U.x * _Sin) + _Center.y;
	z = _NewX * (_U.z * _U.x * (1.0f - _Cos) - _U.y * _Sin) + _NewY * (_U.z * _U.y * (1.0f - _Cos) + _U.x * _Sin) + _NewZ * (_Cos + _U.z * _U.z * (1.0f - _Cos)) + _Center.z;

	return *this;
}

const BFW::Math::Vec3f BFW::Math::Vec3f::Flipped(const Vec3f& _U, const Vec3f& _Center) const
{
	float _NewX = x - _Center.x;
	float _NewY = y - _Center.y;
	float _NewZ = z - _Center.z;

	float _x = _NewX * (1.0f - 2.0f * _U.x * _U.x) + _NewY * (-2.0f * _U.x * _U.y) + _NewZ * (-2.0f * _U.x * _U.z) + _Center.x;
	float _y = _NewX * (-2.0f * _U.x * _U.y) + _NewY * (1.0f - 2.0f * _U.y * _U.y) + _NewZ * (-2.0f * _U.y * _U.z) + _Center.y;
	float _z = _NewX * (-2.0f * _U.x * _U.z) + _NewY * (-2.0f * _U.y * _U.z) + _NewZ * (1.0f - 2.0f * _U.z * _U.z) + _Center.z;

	return Vec3f(_x, _y, _z);
}

const BFW::Math::Vec3f& BFW::Math::Vec3f::Flip(const Vec3f& _U, const Vec3f& _Center)
{
	float _NewX = x - _Center.x;
	float _NewY = y - _Center.y;
	float _NewZ = z - _Center.z;

	x = _NewX * (1.0f - 2.0f * _U.x * _U.x) + _NewY * (-2.0f * _U.x * _U.y) + _NewZ * (-2.0f * _U.x * _U.z) + _Center.x;
	y = _NewX * (-2.0f * _U.x * _U.y) + _NewY * (1.0f - 2.0f * _U.y * _U.y) + _NewZ * (-2.0f * _U.y * _U.z) + _Center.y;
	z = _NewX * (-2.0f * _U.x * _U.z) + _NewY * (-2.0f * _U.y * _U.z) + _NewZ * (1.0f - 2.0f * _U.z * _U.z) + _Center.z;

	return *this;
}

const BFW::Math::Vec3f& BFW::Math::Vec3f::operator+ () const
{
	return *this;
}

const BFW::Math::Vec3f BFW::Math::Vec3f::operator- () const
{
	return Vec3f(-x, -y, -z);
}

const BFW::Math::Vec3f BFW::Math::Vec3f::operator+ (const Vec3f& _Other) const
{
	float _x = x + _Other.x;
	float _y = y + _Other.y;
	float _z = z + _Other.z;

	return Vec3f(_x, _y, _z);
}

const BFW::Math::Vec3f& BFW::Math::Vec3f::operator+= (const Vec3f& _Other)
{
	x += _Other.x;
	y += _Other.y;
	z += _Other.z;

	return *this;
}

const BFW::Math::Vec3f BFW::Math::Vec3f::operator+ (const float _Scale) const
{
	float _x = x + _Scale;
	float _y = y + _Scale;
	float _z = z + _Scale;

	return Vec3f(_x, _y, _z);
}

const BFW::Math::Vec3f& BFW::Math::Vec3f::operator+= (const float _Scale)
{
	x += _Scale;
	y += _Scale;
	z += _Scale;

	return *this;
}

const BFW::Math::Vec3f BFW::Math::Vec3f::operator- (const Vec3f& _Other) const
{
	float _x = x - _Other.x;
	float _y = y - _Other.y;
	float _z = z - _Other.z;

	return Vec3f(_x, _y, _z);
}

const BFW::Math::Vec3f& BFW::Math::Vec3f::operator-= (const Vec3f& _Other)
{
	x -= _Other.x;
	y -= _Other.y;
	z -= _Other.z;

	return *this;
}

const BFW::Math::Vec3f BFW::Math::Vec3f::operator- (const float _Scale) const
{
	float _x = x - _Scale;
	float _y = y - _Scale;
	float _z = z - _Scale;

	return Vec3f(_x, _y, _z);
}

const BFW::Math::Vec3f& BFW::Math::Vec3f::operator-= (const float _Scale)
{
	x -= _Scale;
	y -= _Scale;
	z -= _Scale;

	return *this;
}

const BFW::Math::Vec3f BFW::Math::Vec3f::operator* (const Vec3f& _Other) const
{
	float _x = x * _Other.x;
	float _y = y * _Other.y;
	float _z = z * _Other.z;

	return Vec3f(_x, _y, _z);
}

const BFW::Math::Vec3f& BFW::Math::Vec3f::operator*= (const Vec3f& _Other)
{
	x *= _Other.x;
	y *= _Other.y;
	z *= _Other.z;

	return *this;
}

const BFW::Math::Vec3f BFW::Math::Vec3f::operator* (const float _Scale) const
{
	float _x = x * _Scale;
	float _y = y * _Scale;
	float _z = z * _Scale;

	return Vec3f(_x, _y, _z);
}

const BFW::Math::Vec3f& BFW::Math::Vec3f::operator*= (const float _Scale)
{
	x *= _Scale;
	y *= _Scale;
	z *= _Scale;

	return *this;
}

const BFW::Math::Vec3f BFW::Math::Vec3f::operator/ (const Vec3f& _Other) const
{
	float _x = x / _Other.x;
	float _y = y / _Other.y;
	float _z = z / _Other.z;

	return Vec3f(_x, _y, _z);
}

const BFW::Math::Vec3f& BFW::Math::Vec3f::operator/= (const Vec3f& _Other)
{
	x /= _Other.x;
	y /= _Other.y;
	z /= _Other.z;

	return *this;
}

const BFW::Math::Vec3f BFW::Math::Vec3f::operator/ (const float _Scale) const
{
	float _x = x / _Scale;
	float _y = y / _Scale;
	float _z = z / _Scale;

	return Vec3f(_x, _y, _z);
}

const BFW::Math::Vec3f& BFW::Math::Vec3f::operator/= (const float _Scale)
{
	x /= _Scale;
	y /= _Scale;
	z /= _Scale;

	return *this;
}

const bool BFW::Math::Vec3f::operator== (const Vec3f& _Other) const
{
	return x == _Other.x && y == _Other.y && z == _Other.z;
}

const bool BFW::Math::Vec3f::operator!= (const Vec3f& _Other) const
{
	return x != _Other.x || y != _Other.y || z != _Other.z;
}

const bool BFW::Math::Vec3f::operator> (const Vec3f& _Other) const
{
	return Magnitude() > _Other.Magnitude();
}

const bool BFW::Math::Vec3f::operator>= (const Vec3f& _Other) const
{
	return Magnitude() >= _Other.Magnitude();
}

const bool BFW::Math::Vec3f::operator< (const Vec3f& _Other) const
{
	return Magnitude() < _Other.Magnitude();
}

const bool BFW::Math::Vec3f::operator<= (const Vec3f& _Other) const
{
	return Magnitude() <= _Other.Magnitude();
}

float& BFW::Math::Vec3f::operator[] (const unsigned long _Index)
{
	return Data()[_Index];
}

const float& BFW::Math::Vec3f::operator[] (const unsigned long _Index) const
{
	return Data()[_Index];
}

const BFW::Math::Vec3f& BFW::Math::Vec3f::operator= (const Vec3f& _Other)
{
	x = _Other.x;
	y = _Other.y;
	z = _Other.z;

	return *this;
}

const BFW::Math::Vec3f& BFW::Math::Vec3f::operator= (Vec3f&& _Other) noexcept
{
	x = _Other.x;
	y = _Other.y;
	z = _Other.z;

	_Other.x = 0.0f;
	_Other.y = 0.0f;
	_Other.z = 0.0f;

	return *this;
}



BFW::Math::Vec4f::Vec4f(const float _x, const float _y, const float _z, const float _w) : x(_x), y(_y), z(_z), w(_w)
{

}

BFW::Math::Vec4f::Vec4f(const Vec4f& _Other) : x(_Other.x), y(_Other.y), z(_Other.z), w(_Other.w)
{

}

BFW::Math::Vec4f::Vec4f(Vec4f&& _Other) noexcept : x(_Other.x), y(_Other.y), z(_Other.z), w(_Other.w)
{
	_Other.x = 0.0f;
	_Other.y = 0.0f;
	_Other.z = 0.0f;
	_Other.w = 0.0f;
}

BFW::Math::Vec4f::~Vec4f()
{

}

float* BFW::Math::Vec4f::Data()
{
	return &x;
}

const float* BFW::Math::Vec4f::Data() const
{
	return &x;
}

const float BFW::Math::Vec4f::Magnitude() const
{
	return fSqrt(x * x + y * y + z * z + w * w);
}

const float BFW::Math::Vec4f::DotProduct(const Vec4f& _Other) const
{
	return x * _Other.x + y * _Other.y + z * _Other.z + w * _Other.w;
}

const BFW::Math::Vec4f BFW::Math::Vec4f::CrossProduct(const Vec4f& _Other) const
{
	float _x = y * _Other.z - z * _Other.y;
	float _y = z * _Other.x - x * _Other.z;
	float _z = x * _Other.y - y * _Other.x;
	return Vec4f(_x, _y, _z, w);
}

const float BFW::Math::Vec4f::GetAngle(const Vec4f& _Center, const Vec4f& _Other) const
{
	Vec4f _V = *this - _Center;
	return fPeriod(fACos(_V.DotProduct(_Other) / (_V.Magnitude() * _Other.Magnitude())), 0.0f, fPi * 2.0f);
}

const BFW::Math::Vec4f BFW::Math::Vec4f::Rotated(const float _Angle, const Vec4f& _Center, const Vec4f& _U) const
{
	float _NewX = x - _Center.x;
	float _NewY = y - _Center.y;
	float _NewZ = z - _Center.z;
	float _Sin = fSin(_Angle);
	float _Cos = fCos(_Angle);

	float _x = _NewX * (_Cos + _U.x * _U.x * (1.0f - _Cos)) + _NewY * (_U.x * _U.y * (1.0f - _Cos) - _U.z * _Sin) + _NewZ * (_U.x * _U.z * (1.0f - _Cos) + _U.y * _Sin) + _Center.x;
	float _y = _NewX * (_U.y * _U.x * (1.0f - _Cos) + _U.z * _Sin) + _NewY * (_Cos + _U.y * _U.y * (1.0f - _Cos)) + _NewZ * (_U.y * _U.z * (1.0f - _Cos) - _U.x * _Sin) + _Center.y;
	float _z = _NewX * (_U.z * _U.x * (1.0f - _Cos) - _U.y * _Sin) + _NewY * (_U.z * _U.y * (1.0f - _Cos) + _U.x * _Sin) + _NewZ * (_Cos + _U.z * _U.z * (1.0f - _Cos)) + _Center.z;

	return Vec4f(_x, _y, _z, w);
}

const BFW::Math::Vec4f& BFW::Math::Vec4f::Rotate(const float _Angle, const Vec4f& _Center, const Vec4f& _U)
{
	float _NewX = x - _Center.x;
	float _NewY = y - _Center.y;
	float _NewZ = z - _Center.z;
	float _Sin = fSin(_Angle);
	float _Cos = fCos(_Angle);

	x = _NewX * (_Cos + _U.x * _U.x * (1.0f - _Cos)) + _NewY * (_U.x * _U.y * (1.0f - _Cos) - _U.z * _Sin) + _NewZ * (_U.x * _U.z * (1.0f - _Cos) + _U.y * _Sin) + _Center.x;
	y = _NewX * (_U.y * _U.x * (1.0f - _Cos) + _U.z * _Sin) + _NewY * (_Cos + _U.y * _U.y * (1.0f - _Cos)) + _NewZ * (_U.y * _U.z * (1.0f - _Cos) - _U.x * _Sin) + _Center.y;
	z = _NewX * (_U.z * _U.x * (1.0f - _Cos) - _U.y * _Sin) + _NewY * (_U.z * _U.y * (1.0f - _Cos) + _U.x * _Sin) + _NewZ * (_Cos + _U.z * _U.z * (1.0f - _Cos)) + _Center.z;

	return *this;
}

const BFW::Math::Vec4f BFW::Math::Vec4f::Flipped(const Vec4f& _U, const Vec4f& _Center) const
{
	float _NewX = x - _Center.x;
	float _NewY = y - _Center.y;
	float _NewZ = z - _Center.z;

	float _x = _NewX * (1.0f - 2.0f * _U.x * _U.x) + _NewY * (-2.0f * _U.x * _U.y) + _NewZ * (-2.0f * _U.x * _U.z) + _Center.x;
	float _y = _NewX * (-2.0f * _U.x * _U.y) + _NewY * (1.0f - 2.0f * _U.y * _U.y) + _NewZ * (-2.0f * _U.y * _U.z) + _Center.y;
	float _z = _NewX * (-2.0f * _U.x * _U.z) + _NewY * (-2.0f * _U.y * _U.z) + _NewZ * (1.0f - 2.0f * _U.z * _U.z) + _Center.z;

	return Vec4f(_x, _y, _z, w);
}

const BFW::Math::Vec4f& BFW::Math::Vec4f::Flip(const Vec4f& _U, const Vec4f& _Center)
{
	float _NewX = x - _Center.x;
	float _NewY = y - _Center.y;
	float _NewZ = z - _Center.z;

	x = _NewX * (1.0f - 2.0f * _U.x * _U.x) + _NewY * (-2.0f * _U.x * _U.y) + _NewZ * (-2.0f * _U.x * _U.z) + _Center.x;
	y = _NewX * (-2.0f * _U.x * _U.y) + _NewY * (1.0f - 2.0f * _U.y * _U.y) + _NewZ * (-2.0f * _U.y * _U.z) + _Center.y;
	z = _NewX * (-2.0f * _U.x * _U.z) + _NewY * (-2.0f * _U.y * _U.z) + _NewZ * (1.0f - 2.0f * _U.z * _U.z) + _Center.z;

	return *this;
}

const BFW::Math::Vec4f& BFW::Math::Vec4f::operator+ () const
{
	return *this;
}

const BFW::Math::Vec4f BFW::Math::Vec4f::operator- () const
{
	return Vec4f(-x, -y, -z, -w);
}

const BFW::Math::Vec4f BFW::Math::Vec4f::operator+ (const Vec4f& _Other) const
{
	float _x = x + _Other.x;
	float _y = y + _Other.y;
	float _z = z + _Other.z;
	float _w = w + _Other.w;

	return Vec4f(_x, _y, _z, _w);
}

const BFW::Math::Vec4f& BFW::Math::Vec4f::operator+= (const Vec4f& _Other)
{
	x += _Other.x;
	y += _Other.y;
	z += _Other.z;
	w += _Other.w;

	return *this;
}

const BFW::Math::Vec4f BFW::Math::Vec4f::operator+ (const float _Scale) const
{
	float _x = x + _Scale;
	float _y = y + _Scale;
	float _z = z + _Scale;
	float _w = w + _Scale;

	return Vec4f(_x, _y, _z, _w);
}

const BFW::Math::Vec4f& BFW::Math::Vec4f::operator+= (const float _Scale)
{
	x += _Scale;
	y += _Scale;
	z += _Scale;
	w += _Scale;

	return *this;
}

const BFW::Math::Vec4f BFW::Math::Vec4f::operator- (const Vec4f& _Other) const
{
	float _x = x - _Other.x;
	float _y = y - _Other.y;
	float _z = z - _Other.z;
	float _w = w - _Other.w;

	return Vec4f(_x, _y, _z, _w);
}

const BFW::Math::Vec4f& BFW::Math::Vec4f::operator-= (const Vec4f& _Other)
{
	x -= _Other.x;
	y -= _Other.y;
	z -= _Other.z;
	w -= _Other.w;

	return *this;
}

const BFW::Math::Vec4f BFW::Math::Vec4f::operator- (const float _Scale) const
{
	float _x = x - _Scale;
	float _y = y - _Scale;
	float _z = z - _Scale;
	float _w = w - _Scale;

	return Vec4f(_x, _y, _z, _w);
}

const BFW::Math::Vec4f& BFW::Math::Vec4f::operator-= (const float _Scale)
{
	x -= _Scale;
	y -= _Scale;
	z -= _Scale;
	w -= _Scale;

	return *this;
}

const BFW::Math::Vec4f BFW::Math::Vec4f::operator* (const Vec4f& _Other) const
{
	float _x = x * _Other.x;
	float _y = y * _Other.y;
	float _z = z * _Other.z;
	float _w = w * _Other.w;

	return Vec4f(_x, _y, _z, _w);
}

const BFW::Math::Vec4f& BFW::Math::Vec4f::operator*= (const Vec4f& _Other)
{
	x *= _Other.x;
	y *= _Other.y;
	z *= _Other.z;
	w *= _Other.w;

	return *this;
}

const BFW::Math::Vec4f BFW::Math::Vec4f::operator* (const float _Scale) const
{
	float _x = x * _Scale;
	float _y = y * _Scale;
	float _z = z * _Scale;
	float _w = w * _Scale;

	return Vec4f(_x, _y, _z, _w);
}

const BFW::Math::Vec4f& BFW::Math::Vec4f::operator*= (const float _Scale)
{
	x *= _Scale;
	y *= _Scale;
	z *= _Scale;
	w *= _Scale;

	return *this;
}

const BFW::Math::Vec4f BFW::Math::Vec4f::operator/ (const Vec4f& _Other) const
{
	float _x = x / _Other.x;
	float _y = y / _Other.y;
	float _z = z / _Other.z;
	float _w = w / _Other.w;

	return Vec4f(_x, _y, _z, _w);
}

const BFW::Math::Vec4f& BFW::Math::Vec4f::operator/= (const Vec4f& _Other)
{
	x /= _Other.x;
	y /= _Other.y;
	z /= _Other.z;
	w /= _Other.w;

	return *this;
}

const BFW::Math::Vec4f BFW::Math::Vec4f::operator/ (const float _Scale) const
{
	float _x = x / _Scale;
	float _y = y / _Scale;
	float _z = z / _Scale;
	float _w = w / _Scale;

	return Vec4f(_x, _y, _z, _w);
}

const BFW::Math::Vec4f& BFW::Math::Vec4f::operator/= (const float _Scale)
{
	x /= _Scale;
	y /= _Scale;
	z /= _Scale;
	w /= _Scale;

	return *this;
}

const bool BFW::Math::Vec4f::operator== (const Vec4f& _Other) const
{
	return x == _Other.x && y == _Other.y && z == _Other.z && w == _Other.w;
}

const bool BFW::Math::Vec4f::operator!= (const Vec4f& _Other) const
{
	return x != _Other.x || y != _Other.y || z != _Other.z || w != _Other.w;
}

const bool BFW::Math::Vec4f::operator> (const Vec4f& _Other) const
{
	return Magnitude() > _Other.Magnitude();
}

const bool BFW::Math::Vec4f::operator>= (const Vec4f& _Other) const
{
	return Magnitude() >= _Other.Magnitude();
}

const bool BFW::Math::Vec4f::operator< (const Vec4f& _Other) const
{
	return Magnitude() < _Other.Magnitude();
}

const bool BFW::Math::Vec4f::operator<= (const Vec4f& _Other) const
{
	return Magnitude() <= _Other.Magnitude();
}

float& BFW::Math::Vec4f::operator[] (const unsigned long _Index)
{
	return Data()[_Index];
}

const float& BFW::Math::Vec4f::operator[] (const unsigned long _Index) const
{
	return Data()[_Index];
}

const BFW::Math::Vec4f& BFW::Math::Vec4f::operator= (const Vec4f& _Other)
{
	x = _Other.x;
	y = _Other.y;
	z = _Other.z;
	w = _Other.w;

	return *this;
}

const BFW::Math::Vec4f& BFW::Math::Vec4f::operator= (Vec4f&& _Other) noexcept
{
	x = _Other.x;
	y = _Other.y;
	z = _Other.z;
	w = _Other.w;

	_Other.x = 0.0f;
	_Other.y = 0.0f;
	_Other.z = 0.0f;
	_Other.w = 0.0f;

	return *this;
}



BFW::Math::Vec2d::Vec2d(const double _x, const double _y) : x(_x), y(_y)
{

}

BFW::Math::Vec2d::Vec2d(const Vec2d& _Other) : x(_Other.x), y(_Other.y)
{

}

BFW::Math::Vec2d::Vec2d(Vec2d&& _Other) noexcept : x(_Other.x), y(_Other.y)
{
	_Other.x = 0.0;
	_Other.y = 0.0;
}

BFW::Math::Vec2d::~Vec2d()
{

}

double* BFW::Math::Vec2d::Data()
{
	return &x;
}

const double* BFW::Math::Vec2d::Data() const
{
	return &x;
}

const double BFW::Math::Vec2d::Magnitude() const
{
	return dSqrt(x * x + y * y);
}

const double BFW::Math::Vec2d::DotProduct(const Vec2d& _Other) const
{
	return x * _Other.x + y * _Other.y;
}

const double BFW::Math::Vec2d::GetAngle(const Vec2d& _Center, const Vec2d& _Other) const
{
	Vec2d _V = *this - _Center;
	return dPeriod(dACos(_V.DotProduct(_Other) / (_V.Magnitude() * _Other.Magnitude())), 0.0, dPi * 2.0);
}

const BFW::Math::Vec2d BFW::Math::Vec2d::Rotated(const double _Angle, const Vec2d& _Center) const
{
	double _NewX = x - _Center.x;
	double _NewY = y - _Center.y;
	double _Sin = dSin(_Angle);
	double _Cos = dCos(_Angle);

	double _x = _Cos * _NewX - _Sin * _NewY + _Center.x;
	double _y = _Sin * _NewX + _Cos * _NewY + _Center.y;

	return Vec2d(_x, _y);
}

const BFW::Math::Vec2d& BFW::Math::Vec2d::Rotate(const double _Angle, const Vec2d& _Center)
{
	double _NewX = x - _Center.x;
	double _NewY = y - _Center.y;
	double _Sin = dSin(_Angle);
	double _Cos = dCos(_Angle);

	x = _Cos * _NewX - _Sin * _NewY + _Center.x;
	y = _Sin * _NewX + _Cos * _NewY + _Center.y;

	return *this;
}

const BFW::Math::Vec2d BFW::Math::Vec2d::Flipped(const Vec2d& _U, const Vec2d& _Center) const
{
	double _Angle = _U.GetAngle() * 2.0;
	double _NewX = x - _Center.x;
	double _NewY = y - _Center.y;
	double _Sin = dSin(_Angle);
	double _Cos = dCos(_Angle);

	double _x = _Cos * _NewX + _Sin * _NewY + _Center.x;
	double _y = _Sin * _NewX - _Cos * _NewY + _Center.y;

	return Vec2d(_x, _y);
}

const BFW::Math::Vec2d& BFW::Math::Vec2d::Flip(const Vec2d& _U, const Vec2d& _Center)
{
	double _Angle = _U.GetAngle() * 2.0;
	double _NewX = x - _Center.x;
	double _NewY = y - _Center.y;
	double _Sin = dSin(_Angle);
	double _Cos = dCos(_Angle);

	x = _Cos * _NewX + _Sin * _NewY + _Center.x;
	y = _Sin * _NewX - _Cos * _NewY + _Center.y;

	return *this;
}

const BFW::Math::Vec2d& BFW::Math::Vec2d::operator+ () const
{
	return *this;
}

const BFW::Math::Vec2d BFW::Math::Vec2d::operator- () const
{
	return Vec2d(-x, -y);
}

const BFW::Math::Vec2d BFW::Math::Vec2d::operator+ (const Vec2d& _Other) const
{
	double _x = x + _Other.x;
	double _y = y + _Other.y;

	return Vec2d(_x, _y);
}

const BFW::Math::Vec2d& BFW::Math::Vec2d::operator+= (const Vec2d& _Other)
{
	x += _Other.x;
	y += _Other.y;

	return *this;
}

const BFW::Math::Vec2d BFW::Math::Vec2d::operator+ (const double _Scale) const
{
	double _x = x + _Scale;
	double _y = y + _Scale;

	return Vec2d(_x, _y);
}

const BFW::Math::Vec2d& BFW::Math::Vec2d::operator+= (const double _Scale)
{
	x += _Scale;
	y += _Scale;

	return *this;
}

const BFW::Math::Vec2d BFW::Math::Vec2d::operator- (const Vec2d& _Other) const
{
	double _x = x - _Other.x;
	double _y = y - _Other.y;

	return Vec2d(_x, _y);
}

const BFW::Math::Vec2d& BFW::Math::Vec2d::operator-= (const Vec2d& _Other)
{
	x -= _Other.x;
	y -= _Other.y;

	return *this;
}

const BFW::Math::Vec2d BFW::Math::Vec2d::operator- (const double _Scale) const
{
	double _x = x - _Scale;
	double _y = y - _Scale;

	return Vec2d(_x, _y);
}

const BFW::Math::Vec2d& BFW::Math::Vec2d::operator-= (const double _Scale)
{
	x -= _Scale;
	y -= _Scale;

	return *this;
}

const BFW::Math::Vec2d BFW::Math::Vec2d::operator* (const Vec2d& _Other) const
{
	double _x = x * _Other.x;
	double _y = y * _Other.y;

	return Vec2d(_x, _y);
}

const BFW::Math::Vec2d& BFW::Math::Vec2d::operator*= (const Vec2d& _Other)
{
	x *= _Other.x;
	y *= _Other.y;

	return *this;
}

const BFW::Math::Vec2d BFW::Math::Vec2d::operator* (const double _Scale) const
{
	double _x = x * _Scale;
	double _y = y * _Scale;

	return Vec2d(_x, _y);
}

const BFW::Math::Vec2d& BFW::Math::Vec2d::operator*= (const double _Scale)
{
	x *= _Scale;
	y *= _Scale;

	return *this;
}

const BFW::Math::Vec2d BFW::Math::Vec2d::operator/ (const Vec2d& _Other) const
{
	double _x = x / _Other.x;
	double _y = y / _Other.y;

	return Vec2d(_x, _y);
}

const BFW::Math::Vec2d& BFW::Math::Vec2d::operator/= (const Vec2d& _Other)
{
	x /= _Other.x;
	y /= _Other.y;

	return *this;
}

const BFW::Math::Vec2d BFW::Math::Vec2d::operator/ (const double _Scale) const
{
	double _x = x / _Scale;
	double _y = y / _Scale;

	return Vec2d(_x, _y);
}

const BFW::Math::Vec2d& BFW::Math::Vec2d::operator/= (const double _Scale)
{
	x /= _Scale;
	y /= _Scale;

	return *this;
}

const bool BFW::Math::Vec2d::operator== (const Vec2d& _Other) const
{
	return x == _Other.x && y == _Other.y;
}

const bool BFW::Math::Vec2d::operator!= (const Vec2d& _Other) const
{
	return x != _Other.x || y != _Other.y;
}

const bool BFW::Math::Vec2d::operator> (const Vec2d& _Other) const
{
	return Magnitude() > _Other.Magnitude();
}

const bool BFW::Math::Vec2d::operator>= (const Vec2d& _Other) const
{
	return Magnitude() >= _Other.Magnitude();
}

const bool BFW::Math::Vec2d::operator< (const Vec2d& _Other) const
{
	return Magnitude() < _Other.Magnitude();
}

const bool BFW::Math::Vec2d::operator<= (const Vec2d& _Other) const
{
	return Magnitude() <= _Other.Magnitude();
}

double& BFW::Math::Vec2d::operator[] (const unsigned long _Index)
{
	return Data()[_Index];
}

const double& BFW::Math::Vec2d::operator[] (const unsigned long _Index) const
{
	return Data()[_Index];
}

const BFW::Math::Vec2d& BFW::Math::Vec2d::operator= (const Vec2d& _Other)
{
	x = _Other.x;
	y = _Other.y;

	return *this;
}

const BFW::Math::Vec2d& BFW::Math::Vec2d::operator= (Vec2d&& _Other) noexcept
{
	x = _Other.x;
	y = _Other.y;

	_Other.x = 0.0;
	_Other.y = 0.0;

	return *this;
}



BFW::Math::Vec3d::Vec3d(const double _x, const double _y, const double _z) : x(_x), y(_y), z(_z)
{

}

BFW::Math::Vec3d::Vec3d(const Vec3d& _Other) : x(_Other.x), y(_Other.y), z(_Other.z)
{

}

BFW::Math::Vec3d::Vec3d(Vec3d&& _Other) noexcept : x(_Other.x), y(_Other.y), z(_Other.z)
{
	_Other.x = 0.0;
	_Other.y = 0.0;
	_Other.z = 0.0;
}

BFW::Math::Vec3d::~Vec3d()
{

}

double* BFW::Math::Vec3d::Data()
{
	return &x;
}

const double* BFW::Math::Vec3d::Data() const
{
	return &x;
}

const double BFW::Math::Vec3d::Magnitude() const
{
	return dSqrt(x * x + y * y + z * z);
}

const double BFW::Math::Vec3d::DotProduct(const Vec3d& _Other) const
{
	return x * _Other.x + y * _Other.y + z * _Other.z;
}

const BFW::Math::Vec3d BFW::Math::Vec3d::CrossProduct(const Vec3d& _Other) const
{
	double _x = y * _Other.z - z * _Other.y;
	double _y = z * _Other.x - x * _Other.z;
	double _z = x * _Other.y - y * _Other.x;
	return Vec3d(_x, _y, _z);
}

const double BFW::Math::Vec3d::GetAngle(const Vec3d& _Center, const Vec3d& _Other) const
{
	Vec3d _V = *this - _Center;
	return dPeriod(dACos(_V.DotProduct(_Other) / (_V.Magnitude() * _Other.Magnitude())), 0.0, dPi * 2.0);
}

const BFW::Math::Vec3d BFW::Math::Vec3d::Rotated(const double _Angle, const Vec3d& _Center, const Vec3d& _U) const
{
	double _NewX = x - _Center.x;
	double _NewY = y - _Center.y;
	double _NewZ = z - _Center.z;
	double _Sin = dSin(_Angle);
	double _Cos = dCos(_Angle);

	double _x = _NewX * (_Cos + _U.x * _U.x * (1.0 - _Cos)) + _NewY * (_U.x * _U.y * (1.0 - _Cos) - _U.z * _Sin) + _NewZ * (_U.x * _U.z * (1.0 - _Cos) + _U.y * _Sin) + _Center.x;
	double _y = _NewX * (_U.y * _U.x * (1.0 - _Cos) + _U.z * _Sin) + _NewY * (_Cos + _U.y * _U.y * (1.0 - _Cos)) + _NewZ * (_U.y * _U.z * (1.0 - _Cos) - _U.x * _Sin) + _Center.y;
	double _z = _NewX * (_U.z * _U.x * (1.0 - _Cos) - _U.y * _Sin) + _NewY * (_U.z * _U.y * (1.0 - _Cos) + _U.x * _Sin) + _NewZ * (_Cos + _U.z * _U.z * (1.0 - _Cos)) + _Center.z;

	return Vec3d(_x, _y, _z);
}

const BFW::Math::Vec3d& BFW::Math::Vec3d::Rotate(const double _Angle, const Vec3d& _Center, const Vec3d& _U)
{
	double _NewX = x - _Center.x;
	double _NewY = y - _Center.y;
	double _NewZ = z - _Center.z;
	double _Sin = dSin(_Angle);
	double _Cos = dCos(_Angle);

	x = _NewX * (_Cos + _U.x * _U.x * (1.0 - _Cos)) + _NewY * (_U.x * _U.y * (1.0 - _Cos) - _U.z * _Sin) + _NewZ * (_U.x * _U.z * (1.0 - _Cos) + _U.y * _Sin) + _Center.x;
	y = _NewX * (_U.y * _U.x * (1.0 - _Cos) + _U.z * _Sin) + _NewY * (_Cos + _U.y * _U.y * (1.0 - _Cos)) + _NewZ * (_U.y * _U.z * (1.0 - _Cos) - _U.x * _Sin) + _Center.y;
	z = _NewX * (_U.z * _U.x * (1.0 - _Cos) - _U.y * _Sin) + _NewY * (_U.z * _U.y * (1.0 - _Cos) + _U.x * _Sin) + _NewZ * (_Cos + _U.z * _U.z * (1.0 - _Cos)) + _Center.z;

	return *this;
}

const BFW::Math::Vec3d BFW::Math::Vec3d::Flipped(const Vec3d& _U, const Vec3d& _Center) const
{
	double _NewX = x - _Center.x;
	double _NewY = y - _Center.y;
	double _NewZ = z - _Center.z;

	double _x = _NewX * (1.0 - 2.0 * _U.x * _U.x) + _NewY * (-2.0 * _U.x * _U.y) + _NewZ * (-2.0 * _U.x * _U.z) + _Center.x;
	double _y = _NewX * (-2.0 * _U.x * _U.y) + _NewY * (1.0 - 2.0 * _U.y * _U.y) + _NewZ * (-2.0 * _U.y * _U.z) + _Center.y;
	double _z = _NewX * (-2.0 * _U.x * _U.z) + _NewY * (-2.0 * _U.y * _U.z) + _NewZ * (1.0 - 2.0 * _U.z * _U.z) + _Center.z;

	return Vec3d(_x, _y, _z);
}

const BFW::Math::Vec3d& BFW::Math::Vec3d::Flip(const Vec3d& _U, const Vec3d& _Center)
{
	double _NewX = x - _Center.x;
	double _NewY = y - _Center.y;
	double _NewZ = z - _Center.z;

	x = _NewX * (1.0 - 2.0 * _U.x * _U.x) + _NewY * (-2.0 * _U.x * _U.y) + _NewZ * (-2.0 * _U.x * _U.z) + _Center.x;
	y = _NewX * (-2.0 * _U.x * _U.y) + _NewY * (1.0 - 2.0 * _U.y * _U.y) + _NewZ * (-2.0 * _U.y * _U.z) + _Center.y;
	z = _NewX * (-2.0 * _U.x * _U.z) + _NewY * (-2.0 * _U.y * _U.z) + _NewZ * (1.0 - 2.0 * _U.z * _U.z) + _Center.z;

	return *this;
}

const BFW::Math::Vec3d& BFW::Math::Vec3d::operator+ () const
{
	return *this;
}

const BFW::Math::Vec3d BFW::Math::Vec3d::operator- () const
{
	return Vec3d(-x, -y, -z);
}

const BFW::Math::Vec3d BFW::Math::Vec3d::operator+ (const Vec3d& _Other) const
{
	double _x = x + _Other.x;
	double _y = y + _Other.y;
	double _z = z + _Other.z;

	return Vec3d(_x, _y, _z);
}

const BFW::Math::Vec3d& BFW::Math::Vec3d::operator+= (const Vec3d& _Other)
{
	x += _Other.x;
	y += _Other.y;
	z += _Other.z;

	return *this;
}

const BFW::Math::Vec3d BFW::Math::Vec3d::operator+ (const double _Scale) const
{
	double _x = x + _Scale;
	double _y = y + _Scale;
	double _z = z + _Scale;

	return Vec3d(_x, _y, _z);
}

const BFW::Math::Vec3d& BFW::Math::Vec3d::operator+= (const double _Scale)
{
	x += _Scale;
	y += _Scale;
	z += _Scale;

	return *this;
}

const BFW::Math::Vec3d BFW::Math::Vec3d::operator- (const Vec3d& _Other) const
{
	double _x = x - _Other.x;
	double _y = y - _Other.y;
	double _z = z - _Other.z;

	return Vec3d(_x, _y, _z);
}

const BFW::Math::Vec3d& BFW::Math::Vec3d::operator-= (const Vec3d& _Other)
{
	x -= _Other.x;
	y -= _Other.y;
	z -= _Other.z;

	return *this;
}

const BFW::Math::Vec3d BFW::Math::Vec3d::operator- (const double _Scale) const
{
	double _x = x - _Scale;
	double _y = y - _Scale;
	double _z = z - _Scale;

	return Vec3d(_x, _y, _z);
}

const BFW::Math::Vec3d& BFW::Math::Vec3d::operator-= (const double _Scale)
{
	x -= _Scale;
	y -= _Scale;
	z -= _Scale;

	return *this;
}

const BFW::Math::Vec3d BFW::Math::Vec3d::operator* (const Vec3d& _Other) const
{
	double _x = x * _Other.x;
	double _y = y * _Other.y;
	double _z = z * _Other.z;

	return Vec3d(_x, _y, _z);
}

const BFW::Math::Vec3d& BFW::Math::Vec3d::operator*= (const Vec3d& _Other)
{
	x *= _Other.x;
	y *= _Other.y;
	z *= _Other.z;

	return *this;
}

const BFW::Math::Vec3d BFW::Math::Vec3d::operator* (const double _Scale) const
{
	double _x = x * _Scale;
	double _y = y * _Scale;
	double _z = z * _Scale;

	return Vec3d(_x, _y, _z);
}

const BFW::Math::Vec3d& BFW::Math::Vec3d::operator*= (const double _Scale)
{
	x *= _Scale;
	y *= _Scale;
	z *= _Scale;

	return *this;
}

const BFW::Math::Vec3d BFW::Math::Vec3d::operator/ (const Vec3d& _Other) const
{
	double _x = x / _Other.x;
	double _y = y / _Other.y;
	double _z = z / _Other.z;

	return Vec3d(_x, _y, _z);
}

const BFW::Math::Vec3d& BFW::Math::Vec3d::operator/= (const Vec3d& _Other)
{
	x /= _Other.x;
	y /= _Other.y;
	z /= _Other.z;

	return *this;
}

const BFW::Math::Vec3d BFW::Math::Vec3d::operator/ (const double _Scale) const
{
	double _x = x / _Scale;
	double _y = y / _Scale;
	double _z = z / _Scale;

	return Vec3d(_x, _y, _z);
}

const BFW::Math::Vec3d& BFW::Math::Vec3d::operator/= (const double _Scale)
{
	x /= _Scale;
	y /= _Scale;
	z /= _Scale;

	return *this;
}

const bool BFW::Math::Vec3d::operator== (const Vec3d& _Other) const
{
	return x == _Other.x && y == _Other.y && z == _Other.z;
}

const bool BFW::Math::Vec3d::operator!= (const Vec3d& _Other) const
{
	return x != _Other.x || y != _Other.y || z != _Other.z;
}

const bool BFW::Math::Vec3d::operator> (const Vec3d& _Other) const
{
	return Magnitude() > _Other.Magnitude();
}

const bool BFW::Math::Vec3d::operator>= (const Vec3d& _Other) const
{
	return Magnitude() >= _Other.Magnitude();
}

const bool BFW::Math::Vec3d::operator< (const Vec3d& _Other) const
{
	return Magnitude() < _Other.Magnitude();
}

const bool BFW::Math::Vec3d::operator<= (const Vec3d& _Other) const
{
	return Magnitude() <= _Other.Magnitude();
}

double& BFW::Math::Vec3d::operator[] (const unsigned long _Index)
{
	return Data()[_Index];
}

const double& BFW::Math::Vec3d::operator[] (const unsigned long _Index) const
{
	return Data()[_Index];
}

const BFW::Math::Vec3d& BFW::Math::Vec3d::operator= (const Vec3d& _Other)
{
	x = _Other.x;
	y = _Other.y;
	z = _Other.z;

	return *this;
}

const BFW::Math::Vec3d& BFW::Math::Vec3d::operator= (Vec3d&& _Other) noexcept
{
	x = _Other.x;
	y = _Other.y;
	z = _Other.z;

	_Other.x = 0.0;
	_Other.y = 0.0;
	_Other.z = 0.0;

	return *this;
}



BFW::Math::Vec4d::Vec4d(const double _x, const double _y, const double _z, const double _w) : x(_x), y(_y), z(_z), w(_w)
{

}

BFW::Math::Vec4d::Vec4d(const Vec4d& _Other) : x(_Other.x), y(_Other.y), z(_Other.z), w(_Other.w)
{

}

BFW::Math::Vec4d::Vec4d(Vec4d&& _Other) noexcept : x(_Other.x), y(_Other.y), z(_Other.z), w(_Other.w)
{
	_Other.x = 0.0;
	_Other.y = 0.0;
	_Other.z = 0.0;
	_Other.w = 0.0;
}

BFW::Math::Vec4d::~Vec4d()
{

}

double* BFW::Math::Vec4d::Data()
{
	return &x;
}

const double* BFW::Math::Vec4d::Data() const
{
	return &x;
}

const double BFW::Math::Vec4d::Magnitude() const
{
	return dSqrt(x * x + y * y + z * z + w * w);
}

const double BFW::Math::Vec4d::DotProduct(const Vec4d& _Other) const
{
	return x * _Other.x + y * _Other.y + z * _Other.z + w * _Other.w;
}

const BFW::Math::Vec4d BFW::Math::Vec4d::CrossProduct(const Vec4d& _Other) const
{
	double _x = y * _Other.z - z * _Other.y;
	double _y = z * _Other.x - x * _Other.z;
	double _z = x * _Other.y - y * _Other.x;
	return Vec4d(_x, _y, _z, w);
}

const double BFW::Math::Vec4d::GetAngle(const Vec4d& _Center, const Vec4d& _Other) const
{
	Vec4d _V = *this - _Center;
	return dPeriod(dACos(_V.DotProduct(_Other) / (_V.Magnitude() * _Other.Magnitude())), 0.0, dPi * 2.0);
}

const BFW::Math::Vec4d BFW::Math::Vec4d::Rotated(const double _Angle, const Vec4d& _Center, const Vec4d& _U) const
{
	double _NewX = x - _Center.x;
	double _NewY = y - _Center.y;
	double _NewZ = z - _Center.z;
	double _Sin = dSin(_Angle);
	double _Cos = dCos(_Angle);

	double _x = _NewX * (_Cos + _U.x * _U.x * (1.0 - _Cos)) + _NewY * (_U.x * _U.y * (1.0 - _Cos) - _U.z * _Sin) + _NewZ * (_U.x * _U.z * (1.0 - _Cos) + _U.y * _Sin) + _Center.x;
	double _y = _NewX * (_U.y * _U.x * (1.0 - _Cos) + _U.z * _Sin) + _NewY * (_Cos + _U.y * _U.y * (1.0 - _Cos)) + _NewZ * (_U.y * _U.z * (1.0 - _Cos) - _U.x * _Sin) + _Center.y;
	double _z = _NewX * (_U.z * _U.x * (1.0 - _Cos) - _U.y * _Sin) + _NewY * (_U.z * _U.y * (1.0 - _Cos) + _U.x * _Sin) + _NewZ * (_Cos + _U.z * _U.z * (1.0 - _Cos)) + _Center.z;

	return Vec4d(_x, _y, _z, w);
}

const BFW::Math::Vec4d& BFW::Math::Vec4d::Rotate(const double _Angle, const Vec4d& _Center, const Vec4d& _U)
{
	double _NewX = x - _Center.x;
	double _NewY = y - _Center.y;
	double _NewZ = z - _Center.z;
	double _Sin = dSin(_Angle);
	double _Cos = dCos(_Angle);

	x = _NewX * (_Cos + _U.x * _U.x * (1.0 - _Cos)) + _NewY * (_U.x * _U.y * (1.0 - _Cos) - _U.z * _Sin) + _NewZ * (_U.x * _U.z * (1.0 - _Cos) + _U.y * _Sin) + _Center.x;
	y = _NewX * (_U.y * _U.x * (1.0 - _Cos) + _U.z * _Sin) + _NewY * (_Cos + _U.y * _U.y * (1.0 - _Cos)) + _NewZ * (_U.y * _U.z * (1.0 - _Cos) - _U.x * _Sin) + _Center.y;
	z = _NewX * (_U.z * _U.x * (1.0 - _Cos) - _U.y * _Sin) + _NewY * (_U.z * _U.y * (1.0 - _Cos) + _U.x * _Sin) + _NewZ * (_Cos + _U.z * _U.z * (1.0 - _Cos)) + _Center.z;

	return *this;
}

const BFW::Math::Vec4d BFW::Math::Vec4d::Flipped(const Vec4d& _U, const Vec4d& _Center) const
{
	double _NewX = x - _Center.x;
	double _NewY = y - _Center.y;
	double _NewZ = z - _Center.z;

	double _x = _NewX * (1.0 - 2.0 * _U.x * _U.x) + _NewY * (-2.0 * _U.x * _U.y) + _NewZ * (-2.0 * _U.x * _U.z) + _Center.x;
	double _y = _NewX * (-2.0 * _U.x * _U.y) + _NewY * (1.0 - 2.0 * _U.y * _U.y) + _NewZ * (-2.0 * _U.y * _U.z) + _Center.y;
	double _z = _NewX * (-2.0 * _U.x * _U.z) + _NewY * (-2.0 * _U.y * _U.z) + _NewZ * (1.0 - 2.0 * _U.z * _U.z) + _Center.z;

	return Vec4d(_x, _y, _z, w);
}

const BFW::Math::Vec4d& BFW::Math::Vec4d::Flip(const Vec4d& _U, const Vec4d& _Center)
{
	double _NewX = x - _Center.x;
	double _NewY = y - _Center.y;
	double _NewZ = z - _Center.z;

	x = _NewX * (1.0 - 2.0 * _U.x * _U.x) + _NewY * (-2.0 * _U.x * _U.y) + _NewZ * (-2.0 * _U.x * _U.z) + _Center.x;
	y = _NewX * (-2.0 * _U.x * _U.y) + _NewY * (1.0 - 2.0 * _U.y * _U.y) + _NewZ * (-2.0 * _U.y * _U.z) + _Center.y;
	z = _NewX * (-2.0 * _U.x * _U.z) + _NewY * (-2.0 * _U.y * _U.z) + _NewZ * (1.0 - 2.0 * _U.z * _U.z) + _Center.z;

	return *this;
}

const BFW::Math::Vec4d& BFW::Math::Vec4d::operator+ () const
{
	return *this;
}

const BFW::Math::Vec4d BFW::Math::Vec4d::operator- () const
{
	return Vec4d(-x, -y, -z, -w);
}

const BFW::Math::Vec4d BFW::Math::Vec4d::operator+ (const Vec4d& _Other) const
{
	double _x = x + _Other.x;
	double _y = y + _Other.y;
	double _z = z + _Other.z;
	double _w = w + _Other.w;

	return Vec4d(_x, _y, _z, _w);
}

const BFW::Math::Vec4d& BFW::Math::Vec4d::operator+= (const Vec4d& _Other)
{
	x += _Other.x;
	y += _Other.y;
	z += _Other.z;
	w += _Other.w;

	return *this;
}

const BFW::Math::Vec4d BFW::Math::Vec4d::operator+ (const double _Scale) const
{
	double _x = x + _Scale;
	double _y = y + _Scale;
	double _z = z + _Scale;
	double _w = w + _Scale;

	return Vec4d(_x, _y, _z, _w);
}

const BFW::Math::Vec4d& BFW::Math::Vec4d::operator+= (const double _Scale)
{
	x += _Scale;
	y += _Scale;
	z += _Scale;
	w += _Scale;

	return *this;
}

const BFW::Math::Vec4d BFW::Math::Vec4d::operator- (const Vec4d& _Other) const
{
	double _x = x - _Other.x;
	double _y = y - _Other.y;
	double _z = z - _Other.z;
	double _w = w - _Other.w;

	return Vec4d(_x, _y, _z, _w);
}

const BFW::Math::Vec4d& BFW::Math::Vec4d::operator-= (const Vec4d& _Other)
{
	x -= _Other.x;
	y -= _Other.y;
	z -= _Other.z;
	w -= _Other.w;

	return *this;
}

const BFW::Math::Vec4d BFW::Math::Vec4d::operator- (const double _Scale) const
{
	double _x = x - _Scale;
	double _y = y - _Scale;
	double _z = z - _Scale;
	double _w = w - _Scale;

	return Vec4d(_x, _y, _z, _w);
}

const BFW::Math::Vec4d& BFW::Math::Vec4d::operator-= (const double _Scale)
{
	x -= _Scale;
	y -= _Scale;
	z -= _Scale;
	w -= _Scale;

	return *this;
}

const BFW::Math::Vec4d BFW::Math::Vec4d::operator* (const Vec4d& _Other) const
{
	double _x = x * _Other.x;
	double _y = y * _Other.y;
	double _z = z * _Other.z;
	double _w = w * _Other.w;

	return Vec4d(_x, _y, _z, _w);
}

const BFW::Math::Vec4d& BFW::Math::Vec4d::operator*= (const Vec4d& _Other)
{
	x *= _Other.x;
	y *= _Other.y;
	z *= _Other.z;
	w *= _Other.w;

	return *this;
}

const BFW::Math::Vec4d BFW::Math::Vec4d::operator* (const double _Scale) const
{
	double _x = x * _Scale;
	double _y = y * _Scale;
	double _z = z * _Scale;
	double _w = w * _Scale;

	return Vec4d(_x, _y, _z, _w);
}

const BFW::Math::Vec4d& BFW::Math::Vec4d::operator*= (const double _Scale)
{
	x *= _Scale;
	y *= _Scale;
	z *= _Scale;
	w *= _Scale;

	return *this;
}

const BFW::Math::Vec4d BFW::Math::Vec4d::operator/ (const Vec4d& _Other) const
{
	double _x = x / _Other.x;
	double _y = y / _Other.y;
	double _z = z / _Other.z;
	double _w = w / _Other.w;

	return Vec4d(_x, _y, _z, _w);
}

const BFW::Math::Vec4d& BFW::Math::Vec4d::operator/= (const Vec4d& _Other)
{
	x /= _Other.x;
	y /= _Other.y;
	z /= _Other.z;
	w /= _Other.w;

	return *this;
}

const BFW::Math::Vec4d BFW::Math::Vec4d::operator/ (const double _Scale) const
{
	double _x = x / _Scale;
	double _y = y / _Scale;
	double _z = z / _Scale;
	double _w = w / _Scale;

	return Vec4d(_x, _y, _z, _w);
}

const BFW::Math::Vec4d& BFW::Math::Vec4d::operator/= (const double _Scale)
{
	x /= _Scale;
	y /= _Scale;
	z /= _Scale;
	w /= _Scale;

	return *this;
}

const bool BFW::Math::Vec4d::operator== (const Vec4d& _Other) const
{
	return x == _Other.x && y == _Other.y && z == _Other.z && w == _Other.w;
}

const bool BFW::Math::Vec4d::operator!= (const Vec4d& _Other) const
{
	return x != _Other.x || y != _Other.y || z != _Other.z || w != _Other.w;
}

const bool BFW::Math::Vec4d::operator> (const Vec4d& _Other) const
{
	return Magnitude() > _Other.Magnitude();
}

const bool BFW::Math::Vec4d::operator>= (const Vec4d& _Other) const
{
	return Magnitude() >= _Other.Magnitude();
}

const bool BFW::Math::Vec4d::operator< (const Vec4d& _Other) const
{
	return Magnitude() < _Other.Magnitude();
}

const bool BFW::Math::Vec4d::operator<= (const Vec4d& _Other) const
{
	return Magnitude() <= _Other.Magnitude();
}

double& BFW::Math::Vec4d::operator[] (const unsigned long _Index)
{
	return Data()[_Index];
}

const double& BFW::Math::Vec4d::operator[] (const unsigned long _Index) const
{
	return Data()[_Index];
}

const BFW::Math::Vec4d& BFW::Math::Vec4d::operator= (const Vec4d& _Other)
{
	x = _Other.x;
	y = _Other.y;
	z = _Other.z;
	w = _Other.w;

	return *this;
}

const BFW::Math::Vec4d& BFW::Math::Vec4d::operator= (Vec4d&& _Other) noexcept
{
	x = _Other.x;
	y = _Other.y;
	z = _Other.z;
	w = _Other.w;

	_Other.x = 0.0;
	_Other.y = 0.0;
	_Other.z = 0.0;
	_Other.w = 0.0;

	return *this;
}
