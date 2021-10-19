#ifndef BFW_Sound_hpp

#define BFW_Sound_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace Sound
	{

#ifdef BFW_WINDOWS_PLATFORM

		class BFW_API SoundBuff
		{

		public:

			SoundBuff();
			SoundBuff(const SoundBuff& _Other);
			SoundBuff(SoundBuff&& _Other) noexcept;
			~SoundBuff();

			bool Create(const unsigned long _BuffSize);
			void Destroy();

			bool LoadFromResource(const HINSTANCE _hInstance, const unsigned long _ResourceID);
			bool LoadFromFile(const wchar_t* _FilePath);
			const bool SaveToFile(const wchar_t* _FilePath) const;

			const unsigned long GetBuffSize() const;

			WAVEFORMATEX& GetAudioInfo();
			const WAVEFORMATEX& GetAudioInfo() const;

			operator unsigned char* ();
			operator const unsigned char* () const;

			void operator= (const SoundBuff& _Other);
			void operator= (SoundBuff&& _Other) noexcept;

		private:

			WAVEFORMATEX AudioInfo;
			unsigned long BuffSize;
			unsigned char* Buff;

		};

		class BFW_API ResourceInStream
		{

		public:

			ResourceInStream();
			ResourceInStream(const ResourceInStream& _Other) = delete;
			ResourceInStream(ResourceInStream&& _Other) noexcept;
			~ResourceInStream();

			const bool Started() const;

			bool Start(const HINSTANCE _hInstance, const unsigned long _ResourceID);
			bool Stream(unsigned char* _Buff, const unsigned long _BuffSize, unsigned long& _ReadSize);
			void Stop();

			const WAVEFORMATEX GetAudioInfo() const;
			const unsigned long GetBuffSize() const;
			const unsigned long GetCurrentPoint() const;

			void operator= (const ResourceInStream& _Other) = delete;
			void operator= (ResourceInStream&& _Other) noexcept;

		private:

			HGLOBAL hGlobal;
			WAVEFORMATEX AudioInfo;
			unsigned long ResourceBuffSize;
			const unsigned char* ResourceBuff;
			unsigned long CurrentPoint;

		};

		class BFW_API FileInStream
		{

		public:

			FileInStream();
			FileInStream(const FileInStream& _Other) = delete;
			FileInStream(FileInStream&& _Other) noexcept;
			~FileInStream();

			const bool Started() const;

			bool Start(const wchar_t* _FileName);
			bool Stream(unsigned char* _Buff, const unsigned long _BuffSize, unsigned long& _ReadSize);
			void Stop();

			const WAVEFORMATEX GetAudioInfo() const;
			const unsigned long GetBuffSize() const;
			const unsigned long GetCurrentPoint() const;

			void operator= (const FileInStream& _Other) = delete;
			void operator= (FileInStream&& _Other) noexcept;

		private:

			FILE* File;
			WAVEFORMATEX AudioInfo;
			unsigned long FileBuffSize;
			unsigned long CurrentPoint;

		};

		class BFW_API FileOutStream
		{

		public:

			FileOutStream();
			FileOutStream(const FileOutStream& _Other) = delete;
			FileOutStream(FileOutStream&& _Other) noexcept;
			~FileOutStream();

			const bool Started() const;

			bool Start(const wchar_t* _FileName, const WAVEFORMATEX& _AudioInfo);
			bool Stream(const unsigned char* _Buff, const unsigned long _BuffSize);
			bool Stop();

			const wchar_t* GetFileName() const;
			const WAVEFORMATEX GetAudioInfo() const;
			const unsigned long GetSavedSize() const;

			void operator= (const FileOutStream& _Other) = delete;
			void operator= (FileOutStream&& _Other) noexcept;

		private:

			FILE* File;
			wchar_t* FileName;
			WAVEFORMATEX AudioInfo;
			unsigned long SavedSize;

		};

#endif

	}

}



#endif
