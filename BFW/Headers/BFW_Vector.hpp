#ifndef BFW_Vector_hpp

#define BFW_Vector_hpp



#include "BFW.hpp"



namespace BFW
{

	template <typename T> class Vector
	{

	private:

		using Type = std::remove_const_t<T>;
		using ConstType = std::add_const_t<T>;

	public:

		Vector() : Size(0), Capacity(0), Data(nullptr)
		{

		}

		Vector(const Vector& _Other) : Size(0), Capacity(0), Data(nullptr)
		{
			if (_Other.Capacity == 0)
			{
				return;
			}

			Size = _Other.Size;
			Capacity = _Other.Capacity;
			Data = new Type[Capacity];

			if (!Data)
			{
				Size = 0;
				Capacity = 0;
				throw nullptr;
			}

			for (size_t _Index = 0; _Index < Capacity; _Index++)
			{
				Data[_Index] = _Other[_Index];
			}
		}

		Vector(Vector&& _Other) noexcept : Size(_Other.Size), Capacity(_Other.Capacity), Data(_Other.Data)
		{
			_Other.Size = 0;
			_Other.Capacity = 0;
			_Other.Data = nullptr;
		}

		Vector(const std::initializer_list<Type>& _List) : Size(0), Capacity(0), Data(nullptr)
		{
			if (_List.size() == 0)
			{
				return;
			}

			Size = _List.size();
			Capacity = _List.size();
			Data = new Type[Capacity];

			if (!Data)
			{
				Size = 0;
				Capacity = 0;
				throw nullptr;
			}

			for (size_t _Index = 0; _Index < Capacity; _Index++)
			{
				Data[_Index] = *(_List.begin() + _Index);
			}
		}

		~Vector()
		{
			delete[] Data;
		}

		void PushBack(const ConstType& _Object)
		{
			if (Size == 0)
			{
				Data = new Type[1];

				if (!Data)
				{
					throw nullptr;
				}

				Size = 1;
				Capacity = 1;
				Data[0] = _Object;

				return;
			}

			if (Size + 1 > Capacity)
			{
				Size++;
				Capacity *= 2;

				Type* _NewData = new Type[Capacity];

				if (!_NewData)
				{
					Size--;
					Capacity /= 2;
					throw nullptr;
				}

				for (size_t _Index = 0; _Index < Size - 1; _Index++)
				{
					_NewData[_Index] = (Type&&)(Data[_Index]);
				}

				delete[] Data;
				Data = _NewData;

				_NewData[Size - 1] = _Object;

				return;
			}

			Size++;
			Data[Size - 1] = _Object;
		}

		void EmplaceBack(Type&& _Object)
		{
			if (Size == 0)
			{
				Data = new Type[1];

				if (!Data)
				{
					throw nullptr;
				}

				Size = 1;
				Capacity = 1;
				Data[0] = (Type&&)(_Object);

				return;
			}

			if (Size + 1 > Capacity)
			{
				Size++;
				Capacity *= 2;

				Type* _NewData = new Type[Capacity];

				if (!_NewData)
				{
					Size--;
					Capacity /= 2;
					throw nullptr;
				}

				for (size_t _Index = 0; _Index < Size - 1; _Index++)
				{
					_NewData[_Index] = (Type&&)(Data[_Index]);
				}

				delete[] Data;
				Data = _NewData;

				_NewData[Size - 1] = (Type&&)(_Object);

				return;
			}

			Size++;
			Data[Size - 1] = (Type&&)(_Object);
		}

		void Erase(const size_t _EraseIndex)
		{
			if (Size == 0 || _EraseIndex >= Size)
			{
				throw nullptr;
			}

			if (Size - 1 == 0)
			{
				Clear();
				return;
			}

			if (Size - 1 == Capacity / 2)
			{
				Size--;
				Capacity /= 2;

				Type* _NewData = new Type[Capacity];

				if (!_NewData)
				{
					Size++;
					Capacity *= 2;
					throw nullptr;
				}

				for (size_t _Index = 0; _Index < Capacity; _Index++)
				{
					_NewData[_Index] = (Type&&)(Data[_Index + (size_t)(_Index >= _EraseIndex)]);
				}

				delete[] Data;
				Data = _NewData;

				return;
			}

			Size--;

			for (size_t _Index = _EraseIndex; _Index < Size; _Index++)
			{
				Data[_Index] = (Type&&)(Data[_Index + 1]);
			}

			if (_EraseIndex == Size)
			{
				Data[Size] = Type();
			}
		}

		void Clear()
		{
			Size = 0;
			Capacity = 0;
			delete[] Data;
			Data = nullptr;
		}

		const size_t GetSize() const
		{
			return Size;
		}

		const size_t GetCapacity() const
		{
			return Capacity;
		}

		Type* GetData() requires (!std::is_const_v<T>)
		{
			return Data;
		}

		ConstType* GetData() const
		{
			return Data;
		}

		explicit operator Type* () requires (!std::is_const_v<T>)
		{
			return Data;
		}

		explicit operator ConstType* () const
		{
			return Data;
		}

		Type* operator-> () requires (!std::is_const_v<T>)
		{
			return Data;
		}

		ConstType* operator-> () const
		{
			return Data;
		}

		Type& operator* () requires (!std::is_const_v<T>)
		{
			return *Data;
		}

		ConstType& operator* () const
		{
			return *Data;
		}

		Type& operator[] (const size_t _Index) requires (!std::is_const_v<T>)
		{
			return Data[_Index];
		}

		ConstType& operator[] (const size_t _Index) const
		{
			return Data[_Index];
		}

		Vector& operator= (const Vector& _Other)
		{
			if (this == &_Other)
			{
				return *this;
			}

			Size = 0;
			Capacity = 0;
			delete[] Data;
			Data = nullptr;

			if (_Other.Capacity == 0)
			{
				return *this;
			}

			Size = _Other.Size;
			Capacity = _Other.Capacity;
			Data = new Type[Capacity];

			if (!Data)
			{
				Size = 0;
				Capacity = 0;
				throw nullptr;
			}

			for (size_t _Index = 0; _Index < Capacity; _Index++)
			{
				Data[_Index] = _Other[_Index];
			}

			return *this;
		}

		Vector& operator= (Vector&& _Other) noexcept
		{
			if (this == &_Other)
			{
				return *this;
			}

			delete[] Data;

			Size = _Other.Size;
			Capacity = _Other.Capacity;
			Data = _Other.Data;

			_Other.Size = 0;
			_Other.Capacity = 0;
			_Other.Data = nullptr;

			return *this;
		}

		Vector& operator= (const std::initializer_list<Type>& _List)
		{
			Clear();

			if (_List.size() == 0)
			{
				return *this;
			}

			Size = _List.size();
			Capacity = _List.size();
			Data = new Type[Capacity];

			if (!Data)
			{
				Size = 0;
				Capacity = 0;
				throw nullptr;
			}

			for (size_t _Index = 0; _Index < Capacity; _Index++)
			{
				Data[_Index] = *(_List.begin() + _Index);
			}

			return *this;
		}

	private:

		size_t Size;
		size_t Capacity;
		Type* Data;

	};

}



#endif
