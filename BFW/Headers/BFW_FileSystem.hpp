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

		struct BFW_API File
		{

			BFW_STRING_TYPE Path;
			FileContent Content;
			time_t LastWrite;

			File();
			File(const File& _Other) = default;
			File(File&& _Other) noexcept;
			~File();

			const BFW_STRING_TYPE GetParentPath() const;

			File& operator= (const File& _Other) = default;
			File& operator= (File&& _Other) noexcept;

		};

		struct BFW_API Directory
		{

			BFW_STRING_TYPE Path;
			Vector<File> Files;
			Vector<Directory> SubDirectories;

			Directory();
			Directory(const Directory& _Other) = default;
			Directory(Directory&& _Other) noexcept;
			~Directory();

			File& GetFile(const BFW_STRING_TYPE& _Path);
			const File& GetFile(const BFW_STRING_TYPE& _Path) const;
			Directory& GetDirectory(const BFW_STRING_TYPE& _Path);
			const Directory& GetDirectory(const BFW_STRING_TYPE& _Path) const;

			const BFW_STRING_TYPE GetParentPath() const;

			const bool FileExists(const BFW_STRING_TYPE& _Path) const;
			const bool DirectoryExists(const BFW_STRING_TYPE& _Path) const;

			Directory& operator= (const Directory& _Other) = default;
			Directory& operator= (Directory&& _Other) noexcept;

		};

		struct BFW_API DirectoryDiff
		{

			Vector<Directory> AddedDirectories;
			Vector<Directory> DeletedDirectories;
			Vector<File> AddedFiles;
			Vector<File> DeletedFiles;
			Vector<File> ModifiedFiles;

			DirectoryDiff();
			DirectoryDiff(const DirectoryDiff& _Other) = default;
			DirectoryDiff(DirectoryDiff&& _Other) noexcept;
			~DirectoryDiff();

			const bool Empty() const;

			const DirectoryDiff operator+ (const DirectoryDiff& _Other) const;
			DirectoryDiff& operator+= (const DirectoryDiff& _Other);

			const DirectoryDiff operator+ (const Directory& _Directory) const;
			DirectoryDiff& operator+= (const Directory& _Directory);

			const DirectoryDiff operator- (const Directory& _Directory) const;
			DirectoryDiff& operator-= (const Directory& _Directory);

			DirectoryDiff& operator= (const DirectoryDiff& _Other) = default;
			DirectoryDiff& operator= (DirectoryDiff&& _Other) noexcept;

			static const DirectoryDiff Get(const Directory& _Old, const Directory& _New);

		};

		const BFW_STRING_TYPE BFW_API GetWorkingDirectory();
		const File BFW_API LoadFile(const BFW_STRING_TYPE& _Path, const bool _LoadContent = false);
		const Directory BFW_API LoadDirectory(const BFW_STRING_TYPE& _Path, const bool _LoadContent = false);
		const Directory BFW_API ApplyDirectoryDiff(const Directory& _Old, const DirectoryDiff& _DirectoryDiff, const bool _LoadContent = false);

	}

}



#endif
