#ifndef BFW_Heap_hpp

#define BFW_Heap_hpp



#include "BFW.hpp"



namespace BFW
{

	template <typename T, typename ValueT = float, const bool (*Rule)(const ValueT _Parent, const ValueT _Child) = [](const ValueT _Parent, const ValueT _Child) -> const bool { return _Parent <= _Child; }> requires (!std::is_const_v<ValueT>) class Heap
	{

	private:

		using Type = std::remove_const_t<T>;
		using ConstType = std::add_const_t<T>;

	public:

		Heap() : Objects(), Values()
		{

		}

		Heap(const Heap& _Other) : Objects(_Other.Objects), Values(_Other.Values)
		{

		}

		Heap(Heap&& _Other) noexcept : Objects((Vector<Type>&&)(_Other.Objects)), Values((Vector<ValueT>&&)(_Other.Values))
		{

		}

		~Heap()
		{

		}

		void Push(ConstType& _Object, const ValueT _Value)
		{
			Objects.PushBack(_Object);
			Values.PushBack(_Value);

			size_t _NodeIndex = Objects.GetSize() - 1;

			while (_NodeIndex != 0)
			{
				if (Rule(Values[(_NodeIndex + 1) / 2 - 1], Values[_NodeIndex]))
				{
					break;
				}

				Type _Aux = (Type&&)(Objects[_NodeIndex]);
				ValueT _AuxVal = Values[_NodeIndex];

				Objects[_NodeIndex] = (Type&&)(Objects[(_NodeIndex + 1) / 2 - 1]);
				Values[_NodeIndex] = Values[(_NodeIndex + 1) / 2 - 1];

				Objects[(_NodeIndex + 1) / 2 - 1] = (Type&&)(_Aux);
				Values[(_NodeIndex + 1) / 2 - 1] = _AuxVal;

				_NodeIndex = (_NodeIndex + 1) / 2 - 1;
			}
		}

		void Emplace(Type&& _Object, const ValueT _Value)
		{
			Objects.EmplaceBack((Type&&)(_Object));
			Values.PushBack(_Value);

			size_t _NodeIndex = Objects.GetSize() - 1;

			while (_NodeIndex != 0)
			{
				if (Rule(Values[(_NodeIndex + 1) / 2 - 1], Values[_NodeIndex]))
				{
					break;
				}

				Type _Aux = (Type&&)(Objects[_NodeIndex]);
				ValueT _AuxVal = Values[_NodeIndex];

				Objects[_NodeIndex] = (Type&&)(Objects[(_NodeIndex + 1) / 2 - 1]);
				Values[_NodeIndex] = Values[(_NodeIndex + 1) / 2 - 1];

				Objects[(_NodeIndex + 1) / 2 - 1] = (Type&&)(_Aux);
				Values[(_NodeIndex + 1) / 2 - 1] = _AuxVal;

				_NodeIndex = (_NodeIndex + 1) / 2 - 1;
			}
		}

		T Pop()
		{
			if (!Objects.GetSize())
			{
				throw nullptr;
			}

			Type _Result = (Type&&)(Objects[0]);

			Objects[0] = (Type&&)(Objects[Objects.GetSize() - 1]);
			Values[0] = Values[Values.GetSize() - 1];

			Objects.Erase(Objects.GetSize() - 1);
			Values.Erase(Values.GetSize() - 1);

			size_t _NodeIndex = 0;
			size_t _Left = (_NodeIndex + 1) * 2 - 1;
			size_t _Right = (_NodeIndex + 1) * 2;

			while (_Left < Values.GetSize())
			{
				size_t _BestIndex = _Left;

				if (_Right < Values.GetSize() && Rule(Values[_Right], Values[_Left]))
				{
					_BestIndex = _Right;
				}

				if (Rule(Values[_NodeIndex], Values[_BestIndex]))
				{
					break;
				}

				Type _Aux = (Type&&)(Objects[_NodeIndex]);
				ValueT _AuxVal = Values[_NodeIndex];

				Objects[_NodeIndex] = (Type&&)(Objects[_BestIndex]);
				Values[_NodeIndex] = Values[_BestIndex];

				Objects[_BestIndex] = (Type&&)(_Aux);
				Values[_BestIndex] = _AuxVal;

				_NodeIndex = _BestIndex;
				_Left = (_NodeIndex + 1) * 2 - 1;
				_Right = (_NodeIndex + 1) * 2;
			}

			return _Result;
		}

		Type& Peek() requires (!std::is_const_v<T>)
		{
			return Objects[0];
		}

		ConstType& Peek() const
		{
			return Objects[0];
		}

		const size_t GetSize() const
		{
			return Objects.GetSize();
		}

		Heap& operator= (const Heap& _Other)
		{
			if (this == &_Other)
			{
				return *this;
			}

			Objects = _Other.Objects;
			Values = _Other.Values;

			return *this;
		}

		Heap& operator= (Heap&& _Other) noexcept
		{
			if (this == &_Other)
			{
				return *this;
			}

			Objects = (Vector<Type>&&)(_Other.Objects);
			Values = (Vector<ValueT>&&)(_Other.Values);

			return *this;
		}

	private:

		Vector<Type> Objects;
		Vector<ValueT> Values;

	};

}



#endif
