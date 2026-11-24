#include "../Headers/BFW.hpp"



template <typename T> static const bool ManagerDefaultLoader(BFW::Assets::FileContent& _FileContent, BFW::SharedPointer<T>& _Asset, const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _CurrentPath)
{
	return _Asset->Load(_FileContent);
}

static const bool ManagerMoveLoader(BFW::Assets::FileContent& _FileContent, BFW::SharedPointer<BFW::Assets::FileContent>& _Asset, const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _CurrentPath)
{
	*_Asset = (BFW::Assets::FileContent&&)(_FileContent);
	return true;
}

template <typename T> static const bool ManagerLoaderWithPath(BFW::Assets::FileContent& _FileContent, BFW::SharedPointer<T>& _Asset, const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _CurrentPath)
{
	return _Asset->Load(_FileContent, _Path, _CurrentPath);
}

static const bool (*ManagerRawFileLoader)(BFW::Assets::FileContent& _FileContent, BFW::SharedPointer<BFW::Assets::FileContent>& _Asset, const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _CurrentPath) = ManagerMoveLoader;
static const bool (*ManagerBitMapLoader)(BFW::Assets::FileContent& _FileContent, BFW::SharedPointer<BFW::Assets::BitMap>& _Asset, const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _CurrentPath) = ManagerDefaultLoader<BFW::Assets::BitMap>;
static const bool (*ManagerHdrLoader)(BFW::Assets::FileContent& _FileContent, BFW::SharedPointer<BFW::Assets::Hdr>& _Asset, const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _CurrentPath) = ManagerDefaultLoader<BFW::Assets::Hdr>;
static const bool (*ManagerWaveLoader)(BFW::Assets::FileContent& _FileContent, BFW::SharedPointer<BFW::Assets::Wave>& _Asset, const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _CurrentPath) = ManagerDefaultLoader<BFW::Assets::Wave>;
static const bool (*ManagerWaveFrontObjLoader)(BFW::Assets::FileContent& _FileContent, BFW::SharedPointer<BFW::Assets::WaveFrontObj>& _Asset, const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _CurrentPath) = ManagerLoaderWithPath<BFW::Assets::WaveFrontObj>;
static const bool (*ManagerMaterialLibLoader)(BFW::Assets::FileContent& _FileContent, BFW::SharedPointer<BFW::Assets::MaterialLib>& _Asset, const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _CurrentPath) = ManagerLoaderWithPath<BFW::Assets::MaterialLib>;
static const bool (*ManagerGLSLLoader)(BFW::Assets::FileContent& _FileContent, BFW::SharedPointer<BFW::Assets::FileContent>& _Asset, const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _CurrentPath) = ManagerMoveLoader;
static const bool (*ManagerXMLLoader)(BFW::Assets::FileContent& _FileContent, BFW::SharedPointer<BFW::Assets::XML>& _Asset, const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _CurrentPath) = ManagerDefaultLoader<BFW::Assets::XML>;
static const bool (*ManagerCSSLoader)(BFW::Assets::FileContent& _FileContent, BFW::SharedPointer<BFW::Assets::FileContent>& _Asset, const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _CurrentPath) = ManagerMoveLoader;
static const bool (*ManagerJavaScriptLoader)(BFW::Assets::FileContent& _FileContent, BFW::SharedPointer<BFW::Assets::FileContent>& _Asset, const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _CurrentPath) = ManagerMoveLoader;
static const bool (*ManagerJsonLoader)(BFW::Assets::FileContent& _FileContent, BFW::SharedPointer<BFW::Assets::Json>& _Asset, const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _CurrentPath) = ManagerDefaultLoader<BFW::Assets::Json>;
static const bool (*ManagerScriptLibLoader)(BFW::Assets::FileContent& _FileContent, BFW::SharedPointer<BFW::Assets::ScriptLib>& _Asset, const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _CurrentPath) = ManagerLoaderWithPath<BFW::Assets::ScriptLib>;

static void ManagerQueue(const BFW_CHAR_TYPE* _Name, BFW::Vector<BFW_STRING_TYPE>& _Queued)
{
	if (!_Name || _Name[0] == BFW_STRING_PREFIX('\0') || BFW_STRING_TYPE(_Name).starts_with(BFW_STRING_PREFIX("Dynamic/")))
	{
		throw nullptr;
	}

	for (size_t _Index = 0; _Index < _Queued.GetSize(); _Index++)
	{
		if (_Queued[_Index] == _Name)
		{
			return;
		}
	}

	_Queued.EmplaceBack(_Name);
}

#ifdef BFW_WINDOWS_PLATFORM

static void ManagerQueueResource(const size_t _Id, BFW::Vector<size_t>& _Queued)
{
	for (size_t _Index = 0; _Index < _Queued.GetSize(); _Index++)
	{
		if (_Queued[_Index] == _Id)
		{
			return;
		}
	}

	_Queued.PushBack(_Id);
}

#endif

template <typename T> static void ManagerFlushAllocate(BFW::Vector<BFW_STRING_TYPE>& _Queued, BFW::Trie<BFW::SharedPointer<T>>& _Loaded, BFW::Trie<BFW::WeakPointer<T>>& _Cached, BFW::Trie<uint64_t>& _LastWrite, BFW::Vector<BFW_STRING_TYPE>& _CachedNames)
{
	for (size_t _Index = 0; _Index < _Queued.GetSize(); _Index++)
	{
		if (_Loaded.GetData(_Queued[_Index].c_str()))
		{
			_Queued.Erase(_Index);
			_Index--;
			continue;
		}

		BFW::WeakPointer<T>* _CachedWeak = _Cached.GetData(_Queued[_Index].c_str());

		if (_CachedWeak)
		{
			BFW::SharedPointer<T> _CachedShared = _CachedWeak->Lock();

			if ((T*)(_CachedShared))
			{
				_Loaded.Emplace(_Queued[_Index].c_str(), (BFW::SharedPointer<T>&&)(_CachedShared));
				_Queued.Erase(_Index);
				_Index--;
				continue;
			}
		}

		BFW::SharedPointer<T> _Asset = BFW::SharedPointer<T>::MakeShared(T());

		_Cached.Emplace(_Queued[_Index].c_str(), _Asset);
		_LastWrite.Push(_Queued[_Index].c_str(), 0);
		_Loaded.Emplace(_Queued[_Index].c_str(), (BFW::SharedPointer<T>&&)(_Asset));

		bool _Found = false;

		for (size_t _NameIndex = 0; _NameIndex < _CachedNames.GetSize(); _NameIndex++)
		{
			if (_CachedNames[_NameIndex] == _Queued[_Index])
			{
				_Found = true;
				break;
			}
		}

		if (!_Found)
		{
			_CachedNames.PushBack(_Queued[_Index]);
		}
	}
}

template <typename T> static void ManagerFlushSpawn(BFW::Vector<std::thread>& _Threads, bool& _Fail, BFW::Vector<BFW_STRING_TYPE>& _Queued, BFW::Trie<BFW::SharedPointer<T>>& _Loaded, BFW::Trie<uint64_t>& _LastWrite, const bool (*_Loader)(BFW::Assets::FileContent& _FileContent, BFW::SharedPointer<T>& _Asset, const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _CurrentPath))
{
	for (size_t _Index = 0; _Index < _Queued.GetSize(); _Index++)
	{
		_Threads.EmplaceBack
		(
			std::thread
			(
				[](bool& _Fail, const BFW_CHAR_TYPE* _Name, BFW::SharedPointer<T> _Asset, uint64_t& _LastWrite, const bool (*_Loader)(BFW::Assets::FileContent& _FileContent, BFW::SharedPointer<T>& _Asset, const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _CurrentPath))
				{
					std::ifstream _InStream;

#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

					_InStream.open(_Name, std::ios::binary);

#endif

#ifdef BFW_ESP32_PLATFORM

					if (BFW_STRING_TYPE(_Name).starts_with(BFW_STRING_PREFIX("../")))
					{
						throw nullptr;
					}
					else if (BFW_STRING_TYPE(_Name) == BFW_STRING_PREFIX("."))
					{
						throw nullptr;
					}
					else if (BFW_STRING_TYPE(_Name) == BFW_STRING_PREFIX(".."))
					{
						throw nullptr;
					}
					else if (BFW_STRING_TYPE(_Name).starts_with(BFW_STRING_PREFIX("./")))
					{
						_InStream.open(BFW_STRING_TYPE("/sdcard/") + (_Name + 2), std::ios::binary);
					}
					else if (BFW_STRING_TYPE(_Name).starts_with(BFW_STRING_PREFIX("/")))
					{
						_InStream.open(BFW_STRING_TYPE("/sdcard/") + (_Name + 1), std::ios::binary);
					}
					else
					{
						_InStream.open(BFW_STRING_TYPE("/sdcard/") + _Name, std::ios::binary);
					}

#endif

					if (!_InStream.is_open())
					{
						_Fail = true;
						return;
					}

					try
					{
#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

						_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();

#endif

#ifdef BFW_ESP32_PLATFORM

						if (BFW_STRING_TYPE(_Name).starts_with(BFW_STRING_PREFIX("../")))
						{
							throw nullptr;
						}
						else if (BFW_STRING_TYPE(_Name) == BFW_STRING_PREFIX("."))
						{
							throw nullptr;
						}
						else if (BFW_STRING_TYPE(_Name) == BFW_STRING_PREFIX(".."))
						{
							throw nullptr;
						}
						else if (BFW_STRING_TYPE(_Name).starts_with(BFW_STRING_PREFIX("./")))
						{
							_LastWrite = std::filesystem::directory_entry(BFW_STRING_TYPE("/sdcard/") + (_Name + 2)).last_write_time().time_since_epoch().count();
						}
						else if (BFW_STRING_TYPE(_Name).starts_with(BFW_STRING_PREFIX("/")))
						{
							_LastWrite = std::filesystem::directory_entry(BFW_STRING_TYPE("/sdcard/") + (_Name + 1)).last_write_time().time_since_epoch().count();
						}
						else
						{
							_LastWrite = std::filesystem::directory_entry(BFW_STRING_TYPE("/sdcard/") + _Name).last_write_time().time_since_epoch().count();
						}

#endif
					}
					catch (...)
					{
						_Fail = true;
						return;
					}

					BFW::Assets::FileContent _FileContent;

					if (!_FileContent.Load(_InStream))
					{
						_Fail = true;
						return;
					}

					if (!_Loader(_FileContent, _Asset, _Name, BFW_WINDOWS_PLATFORM_CALL(BFW_STRING_PREFIX("./")) BFW_LINUX_PLATFORM_CALL(BFW_STRING_PREFIX("./")) BFW_ESP32_PLATFORM_CALL(BFW_STRING_PREFIX("/sdcard/"))))
					{
						_Fail = true;
						return;
					}
				},
				std::ref(_Fail),
				_Queued[_Index].c_str(),
				*_Loaded.GetData(_Queued[_Index].c_str()),
				std::ref(*_LastWrite.GetData(_Queued[_Index].c_str())),
				_Loader
			)
		);
	}
}

#ifdef BFW_WINDOWS_PLATFORM

template <typename T> static void ManagerFlushAllocateResource(BFW::Vector<size_t>& _Queued, BFW::Trie<BFW::SharedPointer<T>>& _Loaded, BFW::Trie<BFW::WeakPointer<T>>& _Cached, BFW::Vector<BFW_STRING_TYPE>& _CachedNames)
{
	for (size_t _Index = 0; _Index < _Queued.GetSize(); _Index++)
	{
		if (_Loaded.GetData(BFW_TO_STRING_PTR(_Queued[_Index])))
		{
			_Queued.Erase(_Index);
			_Index--;
			continue;
		}

		BFW::WeakPointer<T>* _CachedWeak = _Cached.GetData(BFW_TO_STRING_PTR(_Queued[_Index]));

		if (_CachedWeak)
		{
			BFW::SharedPointer<T> _CachedShared = _CachedWeak->Lock();

			if ((T*)(_CachedShared))
			{
				_Loaded.Emplace(BFW_TO_STRING_PTR(_Queued[_Index]), (BFW::SharedPointer<T>&&)(_CachedShared));
				_Queued.Erase(_Index);
				_Index--;
				continue;
			}
		}

		BFW::SharedPointer<T> _Asset = BFW::SharedPointer<T>::MakeShared(T());

		_Cached.Emplace(BFW_TO_STRING_PTR(_Queued[_Index]), _Asset);
		_Loaded.Emplace(BFW_TO_STRING_PTR(_Queued[_Index]), (BFW::SharedPointer<T>&&)(_Asset));

		bool _Found = false;

		for (size_t _NameIndex = 0; _NameIndex < _CachedNames.GetSize(); _NameIndex++)
		{
			if (_CachedNames[_NameIndex] == BFW_TO_STRING_PTR(_Queued[_Index]))
			{
				_Found = true;
				break;
			}
		}

		if (!_Found)
		{
			_CachedNames.PushBack(BFW_TO_STRING_PTR(_Queued[_Index]));
		}
	}
}

template <typename T> static void ManagerFlushSpawnResource(BFW::Vector<std::thread>& _Threads, bool& _Fail, BFW::Vector<size_t>& _Queued, const size_t _ResourceType, BFW::Trie<BFW::SharedPointer<T>>& _Loaded, const bool (*_Loader)(BFW::Assets::FileContent& _FileContent, BFW::SharedPointer<T>& _Asset, const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _CurrentPath))
{
	for (size_t _Index = 0; _Index < _Queued.GetSize(); _Index++)
	{
		_Threads.EmplaceBack
		(
			std::thread
			(
				[](bool& _Fail, const size_t _Id, const size_t _ResourceType, BFW::SharedPointer<T> _Asset, const bool (*_Loader)(BFW::Assets::FileContent& _FileContent, BFW::SharedPointer<T>& _Asset, const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _CurrentPath))
				{
					BFW::Assets::FileContent _FileContent;

					if (!_FileContent.Load(_ResourceType, _Id))
					{
						_Fail = true;
						return;
					}

					if (!_Loader(_FileContent, _Asset, (BFW_STRING_TYPE(BFW_STRING_PREFIX("./")) + BFW_TO_STRING(_Id)).c_str(), BFW_WINDOWS_PLATFORM_CALL(BFW_STRING_PREFIX("./")) BFW_LINUX_PLATFORM_CALL(BFW_STRING_PREFIX("./")) BFW_ESP32_PLATFORM_CALL(BFW_STRING_PREFIX("/sdcard/"))))
					{
						_Fail = true;
						return;
					}
				},
				std::ref(_Fail),
				_Queued[_Index],
				_ResourceType,
				*_Loaded.GetData(BFW_TO_STRING_PTR(_Queued[_Index])),
				_Loader
			)
		);
	}
}

#endif

#ifdef BFW_WINDOWS_PLATFORM

template <typename T, typename NextT> static void ManagerFlushQueueNext(BFW::Vector<BFW_STRING_TYPE>& _Queued, BFW::Trie<BFW::SharedPointer<T>>& _Loaded, BFW::Trie<BFW::SharedPointer<NextT>>& _LoadedNext, BFW::Trie<BFW::SharedPointer<NextT>>& _LoadedResourceNext, BFW::Trie<BFW::WeakPointer<NextT>>& _CachedNext, BFW::Trie<BFW::WeakPointer<NextT>>& _CachedResourceNext, BFW::Vector<BFW_STRING_TYPE>& _NewQueued, BFW::Trie<bool>& _TrieNewQueued, BFW::Vector<size_t>& _NewQueuedResource, BFW::Trie<bool>& _TrieNewQueuedResource, const BFW::Vector<BFW_STRING_TYPE> (T::*_Method)() const)
{
	for (size_t _CurrentIndex = 0; _CurrentIndex < _Queued.GetSize(); _CurrentIndex++)
	{
		const T& _Current = *_Loaded[_Queued[_CurrentIndex].c_str()];
		const BFW::Vector<BFW_STRING_TYPE>& _Resources = (_Current.*_Method)();

		for (size_t _ResourceIndex = 0; _ResourceIndex < _Resources.GetSize(); _ResourceIndex++)
		{
			size_t _NullIndex = 0;

			while (_Resources[_ResourceIndex][_NullIndex] == BFW_STRING_PREFIX('0'))
			{
				_NullIndex++;
			}

			if (_NullIndex == _Resources[_ResourceIndex].size())
			{
				_NullIndex--;
			}

			if (_LoadedNext.GetData(_Resources[_ResourceIndex].c_str()))
			{
				continue;
			}

			if (_LoadedResourceNext.GetData(_Resources[_ResourceIndex].c_str() + _NullIndex))
			{
				continue;
			}

			BFW::WeakPointer<NextT>* _CachedWeak = _CachedNext.GetData(_Resources[_ResourceIndex].c_str());

			bool _IsResource = false;

			if (!_CachedWeak)
			{
				_IsResource = true;
				_CachedWeak = _CachedResourceNext.GetData(_Resources[_ResourceIndex].c_str() + _NullIndex);
			}

			if (_CachedWeak)
			{
				BFW::SharedPointer<NextT> _CachedShared = _CachedWeak->Lock();

				if ((NextT*)(_CachedShared))
				{
					if (_IsResource)
					{
						_LoadedResourceNext.Emplace(_Resources[_ResourceIndex].c_str() + _NullIndex, (BFW::SharedPointer<NextT>&&)(_CachedShared));
					}
					else
					{
						_LoadedNext.Emplace(_Resources[_ResourceIndex].c_str(), (BFW::SharedPointer<NextT>&&)(_CachedShared));
					}

					continue;
				}
			}

			size_t _Id = 0;
			BFW_STRING_STREAM_TYPE _Stream(_Resources[_ResourceIndex]);

			if ((_Stream >> _Id) && _Stream.eof())
			{
				if (!_TrieNewQueuedResource.GetData(_Resources[_ResourceIndex].c_str() + _NullIndex))
				{
					_TrieNewQueuedResource.Push(_Resources[_ResourceIndex].c_str() + _NullIndex, true);
					_NewQueuedResource.PushBack(_Id);
				}
				continue;
			}

			if (!_TrieNewQueued.GetData(_Resources[_ResourceIndex].c_str()))
			{
				_TrieNewQueued.Push(_Resources[_ResourceIndex].c_str(), true);
				_NewQueued.PushBack(_Resources[_ResourceIndex]);
			}
		}
	}
}

template <typename T, typename NextT> static void ManagerFlushResourceQueueNext(BFW::Vector<size_t>& _Queued, BFW::Trie<BFW::SharedPointer<T>>& _Loaded, BFW::Trie<BFW::SharedPointer<NextT>>& _LoadedNext, BFW::Trie<BFW::SharedPointer<NextT>>& _LoadedResourceNext, BFW::Trie<BFW::WeakPointer<NextT>>& _CachedNext, BFW::Trie<BFW::WeakPointer<NextT>>& _CachedResourceNext, BFW::Vector<BFW_STRING_TYPE>& _NewQueued, BFW::Trie<bool>& _TrieNewQueued, BFW::Vector<size_t>& _NewQueuedResource, BFW::Trie<bool>& _TrieNewQueuedResource, const BFW::Vector<BFW_STRING_TYPE> (T::*_Method)() const)
{
	for (size_t _CurrentIndex = 0; _CurrentIndex < _Queued.GetSize(); _CurrentIndex++)
	{
		const T& _Current = *_Loaded[BFW_TO_STRING_PTR(_Queued[_CurrentIndex])];
		const BFW::Vector<BFW_STRING_TYPE>& _Resources = (_Current.*_Method)();

		for (size_t _ResourceIndex = 0; _ResourceIndex < _Resources.GetSize(); _ResourceIndex++)
		{
			size_t _NullIndex = 0;

			while (_Resources[_ResourceIndex][_NullIndex] == BFW_STRING_PREFIX('0'))
			{
				_NullIndex++;
			}

			if (_NullIndex == _Resources[_ResourceIndex].size())
			{
				_NullIndex--;
			}

			if (_LoadedNext.GetData(_Resources[_ResourceIndex].c_str()))
			{
				continue;
			}

			if (_LoadedResourceNext.GetData(_Resources[_ResourceIndex].c_str() + _NullIndex))
			{
				continue;
			}

			BFW::WeakPointer<NextT>* _CachedWeak = _CachedNext.GetData(_Resources[_ResourceIndex].c_str());

			bool _IsResource = false;

			if (!_CachedWeak)
			{
				_IsResource = true;
				_CachedWeak = _CachedResourceNext.GetData(_Resources[_ResourceIndex].c_str() + _NullIndex);
			}

			if (_CachedWeak)
			{
				BFW::SharedPointer<NextT> _CachedShared = _CachedWeak->Lock();

				if ((NextT*)(_CachedShared))
				{
					if (_IsResource)
					{
						_LoadedResourceNext.Emplace(_Resources[_ResourceIndex].c_str() + _NullIndex, (BFW::SharedPointer<NextT>&&)(_CachedShared));
					}
					else
					{
						_LoadedNext.Emplace(_Resources[_ResourceIndex].c_str(), (BFW::SharedPointer<NextT>&&)(_CachedShared));
					}

					continue;
				}
			}

			size_t _Id = 0;
			BFW_STRING_STREAM_TYPE _Stream(_Resources[_ResourceIndex]);

			if ((_Stream >> _Id) && _Stream.eof())
			{
				if (!_TrieNewQueuedResource.GetData(_Resources[_ResourceIndex].c_str() + _NullIndex))
				{
					_TrieNewQueuedResource.Push(_Resources[_ResourceIndex].c_str() + _NullIndex, true);
					_NewQueuedResource.PushBack(_Id);
				}
				continue;
			}

			if (!_TrieNewQueued.GetData(_Resources[_ResourceIndex].c_str()))
			{
				_TrieNewQueued.Push(_Resources[_ResourceIndex].c_str(), true);
				_NewQueued.PushBack(_Resources[_ResourceIndex]);
			}
		}
	}
}

#endif

#if defined BFW_LINUX_PLATFORM || defined BFW_ESP32_PLATFORM

template <typename T, typename NextT> static void ManagerFlushQueueNext(BFW::Vector<BFW_STRING_TYPE>& _Queued, BFW::Trie<BFW::SharedPointer<T>>& _Loaded, BFW::Trie<BFW::SharedPointer<NextT>>& _LoadedNext, BFW::Trie<BFW::WeakPointer<NextT>>& _CachedNext, BFW::Vector<BFW_STRING_TYPE>& _NewQueued, BFW::Trie<bool>& _TrieNewQueued, const BFW::Vector<BFW_STRING_TYPE> (T::*_Method)() const)
{
	for (size_t _CurrentIndex = 0; _CurrentIndex < _Queued.GetSize(); _CurrentIndex++)
	{
		const T& _Current = *_Loaded[_Queued[_CurrentIndex].c_str()];
		const BFW::Vector<BFW_STRING_TYPE>& _Resources = (_Current.*_Method)();

		for (size_t _ResourceIndex = 0; _ResourceIndex < _Resources.GetSize(); _ResourceIndex++)
		{
			if (_LoadedNext.GetData(_Resources[_ResourceIndex].c_str()))
			{
				continue;
			}

			BFW::WeakPointer<NextT>* _CachedWeak = _CachedNext.GetData(_Resources[_ResourceIndex].c_str());

			if (_CachedWeak)
			{
				BFW::SharedPointer<NextT> _CachedShared = _CachedWeak->Lock();

				if ((NextT*)(_CachedShared))
				{
					_LoadedNext.Emplace(_Resources[_ResourceIndex].c_str(), (BFW::SharedPointer<NextT>&&)(_CachedShared));

					continue;
				}
			}

			if (!_TrieNewQueued.GetData(_Resources[_ResourceIndex].c_str()))
			{
				_TrieNewQueued.Push(_Resources[_ResourceIndex].c_str(), true);
				_NewQueued.PushBack(_Resources[_ResourceIndex]);
			}
		}
	}
}

#endif

template <typename T> static void ManagerAddDynamic(const BFW_CHAR_TYPE* _Name, BFW::SharedPointer<T> _Asset, BFW::Trie<BFW::SharedPointer<T>>& _Loaded, BFW::Trie<BFW::WeakPointer<T>>& _Cached, BFW::Vector<BFW_STRING_TYPE>& _CachedNames)
{
	if (!_Name || _Name[0] == BFW_STRING_PREFIX('\0') || !BFW_STRING_TYPE(_Name).starts_with(BFW_STRING_PREFIX("Dynamic/")) || !(T*)(_Asset))
	{
		throw nullptr;
	}

	_Loaded.Push(_Name, _Asset);
	_Cached.Emplace(_Name, _Asset);

	for (size_t _Index = 0; _Index < _CachedNames.GetSize(); _Index++)
	{
		if (_CachedNames[_Index] == _Name)
		{
			return;
		}
	}

	_CachedNames.PushBack(_Name);
}

template <typename T> static void ManagerAddDynamicRef(const BFW_CHAR_TYPE* _Name, BFW::SharedPointer<T>& _Asset, BFW::Trie<BFW::WeakPointer<T>>& _Cached, BFW::Vector<BFW_STRING_TYPE>& _CachedNames)
{
	if (!_Name || _Name[0] == BFW_STRING_PREFIX('\0') || !BFW_STRING_TYPE(_Name).starts_with(BFW_STRING_PREFIX("Dynamic/")) || !(T*)(_Asset))
	{
		throw nullptr;
	}

	_Cached.Emplace(_Name, _Asset);

	for (size_t _Index = 0; _Index < _CachedNames.GetSize(); _Index++)
	{
		if (_CachedNames[_Index] == _Name)
		{
			return;
		}
	}

	_CachedNames.PushBack(_Name);
}

template <typename T> static void ManagerUpdate(BFW::Vector<std::thread>& _Threads, BFW::Trie<BFW::WeakPointer<T>>& _Cached, BFW::Trie<uint64_t>& _LastWrite, BFW::Vector<BFW_STRING_TYPE>& _CachedNames, const bool (*_Loader)(BFW::Assets::FileContent& _FileContent, BFW::SharedPointer<T>& _Asset, const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _CurrentPath))
{
	for (size_t _Index = 0; _Index < _CachedNames.GetSize(); _Index++)
	{
		if (_CachedNames[_Index].starts_with(BFW_STRING_PREFIX("Dynamic/")))
		{
			continue;
		}

		uint64_t _LastWriteValue = 0;

		try
		{
#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

			_LastWriteValue = std::filesystem::directory_entry(_CachedNames[_Index]).last_write_time().time_since_epoch().count();

#endif

#ifdef BFW_ESP32_PLATFORM

			if (_CachedNames[_Index].starts_with(BFW_STRING_PREFIX("../")))
			{
				throw nullptr;
			}
			else if (_CachedNames[_Index] == BFW_STRING_PREFIX("."))
			{
				throw nullptr;
			}
			else if (_CachedNames[_Index] == BFW_STRING_PREFIX(".."))
			{
				throw nullptr;
			}
			else if (_CachedNames[_Index].starts_with(BFW_STRING_PREFIX("./")))
			{
				_LastWriteValue = std::filesystem::directory_entry(BFW_STRING_TYPE("/sdcard/") + _CachedNames[_Index].substr(2)).last_write_time().time_since_epoch().count();
			}
			else if (_CachedNames[_Index].starts_with(BFW_STRING_PREFIX("/")))
			{
				_LastWriteValue = std::filesystem::directory_entry(BFW_STRING_TYPE("/sdcard/") + _CachedNames[_Index].substr(1)).last_write_time().time_since_epoch().count();
			}
			else
			{
				_LastWriteValue = std::filesystem::directory_entry(BFW_STRING_TYPE("/sdcard/") + _CachedNames[_Index]).last_write_time().time_since_epoch().count();
			}

#endif
		}
		catch (...)
		{
			continue;
		}

		uint64_t& _OldLastWrite = *_LastWrite.GetData(_CachedNames[_Index].c_str());

		if (_LastWriteValue == _OldLastWrite)
		{
			continue;
		}

		BFW::SharedPointer<T> _CachedShared = _Cached.GetData(_CachedNames[_Index].c_str())->Lock();

		if (!(T*)(_CachedShared))
		{
			continue;
		}

		_Threads.EmplaceBack
		(
			std::thread
			(
				[](const BFW_CHAR_TYPE* _Name, BFW::SharedPointer<T> _CachedShared, uint64_t& _OldLastWrite, const uint64_t _LastWriteValue, const bool (*_Loader)(BFW::Assets::FileContent& _FileContent, BFW::SharedPointer<T>& _Asset, const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _CurrentPath))
				{
					std::ifstream _InStream;

#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

					_InStream.open(_Name, std::ios::binary);

#endif

#ifdef BFW_ESP32_PLATFORM

					if (BFW_STRING_TYPE(_Name).starts_with(BFW_STRING_PREFIX("../")))
					{
						throw nullptr;
					}
					else if (BFW_STRING_TYPE(_Name) == BFW_STRING_PREFIX("."))
					{
						throw nullptr;
					}
					else if (BFW_STRING_TYPE(_Name) == BFW_STRING_PREFIX(".."))
					{
						throw nullptr;
					}
					else if (BFW_STRING_TYPE(_Name).starts_with(BFW_STRING_PREFIX("./")))
					{
						_InStream.open(BFW_STRING_TYPE("/sdcard/") + (_Name + 2), std::ios::binary);
					}
					else if (BFW_STRING_TYPE(_Name).starts_with(BFW_STRING_PREFIX("/")))
					{
						_InStream.open(BFW_STRING_TYPE("/sdcard/") + (_Name + 1), std::ios::binary);
					}
					else
					{
						_InStream.open(BFW_STRING_TYPE("/sdcard/") + _Name, std::ios::binary);
					}

#endif

					if (!_InStream.is_open())
					{
						return;
					}

					BFW::Assets::FileContent _FileContent;

					if (!_FileContent.Load(_InStream))
					{
						return;
					}

					BFW::SharedPointer<T> _Asset = BFW::SharedPointer<T>::MakeShared(T());

					if (!_Loader(_FileContent, _Asset, _Name, BFW_WINDOWS_PLATFORM_CALL(BFW_STRING_PREFIX("./")) BFW_LINUX_PLATFORM_CALL(BFW_STRING_PREFIX("./")) BFW_ESP32_PLATFORM_CALL(BFW_STRING_PREFIX("/sdcard/"))))
					{
						return;
					}

					*_CachedShared = (T&&)(*_Asset);

					_OldLastWrite = _LastWriteValue;
				},
				_CachedNames[_Index].c_str(),
				_CachedShared,
				std::ref(_OldLastWrite),
				_LastWriteValue,
				_Loader
			)
		);
	}
}

template <typename T> static void ManagerRelease(const BFW_CHAR_TYPE* _Name, BFW::Trie<BFW::SharedPointer<T>>& _Loaded)
{
	_Loaded.Erase(_Name);
}

#ifdef BFW_WINDOWS_PLATFORM

template <typename T> static void ManagerReleaseResource(const size_t _Id, BFW::Trie<BFW::SharedPointer<T>>& _Loaded)
{
	_Loaded.Erase(BFW_TO_STRING_PTR(_Id));
}

#endif

static const bool ManagerWasUpdated(const BFW_CHAR_TYPE* _Name, const BFW::Trie<uint64_t>& _LastWrite, const BFW::Trie<uint64_t>& _OldLastWrite)
{
	if (!_Name || _Name[0] == BFW_STRING_PREFIX('\0'))
	{
		return false;
	}

	const uint64_t* _LastWritePtr = _LastWrite.GetData(_Name);
	const uint64_t* _OldLastWritePtr = _OldLastWrite.GetData(_Name);

	if (!_LastWritePtr)
	{
		return false;
	}

	if (!_OldLastWritePtr)
	{
		return true;
	}

	return *_LastWritePtr != *_OldLastWritePtr;
}

template <typename T> static BFW::SharedPointer<T> ManagerGet(const BFW_CHAR_TYPE* _Name, BFW::Trie<BFW::WeakPointer<T>>& _Cached, BFW::Trie<uint64_t>& _LastWrite, BFW::Vector<BFW_STRING_TYPE>& _CachedNames, const bool (*_Loader)(BFW::Assets::FileContent& _FileContent, BFW::SharedPointer<T>& _Asset, const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _CurrentPath))
{
	if (!_Name || _Name[0] == BFW_STRING_PREFIX('\0'))
	{
		return BFW::SharedPointer<T>();
	}

	BFW::WeakPointer<T>* _CachedWeak = _Cached.GetData(_Name);

	if (_CachedWeak)
	{
		BFW::SharedPointer<T> _CachedShared = _CachedWeak->Lock();

		if ((T*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	std::ifstream _InStream;

#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

	_InStream.open(_Name, std::ios::binary);

#endif

#ifdef BFW_ESP32_PLATFORM

	if (BFW_STRING_TYPE(_Name).starts_with(BFW_STRING_PREFIX("../")))
	{
		throw nullptr;
	}
	else if (BFW_STRING_TYPE(_Name) == BFW_STRING_PREFIX("."))
	{
		throw nullptr;
	}
	else if (BFW_STRING_TYPE(_Name) == BFW_STRING_PREFIX(".."))
	{
		throw nullptr;
	}
	else if (BFW_STRING_TYPE(_Name).starts_with(BFW_STRING_PREFIX("./")))
	{
		_InStream.open(BFW_STRING_TYPE("/sdcard/") + (_Name + 2), std::ios::binary);
	}
	else if (BFW_STRING_TYPE(_Name).starts_with(BFW_STRING_PREFIX("/")))
	{
		_InStream.open(BFW_STRING_TYPE("/sdcard/") + (_Name + 1), std::ios::binary);
	}
	else
	{
		_InStream.open(BFW_STRING_TYPE("/sdcard/") + _Name, std::ios::binary);
	}

#endif

	if (!_InStream.is_open())
	{
		return BFW::SharedPointer<T>();
	}

	BFW::Assets::FileContent _FileContent;

	if (!_FileContent.Load(_InStream))
	{
		return BFW::SharedPointer<T>();
	}

	BFW::SharedPointer<T> _Shared = BFW::SharedPointer<T>::MakeShared(T());

	if (!_Loader(_FileContent, _Shared, _Name, BFW_WINDOWS_PLATFORM_CALL(BFW_STRING_PREFIX("./")) BFW_LINUX_PLATFORM_CALL(BFW_STRING_PREFIX("./")) BFW_ESP32_PLATFORM_CALL(BFW_STRING_PREFIX("/sdcard/"))))
	{
		return BFW::SharedPointer<T>();
	}

	uint64_t _LastWriteValue = 0;

	try
	{
#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

		_LastWriteValue = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();

#endif

#ifdef BFW_ESP32_PLATFORM

		if (BFW_STRING_TYPE(_Name).starts_with(BFW_STRING_PREFIX("../")))
		{
			throw nullptr;
		}
		else if (BFW_STRING_TYPE(_Name) == BFW_STRING_PREFIX("."))
		{
			throw nullptr;
		}
		else if (BFW_STRING_TYPE(_Name) == BFW_STRING_PREFIX(".."))
		{
			throw nullptr;
		}
		else if (BFW_STRING_TYPE(_Name).starts_with(BFW_STRING_PREFIX("./")))
		{
			_LastWriteValue = std::filesystem::directory_entry(BFW_STRING_TYPE("/sdcard/") + (_Name + 2)).last_write_time().time_since_epoch().count();
		}
		else if (BFW_STRING_TYPE(_Name).starts_with(BFW_STRING_PREFIX("/")))
		{
			_LastWriteValue = std::filesystem::directory_entry(BFW_STRING_TYPE("/sdcard/") + (_Name + 1)).last_write_time().time_since_epoch().count();
		}
		else
		{
			_LastWriteValue = std::filesystem::directory_entry(BFW_STRING_TYPE("/sdcard/") + _Name).last_write_time().time_since_epoch().count();
		}

#endif
	}
	catch (...)
	{
		return BFW::SharedPointer<T>();
	}

	_Cached.Emplace(_Name, _Shared);
	_LastWrite.Push(_Name, _LastWriteValue);

	for (size_t _Index = 0; _Index < _CachedNames.GetSize(); _Index++)
	{
		if (_CachedNames[_Index] == _Name)
		{
			return _Shared;
		}
	}

	_CachedNames.PushBack(_Name);

	return _Shared;
}

#ifdef BFW_WINDOWS_PLATFORM

template <typename T> static BFW::SharedPointer<T> ManagerGetResource(const size_t _Id, const size_t _ResourceType, BFW::Trie<BFW::WeakPointer<T>>& _Cached, BFW::Vector<BFW_STRING_TYPE>& _CachedNames, const bool (*_Loader)(BFW::Assets::FileContent& _FileContent, BFW::SharedPointer<T>& _Asset, const BFW_CHAR_TYPE* _Path, const BFW_CHAR_TYPE* _CurrentPath))
{
	BFW::WeakPointer<T>* _CachedWeak = _Cached.GetData(BFW_TO_STRING_PTR(_Id));

	if (_CachedWeak)
	{
		BFW::SharedPointer<T> _CachedShared = _CachedWeak->Lock();

		if ((T*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	BFW::Assets::FileContent _FileContent;

	if (!_FileContent.Load(_ResourceType, _Id))
	{
		return BFW::SharedPointer<T>();
	}

	BFW::SharedPointer<T> _Shared = BFW::SharedPointer<T>::MakeShared(T());

	if (!_Loader(_FileContent, _Shared, (BFW_STRING_TYPE(BFW_STRING_PREFIX("./")) + BFW_TO_STRING(_Id)).c_str(), BFW_WINDOWS_PLATFORM_CALL(BFW_STRING_PREFIX("./")) BFW_LINUX_PLATFORM_CALL(BFW_STRING_PREFIX("./")) BFW_ESP32_PLATFORM_CALL(BFW_STRING_PREFIX("/sdcard/"))))
	{
		return BFW::SharedPointer<T>();
	}

	_Cached.Emplace(BFW_TO_STRING_PTR(_Id), _Shared);

	for (size_t _Index = 0; _Index < _CachedNames.GetSize(); _Index++)
	{
		if (_CachedNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			return _Shared;
		}
	}

	_CachedNames.PushBack(BFW_TO_STRING_PTR(_Id));

	return _Shared;
}

#endif

#ifdef BFW_WINDOWS_PLATFORM

template <typename T, typename LibT> static T* ManagerResolveLib(const BFW_CHAR_TYPE* _TName, const BFW::Vector<BFW_STRING_TYPE>& _Files, BFW::Trie<BFW::WeakPointer<LibT>>& _Cached, BFW::Vector<BFW_STRING_TYPE>& _CachedNames, BFW::Trie<BFW::WeakPointer<LibT>>& _CachedResource, BFW::Vector<BFW_STRING_TYPE>& _CachedResourceNames)
{
	if (!_TName || _TName[0] == '\0')
	{
		return nullptr;
	}

	BFW::Vector<BFW_STRING_TYPE> _TrueFiles = _Files;

	if (_Files.GetSize() == 0)
	{
		for (size_t _Index = 0; _Index < _CachedNames.GetSize(); _Index++)
		{
			_TrueFiles.PushBack(_CachedNames[_Index]);
		}

		for (size_t _Index = 0; _Index < _CachedResourceNames.GetSize(); _Index++)
		{
			_TrueFiles.PushBack(_CachedResourceNames[_Index]);
		}
	}

	for (size_t _Index = 0; _Index < _TrueFiles.GetSize(); _Index++)
	{
		BFW::WeakPointer<LibT>* _CachedWeak = _Cached.GetData(_TrueFiles[_Index].c_str());

		if (!_CachedWeak)
		{
			size_t _NullIndex = 0;

			while (_TrueFiles[_Index][_NullIndex] == BFW_STRING_PREFIX('0'))
			{
				_NullIndex++;
			}

			if (_NullIndex == _TrueFiles[_Index].size())
			{
				_NullIndex--;
			}

			_CachedWeak = _CachedResource.GetData(_TrueFiles[_Index].c_str() + _NullIndex);
		}

		if (!_CachedWeak)
		{
			continue;
		}

		BFW::SharedPointer<LibT> _CachedShared = _CachedWeak->Lock();

		if (!(LibT*)(_CachedShared))
		{
			continue;
		}

		T* _T = _CachedShared->GetData(_TName);

		if (!_T)
		{
			continue;
		}

		return _T;
	}

	return nullptr;
}

template <typename T, typename LibT> static const BFW_STRING_TYPE ManagerResolveLibFile(const BFW_CHAR_TYPE* _TName, const BFW::Vector<BFW_STRING_TYPE>& _Files, BFW::Trie<BFW::WeakPointer<LibT>>& _Cached, BFW::Vector<BFW_STRING_TYPE>& _CachedNames, BFW::Trie<BFW::WeakPointer<LibT>>& _CachedResource, BFW::Vector<BFW_STRING_TYPE>& _CachedResourceNames)
{
	if (!_TName || _TName[0] == '\0')
	{
		return BFW_STRING_PREFIX("");
	}

	BFW::Vector<BFW_STRING_TYPE> _TrueFiles = _Files;

	if (_Files.GetSize() == 0)
	{
		for (size_t _Index = 0; _Index < _CachedNames.GetSize(); _Index++)
		{
			_TrueFiles.PushBack(_CachedNames[_Index]);
		}

		for (size_t _Index = 0; _Index < _CachedResourceNames.GetSize(); _Index++)
		{
			_TrueFiles.PushBack(_CachedResourceNames[_Index]);
		}
	}

	for (size_t _Index = 0; _Index < _TrueFiles.GetSize(); _Index++)
	{
		BFW::WeakPointer<LibT>* _CachedWeak = _Cached.GetData(_TrueFiles[_Index].c_str());

		if (!_CachedWeak)
		{
			size_t _NullIndex = 0;

			while (_TrueFiles[_Index][_NullIndex] == BFW_STRING_PREFIX('0'))
			{
				_NullIndex++;
			}

			if (_NullIndex == _TrueFiles[_Index].size())
			{
				_NullIndex--;
			}

			_CachedWeak = _CachedResource.GetData(_TrueFiles[_Index].c_str() + _NullIndex);
		}

		if (!_CachedWeak)
		{
			continue;
		}

		BFW::SharedPointer<LibT> _CachedShared = _CachedWeak->Lock();

		if (!(LibT*)(_CachedShared))
		{
			continue;
		}

		T* _T = _CachedShared->GetData(_TName);

		if (!_T)
		{
			continue;
		}

		return _TrueFiles[_Index];
	}

	return BFW_STRING_PREFIX("");
}

#endif

#if defined BFW_LINUX_PLATFORM || defined BFW_ESP32_PLATFORM

template <typename T, typename LibT> static T* ManagerResolveLib(const BFW_CHAR_TYPE* _TName, const BFW::Vector<BFW_STRING_TYPE>& _Files, BFW::Trie<BFW::WeakPointer<LibT>>& _Cached, BFW::Vector<BFW_STRING_TYPE>& _CachedNames)
{
	if (!_TName || _TName[0] == '\0')
	{
		return nullptr;
	}

	BFW::Vector<BFW_STRING_TYPE> _TrueFiles = _Files;

	if (_Files.GetSize() == 0)
	{
		for (size_t _Index = 0; _Index < _CachedNames.GetSize(); _Index++)
		{
			_TrueFiles.PushBack(_CachedNames[_Index]);
		}
	}

	for (size_t _Index = 0; _Index < _TrueFiles.GetSize(); _Index++)
	{
		BFW::WeakPointer<LibT>* _CachedWeak = _Cached.GetData(_TrueFiles[_Index].c_str());

		if (!_CachedWeak)
		{
			continue;
		}

		BFW::SharedPointer<LibT> _CachedShared = _CachedWeak->Lock();

		if (!(LibT*)(_CachedShared))
		{
			continue;
		}

		T* _T = _CachedShared->GetData(_TName);

		if (!_T)
		{
			continue;
		}

		return _T;
	}

	return nullptr;
}

template <typename T, typename LibT> static const BFW_STRING_TYPE ManagerResolveLibFile(const BFW_CHAR_TYPE* _TName, const BFW::Vector<BFW_STRING_TYPE>& _Files, BFW::Trie<BFW::WeakPointer<LibT>>& _Cached, BFW::Vector<BFW_STRING_TYPE>& _CachedNames)
{
	if (!_TName || _TName[0] == '\0')
	{
		return BFW_STRING_PREFIX("");
	}

	BFW::Vector<BFW_STRING_TYPE> _TrueFiles = _Files;

	if (_Files.GetSize() == 0)
	{
		for (size_t _Index = 0; _Index < _CachedNames.GetSize(); _Index++)
		{
			_TrueFiles.PushBack(_CachedNames[_Index]);
		}
	}

	for (size_t _Index = 0; _Index < _TrueFiles.GetSize(); _Index++)
	{
		BFW::WeakPointer<LibT>* _CachedWeak = _Cached.GetData(_TrueFiles[_Index].c_str());

		if (!_CachedWeak)
		{
			continue;
		}

		BFW::SharedPointer<LibT> _CachedShared = _CachedWeak->Lock();

		if (!(LibT*)(_CachedShared))
		{
			continue;
		}

		T* _T = _CachedShared->GetData(_TName);

		if (!_T)
		{
			continue;
		}

		return _TrueFiles[_Index];
	}

	return BFW_STRING_PREFIX("");
}

#endif

template <typename T> static void ManagerRefreshCache(BFW::Trie<BFW::WeakPointer<T>>& _Cached, BFW::Trie<uint64_t>& _LastWrite, BFW::Vector<BFW_STRING_TYPE>& _CachedNames)
{
	for (size_t _Index = 0; _Index < _CachedNames.GetSize(); _Index++)
	{
		BFW::WeakPointer<T>* _CachedWeak = _Cached.GetData(_CachedNames[_Index].c_str());

		if (!_CachedWeak)
		{
			_LastWrite.Erase(_CachedNames[_Index].c_str());
			_CachedNames.Erase(_Index);
			_Index--;
			continue;
		}

		BFW::SharedPointer<T> _CachedShared = _CachedWeak->Lock();

		if ((T*)(_CachedShared) == nullptr)
		{
			_Cached.Erase(_CachedNames[_Index].c_str());
			_LastWrite.Erase(_CachedNames[_Index].c_str());
			_CachedNames.Erase(_Index);
			_Index--;
			continue;
		}
	}
}

#ifdef BFW_WINDOWS_PLATFORM

template <typename T> static void ManagerRefreshResourceCache(BFW::Trie<BFW::WeakPointer<T>>& _Cached, BFW::Vector<BFW_STRING_TYPE>& _CachedNames)
{
	for (size_t _Index = 0; _Index < _CachedNames.GetSize(); _Index++)
	{
		BFW::WeakPointer<T>* _CachedWeak = _Cached.GetData(_CachedNames[_Index].c_str());

		if (!_CachedWeak)
		{
			_CachedNames.Erase(_Index);
			_Index--;
			continue;
		}

		BFW::SharedPointer<T> _CachedShared = _CachedWeak->Lock();

		if ((T*)(_CachedShared) == nullptr)
		{
			_Cached.Erase(_CachedNames[_Index].c_str());
			_CachedNames.Erase(_Index);
			_Index--;
			continue;
		}
	}
}

#endif



BFW::Assets::FileContent::FileContent() : Data(nullptr), Length(0)
{

}

BFW::Assets::FileContent::FileContent(const FileContent& _Other) : Data(nullptr), Length(0)
{
	if (!_Other.Length)
	{
		return;
	}

	Data = new uint8_t[_Other.Length];

	if (!Data)
	{
		throw nullptr;
	}

	Length = _Other.Length;

	for (size_t _Index = 0; _Index < Length; _Index++)
	{
		Data[_Index] = _Other.Data[_Index];
	}
}

BFW::Assets::FileContent::FileContent(FileContent&& _Other) noexcept : Data(_Other.Data), Length(_Other.Length)
{
	_Other.Data = nullptr;
	_Other.Length = 0;
}

BFW::Assets::FileContent::~FileContent()
{
	delete[] Data;
}

const bool BFW::Assets::FileContent::Create(const size_t _Length)
{
	Destroy();

	if (!_Length)
	{
		return false;
	}

	Data = new uint8_t[_Length];

	if (!Data)
	{
		return false;
	}

	Length = _Length;

	for (size_t _Index = 0; _Index < Length; _Index++)
	{
		Data[_Index] = 0;
	}

	return true;
}

const bool BFW::Assets::FileContent::Load(std::ifstream& _File)
{
	Destroy();

	if (!_File.is_open())
	{
		return false;
	}

	size_t _CurrentPos = (size_t)(_File.tellg());

	if (_CurrentPos == std::numeric_limits<size_t>::max())
	{
		return false;
	}

	_File.seekg(0, std::ios::end);

	size_t _Length = (size_t)(_File.tellg()) + 1;

	if (!_Length)
	{
		_File.seekg(_CurrentPos, std::ios::beg);
		return false;
	}

	uint8_t* _Data = new uint8_t[_Length];

	if (!_Data)
	{
		_File.seekg(_CurrentPos, std::ios::beg);
		return false;
	}

	_File.seekg(0, std::ios::beg);

	_File.read((BFW_CHAR_TYPE_A*)(_Data), _Length - 1);

	if ((size_t)(_File.gcount()) != _Length - 1)
	{
		delete[] _Data;
		_File.seekg(_CurrentPos, std::ios::beg);
		return false;
	}

	_Data[_Length - 1] = '\0';

	Data = _Data;
	Length = _Length;

	_File.seekg(_CurrentPos, std::ios::beg);

	return true;
}

const bool BFW::Assets::FileContent::Load(std::fstream& _File)
{
	Destroy();

	if (!_File.is_open())
	{
		return false;
	}

	size_t _CurrentPos = (size_t)(_File.tellg());

	if (_CurrentPos == std::numeric_limits<size_t>::max())
	{
		return false;
	}

	_File.seekg(0, std::ios::end);

	size_t _Length = (size_t)(_File.tellg()) + 1;

	if (!_Length)
	{
		_File.seekg(_CurrentPos, std::ios::beg);
		return false;
	}

	uint8_t* _Data = new uint8_t[_Length];

	if (!_Data)
	{
		_File.seekg(_CurrentPos, std::ios::beg);
		return false;
	}

	_File.seekg(0, std::ios::beg);

	_File.read((BFW_CHAR_TYPE_A*)(_Data), _Length - 1);

	if ((size_t)(_File.gcount()) != _Length - 1)
	{
		delete[] _Data;
		_File.seekg(_CurrentPos, std::ios::beg);
		return false;
	}

	_Data[_Length - 1] = '\0';

	Data = _Data;
	Length = _Length;

	_File.seekg(_CurrentPos, std::ios::beg);

	return true;
}

#ifdef BFW_WINDOWS_PLATFORM

const bool BFW::Assets::FileContent::Load(const size_t _ResourceType, const size_t _ResourceId)
{
	HINSTANCE _InstanceHandle = GetModuleHandle(nullptr);

	if (!_InstanceHandle)
	{
		return false;
	}

	HRSRC _ResourceHandle = FindResource(_InstanceHandle, MAKEINTRESOURCE(_ResourceId), MAKEINTRESOURCE(_ResourceType));

	if (!_ResourceHandle)
	{
		return false;
	}

	size_t _Length = (size_t)(SizeofResource(_InstanceHandle, _ResourceHandle)) + 1;

	HGLOBAL _ResourceGlobal = LoadResource(_InstanceHandle, _ResourceHandle);

	if (!_ResourceGlobal)
	{
		return false;
	}

	const uint8_t* _ResourceMemory = (const uint8_t*)(LockResource(_ResourceGlobal));

	if (!_ResourceMemory)
	{
		FreeResource(_ResourceGlobal);
		return false;
	}

	uint8_t* _Data = new uint8_t[_Length];

	if (!_Data)
	{
		UnlockResource(_ResourceMemory);
		FreeResource(_ResourceGlobal);
		return false;
	}

	for (size_t _Index = 0; _Index < _Length - 1; _Index++)
	{
		_Data[_Index] = _ResourceMemory[_Index];
	}

	_Data[_Length - 1] = '\0';

	Data = _Data;
	Length = _Length;

	UnlockResource(_ResourceMemory);
	FreeResource(_ResourceGlobal);

	return true;
}

#endif

void BFW::Assets::FileContent::Destroy()
{
	delete[] Data;
	Data = nullptr;
	Length = 0;
}

const bool BFW::Assets::FileContent::Save(std::ofstream& _File) const
{
	if (!Data || Length < 1 || !_File.is_open())
	{
		return false;
	}

	_File.seekp(0, std::ios::beg);

	if (!_File)
	{
		return false;
	}

	_File.write((const BFW_CHAR_TYPE_A*)(Data), Length - 1);

	if (!_File)
	{
		return false;
	}

	return true;
}

const bool BFW::Assets::FileContent::Save(std::fstream& _File) const
{
	if (!Data || Length <= 1 || !_File.is_open())
	{
		return false;
	}

	_File.seekp(0, std::ios::beg);

	if (!_File)
	{
		return false;
	}

	_File.write((const BFW_CHAR_TYPE_A*)(Data), Length - 1);

	if (!_File)
	{
		return false;
	}

	return true;
}

const uint64_t BFW::Assets::FileContent::Hash() const
{
	if (!Length)
	{
		return BFW::Cryptography::HashA(nullptr, 0);
	}

	return BFW::Cryptography::HashA((const BFW_CHAR_TYPE_A*)(Data), Length - 1);
}

uint8_t* BFW::Assets::FileContent::GetData()
{
	return Data;
}

const uint8_t* BFW::Assets::FileContent::GetData() const
{
	return Data;
}

const size_t BFW::Assets::FileContent::GetLength() const
{
	return Length;
}

BFW::Assets::FileContent::operator uint8_t* ()
{
	return Data;
}

BFW::Assets::FileContent::operator const uint8_t* () const
{
	return Data;
}

uint8_t& BFW::Assets::FileContent::operator* ()
{
	return *Data;
}

const uint8_t& BFW::Assets::FileContent::operator* () const
{
	return *Data;
}

uint8_t& BFW::Assets::FileContent::operator[] (const size_t _Index)
{
	return Data[_Index];
}

const uint8_t& BFW::Assets::FileContent::operator[] (const size_t _Index) const
{
	return Data[_Index];
}

BFW::Assets::FileContent& BFW::Assets::FileContent::operator= (const FileContent& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Destroy();

	if (!_Other.Length)
	{
		return *this;
	}

	Data = new uint8_t[_Other.Length];

	if (!Data)
	{
		throw nullptr;
	}

	Length = _Other.Length;

	for (size_t _Index = 0; _Index < Length; _Index++)
	{
		Data[_Index] = _Other.Data[_Index];
	}

	return *this;
}

BFW::Assets::FileContent& BFW::Assets::FileContent::operator= (FileContent&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Destroy();

	Data = _Other.Data;
	Length = _Other.Length;

	_Other.Data = nullptr;
	_Other.Length = 0;

	return *this;
}



#ifdef BFW_WINDOWS_PLATFORM

BFW::Assets::Manager::Manager() :
	QueuedRawFiles(),
	QueuedBitMaps(),
	QueuedHdrs(),
	QueuedWaves(),
	QueuedWaveFrontObjs(),
	QueuedMaterialLibs(),
	QueuedGLSLs(),
	QueuedXMLs(),
	QueuedCSSs(),
	QueuedJavaScripts(),
	QueuedJsons(),
	QueuedScriptLibs(),

	QueuedResourceRawFiles(),
	QueuedResourceBitMaps(),
	QueuedResourceHdrs(),
	QueuedResourceWaves(),
	QueuedResourceWaveFrontObjs(),
	QueuedResourceMaterialLibs(),
	QueuedResourceGLSLs(),
	QueuedResourceXMLs(),
	QueuedResourceCSSs(),
	QueuedResourceJavaScripts(),
	QueuedResourceJsons(),
	QueuedResourceScriptLibs(),

	LoadedRawFiles(),
	LoadedBitMaps(),
	LoadedHdrs(),
	LoadedWaves(),
	LoadedWaveFrontObjs(),
	LoadedMaterialLibs(),
	LoadedGLSLs(),
	LoadedXMLs(),
	LoadedCSSs(),
	LoadedJavaScripts(),
	LoadedJsons(),
	LoadedScriptLibs(),

	LoadedResourceRawFiles(),
	LoadedResourceBitMaps(),
	LoadedResourceHdrs(),
	LoadedResourceWaves(),
	LoadedResourceWaveFrontObjs(),
	LoadedResourceMaterialLibs(),
	LoadedResourceGLSLs(),
	LoadedResourceXMLs(),
	LoadedResourceCSSs(),
	LoadedResourceJavaScripts(),
	LoadedResourceJsons(),
	LoadedResourceScriptLibs(),

	CachedRawFileNames(),
	CachedBitMapNames(),
	CachedHdrNames(),
	CachedWaveNames(),
	CachedWaveFrontObjNames(),
	CachedMaterialLibNames(),
	CachedGLSLNames(),
	CachedXMLNames(),
	CachedCSSNames(),
	CachedJavaScriptNames(),
	CachedJsonNames(),
	CachedScriptLibNames(),

	CachedRawFiles(),
	CachedBitMaps(),
	CachedHdrs(),
	CachedWaves(),
	CachedWaveFrontObjs(),
	CachedMaterialLibs(),
	CachedGLSLs(),
	CachedXMLs(),
	CachedCSSs(),
	CachedJavaScripts(),
	CachedJsons(),
	CachedScriptLibs(),

	LastWriteRawFiles(),
	LastWriteBitMaps(),
	LastWriteHdrs(),
	LastWriteWaves(),
	LastWriteWaveFrontObjs(),
	LastWriteMaterialLibs(),
	LastWriteGLSLs(),
	LastWriteXMLs(),
	LastWriteCSSs(),
	LastWriteJavaScripts(),
	LastWriteJsons(),
	LastWriteScriptLibs(),

	OldLastWriteRawFiles(),
	OldLastWriteBitMaps(),
	OldLastWriteHdrs(),
	OldLastWriteWaves(),
	OldLastWriteWaveFrontObjs(),
	OldLastWriteMaterialLibs(),
	OldLastWriteGLSLs(),
	OldLastWriteXMLs(),
	OldLastWriteCSSs(),
	OldLastWriteJavaScripts(),
	OldLastWriteJsons(),
	OldLastWriteScriptLibs(),

	CachedResourceRawFileNames(),
	CachedResourceBitMapNames(),
	CachedResourceHdrNames(),
	CachedResourceWaveNames(),
	CachedResourceWaveFrontObjNames(),
	CachedResourceMaterialLibNames(),
	CachedResourceGLSLNames(),
	CachedResourceXMLNames(),
	CachedResourceCSSNames(),
	CachedResourceJavaScriptNames(),
	CachedResourceJsonNames(),
	CachedResourceScriptLibNames(),

	CachedResourceRawFiles(),
	CachedResourceBitMaps(),
	CachedResourceHdrs(),
	CachedResourceWaves(),
	CachedResourceWaveFrontObjs(),
	CachedResourceMaterialLibs(),
	CachedResourceGLSLs(),
	CachedResourceXMLs(),
	CachedResourceCSSs(),
	CachedResourceJavaScripts(),
	CachedResourceJsons(),
	CachedResourceScriptLibs()
{

}

BFW::Assets::Manager::Manager(Manager&& _Other) noexcept :
	QueuedRawFiles((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedRawFiles)),
	QueuedBitMaps((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedBitMaps)),
	QueuedHdrs((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedHdrs)),
	QueuedWaves((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedWaves)),
	QueuedWaveFrontObjs((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedWaveFrontObjs)),
	QueuedMaterialLibs((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedMaterialLibs)),
	QueuedGLSLs((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedGLSLs)),
	QueuedXMLs((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedXMLs)),
	QueuedCSSs((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedCSSs)),
	QueuedJavaScripts((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedJavaScripts)),
	QueuedJsons((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedJsons)),
	QueuedScriptLibs((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedScriptLibs)),

	QueuedResourceRawFiles((Vector<size_t>&&)(_Other.QueuedResourceRawFiles)),
	QueuedResourceBitMaps((Vector<size_t>&&)(_Other.QueuedResourceBitMaps)),
	QueuedResourceHdrs((Vector<size_t>&&)(_Other.QueuedResourceHdrs)),
	QueuedResourceWaves((Vector<size_t>&&)(_Other.QueuedResourceWaves)),
	QueuedResourceWaveFrontObjs((Vector<size_t>&&)(_Other.QueuedResourceWaveFrontObjs)),
	QueuedResourceMaterialLibs((Vector<size_t>&&)(_Other.QueuedResourceMaterialLibs)),
	QueuedResourceGLSLs((Vector<size_t>&&)(_Other.QueuedResourceGLSLs)),
	QueuedResourceXMLs((Vector<size_t>&&)(_Other.QueuedResourceXMLs)),
	QueuedResourceCSSs((Vector<size_t>&&)(_Other.QueuedResourceCSSs)),
	QueuedResourceJavaScripts((Vector<size_t>&&)(_Other.QueuedResourceJavaScripts)),
	QueuedResourceJsons((Vector<size_t>&&)(_Other.QueuedResourceJsons)),
	QueuedResourceScriptLibs((Vector<size_t>&&)(_Other.QueuedResourceScriptLibs)),

	LoadedRawFiles((Trie<SharedPointer<FileContent>>&&)(_Other.LoadedRawFiles)),
	LoadedBitMaps((Trie<SharedPointer<BitMap>>&&)(_Other.LoadedBitMaps)),
	LoadedHdrs((Trie<SharedPointer<Hdr>>&&)(_Other.LoadedHdrs)),
	LoadedWaves((Trie<SharedPointer<Wave>>&&)(_Other.LoadedWaves)),
	LoadedWaveFrontObjs((Trie<SharedPointer<WaveFrontObj>>&&)(_Other.LoadedWaveFrontObjs)),
	LoadedMaterialLibs((Trie<SharedPointer<MaterialLib>>&&)(_Other.LoadedMaterialLibs)),
	LoadedGLSLs((Trie<SharedPointer<FileContent>>&&)(_Other.LoadedGLSLs)),
	LoadedXMLs((Trie<SharedPointer<XML>>&&)(_Other.LoadedXMLs)),
	LoadedCSSs((Trie<SharedPointer<FileContent>>&&)(_Other.LoadedCSSs)),
	LoadedJavaScripts((Trie<SharedPointer<FileContent>>&&)(_Other.LoadedJavaScripts)),
	LoadedJsons((Trie<SharedPointer<Json>>&&)(_Other.LoadedJsons)),
	LoadedScriptLibs((Trie<SharedPointer<ScriptLib>>&&)(_Other.LoadedScriptLibs)),

	LoadedResourceRawFiles((Trie<SharedPointer<FileContent>>&&)(_Other.LoadedResourceRawFiles)),
	LoadedResourceBitMaps((Trie<SharedPointer<BitMap>>&&)(_Other.LoadedResourceBitMaps)),
	LoadedResourceHdrs((Trie<SharedPointer<Hdr>>&&)(_Other.LoadedResourceHdrs)),
	LoadedResourceWaves((Trie<SharedPointer<Wave>>&&)(_Other.LoadedResourceWaves)),
	LoadedResourceWaveFrontObjs((Trie<SharedPointer<WaveFrontObj>>&&)(_Other.LoadedResourceWaveFrontObjs)),
	LoadedResourceMaterialLibs((Trie<SharedPointer<MaterialLib>>&&)(_Other.LoadedResourceMaterialLibs)),
	LoadedResourceGLSLs((Trie<SharedPointer<FileContent>>&&)(_Other.LoadedResourceGLSLs)),
	LoadedResourceXMLs((Trie<SharedPointer<XML>>&&)(_Other.LoadedResourceXMLs)),
	LoadedResourceCSSs((Trie<SharedPointer<FileContent>>&&)(_Other.LoadedResourceCSSs)),
	LoadedResourceJavaScripts((Trie<SharedPointer<FileContent>>&&)(_Other.LoadedResourceJavaScripts)),
	LoadedResourceJsons((Trie<SharedPointer<Json>>&&)(_Other.LoadedResourceJsons)),
	LoadedResourceScriptLibs((Trie<SharedPointer<ScriptLib>>&&)(_Other.LoadedResourceScriptLibs)),

	CachedRawFileNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedRawFileNames)),
	CachedBitMapNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedBitMapNames)),
	CachedHdrNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedHdrNames)),
	CachedWaveNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedWaveNames)),
	CachedWaveFrontObjNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedWaveFrontObjNames)),
	CachedMaterialLibNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedMaterialLibNames)),
	CachedGLSLNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedGLSLNames)),
	CachedXMLNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedXMLNames)),
	CachedCSSNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedCSSNames)),
	CachedJavaScriptNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedJavaScriptNames)),
	CachedJsonNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedJsonNames)),
	CachedScriptLibNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedScriptLibNames)),

	CachedRawFiles((Trie<WeakPointer<FileContent>>&&)(_Other.CachedRawFiles)),
	CachedBitMaps((Trie<WeakPointer<BitMap>>&&)(_Other.CachedBitMaps)),
	CachedHdrs((Trie<WeakPointer<Hdr>>&&)(_Other.CachedHdrs)),
	CachedWaves((Trie<WeakPointer<Wave>>&&)(_Other.CachedWaves)),
	CachedWaveFrontObjs((Trie<WeakPointer<WaveFrontObj>>&&)(_Other.CachedWaveFrontObjs)),
	CachedMaterialLibs((Trie<WeakPointer<MaterialLib>>&&)(_Other.CachedMaterialLibs)),
	CachedGLSLs((Trie<WeakPointer<FileContent>>&&)(_Other.CachedGLSLs)),
	CachedXMLs((Trie<WeakPointer<XML>>&&)(_Other.CachedXMLs)),
	CachedCSSs((Trie<WeakPointer<FileContent>>&&)(_Other.CachedCSSs)),
	CachedJavaScripts((Trie<WeakPointer<FileContent>>&&)(_Other.CachedJavaScripts)),
	CachedJsons((Trie<WeakPointer<Json>>&&)(_Other.CachedJsons)),
	CachedScriptLibs((Trie<WeakPointer<ScriptLib>>&&)(_Other.CachedScriptLibs)),

	LastWriteRawFiles((Trie<uint64_t>&&)(_Other.LastWriteRawFiles)),
	LastWriteBitMaps((Trie<uint64_t>&&)(_Other.LastWriteBitMaps)),
	LastWriteHdrs((Trie<uint64_t>&&)(_Other.LastWriteHdrs)),
	LastWriteWaves((Trie<uint64_t>&&)(_Other.LastWriteWaves)),
	LastWriteWaveFrontObjs((Trie<uint64_t>&&)(_Other.LastWriteWaveFrontObjs)),
	LastWriteMaterialLibs((Trie<uint64_t>&&)(_Other.LastWriteMaterialLibs)),
	LastWriteGLSLs((Trie<uint64_t>&&)(_Other.LastWriteGLSLs)),
	LastWriteXMLs((Trie<uint64_t>&&)(_Other.LastWriteXMLs)),
	LastWriteCSSs((Trie<uint64_t>&&)(_Other.LastWriteCSSs)),
	LastWriteJavaScripts((Trie<uint64_t>&&)(_Other.LastWriteJavaScripts)),
	LastWriteJsons((Trie<uint64_t>&&)(_Other.LastWriteJsons)),
	LastWriteScriptLibs((Trie<uint64_t>&&)(_Other.LastWriteScriptLibs)),

	OldLastWriteRawFiles((Trie<uint64_t>&&)(_Other.OldLastWriteRawFiles)),
	OldLastWriteBitMaps((Trie<uint64_t>&&)(_Other.OldLastWriteBitMaps)),
	OldLastWriteHdrs((Trie<uint64_t>&&)(_Other.OldLastWriteHdrs)),
	OldLastWriteWaves((Trie<uint64_t>&&)(_Other.OldLastWriteWaves)),
	OldLastWriteWaveFrontObjs((Trie<uint64_t>&&)(_Other.OldLastWriteWaveFrontObjs)),
	OldLastWriteMaterialLibs((Trie<uint64_t>&&)(_Other.OldLastWriteMaterialLibs)),
	OldLastWriteGLSLs((Trie<uint64_t>&&)(_Other.OldLastWriteGLSLs)),
	OldLastWriteXMLs((Trie<uint64_t>&&)(_Other.OldLastWriteXMLs)),
	OldLastWriteCSSs((Trie<uint64_t>&&)(_Other.OldLastWriteCSSs)),
	OldLastWriteJavaScripts((Trie<uint64_t>&&)(_Other.OldLastWriteJavaScripts)),
	OldLastWriteJsons((Trie<uint64_t>&&)(_Other.OldLastWriteJsons)),
	OldLastWriteScriptLibs((Trie<uint64_t>&&)(_Other.OldLastWriteScriptLibs)),

	CachedResourceRawFileNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceRawFileNames)),
	CachedResourceBitMapNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceBitMapNames)),
	CachedResourceHdrNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceHdrNames)),
	CachedResourceWaveNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceWaveNames)),
	CachedResourceWaveFrontObjNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceWaveFrontObjNames)),
	CachedResourceMaterialLibNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceMaterialLibNames)),
	CachedResourceGLSLNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceGLSLNames)),
	CachedResourceXMLNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceXMLNames)),
	CachedResourceCSSNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceCSSNames)),
	CachedResourceJavaScriptNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceJavaScriptNames)),
	CachedResourceJsonNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceJsonNames)),
	CachedResourceScriptLibNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceScriptLibNames)),

	CachedResourceRawFiles((Trie<WeakPointer<FileContent>>&&)(_Other.CachedResourceRawFiles)),
	CachedResourceBitMaps((Trie<WeakPointer<BitMap>>&&)(_Other.CachedResourceBitMaps)),
	CachedResourceHdrs((Trie<WeakPointer<Hdr>>&&)(_Other.CachedResourceHdrs)),
	CachedResourceWaves((Trie<WeakPointer<Wave>>&&)(_Other.CachedResourceWaves)),
	CachedResourceWaveFrontObjs((Trie<WeakPointer<WaveFrontObj>>&&)(_Other.CachedResourceWaveFrontObjs)),
	CachedResourceMaterialLibs((Trie<WeakPointer<MaterialLib>>&&)(_Other.CachedResourceMaterialLibs)),
	CachedResourceGLSLs((Trie<WeakPointer<FileContent>>&&)(_Other.CachedResourceGLSLs)),
	CachedResourceXMLs((Trie<WeakPointer<XML>>&&)(_Other.CachedResourceXMLs)),
	CachedResourceCSSs((Trie<WeakPointer<FileContent>>&&)(_Other.CachedResourceCSSs)),
	CachedResourceJavaScripts((Trie<WeakPointer<FileContent>>&&)(_Other.CachedResourceJavaScripts)),
	CachedResourceJsons((Trie<WeakPointer<Json>>&&)(_Other.CachedResourceJsons)),
	CachedResourceScriptLibs((Trie<WeakPointer<ScriptLib>>&&)(_Other.CachedResourceScriptLibs))
{

}

#endif

#if defined BFW_LINUX_PLATFORM || defined BFW_ESP32_PLATFORM

BFW::Assets::Manager::Manager() :
	QueuedRawFiles(),
	QueuedBitMaps(),
	QueuedHdrs(),
	QueuedWaves(),
	QueuedWaveFrontObjs(),
	QueuedMaterialLibs(),
	QueuedGLSLs(),
	QueuedXMLs(),
	QueuedCSSs(),
	QueuedJavaScripts(),
	QueuedJsons(),
	QueuedScriptLibs(),

	LoadedRawFiles(),
	LoadedBitMaps(),
	LoadedHdrs(),
	LoadedWaves(),
	LoadedWaveFrontObjs(),
	LoadedMaterialLibs(),
	LoadedGLSLs(),
	LoadedXMLs(),
	LoadedCSSs(),
	LoadedJavaScripts(),
	LoadedJsons(),
	LoadedScriptLibs(),

	CachedRawFileNames(),
	CachedBitMapNames(),
	CachedHdrNames(),
	CachedWaveNames(),
	CachedWaveFrontObjNames(),
	CachedMaterialLibNames(),
	CachedGLSLNames(),
	CachedXMLNames(),
	CachedCSSNames(),
	CachedJavaScriptNames(),
	CachedJsonNames(),
	CachedScriptLibNames(),

	CachedRawFiles(),
	CachedBitMaps(),
	CachedHdrs(),
	CachedWaves(),
	CachedWaveFrontObjs(),
	CachedMaterialLibs(),
	CachedGLSLs(),
	CachedXMLs(),
	CachedCSSs(),
	CachedJavaScripts(),
	CachedJsons(),
	CachedScriptLibs(),

	LastWriteRawFiles(),
	LastWriteBitMaps(),
	LastWriteHdrs(),
	LastWriteWaves(),
	LastWriteWaveFrontObjs(),
	LastWriteMaterialLibs(),
	LastWriteGLSLs(),
	LastWriteXMLs(),
	LastWriteCSSs(),
	LastWriteJavaScripts(),
	LastWriteJsons(),
	LastWriteScriptLibs(),

	OldLastWriteRawFiles(),
	OldLastWriteBitMaps(),
	OldLastWriteHdrs(),
	OldLastWriteWaves(),
	OldLastWriteWaveFrontObjs(),
	OldLastWriteMaterialLibs(),
	OldLastWriteGLSLs(),
	OldLastWriteXMLs(),
	OldLastWriteCSSs(),
	OldLastWriteJavaScripts(),
	OldLastWriteJsons(),
	OldLastWriteScriptLibs()
{

}

BFW::Assets::Manager::Manager(Manager&& _Other) noexcept :
	QueuedRawFiles((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedRawFiles)),
	QueuedBitMaps((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedBitMaps)),
	QueuedHdrs((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedHdrs)),
	QueuedWaves((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedWaves)),
	QueuedWaveFrontObjs((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedWaveFrontObjs)),
	QueuedMaterialLibs((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedMaterialLibs)),
	QueuedGLSLs((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedGLSLs)),
	QueuedXMLs((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedXMLs)),
	QueuedCSSs((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedCSSs)),
	QueuedJavaScripts((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedJavaScripts)),
	QueuedJsons((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedJsons)),
	QueuedScriptLibs((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedScriptLibs)),

	LoadedRawFiles((Trie<SharedPointer<FileContent>>&&)(_Other.LoadedRawFiles)),
	LoadedBitMaps((Trie<SharedPointer<BitMap>>&&)(_Other.LoadedBitMaps)),
	LoadedHdrs((Trie<SharedPointer<Hdr>>&&)(_Other.LoadedHdrs)),
	LoadedWaves((Trie<SharedPointer<Wave>>&&)(_Other.LoadedWaves)),
	LoadedWaveFrontObjs((Trie<SharedPointer<WaveFrontObj>>&&)(_Other.LoadedWaveFrontObjs)),
	LoadedMaterialLibs((Trie<SharedPointer<MaterialLib>>&&)(_Other.LoadedMaterialLibs)),
	LoadedGLSLs((Trie<SharedPointer<FileContent>>&&)(_Other.LoadedGLSLs)),
	LoadedXMLs((Trie<SharedPointer<XML>>&&)(_Other.LoadedXMLs)),
	LoadedCSSs((Trie<SharedPointer<FileContent>>&&)(_Other.LoadedCSSs)),
	LoadedJavaScripts((Trie<SharedPointer<FileContent>>&&)(_Other.LoadedJavaScripts)),
	LoadedJsons((Trie<SharedPointer<Json>>&&)(_Other.LoadedJsons)),
	LoadedScriptLibs((Trie<SharedPointer<ScriptLib>>&&)(_Other.LoadedScriptLibs)),

	CachedRawFileNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedRawFileNames)),
	CachedBitMapNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedBitMapNames)),
	CachedHdrNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedHdrNames)),
	CachedWaveNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedWaveNames)),
	CachedWaveFrontObjNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedWaveFrontObjNames)),
	CachedMaterialLibNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedMaterialLibNames)),
	CachedGLSLNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedGLSLNames)),
	CachedXMLNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedXMLNames)),
	CachedCSSNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedCSSNames)),
	CachedJavaScriptNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedJavaScriptNames)),
	CachedJsonNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedJsonNames)),
	CachedScriptLibNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedScriptLibNames)),

	CachedRawFiles((Trie<WeakPointer<FileContent>>&&)(_Other.CachedRawFiles)),
	CachedBitMaps((Trie<WeakPointer<BitMap>>&&)(_Other.CachedBitMaps)),
	CachedHdrs((Trie<WeakPointer<Hdr>>&&)(_Other.CachedHdrs)),
	CachedWaves((Trie<WeakPointer<Wave>>&&)(_Other.CachedWaves)),
	CachedWaveFrontObjs((Trie<WeakPointer<WaveFrontObj>>&&)(_Other.CachedWaveFrontObjs)),
	CachedMaterialLibs((Trie<WeakPointer<MaterialLib>>&&)(_Other.CachedMaterialLibs)),
	CachedGLSLs((Trie<WeakPointer<FileContent>>&&)(_Other.CachedGLSLs)),
	CachedXMLs((Trie<WeakPointer<XML>>&&)(_Other.CachedXMLs)),
	CachedCSSs((Trie<WeakPointer<FileContent>>&&)(_Other.CachedCSSs)),
	CachedJavaScripts((Trie<WeakPointer<FileContent>>&&)(_Other.CachedJavaScripts)),
	CachedJsons((Trie<WeakPointer<Json>>&&)(_Other.CachedJsons)),
	CachedScriptLibs((Trie<WeakPointer<ScriptLib>>&&)(_Other.CachedScriptLibs)),

	LastWriteRawFiles((Trie<uint64_t>&&)(_Other.LastWriteRawFiles)),
	LastWriteBitMaps((Trie<uint64_t>&&)(_Other.LastWriteBitMaps)),
	LastWriteHdrs((Trie<uint64_t>&&)(_Other.LastWriteHdrs)),
	LastWriteWaves((Trie<uint64_t>&&)(_Other.LastWriteWaves)),
	LastWriteWaveFrontObjs((Trie<uint64_t>&&)(_Other.LastWriteWaveFrontObjs)),
	LastWriteMaterialLibs((Trie<uint64_t>&&)(_Other.LastWriteMaterialLibs)),
	LastWriteGLSLs((Trie<uint64_t>&&)(_Other.LastWriteGLSLs)),
	LastWriteXMLs((Trie<uint64_t>&&)(_Other.LastWriteXMLs)),
	LastWriteCSSs((Trie<uint64_t>&&)(_Other.LastWriteCSSs)),
	LastWriteJavaScripts((Trie<uint64_t>&&)(_Other.LastWriteJavaScripts)),
	LastWriteJsons((Trie<uint64_t>&&)(_Other.LastWriteJsons)),
	LastWriteScriptLibs((Trie<uint64_t>&&)(_Other.LastWriteScriptLibs)),

	OldLastWriteRawFiles((Trie<uint64_t>&&)(_Other.OldLastWriteRawFiles)),
	OldLastWriteBitMaps((Trie<uint64_t>&&)(_Other.OldLastWriteBitMaps)),
	OldLastWriteHdrs((Trie<uint64_t>&&)(_Other.OldLastWriteHdrs)),
	OldLastWriteWaves((Trie<uint64_t>&&)(_Other.OldLastWriteWaves)),
	OldLastWriteWaveFrontObjs((Trie<uint64_t>&&)(_Other.OldLastWriteWaveFrontObjs)),
	OldLastWriteMaterialLibs((Trie<uint64_t>&&)(_Other.OldLastWriteMaterialLibs)),
	OldLastWriteGLSLs((Trie<uint64_t>&&)(_Other.OldLastWriteGLSLs)),
	OldLastWriteXMLs((Trie<uint64_t>&&)(_Other.OldLastWriteXMLs)),
	OldLastWriteCSSs((Trie<uint64_t>&&)(_Other.OldLastWriteCSSs)),
	OldLastWriteJavaScripts((Trie<uint64_t>&&)(_Other.OldLastWriteJavaScripts)),
	OldLastWriteJsons((Trie<uint64_t>&&)(_Other.OldLastWriteJsons)),
	OldLastWriteScriptLibs((Trie<uint64_t>&&)(_Other.OldLastWriteScriptLibs))
{

}

#endif

BFW::Assets::Manager::~Manager()
{

}

void BFW::Assets::Manager::QueueRawFile(const BFW_CHAR_TYPE* _Name)
{
	ManagerQueue(_Name, QueuedRawFiles);
}

void BFW::Assets::Manager::QueueBitMap(const BFW_CHAR_TYPE* _Name)
{
	ManagerQueue(_Name, QueuedBitMaps);
}

void BFW::Assets::Manager::QueueHdr(const BFW_CHAR_TYPE* _Name)
{
	ManagerQueue(_Name, QueuedHdrs);
}

void BFW::Assets::Manager::QueueWave(const BFW_CHAR_TYPE* _Name)
{
	ManagerQueue(_Name, QueuedWaves);
}

void BFW::Assets::Manager::QueueWaveFrontObj(const BFW_CHAR_TYPE* _Name)
{
	ManagerQueue(_Name, QueuedWaveFrontObjs);
}

void BFW::Assets::Manager::QueueMaterialLib(const BFW_CHAR_TYPE* _Name)
{
	ManagerQueue(_Name, QueuedMaterialLibs);
}

void BFW::Assets::Manager::QueueGLSL(const BFW_CHAR_TYPE* _Name)
{
	ManagerQueue(_Name, QueuedGLSLs);
}

void BFW::Assets::Manager::QueueXML(const BFW_CHAR_TYPE* _Name)
{
	ManagerQueue(_Name, QueuedXMLs);
}

void BFW::Assets::Manager::QueueCSS(const BFW_CHAR_TYPE* _Name)
{
	ManagerQueue(_Name, QueuedCSSs);
}

void BFW::Assets::Manager::QueueJavaScript(const BFW_CHAR_TYPE* _Name)
{
	ManagerQueue(_Name, QueuedJavaScripts);
}

void BFW::Assets::Manager::QueueJson(const BFW_CHAR_TYPE* _Name)
{
	ManagerQueue(_Name, QueuedJsons);
}

void BFW::Assets::Manager::QueueScriptLib(const BFW_CHAR_TYPE* _Name)
{
	ManagerQueue(_Name, QueuedScriptLibs);
}

#ifdef BFW_WINDOWS_PLATFORM

void BFW::Assets::Manager::QueueResourceRawFile(const size_t _Id)
{
	ManagerQueueResource(_Id, QueuedResourceRawFiles);
}

void BFW::Assets::Manager::QueueResourceBitMap(const size_t _Id)
{
	ManagerQueueResource(_Id, QueuedResourceBitMaps);
}

void BFW::Assets::Manager::QueueResourceHdr(const size_t _Id)
{
	ManagerQueueResource(_Id, QueuedResourceHdrs);
}

void BFW::Assets::Manager::QueueResourceWave(const size_t _Id)
{
	ManagerQueueResource(_Id, QueuedResourceWaves);
}

void BFW::Assets::Manager::QueueResourceWaveFrontObj(const size_t _Id)
{
	ManagerQueueResource(_Id, QueuedResourceWaveFrontObjs);
}

void BFW::Assets::Manager::QueueResourceMaterialLib(const size_t _Id)
{
	ManagerQueueResource(_Id, QueuedResourceMaterialLibs);
}

void BFW::Assets::Manager::QueueResourceGLSL(const size_t _Id)
{
	ManagerQueueResource(_Id, QueuedResourceGLSLs);
}

void BFW::Assets::Manager::QueueResourceXML(const size_t _Id)
{
	ManagerQueueResource(_Id, QueuedResourceXMLs);
}

void BFW::Assets::Manager::QueueResourceCSS(const size_t _Id)
{
	ManagerQueueResource(_Id, QueuedResourceCSSs);
}

void BFW::Assets::Manager::QueueResourceJavaScript(const size_t _Id)
{
	ManagerQueueResource(_Id, QueuedResourceJavaScripts);
}

void BFW::Assets::Manager::QueueResourceJson(const size_t _Id)
{
	ManagerQueueResource(_Id, QueuedResourceJsons);
}

void BFW::Assets::Manager::QueueResourceScriptLib(const size_t _Id)
{
	ManagerQueueResource(_Id, QueuedResourceScriptLibs);
}

#endif

const bool BFW::Assets::Manager::Flush()
{
	RefreshCache();

	bool _Fail = false;
	Vector<std::thread> _Threads;

	ManagerFlushAllocate<FileContent>(QueuedRawFiles, LoadedRawFiles, CachedRawFiles, LastWriteRawFiles, CachedRawFileNames);
	ManagerFlushAllocate<BitMap>(QueuedBitMaps, LoadedBitMaps, CachedBitMaps, LastWriteBitMaps, CachedBitMapNames);
	ManagerFlushAllocate<Hdr>(QueuedHdrs, LoadedHdrs, CachedHdrs, LastWriteHdrs, CachedHdrNames);
	ManagerFlushAllocate<Wave>(QueuedWaves, LoadedWaves, CachedWaves, LastWriteWaves, CachedWaveNames);
	ManagerFlushAllocate<WaveFrontObj>(QueuedWaveFrontObjs, LoadedWaveFrontObjs, CachedWaveFrontObjs, LastWriteWaveFrontObjs, CachedWaveFrontObjNames);
	ManagerFlushAllocate<MaterialLib>(QueuedMaterialLibs, LoadedMaterialLibs, CachedMaterialLibs, LastWriteMaterialLibs, CachedMaterialLibNames);
	ManagerFlushAllocate<FileContent>(QueuedGLSLs, LoadedGLSLs, CachedGLSLs, LastWriteGLSLs, CachedGLSLNames);
	ManagerFlushAllocate<XML>(QueuedXMLs, LoadedXMLs, CachedXMLs, LastWriteXMLs, CachedXMLNames);
	ManagerFlushAllocate<FileContent>(QueuedCSSs, LoadedCSSs, CachedCSSs, LastWriteCSSs, CachedCSSNames);
	ManagerFlushAllocate<FileContent>(QueuedJavaScripts, LoadedJavaScripts, CachedJavaScripts, LastWriteJavaScripts, CachedJavaScriptNames);
	ManagerFlushAllocate<Json>(QueuedJsons, LoadedJsons, CachedJsons, LastWriteJsons, CachedJsonNames);
	ManagerFlushAllocate<ScriptLib>(QueuedScriptLibs, LoadedScriptLibs, CachedScriptLibs, LastWriteScriptLibs, CachedScriptLibNames);

	ManagerFlushSpawn<FileContent>(_Threads, _Fail, QueuedRawFiles, LoadedRawFiles, LastWriteRawFiles, ManagerRawFileLoader);
	ManagerFlushSpawn<BitMap>(_Threads, _Fail, QueuedBitMaps, LoadedBitMaps, LastWriteBitMaps, ManagerBitMapLoader);
	ManagerFlushSpawn<Hdr>(_Threads, _Fail, QueuedHdrs, LoadedHdrs, LastWriteHdrs, ManagerHdrLoader);
	ManagerFlushSpawn<Wave>(_Threads, _Fail, QueuedWaves, LoadedWaves, LastWriteWaves, ManagerWaveLoader);
	ManagerFlushSpawn<WaveFrontObj>(_Threads, _Fail, QueuedWaveFrontObjs, LoadedWaveFrontObjs, LastWriteWaveFrontObjs, ManagerWaveFrontObjLoader);
	ManagerFlushSpawn<MaterialLib>(_Threads, _Fail, QueuedMaterialLibs, LoadedMaterialLibs, LastWriteMaterialLibs, ManagerMaterialLibLoader);
	ManagerFlushSpawn<FileContent>(_Threads, _Fail, QueuedGLSLs, LoadedGLSLs, LastWriteGLSLs, ManagerGLSLLoader);
	ManagerFlushSpawn<XML>(_Threads, _Fail, QueuedXMLs, LoadedXMLs, LastWriteXMLs, ManagerXMLLoader);
	ManagerFlushSpawn<FileContent>(_Threads, _Fail, QueuedCSSs, LoadedCSSs, LastWriteCSSs, ManagerCSSLoader);
	ManagerFlushSpawn<FileContent>(_Threads, _Fail, QueuedJavaScripts, LoadedJavaScripts, LastWriteJavaScripts, ManagerJavaScriptLoader);
	ManagerFlushSpawn<Json>(_Threads, _Fail, QueuedJsons, LoadedJsons, LastWriteJsons, ManagerJsonLoader);
	ManagerFlushSpawn<ScriptLib>(_Threads, _Fail, QueuedScriptLibs, LoadedScriptLibs, LastWriteScriptLibs, ManagerScriptLibLoader);

#ifdef BFW_WINDOWS_PLATFORM

	ManagerFlushAllocateResource<FileContent>(QueuedResourceRawFiles, LoadedResourceRawFiles, CachedResourceRawFiles, CachedResourceRawFileNames);
	ManagerFlushAllocateResource<BitMap>(QueuedResourceBitMaps, LoadedResourceBitMaps, CachedResourceBitMaps, CachedResourceBitMapNames);
	ManagerFlushAllocateResource<Hdr>(QueuedResourceHdrs, LoadedResourceHdrs, CachedResourceHdrs, CachedResourceHdrNames);
	ManagerFlushAllocateResource<Wave>(QueuedResourceWaves, LoadedResourceWaves, CachedResourceWaves, CachedResourceWaveNames);
	ManagerFlushAllocateResource<WaveFrontObj>(QueuedResourceWaveFrontObjs, LoadedResourceWaveFrontObjs, CachedResourceWaveFrontObjs, CachedResourceWaveFrontObjNames);
	ManagerFlushAllocateResource<MaterialLib>(QueuedResourceMaterialLibs, LoadedResourceMaterialLibs, CachedResourceMaterialLibs, CachedResourceMaterialLibNames);
	ManagerFlushAllocateResource<FileContent>(QueuedResourceGLSLs, LoadedResourceGLSLs, CachedResourceGLSLs, CachedResourceGLSLNames);
	ManagerFlushAllocateResource<XML>(QueuedResourceXMLs, LoadedResourceXMLs, CachedResourceXMLs, CachedResourceXMLNames);
	ManagerFlushAllocateResource<FileContent>(QueuedResourceCSSs, LoadedResourceCSSs, CachedResourceCSSs, CachedResourceCSSNames);
	ManagerFlushAllocateResource<FileContent>(QueuedResourceJavaScripts, LoadedResourceJavaScripts, CachedResourceJavaScripts, CachedResourceJavaScriptNames);
	ManagerFlushAllocateResource<Json>(QueuedResourceJsons, LoadedResourceJsons, CachedResourceJsons, CachedResourceJsonNames);
	ManagerFlushAllocateResource<ScriptLib>(QueuedResourceScriptLibs, LoadedResourceScriptLibs, CachedResourceScriptLibs, CachedResourceScriptLibNames);

	ManagerFlushSpawnResource<FileContent>(_Threads, _Fail, QueuedResourceRawFiles, BFW_RAW_RESOURCE, LoadedResourceRawFiles, ManagerRawFileLoader);
	ManagerFlushSpawnResource<BitMap>(_Threads, _Fail, QueuedResourceBitMaps, BFW_BMP_RESOURCE, LoadedResourceBitMaps, ManagerBitMapLoader);
	ManagerFlushSpawnResource<Hdr>(_Threads, _Fail, QueuedResourceHdrs, BFW_HDR_RESOURCE, LoadedResourceHdrs, ManagerHdrLoader);
	ManagerFlushSpawnResource<Wave>(_Threads, _Fail, QueuedResourceWaves, BFW_WAV_RESOURCE, LoadedResourceWaves, ManagerWaveLoader);
	ManagerFlushSpawnResource<WaveFrontObj>(_Threads, _Fail, QueuedResourceWaveFrontObjs, BFW_WFOBJ_RESOURCE, LoadedResourceWaveFrontObjs, ManagerWaveFrontObjLoader);
	ManagerFlushSpawnResource<MaterialLib>(_Threads, _Fail, QueuedResourceMaterialLibs, BFW_MTL_RESOURCE, LoadedResourceMaterialLibs, ManagerMaterialLibLoader);
	ManagerFlushSpawnResource<FileContent>(_Threads, _Fail, QueuedResourceGLSLs, BFW_GLSL_RESOURCE, LoadedResourceGLSLs, ManagerGLSLLoader);
	ManagerFlushSpawnResource<XML>(_Threads, _Fail, QueuedResourceXMLs, BFW_XML_RESOURCE, LoadedResourceXMLs, ManagerXMLLoader);
	ManagerFlushSpawnResource<FileContent>(_Threads, _Fail, QueuedResourceCSSs, BFW_CSS_RESOURCE, LoadedResourceCSSs, ManagerCSSLoader);
	ManagerFlushSpawnResource<FileContent>(_Threads, _Fail, QueuedResourceJavaScripts, BFW_JS_RESOURCE, LoadedResourceJavaScripts, ManagerJavaScriptLoader);
	ManagerFlushSpawnResource<Json>(_Threads, _Fail, QueuedResourceJsons, BFW_JSON_RESOURCE, LoadedResourceJsons, ManagerJsonLoader);
	ManagerFlushSpawnResource<ScriptLib>(_Threads, _Fail, QueuedResourceScriptLibs, BFW_JSON_RESOURCE, LoadedResourceScriptLibs, ManagerScriptLibLoader);

#endif

	for (size_t _Index = 0; _Index < _Threads.GetSize(); _Index++)
	{
		_Threads[_Index].join();
	}

	if (_Fail)
	{
		QueuedRawFiles.Clear();
		QueuedBitMaps.Clear();
		QueuedHdrs.Clear();
		QueuedWaves.Clear();
		QueuedWaveFrontObjs.Clear();
		QueuedMaterialLibs.Clear();
		QueuedGLSLs.Clear();
		QueuedXMLs.Clear();
		QueuedCSSs.Clear();
		QueuedJavaScripts.Clear();
		QueuedJsons.Clear();
		QueuedScriptLibs.Clear();

#ifdef BFW_WINDOWS_PLATFORM

		QueuedResourceRawFiles.Clear();
		QueuedResourceBitMaps.Clear();
		QueuedResourceHdrs.Clear();
		QueuedResourceWaves.Clear();
		QueuedResourceWaveFrontObjs.Clear();
		QueuedResourceMaterialLibs.Clear();
		QueuedResourceGLSLs.Clear();
		QueuedResourceXMLs.Clear();
		QueuedResourceCSSs.Clear();
		QueuedResourceJavaScripts.Clear();
		QueuedResourceJsons.Clear();
		QueuedResourceScriptLibs.Clear();

#endif

		return false;
	}

	Vector<BFW_STRING_TYPE> _NewQueuedRawFiles;
	Vector<BFW_STRING_TYPE> _NewQueuedBitMaps;
	Vector<BFW_STRING_TYPE> _NewQueuedHdrs;
	Vector<BFW_STRING_TYPE> _NewQueuedWaves;
	Vector<BFW_STRING_TYPE> _NewQueuedWaveFrontObjs;
	Vector<BFW_STRING_TYPE> _NewQueuedMaterialLibs;
	Vector<BFW_STRING_TYPE> _NewQueuedGLSLs;
	Vector<BFW_STRING_TYPE> _NewQueuedXMLs;
	Vector<BFW_STRING_TYPE> _NewQueuedCSSs;
	Vector<BFW_STRING_TYPE> _NewQueuedJavaScripts;
	Vector<BFW_STRING_TYPE> _NewQueuedJsons;
	Vector<BFW_STRING_TYPE> _NewQueuedScriptLibs;

	Trie<bool> _TrieNewQueuedRawFiles;
	Trie<bool> _TrieNewQueuedBitMaps;
	Trie<bool> _TrieNewQueuedHdrs;
	Trie<bool> _TrieNewQueuedWaves;
	Trie<bool> _TrieNewQueuedWaveFrontObjs;
	Trie<bool> _TrieNewQueuedMaterialLibs;
	Trie<bool> _TrieNewQueuedGLSLs;
	Trie<bool> _TrieNewQueuedXMLs;
	Trie<bool> _TrieNewQueuedCSSs;
	Trie<bool> _TrieNewQueuedJavaScripts;
	Trie<bool> _TrieNewQueuedJsons;
	Trie<bool> _TrieNewQueuedScriptLibs;

#ifdef BFW_WINDOWS_PLATFORM

	Vector<size_t> _NewQueuedResourceRawFiles;
	Vector<size_t> _NewQueuedResourceBitMaps;
	Vector<size_t> _NewQueuedResourceHdrs;
	Vector<size_t> _NewQueuedResourceWaves;
	Vector<size_t> _NewQueuedResourceWaveFrontObjs;
	Vector<size_t> _NewQueuedResourceMaterialLibs;
	Vector<size_t> _NewQueuedResourceGLSLs;
	Vector<size_t> _NewQueuedResourceXMLs;
	Vector<size_t> _NewQueuedResourceCSSs;
	Vector<size_t> _NewQueuedResourceJavaScripts;
	Vector<size_t> _NewQueuedResourceJsons;
	Vector<size_t> _NewQueuedResourceScriptLibs;

	Trie<bool> _TrieNewQueuedResourceRawFiles;
	Trie<bool> _TrieNewQueuedResourceBitMaps;
	Trie<bool> _TrieNewQueuedResourceHdrs;
	Trie<bool> _TrieNewQueuedResourceWaves;
	Trie<bool> _TrieNewQueuedResourceWaveFrontObjs;
	Trie<bool> _TrieNewQueuedResourceMaterialLibs;
	Trie<bool> _TrieNewQueuedResourceGLSLs;
	Trie<bool> _TrieNewQueuedResourceXMLs;
	Trie<bool> _TrieNewQueuedResourceCSSs;
	Trie<bool> _TrieNewQueuedResourceJavaScripts;
	Trie<bool> _TrieNewQueuedResourceJsons;
	Trie<bool> _TrieNewQueuedResourceScriptLibs;

#endif

#ifdef BFW_WINDOWS_PLATFORM

	ManagerFlushQueueNext<WaveFrontObj, MaterialLib>(QueuedWaveFrontObjs, LoadedWaveFrontObjs, LoadedMaterialLibs, LoadedResourceMaterialLibs, CachedMaterialLibs, CachedResourceMaterialLibs, _NewQueuedMaterialLibs, _TrieNewQueuedMaterialLibs, _NewQueuedResourceMaterialLibs, _TrieNewQueuedResourceMaterialLibs, &WaveFrontObj::GetMaterialLibs);
	ManagerFlushQueueNext<MaterialLib, BitMap>(QueuedMaterialLibs, LoadedMaterialLibs, LoadedBitMaps, LoadedResourceBitMaps, CachedBitMaps, CachedResourceBitMaps, _NewQueuedBitMaps, _TrieNewQueuedBitMaps, _NewQueuedResourceBitMaps, _TrieNewQueuedResourceBitMaps, &MaterialLib::GetBitMaps);
	ManagerFlushQueueNext<MaterialLib, Hdr>(QueuedMaterialLibs, LoadedMaterialLibs, LoadedHdrs, LoadedResourceHdrs, CachedHdrs, CachedResourceHdrs, _NewQueuedHdrs, _TrieNewQueuedHdrs, _NewQueuedResourceHdrs, _TrieNewQueuedResourceHdrs, &MaterialLib::GetHdrs);

	ManagerFlushResourceQueueNext<WaveFrontObj, MaterialLib>(QueuedResourceWaveFrontObjs, LoadedWaveFrontObjs, LoadedMaterialLibs, LoadedResourceMaterialLibs, CachedMaterialLibs, CachedResourceMaterialLibs, _NewQueuedMaterialLibs, _TrieNewQueuedMaterialLibs, _NewQueuedResourceMaterialLibs, _TrieNewQueuedResourceMaterialLibs, &WaveFrontObj::GetMaterialLibs);
	ManagerFlushResourceQueueNext<MaterialLib, BitMap>(QueuedResourceMaterialLibs, LoadedMaterialLibs, LoadedBitMaps, LoadedResourceBitMaps, CachedBitMaps, CachedResourceBitMaps, _NewQueuedBitMaps, _TrieNewQueuedBitMaps, _NewQueuedResourceBitMaps, _TrieNewQueuedResourceBitMaps, &MaterialLib::GetBitMaps);
	ManagerFlushResourceQueueNext<MaterialLib, Hdr>(QueuedResourceMaterialLibs, LoadedMaterialLibs, LoadedHdrs, LoadedResourceHdrs, CachedHdrs, CachedResourceHdrs, _NewQueuedHdrs, _TrieNewQueuedHdrs, _NewQueuedResourceHdrs, _TrieNewQueuedResourceHdrs, &MaterialLib::GetHdrs);

#endif

#if defined BFW_LINUX_PLATFORM || defined BFW_ESP32_PLATFORM

	ManagerFlushQueueNext<WaveFrontObj, MaterialLib>(QueuedWaveFrontObjs, LoadedWaveFrontObjs, LoadedMaterialLibs, CachedMaterialLibs, _NewQueuedMaterialLibs, _TrieNewQueuedMaterialLibs, &WaveFrontObj::GetMaterialLibs);
	ManagerFlushQueueNext<MaterialLib, BitMap>(QueuedMaterialLibs, LoadedMaterialLibs, LoadedBitMaps, CachedBitMaps, _NewQueuedBitMaps, _TrieNewQueuedBitMaps, &MaterialLib::GetBitMaps);
	ManagerFlushQueueNext<MaterialLib, Hdr>(QueuedMaterialLibs, LoadedMaterialLibs, LoadedHdrs, CachedHdrs, _NewQueuedHdrs, _TrieNewQueuedHdrs, &MaterialLib::GetHdrs);

#endif

	QueuedRawFiles = (Vector<BFW_STRING_TYPE>&&)(_NewQueuedRawFiles);
	QueuedBitMaps = (Vector<BFW_STRING_TYPE>&&)(_NewQueuedBitMaps);
	QueuedHdrs = (Vector<BFW_STRING_TYPE>&&)(_NewQueuedHdrs);
	QueuedWaves = (Vector<BFW_STRING_TYPE>&&)(_NewQueuedWaves);
	QueuedWaveFrontObjs = (Vector<BFW_STRING_TYPE>&&)(_NewQueuedWaveFrontObjs);
	QueuedMaterialLibs = (Vector<BFW_STRING_TYPE>&&)(_NewQueuedMaterialLibs);
	QueuedGLSLs = (Vector<BFW_STRING_TYPE>&&)(_NewQueuedGLSLs);
	QueuedXMLs = (Vector<BFW_STRING_TYPE>&&)(_NewQueuedXMLs);
	QueuedCSSs = (Vector<BFW_STRING_TYPE>&&)(_NewQueuedCSSs);
	QueuedJavaScripts = (Vector<BFW_STRING_TYPE>&&)(_NewQueuedJavaScripts);
	QueuedJsons = (Vector<BFW_STRING_TYPE>&&)(_NewQueuedJsons);
	QueuedScriptLibs = (Vector<BFW_STRING_TYPE>&&)(_NewQueuedScriptLibs);

#ifdef BFW_WINDOWS_PLATFORM

	QueuedResourceRawFiles = (Vector<size_t>&&)(_NewQueuedResourceRawFiles);
	QueuedResourceBitMaps = (Vector<size_t>&&)(_NewQueuedResourceBitMaps);
	QueuedResourceHdrs = (Vector<size_t>&&)(_NewQueuedResourceHdrs);
	QueuedResourceWaves = (Vector<size_t>&&)(_NewQueuedResourceWaves);
	QueuedResourceWaveFrontObjs = (Vector<size_t>&&)(_NewQueuedResourceWaveFrontObjs);
	QueuedResourceMaterialLibs = (Vector<size_t>&&)(_NewQueuedResourceMaterialLibs);
	QueuedResourceGLSLs = (Vector<size_t>&&)(_NewQueuedResourceGLSLs);
	QueuedResourceXMLs = (Vector<size_t>&&)(_NewQueuedResourceXMLs);
	QueuedResourceCSSs = (Vector<size_t>&&)(_NewQueuedResourceCSSs);
	QueuedResourceJavaScripts = (Vector<size_t>&&)(_NewQueuedResourceJavaScripts);
	QueuedResourceJsons = (Vector<size_t>&&)(_NewQueuedResourceJsons);
	QueuedResourceScriptLibs = (Vector<size_t>&&)(_NewQueuedResourceScriptLibs);

#endif

	if
	(
		QueuedRawFiles.GetSize() ||
		QueuedBitMaps.GetSize() ||
		QueuedHdrs.GetSize() ||
		QueuedWaves.GetSize() ||
		QueuedWaveFrontObjs.GetSize() ||
		QueuedMaterialLibs.GetSize() ||
		QueuedGLSLs.GetSize() ||
		QueuedXMLs.GetSize() ||
		QueuedCSSs.GetSize() ||
		QueuedJavaScripts.GetSize() ||
		QueuedJsons.GetSize() ||
		QueuedScriptLibs.GetSize()
	)
	{
		return Flush();
	}

#ifdef BFW_WINDOWS_PLATFORM

	else if
	(
		QueuedResourceRawFiles.GetSize() ||
		QueuedResourceBitMaps.GetSize() ||
		QueuedResourceHdrs.GetSize() ||
		QueuedResourceWaves.GetSize() ||
		QueuedResourceWaveFrontObjs.GetSize() ||
		QueuedResourceMaterialLibs.GetSize() ||
		QueuedResourceGLSLs.GetSize() ||
		QueuedResourceXMLs.GetSize() ||
		QueuedResourceCSSs.GetSize() ||
		QueuedResourceJavaScripts.GetSize() ||
		QueuedResourceJsons.GetSize() ||
		QueuedResourceScriptLibs.GetSize()
	)
	{
		return Flush();
	}

#endif

	return true;
}

void BFW::Assets::Manager::AddDynamicRawFile(const BFW_CHAR_TYPE* _Name, SharedPointer<FileContent> _Asset)
{
	ManagerAddDynamic<FileContent>(_Name, _Asset, LoadedRawFiles, CachedRawFiles, CachedRawFileNames);
}

void BFW::Assets::Manager::AddDynamicBitMap(const BFW_CHAR_TYPE* _Name, SharedPointer<BitMap> _Asset)
{
	ManagerAddDynamic<BitMap>(_Name, _Asset, LoadedBitMaps, CachedBitMaps, CachedBitMapNames);
}

void BFW::Assets::Manager::AddDynamicHdr(const BFW_CHAR_TYPE* _Name, SharedPointer<Hdr> _Asset)
{
	ManagerAddDynamic<Hdr>(_Name, _Asset, LoadedHdrs, CachedHdrs, CachedHdrNames);
}

void BFW::Assets::Manager::AddDynamicWave(const BFW_CHAR_TYPE* _Name, SharedPointer<Wave> _Asset)
{
	ManagerAddDynamic<Wave>(_Name, _Asset, LoadedWaves, CachedWaves, CachedWaveNames);
}

void BFW::Assets::Manager::AddDynamicWaveFrontObj(const BFW_CHAR_TYPE* _Name, SharedPointer<WaveFrontObj> _Asset)
{
	ManagerAddDynamic<WaveFrontObj>(_Name, _Asset, LoadedWaveFrontObjs, CachedWaveFrontObjs, CachedWaveFrontObjNames);
}

void BFW::Assets::Manager::AddDynamicMaterialLib(const BFW_CHAR_TYPE* _Name, SharedPointer<MaterialLib> _Asset)
{
	ManagerAddDynamic<MaterialLib>(_Name, _Asset, LoadedMaterialLibs, CachedMaterialLibs, CachedMaterialLibNames);
}

void BFW::Assets::Manager::AddDynamicGLSL(const BFW_CHAR_TYPE* _Name, SharedPointer<FileContent> _Asset)
{
	ManagerAddDynamic<FileContent>(_Name, _Asset, LoadedGLSLs, CachedGLSLs, CachedGLSLNames);
}

void BFW::Assets::Manager::AddDynamicXML(const BFW_CHAR_TYPE* _Name, SharedPointer<XML> _Asset)
{
	ManagerAddDynamic<XML>(_Name, _Asset, LoadedXMLs, CachedXMLs, CachedXMLNames);
}

void BFW::Assets::Manager::AddDynamicCSS(const BFW_CHAR_TYPE* _Name, SharedPointer<FileContent> _Asset)
{
	ManagerAddDynamic<FileContent>(_Name, _Asset, LoadedCSSs, CachedCSSs, CachedCSSNames);
}

void BFW::Assets::Manager::AddDynamicJavaScript(const BFW_CHAR_TYPE* _Name, SharedPointer<FileContent> _Asset)
{
	ManagerAddDynamic<FileContent>(_Name, _Asset, LoadedJavaScripts, CachedJavaScripts, CachedJavaScriptNames);
}

void BFW::Assets::Manager::AddDynamicJson(const BFW_CHAR_TYPE* _Name, SharedPointer<Json> _Asset)
{
	ManagerAddDynamic<Json>(_Name, _Asset, LoadedJsons, CachedJsons, CachedJsonNames);
}

void BFW::Assets::Manager::AddDynamicScriptLib(const BFW_CHAR_TYPE* _Name, SharedPointer<ScriptLib> _Asset)
{
	ManagerAddDynamic<ScriptLib>(_Name, _Asset, LoadedScriptLibs, CachedScriptLibs, CachedScriptLibNames);
}

void BFW::Assets::Manager::AddDynamicRawFileRef(const BFW_CHAR_TYPE* _Name, SharedPointer<FileContent>& _Asset)
{
	ManagerAddDynamicRef<FileContent>(_Name, _Asset, CachedRawFiles, CachedRawFileNames);
}

void BFW::Assets::Manager::AddDynamicBitMapRef(const BFW_CHAR_TYPE* _Name, SharedPointer<BitMap>& _Asset)
{
	ManagerAddDynamicRef<BitMap>(_Name, _Asset, CachedBitMaps, CachedBitMapNames);
}

void BFW::Assets::Manager::AddDynamicHdrRef(const BFW_CHAR_TYPE* _Name, SharedPointer<Hdr>& _Asset)
{
	ManagerAddDynamicRef<Hdr>(_Name, _Asset, CachedHdrs, CachedHdrNames);
}

void BFW::Assets::Manager::AddDynamicWaveRef(const BFW_CHAR_TYPE* _Name, SharedPointer<Wave>& _Asset)
{
	ManagerAddDynamicRef<Wave>(_Name, _Asset, CachedWaves, CachedWaveNames);
}

void BFW::Assets::Manager::AddDynamicWaveFrontObjRef(const BFW_CHAR_TYPE* _Name, SharedPointer<WaveFrontObj>& _Asset)
{
	ManagerAddDynamicRef<WaveFrontObj>(_Name, _Asset, CachedWaveFrontObjs, CachedWaveFrontObjNames);
}

void BFW::Assets::Manager::AddDynamicMaterialLibRef(const BFW_CHAR_TYPE* _Name, SharedPointer<MaterialLib>& _Asset)
{
	ManagerAddDynamicRef<MaterialLib>(_Name, _Asset, CachedMaterialLibs, CachedMaterialLibNames);
}

void BFW::Assets::Manager::AddDynamicGLSLRef(const BFW_CHAR_TYPE* _Name, SharedPointer<FileContent>& _Asset)
{
	ManagerAddDynamicRef<FileContent>(_Name, _Asset, CachedGLSLs, CachedGLSLNames);
}

void BFW::Assets::Manager::AddDynamicXMLRef(const BFW_CHAR_TYPE* _Name, SharedPointer<XML>& _Asset)
{
	ManagerAddDynamicRef<XML>(_Name, _Asset, CachedXMLs, CachedXMLNames);
}

void BFW::Assets::Manager::AddDynamicCSSRef(const BFW_CHAR_TYPE* _Name, SharedPointer<FileContent>& _Asset)
{
	ManagerAddDynamicRef<FileContent>(_Name, _Asset, CachedCSSs, CachedCSSNames);
}

void BFW::Assets::Manager::AddDynamicJavaScriptRef(const BFW_CHAR_TYPE* _Name, SharedPointer<FileContent>& _Asset)
{
	ManagerAddDynamicRef<FileContent>(_Name, _Asset, CachedJavaScripts, CachedJavaScriptNames);
}

void BFW::Assets::Manager::AddDynamicJsonRef(const BFW_CHAR_TYPE* _Name, SharedPointer<Json>& _Asset)
{
	ManagerAddDynamicRef<Json>(_Name, _Asset, CachedJsons, CachedJsonNames);
}

void BFW::Assets::Manager::AddDynamicScriptLibRef(const BFW_CHAR_TYPE* _Name, SharedPointer<ScriptLib>& _Asset)
{
	ManagerAddDynamicRef<ScriptLib>(_Name, _Asset, CachedScriptLibs, CachedScriptLibNames);
}

void BFW::Assets::Manager::Update()
{
	RefreshCache();

	OldLastWriteRawFiles = LastWriteRawFiles;
	OldLastWriteBitMaps = LastWriteBitMaps;
	OldLastWriteHdrs = LastWriteHdrs;
	OldLastWriteWaves = LastWriteWaves;
	OldLastWriteWaveFrontObjs = LastWriteWaveFrontObjs;
	OldLastWriteMaterialLibs = LastWriteMaterialLibs;
	OldLastWriteGLSLs = LastWriteGLSLs;
	OldLastWriteXMLs = LastWriteXMLs;
	OldLastWriteCSSs = LastWriteCSSs;
	OldLastWriteJavaScripts = LastWriteJavaScripts;
	OldLastWriteJsons = LastWriteJsons;
	OldLastWriteScriptLibs = LastWriteScriptLibs;

	Vector<std::thread> _Threads;

	ManagerUpdate<FileContent>(_Threads, CachedRawFiles, LastWriteRawFiles, CachedRawFileNames, ManagerRawFileLoader);
	ManagerUpdate<BitMap>(_Threads, CachedBitMaps, LastWriteBitMaps, CachedBitMapNames, ManagerBitMapLoader);
	ManagerUpdate<Hdr>(_Threads, CachedHdrs, LastWriteHdrs, CachedHdrNames, ManagerHdrLoader);
	ManagerUpdate<Wave>(_Threads, CachedWaves, LastWriteWaves, CachedWaveNames, ManagerWaveLoader);
	ManagerUpdate<WaveFrontObj>(_Threads, CachedWaveFrontObjs, LastWriteWaveFrontObjs, CachedWaveFrontObjNames, ManagerWaveFrontObjLoader);
	ManagerUpdate<MaterialLib>(_Threads, CachedMaterialLibs, LastWriteMaterialLibs, CachedMaterialLibNames, ManagerMaterialLibLoader);
	ManagerUpdate<FileContent>(_Threads, CachedGLSLs, LastWriteGLSLs, CachedGLSLNames, ManagerGLSLLoader);
	ManagerUpdate<XML>(_Threads, CachedXMLs, LastWriteXMLs, CachedXMLNames, ManagerXMLLoader);
	ManagerUpdate<FileContent>(_Threads, CachedCSSs, LastWriteCSSs, CachedCSSNames, ManagerCSSLoader);
	ManagerUpdate<FileContent>(_Threads, CachedJavaScripts, LastWriteJavaScripts, CachedJavaScriptNames, ManagerJavaScriptLoader);
	ManagerUpdate<Json>(_Threads, CachedJsons, LastWriteJsons, CachedJsonNames, ManagerJsonLoader);
	ManagerUpdate<ScriptLib>(_Threads, CachedScriptLibs, LastWriteScriptLibs, CachedScriptLibNames, ManagerScriptLibLoader);

	for (size_t _Index = 0; _Index < _Threads.GetSize(); _Index++)
	{
		_Threads[_Index].join();
	}
}

void BFW::Assets::Manager::ReleaseRawFile(const BFW_CHAR_TYPE* _Name)
{
	ManagerRelease<FileContent>(_Name, LoadedRawFiles);
}

void BFW::Assets::Manager::ReleaseBitMap(const BFW_CHAR_TYPE* _Name)
{
	ManagerRelease<BitMap>(_Name, LoadedBitMaps);
}

void BFW::Assets::Manager::ReleaseHdr(const BFW_CHAR_TYPE* _Name)
{
	ManagerRelease<Hdr>(_Name, LoadedHdrs);
}

void BFW::Assets::Manager::ReleaseWave(const BFW_CHAR_TYPE* _Name)
{
	ManagerRelease<Wave>(_Name, LoadedWaves);
}

void BFW::Assets::Manager::ReleaseWaveFrontObj(const BFW_CHAR_TYPE* _Name)
{
	ManagerRelease<WaveFrontObj>(_Name, LoadedWaveFrontObjs);
}

void BFW::Assets::Manager::ReleaseMaterialLib(const BFW_CHAR_TYPE* _Name)
{
	ManagerRelease<MaterialLib>(_Name, LoadedMaterialLibs);
}

void BFW::Assets::Manager::ReleaseGLSL(const BFW_CHAR_TYPE* _Name)
{
	ManagerRelease<FileContent>(_Name, LoadedGLSLs);
}

void BFW::Assets::Manager::ReleaseXML(const BFW_CHAR_TYPE* _Name)
{
	ManagerRelease<XML>(_Name, LoadedXMLs);
}

void BFW::Assets::Manager::ReleaseCSS(const BFW_CHAR_TYPE* _Name)
{
	ManagerRelease<FileContent>(_Name, LoadedCSSs);
}

void BFW::Assets::Manager::ReleaseJavaScript(const BFW_CHAR_TYPE* _Name)
{
	ManagerRelease<FileContent>(_Name, LoadedJavaScripts);
}

void BFW::Assets::Manager::ReleaseJson(const BFW_CHAR_TYPE* _Name)
{
	ManagerRelease<Json>(_Name, LoadedJsons);
}

void BFW::Assets::Manager::ReleaseScriptLib(const BFW_CHAR_TYPE* _Name)
{
	ManagerRelease<ScriptLib>(_Name, LoadedScriptLibs);
}

#ifdef BFW_WINDOWS_PLATFORM

void BFW::Assets::Manager::ReleaseResourceRawFile(const size_t _Id)
{
	ManagerReleaseResource<FileContent>(_Id, LoadedResourceRawFiles);
}

void BFW::Assets::Manager::ReleaseResourceBitMap(const size_t _Id)
{
	ManagerReleaseResource<BitMap>(_Id, LoadedResourceBitMaps);
}

void BFW::Assets::Manager::ReleaseResourceHdr(const size_t _Id)
{
	ManagerReleaseResource<Hdr>(_Id, LoadedResourceHdrs);
}

void BFW::Assets::Manager::ReleaseResourceWave(const size_t _Id)
{
	ManagerReleaseResource<Wave>(_Id, LoadedResourceWaves);
}

void BFW::Assets::Manager::ReleaseResourceWaveFrontObj(const size_t _Id)
{
	ManagerReleaseResource<WaveFrontObj>(_Id, LoadedResourceWaveFrontObjs);
}

void BFW::Assets::Manager::ReleaseResourceMaterialLib(const size_t _Id)
{
	ManagerReleaseResource<MaterialLib>(_Id, LoadedResourceMaterialLibs);
}

void BFW::Assets::Manager::ReleaseResourceGLSL(const size_t _Id)
{
	ManagerReleaseResource<FileContent>(_Id, LoadedResourceGLSLs);
}

void BFW::Assets::Manager::ReleaseResourceXML(const size_t _Id)
{
	ManagerReleaseResource<XML>(_Id, LoadedResourceXMLs);
}

void BFW::Assets::Manager::ReleaseResourceCSS(const size_t _Id)
{
	ManagerReleaseResource<FileContent>(_Id, LoadedResourceCSSs);
}

void BFW::Assets::Manager::ReleaseResourceJavaScript(const size_t _Id)
{
	ManagerReleaseResource<FileContent>(_Id, LoadedResourceJavaScripts);
}

void BFW::Assets::Manager::ReleaseResourceJson(const size_t _Id)
{
	ManagerReleaseResource<Json>(_Id, LoadedResourceJsons);
}

void BFW::Assets::Manager::ReleaseResourceScriptLib(const size_t _Id)
{
	ManagerReleaseResource<ScriptLib>(_Id, LoadedResourceScriptLibs);
}

#endif

const bool BFW::Assets::Manager::WasRawFileUpdated(const BFW_CHAR_TYPE* _Name)
{
	return ManagerWasUpdated(_Name, LastWriteRawFiles, OldLastWriteRawFiles);
}

const bool BFW::Assets::Manager::WasBitMapUpdated(const BFW_CHAR_TYPE* _Name)
{
	return ManagerWasUpdated(_Name, LastWriteBitMaps, OldLastWriteBitMaps);
}

const bool BFW::Assets::Manager::WasHdrUpdated(const BFW_CHAR_TYPE* _Name)
{
	return ManagerWasUpdated(_Name, LastWriteHdrs, OldLastWriteHdrs);
}

const bool BFW::Assets::Manager::WasWaveUpdated(const BFW_CHAR_TYPE* _Name)
{
	return ManagerWasUpdated(_Name, LastWriteWaves, OldLastWriteWaves);
}

const bool BFW::Assets::Manager::WasWaveFrontObjUpdated(const BFW_CHAR_TYPE* _Name)
{
	return ManagerWasUpdated(_Name, LastWriteWaveFrontObjs, OldLastWriteWaveFrontObjs);
}

const bool BFW::Assets::Manager::WasMaterialLibUpdated(const BFW_CHAR_TYPE* _Name)
{
	return ManagerWasUpdated(_Name, LastWriteMaterialLibs, OldLastWriteMaterialLibs);
}

const bool BFW::Assets::Manager::WasGLSLUpdated(const BFW_CHAR_TYPE* _Name)
{
	return ManagerWasUpdated(_Name, LastWriteGLSLs, OldLastWriteGLSLs);
}

const bool BFW::Assets::Manager::WasXMLUpdated(const BFW_CHAR_TYPE* _Name)
{
	return ManagerWasUpdated(_Name, LastWriteXMLs, OldLastWriteXMLs);
}

const bool BFW::Assets::Manager::WasCSSUpdated(const BFW_CHAR_TYPE* _Name)
{
	return ManagerWasUpdated(_Name, LastWriteCSSs, OldLastWriteCSSs);
}

const bool BFW::Assets::Manager::WasJavaScriptUpdated(const BFW_CHAR_TYPE* _Name)
{
	return ManagerWasUpdated(_Name, LastWriteJavaScripts, OldLastWriteJavaScripts);
}

const bool BFW::Assets::Manager::WasJsonUpdated(const BFW_CHAR_TYPE* _Name)
{
	return ManagerWasUpdated(_Name, LastWriteJsons, OldLastWriteJsons);
}

const bool BFW::Assets::Manager::WasScriptLibUpdated(const BFW_CHAR_TYPE* _Name)
{
	return ManagerWasUpdated(_Name, LastWriteScriptLibs, OldLastWriteScriptLibs);
}

BFW::SharedPointer<BFW::Assets::FileContent> BFW::Assets::Manager::GetRawFile(const BFW_CHAR_TYPE* _Name)
{
	return ManagerGet<FileContent>(_Name, CachedRawFiles, LastWriteRawFiles, CachedRawFileNames, ManagerRawFileLoader);
}

const BFW::SharedPointer<BFW::Assets::FileContent> BFW::Assets::Manager::GetRawFile(const BFW_CHAR_TYPE* _Name) const
{
	return ManagerGet<FileContent>(_Name, CachedRawFiles, LastWriteRawFiles, CachedRawFileNames, ManagerRawFileLoader);
}

BFW::SharedPointer<BFW::Assets::BitMap> BFW::Assets::Manager::GetBitMap(const BFW_CHAR_TYPE* _Name)
{
	return ManagerGet<BitMap>(_Name, CachedBitMaps, LastWriteBitMaps, CachedBitMapNames, ManagerBitMapLoader);
}

const BFW::SharedPointer<BFW::Assets::BitMap> BFW::Assets::Manager::GetBitMap(const BFW_CHAR_TYPE* _Name) const
{
	return ManagerGet<BitMap>(_Name, CachedBitMaps, LastWriteBitMaps, CachedBitMapNames, ManagerBitMapLoader);
}

BFW::SharedPointer<BFW::Assets::Hdr> BFW::Assets::Manager::GetHdr(const BFW_CHAR_TYPE* _Name)
{
	return ManagerGet<Hdr>(_Name, CachedHdrs, LastWriteHdrs, CachedHdrNames, ManagerHdrLoader);
}

const BFW::SharedPointer<BFW::Assets::Hdr> BFW::Assets::Manager::GetHdr(const BFW_CHAR_TYPE* _Name) const
{
	return ManagerGet<Hdr>(_Name, CachedHdrs, LastWriteHdrs, CachedHdrNames, ManagerHdrLoader);
}

BFW::SharedPointer<BFW::Assets::Wave> BFW::Assets::Manager::GetWave(const BFW_CHAR_TYPE* _Name)
{
	return ManagerGet<Wave>(_Name, CachedWaves, LastWriteWaves, CachedWaveNames, ManagerWaveLoader);
}

const BFW::SharedPointer<BFW::Assets::Wave> BFW::Assets::Manager::GetWave(const BFW_CHAR_TYPE* _Name) const
{
	return ManagerGet<Wave>(_Name, CachedWaves, LastWriteWaves, CachedWaveNames, ManagerWaveLoader);
}

BFW::SharedPointer<BFW::Assets::WaveFrontObj> BFW::Assets::Manager::GetWaveFrontObj(const BFW_CHAR_TYPE* _Name)
{
	return ManagerGet<WaveFrontObj>(_Name, CachedWaveFrontObjs, LastWriteWaveFrontObjs, CachedWaveFrontObjNames, ManagerWaveFrontObjLoader);
}

const BFW::SharedPointer<BFW::Assets::WaveFrontObj> BFW::Assets::Manager::GetWaveFrontObj(const BFW_CHAR_TYPE* _Name) const
{
	return ManagerGet<WaveFrontObj>(_Name, CachedWaveFrontObjs, LastWriteWaveFrontObjs, CachedWaveFrontObjNames, ManagerWaveFrontObjLoader);
}

BFW::SharedPointer<BFW::Assets::MaterialLib> BFW::Assets::Manager::GetMaterialLib(const BFW_CHAR_TYPE* _Name)
{
	return ManagerGet<MaterialLib>(_Name, CachedMaterialLibs, LastWriteMaterialLibs, CachedMaterialLibNames, ManagerMaterialLibLoader);
}

const BFW::SharedPointer<BFW::Assets::MaterialLib> BFW::Assets::Manager::GetMaterialLib(const BFW_CHAR_TYPE* _Name) const
{
	return ManagerGet<MaterialLib>(_Name, CachedMaterialLibs, LastWriteMaterialLibs, CachedMaterialLibNames, ManagerMaterialLibLoader);
}

BFW::SharedPointer<BFW::Assets::FileContent> BFW::Assets::Manager::GetGLSL(const BFW_CHAR_TYPE* _Name)
{
	return ManagerGet<FileContent>(_Name, CachedGLSLs, LastWriteGLSLs, CachedGLSLNames, ManagerGLSLLoader);
}

const BFW::SharedPointer<BFW::Assets::FileContent> BFW::Assets::Manager::GetGLSL(const BFW_CHAR_TYPE* _Name) const
{
	return ManagerGet<FileContent>(_Name, CachedGLSLs, LastWriteGLSLs, CachedGLSLNames, ManagerGLSLLoader);
}

BFW::SharedPointer<BFW::Assets::XML> BFW::Assets::Manager::GetXML(const BFW_CHAR_TYPE* _Name)
{
	return ManagerGet<XML>(_Name, CachedXMLs, LastWriteXMLs, CachedXMLNames, ManagerXMLLoader);
}

const BFW::SharedPointer<BFW::Assets::XML> BFW::Assets::Manager::GetXML(const BFW_CHAR_TYPE* _Name) const
{
	return ManagerGet<XML>(_Name, CachedXMLs, LastWriteXMLs, CachedXMLNames, ManagerXMLLoader);
}

BFW::SharedPointer<BFW::Assets::FileContent> BFW::Assets::Manager::GetCSS(const BFW_CHAR_TYPE* _Name)
{
	return ManagerGet<FileContent>(_Name, CachedCSSs, LastWriteCSSs, CachedCSSNames, ManagerCSSLoader);
}

const BFW::SharedPointer<BFW::Assets::FileContent> BFW::Assets::Manager::GetCSS(const BFW_CHAR_TYPE* _Name) const
{
	return ManagerGet<FileContent>(_Name, CachedCSSs, LastWriteCSSs, CachedCSSNames, ManagerCSSLoader);
}

BFW::SharedPointer<BFW::Assets::FileContent> BFW::Assets::Manager::GetJavaScript(const BFW_CHAR_TYPE* _Name)
{
	return ManagerGet<FileContent>(_Name, CachedJavaScripts, LastWriteJavaScripts, CachedJavaScriptNames, ManagerJavaScriptLoader);
}

const BFW::SharedPointer<BFW::Assets::FileContent> BFW::Assets::Manager::GetJavaScript(const BFW_CHAR_TYPE* _Name) const
{
	return ManagerGet<FileContent>(_Name, CachedJavaScripts, LastWriteJavaScripts, CachedJavaScriptNames, ManagerJavaScriptLoader);
}

BFW::SharedPointer<BFW::Assets::Json> BFW::Assets::Manager::GetJson(const BFW_CHAR_TYPE* _Name)
{
	return ManagerGet<Json>(_Name, CachedJsons, LastWriteJsons, CachedJsonNames, ManagerJsonLoader);
}

const BFW::SharedPointer<BFW::Assets::Json> BFW::Assets::Manager::GetJson(const BFW_CHAR_TYPE* _Name) const
{
	return ManagerGet<Json>(_Name, CachedJsons, LastWriteJsons, CachedJsonNames, ManagerJsonLoader);
}

BFW::SharedPointer<BFW::Assets::ScriptLib> BFW::Assets::Manager::GetScriptLib(const BFW_CHAR_TYPE* _Name)
{
	return ManagerGet<ScriptLib>(_Name, CachedScriptLibs, LastWriteScriptLibs, CachedScriptLibNames, ManagerScriptLibLoader);
}

const BFW::SharedPointer<BFW::Assets::ScriptLib> BFW::Assets::Manager::GetScriptLib(const BFW_CHAR_TYPE* _Name) const
{
	return ManagerGet<ScriptLib>(_Name, CachedScriptLibs, LastWriteScriptLibs, CachedScriptLibNames, ManagerScriptLibLoader);
}

#ifdef BFW_WINDOWS_PLATFORM

BFW::SharedPointer<BFW::Assets::FileContent> BFW::Assets::Manager::GetResourceRawFile(const size_t _Id)
{
	return ManagerGetResource<FileContent>(_Id, BFW_RAW_RESOURCE, CachedResourceRawFiles, CachedResourceRawFileNames, ManagerRawFileLoader);
}

const BFW::SharedPointer<BFW::Assets::FileContent> BFW::Assets::Manager::GetResourceRawFile(const size_t _Id) const
{
	return ManagerGetResource<FileContent>(_Id, BFW_RAW_RESOURCE, CachedResourceRawFiles, CachedResourceRawFileNames, ManagerRawFileLoader);
}

BFW::SharedPointer<BFW::Assets::BitMap> BFW::Assets::Manager::GetResourceBitMap(const size_t _Id)
{
	return ManagerGetResource<BitMap>(_Id, BFW_BMP_RESOURCE, CachedResourceBitMaps, CachedResourceBitMapNames, ManagerBitMapLoader);
}

const BFW::SharedPointer<BFW::Assets::BitMap> BFW::Assets::Manager::GetResourceBitMap(const size_t _Id) const
{
	return ManagerGetResource<BitMap>(_Id, BFW_BMP_RESOURCE, CachedResourceBitMaps, CachedResourceBitMapNames, ManagerBitMapLoader);
}

BFW::SharedPointer<BFW::Assets::Hdr> BFW::Assets::Manager::GetResourceHdr(const size_t _Id)
{
	return ManagerGetResource<Hdr>(_Id, BFW_HDR_RESOURCE, CachedResourceHdrs, CachedResourceHdrNames, ManagerHdrLoader);
}

const BFW::SharedPointer<BFW::Assets::Hdr> BFW::Assets::Manager::GetResourceHdr(const size_t _Id) const
{
	return ManagerGetResource<Hdr>(_Id, BFW_HDR_RESOURCE, CachedResourceHdrs, CachedResourceHdrNames, ManagerHdrLoader);
}

BFW::SharedPointer<BFW::Assets::Wave> BFW::Assets::Manager::GetResourceWave(const size_t _Id)
{
	return ManagerGetResource<Wave>(_Id, BFW_WAV_RESOURCE, CachedResourceWaves, CachedResourceWaveNames, ManagerWaveLoader);
}

const BFW::SharedPointer<BFW::Assets::Wave> BFW::Assets::Manager::GetResourceWave(const size_t _Id) const
{
	return ManagerGetResource<Wave>(_Id, BFW_WAV_RESOURCE, CachedResourceWaves, CachedResourceWaveNames, ManagerWaveLoader);
}

BFW::SharedPointer<BFW::Assets::WaveFrontObj> BFW::Assets::Manager::GetResourceWaveFrontObj(const size_t _Id)
{
	return ManagerGetResource<WaveFrontObj>(_Id, BFW_WFOBJ_RESOURCE, CachedResourceWaveFrontObjs, CachedResourceWaveFrontObjNames, ManagerWaveFrontObjLoader);
}

const BFW::SharedPointer<BFW::Assets::WaveFrontObj> BFW::Assets::Manager::GetResourceWaveFrontObj(const size_t _Id) const
{
	return ManagerGetResource<WaveFrontObj>(_Id, BFW_WFOBJ_RESOURCE, CachedResourceWaveFrontObjs, CachedResourceWaveFrontObjNames, ManagerWaveFrontObjLoader);
}

BFW::SharedPointer<BFW::Assets::MaterialLib> BFW::Assets::Manager::GetResourceMaterialLib(const size_t _Id)
{
	return ManagerGetResource<MaterialLib>(_Id, BFW_MTL_RESOURCE, CachedResourceMaterialLibs, CachedResourceMaterialLibNames, ManagerMaterialLibLoader);
}

const BFW::SharedPointer<BFW::Assets::MaterialLib> BFW::Assets::Manager::GetResourceMaterialLib(const size_t _Id) const
{
	return ManagerGetResource<MaterialLib>(_Id, BFW_MTL_RESOURCE, CachedResourceMaterialLibs, CachedResourceMaterialLibNames, ManagerMaterialLibLoader);
}

BFW::SharedPointer<BFW::Assets::FileContent> BFW::Assets::Manager::GetResourceGLSL(const size_t _Id)
{
	return ManagerGetResource<FileContent>(_Id, BFW_GLSL_RESOURCE, CachedResourceGLSLs, CachedResourceGLSLNames, ManagerGLSLLoader);
}

const BFW::SharedPointer<BFW::Assets::FileContent> BFW::Assets::Manager::GetResourceGLSL(const size_t _Id) const
{
	return ManagerGetResource<FileContent>(_Id, BFW_GLSL_RESOURCE, CachedResourceGLSLs, CachedResourceGLSLNames, ManagerGLSLLoader);
}

BFW::SharedPointer<BFW::Assets::XML> BFW::Assets::Manager::GetResourceXML(const size_t _Id)
{
	return ManagerGetResource<XML>(_Id, BFW_XML_RESOURCE, CachedResourceXMLs, CachedResourceXMLNames, ManagerXMLLoader);
}

const BFW::SharedPointer<BFW::Assets::XML> BFW::Assets::Manager::GetResourceXML(const size_t _Id) const
{
	return ManagerGetResource<XML>(_Id, BFW_XML_RESOURCE, CachedResourceXMLs, CachedResourceXMLNames, ManagerXMLLoader);
}

BFW::SharedPointer<BFW::Assets::FileContent> BFW::Assets::Manager::GetResourceCSS(const size_t _Id)
{
	return ManagerGetResource<FileContent>(_Id, BFW_CSS_RESOURCE, CachedResourceCSSs, CachedResourceCSSNames, ManagerCSSLoader);
}

const BFW::SharedPointer<BFW::Assets::FileContent> BFW::Assets::Manager::GetResourceCSS(const size_t _Id) const
{
	return ManagerGetResource<FileContent>(_Id, BFW_CSS_RESOURCE, CachedResourceCSSs, CachedResourceCSSNames, ManagerCSSLoader);
}

BFW::SharedPointer<BFW::Assets::FileContent> BFW::Assets::Manager::GetResourceJavaScript(const size_t _Id)
{
	return ManagerGetResource<FileContent>(_Id, BFW_JS_RESOURCE, CachedResourceJavaScripts, CachedResourceJavaScriptNames, ManagerJavaScriptLoader);
}

const BFW::SharedPointer<BFW::Assets::FileContent> BFW::Assets::Manager::GetResourceJavaScript(const size_t _Id) const
{
	return ManagerGetResource<FileContent>(_Id, BFW_JS_RESOURCE, CachedResourceJavaScripts, CachedResourceJavaScriptNames, ManagerJavaScriptLoader);
}

BFW::SharedPointer<BFW::Assets::Json> BFW::Assets::Manager::GetResourceJson(const size_t _Id)
{
	return ManagerGetResource<Json>(_Id, BFW_JSON_RESOURCE, CachedResourceJsons, CachedResourceJsonNames, ManagerJsonLoader);
}

const BFW::SharedPointer<BFW::Assets::Json> BFW::Assets::Manager::GetResourceJson(const size_t _Id) const
{
	return ManagerGetResource<Json>(_Id, BFW_JSON_RESOURCE, CachedResourceJsons, CachedResourceJsonNames, ManagerJsonLoader);
}

BFW::SharedPointer<BFW::Assets::ScriptLib> BFW::Assets::Manager::GetResourceScriptLib(const size_t _Id)
{
	return ManagerGetResource<ScriptLib>(_Id, BFW_JSON_RESOURCE, CachedResourceScriptLibs, CachedResourceScriptLibNames, ManagerScriptLibLoader);
}

const BFW::SharedPointer<BFW::Assets::ScriptLib> BFW::Assets::Manager::GetResourceScriptLib(const size_t _Id) const
{
	return ManagerGetResource<ScriptLib>(_Id, BFW_JSON_RESOURCE, CachedResourceScriptLibs, CachedResourceScriptLibNames, ManagerScriptLibLoader);
}

#endif

BFW::Assets::Mesh* BFW::Assets::Manager::ResolveMesh(const BFW_CHAR_TYPE* _MeshName, const Vector<BFW_STRING_TYPE>& _Files)
{
#ifdef BFW_WINDOWS_PLATFORM

	return ManagerResolveLib<Mesh, WaveFrontObj>(_MeshName, _Files, CachedWaveFrontObjs, CachedWaveFrontObjNames, CachedResourceWaveFrontObjs, CachedResourceWaveFrontObjNames);

#endif

#if defined BFW_LINUX_PLATFORM || defined BFW_ESP32_PLATFORM

	return ManagerResolveLib<Mesh, WaveFrontObj>(_MeshName, _Files, CachedWaveFrontObjs, CachedWaveFrontObjNames);

#endif
}

const BFW::Assets::Mesh* BFW::Assets::Manager::ResolveMesh(const BFW_CHAR_TYPE* _MeshName, const Vector<BFW_STRING_TYPE>& _Files) const
{
#ifdef BFW_WINDOWS_PLATFORM

	return ManagerResolveLib<Mesh, WaveFrontObj>(_MeshName, _Files, CachedWaveFrontObjs, CachedWaveFrontObjNames, CachedResourceWaveFrontObjs, CachedResourceWaveFrontObjNames);

#endif

#if defined BFW_LINUX_PLATFORM || defined BFW_ESP32_PLATFORM

	return ManagerResolveLib<Mesh, WaveFrontObj>(_MeshName, _Files, CachedWaveFrontObjs, CachedWaveFrontObjNames);

#endif
}

const BFW_STRING_TYPE BFW::Assets::Manager::ResolveMeshFile(const BFW_CHAR_TYPE* _MeshName, const Vector<BFW_STRING_TYPE>& _Files) const
{
#ifdef BFW_WINDOWS_PLATFORM

	return ManagerResolveLibFile<Mesh, WaveFrontObj>(_MeshName, _Files, CachedWaveFrontObjs, CachedWaveFrontObjNames, CachedResourceWaveFrontObjs, CachedResourceWaveFrontObjNames);

#endif

#if defined BFW_LINUX_PLATFORM || defined BFW_ESP32_PLATFORM

	return ManagerResolveLibFile<Mesh, WaveFrontObj>(_MeshName, _Files, CachedWaveFrontObjs, CachedWaveFrontObjNames);

#endif
}

BFW::Assets::Material* BFW::Assets::Manager::ResolveMaterial(const BFW_CHAR_TYPE* _MaterialName, const Vector<BFW_STRING_TYPE>& _Files)
{
#ifdef BFW_WINDOWS_PLATFORM

	return ManagerResolveLib<Material, MaterialLib>(_MaterialName, _Files, CachedMaterialLibs, CachedMaterialLibNames, CachedResourceMaterialLibs, CachedResourceMaterialLibNames);

#endif

#if defined BFW_LINUX_PLATFORM || defined BFW_ESP32_PLATFORM

	return ManagerResolveLib<Material, MaterialLib>(_MaterialName, _Files, CachedMaterialLibs, CachedMaterialLibNames);

#endif
}

const BFW::Assets::Material* BFW::Assets::Manager::ResolveMaterial(const BFW_CHAR_TYPE* _MaterialName, const Vector<BFW_STRING_TYPE>& _Files) const
{
#ifdef BFW_WINDOWS_PLATFORM

	return ManagerResolveLib<Material, MaterialLib>(_MaterialName, _Files, CachedMaterialLibs, CachedMaterialLibNames, CachedResourceMaterialLibs, CachedResourceMaterialLibNames);

#endif

#if defined BFW_LINUX_PLATFORM || defined BFW_ESP32_PLATFORM

	return ManagerResolveLib<Material, MaterialLib>(_MaterialName, _Files, CachedMaterialLibs, CachedMaterialLibNames);

#endif
}

const BFW_STRING_TYPE BFW::Assets::Manager::ResolveMaterialFile(const BFW_CHAR_TYPE* _MaterialName, const Vector<BFW_STRING_TYPE>& _Files) const
{
#ifdef BFW_WINDOWS_PLATFORM

	return ManagerResolveLibFile<Material, MaterialLib>(_MaterialName, _Files, CachedMaterialLibs, CachedMaterialLibNames, CachedResourceMaterialLibs, CachedResourceMaterialLibNames);

#endif

#if defined BFW_LINUX_PLATFORM || defined BFW_ESP32_PLATFORM

	return ManagerResolveLibFile<Material, MaterialLib>(_MaterialName, _Files, CachedMaterialLibs, CachedMaterialLibNames);

#endif
}

const bool BFW::Assets::Manager::SaveWaveFrontObj(const BFW_CHAR_TYPE* _Name, const BFW_STRING_VIEW_TYPE& _FileName, Vector<BFW_STRING_TYPE>& _Paths, Vector<FileContent>& _FileContents) const
{
	if (!_Name || _Name[0] == BFW_STRING_PREFIX('\0') || !_FileName.data())
	{
		return false;
	}

	_Paths.Clear();
	_FileContents.Clear();

	Vector<BFW_STRING_TYPE> _FinalPaths;
	Vector<FileContent> _FinalFileContents;

	Trie<BFW_STRING_TYPE> _FoundMaterialLib;
	size_t _MaterialLibRefCount = 0;

	Trie<BFW_STRING_TYPE> _BitMapTextureNames;
	_BitMapTextureNames.Push(BFW_STRING_PREFIX(""), BFW_STRING_PREFIX(""));
	size_t _BitMapTextureIndex = 0;

	Trie<BFW_STRING_TYPE> _HdrTextureNames;
	_HdrTextureNames.Push(BFW_STRING_PREFIX(""), BFW_STRING_PREFIX(""));
	size_t _HdrTextureIndex = 0;

	SharedPointer<WaveFrontObj> _WaveFrontObj = GetWaveFrontObj(_Name);

#ifdef BFW_WINDOWS_PLATFORM

	if (!(WaveFrontObj*)(_WaveFrontObj))
	{
		size_t _Id = 0;
		BFW_STRING_STREAM_TYPE _Stream(_Name);

		if ((_Stream >> _Id) && _Stream.eof())
		{
			_WaveFrontObj = GetResourceWaveFrontObj(_Id);
		}
	}

#endif

	if (!(WaveFrontObj*)(_WaveFrontObj))
	{
		return false;
	}

	WaveFrontObj _NewWaveFrontObj = *_WaveFrontObj;

	Vector<BFW_STRING_TYPE> _MaterialLibs = _WaveFrontObj->GetMaterialLibs();

	for (size_t _MaterialLibIndex = 0; _MaterialLibIndex < _MaterialLibs.GetSize(); _MaterialLibIndex++)
	{
		BFW_STRING_TYPE& _MaterialLibName = _MaterialLibs[_MaterialLibIndex];

		BFW_STRING_TYPE* _TrieString = _FoundMaterialLib.GetData(_MaterialLibName.c_str());

		if (_TrieString)
		{
			_NewWaveFrontObj.GetMaterialLibsRef()[_MaterialLibIndex] = *_TrieString;
			continue;
		}

		if (_MaterialLibRefCount == 0)
		{
			_NewWaveFrontObj.GetMaterialLibsRef()[_MaterialLibIndex] = BFW_STRING_TYPE(_FileName) + BFW_STRING_PREFIX(".mtl");
		}
		else
		{
			_NewWaveFrontObj.GetMaterialLibsRef()[_MaterialLibIndex] = BFW_STRING_TYPE(_FileName) + BFW_TO_STRING(_MaterialLibRefCount + 1) + BFW_STRING_PREFIX(".mtl");
		}
		_MaterialLibRefCount++;
		_FoundMaterialLib.Push(_MaterialLibName.c_str(), _NewWaveFrontObj.GetMaterialLibsRef()[_MaterialLibIndex]);

		SharedPointer<MaterialLib> _MaterialLib = GetMaterialLib(_MaterialLibName.c_str());

#ifdef BFW_WINDOWS_PLATFORM

		if (!(MaterialLib*)(_MaterialLib))
		{
			size_t _Id = 0;
			BFW_STRING_STREAM_TYPE _Stream(_MaterialLibName);

			if ((_Stream >> _Id) && _Stream.eof())
			{
				_MaterialLib = GetResourceMaterialLib(_Id);
			}
		}

#endif

		if (!(MaterialLib*)(_MaterialLib))
		{
			return false;
		}

		MaterialLib _NewMaterialLib = *_MaterialLib;

		Vector<BFW_STRING_TYPE> _BitMaps = _MaterialLib->GetBitMaps();

		for (size_t _BitMapIndex = 0; _BitMapIndex < _BitMaps.GetSize(); _BitMapIndex++)
		{
			BFW_STRING_TYPE& _BitMapName = _BitMaps[_BitMapIndex];

			if (_BitMapTextureNames.GetData(_BitMapName.c_str()))
			{
				continue;
			}

			BFW_STRING_TYPE _BitMapTextureName = BFW_STRING_TYPE(_FileName) + BFW_TO_STRING(_BitMapTextureIndex + 1) + BFW_STRING_PREFIX(".bmp");
			_BitMapTextureNames.Push(_BitMapName.c_str(), _BitMapTextureName.c_str());
			_BitMapTextureIndex++;

			SharedPointer<BitMap> _BitMap = GetBitMap(_BitMapName.c_str());

#ifdef BFW_WINDOWS_PLATFORM

			if (!(BitMap*)(_BitMap))
			{
				size_t _Id = 0;
				BFW_STRING_STREAM_TYPE _Stream(_BitMapName);

				if ((_Stream >> _Id) && _Stream.eof())
				{
					_BitMap = GetResourceBitMap(_Id);
				}
			}

#endif

			if (!(BitMap*)(_BitMap))
			{
				return false;
			}

			_FinalPaths.PushBack(_BitMapTextureName);
			_FinalFileContents.PushBack(_BitMap->Save());
			if (_FinalFileContents[_FinalFileContents.GetSize() - 1].GetLength() < 1)
			{
				return false;
			}
		}

		Vector<BFW_STRING_TYPE> _Hdrs = _MaterialLib->GetHdrs();

		for (size_t _HdrIndex = 0; _HdrIndex < _Hdrs.GetSize(); _HdrIndex++)
		{
			BFW_STRING_TYPE& _HdrName = _Hdrs[_HdrIndex];

			if (_HdrTextureNames.GetData(_HdrName.c_str()))
			{
				continue;
			}

			BFW_STRING_TYPE _HdrTextureName = BFW_STRING_TYPE(_FileName) + BFW_TO_STRING(_HdrTextureIndex + 1) + BFW_STRING_PREFIX(".hdr");
			_HdrTextureNames.Push(_HdrName.c_str(), _HdrTextureName.c_str());
			_HdrTextureIndex++;

			SharedPointer<Hdr> _Hdr = GetHdr(_HdrName.c_str());

#ifdef BFW_WINDOWS_PLATFORM

			if (!(Hdr*)(_Hdr))
			{
				size_t _Id = 0;
				BFW_STRING_STREAM_TYPE _Stream(_HdrName);

				if ((_Stream >> _Id) && _Stream.eof())
				{
					_Hdr = GetResourceHdr(_Id);
				}
			}

#endif

			if (!(Hdr*)(_Hdr))
			{
				return false;
			}

			_FinalPaths.PushBack(_HdrTextureName);
			_FinalFileContents.PushBack(_Hdr->Save());
			if (_FinalFileContents[_FinalFileContents.GetSize() - 1].GetLength() < 1)
			{
				return false;
			}
		}

		Vector<BFW_STRING_TYPE> _Materials = _MaterialLib->GetMaterialNames();

		for (size_t _MaterialIndex = 0; _MaterialIndex < _Materials.GetSize(); _MaterialIndex++)
		{
			Material& _Material = _NewMaterialLib[_Materials[_MaterialIndex].c_str()];

			_Material.AlbedoTexture = _BitMapTextureNames[_Material.AlbedoTexture.c_str()];
			_Material.SpecularColorTexture = _BitMapTextureNames[_Material.SpecularColorTexture.c_str()];
			_Material.SpecularExponentTexture = _HdrTextureNames[_Material.SpecularExponentTexture.c_str()];
			_Material.EmissionColorTexture = _HdrTextureNames[_Material.EmissionColorTexture.c_str()];
			_Material.RoughnessTexture = _BitMapTextureNames[_Material.RoughnessTexture.c_str()];
			_Material.MetalnessTexture = _BitMapTextureNames[_Material.MetalnessTexture.c_str()];
			_Material.AmbientOcclusionTexture = _BitMapTextureNames[_Material.AmbientOcclusionTexture.c_str()];
			_Material.AmbientColorTexture = _BitMapTextureNames[_Material.AmbientColorTexture.c_str()];
			_Material.SheenTexture = _BitMapTextureNames[_Material.SheenTexture.c_str()];
			_Material.SheenColorTexture = _BitMapTextureNames[_Material.SheenColorTexture.c_str()];
			_Material.ClearCoatTexture = _BitMapTextureNames[_Material.ClearCoatTexture.c_str()];
			_Material.ClearCoatColorTexture = _BitMapTextureNames[_Material.ClearCoatColorTexture.c_str()];
			_Material.ClearCoatRoughnessTexture = _BitMapTextureNames[_Material.ClearCoatRoughnessTexture.c_str()];
			_Material.AnisotropyTexture = _BitMapTextureNames[_Material.AnisotropyTexture.c_str()];
			_Material.AnisotropyRotationTexture = _BitMapTextureNames[_Material.AnisotropyRotationTexture.c_str()];
			_Material.AlphaTexture = _BitMapTextureNames[_Material.AlphaTexture.c_str()];
			_Material.TransmissionFilterTexture = _HdrTextureNames[_Material.TransmissionFilterTexture.c_str()];
			_Material.DisplacementTexture = _HdrTextureNames[_Material.DisplacementTexture.c_str()];
			_Material.NormalTexture = _BitMapTextureNames[_Material.NormalTexture.c_str()];
			_Material.TangentTexture = _BitMapTextureNames[_Material.TangentTexture.c_str()];
			_Material.ClearCoatNormalTexture = _BitMapTextureNames[_Material.ClearCoatNormalTexture.c_str()];
			_Material.DecalTexture = _BitMapTextureNames[_Material.DecalTexture.c_str()];
			_Material.BumpTexture = _BitMapTextureNames[_Material.BumpTexture.c_str()];

			if (_Material.ReflectionTextures.GetSize() == 1)
			{
				_Material.ReflectionTextures[0] = _HdrTextureNames[_Material.ReflectionTextures[0].c_str()];
			}
			else if (_Material.ReflectionTextures.GetSize() == 6)
			{
				for (size_t _ReflectionIndex = 0; _ReflectionIndex < 6; _ReflectionIndex++)
				{
					_Material.ReflectionTextures[_ReflectionIndex] = _BitMapTextureNames[_Material.ReflectionTextures[_ReflectionIndex].c_str()];
				}
			}
		}

		_FinalPaths.PushBack(_NewWaveFrontObj.GetMaterialLibsRef()[_MaterialLibIndex]);
		_FinalFileContents.PushBack(_NewMaterialLib.Save());
		if (_FinalFileContents[_FinalFileContents.GetSize() - 1].GetLength() < 1)
		{
			return false;
		}
	}

	_FinalPaths.PushBack(BFW_STRING_TYPE(_FileName) + BFW_STRING_PREFIX(".obj"));
	_FinalFileContents.PushBack(_NewWaveFrontObj.Save());
	if (_FinalFileContents[_FinalFileContents.GetSize() - 1].GetLength() < 1)
	{
		return false;
	}

	_Paths = (Vector<BFW_STRING_TYPE>&&)(_FinalPaths);
	_FileContents = (Vector<FileContent>&&)(_FinalFileContents);

	return true;
}

const bool BFW::Assets::Manager::SaveMaterialLib(const BFW_CHAR_TYPE* _Name, const BFW_STRING_VIEW_TYPE& _FileName, Vector<BFW_STRING_TYPE>& _Paths, Vector<FileContent>& _FileContents) const
{
	if (!_Name || _Name[0] == BFW_STRING_PREFIX('\0') || !_FileName.data())
	{
		return false;
	}

	_Paths.Clear();
	_FileContents.Clear();

	Vector<BFW_STRING_TYPE> _FinalPaths;
	Vector<FileContent> _FinalFileContents;

	Trie<BFW_STRING_TYPE> _BitMapTextureNames;
	_BitMapTextureNames.Push(BFW_STRING_PREFIX(""), BFW_STRING_PREFIX(""));
	size_t _BitMapTextureIndex = 0;

	Trie<BFW_STRING_TYPE> _HdrTextureNames;
	_HdrTextureNames.Push(BFW_STRING_PREFIX(""), BFW_STRING_PREFIX(""));
	size_t _HdrTextureIndex = 0;

	SharedPointer<MaterialLib> _MaterialLib = GetMaterialLib(_Name);

#ifdef BFW_WINDOWS_PLATFORM

	if (!(MaterialLib*)(_MaterialLib))
	{
		size_t _Id = 0;
		BFW_STRING_STREAM_TYPE _Stream(_Name);

		if ((_Stream >> _Id) && _Stream.eof())
		{
			_MaterialLib = GetResourceMaterialLib(_Id);
		}
	}

#endif

	if (!(MaterialLib*)(_MaterialLib))
	{
		return false;
	}

	MaterialLib _NewMaterialLib = *_MaterialLib;

	Vector<BFW_STRING_TYPE> _BitMaps = _MaterialLib->GetBitMaps();

	for (size_t _BitMapIndex = 0; _BitMapIndex < _BitMaps.GetSize(); _BitMapIndex++)
	{
		BFW_STRING_TYPE& _BitMapName = _BitMaps[_BitMapIndex];

		if (_BitMapTextureNames.GetData(_BitMapName.c_str()))
		{
			continue;
		}

		BFW_STRING_TYPE _BitMapTextureName = BFW_STRING_TYPE(_FileName) + BFW_TO_STRING(_BitMapTextureIndex + 1) + BFW_STRING_PREFIX(".bmp");
		_BitMapTextureNames.Push(_BitMapName.c_str(), _BitMapTextureName.c_str());
		_BitMapTextureIndex++;

		SharedPointer<BitMap> _BitMap = GetBitMap(_BitMapName.c_str());

#ifdef BFW_WINDOWS_PLATFORM

		if (!(BitMap*)(_BitMap))
		{
			size_t _Id = 0;
			BFW_STRING_STREAM_TYPE _Stream(_BitMapName);

			if ((_Stream >> _Id) && _Stream.eof())
			{
				_BitMap = GetResourceBitMap(_Id);
			}
		}

#endif

		if (!(BitMap*)(_BitMap))
		{
			return false;
		}

		_FinalPaths.PushBack(_BitMapTextureName);
		_FinalFileContents.PushBack(_BitMap->Save());
		if (_FinalFileContents[_FinalFileContents.GetSize() - 1].GetLength() < 1)
		{
			return false;
		}
	}

	Vector<BFW_STRING_TYPE> _Hdrs = _MaterialLib->GetHdrs();

	for (size_t _HdrIndex = 0; _HdrIndex < _Hdrs.GetSize(); _HdrIndex++)
	{
		BFW_STRING_TYPE& _HdrName = _Hdrs[_HdrIndex];

		if (_HdrTextureNames.GetData(_HdrName.c_str()))
		{
			continue;
		}

		BFW_STRING_TYPE _HdrTextureName = BFW_STRING_TYPE(_FileName) + BFW_TO_STRING(_HdrTextureIndex + 1) + BFW_STRING_PREFIX(".hdr");
		_HdrTextureNames.Push(_HdrName.c_str(), _HdrTextureName.c_str());
		_HdrTextureIndex++;

		SharedPointer<Hdr> _Hdr = GetHdr(_HdrName.c_str());

#ifdef BFW_WINDOWS_PLATFORM

		if (!(Hdr*)(_Hdr))
		{
			size_t _Id = 0;
			BFW_STRING_STREAM_TYPE _Stream(_HdrName);

			if ((_Stream >> _Id) && _Stream.eof())
			{
				_Hdr = GetResourceHdr(_Id);
			}
		}

#endif

		if (!(Hdr*)(_Hdr))
		{
			return false;
		}

		_FinalPaths.PushBack(_HdrTextureName);
		_FinalFileContents.PushBack(_Hdr->Save());
		if (_FinalFileContents[_FinalFileContents.GetSize() - 1].GetLength() < 1)
		{
			return false;
		}
	}

	Vector<BFW_STRING_TYPE> _Materials = _MaterialLib->GetMaterialNames();

	for (size_t _MaterialIndex = 0; _MaterialIndex < _Materials.GetSize(); _MaterialIndex++)
	{
		Material& _Material = _NewMaterialLib[_Materials[_MaterialIndex].c_str()];

		_Material.AlbedoTexture = _BitMapTextureNames[_Material.AlbedoTexture.c_str()];
		_Material.SpecularColorTexture = _BitMapTextureNames[_Material.SpecularColorTexture.c_str()];
		_Material.SpecularExponentTexture = _HdrTextureNames[_Material.SpecularExponentTexture.c_str()];
		_Material.EmissionColorTexture = _HdrTextureNames[_Material.EmissionColorTexture.c_str()];
		_Material.RoughnessTexture = _BitMapTextureNames[_Material.RoughnessTexture.c_str()];
		_Material.MetalnessTexture = _BitMapTextureNames[_Material.MetalnessTexture.c_str()];
		_Material.AmbientOcclusionTexture = _BitMapTextureNames[_Material.AmbientOcclusionTexture.c_str()];
		_Material.AmbientColorTexture = _BitMapTextureNames[_Material.AmbientColorTexture.c_str()];
		_Material.SheenTexture = _BitMapTextureNames[_Material.SheenTexture.c_str()];
		_Material.SheenColorTexture = _BitMapTextureNames[_Material.SheenColorTexture.c_str()];
		_Material.ClearCoatTexture = _BitMapTextureNames[_Material.ClearCoatTexture.c_str()];
		_Material.ClearCoatColorTexture = _BitMapTextureNames[_Material.ClearCoatColorTexture.c_str()];
		_Material.ClearCoatRoughnessTexture = _BitMapTextureNames[_Material.ClearCoatRoughnessTexture.c_str()];
		_Material.AnisotropyTexture = _BitMapTextureNames[_Material.AnisotropyTexture.c_str()];
		_Material.AnisotropyRotationTexture = _BitMapTextureNames[_Material.AnisotropyRotationTexture.c_str()];
		_Material.AlphaTexture = _BitMapTextureNames[_Material.AlphaTexture.c_str()];
		_Material.TransmissionFilterTexture = _HdrTextureNames[_Material.TransmissionFilterTexture.c_str()];
		_Material.DisplacementTexture = _HdrTextureNames[_Material.DisplacementTexture.c_str()];
		_Material.NormalTexture = _BitMapTextureNames[_Material.NormalTexture.c_str()];
		_Material.TangentTexture = _BitMapTextureNames[_Material.TangentTexture.c_str()];
		_Material.ClearCoatNormalTexture = _BitMapTextureNames[_Material.ClearCoatNormalTexture.c_str()];
		_Material.DecalTexture = _BitMapTextureNames[_Material.DecalTexture.c_str()];
		_Material.BumpTexture = _BitMapTextureNames[_Material.BumpTexture.c_str()];

		if (_Material.ReflectionTextures.GetSize() == 1)
		{
			_Material.ReflectionTextures[0] = _HdrTextureNames[_Material.ReflectionTextures[0].c_str()];
		}
		else if (_Material.ReflectionTextures.GetSize() == 6)
		{
			for (size_t _ReflectionIndex = 0; _ReflectionIndex < 6; _ReflectionIndex++)
			{
				_Material.ReflectionTextures[_ReflectionIndex] = _BitMapTextureNames[_Material.ReflectionTextures[_ReflectionIndex].c_str()];
			}
		}
	}

	_FinalPaths.PushBack(BFW_STRING_TYPE(_FileName) + BFW_STRING_PREFIX(".mtl"));
	_FinalFileContents.PushBack(_NewMaterialLib.Save());
	if (_FinalFileContents[_FinalFileContents.GetSize() - 1].GetLength() < 1)
	{
		return false;
	}

	_Paths = (Vector<BFW_STRING_TYPE>&&)(_FinalPaths);
	_FileContents = (Vector<FileContent>&&)(_FinalFileContents);

	return true;
}

const bool BFW::Assets::Manager::StartAllScripts()
{
	RefreshCache();

	bool _Result = true;

	for (size_t _Index = 0; _Index < CachedScriptLibNames.GetSize(); _Index++)
	{
		if (!CachedScriptLibs.GetData(CachedScriptLibNames[_Index].c_str())->Lock()->Start())
		{
			_Result = false;
		}
	}

#ifdef BFW_WINDOWS_PLATFORM

	for (size_t _Index = 0; _Index < CachedResourceScriptLibNames.GetSize(); _Index++)
	{
		if (!CachedResourceScriptLibs.GetData(CachedResourceScriptLibNames[_Index].c_str())->Lock()->Start())
		{
			_Result = false;
		}
	}

#endif

	return _Result;
}

void BFW::Assets::Manager::StopAllScripts()
{
	RefreshCache();

	for (size_t _Index = 0; _Index < CachedScriptLibNames.GetSize(); _Index++)
	{
		CachedScriptLibs.GetData(CachedScriptLibNames[_Index].c_str())->Lock()->Stop();
	}

#ifdef BFW_WINDOWS_PLATFORM

	for (size_t _Index = 0; _Index < CachedResourceScriptLibNames.GetSize(); _Index++)
	{
		CachedResourceScriptLibs.GetData(CachedResourceScriptLibNames[_Index].c_str())->Lock()->Stop();
	}

#endif
}

#ifdef BFW_WINDOWS_PLATFORM

BFW::Assets::Manager& BFW::Assets::Manager::operator= (Manager&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	QueuedRawFiles = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedRawFiles);
	QueuedBitMaps = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedBitMaps);
	QueuedHdrs = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedHdrs);
	QueuedWaves = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedWaves);
	QueuedWaveFrontObjs = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedWaveFrontObjs);
	QueuedMaterialLibs = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedMaterialLibs);
	QueuedGLSLs = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedGLSLs);
	QueuedXMLs = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedXMLs);
	QueuedCSSs = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedCSSs);
	QueuedJavaScripts = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedJavaScripts);
	QueuedJsons = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedJsons);
	QueuedScriptLibs = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedScriptLibs);

	QueuedResourceRawFiles = (Vector<size_t>&&)(_Other.QueuedResourceRawFiles);
	QueuedResourceBitMaps = (Vector<size_t>&&)(_Other.QueuedResourceBitMaps);
	QueuedResourceHdrs = (Vector<size_t>&&)(_Other.QueuedResourceHdrs);
	QueuedResourceWaves = (Vector<size_t>&&)(_Other.QueuedResourceWaves);
	QueuedResourceWaveFrontObjs = (Vector<size_t>&&)(_Other.QueuedResourceWaveFrontObjs);
	QueuedResourceMaterialLibs = (Vector<size_t>&&)(_Other.QueuedResourceMaterialLibs);
	QueuedResourceGLSLs = (Vector<size_t>&&)(_Other.QueuedResourceGLSLs);
	QueuedResourceXMLs = (Vector<size_t>&&)(_Other.QueuedResourceXMLs);
	QueuedResourceCSSs = (Vector<size_t>&&)(_Other.QueuedResourceCSSs);
	QueuedResourceJavaScripts = (Vector<size_t>&&)(_Other.QueuedResourceJavaScripts);
	QueuedResourceJsons = (Vector<size_t>&&)(_Other.QueuedResourceJsons);
	QueuedResourceScriptLibs = (Vector<size_t>&&)(_Other.QueuedResourceScriptLibs);

	LoadedRawFiles = (Trie<SharedPointer<FileContent>>&&)(_Other.LoadedRawFiles);
	LoadedBitMaps = (Trie<SharedPointer<BitMap>>&&)(_Other.LoadedBitMaps);
	LoadedHdrs = (Trie<SharedPointer<Hdr>>&&)(_Other.LoadedHdrs);
	LoadedWaves = (Trie<SharedPointer<Wave>>&&)(_Other.LoadedWaves);
	LoadedWaveFrontObjs = (Trie<SharedPointer<WaveFrontObj>>&&)(_Other.LoadedWaveFrontObjs);
	LoadedMaterialLibs = (Trie<SharedPointer<MaterialLib>>&&)(_Other.LoadedMaterialLibs);
	LoadedGLSLs = (Trie<SharedPointer<FileContent>>&&)(_Other.LoadedGLSLs);
	LoadedXMLs = (Trie<SharedPointer<XML>>&&)(_Other.LoadedXMLs);
	LoadedCSSs = (Trie<SharedPointer<FileContent>>&&)(_Other.LoadedCSSs);
	LoadedJavaScripts = (Trie<SharedPointer<FileContent>>&&)(_Other.LoadedJavaScripts);
	LoadedJsons = (Trie<SharedPointer<Json>>&&)(_Other.LoadedJsons);
	LoadedScriptLibs = (Trie<SharedPointer<ScriptLib>>&&)(_Other.LoadedScriptLibs);

	LoadedResourceRawFiles = (Trie<SharedPointer<FileContent>>&&)(_Other.LoadedResourceRawFiles);
	LoadedResourceBitMaps = (Trie<SharedPointer<BitMap>>&&)(_Other.LoadedResourceBitMaps);
	LoadedResourceHdrs = (Trie<SharedPointer<Hdr>>&&)(_Other.LoadedResourceHdrs);
	LoadedResourceWaves = (Trie<SharedPointer<Wave>>&&)(_Other.LoadedResourceWaves);
	LoadedResourceWaveFrontObjs = (Trie<SharedPointer<WaveFrontObj>>&&)(_Other.LoadedResourceWaveFrontObjs);
	LoadedResourceMaterialLibs = (Trie<SharedPointer<MaterialLib>>&&)(_Other.LoadedResourceMaterialLibs);
	LoadedResourceGLSLs = (Trie<SharedPointer<FileContent>>&&)(_Other.LoadedResourceGLSLs);
	LoadedResourceXMLs = (Trie<SharedPointer<XML>>&&)(_Other.LoadedResourceXMLs);
	LoadedResourceCSSs = (Trie<SharedPointer<FileContent>>&&)(_Other.LoadedResourceCSSs);
	LoadedResourceJavaScripts = (Trie<SharedPointer<FileContent>>&&)(_Other.LoadedResourceJavaScripts);
	LoadedResourceJsons = (Trie<SharedPointer<Json>>&&)(_Other.LoadedResourceJsons);
	LoadedResourceScriptLibs = (Trie<SharedPointer<ScriptLib>>&&)(_Other.LoadedResourceScriptLibs);

	CachedRawFileNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedRawFileNames);
	CachedBitMapNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedBitMapNames);
	CachedHdrNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedHdrNames);
	CachedWaveNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedWaveNames);
	CachedWaveFrontObjNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedWaveFrontObjNames);
	CachedMaterialLibNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedMaterialLibNames);
	CachedGLSLNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedGLSLNames);
	CachedXMLNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedXMLNames);
	CachedCSSNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedCSSNames);
	CachedJavaScriptNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedJavaScriptNames);
	CachedJsonNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedJsonNames);
	CachedScriptLibNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedScriptLibNames);

	CachedRawFiles = (Trie<WeakPointer<FileContent>>&&)(_Other.CachedRawFiles);
	CachedBitMaps = (Trie<WeakPointer<BitMap>>&&)(_Other.CachedBitMaps);
	CachedHdrs = (Trie<WeakPointer<Hdr>>&&)(_Other.CachedHdrs);
	CachedWaves = (Trie<WeakPointer<Wave>>&&)(_Other.CachedWaves);
	CachedWaveFrontObjs = (Trie<WeakPointer<WaveFrontObj>>&&)(_Other.CachedWaveFrontObjs);
	CachedMaterialLibs = (Trie<WeakPointer<MaterialLib>>&&)(_Other.CachedMaterialLibs);
	CachedGLSLs = (Trie<WeakPointer<FileContent>>&&)(_Other.CachedGLSLs);
	CachedXMLs = (Trie<WeakPointer<XML>>&&)(_Other.CachedXMLs);
	CachedCSSs = (Trie<WeakPointer<FileContent>>&&)(_Other.CachedCSSs);
	CachedJavaScripts = (Trie<WeakPointer<FileContent>>&&)(_Other.CachedJavaScripts);
	CachedJsons = (Trie<WeakPointer<Json>>&&)(_Other.CachedJsons);
	CachedScriptLibs = (Trie<WeakPointer<ScriptLib>>&&)(_Other.CachedScriptLibs);

	LastWriteRawFiles = (Trie<uint64_t>&&)(_Other.LastWriteRawFiles);
	LastWriteBitMaps = (Trie<uint64_t>&&)(_Other.LastWriteBitMaps);
	LastWriteHdrs = (Trie<uint64_t>&&)(_Other.LastWriteHdrs);
	LastWriteWaves = (Trie<uint64_t>&&)(_Other.LastWriteWaves);
	LastWriteWaveFrontObjs = (Trie<uint64_t>&&)(_Other.LastWriteWaveFrontObjs);
	LastWriteMaterialLibs = (Trie<uint64_t>&&)(_Other.LastWriteMaterialLibs);
	LastWriteGLSLs = (Trie<uint64_t>&&)(_Other.LastWriteGLSLs);
	LastWriteXMLs = (Trie<uint64_t>&&)(_Other.LastWriteXMLs);
	LastWriteCSSs = (Trie<uint64_t>&&)(_Other.LastWriteCSSs);
	LastWriteJavaScripts = (Trie<uint64_t>&&)(_Other.LastWriteJavaScripts);
	LastWriteJsons = (Trie<uint64_t>&&)(_Other.LastWriteJsons);
	LastWriteScriptLibs = (Trie<uint64_t>&&)(_Other.LastWriteScriptLibs);

	OldLastWriteRawFiles = (Trie<uint64_t>&&)(_Other.OldLastWriteRawFiles);
	OldLastWriteBitMaps = (Trie<uint64_t>&&)(_Other.OldLastWriteBitMaps);
	OldLastWriteHdrs = (Trie<uint64_t>&&)(_Other.OldLastWriteHdrs);
	OldLastWriteWaves = (Trie<uint64_t>&&)(_Other.OldLastWriteWaves);
	OldLastWriteWaveFrontObjs = (Trie<uint64_t>&&)(_Other.OldLastWriteWaveFrontObjs);
	OldLastWriteMaterialLibs = (Trie<uint64_t>&&)(_Other.OldLastWriteMaterialLibs);
	OldLastWriteGLSLs = (Trie<uint64_t>&&)(_Other.OldLastWriteGLSLs);
	OldLastWriteXMLs = (Trie<uint64_t>&&)(_Other.OldLastWriteXMLs);
	OldLastWriteCSSs = (Trie<uint64_t>&&)(_Other.OldLastWriteCSSs);
	OldLastWriteJavaScripts = (Trie<uint64_t>&&)(_Other.OldLastWriteJavaScripts);
	OldLastWriteJsons = (Trie<uint64_t>&&)(_Other.OldLastWriteJsons);
	OldLastWriteScriptLibs = (Trie<uint64_t>&&)(_Other.OldLastWriteScriptLibs);

	CachedResourceRawFileNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceRawFileNames);
	CachedResourceBitMapNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceBitMapNames);
	CachedResourceHdrNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceHdrNames);
	CachedResourceWaveNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceWaveNames);
	CachedResourceWaveFrontObjNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceWaveFrontObjNames);
	CachedResourceMaterialLibNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceMaterialLibNames);
	CachedResourceGLSLNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceGLSLNames);
	CachedResourceXMLNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceXMLNames);
	CachedResourceCSSNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceCSSNames);
	CachedResourceJavaScriptNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceJavaScriptNames);
	CachedResourceJsonNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceJsonNames);
	CachedResourceScriptLibNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceScriptLibNames);

	CachedResourceRawFiles = (Trie<WeakPointer<FileContent>>&&)(_Other.CachedResourceRawFiles);
	CachedResourceBitMaps = (Trie<WeakPointer<BitMap>>&&)(_Other.CachedResourceBitMaps);
	CachedResourceHdrs = (Trie<WeakPointer<Hdr>>&&)(_Other.CachedResourceHdrs);
	CachedResourceWaves = (Trie<WeakPointer<Wave>>&&)(_Other.CachedResourceWaves);
	CachedResourceWaveFrontObjs = (Trie<WeakPointer<WaveFrontObj>>&&)(_Other.CachedResourceWaveFrontObjs);
	CachedResourceMaterialLibs = (Trie<WeakPointer<MaterialLib>>&&)(_Other.CachedResourceMaterialLibs);
	CachedResourceGLSLs = (Trie<WeakPointer<FileContent>>&&)(_Other.CachedResourceGLSLs);
	CachedResourceXMLs = (Trie<WeakPointer<XML>>&&)(_Other.CachedResourceXMLs);
	CachedResourceCSSs = (Trie<WeakPointer<FileContent>>&&)(_Other.CachedResourceCSSs);
	CachedResourceJavaScripts = (Trie<WeakPointer<FileContent>>&&)(_Other.CachedResourceJavaScripts);
	CachedResourceJsons = (Trie<WeakPointer<Json>>&&)(_Other.CachedResourceJsons);
	CachedResourceScriptLibs = (Trie<WeakPointer<ScriptLib>>&&)(_Other.CachedResourceScriptLibs);

	return *this;
}

#endif

#if defined BFW_LINUX_PLATFORM || defined BFW_ESP32_PLATFORM

BFW::Assets::Manager& BFW::Assets::Manager::operator= (Manager&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	QueuedRawFiles = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedRawFiles);
	QueuedBitMaps = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedBitMaps);
	QueuedHdrs = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedHdrs);
	QueuedWaves = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedWaves);
	QueuedWaveFrontObjs = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedWaveFrontObjs);
	QueuedMaterialLibs = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedMaterialLibs);
	QueuedGLSLs = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedGLSLs);
	QueuedXMLs = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedXMLs);
	QueuedCSSs = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedCSSs);
	QueuedJavaScripts = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedJavaScripts);
	QueuedJsons = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedJsons);
	QueuedScriptLibs = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedScriptLibs);

	LoadedRawFiles = (Trie<SharedPointer<FileContent>>&&)(_Other.LoadedRawFiles);
	LoadedBitMaps = (Trie<SharedPointer<BitMap>>&&)(_Other.LoadedBitMaps);
	LoadedHdrs = (Trie<SharedPointer<Hdr>>&&)(_Other.LoadedHdrs);
	LoadedWaves = (Trie<SharedPointer<Wave>>&&)(_Other.LoadedWaves);
	LoadedWaveFrontObjs = (Trie<SharedPointer<WaveFrontObj>>&&)(_Other.LoadedWaveFrontObjs);
	LoadedMaterialLibs = (Trie<SharedPointer<MaterialLib>>&&)(_Other.LoadedMaterialLibs);
	LoadedGLSLs = (Trie<SharedPointer<FileContent>>&&)(_Other.LoadedGLSLs);
	LoadedXMLs = (Trie<SharedPointer<XML>>&&)(_Other.LoadedXMLs);
	LoadedCSSs = (Trie<SharedPointer<FileContent>>&&)(_Other.LoadedCSSs);
	LoadedJavaScripts = (Trie<SharedPointer<FileContent>>&&)(_Other.LoadedJavaScripts);
	LoadedJsons = (Trie<SharedPointer<Json>>&&)(_Other.LoadedJsons);
	LoadedScriptLibs = (Trie<SharedPointer<ScriptLib>>&&)(_Other.LoadedScriptLibs);

	CachedRawFileNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedRawFileNames);
	CachedBitMapNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedBitMapNames);
	CachedHdrNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedHdrNames);
	CachedWaveNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedWaveNames);
	CachedWaveFrontObjNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedWaveFrontObjNames);
	CachedMaterialLibNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedMaterialLibNames);
	CachedGLSLNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedGLSLNames);
	CachedXMLNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedXMLNames);
	CachedCSSNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedCSSNames);
	CachedJavaScriptNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedJavaScriptNames);
	CachedJsonNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedJsonNames);
	CachedScriptLibNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedScriptLibNames);

	CachedRawFiles = (Trie<WeakPointer<FileContent>>&&)(_Other.CachedRawFiles);
	CachedBitMaps = (Trie<WeakPointer<BitMap>>&&)(_Other.CachedBitMaps);
	CachedHdrs = (Trie<WeakPointer<Hdr>>&&)(_Other.CachedHdrs);
	CachedWaves = (Trie<WeakPointer<Wave>>&&)(_Other.CachedWaves);
	CachedWaveFrontObjs = (Trie<WeakPointer<WaveFrontObj>>&&)(_Other.CachedWaveFrontObjs);
	CachedMaterialLibs = (Trie<WeakPointer<MaterialLib>>&&)(_Other.CachedMaterialLibs);
	CachedGLSLs = (Trie<WeakPointer<FileContent>>&&)(_Other.CachedGLSLs);
	CachedXMLs = (Trie<WeakPointer<XML>>&&)(_Other.CachedXMLs);
	CachedCSSs = (Trie<WeakPointer<FileContent>>&&)(_Other.CachedCSSs);
	CachedJavaScripts = (Trie<WeakPointer<FileContent>>&&)(_Other.CachedJavaScripts);
	CachedJsons = (Trie<WeakPointer<Json>>&&)(_Other.CachedJsons);
	CachedScriptLibs = (Trie<WeakPointer<ScriptLib>>&&)(_Other.CachedScriptLibs);

	LastWriteRawFiles = (Trie<uint64_t>&&)(_Other.LastWriteRawFiles);
	LastWriteBitMaps = (Trie<uint64_t>&&)(_Other.LastWriteBitMaps);
	LastWriteHdrs = (Trie<uint64_t>&&)(_Other.LastWriteHdrs);
	LastWriteWaves = (Trie<uint64_t>&&)(_Other.LastWriteWaves);
	LastWriteWaveFrontObjs = (Trie<uint64_t>&&)(_Other.LastWriteWaveFrontObjs);
	LastWriteMaterialLibs = (Trie<uint64_t>&&)(_Other.LastWriteMaterialLibs);
	LastWriteGLSLs = (Trie<uint64_t>&&)(_Other.LastWriteGLSLs);
	LastWriteXMLs = (Trie<uint64_t>&&)(_Other.LastWriteXMLs);
	LastWriteCSSs = (Trie<uint64_t>&&)(_Other.LastWriteCSSs);
	LastWriteJavaScripts = (Trie<uint64_t>&&)(_Other.LastWriteJavaScripts);
	LastWriteJsons = (Trie<uint64_t>&&)(_Other.LastWriteJsons);
	LastWriteScriptLibs = (Trie<uint64_t>&&)(_Other.LastWriteScriptLibs);

	OldLastWriteRawFiles = (Trie<uint64_t>&&)(_Other.OldLastWriteRawFiles);
	OldLastWriteBitMaps = (Trie<uint64_t>&&)(_Other.OldLastWriteBitMaps);
	OldLastWriteHdrs = (Trie<uint64_t>&&)(_Other.OldLastWriteHdrs);
	OldLastWriteWaves = (Trie<uint64_t>&&)(_Other.OldLastWriteWaves);
	OldLastWriteWaveFrontObjs = (Trie<uint64_t>&&)(_Other.OldLastWriteWaveFrontObjs);
	OldLastWriteMaterialLibs = (Trie<uint64_t>&&)(_Other.OldLastWriteMaterialLibs);
	OldLastWriteGLSLs = (Trie<uint64_t>&&)(_Other.OldLastWriteGLSLs);
	OldLastWriteXMLs = (Trie<uint64_t>&&)(_Other.OldLastWriteXMLs);
	OldLastWriteCSSs = (Trie<uint64_t>&&)(_Other.OldLastWriteCSSs);
	OldLastWriteJavaScripts = (Trie<uint64_t>&&)(_Other.OldLastWriteJavaScripts);
	OldLastWriteJsons = (Trie<uint64_t>&&)(_Other.OldLastWriteJsons);
	OldLastWriteScriptLibs = (Trie<uint64_t>&&)(_Other.OldLastWriteScriptLibs);

	return *this;
}

#endif

void BFW::Assets::Manager::RefreshCache()
{
	ManagerRefreshCache<FileContent>(CachedRawFiles, LastWriteRawFiles, CachedRawFileNames);
	ManagerRefreshCache<BitMap>(CachedBitMaps, LastWriteBitMaps, CachedBitMapNames);
	ManagerRefreshCache<Hdr>(CachedHdrs, LastWriteHdrs, CachedHdrNames);
	ManagerRefreshCache<Wave>(CachedWaves, LastWriteWaves, CachedWaveNames);
	ManagerRefreshCache<WaveFrontObj>(CachedWaveFrontObjs, LastWriteWaveFrontObjs, CachedWaveFrontObjNames);
	ManagerRefreshCache<MaterialLib>(CachedMaterialLibs, LastWriteMaterialLibs, CachedMaterialLibNames);
	ManagerRefreshCache<FileContent>(CachedGLSLs, LastWriteGLSLs, CachedGLSLNames);
	ManagerRefreshCache<XML>(CachedXMLs, LastWriteXMLs, CachedXMLNames);
	ManagerRefreshCache<FileContent>(CachedCSSs, LastWriteCSSs, CachedCSSNames);
	ManagerRefreshCache<FileContent>(CachedJavaScripts, LastWriteJavaScripts, CachedJavaScriptNames);
	ManagerRefreshCache<Json>(CachedJsons, LastWriteJsons, CachedJsonNames);
	ManagerRefreshCache<ScriptLib>(CachedScriptLibs, LastWriteScriptLibs, CachedScriptLibNames);

#ifdef BFW_WINDOWS_PLATFORM

	ManagerRefreshResourceCache<FileContent>(CachedResourceRawFiles, CachedResourceRawFileNames);
	ManagerRefreshResourceCache<BitMap>(CachedResourceBitMaps, CachedResourceBitMapNames);
	ManagerRefreshResourceCache<Hdr>(CachedResourceHdrs, CachedResourceHdrNames);
	ManagerRefreshResourceCache<Wave>(CachedResourceWaves, CachedResourceWaveNames);
	ManagerRefreshResourceCache<WaveFrontObj>(CachedResourceWaveFrontObjs, CachedResourceWaveFrontObjNames);
	ManagerRefreshResourceCache<MaterialLib>(CachedResourceMaterialLibs, CachedResourceMaterialLibNames);
	ManagerRefreshResourceCache<FileContent>(CachedResourceGLSLs, CachedResourceGLSLNames);
	ManagerRefreshResourceCache<XML>(CachedResourceXMLs, CachedResourceXMLNames);
	ManagerRefreshResourceCache<FileContent>(CachedResourceCSSs, CachedResourceCSSNames);
	ManagerRefreshResourceCache<FileContent>(CachedResourceJavaScripts, CachedResourceJavaScriptNames);
	ManagerRefreshResourceCache<Json>(CachedResourceJsons, CachedResourceJsonNames);
	ManagerRefreshResourceCache<ScriptLib>(CachedResourceScriptLibs, CachedResourceScriptLibNames);

#endif
}
