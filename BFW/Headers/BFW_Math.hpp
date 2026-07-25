#ifndef BFW_Math_hpp

#define BFW_Math_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace Math
	{

		class BFW_API Vec2
		{

		public:

			float x, y;

			Vec2();
			Vec2(const float _x, const float _y);
			Vec2(const Vec2& _Other);
			Vec2(Vec2&& _Other) noexcept;
			~Vec2();

			float* Data();
			const float* Data() const;

			const float Magnitude() const;

			Vec2& Normalize();
			const Vec2 Normalized() const;

			const Vec2& operator+ () const;
			const Vec2 operator- () const;

			const Vec2 operator+ (const Vec2& _Other) const;
			Vec2& operator+= (const Vec2& _Other);
			const Vec2 operator+ (const float _Value) const;
			Vec2& operator+= (const float _Value);

			const Vec2 operator- (const Vec2& _Other) const;
			Vec2& operator-= (const Vec2& _Other);
			const Vec2 operator- (const float _Value) const;
			Vec2& operator-= (const float _Value);

			const Vec2 operator* (const Vec2& _Other) const;
			Vec2& operator*= (const Vec2& _Other);
			const Vec2 operator* (const float _Value) const;
			Vec2& operator*= (const float _Value);

			const Vec2 operator/ (const Vec2& _Other) const;
			Vec2& operator/= (const Vec2& _Other);
			const Vec2 operator/ (const float _Value) const;
			Vec2& operator/= (const float _Value);

			const bool operator== (const Vec2& _Other) const;
			const bool operator!= (const Vec2& _Other) const;

			float& operator[] (const size_t _Index);
			const float& operator[] (const size_t _Index) const;

			Vec2& operator= (const Vec2& _Other);
			Vec2& operator= (Vec2&& _Other) noexcept;

			static const float Distance(const Vec2& _AVec, const Vec2& _BVec);
			static const float Angle(const Vec2& _AVec, const Vec2& _BVec);
			static const float Dot(const Vec2& _AVec, const Vec2& _BVec);
			static const Vec2 Mix(const Vec2& _AVec, const Vec2& _BVec, const float _Percentage);
			static const Vec2 Clamp(const Vec2& _Value, const Vec2& _Min, const Vec2& _Max);
			static const Vec2 Min(const Vec2& _AVec, const Vec2& _BVec);
			static const Vec2 Max(const Vec2& _AVec, const Vec2& _BVec);
			static const Vec2 Pow(const Vec2& _Base, const Vec2& _Power);
			static const Vec2 Exp(const Vec2& _Power);
			static const Vec2 Reflect(const Vec2& _Vec, const Vec2& _Normal);

		};

		class BFW_API Vec3
		{

		public:

			float x, y, z;

			Vec3();
			Vec3(const float _x, const float _y, const float _z);
			Vec3(const Vec3& _Other);
			Vec3(Vec3&& _Other) noexcept;
			Vec3(const Vec2& _Other, const float _z);
			~Vec3();

			operator const Vec2 () const;

			float* Data();
			const float* Data() const;

			const float Magnitude() const;

			Vec3& Normalize();
			const Vec3 Normalized() const;

			const Vec3& operator+ () const;
			const Vec3 operator- () const;

			const Vec3 operator+ (const Vec3& _Other) const;
			Vec3& operator+= (const Vec3& _Other);
			const Vec3 operator+ (const float _Value) const;
			Vec3& operator+= (const float _Value);

			const Vec3 operator- (const Vec3& _Other) const;
			Vec3& operator-= (const Vec3& _Other);
			const Vec3 operator- (const float _Value) const;
			Vec3& operator-= (const float _Value);

			const Vec3 operator* (const Vec3& _Other) const;
			Vec3& operator*= (const Vec3& _Other);
			const Vec3 operator* (const float _Value) const;
			Vec3& operator*= (const float _Value);

			const Vec3 operator/ (const Vec3& _Other) const;
			Vec3& operator/= (const Vec3& _Other);
			const Vec3 operator/ (const float _Value) const;
			Vec3& operator/= (const float _Value);

			const bool operator== (const Vec3& _Other) const;
			const bool operator!= (const Vec3& _Other) const;

			float& operator[] (const size_t _Index);
			const float& operator[] (const size_t _Index) const;

			Vec3& operator= (const Vec3& _Other);
			Vec3& operator= (Vec3&& _Other) noexcept;

			static const float Distance(const Vec3& _AVec, const Vec3& _BVec);
			static const float Angle(const Vec3& _AVec, const Vec3& _BVec);
			static const float Dot(const Vec3& _AVec, const Vec3& _BVec);
			static const Vec3 Cross(const Vec3& _AVec, const Vec3& _BVec);
			static const Vec3 Mix(const Vec3& _AVec, const Vec3& _BVec, const float _Percentage);
			static const Vec3 Clamp(const Vec3& _Value, const Vec3& _Min, const Vec3& _Max);
			static const Vec3 Min(const Vec3& _AVec, const Vec3& _BVec);
			static const Vec3 Max(const Vec3& _AVec, const Vec3& _BVec);
			static const Vec3 Pow(const Vec3& _Base, const Vec3& _Power);
			static const Vec3 Exp(const Vec3& _Power);
			static const Vec3 Reflect(const Vec3& _Vec, const Vec3& _Normal);

		};

		class BFW_API Vec4
		{

		public:

			float x, y, z, w;

			Vec4();
			Vec4(const float _x, const float _y, const float _z, const float _w);
			Vec4(const Vec4& _Other);
			Vec4(Vec4&& _Other) noexcept;
			Vec4(const Vec2& _Other, const float _z, const float _w);
			Vec4(const Vec3& _Other, const float _w);
			~Vec4();

			operator const Vec2 () const;
			operator const Vec3 () const;

			float* Data();
			const float* Data() const;

			const float Magnitude() const;

			Vec4& Normalize();
			const Vec4 Normalized() const;

			const Vec4& operator+ () const;
			const Vec4 operator- () const;

			const Vec4 operator+ (const Vec4& _Other) const;
			Vec4& operator+= (const Vec4& _Other);
			const Vec4 operator+ (const float _Value) const;
			Vec4& operator+= (const float _Value);

			const Vec4 operator- (const Vec4& _Other) const;
			Vec4& operator-= (const Vec4& _Other);
			const Vec4 operator- (const float _Value) const;
			Vec4& operator-= (const float _Value);

			const Vec4 operator* (const Vec4& _Other) const;
			Vec4& operator*= (const Vec4& _Other);
			const Vec4 operator* (const float _Value) const;
			Vec4& operator*= (const float _Value);

			const Vec4 operator/ (const Vec4& _Other) const;
			Vec4& operator/= (const Vec4& _Other);
			const Vec4 operator/ (const float _Value) const;
			Vec4& operator/= (const float _Value);

			const bool operator== (const Vec4& _Other) const;
			const bool operator!= (const Vec4& _Other) const;

			float& operator[] (const size_t _Index);
			const float& operator[] (const size_t _Index) const;

			Vec4& operator= (const Vec4& _Other);
			Vec4& operator= (Vec4&& _Other) noexcept;

			static const float Distance(const Vec4& _AVec, const Vec4& _BVec);
			static const float Angle(const Vec4& _AVec, const Vec4& _BVec);
			static const float Dot(const Vec4& _AVec, const Vec4& _BVec);
			static const Vec4 Cross(const Vec4& _AVec, const Vec4& _BVec);
			static const Vec4 Mix(const Vec4& _AVec, const Vec4& _BVec, const float _Percentage);
			static const Vec4 Clamp(const Vec4& _Value, const Vec4& _Min, const Vec4& _Max);
			static const Vec4 Min(const Vec4& _AVec, const Vec4& _BVec);
			static const Vec4 Max(const Vec4& _AVec, const Vec4& _BVec);
			static const Vec4 Pow(const Vec4& _Base, const Vec4& _Power);
			static const Vec4 Exp(const Vec4& _Power);
			static const Vec4 Reflect(const Vec4& _Vec, const Vec4& _Normal);

		};

		class BFW_API Mat2
		{

		public:

			Mat2();
			Mat2(const Mat2& _Other);
			Mat2(Mat2&& _Other) noexcept;
			Mat2(const Vec2& _Ox, const Vec2& _Oy);
			~Mat2();

			float* Data();
			const float* Data() const;

			const float Determinant() const;
			const float Trace() const;

			Mat2& Transpose();
			const Mat2 Transposed() const;

			Mat2& Inverse();
			const Mat2 Inversed() const;

			const Mat2& operator+ () const;
			const Mat2 operator- () const;

			const Vec2 operator* (const Vec2& _Vec) const;

			const Mat2 operator+ (const Mat2& _Other) const;
			Mat2& operator+= (const Mat2& _Other);
			const Mat2 operator+ (const float _Value) const;
			Mat2& operator+= (const float _Value);

			const Mat2 operator- (const Mat2& _Other) const;
			Mat2& operator-= (const Mat2& _Other);
			const Mat2 operator- (const float _Value) const;
			Mat2& operator-= (const float _Value);

			const Mat2 operator* (const Mat2& _Other) const;
			Mat2& operator*= (const Mat2& _Other);
			const Mat2 operator* (const float _Value) const;
			Mat2& operator*= (const float _Value);

			const Mat2 operator/ (const float _Value) const;
			Mat2& operator/= (const float _Value);

			const bool operator== (const Mat2& _Other) const;
			const bool operator!= (const Mat2& _Other) const;

			float* operator[] (const size_t _Index);
			const float* operator[] (const size_t _Index) const;

			Mat2& operator= (const Mat2& _Other);
			Mat2& operator= (Mat2&& _Other) noexcept;

			static const Mat2 GetFill(const float _Value);
			static const Mat2 GetRotation(const float _Angle);
			static const Mat2 GetScale(const Vec2& _Size);
			static const Mat2 GetShear(const float _Value, const size_t _ShearedAxis, const size_t _ShearByAxis);
			static const Mat2 GetFlip(const Vec2& _Normal);

		private:

			Vec2 Matrix[2];

		};

		class BFW_API Mat3
		{

		public:

			Mat3();
			Mat3(const Mat3& _Other);
			Mat3(Mat3&& _Other) noexcept;
			Mat3(const Vec3& _Ox, const Vec3& _Oy, const Vec3& _Oz);
			Mat3(const Mat2& _Other);
			~Mat3();

			operator const Mat2 () const;

			float* Data();
			const float* Data() const;

			const float Determinant() const;
			const float Trace() const;

			Mat3& Transpose();
			const Mat3 Transposed() const;

			Mat3& Inverse();
			const Mat3 Inversed() const;

			const Mat3& operator+ () const;
			const Mat3 operator- () const;

			const Vec3 operator* (const Vec3& _Vec) const;

			const Mat3 operator+ (const Mat3& _Other) const;
			Mat3& operator+= (const Mat3& _Other);
			const Mat3 operator+ (const float _Value) const;
			Mat3& operator+= (const float _Value);

			const Mat3 operator- (const Mat3& _Other) const;
			Mat3& operator-= (const Mat3& _Other);
			const Mat3 operator- (const float _Value) const;
			Mat3& operator-= (const float _Value);

			const Mat3 operator* (const Mat3& _Other) const;
			Mat3& operator*= (const Mat3& _Other);
			const Mat3 operator* (const float _Value) const;
			Mat3& operator*= (const float _Value);

			const Mat3 operator/ (const float _Value) const;
			Mat3& operator/= (const float _Value);

			const bool operator== (const Mat3& _Other) const;
			const bool operator!= (const Mat3& _Other) const;

			float* operator[] (const size_t _Index);
			const float* operator[] (const size_t _Index) const;

			Mat3& operator= (const Mat3& _Other);
			Mat3& operator= (Mat3&& _Other) noexcept;

			static const Mat3 GetFill(const float _Value);
			static const Mat3 GetTranslation(const Vec2& _Position);
			static const Mat3 GetRotation(const float _Angle, const Vec3& _Axis);
			static const Mat3 GetScale(const Vec3& _Size);
			static const Mat3 GetShear(const float _Value, const size_t _ShearedAxis, const size_t _ShearByAxis);
			static const Mat3 GetFlip(const Vec3& _Normal);
			static const Mat3 GetOrtho(const float _Left, const float _Right, const float _Bottom, const float _Top);

		private:

			Vec3 Matrix[3];

		};

		class BFW_API Mat4
		{

		public:

			Mat4();
			Mat4(const Mat4& _Other);
			Mat4(Mat4&& _Other) noexcept;
			Mat4(const Vec3& _Ox, const Vec3& _Oy, const Vec3& _Oz);
			Mat4(const Mat2& _Other);
			Mat4(const Mat3& _Other);
			~Mat4();

			operator const Mat2 () const;
			operator const Mat3 () const;

			float* Data();
			const float* Data() const;

			const float Determinant() const;
			const float Trace() const;

			Mat4& Transpose();
			const Mat4 Transposed() const;

			Mat4& Inverse();
			const Mat4 Inversed() const;

			const Mat4& operator+ () const;
			const Mat4 operator- () const;

			const Vec4 operator* (const Vec4& _Vec) const;

			const Mat4 operator+ (const Mat4& _Other) const;
			Mat4& operator+= (const Mat4& _Other);
			const Mat4 operator+ (const float _Value) const;
			Mat4& operator+= (const float _Value);

			const Mat4 operator- (const Mat4& _Other) const;
			Mat4& operator-= (const Mat4& _Other);
			const Mat4 operator- (const float _Value) const;
			Mat4& operator-= (const float _Value);

			const Mat4 operator* (const Mat4& _Other) const;
			Mat4& operator*= (const Mat4& _Other);
			const Mat4 operator* (const float _Value) const;
			Mat4& operator*= (const float _Value);

			const Mat4 operator/ (const float _Value) const;
			Mat4& operator/= (const float _Value);

			const bool operator== (const Mat4& _Other) const;
			const bool operator!= (const Mat4& _Other) const;

			float* operator[] (const size_t _Index);
			const float* operator[] (const size_t _Index) const;

			Mat4& operator= (const Mat4& _Other);
			Mat4& operator= (Mat4&& _Other) noexcept;

			static const Mat4 GetFill(const float _Value);
			static const Mat4 GetTranslation(const Vec3& _Position);
			static const Mat4 GetRotation(const float _Angle, const Vec3& _Axis);
			static const Mat4 GetScale(const Vec3& _Size);
			static const Mat4 GetShear(const float _Value, const size_t _ShearedAxis, const size_t _ShearByAxis);
			static const Mat4 GetFlip(const Vec3& _Normal);
			static const Mat4 GetOrthoLeftHand(const float _Left, const float _Right, const float _Bottom, const float _Top, const float _ZNear, const float _ZFar);
			static const Mat4 GetOrthoRightHand(const float _Left, const float _Right, const float _Bottom, const float _Top, const float _ZNear, const float _ZFar);
			static const Mat4 GetPerspectiveOxLeftHand(const float _Fov, const float _AspectRatio, const float _ZNear, const float _ZFar);
			static const Mat4 GetPerspectiveOyLeftHand(const float _Fov, const float _AspectRatio, const float _ZNear, const float _ZFar);
			static const Mat4 GetPerspectiveOxRightHand(const float _Fov, const float _AspectRatio, const float _ZNear, const float _ZFar);
			static const Mat4 GetPerspectiveOyRightHand(const float _Fov, const float _AspectRatio, const float _ZNear, const float _ZFar);

		private:

			Vec4 Matrix[4];

		};

		class BFW_API Quat
		{

		public:

			float r, i, j, k;

			Quat();
			Quat(const float _r, const float _i, const float _j, const float _k);
			Quat(const float _Angle, const Vec3& _Axis);
			Quat(const Quat& _Other);
			Quat(Quat&& _Other) noexcept;
			~Quat();

			float* Data();
			const float* Data() const;

			const float Magnitude() const;

			Quat& Normalize();
			const Quat Normalized() const;

			Quat& Conjugate();
			const Quat Conjugated() const;

			Quat& Inverse();
			const Quat Inversed() const;

			const Mat4 GetMatrix() const;

			const Quat& operator+ () const;
			const Quat operator- () const;

			const Vec3 operator* (const Vec3& _Vec) const;

			const Quat operator+ (const Quat& _Other) const;
			Quat& operator+= (const Quat& _Other);
			const Quat operator+ (const float _Value) const;
			Quat& operator+= (const float _Value);

			const Quat operator- (const Quat& _Other) const;
			Quat& operator-= (const Quat& _Other);
			const Quat operator- (const float _Value) const;
			Quat& operator-= (const float _Value);

			const Quat operator* (const Quat& _Other) const;
			Quat& operator*= (const Quat& _Other);
			const Quat operator* (const float _Value) const;
			Quat& operator*= (const float _Value);

			const Quat operator/ (const float _Value) const;
			Quat& operator/= (const float _Value);

			const bool operator== (const Quat& _Other) const;
			const bool operator!= (const Quat& _Other) const;

			float& operator[] (const size_t _Index);
			const float& operator[] (const size_t _Index) const;

			Quat& operator= (const Quat& _Other);
			Quat& operator= (Quat&& _Other) noexcept;

			static const Quat Mix(const Quat& _AQuat, const Quat& _BQuat, const float _Percentage);
			static const Quat Pow(const Quat& _Base, const float _Power);

		};

		extern const float BFW_API Pi;
		extern const float BFW_API DegreesToRadians;
		extern const float BFW_API RadiansToDegrees;

		const float BFW_API Mix(const float& _AVal, const float& _BVal, const float _Percentage);
		const float BFW_API Clamp(const float& _Value, const float& _Min, const float& _Max);
		const float BFW_API Min(const float& _AVal, const float& _BVal);
		const float BFW_API Max(const float& _AVal, const float& _BVal);

	}

}



#endif
