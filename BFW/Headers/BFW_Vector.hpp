#ifndef BFW_Vector_hpp

#define BFW_Vector_hpp



namespace BFW
{

	template <typename T> class Vector
	{

	public:

		Vector() : Size(0), Capacity(0), Vec(nullptr)
		{

		}

		Vector(const Vector& _Other) : Size(0), Capacity(0), Vec(nullptr)
		{
			if (!_Other.Capacity)
			{
				return;
			}

			Vec = (T*)(malloc(_Other.Capacity * sizeof(T)));

			if (!Vec)
			{
				return;
			}

			for (unsigned long _Index = 0; _Index < _Other.Size; _Index++)
			{
				Vec[_Index] = ((const T&)(_Other.Vec[_Index]));
			}

			Capacity = _Other.Capacity;
			Size = _Other.Size;
		}

		Vector(Vector&& _Other) noexcept : Size(_Other.Size), Capacity(_Other.Capacity), Vec(_Other.Vec)
		{
			_Other.Size = 0;
			_Other.Capacity = 0;
			_Other.Vec = nullptr;
		}

		virtual ~Vector()
		{
			if (Capacity)
			{
				for (unsigned long _Index = 0; _Index < Size; _Index++)
				{
					((T*)(&Vec[_Index]))->~T();
				}
				Size = 0;
				Capacity = 0;
				free((void*)(Vec));
				Vec = nullptr;
			}
		}

		void PushBack(const T& _Obj)
		{
			if (Size + 1 <= Capacity)
			{
				Vec[Size] = ((const T&)(_Obj));
				Size++;
				return;
			}

			unsigned long _Size = Size + 1;
			unsigned long _Capacity = GetResize(_Size);

			if (_Capacity < _Size)
			{
				return;
			}

			T* _Vec = (T*)(malloc(_Capacity * sizeof(T)));

			if (!_Vec)
			{
				return;
			}

			_Vec[_Size - 1] = ((const T&)(_Obj));

			MoveAll(_Vec);

			if (Capacity)
			{
				for (unsigned long _Index = 0; _Index < Size; _Index++)
				{
					((T*)(&Vec[_Index]))->~T();
				}
				Size = 0;
				Capacity = 0;
				free((void*)(Vec));
				Vec = nullptr;
			}

			Vec = _Vec;
			Capacity = _Capacity;
			Size = _Size;
		}

		void MoveBack(T&& _Obj) noexcept
		{
			if (Size + 1 <= Capacity)
			{
				Vec[Size] = ((T&&)(_Obj));
				Size++;
				return;
			}

			unsigned long _Size = Size + 1;
			unsigned long _Capacity = GetResize(_Size);

			if (_Capacity < _Size)
			{
				return;
			}

			T* _Vec = (T*)(malloc(_Capacity * sizeof(T)));

			if (!_Vec)
			{
				return;
			}

			_Vec[_Size - 1] = ((T&&)(_Obj));

			MoveAll(_Vec);

			if (Capacity)
			{
				for (unsigned long _Index = 0; _Index < Size; _Index++)
				{
					((T*)(&Vec[_Index]))->~T();
				}
				Size = 0;
				Capacity = 0;
				free((void*)(Vec));
				Vec = nullptr;
			}

			Vec = _Vec;
			Capacity = _Capacity;
			Size = _Size;
		}

		void Erase(const unsigned long _Index)
		{
			if (_Index >= Size)
			{
				return;
			}

			unsigned long _Capacity = GetResize(Size - 1);

			if (!_Capacity)
			{
				if (Capacity)
				{
					for (unsigned long _Index = 0; _Index < Size; _Index++)
					{
						((T*)(&Vec[_Index]))->~T();
					}
					Size = 0;
					Capacity = 0;
					free((void*)(Vec));
					Vec = nullptr;
				}
				return;
			}

			if (_Capacity == Capacity)
			{
				Size--;
				((T*)(&Vec[_Index]))->~T();
				return;
			}

			unsigned long _Size = Size - 1;

			if (_Capacity < _Size)
			{
				return;
			}

			T* _Vec = (T*)(malloc(_Capacity * sizeof(T)));

			if (!_Vec)
			{
				return;
			}

			for (unsigned long _MoveIndex = 0; _MoveIndex < _Index; _MoveIndex++)
			{
				_Vec[_MoveIndex] = ((T&&)(Vec[_MoveIndex]));
			}

			for (unsigned long _MoveIndex = _Index; _MoveIndex < _Size; _MoveIndex++)
			{
				_Vec[_MoveIndex] = ((T&&)(Vec[_MoveIndex + 1]));
			}

			if (Capacity)
			{
				for (unsigned long _DeleteIndex = 0; _DeleteIndex < Size; _DeleteIndex++)
				{
					((T*)(&Vec[_DeleteIndex]))->~T();
				}
				Size = 0;
				Capacity = 0;
				free((void*)(Vec));
				Vec = nullptr;
			}

			Vec = _Vec;
			Capacity = _Capacity;
			Size = _Size;
		}

		void Clear()
		{
			if (Capacity)
			{
				for (unsigned long _Index = 0; _Index < Size; _Index++)
				{
					((T*)(&Vec[_Index]))->~T();
				}
				Size = 0;
				Capacity = 0;
				free((void*)(Vec));
				Vec = nullptr;
			}
		}

		const unsigned long GetSize() const
		{
			return Size;
		}

		const unsigned long GetCapacity() const
		{
			return Capacity;
		}

		T* Data()
		{
			return Vec;
		}

		const T* Data() const
		{
			return Vec;
		}

		operator T* ()
		{
			return Vec;
		}

		operator const T* () const
		{
			return Vec;
		}

		T* operator-> ()
		{
			return Vec;
		}

		const T* operator-> () const
		{
			return Vec;
		}

		T& operator* ()
		{
			return *Vec;
		}

		const T& operator* () const
		{
			return *Vec;
		}

		T& operator[] (unsigned long _Index)
		{
			return Vec[_Index];
		}

		const T& operator[] (unsigned long _Index) const
		{
			return Vec[_Index];
		}

		void operator= (const Vector& _Other)
		{
			if (Capacity)
			{
				for (unsigned long _Index = 0; _Index < Size; _Index++)
				{
					((T*)(&Vec[_Index]))->~T();
				}
				Size = 0;
				Capacity = 0;
				free((void*)(Vec));
				Vec = nullptr;
			}

			if (!_Other.Capacity)
			{
				return;
			}

			Vec = (T*)(malloc(_Other.Capacity * sizeof(T)));

			if (!Vec)
			{
				return;
			}

			for (unsigned long _Index = 0; _Index < _Other.Size; _Index++)
			{
				Vec[_Index] = ((const T&)(_Other.Vec[_Index]));
			}

			Capacity = _Other.Capacity;
			Size = _Other.Size;
		}

		void operator= (Vector&& _Other) noexcept
		{
			Vec = _Other.Vec;
			Capacity = _Other.Capacity;
			Size = _Other.Size;

			_Other.Size = 0;
			_Other.Capacity = 0;
			_Other.Vec = nullptr;
		}

	protected:

		unsigned long Size;
		unsigned long Capacity;
		T* Vec;

		virtual const unsigned long GetResize(const unsigned long _Size) const
		{
			if (!_Size)
			{
				return 0;
			}

			unsigned long _Capacity = 1;

			while (_Capacity < _Size)
			{
				_Capacity *= 2;
			}

			return _Capacity;
		}

	private:

		void MoveAll(T* _Vec)
		{
			if (!_Vec)
			{
				return;
			}
			for (unsigned long _Index = 0; _Index < Size; _Index++)
			{
				_Vec[_Index] = ((T&&)(Vec[_Index]));
			}
		}

	};

}



#endif
