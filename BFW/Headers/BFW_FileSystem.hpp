#ifndef BFW_FileSystem_hpp

#define BFW_FileSystem_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace FileSystem
	{

		class BFW_API FileContent
		{

		public:

			FileContent();
			FileContent(const FileContent& _Other);
			FileContent(FileContent&& _Other) noexcept;
			~FileContent();

			const bool Create(const size_t _Length);

			const bool Load(std::ifstream& _File);
			const bool Load(std::fstream& _File);

#ifdef BFW_WINDOWS_PLATFORM

			const bool Load(const size_t _ResourceType, const size_t _ResourceId);

#endif

			void Destroy();

			const bool Save(std::ofstream& _File) const;
			const bool Save(std::fstream& _File) const;

			const size_t Hash() const;

			uint8_t* GetData();
			const uint8_t* GetData() const;
			const size_t GetLength() const;

			explicit operator uint8_t* ();
			explicit operator const uint8_t* () const;

			uint8_t& operator* ();
			const uint8_t& operator* () const;

			uint8_t& operator[] (const size_t _Index);
			const uint8_t& operator[] (const size_t _Index) const;

			FileContent& operator= (const FileContent& _Other);
			FileContent& operator= (FileContent&& _Other) noexcept;

		private:

			uint8_t* Data;
			size_t Length;

		};

		class BFW_API File
		{

		public:

			BFW_STRING_TYPE Path;
			FileContent Content;
			time_t LastWrite;

			File();
			File(const File& _Other);
			File(File&& _Other) noexcept;
			~File();

			const BFW_STRING_TYPE GetParentPath() const;
			const BFW_STRING_TYPE GetName() const;
			const BFW_STRING_TYPE GetExtension() const;

			File& operator= (const File& _Other);
			File& operator= (File&& _Other) noexcept;

			static const File Load(const BFW_STRING_TYPE& _Path, const bool _LoadContent = false);

		};

		class BFW_API Directory
		{

		public:

			BFW_STRING_TYPE Path;
			Vector<File> Files;
			Vector<Directory> SubDirectories;

			Directory();
			Directory(const Directory& _Other);
			Directory(Directory&& _Other) noexcept;
			~Directory();

			const BFW_STRING_TYPE GetParentPath() const;

			const bool FileExists(const BFW_STRING_TYPE& _Path) const;
			const bool DirectoryExists(const BFW_STRING_TYPE& _Path) const;

			File& GetFile(const BFW_STRING_TYPE& _Path);
			const File& GetFile(const BFW_STRING_TYPE& _Path) const;
			Directory& GetDirectory(const BFW_STRING_TYPE& _Path);
			const Directory& GetDirectory(const BFW_STRING_TYPE& _Path) const;

			Directory& operator= (const Directory& _Other);
			Directory& operator= (Directory&& _Other) noexcept;

			static const Directory Load(const BFW_STRING_TYPE& _Path, const bool _LoadContent = false);

		};

		class BFW_API DirectoryDiff
		{

		public:

			Vector<Directory> AddedDirectories;
			Vector<Directory> DeletedDirectories;
			Vector<File> AddedFiles;
			Vector<File> DeletedFiles;
			Vector<File> ModifiedFiles;

			DirectoryDiff();
			DirectoryDiff(const DirectoryDiff& _Other);
			DirectoryDiff(DirectoryDiff&& _Other) noexcept;
			~DirectoryDiff();

			const Directory Apply(const Directory& _Old, const bool _LoadContent = false);

			const bool Empty() const;

			const DirectoryDiff operator+ (const DirectoryDiff& _Other) const;
			DirectoryDiff& operator+= (const DirectoryDiff& _Other);

			const DirectoryDiff operator+ (const Directory& _Directory) const;
			DirectoryDiff& operator+= (const Directory& _Directory);

			const DirectoryDiff operator- (const Directory& _Directory) const;
			DirectoryDiff& operator-= (const Directory& _Directory);

			DirectoryDiff& operator= (const DirectoryDiff& _Other);
			DirectoryDiff& operator= (DirectoryDiff&& _Other) noexcept;

			static const DirectoryDiff Get(const Directory& _Old, const Directory& _New);

		};

#ifdef BFW_WINDOWS_PLATFORM

		extern const LockedDirectoryHandle NullLockedDirectoryHandle;

#endif

		const BFW_STRING_TYPE BFW_API GetWorkingDirectory();

#ifdef BFW_WINDOWS_PLATFORM

		const LockedDirectoryHandle BFW_API LockDirectory(const BFW_STRING_TYPE& _Path);
		void BFW_API ReleaseLockedDirectory(LockedDirectoryHandle& _LockedDirectoryHandle);

#endif

	}

}



#endif
