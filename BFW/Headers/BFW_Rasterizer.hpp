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

		enum BFW_API LerpingTypes : const uint8_t
		{
			_NearestLerpingType = 0,
			_LinearLerpingType = 1
		};

		enum BFW_API WrappingTypes : const uint8_t
		{
			_BlackWrappingType = 0,
			_ClampWrappingType = 1,
			_RepeatWrappingType = 2,
			_MirrorWrappingType = 3
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

		struct BFW_API VertexArrayEntry
		{

			VertexArrayEntry();
			VertexArrayEntry(const size_t _Count, const uint8_t _DataType, const bool _Normalize, const size_t _Stride, const size_t _Offset);
			VertexArrayEntry(const VertexArrayEntry& _Other) = default;
			VertexArrayEntry(VertexArrayEntry&& _Other) noexcept;
			VertexArrayEntry& operator= (const VertexArrayEntry& _Other) = default;
			VertexArrayEntry& operator= (VertexArrayEntry&& _Other) noexcept;

			size_t Count;
			uint8_t DataType;
			bool Normalize;
			size_t Stride;
			size_t Offset;

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

			VertexArray& operator= (const VertexArray& _Other);
			VertexArray& operator= (VertexArray&& _Other) noexcept;

		private:

			Vector<bool> EnabledEntries;
			Vector<VertexArrayEntry> Entries;

		};

		struct BFW_API Program
		{

			Program();
			Program(const VertexShaderFnc& _VertexShader, const GeometryShaderFnc& _GeometryShader, const FragmentShaderFnc& _FragmentShader);
			Program(const Program& _Other) = default;
			Program(Program&& _Other) noexcept;
			Program& operator= (const Program& _Other) = default;
			Program& operator= (Program&& _Other) noexcept;

			VertexShaderFnc VertexShader;
			GeometryShaderFnc GeometryShader;
			FragmentShaderFnc FragmentShader;

		};

		class BFW_API TextureSDR
		{

		public:

			TextureSDR();
			TextureSDR(const TextureSDR& _Other);
			TextureSDR(TextureSDR&& _Other) noexcept;
			~TextureSDR();

			void Data(const size_t _Level, const size_t _Width, const size_t _Height, const size_t _ChannelsCount, const uint8_t* _Data);
			void LerpingTypes(const uint8_t _XLerpingType, const uint8_t _YLerpingType);
			void WrappingTypes(const uint8_t _XWrappingType, const uint8_t _YWrappingType);

			const Math::Vec4 Sample(const Math::Vec2& _TextureCoords, const float _MipLevel = 0.0f) const;
			const Math::Vec4 Sample(const Math::Vec3& _TextureCoords) const;

			TextureSDR& operator= (const TextureSDR& _Other);
			TextureSDR& operator= (TextureSDR&& _Other) noexcept;

		private:

			Vector<Assets::BitMap> TextureChain;
			uint8_t XLerpingType;
			uint8_t YLerpingType;
			uint8_t XWrappingType;
			uint8_t YWrappingType;
			bool LerpingTypeSet;
			bool WrappingTypeSet;

		};

		class BFW_API TextureHDR
		{

		public:

			TextureHDR();
			TextureHDR(const TextureHDR& _Other);
			TextureHDR(TextureHDR&& _Other) noexcept;
			~TextureHDR();

			void Data(const size_t _Level, const size_t _Width, const size_t _Height, const size_t _ChannelsCount, const float* _Data);
			void LerpingTypes(const uint8_t _XLerpingType, const uint8_t _YLerpingType);
			void WrappingTypes(const uint8_t _XWrappingType, const uint8_t _YWrappingType);

			const Math::Vec4 Sample(const Math::Vec2& _TextureCoords, const float _MipLevel = 0.0f) const;
			const Math::Vec4 Sample(const Math::Vec3& _TextureCoords) const;

			TextureHDR& operator= (const TextureHDR& _Other);
			TextureHDR& operator= (TextureHDR&& _Other) noexcept;

		private:

			Vector<Assets::Hdr> TextureChain;
			uint8_t XLerpingType;
			uint8_t YLerpingType;
			uint8_t XWrappingType;
			uint8_t YWrappingType;
			bool LerpingTypeSet;
			bool WrappingTypeSet;

		};

		class BFW_API CubeTextureSDR
		{

		public:

			CubeTextureSDR();
			CubeTextureSDR(const CubeTextureSDR& _Other);
			CubeTextureSDR(CubeTextureSDR&& _Other) noexcept;
			~CubeTextureSDR();

			CubeTextureSDR& operator= (const CubeTextureSDR& _Other);
			CubeTextureSDR& operator= (CubeTextureSDR&& _Other) noexcept;

		private:



		};

		class BFW_API CubeTextureHDR
		{

		public:

			CubeTextureHDR();
			CubeTextureHDR(const CubeTextureHDR& _Other);
			CubeTextureHDR(CubeTextureHDR&& _Other) noexcept;
			~CubeTextureHDR();

			CubeTextureHDR& operator= (const CubeTextureHDR& _Other);
			CubeTextureHDR& operator= (CubeTextureHDR&& _Other) noexcept;

		private:



		};

		class BFW_API FrameBuffer
		{

		public:

			FrameBuffer();
			FrameBuffer(const FrameBuffer& _Other);
			FrameBuffer(FrameBuffer&& _Other) noexcept;
			~FrameBuffer();

			FrameBuffer& operator= (const FrameBuffer& _Other);
			FrameBuffer& operator= (FrameBuffer&& _Other) noexcept;

		private:



		};

		class BFW_API Context
		{

		public:

			Context();
			Context(const Context& _Other);
			Context(Context&& _Other) noexcept;
			~Context();

			Context& operator= (const Context& _Other);
			Context& operator= (Context&& _Other) noexcept;

		private:



		};

		const bool LastError();

	}

}



#endif
