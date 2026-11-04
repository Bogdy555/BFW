#include "../Headers/BFW.hpp"



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

	_File.seekg(0, std::ios::end);

	size_t _Length = (size_t)(_File.tellg()) + 1;

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

	_File.seekg(0, std::ios::end);

	size_t _Length = (size_t)(_File.tellg()) + 1;

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

	const uint8_t* _ResourceMemory = (const uint8_t*)(LoadResource(_InstanceHandle, _ResourceHandle));

	if (!_ResourceMemory)
	{
		return false;
	}

	uint8_t* _Data = new uint8_t[_Length];

	if (!_Data)
	{
		FreeResource((HGLOBAL)(_ResourceMemory));
		return false;
	}

	for (size_t _Index = 0; _Index < _Length - 1; _Index++)
	{
		_Data[_Index] = _ResourceMemory[_Index];
	}

	_Data[_Length - 1] = '\0';

	Data = _Data;
	Length = _Length;

	FreeResource((HGLOBAL)(_ResourceMemory));

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
	if (!Data || Length <= 1 || !_File.is_open())
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

BFW::Assets::Manager::Manager() : QueuedBitMaps(), QueuedHdrs(), QueuedWaves(), QueuedWaveFrontObjs(), QueuedGLSLs(), QueuedJsons(), QueuedResourceBitMaps(), QueuedResourceHdrs(), QueuedResourceWaves(), QueuedResourceWaveFrontObjs(), QueuedResourceGLSLs(), QueuedResourceJsons(), LoadedBitMaps(), LoadedHdrs(), LoadedWaves(), LoadedWaveFrontObjs(), LoadedGLSLs(), LoadedJsons(), LoadedResourceBitMaps(), LoadedResourceHdrs(), LoadedResourceWaves(), LoadedResourceWaveFrontObjs(), LoadedResourceGLSLs(), LoadedResourceJsons(), CachedBitMapNames(), CachedHdrNames(), CachedWaveNames(), CachedWaveFrontObjNames(), CachedGLSLNames(), CachedJsonNames(), CachedBitMaps(), CachedHdrs(), CachedWaves(), CachedWaveFrontObjs(), CachedGLSLs(), CachedJsons(), LastWriteBitMaps(), LastWriteHdrs(), LastWriteWaves(), LastWriteWaveFrontObjs(), LastWriteGLSLs(), LastWriteJsons(), CachedResourceBitMapNames(), CachedResourceHdrNames(), CachedResourceWaveNames(), CachedResourceWaveFrontObjNames(), CachedResourceGLSLNames(), CachedResourceJsonNames(), CachedResourceBitMaps(), CachedResourceHdrs(), CachedResourceWaves(), CachedResourceWaveFrontObjs(), CachedResourceGLSLs(), CachedResourceJsons()
{

}

BFW::Assets::Manager::Manager(Manager&& _Other) noexcept : QueuedBitMaps((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedBitMaps)), QueuedHdrs((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedHdrs)), QueuedWaves((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedWaves)), QueuedWaveFrontObjs((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedWaveFrontObjs)), QueuedGLSLs((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedGLSLs)), QueuedJsons((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedJsons)), QueuedResourceBitMaps((Vector<size_t>&&)(_Other.QueuedResourceBitMaps)), QueuedResourceHdrs((Vector<size_t>&&)(_Other.QueuedResourceHdrs)), QueuedResourceWaves((Vector<size_t>&&)(_Other.QueuedResourceWaves)), QueuedResourceWaveFrontObjs((Vector<size_t>&&)(_Other.QueuedResourceWaveFrontObjs)), QueuedResourceGLSLs((Vector<size_t>&&)(_Other.QueuedResourceGLSLs)), QueuedResourceJsons((Vector<size_t>&&)(_Other.QueuedResourceJsons)), LoadedBitMaps((Trie<SharedPointer<BitMap>>&&)(_Other.LoadedBitMaps)), LoadedHdrs((Trie<SharedPointer<Hdr>>&&)(_Other.LoadedHdrs)), LoadedWaves((Trie<SharedPointer<Wave>>&&)(_Other.LoadedWaves)), LoadedWaveFrontObjs((Trie<SharedPointer<WaveFrontObj>>&&)(_Other.LoadedWaveFrontObjs)), LoadedGLSLs((Trie<SharedPointer<FileContent>>&&)(_Other.LoadedGLSLs)), LoadedJsons((Trie<SharedPointer<Json>>&&)(_Other.LoadedJsons)), LoadedResourceBitMaps((Trie<SharedPointer<BitMap>>&&)(_Other.LoadedResourceBitMaps)), LoadedResourceHdrs((Trie<SharedPointer<Hdr>>&&)(_Other.LoadedResourceHdrs)), LoadedResourceWaves((Trie<SharedPointer<Wave>>&&)(_Other.LoadedResourceWaves)), LoadedResourceWaveFrontObjs((Trie<SharedPointer<WaveFrontObj>>&&)(_Other.LoadedResourceWaveFrontObjs)), LoadedResourceGLSLs((Trie<SharedPointer<FileContent>>&&)(_Other.LoadedResourceGLSLs)), LoadedResourceJsons((Trie<SharedPointer<Json>>&&)(_Other.LoadedResourceJsons)), CachedBitMapNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedBitMapNames)), CachedHdrNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedHdrNames)), CachedWaveNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedWaveNames)), CachedWaveFrontObjNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedWaveFrontObjNames)), CachedGLSLNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedGLSLNames)), CachedJsonNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedJsonNames)), CachedBitMaps((Trie<WeakPointer<BitMap>>&&)(_Other.CachedBitMaps)), CachedHdrs((Trie<WeakPointer<Hdr>>&&)(_Other.CachedHdrs)), CachedWaves((Trie<WeakPointer<Wave>>&&)(_Other.CachedWaves)), CachedWaveFrontObjs((Trie<WeakPointer<WaveFrontObj>>&&)(_Other.CachedWaveFrontObjs)), CachedGLSLs((Trie<WeakPointer<FileContent>>&&)(_Other.CachedGLSLs)), CachedJsons((Trie<WeakPointer<Json>>&&)(_Other.CachedJsons)), LastWriteBitMaps((Trie<uint64_t>&&)(_Other.LastWriteBitMaps)), LastWriteHdrs((Trie<uint64_t>&&)(_Other.LastWriteHdrs)), LastWriteWaves((Trie<uint64_t>&&)(_Other.LastWriteWaves)), LastWriteWaveFrontObjs((Trie<uint64_t>&&)(_Other.LastWriteWaveFrontObjs)), LastWriteGLSLs((Trie<uint64_t>&&)(_Other.LastWriteGLSLs)), LastWriteJsons((Trie<uint64_t>&&)(_Other.LastWriteJsons)), CachedResourceBitMapNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceBitMapNames)), CachedResourceHdrNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceHdrNames)), CachedResourceWaveNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceWaveNames)), CachedResourceWaveFrontObjNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceWaveFrontObjNames)), CachedResourceGLSLNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceGLSLNames)), CachedResourceJsonNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceJsonNames)), CachedResourceBitMaps((Trie<WeakPointer<BitMap>>&&)(_Other.CachedResourceBitMaps)), CachedResourceHdrs((Trie<WeakPointer<Hdr>>&&)(_Other.CachedResourceHdrs)), CachedResourceWaves((Trie<WeakPointer<Wave>>&&)(_Other.CachedResourceWaves)), CachedResourceWaveFrontObjs((Trie<WeakPointer<WaveFrontObj>>&&)(_Other.CachedResourceWaveFrontObjs)), CachedResourceGLSLs((Trie<WeakPointer<FileContent>>&&)(_Other.CachedResourceGLSLs)), CachedResourceJsons((Trie<WeakPointer<Json>>&&)(_Other.CachedResourceJsons))
{

}

#endif

#if defined BFW_LINUX_PLATFORM || defined BFW_ESP32_PLATFORM

BFW::Assets::Manager::Manager() : QueuedBitMaps(), QueuedHdrs(), QueuedWaves(), QueuedWaveFrontObjs(), QueuedGLSLs(), QueuedJsons(), LoadedBitMaps(), LoadedHdrs(), LoadedWaves(), LoadedWaveFrontObjs(), LoadedGLSLs(), LoadedJsons(), CachedBitMapNames(), CachedHdrNames(), CachedWaveNames(), CachedWaveFrontObjNames(), CachedGLSLNames(), CachedJsonNames(), CachedBitMaps(), CachedHdrs(), CachedWaves(), CachedWaveFrontObjs(), CachedGLSLs(), CachedJsons(), LastWriteBitMaps(), LastWriteHdrs(), LastWriteWaves(), LastWriteWaveFrontObjs(), LastWriteGLSLs(), LastWriteJsons()
{

}

BFW::Assets::Manager::Manager(Manager&& _Other) noexcept : QueuedBitMaps((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedBitMaps)), QueuedHdrs((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedHdrs)), QueuedWaves((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedWaves)), QueuedWaveFrontObjs((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedWaveFrontObjs)), QueuedGLSLs((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedGLSLs)), QueuedJsons((Vector<BFW_STRING_TYPE>&&)(_Other.QueuedJsons)), LoadedBitMaps((Trie<SharedPointer<BitMap>>&&)(_Other.LoadedBitMaps)), LoadedHdrs((Trie<SharedPointer<Hdr>>&&)(_Other.LoadedHdrs)), LoadedWaves((Trie<SharedPointer<Wave>>&&)(_Other.LoadedWaves)), LoadedWaveFrontObjs((Trie<SharedPointer<WaveFrontObj>>&&)(_Other.LoadedWaveFrontObjs)), LoadedGLSLs((Trie<SharedPointer<FileContent>>&&)(_Other.LoadedGLSLs)), LoadedJsons((Trie<SharedPointer<Json>>&&)(_Other.LoadedJsons)), CachedBitMapNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedBitMapNames)), CachedHdrNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedHdrNames)), CachedWaveNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedWaveNames)), CachedWaveFrontObjNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedWaveFrontObjNames)), CachedGLSLNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedGLSLNames)), CachedJsonNames((Vector<BFW_STRING_TYPE>&&)(_Other.CachedJsonNames)), CachedBitMaps((Trie<WeakPointer<BitMap>>&&)(_Other.CachedBitMaps)), CachedHdrs((Trie<WeakPointer<Hdr>>&&)(_Other.CachedHdrs)), CachedWaves((Trie<WeakPointer<Wave>>&&)(_Other.CachedWaves)), CachedWaveFrontObjs((Trie<WeakPointer<WaveFrontObj>>&&)(_Other.CachedWaveFrontObjs)), CachedGLSLs((Trie<WeakPointer<FileContent>>&&)(_Other.CachedGLSLs)), CachedJsons((Trie<WeakPointer<Json>>&&)(_Other.CachedJsons)), LastWriteBitMaps((Trie<uint64_t>&&)(_Other.LastWriteBitMaps)), LastWriteHdrs((Trie<uint64_t>&&)(_Other.LastWriteHdrs)), LastWriteWaves((Trie<uint64_t>&&)(_Other.LastWriteWaves)), LastWriteWaveFrontObjs((Trie<uint64_t>&&)(_Other.LastWriteWaveFrontObjs)), LastWriteGLSLs((Trie<uint64_t>&&)(_Other.LastWriteGLSLs)), LastWriteJsons((Trie<uint64_t>&&)(_Other.LastWriteJsons))
{

}

#endif

BFW::Assets::Manager::~Manager()
{

}

void BFW::Assets::Manager::QueueBitMap(const BFW_CHAR_TYPE* _Name)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) == BFW_STRING_PREFIX("Dynamic/"))
	{
		throw nullptr;
	}

	bool _Found = false;

	for (size_t _Index = 0; _Index < QueuedBitMaps.GetSize(); _Index++)
	{
		if (QueuedBitMaps[_Index] == _Name)
		{
			_Found = true;
		}
	}

	if (_Found)
	{
		return;
	}

	QueuedBitMaps.EmplaceBack(_Name);
}

void BFW::Assets::Manager::QueueHdr(const BFW_CHAR_TYPE* _Name)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) == BFW_STRING_PREFIX("Dynamic/"))
	{
		throw nullptr;
	}

	bool _Found = false;

	for (size_t _Index = 0; _Index < QueuedHdrs.GetSize(); _Index++)
	{
		if (QueuedHdrs[_Index] == _Name)
		{
			_Found = true;
		}
	}

	if (_Found)
	{
		return;
	}

	QueuedHdrs.EmplaceBack(_Name);
}

void BFW::Assets::Manager::QueueWave(const BFW_CHAR_TYPE* _Name)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) == BFW_STRING_PREFIX("Dynamic/"))
	{
		throw nullptr;
	}

	bool _Found = false;

	for (size_t _Index = 0; _Index < QueuedWaves.GetSize(); _Index++)
	{
		if (QueuedWaves[_Index] == _Name)
		{
			_Found = true;
		}
	}

	if (_Found)
	{
		return;
	}

	QueuedWaves.EmplaceBack(_Name);
}

void BFW::Assets::Manager::QueueWaveFrontObj(const BFW_CHAR_TYPE* _Name)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) == BFW_STRING_PREFIX("Dynamic/"))
	{
		throw nullptr;
	}

	bool _Found = false;

	for (size_t _Index = 0; _Index < QueuedWaveFrontObjs.GetSize(); _Index++)
	{
		if (QueuedWaveFrontObjs[_Index] == _Name)
		{
			_Found = true;
		}
	}

	if (_Found)
	{
		return;
	}

	QueuedWaveFrontObjs.EmplaceBack(_Name);
}

void BFW::Assets::Manager::QueueGLSL(const BFW_CHAR_TYPE* _Name)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) == BFW_STRING_PREFIX("Dynamic/"))
	{
		throw nullptr;
	}

	bool _Found = false;

	for (size_t _Index = 0; _Index < QueuedGLSLs.GetSize(); _Index++)
	{
		if (QueuedGLSLs[_Index] == _Name)
		{
			_Found = true;
		}
	}

	if (_Found)
	{
		return;
	}

	QueuedGLSLs.EmplaceBack(_Name);
}

void BFW::Assets::Manager::QueueJson(const BFW_CHAR_TYPE* _Name)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) == BFW_STRING_PREFIX("Dynamic/"))
	{
		throw nullptr;
	}

	bool _Found = false;

	for (size_t _Index = 0; _Index < QueuedJsons.GetSize(); _Index++)
	{
		if (QueuedJsons[_Index] == _Name)
		{
			_Found = true;
		}
	}

	if (_Found)
	{
		return;
	}

	QueuedJsons.EmplaceBack(_Name);
}

#ifdef BFW_WINDOWS_PLATFORM

void BFW::Assets::Manager::QueueResourceBitMap(const size_t _Id)
{
	bool _Found = false;

	for (size_t _Index = 0; _Index < QueuedResourceBitMaps.GetSize(); _Index++)
	{
		if (QueuedResourceBitMaps[_Index] == _Id)
		{
			_Found = true;
		}
	}

	if (_Found)
	{
		return;
	}

	QueuedResourceBitMaps.PushBack(_Id);
}

void BFW::Assets::Manager::QueueResourceHdr(const size_t _Id)
{
	bool _Found = false;

	for (size_t _Index = 0; _Index < QueuedResourceHdrs.GetSize(); _Index++)
	{
		if (QueuedResourceHdrs[_Index] == _Id)
		{
			_Found = true;
		}
	}

	if (_Found)
	{
		return;
	}

	QueuedResourceHdrs.PushBack(_Id);
}

void BFW::Assets::Manager::QueueResourceWave(const size_t _Id)
{
	bool _Found = false;

	for (size_t _Index = 0; _Index < QueuedResourceWaves.GetSize(); _Index++)
	{
		if (QueuedResourceWaves[_Index] == _Id)
		{
			_Found = true;
		}
	}

	if (_Found)
	{
		return;
	}

	QueuedResourceWaves.PushBack(_Id);
}

void BFW::Assets::Manager::QueueResourceWaveFrontObj(const size_t _Id)
{
	bool _Found = false;

	for (size_t _Index = 0; _Index < QueuedResourceWaveFrontObjs.GetSize(); _Index++)
	{
		if (QueuedResourceWaveFrontObjs[_Index] == _Id)
		{
			_Found = true;
		}
	}

	if (_Found)
	{
		return;
	}

	QueuedResourceWaveFrontObjs.PushBack(_Id);
}

void BFW::Assets::Manager::QueueResourceGLSL(const size_t _Id)
{
	bool _Found = false;

	for (size_t _Index = 0; _Index < QueuedResourceGLSLs.GetSize(); _Index++)
	{
		if (QueuedResourceGLSLs[_Index] == _Id)
		{
			_Found = true;
		}
	}

	if (_Found)
	{
		return;
	}

	QueuedResourceGLSLs.PushBack(_Id);
}

void BFW::Assets::Manager::QueueResourceJson(const size_t _Id)
{
	bool _Found = false;

	for (size_t _Index = 0; _Index < QueuedResourceJsons.GetSize(); _Index++)
	{
		if (QueuedResourceJsons[_Index] == _Id)
		{
			_Found = true;
		}
	}

	if (_Found)
	{
		return;
	}

	QueuedResourceJsons.PushBack(_Id);
}

#endif

void BFW::Assets::Manager::Flush()
{
	RefreshCache();

	bool _Fail = false;
	Vector<std::thread> _Threads;

	for (size_t _Index = 0; _Index < QueuedBitMaps.GetSize(); _Index++)
	{
		if (LoadedBitMaps.GetData(QueuedBitMaps[_Index].c_str()))
		{
			QueuedBitMaps.Erase(_Index);
			_Index--;
			continue;
		}

		{
			WeakPointer<BitMap>* _CachedWeak = CachedBitMaps.GetData(QueuedBitMaps[_Index].c_str());

			if (_CachedWeak)
			{
				SharedPointer<BitMap> _CachedShared = _CachedWeak->Lock();

				if ((BitMap*)(_CachedShared))
				{
					LoadedBitMaps.Emplace(QueuedBitMaps[_Index].c_str(), (SharedPointer<BitMap>&&)(_CachedShared));
					QueuedBitMaps.Erase(_Index);
					_Index--;
					continue;
				}
			}
		}

		SharedPointer<BitMap> _Asset = SharedPointer<BitMap>::MakeShared(BitMap());

		CachedBitMaps.Emplace(QueuedBitMaps[_Index].c_str(), _Asset);
		LastWriteBitMaps.Push(QueuedBitMaps[_Index].c_str(), 0);
		LoadedBitMaps.Emplace(QueuedBitMaps[_Index].c_str(), (SharedPointer<BitMap>&&)(_Asset));

		bool _Found = false;

		for (size_t _NameIndex = 0; _NameIndex < CachedBitMapNames.GetSize(); _NameIndex++)
		{
			if (CachedBitMapNames[_NameIndex] == QueuedBitMaps[_Index])
			{
				_Found = true;
				break;
			}
		}

		if (!_Found)
		{
			CachedBitMapNames.PushBack(QueuedBitMaps[_Index]);
		}
	}

	for (size_t _Index = 0; _Index < QueuedBitMaps.GetSize(); _Index++)
	{
		_Threads.EmplaceBack
		(
			std::thread
			(
				[](bool& _Fail, const BFW_CHAR_TYPE* _Name, SharedPointer<BitMap> _Asset, uint64_t& _LastWrite)
				{
					std::ifstream _InStream;

					_InStream.open(_Name, std::ios::binary);

					if (!_InStream.is_open())
					{
						_Fail = true;
						return;
					}

					try
					{
						_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
					}
					catch (...)
					{
						_Fail = true;
						return;
					}

					FileContent _FileContent;

					if (!_FileContent.Load(_InStream))
					{
						_Fail = true;
						return;
					}

					if (!_Asset->Load(_FileContent))
					{
						_Fail = true;
						return;
					}
				},
				std::ref(_Fail),
				QueuedBitMaps[_Index].c_str(),
				*LoadedBitMaps.GetData(QueuedBitMaps[_Index].c_str()),
				std::ref(*LastWriteBitMaps.GetData(QueuedBitMaps[_Index].c_str()))
			)
		);
	}

	for (size_t _Index = 0; _Index < QueuedHdrs.GetSize(); _Index++)
	{
		if (LoadedHdrs.GetData(QueuedHdrs[_Index].c_str()))
		{
			QueuedHdrs.Erase(_Index);
			_Index--;
			continue;
		}

		{
			WeakPointer<Hdr>* _CachedWeak = CachedHdrs.GetData(QueuedHdrs[_Index].c_str());

			if (_CachedWeak)
			{
				SharedPointer<Hdr> _CachedShared = _CachedWeak->Lock();

				if ((Hdr*)(_CachedShared))
				{
					LoadedHdrs.Emplace(QueuedHdrs[_Index].c_str(), (SharedPointer<Hdr>&&)(_CachedShared));
					QueuedHdrs.Erase(_Index);
					_Index--;
					continue;
				}
			}
		}

		SharedPointer<Hdr> _Asset = SharedPointer<Hdr>::MakeShared(Hdr());

		CachedHdrs.Emplace(QueuedHdrs[_Index].c_str(), _Asset);
		LastWriteHdrs.Push(QueuedHdrs[_Index].c_str(), 0);
		LoadedHdrs.Emplace(QueuedHdrs[_Index].c_str(), (SharedPointer<Hdr>&&)(_Asset));

		bool _Found = false;

		for (size_t _NameIndex = 0; _NameIndex < CachedHdrNames.GetSize(); _NameIndex++)
		{
			if (CachedHdrNames[_NameIndex] == QueuedHdrs[_Index])
			{
				_Found = true;
				break;
			}
		}

		if (!_Found)
		{
			CachedHdrNames.PushBack(QueuedHdrs[_Index]);
		}
	}

	for (size_t _Index = 0; _Index < QueuedHdrs.GetSize(); _Index++)
	{
		_Threads.EmplaceBack
		(
			std::thread
			(
				[](bool& _Fail, const BFW_CHAR_TYPE* _Name, SharedPointer<Hdr> _Asset, uint64_t& _LastWrite)
				{
					std::ifstream _InStream;

					_InStream.open(_Name, std::ios::binary);

					if (!_InStream.is_open())
					{
						_Fail = true;
						return;
					}

					try
					{
						_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
					}
					catch (...)
					{
						_Fail = true;
						return;
					}

					FileContent _FileContent;

					if (!_FileContent.Load(_InStream))
					{
						_Fail = true;
						return;
					}

					if (!_Asset->Load(_FileContent))
					{
						_Fail = true;
						return;
					}
				},
				std::ref(_Fail),
				QueuedHdrs[_Index].c_str(),
				*LoadedHdrs.GetData(QueuedHdrs[_Index].c_str()),
				std::ref(*LastWriteHdrs.GetData(QueuedHdrs[_Index].c_str()))
			)
		);
	}

	for (size_t _Index = 0; _Index < QueuedWaves.GetSize(); _Index++)
	{
		if (LoadedWaves.GetData(QueuedWaves[_Index].c_str()))
		{
			QueuedWaves.Erase(_Index);
			_Index--;
			continue;
		}

		{
			WeakPointer<Wave>* _CachedWeak = CachedWaves.GetData(QueuedWaves[_Index].c_str());

			if (_CachedWeak)
			{
				SharedPointer<Wave> _CachedShared = _CachedWeak->Lock();

				if ((Wave*)(_CachedShared))
				{
					LoadedWaves.Emplace(QueuedWaves[_Index].c_str(), (SharedPointer<Wave>&&)(_CachedShared));
					QueuedWaves.Erase(_Index);
					_Index--;
					continue;
				}
			}
		}

		SharedPointer<Wave> _Asset = SharedPointer<Wave>::MakeShared(Wave());

		CachedWaves.Emplace(QueuedWaves[_Index].c_str(), _Asset);
		LastWriteWaves.Push(QueuedWaves[_Index].c_str(), 0);
		LoadedWaves.Emplace(QueuedWaves[_Index].c_str(), (SharedPointer<Wave>&&)(_Asset));

		bool _Found = false;

		for (size_t _NameIndex = 0; _NameIndex < CachedWaveNames.GetSize(); _NameIndex++)
		{
			if (CachedWaveNames[_NameIndex] == QueuedWaves[_Index])
			{
				_Found = true;
				break;
			}
		}

		if (!_Found)
		{
			CachedWaveNames.PushBack(QueuedWaves[_Index]);
		}
	}

	for (size_t _Index = 0; _Index < QueuedWaves.GetSize(); _Index++)
	{
		_Threads.EmplaceBack
		(
			std::thread
			(
				[](bool& _Fail, const BFW_CHAR_TYPE* _Name, SharedPointer<Wave> _Asset, uint64_t& _LastWrite)
				{
					std::ifstream _InStream;

					_InStream.open(_Name, std::ios::binary);

					if (!_InStream.is_open())
					{
						_Fail = true;
						return;
					}

					try
					{
						_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
					}
					catch (...)
					{
						_Fail = true;
						return;
					}

					FileContent _FileContent;

					if (!_FileContent.Load(_InStream))
					{
						_Fail = true;
						return;
					}

					if (!_Asset->Load(_FileContent))
					{
						_Fail = true;
						return;
					}
				},
				std::ref(_Fail),
				QueuedWaves[_Index].c_str(),
				*LoadedWaves.GetData(QueuedWaves[_Index].c_str()),
				std::ref(*LastWriteWaves.GetData(QueuedWaves[_Index].c_str()))
			)
		);
	}

	for (size_t _Index = 0; _Index < QueuedWaveFrontObjs.GetSize(); _Index++)
	{
		if (LoadedWaveFrontObjs.GetData(QueuedWaveFrontObjs[_Index].c_str()))
		{
			QueuedWaveFrontObjs.Erase(_Index);
			_Index--;
			continue;
		}

		{
			WeakPointer<WaveFrontObj>* _CachedWeak = CachedWaveFrontObjs.GetData(QueuedWaveFrontObjs[_Index].c_str());

			if (_CachedWeak)
			{
				SharedPointer<WaveFrontObj> _CachedShared = _CachedWeak->Lock();

				if ((WaveFrontObj*)(_CachedShared))
				{
					LoadedWaveFrontObjs.Emplace(QueuedWaveFrontObjs[_Index].c_str(), (SharedPointer<WaveFrontObj>&&)(_CachedShared));
					QueuedWaveFrontObjs.Erase(_Index);
					_Index--;
					continue;
				}
			}
		}

		SharedPointer<WaveFrontObj> _Asset = SharedPointer<WaveFrontObj>::MakeShared(WaveFrontObj());

		CachedWaveFrontObjs.Emplace(QueuedWaveFrontObjs[_Index].c_str(), _Asset);
		LastWriteWaveFrontObjs.Push(QueuedWaveFrontObjs[_Index].c_str(), 0);
		LoadedWaveFrontObjs.Emplace(QueuedWaveFrontObjs[_Index].c_str(), (SharedPointer<WaveFrontObj>&&)(_Asset));

		bool _Found = false;

		for (size_t _NameIndex = 0; _NameIndex < CachedWaveFrontObjNames.GetSize(); _NameIndex++)
		{
			if (CachedWaveFrontObjNames[_NameIndex] == QueuedWaveFrontObjs[_Index])
			{
				_Found = true;
				break;
			}
		}

		if (!_Found)
		{
			CachedWaveFrontObjNames.PushBack(QueuedWaveFrontObjs[_Index]);
		}
	}

	for (size_t _Index = 0; _Index < QueuedWaveFrontObjs.GetSize(); _Index++)
	{
		_Threads.EmplaceBack
		(
			std::thread
			(
				[](bool& _Fail, const BFW_CHAR_TYPE* _Name, SharedPointer<WaveFrontObj> _Asset, uint64_t& _LastWrite)
				{
					std::ifstream _InStream;

					_InStream.open(_Name, std::ios::binary);

					if (!_InStream.is_open())
					{
						_Fail = true;
						return;
					}

					try
					{
						_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
					}
					catch (...)
					{
						_Fail = true;
						return;
					}

					FileContent _FileContent;

					if (!_FileContent.Load(_InStream))
					{
						_Fail = true;
						return;
					}

					if (!_Asset->Load(_FileContent))
					{
						_Fail = true;
						return;
					}
				},
				std::ref(_Fail),
				QueuedWaveFrontObjs[_Index].c_str(),
				*LoadedWaveFrontObjs.GetData(QueuedWaveFrontObjs[_Index].c_str()),
				std::ref(*LastWriteWaveFrontObjs.GetData(QueuedWaveFrontObjs[_Index].c_str()))
			)
		);
	}

	for (size_t _Index = 0; _Index < QueuedGLSLs.GetSize(); _Index++)
	{
		if (LoadedGLSLs.GetData(QueuedGLSLs[_Index].c_str()))
		{
			QueuedGLSLs.Erase(_Index);
			_Index--;
			continue;
		}

		{
			WeakPointer<FileContent>* _CachedWeak = CachedGLSLs.GetData(QueuedGLSLs[_Index].c_str());

			if (_CachedWeak)
			{
				SharedPointer<FileContent> _CachedShared = _CachedWeak->Lock();

				if ((FileContent*)(_CachedShared))
				{
					LoadedGLSLs.Emplace(QueuedGLSLs[_Index].c_str(), (SharedPointer<FileContent>&&)(_CachedShared));
					QueuedGLSLs.Erase(_Index);
					_Index--;
					continue;
				}
			}
		}

		SharedPointer<FileContent> _Asset = SharedPointer<FileContent>::MakeShared(FileContent());

		CachedGLSLs.Emplace(QueuedGLSLs[_Index].c_str(), _Asset);
		LastWriteGLSLs.Push(QueuedGLSLs[_Index].c_str(), 0);
		LoadedGLSLs.Emplace(QueuedGLSLs[_Index].c_str(), (SharedPointer<FileContent>&&)(_Asset));

		bool _Found = false;

		for (size_t _NameIndex = 0; _NameIndex < CachedGLSLNames.GetSize(); _NameIndex++)
		{
			if (CachedGLSLNames[_NameIndex] == QueuedGLSLs[_Index])
			{
				_Found = true;
				break;
			}
		}

		if (!_Found)
		{
			CachedGLSLNames.PushBack(QueuedGLSLs[_Index]);
		}
	}

	for (size_t _Index = 0; _Index < QueuedGLSLs.GetSize(); _Index++)
	{
		_Threads.EmplaceBack
		(
			std::thread
			(
				[](bool& _Fail, const BFW_CHAR_TYPE* _Name, SharedPointer<FileContent> _Asset, uint64_t& _LastWrite)
				{
					std::ifstream _InStream;

					_InStream.open(_Name, std::ios::binary);

					if (!_InStream.is_open())
					{
						_Fail = true;
						return;
					}

					try
					{
						_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
					}
					catch (...)
					{
						_Fail = true;
						return;
					}

					if (!_Asset->Load(_InStream))
					{
						_Fail = true;
						return;
					}
				},
				std::ref(_Fail),
				QueuedGLSLs[_Index].c_str(),
				*LoadedGLSLs.GetData(QueuedGLSLs[_Index].c_str()),
				std::ref(*LastWriteGLSLs.GetData(QueuedGLSLs[_Index].c_str()))
			)
		);
	}

	for (size_t _Index = 0; _Index < QueuedJsons.GetSize(); _Index++)
	{
		if (LoadedJsons.GetData(QueuedJsons[_Index].c_str()))
		{
			QueuedJsons.Erase(_Index);
			_Index--;
			continue;
		}

		{
			WeakPointer<Json>* _CachedWeak = CachedJsons.GetData(QueuedJsons[_Index].c_str());

			if (_CachedWeak)
			{
				SharedPointer<Json> _CachedShared = _CachedWeak->Lock();

				if ((Json*)(_CachedShared))
				{
					LoadedJsons.Emplace(QueuedJsons[_Index].c_str(), (SharedPointer<Json>&&)(_CachedShared));
					QueuedJsons.Erase(_Index);
					_Index--;
					continue;
				}
			}
		}

		SharedPointer<Json> _Asset = SharedPointer<Json>::MakeShared(Json());

		CachedJsons.Emplace(QueuedJsons[_Index].c_str(), _Asset);
		LastWriteJsons.Push(QueuedJsons[_Index].c_str(), 0);
		LoadedJsons.Emplace(QueuedJsons[_Index].c_str(), (SharedPointer<Json>&&)(_Asset));

		bool _Found = false;

		for (size_t _NameIndex = 0; _NameIndex < CachedJsonNames.GetSize(); _NameIndex++)
		{
			if (CachedJsonNames[_NameIndex] == QueuedJsons[_Index])
			{
				_Found = true;
				break;
			}
		}

		if (!_Found)
		{
			CachedJsonNames.PushBack(QueuedJsons[_Index]);
		}
	}

	for (size_t _Index = 0; _Index < QueuedJsons.GetSize(); _Index++)
	{
		_Threads.EmplaceBack
		(
			std::thread
			(
				[](bool& _Fail, const BFW_CHAR_TYPE* _Name, SharedPointer<Json> _Asset, uint64_t& _LastWrite)
				{
					std::ifstream _InStream;

					_InStream.open(_Name, std::ios::binary);

					if (!_InStream.is_open())
					{
						_Fail = true;
						return;
					}

					try
					{
						_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
					}
					catch (...)
					{
						_Fail = true;
						return;
					}

					FileContent _FileContent;

					if (!_FileContent.Load(_InStream))
					{
						_Fail = true;
						return;
					}

					if (!_Asset->Load(_FileContent))
					{
						_Fail = true;
						return;
					}
				},
				std::ref(_Fail),
				QueuedJsons[_Index].c_str(),
				*LoadedJsons.GetData(QueuedJsons[_Index].c_str()),
				std::ref(*LastWriteJsons.GetData(QueuedJsons[_Index].c_str()))
			)
		);
	}

#ifdef BFW_WINDOWS_PLATFORM

	for (size_t _Index = 0; _Index < QueuedResourceBitMaps.GetSize(); _Index++)
	{
		if (LoadedResourceBitMaps.GetData(BFW_TO_STRING_PTR(QueuedResourceBitMaps[_Index])))
		{
			QueuedResourceBitMaps.Erase(_Index);
			_Index--;
			continue;
		}

		{
			WeakPointer<BitMap>* _CachedWeak = CachedResourceBitMaps.GetData(BFW_TO_STRING_PTR(QueuedResourceBitMaps[_Index]));

			if (_CachedWeak)
			{
				SharedPointer<BitMap> _CachedShared = _CachedWeak->Lock();

				if ((BitMap*)(_CachedShared))
				{
					LoadedResourceBitMaps.Emplace(BFW_TO_STRING_PTR(QueuedResourceBitMaps[_Index]), (SharedPointer<BitMap>&&)(_CachedShared));
					QueuedResourceBitMaps.Erase(_Index);
					_Index--;
					continue;
				}
			}
		}

		SharedPointer<BitMap> _Asset = SharedPointer<BitMap>::MakeShared(BitMap());

		CachedResourceBitMaps.Emplace(BFW_TO_STRING_PTR(QueuedResourceBitMaps[_Index]), _Asset);
		LoadedResourceBitMaps.Emplace(BFW_TO_STRING_PTR(QueuedResourceBitMaps[_Index]), (SharedPointer<BitMap>&&)(_Asset));

		bool _Found = false;

		for (size_t _NameIndex = 0; _NameIndex < CachedResourceBitMapNames.GetSize(); _NameIndex++)
		{
			if (CachedResourceBitMapNames[_NameIndex] == BFW_TO_STRING_PTR(QueuedResourceBitMaps[_Index]))
			{
				_Found = true;
				break;
			}
		}

		if (!_Found)
		{
			CachedResourceBitMapNames.PushBack(BFW_TO_STRING_PTR(QueuedResourceBitMaps[_Index]));
		}
	}

	for (size_t _Index = 0; _Index < QueuedResourceBitMaps.GetSize(); _Index++)
	{
		_Threads.EmplaceBack
		(
			std::thread
			(
				[](bool& _Fail, const size_t _Id, SharedPointer<BitMap> _Asset)
				{
					FileContent _FileContent;

					if (!_FileContent.Load(BFW_BMP_RESOURCE, _Id))
					{
						_Fail = true;
						return;
					}

					if (!_Asset->Load(_FileContent))
					{
						_Fail = true;
						return;
					}
				},
				std::ref(_Fail),
				QueuedResourceBitMaps[_Index],
				*LoadedResourceBitMaps.GetData(BFW_TO_STRING_PTR(QueuedResourceBitMaps[_Index]))
			)
		);
	}

	for (size_t _Index = 0; _Index < QueuedResourceHdrs.GetSize(); _Index++)
	{
		if (LoadedResourceHdrs.GetData(BFW_TO_STRING_PTR(QueuedResourceHdrs[_Index])))
		{
			QueuedResourceHdrs.Erase(_Index);
			_Index--;
			continue;
		}

		{
			WeakPointer<Hdr>* _CachedWeak = CachedResourceHdrs.GetData(BFW_TO_STRING_PTR(QueuedResourceHdrs[_Index]));

			if (_CachedWeak)
			{
				SharedPointer<Hdr> _CachedShared = _CachedWeak->Lock();

				if ((Hdr*)(_CachedShared))
				{
					LoadedResourceHdrs.Emplace(BFW_TO_STRING_PTR(QueuedResourceHdrs[_Index]), (SharedPointer<Hdr>&&)(_CachedShared));
					QueuedResourceHdrs.Erase(_Index);
					_Index--;
					continue;
				}
			}
		}

		SharedPointer<Hdr> _Asset = SharedPointer<Hdr>::MakeShared(Hdr());

		CachedResourceHdrs.Emplace(BFW_TO_STRING_PTR(QueuedResourceHdrs[_Index]), _Asset);
		LoadedResourceHdrs.Emplace(BFW_TO_STRING_PTR(QueuedResourceHdrs[_Index]), (SharedPointer<Hdr>&&)(_Asset));

		bool _Found = false;

		for (size_t _NameIndex = 0; _NameIndex < CachedResourceHdrNames.GetSize(); _NameIndex++)
		{
			if (CachedResourceHdrNames[_NameIndex] == BFW_TO_STRING_PTR(QueuedResourceHdrs[_Index]))
			{
				_Found = true;
				break;
			}
		}

		if (!_Found)
		{
			CachedResourceHdrNames.PushBack(BFW_TO_STRING_PTR(QueuedResourceHdrs[_Index]));
		}
	}

	for (size_t _Index = 0; _Index < QueuedResourceHdrs.GetSize(); _Index++)
	{
		_Threads.EmplaceBack
		(
			std::thread
			(
				[](bool& _Fail, const size_t _Id, SharedPointer<Hdr> _Asset)
				{
					FileContent _FileContent;

					if (!_FileContent.Load(BFW_HDR_RESOURCE, _Id))
					{
						_Fail = true;
						return;
					}

					if (!_Asset->Load(_FileContent))
					{
						_Fail = true;
						return;
					}
				},
				std::ref(_Fail),
				QueuedResourceHdrs[_Index],
				*LoadedResourceHdrs.GetData(BFW_TO_STRING_PTR(QueuedResourceHdrs[_Index]))
			)
		);
	}

	for (size_t _Index = 0; _Index < QueuedResourceWaves.GetSize(); _Index++)
	{
		if (LoadedResourceWaves.GetData(BFW_TO_STRING_PTR(QueuedResourceWaves[_Index])))
		{
			QueuedResourceWaves.Erase(_Index);
			_Index--;
			continue;
		}

		{
			WeakPointer<Wave>* _CachedWeak = CachedResourceWaves.GetData(BFW_TO_STRING_PTR(QueuedResourceWaves[_Index]));

			if (_CachedWeak)
			{
				SharedPointer<Wave> _CachedShared = _CachedWeak->Lock();

				if ((Wave*)(_CachedShared))
				{
					LoadedResourceWaves.Emplace(BFW_TO_STRING_PTR(QueuedResourceWaves[_Index]), (SharedPointer<Wave>&&)(_CachedShared));
					QueuedResourceWaves.Erase(_Index);
					_Index--;
					continue;
				}
			}
		}

		SharedPointer<Wave> _Asset = SharedPointer<Wave>::MakeShared(Wave());

		CachedResourceWaves.Emplace(BFW_TO_STRING_PTR(QueuedResourceWaves[_Index]), _Asset);
		LoadedResourceWaves.Emplace(BFW_TO_STRING_PTR(QueuedResourceWaves[_Index]), (SharedPointer<Wave>&&)(_Asset));

		bool _Found = false;

		for (size_t _NameIndex = 0; _NameIndex < CachedResourceWaveNames.GetSize(); _NameIndex++)
		{
			if (CachedResourceWaveNames[_NameIndex] == BFW_TO_STRING_PTR(QueuedResourceWaves[_Index]))
			{
				_Found = true;
				break;
			}
		}

		if (!_Found)
		{
			CachedResourceWaveNames.PushBack(BFW_TO_STRING_PTR(QueuedResourceWaves[_Index]));
		}
	}

	for (size_t _Index = 0; _Index < QueuedResourceWaves.GetSize(); _Index++)
	{
		_Threads.EmplaceBack
		(
			std::thread
			(
				[](bool& _Fail, const size_t _Id, SharedPointer<Wave> _Asset)
				{
					FileContent _FileContent;

					if (!_FileContent.Load(BFW_WAV_RESOURCE, _Id))
					{
						_Fail = true;
						return;
					}

					if (!_Asset->Load(_FileContent))
					{
						_Fail = true;
						return;
					}
				},
				std::ref(_Fail),
				QueuedResourceWaves[_Index],
				*LoadedResourceWaves.GetData(BFW_TO_STRING_PTR(QueuedResourceWaves[_Index]))
			)
		);
	}

	for (size_t _Index = 0; _Index < QueuedResourceWaveFrontObjs.GetSize(); _Index++)
	{
		if (LoadedResourceWaveFrontObjs.GetData(BFW_TO_STRING_PTR(QueuedResourceWaveFrontObjs[_Index])))
		{
			QueuedResourceWaveFrontObjs.Erase(_Index);
			_Index--;
			continue;
		}

		{
			WeakPointer<WaveFrontObj>* _CachedWeak = CachedResourceWaveFrontObjs.GetData(BFW_TO_STRING_PTR(QueuedResourceWaveFrontObjs[_Index]));

			if (_CachedWeak)
			{
				SharedPointer<WaveFrontObj> _CachedShared = _CachedWeak->Lock();

				if ((WaveFrontObj*)(_CachedShared))
				{
					LoadedResourceWaveFrontObjs.Emplace(BFW_TO_STRING_PTR(QueuedResourceWaveFrontObjs[_Index]), (SharedPointer<WaveFrontObj>&&)(_CachedShared));
					QueuedResourceWaveFrontObjs.Erase(_Index);
					_Index--;
					continue;
				}
			}
		}

		SharedPointer<WaveFrontObj> _Asset = SharedPointer<WaveFrontObj>::MakeShared(WaveFrontObj());

		CachedResourceWaveFrontObjs.Emplace(BFW_TO_STRING_PTR(QueuedResourceWaveFrontObjs[_Index]), _Asset);
		LoadedResourceWaveFrontObjs.Emplace(BFW_TO_STRING_PTR(QueuedResourceWaveFrontObjs[_Index]), (SharedPointer<WaveFrontObj>&&)(_Asset));

		bool _Found = false;

		for (size_t _NameIndex = 0; _NameIndex < CachedResourceWaveFrontObjNames.GetSize(); _NameIndex++)
		{
			if (CachedResourceWaveFrontObjNames[_NameIndex] == BFW_TO_STRING_PTR(QueuedResourceWaveFrontObjs[_Index]))
			{
				_Found = true;
				break;
			}
		}

		if (!_Found)
		{
			CachedResourceWaveFrontObjNames.PushBack(BFW_TO_STRING_PTR(QueuedResourceWaveFrontObjs[_Index]));
		}
	}

	for (size_t _Index = 0; _Index < QueuedResourceWaveFrontObjs.GetSize(); _Index++)
	{
		_Threads.EmplaceBack
		(
			std::thread
			(
				[](bool& _Fail, const size_t _Id, SharedPointer<WaveFrontObj> _Asset)
				{
					FileContent _FileContent;

					if (!_FileContent.Load(BFW_WFOBJ_RESOURCE, _Id))
					{
						_Fail = true;
						return;
					}

					if (!_Asset->Load(_FileContent))
					{
						_Fail = true;
						return;
					}
				},
				std::ref(_Fail),
				QueuedResourceWaveFrontObjs[_Index],
				*LoadedResourceWaveFrontObjs.GetData(BFW_TO_STRING_PTR(QueuedResourceWaveFrontObjs[_Index]))
			)
		);
	}

	for (size_t _Index = 0; _Index < QueuedResourceGLSLs.GetSize(); _Index++)
	{
		if (LoadedResourceGLSLs.GetData(BFW_TO_STRING_PTR(QueuedResourceGLSLs[_Index])))
		{
			QueuedResourceGLSLs.Erase(_Index);
			_Index--;
			continue;
		}

		{
			WeakPointer<FileContent>* _CachedWeak = CachedResourceGLSLs.GetData(BFW_TO_STRING_PTR(QueuedResourceGLSLs[_Index]));

			if (_CachedWeak)
			{
				SharedPointer<FileContent> _CachedShared = _CachedWeak->Lock();

				if ((FileContent*)(_CachedShared))
				{
					LoadedResourceGLSLs.Emplace(BFW_TO_STRING_PTR(QueuedResourceGLSLs[_Index]), (SharedPointer<FileContent>&&)(_CachedShared));
					QueuedResourceGLSLs.Erase(_Index);
					_Index--;
					continue;
				}
			}
		}

		SharedPointer<FileContent> _Asset = SharedPointer<FileContent>::MakeShared(FileContent());

		CachedResourceGLSLs.Emplace(BFW_TO_STRING_PTR(QueuedResourceGLSLs[_Index]), _Asset);
		LoadedResourceGLSLs.Emplace(BFW_TO_STRING_PTR(QueuedResourceGLSLs[_Index]), (SharedPointer<FileContent>&&)(_Asset));

		bool _Found = false;

		for (size_t _NameIndex = 0; _NameIndex < CachedResourceGLSLNames.GetSize(); _NameIndex++)
		{
			if (CachedResourceGLSLNames[_NameIndex] == BFW_TO_STRING_PTR(QueuedResourceGLSLs[_Index]))
			{
				_Found = true;
				break;
			}
		}

		if (!_Found)
		{
			CachedResourceGLSLNames.PushBack(BFW_TO_STRING_PTR(QueuedResourceGLSLs[_Index]));
		}
	}

	for (size_t _Index = 0; _Index < QueuedResourceGLSLs.GetSize(); _Index++)
	{
		_Threads.EmplaceBack
		(
			std::thread
			(
				[](bool& _Fail, const size_t _Id, SharedPointer<FileContent> _Asset)
				{
					if (!_Asset->Load(BFW_GLSL_RESOURCE, _Id))
					{
						_Fail = true;
						return;
					}
				},
				std::ref(_Fail),
				QueuedResourceGLSLs[_Index],
				*LoadedResourceGLSLs.GetData(BFW_TO_STRING_PTR(QueuedResourceGLSLs[_Index]))
			)
		);
	}

	for (size_t _Index = 0; _Index < QueuedResourceJsons.GetSize(); _Index++)
	{
		if (LoadedResourceJsons.GetData(BFW_TO_STRING_PTR(QueuedResourceJsons[_Index])))
		{
			QueuedResourceJsons.Erase(_Index);
			_Index--;
			continue;
		}

		{
			WeakPointer<Json>* _CachedWeak = CachedResourceJsons.GetData(BFW_TO_STRING_PTR(QueuedResourceJsons[_Index]));

			if (_CachedWeak)
			{
				SharedPointer<Json> _CachedShared = _CachedWeak->Lock();

				if ((Json*)(_CachedShared))
				{
					LoadedResourceJsons.Emplace(BFW_TO_STRING_PTR(QueuedResourceJsons[_Index]), (SharedPointer<Json>&&)(_CachedShared));
					QueuedResourceJsons.Erase(_Index);
					_Index--;
					continue;
				}
			}
		}

		SharedPointer<Json> _Asset = SharedPointer<Json>::MakeShared(Json());

		CachedResourceJsons.Emplace(BFW_TO_STRING_PTR(QueuedResourceJsons[_Index]), _Asset);
		LoadedResourceJsons.Emplace(BFW_TO_STRING_PTR(QueuedResourceJsons[_Index]), (SharedPointer<Json>&&)(_Asset));

		bool _Found = false;

		for (size_t _NameIndex = 0; _NameIndex < CachedResourceJsonNames.GetSize(); _NameIndex++)
		{
			if (CachedResourceJsonNames[_NameIndex] == BFW_TO_STRING_PTR(QueuedResourceJsons[_Index]))
			{
				_Found = true;
				break;
			}
		}

		if (!_Found)
		{
			CachedResourceJsonNames.PushBack(BFW_TO_STRING_PTR(QueuedResourceJsons[_Index]));
		}
	}

	for (size_t _Index = 0; _Index < QueuedResourceJsons.GetSize(); _Index++)
	{
		_Threads.EmplaceBack
		(
			std::thread
			(
				[](bool& _Fail, const size_t _Id, SharedPointer<Json> _Asset)
				{
					FileContent _FileContent;

					if (!_FileContent.Load(BFW_JSON_RESOURCE, _Id))
					{
						_Fail = true;
						return;
					}

					if (!_Asset->Load(_FileContent))
					{
						_Fail = true;
						return;
					}
				},
				std::ref(_Fail),
				QueuedResourceJsons[_Index],
				*LoadedResourceJsons.GetData(BFW_TO_STRING_PTR(QueuedResourceJsons[_Index]))
			)
		);
	}

	for (size_t _Index = 0; _Index < _Threads.GetSize(); _Index++)
	{
		_Threads[_Index].join();
	}

	if (_Fail)
	{
		throw nullptr;
	}

#endif

	QueuedBitMaps.Clear();
	QueuedHdrs.Clear();
	QueuedWaves.Clear();
	QueuedWaveFrontObjs.Clear();
	QueuedGLSLs.Clear();
	QueuedJsons.Clear();

#ifdef BFW_WINDOWS_PLATFORM

	QueuedResourceBitMaps.Clear();
	QueuedResourceHdrs.Clear();
	QueuedResourceWaves.Clear();
	QueuedResourceWaveFrontObjs.Clear();
	QueuedResourceGLSLs.Clear();
	QueuedResourceJsons.Clear();

#endif
}

void BFW::Assets::Manager::AddDynamicBitMap(const BFW_CHAR_TYPE* _Name, SharedPointer<BitMap>& _Asset)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) != BFW_STRING_PREFIX("Dynamic/") || (BitMap*)(_Asset))
	{
		throw nullptr;
	}

	LoadedBitMaps.Push(_Name, _Asset);
	CachedBitMaps.Emplace(_Name, _Asset);

	bool _Found = false;

	for (size_t _Index = 0; _Index < CachedBitMapNames.GetSize(); _Index++)
	{
		if (CachedBitMapNames[_Index] == _Name)
		{
			_Found = true;
			break;
		}
	}

	if (!_Found)
	{
		CachedBitMapNames.PushBack(_Name);
	}
}

void BFW::Assets::Manager::AddDynamicHdr(const BFW_CHAR_TYPE* _Name, SharedPointer<Hdr>& _Asset)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) != BFW_STRING_PREFIX("Dynamic/") || (Hdr*)(_Asset))
	{
		throw nullptr;
	}

	LoadedHdrs.Push(_Name, _Asset);
	CachedHdrs.Emplace(_Name, _Asset);

	bool _Found = false;

	for (size_t _Index = 0; _Index < CachedHdrNames.GetSize(); _Index++)
	{
		if (CachedHdrNames[_Index] == _Name)
		{
			_Found = true;
			break;
		}
	}

	if (!_Found)
	{
		CachedHdrNames.PushBack(_Name);
	}
}

void BFW::Assets::Manager::AddDynamicWave(const BFW_CHAR_TYPE* _Name, SharedPointer<Wave>& _Asset)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) != BFW_STRING_PREFIX("Dynamic/") || (Wave*)(_Asset))
	{
		throw nullptr;
	}

	LoadedWaves.Push(_Name, _Asset);
	CachedWaves.Emplace(_Name, _Asset);

	bool _Found = false;

	for (size_t _Index = 0; _Index < CachedWaveNames.GetSize(); _Index++)
	{
		if (CachedWaveNames[_Index] == _Name)
		{
			_Found = true;
			break;
		}
	}

	if (!_Found)
	{
		CachedWaveNames.PushBack(_Name);
	}
}

void BFW::Assets::Manager::AddDynamicWaveFrontObj(const BFW_CHAR_TYPE* _Name, SharedPointer<WaveFrontObj>& _Asset)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) != BFW_STRING_PREFIX("Dynamic/") || (WaveFrontObj*)(_Asset))
	{
		throw nullptr;
	}

	LoadedWaveFrontObjs.Push(_Name, _Asset);
	CachedWaveFrontObjs.Emplace(_Name, _Asset);

	bool _Found = false;

	for (size_t _Index = 0; _Index < CachedWaveFrontObjNames.GetSize(); _Index++)
	{
		if (CachedWaveFrontObjNames[_Index] == _Name)
		{
			_Found = true;
			break;
		}
	}

	if (!_Found)
	{
		CachedWaveFrontObjNames.PushBack(_Name);
	}
}

void BFW::Assets::Manager::AddDynamicGLSL(const BFW_CHAR_TYPE* _Name, SharedPointer<FileContent>& _Asset)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) != BFW_STRING_PREFIX("Dynamic/") || (FileContent*)(_Asset))
	{
		throw nullptr;
	}

	LoadedGLSLs.Push(_Name, _Asset);
	CachedGLSLs.Emplace(_Name, _Asset);

	bool _Found = false;

	for (size_t _Index = 0; _Index < CachedGLSLNames.GetSize(); _Index++)
	{
		if (CachedGLSLNames[_Index] == _Name)
		{
			_Found = true;
			break;
		}
	}

	if (!_Found)
	{
		CachedGLSLNames.PushBack(_Name);
	}
}

void BFW::Assets::Manager::AddDynamicJson(const BFW_CHAR_TYPE* _Name, SharedPointer<Json>& _Asset)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) != BFW_STRING_PREFIX("Dynamic/") || (Json*)(_Asset))
	{
		throw nullptr;
	}

	LoadedJsons.Push(_Name, _Asset);
	CachedJsons.Emplace(_Name, _Asset);

	bool _Found = false;

	for (size_t _Index = 0; _Index < CachedJsonNames.GetSize(); _Index++)
	{
		if (CachedJsonNames[_Index] == _Name)
		{
			_Found = true;
			break;
		}
	}

	if (!_Found)
	{
		CachedJsonNames.PushBack(_Name);
	}
}

void BFW::Assets::Manager::AddDynamicBitMapRef(const BFW_CHAR_TYPE* _Name, SharedPointer<BitMap>& _Asset)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) != BFW_STRING_PREFIX("Dynamic/") || (BitMap*)(_Asset))
	{
		throw nullptr;
	}

	CachedBitMaps.Emplace(_Name, _Asset);

	bool _Found = false;

	for (size_t _Index = 0; _Index < CachedBitMapNames.GetSize(); _Index++)
	{
		if (CachedBitMapNames[_Index] == _Name)
		{
			_Found = true;
			break;
		}
	}

	if (!_Found)
	{
		CachedBitMapNames.PushBack(_Name);
	}
}

void BFW::Assets::Manager::AddDynamicHdrRef(const BFW_CHAR_TYPE* _Name, SharedPointer<Hdr>& _Asset)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) != BFW_STRING_PREFIX("Dynamic/") || (Hdr*)(_Asset))
	{
		throw nullptr;
	}

	CachedHdrs.Emplace(_Name, _Asset);

	bool _Found = false;

	for (size_t _Index = 0; _Index < CachedHdrNames.GetSize(); _Index++)
	{
		if (CachedHdrNames[_Index] == _Name)
		{
			_Found = true;
			break;
		}
	}

	if (!_Found)
	{
		CachedHdrNames.PushBack(_Name);
	}
}

void BFW::Assets::Manager::AddDynamicWaveRef(const BFW_CHAR_TYPE* _Name, SharedPointer<Wave>& _Asset)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) != BFW_STRING_PREFIX("Dynamic/") || (Wave*)(_Asset))
	{
		throw nullptr;
	}

	CachedWaves.Emplace(_Name, _Asset);

	bool _Found = false;

	for (size_t _Index = 0; _Index < CachedWaveNames.GetSize(); _Index++)
	{
		if (CachedWaveNames[_Index] == _Name)
		{
			_Found = true;
			break;
		}
	}

	if (!_Found)
	{
		CachedWaveNames.PushBack(_Name);
	}
}

void BFW::Assets::Manager::AddDynamicWaveFrontObjRef(const BFW_CHAR_TYPE* _Name, SharedPointer<WaveFrontObj>& _Asset)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) != BFW_STRING_PREFIX("Dynamic/") || (WaveFrontObj*)(_Asset))
	{
		throw nullptr;
	}

	CachedWaveFrontObjs.Emplace(_Name, _Asset);

	bool _Found = false;

	for (size_t _Index = 0; _Index < CachedWaveFrontObjNames.GetSize(); _Index++)
	{
		if (CachedWaveFrontObjNames[_Index] == _Name)
		{
			_Found = true;
			break;
		}
	}

	if (!_Found)
	{
		CachedWaveFrontObjNames.PushBack(_Name);
	}
}

void BFW::Assets::Manager::AddDynamicGLSLRef(const BFW_CHAR_TYPE* _Name, SharedPointer<FileContent>& _Asset)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) != BFW_STRING_PREFIX("Dynamic/") || (FileContent*)(_Asset))
	{
		throw nullptr;
	}

	CachedGLSLs.Emplace(_Name, _Asset);

	bool _Found = false;

	for (size_t _Index = 0; _Index < CachedGLSLNames.GetSize(); _Index++)
	{
		if (CachedGLSLNames[_Index] == _Name)
		{
			_Found = true;
			break;
		}
	}

	if (!_Found)
	{
		CachedGLSLNames.PushBack(_Name);
	}
}

void BFW::Assets::Manager::AddDynamicJsonRef(const BFW_CHAR_TYPE* _Name, SharedPointer<Json>& _Asset)
{
	if (BFW_STRING_TYPE(_Name).substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) != BFW_STRING_PREFIX("Dynamic/") || (Json*)(_Asset))
	{
		throw nullptr;
	}

	CachedJsons.Emplace(_Name, _Asset);

	bool _Found = false;

	for (size_t _Index = 0; _Index < CachedJsonNames.GetSize(); _Index++)
	{
		if (CachedJsonNames[_Index] == _Name)
		{
			_Found = true;
			break;
		}
	}

	if (!_Found)
	{
		CachedJsonNames.PushBack(_Name);
	}
}

void BFW::Assets::Manager::Update()
{
	RefreshCache();

	Vector<std::thread> _Threads;

	for (size_t _Index = 0; _Index < CachedBitMapNames.GetSize(); _Index++)
	{
		if (CachedBitMapNames[_Index].substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) == BFW_STRING_PREFIX("Dynamic/"))
		{
			continue;
		}

		uint64_t _LastWrite = 0;

		try
		{
			_LastWrite = std::filesystem::directory_entry(CachedBitMapNames[_Index]).last_write_time().time_since_epoch().count();
		}
		catch (...)
		{
			continue;
		}

		uint64_t& _OldLastWrite = *LastWriteBitMaps.GetData(CachedBitMapNames[_Index].c_str());

		if (_LastWrite == _OldLastWrite)
		{
			continue;
		}

		SharedPointer<BitMap> _CachedShared = CachedBitMaps.GetData(CachedBitMapNames[_Index].c_str())->Lock();

		if (!(BitMap*)(_CachedShared))
		{
			continue;
		}

		_Threads.EmplaceBack
		(
			std::thread
			(
				[](const BFW_CHAR_TYPE* _Name, SharedPointer<BitMap> _CachedShared, uint64_t& _OldLastWrite, const uint64_t _LastWrite)
				{
					std::ifstream _InStream;

					_InStream.open(_Name, std::ios::binary);

					if (!_InStream.is_open())
					{
						return;
					}

					FileContent _FileContent;

					if (!_FileContent.Load(_InStream))
					{
						return;
					}

					if (!_CachedShared->Load(_FileContent))
					{
						return;
					}

					_OldLastWrite = _LastWrite;
				},
				CachedBitMapNames[_Index].c_str(),
				_CachedShared,
				std::ref(_OldLastWrite),
				_LastWrite
			)
		);
	}

	for (size_t _Index = 0; _Index < CachedHdrNames.GetSize(); _Index++)
	{
		if (CachedHdrNames[_Index].substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) == BFW_STRING_PREFIX("Dynamic/"))
		{
			continue;
		}

		uint64_t _LastWrite = 0;

		try
		{
			_LastWrite = std::filesystem::directory_entry(CachedHdrNames[_Index]).last_write_time().time_since_epoch().count();
		}
		catch (...)
		{
			continue;
		}

		uint64_t& _OldLastWrite = *LastWriteHdrs.GetData(CachedHdrNames[_Index].c_str());

		if (_LastWrite == _OldLastWrite)
		{
			continue;
		}

		SharedPointer<Hdr> _CachedShared = CachedHdrs.GetData(CachedHdrNames[_Index].c_str())->Lock();

		if (!(Hdr*)(_CachedShared))
		{
			continue;
		}

		_Threads.EmplaceBack
		(
			std::thread
			(
				[](const BFW_CHAR_TYPE* _Name, SharedPointer<Hdr> _CachedShared, uint64_t& _OldLastWrite, const uint64_t _LastWrite)
				{
					std::ifstream _InStream;

					_InStream.open(_Name, std::ios::binary);

					if (!_InStream.is_open())
					{
						return;
					}

					FileContent _FileContent;

					if (!_FileContent.Load(_InStream))
					{
						return;
					}

					if (!_CachedShared->Load(_FileContent))
					{
						return;
					}

					_OldLastWrite = _LastWrite;
				},
				CachedHdrNames[_Index].c_str(),
				_CachedShared,
				std::ref(_OldLastWrite),
				_LastWrite
			)
		);
	}

	for (size_t _Index = 0; _Index < CachedWaveNames.GetSize(); _Index++)
	{
		if (CachedWaveNames[_Index].substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) == BFW_STRING_PREFIX("Dynamic/"))
		{
			continue;
		}

		uint64_t _LastWrite = 0;

		try
		{
			_LastWrite = std::filesystem::directory_entry(CachedWaveNames[_Index]).last_write_time().time_since_epoch().count();
		}
		catch (...)
		{
			continue;
		}

		uint64_t& _OldLastWrite = *LastWriteWaves.GetData(CachedWaveNames[_Index].c_str());

		if (_LastWrite == _OldLastWrite)
		{
			continue;
		}

		SharedPointer<Wave> _CachedShared = CachedWaves.GetData(CachedWaveNames[_Index].c_str())->Lock();

		if (!(Wave*)(_CachedShared))
		{
			continue;
		}

		_Threads.EmplaceBack
		(
			std::thread
			(
				[](const BFW_CHAR_TYPE* _Name, SharedPointer<Wave> _CachedShared, uint64_t& _OldLastWrite, const uint64_t _LastWrite)
				{
					std::ifstream _InStream;

					_InStream.open(_Name, std::ios::binary);

					if (!_InStream.is_open())
					{
						return;
					}

					FileContent _FileContent;

					if (!_FileContent.Load(_InStream))
					{
						return;
					}

					if (!_CachedShared->Load(_FileContent))
					{
						return;
					}

					_OldLastWrite = _LastWrite;
				},
				CachedWaveNames[_Index].c_str(),
				_CachedShared,
				std::ref(_OldLastWrite),
				_LastWrite
			)
		);
	}

	for (size_t _Index = 0; _Index < CachedWaveFrontObjNames.GetSize(); _Index++)
	{
		if (CachedWaveFrontObjNames[_Index].substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) == BFW_STRING_PREFIX("Dynamic/"))
		{
			continue;
		}

		uint64_t _LastWrite = 0;

		try
		{
			_LastWrite = std::filesystem::directory_entry(CachedWaveFrontObjNames[_Index]).last_write_time().time_since_epoch().count();
		}
		catch (...)
		{
			continue;
		}

		uint64_t& _OldLastWrite = *LastWriteWaveFrontObjs.GetData(CachedWaveFrontObjNames[_Index].c_str());

		if (_LastWrite == _OldLastWrite)
		{
			continue;
		}

		SharedPointer<WaveFrontObj> _CachedShared = CachedWaveFrontObjs.GetData(CachedWaveFrontObjNames[_Index].c_str())->Lock();

		if (!(WaveFrontObj*)(_CachedShared))
		{
			continue;
		}

		_Threads.EmplaceBack
		(
			std::thread
			(
				[](const BFW_CHAR_TYPE* _Name, SharedPointer<WaveFrontObj> _CachedShared, uint64_t& _OldLastWrite, const uint64_t _LastWrite)
				{
					std::ifstream _InStream;

					_InStream.open(_Name, std::ios::binary);

					if (!_InStream.is_open())
					{
						return;
					}

					FileContent _FileContent;

					if (!_FileContent.Load(_InStream))
					{
						return;
					}

					if (!_CachedShared->Load(_FileContent))
					{
						return;
					}

					_OldLastWrite = _LastWrite;
				},
				CachedWaveFrontObjNames[_Index].c_str(),
				_CachedShared,
				std::ref(_OldLastWrite),
				_LastWrite
			)
		);
	}

	for (size_t _Index = 0; _Index < CachedGLSLNames.GetSize(); _Index++)
	{
		if (CachedGLSLNames[_Index].substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) == BFW_STRING_PREFIX("Dynamic/"))
		{
			continue;
		}

		uint64_t _LastWrite = 0;

		try
		{
			_LastWrite = std::filesystem::directory_entry(CachedGLSLNames[_Index]).last_write_time().time_since_epoch().count();
		}
		catch (...)
		{
			continue;
		}

		uint64_t& _OldLastWrite = *LastWriteGLSLs.GetData(CachedGLSLNames[_Index].c_str());

		if (_LastWrite == _OldLastWrite)
		{
			continue;
		}

		SharedPointer<FileContent> _CachedShared = CachedGLSLs.GetData(CachedGLSLNames[_Index].c_str())->Lock();

		if (!(FileContent*)(_CachedShared))
		{
			continue;
		}

		_Threads.EmplaceBack
		(
			std::thread
			(
				[](const BFW_CHAR_TYPE* _Name, SharedPointer<FileContent> _CachedShared, uint64_t& _OldLastWrite, const uint64_t _LastWrite)
				{
					std::ifstream _InStream;

					_InStream.open(_Name, std::ios::binary);

					if (!_InStream.is_open())
					{
						return;
					}

					if (!_CachedShared->Load(_InStream))
					{
						return;
					}

					_OldLastWrite = _LastWrite;
				},
				CachedGLSLNames[_Index].c_str(),
				_CachedShared,
				std::ref(_OldLastWrite),
				_LastWrite
			)
		);
	}

	for (size_t _Index = 0; _Index < CachedJsonNames.GetSize(); _Index++)
	{
		if (CachedJsonNames[_Index].substr(0, BFW_STRING_TYPE(BFW_STRING_PREFIX("Dynamic/")).length()) == BFW_STRING_PREFIX("Dynamic/"))
		{
			continue;
		}

		uint64_t _LastWrite = 0;

		try
		{
			_LastWrite = std::filesystem::directory_entry(CachedJsonNames[_Index]).last_write_time().time_since_epoch().count();
		}
		catch (...)
		{
			continue;
		}

		uint64_t& _OldLastWrite = *LastWriteJsons.GetData(CachedJsonNames[_Index].c_str());

		if (_LastWrite == _OldLastWrite)
		{
			continue;
		}

		SharedPointer<Json> _CachedShared = CachedJsons.GetData(CachedJsonNames[_Index].c_str())->Lock();

		if (!(Json*)(_CachedShared))
		{
			continue;
		}

		_Threads.EmplaceBack
		(
			std::thread
			(
				[](const BFW_CHAR_TYPE* _Name, SharedPointer<Json> _CachedShared, uint64_t& _OldLastWrite, const uint64_t _LastWrite)
				{
					std::ifstream _InStream;

					_InStream.open(_Name, std::ios::binary);

					if (!_InStream.is_open())
					{
						return;
					}

					FileContent _FileContent;

					if (!_FileContent.Load(_InStream))
					{
						return;
					}

					if (!_CachedShared->Load(_FileContent))
					{
						return;
					}

					_OldLastWrite = _LastWrite;
				},
				CachedJsonNames[_Index].c_str(),
				_CachedShared,
				std::ref(_OldLastWrite),
				_LastWrite
			)
		);
	}

	for (size_t _Index = 0; _Index < _Threads.GetSize(); _Index++)
	{
		_Threads[_Index].join();
	}
}

void BFW::Assets::Manager::ReleaseBitMap(const BFW_CHAR_TYPE* _Name)
{
	LoadedBitMaps.Erase(_Name);
	CachedBitMaps.Erase(_Name);
	LastWriteBitMaps.Erase(_Name);

	for (size_t _Index = 0; _Index < CachedBitMapNames.GetSize(); _Index++)
	{
		if (CachedBitMapNames[_Index] == _Name)
		{
			CachedBitMapNames.Erase(_Index);
			break;
		}
	}
}

void BFW::Assets::Manager::ReleaseHdr(const BFW_CHAR_TYPE* _Name)
{
	LoadedHdrs.Erase(_Name);
	CachedHdrs.Erase(_Name);
	LastWriteHdrs.Erase(_Name);

	for (size_t _Index = 0; _Index < CachedHdrNames.GetSize(); _Index++)
	{
		if (CachedHdrNames[_Index] == _Name)
		{
			CachedHdrNames.Erase(_Index);
			break;
		}
	}
}

void BFW::Assets::Manager::ReleaseWave(const BFW_CHAR_TYPE* _Name)
{
	LoadedWaves.Erase(_Name);
	CachedWaves.Erase(_Name);
	LastWriteWaves.Erase(_Name);

	for (size_t _Index = 0; _Index < CachedWaveNames.GetSize(); _Index++)
	{
		if (CachedWaveNames[_Index] == _Name)
		{
			CachedWaveNames.Erase(_Index);
			break;
		}
	}
}

void BFW::Assets::Manager::ReleaseWaveFrontObj(const BFW_CHAR_TYPE* _Name)
{
	LoadedWaveFrontObjs.Erase(_Name);
	CachedWaveFrontObjs.Erase(_Name);
	LastWriteWaveFrontObjs.Erase(_Name);

	for (size_t _Index = 0; _Index < CachedWaveFrontObjNames.GetSize(); _Index++)
	{
		if (CachedWaveFrontObjNames[_Index] == _Name)
		{
			CachedWaveFrontObjNames.Erase(_Index);
			break;
		}
	}
}

void BFW::Assets::Manager::ReleaseGLSL(const BFW_CHAR_TYPE* _Name)
{
	LoadedGLSLs.Erase(_Name);
	CachedGLSLs.Erase(_Name);
	LastWriteGLSLs.Erase(_Name);

	for (size_t _Index = 0; _Index < CachedGLSLNames.GetSize(); _Index++)
	{
		if (CachedGLSLNames[_Index] == _Name)
		{
			CachedGLSLNames.Erase(_Index);
			break;
		}
	}
}

void BFW::Assets::Manager::ReleaseJson(const BFW_CHAR_TYPE* _Name)
{
	LoadedJsons.Erase(_Name);
	CachedJsons.Erase(_Name);
	LastWriteJsons.Erase(_Name);

	for (size_t _Index = 0; _Index < CachedJsonNames.GetSize(); _Index++)
	{
		if (CachedJsonNames[_Index] == _Name)
		{
			CachedJsonNames.Erase(_Index);
			break;
		}
	}
}

#ifdef BFW_WINDOWS_PLATFORM

void BFW::Assets::Manager::ReleaseResourceBitMap(const size_t _Id)
{
	LoadedResourceBitMaps.Erase(BFW_TO_STRING_PTR(_Id));
	CachedResourceBitMaps.Erase(BFW_TO_STRING_PTR(_Id));

	for (size_t _Index = 0; _Index < CachedResourceBitMapNames.GetSize(); _Index++)
	{
		if (CachedResourceBitMapNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			CachedResourceBitMapNames.Erase(_Index);
			break;
		}
	}
}

void BFW::Assets::Manager::ReleaseResourceHdr(const size_t _Id)
{
	LoadedResourceHdrs.Erase(BFW_TO_STRING_PTR(_Id));
	CachedResourceHdrs.Erase(BFW_TO_STRING_PTR(_Id));

	for (size_t _Index = 0; _Index < CachedResourceHdrNames.GetSize(); _Index++)
	{
		if (CachedResourceHdrNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			CachedResourceHdrNames.Erase(_Index);
			break;
		}
	}
}

void BFW::Assets::Manager::ReleaseResourceWave(const size_t _Id)
{
	LoadedResourceWaves.Erase(BFW_TO_STRING_PTR(_Id));
	CachedResourceWaves.Erase(BFW_TO_STRING_PTR(_Id));

	for (size_t _Index = 0; _Index < CachedResourceWaveNames.GetSize(); _Index++)
	{
		if (CachedResourceWaveNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			CachedResourceWaveNames.Erase(_Index);
			break;
		}
	}
}

void BFW::Assets::Manager::ReleaseResourceWaveFrontObj(const size_t _Id)
{
	LoadedResourceWaveFrontObjs.Erase(BFW_TO_STRING_PTR(_Id));
	CachedResourceWaveFrontObjs.Erase(BFW_TO_STRING_PTR(_Id));

	for (size_t _Index = 0; _Index < CachedResourceWaveFrontObjNames.GetSize(); _Index++)
	{
		if (CachedResourceWaveFrontObjNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			CachedResourceWaveFrontObjNames.Erase(_Index);
			break;
		}
	}
}

void BFW::Assets::Manager::ReleaseResourceGLSL(const size_t _Id)
{
	LoadedResourceGLSLs.Erase(BFW_TO_STRING_PTR(_Id));
	CachedResourceGLSLs.Erase(BFW_TO_STRING_PTR(_Id));

	for (size_t _Index = 0; _Index < CachedResourceGLSLNames.GetSize(); _Index++)
	{
		if (CachedResourceGLSLNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			CachedResourceGLSLNames.Erase(_Index);
			break;
		}
	}
}

void BFW::Assets::Manager::ReleaseResourceJson(const size_t _Id)
{
	LoadedResourceJsons.Erase(BFW_TO_STRING_PTR(_Id));
	CachedResourceJsons.Erase(BFW_TO_STRING_PTR(_Id));

	for (size_t _Index = 0; _Index < CachedResourceJsonNames.GetSize(); _Index++)
	{
		if (CachedResourceJsonNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			CachedResourceJsonNames.Erase(_Index);
			break;
		}
	}
}

#endif

BFW::SharedPointer<BFW::Assets::BitMap> BFW::Assets::Manager::GetBitMap(const BFW_CHAR_TYPE* _Name)
{
	WeakPointer<BitMap>* _CachedWeak = CachedBitMaps.GetData(_Name);

	if (_CachedWeak)
	{
		SharedPointer<BitMap> _CachedShared = _CachedWeak->Lock();

		if ((BitMap*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	std::ifstream _InStream;

	_InStream.open(_Name, std::ios::binary);

	if (!_InStream.is_open())
	{
		throw nullptr;
	}

	uint64_t _LastWrite = 0;

	try
	{
		_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
	}
	catch (...)
	{
		throw nullptr;
	}

	FileContent _FileContent;

	if (!_FileContent.Load(_InStream))
	{
		throw nullptr;
	}

	SharedPointer<BitMap> _Shared = SharedPointer<BitMap>::MakeShared(BitMap());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedBitMaps.Emplace(_Name, _Shared);
	LastWriteBitMaps.Push(_Name, _LastWrite);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedBitMapNames.GetSize(); _Index++)
	{
		if (CachedBitMapNames[_Index] == _Name)
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedBitMapNames.PushBack(_Name);
	}

	return _Shared;
}

const BFW::SharedPointer<BFW::Assets::BitMap> BFW::Assets::Manager::GetBitMap(const BFW_CHAR_TYPE* _Name) const
{
	WeakPointer<BitMap>* _CachedWeak = CachedBitMaps.GetData(_Name);

	if (_CachedWeak)
	{
		SharedPointer<BitMap> _CachedShared = _CachedWeak->Lock();

		if ((BitMap*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	std::ifstream _InStream;

	_InStream.open(_Name, std::ios::binary);

	if (!_InStream.is_open())
	{
		throw nullptr;
	}

	uint64_t _LastWrite = 0;

	try
	{
		_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
	}
	catch (...)
	{
		throw nullptr;
	}

	FileContent _FileContent;

	if (!_FileContent.Load(_InStream))
	{
		throw nullptr;
	}

	SharedPointer<BitMap> _Shared = SharedPointer<BitMap>::MakeShared(BitMap());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedBitMaps.Emplace(_Name, _Shared);
	LastWriteBitMaps.Push(_Name, _LastWrite);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedBitMapNames.GetSize(); _Index++)
	{
		if (CachedBitMapNames[_Index] == _Name)
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedBitMapNames.PushBack(_Name);
	}

	return _Shared;
}

BFW::SharedPointer<BFW::Assets::Hdr> BFW::Assets::Manager::GetHdr(const BFW_CHAR_TYPE* _Name)
{
	WeakPointer<Hdr>* _CachedWeak = CachedHdrs.GetData(_Name);

	if (_CachedWeak)
	{
		SharedPointer<Hdr> _CachedShared = _CachedWeak->Lock();

		if ((Hdr*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	std::ifstream _InStream;

	_InStream.open(_Name, std::ios::binary);

	if (!_InStream.is_open())
	{
		throw nullptr;
	}

	uint64_t _LastWrite = 0;

	try
	{
		_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
	}
	catch (...)
	{
		throw nullptr;
	}

	FileContent _FileContent;

	if (!_FileContent.Load(_InStream))
	{
		throw nullptr;
	}

	SharedPointer<Hdr> _Shared = SharedPointer<Hdr>::MakeShared(Hdr());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedHdrs.Emplace(_Name, _Shared);
	LastWriteHdrs.Push(_Name, _LastWrite);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedHdrNames.GetSize(); _Index++)
	{
		if (CachedHdrNames[_Index] == _Name)
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedHdrNames.PushBack(_Name);
	}

	return _Shared;
}

const BFW::SharedPointer<BFW::Assets::Hdr> BFW::Assets::Manager::GetHdr(const BFW_CHAR_TYPE* _Name) const
{
	WeakPointer<Hdr>* _CachedWeak = CachedHdrs.GetData(_Name);

	if (_CachedWeak)
	{
		SharedPointer<Hdr> _CachedShared = _CachedWeak->Lock();

		if ((Hdr*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	std::ifstream _InStream;

	_InStream.open(_Name, std::ios::binary);

	if (!_InStream.is_open())
	{
		throw nullptr;
	}

	uint64_t _LastWrite = 0;

	try
	{
		_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
	}
	catch (...)
	{
		throw nullptr;
	}

	FileContent _FileContent;

	if (!_FileContent.Load(_InStream))
	{
		throw nullptr;
	}

	SharedPointer<Hdr> _Shared = SharedPointer<Hdr>::MakeShared(Hdr());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedHdrs.Emplace(_Name, _Shared);
	LastWriteHdrs.Push(_Name, _LastWrite);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedHdrNames.GetSize(); _Index++)
	{
		if (CachedHdrNames[_Index] == _Name)
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedHdrNames.PushBack(_Name);
	}

	return _Shared;
}

BFW::SharedPointer<BFW::Assets::Wave> BFW::Assets::Manager::GetWave(const BFW_CHAR_TYPE* _Name)
{
	WeakPointer<Wave>* _CachedWeak = CachedWaves.GetData(_Name);

	if (_CachedWeak)
	{
		SharedPointer<Wave> _CachedShared = _CachedWeak->Lock();

		if ((Wave*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	std::ifstream _InStream;

	_InStream.open(_Name, std::ios::binary);

	if (!_InStream.is_open())
	{
		throw nullptr;
	}

	uint64_t _LastWrite = 0;

	try
	{
		_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
	}
	catch (...)
	{
		throw nullptr;
	}

	FileContent _FileContent;

	if (!_FileContent.Load(_InStream))
	{
		throw nullptr;
	}

	SharedPointer<Wave> _Shared = SharedPointer<Wave>::MakeShared(Wave());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedWaves.Emplace(_Name, _Shared);
	LastWriteWaves.Push(_Name, _LastWrite);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedWaveNames.GetSize(); _Index++)
	{
		if (CachedWaveNames[_Index] == _Name)
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedWaveNames.PushBack(_Name);
	}

	return _Shared;
}

const BFW::SharedPointer<BFW::Assets::Wave> BFW::Assets::Manager::GetWave(const BFW_CHAR_TYPE* _Name) const
{
	WeakPointer<Wave>* _CachedWeak = CachedWaves.GetData(_Name);

	if (_CachedWeak)
	{
		SharedPointer<Wave> _CachedShared = _CachedWeak->Lock();

		if ((Wave*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	std::ifstream _InStream;

	_InStream.open(_Name, std::ios::binary);

	if (!_InStream.is_open())
	{
		throw nullptr;
	}

	uint64_t _LastWrite = 0;

	try
	{
		_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
	}
	catch (...)
	{
		throw nullptr;
	}

	FileContent _FileContent;

	if (!_FileContent.Load(_InStream))
	{
		throw nullptr;
	}

	SharedPointer<Wave> _Shared = SharedPointer<Wave>::MakeShared(Wave());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedWaves.Emplace(_Name, _Shared);
	LastWriteWaves.Push(_Name, _LastWrite);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedWaveNames.GetSize(); _Index++)
	{
		if (CachedWaveNames[_Index] == _Name)
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedWaveNames.PushBack(_Name);
	}

	return _Shared;
}

BFW::SharedPointer<BFW::Assets::WaveFrontObj> BFW::Assets::Manager::GetWaveFrontObj(const BFW_CHAR_TYPE* _Name)
{
	WeakPointer<WaveFrontObj>* _CachedWeak = CachedWaveFrontObjs.GetData(_Name);

	if (_CachedWeak)
	{
		SharedPointer<WaveFrontObj> _CachedShared = _CachedWeak->Lock();

		if ((WaveFrontObj*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	std::ifstream _InStream;

	_InStream.open(_Name, std::ios::binary);

	if (!_InStream.is_open())
	{
		throw nullptr;
	}

	uint64_t _LastWrite = 0;

	try
	{
		_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
	}
	catch (...)
	{
		throw nullptr;
	}

	FileContent _FileContent;

	if (!_FileContent.Load(_InStream))
	{
		throw nullptr;
	}

	SharedPointer<WaveFrontObj> _Shared = SharedPointer<WaveFrontObj>::MakeShared(WaveFrontObj());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedWaveFrontObjs.Emplace(_Name, _Shared);
	LastWriteWaveFrontObjs.Push(_Name, _LastWrite);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedWaveFrontObjNames.GetSize(); _Index++)
	{
		if (CachedWaveFrontObjNames[_Index] == _Name)
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedWaveFrontObjNames.PushBack(_Name);
	}

	return _Shared;
}

const BFW::SharedPointer<BFW::Assets::WaveFrontObj> BFW::Assets::Manager::GetWaveFrontObj(const BFW_CHAR_TYPE* _Name) const
{
	WeakPointer<WaveFrontObj>* _CachedWeak = CachedWaveFrontObjs.GetData(_Name);

	if (_CachedWeak)
	{
		SharedPointer<WaveFrontObj> _CachedShared = _CachedWeak->Lock();

		if ((WaveFrontObj*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	std::ifstream _InStream;

	_InStream.open(_Name, std::ios::binary);

	if (!_InStream.is_open())
	{
		throw nullptr;
	}

	uint64_t _LastWrite = 0;

	try
	{
		_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
	}
	catch (...)
	{
		throw nullptr;
	}

	FileContent _FileContent;

	if (!_FileContent.Load(_InStream))
	{
		throw nullptr;
	}

	SharedPointer<WaveFrontObj> _Shared = SharedPointer<WaveFrontObj>::MakeShared(WaveFrontObj());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedWaveFrontObjs.Emplace(_Name, _Shared);
	LastWriteWaveFrontObjs.Push(_Name, _LastWrite);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedWaveFrontObjNames.GetSize(); _Index++)
	{
		if (CachedWaveFrontObjNames[_Index] == _Name)
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedWaveFrontObjNames.PushBack(_Name);
	}

	return _Shared;
}

BFW::SharedPointer<BFW::Assets::FileContent> BFW::Assets::Manager::GetGLSL(const BFW_CHAR_TYPE* _Name)
{
	WeakPointer<FileContent>* _CachedWeak = CachedGLSLs.GetData(_Name);

	if (_CachedWeak)
	{
		SharedPointer<FileContent> _CachedShared = _CachedWeak->Lock();

		if ((FileContent*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	std::ifstream _InStream;

	_InStream.open(_Name, std::ios::binary);

	if (!_InStream.is_open())
	{
		throw nullptr;
	}

	uint64_t _LastWrite = 0;

	try
	{
		_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
	}
	catch (...)
	{
		throw nullptr;
	}

	SharedPointer<FileContent> _Shared = SharedPointer<FileContent>::MakeShared(FileContent());

	if (!_Shared->Load(_InStream))
	{
		throw nullptr;
	}

	CachedGLSLs.Emplace(_Name, _Shared);
	LastWriteGLSLs.Push(_Name, _LastWrite);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedGLSLNames.GetSize(); _Index++)
	{
		if (CachedGLSLNames[_Index] == _Name)
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedGLSLNames.PushBack(_Name);
	}

	return _Shared;
}

const BFW::SharedPointer<BFW::Assets::FileContent> BFW::Assets::Manager::GetGLSL(const BFW_CHAR_TYPE* _Name) const
{
	WeakPointer<FileContent>* _CachedWeak = CachedGLSLs.GetData(_Name);

	if (_CachedWeak)
	{
		SharedPointer<FileContent> _CachedShared = _CachedWeak->Lock();

		if ((FileContent*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	std::ifstream _InStream;

	_InStream.open(_Name, std::ios::binary);

	if (!_InStream.is_open())
	{
		throw nullptr;
	}

	uint64_t _LastWrite = 0;

	try
	{
		_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
	}
	catch (...)
	{
		throw nullptr;
	}

	SharedPointer<FileContent> _Shared = SharedPointer<FileContent>::MakeShared(FileContent());

	if (!_Shared->Load(_InStream))
	{
		throw nullptr;
	}

	CachedGLSLs.Emplace(_Name, _Shared);
	LastWriteGLSLs.Push(_Name, _LastWrite);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedGLSLNames.GetSize(); _Index++)
	{
		if (CachedGLSLNames[_Index] == _Name)
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedGLSLNames.PushBack(_Name);
	}

	return _Shared;
}

BFW::SharedPointer<BFW::Assets::Json> BFW::Assets::Manager::GetJson(const BFW_CHAR_TYPE* _Name)
{
	WeakPointer<Json>* _CachedWeak = CachedJsons.GetData(_Name);

	if (_CachedWeak)
	{
		SharedPointer<Json> _CachedShared = _CachedWeak->Lock();

		if ((Json*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	std::ifstream _InStream;

	_InStream.open(_Name, std::ios::binary);

	if (!_InStream.is_open())
	{
		throw nullptr;
	}

	uint64_t _LastWrite = 0;

	try
	{
		_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
	}
	catch (...)
	{
		throw nullptr;
	}

	FileContent _FileContent;

	if (!_FileContent.Load(_InStream))
	{
		throw nullptr;
	}

	SharedPointer<Json> _Shared = SharedPointer<Json>::MakeShared(Json());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedJsons.Emplace(_Name, _Shared);
	LastWriteJsons.Push(_Name, _LastWrite);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedJsonNames.GetSize(); _Index++)
	{
		if (CachedJsonNames[_Index] == _Name)
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedJsonNames.PushBack(_Name);
	}

	return _Shared;
}

const BFW::SharedPointer<BFW::Assets::Json> BFW::Assets::Manager::GetJson(const BFW_CHAR_TYPE* _Name) const
{
	WeakPointer<Json>* _CachedWeak = CachedJsons.GetData(_Name);

	if (_CachedWeak)
	{
		SharedPointer<Json> _CachedShared = _CachedWeak->Lock();

		if ((Json*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	std::ifstream _InStream;

	_InStream.open(_Name, std::ios::binary);

	if (!_InStream.is_open())
	{
		throw nullptr;
	}

	uint64_t _LastWrite = 0;

	try
	{
		_LastWrite = std::filesystem::directory_entry(_Name).last_write_time().time_since_epoch().count();
	}
	catch (...)
	{
		throw nullptr;
	}

	FileContent _FileContent;

	if (!_FileContent.Load(_InStream))
	{
		throw nullptr;
	}

	SharedPointer<Json> _Shared = SharedPointer<Json>::MakeShared(Json());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedJsons.Emplace(_Name, _Shared);
	LastWriteJsons.Push(_Name, _LastWrite);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedJsonNames.GetSize(); _Index++)
	{
		if (CachedJsonNames[_Index] == _Name)
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedJsonNames.PushBack(_Name);
	}

	return _Shared;
}

#ifdef BFW_WINDOWS_PLATFORM

BFW::SharedPointer<BFW::Assets::BitMap> BFW::Assets::Manager::GetResourceBitMap(const size_t _Id)
{
	WeakPointer<BitMap>* _CachedWeak = CachedResourceBitMaps.GetData(BFW_TO_STRING_PTR(_Id));

	if (_CachedWeak)
	{
		SharedPointer<BitMap> _CachedShared = _CachedWeak->Lock();

		if ((BitMap*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	FileContent _FileContent;

	if (!_FileContent.Load(BFW_BMP_RESOURCE, _Id))
	{
		throw nullptr;
	}

	SharedPointer<BitMap> _Shared = SharedPointer<BitMap>::MakeShared(BitMap());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedResourceBitMaps.Emplace(BFW_TO_STRING_PTR(_Id), _Shared);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedResourceBitMapNames.GetSize(); _Index++)
	{
		if (CachedResourceBitMapNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedResourceBitMapNames.PushBack(BFW_TO_STRING_PTR(_Id));
	}

	return _Shared;
}

const BFW::SharedPointer<BFW::Assets::BitMap> BFW::Assets::Manager::GetResourceBitMap(const size_t _Id) const
{
	WeakPointer<BitMap>* _CachedWeak = CachedResourceBitMaps.GetData(BFW_TO_STRING_PTR(_Id));

	if (_CachedWeak)
	{
		SharedPointer<BitMap> _CachedShared = _CachedWeak->Lock();

		if ((BitMap*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	FileContent _FileContent;

	if (!_FileContent.Load(BFW_BMP_RESOURCE, _Id))
	{
		throw nullptr;
	}

	SharedPointer<BitMap> _Shared = SharedPointer<BitMap>::MakeShared(BitMap());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedResourceBitMaps.Emplace(BFW_TO_STRING_PTR(_Id), _Shared);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedResourceBitMapNames.GetSize(); _Index++)
	{
		if (CachedResourceBitMapNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedResourceBitMapNames.PushBack(BFW_TO_STRING_PTR(_Id));
	}

	return _Shared;
}

BFW::SharedPointer<BFW::Assets::Hdr> BFW::Assets::Manager::GetResourceHdr(const size_t _Id)
{
	WeakPointer<Hdr>* _CachedWeak = CachedResourceHdrs.GetData(BFW_TO_STRING_PTR(_Id));

	if (_CachedWeak)
	{
		SharedPointer<Hdr> _CachedShared = _CachedWeak->Lock();

		if ((Hdr*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	FileContent _FileContent;

	if (!_FileContent.Load(BFW_HDR_RESOURCE, _Id))
	{
		throw nullptr;
	}

	SharedPointer<Hdr> _Shared = SharedPointer<Hdr>::MakeShared(Hdr());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedResourceHdrs.Emplace(BFW_TO_STRING_PTR(_Id), _Shared);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedResourceHdrNames.GetSize(); _Index++)
	{
		if (CachedResourceHdrNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedResourceHdrNames.PushBack(BFW_TO_STRING_PTR(_Id));
	}

	return _Shared;
}

const BFW::SharedPointer<BFW::Assets::Hdr> BFW::Assets::Manager::GetResourceHdr(const size_t _Id) const
{
	WeakPointer<Hdr>* _CachedWeak = CachedResourceHdrs.GetData(BFW_TO_STRING_PTR(_Id));

	if (_CachedWeak)
	{
		SharedPointer<Hdr> _CachedShared = _CachedWeak->Lock();

		if ((Hdr*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	FileContent _FileContent;

	if (!_FileContent.Load(BFW_HDR_RESOURCE, _Id))
	{
		throw nullptr;
	}

	SharedPointer<Hdr> _Shared = SharedPointer<Hdr>::MakeShared(Hdr());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedResourceHdrs.Emplace(BFW_TO_STRING_PTR(_Id), _Shared);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedResourceHdrNames.GetSize(); _Index++)
	{
		if (CachedResourceHdrNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedResourceHdrNames.PushBack(BFW_TO_STRING_PTR(_Id));
	}

	return _Shared;
}

BFW::SharedPointer<BFW::Assets::Wave> BFW::Assets::Manager::GetResourceWave(const size_t _Id)
{
	WeakPointer<Wave>* _CachedWeak = CachedResourceWaves.GetData(BFW_TO_STRING_PTR(_Id));

	if (_CachedWeak)
	{
		SharedPointer<Wave> _CachedShared = _CachedWeak->Lock();

		if ((Wave*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	FileContent _FileContent;

	if (!_FileContent.Load(BFW_WAV_RESOURCE, _Id))
	{
		throw nullptr;
	}

	SharedPointer<Wave> _Shared = SharedPointer<Wave>::MakeShared(Wave());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedResourceWaves.Emplace(BFW_TO_STRING_PTR(_Id), _Shared);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedResourceWaveNames.GetSize(); _Index++)
	{
		if (CachedResourceWaveNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedResourceWaveNames.PushBack(BFW_TO_STRING_PTR(_Id));
	}

	return _Shared;
}

const BFW::SharedPointer<BFW::Assets::Wave> BFW::Assets::Manager::GetResourceWave(const size_t _Id) const
{
	WeakPointer<Wave>* _CachedWeak = CachedResourceWaves.GetData(BFW_TO_STRING_PTR(_Id));

	if (_CachedWeak)
	{
		SharedPointer<Wave> _CachedShared = _CachedWeak->Lock();

		if ((Wave*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	FileContent _FileContent;

	if (!_FileContent.Load(BFW_WAV_RESOURCE, _Id))
	{
		throw nullptr;
	}

	SharedPointer<Wave> _Shared = SharedPointer<Wave>::MakeShared(Wave());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedResourceWaves.Emplace(BFW_TO_STRING_PTR(_Id), _Shared);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedResourceWaveNames.GetSize(); _Index++)
	{
		if (CachedResourceWaveNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedResourceWaveNames.PushBack(BFW_TO_STRING_PTR(_Id));
	}

	return _Shared;
}

BFW::SharedPointer<BFW::Assets::WaveFrontObj> BFW::Assets::Manager::GetResourceWaveFrontObj(const size_t _Id)
{
	WeakPointer<WaveFrontObj>* _CachedWeak = CachedResourceWaveFrontObjs.GetData(BFW_TO_STRING_PTR(_Id));

	if (_CachedWeak)
	{
		SharedPointer<WaveFrontObj> _CachedShared = _CachedWeak->Lock();

		if ((WaveFrontObj*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	FileContent _FileContent;

	if (!_FileContent.Load(BFW_WFOBJ_RESOURCE, _Id))
	{
		throw nullptr;
	}

	SharedPointer<WaveFrontObj> _Shared = SharedPointer<WaveFrontObj>::MakeShared(WaveFrontObj());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedResourceWaveFrontObjs.Emplace(BFW_TO_STRING_PTR(_Id), _Shared);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedResourceWaveFrontObjNames.GetSize(); _Index++)
	{
		if (CachedResourceWaveFrontObjNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedResourceWaveFrontObjNames.PushBack(BFW_TO_STRING_PTR(_Id));
	}

	return _Shared;
}

const BFW::SharedPointer<BFW::Assets::WaveFrontObj> BFW::Assets::Manager::GetResourceWaveFrontObj(const size_t _Id) const
{
	WeakPointer<WaveFrontObj>* _CachedWeak = CachedResourceWaveFrontObjs.GetData(BFW_TO_STRING_PTR(_Id));

	if (_CachedWeak)
	{
		SharedPointer<WaveFrontObj> _CachedShared = _CachedWeak->Lock();

		if ((WaveFrontObj*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	FileContent _FileContent;

	if (!_FileContent.Load(BFW_WFOBJ_RESOURCE, _Id))
	{
		throw nullptr;
	}

	SharedPointer<WaveFrontObj> _Shared = SharedPointer<WaveFrontObj>::MakeShared(WaveFrontObj());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedResourceWaveFrontObjs.Emplace(BFW_TO_STRING_PTR(_Id), _Shared);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedResourceWaveFrontObjNames.GetSize(); _Index++)
	{
		if (CachedResourceWaveFrontObjNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedResourceWaveFrontObjNames.PushBack(BFW_TO_STRING_PTR(_Id));
	}

	return _Shared;
}

BFW::SharedPointer<BFW::Assets::FileContent> BFW::Assets::Manager::GetResourceGLSL(const size_t _Id)
{
	WeakPointer<FileContent>* _CachedWeak = CachedResourceGLSLs.GetData(BFW_TO_STRING_PTR(_Id));

	if (_CachedWeak)
	{
		SharedPointer<FileContent> _CachedShared = _CachedWeak->Lock();

		if ((FileContent*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	SharedPointer<FileContent> _Shared = SharedPointer<FileContent>::MakeShared(FileContent());

	if (!_Shared->Load(BFW_GLSL_RESOURCE, _Id))
	{
		throw nullptr;
	}

	CachedResourceGLSLs.Emplace(BFW_TO_STRING_PTR(_Id), _Shared);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedResourceGLSLNames.GetSize(); _Index++)
	{
		if (CachedResourceGLSLNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedResourceGLSLNames.PushBack(BFW_TO_STRING_PTR(_Id));
	}

	return _Shared;
}

const BFW::SharedPointer<BFW::Assets::FileContent> BFW::Assets::Manager::GetResourceGLSL(const size_t _Id) const
{
	WeakPointer<FileContent>* _CachedWeak = CachedResourceGLSLs.GetData(BFW_TO_STRING_PTR(_Id));

	if (_CachedWeak)
	{
		SharedPointer<FileContent> _CachedShared = _CachedWeak->Lock();

		if ((FileContent*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	SharedPointer<FileContent> _Shared = SharedPointer<FileContent>::MakeShared(FileContent());

	if (!_Shared->Load(BFW_GLSL_RESOURCE, _Id))
	{
		throw nullptr;
	}

	CachedResourceGLSLs.Emplace(BFW_TO_STRING_PTR(_Id), _Shared);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedResourceGLSLNames.GetSize(); _Index++)
	{
		if (CachedResourceGLSLNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedResourceGLSLNames.PushBack(BFW_TO_STRING_PTR(_Id));
	}

	return _Shared;
}

BFW::SharedPointer<BFW::Assets::Json> BFW::Assets::Manager::GetResourceJson(const size_t _Id)
{
	WeakPointer<Json>* _CachedWeak = CachedResourceJsons.GetData(BFW_TO_STRING_PTR(_Id));

	if (_CachedWeak)
	{
		SharedPointer<Json> _CachedShared = _CachedWeak->Lock();

		if ((Json*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	FileContent _FileContent;

	if (!_FileContent.Load(BFW_JSON_RESOURCE, _Id))
	{
		throw nullptr;
	}

	SharedPointer<Json> _Shared = SharedPointer<Json>::MakeShared(Json());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedResourceJsons.Emplace(BFW_TO_STRING_PTR(_Id), _Shared);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedResourceJsonNames.GetSize(); _Index++)
	{
		if (CachedResourceJsonNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedResourceJsonNames.PushBack(BFW_TO_STRING_PTR(_Id));
	}

	return _Shared;
}

const BFW::SharedPointer<BFW::Assets::Json> BFW::Assets::Manager::GetResourceJson(const size_t _Id) const
{
	WeakPointer<Json>* _CachedWeak = CachedResourceJsons.GetData(BFW_TO_STRING_PTR(_Id));

	if (_CachedWeak)
	{
		SharedPointer<Json> _CachedShared = _CachedWeak->Lock();

		if ((Json*)(_CachedShared))
		{
			return _CachedShared;
		}
	}

	FileContent _FileContent;

	if (!_FileContent.Load(BFW_JSON_RESOURCE, _Id))
	{
		throw nullptr;
	}

	SharedPointer<Json> _Shared = SharedPointer<Json>::MakeShared(Json());

	if (!_Shared->Load(_FileContent))
	{
		throw nullptr;
	}

	CachedResourceJsons.Emplace(BFW_TO_STRING_PTR(_Id), _Shared);

	bool _FoundName = false;

	for (size_t _Index = 0; _Index < CachedResourceJsonNames.GetSize(); _Index++)
	{
		if (CachedResourceJsonNames[_Index] == BFW_TO_STRING_PTR(_Id))
		{
			_FoundName = true;
		}
	}

	if (!_FoundName)
	{
		CachedResourceJsonNames.PushBack(BFW_TO_STRING_PTR(_Id));
	}

	return _Shared;
}

#endif

#ifdef BFW_WINDOWS_PLATFORM

BFW::Assets::Manager& BFW::Assets::Manager::operator= (Manager&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	QueuedBitMaps = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedBitMaps);
	QueuedHdrs = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedHdrs);
	QueuedWaves = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedWaves);
	QueuedWaveFrontObjs = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedWaveFrontObjs);
	QueuedGLSLs = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedGLSLs);
	QueuedJsons = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedJsons);
	QueuedResourceBitMaps = (Vector<size_t>&&)(_Other.QueuedResourceBitMaps);
	QueuedResourceHdrs = (Vector<size_t>&&)(_Other.QueuedResourceHdrs);
	QueuedResourceWaves = (Vector<size_t>&&)(_Other.QueuedResourceWaves);
	QueuedResourceWaveFrontObjs = (Vector<size_t>&&)(_Other.QueuedResourceWaveFrontObjs);
	QueuedResourceGLSLs = (Vector<size_t>&&)(_Other.QueuedResourceGLSLs);
	QueuedResourceJsons = (Vector<size_t>&&)(_Other.QueuedResourceJsons);
	LoadedBitMaps = (Trie<SharedPointer<BitMap>>&&)(_Other.LoadedBitMaps);
	LoadedHdrs = (Trie<SharedPointer<Hdr>>&&)(_Other.LoadedHdrs);
	LoadedWaves = (Trie<SharedPointer<Wave>>&&)(_Other.LoadedWaves);
	LoadedWaveFrontObjs = (Trie<SharedPointer<WaveFrontObj>>&&)(_Other.LoadedWaveFrontObjs);
	LoadedGLSLs = (Trie<SharedPointer<FileContent>>&&)(_Other.LoadedGLSLs);
	LoadedJsons = (Trie<SharedPointer<Json>>&&)(_Other.LoadedJsons);
	LoadedResourceBitMaps = (Trie<SharedPointer<BitMap>>&&)(_Other.LoadedResourceBitMaps);
	LoadedResourceHdrs = (Trie<SharedPointer<Hdr>>&&)(_Other.LoadedResourceHdrs);
	LoadedResourceWaves = (Trie<SharedPointer<Wave>>&&)(_Other.LoadedResourceWaves);
	LoadedResourceWaveFrontObjs = (Trie<SharedPointer<WaveFrontObj>>&&)(_Other.LoadedResourceWaveFrontObjs);
	LoadedResourceGLSLs = (Trie<SharedPointer<FileContent>>&&)(_Other.LoadedResourceGLSLs);
	LoadedResourceJsons = (Trie<SharedPointer<Json>>&&)(_Other.LoadedResourceJsons);
	CachedBitMapNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedBitMapNames);
	CachedHdrNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedHdrNames);
	CachedWaveNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedWaveNames);
	CachedWaveFrontObjNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedWaveFrontObjNames);
	CachedGLSLNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedGLSLNames);
	CachedJsonNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedJsonNames);
	CachedBitMaps = (Trie<WeakPointer<BitMap>>&&)(_Other.CachedBitMaps);
	CachedHdrs = (Trie<WeakPointer<Hdr>>&&)(_Other.CachedHdrs);
	CachedWaves = (Trie<WeakPointer<Wave>>&&)(_Other.CachedWaves);
	CachedWaveFrontObjs = (Trie<WeakPointer<WaveFrontObj>>&&)(_Other.CachedWaveFrontObjs);
	CachedGLSLs = (Trie<WeakPointer<FileContent>>&&)(_Other.CachedGLSLs);
	CachedJsons = (Trie<WeakPointer<Json>>&&)(_Other.CachedJsons);
	LastWriteBitMaps = (Trie<uint64_t>&&)(_Other.LastWriteBitMaps);
	LastWriteHdrs = (Trie<uint64_t>&&)(_Other.LastWriteHdrs);
	LastWriteWaves = (Trie<uint64_t>&&)(_Other.LastWriteWaves);
	LastWriteWaveFrontObjs = (Trie<uint64_t>&&)(_Other.LastWriteWaveFrontObjs);
	LastWriteGLSLs = (Trie<uint64_t>&&)(_Other.LastWriteGLSLs);
	LastWriteJsons = (Trie<uint64_t>&&)(_Other.LastWriteJsons);
	CachedResourceBitMapNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceBitMapNames);
	CachedResourceHdrNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceHdrNames);
	CachedResourceWaveNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceWaveNames);
	CachedResourceWaveFrontObjNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceWaveFrontObjNames);
	CachedResourceGLSLNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceGLSLNames);
	CachedResourceJsonNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedResourceJsonNames);
	CachedResourceBitMaps = (Trie<WeakPointer<BitMap>>&&)(_Other.CachedResourceBitMaps);
	CachedResourceHdrs = (Trie<WeakPointer<Hdr>>&&)(_Other.CachedResourceHdrs);
	CachedResourceWaves = (Trie<WeakPointer<Wave>>&&)(_Other.CachedResourceWaves);
	CachedResourceWaveFrontObjs = (Trie<WeakPointer<WaveFrontObj>>&&)(_Other.CachedResourceWaveFrontObjs);
	CachedResourceGLSLs = (Trie<WeakPointer<FileContent>>&&)(_Other.CachedResourceGLSLs);
	CachedResourceJsons = (Trie<WeakPointer<Json>>&&)(_Other.CachedResourceJsons);

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

	QueuedBitMaps = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedBitMaps);
	QueuedHdrs = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedHdrs);
	QueuedWaves = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedWaves);
	QueuedWaveFrontObjs = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedWaveFrontObjs);
	QueuedGLSLs = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedGLSLs);
	QueuedJsons = (Vector<BFW_STRING_TYPE>&&)(_Other.QueuedJsons);
	LoadedBitMaps = (Trie<SharedPointer<BitMap>>&&)(_Other.LoadedBitMaps);
	LoadedHdrs = (Trie<SharedPointer<Hdr>>&&)(_Other.LoadedHdrs);
	LoadedWaves = (Trie<SharedPointer<Wave>>&&)(_Other.LoadedWaves);
	LoadedWaveFrontObjs = (Trie<SharedPointer<WaveFrontObj>>&&)(_Other.LoadedWaveFrontObjs);
	LoadedGLSLs = (Trie<SharedPointer<FileContent>>&&)(_Other.LoadedGLSLs);
	LoadedJsons = (Trie<SharedPointer<Json>>&&)(_Other.LoadedJsons);
	CachedBitMapNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedBitMapNames);
	CachedHdrNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedHdrNames);
	CachedWaveNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedWaveNames);
	CachedWaveFrontObjNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedWaveFrontObjNames);
	CachedGLSLNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedGLSLNames);
	CachedJsonNames = (Vector<BFW_STRING_TYPE>&&)(_Other.CachedJsonNames);
	CachedBitMaps = (Trie<WeakPointer<BitMap>>&&)(_Other.CachedBitMaps);
	CachedHdrs = (Trie<WeakPointer<Hdr>>&&)(_Other.CachedHdrs);
	CachedWaves = (Trie<WeakPointer<Wave>>&&)(_Other.CachedWaves);
	CachedWaveFrontObjs = (Trie<WeakPointer<WaveFrontObj>>&&)(_Other.CachedWaveFrontObjs);
	CachedGLSLs = (Trie<WeakPointer<FileContent>>&&)(_Other.CachedGLSLs);
	CachedJsons = (Trie<WeakPointer<Json>>&&)(_Other.CachedJsons);
	LastWriteBitMaps = (Trie<uint64_t>&&)(_Other.LastWriteBitMaps);
	LastWriteHdrs = (Trie<uint64_t>&&)(_Other.LastWriteHdrs);
	LastWriteWaves = (Trie<uint64_t>&&)(_Other.LastWriteWaves);
	LastWriteWaveFrontObjs = (Trie<uint64_t>&&)(_Other.LastWriteWaveFrontObjs);
	LastWriteGLSLs = (Trie<uint64_t>&&)(_Other.LastWriteGLSLs);
	LastWriteJsons = (Trie<uint64_t>&&)(_Other.LastWriteJsons);

	return *this;
}

#endif

void BFW::Assets::Manager::RefreshCache()
{
	for (size_t _Index = 0; _Index < CachedBitMapNames.GetSize(); _Index++)
	{
		WeakPointer<BitMap>* _CachedWeak = CachedBitMaps.GetData(CachedBitMapNames[_Index].c_str());

		if (!_CachedWeak)
		{
			LastWriteBitMaps.Erase(CachedBitMapNames[_Index].c_str());
			CachedBitMapNames.Erase(_Index);
			_Index--;
			continue;
		}

		SharedPointer<BitMap> _CachedShared = _CachedWeak->Lock();

		if ((BitMap*)(_CachedShared) == nullptr)
		{
			CachedBitMaps.Erase(CachedBitMapNames[_Index].c_str());
			LastWriteBitMaps.Erase(CachedBitMapNames[_Index].c_str());
			CachedBitMapNames.Erase(_Index);
			_Index--;
			continue;
		}
	}

	for (size_t _Index = 0; _Index < CachedHdrNames.GetSize(); _Index++)
	{
		WeakPointer<Hdr>* _CachedWeak = CachedHdrs.GetData(CachedHdrNames[_Index].c_str());

		if (!_CachedWeak)
		{
			LastWriteHdrs.Erase(CachedHdrNames[_Index].c_str());
			CachedHdrNames.Erase(_Index);
			_Index--;
			continue;
		}

		SharedPointer<Hdr> _CachedShared = _CachedWeak->Lock();

		if ((Hdr*)(_CachedShared) == nullptr)
		{
			CachedHdrs.Erase(CachedHdrNames[_Index].c_str());
			LastWriteHdrs.Erase(CachedHdrNames[_Index].c_str());
			CachedHdrNames.Erase(_Index);
			_Index--;
			continue;
		}
	}

	for (size_t _Index = 0; _Index < CachedWaveNames.GetSize(); _Index++)
	{
		WeakPointer<Wave>* _CachedWeak = CachedWaves.GetData(CachedWaveNames[_Index].c_str());

		if (!_CachedWeak)
		{
			LastWriteWaves.Erase(CachedWaveNames[_Index].c_str());
			CachedWaveNames.Erase(_Index);
			_Index--;
			continue;
		}

		SharedPointer<Wave> _CachedShared = _CachedWeak->Lock();

		if ((Wave*)(_CachedShared) == nullptr)
		{
			CachedWaves.Erase(CachedWaveNames[_Index].c_str());
			LastWriteWaves.Erase(CachedWaveNames[_Index].c_str());
			CachedWaveNames.Erase(_Index);
			_Index--;
			continue;
		}
	}

	for (size_t _Index = 0; _Index < CachedWaveFrontObjNames.GetSize(); _Index++)
	{
		WeakPointer<WaveFrontObj>* _CachedWeak = CachedWaveFrontObjs.GetData(CachedWaveFrontObjNames[_Index].c_str());

		if (!_CachedWeak)
		{
			LastWriteWaveFrontObjs.Erase(CachedWaveFrontObjNames[_Index].c_str());
			CachedWaveFrontObjNames.Erase(_Index);
			_Index--;
			continue;
		}

		SharedPointer<WaveFrontObj> _CachedShared = _CachedWeak->Lock();

		if ((WaveFrontObj*)(_CachedShared) == nullptr)
		{
			CachedWaveFrontObjs.Erase(CachedWaveFrontObjNames[_Index].c_str());
			LastWriteWaveFrontObjs.Erase(CachedWaveFrontObjNames[_Index].c_str());
			CachedWaveFrontObjNames.Erase(_Index);
			_Index--;
			continue;
		}
	}

	for (size_t _Index = 0; _Index < CachedGLSLNames.GetSize(); _Index++)
	{
		WeakPointer<FileContent>* _CachedWeak = CachedGLSLs.GetData(CachedGLSLNames[_Index].c_str());

		if (!_CachedWeak)
		{
			LastWriteGLSLs.Erase(CachedGLSLNames[_Index].c_str());
			CachedGLSLNames.Erase(_Index);
			_Index--;
			continue;
		}

		SharedPointer<FileContent> _CachedShared = _CachedWeak->Lock();

		if ((FileContent*)(_CachedShared) == nullptr)
		{
			CachedGLSLs.Erase(CachedGLSLNames[_Index].c_str());
			LastWriteGLSLs.Erase(CachedGLSLNames[_Index].c_str());
			CachedGLSLNames.Erase(_Index);
			_Index--;
			continue;
		}
	}

	for (size_t _Index = 0; _Index < CachedJsonNames.GetSize(); _Index++)
	{
		WeakPointer<Json>* _CachedWeak = CachedJsons.GetData(CachedJsonNames[_Index].c_str());

		if (!_CachedWeak)
		{
			LastWriteJsons.Erase(CachedJsonNames[_Index].c_str());
			CachedJsonNames.Erase(_Index);
			_Index--;
			continue;
		}

		SharedPointer<Json> _CachedShared = _CachedWeak->Lock();

		if ((Json*)(_CachedShared) == nullptr)
		{
			CachedJsons.Erase(CachedJsonNames[_Index].c_str());
			LastWriteJsons.Erase(CachedJsonNames[_Index].c_str());
			CachedJsonNames.Erase(_Index);
			_Index--;
			continue;
		}
	}

#ifdef BFW_WINDOWS_PLATFORM

	for (size_t _Index = 0; _Index < CachedResourceBitMapNames.GetSize(); _Index++)
	{
		WeakPointer<BitMap>* _CachedWeak = CachedResourceBitMaps.GetData(CachedResourceBitMapNames[_Index].c_str());

		if (!_CachedWeak)
		{
			CachedResourceBitMapNames.Erase(_Index);
			_Index--;
			continue;
		}

		SharedPointer<BitMap> _CachedShared = _CachedWeak->Lock();

		if ((BitMap*)(_CachedShared) == nullptr)
		{
			CachedResourceBitMaps.Erase(CachedResourceBitMapNames[_Index].c_str());
			CachedResourceBitMapNames.Erase(_Index);
			_Index--;
			continue;
		}
	}

	for (size_t _Index = 0; _Index < CachedResourceHdrNames.GetSize(); _Index++)
	{
		WeakPointer<Hdr>* _CachedWeak = CachedResourceHdrs.GetData(CachedResourceHdrNames[_Index].c_str());

		if (!_CachedWeak)
		{
			CachedResourceHdrNames.Erase(_Index);
			_Index--;
			continue;
		}

		SharedPointer<Hdr> _CachedShared = _CachedWeak->Lock();

		if ((Hdr*)(_CachedShared) == nullptr)
		{
			CachedResourceHdrs.Erase(CachedResourceHdrNames[_Index].c_str());
			CachedResourceHdrNames.Erase(_Index);
			_Index--;
			continue;
		}
	}

	for (size_t _Index = 0; _Index < CachedResourceWaveNames.GetSize(); _Index++)
	{
		WeakPointer<Wave>* _CachedWeak = CachedResourceWaves.GetData(CachedResourceWaveNames[_Index].c_str());

		if (!_CachedWeak)
		{
			CachedResourceWaveNames.Erase(_Index);
			_Index--;
			continue;
		}

		SharedPointer<Wave> _CachedShared = _CachedWeak->Lock();

		if ((Wave*)(_CachedShared) == nullptr)
		{
			CachedResourceWaves.Erase(CachedResourceWaveNames[_Index].c_str());
			CachedResourceWaveNames.Erase(_Index);
			_Index--;
			continue;
		}
	}

	for (size_t _Index = 0; _Index < CachedResourceWaveFrontObjNames.GetSize(); _Index++)
	{
		WeakPointer<WaveFrontObj>* _CachedWeak = CachedResourceWaveFrontObjs.GetData(CachedResourceWaveFrontObjNames[_Index].c_str());

		if (!_CachedWeak)
		{
			CachedResourceWaveFrontObjNames.Erase(_Index);
			_Index--;
			continue;
		}

		SharedPointer<WaveFrontObj> _CachedShared = _CachedWeak->Lock();

		if ((WaveFrontObj*)(_CachedShared) == nullptr)
		{
			CachedResourceWaveFrontObjs.Erase(CachedResourceWaveFrontObjNames[_Index].c_str());
			CachedResourceWaveFrontObjNames.Erase(_Index);
			_Index--;
			continue;
		}
	}

	for (size_t _Index = 0; _Index < CachedResourceGLSLNames.GetSize(); _Index++)
	{
		WeakPointer<FileContent>* _CachedWeak = CachedResourceGLSLs.GetData(CachedResourceGLSLNames[_Index].c_str());

		if (!_CachedWeak)
		{
			CachedResourceGLSLNames.Erase(_Index);
			_Index--;
			continue;
		}

		SharedPointer<FileContent> _CachedShared = _CachedWeak->Lock();

		if ((FileContent*)(_CachedShared) == nullptr)
		{
			CachedResourceGLSLs.Erase(CachedResourceGLSLNames[_Index].c_str());
			CachedResourceGLSLNames.Erase(_Index);
			_Index--;
			continue;
		}
	}

	for (size_t _Index = 0; _Index < CachedResourceJsonNames.GetSize(); _Index++)
	{
		WeakPointer<Json>* _CachedWeak = CachedResourceJsons.GetData(CachedResourceJsonNames[_Index].c_str());

		if (!_CachedWeak)
		{
			CachedResourceJsonNames.Erase(_Index);
			_Index--;
			continue;
		}

		SharedPointer<Json> _CachedShared = _CachedWeak->Lock();

		if ((Json*)(_CachedShared) == nullptr)
		{
			CachedResourceJsons.Erase(CachedResourceJsonNames[_Index].c_str());
			CachedResourceJsonNames.Erase(_Index);
			_Index--;
			continue;
		}
	}

#endif
}
