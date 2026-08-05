#ifndef BFW_Trie_hpp

#define BFW_Trie_hpp



#include "BFW.hpp"



namespace BFW
{

	template <typename T, typename CharT = BFW_CHAR_TYPE> requires (!std::is_const_v<CharT>) class Trie
	{

	private:

		using Type = std::remove_const_t<T>;
		using ConstType = std::add_const_t<T>;

	public:

		Trie() : Id((CharT)('\0')), Data(), Childs()
		{

		}

		Trie(const Trie& _Other) : Id(_Other.Id), Data(_Other.Data), Childs(_Other.Childs)
		{

		}

		Trie(Trie&& _Other) noexcept : Id(_Other.Id), Data((UniquePointer<Type>&&)(_Other.Data)), Childs((Vector<Trie>&&)(_Other.Childs))
		{
			_Other.Id = (CharT)('\0');
		}

		~Trie()
		{

		}

		void Push(const CharT* _Name, ConstType& _Data)
		{
			if (!_Name)
			{
				throw nullptr;
			}

			if (_Name[0] == (CharT)('\0'))
			{
				Data = UniquePointer<Type>::MakeUnique(_Data);
				return;
			}

			Trie* _Child = nullptr;

			for (size_t _Index = 0; _Index < Childs.GetSize(); _Index++)
			{
				if (_Name[0] == Childs[_Index].Id)
				{
					_Child = &Childs[_Index];
					break;
				}
			}

			if (_Child == nullptr)
			{
				Childs.PushBack(Trie());
				_Child = &Childs[Childs.GetSize() - 1];
				_Child->Id = _Name[0];
			}

			_Child->Push(_Name + 1, _Data);
		}

		void Push(const CharT* _Name, const size_t _Length, ConstType& _Data)
		{
			if (!_Name)
			{
				throw nullptr;
			}

			if (_Length == 0)
			{
				Data = UniquePointer<Type>::MakeUnique(_Data);
				return;
			}

			Trie* _Child = nullptr;

			for (size_t _Index = 0; _Index < Childs.GetSize(); _Index++)
			{
				if (_Name[0] == Childs[_Index].Id)
				{
					_Child = &Childs[_Index];
					break;
				}
			}

			if (_Child == nullptr)
			{
				Childs.PushBack(Trie());
				_Child = &Childs[Childs.GetSize() - 1];
				_Child->Id = _Name[0];
			}

			_Child->Push(_Name + 1, _Length - 1, _Data);
		}

		void Emplace(const CharT* _Name, Type&& _Data)
		{
			if (!_Name)
			{
				throw nullptr;
			}

			if (_Name[0] == (CharT)('\0'))
			{
				Data = UniquePointer<Type>::MakeUnique((Type&&)(_Data));
				return;
			}

			Trie* _Child = nullptr;

			for (size_t _Index = 0; _Index < Childs.GetSize(); _Index++)
			{
				if (_Name[0] == Childs[_Index].Id)
				{
					_Child = &Childs[_Index];
					break;
				}
			}

			if (_Child == nullptr)
			{
				Childs.PushBack(Trie());
				_Child = &Childs[Childs.GetSize() - 1];
				_Child->Id = _Name[0];
			}

			_Child->Emplace(_Name + 1, (Type&&)(_Data));
		}

		void Emplace(const CharT* _Name, const size_t _Length, Type&& _Data)
		{
			if (!_Name)
			{
				throw nullptr;
			}

			if (_Length == 0)
			{
				Data = UniquePointer<Type>::MakeUnique((Type&&)(_Data));
				return;
			}

			Trie* _Child = nullptr;

			for (size_t _Index = 0; _Index < Childs.GetSize(); _Index++)
			{
				if (_Name[0] == Childs[_Index].Id)
				{
					_Child = &Childs[_Index];
					break;
				}
			}

			if (_Child == nullptr)
			{
				Childs.PushBack(Trie());
				_Child = &Childs[Childs.GetSize() - 1];
				_Child->Id = _Name[0];
			}

			_Child->Emplace(_Name + 1, _Length - 1, (Type&&)(_Data));
		}

		void Erase(const CharT* _Name)
		{
			if (!_Name)
			{
				throw nullptr;
			}

			if (_Name[0] == (CharT)('\0'))
			{
				Data = UniquePointer<Type>();
				return;
			}

			for (size_t _Index = 0; _Index < Childs.GetSize(); _Index++)
			{
				if (_Name[0] == Childs[_Index].Id)
				{
					Childs[_Index].Erase(_Name + 1);

					if ((Type*)(Childs[_Index].Data) == nullptr && Childs[_Index].Childs.GetSize() == 0)
					{
						Childs.Erase(_Index);
					}

					return;
				}
			}
		}

		void Clear()
		{
			Id = (CharT)('\0');
			Data = UniquePointer<Type>();
			Childs.Clear();
		}

		Type* GetData(const CharT* _Name) requires (!std::is_const_v<T>)
		{
			if (!_Name)
			{
				throw nullptr;
			}

			if (_Name[0] != (CharT)('\0'))
			{
				for (size_t _Index = 0; _Index < Childs.GetSize(); _Index++)
				{
					if (_Name[0] == Childs[_Index].Id)
					{
						return Childs[_Index].GetData(_Name + 1);
					}
				}
			}

			if ((Type*)(Data) == nullptr)
			{
				return nullptr;
			}

			return Data.GetData();
		}

		ConstType* GetData(const CharT* _Name) const
		{
			if (!_Name)
			{
				throw nullptr;
			}

			if (_Name[0] != (CharT)('\0'))
			{
				for (size_t _Index = 0; _Index < Childs.GetSize(); _Index++)
				{
					if (_Name[0] == Childs[_Index].Id)
					{
						return Childs[_Index].GetData(_Name + 1);
					}
				}
			}

			if ((ConstType*)(Data) == nullptr)
			{
				return nullptr;
			}

			return Data.GetData();
		}

		Trie& operator= (const Trie& _Other)
		{
			if (this == &_Other)
			{
				return *this;
			}

			Id = _Other.Id;
			Data = _Other.Data;
			Childs = _Other.Childs;

			return *this;
		}

		Trie& operator= (Trie&& _Other) noexcept
		{
			if (this == &_Other)
			{
				return *this;
			}

			Id = _Other.Id;
			Data = (UniquePointer<Type>&&)(_Other.Data);
			Childs = (Vector<Trie>&&)(_Other.Childs);

			_Other.Id = (CharT)('\0');

			return *this;
		}

	private:

		CharT Id;
		UniquePointer<Type> Data;
		Vector<Trie> Childs;

	};

}



#endif
