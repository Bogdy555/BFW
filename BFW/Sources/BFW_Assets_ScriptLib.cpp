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



BFW::Assets::Script::Script() : OnSetup(nullptr), OnUpdate(nullptr), OnLateUpdate(nullptr), OnFixedUpdate(nullptr), OnRender(nullptr), OnStop(nullptr)
{

}

BFW::Assets::Script::Script(void* _OnSetup, void* _OnUpdate, void* _OnLateUpdate, void* _OnFixedUpdate, void* _OnRender, void* _OnStop) : OnSetup(_OnSetup), OnUpdate(_OnUpdate), OnLateUpdate(_OnLateUpdate), OnFixedUpdate(_OnFixedUpdate), OnRender(_OnRender), OnStop(_OnStop)
{

}

BFW::Assets::Script::Script(Script&& _Other) noexcept : OnSetup(_Other.OnSetup), OnUpdate(_Other.OnUpdate), OnLateUpdate(_Other.OnLateUpdate), OnFixedUpdate(_Other.OnFixedUpdate), OnRender(_Other.OnRender), OnStop(_Other.OnStop)
{
	_Other.OnSetup = nullptr;
	_Other.OnUpdate = nullptr;
	_Other.OnLateUpdate = nullptr;
	_Other.OnFixedUpdate = nullptr;
	_Other.OnRender = nullptr;
	_Other.OnStop = nullptr;
}

BFW::Assets::Script& BFW::Assets::Script::operator=(Script&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	OnSetup = _Other.OnSetup;
	OnUpdate = _Other.OnUpdate;
	OnLateUpdate = _Other.OnLateUpdate;
	OnFixedUpdate = _Other.OnFixedUpdate;
	OnRender = _Other.OnRender;
	OnStop = _Other.OnStop;

	_Other.OnSetup = nullptr;
	_Other.OnUpdate = nullptr;
	_Other.OnLateUpdate = nullptr;
	_Other.OnFixedUpdate = nullptr;
	_Other.OnRender = nullptr;
	_Other.OnStop = nullptr;

	return *this;
}



#ifdef BFW_WINDOWS_PLATFORM

BFW::Assets::ScriptLib::ScriptLib() : Lib(BFW_STRING_PREFIX("")), NameSpaces(), Cache(), Handle(NULL)
{

}

BFW::Assets::ScriptLib::ScriptLib(const ScriptLib& _Other) : Lib(_Other.Lib), NameSpaces(_Other.NameSpaces), Cache(), Handle(NULL)
{
	if (_Other.Handle && !Start())
	{
		throw nullptr;
	}
}

BFW::Assets::ScriptLib::ScriptLib(ScriptLib&& _Other) noexcept : Lib(_Other.Lib), NameSpaces((Vector<BFW_STRING_TYPE>&&)(_Other.NameSpaces)), Cache((Trie<Trie<void*>>&&)(_Other.Cache)), Handle(_Other.Handle)
{
	_Other.Lib = BFW_STRING_PREFIX("");
	_Other.Handle = NULL;
}

#endif

#ifdef BFW_LINUX_PLATFORM

BFW::Assets::ScriptLib::ScriptLib() : Lib(BFW_STRING_PREFIX("")), NameSpaces(), Cache(), Handle(nullptr)
{

}

BFW::Assets::ScriptLib::ScriptLib(const ScriptLib& _Other) : Lib(_Other.Lib), NameSpaces(_Other.NameSpaces), Cache(), Handle(nullptr)
{
	if (_Other.Handle && !Start())
	{
		throw nullptr;
	}
}

BFW::Assets::ScriptLib::ScriptLib(ScriptLib&& _Other) noexcept : Lib(_Other.Lib), NameSpaces((Vector<BFW_STRING_TYPE>&&)(_Other.NameSpaces)), Cache((Trie<Trie<void*>>&&)(_Other.Cache)), Handle(_Other.Handle)
{
	_Other.Lib = BFW_STRING_PREFIX("");
	_Other.Handle = nullptr;
}

#endif

#ifdef BFW_ESP32_PLATFORM

BFW::Assets::ScriptLib::ScriptLib() : Lib(BFW_STRING_PREFIX("")), NameSpaces(), Cache(), Started(false), Handle()
{

}

BFW::Assets::ScriptLib::ScriptLib(const ScriptLib& _Other) : Lib(_Other.Lib), NameSpaces(_Other.NameSpaces), Cache(_Other.Cache), Started(_Other.Started), Handle(_Other.Handle)
{

}

BFW::Assets::ScriptLib::ScriptLib(ScriptLib&& _Other) noexcept : Lib(_Other.Lib), NameSpaces((Vector<BFW_STRING_TYPE>&&)(_Other.NameSpaces)), Cache((Trie<Trie<void*>>&&)(_Other.Cache)), Started(_Other.Started), Handle((Trie<void*>&&)(_Other.Handle))
{
	_Other.Lib = BFW_STRING_PREFIX("");
	_Other.Started = false;
}

#endif

BFW::Assets::ScriptLib::~ScriptLib()
{
	Stop();
}

const bool BFW::Assets::ScriptLib::Load(const FileContent& _FileContent, const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _CurrentPath)
{
#ifdef BFW_WINDOWS_PLATFORM

	if (Handle)
	{
		return false;
	}

#endif

#ifdef BFW_LINUX_PLATFORM

	if (Handle)
	{
		return false;
	}

#endif

#ifdef BFW_ESP32_PLATFORM

	if (Started)
	{
		return false;
	}

#endif

	Lib = BFW_STRING_PREFIX("");
	NameSpaces = Vector<BFW_STRING_TYPE>();

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
		_ObjectData.Tags[1] != "NameSpaces" ||
		_ObjectData.Object.GetSize() != 2 ||
		_ObjectData.Object[0].GetType() != _StringJsonType ||
		_ObjectData.Object[1].GetType() != _ArrayJsonType)
	{
		return false;
	}

	Vector<BFW_STRING_TYPE> _NameSpaces;

	for (size_t _Index = 0; _Index < _ObjectData.Object[1].GetArray().GetSize(); _Index++)
	{
		if (_ObjectData.Object[1].GetArray()[_Index].GetType() != _StringJsonType)
		{
			return false;
		}

		bool _Error = false;

		_NameSpaces.PushBack(BFW_UTF8_TO_MACHINE(_ObjectData.Object[1].GetArray()[_Index].GetString(), &_Error));

		if (_Error || !_NameSpaces[_NameSpaces.GetSize() - 1].size())
		{
			return false;
		}

		for (size_t _CheckIndex = 0; _CheckIndex < _NameSpaces.GetSize() - 1; _CheckIndex++)
		{
			if (_NameSpaces[_CheckIndex] == _NameSpaces[_NameSpaces.GetSize() - 1])
			{
				_NameSpaces.Erase(_NameSpaces.GetSize() - 1);
				break;
			}
		}
	}

	bool _Error = false;

	Lib = BFW_UTF8_TO_MACHINE(_ObjectData.Object[0].GetString(), &_Error);

	if (_Error || !Lib.size())
	{
		return false;
	}

	if (!ScriptLibLoadPath(_Path, _CurrentPath, Lib))
	{
		Lib = BFW_STRING_PREFIX("");
		return false;
	}

	NameSpaces = _NameSpaces;

	return true;
}

const bool BFW::Assets::ScriptLib::Start()
{
#ifdef BFW_WINDOWS_PLATFORM

	if (Handle)
	{
		return true;
	}

	Handle = LoadLibrary(Lib.c_str());

	if (!Handle)
	{
		return false;
	}

#endif

#ifdef BFW_LINUX_PLATFORM

	if (Handle)
	{
		return true;
	}

	bool _Error = false;

	BFW_STRING_TYPE_A _Lib = BFW_MACHINE_TO_UTF8(Lib, &_Error);

	if (_Error)
	{
		return false;
	}

	BFW_CHAR_TYPE_A _Path[PATH_MAX];

	size_t _Length = readlink("/proc/self/exe", _Path, PATH_MAX - 1);

	if (_Length == std::numeric_limits<size_t>::max())
	{
		return false;
	}

	_Path[_Length] = '\0';

	try
	{
		if (std::filesystem::weakly_canonical(std::filesystem::absolute(_Lib)).lexically_normal() == std::filesystem::weakly_canonical(std::filesystem::absolute(_Path)).lexically_normal())
		{
			Handle = dlopen(nullptr, RTLD_LAZY);
		}
		else
		{
			Handle = dlopen(_Lib.c_str(), RTLD_LAZY);
		}
	}
	catch (...)
	{
		return false;
	}

	if (!Handle)
	{
		return false;
	}

#endif

#ifdef BFW_ESP32_PLATFORM

	if (Started)
	{
		return true;
	}

	Handle = BFW::MultiProcessing::LoadLibrary(Lib.c_str());

#endif

	for (size_t _Index = 0; _Index < NameSpaces.GetSize(); _Index++)
	{
		bool _Found = false;

		for (size_t _Index2 = 0; _Index2 < _Index; _Index2++)
		{
			if (NameSpaces[_Index] == NameSpaces[_Index2])
			{
				_Found = true;
				break;
			}
		}

		if (_Found)
		{
			continue;
		}

		Trie<void*>& _Cache = Cache.Emplace(NameSpaces[_Index].c_str(), Trie<void*>());

#ifdef BFW_WINDOWS_PLATFORM

		void* (*Get)(HMODULE _Handle, const BFW_STRING_TYPE& _NameSpace) = [](HMODULE _Handle, const BFW_STRING_TYPE& _NameSpace) -> void*
			{
				bool _Error = false;

				void* _Result = GetProcAddress(_Handle, BFW_MACHINE_TO_UTF8(_NameSpace, &_Error).c_str());

				if (_Error)
				{
					return nullptr;
				}

				return _Result;
			};

#endif

#ifdef BFW_LINUX_PLATFORM

		void* (*Get)(void* _Handle, const BFW_STRING_TYPE& _NameSpace) = [](void* _Handle, const BFW_STRING_TYPE& _NameSpace) -> void*
			{
				bool _Error = false;

				void* _Result = dlsym(_Handle, BFW_MACHINE_TO_UTF8(_NameSpace, &_Error).c_str());

				if (_Error)
				{
					return nullptr;
				}

				return _Result;
			};

#endif

#ifdef BFW_ESP32_PLATFORM

		void* (*Get)(Trie<void*>& _Handle, const BFW_STRING_TYPE& _NameSpace) = [](Trie<void*>& _Handle, const BFW_STRING_TYPE& _NameSpace) -> void*
			{
				void** _Result = _Handle.GetData(_NameSpace.c_str());

				if (!_Result)
				{
					return nullptr;
				}

				return *_Result;
			};

#endif

		Script* _Script = (Script*)(Get(Handle, NameSpaces[_Index]));

		if (!_Script)
		{
			_Cache.Push(BFW_STRING_PREFIX("OnSetup"), nullptr);
			_Cache.Push(BFW_STRING_PREFIX("OnUpdate"), nullptr);
			_Cache.Push(BFW_STRING_PREFIX("OnLateUpdate"), nullptr);
			_Cache.Push(BFW_STRING_PREFIX("OnFixedUpdate"), nullptr);
			_Cache.Push(BFW_STRING_PREFIX("OnRender"), nullptr);
			_Cache.Push(BFW_STRING_PREFIX("OnStop"), nullptr);

			continue;
		}

		_Cache.Push(BFW_STRING_PREFIX("OnSetup"), _Script->OnSetup);
		_Cache.Push(BFW_STRING_PREFIX("OnUpdate"), _Script->OnUpdate);
		_Cache.Push(BFW_STRING_PREFIX("OnLateUpdate"), _Script->OnLateUpdate);
		_Cache.Push(BFW_STRING_PREFIX("OnFixedUpdate"), _Script->OnFixedUpdate);
		_Cache.Push(BFW_STRING_PREFIX("OnRender"), _Script->OnRender);
		_Cache.Push(BFW_STRING_PREFIX("OnStop"), _Script->OnStop);
	}

#ifdef BFW_ESP32_PLATFORM

	Started = true;

#endif

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
	Started = false;
	Handle = Trie<void*>();

#endif
}

const bool BFW::Assets::ScriptLib::SetLib(const BFW_STRING_VIEW_TYPE& _Lib)
{
#ifdef BFW_WINDOWS_PLATFORM

	if (Handle)
	{
		return false;
	}

#endif

#ifdef BFW_LINUX_PLATFORM

	if (Handle)
	{
		return false;
	}

#endif

#ifdef BFW_ESP32_PLATFORM

	if (Started)
	{
		return false;
	}

#endif

	Lib = _Lib;

	return true;
}

const bool BFW::Assets::ScriptLib::SetNameSpaces(const Vector<BFW_STRING_TYPE>& _NameSpaces)
{
#ifdef BFW_WINDOWS_PLATFORM

	if (Handle)
	{
		return false;
	}

#endif

#ifdef BFW_LINUX_PLATFORM

	if (Handle)
	{
		return false;
	}

#endif

#ifdef BFW_ESP32_PLATFORM

	if (Started)
	{
		return false;
	}

#endif

	NameSpaces = _NameSpaces;

	return true;
}

const BFW::Assets::FileContent BFW::Assets::ScriptLib::Save() const
{
	Json _Config;

	_Config.SetObject();

	bool _Error = false;

	_Config.GetObjectData().Tags.PushBack("Lib");
	_Config.GetObjectData().Object.EmplaceBack(Json()).SetString(BFW_MACHINE_TO_UTF8(Lib, &_Error));

	if (_Error || !Lib.size())
	{
		return FileContent();
	}

	_Config.GetObjectData().Tags.PushBack("NameSpaces");
	_Config.GetObjectData().Object.EmplaceBack(Json()).SetArray();

	Vector<Json>& _Array = _Config.GetObjectData().Object[_Config.GetObjectData().Object.GetSize() - 1].GetArray();

	for (size_t _Index = 0; _Index < NameSpaces.GetSize(); _Index++)
	{
		bool _Found = false;

		for (size_t _Index2 = 0; _Index2 < _Index; _Index2++)
		{
			if (NameSpaces[_Index] == NameSpaces[_Index2])
			{
				_Found = true;
				break;
			}
		}

		if (_Found)
		{
			continue;
		}

		_Array.EmplaceBack(Json()).SetString(BFW_MACHINE_TO_UTF8(NameSpaces[_Index], &_Error));

		if (_Error || !_Array[_Array.GetSize() - 1].GetString().size())
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

const BFW::Vector<BFW_STRING_TYPE>& BFW::Assets::ScriptLib::GetNameSpaces() const
{
	return NameSpaces;
}

const void* BFW::Assets::ScriptLib::GetSymbol(const BFW_STRING_VIEW_TYPE& _NameSpace, const BFW_STRING_VIEW_TYPE& _Symbol) const
{
	const Trie<void*>* _NameSpaceTrie = Cache.GetData(_NameSpace.data(), _NameSpace.size());

	if (!_NameSpaceTrie)
	{
		return nullptr;
	}

	void* const* _Result = _NameSpaceTrie->GetData(_Symbol.data(), _Symbol.size());

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
	NameSpaces = _Other.NameSpaces;

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
	NameSpaces = (Vector<BFW_STRING_TYPE>&&)(_Other.NameSpaces);
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
	NameSpaces = _Other.NameSpaces;

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
	NameSpaces = (Vector<BFW_STRING_TYPE>&&)(_Other.NameSpaces);
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
	NameSpaces = _Other.NameSpaces;
	Cache = _Other.Cache;
	Started = _Other.Started;
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
	NameSpaces = (Vector<BFW_STRING_TYPE>&&)(_Other.NameSpaces);
	Cache = (Trie<Trie<void*>>&&)(_Other.Cache);
	Started = _Other.Started;
	Handle = (Trie<void*>&&)(_Other.Handle);

	_Other.Lib = BFW_STRING_PREFIX("");
	_Other.Started = false;

	return *this;
}

#endif
