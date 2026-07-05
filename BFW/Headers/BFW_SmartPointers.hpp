#ifndef BFW_SmartPointers_hpp

#define BFW_SmartPointers_hpp



#include "BFW.hpp"



namespace BFW
{

	template <typename T> class UniquePointer
	{

	private:

		using Type = std::remove_const_t<T>;
		using ConstType = std::add_const_t<T>;

	public:

		UniquePointer() : Size(0), Pointer(nullptr)
		{

		}

		UniquePointer(const UniquePointer& _Other) : Size(0), Pointer(nullptr)
		{
			if (!_Other.Size)
			{
				return;
			}

			Size = _Other.Size;
			Pointer = new Type[Size];

			if (!Pointer)
			{
				Size = 0;
				throw nullptr;
			}

			for (size_t _Index = 0; _Index < Size; _Index++)
			{
				Pointer[_Index] = _Other.Pointer[_Index];
			}
		}

		UniquePointer(UniquePointer&& _Other) noexcept : Size(_Other.Size), Pointer(_Other.Pointer)
		{
			_Other.Size = 0;
			_Other.Pointer = nullptr;
		}

		~UniquePointer()
		{
			delete[] Pointer;
		}

		void Release()
		{
			delete[] Pointer;

			Size = 0;
			Pointer = nullptr;
		}

		const size_t GetSize() const
		{
			return Size;
		}

		Type* GetPointer() requires (!std::is_const_v<T>)
		{
			return Pointer;
		}

		ConstType* GetPointer() const
		{
			return Pointer;
		}

		operator Type* () requires (!std::is_const_v<T>)
		{
			return Pointer;
		}

		operator ConstType* () const
		{
			return Pointer;
		}

		Type* operator-> () requires (!std::is_const_v<T>)
		{
			return Pointer;
		}

		ConstType* operator-> () const
		{
			return Pointer;
		}

		Type& operator* () requires (!std::is_const_v<T>)
		{
			return *Pointer;
		}

		ConstType& operator* () const
		{
			return *Pointer;
		}

		Type& operator[] (const size_t _Index) requires (!std::is_const_v<T>)
		{
			return Pointer[_Index];
		}

		ConstType& operator[] (const size_t _Index) const
		{
			return Pointer[_Index];
		}

		UniquePointer& operator= (const UniquePointer& _Other)
		{
			if (this == &_Other)
			{
				return *this;
			}

			Size = 0;
			delete[] Pointer;
			Pointer = nullptr;

			if (!_Other.Size)
			{
				return *this;
			}

			Size = _Other.Size;
			Pointer = new Type[Size];

			if (!Pointer)
			{
				Size = 0;
				throw nullptr;
			}

			for (size_t _Index = 0; _Index < Size; _Index++)
			{
				Pointer[_Index] = _Other.Pointer[_Index];
			}

			return *this;
		}

		UniquePointer& operator= (UniquePointer&& _Other) noexcept
		{
			if (this == &_Other)
			{
				return *this;
			}

			delete[] Pointer;

			Size = _Other.Size;
			Pointer = _Other.Pointer;

			_Other.Size = 0;
			_Other.Pointer = nullptr;

			return *this;
		}

		static UniquePointer MakeUnique(Type&& _Value = Type())
		{
			UniquePointer _Result;

			_Result.Size = 1;
			_Result.Pointer = new Type[1];

			if (!_Result.Pointer)
			{
				_Result.Size = 0;
				throw nullptr;
			}

			*_Result.Pointer = (Type&&)(_Value);

			return _Result;
		}

		static UniquePointer MakeUnique(const size_t _Size)
		{
			if (_Size == 0)
			{
				throw nullptr;
			}

			UniquePointer _Result;

			_Result.Size = _Size;
			_Result.Pointer = new Type[_Size];

			if (!_Result.Pointer)
			{
				_Result.Size = 0;
				throw nullptr;
			}

			return _Result;
		}

	private:

		size_t Size;
		Type* Pointer;

	};

	template <typename T> class SharedPointer
	{

	private:

		using Type = std::remove_const_t<T>;
		using ConstType = std::add_const_t<T>;

	public:

		SharedPointer() : Mutex(nullptr), RefCount(nullptr), Size(0), Pointer(nullptr)
		{

		}

		SharedPointer(const SharedPointer& _Other) : Mutex(_Other.Mutex), RefCount(_Other.RefCount), Size(_Other.Size), Pointer(_Other.Pointer)
		{
			if (Mutex)
			{
				Mutex->lock();
				(*RefCount)++;
				Mutex->unlock();
			}
		}

		SharedPointer(SharedPointer&& _Other) noexcept : Mutex(_Other.Mutex), RefCount(_Other.RefCount), Size(_Other.Size), Pointer(_Other.Pointer)
		{
			_Other.Mutex = nullptr;
			_Other.RefCount = nullptr;
			_Other.Size = 0;
			_Other.Pointer = nullptr;
		}

		~SharedPointer()
		{
			if (Mutex)
			{
				Mutex->lock();

				(*RefCount)--;

				if (*RefCount == 0)
				{
					Mutex->unlock();

					delete Mutex;
					delete RefCount;
					delete[] Pointer;
				}
				else
				{
					Mutex->unlock();
				}
			}
		}

		void Release()
		{
			if (Mutex)
			{
				Mutex->lock();

				(*RefCount)--;

				if (*RefCount == 0)
				{
					Mutex->unlock();

					delete Mutex;
					delete RefCount;
					delete[] Pointer;
				}
				else
				{
					Mutex->unlock();
				}
			}

			Mutex = nullptr;
			RefCount = nullptr;
			Size = 0;
			Pointer = nullptr;
		}

		const size_t GetSize() const
		{
			return Size;
		}

		Type* GetPointer() requires (!std::is_const_v<T>)
		{
			return Pointer;
		}

		ConstType* GetPointer() const
		{
			return Pointer;
		}

		operator Type* () requires (!std::is_const_v<T>)
		{
			return Pointer;
		}

		operator ConstType* () const
		{
			return Pointer;
		}

		Type* operator-> () requires (!std::is_const_v<T>)
		{
			return Pointer;
		}

		ConstType* operator-> () const
		{
			return Pointer;
		}

		Type& operator* () requires (!std::is_const_v<T>)
		{
			return *Pointer;
		}

		ConstType& operator* () const
		{
			return *Pointer;
		}

		Type& operator[] (const size_t _Index) requires (!std::is_const_v<T>)
		{
			return Pointer[_Index];
		}

		ConstType& operator[] (const size_t _Index) const
		{
			return Pointer[_Index];
		}

		SharedPointer& operator= (const SharedPointer& _Other)
		{
			if (this == &_Other)
			{
				return *this;
			}

			if (Mutex)
			{
				Mutex->lock();

				(*RefCount)--;

				if (*RefCount == 0)
				{
					Mutex->unlock();

					delete Mutex;
					delete RefCount;
					delete[] Pointer;
				}
				else
				{
					Mutex->unlock();
				}
			}

			Mutex = _Other.Mutex;
			RefCount = _Other.RefCount;
			Size = _Other.Size;
			Pointer = _Other.Pointer;

			if (Mutex)
			{
				Mutex->lock();
				(*RefCount)++;
				Mutex->unlock();
			}

			return *this;
		}

		SharedPointer& operator= (SharedPointer&& _Other) noexcept
		{
			if (this == &_Other)
			{
				return *this;
			}

			if (Mutex)
			{
				Mutex->lock();

				(*RefCount)--;

				if (*RefCount == 0)
				{
					Mutex->unlock();

					delete Mutex;
					delete RefCount;
					delete[] Pointer;
				}
				else
				{
					Mutex->unlock();
				}
			}

			Mutex = _Other.Mutex;
			RefCount = _Other.RefCount;
			Size = _Other.Size;
			Pointer = _Other.Pointer;

			_Other.Mutex = nullptr;
			_Other.RefCount = nullptr;
			_Other.Size = 0;
			_Other.Pointer = nullptr;

			return *this;
		}

		static SharedPointer MakeShared(Type&& _Value = Type())
		{
			SharedPointer _Result;

			_Result.Mutex = new std::mutex;
			_Result.RefCount = new size_t;
			_Result.Size = 1;
			_Result.Pointer = new Type[1];

			if (!_Result.Mutex || !_Result.RefCount || !_Result.Pointer)
			{
				delete _Result.Mutex;
				_Result.Mutex = nullptr;
				delete _Result.RefCount;
				_Result.RefCount = nullptr;
				_Result.Size = 0;
				delete[] _Result.Pointer;
				_Result.Pointer = nullptr;
				throw nullptr;
			}

			*_Result.RefCount = 1;
			*_Result.Pointer = (Type&&)(_Value);

			return _Result;
		}

		static SharedPointer MakeShared(const size_t _Size)
		{
			if (_Size == 0)
			{
				throw nullptr;
			}

			SharedPointer _Result;

			_Result.Mutex = new std::mutex;
			_Result.RefCount = new size_t;
			_Result.Size = _Size;
			_Result.Pointer = new Type[_Size];

			if (!_Result.Mutex || !_Result.RefCount || !_Result.Pointer)
			{
				delete _Result.Mutex;
				_Result.Mutex = nullptr;
				delete _Result.RefCount;
				_Result.RefCount = nullptr;
				_Result.Size = 0;
				delete[] _Result.Pointer;
				_Result.Pointer = nullptr;
				throw nullptr;
			}

			*_Result.RefCount = 1;

			return _Result;
		}

	private:

		std::mutex* Mutex;
		size_t* RefCount;
		size_t Size;
		Type* Pointer;

	};

}



#endif
