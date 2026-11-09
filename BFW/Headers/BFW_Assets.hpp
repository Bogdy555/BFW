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

		struct BFW_API TriangleVertexData
		{

			Math::Vec4 Position;
			Math::Vec4 Color;
			Math::Vec3 Normal;
			Math::Vec3 Tangent;
			Math::Vec3 TextureCoords;

			TriangleVertexData();
			TriangleVertexData(const Math::Vec4& _Position, const Math::Vec4& _Color, const Math::Vec3& _Normal, const Math::Vec3& _Tangent, const Math::Vec3& _TextureCoords);
			TriangleVertexData(const TriangleVertexData& _Other) = default;
			TriangleVertexData(TriangleVertexData&& _Other) noexcept;
			TriangleVertexData& operator= (const TriangleVertexData& _Other) = default;
			TriangleVertexData& operator= (TriangleVertexData&& _Other) noexcept;

		};

		struct BFW_API TriangleIndexData
		{

			uint32_t IndexA;
			uint32_t IndexB;
			uint32_t IndexC;

			TriangleIndexData();
			TriangleIndexData(const uint32_t _IndexA, const uint32_t _IndexB, const uint32_t _IndexC);
			TriangleIndexData(const TriangleIndexData& _Other) = default;
			TriangleIndexData(TriangleIndexData&& _Other) noexcept;
			TriangleIndexData& operator= (const TriangleIndexData& _Other) = default;
			TriangleIndexData& operator= (TriangleIndexData&& _Other) noexcept;

		};

		struct BFW_API LineVertexData
		{

			Math::Vec4 Position;
			Math::Vec4 Color;
			Math::Vec3 TextureCoords;

			LineVertexData();
			LineVertexData(const Math::Vec4& _Position, const Math::Vec4& _Color, const Math::Vec3& _TextureCoords);
			LineVertexData(const LineVertexData& _Other) = default;
			LineVertexData(LineVertexData&& _Other) noexcept;
			LineVertexData& operator= (const LineVertexData& _Other) = default;
			LineVertexData& operator= (LineVertexData&& _Other) noexcept;

		};

		struct BFW_API LineIndexData
		{

			uint32_t IndexA;
			uint32_t IndexB;

			LineIndexData();
			LineIndexData(const uint32_t _IndexA, const uint32_t _IndexB);
			LineIndexData(const LineIndexData& _Other) = default;
			LineIndexData(LineIndexData&& _Other) noexcept;
			LineIndexData& operator= (const LineIndexData& _Other) = default;
			LineIndexData& operator= (LineIndexData&& _Other) noexcept;

		};

		class BFW_API Mesh
		{

		public:

			BFW_STRING_TYPE MaterialName;
			Vector<TriangleVertexData> TriangleVBO;
			Vector<TriangleIndexData> TriangleIBO;
			Vector<LineVertexData> LineVBO;
			Vector<LineIndexData> LineIBO;

			Mesh();
			Mesh(const Mesh& _Other);
			Mesh(Mesh&& _Other) noexcept;
			~Mesh();

			void GenerateUnitQuad();
			void GenerateUnitCube();

			Mesh& operator= (const Mesh& _Other);
			Mesh& operator= (Mesh&& _Other) noexcept;

		};

		class BFW_API WaveFrontObj
		{

		public:

			WaveFrontObj();
			WaveFrontObj(const WaveFrontObj& _Other);
			WaveFrontObj(WaveFrontObj&& _Other) noexcept;
			~WaveFrontObj();

			const bool Load(const FileContent& _FileContent, const BFW_CHAR_TYPE* _Path = nullptr, const BFW_CHAR_TYPE* _CurrentPath = nullptr);

			Mesh& Push(const BFW_CHAR_TYPE* _Name, const Mesh& _Data);
			Mesh& Emplace(const BFW_CHAR_TYPE* _Name, Mesh&& _Data);

			void Erase(const BFW_CHAR_TYPE* _Name);
			void Clear();

			FileContent Save(const bool _SaveColors = false, const bool _SaveNormals = true, const bool _SaveTextureCoords = true, const bool _SaveMaterials = true) const;

			const Vector<BFW_STRING_TYPE>& GetMeshNames() const;

			Mesh* GetData(const BFW_CHAR_TYPE* _Name);
			const Mesh* GetData(const BFW_CHAR_TYPE* _Name) const;

			Vector<BFW_STRING_TYPE>& GetMaterialLibs();
			const Vector<BFW_STRING_TYPE>& GetMaterialLibs() const;

			Mesh& operator[] (const BFW_CHAR_TYPE* _Name);
			const Mesh& operator[] (const BFW_CHAR_TYPE* _Name) const;

			WaveFrontObj& operator= (const WaveFrontObj& _Other);
			WaveFrontObj& operator= (WaveFrontObj&& _Other) noexcept;

		private:

			Vector<BFW_STRING_TYPE> MeshNames;
			Trie<Mesh> Meshes;
			Vector<BFW_STRING_TYPE> MaterialLibs;

		};

		class BFW_API TextureSettings
		{

		public:

			bool BlendU;
			bool BlendV;
			bool Clamp;
			BFW_CHAR_TYPE_A Channel;
			float Boost;
			float Base;
			float Gain;
			Math::Vec3 Offset;
			Math::Vec3 Scale;
			Math::Vec3 Turbulence;
			size_t Resolution;
			float BumpMultiplier;
			BFW_STRING_TYPE ReflectionType;

			TextureSettings();
			TextureSettings(const TextureSettings& _Other);
			TextureSettings(TextureSettings&& _Other) noexcept;
			~TextureSettings();

			const bool IsValid() const;

			TextureSettings& operator= (const TextureSettings& _Other);
			TextureSettings& operator= (TextureSettings&& _Other) noexcept;

		};

		class BFW_API Material
		{

		public:

			Math::Vec3 Albedo;
			Math::Vec3 SpecularColor;
			float SpecularExponent;
			Math::Vec3 EmissionColor;
			float Roughness;
			float Metalness;
			float AmbientOcclusion;
			Math::Vec3 AmbientColor;
			float Sheen;
			Math::Vec3 SheenColor;
			float ClearCoat;
			Math::Vec3 ClearCoatColor;
			float ClearCoatRoughness;
			float Anisotropy;
			float AnisotropyRotation;
			float Alpha;
			bool Halo;
			Math::Vec3 TransmissionFilter;
			float IndexOfRefraction;
			float Displacement;
			uint8_t IlluminationModel;
			Math::Vec3 Normal;
			Math::Vec3 Tangent;
			Math::Vec3 ClearCoatNormal;

			BFW_STRING_TYPE AlbedoTexture;
			BFW_STRING_TYPE SpecularColorTexture;
			BFW_STRING_TYPE SpecularExponentTexture;
			BFW_STRING_TYPE EmissionColorTexture;
			BFW_STRING_TYPE RoughnessTexture;
			BFW_STRING_TYPE MetalnessTexture;
			BFW_STRING_TYPE AmbientOcclusionTexture;
			BFW_STRING_TYPE AmbientColorTexture;
			BFW_STRING_TYPE SheenTexture;
			BFW_STRING_TYPE SheenColorTexture;
			BFW_STRING_TYPE ClearCoatTexture;
			BFW_STRING_TYPE ClearCoatColorTexture;
			BFW_STRING_TYPE ClearCoatRoughnessTexture;
			BFW_STRING_TYPE AnisotropyTexture;
			BFW_STRING_TYPE AnisotropyRotationTexture;
			BFW_STRING_TYPE AlphaTexture;
			BFW_STRING_TYPE TransmissionFilterTexture;
			BFW_STRING_TYPE DisplacementTexture;
			BFW_STRING_TYPE NormalTexture;
			BFW_STRING_TYPE TangentTexture;
			BFW_STRING_TYPE ClearCoatNormalTexture;
			BFW_STRING_TYPE DecalTexture;
			BFW_STRING_TYPE BumpTexture;
			Vector<BFW_STRING_TYPE> ReflectionTextures;

			TextureSettings AlbedoTextureSettings;
			TextureSettings SpecularColorTextureSettings;
			TextureSettings SpecularExponentTextureSettings;
			TextureSettings EmissionColorTextureSettings;
			TextureSettings RoughnessTextureSettings;
			TextureSettings MetalnessTextureSettings;
			TextureSettings AmbientOcclusionTextureSettings;
			TextureSettings AmbientColorTextureSettings;
			TextureSettings SheenTextureSettings;
			TextureSettings SheenColorTextureSettings;
			TextureSettings ClearCoatTextureSettings;
			TextureSettings ClearCoatColorTextureSettings;
			TextureSettings ClearCoatRoughnessTextureSettings;
			TextureSettings AnisotropyTextureSettings;
			TextureSettings AnisotropyRotationTextureSettings;
			TextureSettings AlphaTextureSettings;
			TextureSettings TransmissionFilterTextureSettings;
			TextureSettings DisplacementTextureSettings;
			TextureSettings NormalTextureSettings;
			TextureSettings TangentTextureSettings;
			TextureSettings ClearCoatNormalTextureSettings;
			TextureSettings DecalTextureSettings;
			TextureSettings BumpTextureSettings;
			Vector<TextureSettings> ReflectionTexturesSettings;

			Material();
			Material(const Material& _Other);
			Material(Material&& _Other) noexcept;
			~Material();

			const bool IsValid() const;

			Material& operator= (const Material& _Other);
			Material& operator= (Material&& _Other) noexcept;

		};

		class BFW_API MaterialLib
		{

		public:

			MaterialLib();
			MaterialLib(const MaterialLib& _Other);
			MaterialLib(MaterialLib&& _Other) noexcept;
			~MaterialLib();

			const bool Load(const FileContent& _FileContent);

			Material& Push(const BFW_CHAR_TYPE* _Name, const Material& _Data);
			Material& Emplace(const BFW_CHAR_TYPE* _Name, Material&& _Data);

			void Erase(const BFW_CHAR_TYPE* _Name);
			void Clear();

			FileContent Save() const;

			const Vector<BFW_STRING_TYPE>& GetMaterialNames() const;

			Material* GetData(const BFW_CHAR_TYPE* _Name);
			const Material* GetData(const BFW_CHAR_TYPE* _Name) const;

			Material& operator[] (const BFW_CHAR_TYPE* _Name);
			const Material& operator[] (const BFW_CHAR_TYPE* _Name) const;

			MaterialLib& operator= (const MaterialLib& _Other);
			MaterialLib& operator= (MaterialLib&& _Other) noexcept;

		private:

			Vector<BFW_STRING_TYPE> MaterialNames;
			Trie<Material> Materials;

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
			void SetString(const BFW_STRING_VIEW_TYPE_A& _StringValue);
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
			void QueueWaveFrontObj(const BFW_CHAR_TYPE* _Name);
			void QueueGLSL(const BFW_CHAR_TYPE* _Name);
			void QueueJson(const BFW_CHAR_TYPE* _Name);

#ifdef BFW_WINDOWS_PLATFORM

			void QueueResourceBitMap(const size_t _Id);
			void QueueResourceHdr(const size_t _Id);
			void QueueResourceWave(const size_t _Id);
			void QueueResourceWaveFrontObj(const size_t _Id);
			void QueueResourceGLSL(const size_t _Id);
			void QueueResourceJson(const size_t _Id);

#endif

			void Flush();

			void AddDynamicBitMap(const BFW_CHAR_TYPE* _Name, SharedPointer<BitMap>& _Asset);
			void AddDynamicHdr(const BFW_CHAR_TYPE* _Name, SharedPointer<Hdr>& _Asset);
			void AddDynamicWave(const BFW_CHAR_TYPE* _Name, SharedPointer<Wave>& _Asset);
			void AddDynamicWaveFrontObj(const BFW_CHAR_TYPE* _Name, SharedPointer<WaveFrontObj>& _Asset);
			void AddDynamicGLSL(const BFW_CHAR_TYPE* _Name, SharedPointer<FileContent>& _Asset);
			void AddDynamicJson(const BFW_CHAR_TYPE* _Name, SharedPointer<Json>& _Asset);

			void AddDynamicBitMapRef(const BFW_CHAR_TYPE* _Name, SharedPointer<BitMap>& _Asset);
			void AddDynamicHdrRef(const BFW_CHAR_TYPE* _Name, SharedPointer<Hdr>& _Asset);
			void AddDynamicWaveRef(const BFW_CHAR_TYPE* _Name, SharedPointer<Wave>& _Asset);
			void AddDynamicWaveFrontObjRef(const BFW_CHAR_TYPE* _Name, SharedPointer<WaveFrontObj>& _Asset);
			void AddDynamicGLSLRef(const BFW_CHAR_TYPE* _Name, SharedPointer<FileContent>& _Asset);
			void AddDynamicJsonRef(const BFW_CHAR_TYPE* _Name, SharedPointer<Json>& _Asset);

			void Update();

			void ReleaseBitMap(const BFW_CHAR_TYPE* _Name);
			void ReleaseHdr(const BFW_CHAR_TYPE* _Name);
			void ReleaseWave(const BFW_CHAR_TYPE* _Name);
			void ReleaseWaveFrontObj(const BFW_CHAR_TYPE* _Name);
			void ReleaseGLSL(const BFW_CHAR_TYPE* _Name);
			void ReleaseJson(const BFW_CHAR_TYPE* _Name);

#ifdef BFW_WINDOWS_PLATFORM

			void ReleaseResourceBitMap(const size_t _Id);
			void ReleaseResourceHdr(const size_t _Id);
			void ReleaseResourceWave(const size_t _Id);
			void ReleaseResourceWaveFrontObj(const size_t _Id);
			void ReleaseResourceGLSL(const size_t _Id);
			void ReleaseResourceJson(const size_t _Id);

#endif

			SharedPointer<BitMap> GetBitMap(const BFW_CHAR_TYPE* _Name);
			const SharedPointer<BitMap> GetBitMap(const BFW_CHAR_TYPE* _Name) const;
			SharedPointer<Hdr> GetHdr(const BFW_CHAR_TYPE* _Name);
			const SharedPointer<Hdr> GetHdr(const BFW_CHAR_TYPE* _Name) const;
			SharedPointer<Wave> GetWave(const BFW_CHAR_TYPE* _Name);
			const SharedPointer<Wave> GetWave(const BFW_CHAR_TYPE* _Name) const;
			SharedPointer<WaveFrontObj> GetWaveFrontObj(const BFW_CHAR_TYPE* _Name);
			const SharedPointer<WaveFrontObj> GetWaveFrontObj(const BFW_CHAR_TYPE* _Name) const;
			SharedPointer<FileContent> GetGLSL(const BFW_CHAR_TYPE* _Name);
			const SharedPointer<FileContent> GetGLSL(const BFW_CHAR_TYPE* _Name) const;
			SharedPointer<Json> GetJson(const BFW_CHAR_TYPE* _Name);
			const SharedPointer<Json> GetJson(const BFW_CHAR_TYPE* _Name) const;

#ifdef BFW_WINDOWS_PLATFORM

			SharedPointer<BitMap> GetResourceBitMap(const size_t _Id);
			const SharedPointer<BitMap> GetResourceBitMap(const size_t _Id) const;
			SharedPointer<Hdr> GetResourceHdr(const size_t _Id);
			const SharedPointer<Hdr> GetResourceHdr(const size_t _Id) const;
			SharedPointer<Wave> GetResourceWave(const size_t _Id);
			const SharedPointer<Wave> GetResourceWave(const size_t _Id) const;
			SharedPointer<WaveFrontObj> GetResourceWaveFrontObj(const size_t _Id);
			const SharedPointer<WaveFrontObj> GetResourceWaveFrontObj(const size_t _Id) const;
			SharedPointer<FileContent> GetResourceGLSL(const size_t _Id);
			const SharedPointer<FileContent> GetResourceGLSL(const size_t _Id) const;
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
			Vector<BFW_STRING_TYPE> QueuedWaveFrontObjs;
			Vector<BFW_STRING_TYPE> QueuedGLSLs;
			Vector<BFW_STRING_TYPE> QueuedJsons;

#ifdef BFW_WINDOWS_PLATFORM

			Vector<size_t> QueuedResourceBitMaps;
			Vector<size_t> QueuedResourceHdrs;
			Vector<size_t> QueuedResourceWaves;
			Vector<size_t> QueuedResourceWaveFrontObjs;
			Vector<size_t> QueuedResourceGLSLs;
			Vector<size_t> QueuedResourceJsons;

#endif

			Trie<SharedPointer<BitMap>> LoadedBitMaps;
			Trie<SharedPointer<Hdr>> LoadedHdrs;
			Trie<SharedPointer<Wave>> LoadedWaves;
			Trie<SharedPointer<WaveFrontObj>> LoadedWaveFrontObjs;
			Trie<SharedPointer<FileContent>> LoadedGLSLs;
			Trie<SharedPointer<Json>> LoadedJsons;

#ifdef BFW_WINDOWS_PLATFORM

			Trie<SharedPointer<BitMap>> LoadedResourceBitMaps;
			Trie<SharedPointer<Hdr>> LoadedResourceHdrs;
			Trie<SharedPointer<Wave>> LoadedResourceWaves;
			Trie<SharedPointer<WaveFrontObj>> LoadedResourceWaveFrontObjs;
			Trie<SharedPointer<FileContent>> LoadedResourceGLSLs;
			Trie<SharedPointer<Json>> LoadedResourceJsons;

#endif

			mutable Vector<BFW_STRING_TYPE> CachedBitMapNames;
			mutable Vector<BFW_STRING_TYPE> CachedHdrNames;
			mutable Vector<BFW_STRING_TYPE> CachedWaveNames;
			mutable Vector<BFW_STRING_TYPE> CachedWaveFrontObjNames;
			mutable Vector<BFW_STRING_TYPE> CachedGLSLNames;
			mutable Vector<BFW_STRING_TYPE> CachedJsonNames;

			mutable Trie<WeakPointer<BitMap>> CachedBitMaps;
			mutable Trie<WeakPointer<Hdr>> CachedHdrs;
			mutable Trie<WeakPointer<Wave>> CachedWaves;
			mutable Trie<WeakPointer<WaveFrontObj>> CachedWaveFrontObjs;
			mutable Trie<WeakPointer<FileContent>> CachedGLSLs;
			mutable Trie<WeakPointer<Json>> CachedJsons;

			mutable Trie<uint64_t> LastWriteBitMaps;
			mutable Trie<uint64_t> LastWriteHdrs;
			mutable Trie<uint64_t> LastWriteWaves;
			mutable Trie<uint64_t> LastWriteWaveFrontObjs;
			mutable Trie<uint64_t> LastWriteGLSLs;
			mutable Trie<uint64_t> LastWriteJsons;

#ifdef BFW_WINDOWS_PLATFORM

			mutable Vector<BFW_STRING_TYPE> CachedResourceBitMapNames;
			mutable Vector<BFW_STRING_TYPE> CachedResourceHdrNames;
			mutable Vector<BFW_STRING_TYPE> CachedResourceWaveNames;
			mutable Vector<BFW_STRING_TYPE> CachedResourceWaveFrontObjNames;
			mutable Vector<BFW_STRING_TYPE> CachedResourceGLSLNames;
			mutable Vector<BFW_STRING_TYPE> CachedResourceJsonNames;

			mutable Trie<WeakPointer<BitMap>> CachedResourceBitMaps;
			mutable Trie<WeakPointer<Hdr>> CachedResourceHdrs;
			mutable Trie<WeakPointer<Wave>> CachedResourceWaves;
			mutable Trie<WeakPointer<WaveFrontObj>> CachedResourceWaveFrontObjs;
			mutable Trie<WeakPointer<FileContent>> CachedResourceGLSLs;
			mutable Trie<WeakPointer<Json>> CachedResourceJsons;

#endif

		};

	}

}



#endif
