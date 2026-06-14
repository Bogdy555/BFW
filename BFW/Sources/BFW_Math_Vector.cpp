#include "../Headers/BFW.hpp"



BFW::Math::Vec2::Vec2() : x(0.0f), y(0.0f)
{

}

BFW::Math::Vec2::Vec2(const float _x, const float _y) : x(_x), y(_y)
{

}

BFW::Math::Vec2::Vec2(const Vec2& _Other) : x(_Other.x), y(_Other.y)
{

}

BFW::Math::Vec2::Vec2(Vec2&& _Other) noexcept : x(_Other.x), y(_Other.y)
{
	_Other.x = 0.0f;
	_Other.y = 0.0f;
}

BFW::Math::Vec2::~Vec2()
{

}

float* BFW::Math::Vec2::Data()
{
	return &x;
}

const float* BFW::Math::Vec2::Data() const
{
	return &x;
}

const float BFW::Math::Vec2::Magnitude() const
{
	return sqrtf(x * x + y * y);
}

BFW::Math::Vec2& BFW::Math::Vec2::Normalize()
{
	*this /= Magnitude();

	return *this;
}

const BFW::Math::Vec2 BFW::Math::Vec2::Normalized() const
{
	return *this / Magnitude();
}

const BFW::Math::Vec2& BFW::Math::Vec2::operator+ () const
{
	return *this;
}

const BFW::Math::Vec2 BFW::Math::Vec2::operator- () const
{
	return Vec2(-x, -y);
}

const BFW::Math::Vec2 BFW::Math::Vec2::operator+ (const Vec2& _Other) const
{
	return Vec2(x + _Other.x, y + _Other.y);
}

BFW::Math::Vec2& BFW::Math::Vec2::operator+= (const Vec2& _Other)
{
	x += _Other.x;
	y += _Other.y;

	return *this;
}

const BFW::Math::Vec2 BFW::Math::Vec2::operator+ (const float _Value) const
{
	return Vec2(x + _Value, y + _Value);
}

BFW::Math::Vec2& BFW::Math::Vec2::operator+= (const float _Value)
{
	x += _Value;
	y += _Value;

	return *this;
}

const BFW::Math::Vec2 BFW::Math::Vec2::operator- (const Vec2& _Other) const
{
	return Vec2(x - _Other.x, y - _Other.y);
}

BFW::Math::Vec2& BFW::Math::Vec2::operator-= (const Vec2& _Other)
{
	x -= _Other.x;
	y -= _Other.y;

	return *this;
}

const BFW::Math::Vec2 BFW::Math::Vec2::operator- (const float _Value) const
{
	return Vec2(x - _Value, y - _Value);
}

BFW::Math::Vec2& BFW::Math::Vec2::operator-= (const float _Value)
{
	x -= _Value;
	y -= _Value;

	return *this;
}

const BFW::Math::Vec2 BFW::Math::Vec2::operator* (const Vec2& _Other) const
{
	return Vec2(x * _Other.x, y * _Other.y);
}

BFW::Math::Vec2& BFW::Math::Vec2::operator*= (const Vec2& _Other)
{
	x *= _Other.x;
	y *= _Other.y;

	return *this;
}

const BFW::Math::Vec2 BFW::Math::Vec2::operator* (const float _Value) const
{
	return Vec2(x * _Value, y * _Value);
}

BFW::Math::Vec2& BFW::Math::Vec2::operator*= (const float _Value)
{
	x *= _Value;
	y *= _Value;

	return *this;
}

const BFW::Math::Vec2 BFW::Math::Vec2::operator/ (const Vec2& _Other) const
{
	return Vec2(x / _Other.x, y / _Other.y);
}

BFW::Math::Vec2& BFW::Math::Vec2::operator/= (const Vec2& _Other)
{
	x /= _Other.x;
	y /= _Other.y;

	return *this;
}

const BFW::Math::Vec2 BFW::Math::Vec2::operator/ (const float _Value) const
{
	return Vec2(x / _Value, y / _Value);
}

BFW::Math::Vec2& BFW::Math::Vec2::operator/= (const float _Value)
{
	x /= _Value;
	y /= _Value;

	return *this;
}

const bool BFW::Math::Vec2::operator== (const Vec2& _Other) const
{
	return x == _Other.x && y == _Other.y;
}

const bool BFW::Math::Vec2::operator!= (const Vec2& _Other) const
{
	return x != _Other.x || y != _Other.y;
}

float& BFW::Math::Vec2::operator[] (const size_t _Index)
{
	return Data()[_Index];
}

const float& BFW::Math::Vec2::operator[] (const size_t _Index) const
{
	return Data()[_Index];
}

BFW::Math::Vec2& BFW::Math::Vec2::operator= (const Vec2& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	x = _Other.x;
	y = _Other.y;

	return *this;
}

BFW::Math::Vec2& BFW::Math::Vec2::operator= (Vec2&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	x = _Other.x;
	y = _Other.y;

	_Other.x = 0.0f;
	_Other.y = 0.0f;

	return *this;
}

const float BFW::Math::Vec2::Distance(const Vec2& _AVec, const Vec2& _BVec)
{
	return (_BVec - _AVec).Magnitude();
}

const float BFW::Math::Vec2::Angle(const Vec2& _AVec, const Vec2& _BVec)
{
	return acosf(Dot(_AVec.Normalized(), _BVec.Normalized()));
}

const float BFW::Math::Vec2::Dot(const Vec2& _AVec, const Vec2& _BVec)
{
	return _AVec.x * _BVec.x + _AVec.y * _BVec.y;
}

const BFW::Math::Vec2 BFW::Math::Vec2::Mix(const Vec2& _AVec, const Vec2& _BVec, const float _Percentage)
{
	return Vec2(Math::Mix(_AVec.x, _BVec.x, _Percentage), Math::Mix(_AVec.y, _BVec.y, _Percentage));
}

const BFW::Math::Vec2 BFW::Math::Vec2::Clamp(const Vec2& _Value, const Vec2& _Min, const Vec2& _Max)
{
	return Vec2(Math::Clamp(_Value.x, _Min.x, _Max.x), Math::Clamp(_Value.y, _Min.y, _Max.y));
}

const BFW::Math::Vec2 BFW::Math::Vec2::Min(const Vec2& _AVec, const Vec2& _BVec)
{
	return Vec2(Math::Min(_AVec.x, _BVec.x), Math::Min(_AVec.y, _BVec.y));
}

const BFW::Math::Vec2 BFW::Math::Vec2::Max(const Vec2& _AVec, const Vec2& _BVec)
{
	return Vec2(Math::Max(_AVec.x, _BVec.x), Math::Max(_AVec.y, _BVec.y));
}

const BFW::Math::Vec2 BFW::Math::Vec2::Pow(const Vec2& _Base, const Vec2& _Power)
{
	return Vec2(powf(_Base.x, _Power.x), powf(_Base.y, _Power.y));
}

const BFW::Math::Vec2 BFW::Math::Vec2::Exp(const Vec2& _Power)
{
	return Vec2(expf(_Power.x), expf(_Power.y));
}

const BFW::Math::Vec2 BFW::Math::Vec2::Reflect(const Vec2& _Vec, const Vec2& _Normal)
{
	return _Vec - _Normal * 2.0f * Dot(_Vec, _Normal) / _Normal.Magnitude() / _Normal.Magnitude();
}



BFW::Math::Vec3::Vec3() : x(0.0f), y(0.0f), z(0.0f)
{

}

BFW::Math::Vec3::Vec3(const float _x, const float _y, const float _z) : x(_x), y(_y), z(_z)
{

}

BFW::Math::Vec3::Vec3(const Vec3& _Other) : x(_Other.x), y(_Other.y), z(_Other.z)
{

}

BFW::Math::Vec3::Vec3(Vec3&& _Other) noexcept : x(_Other.x), y(_Other.y), z(_Other.z)
{
	_Other.x = 0.0f;
	_Other.y = 0.0f;
	_Other.z = 0.0f;
}

BFW::Math::Vec3::Vec3(const Vec2& _Other, const float _z) : x(_Other.x), y(_Other.y), z(_z)
{

}

BFW::Math::Vec3::~Vec3()
{

}

BFW::Math::Vec3::operator const BFW::Math::Vec2() const
{
	return Vec2(x, y);
}

float* BFW::Math::Vec3::Data()
{
	return &x;
}

const float* BFW::Math::Vec3::Data() const
{
	return &x;
}

const float BFW::Math::Vec3::Magnitude() const
{
	return sqrtf(x * x + y * y + z * z);
}

BFW::Math::Vec3& BFW::Math::Vec3::Normalize()
{
	*this /= Magnitude();

	return *this;
}

const BFW::Math::Vec3 BFW::Math::Vec3::Normalized() const
{
	return *this / Magnitude();
}

const BFW::Math::Vec3& BFW::Math::Vec3::operator+ () const
{
	return *this;
}

const BFW::Math::Vec3 BFW::Math::Vec3::operator- () const
{
	return Vec3(-x, -y, -z);
}

const BFW::Math::Vec3 BFW::Math::Vec3::operator+ (const Vec3& _Other) const
{
	return Vec3(x + _Other.x, y + _Other.y, z + _Other.z);
}

BFW::Math::Vec3& BFW::Math::Vec3::operator+= (const Vec3& _Other)
{
	x += _Other.x;
	y += _Other.y;
	z += _Other.z;

	return *this;
}

const BFW::Math::Vec3 BFW::Math::Vec3::operator+ (const float _Value) const
{
	return Vec3(x + _Value, y + _Value, z + _Value);
}

BFW::Math::Vec3& BFW::Math::Vec3::operator+= (const float _Value)
{
	x += _Value;
	y += _Value;
	z += _Value;

	return *this;
}

const BFW::Math::Vec3 BFW::Math::Vec3::operator- (const Vec3& _Other) const
{
	return Vec3(x - _Other.x, y - _Other.y, z - _Other.z);
}

BFW::Math::Vec3& BFW::Math::Vec3::operator-= (const Vec3& _Other)
{
	x -= _Other.x;
	y -= _Other.y;
	z -= _Other.z;

	return *this;
}

const BFW::Math::Vec3 BFW::Math::Vec3::operator- (const float _Value) const
{
	return Vec3(x - _Value, y - _Value, z - _Value);
}

BFW::Math::Vec3& BFW::Math::Vec3::operator-= (const float _Value)
{
	x -= _Value;
	y -= _Value;
	z -= _Value;

	return *this;
}

const BFW::Math::Vec3 BFW::Math::Vec3::operator* (const Vec3& _Other) const
{
	return Vec3(x * _Other.x, y * _Other.y, z * _Other.z);
}

BFW::Math::Vec3& BFW::Math::Vec3::operator*= (const Vec3& _Other)
{
	x *= _Other.x;
	y *= _Other.y;
	z *= _Other.z;

	return *this;
}

const BFW::Math::Vec3 BFW::Math::Vec3::operator* (const float _Value) const
{
	return Vec3(x * _Value, y * _Value, z * _Value);
}

BFW::Math::Vec3& BFW::Math::Vec3::operator*= (const float _Value)
{
	x *= _Value;
	y *= _Value;
	z *= _Value;

	return *this;
}

const BFW::Math::Vec3 BFW::Math::Vec3::operator/ (const Vec3& _Other) const
{
	return Vec3(x / _Other.x, y / _Other.y, z / _Other.z);
}

BFW::Math::Vec3& BFW::Math::Vec3::operator/= (const Vec3& _Other)
{
	x /= _Other.x;
	y /= _Other.y;
	z /= _Other.z;

	return *this;
}

const BFW::Math::Vec3 BFW::Math::Vec3::operator/ (const float _Value) const
{
	return Vec3(x / _Value, y / _Value, z / _Value);
}

BFW::Math::Vec3& BFW::Math::Vec3::operator/= (const float _Value)
{
	x /= _Value;
	y /= _Value;
	z /= _Value;

	return *this;
}

const bool BFW::Math::Vec3::operator== (const Vec3& _Other) const
{
	return x == _Other.x && y == _Other.y && z == _Other.z;
}

const bool BFW::Math::Vec3::operator!= (const Vec3& _Other) const
{
	return x != _Other.x || y != _Other.y || z != _Other.z;
}

float& BFW::Math::Vec3::operator[] (const size_t _Index)
{
	return Data()[_Index];
}

const float& BFW::Math::Vec3::operator[] (const size_t _Index) const
{
	return Data()[_Index];
}

BFW::Math::Vec3& BFW::Math::Vec3::operator= (const Vec3& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	x = _Other.x;
	y = _Other.y;
	z = _Other.z;

	return *this;
}

BFW::Math::Vec3& BFW::Math::Vec3::operator= (Vec3&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	x = _Other.x;
	y = _Other.y;
	z = _Other.z;

	_Other.x = 0.0f;
	_Other.y = 0.0f;
	_Other.z = 0.0f;

	return *this;
}

const float BFW::Math::Vec3::Distance(const Vec3& _AVec, const Vec3& _BVec)
{
	return (_BVec - _AVec).Magnitude();
}

const float BFW::Math::Vec3::Angle(const Vec3& _AVec, const Vec3& _BVec)
{
	return acosf(Dot(_AVec.Normalized(), _BVec.Normalized()));
}

const float BFW::Math::Vec3::Dot(const Vec3& _AVec, const Vec3& _BVec)
{
	return _AVec.x * _BVec.x + _AVec.y * _BVec.y + _AVec.z * _BVec.z;
}

const BFW::Math::Vec3 BFW::Math::Vec3::Cross(const Vec3& _AVec, const Vec3& _BVec)
{
	return Vec3(_AVec.y * _BVec.z - _AVec.z * _BVec.y, _AVec.z * _BVec.x - _AVec.x * _BVec.z, _AVec.x * _BVec.y - _AVec.y * _BVec.x);
}

const BFW::Math::Vec3 BFW::Math::Vec3::Mix(const Vec3& _AVec, const Vec3& _BVec, const float _Percentage)
{
	return Vec3(Math::Mix(_AVec.x, _BVec.x, _Percentage), Math::Mix(_AVec.y, _BVec.y, _Percentage), Math::Mix(_AVec.z, _BVec.z, _Percentage));
}

const BFW::Math::Vec3 BFW::Math::Vec3::Clamp(const Vec3& _Value, const Vec3& _Min, const Vec3& _Max)
{
	return Vec3(Math::Clamp(_Value.x, _Min.x, _Max.x), Math::Clamp(_Value.y, _Min.y, _Max.y), Math::Clamp(_Value.z, _Min.z, _Max.z));
}

const BFW::Math::Vec3 BFW::Math::Vec3::Min(const Vec3& _AVec, const Vec3& _BVec)
{
	return Vec3(Math::Min(_AVec.x, _BVec.x), Math::Min(_AVec.y, _BVec.y), Math::Min(_AVec.z, _BVec.z));
}

const BFW::Math::Vec3 BFW::Math::Vec3::Max(const Vec3& _AVec, const Vec3& _BVec)
{
	return Vec3(Math::Max(_AVec.x, _BVec.x), Math::Max(_AVec.y, _BVec.y), Math::Max(_AVec.z, _BVec.z));
}

const BFW::Math::Vec3 BFW::Math::Vec3::Pow(const Vec3& _Base, const Vec3& _Power)
{
	return Vec3(powf(_Base.x, _Power.x), powf(_Base.y, _Power.y), powf(_Base.z, _Power.z));
}

const BFW::Math::Vec3 BFW::Math::Vec3::Exp(const Vec3& _Power)
{
	return Vec3(expf(_Power.x), expf(_Power.y), expf(_Power.z));
}

const BFW::Math::Vec3 BFW::Math::Vec3::Reflect(const Vec3& _Vec, const Vec3& _Normal)
{
	return _Vec - _Normal * 2.0f * Dot(_Vec, _Normal) / _Normal.Magnitude() / _Normal.Magnitude();
}



BFW::Math::Vec4::Vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{

}

BFW::Math::Vec4::Vec4(const float _x, const float _y, const float _z, const float _w) : x(_x), y(_y), z(_z), w(_w)
{

}

BFW::Math::Vec4::Vec4(const Vec4& _Other) : x(_Other.x), y(_Other.y), z(_Other.z), w(_Other.w)
{

}

BFW::Math::Vec4::Vec4(Vec4&& _Other) noexcept : x(_Other.x), y(_Other.y), z(_Other.z), w(_Other.w)
{
	_Other.x = 0.0f;
	_Other.y = 0.0f;
	_Other.z = 0.0f;
	_Other.w = 0.0f;
}

BFW::Math::Vec4::Vec4(const Vec2& _Other, const float _z, const float _w) : x(_Other.x), y(_Other.y), z(_z), w(_w)
{

}

BFW::Math::Vec4::Vec4(const Vec3& _Other, const float _w) : x(_Other.x), y(_Other.y), z(_Other.z), w(_w)
{

}

BFW::Math::Vec4::~Vec4()
{

}

BFW::Math::Vec4::operator const BFW::Math::Vec2() const
{
	return Vec2(x, y);
}

BFW::Math::Vec4::operator const BFW::Math::Vec3() const
{
	return Vec3(x, y, z);
}

float* BFW::Math::Vec4::Data()
{
	return &x;
}

const float* BFW::Math::Vec4::Data() const
{
	return &x;
}

const float BFW::Math::Vec4::Magnitude() const
{
	return sqrtf(x * x + y * y + z * z);
}

BFW::Math::Vec4& BFW::Math::Vec4::Normalize()
{
	*this = Vec4(Vec3(*this) / Magnitude(), w);

	return *this;
}

const BFW::Math::Vec4 BFW::Math::Vec4::Normalized() const
{
	return Vec4(Vec3(*this) / Magnitude(), w);
}

const BFW::Math::Vec4& BFW::Math::Vec4::operator+ () const
{
	return *this;
}

const BFW::Math::Vec4 BFW::Math::Vec4::operator- () const
{
	return Vec4(-x, -y, -z, -w);
}

const BFW::Math::Vec4 BFW::Math::Vec4::operator+ (const Vec4& _Other) const
{
	return Vec4(x + _Other.x, y + _Other.y, z + _Other.z, w + _Other.w);
}

BFW::Math::Vec4& BFW::Math::Vec4::operator+= (const Vec4& _Other)
{
	x += _Other.x;
	y += _Other.y;
	z += _Other.z;
	w += _Other.w;

	return *this;
}

const BFW::Math::Vec4 BFW::Math::Vec4::operator+ (const float _Value) const
{
	return Vec4(x + _Value, y + _Value, z + _Value, w + _Value);
}

BFW::Math::Vec4& BFW::Math::Vec4::operator+= (const float _Value)
{
	x += _Value;
	y += _Value;
	z += _Value;
	w += _Value;

	return *this;
}

const BFW::Math::Vec4 BFW::Math::Vec4::operator- (const Vec4& _Other) const
{
	return Vec4(x - _Other.x, y - _Other.y, z - _Other.z, w - _Other.w);
}

BFW::Math::Vec4& BFW::Math::Vec4::operator-= (const Vec4& _Other)
{
	x -= _Other.x;
	y -= _Other.y;
	z -= _Other.z;
	w -= _Other.w;

	return *this;
}

const BFW::Math::Vec4 BFW::Math::Vec4::operator- (const float _Value) const
{
	return Vec4(x - _Value, y - _Value, z - _Value, w - _Value);
}

BFW::Math::Vec4& BFW::Math::Vec4::operator-= (const float _Value)
{
	x -= _Value;
	y -= _Value;
	z -= _Value;
	w -= _Value;

	return *this;
}

const BFW::Math::Vec4 BFW::Math::Vec4::operator* (const Vec4& _Other) const
{
	return Vec4(x * _Other.x, y * _Other.y, z * _Other.z, w * _Other.w);
}

BFW::Math::Vec4& BFW::Math::Vec4::operator*= (const Vec4& _Other)
{
	x *= _Other.x;
	y *= _Other.y;
	z *= _Other.z;
	w *= _Other.w;

	return *this;
}

const BFW::Math::Vec4 BFW::Math::Vec4::operator* (const float _Value) const
{
	return Vec4(x * _Value, y * _Value, z * _Value, w * _Value);
}

BFW::Math::Vec4& BFW::Math::Vec4::operator*= (const float _Value)
{
	x *= _Value;
	y *= _Value;
	z *= _Value;
	w *= _Value;

	return *this;
}

const BFW::Math::Vec4 BFW::Math::Vec4::operator/ (const Vec4& _Other) const
{
	return Vec4(x / _Other.x, y / _Other.y, z / _Other.z, w / _Other.w);
}

BFW::Math::Vec4& BFW::Math::Vec4::operator/= (const Vec4& _Other)
{
	x /= _Other.x;
	y /= _Other.y;
	z /= _Other.z;
	w /= _Other.w;

	return *this;
}

const BFW::Math::Vec4 BFW::Math::Vec4::operator/ (const float _Value) const
{
	return Vec4(x / _Value, y / _Value, z / _Value, w / _Value);
}

BFW::Math::Vec4& BFW::Math::Vec4::operator/= (const float _Value)
{
	x /= _Value;
	y /= _Value;
	z /= _Value;
	w /= _Value;

	return *this;
}

const bool BFW::Math::Vec4::operator== (const Vec4& _Other) const
{
	return x == _Other.x && y == _Other.y && z == _Other.z && w == _Other.w;
}

const bool BFW::Math::Vec4::operator!= (const Vec4& _Other) const
{
	return x != _Other.x || y != _Other.y || z != _Other.z || w != _Other.w;
}

float& BFW::Math::Vec4::operator[] (const size_t _Index)
{
	return Data()[_Index];
}

const float& BFW::Math::Vec4::operator[] (const size_t _Index) const
{
	return Data()[_Index];
}

BFW::Math::Vec4& BFW::Math::Vec4::operator= (const Vec4& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	x = _Other.x;
	y = _Other.y;
	z = _Other.z;
	w = _Other.w;

	return *this;
}

BFW::Math::Vec4& BFW::Math::Vec4::operator= (Vec4&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

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

const float BFW::Math::Vec4::Distance(const Vec4& _AVec, const Vec4& _BVec)
{
	return (_BVec - _AVec).Magnitude();
}

const float BFW::Math::Vec4::Angle(const Vec4& _AVec, const Vec4& _BVec)
{
	return acosf(Dot(_AVec.Normalized(), _BVec.Normalized()));
}

const float BFW::Math::Vec4::Dot(const Vec4& _AVec, const Vec4& _BVec)
{
	return _AVec.x * _BVec.x + _AVec.y * _BVec.y + _AVec.z * _BVec.z;
}

const BFW::Math::Vec4 BFW::Math::Vec4::Cross(const Vec4& _AVec, const Vec4& _BVec)
{
	return Vec4(_AVec.y * _BVec.z - _AVec.z * _BVec.y, _AVec.z * _BVec.x - _AVec.x * _BVec.z, _AVec.x * _BVec.y - _AVec.y * _BVec.x, _AVec.w * _BVec.w);
}

const BFW::Math::Vec4 BFW::Math::Vec4::Mix(const Vec4& _AVec, const Vec4& _BVec, const float _Percentage)
{
	return Vec4(Math::Mix(_AVec.x, _BVec.x, _Percentage), Math::Mix(_AVec.y, _BVec.y, _Percentage), Math::Mix(_AVec.z, _BVec.z, _Percentage), Math::Mix(_AVec.w, _BVec.w, _Percentage));
}

const BFW::Math::Vec4 BFW::Math::Vec4::Clamp(const Vec4& _Value, const Vec4& _Min, const Vec4& _Max)
{
	return Vec4(Math::Clamp(_Value.x, _Min.x, _Max.x), Math::Clamp(_Value.y, _Min.y, _Max.y), Math::Clamp(_Value.z, _Min.z, _Max.z), Math::Clamp(_Value.w, _Min.w, _Max.w));
}

const BFW::Math::Vec4 BFW::Math::Vec4::Min(const Vec4& _AVec, const Vec4& _BVec)
{
	return Vec4(Math::Min(_AVec.x, _BVec.x), Math::Min(_AVec.y, _BVec.y), Math::Min(_AVec.z, _BVec.z), Math::Min(_AVec.w, _BVec.w));
}

const BFW::Math::Vec4 BFW::Math::Vec4::Max(const Vec4& _AVec, const Vec4& _BVec)
{
	return Vec4(Math::Max(_AVec.x, _BVec.x), Math::Max(_AVec.y, _BVec.y), Math::Max(_AVec.z, _BVec.z), Math::Max(_AVec.w, _BVec.w));
}

const BFW::Math::Vec4 BFW::Math::Vec4::Pow(const Vec4& _Base, const Vec4& _Power)
{
	return Vec4(powf(_Base.x, _Power.x), powf(_Base.y, _Power.y), powf(_Base.z, _Power.z), powf(_Base.w, _Power.w));
}

const BFW::Math::Vec4 BFW::Math::Vec4::Exp(const Vec4& _Power)
{
	return Vec4(expf(_Power.x), expf(_Power.y), expf(_Power.z), expf(_Power.w));
}

const BFW::Math::Vec4 BFW::Math::Vec4::Reflect(const Vec4& _Vec, const Vec4& _Normal)
{
	return Vec4(Vec3(_Vec) - Vec3(_Normal) * 2.0f * Dot(_Vec, _Normal) / _Normal.Magnitude() / _Normal.Magnitude(), _Vec.w * _Normal.w);
}
