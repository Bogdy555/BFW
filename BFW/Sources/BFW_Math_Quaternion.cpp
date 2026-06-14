#include "../Headers/BFW.hpp"



BFW::Math::Quat::Quat() : r(0.0f), i(0.0f), j(0.0f), k(0.0f)
{

}

BFW::Math::Quat::Quat(const float _r, const float _i, const float _j, const float _k) : r(_r), i(_i), j(_j), k(_k)
{

}

BFW::Math::Quat::Quat(const float _Angle, const Vec3& _Axis) : r(cosf(_Angle / 2.0f)), i(sinf(_Angle / 2.0f) * _Axis.x), j(sinf(_Angle / 2.0f) * _Axis.y), k(sinf(_Angle / 2.0f) * _Axis.z)
{

}

BFW::Math::Quat::Quat(const Quat& _Other) : r(_Other.r), i(_Other.i), j(_Other.j), k(_Other.k)
{

}

BFW::Math::Quat::Quat(Quat&& _Other) noexcept : r(_Other.r), i(_Other.i), j(_Other.j), k(_Other.k)
{
	_Other.r = 0.0f;
	_Other.i = 0.0f;
	_Other.j = 0.0f;
	_Other.k = 0.0f;
}

BFW::Math::Quat::~Quat()
{

}

float* BFW::Math::Quat::Data()
{
	return &r;
}

const float* BFW::Math::Quat::Data() const
{
	return &r;
}

const float BFW::Math::Quat::Magnitude() const
{
	return sqrtf(r * r + i * i + j * j + k * k);
}

BFW::Math::Quat& BFW::Math::Quat::Normalize()
{
	*this /= Magnitude();

	return *this;
}

const BFW::Math::Quat BFW::Math::Quat::Normalized() const
{
	return *this / Magnitude();
}

BFW::Math::Quat& BFW::Math::Quat::Conjugate()
{
	*this = Quat(r, -i, -j, -k);

	return *this;
}

const BFW::Math::Quat BFW::Math::Quat::Conjugated() const
{
	return Quat(r, -i, -j, -k);
}

BFW::Math::Quat& BFW::Math::Quat::Inverse()
{
	*this = Conjugated() / (r * r + i * i + j * j + k * k);

	return *this;
}

const BFW::Math::Quat BFW::Math::Quat::Inversed() const
{
	return Conjugated() / (r * r + i * i + j * j + k * k);
}

const BFW::Math::Mat4 BFW::Math::Quat::GetMatrix() const
{
	Mat4 _Matrix;

	_Matrix[0][0] = 1.0f - 2.0f * (j * j + k * k);
	_Matrix[1][0] = 2.0f * (i * j - r * k);
	_Matrix[2][0] = 2.0f * (i * k + r * j);

	_Matrix[0][1] = 2.0f * (i * j + r * k);
	_Matrix[1][1] = 1.0f - 2.0f * (i * i + k * k);
	_Matrix[2][1] = 2.0f * (j * k - r * i);

	_Matrix[0][2] = 2.0f * (i * k - r * j);
	_Matrix[1][2] = 2.0f * (j * k + r * i);
	_Matrix[2][2] = 1.0f - 2.0f * (i * i + j * j);

	return _Matrix;
}

const BFW::Math::Quat& BFW::Math::Quat::operator+ () const
{
	return *this;
}

const BFW::Math::Quat BFW::Math::Quat::operator- () const
{
	return Quat(-r, -i, -j, -k);
}

const BFW::Math::Vec3 BFW::Math::Quat::operator* (const Vec3& _Vec) const
{
	Quat _Result = *this * Quat(0.0f, _Vec.x, _Vec.y, _Vec.z) * Conjugated();

	return Vec3(_Result.i, _Result.j, _Result.k);
}

const BFW::Math::Quat BFW::Math::Quat::operator+ (const Quat& _Other) const
{
	return Quat(r + _Other.r, i + _Other.i, j + _Other.j, k + _Other.k);
}

BFW::Math::Quat& BFW::Math::Quat::operator+= (const Quat& _Other)
{
	r += _Other.r;
	i += _Other.i;
	j += _Other.j;
	k += _Other.k;

	return *this;
}

const BFW::Math::Quat BFW::Math::Quat::operator+ (const float _Value) const
{
	return Quat(r + _Value, i, j, k);
}

BFW::Math::Quat& BFW::Math::Quat::operator+= (const float _Value)
{
	r += _Value;

	return *this;
}

const BFW::Math::Quat BFW::Math::Quat::operator- (const Quat& _Other) const
{
	return Quat(r - _Other.r, i - _Other.i, j - _Other.j, k - _Other.k);
}

BFW::Math::Quat& BFW::Math::Quat::operator-= (const Quat& _Other)
{
	r -= _Other.r;
	i -= _Other.i;
	j -= _Other.j;
	k -= _Other.k;

	return *this;
}

const BFW::Math::Quat BFW::Math::Quat::operator- (const float _Value) const
{
	return Quat(r - _Value, i, j, k);
}

BFW::Math::Quat& BFW::Math::Quat::operator-= (const float _Value)
{
	r -= _Value;

	return *this;
}

const BFW::Math::Quat BFW::Math::Quat::operator* (const Quat& _Other) const
{
	return Quat
	(
		r * _Other.r - i * _Other.i - j * _Other.j - k * _Other.k,
		r * _Other.i + i * _Other.r + j * _Other.k - k * _Other.j,
		r * _Other.j - i * _Other.k + j * _Other.r + k * _Other.i,
		r * _Other.k + i * _Other.j - j * _Other.i + k * _Other.r
	);
}

BFW::Math::Quat& BFW::Math::Quat::operator*= (const Quat& _Other)
{
	*this = Quat
	(
		r * _Other.r - i * _Other.i - j * _Other.j - k * _Other.k,
		r * _Other.i + i * _Other.r + j * _Other.k - k * _Other.j,
		r * _Other.j - i * _Other.k + j * _Other.r + k * _Other.i,
		r * _Other.k + i * _Other.j - j * _Other.i + k * _Other.r
	);

	return *this;
}

const BFW::Math::Quat BFW::Math::Quat::operator* (const float _Value) const
{
	return Quat(r * _Value, i * _Value, j * _Value, k * _Value);
}

BFW::Math::Quat& BFW::Math::Quat::operator*= (const float _Value)
{
	r *= _Value;
	i *= _Value;
	j *= _Value;
	k *= _Value;

	return *this;
}

const BFW::Math::Quat BFW::Math::Quat::operator/ (const float _Value) const
{
	return Quat(r / _Value, i / _Value, j / _Value, k / _Value);
}

BFW::Math::Quat& BFW::Math::Quat::operator/= (const float _Value)
{
	r /= _Value;
	i /= _Value;
	j /= _Value;
	k /= _Value;

	return *this;
}

const bool BFW::Math::Quat::operator== (const Quat& _Other) const
{
	return r == _Other.r && i == _Other.i && j == _Other.j && k == _Other.k;
}

const bool BFW::Math::Quat::operator!= (const Quat& _Other) const
{
	return r != _Other.r || i != _Other.i || j != _Other.j || k != _Other.k;
}

float& BFW::Math::Quat::operator[] (const size_t _Index)
{
	return Data()[_Index];
}

const float& BFW::Math::Quat::operator[] (const size_t _Index) const
{
	return Data()[_Index];
}

BFW::Math::Quat& BFW::Math::Quat::operator= (const Quat& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	r = _Other.r;
	i = _Other.i;
	j = _Other.j;
	k = _Other.k;

	return *this;
}

BFW::Math::Quat& BFW::Math::Quat::operator= (Quat&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	r = _Other.r;
	i = _Other.i;
	j = _Other.j;
	k = _Other.k;

	_Other.r = 0.0f;
	_Other.i = 0.0f;
	_Other.j = 0.0f;
	_Other.k = 0.0f;

	return *this;
}

const BFW::Math::Quat BFW::Math::Quat::Mix(const Quat& _AQuat, const Quat& _BQuat, const float _Percentage)
{
	return _AQuat * Pow(_AQuat.Inversed() * _BQuat, _Percentage);
}

const BFW::Math::Quat BFW::Math::Quat::Pow(const Quat& _Base, const float _Power)
{
	return Quat(_Power * acosf(_Base.r) * 2.0f, Vec3(_Base.i / sinf(acosf(_Base.r)), _Base.j / sinf(acosf(_Base.r)), _Base.k / sinf(acosf(_Base.r))));
}
