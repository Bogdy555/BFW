#include "..\Headers\BFW.hpp"



BFW::Math::Mat2f::Mat2f() : Matrix()
{
	Matrix[0][0] = 1.0f; Matrix[0][1] = 0.0f;
	Matrix[1][0] = 0.0f; Matrix[1][1] = 1.0f;
}

BFW::Math::Mat2f::Mat2f(const float _x, const float _y) : Matrix()
{
	Matrix[0][0] = _x; Matrix[0][1] = 0.0f;
	Matrix[1][0] = 0.0f; Matrix[1][1] = _y;
}

BFW::Math::Mat2f::Mat2f(const Mat2f& _Other) : Matrix()
{
	Matrix[0][0] = _Other.Matrix[0][0]; Matrix[0][1] = _Other.Matrix[0][1];
	Matrix[1][0] = _Other.Matrix[1][0]; Matrix[1][1] = _Other.Matrix[1][1];
}

BFW::Math::Mat2f::Mat2f(Mat2f&& _Other) noexcept
{
	Matrix[0][0] = _Other.Matrix[0][0]; Matrix[0][1] = _Other.Matrix[0][1];
	Matrix[1][0] = _Other.Matrix[1][0]; Matrix[1][1] = _Other.Matrix[1][1];

	_Other.Matrix[0][0] = 1.0f; _Other.Matrix[0][1] = 0.0f;
	_Other.Matrix[1][0] = 0.0f; _Other.Matrix[1][1] = 1.0f;
}

BFW::Math::Mat2f::~Mat2f()
{

}

float* BFW::Math::Mat2f::Data()
{
	return Matrix[0].Data();
}

const float* BFW::Math::Mat2f::Data() const
{
	return Matrix[0].Data();
}

const float BFW::Math::Mat2f::Determinant() const
{
	return Matrix[0][0] * Matrix[1][1] - Matrix[0][1] * Matrix[1][0];
}

const float BFW::Math::Mat2f::Trace() const
{
	return Matrix[0][0] + Matrix[1][1];
}

const BFW::Math::Mat2f& BFW::Math::Mat2f::Transpose()
{
	fSwap(Matrix[0][1], Matrix[1][0]);

	return *this;
}

const BFW::Math::Mat2f BFW::Math::Mat2f::Transposed() const
{
	Mat2f _Matrix;

	_Matrix[0][0] = Matrix[0][0]; _Matrix[0][1] = Matrix[1][0];
	_Matrix[1][0] = Matrix[0][1]; _Matrix[1][1] = Matrix[1][1];

	return _Matrix;
}

const BFW::Math::Mat2f& BFW::Math::Mat2f::Scale(const float _x, const float _y)
{
	Matrix[0][0] = _x; Matrix[0][1] = 0.0f;
	Matrix[1][0] = 0.0f; Matrix[1][1] = _y;

	return *this;
}

const BFW::Math::Mat2f BFW::Math::Mat2f::GetScale(const float _x, const float _y)
{
	Mat2f _Matrix;

	_Matrix[0][0] = _x; _Matrix[0][1] = 0.0f;
	_Matrix[1][0] = 0.0f; _Matrix[1][1] = _y;

	return _Matrix;
}

const BFW::Math::Mat2f& BFW::Math::Mat2f::Fill(const float _Value)
{
	Matrix[0][0] = _Value; Matrix[0][1] = _Value;
	Matrix[1][0] = _Value; Matrix[1][1] = _Value;

	return *this;
}

const BFW::Math::Mat2f BFW::Math::Mat2f::GetFill(const float _Value)
{
	Mat2f _Matrix;

	_Matrix[0][0] = _Value; _Matrix[0][1] = _Value;
	_Matrix[1][0] = _Value; _Matrix[1][1] = _Value;

	return _Matrix;
}

const BFW::Math::Mat2f& BFW::Math::Mat2f::Shear(const float _Value, const unsigned long _ShearedAxis, const unsigned long _ByAxis)
{
	Matrix[0][0] = 1.0f; Matrix[0][1] = 0.0f;
	Matrix[1][0] = 0.0f; Matrix[1][1] = 1.0f;

	Matrix[_ShearedAxis][_ByAxis] = _Value;

	return *this;
}

const BFW::Math::Mat2f BFW::Math::Mat2f::GetShear(const float _Value, const unsigned long _ShearedAxis, const unsigned long _ByAxis)
{
	Mat2f _Matrix;

	_Matrix[0][0] = 1.0f; _Matrix[0][1] = 0.0f;
	_Matrix[1][0] = 0.0f; _Matrix[1][1] = 1.0f;

	_Matrix[_ShearedAxis][_ByAxis] = _Value;

	return _Matrix;
}

const BFW::Math::Mat2f& BFW::Math::Mat2f::Rotation(const float _Angle)
{
	float _Sin = fSin(_Angle);
	float _Cos = fCos(_Angle);

	Matrix[0][0] = _Cos; Matrix[0][1] = -_Sin;
	Matrix[1][0] = _Sin; Matrix[1][1] = _Cos;

	return *this;
}

const BFW::Math::Mat2f BFW::Math::Mat2f::GetRotation(const float _Angle)
{
	float _Sin = fSin(_Angle);
	float _Cos = fCos(_Angle);

	Mat2f _Matrix;

	_Matrix[0][0] = _Cos; _Matrix[0][1] = -_Sin;
	_Matrix[1][0] = _Sin; _Matrix[1][1] = _Cos;

	return _Matrix;
}

const BFW::Math::Mat2f& BFW::Math::Mat2f::Flip(const Vec2f& _U)
{
	float _Angle = _U.GetAngle() * 2.0f;
	float _Sin = fSin(_Angle);
	float _Cos = fCos(_Angle);

	Matrix[0][0] = _Cos; Matrix[0][1] = _Sin;
	Matrix[1][0] = _Sin; Matrix[1][1] = -_Cos;

	return *this;
}

const BFW::Math::Mat2f BFW::Math::Mat2f::GetFlip(const Vec2f& _U)
{
	float _Angle = _U.GetAngle() * 2.0f;
	float _Sin = fSin(_Angle);
	float _Cos = fCos(_Angle);

	Mat2f _Matrix;

	_Matrix[0][0] = _Cos; _Matrix[0][1] = _Sin;
	_Matrix[1][0] = _Sin; _Matrix[1][1] = -_Cos;

	return _Matrix;
}

const BFW::Math::Mat2f& BFW::Math::Mat2f::operator+ () const
{
	return *this;
}

const BFW::Math::Mat2f BFW::Math::Mat2f::operator- () const
{
	Mat2f _Matrix;

	_Matrix[0][0] = -Matrix[0][0]; _Matrix[0][1] = -Matrix[0][1];
	_Matrix[1][0] = -Matrix[1][0]; _Matrix[1][1] = -Matrix[1][1];

	return _Matrix;
}

const BFW::Math::Vec2f BFW::Math::Mat2f::operator* (const Vec2f& _Vec) const
{
	float _x = _Vec.x * Matrix[0][0] + _Vec.y * Matrix[0][1];
	float _y = _Vec.x * Matrix[1][0] + _Vec.y * Matrix[1][1];

	return Vec2f(_x, _y);
}

const BFW::Math::Mat2f BFW::Math::Mat2f::operator+ (const Mat2f& _Other) const
{
	Mat2f _Matrix;

	_Matrix[0][0] = Matrix[0][0] + _Other[0][0]; _Matrix[0][1] = Matrix[0][1] + _Other[0][1];
	_Matrix[1][0] = Matrix[1][0] + _Other[1][0]; _Matrix[1][1] = Matrix[1][1] + _Other[1][1];

	return _Matrix;
}

const BFW::Math::Mat2f& BFW::Math::Mat2f::operator+= (const Mat2f& _Other)
{
	Matrix[0][0] += _Other[0][0]; Matrix[0][1] += _Other[0][1];
	Matrix[1][0] += _Other[1][0]; Matrix[1][1] += _Other[1][1];

	return *this;
}

const BFW::Math::Mat2f BFW::Math::Mat2f::operator+ (const float _Scale) const
{
	Mat2f _Matrix;

	_Matrix[0][0] = Matrix[0][0] + _Scale; _Matrix[0][1] = Matrix[0][1] + _Scale;
	_Matrix[1][0] = Matrix[1][0] + _Scale; _Matrix[1][1] = Matrix[1][1] + _Scale;

	return _Matrix;
}

const BFW::Math::Mat2f& BFW::Math::Mat2f::operator+= (const float _Scale)
{
	Matrix[0][0] += _Scale; Matrix[0][1] += _Scale;
	Matrix[1][0] += _Scale; Matrix[1][1] += _Scale;

	return *this;
}

const BFW::Math::Mat2f BFW::Math::Mat2f::operator- (const Mat2f& _Other) const
{
	Mat2f _Matrix;

	_Matrix[0][0] = Matrix[0][0] - _Other[0][0]; _Matrix[0][1] = Matrix[0][1] - _Other[0][1];
	_Matrix[1][0] = Matrix[1][0] - _Other[1][0]; _Matrix[1][1] = Matrix[1][1] - _Other[1][1];

	return _Matrix;
}

const BFW::Math::Mat2f& BFW::Math::Mat2f::operator-= (const Mat2f& _Other)
{
	Matrix[0][0] -= _Other[0][0]; Matrix[0][1] -= _Other[0][1];
	Matrix[1][0] -= _Other[1][0]; Matrix[1][1] -= _Other[1][1];

	return *this;
}

const BFW::Math::Mat2f BFW::Math::Mat2f::operator- (const float _Scale) const
{
	Mat2f _Matrix;

	_Matrix[0][0] = Matrix[0][0] - _Scale; _Matrix[0][1] = Matrix[0][1] - _Scale;
	_Matrix[1][0] = Matrix[1][0] - _Scale; _Matrix[1][1] = Matrix[1][1] - _Scale;

	return _Matrix;
}

const BFW::Math::Mat2f& BFW::Math::Mat2f::operator-= (const float _Scale)
{
	Matrix[0][0] -= _Scale; Matrix[0][1] -= _Scale;
	Matrix[1][0] -= _Scale; Matrix[1][1] -= _Scale;

	return *this;
}

const BFW::Math::Mat2f BFW::Math::Mat2f::operator* (const Mat2f& _Other) const
{
	Mat2f _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Other[0][0] + Matrix[0][1] * _Other[1][0];
	_Matrix[0][1] = Matrix[0][0] * _Other[0][1] + Matrix[0][1] * _Other[1][1];
	_Matrix[1][0] = Matrix[1][0] * _Other[0][0] + Matrix[1][1] * _Other[1][0];
	_Matrix[1][1] = Matrix[1][0] * _Other[0][1] + Matrix[1][1] * _Other[1][1];

	return _Matrix;
}

const BFW::Math::Mat2f& BFW::Math::Mat2f::operator*= (const Mat2f& _Other)
{
	Mat2f _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Other[0][0] + Matrix[0][1] * _Other[1][0];
	_Matrix[0][1] = Matrix[0][0] * _Other[0][1] + Matrix[0][1] * _Other[1][1];
	_Matrix[1][0] = Matrix[1][0] * _Other[0][0] + Matrix[1][1] * _Other[1][0];
	_Matrix[1][1] = Matrix[1][0] * _Other[0][1] + Matrix[1][1] * _Other[1][1];

	*this = _Matrix;

	return *this;
}

const BFW::Math::Mat2f BFW::Math::Mat2f::operator* (const float _Scale) const
{
	Mat2f _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Scale; _Matrix[0][1] = Matrix[0][1] * _Scale;
	_Matrix[1][0] = Matrix[1][0] * _Scale; _Matrix[1][1] = Matrix[1][1] * _Scale;

	return _Matrix;
}

const BFW::Math::Mat2f& BFW::Math::Mat2f::operator*= (const float _Scale)
{
	Matrix[0][0] *= _Scale; Matrix[0][1] *= _Scale;
	Matrix[1][0] *= _Scale; Matrix[1][1] *= _Scale;

	return *this;
}

const BFW::Math::Mat2f BFW::Math::Mat2f::operator/ (const float _Scale) const
{
	Mat2f _Matrix;

	_Matrix[0][0] = Matrix[0][0] / _Scale; _Matrix[0][1] = Matrix[0][1] / _Scale;
	_Matrix[1][0] = Matrix[1][0] / _Scale; _Matrix[1][1] = Matrix[1][1] / _Scale;

	return _Matrix;
}

const BFW::Math::Mat2f& BFW::Math::Mat2f::operator/= (const float _Scale)
{
	Matrix[0][0] /= _Scale; Matrix[0][1] /= _Scale;
	Matrix[1][0] /= _Scale; Matrix[1][1] /= _Scale;

	return *this;
}

const bool BFW::Math::Mat2f::operator== (const Mat2f& _Other) const
{
	return
		Matrix[0][0] == _Other[0][0] && Matrix[0][1] == _Other[0][1] &&
		Matrix[1][0] == _Other[1][0] && Matrix[1][1] == _Other[1][1];
}

const bool BFW::Math::Mat2f::operator!= (const Mat2f& _Other) const
{
	return
		Matrix[0][0] != _Other[0][0] || Matrix[0][1] != _Other[0][1] ||
		Matrix[1][0] != _Other[1][0] || Matrix[1][1] != _Other[1][1];
}

const bool BFW::Math::Mat2f::operator> (const Mat2f& _Other) const
{
	return Determinant() > _Other.Determinant();
}

const bool BFW::Math::Mat2f::operator>= (const Mat2f& _Other) const
{
	return Determinant() >= _Other.Determinant();
}

const bool BFW::Math::Mat2f::operator< (const Mat2f& _Other) const
{
	return Determinant() < _Other.Determinant();
}

const bool BFW::Math::Mat2f::operator<= (const Mat2f& _Other) const
{
	return Determinant() <= _Other.Determinant();
}

float* BFW::Math::Mat2f::operator[] (const unsigned long _Index)
{
	return Matrix[_Index].Data();
}

const float* BFW::Math::Mat2f::operator[] (const unsigned long _Index) const
{
	return Matrix[_Index].Data();
}

const BFW::Math::Mat2f& BFW::Math::Mat2f::operator= (const Mat2f& _Other)
{
	Matrix[0][0] = _Other.Matrix[0][0]; Matrix[0][1] = _Other.Matrix[0][1];
	Matrix[1][0] = _Other.Matrix[1][0]; Matrix[1][1] = _Other.Matrix[1][1];

	return *this;
}

const BFW::Math::Mat2f& BFW::Math::Mat2f::operator= (Mat2f&& _Other) noexcept
{
	Matrix[0][0] = _Other.Matrix[0][0]; Matrix[0][1] = _Other.Matrix[0][1];
	Matrix[1][0] = _Other.Matrix[1][0]; Matrix[1][1] = _Other.Matrix[1][1];

	_Other.Matrix[0][0] = 1.0f; _Other.Matrix[0][1] = 0.0f;
	_Other.Matrix[1][0] = 0.0f; _Other.Matrix[1][1] = 1.0f;

	return *this;
}



BFW::Math::Mat3f::Mat3f() : Matrix()
{
	Matrix[0][0] = 1.0f; Matrix[0][1] = 0.0f; Matrix[0][2] = 0.0f;
	Matrix[1][0] = 0.0f; Matrix[1][1] = 1.0f; Matrix[1][2] = 0.0f;
	Matrix[2][0] = 0.0f; Matrix[2][1] = 0.0f; Matrix[2][2] = 1.0f;
}

BFW::Math::Mat3f::Mat3f(const float _x, const float _y, const float _z) : Matrix()
{
	Matrix[0][0] = _x; Matrix[0][1] = 0.0f; Matrix[0][2] = 0.0f;
	Matrix[1][0] = 0.0f; Matrix[1][1] = _y; Matrix[1][2] = 0.0f;
	Matrix[2][0] = 0.0f; Matrix[2][1] = 0.0f; Matrix[2][2] = _z;
}

BFW::Math::Mat3f::Mat3f(const Mat3f& _Other) : Matrix()
{
	Matrix[0][0] = _Other.Matrix[0][0]; Matrix[0][1] = _Other.Matrix[0][1]; Matrix[0][2] = _Other.Matrix[0][2];
	Matrix[1][0] = _Other.Matrix[1][0]; Matrix[1][1] = _Other.Matrix[1][1]; Matrix[1][2] = _Other.Matrix[1][2];
	Matrix[2][0] = _Other.Matrix[2][0]; Matrix[2][1] = _Other.Matrix[2][1]; Matrix[2][2] = _Other.Matrix[2][2];
}

BFW::Math::Mat3f::Mat3f(Mat3f&& _Other) noexcept : Matrix()
{
	Matrix[0][0] = _Other.Matrix[0][0]; Matrix[0][1] = _Other.Matrix[0][1]; Matrix[0][2] = _Other.Matrix[0][2];
	Matrix[1][0] = _Other.Matrix[1][0]; Matrix[1][1] = _Other.Matrix[1][1]; Matrix[1][2] = _Other.Matrix[1][2];
	Matrix[2][0] = _Other.Matrix[2][0]; Matrix[2][1] = _Other.Matrix[2][1]; Matrix[2][2] = _Other.Matrix[2][2];

	_Other.Matrix[0][0] = 1.0f; _Other.Matrix[0][1] = 0.0f; _Other.Matrix[0][2] = 0.0f;
	_Other.Matrix[1][0] = 0.0f; _Other.Matrix[1][1] = 1.0f; _Other.Matrix[1][2] = 0.0f;
	_Other.Matrix[2][0] = 0.0f; _Other.Matrix[2][1] = 0.0f; _Other.Matrix[2][2] = 1.0f;
}

BFW::Math::Mat3f::~Mat3f()
{

}

float* BFW::Math::Mat3f::Data()
{
	return Matrix[0].Data();
}

const float* BFW::Math::Mat3f::Data() const
{
	return Matrix[0].Data();
}

const float BFW::Math::Mat3f::Determinant() const
{
	return
		Matrix[0][0] * Matrix[1][1] * Matrix[2][2] +
		Matrix[0][2] * Matrix[1][0] * Matrix[2][1] +
		Matrix[0][1] * Matrix[1][2] * Matrix[2][0] -
		Matrix[0][2] * Matrix[1][1] * Matrix[2][0] -
		Matrix[0][0] * Matrix[1][2] * Matrix[2][1] -
		Matrix[0][1] * Matrix[1][0] * Matrix[2][2];
}

const float BFW::Math::Mat3f::Trace() const
{
	return Matrix[0][0] + Matrix[1][1] + Matrix[2][2];
}

const BFW::Math::Mat3f& BFW::Math::Mat3f::Transpose()
{
	fSwap(Matrix[0][1], Matrix[1][0]);
	fSwap(Matrix[0][2], Matrix[2][0]);
	fSwap(Matrix[1][2], Matrix[2][1]);

	return *this;
}

const BFW::Math::Mat3f BFW::Math::Mat3f::Transposed() const
{
	Mat3f _Matrix;

	_Matrix[0][0] = Matrix[0][0]; _Matrix[0][1] = Matrix[1][0]; _Matrix[0][2] = Matrix[2][0];
	_Matrix[1][0] = Matrix[0][1]; _Matrix[1][1] = Matrix[1][1]; _Matrix[1][2] = Matrix[2][1];
	_Matrix[2][0] = Matrix[0][2]; _Matrix[2][1] = Matrix[1][2]; _Matrix[2][2] = Matrix[2][2];

	return _Matrix;
}

const BFW::Math::Mat3f& BFW::Math::Mat3f::Scale(const float _x, const float _y, const float _z)
{
	Matrix[0][0] = _x; Matrix[0][1] = 0.0f; Matrix[0][2] = 0.0f;
	Matrix[1][0] = 0.0f; Matrix[1][1] = _y; Matrix[1][2] = 0.0f;
	Matrix[2][0] = 0.0f; Matrix[2][1] = 0.0f; Matrix[2][2] = _z;

	return *this;
}

const BFW::Math::Mat3f BFW::Math::Mat3f::GetScale(const float _x, const float _y, const float _z)
{
	Mat3f _Matrix;

	_Matrix[0][0] = _x; _Matrix[0][1] = 0.0f; _Matrix[0][2] = 0.0f;
	_Matrix[1][0] = 0.0f; _Matrix[1][1] = _y; _Matrix[1][2] = 0.0f;
	_Matrix[2][0] = 0.0f; _Matrix[2][1] = 0.0f; _Matrix[2][2] = _z;

	return _Matrix;
}

const BFW::Math::Mat3f& BFW::Math::Mat3f::Fill(const float _Value)
{
	Matrix[0][0] = _Value; Matrix[0][1] = _Value; Matrix[0][2] = _Value;
	Matrix[1][0] = _Value; Matrix[1][1] = _Value; Matrix[1][2] = _Value;
	Matrix[2][0] = _Value; Matrix[2][1] = _Value; Matrix[2][2] = _Value;

	return *this;
}

const BFW::Math::Mat3f BFW::Math::Mat3f::GetFill(const float _Value)
{
	Mat3f _Matrix;

	_Matrix[0][0] = _Value; _Matrix[0][1] = _Value; _Matrix[0][2] = _Value;
	_Matrix[1][0] = _Value; _Matrix[1][1] = _Value; _Matrix[1][2] = _Value;
	_Matrix[2][0] = _Value; _Matrix[2][1] = _Value; _Matrix[2][2] = _Value;

	return _Matrix;
}

const BFW::Math::Mat3f& BFW::Math::Mat3f::Shear(const float _Value, const unsigned long _ShearedAxis, const unsigned long _ByAxis)
{
	Matrix[0][0] = 1.0f; Matrix[0][1] = 0.0f; Matrix[0][2] = 0.0f;
	Matrix[1][0] = 0.0f; Matrix[1][1] = 1.0f; Matrix[1][2] = 0.0f;
	Matrix[2][0] = 0.0f; Matrix[2][1] = 0.0f; Matrix[2][2] = 1.0f;

	Matrix[_ShearedAxis][_ByAxis] = _Value;

	return *this;
}

const BFW::Math::Mat3f BFW::Math::Mat3f::GetShear(const float _Value, const unsigned long _ShearedAxis, const unsigned long _ByAxis)
{
	Mat3f _Matrix;

	_Matrix[0][0] = 1.0f; _Matrix[0][1] = 0.0f; _Matrix[0][2] = 0.0f;
	_Matrix[1][0] = 0.0f; _Matrix[1][1] = 1.0f; _Matrix[1][2] = 0.0f;
	_Matrix[2][0] = 0.0f; _Matrix[2][1] = 0.0f; _Matrix[2][2] = 1.0f;

	_Matrix[_ShearedAxis][_ByAxis] = _Value;

	return _Matrix;
}

const BFW::Math::Mat3f& BFW::Math::Mat3f::Rotation(const float _Angle, const Vec3f& _U)
{
	float _Sin = fSin(_Angle);
	float _Cos = fCos(_Angle);

	Matrix[0][0] = _Cos + _U.x * _U.x * (1.0f - _Cos); Matrix[0][1] = _U.x * _U.y * (1.0f - _Cos) - _U.z * _Sin; Matrix[0][2] = _U.x * _U.z * (1.0f - _Cos) + _U.y * _Sin;
	Matrix[1][0] = _U.y * _U.x * (1.0f - _Cos) + _U.z * _Sin; Matrix[1][1] = _Cos + _U.y * _U.y * (1.0f - _Cos); Matrix[1][2] = _U.y * _U.z * (1.0f - _Cos) - _U.x * _Sin;
	Matrix[2][0] = _U.z * _U.x * (1.0f - _Cos) - _U.y * _Sin; Matrix[2][1] = _U.z * _U.y * (1.0f - _Cos) + _U.x * _Sin; Matrix[2][2] = _Cos + _U.z * _U.z * (1.0f - _Cos);

	return *this;
}

const BFW::Math::Mat3f BFW::Math::Mat3f::GetRotation(const float _Angle, const Vec3f& _U)
{
	float _Sin = fSin(_Angle);
	float _Cos = fCos(_Angle);

	Mat3f _Matrix;

	_Matrix[0][0] = _Cos + _U.x * _U.x * (1.0f - _Cos); _Matrix[0][1] = _U.x * _U.y * (1.0f - _Cos) - _U.z * _Sin; _Matrix[0][2] = _U.x * _U.z * (1.0f - _Cos) + _U.y * _Sin;
	_Matrix[1][0] = _U.y * _U.x * (1.0f - _Cos) + _U.z * _Sin; _Matrix[1][1] = _Cos + _U.y * _U.y * (1.0f - _Cos); _Matrix[1][2] = _U.y * _U.z * (1.0f - _Cos) - _U.x * _Sin;
	_Matrix[2][0] = _U.z * _U.x * (1.0f - _Cos) - _U.y * _Sin; _Matrix[2][1] = _U.z * _U.y * (1.0f - _Cos) + _U.x * _Sin; _Matrix[2][2] = _Cos + _U.z * _U.z * (1.0f - _Cos);

	return _Matrix;
}

const BFW::Math::Mat3f& BFW::Math::Mat3f::Translation(const Vec3f& _V)
{
	Matrix[0][0] = 1.0f; Matrix[0][1] = 0.0f; Matrix[0][2] = _V.x;
	Matrix[1][0] = 0.0f; Matrix[1][1] = 1.0f; Matrix[1][2] = _V.y;
	Matrix[2][0] = 0.0f; Matrix[2][1] = 0.0f; Matrix[2][2] = 1.0f;

	return *this;
}

const BFW::Math::Mat3f BFW::Math::Mat3f::GetTranslation(const Vec3f& _V)
{
	Mat3f _Matrix;

	_Matrix[0][0] = 1.0f; _Matrix[0][1] = 0.0f; _Matrix[0][2] = _V.x;
	_Matrix[1][0] = 0.0f; _Matrix[1][1] = 1.0f; _Matrix[1][2] = _V.y;
	_Matrix[2][0] = 0.0f; _Matrix[2][1] = 0.0f; _Matrix[2][2] = 1.0f;

	return _Matrix;
}

const BFW::Math::Mat3f& BFW::Math::Mat3f::Ortho(const float _Left, const float _Right, const float _Top, const float _Bottom)
{
	Matrix[0][0] = 2.0f / (_Right - _Left); Matrix[0][1] = 0.0f; Matrix[0][2] = (_Right + _Left) / (_Left - _Right);
	Matrix[1][0] = 0.0f; Matrix[1][1] = 2.0f / (_Top - _Bottom); Matrix[1][2] = Matrix[1][2] = (_Top + _Bottom) / (_Bottom - _Top);
	Matrix[2][0] = 0.0f; Matrix[2][1] = 0.0f; Matrix[2][2] = 1.0f;

	return *this;
}

const BFW::Math::Mat3f BFW::Math::Mat3f::GetOrtho(const float _Left, const float _Right, const float _Top, const float _Bottom)
{
	Mat3f _Matrix;

	_Matrix[0][0] = 2.0f / (_Right - _Left); _Matrix[0][1] = 0.0f; _Matrix[0][2] = (_Right + _Left) / (_Left - _Right);
	_Matrix[1][0] = 0.0f; _Matrix[1][1] = 2.0f / (_Top - _Bottom); _Matrix[1][2] = _Matrix[1][2] = (_Top + _Bottom) / (_Bottom - _Top);
	_Matrix[2][0] = 0.0f; _Matrix[2][1] = 0.0f; _Matrix[2][2] = 1.0f;

	return _Matrix;
}

const BFW::Math::Mat3f& BFW::Math::Mat3f::Flip(const Vec3f& _U, const Vec3f& _Center)
{
	float _Angle = _U.GetAngle() * 2.0f;
	float _Sin = fSin(_Angle);
	float _Cos = fCos(_Angle);

	Matrix[0][0] = _Cos; Matrix[0][1] = _Sin; Matrix[0][2] = 0.0f;
	Matrix[1][0] = _Sin; Matrix[1][1] = -_Cos; Matrix[1][2] = 0.0f;
	Matrix[2][0] = 0.0f; Matrix[2][1] = 0.0f; Matrix[2][2] = 1.0f;

	*this = GetTranslation(_Center) * (*this) * GetTranslation(-_Center);

	return *this;
}

const BFW::Math::Mat3f BFW::Math::Mat3f::GetFlip(const Vec3f& _U, const Vec3f& _Center)
{
	float _Angle = _U.GetAngle() * 2.0f;
	float _Sin = fSin(_Angle);
	float _Cos = fCos(_Angle);

	Mat3f _Matrix;

	_Matrix[0][0] = _Cos; _Matrix[0][1] = _Sin; _Matrix[0][2] = 0.0f;
	_Matrix[1][0] = _Sin; _Matrix[1][1] = -_Cos; _Matrix[1][2] = 0.0f;
	_Matrix[2][0] = 0.0f; _Matrix[2][1] = 0.0f; _Matrix[2][2] = 1.0f;

	_Matrix = GetTranslation(_Center) * _Matrix * GetTranslation(-_Center);

	return _Matrix;
}

const BFW::Math::Mat3f& BFW::Math::Mat3f::Flip(const Vec3f& _U)
{
	Matrix[0][0] = 1.0f - 2.0f * _U.x * _U.x; Matrix[0][1] = -2.0f * _U.x * _U.y; Matrix[0][2] = -2.0f * _U.x * _U.z;
	Matrix[1][0] = -2.0f * _U.x * _U.y; Matrix[1][1] = 1.0f - 2.0f * _U.y * _U.y; Matrix[1][2] = -2.0f * _U.y * _U.z;
	Matrix[2][0] = -2.0f * _U.x * _U.z; Matrix[2][1] = -2.0f * _U.y * _U.z; Matrix[2][2] = 1.0f - 2.0f * _U.z * _U.z;

	return *this;
}

const BFW::Math::Mat3f BFW::Math::Mat3f::GetFlip(const Vec3f& _U)
{
	Mat3f _Matrix;

	_Matrix[0][0] = 1.0f - 2.0f * _U.x * _U.x; _Matrix[0][1] = -2.0f * _U.x * _U.y; _Matrix[0][2] = -2.0f * _U.x * _U.z;
	_Matrix[1][0] = -2.0f * _U.x * _U.y; _Matrix[1][1] = 1.0f - 2.0f * _U.y * _U.y; _Matrix[1][2] = -2.0f * _U.y * _U.z;
	_Matrix[2][0] = -2.0f * _U.x * _U.z; _Matrix[2][1] = -2.0f * _U.y * _U.z; _Matrix[2][2] = 1.0f - 2.0f * _U.z * _U.z;

	return _Matrix;
}

const BFW::Math::Mat3f& BFW::Math::Mat3f::operator+ () const
{
	return *this;
}

const BFW::Math::Mat3f BFW::Math::Mat3f::operator- () const
{
	Mat3f _Matrix;

	_Matrix[0][0] = -Matrix[0][0]; _Matrix[0][1] = -Matrix[0][1]; _Matrix[0][2] = -Matrix[0][2];
	_Matrix[1][0] = -Matrix[1][0]; _Matrix[1][1] = -Matrix[1][1]; _Matrix[1][2] = -Matrix[1][2];
	_Matrix[2][0] = -Matrix[2][0]; _Matrix[2][1] = -Matrix[2][1]; _Matrix[2][2] = -Matrix[2][2];

	return _Matrix;
}

const BFW::Math::Vec3f BFW::Math::Mat3f::operator* (const Vec3f& _Vec) const
{
	float _x = _Vec.x * Matrix[0][0] + _Vec.y * Matrix[0][1] + _Vec.z * Matrix[0][2];
	float _y = _Vec.x * Matrix[1][0] + _Vec.y * Matrix[1][1] + _Vec.z * Matrix[1][2];
	float _z = _Vec.x * Matrix[2][0] + _Vec.y * Matrix[2][1] + _Vec.z * Matrix[2][2];

	return Vec3f(_x, _y, _z);
}

const BFW::Math::Mat3f BFW::Math::Mat3f::operator+ (const Mat3f& _Other) const
{
	Mat3f _Matrix;

	_Matrix[0][0] = Matrix[0][0] + _Other[0][0]; _Matrix[0][1] = Matrix[0][1] + _Other[0][1]; _Matrix[0][2] = Matrix[0][2] + _Other[0][2];
	_Matrix[1][0] = Matrix[1][0] + _Other[1][0]; _Matrix[1][1] = Matrix[1][1] + _Other[1][1]; _Matrix[1][2] = Matrix[1][2] + _Other[1][2];
	_Matrix[2][0] = Matrix[2][0] + _Other[2][0]; _Matrix[2][1] = Matrix[2][1] + _Other[2][1]; _Matrix[2][2] = Matrix[2][2] + _Other[2][2];

	return _Matrix;
}

const BFW::Math::Mat3f& BFW::Math::Mat3f::operator+= (const Mat3f& _Other)
{
	Matrix[0][0] += _Other[0][0]; Matrix[0][1] += _Other[0][1]; Matrix[0][2] += _Other[0][2];
	Matrix[1][0] += _Other[1][0]; Matrix[1][1] += _Other[1][1]; Matrix[1][2] += _Other[1][2];
	Matrix[2][0] += _Other[2][0]; Matrix[2][1] += _Other[2][1]; Matrix[2][2] += _Other[2][2];

	return *this;
}

const BFW::Math::Mat3f BFW::Math::Mat3f::operator+ (const float _Scale) const
{
	Mat3f _Matrix;

	_Matrix[0][0] = Matrix[0][0] + _Scale; _Matrix[0][1] = Matrix[0][1] + _Scale; _Matrix[0][2] = Matrix[0][2] + _Scale;
	_Matrix[1][0] = Matrix[1][0] + _Scale; _Matrix[1][1] = Matrix[1][1] + _Scale; _Matrix[1][2] = Matrix[1][2] + _Scale;
	_Matrix[2][0] = Matrix[2][0] + _Scale; _Matrix[2][1] = Matrix[2][1] + _Scale; _Matrix[2][2] = Matrix[2][2] + _Scale;

	return _Matrix;
}

const BFW::Math::Mat3f& BFW::Math::Mat3f::operator+= (const float _Scale)
{
	Matrix[0][0] += _Scale; Matrix[0][1] += _Scale; Matrix[0][2] += _Scale;
	Matrix[1][0] += _Scale; Matrix[1][1] += _Scale; Matrix[1][2] += _Scale;
	Matrix[2][0] += _Scale; Matrix[2][1] += _Scale; Matrix[2][2] += _Scale;

	return *this;
}

const BFW::Math::Mat3f BFW::Math::Mat3f::operator- (const Mat3f& _Other) const
{
	Mat3f _Matrix;

	_Matrix[0][0] = Matrix[0][0] - _Other[0][0]; _Matrix[0][1] = Matrix[0][1] - _Other[0][1]; _Matrix[0][2] = Matrix[0][2] - _Other[0][2];
	_Matrix[1][0] = Matrix[1][0] - _Other[1][0]; _Matrix[1][1] = Matrix[1][1] - _Other[1][1]; _Matrix[1][2] = Matrix[1][2] - _Other[1][2];
	_Matrix[2][0] = Matrix[2][0] - _Other[2][0]; _Matrix[2][1] = Matrix[2][1] - _Other[2][1]; _Matrix[2][2] = Matrix[2][2] - _Other[2][2];

	return _Matrix;
}

const BFW::Math::Mat3f& BFW::Math::Mat3f::operator-= (const Mat3f& _Other)
{
	Matrix[0][0] -= _Other[0][0]; Matrix[0][1] -= _Other[0][1]; Matrix[0][2] -= _Other[0][2];
	Matrix[1][0] -= _Other[1][0]; Matrix[1][1] -= _Other[1][1]; Matrix[1][2] -= _Other[1][2];
	Matrix[2][0] -= _Other[2][0]; Matrix[2][1] -= _Other[2][1]; Matrix[2][2] -= _Other[2][2];

	return *this;
}

const BFW::Math::Mat3f BFW::Math::Mat3f::operator- (const float _Scale) const
{
	Mat3f _Matrix;

	_Matrix[0][0] = Matrix[0][0] - _Scale; _Matrix[0][1] = Matrix[0][1] - _Scale; _Matrix[0][2] = Matrix[0][2] - _Scale;
	_Matrix[1][0] = Matrix[1][0] - _Scale; _Matrix[1][1] = Matrix[1][1] - _Scale; _Matrix[1][2] = Matrix[1][2] - _Scale;
	_Matrix[2][0] = Matrix[2][0] - _Scale; _Matrix[2][1] = Matrix[2][1] - _Scale; _Matrix[2][2] = Matrix[2][2] - _Scale;

	return _Matrix;
}

const BFW::Math::Mat3f& BFW::Math::Mat3f::operator-= (const float _Scale)
{
	Matrix[0][0] -= _Scale; Matrix[0][1] -= _Scale; Matrix[0][2] -= _Scale;
	Matrix[1][0] -= _Scale; Matrix[1][1] -= _Scale; Matrix[1][2] -= _Scale;
	Matrix[2][0] -= _Scale; Matrix[2][1] -= _Scale; Matrix[2][2] -= _Scale;

	return *this;
}

const BFW::Math::Mat3f BFW::Math::Mat3f::operator* (const Mat3f& _Other) const
{
	Mat3f _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Other[0][0] + Matrix[0][1] * _Other[1][0] + Matrix[0][2] * _Other[2][0];
	_Matrix[0][1] = Matrix[0][0] * _Other[0][1] + Matrix[0][1] * _Other[1][1] + Matrix[0][2] * _Other[2][1];
	_Matrix[0][2] = Matrix[0][0] * _Other[0][2] + Matrix[0][1] * _Other[1][2] + Matrix[0][2] * _Other[2][2];

	_Matrix[1][0] = Matrix[1][0] * _Other[0][0] + Matrix[1][1] * _Other[1][0] + Matrix[1][2] * _Other[2][0];
	_Matrix[1][1] = Matrix[1][0] * _Other[0][1] + Matrix[1][1] * _Other[1][1] + Matrix[1][2] * _Other[2][1];
	_Matrix[1][2] = Matrix[1][0] * _Other[0][2] + Matrix[1][1] * _Other[1][2] + Matrix[1][2] * _Other[2][2];

	_Matrix[2][0] = Matrix[2][0] * _Other[0][0] + Matrix[2][1] * _Other[1][0] + Matrix[2][2] * _Other[2][0];
	_Matrix[2][1] = Matrix[2][0] * _Other[0][1] + Matrix[2][1] * _Other[1][1] + Matrix[2][2] * _Other[2][1];
	_Matrix[2][2] = Matrix[2][0] * _Other[0][2] + Matrix[2][1] * _Other[1][2] + Matrix[2][2] * _Other[2][2];

	return _Matrix;
}

const BFW::Math::Mat3f& BFW::Math::Mat3f::operator*= (const Mat3f& _Other)
{
	Mat3f _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Other[0][0] + Matrix[0][1] * _Other[1][0] + Matrix[0][2] * _Other[2][0];
	_Matrix[0][1] = Matrix[0][0] * _Other[0][1] + Matrix[0][1] * _Other[1][1] + Matrix[0][2] * _Other[2][1];
	_Matrix[0][2] = Matrix[0][0] * _Other[0][2] + Matrix[0][1] * _Other[1][2] + Matrix[0][2] * _Other[2][2];

	_Matrix[1][0] = Matrix[1][0] * _Other[0][0] + Matrix[1][1] * _Other[1][0] + Matrix[1][2] * _Other[2][0];
	_Matrix[1][1] = Matrix[1][0] * _Other[0][1] + Matrix[1][1] * _Other[1][1] + Matrix[1][2] * _Other[2][1];
	_Matrix[1][2] = Matrix[1][0] * _Other[0][2] + Matrix[1][1] * _Other[1][2] + Matrix[1][2] * _Other[2][2];

	_Matrix[2][0] = Matrix[2][0] * _Other[0][0] + Matrix[2][1] * _Other[1][0] + Matrix[2][2] * _Other[2][0];
	_Matrix[2][1] = Matrix[2][0] * _Other[0][1] + Matrix[2][1] * _Other[1][1] + Matrix[2][2] * _Other[2][1];
	_Matrix[2][2] = Matrix[2][0] * _Other[0][2] + Matrix[2][1] * _Other[1][2] + Matrix[2][2] * _Other[2][2];

	*this = _Matrix;

	return *this;
}

const BFW::Math::Mat3f BFW::Math::Mat3f::operator* (const float _Scale) const
{
	Mat3f _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Scale; _Matrix[0][1] = Matrix[0][1] * _Scale; _Matrix[0][2] = Matrix[0][2] * _Scale;
	_Matrix[1][0] = Matrix[1][0] * _Scale; _Matrix[1][1] = Matrix[1][1] * _Scale; _Matrix[1][2] = Matrix[1][2] * _Scale;
	_Matrix[2][0] = Matrix[2][0] * _Scale; _Matrix[2][1] = Matrix[2][1] * _Scale; _Matrix[2][2] = Matrix[2][2] * _Scale;

	return _Matrix;
}

const BFW::Math::Mat3f& BFW::Math::Mat3f::operator*= (const float _Scale)
{
	Matrix[0][0] *= _Scale; Matrix[0][1] *= _Scale; Matrix[0][2] *= _Scale;
	Matrix[1][0] *= _Scale; Matrix[1][1] *= _Scale; Matrix[1][2] *= _Scale;
	Matrix[2][0] *= _Scale; Matrix[2][1] *= _Scale; Matrix[2][2] *= _Scale;

	return *this;
}

const BFW::Math::Mat3f BFW::Math::Mat3f::operator/ (const float _Scale) const
{
	Mat3f _Matrix;

	_Matrix[0][0] = Matrix[0][0] / _Scale; _Matrix[0][1] = Matrix[0][1] / _Scale; _Matrix[0][2] = Matrix[0][2] / _Scale;
	_Matrix[1][0] = Matrix[1][0] / _Scale; _Matrix[1][1] = Matrix[1][1] / _Scale; _Matrix[1][2] = Matrix[1][2] / _Scale;
	_Matrix[2][0] = Matrix[2][0] / _Scale; _Matrix[2][1] = Matrix[2][1] / _Scale; _Matrix[2][2] = Matrix[2][2] / _Scale;

	return _Matrix;
}

const BFW::Math::Mat3f& BFW::Math::Mat3f::operator/= (const float _Scale)
{
	Matrix[0][0] /= _Scale; Matrix[0][1] /= _Scale; Matrix[0][2] /= _Scale;
	Matrix[1][0] /= _Scale; Matrix[1][1] /= _Scale; Matrix[1][2] /= _Scale;
	Matrix[2][0] /= _Scale; Matrix[2][1] /= _Scale; Matrix[2][2] /= _Scale;

	return *this;
}

const bool BFW::Math::Mat3f::operator== (const Mat3f& _Other) const
{
	return
		Matrix[0][0] == _Other[0][0] && Matrix[0][1] == _Other[0][1] && Matrix[0][2] == _Other[0][2] &&
		Matrix[1][0] == _Other[1][0] && Matrix[1][1] == _Other[1][1] && Matrix[1][2] == _Other[1][2] &&
		Matrix[2][0] == _Other[2][0] && Matrix[2][1] == _Other[2][1] && Matrix[2][2] == _Other[2][2];
}

const bool BFW::Math::Mat3f::operator!= (const Mat3f& _Other) const
{
	return
		Matrix[0][0] != _Other[0][0] || Matrix[0][1] != _Other[0][1] || Matrix[0][2] != _Other[0][2] ||
		Matrix[1][0] != _Other[1][0] || Matrix[1][1] != _Other[1][1] || Matrix[1][2] != _Other[1][2] ||
		Matrix[2][0] != _Other[2][0] || Matrix[2][1] != _Other[2][1] || Matrix[2][2] != _Other[2][2];
}

const bool BFW::Math::Mat3f::operator> (const Mat3f& _Other) const
{
	return Determinant() > _Other.Determinant();
}

const bool BFW::Math::Mat3f::operator>= (const Mat3f& _Other) const
{
	return Determinant() >= _Other.Determinant();
}

const bool BFW::Math::Mat3f::operator< (const Mat3f& _Other) const
{
	return Determinant() < _Other.Determinant();
}

const bool BFW::Math::Mat3f::operator<= (const Mat3f& _Other) const
{
	return Determinant() <= _Other.Determinant();
}

float* BFW::Math::Mat3f::operator[] (const unsigned long _Index)
{
	return Matrix[_Index].Data();
}

const float* BFW::Math::Mat3f::operator[] (const unsigned long _Index) const
{
	return Matrix[_Index].Data();
}

const BFW::Math::Mat3f& BFW::Math::Mat3f::operator= (const Mat3f& _Other)
{
	Matrix[0][0] = _Other.Matrix[0][0]; Matrix[0][1] = _Other.Matrix[0][1]; Matrix[0][2] = _Other.Matrix[0][2];
	Matrix[1][0] = _Other.Matrix[1][0]; Matrix[1][1] = _Other.Matrix[1][1]; Matrix[1][2] = _Other.Matrix[1][2];
	Matrix[2][0] = _Other.Matrix[2][0]; Matrix[2][1] = _Other.Matrix[2][1]; Matrix[2][2] = _Other.Matrix[2][2];

	return *this;
}

const BFW::Math::Mat3f& BFW::Math::Mat3f::operator= (Mat3f&& _Other) noexcept
{
	Matrix[0][0] = _Other.Matrix[0][0]; Matrix[0][1] = _Other.Matrix[0][1]; Matrix[0][2] = _Other.Matrix[0][2];
	Matrix[1][0] = _Other.Matrix[1][0]; Matrix[1][1] = _Other.Matrix[1][1]; Matrix[1][2] = _Other.Matrix[1][2];
	Matrix[2][0] = _Other.Matrix[2][0]; Matrix[2][1] = _Other.Matrix[2][1]; Matrix[2][2] = _Other.Matrix[2][2];

	_Other.Matrix[0][0] = 1.0f; _Other.Matrix[0][1] = 0.0f; _Other.Matrix[0][2] = 0.0f;
	_Other.Matrix[1][0] = 0.0f; _Other.Matrix[1][1] = 1.0f; _Other.Matrix[1][2] = 0.0f;
	_Other.Matrix[2][0] = 0.0f; _Other.Matrix[2][1] = 0.0f; _Other.Matrix[2][2] = 1.0f;

	return *this;
}



BFW::Math::Mat4f::Mat4f() : Matrix()
{
	Matrix[0][0] = 1.0f; Matrix[0][1] = 0.0f; Matrix[0][2] = 0.0f; Matrix[0][3] = 0.0f;
	Matrix[1][0] = 0.0f; Matrix[1][1] = 1.0f; Matrix[1][2] = 0.0f; Matrix[1][3] = 0.0f;
	Matrix[2][0] = 0.0f; Matrix[2][1] = 0.0f; Matrix[2][2] = 1.0f; Matrix[2][3] = 0.0f;
	Matrix[3][0] = 0.0f; Matrix[3][1] = 0.0f; Matrix[3][2] = 0.0f; Matrix[3][3] = 1.0f;
}

BFW::Math::Mat4f::Mat4f(const float _x, const float _y, const float _z) : Matrix()
{
	Matrix[0][0] = _x; Matrix[0][1] = 0.0f; Matrix[0][2] = 0.0f; Matrix[0][3] = 0.0f;
	Matrix[1][0] = 0.0f; Matrix[1][1] = _y; Matrix[1][2] = 0.0f; Matrix[1][3] = 0.0f;
	Matrix[2][0] = 0.0f; Matrix[2][1] = 0.0f; Matrix[2][2] = _z; Matrix[2][3] = 0.0f;
	Matrix[3][0] = 0.0f; Matrix[3][1] = 0.0f; Matrix[3][2] = 0.0f; Matrix[3][3] = 1.0f;
}

BFW::Math::Mat4f::Mat4f(const Mat4f& _Other) : Matrix()
{
	Matrix[0][0] = _Other.Matrix[0][0]; Matrix[0][1] = _Other.Matrix[0][1]; Matrix[0][2] = _Other.Matrix[0][2]; Matrix[0][3] = _Other.Matrix[0][3];
	Matrix[1][0] = _Other.Matrix[1][0]; Matrix[1][1] = _Other.Matrix[1][1]; Matrix[1][2] = _Other.Matrix[1][2]; Matrix[1][3] = _Other.Matrix[1][3];
	Matrix[2][0] = _Other.Matrix[2][0]; Matrix[2][1] = _Other.Matrix[2][1]; Matrix[2][2] = _Other.Matrix[2][2]; Matrix[2][3] = _Other.Matrix[2][3];
	Matrix[3][0] = _Other.Matrix[3][0]; Matrix[3][1] = _Other.Matrix[3][1]; Matrix[3][2] = _Other.Matrix[3][2]; Matrix[3][3] = _Other.Matrix[3][3];
}

BFW::Math::Mat4f::Mat4f(Mat4f&& _Other) noexcept : Matrix()
{
	Matrix[0][0] = _Other.Matrix[0][0]; Matrix[0][1] = _Other.Matrix[0][1]; Matrix[0][2] = _Other.Matrix[0][2]; Matrix[0][3] = _Other.Matrix[0][3];
	Matrix[1][0] = _Other.Matrix[1][0]; Matrix[1][1] = _Other.Matrix[1][1]; Matrix[1][2] = _Other.Matrix[1][2]; Matrix[1][3] = _Other.Matrix[1][3];
	Matrix[2][0] = _Other.Matrix[2][0]; Matrix[2][1] = _Other.Matrix[2][1]; Matrix[2][2] = _Other.Matrix[2][2]; Matrix[2][3] = _Other.Matrix[2][3];
	Matrix[3][0] = _Other.Matrix[3][0]; Matrix[3][1] = _Other.Matrix[3][1]; Matrix[3][2] = _Other.Matrix[3][2]; Matrix[3][3] = _Other.Matrix[3][3];

	_Other.Matrix[0][0] = 1.0f; _Other.Matrix[0][1] = 0.0f; _Other.Matrix[0][2] = 0.0f; _Other.Matrix[0][3] = 0.0f;
	_Other.Matrix[1][0] = 0.0f; _Other.Matrix[1][1] = 1.0f; _Other.Matrix[1][2] = 0.0f; _Other.Matrix[1][3] = 0.0f;
	_Other.Matrix[2][0] = 0.0f; _Other.Matrix[2][1] = 0.0f; _Other.Matrix[2][2] = 1.0f; _Other.Matrix[2][3] = 0.0f;
	_Other.Matrix[3][0] = 0.0f; _Other.Matrix[3][1] = 0.0f; _Other.Matrix[3][2] = 0.0f; _Other.Matrix[3][3] = 1.0f;
}

BFW::Math::Mat4f::~Mat4f()
{

}

float* BFW::Math::Mat4f::Data()
{
	return Matrix[0].Data();
}

const float* BFW::Math::Mat4f::Data() const
{
	return Matrix[0].Data();
}

const float BFW::Math::Mat4f::Determinant() const
{
	Mat3f _Mat[4];

	Mat3f& _Matrix = *((Mat3f*)(nullptr));

	_Matrix = _Mat[0];

	_Matrix[0][0] = Matrix[1][1]; _Matrix[0][1] = Matrix[1][2]; _Matrix[0][2] = Matrix[1][3];
	_Matrix[1][0] = Matrix[2][1]; _Matrix[1][1] = Matrix[2][2]; _Matrix[1][2] = Matrix[2][3];
	_Matrix[2][0] = Matrix[3][1]; _Matrix[2][1] = Matrix[3][2]; _Matrix[2][2] = Matrix[3][3];

	_Matrix = _Mat[1];

	_Matrix[0][0] = Matrix[0][1]; _Matrix[0][1] = Matrix[0][2]; _Matrix[0][2] = Matrix[0][3];
	_Matrix[1][0] = Matrix[2][1]; _Matrix[1][1] = Matrix[2][2]; _Matrix[1][2] = Matrix[2][3];
	_Matrix[2][0] = Matrix[3][1]; _Matrix[2][1] = Matrix[3][2]; _Matrix[2][2] = Matrix[3][3];

	_Matrix = _Mat[2];

	_Matrix[0][0] = Matrix[0][1]; _Matrix[0][1] = Matrix[0][2]; _Matrix[0][2] = Matrix[0][3];
	_Matrix[1][0] = Matrix[1][1]; _Matrix[1][1] = Matrix[1][2]; _Matrix[1][2] = Matrix[1][3];
	_Matrix[2][0] = Matrix[3][1]; _Matrix[2][1] = Matrix[3][2]; _Matrix[2][2] = Matrix[3][3];

	_Matrix = _Mat[3];

	_Matrix[0][0] = Matrix[0][1]; _Matrix[0][1] = Matrix[0][2]; _Matrix[0][2] = Matrix[0][3];
	_Matrix[1][0] = Matrix[1][1]; _Matrix[1][1] = Matrix[1][2]; _Matrix[1][2] = Matrix[1][3];
	_Matrix[2][0] = Matrix[2][1]; _Matrix[2][1] = Matrix[2][2]; _Matrix[2][2] = Matrix[2][3];

	return
		Matrix[0][0] * _Mat[0].Determinant() -
		Matrix[1][0] * _Mat[1].Determinant() +
		Matrix[2][0] * _Mat[2].Determinant() -
		Matrix[3][0] * _Mat[3].Determinant();
}

const float BFW::Math::Mat4f::Trace() const
{
	return Matrix[0][0] + Matrix[1][1] + Matrix[2][2] + Matrix[3][3];
}

const BFW::Math::Mat4f& BFW::Math::Mat4f::Transpose()
{
	fSwap(Matrix[0][1], Matrix[1][0]);
	fSwap(Matrix[0][2], Matrix[2][0]);
	fSwap(Matrix[0][3], Matrix[3][0]);
	fSwap(Matrix[1][2], Matrix[2][1]);
	fSwap(Matrix[1][3], Matrix[3][1]);
	fSwap(Matrix[2][3], Matrix[3][2]);

	return *this;
}

const BFW::Math::Mat4f BFW::Math::Mat4f::Transposed() const
{
	Mat4f _Matrix;

	_Matrix[0][0] = Matrix[0][0]; _Matrix[0][1] = Matrix[1][0]; _Matrix[0][2] = Matrix[2][0]; _Matrix[0][3] = Matrix[3][0];
	_Matrix[1][0] = Matrix[0][1]; _Matrix[1][1] = Matrix[1][1]; _Matrix[1][2] = Matrix[2][1]; _Matrix[1][3] = Matrix[3][1];
	_Matrix[2][0] = Matrix[0][2]; _Matrix[2][1] = Matrix[1][2]; _Matrix[2][2] = Matrix[2][2]; _Matrix[2][3] = Matrix[3][2];
	_Matrix[3][0] = Matrix[0][3]; _Matrix[3][1] = Matrix[1][3]; _Matrix[3][2] = Matrix[2][3]; _Matrix[3][3] = Matrix[3][3];

	return _Matrix;
}

const BFW::Math::Mat4f& BFW::Math::Mat4f::Scale(const float _x, const float _y, const float _z)
{
	Matrix[0][0] = _x; Matrix[0][1] = 0.0f; Matrix[0][2] = 0.0f; Matrix[0][3] = 0.0f;
	Matrix[1][0] = 0.0f; Matrix[1][1] = _y; Matrix[1][2] = 0.0f; Matrix[1][3] = 0.0f;
	Matrix[2][0] = 0.0f; Matrix[2][1] = 0.0f; Matrix[2][2] = _z; Matrix[2][3] = 0.0f;
	Matrix[3][0] = 0.0f; Matrix[3][1] = 0.0f; Matrix[3][2] = 0.0f; Matrix[3][3] = 1.0f;

	return *this;
}

const BFW::Math::Mat4f BFW::Math::Mat4f::GetScale(const float _x, const float _y, const float _z)
{
	Mat4f _Matrix;

	_Matrix[0][0] = _x; _Matrix[0][1] = 0.0f; _Matrix[0][2] = 0.0f; _Matrix[0][3] = 0.0f;
	_Matrix[1][0] = 0.0f; _Matrix[1][1] = _y; _Matrix[1][2] = 0.0f; _Matrix[1][3] = 0.0f;
	_Matrix[2][0] = 0.0f; _Matrix[2][1] = 0.0f; _Matrix[2][2] = _z; _Matrix[2][3] = 0.0f;
	_Matrix[3][0] = 0.0f; _Matrix[3][1] = 0.0f; _Matrix[3][2] = 0.0f; _Matrix[3][3] = 1.0f;

	return _Matrix;
}

const BFW::Math::Mat4f& BFW::Math::Mat4f::Fill(const float _Value)
{
	Matrix[0][0] = _Value; Matrix[0][1] = _Value; Matrix[0][2] = _Value; Matrix[0][3] = _Value;
	Matrix[1][0] = _Value; Matrix[1][1] = _Value; Matrix[1][2] = _Value; Matrix[1][3] = _Value;
	Matrix[2][0] = _Value; Matrix[2][1] = _Value; Matrix[2][2] = _Value; Matrix[2][3] = _Value;
	Matrix[3][0] = _Value; Matrix[3][1] = _Value; Matrix[3][2] = _Value; Matrix[3][3] = _Value;

	return *this;
}

const BFW::Math::Mat4f BFW::Math::Mat4f::GetFill(const float _Value)
{
	Mat4f _Matrix;

	_Matrix[0][0] = _Value; _Matrix[0][1] = _Value; _Matrix[0][2] = _Value; _Matrix[0][3] = _Value;
	_Matrix[1][0] = _Value; _Matrix[1][1] = _Value; _Matrix[1][2] = _Value; _Matrix[1][3] = _Value;
	_Matrix[2][0] = _Value; _Matrix[2][1] = _Value; _Matrix[2][2] = _Value; _Matrix[2][3] = _Value;
	_Matrix[3][0] = _Value; _Matrix[3][1] = _Value; _Matrix[3][2] = _Value; _Matrix[3][3] = _Value;

	return _Matrix;
}

const BFW::Math::Mat4f& BFW::Math::Mat4f::Shear(const float _Value, const unsigned long _ShearedAxis, const unsigned long _ByAxis)
{
	Matrix[0][0] = 1.0f; Matrix[0][1] = 0.0f; Matrix[0][2] = 0.0f; Matrix[0][3] = 0.0f;
	Matrix[1][0] = 0.0f; Matrix[1][1] = 1.0f; Matrix[1][2] = 0.0f; Matrix[1][3] = 0.0f;
	Matrix[2][0] = 0.0f; Matrix[2][1] = 0.0f; Matrix[2][2] = 1.0f; Matrix[2][3] = 0.0f;
	Matrix[3][0] = 0.0f; Matrix[3][1] = 0.0f; Matrix[3][2] = 0.0f; Matrix[3][3] = 1.0f;

	Matrix[_ShearedAxis][_ByAxis] = _Value;

	return *this;
}

const BFW::Math::Mat4f BFW::Math::Mat4f::GetShear(const float _Value, const unsigned long _ShearedAxis, const unsigned long _ByAxis)
{
	Mat4f _Matrix;

	_Matrix[0][0] = 1.0f; _Matrix[0][1] = 0.0f; _Matrix[0][2] = 0.0f; _Matrix[0][3] = 0.0f;
	_Matrix[1][0] = 0.0f; _Matrix[1][1] = 1.0f; _Matrix[1][2] = 0.0f; _Matrix[1][3] = 0.0f;
	_Matrix[2][0] = 0.0f; _Matrix[2][1] = 0.0f; _Matrix[2][2] = 1.0f; _Matrix[2][3] = 0.0f;
	_Matrix[3][0] = 0.0f; _Matrix[3][1] = 0.0f; _Matrix[3][2] = 0.0f; _Matrix[3][3] = 1.0f;

	_Matrix[_ShearedAxis][_ByAxis] = _Value;

	return _Matrix;
}

const BFW::Math::Mat4f& BFW::Math::Mat4f::Rotation(const float _Angle, const Vec4f& _U)
{
	float _Sin = fSin(_Angle);
	float _Cos = fCos(_Angle);

	Matrix[0][0] = _Cos + _U.x * _U.x * (1.0f - _Cos); Matrix[0][1] = _U.x * _U.y * (1.0f - _Cos) - _U.z * _Sin; Matrix[0][2] = _U.x * _U.z * (1.0f - _Cos) + _U.y * _Sin; Matrix[0][3] = 0.0f;
	Matrix[1][0] = _U.y * _U.x * (1.0f - _Cos) + _U.z * _Sin; Matrix[1][1] = _Cos + _U.y * _U.y * (1.0f - _Cos); Matrix[1][2] = _U.y * _U.z * (1.0f - _Cos) - _U.x * _Sin; Matrix[1][3] = 0.0f;
	Matrix[2][0] = _U.z * _U.x * (1.0f - _Cos) - _U.y * _Sin; Matrix[2][1] = _U.z * _U.y * (1.0f - _Cos) + _U.x * _Sin; Matrix[2][2] = _Cos + _U.z * _U.z * (1.0f - _Cos); Matrix[2][3] = 0.0f;
	Matrix[3][0] = 0.0f; Matrix[3][1] = 0.0f; Matrix[3][2] = 0.0f; Matrix[3][3] = 1.0f;

	return *this;
}

const BFW::Math::Mat4f BFW::Math::Mat4f::GetRotation(const float _Angle, const Vec4f& _U)
{
	float _Sin = fSin(_Angle);
	float _Cos = fCos(_Angle);

	Mat4f _Matrix;

	_Matrix[0][0] = _Cos + _U.x * _U.x * (1.0f - _Cos); _Matrix[0][1] = _U.x * _U.y * (1.0f - _Cos) - _U.z * _Sin; _Matrix[0][2] = _U.x * _U.z * (1.0f - _Cos) + _U.y * _Sin; _Matrix[0][3] = 0.0f;
	_Matrix[1][0] = _U.y * _U.x * (1.0f - _Cos) + _U.z * _Sin; _Matrix[1][1] = _Cos + _U.y * _U.y * (1.0f - _Cos); _Matrix[1][2] = _U.y * _U.z * (1.0f - _Cos) - _U.x * _Sin; _Matrix[1][3] = 0.0f;
	_Matrix[2][0] = _U.z * _U.x * (1.0f - _Cos) - _U.y * _Sin; _Matrix[2][1] = _U.z * _U.y * (1.0f - _Cos) + _U.x * _Sin; _Matrix[2][2] = _Cos + _U.z * _U.z * (1.0f - _Cos); _Matrix[2][3] = 0.0f;
	_Matrix[3][0] = 0.0f; _Matrix[3][1] = 0.0f; _Matrix[3][2] = 0.0f; _Matrix[3][3] = 1.0f;

	return _Matrix;
}

const BFW::Math::Mat4f& BFW::Math::Mat4f::Translation(const Vec4f& _V)
{
	Matrix[0][0] = 1.0f; Matrix[0][1] = 0.0f; Matrix[0][2] = 0.0f; Matrix[0][3] = _V.x;
	Matrix[1][0] = 0.0f; Matrix[1][1] = 1.0f; Matrix[1][2] = 0.0f; Matrix[1][3] = _V.y;
	Matrix[2][0] = 0.0f; Matrix[2][1] = 0.0f; Matrix[2][2] = 1.0f; Matrix[2][3] = _V.z;
	Matrix[3][0] = 0.0f; Matrix[3][1] = 0.0f; Matrix[3][2] = 0.0f; Matrix[3][3] = 1.0f;

	return *this;
}

const BFW::Math::Mat4f BFW::Math::Mat4f::GetTranslation(const Vec4f& _V)
{
	Mat4f _Matrix;

	_Matrix[0][0] = 1.0f; _Matrix[0][1] = 0.0f; _Matrix[0][2] = 0.0f; _Matrix[0][3] = _V.x;
	_Matrix[1][0] = 0.0f; _Matrix[1][1] = 1.0f; _Matrix[1][2] = 0.0f; _Matrix[1][3] = _V.y;
	_Matrix[2][0] = 0.0f; _Matrix[2][1] = 0.0f; _Matrix[2][2] = 1.0f; _Matrix[2][3] = _V.z;
	_Matrix[3][0] = 0.0f; _Matrix[3][1] = 0.0f; _Matrix[3][2] = 0.0f; _Matrix[3][3] = 1.0f;

	return _Matrix;
}

const BFW::Math::Mat4f& BFW::Math::Mat4f::Ortho(const float _Left, const float _Right, const float _Top, const float _Bottom, const float _Front, const float _Back)
{
	Matrix[0][0] = 2.0f / (_Right - _Left); Matrix[0][1] = 0.0f; Matrix[0][2] = 0.0f; Matrix[0][3] = (_Right + _Left) / (_Left - _Right);
	Matrix[1][0] = 0.0f; Matrix[1][1] = 2.0f / (_Top - _Bottom); Matrix[1][2] = 0.0f; Matrix[1][3] = (_Top + _Bottom) / (_Bottom - _Top);
	Matrix[2][0] = 0.0f; Matrix[2][1] = 0.0f; Matrix[2][2] = 2.0f / (_Front - _Back); Matrix[2][3] = (_Front + _Back) / (_Back - _Front);
	Matrix[3][0] = 0.0f; Matrix[3][1] = 0.0f; Matrix[3][2] = 0.0f; Matrix[3][3] = 1.0f;

	return *this;
}

const BFW::Math::Mat4f BFW::Math::Mat4f::GetOrtho(const float _Left, const float _Right, const float _Top, const float _Bottom, const float _Front, const float _Back)
{
	Mat4f _Matrix;

	_Matrix[0][0] = 2.0f / (_Right - _Left); _Matrix[0][1] = 0.0f; _Matrix[0][2] = 0.0f; _Matrix[0][3] = (_Right + _Left) / (_Left - _Right);
	_Matrix[1][0] = 0.0f; _Matrix[1][1] = 2.0f / (_Top - _Bottom); _Matrix[1][2] = 0.0f; _Matrix[1][3] = (_Top + _Bottom) / (_Bottom - _Top);
	_Matrix[2][0] = 0.0f; _Matrix[2][1] = 0.0f; _Matrix[2][2] = 2.0f / (_Front - _Back); _Matrix[2][3] = (_Front + _Back) / (_Back - _Front);
	_Matrix[3][0] = 0.0f; _Matrix[3][1] = 0.0f; _Matrix[3][2] = 0.0f; _Matrix[3][3] = 1.0f;

	return _Matrix;
}

const BFW::Math::Mat4f& BFW::Math::Mat4f::Perspective(const float _Fov, const float _AspectRatio, const float _ZNear, const float _ZFar)
{
	float _Tan = fTan(_Fov / 2.0f);

	Matrix[0][0] = 1.0f / (_AspectRatio * _Tan); Matrix[0][1] = 0.0f; Matrix[0][2] = 0.0f; Matrix[0][3] = 0.0f;
	Matrix[1][0] = 0.0f; Matrix[1][1] = 1.0f / _Tan; Matrix[1][2] = 0.0f; Matrix[1][3] = 0.0f;
	Matrix[2][0] = 0.0f; Matrix[2][1] = 0.0f; Matrix[2][2] = -(_ZFar + _ZNear) / (_ZFar - _ZNear); Matrix[2][3] = -(2.0f * _ZFar * _ZNear) / (_ZFar - _ZNear);
	Matrix[3][0] = 0.0f; Matrix[3][1] = 0.0f; Matrix[3][2] = -1.0f; Matrix[3][3] = 0.0f;

	return *this;
}

const BFW::Math::Mat4f BFW::Math::Mat4f::GetPerspective(const float _Fov, const float _AspectRatio, const float _ZNear, const float _ZFar)
{
	float _Tan = fTan(_Fov / 2.0f);

	Mat4f _Matrix;

	_Matrix[0][0] = 1.0f / (_AspectRatio * _Tan); _Matrix[0][1] = 0.0f; _Matrix[0][2] = 0.0f; _Matrix[0][3] = 0.0f;
	_Matrix[1][0] = 0.0f; _Matrix[1][1] = 1.0f / _Tan; _Matrix[1][2] = 0.0f; _Matrix[1][3] = 0.0f;
	_Matrix[2][0] = 0.0f; _Matrix[2][1] = 0.0f; _Matrix[2][2] = -(_ZFar + _ZNear) / (_ZFar - _ZNear); _Matrix[2][3] = -(2.0f * _ZFar * _ZNear) / (_ZFar - _ZNear);
	_Matrix[3][0] = 0.0f; _Matrix[3][1] = 0.0f; _Matrix[3][2] = -1.0f; _Matrix[3][3] = 0.0f;

	return _Matrix;
}

const BFW::Math::Mat4f& BFW::Math::Mat4f::Flip(const Vec4f& _U, const Vec4f& _Center)
{
	Matrix[0][0] = 1.0f - 2.0f * _U.x * _U.x; Matrix[0][1] = -2.0f * _U.x * _U.y; Matrix[0][2] = -2.0f * _U.x * _U.z; Matrix[0][3] = 0.0f;
	Matrix[1][0] = -2.0f * _U.x * _U.y; Matrix[1][1] = 1.0f - 2.0f * _U.y * _U.y; Matrix[1][2] = -2.0f * _U.y * _U.z; Matrix[1][3] = 0.0f;
	Matrix[2][0] = -2.0f * _U.x * _U.z; Matrix[2][1] = -2.0f * _U.y * _U.z; Matrix[2][2] = 1.0f - 2.0f * _U.z * _U.z; Matrix[2][3] = 0.0f;
	Matrix[3][0] = 0.0f; Matrix[3][1] = 0.0f; Matrix[3][2] = 0.0f; Matrix[3][3] = 1.0f;

	*this = GetTranslation(_Center) * (*this) * GetTranslation(-_Center);

	return *this;
}

const BFW::Math::Mat4f BFW::Math::Mat4f::GetFlip(const Vec4f& _U, const Vec4f& _Center)
{
	Mat4f _Matrix;

	_Matrix[0][0] = 1.0f - 2.0f * _U.x * _U.x; _Matrix[0][1] = -2.0f * _U.x * _U.y; _Matrix[0][2] = -2.0f * _U.x * _U.z; _Matrix[0][3] = 0.0f;
	_Matrix[1][0] = -2.0f * _U.x * _U.y; _Matrix[1][1] = 1.0f - 2.0f * _U.y * _U.y; _Matrix[1][2] = -2.0f * _U.y * _U.z; _Matrix[1][3] = 0.0f;
	_Matrix[2][0] = -2.0f * _U.x * _U.z; _Matrix[2][1] = -2.0f * _U.y * _U.z; _Matrix[2][2] = 1.0f - 2.0f * _U.z * _U.z; _Matrix[2][3] = 0.0f;
	_Matrix[3][0] = 0.0f; _Matrix[3][1] = 0.0f; _Matrix[3][2] = 0.0f; _Matrix[3][3] = 1.0f;

	_Matrix = GetTranslation(_Center) * _Matrix * GetTranslation(-_Center);

	return _Matrix;
}

const BFW::Math::Mat4f& BFW::Math::Mat4f::operator+ () const
{
	return *this;
}

const BFW::Math::Mat4f BFW::Math::Mat4f::operator- () const
{
	Mat4f _Matrix;

	_Matrix[0][0] = -Matrix[0][0]; _Matrix[0][1] = -Matrix[0][1]; _Matrix[0][2] = -Matrix[0][2]; _Matrix[0][3] = -Matrix[0][3];
	_Matrix[1][0] = -Matrix[1][0]; _Matrix[1][1] = -Matrix[1][1]; _Matrix[1][2] = -Matrix[1][2]; _Matrix[1][3] = -Matrix[1][3];
	_Matrix[2][0] = -Matrix[2][0]; _Matrix[2][1] = -Matrix[2][1]; _Matrix[2][2] = -Matrix[2][2]; _Matrix[2][3] = -Matrix[2][3];
	_Matrix[3][0] = -Matrix[3][0]; _Matrix[3][1] = -Matrix[3][1]; _Matrix[3][2] = -Matrix[3][2]; _Matrix[3][3] = -Matrix[3][3];

	return _Matrix;
}

const BFW::Math::Vec4f BFW::Math::Mat4f::operator* (const Vec4f& _Vec) const
{
	float _x = _Vec.x * Matrix[0][0] + _Vec.y * Matrix[0][1] + _Vec.z * Matrix[0][2] + _Vec.w * Matrix[0][3];
	float _y = _Vec.x * Matrix[1][0] + _Vec.y * Matrix[1][1] + _Vec.z * Matrix[1][2] + _Vec.w * Matrix[1][3];
	float _z = _Vec.x * Matrix[2][0] + _Vec.y * Matrix[2][1] + _Vec.z * Matrix[2][2] + _Vec.w * Matrix[2][3];
	float _w = _Vec.x * Matrix[3][0] + _Vec.y * Matrix[3][1] + _Vec.z * Matrix[3][2] + _Vec.w * Matrix[3][3];

	return Vec4f(_x, _y, _z, _w);
}

const BFW::Math::Mat4f BFW::Math::Mat4f::operator+ (const Mat4f& _Other) const
{
	Mat4f _Matrix;

	_Matrix[0][0] = Matrix[0][0] + _Other[0][0]; _Matrix[0][1] = Matrix[0][1] + _Other[0][1]; _Matrix[0][2] = Matrix[0][2] + _Other[0][2]; _Matrix[0][3] = Matrix[0][3] + _Other[0][3];
	_Matrix[1][0] = Matrix[1][0] + _Other[1][0]; _Matrix[1][1] = Matrix[1][1] + _Other[1][1]; _Matrix[1][2] = Matrix[1][2] + _Other[1][2]; _Matrix[1][3] = Matrix[1][3] + _Other[1][3];
	_Matrix[2][0] = Matrix[2][0] + _Other[2][0]; _Matrix[2][1] = Matrix[2][1] + _Other[2][1]; _Matrix[2][2] = Matrix[2][2] + _Other[2][2]; _Matrix[2][3] = Matrix[2][3] + _Other[2][3];
	_Matrix[3][0] = Matrix[3][0] + _Other[3][0]; _Matrix[3][1] = Matrix[3][1] + _Other[3][1]; _Matrix[3][2] = Matrix[3][2] + _Other[3][2]; _Matrix[3][3] = Matrix[3][3] + _Other[3][3];

	return _Matrix;
}

const BFW::Math::Mat4f& BFW::Math::Mat4f::operator+= (const Mat4f& _Other)
{
	Matrix[0][0] += _Other[0][0]; Matrix[0][1] += _Other[0][1]; Matrix[0][2] += _Other[0][2]; Matrix[0][3] += _Other[0][3];
	Matrix[1][0] += _Other[1][0]; Matrix[1][1] += _Other[1][1]; Matrix[1][2] += _Other[1][2]; Matrix[1][3] += _Other[1][3];
	Matrix[2][0] += _Other[2][0]; Matrix[2][1] += _Other[2][1]; Matrix[2][2] += _Other[2][2]; Matrix[2][3] += _Other[2][3];
	Matrix[3][0] += _Other[3][0]; Matrix[3][1] += _Other[3][1]; Matrix[3][2] += _Other[3][2]; Matrix[3][3] += _Other[3][3];

	return *this;
}

const BFW::Math::Mat4f BFW::Math::Mat4f::operator+ (const float _Scale) const
{
	Mat4f _Matrix;

	_Matrix[0][0] = Matrix[0][0] + _Scale; _Matrix[0][1] = Matrix[0][1] + _Scale; _Matrix[0][2] = Matrix[0][2] + _Scale; _Matrix[0][3] = Matrix[0][3] + _Scale;
	_Matrix[1][0] = Matrix[1][0] + _Scale; _Matrix[1][1] = Matrix[1][1] + _Scale; _Matrix[1][2] = Matrix[1][2] + _Scale; _Matrix[1][3] = Matrix[1][3] + _Scale;
	_Matrix[2][0] = Matrix[2][0] + _Scale; _Matrix[2][1] = Matrix[2][1] + _Scale; _Matrix[2][2] = Matrix[2][2] + _Scale; _Matrix[2][3] = Matrix[2][3] + _Scale;
	_Matrix[3][0] = Matrix[3][0] + _Scale; _Matrix[3][1] = Matrix[3][1] + _Scale; _Matrix[3][2] = Matrix[3][2] + _Scale; _Matrix[3][3] = Matrix[3][3] + _Scale;

	return _Matrix;

}

const BFW::Math::Mat4f& BFW::Math::Mat4f::operator+= (const float _Scale)
{
	Matrix[0][0] += _Scale; Matrix[0][1] += _Scale; Matrix[0][2] += _Scale; Matrix[0][3] += _Scale;
	Matrix[1][0] += _Scale; Matrix[1][1] += _Scale; Matrix[1][2] += _Scale; Matrix[1][3] += _Scale;
	Matrix[2][0] += _Scale; Matrix[2][1] += _Scale; Matrix[2][2] += _Scale; Matrix[2][3] += _Scale;
	Matrix[3][0] += _Scale; Matrix[3][1] += _Scale; Matrix[3][2] += _Scale; Matrix[3][3] += _Scale;

	return *this;
}

const BFW::Math::Mat4f BFW::Math::Mat4f::operator- (const Mat4f& _Other) const
{
	Mat4f _Matrix;

	_Matrix[0][0] = Matrix[0][0] - _Other[0][0]; _Matrix[0][1] = Matrix[0][1] - _Other[0][1]; _Matrix[0][2] = Matrix[0][2] - _Other[0][2]; _Matrix[0][3] = Matrix[0][3] - _Other[0][3];
	_Matrix[1][0] = Matrix[1][0] - _Other[1][0]; _Matrix[1][1] = Matrix[1][1] - _Other[1][1]; _Matrix[1][2] = Matrix[1][2] - _Other[1][2]; _Matrix[1][3] = Matrix[1][3] - _Other[1][3];
	_Matrix[2][0] = Matrix[2][0] - _Other[2][0]; _Matrix[2][1] = Matrix[2][1] - _Other[2][1]; _Matrix[2][2] = Matrix[2][2] - _Other[2][2]; _Matrix[2][3] = Matrix[2][3] - _Other[2][3];
	_Matrix[3][0] = Matrix[3][0] - _Other[3][0]; _Matrix[3][1] = Matrix[3][1] - _Other[3][1]; _Matrix[3][2] = Matrix[3][2] - _Other[3][2]; _Matrix[3][3] = Matrix[3][3] - _Other[3][3];

	return _Matrix;
}

const BFW::Math::Mat4f& BFW::Math::Mat4f::operator-= (const Mat4f& _Other)
{
	Matrix[0][0] -= _Other[0][0]; Matrix[0][1] -= _Other[0][1]; Matrix[0][2] -= _Other[0][2]; Matrix[0][3] -= _Other[0][3];
	Matrix[1][0] -= _Other[1][0]; Matrix[1][1] -= _Other[1][1]; Matrix[1][2] -= _Other[1][2]; Matrix[1][3] -= _Other[1][3];
	Matrix[2][0] -= _Other[2][0]; Matrix[2][1] -= _Other[2][1]; Matrix[2][2] -= _Other[2][2]; Matrix[2][3] -= _Other[2][3];
	Matrix[3][0] -= _Other[3][0]; Matrix[3][1] -= _Other[3][1]; Matrix[3][2] -= _Other[3][2]; Matrix[3][3] -= _Other[3][3];

	return *this;
}

const BFW::Math::Mat4f BFW::Math::Mat4f::operator- (const float _Scale) const
{
	Mat4f _Matrix;

	_Matrix[0][0] = Matrix[0][0] - _Scale; _Matrix[0][1] = Matrix[0][1] - _Scale; _Matrix[0][2] = Matrix[0][2] - _Scale; _Matrix[0][3] = Matrix[0][3] - _Scale;
	_Matrix[1][0] = Matrix[1][0] - _Scale; _Matrix[1][1] = Matrix[1][1] - _Scale; _Matrix[1][2] = Matrix[1][2] - _Scale; _Matrix[1][3] = Matrix[1][3] - _Scale;
	_Matrix[2][0] = Matrix[2][0] - _Scale; _Matrix[2][1] = Matrix[2][1] - _Scale; _Matrix[2][2] = Matrix[2][2] - _Scale; _Matrix[2][3] = Matrix[2][3] - _Scale;
	_Matrix[3][0] = Matrix[3][0] - _Scale; _Matrix[3][1] = Matrix[3][1] - _Scale; _Matrix[3][2] = Matrix[3][2] - _Scale; _Matrix[3][3] = Matrix[3][3] - _Scale;

	return _Matrix;
}

const BFW::Math::Mat4f& BFW::Math::Mat4f::operator-= (const float _Scale)
{
	Matrix[0][0] -= _Scale; Matrix[0][1] -= _Scale; Matrix[0][2] -= _Scale; Matrix[0][3] -= _Scale;
	Matrix[1][0] -= _Scale; Matrix[1][1] -= _Scale; Matrix[1][2] -= _Scale; Matrix[1][3] -= _Scale;
	Matrix[2][0] -= _Scale; Matrix[2][1] -= _Scale; Matrix[2][2] -= _Scale; Matrix[2][3] -= _Scale;
	Matrix[3][0] -= _Scale; Matrix[3][1] -= _Scale; Matrix[3][2] -= _Scale; Matrix[3][3] -= _Scale;

	return *this;
}

const BFW::Math::Mat4f BFW::Math::Mat4f::operator* (const Mat4f& _Other) const
{
	Mat4f _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Other[0][0] + Matrix[0][1] * _Other[1][0] + Matrix[0][2] * _Other[2][0];
	_Matrix[0][1] = Matrix[0][0] * _Other[0][1] + Matrix[0][1] * _Other[1][1] + Matrix[0][2] * _Other[2][1];
	_Matrix[0][2] = Matrix[0][0] * _Other[0][2] + Matrix[0][1] * _Other[1][2] + Matrix[0][2] * _Other[2][2];
	_Matrix[0][2] = Matrix[0][0] * _Other[0][2] + Matrix[0][1] * _Other[1][2] + Matrix[0][2] * _Other[2][2];

	_Matrix[1][0] = Matrix[1][0] * _Other[0][0] + Matrix[1][1] * _Other[1][0] + Matrix[1][2] * _Other[2][0];
	_Matrix[1][1] = Matrix[1][0] * _Other[0][1] + Matrix[1][1] * _Other[1][1] + Matrix[1][2] * _Other[2][1];
	_Matrix[1][2] = Matrix[1][0] * _Other[0][2] + Matrix[1][1] * _Other[1][2] + Matrix[1][2] * _Other[2][2];
	_Matrix[1][2] = Matrix[1][0] * _Other[0][2] + Matrix[1][1] * _Other[1][2] + Matrix[1][2] * _Other[2][2];

	_Matrix[2][0] = Matrix[2][0] * _Other[0][0] + Matrix[2][1] * _Other[1][0] + Matrix[2][2] * _Other[2][0];
	_Matrix[2][1] = Matrix[2][0] * _Other[0][1] + Matrix[2][1] * _Other[1][1] + Matrix[2][2] * _Other[2][1];
	_Matrix[2][2] = Matrix[2][0] * _Other[0][2] + Matrix[2][1] * _Other[1][2] + Matrix[2][2] * _Other[2][2];
	_Matrix[2][2] = Matrix[2][0] * _Other[0][2] + Matrix[2][1] * _Other[1][2] + Matrix[2][2] * _Other[2][2];

	_Matrix[2][0] = Matrix[2][0] * _Other[0][0] + Matrix[2][1] * _Other[1][0] + Matrix[2][2] * _Other[2][0];
	_Matrix[2][1] = Matrix[2][0] * _Other[0][1] + Matrix[2][1] * _Other[1][1] + Matrix[2][2] * _Other[2][1];
	_Matrix[2][2] = Matrix[2][0] * _Other[0][2] + Matrix[2][1] * _Other[1][2] + Matrix[2][2] * _Other[2][2];
	_Matrix[2][2] = Matrix[2][0] * _Other[0][2] + Matrix[2][1] * _Other[1][2] + Matrix[2][2] * _Other[2][2];

	return _Matrix;
}

const BFW::Math::Mat4f& BFW::Math::Mat4f::operator*= (const Mat4f& _Other)
{
	Mat4f _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Other[0][0] + Matrix[0][1] * _Other[1][0] + Matrix[0][2] * _Other[2][0];
	_Matrix[0][1] = Matrix[0][0] * _Other[0][1] + Matrix[0][1] * _Other[1][1] + Matrix[0][2] * _Other[2][1];
	_Matrix[0][2] = Matrix[0][0] * _Other[0][2] + Matrix[0][1] * _Other[1][2] + Matrix[0][2] * _Other[2][2];
	_Matrix[0][2] = Matrix[0][0] * _Other[0][2] + Matrix[0][1] * _Other[1][2] + Matrix[0][2] * _Other[2][2];

	_Matrix[1][0] = Matrix[1][0] * _Other[0][0] + Matrix[1][1] * _Other[1][0] + Matrix[1][2] * _Other[2][0];
	_Matrix[1][1] = Matrix[1][0] * _Other[0][1] + Matrix[1][1] * _Other[1][1] + Matrix[1][2] * _Other[2][1];
	_Matrix[1][2] = Matrix[1][0] * _Other[0][2] + Matrix[1][1] * _Other[1][2] + Matrix[1][2] * _Other[2][2];
	_Matrix[1][2] = Matrix[1][0] * _Other[0][2] + Matrix[1][1] * _Other[1][2] + Matrix[1][2] * _Other[2][2];

	_Matrix[2][0] = Matrix[2][0] * _Other[0][0] + Matrix[2][1] * _Other[1][0] + Matrix[2][2] * _Other[2][0];
	_Matrix[2][1] = Matrix[2][0] * _Other[0][1] + Matrix[2][1] * _Other[1][1] + Matrix[2][2] * _Other[2][1];
	_Matrix[2][2] = Matrix[2][0] * _Other[0][2] + Matrix[2][1] * _Other[1][2] + Matrix[2][2] * _Other[2][2];
	_Matrix[2][2] = Matrix[2][0] * _Other[0][2] + Matrix[2][1] * _Other[1][2] + Matrix[2][2] * _Other[2][2];

	_Matrix[2][0] = Matrix[2][0] * _Other[0][0] + Matrix[2][1] * _Other[1][0] + Matrix[2][2] * _Other[2][0];
	_Matrix[2][1] = Matrix[2][0] * _Other[0][1] + Matrix[2][1] * _Other[1][1] + Matrix[2][2] * _Other[2][1];
	_Matrix[2][2] = Matrix[2][0] * _Other[0][2] + Matrix[2][1] * _Other[1][2] + Matrix[2][2] * _Other[2][2];
	_Matrix[2][2] = Matrix[2][0] * _Other[0][2] + Matrix[2][1] * _Other[1][2] + Matrix[2][2] * _Other[2][2];

	*this = _Matrix;

	return *this;
}

const BFW::Math::Mat4f BFW::Math::Mat4f::operator* (const float _Scale) const
{
	Mat4f _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Scale; _Matrix[0][1] = Matrix[0][1] * _Scale; _Matrix[0][2] = Matrix[0][2] * _Scale; _Matrix[0][3] = Matrix[0][3] * _Scale;
	_Matrix[1][0] = Matrix[1][0] * _Scale; _Matrix[1][1] = Matrix[1][1] * _Scale; _Matrix[1][2] = Matrix[1][2] * _Scale; _Matrix[1][3] = Matrix[1][3] * _Scale;
	_Matrix[2][0] = Matrix[2][0] * _Scale; _Matrix[2][1] = Matrix[2][1] * _Scale; _Matrix[2][2] = Matrix[2][2] * _Scale; _Matrix[2][3] = Matrix[2][3] * _Scale;
	_Matrix[3][0] = Matrix[3][0] * _Scale; _Matrix[3][1] = Matrix[3][1] * _Scale; _Matrix[3][2] = Matrix[3][2] * _Scale; _Matrix[3][3] = Matrix[3][3] * _Scale;

	return _Matrix;
}

const BFW::Math::Mat4f& BFW::Math::Mat4f::operator*= (const float _Scale)
{
	Matrix[0][0] *= _Scale; Matrix[0][1] *= _Scale; Matrix[0][2] *= _Scale; Matrix[0][3] *= _Scale;
	Matrix[1][0] *= _Scale; Matrix[1][1] *= _Scale; Matrix[1][2] *= _Scale; Matrix[1][3] *= _Scale;
	Matrix[2][0] *= _Scale; Matrix[2][1] *= _Scale; Matrix[2][2] *= _Scale; Matrix[2][3] *= _Scale;
	Matrix[3][0] *= _Scale; Matrix[3][1] *= _Scale; Matrix[3][2] *= _Scale; Matrix[3][3] *= _Scale;

	return *this;
}

const BFW::Math::Mat4f BFW::Math::Mat4f::operator/ (const float _Scale) const
{
	Mat4f _Matrix;

	_Matrix[0][0] = Matrix[0][0] / _Scale; _Matrix[0][1] = Matrix[0][1] / _Scale; _Matrix[0][2] = Matrix[0][2] / _Scale; _Matrix[0][3] = Matrix[0][3] / _Scale;
	_Matrix[1][0] = Matrix[1][0] / _Scale; _Matrix[1][1] = Matrix[1][1] / _Scale; _Matrix[1][2] = Matrix[1][2] / _Scale; _Matrix[1][3] = Matrix[1][3] / _Scale;
	_Matrix[2][0] = Matrix[2][0] / _Scale; _Matrix[2][1] = Matrix[2][1] / _Scale; _Matrix[2][2] = Matrix[2][2] / _Scale; _Matrix[2][3] = Matrix[2][3] / _Scale;
	_Matrix[3][0] = Matrix[3][0] / _Scale; _Matrix[3][1] = Matrix[3][1] / _Scale; _Matrix[3][2] = Matrix[3][2] / _Scale; _Matrix[3][3] = Matrix[3][3] / _Scale;

	return _Matrix;
}

const BFW::Math::Mat4f& BFW::Math::Mat4f::operator/= (const float _Scale)
{
	Matrix[0][0] /= _Scale; Matrix[0][1] /= _Scale; Matrix[0][2] /= _Scale; Matrix[0][3] /= _Scale;
	Matrix[1][0] /= _Scale; Matrix[1][1] /= _Scale; Matrix[1][2] /= _Scale; Matrix[1][3] /= _Scale;
	Matrix[2][0] /= _Scale; Matrix[2][1] /= _Scale; Matrix[2][2] /= _Scale; Matrix[2][3] /= _Scale;
	Matrix[3][0] /= _Scale; Matrix[3][1] /= _Scale; Matrix[3][2] /= _Scale; Matrix[3][3] /= _Scale;

	return *this;
}

const bool BFW::Math::Mat4f::operator== (const Mat4f& _Other) const
{
	return
		Matrix[0][0] == _Other[0][0] && Matrix[0][1] == _Other[0][1] && Matrix[0][2] == _Other[0][2] && Matrix[0][3] == _Other[0][3] &&
		Matrix[1][0] == _Other[1][0] && Matrix[1][1] == _Other[1][1] && Matrix[1][2] == _Other[1][2] && Matrix[1][3] == _Other[1][3] &&
		Matrix[2][0] == _Other[2][0] && Matrix[2][1] == _Other[2][1] && Matrix[2][2] == _Other[2][2] && Matrix[2][3] == _Other[2][3] &&
		Matrix[3][0] == _Other[3][0] && Matrix[3][1] == _Other[3][1] && Matrix[3][2] == _Other[3][2] && Matrix[3][3] == _Other[3][3];
}

const bool BFW::Math::Mat4f::operator!= (const Mat4f& _Other) const
{
	return
		Matrix[0][0] != _Other[0][0] || Matrix[0][1] != _Other[0][1] || Matrix[0][2] != _Other[0][2] || Matrix[0][3] != _Other[0][3] ||
		Matrix[1][0] != _Other[1][0] || Matrix[1][1] != _Other[1][1] || Matrix[1][2] != _Other[1][2] || Matrix[1][3] != _Other[1][3] ||
		Matrix[2][0] != _Other[2][0] || Matrix[2][1] != _Other[2][1] || Matrix[2][2] != _Other[2][2] || Matrix[2][3] != _Other[2][3] ||
		Matrix[3][0] != _Other[3][0] || Matrix[3][1] != _Other[3][1] || Matrix[3][2] != _Other[3][2] || Matrix[3][3] != _Other[3][3];
}

const bool BFW::Math::Mat4f::operator> (const Mat4f& _Other) const
{
	return Determinant() > _Other.Determinant();
}

const bool BFW::Math::Mat4f::operator>= (const Mat4f& _Other) const
{
	return Determinant() >= _Other.Determinant();
}

const bool BFW::Math::Mat4f::operator< (const Mat4f& _Other) const
{
	return Determinant() < _Other.Determinant();
}

const bool BFW::Math::Mat4f::operator<= (const Mat4f& _Other) const
{
	return Determinant() <= _Other.Determinant();
}

float* BFW::Math::Mat4f::operator[] (const unsigned long _Index)
{
	return Matrix[_Index].Data();
}

const float* BFW::Math::Mat4f::operator[] (const unsigned long _Index) const
{
	return Matrix[_Index].Data();
}

const BFW::Math::Mat4f& BFW::Math::Mat4f::operator= (const Mat4f& _Other)
{
	Matrix[0][0] = _Other.Matrix[0][0]; Matrix[0][1] = _Other.Matrix[0][1]; Matrix[0][2] = _Other.Matrix[0][2]; Matrix[0][3] = _Other.Matrix[0][3];
	Matrix[1][0] = _Other.Matrix[1][0]; Matrix[1][1] = _Other.Matrix[1][1]; Matrix[1][2] = _Other.Matrix[1][2]; Matrix[1][3] = _Other.Matrix[1][3];
	Matrix[2][0] = _Other.Matrix[2][0]; Matrix[2][1] = _Other.Matrix[2][1]; Matrix[2][2] = _Other.Matrix[2][2]; Matrix[2][3] = _Other.Matrix[2][3];
	Matrix[3][0] = _Other.Matrix[3][0]; Matrix[3][1] = _Other.Matrix[3][1]; Matrix[3][2] = _Other.Matrix[3][2]; Matrix[3][3] = _Other.Matrix[3][3];

	return *this;
}

const BFW::Math::Mat4f& BFW::Math::Mat4f::operator= (Mat4f&& _Other) noexcept
{
	Matrix[0][0] = _Other.Matrix[0][0]; Matrix[0][1] = _Other.Matrix[0][1]; Matrix[0][2] = _Other.Matrix[0][2]; Matrix[0][3] = _Other.Matrix[0][3];
	Matrix[1][0] = _Other.Matrix[1][0]; Matrix[1][1] = _Other.Matrix[1][1]; Matrix[1][2] = _Other.Matrix[1][2]; Matrix[1][3] = _Other.Matrix[1][3];
	Matrix[2][0] = _Other.Matrix[2][0]; Matrix[2][1] = _Other.Matrix[2][1]; Matrix[2][2] = _Other.Matrix[2][2]; Matrix[2][3] = _Other.Matrix[2][3];
	Matrix[3][0] = _Other.Matrix[3][0]; Matrix[3][1] = _Other.Matrix[3][1]; Matrix[3][2] = _Other.Matrix[3][2]; Matrix[3][3] = _Other.Matrix[3][3];

	_Other.Matrix[0][0] = 1.0f; _Other.Matrix[0][1] = 0.0f; _Other.Matrix[0][2] = 0.0f; _Other.Matrix[0][3] = 0.0f;
	_Other.Matrix[1][0] = 0.0f; _Other.Matrix[1][1] = 1.0f; _Other.Matrix[1][2] = 0.0f; _Other.Matrix[1][3] = 0.0f;
	_Other.Matrix[2][0] = 0.0f; _Other.Matrix[2][1] = 0.0f; _Other.Matrix[2][2] = 1.0f; _Other.Matrix[2][3] = 0.0f;
	_Other.Matrix[3][0] = 0.0f; _Other.Matrix[3][1] = 0.0f; _Other.Matrix[3][2] = 0.0f; _Other.Matrix[3][3] = 1.0f;

	return *this;
}



BFW::Math::Mat2d::Mat2d() : Matrix()
{
	Matrix[0][0] = 1.0; Matrix[0][1] = 0.0;
	Matrix[1][0] = 0.0; Matrix[1][1] = 1.0;
}

BFW::Math::Mat2d::Mat2d(const double _x, const double _y) : Matrix()
{
	Matrix[0][0] = _x; Matrix[0][1] = 0.0;
	Matrix[1][0] = 0.0; Matrix[1][1] = _y;
}

BFW::Math::Mat2d::Mat2d(const Mat2d& _Other) : Matrix()
{
	Matrix[0][0] = _Other.Matrix[0][0]; Matrix[0][1] = _Other.Matrix[0][1];
	Matrix[1][0] = _Other.Matrix[1][0]; Matrix[1][1] = _Other.Matrix[1][1];
}

BFW::Math::Mat2d::Mat2d(Mat2d&& _Other) noexcept : Matrix()
{
	Matrix[0][0] = _Other.Matrix[0][0]; Matrix[0][1] = _Other.Matrix[0][1];
	Matrix[1][0] = _Other.Matrix[1][0]; Matrix[1][1] = _Other.Matrix[1][1];

	_Other.Matrix[0][0] = 1.0; _Other.Matrix[0][1] = 0.0;
	_Other.Matrix[1][0] = 0.0; _Other.Matrix[1][1] = 1.0;
}

BFW::Math::Mat2d::~Mat2d()
{

}

double* BFW::Math::Mat2d::Data()
{
	return Matrix[0].Data();
}

const double* BFW::Math::Mat2d::Data() const
{
	return Matrix[0].Data();
}

const double BFW::Math::Mat2d::Determinant() const
{
	return Matrix[0][0] * Matrix[1][1] - Matrix[0][1] * Matrix[1][0];
}

const double BFW::Math::Mat2d::Trace() const
{
	return Matrix[0][0] + Matrix[1][1];
}

const BFW::Math::Mat2d& BFW::Math::Mat2d::Transpose()
{
	dSwap(Matrix[0][1], Matrix[1][0]);

	return *this;
}

const BFW::Math::Mat2d BFW::Math::Mat2d::Transposed() const
{
	Mat2d _Matrix;

	_Matrix[0][0] = Matrix[0][0]; _Matrix[0][1] = Matrix[1][0];
	_Matrix[1][0] = Matrix[0][1]; _Matrix[1][1] = Matrix[1][1];

	return _Matrix;
}

const BFW::Math::Mat2d& BFW::Math::Mat2d::Scale(const double _x, const double _y)
{
	Matrix[0][0] = _x; Matrix[0][1] = 0.0;
	Matrix[1][0] = 0.0; Matrix[1][1] = _y;

	return *this;
}

const BFW::Math::Mat2d BFW::Math::Mat2d::GetScale(const double _x, const double _y)
{
	Mat2d _Matrix;

	_Matrix[0][0] = _x; _Matrix[0][1] = 0.0;
	_Matrix[1][0] = 0.0; _Matrix[1][1] = _y;

	return _Matrix;
}

const BFW::Math::Mat2d& BFW::Math::Mat2d::Fill(const double _Value)
{
	Matrix[0][0] = _Value; Matrix[0][1] = _Value;
	Matrix[1][0] = _Value; Matrix[1][1] = _Value;

	return *this;
}

const BFW::Math::Mat2d BFW::Math::Mat2d::GetFill(const double _Value)
{
	Mat2d _Matrix;

	_Matrix[0][0] = _Value; _Matrix[0][1] = _Value;
	_Matrix[1][0] = _Value; _Matrix[1][1] = _Value;

	return _Matrix;
}

const BFW::Math::Mat2d& BFW::Math::Mat2d::Shear(const double _Value, const unsigned long _ShearedAxis, const unsigned long _ByAxis)
{
	Matrix[0][0] = 1.0; Matrix[0][1] = 0.0;
	Matrix[1][0] = 0.0; Matrix[1][1] = 1.0;

	Matrix[_ShearedAxis][_ByAxis] = _Value;

	return *this;
}

const BFW::Math::Mat2d BFW::Math::Mat2d::GetShear(const double _Value, const unsigned long _ShearedAxis, const unsigned long _ByAxis)
{
	Mat2d _Matrix;

	_Matrix[0][0] = 1.0; _Matrix[0][1] = 0.0;
	_Matrix[1][0] = 0.0; _Matrix[1][1] = 1.0;

	_Matrix[_ShearedAxis][_ByAxis] = _Value;

	return _Matrix;
}

const BFW::Math::Mat2d& BFW::Math::Mat2d::Rotation(const double _Angle)
{
	double _Sin = dSin(_Angle);
	double _Cos = dCos(_Angle);

	Matrix[0][0] = _Cos; Matrix[0][1] = -_Sin;
	Matrix[1][0] = _Sin; Matrix[1][1] = _Cos;

	return *this;
}

const BFW::Math::Mat2d BFW::Math::Mat2d::GetRotation(const double _Angle)
{
	double _Sin = dSin(_Angle);
	double _Cos = dCos(_Angle);

	Mat2d _Matrix;

	_Matrix[0][0] = _Cos; _Matrix[0][1] = -_Sin;
	_Matrix[1][0] = _Sin; _Matrix[1][1] = _Cos;

	return _Matrix;
}

const BFW::Math::Mat2d& BFW::Math::Mat2d::Flip(const Vec2d& _U)
{
	double _Angle = _U.GetAngle() * 2.0;
	double _Sin = dSin(_Angle);
	double _Cos = dCos(_Angle);

	Matrix[0][0] = _Cos; Matrix[0][1] = _Sin;
	Matrix[1][0] = _Sin; Matrix[1][1] = -_Cos;

	return *this;
}

const BFW::Math::Mat2d BFW::Math::Mat2d::GetFlip(const Vec2d& _U)
{
	double _Angle = _U.GetAngle() * 2.0;
	double _Sin = dSin(_Angle);
	double _Cos = dCos(_Angle);

	Mat2d _Matrix;

	_Matrix[0][0] = _Cos; _Matrix[0][1] = _Sin;
	_Matrix[1][0] = _Sin; _Matrix[1][1] = -_Cos;

	return _Matrix;
}

const BFW::Math::Mat2d& BFW::Math::Mat2d::operator+ () const
{
	return *this;
}

const BFW::Math::Mat2d BFW::Math::Mat2d::operator- () const
{
	Mat2d _Matrix;

	_Matrix[0][0] = -Matrix[0][0]; _Matrix[0][1] = -Matrix[0][1];
	_Matrix[1][0] = -Matrix[1][0]; _Matrix[1][1] = -Matrix[1][1];

	return _Matrix;
}

const BFW::Math::Vec2d BFW::Math::Mat2d::operator* (const Vec2d& _Vec) const
{
	double _x = _Vec.x * Matrix[0][0] + _Vec.y * Matrix[0][1];
	double _y = _Vec.x * Matrix[1][0] + _Vec.y * Matrix[1][1];

	return Vec2d(_x, _y);
}

const BFW::Math::Mat2d BFW::Math::Mat2d::operator+ (const Mat2d& _Other) const
{
	Mat2d _Matrix;

	_Matrix[0][0] = Matrix[0][0] + _Other[0][0]; _Matrix[0][1] = Matrix[0][1] + _Other[0][1];
	_Matrix[1][0] = Matrix[1][0] + _Other[1][0]; _Matrix[1][1] = Matrix[1][1] + _Other[1][1];

	return _Matrix;
}

const BFW::Math::Mat2d& BFW::Math::Mat2d::operator+= (const Mat2d& _Other)
{
	Matrix[0][0] += _Other[0][0]; Matrix[0][1] += _Other[0][1];
	Matrix[1][0] += _Other[1][0]; Matrix[1][1] += _Other[1][1];

	return *this;
}

const BFW::Math::Mat2d BFW::Math::Mat2d::operator+ (const double _Scale) const
{
	Mat2d _Matrix;

	_Matrix[0][0] = Matrix[0][0] + _Scale; _Matrix[0][1] = Matrix[0][1] + _Scale;
	_Matrix[1][0] = Matrix[1][0] + _Scale; _Matrix[1][1] = Matrix[1][1] + _Scale;

	return _Matrix;
}

const BFW::Math::Mat2d& BFW::Math::Mat2d::operator+= (const double _Scale)
{
	Matrix[0][0] += _Scale; Matrix[0][1] += _Scale;
	Matrix[1][0] += _Scale; Matrix[1][1] += _Scale;

	return *this;
}

const BFW::Math::Mat2d BFW::Math::Mat2d::operator- (const Mat2d& _Other) const
{
	Mat2d _Matrix;

	_Matrix[0][0] = Matrix[0][0] - _Other[0][0]; _Matrix[0][1] = Matrix[0][1] - _Other[0][1];
	_Matrix[1][0] = Matrix[1][0] - _Other[1][0]; _Matrix[1][1] = Matrix[1][1] - _Other[1][1];

	return _Matrix;
}

const BFW::Math::Mat2d& BFW::Math::Mat2d::operator-= (const Mat2d& _Other)
{
	Matrix[0][0] -= _Other[0][0]; Matrix[0][1] -= _Other[0][1];
	Matrix[1][0] -= _Other[1][0]; Matrix[1][1] -= _Other[1][1];

	return *this;
}

const BFW::Math::Mat2d BFW::Math::Mat2d::operator- (const double _Scale) const
{
	Mat2d _Matrix;

	_Matrix[0][0] = Matrix[0][0] - _Scale; _Matrix[0][1] = Matrix[0][1] - _Scale;
	_Matrix[1][0] = Matrix[1][0] - _Scale; _Matrix[1][1] = Matrix[1][1] - _Scale;

	return _Matrix;
}

const BFW::Math::Mat2d& BFW::Math::Mat2d::operator-= (const double _Scale)
{
	Matrix[0][0] -= _Scale; Matrix[0][1] -= _Scale;
	Matrix[1][0] -= _Scale; Matrix[1][1] -= _Scale;

	return *this;
}

const BFW::Math::Mat2d BFW::Math::Mat2d::operator* (const Mat2d& _Other) const
{
	Mat2d _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Other[0][0] + Matrix[0][1] * _Other[1][0];
	_Matrix[0][1] = Matrix[0][0] * _Other[0][1] + Matrix[0][1] * _Other[1][1];
	_Matrix[1][0] = Matrix[1][0] * _Other[0][0] + Matrix[1][1] * _Other[1][0];
	_Matrix[1][1] = Matrix[1][0] * _Other[0][1] + Matrix[1][1] * _Other[1][1];

	return _Matrix;
}

const BFW::Math::Mat2d& BFW::Math::Mat2d::operator*= (const Mat2d& _Other)
{
	Mat2d _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Other[0][0] + Matrix[0][1] * _Other[1][0];
	_Matrix[0][1] = Matrix[0][0] * _Other[0][1] + Matrix[0][1] * _Other[1][1];
	_Matrix[1][0] = Matrix[1][0] * _Other[0][0] + Matrix[1][1] * _Other[1][0];
	_Matrix[1][1] = Matrix[1][0] * _Other[0][1] + Matrix[1][1] * _Other[1][1];

	*this = _Matrix;

	return *this;
}

const BFW::Math::Mat2d BFW::Math::Mat2d::operator* (const double _Scale) const
{
	Mat2d _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Scale; _Matrix[0][1] = Matrix[0][1] * _Scale;
	_Matrix[1][0] = Matrix[1][0] * _Scale; _Matrix[1][1] = Matrix[1][1] * _Scale;

	return _Matrix;
}

const BFW::Math::Mat2d& BFW::Math::Mat2d::operator*= (const double _Scale)
{
	Matrix[0][0] *= _Scale; Matrix[0][1] *= _Scale;
	Matrix[1][0] *= _Scale; Matrix[1][1] *= _Scale;

	return *this;
}

const BFW::Math::Mat2d BFW::Math::Mat2d::operator/ (const double _Scale) const
{
	Mat2d _Matrix;

	_Matrix[0][0] = Matrix[0][0] / _Scale; _Matrix[0][1] = Matrix[0][1] / _Scale;
	_Matrix[1][0] = Matrix[1][0] / _Scale; _Matrix[1][1] = Matrix[1][1] / _Scale;

	return _Matrix;
}

const BFW::Math::Mat2d& BFW::Math::Mat2d::operator/= (const double _Scale)
{
	Matrix[0][0] /= _Scale; Matrix[0][1] /= _Scale;
	Matrix[1][0] /= _Scale; Matrix[1][1] /= _Scale;

	return *this;
}

const bool BFW::Math::Mat2d::operator== (const Mat2d& _Other) const
{
	return
		Matrix[0][0] == _Other[0][0] && Matrix[0][1] == _Other[0][1] &&
		Matrix[1][0] == _Other[1][0] && Matrix[1][1] == _Other[1][1];
}

const bool BFW::Math::Mat2d::operator!= (const Mat2d& _Other) const
{
	return
		Matrix[0][0] != _Other[0][0] || Matrix[0][1] != _Other[0][1] ||
		Matrix[1][0] != _Other[1][0] || Matrix[1][1] != _Other[1][1];
}

const bool BFW::Math::Mat2d::operator> (const Mat2d& _Other) const
{
	return Determinant() > _Other.Determinant();
}

const bool BFW::Math::Mat2d::operator>= (const Mat2d& _Other) const
{
	return Determinant() >= _Other.Determinant();
}

const bool BFW::Math::Mat2d::operator< (const Mat2d& _Other) const
{
	return Determinant() < _Other.Determinant();
}

const bool BFW::Math::Mat2d::operator<= (const Mat2d& _Other) const
{
	return Determinant() <= _Other.Determinant();
}

double* BFW::Math::Mat2d::operator[] (const unsigned long _Index)
{
	return Matrix[_Index].Data();
}

const double* BFW::Math::Mat2d::operator[] (const unsigned long _Index) const
{
	return Matrix[_Index].Data();
}

const BFW::Math::Mat2d& BFW::Math::Mat2d::operator= (const Mat2d& _Other)
{
	Matrix[0][0] = _Other.Matrix[0][0]; Matrix[0][1] = _Other.Matrix[0][1];
	Matrix[1][0] = _Other.Matrix[1][0]; Matrix[1][1] = _Other.Matrix[1][1];

	return *this;
}

const BFW::Math::Mat2d& BFW::Math::Mat2d::operator= (Mat2d&& _Other) noexcept
{
	Matrix[0][0] = _Other.Matrix[0][0]; Matrix[0][1] = _Other.Matrix[0][1];
	Matrix[1][0] = _Other.Matrix[1][0]; Matrix[1][1] = _Other.Matrix[1][1];

	_Other.Matrix[0][0] = 1.0; _Other.Matrix[0][1] = 0.0;
	_Other.Matrix[1][0] = 0.0; _Other.Matrix[1][1] = 1.0;

	return *this;
}



BFW::Math::Mat3d::Mat3d() : Matrix()
{
	Matrix[0][0] = 1.0; Matrix[0][1] = 0.0; Matrix[0][2] = 0.0;
	Matrix[1][0] = 0.0; Matrix[1][1] = 1.0; Matrix[1][2] = 0.0;
	Matrix[2][0] = 0.0; Matrix[2][1] = 0.0; Matrix[2][2] = 1.0;
}

BFW::Math::Mat3d::Mat3d(const double _x, const double _y, const double _z) : Matrix()
{
	Matrix[0][0] = _x; Matrix[0][1] = 0.0; Matrix[0][2] = 0.0;
	Matrix[1][0] = 0.0; Matrix[1][1] = _y; Matrix[1][2] = 0.0;
	Matrix[2][0] = 0.0; Matrix[2][1] = 0.0; Matrix[2][2] = _z;
}

BFW::Math::Mat3d::Mat3d(const Mat3d& _Other) : Matrix()
{
	Matrix[0][0] = _Other.Matrix[0][0]; Matrix[0][1] = _Other.Matrix[0][1]; Matrix[0][2] = _Other.Matrix[0][2];
	Matrix[1][0] = _Other.Matrix[1][0]; Matrix[1][1] = _Other.Matrix[1][1]; Matrix[1][2] = _Other.Matrix[1][2];
	Matrix[2][0] = _Other.Matrix[2][0]; Matrix[2][1] = _Other.Matrix[2][1]; Matrix[2][2] = _Other.Matrix[2][2];
}

BFW::Math::Mat3d::Mat3d(Mat3d&& _Other) noexcept : Matrix()
{
	Matrix[0][0] = _Other.Matrix[0][0]; Matrix[0][1] = _Other.Matrix[0][1]; Matrix[0][2] = _Other.Matrix[0][2];
	Matrix[1][0] = _Other.Matrix[1][0]; Matrix[1][1] = _Other.Matrix[1][1]; Matrix[1][2] = _Other.Matrix[1][2];
	Matrix[2][0] = _Other.Matrix[2][0]; Matrix[2][1] = _Other.Matrix[2][1]; Matrix[2][2] = _Other.Matrix[2][2];

	_Other.Matrix[0][0] = 1.0; _Other.Matrix[0][1] = 0.0; _Other.Matrix[0][2] = 0.0;
	_Other.Matrix[1][0] = 0.0; _Other.Matrix[1][1] = 1.0; _Other.Matrix[1][2] = 0.0;
	_Other.Matrix[2][0] = 0.0; _Other.Matrix[2][1] = 0.0; _Other.Matrix[2][2] = 1.0;
}

BFW::Math::Mat3d::~Mat3d()
{

}

double* BFW::Math::Mat3d::Data()
{
	return Matrix[0].Data();
}

const double* BFW::Math::Mat3d::Data() const
{
	return Matrix[0].Data();
}

const double BFW::Math::Mat3d::Determinant() const
{
	return
		Matrix[0][0] * Matrix[1][1] * Matrix[2][2] +
		Matrix[0][2] * Matrix[1][0] * Matrix[2][1] +
		Matrix[0][1] * Matrix[1][2] * Matrix[2][0] -
		Matrix[0][2] * Matrix[1][1] * Matrix[2][0] -
		Matrix[0][0] * Matrix[1][2] * Matrix[2][1] -
		Matrix[0][1] * Matrix[1][0] * Matrix[2][2];
}

const double BFW::Math::Mat3d::Trace() const
{
	return Matrix[0][0] + Matrix[1][1] + Matrix[2][2];
}

const BFW::Math::Mat3d& BFW::Math::Mat3d::Transpose()
{
	dSwap(Matrix[0][1], Matrix[1][0]);
	dSwap(Matrix[0][2], Matrix[2][0]);
	dSwap(Matrix[1][2], Matrix[2][1]);

	return *this;
}

const BFW::Math::Mat3d BFW::Math::Mat3d::Transposed() const
{
	Mat3d _Matrix;

	_Matrix[0][0] = Matrix[0][0]; _Matrix[0][1] = Matrix[1][0]; _Matrix[0][2] = Matrix[2][0];
	_Matrix[1][0] = Matrix[0][1]; _Matrix[1][1] = Matrix[1][1]; _Matrix[1][2] = Matrix[2][1];
	_Matrix[2][0] = Matrix[0][2]; _Matrix[2][1] = Matrix[1][2]; _Matrix[2][2] = Matrix[2][2];

	return _Matrix;
}

const BFW::Math::Mat3d& BFW::Math::Mat3d::Scale(const double _x, const double _y, const double _z)
{
	Matrix[0][0] = _x; Matrix[0][1] = 0.0; Matrix[0][2] = 0.0;
	Matrix[1][0] = 0.0; Matrix[1][1] = _y; Matrix[1][2] = 0.0;
	Matrix[2][0] = 0.0; Matrix[2][1] = 0.0; Matrix[2][2] = _z;

	return *this;
}

const BFW::Math::Mat3d BFW::Math::Mat3d::GetScale(const double _x, const double _y, const double _z)
{
	Mat3d _Matrix;

	_Matrix[0][0] = _x; _Matrix[0][1] = 0.0; _Matrix[0][2] = 0.0;
	_Matrix[1][0] = 0.0; _Matrix[1][1] = _y; _Matrix[1][2] = 0.0;
	_Matrix[2][0] = 0.0; _Matrix[2][1] = 0.0; _Matrix[2][2] = _z;

	return _Matrix;
}

const BFW::Math::Mat3d& BFW::Math::Mat3d::Fill(const double _Value)
{
	Matrix[0][0] = _Value; Matrix[0][1] = _Value; Matrix[0][2] = _Value;
	Matrix[1][0] = _Value; Matrix[1][1] = _Value; Matrix[1][2] = _Value;
	Matrix[2][0] = _Value; Matrix[2][1] = _Value; Matrix[2][2] = _Value;

	return *this;
}

const BFW::Math::Mat3d BFW::Math::Mat3d::GetFill(const double _Value)
{
	Mat3d _Matrix;

	_Matrix[0][0] = _Value; _Matrix[0][1] = _Value; _Matrix[0][2] = _Value;
	_Matrix[1][0] = _Value; _Matrix[1][1] = _Value; _Matrix[1][2] = _Value;
	_Matrix[2][0] = _Value; _Matrix[2][1] = _Value; _Matrix[2][2] = _Value;

	return _Matrix;
}

const BFW::Math::Mat3d& BFW::Math::Mat3d::Shear(const double _Value, const unsigned long _ShearedAxis, const unsigned long _ByAxis)
{
	Matrix[0][0] = 1.0; Matrix[0][1] = 0.0; Matrix[0][2] = 0.0;
	Matrix[1][0] = 0.0; Matrix[1][1] = 1.0; Matrix[1][2] = 0.0;
	Matrix[2][0] = 0.0; Matrix[2][1] = 0.0; Matrix[2][2] = 1.0;

	Matrix[_ShearedAxis][_ByAxis] = _Value;

	return *this;
}

const BFW::Math::Mat3d BFW::Math::Mat3d::GetShear(const double _Value, const unsigned long _ShearedAxis, const unsigned long _ByAxis)
{
	Mat3d _Matrix;

	_Matrix[0][0] = 1.0; _Matrix[0][1] = 0.0; _Matrix[0][2] = 0.0;
	_Matrix[1][0] = 0.0; _Matrix[1][1] = 1.0; _Matrix[1][2] = 0.0;
	_Matrix[2][0] = 0.0; _Matrix[2][1] = 0.0; _Matrix[2][2] = 1.0;

	_Matrix[_ShearedAxis][_ByAxis] = _Value;

	return _Matrix;
}

const BFW::Math::Mat3d& BFW::Math::Mat3d::Rotation(const double _Angle, const Vec3d& _U)
{
	double _Sin = dSin(_Angle);
	double _Cos = dCos(_Angle);

	Matrix[0][0] = _Cos + _U.x * _U.x * (1.0 - _Cos); Matrix[0][1] = _U.x * _U.y * (1.0 - _Cos) - _U.z * _Sin; Matrix[0][2] = _U.x * _U.z * (1.0 - _Cos) + _U.y * _Sin;
	Matrix[1][0] = _U.y * _U.x * (1.0 - _Cos) + _U.z * _Sin; Matrix[1][1] = _Cos + _U.y * _U.y * (1.0 - _Cos); Matrix[1][2] = _U.y * _U.z * (1.0 - _Cos) - _U.x * _Sin;
	Matrix[2][0] = _U.z * _U.x * (1.0 - _Cos) - _U.y * _Sin; Matrix[2][1] = _U.z * _U.y * (1.0 - _Cos) + _U.x * _Sin; Matrix[2][2] = _Cos + _U.z * _U.z * (1.0 - _Cos);

	return *this;
}

const BFW::Math::Mat3d BFW::Math::Mat3d::GetRotation(const double _Angle, const Vec3d& _U)
{
	double _Sin = dSin(_Angle);
	double _Cos = dCos(_Angle);

	Mat3d _Matrix;

	_Matrix[0][0] = _Cos + _U.x * _U.x * (1.0 - _Cos); _Matrix[0][1] = _U.x * _U.y * (1.0 - _Cos) - _U.z * _Sin; _Matrix[0][2] = _U.x * _U.z * (1.0 - _Cos) + _U.y * _Sin;
	_Matrix[1][0] = _U.y * _U.x * (1.0 - _Cos) + _U.z * _Sin; _Matrix[1][1] = _Cos + _U.y * _U.y * (1.0 - _Cos); _Matrix[1][2] = _U.y * _U.z * (1.0 - _Cos) - _U.x * _Sin;
	_Matrix[2][0] = _U.z * _U.x * (1.0 - _Cos) - _U.y * _Sin; _Matrix[2][1] = _U.z * _U.y * (1.0 - _Cos) + _U.x * _Sin; _Matrix[2][2] = _Cos + _U.z * _U.z * (1.0 - _Cos);

	return _Matrix;
}

const BFW::Math::Mat3d& BFW::Math::Mat3d::Translation(const Vec3d& _V)
{
	Matrix[0][0] = 1.0; Matrix[0][1] = 0.0; Matrix[0][2] = _V.x;
	Matrix[1][0] = 0.0; Matrix[1][1] = 1.0; Matrix[1][2] = _V.y;
	Matrix[2][0] = 0.0; Matrix[2][1] = 0.0; Matrix[2][2] = 1.0;

	return *this;
}

const BFW::Math::Mat3d BFW::Math::Mat3d::GetTranslation(const Vec3d& _V)
{
	Mat3d _Matrix;

	_Matrix[0][0] = 1.0; _Matrix[0][1] = 0.0; _Matrix[0][2] = _V.x;
	_Matrix[1][0] = 0.0; _Matrix[1][1] = 1.0; _Matrix[1][2] = _V.y;
	_Matrix[2][0] = 0.0; _Matrix[2][1] = 0.0; _Matrix[2][2] = 1.0;

	return _Matrix;
}

const BFW::Math::Mat3d& BFW::Math::Mat3d::Ortho(const double _Left, const double _Right, const double _Top, const double _Bottom)
{
	Matrix[0][0] = 2.0 / (_Right - _Left); Matrix[0][1] = 0.0; Matrix[0][2] = (_Right + _Left) / (_Left - _Right);
	Matrix[1][0] = 0.0; Matrix[1][1] = 2.0 / (_Top - _Bottom); Matrix[1][2] = Matrix[1][2] = (_Top + _Bottom) / (_Bottom - _Top);
	Matrix[2][0] = 0.0; Matrix[2][1] = 0.0; Matrix[2][2] = 1.0;

	return *this;
}

const BFW::Math::Mat3d BFW::Math::Mat3d::GetOrtho(const double _Left, const double _Right, const double _Top, const double _Bottom)
{
	Mat3d _Matrix;

	_Matrix[0][0] = 2.0 / (_Right - _Left); _Matrix[0][1] = 0.0; _Matrix[0][2] = (_Right + _Left) / (_Left - _Right);
	_Matrix[1][0] = 0.0; _Matrix[1][1] = 2.0 / (_Top - _Bottom); _Matrix[1][2] = _Matrix[1][2] = (_Top + _Bottom) / (_Bottom - _Top);
	_Matrix[2][0] = 0.0; _Matrix[2][1] = 0.0; _Matrix[2][2] = 1.0;

	return _Matrix;
}

const BFW::Math::Mat3d& BFW::Math::Mat3d::Flip(const Vec3d& _U, const Vec3d& _Center)
{
	double _Angle = _U.GetAngle() * 2.0;
	double _Sin = dSin(_Angle);
	double _Cos = dCos(_Angle);

	Matrix[0][0] = _Cos; Matrix[0][1] = _Sin; Matrix[0][2] = 0.0;
	Matrix[1][0] = _Sin; Matrix[1][1] = -_Cos; Matrix[1][2] = 0.0;
	Matrix[2][0] = 0.0; Matrix[2][1] = 0.0; Matrix[2][2] = 1.0;

	*this = GetTranslation(_Center) * (*this) * GetTranslation(-_Center);

	return *this;
}

const BFW::Math::Mat3d BFW::Math::Mat3d::GetFlip(const Vec3d& _U, const Vec3d& _Center)
{
	double _Angle = _U.GetAngle() * 2.0;
	double _Sin = dSin(_Angle);
	double _Cos = dCos(_Angle);

	Mat3d _Matrix;

	_Matrix[0][0] = _Cos; _Matrix[0][1] = _Sin; _Matrix[0][2] = 0.0;
	_Matrix[1][0] = _Sin; _Matrix[1][1] = -_Cos; _Matrix[1][2] = 0.0;
	_Matrix[2][0] = 0.0; _Matrix[2][1] = 0.0; _Matrix[2][2] = 1.0;

	_Matrix = GetTranslation(_Center) * _Matrix * GetTranslation(-_Center);

	return _Matrix;
}

const BFW::Math::Mat3d& BFW::Math::Mat3d::Flip(const Vec3d& _U)
{
	Matrix[0][0] = 1.0 - 2.0 * _U.x * _U.x; Matrix[0][1] = -2.0 * _U.x * _U.y; Matrix[0][2] = -2.0 * _U.x * _U.z;
	Matrix[1][0] = -2.0 * _U.x * _U.y; Matrix[1][1] = 1.0 - 2.0 * _U.y * _U.y; Matrix[1][2] = -2.0 * _U.y * _U.z;
	Matrix[2][0] = -2.0 * _U.x * _U.z; Matrix[2][1] = -2.0 * _U.y * _U.z; Matrix[2][2] = 1.0 - 2.0 * _U.z * _U.z;

	return *this;
}

const BFW::Math::Mat3d BFW::Math::Mat3d::GetFlip(const Vec3d& _U)
{
	Mat3d _Matrix;

	_Matrix[0][0] = 1.0 - 2.0 * _U.x * _U.x; _Matrix[0][1] = -2.0 * _U.x * _U.y; _Matrix[0][2] = -2.0 * _U.x * _U.z;
	_Matrix[1][0] = -2.0 * _U.x * _U.y; _Matrix[1][1] = 1.0 - 2.0 * _U.y * _U.y; _Matrix[1][2] = -2.0 * _U.y * _U.z;
	_Matrix[2][0] = -2.0 * _U.x * _U.z; _Matrix[2][1] = -2.0 * _U.y * _U.z; _Matrix[2][2] = 1.0 - 2.0 * _U.z * _U.z;

	return _Matrix;
}

const BFW::Math::Mat3d& BFW::Math::Mat3d::operator+ () const
{
	return *this;
}

const BFW::Math::Mat3d BFW::Math::Mat3d::operator- () const
{
	Mat3d _Matrix;

	_Matrix[0][0] = -Matrix[0][0]; _Matrix[0][1] = -Matrix[0][1]; _Matrix[0][2] = -Matrix[0][2];
	_Matrix[1][0] = -Matrix[1][0]; _Matrix[1][1] = -Matrix[1][1]; _Matrix[1][2] = -Matrix[1][2];
	_Matrix[2][0] = -Matrix[2][0]; _Matrix[2][1] = -Matrix[2][1]; _Matrix[2][2] = -Matrix[2][2];

	return _Matrix;
}

const BFW::Math::Vec3d BFW::Math::Mat3d::operator* (const Vec3d& _Vec) const
{
	double _x = _Vec.x * Matrix[0][0] + _Vec.y * Matrix[0][1] + _Vec.z * Matrix[0][2];
	double _y = _Vec.x * Matrix[1][0] + _Vec.y * Matrix[1][1] + _Vec.z * Matrix[1][2];
	double _z = _Vec.x * Matrix[2][0] + _Vec.y * Matrix[2][1] + _Vec.z * Matrix[2][2];

	return Vec3d(_x, _y, _z);
}

const BFW::Math::Mat3d BFW::Math::Mat3d::operator+ (const Mat3d& _Other) const
{
	Mat3d _Matrix;

	_Matrix[0][0] = Matrix[0][0] + _Other[0][0]; _Matrix[0][1] = Matrix[0][1] + _Other[0][1]; _Matrix[0][2] = Matrix[0][2] + _Other[0][2];
	_Matrix[1][0] = Matrix[1][0] + _Other[1][0]; _Matrix[1][1] = Matrix[1][1] + _Other[1][1]; _Matrix[1][2] = Matrix[1][2] + _Other[1][2];
	_Matrix[2][0] = Matrix[2][0] + _Other[2][0]; _Matrix[2][1] = Matrix[2][1] + _Other[2][1]; _Matrix[2][2] = Matrix[2][2] + _Other[2][2];

	return _Matrix;
}

const BFW::Math::Mat3d& BFW::Math::Mat3d::operator+= (const Mat3d& _Other)
{
	Matrix[0][0] += _Other[0][0]; Matrix[0][1] += _Other[0][1]; Matrix[0][2] += _Other[0][2];
	Matrix[1][0] += _Other[1][0]; Matrix[1][1] += _Other[1][1]; Matrix[1][2] += _Other[1][2];
	Matrix[2][0] += _Other[2][0]; Matrix[2][1] += _Other[2][1]; Matrix[2][2] += _Other[2][2];

	return *this;
}

const BFW::Math::Mat3d BFW::Math::Mat3d::operator+ (const double _Scale) const
{
	Mat3d _Matrix;

	_Matrix[0][0] = Matrix[0][0] + _Scale; _Matrix[0][1] = Matrix[0][1] + _Scale; _Matrix[0][2] = Matrix[0][2] + _Scale;
	_Matrix[1][0] = Matrix[1][0] + _Scale; _Matrix[1][1] = Matrix[1][1] + _Scale; _Matrix[1][2] = Matrix[1][2] + _Scale;
	_Matrix[2][0] = Matrix[2][0] + _Scale; _Matrix[2][1] = Matrix[2][1] + _Scale; _Matrix[2][2] = Matrix[2][2] + _Scale;

	return _Matrix;
}

const BFW::Math::Mat3d& BFW::Math::Mat3d::operator+= (const double _Scale)
{
	Matrix[0][0] += _Scale; Matrix[0][1] += _Scale; Matrix[0][2] += _Scale;
	Matrix[1][0] += _Scale; Matrix[1][1] += _Scale; Matrix[1][2] += _Scale;
	Matrix[2][0] += _Scale; Matrix[2][1] += _Scale; Matrix[2][2] += _Scale;

	return *this;
}

const BFW::Math::Mat3d BFW::Math::Mat3d::operator- (const Mat3d& _Other) const
{
	Mat3d _Matrix;

	_Matrix[0][0] = Matrix[0][0] - _Other[0][0]; _Matrix[0][1] = Matrix[0][1] - _Other[0][1]; _Matrix[0][2] = Matrix[0][2] - _Other[0][2];
	_Matrix[1][0] = Matrix[1][0] - _Other[1][0]; _Matrix[1][1] = Matrix[1][1] - _Other[1][1]; _Matrix[1][2] = Matrix[1][2] - _Other[1][2];
	_Matrix[2][0] = Matrix[2][0] - _Other[2][0]; _Matrix[2][1] = Matrix[2][1] - _Other[2][1]; _Matrix[2][2] = Matrix[2][2] - _Other[2][2];

	return _Matrix;
}

const BFW::Math::Mat3d& BFW::Math::Mat3d::operator-= (const Mat3d& _Other)
{
	Matrix[0][0] -= _Other[0][0]; Matrix[0][1] -= _Other[0][1]; Matrix[0][2] -= _Other[0][2];
	Matrix[1][0] -= _Other[1][0]; Matrix[1][1] -= _Other[1][1]; Matrix[1][2] -= _Other[1][2];
	Matrix[2][0] -= _Other[2][0]; Matrix[2][1] -= _Other[2][1]; Matrix[2][2] -= _Other[2][2];

	return *this;
}

const BFW::Math::Mat3d BFW::Math::Mat3d::operator- (const double _Scale) const
{
	Mat3d _Matrix;

	_Matrix[0][0] = Matrix[0][0] - _Scale; _Matrix[0][1] = Matrix[0][1] - _Scale; _Matrix[0][2] = Matrix[0][2] - _Scale;
	_Matrix[1][0] = Matrix[1][0] - _Scale; _Matrix[1][1] = Matrix[1][1] - _Scale; _Matrix[1][2] = Matrix[1][2] - _Scale;
	_Matrix[2][0] = Matrix[2][0] - _Scale; _Matrix[2][1] = Matrix[2][1] - _Scale; _Matrix[2][2] = Matrix[2][2] - _Scale;

	return _Matrix;
}

const BFW::Math::Mat3d& BFW::Math::Mat3d::operator-= (const double _Scale)
{
	Matrix[0][0] -= _Scale; Matrix[0][1] -= _Scale; Matrix[0][2] -= _Scale;
	Matrix[1][0] -= _Scale; Matrix[1][1] -= _Scale; Matrix[1][2] -= _Scale;
	Matrix[2][0] -= _Scale; Matrix[2][1] -= _Scale; Matrix[2][2] -= _Scale;

	return *this;
}

const BFW::Math::Mat3d BFW::Math::Mat3d::operator* (const Mat3d& _Other) const
{
	Mat3d _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Other[0][0] + Matrix[0][1] * _Other[1][0] + Matrix[0][2] * _Other[2][0];
	_Matrix[0][1] = Matrix[0][0] * _Other[0][1] + Matrix[0][1] * _Other[1][1] + Matrix[0][2] * _Other[2][1];
	_Matrix[0][2] = Matrix[0][0] * _Other[0][2] + Matrix[0][1] * _Other[1][2] + Matrix[0][2] * _Other[2][2];

	_Matrix[1][0] = Matrix[1][0] * _Other[0][0] + Matrix[1][1] * _Other[1][0] + Matrix[1][2] * _Other[2][0];
	_Matrix[1][1] = Matrix[1][0] * _Other[0][1] + Matrix[1][1] * _Other[1][1] + Matrix[1][2] * _Other[2][1];
	_Matrix[1][2] = Matrix[1][0] * _Other[0][2] + Matrix[1][1] * _Other[1][2] + Matrix[1][2] * _Other[2][2];

	_Matrix[2][0] = Matrix[2][0] * _Other[0][0] + Matrix[2][1] * _Other[1][0] + Matrix[2][2] * _Other[2][0];
	_Matrix[2][1] = Matrix[2][0] * _Other[0][1] + Matrix[2][1] * _Other[1][1] + Matrix[2][2] * _Other[2][1];
	_Matrix[2][2] = Matrix[2][0] * _Other[0][2] + Matrix[2][1] * _Other[1][2] + Matrix[2][2] * _Other[2][2];

	return _Matrix;
}

const BFW::Math::Mat3d& BFW::Math::Mat3d::operator*= (const Mat3d& _Other)
{
	Mat3d _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Other[0][0] + Matrix[0][1] * _Other[1][0] + Matrix[0][2] * _Other[2][0];
	_Matrix[0][1] = Matrix[0][0] * _Other[0][1] + Matrix[0][1] * _Other[1][1] + Matrix[0][2] * _Other[2][1];
	_Matrix[0][2] = Matrix[0][0] * _Other[0][2] + Matrix[0][1] * _Other[1][2] + Matrix[0][2] * _Other[2][2];

	_Matrix[1][0] = Matrix[1][0] * _Other[0][0] + Matrix[1][1] * _Other[1][0] + Matrix[1][2] * _Other[2][0];
	_Matrix[1][1] = Matrix[1][0] * _Other[0][1] + Matrix[1][1] * _Other[1][1] + Matrix[1][2] * _Other[2][1];
	_Matrix[1][2] = Matrix[1][0] * _Other[0][2] + Matrix[1][1] * _Other[1][2] + Matrix[1][2] * _Other[2][2];

	_Matrix[2][0] = Matrix[2][0] * _Other[0][0] + Matrix[2][1] * _Other[1][0] + Matrix[2][2] * _Other[2][0];
	_Matrix[2][1] = Matrix[2][0] * _Other[0][1] + Matrix[2][1] * _Other[1][1] + Matrix[2][2] * _Other[2][1];
	_Matrix[2][2] = Matrix[2][0] * _Other[0][2] + Matrix[2][1] * _Other[1][2] + Matrix[2][2] * _Other[2][2];

	*this = _Matrix;

	return *this;
}

const BFW::Math::Mat3d BFW::Math::Mat3d::operator* (const double _Scale) const
{
	Mat3d _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Scale; _Matrix[0][1] = Matrix[0][1] * _Scale; _Matrix[0][2] = Matrix[0][2] * _Scale;
	_Matrix[1][0] = Matrix[1][0] * _Scale; _Matrix[1][1] = Matrix[1][1] * _Scale; _Matrix[1][2] = Matrix[1][2] * _Scale;
	_Matrix[2][0] = Matrix[2][0] * _Scale; _Matrix[2][1] = Matrix[2][1] * _Scale; _Matrix[2][2] = Matrix[2][2] * _Scale;

	return _Matrix;
}

const BFW::Math::Mat3d& BFW::Math::Mat3d::operator*= (const double _Scale)
{
	Matrix[0][0] *= _Scale; Matrix[0][1] *= _Scale; Matrix[0][2] *= _Scale;
	Matrix[1][0] *= _Scale; Matrix[1][1] *= _Scale; Matrix[1][2] *= _Scale;
	Matrix[2][0] *= _Scale; Matrix[2][1] *= _Scale; Matrix[2][2] *= _Scale;

	return *this;
}

const BFW::Math::Mat3d BFW::Math::Mat3d::operator/ (const double _Scale) const
{
	Mat3d _Matrix;

	_Matrix[0][0] = Matrix[0][0] / _Scale; _Matrix[0][1] = Matrix[0][1] / _Scale; _Matrix[0][2] = Matrix[0][2] / _Scale;
	_Matrix[1][0] = Matrix[1][0] / _Scale; _Matrix[1][1] = Matrix[1][1] / _Scale; _Matrix[1][2] = Matrix[1][2] / _Scale;
	_Matrix[2][0] = Matrix[2][0] / _Scale; _Matrix[2][1] = Matrix[2][1] / _Scale; _Matrix[2][2] = Matrix[2][2] / _Scale;

	return _Matrix;
}

const BFW::Math::Mat3d& BFW::Math::Mat3d::operator/= (const double _Scale)
{
	Matrix[0][0] /= _Scale; Matrix[0][1] /= _Scale; Matrix[0][2] /= _Scale;
	Matrix[1][0] /= _Scale; Matrix[1][1] /= _Scale; Matrix[1][2] /= _Scale;
	Matrix[2][0] /= _Scale; Matrix[2][1] /= _Scale; Matrix[2][2] /= _Scale;

	return *this;
}

const bool BFW::Math::Mat3d::operator== (const Mat3d& _Other) const
{
	return
		Matrix[0][0] == _Other[0][0] && Matrix[0][1] == _Other[0][1] && Matrix[0][2] == _Other[0][2] &&
		Matrix[1][0] == _Other[1][0] && Matrix[1][1] == _Other[1][1] && Matrix[1][2] == _Other[1][2] &&
		Matrix[2][0] == _Other[2][0] && Matrix[2][1] == _Other[2][1] && Matrix[2][2] == _Other[2][2];
}

const bool BFW::Math::Mat3d::operator!= (const Mat3d& _Other) const
{
	return
		Matrix[0][0] != _Other[0][0] || Matrix[0][1] != _Other[0][1] || Matrix[0][2] != _Other[0][2] ||
		Matrix[1][0] != _Other[1][0] || Matrix[1][1] != _Other[1][1] || Matrix[1][2] != _Other[1][2] ||
		Matrix[2][0] != _Other[2][0] || Matrix[2][1] != _Other[2][1] || Matrix[2][2] != _Other[2][2];
}

const bool BFW::Math::Mat3d::operator> (const Mat3d& _Other) const
{
	return Determinant() > _Other.Determinant();
}

const bool BFW::Math::Mat3d::operator>= (const Mat3d& _Other) const
{
	return Determinant() >= _Other.Determinant();
}

const bool BFW::Math::Mat3d::operator< (const Mat3d& _Other) const
{
	return Determinant() < _Other.Determinant();
}

const bool BFW::Math::Mat3d::operator<= (const Mat3d& _Other) const
{
	return Determinant() <= _Other.Determinant();
}

double* BFW::Math::Mat3d::operator[] (const unsigned long _Index)
{
	return Matrix[_Index].Data();
}

const double* BFW::Math::Mat3d::operator[] (const unsigned long _Index) const
{
	return Matrix[_Index].Data();
}

const BFW::Math::Mat3d& BFW::Math::Mat3d::operator= (const Mat3d& _Other)
{
	Matrix[0][0] = _Other.Matrix[0][0]; Matrix[0][1] = _Other.Matrix[0][1]; Matrix[0][2] = _Other.Matrix[0][2];
	Matrix[1][0] = _Other.Matrix[1][0]; Matrix[1][1] = _Other.Matrix[1][1]; Matrix[1][2] = _Other.Matrix[1][2];
	Matrix[2][0] = _Other.Matrix[2][0]; Matrix[2][1] = _Other.Matrix[2][1]; Matrix[2][2] = _Other.Matrix[2][2];

	return *this;
}

const BFW::Math::Mat3d& BFW::Math::Mat3d::operator= (Mat3d&& _Other) noexcept
{
	Matrix[0][0] = _Other.Matrix[0][0]; Matrix[0][1] = _Other.Matrix[0][1]; Matrix[0][2] = _Other.Matrix[0][2];
	Matrix[1][0] = _Other.Matrix[1][0]; Matrix[1][1] = _Other.Matrix[1][1]; Matrix[1][2] = _Other.Matrix[1][2];
	Matrix[2][0] = _Other.Matrix[2][0]; Matrix[2][1] = _Other.Matrix[2][1]; Matrix[2][2] = _Other.Matrix[2][2];

	_Other.Matrix[0][0] = 1.0; _Other.Matrix[0][1] = 0.0; _Other.Matrix[0][2] = 0.0;
	_Other.Matrix[1][0] = 0.0; _Other.Matrix[1][1] = 1.0; _Other.Matrix[1][2] = 0.0;
	_Other.Matrix[2][0] = 0.0; _Other.Matrix[2][1] = 0.0; _Other.Matrix[2][2] = 1.0;

	return *this;
}



BFW::Math::Mat4d::Mat4d() : Matrix()
{
	Matrix[0][0] = 1.0; Matrix[0][1] = 0.0; Matrix[0][2] = 0.0; Matrix[0][3] = 0.0;
	Matrix[1][0] = 0.0; Matrix[1][1] = 1.0; Matrix[1][2] = 0.0; Matrix[1][3] = 0.0;
	Matrix[2][0] = 0.0; Matrix[2][1] = 0.0; Matrix[2][2] = 1.0; Matrix[2][3] = 0.0;
	Matrix[3][0] = 0.0; Matrix[3][1] = 0.0; Matrix[3][2] = 0.0; Matrix[3][3] = 1.0;
}

BFW::Math::Mat4d::Mat4d(const double _x, const double _y, const double _z) : Matrix()
{
	Matrix[0][0] = _x; Matrix[0][1] = 0.0; Matrix[0][2] = 0.0; Matrix[0][3] = 0.0;
	Matrix[1][0] = 0.0; Matrix[1][1] = _y; Matrix[1][2] = 0.0; Matrix[1][3] = 0.0;
	Matrix[2][0] = 0.0; Matrix[2][1] = 0.0; Matrix[2][2] = _z; Matrix[2][3] = 0.0;
	Matrix[3][0] = 0.0; Matrix[3][1] = 0.0; Matrix[3][2] = 0.0; Matrix[3][3] = 1.0;
}

BFW::Math::Mat4d::Mat4d(const Mat4d& _Other) : Matrix()
{
	Matrix[0][0] = _Other.Matrix[0][0]; Matrix[0][1] = _Other.Matrix[0][1]; Matrix[0][2] = _Other.Matrix[0][2]; Matrix[0][3] = _Other.Matrix[0][3];
	Matrix[1][0] = _Other.Matrix[1][0]; Matrix[1][1] = _Other.Matrix[1][1]; Matrix[1][2] = _Other.Matrix[1][2]; Matrix[1][3] = _Other.Matrix[1][3];
	Matrix[2][0] = _Other.Matrix[2][0]; Matrix[2][1] = _Other.Matrix[2][1]; Matrix[2][2] = _Other.Matrix[2][2]; Matrix[2][3] = _Other.Matrix[2][3];
	Matrix[3][0] = _Other.Matrix[3][0]; Matrix[3][1] = _Other.Matrix[3][1]; Matrix[3][2] = _Other.Matrix[3][2]; Matrix[3][3] = _Other.Matrix[3][3];
}

BFW::Math::Mat4d::Mat4d(Mat4d&& _Other) noexcept : Matrix()
{
	Matrix[0][0] = _Other.Matrix[0][0]; Matrix[0][1] = _Other.Matrix[0][1]; Matrix[0][2] = _Other.Matrix[0][2]; Matrix[0][3] = _Other.Matrix[0][3];
	Matrix[1][0] = _Other.Matrix[1][0]; Matrix[1][1] = _Other.Matrix[1][1]; Matrix[1][2] = _Other.Matrix[1][2]; Matrix[1][3] = _Other.Matrix[1][3];
	Matrix[2][0] = _Other.Matrix[2][0]; Matrix[2][1] = _Other.Matrix[2][1]; Matrix[2][2] = _Other.Matrix[2][2]; Matrix[2][3] = _Other.Matrix[2][3];
	Matrix[3][0] = _Other.Matrix[3][0]; Matrix[3][1] = _Other.Matrix[3][1]; Matrix[3][2] = _Other.Matrix[3][2]; Matrix[3][3] = _Other.Matrix[3][3];

	_Other.Matrix[0][0] = 1.0; _Other.Matrix[0][1] = 0.0; _Other.Matrix[0][2] = 0.0; _Other.Matrix[0][3] = 0.0;
	_Other.Matrix[1][0] = 0.0; _Other.Matrix[1][1] = 1.0; _Other.Matrix[1][2] = 0.0; _Other.Matrix[1][3] = 0.0;
	_Other.Matrix[2][0] = 0.0; _Other.Matrix[2][1] = 0.0; _Other.Matrix[2][2] = 1.0; _Other.Matrix[2][3] = 0.0;
	_Other.Matrix[3][0] = 0.0; _Other.Matrix[3][1] = 0.0; _Other.Matrix[3][2] = 0.0; _Other.Matrix[3][3] = 1.0;
}

BFW::Math::Mat4d::~Mat4d()
{

}

double* BFW::Math::Mat4d::Data()
{
	return Matrix[0].Data();
}

const double* BFW::Math::Mat4d::Data() const
{
	return Matrix[0].Data();
}

const double BFW::Math::Mat4d::Determinant() const
{
	Mat3d _Mat[4];

	Mat3d& _Matrix = *((Mat3d*)(nullptr));

	_Matrix = _Mat[0];

	_Matrix[0][0] = Matrix[1][1]; _Matrix[0][1] = Matrix[1][2]; _Matrix[0][2] = Matrix[1][3];
	_Matrix[1][0] = Matrix[2][1]; _Matrix[1][1] = Matrix[2][2]; _Matrix[1][2] = Matrix[2][3];
	_Matrix[2][0] = Matrix[3][1]; _Matrix[2][1] = Matrix[3][2]; _Matrix[2][2] = Matrix[3][3];

	_Matrix = _Mat[1];

	_Matrix[0][0] = Matrix[0][1]; _Matrix[0][1] = Matrix[0][2]; _Matrix[0][2] = Matrix[0][3];
	_Matrix[1][0] = Matrix[2][1]; _Matrix[1][1] = Matrix[2][2]; _Matrix[1][2] = Matrix[2][3];
	_Matrix[2][0] = Matrix[3][1]; _Matrix[2][1] = Matrix[3][2]; _Matrix[2][2] = Matrix[3][3];

	_Matrix = _Mat[2];

	_Matrix[0][0] = Matrix[0][1]; _Matrix[0][1] = Matrix[0][2]; _Matrix[0][2] = Matrix[0][3];
	_Matrix[1][0] = Matrix[1][1]; _Matrix[1][1] = Matrix[1][2]; _Matrix[1][2] = Matrix[1][3];
	_Matrix[2][0] = Matrix[3][1]; _Matrix[2][1] = Matrix[3][2]; _Matrix[2][2] = Matrix[3][3];

	_Matrix = _Mat[3];

	_Matrix[0][0] = Matrix[0][1]; _Matrix[0][1] = Matrix[0][2]; _Matrix[0][2] = Matrix[0][3];
	_Matrix[1][0] = Matrix[1][1]; _Matrix[1][1] = Matrix[1][2]; _Matrix[1][2] = Matrix[1][3];
	_Matrix[2][0] = Matrix[2][1]; _Matrix[2][1] = Matrix[2][2]; _Matrix[2][2] = Matrix[2][3];

	return
		Matrix[0][0] * _Mat[0].Determinant() -
		Matrix[1][0] * _Mat[1].Determinant() +
		Matrix[2][0] * _Mat[2].Determinant() -
		Matrix[3][0] * _Mat[3].Determinant();
}

const double BFW::Math::Mat4d::Trace() const
{
	return Matrix[0][0] + Matrix[1][1] + Matrix[2][2] + Matrix[3][3];
}

const BFW::Math::Mat4d& BFW::Math::Mat4d::Transpose()
{
	dSwap(Matrix[0][1], Matrix[1][0]);
	dSwap(Matrix[0][2], Matrix[2][0]);
	dSwap(Matrix[0][3], Matrix[3][0]);
	dSwap(Matrix[1][2], Matrix[2][1]);
	dSwap(Matrix[1][3], Matrix[3][1]);
	dSwap(Matrix[2][3], Matrix[3][2]);

	return *this;
}

const BFW::Math::Mat4d BFW::Math::Mat4d::Transposed() const
{
	Mat4d _Matrix;

	_Matrix[0][0] = Matrix[0][0]; _Matrix[0][1] = Matrix[1][0]; _Matrix[0][2] = Matrix[2][0]; _Matrix[0][3] = Matrix[3][0];
	_Matrix[1][0] = Matrix[0][1]; _Matrix[1][1] = Matrix[1][1]; _Matrix[1][2] = Matrix[2][1]; _Matrix[1][3] = Matrix[3][1];
	_Matrix[2][0] = Matrix[0][2]; _Matrix[2][1] = Matrix[1][2]; _Matrix[2][2] = Matrix[2][2]; _Matrix[2][3] = Matrix[3][2];
	_Matrix[3][0] = Matrix[0][3]; _Matrix[3][1] = Matrix[1][3]; _Matrix[3][2] = Matrix[2][3]; _Matrix[3][3] = Matrix[3][3];

	return _Matrix;
}

const BFW::Math::Mat4d& BFW::Math::Mat4d::Scale(const double _x, const double _y, const double _z)
{
	Matrix[0][0] = _x; Matrix[0][1] = 0.0; Matrix[0][2] = 0.0; Matrix[0][3] = 0.0;
	Matrix[1][0] = 0.0; Matrix[1][1] = _y; Matrix[1][2] = 0.0; Matrix[1][3] = 0.0;
	Matrix[2][0] = 0.0; Matrix[2][1] = 0.0; Matrix[2][2] = _z; Matrix[2][3] = 0.0;
	Matrix[3][0] = 0.0; Matrix[3][1] = 0.0; Matrix[3][2] = 0.0; Matrix[3][3] = 1.0;

	return *this;
}

const BFW::Math::Mat4d BFW::Math::Mat4d::GetScale(const double _x, const double _y, const double _z)
{
	Mat4d _Matrix;

	_Matrix[0][0] = _x; _Matrix[0][1] = 0.0; _Matrix[0][2] = 0.0; _Matrix[0][3] = 0.0;
	_Matrix[1][0] = 0.0; _Matrix[1][1] = _y; _Matrix[1][2] = 0.0; _Matrix[1][3] = 0.0;
	_Matrix[2][0] = 0.0; _Matrix[2][1] = 0.0; _Matrix[2][2] = _z; _Matrix[2][3] = 0.0;
	_Matrix[3][0] = 0.0; _Matrix[3][1] = 0.0; _Matrix[3][2] = 0.0; _Matrix[3][3] = 1.0;

	return _Matrix;
}

const BFW::Math::Mat4d& BFW::Math::Mat4d::Fill(const double _Value)
{
	Matrix[0][0] = _Value; Matrix[0][1] = _Value; Matrix[0][2] = _Value; Matrix[0][3] = _Value;
	Matrix[1][0] = _Value; Matrix[1][1] = _Value; Matrix[1][2] = _Value; Matrix[1][3] = _Value;
	Matrix[2][0] = _Value; Matrix[2][1] = _Value; Matrix[2][2] = _Value; Matrix[2][3] = _Value;
	Matrix[3][0] = _Value; Matrix[3][1] = _Value; Matrix[3][2] = _Value; Matrix[3][3] = _Value;

	return *this;
}

const BFW::Math::Mat4d BFW::Math::Mat4d::GetFill(const double _Value)
{
	Mat4d _Matrix;

	_Matrix[0][0] = _Value; _Matrix[0][1] = _Value; _Matrix[0][2] = _Value; _Matrix[0][3] = _Value;
	_Matrix[1][0] = _Value; _Matrix[1][1] = _Value; _Matrix[1][2] = _Value; _Matrix[1][3] = _Value;
	_Matrix[2][0] = _Value; _Matrix[2][1] = _Value; _Matrix[2][2] = _Value; _Matrix[2][3] = _Value;
	_Matrix[3][0] = _Value; _Matrix[3][1] = _Value; _Matrix[3][2] = _Value; _Matrix[3][3] = _Value;

	return _Matrix;
}

const BFW::Math::Mat4d& BFW::Math::Mat4d::Shear(const double _Value, const unsigned long _ShearedAxis, const unsigned long _ByAxis)
{
	Matrix[0][0] = 1.0; Matrix[0][1] = 0.0; Matrix[0][2] = 0.0; Matrix[0][3] = 0.0;
	Matrix[1][0] = 0.0; Matrix[1][1] = 1.0; Matrix[1][2] = 0.0; Matrix[1][3] = 0.0;
	Matrix[2][0] = 0.0; Matrix[2][1] = 0.0; Matrix[2][2] = 1.0; Matrix[2][3] = 0.0;
	Matrix[3][0] = 0.0; Matrix[3][1] = 0.0; Matrix[3][2] = 0.0; Matrix[3][3] = 1.0;

	Matrix[_ShearedAxis][_ByAxis] = _Value;

	return *this;
}

const BFW::Math::Mat4d BFW::Math::Mat4d::GetShear(const double _Value, const unsigned long _ShearedAxis, const unsigned long _ByAxis)
{
	Mat4d _Matrix;

	_Matrix[0][0] = 1.0; _Matrix[0][1] = 0.0; _Matrix[0][2] = 0.0; _Matrix[0][3] = 0.0;
	_Matrix[1][0] = 0.0; _Matrix[1][1] = 1.0; _Matrix[1][2] = 0.0; _Matrix[1][3] = 0.0;
	_Matrix[2][0] = 0.0; _Matrix[2][1] = 0.0; _Matrix[2][2] = 1.0; _Matrix[2][3] = 0.0;
	_Matrix[3][0] = 0.0; _Matrix[3][1] = 0.0; _Matrix[3][2] = 0.0; _Matrix[3][3] = 1.0;

	_Matrix[_ShearedAxis][_ByAxis] = _Value;

	return _Matrix;
}

const BFW::Math::Mat4d& BFW::Math::Mat4d::Rotation(const double _Angle, const Vec4d& _U)
{
	double _Sin = dSin(_Angle);
	double _Cos = dCos(_Angle);

	Matrix[0][0] = _Cos + _U.x * _U.x * (1.0 - _Cos); Matrix[0][1] = _U.x * _U.y * (1.0 - _Cos) - _U.z * _Sin; Matrix[0][2] = _U.x * _U.z * (1.0 - _Cos) + _U.y * _Sin; Matrix[0][3] = 0.0;
	Matrix[1][0] = _U.y * _U.x * (1.0 - _Cos) + _U.z * _Sin; Matrix[1][1] = _Cos + _U.y * _U.y * (1.0 - _Cos); Matrix[1][2] = _U.y * _U.z * (1.0 - _Cos) - _U.x * _Sin; Matrix[1][3] = 0.0;
	Matrix[2][0] = _U.z * _U.x * (1.0 - _Cos) - _U.y * _Sin; Matrix[2][1] = _U.z * _U.y * (1.0 - _Cos) + _U.x * _Sin; Matrix[2][2] = _Cos + _U.z * _U.z * (1.0 - _Cos); Matrix[2][3] = 0.0;
	Matrix[3][0] = 0.0; Matrix[3][1] = 0.0; Matrix[3][2] = 0.0; Matrix[3][3] = 1.0;

	return *this;
}

const BFW::Math::Mat4d BFW::Math::Mat4d::GetRotation(const double _Angle, const Vec4d& _U)
{
	double _Sin = dSin(_Angle);
	double _Cos = dCos(_Angle);

	Mat4d _Matrix;

	_Matrix[0][0] = _Cos + _U.x * _U.x * (1.0 - _Cos); _Matrix[0][1] = _U.x * _U.y * (1.0 - _Cos) - _U.z * _Sin; _Matrix[0][2] = _U.x * _U.z * (1.0 - _Cos) + _U.y * _Sin; _Matrix[0][3] = 0.0;
	_Matrix[1][0] = _U.y * _U.x * (1.0 - _Cos) + _U.z * _Sin; _Matrix[1][1] = _Cos + _U.y * _U.y * (1.0 - _Cos); _Matrix[1][2] = _U.y * _U.z * (1.0 - _Cos) - _U.x * _Sin; _Matrix[1][3] = 0.0;
	_Matrix[2][0] = _U.z * _U.x * (1.0 - _Cos) - _U.y * _Sin; _Matrix[2][1] = _U.z * _U.y * (1.0 - _Cos) + _U.x * _Sin; _Matrix[2][2] = _Cos + _U.z * _U.z * (1.0 - _Cos); _Matrix[2][3] = 0.0;
	_Matrix[3][0] = 0.0; _Matrix[3][1] = 0.0; _Matrix[3][2] = 0.0; _Matrix[3][3] = 1.0;

	return _Matrix;
}

const BFW::Math::Mat4d& BFW::Math::Mat4d::Translation(const Vec4d& _V)
{
	Matrix[0][0] = 1.0; Matrix[0][1] = 0.0; Matrix[0][2] = 0.0; Matrix[0][3] = _V.x;
	Matrix[1][0] = 0.0; Matrix[1][1] = 1.0; Matrix[1][2] = 0.0; Matrix[1][3] = _V.y;
	Matrix[2][0] = 0.0; Matrix[2][1] = 0.0; Matrix[2][2] = 1.0; Matrix[2][3] = _V.z;
	Matrix[3][0] = 0.0; Matrix[3][1] = 0.0; Matrix[3][2] = 0.0; Matrix[3][3] = 1.0;

	return *this;
}

const BFW::Math::Mat4d BFW::Math::Mat4d::GetTranslation(const Vec4d& _V)
{
	Mat4d _Matrix;

	_Matrix[0][0] = 1.0; _Matrix[0][1] = 0.0; _Matrix[0][2] = 0.0; _Matrix[0][3] = _V.x;
	_Matrix[1][0] = 0.0; _Matrix[1][1] = 1.0; _Matrix[1][2] = 0.0; _Matrix[1][3] = _V.y;
	_Matrix[2][0] = 0.0; _Matrix[2][1] = 0.0; _Matrix[2][2] = 1.0; _Matrix[2][3] = _V.z;
	_Matrix[3][0] = 0.0; _Matrix[3][1] = 0.0; _Matrix[3][2] = 0.0; _Matrix[3][3] = 1.0;

	return _Matrix;
}

const BFW::Math::Mat4d& BFW::Math::Mat4d::Ortho(const double _Left, const double _Right, const double _Top, const double _Bottom, const double _Front, const double _Back)
{
	Matrix[0][0] = 2.0 / (_Right - _Left); Matrix[0][1] = 0.0; Matrix[0][2] = 0.0; Matrix[0][3] = (_Right + _Left) / (_Left - _Right);
	Matrix[1][0] = 0.0; Matrix[1][1] = 2.0 / (_Top - _Bottom); Matrix[1][2] = 0.0; Matrix[1][3] = (_Top + _Bottom) / (_Bottom - _Top);
	Matrix[2][0] = 0.0; Matrix[2][1] = 0.0; Matrix[2][2] = 2.0 / (_Front - _Back); Matrix[2][3] = (_Front + _Back) / (_Back - _Front);
	Matrix[3][0] = 0.0; Matrix[3][1] = 0.0; Matrix[3][2] = 0.0; Matrix[3][3] = 1.0;

	return *this;
}

const BFW::Math::Mat4d BFW::Math::Mat4d::GetOrtho(const double _Left, const double _Right, const double _Top, const double _Bottom, const double _Front, const double _Back)
{
	Mat4d _Matrix;

	_Matrix[0][0] = 2.0 / (_Right - _Left); _Matrix[0][1] = 0.0; _Matrix[0][2] = 0.0; _Matrix[0][3] = (_Right + _Left) / (_Left - _Right);
	_Matrix[1][0] = 0.0; _Matrix[1][1] = 2.0 / (_Top - _Bottom); _Matrix[1][2] = 0.0; _Matrix[1][3] = (_Top + _Bottom) / (_Bottom - _Top);
	_Matrix[2][0] = 0.0; _Matrix[2][1] = 0.0; _Matrix[2][2] = 2.0 / (_Front - _Back); _Matrix[2][3] = (_Front + _Back) / (_Back - _Front);
	_Matrix[3][0] = 0.0; _Matrix[3][1] = 0.0; _Matrix[3][2] = 0.0; _Matrix[3][3] = 1.0;

	return _Matrix;
}

const BFW::Math::Mat4d& BFW::Math::Mat4d::Perspective(const double _Fov, const double _AspectRatio, const double _ZNear, const double _ZFar)
{
	double _Tan = dTan(_Fov / 2.0);

	Matrix[0][0] = 1.0 / (_AspectRatio * _Tan); Matrix[0][1] = 0.0; Matrix[0][2] = 0.0; Matrix[0][3] = 0.0;
	Matrix[1][0] = 0.0; Matrix[1][1] = 1.0 / _Tan; Matrix[1][2] = 0.0; Matrix[1][3] = 0.0;
	Matrix[2][0] = 0.0; Matrix[2][1] = 0.0; Matrix[2][2] = -(_ZFar + _ZNear) / (_ZFar - _ZNear); Matrix[2][3] = -(2.0 * _ZFar * _ZNear) / (_ZFar - _ZNear);
	Matrix[3][0] = 0.0; Matrix[3][1] = 0.0; Matrix[3][2] = -1.0; Matrix[3][3] = 0.0;

	return *this;
}

const BFW::Math::Mat4d BFW::Math::Mat4d::GetPerspective(const double _Fov, const double _AspectRatio, const double _ZNear, const double _ZFar)
{
	double _Tan = dTan(_Fov / 2.0);

	Mat4d _Matrix;

	_Matrix[0][0] = 1.0 / (_AspectRatio * _Tan); _Matrix[0][1] = 0.0; _Matrix[0][2] = 0.0; _Matrix[0][3] = 0.0;
	_Matrix[1][0] = 0.0; _Matrix[1][1] = 1.0 / _Tan; _Matrix[1][2] = 0.0; _Matrix[1][3] = 0.0;
	_Matrix[2][0] = 0.0; _Matrix[2][1] = 0.0; _Matrix[2][2] = -(_ZFar + _ZNear) / (_ZFar - _ZNear); _Matrix[2][3] = -(2.0 * _ZFar * _ZNear) / (_ZFar - _ZNear);
	_Matrix[3][0] = 0.0; _Matrix[3][1] = 0.0; _Matrix[3][2] = -1.0; _Matrix[3][3] = 0.0;

	return _Matrix;
}

const BFW::Math::Mat4d& BFW::Math::Mat4d::Flip(const Vec4d& _U, const Vec4d& _Center)
{
	Matrix[0][0] = 1.0 - 2.0 * _U.x * _U.x; Matrix[0][1] = -2.0 * _U.x * _U.y; Matrix[0][2] = -2.0 * _U.x * _U.z; Matrix[0][3] = 0.0;
	Matrix[1][0] = -2.0 * _U.x * _U.y; Matrix[1][1] = 1.0 - 2.0 * _U.y * _U.y; Matrix[1][2] = -2.0 * _U.y * _U.z; Matrix[1][3] = 0.0;
	Matrix[2][0] = -2.0 * _U.x * _U.z; Matrix[2][1] = -2.0 * _U.y * _U.z; Matrix[2][2] = 1.0 - 2.0 * _U.z * _U.z; Matrix[2][3] = 0.0;
	Matrix[3][0] = 0.0; Matrix[3][1] = 0.0; Matrix[3][2] = 0.0; Matrix[3][3] = 1.0;

	*this = GetTranslation(_Center) * (*this) * GetTranslation(-_Center);

	return *this;
}

const BFW::Math::Mat4d BFW::Math::Mat4d::GetFlip(const Vec4d& _U, const Vec4d& _Center)
{
	Mat4d _Matrix;

	_Matrix[0][0] = 1.0 - 2.0 * _U.x * _U.x; _Matrix[0][1] = -2.0 * _U.x * _U.y; _Matrix[0][2] = -2.0 * _U.x * _U.z; _Matrix[0][3] = 0.0;
	_Matrix[1][0] = -2.0 * _U.x * _U.y; _Matrix[1][1] = 1.0 - 2.0 * _U.y * _U.y; _Matrix[1][2] = -2.0 * _U.y * _U.z; _Matrix[1][3] = 0.0;
	_Matrix[2][0] = -2.0 * _U.x * _U.z; _Matrix[2][1] = -2.0 * _U.y * _U.z; _Matrix[2][2] = 1.0 - 2.0 * _U.z * _U.z; _Matrix[2][3] = 0.0;
	_Matrix[3][0] = 0.0; _Matrix[3][1] = 0.0; _Matrix[3][2] = 0.0; _Matrix[3][3] = 1.0;

	_Matrix = GetTranslation(_Center) * _Matrix * GetTranslation(-_Center);

	return _Matrix;
}

const BFW::Math::Mat4d& BFW::Math::Mat4d::operator+ () const
{
	return *this;
}

const BFW::Math::Mat4d BFW::Math::Mat4d::operator- () const
{
	Mat4d _Matrix;

	_Matrix[0][0] = -Matrix[0][0]; _Matrix[0][1] = -Matrix[0][1]; _Matrix[0][2] = -Matrix[0][2]; _Matrix[0][3] = -Matrix[0][3];
	_Matrix[1][0] = -Matrix[1][0]; _Matrix[1][1] = -Matrix[1][1]; _Matrix[1][2] = -Matrix[1][2]; _Matrix[1][3] = -Matrix[1][3];
	_Matrix[2][0] = -Matrix[2][0]; _Matrix[2][1] = -Matrix[2][1]; _Matrix[2][2] = -Matrix[2][2]; _Matrix[2][3] = -Matrix[2][3];
	_Matrix[3][0] = -Matrix[3][0]; _Matrix[3][1] = -Matrix[3][1]; _Matrix[3][2] = -Matrix[3][2]; _Matrix[3][3] = -Matrix[3][3];

	return _Matrix;
}

const BFW::Math::Vec4d BFW::Math::Mat4d::operator* (const Vec4d& _Vec) const
{
	double _x = _Vec.x * Matrix[0][0] + _Vec.y * Matrix[0][1] + _Vec.z * Matrix[0][2] + _Vec.w * Matrix[0][3];
	double _y = _Vec.x * Matrix[1][0] + _Vec.y * Matrix[1][1] + _Vec.z * Matrix[1][2] + _Vec.w * Matrix[1][3];
	double _z = _Vec.x * Matrix[2][0] + _Vec.y * Matrix[2][1] + _Vec.z * Matrix[2][2] + _Vec.w * Matrix[2][3];
	double _w = _Vec.x * Matrix[3][0] + _Vec.y * Matrix[3][1] + _Vec.z * Matrix[3][2] + _Vec.w * Matrix[3][3];

	return Vec4d(_x, _y, _z, _w);
}

const BFW::Math::Mat4d BFW::Math::Mat4d::operator+ (const Mat4d& _Other) const
{
	Mat4d _Matrix;

	_Matrix[0][0] = Matrix[0][0] + _Other[0][0]; _Matrix[0][1] = Matrix[0][1] + _Other[0][1]; _Matrix[0][2] = Matrix[0][2] + _Other[0][2]; _Matrix[0][3] = Matrix[0][3] + _Other[0][3];
	_Matrix[1][0] = Matrix[1][0] + _Other[1][0]; _Matrix[1][1] = Matrix[1][1] + _Other[1][1]; _Matrix[1][2] = Matrix[1][2] + _Other[1][2]; _Matrix[1][3] = Matrix[1][3] + _Other[1][3];
	_Matrix[2][0] = Matrix[2][0] + _Other[2][0]; _Matrix[2][1] = Matrix[2][1] + _Other[2][1]; _Matrix[2][2] = Matrix[2][2] + _Other[2][2]; _Matrix[2][3] = Matrix[2][3] + _Other[2][3];
	_Matrix[3][0] = Matrix[3][0] + _Other[3][0]; _Matrix[3][1] = Matrix[3][1] + _Other[3][1]; _Matrix[3][2] = Matrix[3][2] + _Other[3][2]; _Matrix[3][3] = Matrix[3][3] + _Other[3][3];

	return _Matrix;
}

const BFW::Math::Mat4d& BFW::Math::Mat4d::operator+= (const Mat4d& _Other)
{
	Matrix[0][0] += _Other[0][0]; Matrix[0][1] += _Other[0][1]; Matrix[0][2] += _Other[0][2]; Matrix[0][3] += _Other[0][3];
	Matrix[1][0] += _Other[1][0]; Matrix[1][1] += _Other[1][1]; Matrix[1][2] += _Other[1][2]; Matrix[1][3] += _Other[1][3];
	Matrix[2][0] += _Other[2][0]; Matrix[2][1] += _Other[2][1]; Matrix[2][2] += _Other[2][2]; Matrix[2][3] += _Other[2][3];
	Matrix[3][0] += _Other[3][0]; Matrix[3][1] += _Other[3][1]; Matrix[3][2] += _Other[3][2]; Matrix[3][3] += _Other[3][3];

	return *this;
}

const BFW::Math::Mat4d BFW::Math::Mat4d::operator+ (const double _Scale) const
{
	Mat4d _Matrix;

	_Matrix[0][0] = Matrix[0][0] + _Scale; _Matrix[0][1] = Matrix[0][1] + _Scale; _Matrix[0][2] = Matrix[0][2] + _Scale; _Matrix[0][3] = Matrix[0][3] + _Scale;
	_Matrix[1][0] = Matrix[1][0] + _Scale; _Matrix[1][1] = Matrix[1][1] + _Scale; _Matrix[1][2] = Matrix[1][2] + _Scale; _Matrix[1][3] = Matrix[1][3] + _Scale;
	_Matrix[2][0] = Matrix[2][0] + _Scale; _Matrix[2][1] = Matrix[2][1] + _Scale; _Matrix[2][2] = Matrix[2][2] + _Scale; _Matrix[2][3] = Matrix[2][3] + _Scale;
	_Matrix[3][0] = Matrix[3][0] + _Scale; _Matrix[3][1] = Matrix[3][1] + _Scale; _Matrix[3][2] = Matrix[3][2] + _Scale; _Matrix[3][3] = Matrix[3][3] + _Scale;

	return _Matrix;
}

const BFW::Math::Mat4d& BFW::Math::Mat4d::operator+= (const double _Scale)
{
	Matrix[0][0] += _Scale; Matrix[0][1] += _Scale; Matrix[0][2] += _Scale; Matrix[0][3] += _Scale;
	Matrix[1][0] += _Scale; Matrix[1][1] += _Scale; Matrix[1][2] += _Scale; Matrix[1][3] += _Scale;
	Matrix[2][0] += _Scale; Matrix[2][1] += _Scale; Matrix[2][2] += _Scale; Matrix[2][3] += _Scale;
	Matrix[3][0] += _Scale; Matrix[3][1] += _Scale; Matrix[3][2] += _Scale; Matrix[3][3] += _Scale;

	return *this;
}

const BFW::Math::Mat4d BFW::Math::Mat4d::operator- (const Mat4d& _Other) const
{
	Mat4d _Matrix;

	_Matrix[0][0] = Matrix[0][0] - _Other[0][0]; _Matrix[0][1] = Matrix[0][1] - _Other[0][1]; _Matrix[0][2] = Matrix[0][2] - _Other[0][2]; _Matrix[0][3] = Matrix[0][3] - _Other[0][3];
	_Matrix[1][0] = Matrix[1][0] - _Other[1][0]; _Matrix[1][1] = Matrix[1][1] - _Other[1][1]; _Matrix[1][2] = Matrix[1][2] - _Other[1][2]; _Matrix[1][3] = Matrix[1][3] - _Other[1][3];
	_Matrix[2][0] = Matrix[2][0] - _Other[2][0]; _Matrix[2][1] = Matrix[2][1] - _Other[2][1]; _Matrix[2][2] = Matrix[2][2] - _Other[2][2]; _Matrix[2][3] = Matrix[2][3] - _Other[2][3];
	_Matrix[3][0] = Matrix[3][0] - _Other[3][0]; _Matrix[3][1] = Matrix[3][1] - _Other[3][1]; _Matrix[3][2] = Matrix[3][2] - _Other[3][2]; _Matrix[3][3] = Matrix[3][3] - _Other[3][3];

	return _Matrix;
}

const BFW::Math::Mat4d& BFW::Math::Mat4d::operator-= (const Mat4d& _Other)
{
	Matrix[0][0] -= _Other[0][0]; Matrix[0][1] -= _Other[0][1]; Matrix[0][2] -= _Other[0][2]; Matrix[0][3] -= _Other[0][3];
	Matrix[1][0] -= _Other[1][0]; Matrix[1][1] -= _Other[1][1]; Matrix[1][2] -= _Other[1][2]; Matrix[1][3] -= _Other[1][3];
	Matrix[2][0] -= _Other[2][0]; Matrix[2][1] -= _Other[2][1]; Matrix[2][2] -= _Other[2][2]; Matrix[2][3] -= _Other[2][3];
	Matrix[3][0] -= _Other[3][0]; Matrix[3][1] -= _Other[3][1]; Matrix[3][2] -= _Other[3][2]; Matrix[3][3] -= _Other[3][3];

	return *this;
}

const BFW::Math::Mat4d BFW::Math::Mat4d::operator- (const double _Scale) const
{
	Mat4d _Matrix;

	_Matrix[0][0] = Matrix[0][0] - _Scale; _Matrix[0][1] = Matrix[0][1] - _Scale; _Matrix[0][2] = Matrix[0][2] - _Scale; _Matrix[0][3] = Matrix[0][3] - _Scale;
	_Matrix[1][0] = Matrix[1][0] - _Scale; _Matrix[1][1] = Matrix[1][1] - _Scale; _Matrix[1][2] = Matrix[1][2] - _Scale; _Matrix[1][3] = Matrix[1][3] - _Scale;
	_Matrix[2][0] = Matrix[2][0] - _Scale; _Matrix[2][1] = Matrix[2][1] - _Scale; _Matrix[2][2] = Matrix[2][2] - _Scale; _Matrix[2][3] = Matrix[2][3] - _Scale;
	_Matrix[3][0] = Matrix[3][0] - _Scale; _Matrix[3][1] = Matrix[3][1] - _Scale; _Matrix[3][2] = Matrix[3][2] - _Scale; _Matrix[3][3] = Matrix[3][3] - _Scale;

	return _Matrix;
}

const BFW::Math::Mat4d& BFW::Math::Mat4d::operator-= (const double _Scale)
{
	Matrix[0][0] -= _Scale; Matrix[0][1] -= _Scale; Matrix[0][2] -= _Scale; Matrix[0][3] -= _Scale;
	Matrix[1][0] -= _Scale; Matrix[1][1] -= _Scale; Matrix[1][2] -= _Scale; Matrix[1][3] -= _Scale;
	Matrix[2][0] -= _Scale; Matrix[2][1] -= _Scale; Matrix[2][2] -= _Scale; Matrix[2][3] -= _Scale;
	Matrix[3][0] -= _Scale; Matrix[3][1] -= _Scale; Matrix[3][2] -= _Scale; Matrix[3][3] -= _Scale;

	return *this;
}

const BFW::Math::Mat4d BFW::Math::Mat4d::operator* (const Mat4d& _Other) const
{
	Mat4d _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Other[0][0] + Matrix[0][1] * _Other[1][0] + Matrix[0][2] * _Other[2][0];
	_Matrix[0][1] = Matrix[0][0] * _Other[0][1] + Matrix[0][1] * _Other[1][1] + Matrix[0][2] * _Other[2][1];
	_Matrix[0][2] = Matrix[0][0] * _Other[0][2] + Matrix[0][1] * _Other[1][2] + Matrix[0][2] * _Other[2][2];
	_Matrix[0][2] = Matrix[0][0] * _Other[0][2] + Matrix[0][1] * _Other[1][2] + Matrix[0][2] * _Other[2][2];

	_Matrix[1][0] = Matrix[1][0] * _Other[0][0] + Matrix[1][1] * _Other[1][0] + Matrix[1][2] * _Other[2][0];
	_Matrix[1][1] = Matrix[1][0] * _Other[0][1] + Matrix[1][1] * _Other[1][1] + Matrix[1][2] * _Other[2][1];
	_Matrix[1][2] = Matrix[1][0] * _Other[0][2] + Matrix[1][1] * _Other[1][2] + Matrix[1][2] * _Other[2][2];
	_Matrix[1][2] = Matrix[1][0] * _Other[0][2] + Matrix[1][1] * _Other[1][2] + Matrix[1][2] * _Other[2][2];

	_Matrix[2][0] = Matrix[2][0] * _Other[0][0] + Matrix[2][1] * _Other[1][0] + Matrix[2][2] * _Other[2][0];
	_Matrix[2][1] = Matrix[2][0] * _Other[0][1] + Matrix[2][1] * _Other[1][1] + Matrix[2][2] * _Other[2][1];
	_Matrix[2][2] = Matrix[2][0] * _Other[0][2] + Matrix[2][1] * _Other[1][2] + Matrix[2][2] * _Other[2][2];
	_Matrix[2][2] = Matrix[2][0] * _Other[0][2] + Matrix[2][1] * _Other[1][2] + Matrix[2][2] * _Other[2][2];

	_Matrix[2][0] = Matrix[2][0] * _Other[0][0] + Matrix[2][1] * _Other[1][0] + Matrix[2][2] * _Other[2][0];
	_Matrix[2][1] = Matrix[2][0] * _Other[0][1] + Matrix[2][1] * _Other[1][1] + Matrix[2][2] * _Other[2][1];
	_Matrix[2][2] = Matrix[2][0] * _Other[0][2] + Matrix[2][1] * _Other[1][2] + Matrix[2][2] * _Other[2][2];
	_Matrix[2][2] = Matrix[2][0] * _Other[0][2] + Matrix[2][1] * _Other[1][2] + Matrix[2][2] * _Other[2][2];

	return _Matrix;
}

const BFW::Math::Mat4d& BFW::Math::Mat4d::operator*= (const Mat4d& _Other)
{
	Mat4d _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Other[0][0] + Matrix[0][1] * _Other[1][0] + Matrix[0][2] * _Other[2][0];
	_Matrix[0][1] = Matrix[0][0] * _Other[0][1] + Matrix[0][1] * _Other[1][1] + Matrix[0][2] * _Other[2][1];
	_Matrix[0][2] = Matrix[0][0] * _Other[0][2] + Matrix[0][1] * _Other[1][2] + Matrix[0][2] * _Other[2][2];
	_Matrix[0][2] = Matrix[0][0] * _Other[0][2] + Matrix[0][1] * _Other[1][2] + Matrix[0][2] * _Other[2][2];

	_Matrix[1][0] = Matrix[1][0] * _Other[0][0] + Matrix[1][1] * _Other[1][0] + Matrix[1][2] * _Other[2][0];
	_Matrix[1][1] = Matrix[1][0] * _Other[0][1] + Matrix[1][1] * _Other[1][1] + Matrix[1][2] * _Other[2][1];
	_Matrix[1][2] = Matrix[1][0] * _Other[0][2] + Matrix[1][1] * _Other[1][2] + Matrix[1][2] * _Other[2][2];
	_Matrix[1][2] = Matrix[1][0] * _Other[0][2] + Matrix[1][1] * _Other[1][2] + Matrix[1][2] * _Other[2][2];

	_Matrix[2][0] = Matrix[2][0] * _Other[0][0] + Matrix[2][1] * _Other[1][0] + Matrix[2][2] * _Other[2][0];
	_Matrix[2][1] = Matrix[2][0] * _Other[0][1] + Matrix[2][1] * _Other[1][1] + Matrix[2][2] * _Other[2][1];
	_Matrix[2][2] = Matrix[2][0] * _Other[0][2] + Matrix[2][1] * _Other[1][2] + Matrix[2][2] * _Other[2][2];
	_Matrix[2][2] = Matrix[2][0] * _Other[0][2] + Matrix[2][1] * _Other[1][2] + Matrix[2][2] * _Other[2][2];

	_Matrix[2][0] = Matrix[2][0] * _Other[0][0] + Matrix[2][1] * _Other[1][0] + Matrix[2][2] * _Other[2][0];
	_Matrix[2][1] = Matrix[2][0] * _Other[0][1] + Matrix[2][1] * _Other[1][1] + Matrix[2][2] * _Other[2][1];
	_Matrix[2][2] = Matrix[2][0] * _Other[0][2] + Matrix[2][1] * _Other[1][2] + Matrix[2][2] * _Other[2][2];
	_Matrix[2][2] = Matrix[2][0] * _Other[0][2] + Matrix[2][1] * _Other[1][2] + Matrix[2][2] * _Other[2][2];

	*this = _Matrix;

	return *this;
}

const BFW::Math::Mat4d BFW::Math::Mat4d::operator* (const double _Scale) const
{
	Mat4d _Matrix;

	_Matrix[0][0] = Matrix[0][0] * _Scale; _Matrix[0][1] = Matrix[0][1] * _Scale; _Matrix[0][2] = Matrix[0][2] * _Scale; _Matrix[0][3] = Matrix[0][3] * _Scale;
	_Matrix[1][0] = Matrix[1][0] * _Scale; _Matrix[1][1] = Matrix[1][1] * _Scale; _Matrix[1][2] = Matrix[1][2] * _Scale; _Matrix[1][3] = Matrix[1][3] * _Scale;
	_Matrix[2][0] = Matrix[2][0] * _Scale; _Matrix[2][1] = Matrix[2][1] * _Scale; _Matrix[2][2] = Matrix[2][2] * _Scale; _Matrix[2][3] = Matrix[2][3] * _Scale;
	_Matrix[3][0] = Matrix[3][0] * _Scale; _Matrix[3][1] = Matrix[3][1] * _Scale; _Matrix[3][2] = Matrix[3][2] * _Scale; _Matrix[3][3] = Matrix[3][3] * _Scale;

	return _Matrix;
}

const BFW::Math::Mat4d& BFW::Math::Mat4d::operator*= (const double _Scale)
{
	Matrix[0][0] *= _Scale; Matrix[0][1] *= _Scale; Matrix[0][2] *= _Scale; Matrix[0][3] *= _Scale;
	Matrix[1][0] *= _Scale; Matrix[1][1] *= _Scale; Matrix[1][2] *= _Scale; Matrix[1][3] *= _Scale;
	Matrix[2][0] *= _Scale; Matrix[2][1] *= _Scale; Matrix[2][2] *= _Scale; Matrix[2][3] *= _Scale;
	Matrix[3][0] *= _Scale; Matrix[3][1] *= _Scale; Matrix[3][2] *= _Scale; Matrix[3][3] *= _Scale;

	return *this;
}

const BFW::Math::Mat4d BFW::Math::Mat4d::operator/ (const double _Scale) const
{
	Mat4d _Matrix;

	_Matrix[0][0] = Matrix[0][0] / _Scale; _Matrix[0][1] = Matrix[0][1] / _Scale; _Matrix[0][2] = Matrix[0][2] / _Scale; _Matrix[0][3] = Matrix[0][3] / _Scale;
	_Matrix[1][0] = Matrix[1][0] / _Scale; _Matrix[1][1] = Matrix[1][1] / _Scale; _Matrix[1][2] = Matrix[1][2] / _Scale; _Matrix[1][3] = Matrix[1][3] / _Scale;
	_Matrix[2][0] = Matrix[2][0] / _Scale; _Matrix[2][1] = Matrix[2][1] / _Scale; _Matrix[2][2] = Matrix[2][2] / _Scale; _Matrix[2][3] = Matrix[2][3] / _Scale;
	_Matrix[3][0] = Matrix[3][0] / _Scale; _Matrix[3][1] = Matrix[3][1] / _Scale; _Matrix[3][2] = Matrix[3][2] / _Scale; _Matrix[3][3] = Matrix[3][3] / _Scale;

	return _Matrix;
}

const BFW::Math::Mat4d& BFW::Math::Mat4d::operator/= (const double _Scale)
{
	Matrix[0][0] /= _Scale; Matrix[0][1] /= _Scale; Matrix[0][2] /= _Scale; Matrix[0][3] /= _Scale;
	Matrix[1][0] /= _Scale; Matrix[1][1] /= _Scale; Matrix[1][2] /= _Scale; Matrix[1][3] /= _Scale;
	Matrix[2][0] /= _Scale; Matrix[2][1] /= _Scale; Matrix[2][2] /= _Scale; Matrix[2][3] /= _Scale;
	Matrix[3][0] /= _Scale; Matrix[3][1] /= _Scale; Matrix[3][2] /= _Scale; Matrix[3][3] /= _Scale;

	return *this;
}

const bool BFW::Math::Mat4d::operator== (const Mat4d& _Other) const
{
	return
		Matrix[0][0] == _Other[0][0] && Matrix[0][1] == _Other[0][1] && Matrix[0][2] == _Other[0][2] && Matrix[0][3] == _Other[0][3] &&
		Matrix[1][0] == _Other[1][0] && Matrix[1][1] == _Other[1][1] && Matrix[1][2] == _Other[1][2] && Matrix[1][3] == _Other[1][3] &&
		Matrix[2][0] == _Other[2][0] && Matrix[2][1] == _Other[2][1] && Matrix[2][2] == _Other[2][2] && Matrix[2][3] == _Other[2][3] &&
		Matrix[3][0] == _Other[3][0] && Matrix[3][1] == _Other[3][1] && Matrix[3][2] == _Other[3][2] && Matrix[3][3] == _Other[3][3];
}

const bool BFW::Math::Mat4d::operator!= (const Mat4d& _Other) const
{
	return
		Matrix[0][0] != _Other[0][0] || Matrix[0][1] != _Other[0][1] || Matrix[0][2] != _Other[0][2] || Matrix[0][3] != _Other[0][3] ||
		Matrix[1][0] != _Other[1][0] || Matrix[1][1] != _Other[1][1] || Matrix[1][2] != _Other[1][2] || Matrix[1][3] != _Other[1][3] ||
		Matrix[2][0] != _Other[2][0] || Matrix[2][1] != _Other[2][1] || Matrix[2][2] != _Other[2][2] || Matrix[2][3] != _Other[2][3] ||
		Matrix[3][0] != _Other[3][0] || Matrix[3][1] != _Other[3][1] || Matrix[3][2] != _Other[3][2] || Matrix[3][3] != _Other[3][3];
}

const bool BFW::Math::Mat4d::operator> (const Mat4d& _Other) const
{
	return Determinant() > _Other.Determinant();
}

const bool BFW::Math::Mat4d::operator>= (const Mat4d& _Other) const
{
	return Determinant() >= _Other.Determinant();
}

const bool BFW::Math::Mat4d::operator< (const Mat4d& _Other) const
{
	return Determinant() < _Other.Determinant();
}

const bool BFW::Math::Mat4d::operator<= (const Mat4d& _Other) const
{
	return Determinant() <= _Other.Determinant();
}

double* BFW::Math::Mat4d::operator[] (const unsigned long _Index)
{
	return Matrix[_Index].Data();
}

const double* BFW::Math::Mat4d::operator[] (const unsigned long _Index) const
{
	return Matrix[_Index].Data();
}

const BFW::Math::Mat4d& BFW::Math::Mat4d::operator= (const Mat4d& _Other)
{
	Matrix[0][0] = _Other.Matrix[0][0]; Matrix[0][1] = _Other.Matrix[0][1]; Matrix[0][2] = _Other.Matrix[0][2]; Matrix[0][3] = _Other.Matrix[0][3];
	Matrix[1][0] = _Other.Matrix[1][0]; Matrix[1][1] = _Other.Matrix[1][1]; Matrix[1][2] = _Other.Matrix[1][2]; Matrix[1][3] = _Other.Matrix[1][3];
	Matrix[2][0] = _Other.Matrix[2][0]; Matrix[2][1] = _Other.Matrix[2][1]; Matrix[2][2] = _Other.Matrix[2][2]; Matrix[2][3] = _Other.Matrix[2][3];
	Matrix[3][0] = _Other.Matrix[3][0]; Matrix[3][1] = _Other.Matrix[3][1]; Matrix[3][2] = _Other.Matrix[3][2]; Matrix[3][3] = _Other.Matrix[3][3];

	return *this;
}

const BFW::Math::Mat4d& BFW::Math::Mat4d::operator= (Mat4d&& _Other) noexcept
{
	Matrix[0][0] = _Other.Matrix[0][0]; Matrix[0][1] = _Other.Matrix[0][1]; Matrix[0][2] = _Other.Matrix[0][2]; Matrix[0][3] = _Other.Matrix[0][3];
	Matrix[1][0] = _Other.Matrix[1][0]; Matrix[1][1] = _Other.Matrix[1][1]; Matrix[1][2] = _Other.Matrix[1][2]; Matrix[1][3] = _Other.Matrix[1][3];
	Matrix[2][0] = _Other.Matrix[2][0]; Matrix[2][1] = _Other.Matrix[2][1]; Matrix[2][2] = _Other.Matrix[2][2]; Matrix[2][3] = _Other.Matrix[2][3];
	Matrix[3][0] = _Other.Matrix[3][0]; Matrix[3][1] = _Other.Matrix[3][1]; Matrix[3][2] = _Other.Matrix[3][2]; Matrix[3][3] = _Other.Matrix[3][3];

	_Other.Matrix[0][0] = 1.0; _Other.Matrix[0][1] = 0.0; _Other.Matrix[0][2] = 0.0; _Other.Matrix[0][3] = 0.0;
	_Other.Matrix[1][0] = 0.0; _Other.Matrix[1][1] = 1.0; _Other.Matrix[1][2] = 0.0; _Other.Matrix[1][3] = 0.0;
	_Other.Matrix[2][0] = 0.0; _Other.Matrix[2][1] = 0.0; _Other.Matrix[2][2] = 1.0; _Other.Matrix[2][3] = 0.0;
	_Other.Matrix[3][0] = 0.0; _Other.Matrix[3][1] = 0.0; _Other.Matrix[3][2] = 0.0; _Other.Matrix[3][3] = 1.0;

	return *this;
}
