#ifndef BFW_Rasterizer_hpp

#define BFW_Rasterizer_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace Rasterizer
	{

		enum BFW_API DataTypes : const uint8_t
		{
			_FloatDataType = 0,
			_8BitIntDataType = 1,
			_8BitUnsignedIntDataType = 2,
			_16IntDataType = 3,
			_16BitUnsignedIntDataType = 4,
			_32BitIntDataType = 5,
			_32BitUnsignedIntDataType = 6,
			_64BitIntDataType = 7,
			_64BitUnsignedIntDataType = 8
		};

		enum BFW_API FilteringTypes : const uint8_t
		{
			_NearestFilteringType = 0,
			_LinearFilteringType = 1
		};

		enum BFW_API WrappingTypes : const uint8_t
		{
			_BlackWrappingType = 0,
			_ClampWrappingType = 1,
			_RepeatWrappingType = 2,
			_MirrorWrappingType = 3
		};

		enum BFW_API CubeMapFaces : const size_t
		{
			_RightCubeMapFace = 0,
			_LeftCubeMapFace = 1,
			_TopCubeMapFace = 2,
			_BottomCubeMapFace = 3,
			_FrontCubeMapFace = 4,
			_BackCubeMapFace = 5
		};

		enum BFW_API Shapes : const uint8_t
		{
			_PointShape = 0,
			_LineShape = 1,
			_LineStripShape = 2,
			_LineLoopShape = 3,
			_TriangleShape = 4,
			_TriangleStripShape = 5,
			_TriangleFanShape = 6
		};

		enum BFW_API CullingTypes : const uint8_t
		{
			_NoCullingType = 0,
			_ClockWiseCullingType = 1,
			_CounterClockWiseCullingType = 2
		};

		enum BFW_API DepthTestingTypes : const uint8_t
		{
			_NoDepthTestingType = 0,
			_LowerDepthTestingType = 1,
			_LowerOrEqualDepthTestingType = 2,
			_HigherDepthTestingType = 3,
			_HigherOrEqualDepthTestingType = 4
		};

		enum BFW_API BlendingTypes : const uint8_t
		{
			_NoBlendingType = 0,
			_AlphaBlendingType = 1,
			_AdditiveBlendingType = 2
		};

		class BFW_API VertexBuffer
		{

		public:

			VertexBuffer();
			VertexBuffer(const VertexBuffer& _Other);
			VertexBuffer(VertexBuffer&& _Other) noexcept;
			~VertexBuffer();

			void Data(const size_t _Size, const uint8_t* _Data);
			void SubData(const size_t _Offset, const size_t _Size, const uint8_t* _Data);

			VertexBuffer& operator= (const VertexBuffer& _Other);
			VertexBuffer& operator= (VertexBuffer&& _Other) noexcept;

		private:

			Vector<uint8_t> DataVector;

		};

		class BFW_API IndexBuffer
		{

		public:

			IndexBuffer();
			IndexBuffer(const IndexBuffer& _Other);
			IndexBuffer(IndexBuffer&& _Other) noexcept;
			~IndexBuffer();

			void Data(const size_t _Size, const uint32_t* _Data);
			void SubData(const size_t _Offset, const size_t _Size, const uint32_t* _Data);

			IndexBuffer& operator= (const IndexBuffer& _Other);
			IndexBuffer& operator= (IndexBuffer&& _Other) noexcept;

		private:

			Vector<uint32_t> DataVector;

		};

		class BFW_API UniformBuffer
		{

		public:

			UniformBuffer();
			UniformBuffer(const UniformBuffer& _Other);
			UniformBuffer(UniformBuffer&& _Other) noexcept;
			~UniformBuffer();

			void Data(const size_t _Size, const uint8_t* _Data);
			void SubData(const size_t _Offset, const size_t _Size, const uint8_t* _Data);

			const uint8_t* GetData() const;

			UniformBuffer& operator= (const UniformBuffer& _Other);
			UniformBuffer& operator= (UniformBuffer&& _Other) noexcept;

		private:

			friend Context;

			Vector<uint8_t> DataVector;

		};

		struct BFW_API VertexArrayEntry
		{

			const VertexBuffer* VBO;
			size_t Count;
			uint8_t DataType;
			bool Normalize;
			size_t Stride;
			size_t Offset;

			VertexArrayEntry();
			VertexArrayEntry(const VertexBuffer* _VBO, const size_t _Count, const uint8_t _DataType, const bool _Normalize, const size_t _Stride, const size_t _Offset);
			VertexArrayEntry(const VertexArrayEntry& _Other) = default;
			VertexArrayEntry(VertexArrayEntry&& _Other) noexcept;
			VertexArrayEntry& operator= (const VertexArrayEntry& _Other) = default;
			VertexArrayEntry& operator= (VertexArrayEntry&& _Other) noexcept;

		};

		class BFW_API VertexArray
		{

		public:

			VertexArray();
			VertexArray(const VertexArray& _Other);
			VertexArray(VertexArray&& _Other) noexcept;
			~VertexArray();

			void EnableAttribute(const size_t _Index);
			void DisableAttribute(const size_t _Index);
			void AttributePointer(const size_t _Index, const VertexArrayEntry& _Entry);

			void BindIBO(const IndexBuffer* _IBO);

			VertexArray& operator= (const VertexArray& _Other);
			VertexArray& operator= (VertexArray&& _Other) noexcept;

		private:

			const IndexBuffer* IBO;
			Vector<bool> EnabledEntries;
			Vector<VertexArrayEntry> Entries;

		};

		class BFW_API Uniform
		{

		public:

			Uniform();
			Uniform(const Uniform& _Other);
			Uniform(Uniform&& _Other) noexcept;
			~Uniform();

			void Set1f(const float _XVal);
			void Set2f(const float _XVal, const float _YVal);
			void Set3f(const float _XVal, const float _YVal, const float _ZVal);
			void Set4f(const float _XVal, const float _YVal, const float _ZVal, const float _WVal);

			void Set1i(const int32_t _XVal);
			void Set2i(const int32_t _XVal, const int32_t _YVal);
			void Set3i(const int32_t _XVal, const int32_t _YVal, const int32_t _ZVal);
			void Set4i(const int32_t _XVal, const int32_t _YVal, const int32_t _ZVal, const int32_t _WVal);

			void Set1ui(const uint32_t _XVal);
			void Set2ui(const uint32_t _XVal, const uint32_t _YVal);
			void Set3ui(const uint32_t _XVal, const uint32_t _YVal, const uint32_t _ZVal);
			void Set4ui(const uint32_t _XVal, const uint32_t _YVal, const uint32_t _ZVal, const uint32_t _WVal);

			void Set2m(const float* _Data);
			void Set3m(const float* _Data);
			void Set4m(const float* _Data);

			void Setui64(const uint64_t _UInt64);

			const float& Get1f() const;
			const Math::Vec2& Get2f() const;
			const Math::Vec3& Get3f() const;
			const Math::Vec4& Get4f() const;

			const int32_t& Get1i() const;
			const int32_t* Get2i() const;
			const int32_t* Get3i() const;
			const int32_t* Get4i() const;

			const uint32_t& Get1ui() const;
			const uint32_t* Get2ui() const;
			const uint32_t* Get3ui() const;
			const uint32_t* Get4ui() const;

			const Math::Mat2& Get2m() const;
			const Math::Mat3& Get3m() const;
			const Math::Mat4& Get4m() const;

			const uint64_t& Getui64() const;

			Uniform& operator= (const Uniform& _Other);
			Uniform& operator= (Uniform&& _Other) noexcept;

		private:

			float Floats[16];
			int32_t Ints[4];
			uint32_t UInts[4];
			uint64_t UInt64;

		};

		class BFW_API Program
		{

		public:

			VertexShaderFnc VertexShader;
			GeometryShaderFnc GeometryShader;
			FragmentShaderFnc FragmentShader;
			size_t VaryingsVertexToGeometry;
			size_t FlatsVertexToGeometry;
			size_t VaryingsGeometryToFragment;
			size_t FlatsGeometryToFragment;
			Vector<BFW_STRING_TYPE_A> UniformBlocks;
			Trie<Uniform, BFW_CHAR_TYPE_A> Uniforms;
			Trie<size_t, BFW_CHAR_TYPE_A> UniformBlockBindings;

			Program();
			Program(const Program& _Other);
			Program(Program&& _Other) noexcept;
			~Program();

			const bool IsValid() const;

			Program& operator= (const Program& _Other);
			Program& operator= (Program&& _Other) noexcept;

		};

		class BFW_API Texture
		{

		public:

			virtual const Math::Vec4 Sample(const Math::Vec2& _TextureCoords, const float _MipLevel = 0.0f) const = 0;

		protected:

			Texture();
			Texture(const Texture& _Other);
			Texture(Texture&& _Other) noexcept;
			virtual ~Texture();

			Texture& operator= (const Texture& _Other);
			Texture& operator= (Texture&& _Other) noexcept;

		};

		class BFW_API TextureSDR : public Texture
		{

		public:

			TextureSDR();
			TextureSDR(const TextureSDR& _Other);
			TextureSDR(TextureSDR&& _Other) noexcept;
			~TextureSDR();

			void Data(const size_t _Level, const size_t _Width, const size_t _Height, const size_t _ChannelsCount, const uint8_t* _Data);
			void FilteringTypes(const uint8_t _XFilteringType, const uint8_t _YFilteringType, const uint8_t _ZFilteringType);
			void WrappingTypes(const uint8_t _XWrappingType, const uint8_t _YWrappingType);

			const Math::Vec4 Sample(const Math::Vec2& _TextureCoords, const float _MipLevel = 0.0f) const override;

			TextureSDR& operator= (const TextureSDR& _Other);
			TextureSDR& operator= (TextureSDR&& _Other) noexcept;

		private:

			friend CubeTextureSDR;
			friend FrameBuffer;

			Vector<Assets::BitMap> TextureChain;
			uint8_t XFilteringType;
			uint8_t YFilteringType;
			uint8_t ZFilteringType;
			uint8_t XWrappingType;
			uint8_t YWrappingType;
			bool FilteringTypeSet;
			bool WrappingTypeSet;

		};

		class BFW_API TextureHDR : public Texture
		{

		public:

			TextureHDR();
			TextureHDR(const TextureHDR& _Other);
			TextureHDR(TextureHDR&& _Other) noexcept;
			~TextureHDR();

			void Data(const size_t _Level, const size_t _Width, const size_t _Height, const size_t _ChannelsCount, const float* _Data);
			void FilteringTypes(const uint8_t _XFilteringType, const uint8_t _YFilteringType, const uint8_t _ZFilteringType);
			void WrappingTypes(const uint8_t _XWrappingType, const uint8_t _YWrappingType);

			const Math::Vec4 Sample(const Math::Vec2& _TextureCoords, const float _MipLevel = 0.0f) const override;

			TextureHDR& operator= (const TextureHDR& _Other);
			TextureHDR& operator= (TextureHDR&& _Other) noexcept;

		private:

			friend CubeTextureHDR;
			friend FrameBuffer;

			Vector<Assets::Hdr> TextureChain;
			uint8_t XFilteringType;
			uint8_t YFilteringType;
			uint8_t ZFilteringType;
			uint8_t XWrappingType;
			uint8_t YWrappingType;
			bool FilteringTypeSet;
			bool WrappingTypeSet;

		};

		class BFW_API CubeTexture
		{

		public:

			virtual const Math::Vec4 Sample(const Math::Vec3& _Direction, const float _MipLevel = 0.0f) const = 0;

		protected:

			CubeTexture();
			CubeTexture(const CubeTexture& _Other);
			CubeTexture(CubeTexture&& _Other) noexcept;
			virtual ~CubeTexture();

			CubeTexture& operator= (const CubeTexture& _Other);
			CubeTexture& operator= (CubeTexture&& _Other) noexcept;

		};

		class BFW_API CubeTextureSDR : public CubeTexture
		{

		public:

			CubeTextureSDR();
			CubeTextureSDR(const CubeTextureSDR& _Other);
			CubeTextureSDR(CubeTextureSDR&& _Other) noexcept;
			~CubeTextureSDR();

			void Data(const size_t _Face, const size_t _Level, const size_t _Width, const size_t _Height, const size_t _ChannelsCount, const uint8_t* _Data);
			void FilteringTypes(const uint8_t _XFilteringType, const uint8_t _YFilteringType, const uint8_t _ZFilteringType);

			const Math::Vec4 Sample(const Math::Vec3& _Direction, const float _MipLevel = 0.0f) const override;

			CubeTextureSDR& operator= (const CubeTextureSDR& _Other);
			CubeTextureSDR& operator= (CubeTextureSDR&& _Other) noexcept;

		private:

			friend FrameBuffer;

			Vector<TextureSDR> Textures;

		};

		class BFW_API CubeTextureHDR : public CubeTexture
		{

		public:

			CubeTextureHDR();
			CubeTextureHDR(const CubeTextureHDR& _Other);
			CubeTextureHDR(CubeTextureHDR&& _Other) noexcept;
			~CubeTextureHDR();

			void Data(const size_t _Face, const size_t _Level, const size_t _Width, const size_t _Height, const size_t _ChannelsCount, const float* _Data);
			void FilteringTypes(const uint8_t _XFilteringType, const uint8_t _YFilteringType, const uint8_t _ZFilteringType);

			const Math::Vec4 Sample(const Math::Vec3& _Direction, const float _MipLevel = 0.0f) const override;

			CubeTextureHDR& operator= (const CubeTextureHDR& _Other);
			CubeTextureHDR& operator= (CubeTextureHDR&& _Other) noexcept;

		private:

			friend FrameBuffer;

			Vector<TextureHDR> Textures;

		};

		class BFW_API FrameBuffer
		{

		public:

			FrameBuffer();
			FrameBuffer(const FrameBuffer& _Other);
			FrameBuffer(FrameBuffer&& _Other) noexcept;
			~FrameBuffer();

			void AttachColorSDR(TextureSDR& _Texture, const size_t _Level);
			void AttachColorHDR(TextureHDR& _Texture, const size_t _Level);
			void AttachColorCubeSDR(CubeTextureSDR& _Texture, const size_t _Face, const size_t _Level);
			void AttachColorCubeHDR(CubeTextureHDR& _Texture, const size_t _Face, const size_t _Level);
			void AttachDepth(TextureHDR& _Texture, const size_t _Level);
			void DetachColor();
			void DetachDepth();

			const bool IsValid() const;

			void ReadSDR(const intptr_t _PositionX, const intptr_t _PositionY, const size_t _Width, const size_t _Height, const size_t _ChannelsCount, uint8_t* _Data);
			void ReadHDR(const intptr_t _PositionX, const intptr_t _PositionY, const size_t _Width, const size_t _Height, const size_t _ChannelsCount, float* _Data);
			void ReadDepth(const intptr_t _PositionX, const intptr_t _PositionY, const size_t _Width, const size_t _Height, float* _Data);

			FrameBuffer& operator= (const FrameBuffer& _Other);
			FrameBuffer& operator= (FrameBuffer&& _Other) noexcept;

		private:

			friend Context;

			Assets::BitMap* ColorSDR;
			Assets::Hdr* ColorHDR;
			Assets::Hdr* Depth;

		};

		class BFW_API Context
		{

		public:

			Context(const Context* _Parent = nullptr);
			Context(const Context& _Other);
			Context(Context&& _Other) noexcept;
			~Context();

			void Clear(FrameBuffer& _FBO);
			void ClearColor(FrameBuffer& _FBO);
			void ClearDepth(FrameBuffer& _FBO);

			void DrawArrays(const uint8_t _Shape, const size_t _First, const size_t _Count, const VertexArray& _VAO, const Program& _Program, FrameBuffer& _FBO);
			void DrawElements(const uint8_t _Shape, const size_t _Count, const void* _Indices, const VertexArray& _VAO, const Program& _Program, FrameBuffer& _FBO);

			const Math::Vec4 Sample(const uint64_t _GUID, const Math::Vec2& _TextureCoords, const float _MipLevel = 0.0f) const;
			const Math::Vec4 Sample(const uint64_t _GUID, const Math::Vec3& _Direction, const float _MipLevel = 0.0f) const;

			void SetClearColorValue(const Math::Vec4& _ClearColorValue);
			void SetClearDepthValue(const float _ClearDepthValue);

			void SetViewPort(const intptr_t _ViewPortX, const intptr_t _ViewPortY, const size_t _ViewPortWidth, const size_t _ViewPortHeight);

			const bool SetCullingType(const uint8_t _CullingType);
			const bool SetDepthTestingType(const uint8_t _DepthTestingType);
			const bool SetBlendingType(const uint8_t _BlendingType);

			void SetTextureGUID(const Texture* _Texture, const uint64_t _GUID);
			void SetCubeTextureGUID(const CubeTexture* _Texture, const uint64_t _GUID);

			void SetUniformBufferBinding(const size_t _Slot, const UniformBuffer* _UniformBufferBinding, const size_t _UniformBufferBindingOffset, const size_t _UniformBufferBindingSize);

			Context& operator= (const Context& _Other);
			Context& operator= (Context&& _Other) noexcept;

		private:

			void VertexPass();
			void GeometryPass();
			void ClippingPass();
			void CullingPass();
			void RasterizingPass();

			const Context* Parent;

			Math::Vec4 ClearColorValue;
			float ClearDepthValue;

			intptr_t ViewPortX;
			intptr_t ViewPortY;
			size_t ViewPortWidth;
			size_t ViewPortHeight;

			uint8_t CullingType;
			uint8_t DepthTestingType;
			uint8_t BlendingType;

			Vector<uint64_t> TextureGUIDs;
			Trie<const Texture*> Textures;
			Vector<uint64_t> CubeTextureGUIDs;
			Trie<const CubeTexture*> CubeTextures;

			Vector<const UniformBuffer*> UniformBufferBindings;
			Vector<size_t> UniformBufferBindingOffsets;
			Vector<size_t> UniformBufferBindingSizes;

		};

		void SetLastError();
		const bool GetLastError();

	}

}



#endif
