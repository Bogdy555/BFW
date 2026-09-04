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

		Type* GetData() requires (!std::is_const_v<T>)
		{
			return Pointer;
		}

		ConstType* GetData() const
		{
			return Pointer;
		}

		explicit operator Type* () requires (!std::is_const_v<T>)
		{
			return Pointer;
		}

		explicit operator ConstType* () const
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

		static UniquePointer MakeUnique(ConstType& _Value = Type())
		{
			UniquePointer _Result;

			_Result.Size = 1;
			_Result.Pointer = new Type[1];

			if (!_Result.Pointer)
			{
				_Result.Size = 0;
				throw nullptr;
			}

			*_Result.Pointer = _Value;

			return _Result;
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

		static UniquePointer MakeUniqueArray(const std::initializer_list<Type>& _List)
		{
			if (_List.size() == 0)
			{
				throw nullptr;
			}

			UniquePointer _Result;

			_Result.Size = _List.size();
			_Result.Pointer = new Type[_Result.Size];

			if (!_Result.Pointer)
			{
				_Result.Size = 0;
				throw nullptr;
			}

			for (size_t _Index = 0; _Index < _Result.Size; _Index++)
			{
				_Result.Pointer[_Index] = *(_List.begin() + _Index);
			}

			return _Result;
		}

		static UniquePointer MakeUniqueArray(const size_t _Size)
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

		SharedPointer() : Mutex(nullptr), RefCount(nullptr), WeakPointers(nullptr), Size(0), Pointer(nullptr)
		{

		}

		SharedPointer(const SharedPointer& _Other) : Mutex(_Other.Mutex), RefCount(_Other.RefCount), WeakPointers(_Other.WeakPointers), Size(_Other.Size), Pointer(_Other.Pointer)
		{
			if (Mutex)
			{
				Mutex->lock();
				(*RefCount)++;
				Mutex->unlock();
			}
		}

		SharedPointer(SharedPointer&& _Other) noexcept : Mutex(_Other.Mutex), RefCount(_Other.RefCount), WeakPointers(_Other.WeakPointers), Size(_Other.Size), Pointer(_Other.Pointer)
		{
			_Other.Mutex = nullptr;
			_Other.RefCount = nullptr;
			_Other.WeakPointers = nullptr;
			_Other.Size = 0;
			_Other.Pointer = nullptr;
		}

		~SharedPointer()
		{
			Release();
		}

		void Release()
		{
			if (Mutex)
			{
				Mutex->lock();

				(*RefCount)--;

				if (*RefCount == 0)
				{
					for (size_t _Index = 0; _Index < WeakPointers->GetSize(); _Index++)
					{
						(*WeakPointers)[_Index]->Mutex = nullptr;
						(*WeakPointers)[_Index]->RefCount = nullptr;
						(*WeakPointers)[_Index]->WeakPointers = nullptr;
						(*WeakPointers)[_Index]->Size = 0;
						(*WeakPointers)[_Index]->Pointer = nullptr;
					}

					Mutex->unlock();

					delete Mutex;
					delete RefCount;
					delete WeakPointers;
					delete[] Pointer;
				}
				else
				{
					Mutex->unlock();
				}
			}

			Mutex = nullptr;
			RefCount = nullptr;
			WeakPointers = nullptr;
			Size = 0;
			Pointer = nullptr;
		}

		const size_t GetSize() const
		{
			return Size;
		}

		Type* GetData() requires (!std::is_const_v<T>)
		{
			return Pointer;
		}

		ConstType* GetData() const
		{
			return Pointer;
		}

		explicit operator Type* () requires (!std::is_const_v<T>)
		{
			return Pointer;
		}

		explicit operator ConstType* () const
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

			Release();

			Mutex = _Other.Mutex;
			RefCount = _Other.RefCount;
			WeakPointers = _Other.WeakPointers;
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

			Release();

			Mutex = _Other.Mutex;
			RefCount = _Other.RefCount;
			WeakPointers = _Other.WeakPointers;
			Size = _Other.Size;
			Pointer = _Other.Pointer;

			_Other.Mutex = nullptr;
			_Other.RefCount = nullptr;
			_Other.WeakPointers = nullptr;
			_Other.Size = 0;
			_Other.Pointer = nullptr;

			return *this;
		}

		static SharedPointer MakeShared(ConstType& _Value = Type())
		{
			SharedPointer _Result;

			_Result.Mutex = new std::mutex;
			_Result.RefCount = new size_t;
			_Result.WeakPointers = new Vector<WeakPointer<T>*>;
			_Result.Size = 1;
			_Result.Pointer = new Type[1];

			if (!_Result.Mutex || !_Result.RefCount || !_Result.WeakPointers || !_Result.Pointer)
			{
				delete _Result.Mutex;
				_Result.Mutex = nullptr;
				delete _Result.RefCount;
				_Result.RefCount = nullptr;
				delete _Result.WeakPointers;
				_Result.WeakPointers = nullptr;
				_Result.Size = 0;
				delete[] _Result.Pointer;
				_Result.Pointer = nullptr;
				throw nullptr;
			}

			*_Result.RefCount = 1;
			*_Result.Pointer = _Value;

			return _Result;
		}

		static SharedPointer MakeShared(Type&& _Value = Type())
		{
			SharedPointer _Result;

			_Result.Mutex = new std::mutex;
			_Result.RefCount = new size_t;
			_Result.WeakPointers = new Vector<WeakPointer<T>*>;
			_Result.Size = 1;
			_Result.Pointer = new Type[1];

			if (!_Result.Mutex || !_Result.RefCount || !_Result.WeakPointers || !_Result.Pointer)
			{
				delete _Result.Mutex;
				_Result.Mutex = nullptr;
				delete _Result.RefCount;
				_Result.RefCount = nullptr;
				delete _Result.WeakPointers;
				_Result.WeakPointers = nullptr;
				_Result.Size = 0;
				delete[] _Result.Pointer;
				_Result.Pointer = nullptr;
				throw nullptr;
			}

			*_Result.RefCount = 1;
			*_Result.Pointer = (Type&&)(_Value);

			return _Result;
		}

		static SharedPointer MakeSharedArray(const std::initializer_list<Type>& _List)
		{
			if (_List.size() == 0)
			{
				throw nullptr;
			}

			SharedPointer _Result;

			_Result.Mutex = new std::mutex;
			_Result.RefCount = new size_t;
			_Result.WeakPointers = new Vector<WeakPointer<T>*>;
			_Result.Size = _List.size();
			_Result.Pointer = new Type[_Result.Size];

			if (!_Result.Mutex || !_Result.RefCount || !_Result.WeakPointers || !_Result.Pointer)
			{
				delete _Result.Mutex;
				_Result.Mutex = nullptr;
				delete _Result.RefCount;
				_Result.RefCount = nullptr;
				delete _Result.WeakPointers;
				_Result.WeakPointers = nullptr;
				_Result.Size = 0;
				delete[] _Result.Pointer;
				_Result.Pointer = nullptr;
				throw nullptr;
			}

			*_Result.RefCount = 1;

			for (size_t _Index = 0; _Index < _Result.Size; _Index++)
			{
				_Result.Pointer[_Index] = *(_List.begin() + _Index);
			}

			return _Result;
		}

		static SharedPointer MakeSharedArray(const size_t _Size)
		{
			if (_Size == 0)
			{
				throw nullptr;
			}

			SharedPointer _Result;

			_Result.Mutex = new std::mutex;
			_Result.RefCount = new size_t;
			_Result.WeakPointers = new Vector<WeakPointer<T>*>;
			_Result.Size = _Size;
			_Result.Pointer = new Type[_Size];

			if (!_Result.Mutex || !_Result.RefCount || !_Result.WeakPointers || !_Result.Pointer)
			{
				delete _Result.Mutex;
				_Result.Mutex = nullptr;
				delete _Result.RefCount;
				_Result.RefCount = nullptr;
				delete _Result.WeakPointers;
				_Result.WeakPointers = nullptr;
				_Result.Size = 0;
				delete[] _Result.Pointer;
				_Result.Pointer = nullptr;
				throw nullptr;
			}

			*_Result.RefCount = 1;

			return _Result;
		}

	private:

		friend WeakPointer<T>;

		std::mutex* Mutex;
		size_t* RefCount;
		Vector<WeakPointer<T>*>* WeakPointers;
		size_t Size;
		Type* Pointer;

	};

	template <typename T> class WeakPointer
	{

	private:

		using Type = std::remove_const_t<T>;
		using ConstType = std::add_const_t<T>;

	public:

		WeakPointer() : Mutex(nullptr), RefCount(nullptr), WeakPointers(nullptr), Size(0), Pointer(nullptr)
		{

		}

		WeakPointer(const SharedPointer<T>& _SharedPointer) noexcept : Mutex(_SharedPointer.Mutex), RefCount(_SharedPointer.RefCount), WeakPointers(_SharedPointer.WeakPointers), Size(_SharedPointer.Size), Pointer(_SharedPointer.Pointer)
		{
			if (Mutex)
			{
				Mutex->lock();
				(*WeakPointers).PushBack(this);
				Mutex->unlock();
			}
		}

		WeakPointer(const WeakPointer& _Other) : Mutex(_Other.Mutex), RefCount(_Other.RefCount), WeakPointers(_Other.WeakPointers), Size(_Other.Size), Pointer(_Other.Pointer)
		{
			if (Mutex)
			{
				Mutex->lock();
				(*WeakPointers).PushBack(this);
				Mutex->unlock();
			}
		}

		WeakPointer(WeakPointer&& _Other) noexcept : Mutex(_Other.Mutex), RefCount(_Other.RefCount), WeakPointers(_Other.WeakPointers), Size(_Other.Size), Pointer(_Other.Pointer)
		{
			if (Mutex)
			{
				Mutex->lock();

				for (size_t _Index = 0; _Index < WeakPointers->GetSize(); _Index++)
				{
					if ((*WeakPointers)[_Index] == &_Other)
					{
						(*WeakPointers)[_Index] = this;
						break;
					}
				}

				Mutex->unlock();
			}

			_Other.Mutex = nullptr;
			_Other.RefCount = nullptr;
			_Other.WeakPointers = nullptr;
			_Other.Size = 0;
			_Other.Pointer = nullptr;
		}

		~WeakPointer()
		{
			Release();
		}

		SharedPointer<T> Lock() requires (!std::is_const_v<T>)
		{
			SharedPointer<T> _Result;

			if (Mutex)
			{
				Mutex->lock();

				_Result.Mutex = Mutex;
				_Result.RefCount = RefCount;
				_Result.WeakPointers = WeakPointers;
				_Result.Size = Size;
				_Result.Pointer = Pointer;

				(*_Result.RefCount)++;

				Mutex->unlock();
			}

			return _Result;
		}

		const SharedPointer<T> Lock() const
		{
			SharedPointer<T> _Result;

			if (Mutex)
			{
				Mutex->lock();

				_Result.Mutex = Mutex;
				_Result.RefCount = RefCount;
				_Result.WeakPointers = WeakPointers;
				_Result.Size = Size;
				_Result.Pointer = Pointer;

				(*_Result.RefCount)++;

				Mutex->unlock();
			}

			return _Result;
		}

		void Release()
		{
			if (Mutex)
			{
				Mutex->lock();

				for (size_t _Index = 0; _Index < (*WeakPointers).GetSize(); _Index++)
				{
					if ((*WeakPointers)[_Index] == this)
					{
						(*WeakPointers).Erase(_Index);
						break;
					}
				}

				Mutex->unlock();
			}

			Mutex = nullptr;
			RefCount = nullptr;
			WeakPointers = nullptr;
			Size = 0;
			Pointer = nullptr;
		}

		WeakPointer& operator= (const SharedPointer<T>& _SharedPointer) noexcept
		{
			Release();

			Mutex = _SharedPointer.Mutex;
			RefCount = _SharedPointer.RefCount;
			WeakPointers = _SharedPointer.WeakPointers;
			Size = _SharedPointer.Size;
			Pointer = _SharedPointer.Pointer;

			if (Mutex)
			{
				Mutex->lock();
				(*WeakPointers).PushBack(this);
				Mutex->unlock();
			}

			return *this;
		}

		WeakPointer& operator= (const WeakPointer& _Other)
		{
			if (this == &_Other)
			{
				return *this;
			}

			Release();

			Mutex = _Other.Mutex;
			RefCount = _Other.RefCount;
			WeakPointers = _Other.WeakPointers;
			Size = _Other.Size;
			Pointer = _Other.Pointer;

			if (Mutex)
			{
				Mutex->lock();
				(*WeakPointers).PushBack(this);
				Mutex->unlock();
			}

			return *this;
		}

		WeakPointer& operator= (WeakPointer&& _Other) noexcept
		{
			if (this == &_Other)
			{
				return *this;
			}

			Release();

			Mutex = _Other.Mutex;
			RefCount = _Other.RefCount;
			WeakPointers = _Other.WeakPointers;
			Size = _Other.Size;
			Pointer = _Other.Pointer;

			if (Mutex)
			{
				Mutex->lock();

				for (size_t _Index = 0; _Index < (*WeakPointers).GetSize(); _Index++)
				{
					if ((*WeakPointers)[_Index] == &_Other)
					{
						(*WeakPointers)[_Index] = this;
						break;
					}
				}

				Mutex->unlock();
			}

			_Other.Mutex = nullptr;
			_Other.RefCount = nullptr;
			_Other.WeakPointers = nullptr;
			_Other.Size = 0;
			_Other.Pointer = nullptr;

			return *this;
		}

	private:

		friend SharedPointer<T>;

		std::mutex* Mutex;
		size_t* RefCount;
		Vector<WeakPointer<T>*>* WeakPointers;
		size_t Size;
		Type* Pointer;

	};

	template <typename T> class SafePointer
	{

	private:

		using Type = std::remove_const_t<T>;
		using ConstType = std::add_const_t<T>;

	public:

		SafePointer() : Pointer(nullptr)
		{

		}

		SafePointer(T* _Pointer) : Pointer(_Pointer)
		{
			if (Pointer)
			{
				Pointer->SafePointers.PushBack(this);
			}
		}

		SafePointer(const SafePointer& _Other) : Pointer(_Other.Pointer)
		{
			if (Pointer)
			{
				Pointer->SafePointers.PushBack(this);
			}
		}

		SafePointer(SafePointer&& _Other) noexcept : Pointer(_Other.Pointer)
		{
			if (Pointer)
			{
				for (size_t _Index = 0; _Index < Pointer->SafePointers.GetSize(); _Index++)
				{
					if (Pointer->SafePointers[_Index] == &_Other)
					{
						Pointer->SafePointers[_Index] = this;
						break;
					}
				}
			}

			_Other.Pointer = nullptr;
		}

		~SafePointer()
		{
			if (Pointer)
			{
				for (size_t _Index = 0; _Index < Pointer->SafePointers.GetSize(); _Index++)
				{
					if (Pointer->SafePointers[_Index] == this)
					{
						Pointer->SafePointers.Erase(_Index);
						break;
					}
				}
			}
		}

		explicit operator Type* () requires (!std::is_const_v<T>)
		{
			return Pointer;
		}

		explicit operator ConstType* () const
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

		SafePointer& operator= (T* _Pointer)
		{
			if (Pointer == _Pointer)
			{
				return *this;
			}

			if (Pointer)
			{
				for (size_t _Index = 0; _Index < Pointer->SafePointers.GetSize(); _Index++)
				{
					if (Pointer->SafePointers[_Index] == this)
					{
						Pointer->SafePointers.Erase(_Index);
						break;
					}
				}
			}

			Pointer = _Pointer;

			if (Pointer)
			{
				Pointer->SafePointers.PushBack(this);
			}

			return *this;
		}

		SafePointer& operator= (const SafePointer& _Other)
		{
			if (this == &_Other)
			{
				return *this;
			}

			if (Pointer)
			{
				for (size_t _Index = 0; _Index < Pointer->SafePointers.GetSize(); _Index++)
				{
					if (Pointer->SafePointers[_Index] == this)
					{
						Pointer->SafePointers.Erase(_Index);
						break;
					}
				}
			}

			Pointer = _Other.Pointer;

			if (Pointer)
			{
				Pointer->SafePointers.PushBack(this);
			}

			return *this;
		}

		SafePointer& operator= (SafePointer&& _Other) noexcept
		{
			if (this == &_Other)
			{
				return *this;
			}

			if (Pointer)
			{
				for (size_t _Index = 0; _Index < Pointer->SafePointers.GetSize(); _Index++)
				{
					if (Pointer->SafePointers[_Index] == this)
					{
						Pointer->SafePointers.Erase(_Index);
						break;
					}
				}
			}

			Pointer = _Other.Pointer;

			if (Pointer)
			{
				for (size_t _Index = 0; _Index < Pointer->SafePointers.GetSize(); _Index++)
				{
					if (Pointer->SafePointers[_Index] == &_Other)
					{
						Pointer->SafePointers[_Index] = this;
						break;
					}
				}
			}

			_Other.Pointer = nullptr;

			return *this;
		}

		static void MoveAll(T* _Pointer, T* _Other) noexcept
		{
			_Pointer->SafePointers = (Vector<SafePointer*>&&)(_Other->SafePointers);

			for (size_t _Index = 0; _Index < _Pointer->SafePointers.GetSize(); _Index++)
			{
				_Pointer->SafePointers[_Index]->Pointer = _Pointer;
			}
		}

		static void ReleaseAll(T* _Pointer)
		{
			for (size_t _Index = 0; _Index < _Pointer->SafePointers.GetSize(); _Index++)
			{
				_Pointer->SafePointers[_Index]->Pointer = nullptr;
			}

			_Pointer->SafePointers.Clear();
		}

	private:

		friend Type;

		T* Pointer;

	};

}



#endif
