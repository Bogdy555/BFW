#include "../Headers/BFW.hpp"



#ifdef BFW_WINDOWS_PLATFORM

const BFW::FileSystem::LockedDirectoryHandle BFW::FileSystem::NullLockedDirectoryHandle = (LockedDirectoryHandle)(-1);

#endif



BFW::FileSystem::FileContent::FileContent() : Data(nullptr), Length(0)
{

}

BFW::FileSystem::FileContent::FileContent(const FileContent& _Other) : Data(nullptr), Length(0)
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

BFW::FileSystem::FileContent::FileContent(FileContent&& _Other) noexcept : Data(_Other.Data), Length(_Other.Length)
{
	_Other.Data = nullptr;
	_Other.Length = 0;
}

BFW::FileSystem::FileContent::~FileContent()
{
	delete[] Data;
}

const bool BFW::FileSystem::FileContent::Create(const size_t _Length)
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

const bool BFW::FileSystem::FileContent::Load(std::ifstream& _File)
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

	_File.read((char*)(_Data), _Length - 1);

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

const bool BFW::FileSystem::FileContent::Load(std::fstream& _File)
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

	_File.read((char*)(_Data), _Length - 1);

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

const bool BFW::FileSystem::FileContent::Load(const size_t _ResourceType, const size_t _ResourceId)
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

void BFW::FileSystem::FileContent::Destroy()
{
	delete[] Data;
	Data = nullptr;
	Length = 0;
}

const bool BFW::FileSystem::FileContent::Save(std::ofstream& _File) const
{
	if (!Data || Length <= 1 || !_File.is_open())
	{
		return false;
	}

	_File.write((const char*)(Data), Length - 1);

	if (!_File)
	{
		return false;
	}

	return true;
}

const bool BFW::FileSystem::FileContent::Save(std::fstream& _File) const
{
	if (!Data || Length <= 1 || !_File.is_open())
	{
		return false;
	}

	_File.write((const char*)(Data), Length - 1);

	if (!_File)
	{
		return false;
	}

	return true;
}

const uint64_t BFW::FileSystem::FileContent::Hash() const
{
	return BFW::Cryptography::HashA((const BFW_CHAR_TYPE_A*)(Data), Length);
}

uint8_t* BFW::FileSystem::FileContent::GetData()
{
	return Data;
}

const uint8_t* BFW::FileSystem::FileContent::GetData() const
{
	return Data;
}

const size_t BFW::FileSystem::FileContent::GetLength() const
{
	return Length;
}

BFW::FileSystem::FileContent::operator uint8_t* ()
{
	return Data;
}

BFW::FileSystem::FileContent::operator const uint8_t* () const
{
	return Data;
}

uint8_t& BFW::FileSystem::FileContent::operator* ()
{
	return *Data;
}

const uint8_t& BFW::FileSystem::FileContent::operator* () const
{
	return *Data;
}

uint8_t& BFW::FileSystem::FileContent::operator[] (const size_t _Index)
{
	return Data[_Index];
}

const uint8_t& BFW::FileSystem::FileContent::operator[] (const size_t _Index) const
{
	return Data[_Index];
}

BFW::FileSystem::FileContent& BFW::FileSystem::FileContent::operator= (const FileContent& _Other)
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

BFW::FileSystem::FileContent& BFW::FileSystem::FileContent::operator= (FileContent&& _Other) noexcept
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



BFW::FileSystem::File::File() : Path(), Content(), LastWrite(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()))
{

}

BFW::FileSystem::File::File(const File& _Other) : Path(_Other.Path), Content(_Other.Content), LastWrite(_Other.LastWrite)
{

}

BFW::FileSystem::File::File(File&& _Other) noexcept : Path((BFW_STRING_TYPE&&)(_Other.Path)), Content((FileContent&&)(_Other.Content)), LastWrite(_Other.LastWrite)
{
	_Other.LastWrite = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

BFW::FileSystem::File::~File()
{

}

const BFW_STRING_TYPE BFW::FileSystem::File::GetParentPath() const
{
	size_t _Index = 0;

	while (_Index < Path.size())
	{
		if (Path[Path.size() - 1 - _Index] == '/')
		{
			break;
		}

		_Index++;
	}

	if (_Index == Path.size())
	{
		return BFW_STRING_TYPE();
	}

	return Path.substr(0, Path.size() - 1 - _Index);
}

const BFW_STRING_TYPE BFW::FileSystem::File::GetName() const
{
	BFW_STRING_TYPE _Parent = GetParentPath();

	return Path.substr(_Parent.size() + 1, Path.size());
}

const BFW_STRING_TYPE BFW::FileSystem::File::GetExtension() const
{
	BFW_STRING_TYPE _Name = GetName();

	size_t _Index = 0;

	while (_Index < _Name.size())
	{
		if (_Name[_Name.size() - 1 - _Index] == '.')
		{
			break;
		}

		_Index++;
	}

	if (_Index == _Name.size())
	{
		return BFW_STRING_TYPE();
	}

	return _Name.substr(_Name.size() - 1 - _Index, _Name.size());
}

BFW::FileSystem::File& BFW::FileSystem::File::operator= (const File& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Path = _Other.Path;
	Content = _Other.Content;
	LastWrite = _Other.LastWrite;

	return *this;
}

BFW::FileSystem::File& BFW::FileSystem::File::operator= (File&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Path = (BFW_STRING_TYPE&&)(_Other.Path);
	Content = (FileContent&&)(_Other.Content);
	LastWrite = _Other.LastWrite;

	_Other.LastWrite = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	return *this;
}

const BFW::FileSystem::File BFW::FileSystem::File::Load(const BFW_STRING_TYPE& _Path, const bool _LoadContent)
{
	File _Result;

	try
	{
		std::filesystem::directory_entry _Entry;

		if (_Path[0] == '.' && (_Path[1] == '/' || _Path[1] == '\\'))
		{
			_Entry = std::filesystem::directory_entry(GetWorkingDirectory() + _Path.substr(2, _Path.size()));
		}
		else
		{
			_Entry = std::filesystem::directory_entry(_Path);
		}

		if (_Entry.is_directory() && !_Entry.is_symlink())
		{
			throw nullptr;
		}

		if (_LoadContent)
		{
			std::ifstream _FileStream(_Entry.path().BFW_STRING_METHOD(), std::ios::binary);

			if (!_FileStream.is_open())
			{
				throw std::filesystem::filesystem_error("Load failed!", std::make_error_code(std::errc::no_such_file_or_directory));
			}

			if (!_Result.Content.Load(_FileStream))
			{
				throw std::filesystem::filesystem_error("Load failed!", std::make_error_code(std::errc::no_such_file_or_directory));
			}
		}

		_Result.Path = _Path;

		for (size_t _Index = 0; _Index < _Result.Path.size(); _Index++)
		{
			if (_Result.Path[_Index] == BFW_STRING_PREFIX('\\'))
			{
				_Result.Path[_Index] = BFW_STRING_PREFIX('/');
			}
		}

		BFW_WINDOWS_PLATFORM_CALL(_Result.LastWrite = std::chrono::system_clock::to_time_t(std::chrono::clock_cast<std::chrono::system_clock>(_Entry.last_write_time())));
		BFW_LINUX_PLATFORM_CALL(_Result.LastWrite = std::chrono::system_clock::to_time_t(std::chrono::file_clock::to_sys(_Entry.last_write_time())));
		BFW_ESP32_PLATFORM_CALL(_Result.LastWrite = std::chrono::system_clock::to_time_t(std::chrono::clock_cast<std::chrono::system_clock>(_Entry.last_write_time())));
	}
	catch (const std::filesystem::filesystem_error&)
	{
		_Result = File();
	}
	catch (...)
	{
		throw nullptr;
	}

	return _Result;
}



BFW::FileSystem::Directory::Directory() : Path(), Files(), SubDirectories()
{

}

BFW::FileSystem::Directory::Directory(const Directory& _Other) : Path(_Other.Path), Files(_Other.Files), SubDirectories(_Other.SubDirectories)
{

}

BFW::FileSystem::Directory::Directory(Directory&& _Other) noexcept : Path((BFW_STRING_TYPE&&)(_Other.Path)), Files((Vector<File>&&)(_Other.Files)), SubDirectories((Vector<Directory>&&)(_Other.SubDirectories))
{

}

BFW::FileSystem::Directory::~Directory()
{

}

const BFW_STRING_TYPE BFW::FileSystem::Directory::GetParentPath() const
{
	size_t _Index = 0;

	while (_Index < Path.size())
	{
		if (Path[Path.size() - 1 - _Index] == '/')
		{
			break;
		}

		_Index++;
	}

	if (_Index == Path.size())
	{
		return BFW_STRING_TYPE();
	}

	return Path.substr(0, Path.size() - 1 - _Index);
}

const bool BFW::FileSystem::Directory::FileExists(const BFW_STRING_TYPE& _Path) const
{
	if (Path != _Path.substr(0, Path.size()))
	{
		return false;
	}

	for (size_t _Index = 0; _Index < Files.GetSize(); _Index++)
	{
		if (Files[_Index].Path == _Path)
		{
			return true;
		}
	}

	for (size_t _Index = 0; _Index < SubDirectories.GetSize(); _Index++)
	{
		if (SubDirectories[_Index].FileExists(_Path))
		{
			return true;
		}
	}

	return false;
}

const bool BFW::FileSystem::Directory::DirectoryExists(const BFW_STRING_TYPE& _Path) const
{
	if (Path == _Path)
	{
		return true;
	}

	if (Path != _Path.substr(0, Path.size()))
	{
		return false;
	}

	for (size_t _Index = 0; _Index < SubDirectories.GetSize(); _Index++)
	{
		if (SubDirectories[_Index].DirectoryExists(_Path))
		{
			return true;
		}
	}

	return false;
}

BFW::FileSystem::File& BFW::FileSystem::Directory::GetFile(const BFW_STRING_TYPE& _Path)
{
	if (Path != _Path.substr(0, Path.size()))
	{
		throw nullptr;
	}

	for (size_t _Index = 0; _Index < Files.GetSize(); _Index++)
	{
		if (Files[_Index].Path == _Path)
		{
			return Files[_Index];
		}
	}

	for (size_t _Index = 0; _Index < SubDirectories.GetSize(); _Index++)
	{
		try
		{
			return SubDirectories[_Index].GetFile(_Path);
		}
		catch (...)
		{

		}
	}

	throw nullptr;
}

const BFW::FileSystem::File& BFW::FileSystem::Directory::GetFile(const BFW_STRING_TYPE& _Path) const
{
	if (Path != _Path.substr(0, Path.size()))
	{
		throw nullptr;
	}

	for (size_t _Index = 0; _Index < Files.GetSize(); _Index++)
	{
		if (Files[_Index].Path == _Path)
		{
			return Files[_Index];
		}
	}

	for (size_t _Index = 0; _Index < SubDirectories.GetSize(); _Index++)
	{
		try
		{
			return SubDirectories[_Index].GetFile(_Path);
		}
		catch (...)
		{

		}
	}

	throw nullptr;
}

BFW::FileSystem::Directory& BFW::FileSystem::Directory::GetDirectory(const BFW_STRING_TYPE& _Path)
{
	if (Path == _Path)
	{
		return *this;
	}

	if (Path != _Path.substr(0, Path.size()))
	{
		throw nullptr;
	}

	for (size_t _Index = 0; _Index < SubDirectories.GetSize(); _Index++)
	{
		try
		{
			return SubDirectories[_Index].GetDirectory(_Path);
		}
		catch (...)
		{

		}
	}

	throw nullptr;
}

const BFW::FileSystem::Directory& BFW::FileSystem::Directory::GetDirectory(const BFW_STRING_TYPE& _Path) const
{
	if (Path == _Path)
	{
		return *this;
	}

	if (Path != _Path.substr(0, Path.size()))
	{
		throw nullptr;
	}

	for (size_t _Index = 0; _Index < SubDirectories.GetSize(); _Index++)
	{
		try
		{
			return SubDirectories[_Index].GetDirectory(_Path);
		}
		catch (...)
		{

		}
	}

	throw nullptr;
}

BFW::FileSystem::Directory& BFW::FileSystem::Directory::operator= (const Directory& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Path = _Other.Path;
	Files = _Other.Files;
	SubDirectories = _Other.SubDirectories;

	return *this;
}

BFW::FileSystem::Directory& BFW::FileSystem::Directory::operator= (Directory&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Path = (BFW_STRING_TYPE&&)(_Other.Path);
	Files = (Vector<File>&&)(_Other.Files);
	SubDirectories = (Vector<Directory>&&)(_Other.SubDirectories);

	return *this;
}

const BFW::FileSystem::Directory BFW::FileSystem::Directory::Load(const BFW_STRING_TYPE& _Path, const bool _LoadContent)
{
	Directory _Result;

	try
	{
		for (const std::filesystem::directory_entry& _Entry : std::filesystem::directory_iterator(_Path))
		{
			if (_Entry.is_directory() && !_Entry.is_symlink())
			{
				Directory _TempDir = Load(_Entry.path().BFW_STRING_METHOD(), _LoadContent);

				if (!_TempDir.Path.size())
				{
					continue;
				}

				_Result.SubDirectories.EmplaceBack((Directory&&)(_TempDir));
			}
			else if (_LoadContent)
			{
				std::ifstream _FileStream(_Entry.path().BFW_STRING_METHOD(), std::ios::binary);

				if (!_FileStream.is_open())
				{
					continue;
				}

				File _File;

				if (!_File.Content.Load(_FileStream))
				{
					continue;
				}

				_File.Path = _Entry.path().BFW_STRING_METHOD();

				for (size_t _Index = 0; _Index < _File.Path.size(); _Index++)
				{
					if (_File.Path[_Index] == BFW_STRING_PREFIX('\\'))
					{
						_File.Path[_Index] = BFW_STRING_PREFIX('/');
					}
				}

				BFW_WINDOWS_PLATFORM_CALL(_File.LastWrite = std::chrono::system_clock::to_time_t(std::chrono::clock_cast<std::chrono::system_clock>(_Entry.last_write_time())));
				BFW_LINUX_PLATFORM_CALL(_File.LastWrite = std::chrono::system_clock::to_time_t(std::chrono::file_clock::to_sys(_Entry.last_write_time())));
				BFW_ESP32_PLATFORM_CALL(_File.LastWrite = std::chrono::system_clock::to_time_t(std::chrono::clock_cast<std::chrono::system_clock>(_Entry.last_write_time())));

				_Result.Files.EmplaceBack((File&&)(_File));
			}
			else
			{
				File _File;

				_File.Path = _Entry.path().BFW_STRING_METHOD();

				for (size_t _Index = 0; _Index < _File.Path.size(); _Index++)
				{
					if (_File.Path[_Index] == BFW_STRING_PREFIX('\\'))
					{
						_File.Path[_Index] = BFW_STRING_PREFIX('/');
					}
				}

				BFW_WINDOWS_PLATFORM_CALL(_File.LastWrite = std::chrono::system_clock::to_time_t(std::chrono::clock_cast<std::chrono::system_clock>(_Entry.last_write_time())));
				BFW_LINUX_PLATFORM_CALL(_File.LastWrite = std::chrono::system_clock::to_time_t(std::chrono::file_clock::to_sys(_Entry.last_write_time())));
				BFW_ESP32_PLATFORM_CALL(_File.LastWrite = std::chrono::system_clock::to_time_t(std::chrono::clock_cast<std::chrono::system_clock>(_Entry.last_write_time())));

				_Result.Files.EmplaceBack((File&&)(_File));
			}
		}

		_Result.Path = _Path;

		for (size_t _Index = 0; _Index < _Result.Path.size(); _Index++)
		{
			if (_Result.Path[_Index] == BFW_STRING_PREFIX('\\'))
			{
				_Result.Path[_Index] = BFW_STRING_PREFIX('/');
			}
		}
	}
	catch (const std::filesystem::filesystem_error&)
	{
		_Result = Directory();
	}
	catch (...)
	{
		throw nullptr;
	}

	return _Result;
}



BFW::FileSystem::DirectoryDiff::DirectoryDiff() : AddedDirectories(), DeletedDirectories(), AddedFiles(), DeletedFiles(), ModifiedFiles()
{

}

BFW::FileSystem::DirectoryDiff::DirectoryDiff(const DirectoryDiff& _Other) : AddedDirectories(_Other.AddedDirectories), DeletedDirectories(_Other.DeletedDirectories), AddedFiles(_Other.AddedFiles), DeletedFiles(_Other.DeletedFiles), ModifiedFiles(_Other.ModifiedFiles)
{

}

BFW::FileSystem::DirectoryDiff::DirectoryDiff(DirectoryDiff&& _Other) noexcept : AddedDirectories((Vector<Directory>&&)(_Other.AddedDirectories)), DeletedDirectories((Vector<Directory>&&)(_Other.DeletedDirectories)), AddedFiles((Vector<File>&&)(_Other.AddedFiles)), DeletedFiles((Vector<File>&&)(_Other.DeletedFiles)), ModifiedFiles((Vector<File>&&)(_Other.ModifiedFiles))
{

}

BFW::FileSystem::DirectoryDiff::~DirectoryDiff()
{

}

const BFW::FileSystem::Directory BFW::FileSystem::DirectoryDiff::Apply(const Directory& _Old, const bool _LoadContent)
{
	Directory _Result = _Old;

	for (size_t _IndexDeletedDirectories = 0; _IndexDeletedDirectories < DeletedDirectories.GetSize(); _IndexDeletedDirectories++)
	{
		if (!_Result.DirectoryExists(DeletedDirectories[_IndexDeletedDirectories].GetParentPath()))
		{
			continue;
		}

		Directory& _Parent = _Result.GetDirectory(DeletedDirectories[_IndexDeletedDirectories].GetParentPath());

		bool _Found = false;
		size_t _Index = 0;

		while (_Index < _Parent.SubDirectories.GetSize())
		{
			if (_Parent.SubDirectories[_Index].Path == DeletedDirectories[_IndexDeletedDirectories].Path)
			{
				_Found = true;
				break;
			}

			_Index++;
		}

		if (!_Found)
		{
			continue;
		}

		_Parent.SubDirectories.Erase(_Index);
	}

	for (size_t _IndexAddedDirectories = 0; _IndexAddedDirectories < AddedDirectories.GetSize(); _IndexAddedDirectories++)
	{
		if (_Result.DirectoryExists(AddedDirectories[_IndexAddedDirectories].Path))
		{
			continue;
		}

		BFW_STRING_TYPE _Path = AddedDirectories[_IndexAddedDirectories].Path;

		while (!_Result.DirectoryExists(_Path) && _Path.size())
		{
			size_t _Index = 0;

			while (_Index < _Path.size())
			{
				if (_Path[_Path.size() - 1 - _Index] == '/')
				{
					break;
				}

				_Index++;
			}

			if (_Index == _Path.size())
			{
				_Path = BFW_STRING_TYPE();
				continue;
			}

			_Path = _Path.substr(0, _Path.size() - 1 - _Index);
		}

		if (!_Path.size())
		{
			continue;
		}

		while (_Path != AddedDirectories[_IndexAddedDirectories].Path)
		{
			size_t _NextIndex = _Path.size() + 1;

			while (_NextIndex < AddedDirectories[_IndexAddedDirectories].Path.size() && AddedDirectories[_IndexAddedDirectories].Path[_NextIndex] != '/')
			{
				_NextIndex++;
			}

			Directory _TempDir;

			_TempDir.Path = _Path + AddedDirectories[_IndexAddedDirectories].Path.substr(_Path.size(), _NextIndex - _Path.size());

			_Result.GetDirectory(_Path).SubDirectories.EmplaceBack((Directory&&)(_TempDir));

			_Path += AddedDirectories[_IndexAddedDirectories].Path.substr(_Path.size(), _NextIndex - _Path.size());
		}
	}

	for (size_t _IndexDeletedFiles = 0; _IndexDeletedFiles < DeletedFiles.GetSize(); _IndexDeletedFiles++)
	{
		if (!_Result.DirectoryExists(DeletedFiles[_IndexDeletedFiles].GetParentPath()))
		{
			continue;
		}

		Directory& _Parent = _Result.GetDirectory(DeletedFiles[_IndexDeletedFiles].GetParentPath());

		bool _Found = false;
		size_t _Index = 0;

		while (_Index < _Parent.Files.GetSize())
		{
			if (_Parent.Files[_Index].Path == DeletedFiles[_IndexDeletedFiles].Path)
			{
				_Found = true;
				break;
			}

			_Index++;
		}

		if (!_Found)
		{
			continue;
		}

		_Parent.Files.Erase(_Index);
	}

	for (size_t _IndexAddedFiles = 0; _IndexAddedFiles < AddedFiles.GetSize(); _IndexAddedFiles++)
	{
		if (_Result.FileExists(AddedFiles[_IndexAddedFiles].Path))
		{
			continue;
		}

		if (!_Result.DirectoryExists(AddedFiles[_IndexAddedFiles].GetParentPath()))
		{
			continue;
		}

		Directory& _Parent = _Result.GetDirectory(AddedFiles[_IndexAddedFiles].GetParentPath());

		File _TempFile;

		_TempFile.Path = AddedFiles[_IndexAddedFiles].Path;
		_TempFile.LastWrite = AddedFiles[_IndexAddedFiles].LastWrite;

		if (_LoadContent)
		{
			std::ifstream _Stream(_TempFile.Path);

			if (!_Stream.is_open())
			{
				continue;
			}

			if (!_TempFile.Content.Load(_Stream))
			{
				continue;
			}
		}

		_Parent.Files.EmplaceBack((File&&)(_TempFile));
	}

	for (size_t _IndexModifiedFiles = 0; _IndexModifiedFiles < ModifiedFiles.GetSize(); _IndexModifiedFiles++)
	{
		if (!_Result.FileExists(ModifiedFiles[_IndexModifiedFiles].Path))
		{
			continue;
		}

		File _TempFile;

		_TempFile.Path = ModifiedFiles[_IndexModifiedFiles].Path;
		_TempFile.LastWrite = ModifiedFiles[_IndexModifiedFiles].LastWrite;

		if (_LoadContent)
		{
			std::ifstream _Stream(_TempFile.Path);

			if (!_Stream.is_open())
			{
				continue;
			}

			if (!_TempFile.Content.Load(_Stream))
			{
				continue;
			}
		}

		_Result.GetFile(ModifiedFiles[_IndexModifiedFiles].Path) = (File&&)(_TempFile);
	}

	return _Result;
}

const bool BFW::FileSystem::DirectoryDiff::Empty() const
{
	return !AddedDirectories.GetSize() && !DeletedDirectories.GetSize() && !AddedFiles.GetSize() && !DeletedFiles.GetSize() && !ModifiedFiles.GetSize();
}

const BFW::FileSystem::DirectoryDiff BFW::FileSystem::DirectoryDiff::operator+ (const DirectoryDiff& _Other) const
{
	DirectoryDiff _Result = *this;

	for (size_t _Index = 0; _Index < _Other.AddedDirectories.GetSize(); _Index++)
	{
		_Result.AddedDirectories.PushBack(_Other.AddedDirectories[_Index]);
	}

	for (size_t _Index = 0; _Index < _Other.DeletedDirectories.GetSize(); _Index++)
	{
		_Result.DeletedDirectories.PushBack(_Other.DeletedDirectories[_Index]);
	}

	for (size_t _Index = 0; _Index < _Other.AddedFiles.GetSize(); _Index++)
	{
		_Result.AddedFiles.PushBack(_Other.AddedFiles[_Index]);
	}

	for (size_t _Index = 0; _Index < _Other.DeletedFiles.GetSize(); _Index++)
	{
		_Result.DeletedFiles.PushBack(_Other.DeletedFiles[_Index]);
	}

	for (size_t _Index = 0; _Index < _Other.ModifiedFiles.GetSize(); _Index++)
	{
		_Result.ModifiedFiles.PushBack(_Other.ModifiedFiles[_Index]);
	}

	return _Result;
}

BFW::FileSystem::DirectoryDiff& BFW::FileSystem::DirectoryDiff::operator+= (const DirectoryDiff& _Other)
{
	for (size_t _Index = 0; _Index < _Other.AddedDirectories.GetSize(); _Index++)
	{
		AddedDirectories.PushBack(_Other.AddedDirectories[_Index]);
	}

	for (size_t _Index = 0; _Index < _Other.DeletedDirectories.GetSize(); _Index++)
	{
		DeletedDirectories.PushBack(_Other.DeletedDirectories[_Index]);
	}

	for (size_t _Index = 0; _Index < _Other.AddedFiles.GetSize(); _Index++)
	{
		AddedFiles.PushBack(_Other.AddedFiles[_Index]);
	}

	for (size_t _Index = 0; _Index < _Other.DeletedFiles.GetSize(); _Index++)
	{
		DeletedFiles.PushBack(_Other.DeletedFiles[_Index]);
	}

	for (size_t _Index = 0; _Index < _Other.ModifiedFiles.GetSize(); _Index++)
	{
		ModifiedFiles.PushBack(_Other.ModifiedFiles[_Index]);
	}

	return *this;
}

const BFW::FileSystem::DirectoryDiff BFW::FileSystem::DirectoryDiff::operator+ (const Directory& _Directory) const
{
	DirectoryDiff _Result = *this;

	Directory _TempDir;

	_TempDir.Path = _Directory.Path;

	_Result.AddedDirectories.EmplaceBack((Directory&&)(_TempDir));

	for (size_t _Index = 0; _Index < _Directory.Files.GetSize(); _Index++)
	{
		File _TempFile;

		_TempFile.Path = _Directory.Files[_Index].Path;
		_TempFile.LastWrite = _Directory.Files[_Index].LastWrite;

		_Result.AddedFiles.EmplaceBack((File&&)(_TempFile));
	}

	for (size_t _Index = 0; _Index < _Directory.SubDirectories.GetSize(); _Index++)
	{
		_Result += _Directory.SubDirectories[_Index];
	}

	return _Result;
}

BFW::FileSystem::DirectoryDiff& BFW::FileSystem::DirectoryDiff::operator+= (const Directory& _Directory)
{
	Directory _TempDir;

	_TempDir.Path = _Directory.Path;

	AddedDirectories.EmplaceBack((Directory&&)(_TempDir));

	for (size_t _Index = 0; _Index < _Directory.Files.GetSize(); _Index++)
	{
		File _TempFile;

		_TempFile.Path = _Directory.Files[_Index].Path;
		_TempFile.LastWrite = _Directory.Files[_Index].LastWrite;

		AddedFiles.EmplaceBack((File&&)(_TempFile));
	}

	for (size_t _Index = 0; _Index < _Directory.SubDirectories.GetSize(); _Index++)
	{
		*this += _Directory.SubDirectories[_Index];
	}

	return *this;
}

const BFW::FileSystem::DirectoryDiff BFW::FileSystem::DirectoryDiff::operator- (const Directory& _Directory) const
{
	DirectoryDiff _Result = *this;

	Directory _TempDir;

	_TempDir.Path = _Directory.Path;

	_Result.DeletedDirectories.EmplaceBack((Directory&&)(_TempDir));

	for (size_t _Index = 0; _Index < _Directory.Files.GetSize(); _Index++)
	{
		File _TempFile;

		_TempFile.Path = _Directory.Files[_Index].Path;
		_TempFile.LastWrite = _Directory.Files[_Index].LastWrite;

		_Result.DeletedFiles.EmplaceBack((File&&)(_TempFile));
	}

	for (size_t _Index = 0; _Index < _Directory.SubDirectories.GetSize(); _Index++)
	{
		_Result -= _Directory.SubDirectories[_Index];
	}

	return _Result;
}

BFW::FileSystem::DirectoryDiff& BFW::FileSystem::DirectoryDiff::operator-= (const Directory& _Directory)
{
	Directory _TempDir;

	_TempDir.Path = _Directory.Path;

	DeletedDirectories.EmplaceBack((Directory&&)(_TempDir));

	for (size_t _Index = 0; _Index < _Directory.Files.GetSize(); _Index++)
	{
		File _TempFile;

		_TempFile.Path = _Directory.Files[_Index].Path;
		_TempFile.LastWrite = _Directory.Files[_Index].LastWrite;

		DeletedFiles.EmplaceBack((File&&)(_TempFile));
	}

	for (size_t _Index = 0; _Index < _Directory.SubDirectories.GetSize(); _Index++)
	{
		*this -= _Directory.SubDirectories[_Index];
	}

	return *this;
}

BFW::FileSystem::DirectoryDiff& BFW::FileSystem::DirectoryDiff::operator= (const DirectoryDiff& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	AddedDirectories = _Other.AddedDirectories;
	DeletedDirectories = _Other.DeletedDirectories;
	AddedFiles = _Other.AddedFiles;
	DeletedFiles = _Other.DeletedFiles;
	ModifiedFiles = _Other.ModifiedFiles;

	return *this;
}

BFW::FileSystem::DirectoryDiff& BFW::FileSystem::DirectoryDiff::operator= (DirectoryDiff&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	AddedDirectories = (Vector<Directory>&&)(_Other.AddedDirectories);
	DeletedDirectories = (Vector<Directory>&&)(_Other.DeletedDirectories);
	AddedFiles = (Vector<File>&&)(_Other.AddedFiles);
	DeletedFiles = (Vector<File>&&)(_Other.DeletedFiles);
	ModifiedFiles = (Vector<File>&&)(_Other.ModifiedFiles);

	return *this;
}

const BFW::FileSystem::DirectoryDiff BFW::FileSystem::DirectoryDiff::Get(const Directory& _Old, const Directory& _New)
{
	DirectoryDiff _Result;

	if (_Old.Path != _New.Path)
	{
		BFW_DEBUG_BREAK_MSG(BFW_STRING_PREFIX("Can't get a directory diff on different folders!"));
		throw nullptr;
	}

	for (size_t _IndexOld = 0; _IndexOld < _Old.SubDirectories.GetSize(); _IndexOld++)
	{
		bool _Found = false;
		size_t _IndexFound = 0;

		for (size_t _IndexNew = 0; _IndexNew < _New.SubDirectories.GetSize(); _IndexNew++)
		{
			if (_Old.SubDirectories[_IndexOld].Path == _New.SubDirectories[_IndexNew].Path)
			{
				_Found = true;
				_IndexFound = _IndexNew;
				break;
			}
		}

		if (_Found)
		{
			_Result += Get(_Old.SubDirectories[_IndexOld], _New.SubDirectories[_IndexFound]);
			continue;
		}

		_Result -= _Old.SubDirectories[_IndexOld];
	}

	for (size_t _IndexNew = 0; _IndexNew < _New.SubDirectories.GetSize(); _IndexNew++)
	{
		bool _Found = false;

		for (size_t _IndexOld = 0; _IndexOld < _Old.SubDirectories.GetSize(); _IndexOld++)
		{
			if (_Old.SubDirectories[_IndexOld].Path == _New.SubDirectories[_IndexNew].Path)
			{
				_Found = true;
				break;
			}
		}

		if (_Found)
		{
			continue;
		}

		_Result += _New.SubDirectories[_IndexNew];
	}

	for (size_t _IndexOld = 0; _IndexOld < _Old.Files.GetSize(); _IndexOld++)
	{
		bool _Found = false;
		size_t _IndexFound = 0;

		for (size_t _IndexNew = 0; _IndexNew < _New.Files.GetSize(); _IndexNew++)
		{
			if (_Old.Files[_IndexOld].Path == _New.Files[_IndexNew].Path)
			{
				_Found = true;
				_IndexFound = _IndexNew;
				break;
			}
		}

		if (!_Found)
		{
			File _File;

			_File.Path = _Old.Files[_IndexOld].Path;
			_File.LastWrite = _Old.Files[_IndexOld].LastWrite;

			_Result.DeletedFiles.EmplaceBack((File&&)(_File));

			continue;
		}

		if (_Old.Files[_IndexOld].LastWrite < _New.Files[_IndexFound].LastWrite)
		{
			File _File;

			_File.Path = _New.Files[_IndexFound].Path;
			_File.LastWrite = _New.Files[_IndexFound].LastWrite;

			_Result.ModifiedFiles.EmplaceBack((File&&)(_File));
		}
	}

	for (size_t _IndexNew = 0; _IndexNew < _New.Files.GetSize(); _IndexNew++)
	{
		bool _Found = false;

		for (size_t _IndexOld = 0; _IndexOld < _Old.Files.GetSize(); _IndexOld++)
		{
			if (_New.Files[_IndexNew].Path == _Old.Files[_IndexOld].Path)
			{
				_Found = true;
				break;
			}
		}

		if (_Found)
		{
			continue;
		}

		File _File;

		_File.Path = _New.Files[_IndexNew].Path;
		_File.LastWrite = _New.Files[_IndexNew].LastWrite;

		_Result.AddedFiles.EmplaceBack((File&&)(_File));
	}

	return _Result;
}



#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

const bool BFW_API BFW::FileSystem::SetWorkingDirectory(const BFW_STRING_TYPE& _Path)
{
	try
	{
		std::filesystem::current_path(_Path);
	}
	catch (const std::filesystem::filesystem_error&)
	{
		return false;
	}

	return true;
}

const BFW_STRING_TYPE BFW_API BFW::FileSystem::GetWorkingDirectory()
{
	BFW_STRING_TYPE _Result = std::filesystem::current_path().BFW_STRING_METHOD();

	for (size_t _Index = 0; _Index < _Result.size(); _Index++)
	{
		if (_Result[_Index] == '\\')
		{
			_Result[_Index] = '/';
		}
	}

	return _Result;
}

#endif

#ifdef BFW_ESP32_PLATFORM

const BFW_STRING_TYPE BFW_API BFW::FileSystem::GetWorkingDirectory(const BFW_STRING_TYPE& _SDCardPath)
{
	return _SDCardPath;
}

#endif

#ifdef BFW_WINDOWS_PLATFORM

const BFW::FileSystem::LockedDirectoryHandle BFW_API BFW::FileSystem::LockDirectory(const BFW_STRING_TYPE& _Path)
{
	return CreateFile(_Path.c_str(), DELETE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
}

void BFW_API BFW::FileSystem::ReleaseLockedDirectory(LockedDirectoryHandle& _LockedDirectoryHandle)
{
	if (_LockedDirectoryHandle == NullLockedDirectoryHandle)
	{
		return;
	}

	CloseHandle(_LockedDirectoryHandle);
	_LockedDirectoryHandle = NullLockedDirectoryHandle;
}

#endif
