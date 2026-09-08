#ifndef BFW_Assets_hpp

#define BFW_Assets_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace Assets
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

			const uint64_t Hash() const;

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

		class BFW_API BitMap
		{

		public:

			BitMap();
			BitMap(const BitMap& _Other);
			BitMap(BitMap&& _Other) noexcept;
			~BitMap();

			const bool Create(const size_t _Width, const size_t _Height, const size_t _ChannelsCount = 4);
			const bool Load(const FileContent& _FileContent, const bool _Flip = true);
			void Destroy();

			FileContent Save(const bool _Flip = true) const;

			uint8_t* GetData();
			const uint8_t* GetData() const;
			const size_t GetChannelsCount() const;
			const size_t GetWidth() const;
			const size_t GetHeight() const;

			explicit operator uint8_t* ();
			explicit operator const uint8_t* () const;

			uint8_t& operator* ();
			const uint8_t& operator* () const;

			uint8_t* operator[] (const size_t _PositionY);
			const uint8_t* operator* (const size_t _PositionY) const;

			BitMap& operator= (const BitMap& _Other);
			BitMap& operator= (BitMap&& _Other) noexcept;

		private:

			uint8_t* Data;
			size_t ChannelsCount;
			size_t Width;
			size_t Height;

		};

		class BFW_API Hdr
		{

		public:

			Hdr();
			Hdr(const Hdr& _Other);
			Hdr(Hdr&& _Other) noexcept;
			~Hdr();

			const bool Create(const size_t _Width, const size_t _Height, const size_t _ChannelsCount = 4);
			const bool Load(const FileContent& _FileContent, const bool _Flip = true);
			void Destroy();

			FileContent Save(const bool _Flip = true) const;

			float* GetData();
			const float* GetData() const;
			const size_t GetChannelsCount() const;
			const size_t GetWidth() const;
			const size_t GetHeight() const;

			explicit operator float* ();
			explicit operator const float* () const;

			float& operator* ();
			const float& operator* () const;

			float* operator[] (const size_t _PositionY);
			const float* operator* (const size_t _PositionY) const;

			Hdr& operator= (const Hdr& _Other);
			Hdr& operator= (Hdr&& _Other) noexcept;

		private:

			float* Data;
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
			const bool Load(const FileContent& _FileContent);
			void Destroy();

			FileContent Save() const;

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

		enum BFW_API JsonTypes : const uint8_t
		{
			_NullJsonType = 0,
			_BoolJsonType = 1,
			_NumberJsonType = 2,
			_StringJsonType = 3,
			_ArrayJsonType = 4,
			_ObjectJsonType = 5
		};

		class BFW_API JsonObjectData
		{

		public:

			Vector<Json> Object;
			Vector<BFW_STRING_TYPE_A> Tags;

			JsonObjectData();
			JsonObjectData(const JsonObjectData& _Other);
			JsonObjectData(JsonObjectData&& _Other) noexcept;
			~JsonObjectData();

			Json& operator[] (const BFW_CHAR_TYPE_A* _Tag);
			const Json& operator[] (const BFW_CHAR_TYPE_A* _Tag) const;

			JsonObjectData& operator= (const JsonObjectData& _Other);
			JsonObjectData& operator= (JsonObjectData&& _Other) noexcept;

		};

		class BFW_API Json
		{

		public:

			Json();
			Json(const Json& _Other);
			Json(Json&& _Other) noexcept;
			~Json();

			const bool Load(const FileContent& _FileContent);

			void SetNull();
			void SetBool(const bool _BoolValue);
			void SetNumber(const float _NumberValue);
			void SetString(const BFW_STRING_TYPE_A _StringValue);
			void SetArray();
			void SetObject();

			FileContent Save() const;

			const uint8_t GetType() const;
			const bool GetBool() const;
			const float GetNumber() const;
			const BFW_STRING_TYPE_A& GetString() const;
			Vector<Json>& GetArray();
			const Vector<Json>& GetArray() const;
			JsonObjectData& GetObjectData();
			const JsonObjectData& GetObjectData() const;

			Json& operator= (const Json& _Other);
			Json& operator= (Json&& _Other) noexcept;

		private:

			uint8_t Type;

			bool BoolValue;
			float NumberValue;
			BFW_STRING_TYPE_A StringValue;
			Vector<Json> ArrayValue;
			JsonObjectData ObjectDataValue;

		};

		class BFW_API Manager
		{

		public:

			Manager();
			Manager(const Manager& _Other) = delete;
			Manager(Manager&& _Other) noexcept;
			~Manager();

			void QueueBitMap(const BFW_CHAR_TYPE* _Name);
			void QueueHdr(const BFW_CHAR_TYPE* _Name);
			void QueueWave(const BFW_CHAR_TYPE* _Name);
			void QueueJson(const BFW_CHAR_TYPE* _Name);

#ifdef BFW_WINDOWS_PLATFORM

			void QueueResourceBitMap(const size_t _Id);
			void QueueResourceHdr(const size_t _Id);
			void QueueResourceWave(const size_t _Id);
			void QueueResourceJson(const size_t _Id);

#endif

			void Flush();

			void AddDynamicBitMap(const BFW_CHAR_TYPE* _Name, SharedPointer<BitMap>& _Asset);
			void AddDynamicHdr(const BFW_CHAR_TYPE* _Name, SharedPointer<Hdr>& _Asset);
			void AddDynamicWave(const BFW_CHAR_TYPE* _Name, SharedPointer<Wave>& _Asset);
			void AddDynamicJson(const BFW_CHAR_TYPE* _Name, SharedPointer<Json>& _Asset);

			void AddDynamicBitMapRef(const BFW_CHAR_TYPE* _Name, SharedPointer<BitMap>& _Asset);
			void AddDynamicHdrRef(const BFW_CHAR_TYPE* _Name, SharedPointer<Hdr>& _Asset);
			void AddDynamicWaveRef(const BFW_CHAR_TYPE* _Name, SharedPointer<Wave>& _Asset);
			void AddDynamicJsonRef(const BFW_CHAR_TYPE* _Name, SharedPointer<Json>& _Asset);

			void Update();

			void ReleaseBitMap(const BFW_CHAR_TYPE* _Name);
			void ReleaseHdr(const BFW_CHAR_TYPE* _Name);
			void ReleaseWave(const BFW_CHAR_TYPE* _Name);
			void ReleaseJson(const BFW_CHAR_TYPE* _Name);

#ifdef BFW_WINDOWS_PLATFORM

			void ReleaseResourceBitMap(const size_t _Id);
			void ReleaseResourceHdr(const size_t _Id);
			void ReleaseResourceWave(const size_t _Id);
			void ReleaseResourceJson(const size_t _Id);

#endif

			SharedPointer<BitMap> GetBitMap(const BFW_CHAR_TYPE* _Name);
			const SharedPointer<BitMap> GetBitMap(const BFW_CHAR_TYPE* _Name) const;
			SharedPointer<Hdr> GetHdr(const BFW_CHAR_TYPE* _Name);
			const SharedPointer<Hdr> GetHdr(const BFW_CHAR_TYPE* _Name) const;
			SharedPointer<Wave> GetWave(const BFW_CHAR_TYPE* _Name);
			const SharedPointer<Wave> GetWave(const BFW_CHAR_TYPE* _Name) const;
			SharedPointer<Json> GetJson(const BFW_CHAR_TYPE* _Name);
			const SharedPointer<Json> GetJson(const BFW_CHAR_TYPE* _Name) const;

#ifdef BFW_WINDOWS_PLATFORM

			SharedPointer<BitMap> GetResourceBitMap(const size_t _Id);
			const SharedPointer<BitMap> GetResourceBitMap(const size_t _Id) const;
			SharedPointer<Hdr> GetResourceHdr(const size_t _Id);
			const SharedPointer<Hdr> GetResourceHdr(const size_t _Id) const;
			SharedPointer<Wave> GetResourceWave(const size_t _Id);
			const SharedPointer<Wave> GetResourceWave(const size_t _Id) const;
			SharedPointer<Json> GetResourceJson(const size_t _Id);
			const SharedPointer<Json> GetResourceJson(const size_t _Id) const;

#endif

			Manager& operator= (const Manager& _Other) = delete;
			Manager& operator= (Manager&& _Other) noexcept;

		private:

			void RefreshCache();

			Vector<BFW_STRING_TYPE> QueuedBitMaps;
			Vector<BFW_STRING_TYPE> QueuedHdrs;
			Vector<BFW_STRING_TYPE> QueuedWaves;
			Vector<BFW_STRING_TYPE> QueuedJsons;

#ifdef BFW_WINDOWS_PLATFORM

			Vector<size_t> QueuedResourceBitMaps;
			Vector<size_t> QueuedResourceHdrs;
			Vector<size_t> QueuedResourceWaves;
			Vector<size_t> QueuedResourceJsons;

#endif

			Trie<SharedPointer<BitMap>> LoadedBitMaps;
			Trie<SharedPointer<Hdr>> LoadedHdrs;
			Trie<SharedPointer<Wave>> LoadedWaves;
			Trie<SharedPointer<Json>> LoadedJsons;

#ifdef BFW_WINDOWS_PLATFORM

			Trie<SharedPointer<BitMap>> LoadedResourceBitMaps;
			Trie<SharedPointer<Hdr>> LoadedResourceHdrs;
			Trie<SharedPointer<Wave>> LoadedResourceWaves;
			Trie<SharedPointer<Json>> LoadedResourceJsons;

#endif

			mutable Vector<BFW_STRING_TYPE> CachedBitMapNames;
			mutable Vector<BFW_STRING_TYPE> CachedHdrNames;
			mutable Vector<BFW_STRING_TYPE> CachedWaveNames;
			mutable Vector<BFW_STRING_TYPE> CachedJsonNames;

			mutable Trie<WeakPointer<BitMap>> CachedBitMaps;
			mutable Trie<WeakPointer<Hdr>> CachedHdrs;
			mutable Trie<WeakPointer<Wave>> CachedWaves;
			mutable Trie<WeakPointer<Json>> CachedJsons;

			mutable Trie<uint64_t> LastWriteBitMaps;
			mutable Trie<uint64_t> LastWriteHdrs;
			mutable Trie<uint64_t> LastWriteWaves;
			mutable Trie<uint64_t> LastWriteJsons;

#ifdef BFW_WINDOWS_PLATFORM

			mutable Vector<BFW_STRING_TYPE> CachedResourceBitMapNames;
			mutable Vector<BFW_STRING_TYPE> CachedResourceHdrNames;
			mutable Vector<BFW_STRING_TYPE> CachedResourceWaveNames;
			mutable Vector<BFW_STRING_TYPE> CachedResourceJsonNames;

			mutable Trie<WeakPointer<BitMap>> CachedResourceBitMaps;
			mutable Trie<WeakPointer<Hdr>> CachedResourceHdrs;
			mutable Trie<WeakPointer<Wave>> CachedResourceWaves;
			mutable Trie<WeakPointer<Json>> CachedResourceJsons;

#endif

		};

	}

}



#endif
