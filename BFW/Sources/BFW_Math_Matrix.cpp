#include "../Headers/BFW.hpp"



BFW::Math::Mat2::Mat2() : Matrix()
{
	Matrix[0][0] = 1.0f; Matrix[1][0] = 0.0f;
	Matrix[0][1] = 0.0f; Matrix[1][1] = 1.0f;
}

BFW::Math::Mat2::Mat2(const Mat2& _Other) : Matrix()
{
	Matrix[0][0] = _Other[0][0]; Matrix[1][0] = _Other[1][0];
	Matrix[0][1] = _Other[0][1]; Matrix[1][1] = _Other[1][1];
}

BFW::Math::Mat2::Mat2(Mat2&& _Other) noexcept : Matrix()
{
	Matrix[0][0] = _Other[0][0]; Matrix[1][0] = _Other[1][0];
	Matrix[0][1] = _Other[0][1]; Matrix[1][1] = _Other[1][1];

	_Other[0][0] = 1.0f; _Other[1][0] = 0.0f;
	_Other[0][1] = 0.0f; _Other[1][1] = 1.0f;
}

BFW::Math::Mat2::Mat2(const Vec2& _Ox, const Vec2& _Oy)
{
	Matrix[0][0] = _Ox.x; Matrix[1][0] = _Oy.x;
	Matrix[0][1] = _Ox.y; Matrix[1][1] = _Oy.y;
}

BFW::Math::Mat2::~Mat2()
{

}

float* BFW::Math::Mat2::Data()
{
	return &Matrix[0][0];
}

const float* BFW::Math::Mat2::Data() const
{
	return &Matrix[0][0];
}

const float BFW::Math::Mat2::Determinant() const
{
	return
		Matrix[0][0] * Matrix[1][1] -
		Matrix[1][0] * Matrix[0][1];
}

const float BFW::Math::Mat2::Trace() const
{
	return Matrix[0][0] + Matrix[1][1];
}

BFW::Math::Mat2& BFW::Math::Mat2::Transpose()
{
	float _Aux = 0.0f;

	_Aux = Matrix[1][0];
	Matrix[1][0] = Matrix[0][1];
	Matrix[0][1] = _Aux;

	return *this;
}

const BFW::Math::Mat2 BFW::Math::Mat2::Transposed() const
{
	return Mat2(*this).Transpose();
}

BFW::Math::Mat2& BFW::Math::Mat2::Inverse()
{
	Mat2 _Matrix;

	_Matrix[0][0] = Matrix[1][1];

	_Matrix[1][0] = -Matrix[1][0];

	_Matrix[0][1] = -Matrix[0][1];

	_Matrix[1][1] = Matrix[0][0];

	_Matrix /= Determinant();

	*this = _Matrix;

	return *this;
}

const BFW::Math::Mat2 BFW::Math::Mat2::Inversed() const
{
	return Mat2(*this).Inverse();
}

const BFW::Math::Mat2& BFW::Math::Mat2::operator+ () const
{
	return *this;
}

const BFW::Math::Mat2 BFW::Math::Mat2::operator- () const
{
	Mat2 _Matrix;

	_Matrix[0][0] = -Matrix[0][0]; _Matrix[1][0] = -Matrix[1][0];
	_Matrix[0][1] = -Matrix[0][1]; _Matrix[1][1] = -Matrix[1][1];

	return _Matrix;
}

const BFW::Math::Vec2 BFW::Math::Mat2::operator* (const Vec2& _Vec) const
{
	return Vec2
	(
		Matrix[0][0] * _Vec.x + Matrix[1][0] * _Vec.y,
		Matrix[0][1] * _Vec.x + Matrix[1][1] * _Vec.y
	);
}

const BFW::Math::Mat2 BFW::Math::Mat2::operator+ (const Mat2& _Other) const
{
	Mat2 _Matrix(*this);

	_Matrix[0][0] += _Other[0][0]; _Matrix[1][0] += _Other[1][0];
	_Matrix[0][1] += _Other[0][1]; _Matrix[1][1] += _Other[1][1];

	return _Matrix;
}

BFW::Math::Mat2& BFW::Math::Mat2::operator+= (const Mat2& _Other)
{
	Matrix[0][0] += _Other[0][0]; Matrix[1][0] += _Other[1][0];
	Matrix[0][1] += _Other[0][1]; Matrix[1][1] += _Other[1][1];

	return *this;
}

const BFW::Math::Mat2 BFW::Math::Mat2::operator+ (const float _Value) const
{
	Mat2 _Matrix(*this);

	_Matrix[0][0] += _Value; _Matrix[1][0] += _Value;
	_Matrix[0][1] += _Value; _Matrix[1][1] += _Value;

	return _Matrix;
}

BFW::Math::Mat2& BFW::Math::Mat2::operator+= (const float _Value)
{
	Matrix[0][0] += _Value; Matrix[1][0] += _Value;
	Matrix[0][1] += _Value; Matrix[1][1] += _Value;

	return *this;
}

const BFW::Math::Mat2 BFW::Math::Mat2::operator- (const Mat2& _Other) const
{
	Mat2 _Matrix(*this);

	_Matrix[0][0] -= _Other[0][0]; _Matrix[1][0] -= _Other[1][0];
	_Matrix[0][1] -= _Other[0][1]; _Matrix[1][1] -= _Other[1][1];

	return _Matrix;
}

BFW::Math::Mat2& BFW::Math::Mat2::operator-= (const Mat2& _Other)
{
	Matrix[0][0] -= _Other[0][0]; Matrix[1][0] -= _Other[1][0];
	Matrix[0][1] -= _Other[0][1]; Matrix[1][1] -= _Other[1][1];

	return *this;
}

const BFW::Math::Mat2 BFW::Math::Mat2::operator- (const float _Value) const
{
	Mat2 _Matrix(*this);

	_Matrix[0][0] -= _Value; _Matrix[1][0] -= _Value;
	_Matrix[0][1] -= _Value; _Matrix[1][1] -= _Value;

	return _Matrix;
}

BFW::Math::Mat2& BFW::Math::Mat2::operator-= (const float _Value)
{
	Matrix[0][0] -= _Value; Matrix[1][0] -= _Value;
	Matrix[0][1] -= _Value; Matrix[1][1] -= _Value;

	return *this;
}

const BFW::Math::Mat2 BFW::Math::Mat2::operator* (const Mat2& _Other) const
{
	Mat2 _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Other[0][0] + Matrix[1][0] * _Other[0][1];
	_Matrix[1][0] = Matrix[0][0] * _Other[1][0] + Matrix[1][0] * _Other[1][1];

	_Matrix[0][1] = Matrix[0][1] * _Other[0][0] + Matrix[1][1] * _Other[0][1];
	_Matrix[1][1] = Matrix[0][1] * _Other[1][0] + Matrix[1][1] * _Other[1][1];

	return _Matrix;
}

BFW::Math::Mat2& BFW::Math::Mat2::operator*= (const Mat2& _Other)
{
	Mat2 _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Other[0][0] + Matrix[1][0] * _Other[0][1];
	_Matrix[1][0] = Matrix[0][0] * _Other[1][0] + Matrix[1][0] * _Other[1][1];

	_Matrix[0][1] = Matrix[0][1] * _Other[0][0] + Matrix[1][1] * _Other[0][1];
	_Matrix[1][1] = Matrix[0][1] * _Other[1][0] + Matrix[1][1] * _Other[1][1];

	*this = _Matrix;

	return *this;
}

const BFW::Math::Mat2 BFW::Math::Mat2::operator* (const float _Value) const
{
	Mat2 _Matrix(*this);

	_Matrix[0][0] *= _Value; _Matrix[1][0] *= _Value;
	_Matrix[0][1] *= _Value; _Matrix[1][1] *= _Value;

	return _Matrix;
}

BFW::Math::Mat2& BFW::Math::Mat2::operator*= (const float _Value)
{
	Matrix[0][0] *= _Value; Matrix[1][0] *= _Value;
	Matrix[0][1] *= _Value; Matrix[1][1] *= _Value;

	return *this;
}

const BFW::Math::Mat2 BFW::Math::Mat2::operator/ (const float _Value) const
{
	Mat2 _Matrix(*this);

	_Matrix[0][0] /= _Value; _Matrix[1][0] /= _Value;
	_Matrix[0][1] /= _Value; _Matrix[1][1] /= _Value;

	return _Matrix;
}

BFW::Math::Mat2& BFW::Math::Mat2::operator/= (const float _Value)
{
	Matrix[0][0] /= _Value; Matrix[1][0] /= _Value;
	Matrix[0][1] /= _Value; Matrix[1][1] /= _Value;

	return *this;
}

const bool BFW::Math::Mat2::operator== (const Mat2& _Other) const
{
	return
		Matrix[0][0] == _Other[0][0] && Matrix[1][0] == _Other[1][0] &&
		Matrix[0][1] == _Other[0][1] && Matrix[1][1] == _Other[1][1];
}

const bool BFW::Math::Mat2::operator!= (const Mat2& _Other) const
{
	return
		Matrix[0][0] != _Other[0][0] || Matrix[1][0] != _Other[1][0] ||
		Matrix[0][1] != _Other[0][1] || Matrix[1][1] != _Other[1][1];
}

float* BFW::Math::Mat2::operator[] (const size_t _Index)
{
	return Matrix[_Index].Data();
}

const float* BFW::Math::Mat2::operator[] (const size_t _Index) const
{
	return Matrix[_Index].Data();
}

BFW::Math::Mat2& BFW::Math::Mat2::operator= (const Mat2& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Matrix[0][0] = _Other[0][0]; Matrix[1][0] = _Other[1][0];
	Matrix[0][1] = _Other[0][1]; Matrix[1][1] = _Other[1][1];

	return *this;
}

BFW::Math::Mat2& BFW::Math::Mat2::operator= (Mat2&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Matrix[0][0] = _Other[0][0]; Matrix[1][0] = _Other[1][0];
	Matrix[0][1] = _Other[0][1]; Matrix[1][1] = _Other[1][1];

	_Other[0][0] = 1.0f; _Other[1][0] = 0.0f;
	_Other[0][1] = 0.0f; _Other[1][1] = 1.0f;

	return *this;
}

const BFW::Math::Mat2 BFW::Math::Mat2::GetFill(const float _Value)
{
	Mat2 _Matrix;

	_Matrix[0][0] = _Value; _Matrix[1][0] = _Value;
	_Matrix[0][1] = _Value; _Matrix[1][1] = _Value;

	return _Matrix;
}

const BFW::Math::Mat2 BFW::Math::Mat2::GetRotation(const float _Angle)
{
	Mat2 _Matrix;

	float _Sin = sinf(_Angle);
	float _Cos = cosf(_Angle);

	_Matrix[0][0] = _Cos;
	_Matrix[1][0] = -_Sin;

	_Matrix[0][1] = _Sin;
	_Matrix[1][1] = _Cos;

	return _Matrix;
}

const BFW::Math::Mat2 BFW::Math::Mat2::GetScale(const Vec2& _Size)
{
	Mat2 _Matrix;

	_Matrix[0][0] = _Size.x;
	_Matrix[1][1] = _Size.y;

	return _Matrix;
}

const BFW::Math::Mat2 BFW::Math::Mat2::GetShear(const float _Value, const size_t _ShearedAxis, const size_t _ShearByAxis)
{
	Mat2 _Matrix;

	_Matrix[_ShearByAxis][_ShearedAxis] = _Value;

	return _Matrix;
}

const BFW::Math::Mat2 BFW::Math::Mat2::GetFlip(const Vec2& _Normal)
{
	Mat2 _Matrix;

	_Matrix[0][0] = _Normal.x * _Normal.x - _Normal.y * _Normal.y;
	_Matrix[1][0] = 2.0f * _Normal.x * _Normal.y;

	_Matrix[0][1] = 2.0f * _Normal.x * _Normal.y;
	_Matrix[1][1] = _Normal.y * _Normal.y - _Normal.x * _Normal.x;

	_Matrix /= _Normal.x * _Normal.x + _Normal.y * _Normal.y;

	return _Matrix;
}



BFW::Math::Mat3::Mat3() : Matrix()
{
	Matrix[0][0] = 1.0f; Matrix[1][0] = 0.0f; Matrix[2][0] = 0.0f;
	Matrix[0][1] = 0.0f; Matrix[1][1] = 1.0f; Matrix[2][1] = 0.0f;
	Matrix[0][2] = 0.0f; Matrix[1][2] = 0.0f; Matrix[2][2] = 1.0f;
}

BFW::Math::Mat3::Mat3(const Mat3& _Other) : Matrix()
{
	Matrix[0][0] = _Other[0][0]; Matrix[1][0] = _Other[1][0]; Matrix[2][0] = _Other[2][0];
	Matrix[0][1] = _Other[0][1]; Matrix[1][1] = _Other[1][1]; Matrix[2][1] = _Other[2][1];
	Matrix[0][2] = _Other[0][2]; Matrix[1][2] = _Other[1][2]; Matrix[2][2] = _Other[2][2];
}

BFW::Math::Mat3::Mat3(Mat3&& _Other) noexcept : Matrix()
{
	Matrix[0][0] = _Other[0][0]; Matrix[1][0] = _Other[1][0]; Matrix[2][0] = _Other[2][0];
	Matrix[0][1] = _Other[0][1]; Matrix[1][1] = _Other[1][1]; Matrix[2][1] = _Other[2][1];
	Matrix[0][2] = _Other[0][2]; Matrix[1][2] = _Other[1][2]; Matrix[2][2] = _Other[2][2];

	_Other[0][0] = 1.0f; _Other[1][0] = 0.0f; _Other[2][0] = 0.0f;
	_Other[0][1] = 0.0f; _Other[1][1] = 1.0f; _Other[2][1] = 0.0f;
	_Other[0][2] = 0.0f; _Other[1][2] = 0.0f; _Other[2][2] = 1.0f;
}

BFW::Math::Mat3::Mat3(const Vec3& _Ox, const Vec3& _Oy, const Vec3& _Oz)
{
	Matrix[0][0] = _Ox.x; Matrix[1][0] = _Oy.x; Matrix[2][0] = _Oz.x;
	Matrix[0][1] = _Ox.y; Matrix[1][1] = _Oy.y; Matrix[2][1] = _Oz.y;
	Matrix[0][2] = _Ox.z; Matrix[1][2] = _Oy.z; Matrix[2][2] = _Oz.z;
}

BFW::Math::Mat3::Mat3(const Mat2& _Other) : Matrix()
{
	Matrix[0][0] = _Other[0][0]; Matrix[1][0] = _Other[1][0]; Matrix[2][0] = 0.0f;
	Matrix[0][1] = _Other[0][1]; Matrix[1][1] = _Other[1][1]; Matrix[2][1] = 0.0f;
	Matrix[0][2] = 0.0f; Matrix[1][2] = 0.0f; Matrix[2][2] = 1.0f;
}

BFW::Math::Mat3::~Mat3()
{

}

BFW::Math::Mat3::operator const BFW::Math::Mat2 () const
{
	Mat2 _Matrix;

	_Matrix[0][0] = Matrix[0][0]; _Matrix[1][0] = Matrix[1][0];
	_Matrix[0][1] = Matrix[0][1]; _Matrix[1][1] = Matrix[1][1];

	return _Matrix;
}

float* BFW::Math::Mat3::Data()
{
	return &Matrix[0][0];
}

const float* BFW::Math::Mat3::Data() const
{
	return &Matrix[0][0];
}

const float BFW::Math::Mat3::Determinant() const
{
	return
		Matrix[0][0] * Matrix[1][1] * Matrix[2][2] +
		Matrix[2][0] * Matrix[0][1] * Matrix[1][2] +
		Matrix[1][0] * Matrix[2][1] * Matrix[0][2] -
		Matrix[2][0] * Matrix[1][1] * Matrix[0][2] -
		Matrix[0][0] * Matrix[2][1] * Matrix[1][2] -
		Matrix[1][0] * Matrix[0][1] * Matrix[2][2];
}

const float BFW::Math::Mat3::Trace() const
{
	return Matrix[0][0] + Matrix[1][1] + Matrix[2][2];
}

BFW::Math::Mat3& BFW::Math::Mat3::Transpose()
{
	float _Aux = 0.0f;

	_Aux = Matrix[1][0];
	Matrix[1][0] = Matrix[0][1];
	Matrix[0][1] = _Aux;

	_Aux = Matrix[2][0];
	Matrix[2][0] = Matrix[0][2];
	Matrix[0][2] = _Aux;

	_Aux = Matrix[2][1];
	Matrix[2][1] = Matrix[1][2];
	Matrix[1][2] = _Aux;

	return *this;
}

const BFW::Math::Mat3 BFW::Math::Mat3::Transposed() const
{
	return Mat3(*this).Transpose();
}

BFW::Math::Mat3& BFW::Math::Mat3::Inverse()
{
	Mat3 _Matrix;

	Mat2 _DetMat;

	_DetMat[0][0] = Matrix[1][1]; _DetMat[1][0] = Matrix[2][1];
	_DetMat[0][1] = Matrix[1][2]; _DetMat[1][1] = Matrix[2][2];

	_Matrix[0][0] = _DetMat.Determinant();

	_DetMat[0][0] = Matrix[1][0]; _DetMat[1][0] = Matrix[2][0];
	_DetMat[0][1] = Matrix[1][2]; _DetMat[1][1] = Matrix[2][2];

	_Matrix[1][0] = -_DetMat.Determinant();

	_DetMat[0][0] = Matrix[1][0]; _DetMat[1][0] = Matrix[2][0];
	_DetMat[0][1] = Matrix[1][1]; _DetMat[1][1] = Matrix[2][1];

	_Matrix[2][0] = _DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][1]; _DetMat[1][0] = Matrix[2][1];
	_DetMat[0][1] = Matrix[0][2]; _DetMat[1][1] = Matrix[2][2];

	_Matrix[0][1] = -_DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][0]; _DetMat[1][0] = Matrix[2][0];
	_DetMat[0][1] = Matrix[0][2]; _DetMat[1][1] = Matrix[2][2];

	_Matrix[1][1] = _DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][0]; _DetMat[1][0] = Matrix[2][0];
	_DetMat[0][1] = Matrix[0][1]; _DetMat[1][1] = Matrix[2][1];

	_Matrix[2][1] = -_DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][1]; _DetMat[1][0] = Matrix[1][1];
	_DetMat[0][1] = Matrix[0][2]; _DetMat[1][1] = Matrix[1][2];

	_Matrix[0][2] = _DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][0]; _DetMat[1][0] = Matrix[1][0];
	_DetMat[0][1] = Matrix[0][2]; _DetMat[1][1] = Matrix[1][2];

	_Matrix[1][2] = -_DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][0]; _DetMat[1][0] = Matrix[1][0];
	_DetMat[0][1] = Matrix[0][1]; _DetMat[1][1] = Matrix[1][1];

	_Matrix[2][2] = _DetMat.Determinant();

	_Matrix /= Determinant();

	*this = _Matrix;

	return *this;
}

const BFW::Math::Mat3 BFW::Math::Mat3::Inversed() const
{
	return Mat3(*this).Inverse();
}

const BFW::Math::Mat3& BFW::Math::Mat3::operator+ () const
{
	return *this;
}

const BFW::Math::Mat3 BFW::Math::Mat3::operator- () const
{
	Mat3 _Matrix;

	_Matrix[0][0] = -Matrix[0][0]; _Matrix[1][0] = -Matrix[1][0]; _Matrix[2][0] = -Matrix[2][0];
	_Matrix[0][1] = -Matrix[0][1]; _Matrix[1][1] = -Matrix[1][1]; _Matrix[2][1] = -Matrix[2][1];
	_Matrix[0][2] = -Matrix[0][2]; _Matrix[1][2] = -Matrix[1][2]; _Matrix[2][2] = -Matrix[2][2];

	return _Matrix;
}

const BFW::Math::Vec3 BFW::Math::Mat3::operator* (const Vec3& _Vec) const
{
	return Vec3
	(
		Matrix[0][0] * _Vec.x + Matrix[1][0] * _Vec.y + Matrix[2][0] * _Vec.z,
		Matrix[0][1] * _Vec.x + Matrix[1][1] * _Vec.y + Matrix[2][1] * _Vec.z,
		Matrix[0][2] * _Vec.x + Matrix[1][2] * _Vec.y + Matrix[2][2] * _Vec.z
	);
}

const BFW::Math::Mat3 BFW::Math::Mat3::operator+ (const Mat3& _Other) const
{
	Mat3 _Matrix(*this);

	_Matrix[0][0] += _Other[0][0]; _Matrix[1][0] += _Other[1][0]; _Matrix[2][0] += _Other[2][0];
	_Matrix[0][1] += _Other[0][1]; _Matrix[1][1] += _Other[1][1]; _Matrix[2][1] += _Other[2][1];
	_Matrix[0][2] += _Other[0][2]; _Matrix[1][2] += _Other[1][2]; _Matrix[2][2] += _Other[2][2];

	return _Matrix;
}

BFW::Math::Mat3& BFW::Math::Mat3::operator+= (const Mat3& _Other)
{
	Matrix[0][0] += _Other[0][0]; Matrix[1][0] += _Other[1][0]; Matrix[2][0] += _Other[2][0];
	Matrix[0][1] += _Other[0][1]; Matrix[1][1] += _Other[1][1]; Matrix[2][1] += _Other[2][1];
	Matrix[0][2] += _Other[0][2]; Matrix[1][2] += _Other[1][2]; Matrix[2][2] += _Other[2][2];

	return *this;
}

const BFW::Math::Mat3 BFW::Math::Mat3::operator+ (const float _Value) const
{
	Mat3 _Matrix(*this);

	_Matrix[0][0] += _Value; _Matrix[1][0] += _Value; _Matrix[2][0] += _Value;
	_Matrix[0][1] += _Value; _Matrix[1][1] += _Value; _Matrix[2][1] += _Value;
	_Matrix[0][2] += _Value; _Matrix[1][2] += _Value; _Matrix[2][2] += _Value;

	return _Matrix;
}

BFW::Math::Mat3& BFW::Math::Mat3::operator+= (const float _Value)
{
	Matrix[0][0] += _Value; Matrix[1][0] += _Value; Matrix[2][0] += _Value;
	Matrix[0][1] += _Value; Matrix[1][1] += _Value; Matrix[2][1] += _Value;
	Matrix[0][2] += _Value; Matrix[1][2] += _Value; Matrix[2][2] += _Value;

	return *this;
}

const BFW::Math::Mat3 BFW::Math::Mat3::operator- (const Mat3& _Other) const
{
	Mat3 _Matrix(*this);

	_Matrix[0][0] -= _Other[0][0]; _Matrix[1][0] -= _Other[1][0]; _Matrix[2][0] -= _Other[2][0];
	_Matrix[0][1] -= _Other[0][1]; _Matrix[1][1] -= _Other[1][1]; _Matrix[2][1] -= _Other[2][1];
	_Matrix[0][2] -= _Other[0][2]; _Matrix[1][2] -= _Other[1][2]; _Matrix[2][2] -= _Other[2][2];

	return _Matrix;
}

BFW::Math::Mat3& BFW::Math::Mat3::operator-= (const Mat3& _Other)
{
	Matrix[0][0] -= _Other[0][0]; Matrix[1][0] -= _Other[1][0]; Matrix[2][0] -= _Other[2][0];
	Matrix[0][1] -= _Other[0][1]; Matrix[1][1] -= _Other[1][1]; Matrix[2][1] -= _Other[2][1];
	Matrix[0][2] -= _Other[0][2]; Matrix[1][2] -= _Other[1][2]; Matrix[2][2] -= _Other[2][2];

	return *this;
}

const BFW::Math::Mat3 BFW::Math::Mat3::operator- (const float _Value) const
{
	Mat3 _Matrix(*this);

	_Matrix[0][0] -= _Value; _Matrix[1][0] -= _Value; _Matrix[2][0] -= _Value;
	_Matrix[0][1] -= _Value; _Matrix[1][1] -= _Value; _Matrix[2][1] -= _Value;
	_Matrix[0][2] -= _Value; _Matrix[1][2] -= _Value; _Matrix[2][2] -= _Value;

	return _Matrix;
}

BFW::Math::Mat3& BFW::Math::Mat3::operator-= (const float _Value)
{
	Matrix[0][0] -= _Value; Matrix[1][0] -= _Value; Matrix[2][0] -= _Value;
	Matrix[0][1] -= _Value; Matrix[1][1] -= _Value; Matrix[2][1] -= _Value;
	Matrix[0][2] -= _Value; Matrix[1][2] -= _Value; Matrix[2][2] -= _Value;

	return *this;
}

const BFW::Math::Mat3 BFW::Math::Mat3::operator* (const Mat3& _Other) const
{
	Mat3 _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Other[0][0] + Matrix[1][0] * _Other[0][1] + Matrix[2][0] * _Other[0][2];
	_Matrix[1][0] = Matrix[0][0] * _Other[1][0] + Matrix[1][0] * _Other[1][1] + Matrix[2][0] * _Other[1][2];
	_Matrix[2][0] = Matrix[0][0] * _Other[2][0] + Matrix[1][0] * _Other[2][1] + Matrix[2][0] * _Other[2][2];

	_Matrix[0][1] = Matrix[0][1] * _Other[0][0] + Matrix[1][1] * _Other[0][1] + Matrix[2][1] * _Other[0][2];
	_Matrix[1][1] = Matrix[0][1] * _Other[1][0] + Matrix[1][1] * _Other[1][1] + Matrix[2][1] * _Other[1][2];
	_Matrix[2][1] = Matrix[0][1] * _Other[2][0] + Matrix[1][1] * _Other[2][1] + Matrix[2][1] * _Other[2][2];

	_Matrix[0][2] = Matrix[0][2] * _Other[0][0] + Matrix[1][2] * _Other[0][1] + Matrix[2][2] * _Other[0][2];
	_Matrix[1][2] = Matrix[0][2] * _Other[1][0] + Matrix[1][2] * _Other[1][1] + Matrix[2][2] * _Other[1][2];
	_Matrix[2][2] = Matrix[0][2] * _Other[2][0] + Matrix[1][2] * _Other[2][1] + Matrix[2][2] * _Other[2][2];

	return _Matrix;
}

BFW::Math::Mat3& BFW::Math::Mat3::operator*= (const Mat3& _Other)
{
	Mat3 _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Other[0][0] + Matrix[1][0] * _Other[0][1] + Matrix[2][0] * _Other[0][2];
	_Matrix[1][0] = Matrix[0][0] * _Other[1][0] + Matrix[1][0] * _Other[1][1] + Matrix[2][0] * _Other[1][2];
	_Matrix[2][0] = Matrix[0][0] * _Other[2][0] + Matrix[1][0] * _Other[2][1] + Matrix[2][0] * _Other[2][2];

	_Matrix[0][1] = Matrix[0][1] * _Other[0][0] + Matrix[1][1] * _Other[0][1] + Matrix[2][1] * _Other[0][2];
	_Matrix[1][1] = Matrix[0][1] * _Other[1][0] + Matrix[1][1] * _Other[1][1] + Matrix[2][1] * _Other[1][2];
	_Matrix[2][1] = Matrix[0][1] * _Other[2][0] + Matrix[1][1] * _Other[2][1] + Matrix[2][1] * _Other[2][2];

	_Matrix[0][2] = Matrix[0][2] * _Other[0][0] + Matrix[1][2] * _Other[0][1] + Matrix[2][2] * _Other[0][2];
	_Matrix[1][2] = Matrix[0][2] * _Other[1][0] + Matrix[1][2] * _Other[1][1] + Matrix[2][2] * _Other[1][2];
	_Matrix[2][2] = Matrix[0][2] * _Other[2][0] + Matrix[1][2] * _Other[2][1] + Matrix[2][2] * _Other[2][2];

	*this = _Matrix;

	return *this;
}

const BFW::Math::Mat3 BFW::Math::Mat3::operator* (const float _Value) const
{
	Mat3 _Matrix(*this);

	_Matrix[0][0] *= _Value; _Matrix[1][0] *= _Value; _Matrix[2][0] *= _Value;
	_Matrix[0][1] *= _Value; _Matrix[1][1] *= _Value; _Matrix[2][1] *= _Value;
	_Matrix[0][2] *= _Value; _Matrix[1][2] *= _Value; _Matrix[2][2] *= _Value;

	return _Matrix;
}

BFW::Math::Mat3& BFW::Math::Mat3::operator*= (const float _Value)
{
	Matrix[0][0] *= _Value; Matrix[1][0] *= _Value; Matrix[2][0] *= _Value;
	Matrix[0][1] *= _Value; Matrix[1][1] *= _Value; Matrix[2][1] *= _Value;
	Matrix[0][2] *= _Value; Matrix[1][2] *= _Value; Matrix[2][2] *= _Value;

	return *this;
}

const BFW::Math::Mat3 BFW::Math::Mat3::operator/ (const float _Value) const
{
	Mat3 _Matrix(*this);

	_Matrix[0][0] /= _Value; _Matrix[1][0] /= _Value; _Matrix[2][0] /= _Value;
	_Matrix[0][1] /= _Value; _Matrix[1][1] /= _Value; _Matrix[2][1] /= _Value;
	_Matrix[0][2] /= _Value; _Matrix[1][2] /= _Value; _Matrix[2][2] /= _Value;

	return _Matrix;
}

BFW::Math::Mat3& BFW::Math::Mat3::operator/= (const float _Value)
{
	Matrix[0][0] /= _Value; Matrix[1][0] /= _Value; Matrix[2][0] /= _Value;
	Matrix[0][1] /= _Value; Matrix[1][1] /= _Value; Matrix[2][1] /= _Value;
	Matrix[0][2] /= _Value; Matrix[1][2] /= _Value; Matrix[2][2] /= _Value;

	return *this;
}

const bool BFW::Math::Mat3::operator== (const Mat3& _Other) const
{
	return
		Matrix[0][0] == _Other[0][0] && Matrix[1][0] == _Other[1][0] && Matrix[2][0] == _Other[2][0] &&
		Matrix[0][1] == _Other[0][1] && Matrix[1][1] == _Other[1][1] && Matrix[2][1] == _Other[2][1] &&
		Matrix[0][2] == _Other[0][2] && Matrix[1][2] == _Other[1][2] && Matrix[2][2] == _Other[2][2];
}

const bool BFW::Math::Mat3::operator!= (const Mat3& _Other) const
{
	return
		Matrix[0][0] != _Other[0][0] || Matrix[1][0] != _Other[1][0] || Matrix[2][0] != _Other[2][0] ||
		Matrix[0][1] != _Other[0][1] || Matrix[1][1] != _Other[1][1] || Matrix[2][1] != _Other[2][1] ||
		Matrix[0][2] != _Other[0][2] || Matrix[1][2] != _Other[1][2] || Matrix[2][2] != _Other[2][2];
}

float* BFW::Math::Mat3::operator[] (const size_t _Index)
{
	return Matrix[_Index].Data();
}

const float* BFW::Math::Mat3::operator[] (const size_t _Index) const
{
	return Matrix[_Index].Data();
}

BFW::Math::Mat3& BFW::Math::Mat3::operator= (const Mat3& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Matrix[0][0] = _Other[0][0]; Matrix[1][0] = _Other[1][0]; Matrix[2][0] = _Other[2][0];
	Matrix[0][1] = _Other[0][1]; Matrix[1][1] = _Other[1][1]; Matrix[2][1] = _Other[2][1];
	Matrix[0][2] = _Other[0][2]; Matrix[1][2] = _Other[1][2]; Matrix[2][2] = _Other[2][2];

	return *this;
}

BFW::Math::Mat3& BFW::Math::Mat3::operator= (Mat3&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Matrix[0][0] = _Other[0][0]; Matrix[1][0] = _Other[1][0]; Matrix[2][0] = _Other[2][0];
	Matrix[0][1] = _Other[0][1]; Matrix[1][1] = _Other[1][1]; Matrix[2][1] = _Other[2][1];
	Matrix[0][2] = _Other[0][2]; Matrix[1][2] = _Other[1][2]; Matrix[2][2] = _Other[2][2];

	_Other[0][0] = 1.0f; _Other[1][0] = 0.0f; _Other[2][0] = 0.0f;
	_Other[0][1] = 0.0f; _Other[1][1] = 1.0f; _Other[2][1] = 0.0f;
	_Other[0][2] = 0.0f; _Other[1][2] = 0.0f; _Other[2][2] = 1.0f;

	return *this;
}

const BFW::Math::Mat3 BFW::Math::Mat3::GetFill(const float _Value)
{
	Mat3 _Matrix;

	_Matrix[0][0] = _Value; _Matrix[1][0] = _Value; _Matrix[2][0] = _Value;
	_Matrix[0][1] = _Value; _Matrix[1][1] = _Value; _Matrix[2][1] = _Value;
	_Matrix[0][2] = _Value; _Matrix[1][2] = _Value; _Matrix[2][2] = _Value;

	return _Matrix;
}

const BFW::Math::Mat3 BFW::Math::Mat3::GetTranslation(const Vec2& _Position)
{
	Mat3 _Matrix;

	_Matrix[2][0] = _Position.x;
	_Matrix[2][1] = _Position.y;

	return _Matrix;
}

const BFW::Math::Mat3 BFW::Math::Mat3::GetRotation(const float _Angle, const Vec3& _Axis)
{
	Mat3 _Matrix;

	float _Sin = sinf(_Angle);
	float _Cos = cosf(_Angle);

	_Matrix[0][0] = _Cos + _Axis.x * _Axis.x * (1.0f - _Cos);
	_Matrix[1][0] = _Axis.x * _Axis.y * (1.0f - _Cos) - _Axis.z * _Sin;
	_Matrix[2][0] = _Axis.x * _Axis.z * (1.0f - _Cos) + _Axis.y * _Sin;

	_Matrix[0][1] = _Axis.y * _Axis.x * (1.0f - _Cos) + _Axis.z * _Sin;
	_Matrix[1][1] = _Cos + _Axis.y * _Axis.y * (1.0f - _Cos);
	_Matrix[2][1] = _Axis.y * _Axis.z * (1.0f - _Cos) - _Axis.x * _Sin;

	_Matrix[0][2] = _Axis.z * _Axis.x * (1.0f - _Cos) - _Axis.y * _Sin;
	_Matrix[1][2] = _Axis.z * _Axis.y * (1.0f - _Cos) + _Axis.x * _Sin;
	_Matrix[2][2] = _Cos + _Axis.z * _Axis.z * (1.0f - _Cos);

	return _Matrix;
}

const BFW::Math::Mat3 BFW::Math::Mat3::GetScale(const Vec3& _Size)
{
	Mat3 _Matrix;

	_Matrix[0][0] = _Size.x;
	_Matrix[1][1] = _Size.y;
	_Matrix[2][2] = _Size.z;

	return _Matrix;
}

const BFW::Math::Mat3 BFW::Math::Mat3::GetShear(const float _Value, const size_t _ShearedAxis, const size_t _ShearByAxis)
{
	Mat3 _Matrix;

	_Matrix[_ShearByAxis][_ShearedAxis] = _Value;

	return _Matrix;
}

const BFW::Math::Mat3 BFW::Math::Mat3::GetFlip(const Vec3& _Normal)
{
	Mat3 _Matrix;

	_Matrix[0][0] = 1.0f - 2.0f * _Normal.x * _Normal.x;
	_Matrix[1][0] = -2.0f * _Normal.x * _Normal.y;
	_Matrix[2][0] = -2.0f * _Normal.x * _Normal.z;

	_Matrix[0][1] = -2.0f * _Normal.y * _Normal.x;
	_Matrix[1][1] = 1.0f - 2.0f * _Normal.y * _Normal.y;
	_Matrix[2][1] = -2.0f * _Normal.y * _Normal.z;

	_Matrix[0][2] = -2.0f * _Normal.z * _Normal.x;
	_Matrix[1][2] = -2.0f * _Normal.z * _Normal.y;
	_Matrix[2][2] = 1.0f - 2.0f * _Normal.z * _Normal.z;

	return _Matrix;
}

const BFW::Math::Mat3 BFW::Math::Mat3::GetOrtho(const float _Left, const float _Right, const float _Bottom, const float _Top)
{
	Mat3 _Matrix;

	_Matrix[0][0] = 2.0f / (_Right - _Left);
	_Matrix[1][1] = 2.0f / (_Top - _Bottom);

	_Matrix[2][0] = (_Left + _Right) / (_Left - _Right);
	_Matrix[2][1] = (_Bottom + _Top) / (_Bottom - _Top);

	return _Matrix;
}



BFW::Math::Mat4::Mat4() : Matrix()
{
	Matrix[0][0] = 1.0f; Matrix[1][0] = 0.0f; Matrix[2][0] = 0.0f; Matrix[3][0] = 0.0f;
	Matrix[0][1] = 0.0f; Matrix[1][1] = 1.0f; Matrix[2][1] = 0.0f; Matrix[3][1] = 0.0f;
	Matrix[0][2] = 0.0f; Matrix[1][2] = 0.0f; Matrix[2][2] = 1.0f; Matrix[3][2] = 0.0f;
	Matrix[0][3] = 0.0f; Matrix[1][3] = 0.0f; Matrix[2][3] = 0.0f; Matrix[3][3] = 1.0f;
}

BFW::Math::Mat4::Mat4(const Mat4& _Other) : Matrix()
{
	Matrix[0][0] = _Other[0][0]; Matrix[1][0] = _Other[1][0]; Matrix[2][0] = _Other[2][0]; Matrix[3][0] = _Other[3][0];
	Matrix[0][1] = _Other[0][1]; Matrix[1][1] = _Other[1][1]; Matrix[2][1] = _Other[2][1]; Matrix[3][1] = _Other[3][1];
	Matrix[0][2] = _Other[0][2]; Matrix[1][2] = _Other[1][2]; Matrix[2][2] = _Other[2][2]; Matrix[3][2] = _Other[3][2];
	Matrix[0][3] = _Other[0][3]; Matrix[1][3] = _Other[1][3]; Matrix[2][3] = _Other[2][3]; Matrix[3][3] = _Other[3][3];
}

BFW::Math::Mat4::Mat4(Mat4&& _Other) noexcept : Matrix()
{
	Matrix[0][0] = _Other[0][0]; Matrix[1][0] = _Other[1][0]; Matrix[2][0] = _Other[2][0]; Matrix[3][0] = _Other[3][0];
	Matrix[0][1] = _Other[0][1]; Matrix[1][1] = _Other[1][1]; Matrix[2][1] = _Other[2][1]; Matrix[3][1] = _Other[3][1];
	Matrix[0][2] = _Other[0][2]; Matrix[1][2] = _Other[1][2]; Matrix[2][2] = _Other[2][2]; Matrix[3][2] = _Other[3][2];
	Matrix[0][3] = _Other[0][3]; Matrix[1][3] = _Other[1][3]; Matrix[2][3] = _Other[2][3]; Matrix[3][3] = _Other[3][3];

	_Other[0][0] = 1.0f; _Other[1][0] = 0.0f; _Other[2][0] = 0.0f; _Other[3][0] = 0.0f;
	_Other[0][1] = 0.0f; _Other[1][1] = 1.0f; _Other[2][1] = 0.0f; _Other[3][1] = 0.0f;
	_Other[0][2] = 0.0f; _Other[1][2] = 0.0f; _Other[2][2] = 1.0f; _Other[3][2] = 0.0f;
	_Other[0][3] = 0.0f; _Other[1][3] = 0.0f; _Other[2][3] = 0.0f; _Other[3][3] = 1.0f;
}

BFW::Math::Mat4::Mat4(const Vec3& _Ox, const Vec3& _Oy, const Vec3& _Oz)
{
	Matrix[0][0] = _Ox.x; Matrix[1][0] = _Oy.x; Matrix[2][0] = _Oz.x; Matrix[3][0] = 0.0f;
	Matrix[0][1] = _Ox.y; Matrix[1][1] = _Oy.y; Matrix[2][1] = _Oz.y; Matrix[3][1] = 0.0f;
	Matrix[0][2] = _Ox.z; Matrix[1][2] = _Oy.z; Matrix[2][2] = _Oz.z; Matrix[3][2] = 0.0f;
	Matrix[0][3] = 0.0f; Matrix[1][3] = 0.0f; Matrix[2][3] = 0.0f; Matrix[3][3] = 1.0f;
}

BFW::Math::Mat4::Mat4(const Mat2& _Other) : Matrix()
{
	Matrix[0][0] = _Other[0][0]; Matrix[1][0] = _Other[1][0]; Matrix[2][0] = 0.0f; Matrix[3][0] = 0.0f;
	Matrix[0][1] = _Other[0][1]; Matrix[1][1] = _Other[1][1]; Matrix[2][1] = 0.0f; Matrix[3][1] = 0.0f;
	Matrix[0][2] = 0.0f; Matrix[1][2] = 0.0f; Matrix[2][2] = 1.0f; Matrix[3][2] = 0.0f;
	Matrix[0][3] = 0.0f; Matrix[1][3] = 0.0f; Matrix[2][3] = 0.0f; Matrix[3][3] = 1.0f;
}

BFW::Math::Mat4::Mat4(const Mat3& _Other) : Matrix()
{
	Matrix[0][0] = _Other[0][0]; Matrix[1][0] = _Other[1][0]; Matrix[2][0] = _Other[2][0]; Matrix[3][0] = 0.0f;
	Matrix[0][1] = _Other[0][1]; Matrix[1][1] = _Other[1][1]; Matrix[2][1] = _Other[2][1]; Matrix[3][1] = 0.0f;
	Matrix[0][2] = _Other[0][2]; Matrix[1][2] = _Other[1][2]; Matrix[2][2] = _Other[2][2]; Matrix[3][2] = 0.0f;
	Matrix[0][3] = 0.0f; Matrix[1][3] = 0.0f; Matrix[2][3] = 0.0f; Matrix[3][3] = 1.0f;
}

BFW::Math::Mat4::~Mat4()
{

}

BFW::Math::Mat4::operator const BFW::Math::Mat2 () const
{
	Mat2 _Matrix;

	_Matrix[0][0] = Matrix[0][0]; _Matrix[1][0] = Matrix[1][0];
	_Matrix[0][1] = Matrix[0][1]; _Matrix[1][1] = Matrix[1][1];

	return _Matrix;
}

BFW::Math::Mat4::operator const BFW::Math::Mat3 () const
{
	Mat3 _Matrix;

	_Matrix[0][0] = Matrix[0][0]; _Matrix[1][0] = Matrix[1][0]; _Matrix[2][0] = Matrix[2][0];
	_Matrix[0][1] = Matrix[0][1]; _Matrix[1][1] = Matrix[1][1]; _Matrix[2][1] = Matrix[2][1];
	_Matrix[0][2] = Matrix[0][2]; _Matrix[1][2] = Matrix[1][2]; _Matrix[2][2] = Matrix[2][2];

	return _Matrix;
}

float* BFW::Math::Mat4::Data()
{
	return &Matrix[0][0];
}

const float* BFW::Math::Mat4::Data() const
{
	return &Matrix[0][0];
}

const float BFW::Math::Mat4::Determinant() const
{
	Mat3 _DetMat[4];

	_DetMat[0][0][0] = Matrix[1][1]; _DetMat[0][1][0] = Matrix[2][1]; _DetMat[0][2][0] = Matrix[3][1];
	_DetMat[0][0][1] = Matrix[1][2]; _DetMat[0][1][1] = Matrix[2][2]; _DetMat[0][2][1] = Matrix[3][2];
	_DetMat[0][0][2] = Matrix[1][3]; _DetMat[0][1][2] = Matrix[2][3]; _DetMat[0][2][2] = Matrix[3][3];

	_DetMat[1][0][0] = Matrix[1][0]; _DetMat[1][1][0] = Matrix[2][0]; _DetMat[1][2][0] = Matrix[3][0];
	_DetMat[1][0][1] = Matrix[1][2]; _DetMat[1][1][1] = Matrix[2][2]; _DetMat[1][2][1] = Matrix[3][2];
	_DetMat[1][0][2] = Matrix[1][3]; _DetMat[1][1][2] = Matrix[2][3]; _DetMat[1][2][2] = Matrix[3][3];

	_DetMat[2][0][0] = Matrix[1][0]; _DetMat[2][1][0] = Matrix[2][0]; _DetMat[2][2][0] = Matrix[3][0];
	_DetMat[2][0][1] = Matrix[1][1]; _DetMat[2][1][1] = Matrix[2][1]; _DetMat[2][2][1] = Matrix[3][1];
	_DetMat[2][0][2] = Matrix[1][3]; _DetMat[2][1][2] = Matrix[2][3]; _DetMat[2][2][2] = Matrix[3][3];

	_DetMat[3][0][0] = Matrix[1][0]; _DetMat[3][1][0] = Matrix[2][0]; _DetMat[3][2][0] = Matrix[3][0];
	_DetMat[3][0][1] = Matrix[1][1]; _DetMat[3][1][1] = Matrix[2][1]; _DetMat[3][2][1] = Matrix[3][1];
	_DetMat[3][0][2] = Matrix[1][2]; _DetMat[3][1][2] = Matrix[2][2]; _DetMat[3][2][2] = Matrix[3][2];

	return
		Matrix[0][0] * _DetMat[0].Determinant() -
		Matrix[0][1] * _DetMat[1].Determinant() +
		Matrix[0][2] * _DetMat[2].Determinant() -
		Matrix[0][3] * _DetMat[3].Determinant();
}

const float BFW::Math::Mat4::Trace() const
{
	return Matrix[0][0] + Matrix[1][1] + Matrix[2][2] + Matrix[3][3];
}

BFW::Math::Mat4& BFW::Math::Mat4::Transpose()
{
	float _Aux = 0.0f;

	_Aux = Matrix[1][0];
	Matrix[1][0] = Matrix[0][1];
	Matrix[0][1] = _Aux;

	_Aux = Matrix[2][0];
	Matrix[2][0] = Matrix[0][2];
	Matrix[0][2] = _Aux;

	_Aux = Matrix[3][0];
	Matrix[3][0] = Matrix[0][3];
	Matrix[0][3] = _Aux;

	_Aux = Matrix[2][1];
	Matrix[2][1] = Matrix[1][2];
	Matrix[1][2] = _Aux;

	_Aux = Matrix[3][1];
	Matrix[3][1] = Matrix[1][3];
	Matrix[1][3] = _Aux;

	_Aux = Matrix[3][2];
	Matrix[3][2] = Matrix[2][3];
	Matrix[2][3] = _Aux;

	return *this;
}

const BFW::Math::Mat4 BFW::Math::Mat4::Transposed() const
{
	return Mat4(*this).Transpose();
}

BFW::Math::Mat4& BFW::Math::Mat4::Inverse()
{
	Mat4 _Matrix;

	Mat3 _DetMat;

	_DetMat[0][0] = Matrix[1][1]; _DetMat[1][0] = Matrix[2][1]; _DetMat[2][0] = Matrix[3][1];
	_DetMat[0][1] = Matrix[1][2]; _DetMat[1][1] = Matrix[2][2]; _DetMat[2][1] = Matrix[3][2];
	_DetMat[0][2] = Matrix[1][3]; _DetMat[1][2] = Matrix[2][3]; _DetMat[2][2] = Matrix[3][3];

	_Matrix[0][0] = _DetMat.Determinant();

	_DetMat[0][0] = Matrix[1][0]; _DetMat[1][0] = Matrix[2][0]; _DetMat[2][0] = Matrix[3][0];
	_DetMat[0][1] = Matrix[1][2]; _DetMat[1][1] = Matrix[2][2]; _DetMat[2][1] = Matrix[3][2];
	_DetMat[0][2] = Matrix[1][3]; _DetMat[1][2] = Matrix[2][3]; _DetMat[2][2] = Matrix[3][3];

	_Matrix[1][0] = -_DetMat.Determinant();

	_DetMat[0][0] = Matrix[1][0]; _DetMat[1][0] = Matrix[2][0]; _DetMat[2][0] = Matrix[3][0];
	_DetMat[0][1] = Matrix[1][1]; _DetMat[1][1] = Matrix[2][1]; _DetMat[2][1] = Matrix[3][1];
	_DetMat[0][2] = Matrix[1][3]; _DetMat[1][2] = Matrix[2][3]; _DetMat[2][2] = Matrix[3][3];

	_Matrix[2][0] = _DetMat.Determinant();

	_DetMat[0][0] = Matrix[1][0]; _DetMat[1][0] = Matrix[2][0]; _DetMat[2][0] = Matrix[3][0];
	_DetMat[0][1] = Matrix[1][1]; _DetMat[1][1] = Matrix[2][1]; _DetMat[2][1] = Matrix[3][1];
	_DetMat[0][2] = Matrix[1][2]; _DetMat[1][2] = Matrix[2][2]; _DetMat[2][2] = Matrix[3][2];

	_Matrix[3][0] = -_DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][1]; _DetMat[1][0] = Matrix[2][1]; _DetMat[2][0] = Matrix[3][1];
	_DetMat[0][1] = Matrix[0][2]; _DetMat[1][1] = Matrix[2][2]; _DetMat[2][1] = Matrix[3][2];
	_DetMat[0][2] = Matrix[0][3]; _DetMat[1][2] = Matrix[2][3]; _DetMat[2][2] = Matrix[3][3];

	_Matrix[0][1] = -_DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][0]; _DetMat[1][0] = Matrix[2][0]; _DetMat[2][0] = Matrix[3][0];
	_DetMat[0][1] = Matrix[0][2]; _DetMat[1][1] = Matrix[2][2]; _DetMat[2][1] = Matrix[3][2];
	_DetMat[0][2] = Matrix[0][3]; _DetMat[1][2] = Matrix[2][3]; _DetMat[2][2] = Matrix[3][3];

	_Matrix[1][1] = _DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][0]; _DetMat[1][0] = Matrix[2][0]; _DetMat[2][0] = Matrix[3][0];
	_DetMat[0][1] = Matrix[0][1]; _DetMat[1][1] = Matrix[2][1]; _DetMat[2][1] = Matrix[3][1];
	_DetMat[0][2] = Matrix[0][3]; _DetMat[1][2] = Matrix[2][3]; _DetMat[2][2] = Matrix[3][3];

	_Matrix[2][1] = -_DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][0]; _DetMat[1][0] = Matrix[2][0]; _DetMat[2][0] = Matrix[3][0];
	_DetMat[0][1] = Matrix[0][1]; _DetMat[1][1] = Matrix[2][1]; _DetMat[2][1] = Matrix[3][1];
	_DetMat[0][2] = Matrix[0][2]; _DetMat[1][2] = Matrix[2][2]; _DetMat[2][2] = Matrix[3][2];

	_Matrix[3][1] = _DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][1]; _DetMat[1][0] = Matrix[1][1]; _DetMat[2][0] = Matrix[3][1];
	_DetMat[0][1] = Matrix[0][2]; _DetMat[1][1] = Matrix[1][2]; _DetMat[2][1] = Matrix[3][2];
	_DetMat[0][2] = Matrix[0][3]; _DetMat[1][2] = Matrix[1][3]; _DetMat[2][2] = Matrix[3][3];

	_Matrix[0][2] = _DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][0]; _DetMat[1][0] = Matrix[1][0]; _DetMat[2][0] = Matrix[3][0];
	_DetMat[0][1] = Matrix[0][2]; _DetMat[1][1] = Matrix[1][2]; _DetMat[2][1] = Matrix[3][2];
	_DetMat[0][2] = Matrix[0][3]; _DetMat[1][2] = Matrix[1][3]; _DetMat[2][2] = Matrix[3][3];

	_Matrix[1][2] = -_DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][0]; _DetMat[1][0] = Matrix[1][0]; _DetMat[2][0] = Matrix[3][0];
	_DetMat[0][1] = Matrix[0][1]; _DetMat[1][1] = Matrix[1][1]; _DetMat[2][1] = Matrix[3][1];
	_DetMat[0][2] = Matrix[0][3]; _DetMat[1][2] = Matrix[1][3]; _DetMat[2][2] = Matrix[3][3];

	_Matrix[2][2] = _DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][0]; _DetMat[1][0] = Matrix[1][0]; _DetMat[2][0] = Matrix[3][0];
	_DetMat[0][1] = Matrix[0][1]; _DetMat[1][1] = Matrix[1][1]; _DetMat[2][1] = Matrix[3][1];
	_DetMat[0][2] = Matrix[0][2]; _DetMat[1][2] = Matrix[1][2]; _DetMat[2][2] = Matrix[3][2];

	_Matrix[3][2] = -_DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][1]; _DetMat[1][0] = Matrix[1][1]; _DetMat[2][0] = Matrix[2][1];
	_DetMat[0][1] = Matrix[0][2]; _DetMat[1][1] = Matrix[1][2]; _DetMat[2][1] = Matrix[2][2];
	_DetMat[0][2] = Matrix[0][3]; _DetMat[1][2] = Matrix[1][3]; _DetMat[2][2] = Matrix[2][3];

	_Matrix[0][3] = -_DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][0]; _DetMat[1][0] = Matrix[1][0]; _DetMat[2][0] = Matrix[2][0];
	_DetMat[0][1] = Matrix[0][2]; _DetMat[1][1] = Matrix[1][2]; _DetMat[2][1] = Matrix[2][2];
	_DetMat[0][2] = Matrix[0][3]; _DetMat[1][2] = Matrix[1][3]; _DetMat[2][2] = Matrix[2][3];

	_Matrix[1][3] = _DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][0]; _DetMat[1][0] = Matrix[1][0]; _DetMat[2][0] = Matrix[2][0];
	_DetMat[0][1] = Matrix[0][1]; _DetMat[1][1] = Matrix[1][1]; _DetMat[2][1] = Matrix[2][1];
	_DetMat[0][2] = Matrix[0][3]; _DetMat[1][2] = Matrix[1][3]; _DetMat[2][2] = Matrix[2][3];

	_Matrix[2][3] = -_DetMat.Determinant();

	_DetMat[0][0] = Matrix[0][0]; _DetMat[1][0] = Matrix[1][0]; _DetMat[2][0] = Matrix[2][0];
	_DetMat[0][1] = Matrix[0][1]; _DetMat[1][1] = Matrix[1][1]; _DetMat[2][1] = Matrix[2][1];
	_DetMat[0][2] = Matrix[0][2]; _DetMat[1][2] = Matrix[1][2]; _DetMat[2][2] = Matrix[2][2];

	_Matrix[3][3] = _DetMat.Determinant();

	_Matrix /= Determinant();

	*this = _Matrix;

	return *this;
}

const BFW::Math::Mat4 BFW::Math::Mat4::Inversed() const
{
	return Mat4(*this).Inverse();
}

const BFW::Math::Mat4& BFW::Math::Mat4::operator+ () const
{
	return *this;
}

const BFW::Math::Mat4 BFW::Math::Mat4::operator- () const
{
	Mat4 _Matrix;

	_Matrix[0][0] = -Matrix[0][0]; _Matrix[1][0] = -Matrix[1][0]; _Matrix[2][0] = -Matrix[2][0]; _Matrix[3][0] = -Matrix[3][0];
	_Matrix[0][1] = -Matrix[0][1]; _Matrix[1][1] = -Matrix[1][1]; _Matrix[2][1] = -Matrix[2][1]; _Matrix[3][1] = -Matrix[3][1];
	_Matrix[0][2] = -Matrix[0][2]; _Matrix[1][2] = -Matrix[1][2]; _Matrix[2][2] = -Matrix[2][2]; _Matrix[3][2] = -Matrix[3][2];
	_Matrix[0][3] = -Matrix[0][3]; _Matrix[1][3] = -Matrix[1][3]; _Matrix[2][3] = -Matrix[2][3]; _Matrix[3][3] = -Matrix[3][3];

	return _Matrix;
}

const BFW::Math::Vec4 BFW::Math::Mat4::operator* (const Vec4& _Vec) const
{
	return Vec4
	(
		Matrix[0][0] * _Vec.x + Matrix[1][0] * _Vec.y + Matrix[2][0] * _Vec.z + Matrix[3][0] * _Vec.w,
		Matrix[0][1] * _Vec.x + Matrix[1][1] * _Vec.y + Matrix[2][1] * _Vec.z + Matrix[3][1] * _Vec.w,
		Matrix[0][2] * _Vec.x + Matrix[1][2] * _Vec.y + Matrix[2][2] * _Vec.z + Matrix[3][2] * _Vec.w,
		Matrix[0][3] * _Vec.x + Matrix[1][3] * _Vec.y + Matrix[2][3] * _Vec.z + Matrix[3][3] * _Vec.w
	);
}

const BFW::Math::Mat4 BFW::Math::Mat4::operator+ (const Mat4& _Other) const
{
	Mat4 _Matrix(*this);

	_Matrix[0][0] += _Other[0][0]; _Matrix[1][0] += _Other[1][0]; _Matrix[2][0] += _Other[2][0]; _Matrix[3][0] += _Other[3][0];
	_Matrix[0][1] += _Other[0][1]; _Matrix[1][1] += _Other[1][1]; _Matrix[2][1] += _Other[2][1]; _Matrix[3][1] += _Other[3][1];
	_Matrix[0][2] += _Other[0][2]; _Matrix[1][2] += _Other[1][2]; _Matrix[2][2] += _Other[2][2]; _Matrix[3][2] += _Other[3][2];
	_Matrix[0][3] += _Other[0][3]; _Matrix[1][3] += _Other[1][3]; _Matrix[2][3] += _Other[2][3]; _Matrix[3][3] += _Other[3][3];

	return _Matrix;
}

BFW::Math::Mat4& BFW::Math::Mat4::operator+= (const Mat4& _Other)
{
	Matrix[0][0] += _Other[0][0]; Matrix[1][0] += _Other[1][0]; Matrix[2][0] += _Other[2][0]; Matrix[3][0] += _Other[3][0];
	Matrix[0][1] += _Other[0][1]; Matrix[1][1] += _Other[1][1]; Matrix[2][1] += _Other[2][1]; Matrix[3][1] += _Other[3][1];
	Matrix[0][2] += _Other[0][2]; Matrix[1][2] += _Other[1][2]; Matrix[2][2] += _Other[2][2]; Matrix[3][2] += _Other[3][2];
	Matrix[0][3] += _Other[0][3]; Matrix[1][3] += _Other[1][3]; Matrix[2][3] += _Other[2][3]; Matrix[3][3] += _Other[3][3];

	return *this;
}

const BFW::Math::Mat4 BFW::Math::Mat4::operator+ (const float _Value) const
{
	Mat4 _Matrix(*this);

	_Matrix[0][0] += _Value; _Matrix[1][0] += _Value; _Matrix[2][0] += _Value; _Matrix[3][0] += _Value;
	_Matrix[0][1] += _Value; _Matrix[1][1] += _Value; _Matrix[2][1] += _Value; _Matrix[3][1] += _Value;
	_Matrix[0][2] += _Value; _Matrix[1][2] += _Value; _Matrix[2][2] += _Value; _Matrix[3][2] += _Value;
	_Matrix[0][3] += _Value; _Matrix[1][3] += _Value; _Matrix[2][3] += _Value; _Matrix[3][3] += _Value;

	return _Matrix;
}

BFW::Math::Mat4& BFW::Math::Mat4::operator+= (const float _Value)
{
	Matrix[0][0] += _Value; Matrix[1][0] += _Value; Matrix[2][0] += _Value; Matrix[3][0] += _Value;
	Matrix[0][1] += _Value; Matrix[1][1] += _Value; Matrix[2][1] += _Value; Matrix[3][1] += _Value;
	Matrix[0][2] += _Value; Matrix[1][2] += _Value; Matrix[2][2] += _Value; Matrix[3][2] += _Value;
	Matrix[0][3] += _Value; Matrix[1][3] += _Value; Matrix[2][3] += _Value; Matrix[3][3] += _Value;

	return *this;
}

const BFW::Math::Mat4 BFW::Math::Mat4::operator- (const Mat4& _Other) const
{
	Mat4 _Matrix(*this);

	_Matrix[0][0] -= _Other[0][0]; _Matrix[1][0] -= _Other[1][0]; _Matrix[2][0] -= _Other[2][0]; _Matrix[3][0] -= _Other[3][0];
	_Matrix[0][1] -= _Other[0][1]; _Matrix[1][1] -= _Other[1][1]; _Matrix[2][1] -= _Other[2][1]; _Matrix[3][1] -= _Other[3][1];
	_Matrix[0][2] -= _Other[0][2]; _Matrix[1][2] -= _Other[1][2]; _Matrix[2][2] -= _Other[2][2]; _Matrix[3][2] -= _Other[3][2];
	_Matrix[0][3] -= _Other[0][3]; _Matrix[1][3] -= _Other[1][3]; _Matrix[2][3] -= _Other[2][3]; _Matrix[3][3] -= _Other[3][3];

	return _Matrix;
}

BFW::Math::Mat4& BFW::Math::Mat4::operator-= (const Mat4& _Other)
{
	Matrix[0][0] -= _Other[0][0]; Matrix[1][0] -= _Other[1][0]; Matrix[2][0] -= _Other[2][0]; Matrix[3][0] -= _Other[3][0];
	Matrix[0][1] -= _Other[0][1]; Matrix[1][1] -= _Other[1][1]; Matrix[2][1] -= _Other[2][1]; Matrix[3][1] -= _Other[3][1];
	Matrix[0][2] -= _Other[0][2]; Matrix[1][2] -= _Other[1][2]; Matrix[2][2] -= _Other[2][2]; Matrix[3][2] -= _Other[3][2];
	Matrix[0][3] -= _Other[0][3]; Matrix[1][3] -= _Other[1][3]; Matrix[2][3] -= _Other[2][3]; Matrix[3][3] -= _Other[3][3];

	return *this;
}

const BFW::Math::Mat4 BFW::Math::Mat4::operator- (const float _Value) const
{
	Mat4 _Matrix(*this);

	_Matrix[0][0] -= _Value; _Matrix[1][0] -= _Value; _Matrix[2][0] -= _Value; _Matrix[3][0] -= _Value;
	_Matrix[0][1] -= _Value; _Matrix[1][1] -= _Value; _Matrix[2][1] -= _Value; _Matrix[3][1] -= _Value;
	_Matrix[0][2] -= _Value; _Matrix[1][2] -= _Value; _Matrix[2][2] -= _Value; _Matrix[3][2] -= _Value;
	_Matrix[0][3] -= _Value; _Matrix[1][3] -= _Value; _Matrix[2][3] -= _Value; _Matrix[3][3] -= _Value;

	return _Matrix;
}

BFW::Math::Mat4& BFW::Math::Mat4::operator-= (const float _Value)
{
	Matrix[0][0] -= _Value; Matrix[1][0] -= _Value; Matrix[2][0] -= _Value; Matrix[3][0] -= _Value;
	Matrix[0][1] -= _Value; Matrix[1][1] -= _Value; Matrix[2][1] -= _Value; Matrix[3][1] -= _Value;
	Matrix[0][2] -= _Value; Matrix[1][2] -= _Value; Matrix[2][2] -= _Value; Matrix[3][2] -= _Value;
	Matrix[0][3] -= _Value; Matrix[1][3] -= _Value; Matrix[2][3] -= _Value; Matrix[3][3] -= _Value;

	return *this;
}

const BFW::Math::Mat4 BFW::Math::Mat4::operator* (const Mat4& _Other) const
{
	Mat4 _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Other[0][0] + Matrix[1][0] * _Other[0][1] + Matrix[2][0] * _Other[0][2] + Matrix[3][0] * _Other[0][3];
	_Matrix[1][0] = Matrix[0][0] * _Other[1][0] + Matrix[1][0] * _Other[1][1] + Matrix[2][0] * _Other[1][2] + Matrix[3][0] * _Other[1][3];
	_Matrix[2][0] = Matrix[0][0] * _Other[2][0] + Matrix[1][0] * _Other[2][1] + Matrix[2][0] * _Other[2][2] + Matrix[3][0] * _Other[2][3];
	_Matrix[3][0] = Matrix[0][0] * _Other[3][0] + Matrix[1][0] * _Other[3][1] + Matrix[2][0] * _Other[3][2] + Matrix[3][0] * _Other[3][3];

	_Matrix[0][1] = Matrix[0][1] * _Other[0][0] + Matrix[1][1] * _Other[0][1] + Matrix[2][1] * _Other[0][2] + Matrix[3][1] * _Other[0][3];
	_Matrix[1][1] = Matrix[0][1] * _Other[1][0] + Matrix[1][1] * _Other[1][1] + Matrix[2][1] * _Other[1][2] + Matrix[3][1] * _Other[1][3];
	_Matrix[2][1] = Matrix[0][1] * _Other[2][0] + Matrix[1][1] * _Other[2][1] + Matrix[2][1] * _Other[2][2] + Matrix[3][1] * _Other[2][3];
	_Matrix[3][1] = Matrix[0][1] * _Other[3][0] + Matrix[1][1] * _Other[3][1] + Matrix[2][1] * _Other[3][2] + Matrix[3][1] * _Other[3][3];

	_Matrix[0][2] = Matrix[0][2] * _Other[0][0] + Matrix[1][2] * _Other[0][1] + Matrix[2][2] * _Other[0][2] + Matrix[3][2] * _Other[0][3];
	_Matrix[1][2] = Matrix[0][2] * _Other[1][0] + Matrix[1][2] * _Other[1][1] + Matrix[2][2] * _Other[1][2] + Matrix[3][2] * _Other[1][3];
	_Matrix[2][2] = Matrix[0][2] * _Other[2][0] + Matrix[1][2] * _Other[2][1] + Matrix[2][2] * _Other[2][2] + Matrix[3][2] * _Other[2][3];
	_Matrix[3][2] = Matrix[0][2] * _Other[3][0] + Matrix[1][2] * _Other[3][1] + Matrix[2][2] * _Other[3][2] + Matrix[3][2] * _Other[3][3];

	_Matrix[0][3] = Matrix[0][3] * _Other[0][0] + Matrix[1][3] * _Other[0][1] + Matrix[2][3] * _Other[0][2] + Matrix[3][3] * _Other[0][3];
	_Matrix[1][3] = Matrix[0][3] * _Other[1][0] + Matrix[1][3] * _Other[1][1] + Matrix[2][3] * _Other[1][2] + Matrix[3][3] * _Other[1][3];
	_Matrix[2][3] = Matrix[0][3] * _Other[2][0] + Matrix[1][3] * _Other[2][1] + Matrix[2][3] * _Other[2][2] + Matrix[3][3] * _Other[2][3];
	_Matrix[3][3] = Matrix[0][3] * _Other[3][0] + Matrix[1][3] * _Other[3][1] + Matrix[2][3] * _Other[3][2] + Matrix[3][3] * _Other[3][3];

	return _Matrix;
}

BFW::Math::Mat4& BFW::Math::Mat4::operator*= (const Mat4& _Other)
{
	Mat4 _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Other[0][0] + Matrix[1][0] * _Other[0][1] + Matrix[2][0] * _Other[0][2] + Matrix[3][0] * _Other[0][3];
	_Matrix[1][0] = Matrix[0][0] * _Other[1][0] + Matrix[1][0] * _Other[1][1] + Matrix[2][0] * _Other[1][2] + Matrix[3][0] * _Other[1][3];
	_Matrix[2][0] = Matrix[0][0] * _Other[2][0] + Matrix[1][0] * _Other[2][1] + Matrix[2][0] * _Other[2][2] + Matrix[3][0] * _Other[2][3];
	_Matrix[3][0] = Matrix[0][0] * _Other[3][0] + Matrix[1][0] * _Other[3][1] + Matrix[2][0] * _Other[3][2] + Matrix[3][0] * _Other[3][3];

	_Matrix[0][1] = Matrix[0][1] * _Other[0][0] + Matrix[1][1] * _Other[0][1] + Matrix[2][1] * _Other[0][2] + Matrix[3][1] * _Other[0][3];
	_Matrix[1][1] = Matrix[0][1] * _Other[1][0] + Matrix[1][1] * _Other[1][1] + Matrix[2][1] * _Other[1][2] + Matrix[3][1] * _Other[1][3];
	_Matrix[2][1] = Matrix[0][1] * _Other[2][0] + Matrix[1][1] * _Other[2][1] + Matrix[2][1] * _Other[2][2] + Matrix[3][1] * _Other[2][3];
	_Matrix[3][1] = Matrix[0][1] * _Other[3][0] + Matrix[1][1] * _Other[3][1] + Matrix[2][1] * _Other[3][2] + Matrix[3][1] * _Other[3][3];

	_Matrix[0][2] = Matrix[0][2] * _Other[0][0] + Matrix[1][2] * _Other[0][1] + Matrix[2][2] * _Other[0][2] + Matrix[3][2] * _Other[0][3];
	_Matrix[1][2] = Matrix[0][2] * _Other[1][0] + Matrix[1][2] * _Other[1][1] + Matrix[2][2] * _Other[1][2] + Matrix[3][2] * _Other[1][3];
	_Matrix[2][2] = Matrix[0][2] * _Other[2][0] + Matrix[1][2] * _Other[2][1] + Matrix[2][2] * _Other[2][2] + Matrix[3][2] * _Other[2][3];
	_Matrix[3][2] = Matrix[0][2] * _Other[3][0] + Matrix[1][2] * _Other[3][1] + Matrix[2][2] * _Other[3][2] + Matrix[3][2] * _Other[3][3];

	_Matrix[0][3] = Matrix[0][3] * _Other[0][0] + Matrix[1][3] * _Other[0][1] + Matrix[2][3] * _Other[0][2] + Matrix[3][3] * _Other[0][3];
	_Matrix[1][3] = Matrix[0][3] * _Other[1][0] + Matrix[1][3] * _Other[1][1] + Matrix[2][3] * _Other[1][2] + Matrix[3][3] * _Other[1][3];
	_Matrix[2][3] = Matrix[0][3] * _Other[2][0] + Matrix[1][3] * _Other[2][1] + Matrix[2][3] * _Other[2][2] + Matrix[3][3] * _Other[2][3];
	_Matrix[3][3] = Matrix[0][3] * _Other[3][0] + Matrix[1][3] * _Other[3][1] + Matrix[2][3] * _Other[3][2] + Matrix[3][3] * _Other[3][3];

	*this = _Matrix;

	return *this;
}

const BFW::Math::Mat4 BFW::Math::Mat4::operator* (const float _Value) const
{
	Mat4 _Matrix(*this);

	_Matrix[0][0] *= _Value; _Matrix[1][0] *= _Value; _Matrix[2][0] *= _Value; _Matrix[3][0] *= _Value;
	_Matrix[0][1] *= _Value; _Matrix[1][1] *= _Value; _Matrix[2][1] *= _Value; _Matrix[3][1] *= _Value;
	_Matrix[0][2] *= _Value; _Matrix[1][2] *= _Value; _Matrix[2][2] *= _Value; _Matrix[3][2] *= _Value;
	_Matrix[0][3] *= _Value; _Matrix[1][3] *= _Value; _Matrix[2][3] *= _Value; _Matrix[3][3] *= _Value;

	return _Matrix;
}

BFW::Math::Mat4& BFW::Math::Mat4::operator*= (const float _Value)
{
	Matrix[0][0] *= _Value; Matrix[1][0] *= _Value; Matrix[2][0] *= _Value; Matrix[3][0] *= _Value;
	Matrix[0][1] *= _Value; Matrix[1][1] *= _Value; Matrix[2][1] *= _Value; Matrix[3][1] *= _Value;
	Matrix[0][2] *= _Value; Matrix[1][2] *= _Value; Matrix[2][2] *= _Value; Matrix[3][2] *= _Value;
	Matrix[0][3] *= _Value; Matrix[1][3] *= _Value; Matrix[2][3] *= _Value; Matrix[3][3] *= _Value;

	return *this;
}

const BFW::Math::Mat4 BFW::Math::Mat4::operator/ (const float _Value) const
{
	Mat4 _Matrix(*this);

	_Matrix[0][0] /= _Value; _Matrix[1][0] /= _Value; _Matrix[2][0] /= _Value; _Matrix[3][0] /= _Value;
	_Matrix[0][1] /= _Value; _Matrix[1][1] /= _Value; _Matrix[2][1] /= _Value; _Matrix[3][1] /= _Value;
	_Matrix[0][2] /= _Value; _Matrix[1][2] /= _Value; _Matrix[2][2] /= _Value; _Matrix[3][2] /= _Value;
	_Matrix[0][3] /= _Value; _Matrix[1][3] /= _Value; _Matrix[2][3] /= _Value; _Matrix[3][3] /= _Value;

	return _Matrix;
}

BFW::Math::Mat4& BFW::Math::Mat4::operator/= (const float _Value)
{
	Matrix[0][0] /= _Value; Matrix[1][0] /= _Value; Matrix[2][0] /= _Value; Matrix[3][0] /= _Value;
	Matrix[0][1] /= _Value; Matrix[1][1] /= _Value; Matrix[2][1] /= _Value; Matrix[3][1] /= _Value;
	Matrix[0][2] /= _Value; Matrix[1][2] /= _Value; Matrix[2][2] /= _Value; Matrix[3][2] /= _Value;
	Matrix[0][3] /= _Value; Matrix[1][3] /= _Value; Matrix[2][3] /= _Value; Matrix[3][3] /= _Value;

	return *this;
}

const bool BFW::Math::Mat4::operator== (const Mat4& _Other) const
{
	return
		Matrix[0][0] == _Other[0][0] && Matrix[1][0] == _Other[1][0] && Matrix[2][0] == _Other[2][0] && Matrix[3][0] == _Other[3][0] &&
		Matrix[0][1] == _Other[0][1] && Matrix[1][1] == _Other[1][1] && Matrix[2][1] == _Other[2][1] && Matrix[3][1] == _Other[3][1] &&
		Matrix[0][2] == _Other[0][2] && Matrix[1][2] == _Other[1][2] && Matrix[2][2] == _Other[2][2] && Matrix[3][2] == _Other[3][2] &&
		Matrix[0][3] == _Other[0][3] && Matrix[1][3] == _Other[1][3] && Matrix[2][3] == _Other[2][3] && Matrix[3][3] == _Other[3][3];
}

const bool BFW::Math::Mat4::operator!= (const Mat4& _Other) const
{
	return
		Matrix[0][0] != _Other[0][0] || Matrix[1][0] != _Other[1][0] || Matrix[2][0] != _Other[2][0] || Matrix[3][0] != _Other[3][0] ||
		Matrix[0][1] != _Other[0][1] || Matrix[1][1] != _Other[1][1] || Matrix[2][1] != _Other[2][1] || Matrix[3][1] != _Other[3][1] ||
		Matrix[0][2] != _Other[0][2] || Matrix[1][2] != _Other[1][2] || Matrix[2][2] != _Other[2][2] || Matrix[3][2] != _Other[3][2] ||
		Matrix[0][3] != _Other[0][3] || Matrix[1][3] != _Other[1][3] || Matrix[2][3] != _Other[2][3] || Matrix[3][3] != _Other[3][3];
}

float* BFW::Math::Mat4::operator[] (const size_t _Index)
{
	return Matrix[_Index].Data();
}

const float* BFW::Math::Mat4::operator[] (const size_t _Index) const
{
	return Matrix[_Index].Data();
}

BFW::Math::Mat4& BFW::Math::Mat4::operator= (const Mat4& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Matrix[0][0] = _Other[0][0]; Matrix[1][0] = _Other[1][0]; Matrix[2][0] = _Other[2][0]; Matrix[3][0] = _Other[3][0];
	Matrix[0][1] = _Other[0][1]; Matrix[1][1] = _Other[1][1]; Matrix[2][1] = _Other[2][1]; Matrix[3][1] = _Other[3][1];
	Matrix[0][2] = _Other[0][2]; Matrix[1][2] = _Other[1][2]; Matrix[2][2] = _Other[2][2]; Matrix[3][2] = _Other[3][2];
	Matrix[0][3] = _Other[0][3]; Matrix[1][3] = _Other[1][3]; Matrix[2][3] = _Other[2][3]; Matrix[3][3] = _Other[3][3];

	return *this;
}

BFW::Math::Mat4& BFW::Math::Mat4::operator= (Mat4&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Matrix[0][0] = _Other[0][0]; Matrix[1][0] = _Other[1][0]; Matrix[2][0] = _Other[2][0]; Matrix[3][0] = _Other[3][0];
	Matrix[0][1] = _Other[0][1]; Matrix[1][1] = _Other[1][1]; Matrix[2][1] = _Other[2][1]; Matrix[3][1] = _Other[3][1];
	Matrix[0][2] = _Other[0][2]; Matrix[1][2] = _Other[1][2]; Matrix[2][2] = _Other[2][2]; Matrix[3][2] = _Other[3][2];
	Matrix[0][3] = _Other[0][3]; Matrix[1][3] = _Other[1][3]; Matrix[2][3] = _Other[2][3]; Matrix[3][3] = _Other[3][3];

	_Other[0][0] = 1.0f; _Other[1][0] = 0.0f; _Other[2][0] = 0.0f; _Other[3][0] = 0.0f;
	_Other[0][1] = 0.0f; _Other[1][1] = 1.0f; _Other[2][1] = 0.0f; _Other[3][1] = 0.0f;
	_Other[0][2] = 0.0f; _Other[1][2] = 0.0f; _Other[2][2] = 1.0f; _Other[3][2] = 0.0f;
	_Other[0][3] = 0.0f; _Other[1][3] = 0.0f; _Other[2][3] = 0.0f; _Other[3][3] = 1.0f;

	return *this;
}

const BFW::Math::Mat4 BFW::Math::Mat4::GetFill(const float _Value)
{
	Mat4 _Matrix;

	_Matrix[0][0] = _Value; _Matrix[1][0] = _Value; _Matrix[2][0] = _Value; _Matrix[3][0] = _Value;
	_Matrix[0][1] = _Value; _Matrix[1][1] = _Value; _Matrix[2][1] = _Value; _Matrix[3][1] = _Value;
	_Matrix[0][2] = _Value; _Matrix[1][2] = _Value; _Matrix[2][2] = _Value; _Matrix[3][2] = _Value;
	_Matrix[0][3] = _Value; _Matrix[1][3] = _Value; _Matrix[2][3] = _Value; _Matrix[3][3] = _Value;

	return _Matrix;
}

const BFW::Math::Mat4 BFW::Math::Mat4::GetTranslation(const Vec3& _Position)
{
	Mat4 _Matrix;

	_Matrix[3][0] = _Position.x;
	_Matrix[3][1] = _Position.y;
	_Matrix[3][2] = _Position.z;

	return _Matrix;
}

const BFW::Math::Mat4 BFW::Math::Mat4::GetRotation(const float _Angle, const Vec3& _Axis)
{
	Mat4 _Matrix;

	float _Sin = sinf(_Angle);
	float _Cos = cosf(_Angle);

	_Matrix[0][0] = _Cos + _Axis.x * _Axis.x * (1.0f - _Cos);
	_Matrix[1][0] = _Axis.x * _Axis.y * (1.0f - _Cos) - _Axis.z * _Sin;
	_Matrix[2][0] = _Axis.x * _Axis.z * (1.0f - _Cos) + _Axis.y * _Sin;

	_Matrix[0][1] = _Axis.y * _Axis.x * (1.0f - _Cos) + _Axis.z * _Sin;
	_Matrix[1][1] = _Cos + _Axis.y * _Axis.y * (1.0f - _Cos);
	_Matrix[2][1] = _Axis.y * _Axis.z * (1.0f - _Cos) - _Axis.x * _Sin;

	_Matrix[0][2] = _Axis.z * _Axis.x * (1.0f - _Cos) - _Axis.y * _Sin;
	_Matrix[1][2] = _Axis.z * _Axis.y * (1.0f - _Cos) + _Axis.x * _Sin;
	_Matrix[2][2] = _Cos + _Axis.z * _Axis.z * (1.0f - _Cos);

	return _Matrix;
}

const BFW::Math::Mat4 BFW::Math::Mat4::GetScale(const Vec3& _Size)
{
	Mat4 _Matrix;

	_Matrix[0][0] = _Size.x;
	_Matrix[1][1] = _Size.y;
	_Matrix[2][2] = _Size.z;

	return _Matrix;
}

const BFW::Math::Mat4 BFW::Math::Mat4::GetShear(const float _Value, const size_t _ShearedAxis, const size_t _ShearByAxis)
{
	Mat4 _Matrix;

	_Matrix[_ShearByAxis][_ShearedAxis] = _Value;

	return _Matrix;
}

const BFW::Math::Mat4 BFW::Math::Mat4::GetFlip(const Vec3& _Normal)
{
	Mat4 _Matrix;

	_Matrix[0][0] = 1.0f - 2.0f * _Normal.x * _Normal.x;
	_Matrix[1][0] = -2.0f * _Normal.x * _Normal.y;
	_Matrix[2][0] = -2.0f * _Normal.x * _Normal.z;

	_Matrix[0][1] = -2.0f * _Normal.y * _Normal.x;
	_Matrix[1][1] = 1.0f - 2.0f * _Normal.y * _Normal.y;
	_Matrix[2][1] = -2.0f * _Normal.y * _Normal.z;

	_Matrix[0][2] = -2.0f * _Normal.z * _Normal.x;
	_Matrix[1][2] = -2.0f * _Normal.z * _Normal.y;
	_Matrix[2][2] = 1.0f - 2.0f * _Normal.z * _Normal.z;

	return _Matrix;
}

const BFW::Math::Mat4 BFW::Math::Mat4::GetOrthoLeftHand(const float _Left, const float _Right, const float _Bottom, const float _Top, const float _ZNear, const float _ZFar)
{
	Mat4 _Matrix;

	_Matrix[0][0] = 2.0f / (_Right - _Left);
	_Matrix[1][1] = 2.0f / (_Top - _Bottom);
	_Matrix[2][2] = 1.0f / (_ZNear - _ZFar);

	_Matrix[3][0] = (_Left + _Right) / (_Left - _Right);
	_Matrix[3][1] = (_Bottom + _Top) / (_Bottom - _Top);
	_Matrix[3][2] = _ZFar / (_ZFar - _ZNear);

	return _Matrix;
}

const BFW::Math::Mat4 BFW::Math::Mat4::GetOrthoRightHand(const float _Left, const float _Right, const float _Bottom, const float _Top, const float _ZNear, const float _ZFar)
{
	Mat4 _Matrix;

	_Matrix[0][0] = 2.0f / (_Right - _Left);
	_Matrix[1][1] = 2.0f / (_Top - _Bottom);
	_Matrix[2][2] = -2.0f / (_ZNear - _ZFar);

	_Matrix[3][0] = (_Left + _Right) / (_Left - _Right);
	_Matrix[3][1] = (_Bottom + _Top) / (_Bottom - _Top);
	_Matrix[3][2] = (_ZFar + _ZNear) / (_ZFar - _ZNear);

	return _Matrix;
}

const BFW::Math::Mat4 BFW::Math::Mat4::GetPerspectiveOxLeftHand(const float _Fov, const float _AspectRatio, const float _ZNear, const float _ZFar)
{
	Mat4 _Matrix;

	float _Tan = tanf(_Fov / 2.0f);

	_Matrix[0][0] = 1.0f / _Tan;
	_Matrix[1][1] = 1.0f / (_Tan / _AspectRatio);
	_Matrix[2][2] = _ZFar / (_ZFar - _ZNear);
	_Matrix[3][2] = (_ZNear * _ZFar) / (_ZNear - _ZFar);
	_Matrix[2][3] = 1.0f;
	_Matrix[3][3] = 0.0f;

	return _Matrix;
}

const BFW::Math::Mat4 BFW::Math::Mat4::GetPerspectiveOyLeftHand(const float _Fov, const float _AspectRatio, const float _ZNear, const float _ZFar)
{
	Mat4 _Matrix;

	float _Tan = tanf(_Fov / 2.0f);

	_Matrix[0][0] = 1.0f / (_Tan * _AspectRatio);
	_Matrix[1][1] = 1.0f / _Tan;
	_Matrix[2][2] = _ZFar / (_ZFar - _ZNear);
	_Matrix[3][2] = (_ZNear * _ZFar) / (_ZNear - _ZFar);
	_Matrix[2][3] = 1.0f;
	_Matrix[3][3] = 0.0f;

	return _Matrix;
}

const BFW::Math::Mat4 BFW::Math::Mat4::GetPerspectiveOxRightHand(const float _Fov, const float _AspectRatio, const float _ZNear, const float _ZFar)
{
	Mat4 _Matrix;

	float _Tan = tanf(_Fov / 2.0f);

	_Matrix[0][0] = 1.0f / _Tan;
	_Matrix[1][1] = 1.0f / (_Tan / _AspectRatio);
	_Matrix[2][2] = (_ZNear + _ZFar) / (_ZNear - _ZFar);
	_Matrix[3][2] = (2.0f * _ZNear * _ZFar) / (_ZNear - _ZFar);
	_Matrix[2][3] = -1.0f;
	_Matrix[3][3] = 0.0f;

	return _Matrix;
}

const BFW::Math::Mat4 BFW::Math::Mat4::GetPerspectiveOyRightHand(const float _Fov, const float _AspectRatio, const float _ZNear, const float _ZFar)
{
	Mat4 _Matrix;

	float _Tan = tanf(_Fov / 2.0f);

	_Matrix[0][0] = 1.0f / (_Tan * _AspectRatio);
	_Matrix[1][1] = 1.0f / _Tan;
	_Matrix[2][2] = (_ZNear + _ZFar) / (_ZNear - _ZFar);
	_Matrix[3][2] = (2.0f * _ZNear * _ZFar) / (_ZNear - _ZFar);
	_Matrix[2][3] = -1.0f;
	_Matrix[3][3] = 0.0f;

	return _Matrix;
}
