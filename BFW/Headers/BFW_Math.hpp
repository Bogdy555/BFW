#ifndef BFW_Math_hpp

#define BFW_Math_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace Math
	{

#ifdef BFW_WINDOWS_PLATFORM

		class BFW_API RandomLong
		{

		public:

			RandomLong(const long _Min = 0, const long _Max = 1000000, const unsigned long _Seed = 0);
			RandomLong(const RandomLong& _Other);
			RandomLong(RandomLong&& _Other) noexcept;
			~RandomLong();

			void SetSeed(const long _Min, const long _Max, const unsigned long _Seed);
			void GetSeed(long* _Min = nullptr, long* _Max = nullptr, unsigned long* _Seed = nullptr) const;

			const unsigned long long GetCount() const;

			long operator() ();

			void operator= (const RandomLong& _Other);
			void operator= (RandomLong&& _Other) noexcept;

		private:

			long Min, Max;
			unsigned long Seed;
			unsigned long long Count;

			std::mt19937 Generator;
			std::uniform_int_distribution<long> Distribution;

		};

		class BFW_API RandomLongLong
		{

		public:

			RandomLongLong(const long long _Min = 0, const long long _Max = 1000000, const unsigned long _Seed = 0);
			RandomLongLong(const RandomLongLong& _Other);
			RandomLongLong(RandomLongLong&& _Other) noexcept;
			~RandomLongLong();

			void SetSeed(const long long _Min, const long long _Max, const unsigned long _Seed);
			void GetSeed(long long* _Min = nullptr, long long* _Max = nullptr, unsigned long* _Seed = nullptr) const;

			const unsigned long long GetCount() const;

			long long operator() ();

			void operator= (const RandomLongLong& _Other);
			void operator= (RandomLongLong&& _Other) noexcept;

		private:

			long long Min, Max;
			unsigned long Seed;
			unsigned long long Count;

			std::mt19937_64 Generator;
			std::uniform_int_distribution<long long> Distribution;

		};

		class BFW_API RandomFloat
		{

		public:

			RandomFloat(const float _Min = 0.0f, const float _Max = 1.0f, const unsigned long _Seed = 0);
			RandomFloat(const RandomFloat& _Other);
			RandomFloat(RandomFloat&& _Other) noexcept;
			~RandomFloat();

			void SetSeed(const float _Min, const float _Max, const unsigned long _Seed);
			void GetSeed(float* _Min = nullptr, float* _Max = nullptr, unsigned long* _Seed = nullptr) const;

			const unsigned long long GetCount() const;

			float operator() ();

			void operator= (const RandomFloat& _Other);
			void operator= (RandomFloat&& _Other) noexcept;

		private:

			float Min, Max;
			unsigned long Seed;
			unsigned long long Count;

			std::mt19937 Generator;
			std::uniform_real_distribution<float> Distribution;

		};

		class BFW_API RandomDouble
		{

		public:

			RandomDouble(const double _Min = 0.0, const double _Max = 1.0, const unsigned long _Seed = 0);
			RandomDouble(const RandomDouble& _Other);
			RandomDouble(RandomDouble&& _Other) noexcept;
			~RandomDouble();

			void SetSeed(const double _Min, const double _Max, const unsigned long _Seed);
			void GetSeed(double* _Min = nullptr, double* _Max = nullptr, unsigned long* _Seed = nullptr) const;

			const unsigned long long GetCount() const;

			double operator() ();

			void operator= (const RandomDouble& _Other);
			void operator= (RandomDouble&& _Other) noexcept;

		private:

			double Min, Max;
			unsigned long Seed;
			unsigned long long Count;

			std::mt19937_64 Generator;
			std::uniform_real_distribution<double> Distribution;

		};

		class BFW_API NoiseFloat
		{

		public:

			NoiseFloat(const long _MinL, const long _MaxL, const unsigned long _SeedL, const float _MinF, const float _MaxF, const unsigned long _SeedF);
			NoiseFloat(const NoiseFloat& _Other);
			NoiseFloat(NoiseFloat&& _Other) noexcept;
			~NoiseFloat();

			void SetSeed(const long _MinL, const long _MaxL, const unsigned long _SeedL, const float _MinF, const float _MaxF, const unsigned long _SeedF);
			void GetSeed(long* _MinL = nullptr, long* _MaxL = nullptr, unsigned long* _SeedL = nullptr, float* _MinF = nullptr, float* _MaxF = nullptr, unsigned long* _SeedF = nullptr) const;

			const unsigned long long GetCount() const;

			float operator() (const float _Value);

			void operator= (const NoiseFloat& _Other);
			void operator= (NoiseFloat&& _Other) noexcept;

		private:

			RandomLong RngLong;
			RandomFloat RngFloat;

		};

		class BFW_API NoiseDouble
		{

		public:

			NoiseDouble(const long long _MinLL, const long long _MaxLL, const unsigned long _SeedLL, const double _MinD, const double _MaxD, const unsigned long _SeedD);
			NoiseDouble(const NoiseDouble& _Other);
			NoiseDouble(NoiseDouble&& _Other) noexcept;
			~NoiseDouble();

			void SetSeed(const long long _MinLL, const long long _MaxLL, const unsigned long _SeedLL, const double _MinD, const double _MaxD, const unsigned long _SeedD);
			void GetSeed(long long* _MinLL = nullptr, long long* _MaxLL = nullptr, unsigned long* _SeedLL = nullptr, double* _MinD = nullptr, double* _MaxD = nullptr, unsigned long* _SeedD = nullptr) const;

			const unsigned long long GetCount() const;

			double operator() (const double _Value);

			void operator= (const NoiseDouble& _Other);
			void operator= (NoiseDouble&& _Other) noexcept;

		private:

			RandomLongLong RngLongLong;
			RandomDouble RngDouble;

		};

		class BFW_API Crypt
		{

		public:

			Crypt();
			Crypt(const Crypt& _Other) = delete;
			Crypt(Crypt&& _Other) noexcept;
			~Crypt();

			bool Create(const wchar_t* _Name);
			void Destroy();

			bool Get(unsigned char* _Buff, const unsigned long _Size);

			const bool CheckCreated() const;
			const wchar_t* GetName() const;

			void operator= (const Crypt& _Other) = delete;
			void operator= (Crypt&& _Other) noexcept;

		private:

			HCRYPTPROV hCrypt;
			bool Created;
			const wchar_t* Name;

		};

#endif

#ifdef BFW_ARDUINO_PLATFORM

		void BFW_API SetRandomSeed(const unsigned long _Seed);

		long BFW_API lRandom(const long _Min = 0, const long _Max = 1000000);
		long long BFW_API llRandom(const long long _Min = 0, const long long _Max = 1000000);
		float BFW_API fRandom(const float _Min = 0.0f, const float _Max = 1.0f);
		double BFW_API dRandom(const double _Min = 0.0, const double _Max = 1.0);

		float BFW_API fNoise(const float _Value, const float _Min = 0.0f, const float _Max = 1.0f);
		double BFW_API dNoise(const double _Value, const double _Min = 0.0, const double _Max = 1.0);

#endif

		class BFW_API Vec2f
		{

		public:

			float x, y;

			Vec2f(const float _x = 0.0f, const float _y = 0.0f);
			Vec2f(const Vec2f& _Other);
			Vec2f(Vec2f&& _Other) noexcept;
			~Vec2f();

			float* Data();
			const float* Data() const;

			const float Magnitude() const;
			const float DotProduct(const Vec2f& _Other) const;

			const float GetAngle(const Vec2f& _Center = Vec2f(0.0f, 0.0f), const Vec2f& _Other = Vec2f(1.0f, 0.0f)) const;

			const Vec2f Rotated(const float _Angle, const Vec2f& _Center = Vec2f(0.0f, 0.0f)) const;
			const Vec2f& Rotate(const float _Angle, const Vec2f& _Center = Vec2f(0.0f, 0.0f));

			const Vec2f Flipped(const Vec2f& _U = Vec2f(0.0f, 1.0f), const Vec2f& _Center = Vec2f(0.0f, 0.0f)) const;
			const Vec2f& Flip(const Vec2f& _U = Vec2f(0.0f, 1.0f), const Vec2f& _Center = Vec2f(0.0f, 0.0f));

			const Vec2f& operator+ () const;
			const Vec2f operator- () const;

			const Vec2f operator+ (const Vec2f& _Other) const;
			const Vec2f& operator+= (const Vec2f& _Other);
			const Vec2f operator+ (const float _Scale) const;
			const Vec2f& operator+= (const float _Scale);

			const Vec2f operator- (const Vec2f& _Other) const;
			const Vec2f& operator-= (const Vec2f& _Other);
			const Vec2f operator- (const float _Scale) const;
			const Vec2f& operator-= (const float _Scale);

			const Vec2f operator* (const Vec2f& _Other) const;
			const Vec2f& operator*= (const Vec2f& _Other);
			const Vec2f operator* (const float _Scale) const;
			const Vec2f& operator*= (const float _Scale);

			const Vec2f operator/ (const Vec2f& _Other) const;
			const Vec2f& operator/= (const Vec2f& _Other);
			const Vec2f operator/ (const float _Scale) const;
			const Vec2f& operator/= (const float _Scale);

			const bool operator== (const Vec2f& _Other) const;
			const bool operator!= (const Vec2f& _Other) const;
			const bool operator> (const Vec2f& _Other) const;
			const bool operator>= (const Vec2f& _Other) const;
			const bool operator< (const Vec2f& _Other) const;
			const bool operator<= (const Vec2f& _Other) const;

			float& operator[] (const unsigned long _Index);
			const float& operator[] (const unsigned long _Index) const;

			const Vec2f& operator= (const Vec2f& _Other);
			const Vec2f& operator= (Vec2f&& _Other) noexcept;

		};

		class BFW_API Vec3f
		{

		public:

			float x, y, z;

			Vec3f(const float _x = 0.0f, const float _y = 0.0f, const float _z = 0.0f);
			Vec3f(const Vec3f& _Other);
			Vec3f(Vec3f&& _Other) noexcept;
			~Vec3f();

			float* Data();
			const float* Data() const;

			const float Magnitude() const;
			const float DotProduct(const Vec3f& _Other) const;
			const Vec3f CrossProduct(const Vec3f& _Other) const;

			const float GetAngle(const Vec3f& _Center = Vec3f(0.0f, 0.0f, 0.0f), const Vec3f& _Other = Vec3f(1.0f, 0.0f, 0.0f)) const;

			const Vec3f Rotated(const float _Angle, const Vec3f& _Center = Vec3f(0.0f, 0.0f, 0.0f), const Vec3f& _U = Vec3f(0.0f, 1.0f, 0.0f)) const;
			const Vec3f& Rotate(const float _Angle, const Vec3f& _Center = Vec3f(0.0f, 0.0f, 0.0f), const Vec3f& _U = Vec3f(0.0f, 1.0f, 0.0f));

			const Vec3f Flipped(const Vec3f& _U = Vec3f(1.0f, 0.0f, 0.0f), const Vec3f& _Center = Vec3f(0.0f, 0.0f, 0.0f)) const;
			const Vec3f& Flip(const Vec3f& _U = Vec3f(1.0f, 0.0f, 0.0f), const Vec3f& _Center = Vec3f(0.0f, 0.0f, 0.0f));

			const Vec3f& operator+ () const;
			const Vec3f operator- () const;

			const Vec3f operator+ (const Vec3f& _Other) const;
			const Vec3f& operator+= (const Vec3f& _Other);
			const Vec3f operator+ (const float _Scale) const;
			const Vec3f& operator+= (const float _Scale);

			const Vec3f operator- (const Vec3f& _Other) const;
			const Vec3f& operator-= (const Vec3f& _Other);
			const Vec3f operator- (const float _Scale) const;
			const Vec3f& operator-= (const float _Scale);

			const Vec3f operator* (const Vec3f& _Other) const;
			const Vec3f& operator*= (const Vec3f& _Other);
			const Vec3f operator* (const float _Scale) const;
			const Vec3f& operator*= (const float _Scale);

			const Vec3f operator/ (const Vec3f& _Other) const;
			const Vec3f& operator/= (const Vec3f& _Other);
			const Vec3f operator/ (const float _Scale) const;
			const Vec3f& operator/= (const float _Scale);

			const bool operator== (const Vec3f& _Other) const;
			const bool operator!= (const Vec3f& _Other) const;
			const bool operator> (const Vec3f& _Other) const;
			const bool operator>= (const Vec3f& _Other) const;
			const bool operator< (const Vec3f& _Other) const;
			const bool operator<= (const Vec3f& _Other) const;

			float& operator[] (const unsigned long _Index);
			const float& operator[] (const unsigned long _Index) const;

			const Vec3f& operator= (const Vec3f& _Other);
			const Vec3f& operator= (Vec3f&& _Other) noexcept;

		};

		class BFW_API Vec4f
		{

		public:

			float x, y, z, w;

			Vec4f(const float _x = 0.0f, const float _y = 0.0f, const float _z = 0.0f, const float _w = 0.0f);
			Vec4f(const Vec4f& _Other);
			Vec4f(Vec4f&& _Other) noexcept;
			~Vec4f();

			float* Data();
			const float* Data() const;

			const float Magnitude() const;
			const float DotProduct(const Vec4f& _Other) const;
			const Vec4f CrossProduct(const Vec4f& _Other) const;

			const float GetAngle(const Vec4f& _Center = Vec4f(0.0f, 0.0f, 0.0f, 0.0f), const Vec4f& _Other = Vec4f(1.0f, 0.0f, 0.0f, 0.0f)) const;

			const Vec4f Rotated(const float _Angle, const Vec4f& _Center = Vec4f(0.0f, 0.0f, 0.0f, 0.0f), const Vec4f& _U = Vec4f(0.0f, 0.0f, 1.0f, 0.0f)) const;
			const Vec4f& Rotate(const float _Angle, const Vec4f& _Center = Vec4f(0.0f, 0.0f, 0.0f, 0.0f), const Vec4f& _U = Vec4f(0.0f, 0.0f, 1.0f, 0.0f));

			const Vec4f Flipped(const Vec4f& _U = Vec4f(1.0f, 0.0f, 0.0f, 0.0f), const Vec4f& _Center = Vec4f(0.0f, 0.0f, 0.0f, 0.0f)) const;
			const Vec4f& Flip(const Vec4f& _U = Vec4f(1.0f, 0.0f, 0.0f, 0.0f), const Vec4f& _Center = Vec4f(0.0f, 0.0f, 0.0f, 0.0f));

			const Vec4f& operator+ () const;
			const Vec4f operator- () const;

			const Vec4f operator+ (const Vec4f& _Other) const;
			const Vec4f& operator+= (const Vec4f& _Other);
			const Vec4f operator+ (const float _Scale) const;
			const Vec4f& operator+= (const float _Scale);

			const Vec4f operator- (const Vec4f& _Other) const;
			const Vec4f& operator-= (const Vec4f& _Other);
			const Vec4f operator- (const float _Scale) const;
			const Vec4f& operator-= (const float _Scale);

			const Vec4f operator* (const Vec4f& _Other) const;
			const Vec4f& operator*= (const Vec4f& _Other);
			const Vec4f operator* (const float _Scale) const;
			const Vec4f& operator*= (const float _Scale);

			const Vec4f operator/ (const Vec4f& _Other) const;
			const Vec4f& operator/= (const Vec4f& _Other);
			const Vec4f operator/ (const float _Scale) const;
			const Vec4f& operator/= (const float _Scale);

			const bool operator== (const Vec4f& _Other) const;
			const bool operator!= (const Vec4f& _Other) const;
			const bool operator> (const Vec4f& _Other) const;
			const bool operator>= (const Vec4f& _Other) const;
			const bool operator< (const Vec4f& _Other) const;
			const bool operator<= (const Vec4f& _Other) const;

			float& operator[] (const unsigned long _Index);
			const float& operator[] (const unsigned long _Index) const;

			const Vec4f& operator= (const Vec4f& _Other);
			const Vec4f& operator= (Vec4f&& _Other) noexcept;

		};

		class BFW_API Vec2d
		{

		public:

			double x, y;

			Vec2d(const double _x = 0.0, const double _y = 0.0);
			Vec2d(const Vec2d& _Other);
			Vec2d(Vec2d&& _Other) noexcept;
			~Vec2d();

			double* Data();
			const double* Data() const;

			const double Magnitude() const;
			const double DotProduct(const Vec2d& _Other) const;

			const double GetAngle(const Vec2d& _Center = Vec2d(0.0, 0.0), const Vec2d& _Other = Vec2d(1.0, 0.0)) const;

			const Vec2d Rotated(const double _Angle, const Vec2d& _Center = Vec2d(0.0, 0.0)) const;
			const Vec2d& Rotate(const double _Angle, const Vec2d& _Center = Vec2d(0.0, 0.0));

			const Vec2d Flipped(const Vec2d& _U = Vec2d(0.0, 1.0), const Vec2d& _Center = Vec2d(0.0, 0.0)) const;
			const Vec2d& Flip(const Vec2d& _U = Vec2d(0.0, 1.0), const Vec2d& _Center = Vec2d(0.0, 0.0));

			const Vec2d& operator+ () const;
			const Vec2d operator- () const;

			const Vec2d operator+ (const Vec2d& _Other) const;
			const Vec2d& operator+= (const Vec2d& _Other);
			const Vec2d operator+ (const double _Scale) const;
			const Vec2d& operator+= (const double _Scale);

			const Vec2d operator- (const Vec2d& _Other) const;
			const Vec2d& operator-= (const Vec2d& _Other);
			const Vec2d operator- (const double _Scale) const;
			const Vec2d& operator-= (const double _Scale);

			const Vec2d operator* (const Vec2d& _Other) const;
			const Vec2d& operator*= (const Vec2d& _Other);
			const Vec2d operator* (const double _Scale) const;
			const Vec2d& operator*= (const double _Scale);

			const Vec2d operator/ (const Vec2d& _Other) const;
			const Vec2d& operator/= (const Vec2d& _Other);
			const Vec2d operator/ (const double _Scale) const;
			const Vec2d& operator/= (const double _Scale);

			const bool operator== (const Vec2d& _Other) const;
			const bool operator!= (const Vec2d& _Other) const;
			const bool operator> (const Vec2d& _Other) const;
			const bool operator>= (const Vec2d& _Other) const;
			const bool operator< (const Vec2d& _Other) const;
			const bool operator<= (const Vec2d& _Other) const;

			double& operator[] (const unsigned long _Index);
			const double& operator[] (const unsigned long _Index) const;

			const Vec2d& operator= (const Vec2d& _Other);
			const Vec2d& operator= (Vec2d&& _Other) noexcept;

		};

		class BFW_API Vec3d
		{

		public:

			double x, y, z;

			Vec3d(const double _x = 0.0, const double _y = 0.0, const double _z = 0.0);
			Vec3d(const Vec3d& _Other);
			Vec3d(Vec3d&& _Other) noexcept;
			~Vec3d();

			double* Data();
			const double* Data() const;

			const double Magnitude() const;
			const double DotProduct(const Vec3d& _Other) const;
			const Vec3d CrossProduct(const Vec3d& _Other) const;

			const double GetAngle(const Vec3d& _Center = Vec3d(0.0, 0.0, 0.0), const Vec3d& _Other = Vec3d(1.0, 0.0, 0.0)) const;

			const Vec3d Rotated(const double _Angle, const Vec3d& _Center = Vec3d(0.0, 0.0, 0.0), const Vec3d& _U = Vec3d(0.0, 1.0, 0.0)) const;
			const Vec3d& Rotate(const double _Angle, const Vec3d& _Center = Vec3d(0.0, 0.0, 0.0), const Vec3d& _U = Vec3d(0.0, 1.0, 0.0));

			const Vec3d Flipped(const Vec3d& _U = Vec3d(1.0, 0.0, 0.0), const Vec3d& _Center = Vec3d(0.0, 0.0, 0.0)) const;
			const Vec3d& Flip(const Vec3d& _U = Vec3d(1.0, 0.0, 0.0), const Vec3d& _Center = Vec3d(0.0, 0.0, 0.0));

			const Vec3d& operator+ () const;
			const Vec3d operator- () const;

			const Vec3d operator+ (const Vec3d& _Other) const;
			const Vec3d& operator+= (const Vec3d& _Other);
			const Vec3d operator+ (const double _Scale) const;
			const Vec3d& operator+= (const double _Scale);

			const Vec3d operator- (const Vec3d& _Other) const;
			const Vec3d& operator-= (const Vec3d& _Other);
			const Vec3d operator- (const double _Scale) const;
			const Vec3d& operator-= (const double _Scale);

			const Vec3d operator* (const Vec3d& _Other) const;
			const Vec3d& operator*= (const Vec3d& _Other);
			const Vec3d operator* (const double _Scale) const;
			const Vec3d& operator*= (const double _Scale);

			const Vec3d operator/ (const Vec3d& _Other) const;
			const Vec3d& operator/= (const Vec3d& _Other);
			const Vec3d operator/ (const double _Scale) const;
			const Vec3d& operator/= (const double _Scale);

			const bool operator== (const Vec3d& _Other) const;
			const bool operator!= (const Vec3d& _Other) const;
			const bool operator> (const Vec3d& _Other) const;
			const bool operator>= (const Vec3d& _Other) const;
			const bool operator< (const Vec3d& _Other) const;
			const bool operator<= (const Vec3d& _Other) const;

			double& operator[] (const unsigned long _Index);
			const double& operator[] (const unsigned long _Index) const;

			const Vec3d& operator= (const Vec3d& _Other);
			const Vec3d& operator= (Vec3d&& _Other) noexcept;

		};

		class BFW_API Vec4d
		{

		public:

			double x, y, z, w;

			Vec4d(const double _x = 0.0, const double _y = 0.0, const double _z = 0.0, const double _w = 0.0);
			Vec4d(const Vec4d& _Other);
			Vec4d(Vec4d&& _Other) noexcept;
			~Vec4d();

			double* Data();
			const double* Data() const;

			const double Magnitude() const;
			const double DotProduct(const Vec4d& _Other) const;
			const Vec4d CrossProduct(const Vec4d& _Other) const;

			const double GetAngle(const Vec4d& _Center = Vec4d(0.0, 0.0, 0.0, 0.0), const Vec4d& _Other = Vec4d(1.0, 0.0, 0.0, 0.0)) const;

			const Vec4d Rotated(const double _Angle, const Vec4d& _Center = Vec4d(0.0, 0.0, 0.0, 0.0), const Vec4d& _U = Vec4d(0.0, 0.0, 1.0, 0.0)) const;
			const Vec4d& Rotate(const double _Angle, const Vec4d& _Center = Vec4d(0.0, 0.0, 0.0, 0.0), const Vec4d& _U = Vec4d(0.0, 0.0, 1.0, 0.0));

			const Vec4d Flipped(const Vec4d& _U = Vec4d(1.0, 0.0, 0.0, 0.0), const Vec4d& _Center = Vec4d(0.0, 0.0, 0.0, 0.0)) const;
			const Vec4d& Flip(const Vec4d& _U = Vec4d(1.0, 0.0, 0.0, 0.0), const Vec4d& _Center = Vec4d(0.0, 0.0, 0.0, 0.0));

			const Vec4d& operator+ () const;
			const Vec4d operator- () const;

			const Vec4d operator+ (const Vec4d& _Other) const;
			const Vec4d& operator+= (const Vec4d& _Other);
			const Vec4d operator+ (const double _Scale) const;
			const Vec4d& operator+= (const double _Scale);

			const Vec4d operator- (const Vec4d& _Other) const;
			const Vec4d& operator-= (const Vec4d& _Other);
			const Vec4d operator- (const double _Scale) const;
			const Vec4d& operator-= (const double _Scale);

			const Vec4d operator* (const Vec4d& _Other) const;
			const Vec4d& operator*= (const Vec4d& _Other);
			const Vec4d operator* (const double _Scale) const;
			const Vec4d& operator*= (const double _Scale);

			const Vec4d operator/ (const Vec4d& _Other) const;
			const Vec4d& operator/= (const Vec4d& _Other);
			const Vec4d operator/ (const double _Scale) const;
			const Vec4d& operator/= (const double _Scale);

			const bool operator== (const Vec4d& _Other) const;
			const bool operator!= (const Vec4d& _Other) const;
			const bool operator> (const Vec4d& _Other) const;
			const bool operator>= (const Vec4d& _Other) const;
			const bool operator< (const Vec4d& _Other) const;
			const bool operator<= (const Vec4d& _Other) const;

			double& operator[] (const unsigned long _Index);
			const double& operator[] (const unsigned long _Index) const;

			const Vec4d& operator= (const Vec4d& _Other);
			const Vec4d& operator= (Vec4d&& _Other) noexcept;

		};

		class BFW_API Mat2f
		{

		public:

			Mat2f();
			Mat2f(const float _x, const float _y);
			Mat2f(const Mat2f& _Other);
			Mat2f(Mat2f&& _Other) noexcept;
			~Mat2f();

			float* Data();
			const float* Data() const;

			const float Determinant() const;
			const float Trace() const;

			const Mat2f& Transpose();
			const Mat2f Transposed() const;

			const Mat2f& Scale(const float _x, const float _y);
			static const Mat2f GetScale(const float _x, const float _y);

			const Mat2f& Fill(const float _Value);
			static const Mat2f GetFill(const float _Value);

			const Mat2f& Shear(const float _Value, const unsigned long _ShearedAxis, const unsigned long _ByAxis);
			static const Mat2f GetShear(const float _Value, const unsigned long _ShearedAxis, const unsigned long _ByAxis);

			const Mat2f& Rotation(const float _Angle);
			static const Mat2f GetRotation(const float _Angle);

			const Mat2f& Flip(const Vec2f& _U);
			static const Mat2f GetFlip(const Vec2f& _U);

			const Mat2f& operator+ () const;
			const Mat2f operator- () const;

			const Vec2f operator* (const Vec2f& _Vec) const;

			const Mat2f operator+ (const Mat2f& _Other) const;
			const Mat2f& operator+= (const Mat2f& _Other);
			const Mat2f operator+ (const float _Scale) const;
			const Mat2f& operator+= (const float _Scale);
			const Mat2f operator- (const Mat2f& _Other) const;
			const Mat2f& operator-= (const Mat2f& _Other);
			const Mat2f operator- (const float _Scale) const;
			const Mat2f& operator-= (const float _Scale);
			const Mat2f operator* (const Mat2f& _Other) const;
			const Mat2f& operator*= (const Mat2f& _Other);
			const Mat2f operator* (const float _Scale) const;
			const Mat2f& operator*= (const float _Scale);
			const Mat2f operator/ (const float _Scale) const;
			const Mat2f& operator/= (const float _Scale);

			const bool operator== (const Mat2f& _Other) const;
			const bool operator!= (const Mat2f& _Other) const;
			const bool operator> (const Mat2f& _Other) const;
			const bool operator>= (const Mat2f& _Other) const;
			const bool operator< (const Mat2f& _Other) const;
			const bool operator<= (const Mat2f& _Other) const;

			float* operator[] (const unsigned long _Index);
			const float* operator[] (const unsigned long _Index) const;

			const Mat2f& operator= (const Mat2f& _Other);
			const Mat2f& operator= (Mat2f&& _Other) noexcept;

		private:

			Vec2f Matrix[2];

		};

		class BFW_API Mat3f
		{

		public:

			Mat3f();
			Mat3f(const float _x, const float _y, const float _z);
			Mat3f(const Mat3f& _Other);
			Mat3f(Mat3f&& _Other) noexcept;
			~Mat3f();

			float* Data();
			const float* Data() const;

			const float Determinant() const;
			const float Trace() const;

			const Mat3f& Transpose();
			const Mat3f Transposed() const;

			const Mat3f& Scale(const float _x, const float _y, const float _z);
			static const Mat3f GetScale(const float _x, const float _y, const float _z);

			const Mat3f& Fill(const float _Value);
			static const Mat3f GetFill(const float _Value);

			const Mat3f& Shear(const float _Value, const unsigned long _ShearedAxis, const unsigned long _ByAxis);
			static const Mat3f GetShear(const float _Value, const unsigned long _ShearedAxis, const unsigned long _ByAxis);

			const Mat3f& Rotation(const float _Angle, const Vec3f& _U);
			static const Mat3f GetRotation(const float _Angle, const Vec3f& _U);

			const Mat3f& Translation(const Vec3f& _V);
			static const Mat3f GetTranslation(const Vec3f& _V);

			const Mat3f& Ortho(const float _Left, const float _Right, const float _Top, const float _Bottom);
			static const Mat3f GetOrtho(const float _Left, const float _Right, const float _Top, const float _Bottom);

			const Mat3f& Flip(const Vec3f& _U, const Vec3f& _Center);
			static const Mat3f GetFlip(const Vec3f& _U, const Vec3f& _Center);

			const Mat3f& Flip(const Vec3f& _U);
			static const Mat3f GetFlip(const Vec3f& _U);

			const Mat3f& operator+ () const;
			const Mat3f operator- () const;

			const Vec3f operator* (const Vec3f& _Vec) const;

			const Mat3f operator+ (const Mat3f& _Other) const;
			const Mat3f& operator+= (const Mat3f& _Other);
			const Mat3f operator+ (const float _Scale) const;
			const Mat3f& operator+= (const float _Scale);
			const Mat3f operator- (const Mat3f& _Other) const;
			const Mat3f& operator-= (const Mat3f& _Other);
			const Mat3f operator- (const float _Scale) const;
			const Mat3f& operator-= (const float _Scale);
			const Mat3f operator* (const Mat3f& _Other) const;
			const Mat3f& operator*= (const Mat3f& _Other);
			const Mat3f operator* (const float _Scale) const;
			const Mat3f& operator*= (const float _Scale);
			const Mat3f operator/ (const float _Scale) const;
			const Mat3f& operator/= (const float _Scale);

			const bool operator== (const Mat3f& _Other) const;
			const bool operator!= (const Mat3f& _Other) const;
			const bool operator> (const Mat3f& _Other) const;
			const bool operator>= (const Mat3f& _Other) const;
			const bool operator< (const Mat3f& _Other) const;
			const bool operator<= (const Mat3f& _Other) const;

			float* operator[] (const unsigned long _Index);
			const float* operator[] (const unsigned long _Index) const;

			const Mat3f& operator= (const Mat3f& _Other);
			const Mat3f& operator= (Mat3f&& _Other) noexcept;

		private:

			Vec3f Matrix[3];

		};

		class BFW_API Mat4f
		{

		public:

			Mat4f();
			Mat4f(const float _x, const float _y, const float _z);
			Mat4f(const Mat4f& _Other);
			Mat4f(Mat4f&& _Other) noexcept;
			~Mat4f();

			float* Data();
			const float* Data() const;

			const float Determinant() const;
			const float Trace() const;

			const Mat4f& Transpose();
			const Mat4f Transposed() const;

			const Mat4f& Scale(const float _x, const float _y, const float _z);
			static const Mat4f GetScale(const float _x, const float _y, const float _z);

			const Mat4f& Fill(const float _Value);
			static const Mat4f GetFill(const float _Value);

			const Mat4f& Shear(const float _Value, const unsigned long _ShearedAxis, const unsigned long _ByAxis);
			static const Mat4f GetShear(const float _Value, const unsigned long _ShearedAxis, const unsigned long _ByAxis);

			const Mat4f& Rotation(const float _Angle, const Vec4f& _U);
			static const Mat4f GetRotation(const float _Angle, const Vec4f& _U);

			const Mat4f& Translation(const Vec4f& _V);
			static const Mat4f GetTranslation(const Vec4f& _V);

			const Mat4f& Ortho(const float _Left, const float _Right, const float _Top, const float _Bottom, const float _Front, const float _Back);
			static const Mat4f GetOrtho(const float _Left, const float _Right, const float _Top, const float _Bottom, const float _Front, const float _Back);

			const Mat4f& Perspective(const float _Fov, const float _AspectRatio, const float _ZNear, const float _ZFar);
			static const Mat4f GetPerspective(const float _Fov, const float _AspectRatio, const float _ZNear, const float _ZFar);

			const Mat4f& Flip(const Vec4f& _U, const Vec4f& _Center);
			static const Mat4f GetFlip(const Vec4f& _U, const Vec4f& _Center);

			const Mat4f& operator+ () const;
			const Mat4f operator- () const;

			const Vec4f operator* (const Vec4f& _Vec) const;

			const Mat4f operator+ (const Mat4f& _Other) const;
			const Mat4f& operator+= (const Mat4f& _Other);
			const Mat4f operator+ (const float _Scale) const;
			const Mat4f& operator+= (const float _Scale);
			const Mat4f operator- (const Mat4f& _Other) const;
			const Mat4f& operator-= (const Mat4f& _Other);
			const Mat4f operator- (const float _Scale) const;
			const Mat4f& operator-= (const float _Scale);
			const Mat4f operator* (const Mat4f& _Other) const;
			const Mat4f& operator*= (const Mat4f& _Other);
			const Mat4f operator* (const float _Scale) const;
			const Mat4f& operator*= (const float _Scale);
			const Mat4f operator/ (const float _Scale) const;
			const Mat4f& operator/= (const float _Scale);

			const bool operator== (const Mat4f& _Other) const;
			const bool operator!= (const Mat4f& _Other) const;
			const bool operator> (const Mat4f& _Other) const;
			const bool operator>= (const Mat4f& _Other) const;
			const bool operator< (const Mat4f& _Other) const;
			const bool operator<= (const Mat4f& _Other) const;

			float* operator[] (const unsigned long _Index);
			const float* operator[] (const unsigned long _Index) const;

			const Mat4f& operator= (const Mat4f& _Other);
			const Mat4f& operator= (Mat4f&& _Other) noexcept;

		private:

			Vec4f Matrix[4];

		};

		class BFW_API Mat2d
		{

		public:

			Mat2d();
			Mat2d(const double _x, const double _y);
			Mat2d(const Mat2d& _Other);
			Mat2d(Mat2d&& _Other) noexcept;
			~Mat2d();

			double* Data();
			const double* Data() const;

			const double Determinant() const;
			const double Trace() const;

			const Mat2d& Transpose();
			const Mat2d Transposed() const;

			const Mat2d& Scale(const double _x, const double _y);
			static const Mat2d GetScale(const double _x, const double _y);

			const Mat2d& Fill(const double _Value);
			static const Mat2d GetFill(const double _Value);

			const Mat2d& Shear(const double _Value, const unsigned long _ShearedAxis, const unsigned long _ByAxis);
			static const Mat2d GetShear(const double _Value, const unsigned long _ShearedAxis, const unsigned long _ByAxis);

			const Mat2d& Rotation(const double _Angle);
			static const Mat2d GetRotation(const double _Angle);

			const Mat2d& Flip(const Vec2d& _U);
			static const Mat2d GetFlip(const Vec2d& _U);

			const Mat2d& operator+ () const;
			const Mat2d operator- () const;

			const Vec2d operator* (const Vec2d& _Vec) const;

			const Mat2d operator+ (const Mat2d& _Other) const;
			const Mat2d& operator+= (const Mat2d& _Other);
			const Mat2d operator+ (const double _Scale) const;
			const Mat2d& operator+= (const double _Scale);
			const Mat2d operator- (const Mat2d& _Other) const;
			const Mat2d& operator-= (const Mat2d& _Other);
			const Mat2d operator- (const double _Scale) const;
			const Mat2d& operator-= (const double _Scale);
			const Mat2d operator* (const Mat2d& _Other) const;
			const Mat2d& operator*= (const Mat2d& _Other);
			const Mat2d operator* (const double _Scale) const;
			const Mat2d& operator*= (const double _Scale);
			const Mat2d operator/ (const double _Scale) const;
			const Mat2d& operator/= (const double _Scale);

			const bool operator== (const Mat2d& _Other) const;
			const bool operator!= (const Mat2d& _Other) const;
			const bool operator> (const Mat2d& _Other) const;
			const bool operator>= (const Mat2d& _Other) const;
			const bool operator< (const Mat2d& _Other) const;
			const bool operator<= (const Mat2d& _Other) const;

			double* operator[] (const unsigned long _Index);
			const double* operator[] (const unsigned long _Index) const;

			const Mat2d& operator= (const Mat2d& _Other);
			const Mat2d& operator= (Mat2d&& _Other) noexcept;

		private:

			Vec2d Matrix[2];

		};

		class BFW_API Mat3d
		{

		public:

			Mat3d();
			Mat3d(const double _x, const double _y, const double _z);
			Mat3d(const Mat3d& _Other);
			Mat3d(Mat3d&& _Other) noexcept;
			~Mat3d();

			double* Data();
			const double* Data() const;

			const double Determinant() const;
			const double Trace() const;

			const Mat3d& Transpose();
			const Mat3d Transposed() const;

			const Mat3d& Scale(const double _x, const double _y, const double _z);
			static const Mat3d GetScale(const double _x, const double _y, const double _z);

			const Mat3d& Fill(const double _Value);
			static const Mat3d GetFill(const double _Value);

			const Mat3d& Shear(const double _Value, const unsigned long _ShearedAxis, const unsigned long _ByAxis);
			static const Mat3d GetShear(const double _Value, const unsigned long _ShearedAxis, const unsigned long _ByAxis);

			const Mat3d& Rotation(const double _Angle, const Vec3d& _U);
			static const Mat3d GetRotation(const double _Angle, const Vec3d& _U);

			const Mat3d& Translation(const Vec3d& _V);
			static const Mat3d GetTranslation(const Vec3d& _V);

			const Mat3d& Ortho(const double _Left, const double _Right, const double _Top, const double _Bottom);
			static const Mat3d GetOrtho(const double _Left, const double _Right, const double _Top, const double _Bottom);

			const Mat3d& Flip(const Vec3d& _U, const Vec3d& _Center);
			static const Mat3d GetFlip(const Vec3d& _U, const Vec3d& _Center);

			const Mat3d& Flip(const Vec3d& _U);
			static const Mat3d GetFlip(const Vec3d& _U);

			const Mat3d& operator+ () const;
			const Mat3d operator- () const;

			const Vec3d operator* (const Vec3d& _Vec) const;

			const Mat3d operator+ (const Mat3d& _Other) const;
			const Mat3d& operator+= (const Mat3d& _Other);
			const Mat3d operator+ (const double _Scale) const;
			const Mat3d& operator+= (const double _Scale);
			const Mat3d operator- (const Mat3d& _Other) const;
			const Mat3d& operator-= (const Mat3d& _Other);
			const Mat3d operator- (const double _Scale) const;
			const Mat3d& operator-= (const double _Scale);
			const Mat3d operator* (const Mat3d& _Other) const;
			const Mat3d& operator*= (const Mat3d& _Other);
			const Mat3d operator* (const double _Scale) const;
			const Mat3d& operator*= (const double _Scale);
			const Mat3d operator/ (const double _Scale) const;
			const Mat3d& operator/= (const double _Scale);

			const bool operator== (const Mat3d& _Other) const;
			const bool operator!= (const Mat3d& _Other) const;
			const bool operator> (const Mat3d& _Other) const;
			const bool operator>= (const Mat3d& _Other) const;
			const bool operator< (const Mat3d& _Other) const;
			const bool operator<= (const Mat3d& _Other) const;

			double* operator[] (const unsigned long _Index);
			const double* operator[] (const unsigned long _Index) const;

			const Mat3d& operator= (const Mat3d& _Other);
			const Mat3d& operator= (Mat3d&& _Other) noexcept;

		private:

			Vec3d Matrix[3];

		};

		class BFW_API Mat4d
		{

		public:

			Mat4d();
			Mat4d(const double _x, const double _y, const double _z);
			Mat4d(const Mat4d& _Other);
			Mat4d(Mat4d&& _Other) noexcept;
			~Mat4d();

			double* Data();
			const double* Data() const;

			const double Determinant() const;
			const double Trace() const;

			const Mat4d& Transpose();
			const Mat4d Transposed() const;

			const Mat4d& Scale(const double _x, const double _y, const double _z);
			static const Mat4d GetScale(const double _x, const double _y, const double _z);

			const Mat4d& Fill(const double _Value);
			static const Mat4d GetFill(const double _Value);

			const Mat4d& Shear(const double _Value, const unsigned long _ShearedAxis, const unsigned long _ByAxis);
			static const Mat4d GetShear(const double _Value, const unsigned long _ShearedAxis, const unsigned long _ByAxis);

			const Mat4d& Rotation(const double _Angle, const Vec4d& _U);
			static const Mat4d GetRotation(const double _Angle, const Vec4d& _U);

			const Mat4d& Translation(const Vec4d& _V);
			static const Mat4d GetTranslation(const Vec4d& _V);

			const Mat4d& Ortho(const double _Left, const double _Right, const double _Top, const double _Bottom, const double _Front, const double _Back);
			static const Mat4d GetOrtho(const double _Left, const double _Right, const double _Top, const double _Bottom, const double _Front, const double _Back);

			const Mat4d& Perspective(const double _Fov, const double _AspectRatio, const double _ZNear, const double _ZFar);
			static const Mat4d GetPerspective(const double _Fov, const double _AspectRatio, const double _ZNear, const double _ZFar);

			const Mat4d& Flip(const Vec4d& _U, const Vec4d& _Center);
			static const Mat4d GetFlip(const Vec4d& _U, const Vec4d& _Center);

			const Mat4d& operator+ () const;
			const Mat4d operator- () const;

			const Vec4d operator* (const Vec4d& _Vec) const;

			const Mat4d operator+ (const Mat4d& _Other) const;
			const Mat4d& operator+= (const Mat4d& _Other);
			const Mat4d operator+ (const double _Scale) const;
			const Mat4d& operator+= (const double _Scale);
			const Mat4d operator- (const Mat4d& _Other) const;
			const Mat4d& operator-= (const Mat4d& _Other);
			const Mat4d operator- (const double _Scale) const;
			const Mat4d& operator-= (const double _Scale);
			const Mat4d operator* (const Mat4d& _Other) const;
			const Mat4d& operator*= (const Mat4d& _Other);
			const Mat4d operator* (const double _Scale) const;
			const Mat4d& operator*= (const double _Scale);
			const Mat4d operator/ (const double _Scale) const;
			const Mat4d& operator/= (const double _Scale);

			const bool operator== (const Mat4d& _Other) const;
			const bool operator!= (const Mat4d& _Other) const;
			const bool operator> (const Mat4d& _Other) const;
			const bool operator>= (const Mat4d& _Other) const;
			const bool operator< (const Mat4d& _Other) const;
			const bool operator<= (const Mat4d& _Other) const;

			double* operator[] (const unsigned long _Index);
			const double* operator[] (const unsigned long _Index) const;

			const Mat4d& operator= (const Mat4d& _Other);
			const Mat4d& operator= (Mat4d&& _Other) noexcept;

		private:

			Vec4d Matrix[4];

		};

		extern const double BFW_API dPi;
		extern const double BFW_API dDegreesToRadians;
		extern const double BFW_API dRadiansToDegrees;

		extern const float BFW_API fPi;
		extern const float BFW_API fDegreesToRadians;
		extern const float BFW_API fRadiansToDegrees;

		float BFW_API fSqrt(const float _Value);
		float BFW_API fSin(const float _Value);
		float BFW_API fCos(const float _Value);
		float BFW_API fTan(const float _Value);
		float BFW_API fCoTan(const float _Value);
		float BFW_API fASin(const float _Value);
		float BFW_API fACos(const float _Value);
		float BFW_API fATan(const float _Value);
		float BFW_API fACoTan(const float _Value);

		double BFW_API dSqrt(const double _Value);
		double BFW_API dSin(const double _Value);
		double BFW_API dCos(const double _Value);
		double BFW_API dTan(const double _Value);
		double BFW_API dCoTan(const double _Value);
		double BFW_API dASin(const double _Value);
		double BFW_API dACos(const double _Value);
		double BFW_API dATan(const double _Value);
		double BFW_API dACoTan(const double _Value);

		long BFW_API lModule(const long _Value);
		long long BFW_API llModule(const long long _Value);
		float BFW_API fModule(const float _Value);
		double BFW_API dModule(const double _Value);

		void BFW_API lSwap(long& _A, long& _B);
		void BFW_API llSwap(long long& _A, long long& _B);
		void BFW_API fSwap(float& _A, float& _B);
		void BFW_API dSwap(double& _A, double& _B);

		long BFW_API lPeriod(const long _Value, const long _Min, const long _Max);
		long long BFW_API llPeriod(const long long _Value, const long long _Min, const long long _Max);
		float BFW_API fPeriod(const float _Value, const float _Min, const float _Max);
		double BFW_API dPeriod(const double _Value, const double _Min, const double _Max);

		long BFW_API lMap(const long _Value, const long _Min, const long _Max, const long _NewMin, const long _NewMax);
		long long BFW_API llMap(const long long _Value, const long long _Min, const long long _Max, const long long _NewMin, const long long _NewMax);
		float BFW_API fMap(const float _Value, const float _Min, const float _Max, const float _NewMin, const float _NewMax);
		double BFW_API dMap(const double _Value, const double _Min, const double _Max, const double _NewMin, const double _NewMax);

		long BFW_API lAdjustValue(const long _Value, const long _Min, const long _Max);
		long long BFW_API llAdjustValue(const long long _Value, const long long _Min, const long long _Max);
		float BFW_API fAdjustValue(const float _Value, const float _Min, const float _Max);
		double BFW_API dAdjustValue(const double _Value, const double _Min, const double _Max);

	}

}



#endif
