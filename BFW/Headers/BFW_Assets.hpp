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

		struct BFW_API JsonObjectData
		{

			Vector<Json> Object;
			Vector<BFW_STRING_TYPE_A> Tags;

			JsonObjectData();
			JsonObjectData(const JsonObjectData& _Other) = default;
			JsonObjectData(JsonObjectData&& _Other) noexcept;
			~JsonObjectData();
			JsonObjectData& operator= (const JsonObjectData& _Other) = default;
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

	}

}



#endif
