#ifndef BFW_Assets_hpp

#define BFW_Assets_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace Assets
	{

		class BFW_API BitMap
		{

		public:

			BitMap();
			BitMap(const BitMap& _Other);
			BitMap(BitMap&& _Other) noexcept;
			~BitMap();

			const bool Create(const size_t _Width, const size_t _Height, const size_t _ChannelsCount = 4);
			const bool Load(const FileSystem::FileContent& _FileContent, const bool _Flip = true);
			void Destroy();

			FileSystem::FileContent Save(const bool _Flip = true) const;

			uint8_t* GetData();
			const uint8_t* GetData() const;
			const size_t GetChannelsCount() const;
			const size_t GetWidth() const;
			const size_t GetHeight() const;

			explicit operator uint8_t* ();
			explicit operator const uint8_t* () const;

			uint8_t& operator* ();
			const uint8_t& operator* () const;

			uint8_t* operator[] (const size_t _Y);
			const uint8_t* operator* (const size_t _Y) const;

			BitMap& operator= (const BitMap& _Other);
			BitMap& operator= (BitMap&& _Other) noexcept;

		private:

			uint8_t* Data;
			size_t ChannelsCount;
			size_t Width;
			size_t Height;

		};

#pragma pack(push, 1)

		struct BFW_API WaveFormat
		{

			uint16_t FormatTag;
			uint16_t Channels;
			uint32_t SamplesPerSec;
			uint32_t AvgBytesPerSec;
			uint16_t BlockAlign;
			uint16_t BitsPerSample;

			WaveFormat();
			WaveFormat(const WaveFormat& _Other) = default;
			WaveFormat(WaveFormat&& _Other) noexcept;
			~WaveFormat();
			WaveFormat& operator= (const WaveFormat& _Other) = default;
			WaveFormat& operator= (WaveFormat&& _Other) noexcept;

		};

#pragma pack(pop)

		class BFW_API Wave
		{

		public:

			Wave();
			Wave(const Wave& _Other);
			Wave(Wave&& _Other) noexcept;
			~Wave();

			const bool Create(const WaveFormat& _Info, const size_t _Size);
			const bool Load(const FileSystem::FileContent& _FileContent);
			void Destroy();

			FileSystem::FileContent Save() const;

			const WaveFormat GetInfo() const;
			uint8_t* GetData8();
			const uint8_t* GetData8() const;
			int16_t* GetData16();
			const int16_t* GetData16() const;
			const size_t GetSize() const;

			explicit operator uint8_t* ();
			explicit operator const uint8_t* () const;

			uint8_t& operator* ();
			const uint8_t& operator* () const;

			uint8_t& operator[] (const size_t _Index);
			const uint8_t& operator[] (const size_t _Index) const;

			Wave& operator= (const Wave& _Other);
			Wave& operator= (Wave&& _Other) noexcept;

		private:

			WaveFormat Info;
			uint8_t* Data;
			size_t Size;

		};

	}

}



#endif
