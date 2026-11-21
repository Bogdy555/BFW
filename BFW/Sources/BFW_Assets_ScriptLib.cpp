#include "../Headers/BFW.hpp"



static const bool ScriptLibLoadPath(const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _CurrentPath, BFW_STRING_TYPE& _Name)
{
	bool _IsAbsolute = std::filesystem::path(_Name).is_absolute();

	if (_Path != nullptr && _CurrentPath != nullptr && !_IsAbsolute)
	{
		try
		{
			_Name =
				std::filesystem::relative
				(
					std::filesystem::weakly_canonical((std::filesystem::absolute(_Path).parent_path() / _Name).lexically_normal()),
					std::filesystem::weakly_canonical(std::filesystem::absolute(_CurrentPath).lexically_normal())
				);
		}
		catch (...)
		{
			return false;
		}
	}

	for (size_t _Index = 0; _Index < _Name.size(); _Index++)
	{
		if (_Name[_Index] == BFW_STRING_PREFIX('\\'))
		{
			_Name[_Index] = BFW_STRING_PREFIX('/');
		}
	}

	if (!_IsAbsolute && !_Name.starts_with(BFW_STRING_PREFIX("./")) && !_Name.starts_with(BFW_STRING_PREFIX("../")))
	{
		if (_Name == BFW_STRING_PREFIX("."))
		{
			_Name = BFW_STRING_PREFIX("./");
		}
		else if (_Name == BFW_STRING_PREFIX(".."))
		{
			_Name = BFW_STRING_PREFIX("../");
		}
		else if (_Name.starts_with(BFW_STRING_PREFIX("/")))
		{
			_Name = BFW_STRING_PREFIX('.') + _Name;
		}
		else
		{
			_Name = BFW_STRING_PREFIX("./") + _Name;
		}
	}

	if (_Path != nullptr && _CurrentPath != nullptr && !_IsAbsolute)
	{
		try
		{
			BFW_STRING_TYPE _TruePath = std::filesystem::weakly_canonical((std::filesystem::absolute(_CurrentPath) / _Name).lexically_normal());

			if (std::filesystem::exists(_TruePath) && !std::filesystem::is_regular_file(_TruePath))
			{
				return false;
			}
		}
		catch (...)
		{
			return false;
		}
	}
	else
	{
		try
		{
			if (std::filesystem::exists(_Name) && !std::filesystem::is_regular_file(_Name))
			{
				return false;
			}
		}
		catch (...)
		{
			return false;
		}
	}

	return true;
}



#ifdef BFW_WINDOWS_PLATFORM

BFW::Assets::ScriptLib::ScriptLib() : Lib(BFW_STRING_PREFIX("")), Names(), Cache(), Handle(NULL)
{

}

BFW::Assets::ScriptLib::ScriptLib(const ScriptLib& _Other) : Lib(_Other.Lib), Names(_Other.Names), Cache(), Handle(NULL)
{
	if (_Other.Handle && !Start())
	{
		throw nullptr;
	}
}

BFW::Assets::ScriptLib::ScriptLib(ScriptLib&& _Other) noexcept : Lib(_Other.Lib), Names((Vector<BFW_STRING_TYPE>&&)(_Other.Names)), Cache((Trie<Trie<void*>>&&)(_Other.Cache)), Handle(_Other.Handle)
{
	_Other.Lib = BFW_STRING_PREFIX("");
	_Other.Handle = NULL;
}

#endif

#ifdef BFW_LINUX_PLATFORM

BFW::Assets::ScriptLib::ScriptLib() : Lib(BFW_STRING_PREFIX("")), Names(), Cache(), Handle(nullptr)
{

}

BFW::Assets::ScriptLib::ScriptLib(const ScriptLib& _Other) : Lib(_Other.Lib), Names(_Other.Names), Cache(), Handle(nullptr)
{
	if (_Other.Handle && !Start())
	{
		throw nullptr;
	}
}

BFW::Assets::ScriptLib::ScriptLib(ScriptLib&& _Other) noexcept : Lib(_Other.Lib), Names((Vector<BFW_STRING_TYPE>&&)(_Other.Names)), Cache((Trie<Trie<void*>>&&)(_Other.Cache)), Handle(_Other.Handle)
{
	_Other.Lib = BFW_STRING_PREFIX("");
	_Other.Handle = nullptr;
}

#endif

#ifdef BFW_ESP32_PLATFORM

BFW::Assets::ScriptLib::ScriptLib() : Lib(BFW_STRING_PREFIX("")), Names(), Cache(), Handle()
{

}

BFW::Assets::ScriptLib::ScriptLib(const ScriptLib& _Other) : Lib(_Other.Lib), Names(_Other.Names), Cache(_Other.Cache), Handle(_Other.Handle)
{

}

BFW::Assets::ScriptLib::ScriptLib(ScriptLib&& _Other) noexcept : Lib(_Other.Lib), Names((Vector<BFW_STRING_TYPE>&&)(_Other.Names)), Cache((Trie<Trie<void*>>&&)(_Other.Cache)), Handle((Trie<void*>&&)(_Other.Handle))
{
	_Other.Lib = BFW_STRING_PREFIX("");
}

#endif

BFW::Assets::ScriptLib::~ScriptLib()
{
	Stop();
}

const bool BFW::Assets::ScriptLib::Load(const FileContent& _FileContent, const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _CurrentPath)
{
	Lib = BFW_STRING_PREFIX("");
	Names = Vector<BFW_STRING_TYPE>();
	Stop();

	if (_Path != nullptr && _CurrentPath != nullptr && ((std::filesystem::exists(_Path) && !std::filesystem::is_regular_file(_Path)) || !std::filesystem::is_directory(_CurrentPath)))
	{
		return false;
	}

	Json _Config;

	if (!_Config.Load(_FileContent) || _Config.GetType() != _ObjectJsonType)
	{
		return false;
	}

	JsonObjectData& _ObjectData = _Config.GetObjectData();

	if (_ObjectData.Tags.GetSize() != 2 ||
		_ObjectData.Tags[0] != "Lib" ||
		_ObjectData.Tags[1] != "Names" ||
		_ObjectData.Object.GetSize() != 2 ||
		_ObjectData.Object[0].GetType() != _StringJsonType ||
		_ObjectData.Object[1].GetType() != _ArrayJsonType)
	{
		return false;
	}

	Vector<BFW_STRING_TYPE> _Names;

	for (size_t _Index = 0; _Index < _ObjectData.Object[1].GetArray().GetSize(); _Index++)
	{
		if (_ObjectData.Object[1].GetArray()[_Index].GetType() != _StringJsonType)
		{
			return false;
		}

		bool _Error = false;

		_Names.PushBack(BFW_UTF8_TO_MACHINE(_ObjectData.Object[1].GetArray()[_Index].GetString(), &_Error));

		if (_Error)
		{
			return false;
		}

		for (size_t _CheckIndex = 0; _CheckIndex < _Names.GetSize() - 1; _CheckIndex++)
		{
			if (_Names[_CheckIndex] == _Names[_Names.GetSize() - 1])
			{
				_Names.Erase(_Names.GetSize() - 1);
				break;
			}
		}
	}

	bool _Error = false;

	Lib = BFW_UTF8_TO_MACHINE(_ObjectData.Object[0].GetString(), &_Error);

	if (_Error)
	{
		return false;
	}

	if (!ScriptLibLoadPath(_Path, _CurrentPath, Lib))
	{
		Lib = BFW_STRING_PREFIX("");
		return false;
	}

	Names = _Names;

	return true;
}

const bool BFW::Assets::ScriptLib::Start()
{
	Stop();

#ifdef BFW_WINDOWS_PLATFORM

	Handle = LoadLibrary(Lib.c_str());

	if (!Handle)
	{
		return false;
	}

#endif

#ifdef BFW_LINUX_PLATFORM

	Handle = dlopen(BFW_MACHINE_TO_UTF8(Lib, nullptr).c_str(), RTLD_LAZY);

	if (!Handle)
	{
		return false;
	}

#endif

#ifdef BFW_ESP32_PLATFORM

	Handle = BFW::MultiProcessing::LoadLibrary(Lib.c_str());

#endif

	for (size_t _Index = 0; _Index < Names.GetSize(); _Index++)
	{
		bool _Found = false;

		for (size_t _Index2 = 0; _Index2 < _Index; _Index2++)
		{
			if (Names[_Index] == Names[_Index2])
			{
				_Found = true;
				break;
			}
		}

		if (_Found)
		{
			continue;
		}

		Trie<void*>& _Cache = Cache.Emplace(Names[_Index].c_str(), Trie<void*>());

#ifdef BFW_WINDOWS_PLATFORM

		void* (*Get)(HMODULE _Handle, const BFW_STRING_TYPE& _Symbol) = [](HMODULE _Handle, const BFW_STRING_TYPE& _Symbol) -> void*
			{
				bool _Error = false;

				void* _Result = GetProcAddress(_Handle, BFW_MACHINE_TO_UTF8(_Symbol, &_Error).c_str());

				if (_Error)
				{
					return nullptr;
				}

				return _Result;
			};

#endif

#ifdef BFW_LINUX_PLATFORM

		void* (*Get)(void* _Handle, const BFW_STRING_TYPE& _Symbol) = [](void* _Handle, const BFW_STRING_TYPE& _Symbol) -> void*
			{
				bool _Error = false;

				void* _Result = dlsym(_Handle, BFW_MACHINE_TO_UTF8(_Symbol, &_Error).c_str());

				if (_Error)
				{
					return nullptr;
				}

				return _Result;
			};

#endif

#ifdef BFW_ESP32_PLATFORM

		void* (*Get)(Trie<void*>& _Handle, const BFW_STRING_TYPE& _Symbol) = [](Trie<void*>& _Handle, const BFW_STRING_TYPE& _Symbol) -> void*
			{
				void** _Result = _Handle.GetData(_Symbol.c_str());

				if (!_Result)
				{
					return nullptr;
				}

				return *_Result;
			};

#endif

		_Cache.Push(BFW_STRING_PREFIX("OnSetup"), Get(Handle, Names[_Index] + BFW_STRING_PREFIX("::OnSetup")));
		_Cache.Push(BFW_STRING_PREFIX("OnUpdate"), Get(Handle, Names[_Index] + BFW_STRING_PREFIX("::OnUpdate")));
		_Cache.Push(BFW_STRING_PREFIX("OnLateUpdate"), Get(Handle, Names[_Index] + BFW_STRING_PREFIX("::OnLateUpdate")));
		_Cache.Push(BFW_STRING_PREFIX("OnFixedUpdate"), Get(Handle, Names[_Index] + BFW_STRING_PREFIX("::OnFixedUpdate")));
		_Cache.Push(BFW_STRING_PREFIX("OnRender"), Get(Handle, Names[_Index] + BFW_STRING_PREFIX("::OnRender")));
		_Cache.Push(BFW_STRING_PREFIX("OnStop"), Get(Handle, Names[_Index] + BFW_STRING_PREFIX("::OnStop")));
	}

	return true;
}

void BFW::Assets::ScriptLib::Stop()
{
#ifdef BFW_WINDOWS_PLATFORM

	if (!Handle)
	{
		return;
	}

	Cache = Trie<Trie<void*>>();
	FreeLibrary(Handle);
	Handle = NULL;

#endif

#ifdef BFW_LINUX_PLATFORM

	if (!Handle)
	{
		return;
	}

	Cache = Trie<Trie<void*>>();
	dlclose(Handle);
	Handle = nullptr;

#endif

#ifdef BFW_ESP32_PLATFORM

	Cache = Trie<Trie<void*>>();
	Handle = Trie<void*>();

#endif
}

void BFW::Assets::ScriptLib::SetLib(const BFW_STRING_VIEW_TYPE& _Lib)
{
	Stop();
	Lib = _Lib;
}

void BFW::Assets::ScriptLib::SetNames(const Vector<BFW_STRING_TYPE>& _Names)
{
	Stop();
	Names = _Names;
}

const BFW::Assets::FileContent BFW::Assets::ScriptLib::Save() const
{
	Json _Config;

	_Config.SetObject();

	bool _Error = false;

	_Config.GetObjectData().Tags.PushBack("Lib");
	_Config.GetObjectData().Object.EmplaceBack(Json()).SetString(BFW_MACHINE_TO_UTF8(Lib, &_Error));

	if (_Error)
	{
		return FileContent();
	}

	_Config.GetObjectData().Tags.PushBack("Names");
	_Config.GetObjectData().Object.EmplaceBack(Json()).SetArray();

	Vector<Json>& _Array = _Config.GetObjectData().Object[_Config.GetObjectData().Object.GetSize() - 1].GetArray();

	for (size_t _Index = 0; _Index < Names.GetSize(); _Index++)
	{
		bool _Found = false;

		for (size_t _Index2 = 0; _Index2 < _Index; _Index2++)
		{
			if (Names[_Index] == Names[_Index2])
			{
				_Found = true;
				break;
			}
		}

		if (_Found)
		{
			continue;
		}

		_Array.EmplaceBack(Json()).SetString(BFW_MACHINE_TO_UTF8(Names[_Index], &_Error));

		if (_Error)
		{
			return FileContent();
		}
	}

	return _Config.Save();
}

const BFW_STRING_TYPE& BFW::Assets::ScriptLib::GetLib() const
{
	return Lib;
}

const BFW::Vector<BFW_STRING_TYPE>& BFW::Assets::ScriptLib::GetNames() const
{
	return Names;
}

const void* BFW::Assets::ScriptLib::GetSymbol(const BFW_STRING_VIEW_TYPE& _Name, const BFW_STRING_VIEW_TYPE& _Symbol) const
{
	const Trie<void*>* _NameTrie = Cache.GetData(_Name.data(), _Name.size());

	if (!_NameTrie)
	{
		return nullptr;
	}

	void* const* _Result = _NameTrie->GetData(_Symbol.data(), _Symbol.size());

	if (!_Result)
	{
		return nullptr;
	}

	return *_Result;
}

#ifdef BFW_WINDOWS_PLATFORM

BFW::Assets::ScriptLib& BFW::Assets::ScriptLib::operator= (const ScriptLib& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Stop();

	Lib = _Other.Lib;
	Names = _Other.Names;

	if (_Other.Handle && !Start())
	{
		throw nullptr;
	}

	return *this;
}

BFW::Assets::ScriptLib& BFW::Assets::ScriptLib::operator= (ScriptLib&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Stop();

	Lib = _Other.Lib;
	Names = (Vector<BFW_STRING_TYPE>&&)(_Other.Names);
	Cache = (Trie<Trie<void*>>&&)(_Other.Cache);
	Handle = _Other.Handle;

	_Other.Lib = BFW_STRING_PREFIX("");
	_Other.Handle = NULL;

	return *this;
}

#endif

#ifdef BFW_LINUX_PLATFORM

BFW::Assets::ScriptLib& BFW::Assets::ScriptLib::operator= (const ScriptLib& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Stop();

	Lib = _Other.Lib;
	Names = _Other.Names;

	if (_Other.Handle && !Start())
	{
		throw nullptr;
	}

	return *this;
}

BFW::Assets::ScriptLib& BFW::Assets::ScriptLib::operator= (ScriptLib&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Stop();

	Lib = _Other.Lib;
	Names = (Vector<BFW_STRING_TYPE>&&)(_Other.Names);
	Cache = (Trie<Trie<void*>>&&)(_Other.Cache);
	Handle = _Other.Handle;

	_Other.Lib = BFW_STRING_PREFIX("");
	_Other.Handle = nullptr;

	return *this;
}

#endif

#ifdef BFW_ESP32_PLATFORM

BFW::Assets::ScriptLib& BFW::Assets::ScriptLib::operator= (const ScriptLib& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Stop();

	Lib = _Other.Lib;
	Names = _Other.Names;
	Cache = _Other.Cache;
	Handle = _Other.Handle;

	return *this;
}

BFW::Assets::ScriptLib& BFW::Assets::ScriptLib::operator= (ScriptLib&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Stop();

	Lib = _Other.Lib;
	Names = (Vector<BFW_STRING_TYPE>&&)(_Other.Names);
	Cache = (Trie<Trie<void*>>&&)(_Other.Cache);
	Handle = (Trie<void*>&&)(_Other.Handle);

	_Other.Lib = BFW_STRING_PREFIX("");

	return *this;
}

#endif
