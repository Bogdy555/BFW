#include "../Headers/BFW.hpp"



static thread_local bool LastError = false;



static const BFW::Math::Vec2 WrapTextureCoords(const BFW::Math::Vec2& _TextureCoords, const uint8_t _XWrappingType, const uint8_t _YWrappingType)
{
	BFW::Math::Vec2 _NewTextureCoords = _TextureCoords;

	if (_XWrappingType == BFW::Rasterizer::_RepeatWrappingType)
	{
		_NewTextureCoords.x = _NewTextureCoords.x - floorf(_NewTextureCoords.x);
	}
	else if (_XWrappingType == BFW::Rasterizer::_MirrorWrappingType)
	{
		float _Period = _NewTextureCoords.x - floorf(_NewTextureCoords.x);
		int32_t _Mod = (int32_t)(fabs(floorf(_NewTextureCoords.x))) % 2;

		_NewTextureCoords.x = _Period * (float)(_Mod == 0) + (1.0f - _Period) * (float)(_Mod == 1);
	}
	else
	{
		_NewTextureCoords.x = BFW::Math::Clamp(_NewTextureCoords.x, 0.0f, 1.0f);
	}

	if (_YWrappingType == BFW::Rasterizer::_RepeatWrappingType)
	{
		_NewTextureCoords.y = _NewTextureCoords.y - floorf(_NewTextureCoords.y);
	}
	else if (_YWrappingType == BFW::Rasterizer::_MirrorWrappingType)
	{
		float _Period = _NewTextureCoords.y - floorf(_NewTextureCoords.y);
		int32_t _Mod = (int32_t)(fabs(floorf(_NewTextureCoords.y))) % 2;

		_NewTextureCoords.y = _Period * (float)(_Mod == 0) + (1.0f - _Period) * (float)(_Mod == 1);
	}
	else
	{
		_NewTextureCoords.y = BFW::Math::Clamp(_NewTextureCoords.y, 0.0f, 1.0f);
	}

	return _NewTextureCoords;
}

static const BFW::Math::Vec4 SampleNearestSDR(const BFW::Vector<BFW::Assets::BitMap>& _TextureChain, const BFW::Math::Vec2& _TextureCoords, const float _MipLevel)
{
	size_t _PositionX = (size_t)(BFW::Math::Clamp(_TextureCoords.x * (float)(_TextureChain[(size_t)(floorf(_MipLevel + 0.5f))].GetWidth()), 0.0f, (float)(_TextureChain[(size_t)(floorf(_MipLevel + 0.5f))].GetWidth() - 1)));
	size_t _PositionY = (size_t)(BFW::Math::Clamp(_TextureCoords.y * (float)(_TextureChain[(size_t)(floorf(_MipLevel + 0.5f))].GetHeight()), 0.0f, (float)(_TextureChain[(size_t)(floorf(_MipLevel + 0.5f))].GetHeight() - 1)));

	BFW::Math::Vec4 _Result = BFW::Math::Vec4(0.0f, 0.0f, 0.0f, 1.0f);

	for (size_t _Channel = 0; _Channel < _TextureChain[(size_t)(floorf(_MipLevel + 0.5f))].GetChannelsCount(); _Channel++)
	{
		_Result[_Channel] = (float)(_TextureChain[(size_t)(floorf(_MipLevel + 0.5f))][_PositionY][_PositionX * _TextureChain[(size_t)(floorf(_MipLevel + 0.5f))].GetChannelsCount() + _Channel]) / 255.0f;
	}

	return _Result;
}

static const BFW::Math::Vec4 SampleNearestHDR(const BFW::Vector<BFW::Assets::Hdr>& _TextureChain, const BFW::Math::Vec2& _TextureCoords, const float _MipLevel)
{
	size_t _PositionX = (size_t)(BFW::Math::Clamp(_TextureCoords.x * (float)(_TextureChain[(size_t)(floorf(_MipLevel + 0.5f))].GetWidth()), 0.0f, (float)(_TextureChain[(size_t)(floorf(_MipLevel + 0.5f))].GetWidth() - 1)));
	size_t _PositionY = (size_t)(BFW::Math::Clamp(_TextureCoords.y * (float)(_TextureChain[(size_t)(floorf(_MipLevel + 0.5f))].GetHeight()), 0.0f, (float)(_TextureChain[(size_t)(floorf(_MipLevel + 0.5f))].GetHeight() - 1)));

	BFW::Math::Vec4 _Result = BFW::Math::Vec4(0.0f, 0.0f, 0.0f, 1.0f);

	for (size_t _Channel = 0; _Channel < _TextureChain[(size_t)(floorf(_MipLevel + 0.5f))].GetChannelsCount(); _Channel++)
	{
		_Result[_Channel] = _TextureChain[(size_t)(floorf(_MipLevel + 0.5f))][_PositionY][_PositionX * _TextureChain[(size_t)(floorf(_MipLevel + 0.5f))].GetChannelsCount() + _Channel];
	}

	return _Result;
}



BFW::Rasterizer::VertexBuffer::VertexBuffer() : DataVector()
{

}

BFW::Rasterizer::VertexBuffer::VertexBuffer(const VertexBuffer& _Other) : DataVector(_Other.DataVector)
{

}

BFW::Rasterizer::VertexBuffer::VertexBuffer(VertexBuffer&& _Other) noexcept : DataVector((Vector<uint8_t>&&)(_Other.DataVector))
{

}

BFW::Rasterizer::VertexBuffer::~VertexBuffer()
{

}

void BFW::Rasterizer::VertexBuffer::Data(const size_t _Size, const uint8_t* _Data)
{
	DataVector = Vector<uint8_t>(_Size);

	if (!_Data)
	{
		return;
	}

	for (size_t _Index = 0; _Index < _Size; _Index++)
	{
		DataVector[_Index] = _Data[_Index];
	}
}

void BFW::Rasterizer::VertexBuffer::SubData(const size_t _Offset, const size_t _Size, const uint8_t* _Data)
{
	if (_Offset + _Size > DataVector.GetSize() || !_Data)
	{
		LastError = true;
		return;
	}

	for (size_t _Index = 0; _Index < _Size; _Index++)
	{
		DataVector[_Index + _Offset] = _Data[_Index];
	}
}

BFW::Rasterizer::VertexBuffer& BFW::Rasterizer::VertexBuffer::operator= (const VertexBuffer& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	DataVector = _Other.DataVector;

	return *this;
}

BFW::Rasterizer::VertexBuffer& BFW::Rasterizer::VertexBuffer::operator= (VertexBuffer&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	DataVector = (Vector<uint8_t>&&)(_Other.DataVector);

	return *this;
}



BFW::Rasterizer::IndexBuffer::IndexBuffer() : DataVector()
{

}

BFW::Rasterizer::IndexBuffer::IndexBuffer(const IndexBuffer& _Other) : DataVector(_Other.DataVector)
{

}

BFW::Rasterizer::IndexBuffer::IndexBuffer(IndexBuffer&& _Other) noexcept : DataVector((Vector<uint32_t>&&)(_Other.DataVector))
{

}

BFW::Rasterizer::IndexBuffer::~IndexBuffer()
{

}

void BFW::Rasterizer::IndexBuffer::Data(const size_t _Size, const uint32_t* _Data)
{
	DataVector = Vector<uint32_t>(_Size);

	if (!_Data)
	{
		return;
	}

	for (size_t _Index = 0; _Index < _Size; _Index++)
	{
		DataVector[_Index] = _Data[_Index];
	}
}

void BFW::Rasterizer::IndexBuffer::SubData(const size_t _Offset, const size_t _Size, const uint32_t* _Data)
{
	if (_Offset + _Size > DataVector.GetSize() || !_Data)
	{
		LastError = true;
		return;
	}

	for (size_t _Index = 0; _Index < _Size; _Index++)
	{
		DataVector[_Index + _Offset] = _Data[_Index];
	}
}

BFW::Rasterizer::IndexBuffer& BFW::Rasterizer::IndexBuffer::operator= (const IndexBuffer& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	DataVector = _Other.DataVector;

	return *this;
}

BFW::Rasterizer::IndexBuffer& BFW::Rasterizer::IndexBuffer::operator= (IndexBuffer&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	DataVector = (Vector<uint32_t>&&)(_Other.DataVector);

	return *this;
}



BFW::Rasterizer::UniformBuffer::UniformBuffer() : DataVector()
{

}

BFW::Rasterizer::UniformBuffer::UniformBuffer(const UniformBuffer& _Other) : DataVector(_Other.DataVector)
{

}

BFW::Rasterizer::UniformBuffer::UniformBuffer(UniformBuffer&& _Other) noexcept : DataVector((Vector<uint8_t>&&)(_Other.DataVector))
{

}

BFW::Rasterizer::UniformBuffer::~UniformBuffer()
{

}

void BFW::Rasterizer::UniformBuffer::Data(const size_t _Size, const uint8_t* _Data)
{
	DataVector = Vector<uint8_t>(_Size);

	if (!_Data)
	{
		return;
	}

	for (size_t _Index = 0; _Index < _Size; _Index++)
	{
		DataVector[_Index] = _Data[_Index];
	}
}

void BFW::Rasterizer::UniformBuffer::SubData(const size_t _Offset, const size_t _Size, const uint8_t* _Data)
{
	if (_Offset + _Size > DataVector.GetSize() || !_Data)
	{
		LastError = true;
		return;
	}

	for (size_t _Index = 0; _Index < _Size; _Index++)
	{
		DataVector[_Index + _Offset] = _Data[_Index];
	}
}

const uint8_t* BFW::Rasterizer::UniformBuffer::GetData() const
{
	return DataVector.GetData();
}

BFW::Rasterizer::UniformBuffer& BFW::Rasterizer::UniformBuffer::operator= (const UniformBuffer& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	DataVector = _Other.DataVector;

	return *this;
}

BFW::Rasterizer::UniformBuffer& BFW::Rasterizer::UniformBuffer::operator= (UniformBuffer&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	DataVector = (Vector<uint8_t>&&)(_Other.DataVector);

	return *this;
}



BFW::Rasterizer::VertexArrayEntry::VertexArrayEntry() : VBO(nullptr), Count(0), DataType(_FloatDataType), Normalize(false), Stride(0), Offset(0)
{

}

BFW::Rasterizer::VertexArrayEntry::VertexArrayEntry(VertexBuffer* _VBO, const size_t _Count, const uint8_t _DataType, const bool _Normalize, const size_t _Stride, const size_t _Offset) : VBO(_VBO), Count(_Count), DataType(_DataType), Normalize(_Normalize), Stride(_Stride), Offset(_Offset)
{

}

BFW::Rasterizer::VertexArrayEntry::VertexArrayEntry(VertexArrayEntry&& _Other) noexcept : VBO(_Other.VBO), Count(_Other.Count), DataType(_Other.DataType), Normalize(_Other.Normalize), Stride(_Other.Stride), Offset(_Other.Offset)
{
	_Other.VBO = nullptr;
	_Other.Count = 0;
	_Other.DataType = _FloatDataType;
	_Other.Normalize = false;
	_Other.Stride = 0;
	_Other.Offset = 0;
}

BFW::Rasterizer::VertexArrayEntry& BFW::Rasterizer::VertexArrayEntry::operator= (VertexArrayEntry&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	VBO = _Other.VBO;
	Count = _Other.Count;
	DataType = _Other.DataType;
	Normalize = _Other.Normalize;
	Stride = _Other.Stride;
	Offset = _Other.Offset;

	_Other.VBO = nullptr;
	_Other.Count = 0;
	_Other.DataType = _FloatDataType;
	_Other.Normalize = false;
	_Other.Stride = 0;
	_Other.Offset = 0;

	return *this;
}



BFW::Rasterizer::VertexArray::VertexArray() : IBO(nullptr), EnabledEntries(), Entries()
{

}

BFW::Rasterizer::VertexArray::VertexArray(const VertexArray& _Other) : IBO(_Other.IBO), EnabledEntries(_Other.EnabledEntries), Entries(_Other.Entries)
{

}

BFW::Rasterizer::VertexArray::VertexArray(VertexArray&& _Other) noexcept : IBO(_Other.IBO), EnabledEntries((Vector<bool>&&)(_Other.EnabledEntries)), Entries((Vector<VertexArrayEntry>&&)(_Other.Entries))
{
	_Other.IBO = nullptr;
}

BFW::Rasterizer::VertexArray::~VertexArray()
{

}

void BFW::Rasterizer::VertexArray::EnableAttribute(const size_t _Index)
{
	size_t _CurrentSize = EnabledEntries.GetSize();

	EnabledEntries.Reserve(_Index + 1);
	Entries.Reserve(_Index + 1);

	for (size_t _ForIndex = _CurrentSize; _ForIndex < _Index + 1; _ForIndex++)
	{
		EnabledEntries.PushBack(false);
		Entries.EmplaceBack(VertexArrayEntry());
	}

	EnabledEntries[_Index] = true;
}

void BFW::Rasterizer::VertexArray::DisableAttribute(const size_t _Index)
{
	if (_Index >= EnabledEntries.GetSize())
	{
		return;
	}

	EnabledEntries[_Index] = false;
}

void BFW::Rasterizer::VertexArray::AttributePointer(const size_t _Index, const VertexArrayEntry& _Entry)
{
	if (!_Entry.VBO || _Entry.DataType > _64BitUnsignedIntDataType)
	{
		LastError = true;
		return;
	}

	size_t _CurrentSize = EnabledEntries.GetSize();

	EnabledEntries.Reserve(_Index + 1);
	Entries.Reserve(_Index + 1);

	for (size_t _ForIndex = _CurrentSize; _ForIndex < _Index + 1; _ForIndex++)
	{
		EnabledEntries.PushBack(false);
		Entries.EmplaceBack(VertexArrayEntry());
	}

	Entries[_Index] = _Entry;
}

void BFW::Rasterizer::VertexArray::BindIBO(IndexBuffer* _IBO)
{
	IBO = _IBO;
}

BFW::Rasterizer::VertexArray& BFW::Rasterizer::VertexArray::operator= (const VertexArray& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	IBO = _Other.IBO;
	EnabledEntries = _Other.EnabledEntries;
	Entries = _Other.Entries;

	return *this;
}

BFW::Rasterizer::VertexArray& BFW::Rasterizer::VertexArray::operator= (VertexArray&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	IBO = _Other.IBO;
	EnabledEntries = (Vector<bool>&&)(_Other.EnabledEntries);
	Entries = (Vector<VertexArrayEntry>&&)(_Other.Entries);

	_Other.IBO = nullptr;

	return *this;
}



BFW::Rasterizer::Program::Program() : VertexShader(nullptr), GeometryShader(nullptr), FragmentShader(nullptr), VaryingsVertexToGeometry(0), FlatsVertexToGeometry(0), VaryingsGeometryToFragment(0), FlatsGeometryToFragment(0)
{

}

BFW::Rasterizer::Program::Program(const Program& _Other) : VertexShader(_Other.VertexShader), GeometryShader(_Other.GeometryShader), FragmentShader(_Other.FragmentShader), VaryingsVertexToGeometry(_Other.VaryingsVertexToGeometry), FlatsVertexToGeometry(_Other.FlatsVertexToGeometry), VaryingsGeometryToFragment(_Other.VaryingsGeometryToFragment), FlatsGeometryToFragment(_Other.FlatsGeometryToFragment)
{

}

BFW::Rasterizer::Program::Program(Program&& _Other) noexcept : VertexShader(_Other.VertexShader), GeometryShader(_Other.GeometryShader), FragmentShader(_Other.FragmentShader), VaryingsVertexToGeometry(_Other.VaryingsVertexToGeometry), FlatsVertexToGeometry(_Other.FlatsVertexToGeometry), VaryingsGeometryToFragment(_Other.VaryingsGeometryToFragment), FlatsGeometryToFragment(_Other.FlatsGeometryToFragment)
{
	_Other.VertexShader = nullptr;
	_Other.GeometryShader = nullptr;
	_Other.FragmentShader = nullptr;
	_Other.VaryingsVertexToGeometry = 0;
	_Other.FlatsVertexToGeometry = 0;
	_Other.VaryingsGeometryToFragment = 0;
	_Other.FlatsGeometryToFragment = 0;
}

BFW::Rasterizer::Program::~Program()
{

}

const bool BFW::Rasterizer::Program::IsValid() const
{
	if (!VertexShader || !FragmentShader)
	{
		return false;
	}

	if (!GeometryShader && (VaryingsVertexToGeometry != VaryingsGeometryToFragment || FlatsVertexToGeometry != FlatsGeometryToFragment))
	{
		return false;
	}

	return true;
}

BFW::Rasterizer::Program& BFW::Rasterizer::Program::operator= (const Program& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	VertexShader = _Other.VertexShader;
	GeometryShader = _Other.GeometryShader;
	FragmentShader = _Other.FragmentShader;
	VaryingsVertexToGeometry = _Other.VaryingsVertexToGeometry;
	FlatsVertexToGeometry = _Other.FlatsVertexToGeometry;
	VaryingsGeometryToFragment = _Other.VaryingsGeometryToFragment;
	FlatsGeometryToFragment = _Other.FlatsGeometryToFragment;

	return *this;
}

BFW::Rasterizer::Program& BFW::Rasterizer::Program::operator= (Program&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	VertexShader = _Other.VertexShader;
	GeometryShader = _Other.GeometryShader;
	FragmentShader = _Other.FragmentShader;
	VaryingsVertexToGeometry = _Other.VaryingsVertexToGeometry;
	FlatsVertexToGeometry = _Other.FlatsVertexToGeometry;
	VaryingsGeometryToFragment = _Other.VaryingsGeometryToFragment;
	FlatsGeometryToFragment = _Other.FlatsGeometryToFragment;

	_Other.VertexShader = nullptr;
	_Other.GeometryShader = nullptr;
	_Other.FragmentShader = nullptr;
	_Other.VaryingsVertexToGeometry = 0;
	_Other.FlatsVertexToGeometry = 0;
	_Other.VaryingsGeometryToFragment = 0;
	_Other.FlatsGeometryToFragment = 0;

	return *this;
}



BFW::Rasterizer::TextureSDR::TextureSDR() : TextureChain(), XFilteringType(_NearestFilteringType), YFilteringType(_NearestFilteringType), ZFilteringType(_NearestFilteringType), XWrappingType(_BlackWrappingType), YWrappingType(_BlackWrappingType), FilteringTypeSet(false), WrappingTypeSet(false)
{

}

BFW::Rasterizer::TextureSDR::TextureSDR(const TextureSDR& _Other) : TextureChain(_Other.TextureChain), XFilteringType(_Other.XFilteringType), YFilteringType(_Other.YFilteringType), ZFilteringType(_Other.ZFilteringType), XWrappingType(_Other.XWrappingType), YWrappingType(_Other.YWrappingType), FilteringTypeSet(_Other.FilteringTypeSet), WrappingTypeSet(_Other.WrappingTypeSet)
{

}

BFW::Rasterizer::TextureSDR::TextureSDR(TextureSDR&& _Other) noexcept : TextureChain((Vector<Assets::BitMap>&&)(_Other.TextureChain)), XFilteringType(_Other.XFilteringType), YFilteringType(_Other.YFilteringType), ZFilteringType(_Other.ZFilteringType), XWrappingType(_Other.XWrappingType), YWrappingType(_Other.YWrappingType), FilteringTypeSet(_Other.FilteringTypeSet), WrappingTypeSet(_Other.WrappingTypeSet)
{
	_Other.XFilteringType = _NearestFilteringType;
	_Other.YFilteringType = _NearestFilteringType;
	_Other.ZFilteringType = _NearestFilteringType;
	_Other.XWrappingType = _BlackWrappingType;
	_Other.YWrappingType = _BlackWrappingType;
	_Other.FilteringTypeSet = false;
	_Other.WrappingTypeSet = false;
}

BFW::Rasterizer::TextureSDR::~TextureSDR()
{

}

void BFW::Rasterizer::TextureSDR::Data(const size_t _Level, const size_t _Width, const size_t _Height, const size_t _ChannelsCount, const uint8_t* _Data)
{
	if (_Level > TextureChain.GetSize() || !_Width || !_Height || !_ChannelsCount || _ChannelsCount > 4)
	{
		LastError = true;
		return;
	}

	if (_Level == TextureChain.GetSize())
	{
		TextureChain.EmplaceBack(Assets::BitMap());
	}

	if (!TextureChain[_Level].Create(_Width, _Height, _ChannelsCount))
	{
		TextureChain.Clear();
		LastError = true;
		return;
	}

	if (!_Data)
	{
		return;
	}

	for (size_t _PositionY = 0; _PositionY < _Height; _PositionY++)
	{
		for (size_t _PositionX = 0; _PositionX < _Width; _PositionX++)
		{
			for (size_t _Channel = 0; _Channel < _ChannelsCount; _Channel++)
			{
				TextureChain[_Level][_PositionY][_PositionX * _ChannelsCount + _Channel] = _Data[(_PositionX + _PositionY * _Width) * _ChannelsCount + _Channel];
			}
		}
	}
}

void BFW::Rasterizer::TextureSDR::FilteringTypes(const uint8_t _XFilteringType, const uint8_t _YFilteringType, const uint8_t _ZFilteringType)
{
	if (_XFilteringType > _LinearFilteringType || _YFilteringType > _LinearFilteringType || _ZFilteringType > _LinearFilteringType)
	{
		LastError = true;
		return;
	}

	XFilteringType = _XFilteringType;
	YFilteringType = _YFilteringType;
	ZFilteringType = _ZFilteringType;
	FilteringTypeSet = true;
}

void BFW::Rasterizer::TextureSDR::WrappingTypes(const uint8_t _XWrappingType, const uint8_t _YWrappingType)
{
	if (_XWrappingType > _MirrorWrappingType || _YWrappingType > _MirrorWrappingType)
	{
		LastError = true;
		return;
	}

	XWrappingType = _XWrappingType;
	YWrappingType = _YWrappingType;
	WrappingTypeSet = true;
}

const BFW::Math::Vec4 BFW::Rasterizer::TextureSDR::Sample(const Math::Vec2& _TextureCoords, const float _MipLevel) const
{
	if (!TextureChain.GetSize() || !FilteringTypeSet || !WrappingTypeSet ||
		((_TextureCoords.x < 0.0f || _TextureCoords.x > 1.0f) && XWrappingType == _BlackWrappingType) ||
		((_TextureCoords.y < 0.0f || _TextureCoords.y > 1.0f) && YWrappingType == _BlackWrappingType))
	{
		return Math::Vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	float _MipLevels[2] =
	{
		Math::Clamp(floorf(_MipLevel), 0.0f, (float)(TextureChain.GetSize() - 1)),
		Math::Clamp(floorf(_MipLevel) + 1.0f, 0.0f, (float)(TextureChain.GetSize() - 1))
	};

	Math::Vec2 _MipSizes[2] =
	{
		Math::Vec2((float)(TextureChain[(size_t)(floorf(_MipLevels[0] + 0.5f))].GetWidth()), (float)(TextureChain[(size_t)(floorf(_MipLevels[0] + 0.5f))].GetHeight())),
		Math::Vec2((float)(TextureChain[(size_t)(floorf(_MipLevels[1] + 0.5f))].GetWidth()), (float)(TextureChain[(size_t)(floorf(_MipLevels[1] + 0.5f))].GetHeight()))
	};

	Math::Vec2 _TexelSizes[2] =
	{
		Math::Vec2(1.0f / _MipSizes[0].x, 1.0f / _MipSizes[0].y),
		Math::Vec2(1.0f / _MipSizes[1].x, 1.0f / _MipSizes[1].y)
	};

	Math::Vec2 _LowTexelCoords[2] =
	{
		Math::Vec2((floorf(_TextureCoords.x * _MipSizes[0].x - 0.5f) + 0.5f) * _TexelSizes[0].x, (floorf(_TextureCoords.y * _MipSizes[0].y - 0.5f) + 0.5f) * _TexelSizes[0].y),
		Math::Vec2((floorf(_TextureCoords.x * _MipSizes[1].x - 0.5f) + 0.5f) * _TexelSizes[1].x, (floorf(_TextureCoords.y * _MipSizes[1].y - 0.5f) + 0.5f) * _TexelSizes[1].y)
	};

	Math::Vec4 _ColorXYZ[2][2][2];

	for (size_t _PositionZ = 0; _PositionZ < 2; _PositionZ++)
	{
		for (size_t _PositionY = 0; _PositionY < 2; _PositionY++)
		{
			for (size_t _PositionX = 0; _PositionX < 2; _PositionX++)
			{
				_ColorXYZ[_PositionX][_PositionY][_PositionZ] = SampleNearestSDR(TextureChain, WrapTextureCoords(Math::Vec2(_LowTexelCoords[_PositionZ].x + _TexelSizes[_PositionZ].x * (float)(_PositionX), _LowTexelCoords[_PositionZ].y + _TexelSizes[_PositionZ].y * (float)(_PositionY)), XWrappingType, YWrappingType), _MipLevels[_PositionZ]);
			}
		}
	}

	Math::Vec4 _ColorYZ[2][2];

	if (XFilteringType == _LinearFilteringType)
	{
		for (size_t _PositionZ = 0; _PositionZ < 2; _PositionZ++)
		{
			for (size_t _PositionY = 0; _PositionY < 2; _PositionY++)
			{
				_ColorYZ[_PositionY][_PositionZ] = Math::Vec4::Mix(_ColorXYZ[0][_PositionY][_PositionZ], _ColorXYZ[1][_PositionY][_PositionZ], (_TextureCoords.x - _LowTexelCoords[_PositionZ].x) / _TexelSizes[_PositionZ].x);
			}
		}
	}
	else
	{
		for (size_t _PositionZ = 0; _PositionZ < 2; _PositionZ++)
		{
			for (size_t _PositionY = 0; _PositionY < 2; _PositionY++)
			{
				_ColorYZ[_PositionY][_PositionZ] = (_TextureCoords.x - _LowTexelCoords[_PositionZ].x) / _TexelSizes[_PositionZ].x < 0.5f ? _ColorXYZ[0][_PositionY][_PositionZ] : _ColorXYZ[1][_PositionY][_PositionZ];
			}
		}
	}

	Math::Vec4 _ColorZ[2];

	if (YFilteringType == _LinearFilteringType)
	{
		for (size_t _PositionZ = 0; _PositionZ < 2; _PositionZ++)
		{
			_ColorZ[_PositionZ] = Math::Vec4::Mix(_ColorYZ[0][_PositionZ], _ColorYZ[1][_PositionZ], (_TextureCoords.y - _LowTexelCoords[_PositionZ].y) / _TexelSizes[_PositionZ].y);
		}
	}
	else
	{
		for (size_t _PositionZ = 0; _PositionZ < 2; _PositionZ++)
		{
			_ColorZ[_PositionZ] = (_TextureCoords.y - _LowTexelCoords[_PositionZ].y) / _TexelSizes[_PositionZ].y < 0.5f ? _ColorYZ[0][_PositionZ] : _ColorYZ[1][_PositionZ];
		}
	}

	Math::Vec4 _Color;

	if (ZFilteringType == _LinearFilteringType)
	{
		_Color = Math::Vec4::Mix(_ColorZ[0], _ColorZ[1], _MipLevel - floorf(_MipLevel));
	}
	else
	{
		_Color = _MipLevel - floorf(_MipLevel) < 0.5f ? _ColorZ[0] : _ColorZ[1];
	}

	return _Color;
}

const BFW::Math::Vec4 BFW::Rasterizer::TextureSDR::Sample(const Math::Vec3& _TextureCoords) const
{
	return Sample(Math::Vec2(_TextureCoords), _TextureCoords.z);
}

BFW::Rasterizer::TextureSDR& BFW::Rasterizer::TextureSDR::operator= (const TextureSDR& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	TextureChain = _Other.TextureChain;
	XFilteringType = _Other.XFilteringType;
	YFilteringType = _Other.YFilteringType;
	ZFilteringType = _Other.ZFilteringType;
	XWrappingType = _Other.XWrappingType;
	YWrappingType = _Other.YWrappingType;
	FilteringTypeSet = _Other.FilteringTypeSet;
	WrappingTypeSet = _Other.WrappingTypeSet;

	return *this;
}

BFW::Rasterizer::TextureSDR& BFW::Rasterizer::TextureSDR::operator= (TextureSDR&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	TextureChain = (Vector<Assets::BitMap>&&)(_Other.TextureChain);
	XFilteringType = _Other.XFilteringType;
	YFilteringType = _Other.YFilteringType;
	ZFilteringType = _Other.ZFilteringType;
	XWrappingType = _Other.XWrappingType;
	YWrappingType = _Other.YWrappingType;
	FilteringTypeSet = _Other.FilteringTypeSet;
	WrappingTypeSet = _Other.WrappingTypeSet;

	_Other.XFilteringType = _NearestFilteringType;
	_Other.YFilteringType = _NearestFilteringType;
	_Other.ZFilteringType = _NearestFilteringType;
	_Other.XWrappingType = _BlackWrappingType;
	_Other.YWrappingType = _BlackWrappingType;
	_Other.FilteringTypeSet = false;
	_Other.WrappingTypeSet = false;

	return *this;
}



BFW::Rasterizer::TextureHDR::TextureHDR() : TextureChain(), XFilteringType(_NearestFilteringType), YFilteringType(_NearestFilteringType), ZFilteringType(_NearestFilteringType), XWrappingType(_BlackWrappingType), YWrappingType(_BlackWrappingType), FilteringTypeSet(false), WrappingTypeSet(false)
{

}

BFW::Rasterizer::TextureHDR::TextureHDR(const TextureHDR& _Other) : TextureChain(_Other.TextureChain), XFilteringType(_Other.XFilteringType), YFilteringType(_Other.YFilteringType), ZFilteringType(_Other.ZFilteringType), XWrappingType(_Other.XWrappingType), YWrappingType(_Other.YWrappingType), FilteringTypeSet(_Other.FilteringTypeSet), WrappingTypeSet(_Other.WrappingTypeSet)
{

}

BFW::Rasterizer::TextureHDR::TextureHDR(TextureHDR&& _Other) noexcept : TextureChain((Vector<Assets::Hdr>&&)(_Other.TextureChain)), XFilteringType(_Other.XFilteringType), YFilteringType(_Other.YFilteringType), ZFilteringType(_Other.ZFilteringType), XWrappingType(_Other.XWrappingType), YWrappingType(_Other.YWrappingType), FilteringTypeSet(_Other.FilteringTypeSet), WrappingTypeSet(_Other.WrappingTypeSet)
{
	_Other.XFilteringType = _NearestFilteringType;
	_Other.YFilteringType = _NearestFilteringType;
	_Other.ZFilteringType = _NearestFilteringType;
	_Other.XWrappingType = _BlackWrappingType;
	_Other.YWrappingType = _BlackWrappingType;
	_Other.FilteringTypeSet = false;
	_Other.WrappingTypeSet = false;
}

BFW::Rasterizer::TextureHDR::~TextureHDR()
{

}

void BFW::Rasterizer::TextureHDR::Data(const size_t _Level, const size_t _Width, const size_t _Height, const size_t _ChannelsCount, const float* _Data)
{
	if (_Level > TextureChain.GetSize() || !_Width || !_Height || !_ChannelsCount || _ChannelsCount > 4)
	{
		LastError = true;
		return;
	}

	if (_Level == TextureChain.GetSize())
	{
		TextureChain.EmplaceBack(Assets::Hdr());
	}

	if (!TextureChain[_Level].Create(_Width, _Height, _ChannelsCount))
	{
		TextureChain.Clear();
		LastError = true;
		return;
	}

	if (!_Data)
	{
		return;
	}

	for (size_t _PositionY = 0; _PositionY < _Height; _PositionY++)
	{
		for (size_t _PositionX = 0; _PositionX < _Width; _PositionX++)
		{
			for (size_t _Channel = 0; _Channel < _ChannelsCount; _Channel++)
			{
				TextureChain[_Level][_PositionY][_PositionX * _ChannelsCount + _Channel] = _Data[(_PositionX + _PositionY * _Width) * _ChannelsCount + _Channel];
			}
		}
	}
}

void BFW::Rasterizer::TextureHDR::FilteringTypes(const uint8_t _XFilteringType, const uint8_t _YFilteringType, const uint8_t _ZFilteringType)
{
	if (_XFilteringType > _LinearFilteringType || _YFilteringType > _LinearFilteringType || _ZFilteringType > _LinearFilteringType)
	{
		LastError = true;
		return;
	}

	XFilteringType = _XFilteringType;
	YFilteringType = _YFilteringType;
	ZFilteringType = _ZFilteringType;
	FilteringTypeSet = true;
}

void BFW::Rasterizer::TextureHDR::WrappingTypes(const uint8_t _XWrappingType, const uint8_t _YWrappingType)
{
	if (_XWrappingType > _MirrorWrappingType || _YWrappingType > _MirrorWrappingType)
	{
		LastError = true;
		return;
	}

	XWrappingType = _XWrappingType;
	YWrappingType = _YWrappingType;
	WrappingTypeSet = true;
}

const BFW::Math::Vec4 BFW::Rasterizer::TextureHDR::Sample(const Math::Vec2& _TextureCoords, const float _MipLevel) const
{
	if (!TextureChain.GetSize() || !FilteringTypeSet || !WrappingTypeSet ||
		((_TextureCoords.x < 0.0f || _TextureCoords.x > 1.0f) && XWrappingType == _BlackWrappingType) ||
		((_TextureCoords.y < 0.0f || _TextureCoords.y > 1.0f) && YWrappingType == _BlackWrappingType))
	{
		return Math::Vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	float _MipLevels[2] =
	{
		Math::Clamp(floorf(_MipLevel), 0.0f, (float)(TextureChain.GetSize() - 1)),
		Math::Clamp(floorf(_MipLevel) + 1.0f, 0.0f, (float)(TextureChain.GetSize() - 1))
	};

	Math::Vec2 _MipSizes[2] =
	{
		Math::Vec2((float)(TextureChain[(size_t)(floorf(_MipLevels[0] + 0.5f))].GetWidth()), (float)(TextureChain[(size_t)(floorf(_MipLevels[0] + 0.5f))].GetHeight())),
		Math::Vec2((float)(TextureChain[(size_t)(floorf(_MipLevels[1] + 0.5f))].GetWidth()), (float)(TextureChain[(size_t)(floorf(_MipLevels[1] + 0.5f))].GetHeight()))
	};

	Math::Vec2 _TexelSizes[2] =
	{
		Math::Vec2(1.0f / _MipSizes[0].x, 1.0f / _MipSizes[0].y),
		Math::Vec2(1.0f / _MipSizes[1].x, 1.0f / _MipSizes[1].y)
	};

	Math::Vec2 _LowTexelCoords[2] =
	{
		Math::Vec2((floorf(_TextureCoords.x * _MipSizes[0].x - 0.5f) + 0.5f) * _TexelSizes[0].x, (floorf(_TextureCoords.y * _MipSizes[0].y - 0.5f) + 0.5f) * _TexelSizes[0].y),
		Math::Vec2((floorf(_TextureCoords.x * _MipSizes[1].x - 0.5f) + 0.5f) * _TexelSizes[1].x, (floorf(_TextureCoords.y * _MipSizes[1].y - 0.5f) + 0.5f) * _TexelSizes[1].y)
	};

	Math::Vec4 _ColorXYZ[2][2][2];

	for (size_t _PositionZ = 0; _PositionZ < 2; _PositionZ++)
	{
		for (size_t _PositionY = 0; _PositionY < 2; _PositionY++)
		{
			for (size_t _PositionX = 0; _PositionX < 2; _PositionX++)
			{
				_ColorXYZ[_PositionX][_PositionY][_PositionZ] = SampleNearestHDR(TextureChain, WrapTextureCoords(Math::Vec2(_LowTexelCoords[_PositionZ].x + _TexelSizes[_PositionZ].x * (float)(_PositionX), _LowTexelCoords[_PositionZ].y + _TexelSizes[_PositionZ].y * (float)(_PositionY)), XWrappingType, YWrappingType), _MipLevels[_PositionZ]);
			}
		}
	}

	Math::Vec4 _ColorYZ[2][2];

	if (XFilteringType == _LinearFilteringType)
	{
		for (size_t _PositionZ = 0; _PositionZ < 2; _PositionZ++)
		{
			for (size_t _PositionY = 0; _PositionY < 2; _PositionY++)
			{
				_ColorYZ[_PositionY][_PositionZ] = Math::Vec4::Mix(_ColorXYZ[0][_PositionY][_PositionZ], _ColorXYZ[1][_PositionY][_PositionZ], (_TextureCoords.x - _LowTexelCoords[_PositionZ].x) / _TexelSizes[_PositionZ].x);
			}
		}
	}
	else
	{
		for (size_t _PositionZ = 0; _PositionZ < 2; _PositionZ++)
		{
			for (size_t _PositionY = 0; _PositionY < 2; _PositionY++)
			{
				_ColorYZ[_PositionY][_PositionZ] = (_TextureCoords.x - _LowTexelCoords[_PositionZ].x) / _TexelSizes[_PositionZ].x < 0.5f ? _ColorXYZ[0][_PositionY][_PositionZ] : _ColorXYZ[1][_PositionY][_PositionZ];
			}
		}
	}

	Math::Vec4 _ColorZ[2];

	if (YFilteringType == _LinearFilteringType)
	{
		for (size_t _PositionZ = 0; _PositionZ < 2; _PositionZ++)
		{
			_ColorZ[_PositionZ] = Math::Vec4::Mix(_ColorYZ[0][_PositionZ], _ColorYZ[1][_PositionZ], (_TextureCoords.y - _LowTexelCoords[_PositionZ].y) / _TexelSizes[_PositionZ].y);
		}
	}
	else
	{
		for (size_t _PositionZ = 0; _PositionZ < 2; _PositionZ++)
		{
			_ColorZ[_PositionZ] = (_TextureCoords.y - _LowTexelCoords[_PositionZ].y) / _TexelSizes[_PositionZ].y < 0.5f ? _ColorYZ[0][_PositionZ] : _ColorYZ[1][_PositionZ];
		}
	}

	Math::Vec4 _Color;

	if (ZFilteringType == _LinearFilteringType)
	{
		_Color = Math::Vec4::Mix(_ColorZ[0], _ColorZ[1], _MipLevel - floorf(_MipLevel));
	}
	else
	{
		_Color = _MipLevel - floorf(_MipLevel) < 0.5f ? _ColorZ[0] : _ColorZ[1];
	}

	return _Color;
}

const BFW::Math::Vec4 BFW::Rasterizer::TextureHDR::Sample(const Math::Vec3& _TextureCoords) const
{
	return Sample(Math::Vec2(_TextureCoords), _TextureCoords.z);
}

BFW::Rasterizer::TextureHDR& BFW::Rasterizer::TextureHDR::operator= (const TextureHDR& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	TextureChain = _Other.TextureChain;
	XFilteringType = _Other.XFilteringType;
	YFilteringType = _Other.YFilteringType;
	ZFilteringType = _Other.ZFilteringType;
	XWrappingType = _Other.XWrappingType;
	YWrappingType = _Other.YWrappingType;
	FilteringTypeSet = _Other.FilteringTypeSet;
	WrappingTypeSet = _Other.WrappingTypeSet;

	return *this;
}

BFW::Rasterizer::TextureHDR& BFW::Rasterizer::TextureHDR::operator= (TextureHDR&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	TextureChain = (Vector<Assets::Hdr>&&)(_Other.TextureChain);
	XFilteringType = _Other.XFilteringType;
	YFilteringType = _Other.YFilteringType;
	ZFilteringType = _Other.ZFilteringType;
	XWrappingType = _Other.XWrappingType;
	YWrappingType = _Other.YWrappingType;
	FilteringTypeSet = _Other.FilteringTypeSet;
	WrappingTypeSet = _Other.WrappingTypeSet;

	_Other.XFilteringType = _NearestFilteringType;
	_Other.YFilteringType = _NearestFilteringType;
	_Other.ZFilteringType = _NearestFilteringType;
	_Other.XWrappingType = _BlackWrappingType;
	_Other.YWrappingType = _BlackWrappingType;
	_Other.FilteringTypeSet = false;
	_Other.WrappingTypeSet = false;

	return *this;
}



BFW::Rasterizer::CubeTextureSDR::CubeTextureSDR() : Textures(6)
{

}

BFW::Rasterizer::CubeTextureSDR::CubeTextureSDR(const CubeTextureSDR& _Other) : Textures(_Other.Textures)
{

}

BFW::Rasterizer::CubeTextureSDR::CubeTextureSDR(CubeTextureSDR&& _Other) noexcept : Textures((Vector<TextureSDR>&&)(_Other.Textures))
{
	_Other.Textures = Vector<TextureSDR>(6);
}

BFW::Rasterizer::CubeTextureSDR::~CubeTextureSDR()
{

}

void BFW::Rasterizer::CubeTextureSDR::Data(const size_t _Face, const size_t _Level, const size_t _Width, const size_t _Height, const size_t _ChannelsCount, const uint8_t* _Data)
{
	if (_Face > _BackCubeMapFace)
	{
		LastError = true;
		return;
	}

	Textures[_Face].Data(_Level, _Width, _Height, _ChannelsCount, _Data);
}

void BFW::Rasterizer::CubeTextureSDR::FilteringTypes(const uint8_t _XFilteringType, const uint8_t _YFilteringType, const uint8_t _ZFilteringType)
{
	for (size_t _Index = 0; _Index < 6; _Index++)
	{
		Textures[_Index].FilteringTypes(_XFilteringType, _YFilteringType, _ZFilteringType);
		Textures[_Index].WrappingTypes(_ClampWrappingType, _ClampWrappingType);
	}
}

const BFW::Math::Vec4 BFW::Rasterizer::CubeTextureSDR::Sample(const Math::Vec3& _Direction, const float _MipLevel) const
{
	if (_Direction == Math::Vec3(0.0f, 0.0f, 0.0f))
	{
		return Math::Vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	for (size_t _Index = 0; _Index < 6; _Index++)
	{
		if (!Textures[_Index].TextureChain.GetSize() || !Textures[_Index].FilteringTypeSet)
		{
			return Math::Vec4(0.0f, 0.0f, 0.0f, 1.0f);
		}
	}

	size_t _Face = _RightCubeMapFace;
	Math::Vec2 _UV;

	Math::Vec3 _AbsVec = Math::Vec3(fabs(_Direction.x), fabs(_Direction.y), fabs(_Direction.z));

	if (_AbsVec.x >= _AbsVec.y && _AbsVec.x >= _AbsVec.z)
	{
		if (_Direction.x > 0.0f)
		{
			_Face = _RightCubeMapFace;
			_UV = Math::Vec2(-_Direction.z / _AbsVec.x, -_Direction.y / _AbsVec.x);
		}
		else
		{
			_Face = _LeftCubeMapFace;
			_UV = Math::Vec2(_Direction.z / _AbsVec.x, -_Direction.y / _AbsVec.x);
		}
	}
	else if (_AbsVec.y >= _AbsVec.x && _AbsVec.y >= _AbsVec.z)
	{
		if (_Direction.y > 0.0f)
		{
			_Face = _TopCubeMapFace;
			_UV = Math::Vec2(_Direction.x / _AbsVec.y, _Direction.z / _AbsVec.y);
		}
		else
		{
			_Face = _BottomCubeMapFace;
			_UV = Math::Vec2(_Direction.x / _AbsVec.y, -_Direction.z / _AbsVec.y);
		}
	}
	else
	{
		if (_Direction.z > 0.0f)
		{
			_Face = _FrontCubeMapFace;
			_UV = Math::Vec2(_Direction.x / _AbsVec.z, -_Direction.y / _AbsVec.z);
		}
		else
		{
			_Face = _BackCubeMapFace;
			_UV = Math::Vec2(-_Direction.x / _AbsVec.z, -_Direction.y / _AbsVec.z);
		}
	}

	_UV *= 0.5f;
	_UV += 0.5f;

	return Textures[_Face].Sample(_UV, _MipLevel);
}

const BFW::Math::Vec4 BFW::Rasterizer::CubeTextureSDR::Sample(const Math::Vec4& _Direction) const
{
	return Sample(Math::Vec3(_Direction), _Direction.w);
}

BFW::Rasterizer::CubeTextureSDR& BFW::Rasterizer::CubeTextureSDR::operator= (const CubeTextureSDR& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Textures = _Other.Textures;

	return *this;
}

BFW::Rasterizer::CubeTextureSDR& BFW::Rasterizer::CubeTextureSDR::operator= (CubeTextureSDR&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Textures = (Vector<TextureSDR>&&)(_Other.Textures);

	_Other.Textures = Vector<TextureSDR>(6);

	return *this;
}



BFW::Rasterizer::CubeTextureHDR::CubeTextureHDR() : Textures(6)
{

}

BFW::Rasterizer::CubeTextureHDR::CubeTextureHDR(const CubeTextureHDR& _Other) : Textures(_Other.Textures)
{

}

BFW::Rasterizer::CubeTextureHDR::CubeTextureHDR(CubeTextureHDR&& _Other) noexcept : Textures((Vector<TextureHDR>&&)(_Other.Textures))
{
	_Other.Textures = Vector<TextureHDR>(6);
}

BFW::Rasterizer::CubeTextureHDR::~CubeTextureHDR()
{

}

void BFW::Rasterizer::CubeTextureHDR::Data(const size_t _Face, const size_t _Level, const size_t _Width, const size_t _Height, const size_t _ChannelsCount, const float* _Data)
{
	if (_Face > _BackCubeMapFace)
	{
		LastError = true;
		return;
	}

	Textures[_Face].Data(_Level, _Width, _Height, _ChannelsCount, _Data);
}

void BFW::Rasterizer::CubeTextureHDR::FilteringTypes(const uint8_t _XFilteringType, const uint8_t _YFilteringType, const uint8_t _ZFilteringType)
{
	for (size_t _Index = 0; _Index < 6; _Index++)
	{
		Textures[_Index].FilteringTypes(_XFilteringType, _YFilteringType, _ZFilteringType);
		Textures[_Index].WrappingTypes(_ClampWrappingType, _ClampWrappingType);
	}
}

const BFW::Math::Vec4 BFW::Rasterizer::CubeTextureHDR::Sample(const Math::Vec3& _Direction, const float _MipLevel) const
{
	if (_Direction == Math::Vec3(0.0f, 0.0f, 0.0f))
	{
		return Math::Vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	for (size_t _Index = 0; _Index < 6; _Index++)
	{
		if (!Textures[_Index].TextureChain.GetSize() || !Textures[_Index].FilteringTypeSet)
		{
			return Math::Vec4(0.0f, 0.0f, 0.0f, 1.0f);
		}
	}

	size_t _Face = _RightCubeMapFace;
	Math::Vec2 _UV;

	Math::Vec3 _AbsVec = Math::Vec3(fabs(_Direction.x), fabs(_Direction.y), fabs(_Direction.z));

	if (_AbsVec.x >= _AbsVec.y && _AbsVec.x >= _AbsVec.z)
	{
		if (_Direction.x > 0.0f)
		{
			_Face = _RightCubeMapFace;
			_UV = Math::Vec2(-_Direction.z / _AbsVec.x, -_Direction.y / _AbsVec.x);
		}
		else
		{
			_Face = _LeftCubeMapFace;
			_UV = Math::Vec2(_Direction.z / _AbsVec.x, -_Direction.y / _AbsVec.x);
		}
	}
	else if (_AbsVec.y >= _AbsVec.x && _AbsVec.y >= _AbsVec.z)
	{
		if (_Direction.y > 0.0f)
		{
			_Face = _TopCubeMapFace;
			_UV = Math::Vec2(_Direction.x / _AbsVec.y, _Direction.z / _AbsVec.y);
		}
		else
		{
			_Face = _BottomCubeMapFace;
			_UV = Math::Vec2(_Direction.x / _AbsVec.y, -_Direction.z / _AbsVec.y);
		}
	}
	else
	{
		if (_Direction.z > 0.0f)
		{
			_Face = _FrontCubeMapFace;
			_UV = Math::Vec2(_Direction.x / _AbsVec.z, -_Direction.y / _AbsVec.z);
		}
		else
		{
			_Face = _BackCubeMapFace;
			_UV = Math::Vec2(-_Direction.x / _AbsVec.z, -_Direction.y / _AbsVec.z);
		}
	}

	_UV *= 0.5f;
	_UV += 0.5f;

	return Textures[_Face].Sample(_UV, _MipLevel);
}

const BFW::Math::Vec4 BFW::Rasterizer::CubeTextureHDR::Sample(const Math::Vec4& _Direction) const
{
	return Sample(Math::Vec3(_Direction), _Direction.w);
}

BFW::Rasterizer::CubeTextureHDR& BFW::Rasterizer::CubeTextureHDR::operator= (const CubeTextureHDR& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Textures = _Other.Textures;

	return *this;
}

BFW::Rasterizer::CubeTextureHDR& BFW::Rasterizer::CubeTextureHDR::operator= (CubeTextureHDR&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Textures = (Vector<TextureHDR>&&)(_Other.Textures);

	_Other.Textures = Vector<TextureHDR>(6);

	return *this;
}



BFW::Rasterizer::FrameBuffer::FrameBuffer() : ColorSDR(nullptr), ColorHDR(nullptr), Depth(nullptr)
{

}

BFW::Rasterizer::FrameBuffer::FrameBuffer(const FrameBuffer& _Other) : ColorSDR(_Other.ColorSDR), ColorHDR(_Other.ColorHDR), Depth(_Other.Depth)
{

}

BFW::Rasterizer::FrameBuffer::FrameBuffer(FrameBuffer&& _Other) noexcept : ColorSDR(_Other.ColorSDR), ColorHDR(_Other.ColorHDR), Depth(_Other.Depth)
{
	_Other.ColorSDR = nullptr;
	_Other.ColorHDR = nullptr;
	_Other.Depth = nullptr;
}

BFW::Rasterizer::FrameBuffer::~FrameBuffer()
{

}

void BFW::Rasterizer::FrameBuffer::AttachColorSDR(TextureSDR& _Texture, const size_t _Level)
{
	if (_Level >= _Texture.TextureChain.GetSize())
	{
		LastError = true;
		return;
	}

	ColorSDR = &_Texture.TextureChain[_Level];
	ColorHDR = nullptr;
}

void BFW::Rasterizer::FrameBuffer::AttachColorHDR(TextureHDR& _Texture, const size_t _Level)
{
	if (_Level >= _Texture.TextureChain.GetSize())
	{
		LastError = true;
		return;
	}

	ColorSDR = nullptr;
	ColorHDR = &_Texture.TextureChain[_Level];
}

void BFW::Rasterizer::FrameBuffer::AttachColorCubeSDR(CubeTextureSDR& _Texture, const size_t _Face, const size_t _Level)
{
	if (_Face > _BackCubeMapFace || _Level >= _Texture.Textures[_Face].TextureChain.GetSize())
	{
		LastError = true;
		return;
	}

	ColorSDR = &_Texture.Textures[_Face].TextureChain[_Level];
	ColorHDR = nullptr;
}

void BFW::Rasterizer::FrameBuffer::AttachColorCubeHDR(CubeTextureHDR& _Texture, const size_t _Face, const size_t _Level)
{
	if (_Face > _BackCubeMapFace || _Level >= _Texture.Textures[_Face].TextureChain.GetSize())
	{
		LastError = true;
		return;
	}

	ColorSDR = nullptr;
	ColorHDR = &_Texture.Textures[_Face].TextureChain[_Level];
}

void BFW::Rasterizer::FrameBuffer::AttachDepth(TextureHDR& _Texture, const size_t _Level)
{
	if (_Level >= _Texture.TextureChain.GetSize() || _Texture.TextureChain[_Level].GetChannelsCount() != 1)
	{
		LastError = true;
		return;
	}

	Depth = &_Texture.TextureChain[_Level];
}

void BFW::Rasterizer::FrameBuffer::DetachColor()
{
	ColorSDR = nullptr;
	ColorHDR = nullptr;
}

void BFW::Rasterizer::FrameBuffer::DetachDepth()
{
	Depth = nullptr;
}

const bool BFW::Rasterizer::FrameBuffer::IsValid() const
{
	return ColorSDR != nullptr || ColorHDR != nullptr;
}

void BFW::Rasterizer::FrameBuffer::ReadSDR(const intptr_t _PositionX, const intptr_t _PositionY, const size_t _Width, const size_t _Height, const size_t _ChannelsCount, uint8_t* _Data)
{
	if (!_Width || !_Height || !_ChannelsCount || _ChannelsCount > 4 || !_Data || (!ColorSDR && !ColorHDR))
	{
		LastError = true;
		return;
	}

	for (size_t _ForPositionY = 0; _ForPositionY < _Height; _ForPositionY++)
	{
		for (size_t _ForPositionX = 0; _ForPositionX < _Width; _ForPositionX++)
		{
			for (size_t _Channel = 0; _Channel < _ChannelsCount; _Channel++)
			{
				_Data[(_ForPositionX + _ForPositionY * _Width) * _ChannelsCount + _Channel] = 0;
			}

			if (_ChannelsCount == 4)
			{
				_Data[(_ForPositionX + _ForPositionY * _Width) * _ChannelsCount + 3] = 255;
			}
		}
	}

	if (ColorSDR)
	{
		for (size_t _ForPositionY = _PositionY * (_PositionY >= 0); _ForPositionY < ((intptr_t)(_Height) + _PositionY < (intptr_t)(ColorSDR->GetHeight()) ? _Height + _PositionY : ColorSDR->GetHeight()); _ForPositionY++)
		{
			for (size_t _ForPositionX = _PositionX * (_PositionX >= 0); _ForPositionX < ((intptr_t)(_Width) + _PositionX < (intptr_t)(ColorSDR->GetWidth()) ? _Width + _PositionX : ColorSDR->GetWidth()); _ForPositionX++)
			{
				for (size_t _Channel = 0; _Channel < (_ChannelsCount < ColorSDR->GetChannelsCount() ? _ChannelsCount : ColorSDR->GetChannelsCount()); _Channel++)
				{
					_Data[((_ForPositionX - _PositionX) + (_ForPositionY - _PositionY) * _Width) * _ChannelsCount + _Channel] = (*ColorSDR)[_ForPositionY][_ForPositionX * ColorSDR->GetChannelsCount() + _Channel];
				}
			}
		}

		return;
	}

	for (size_t _ForPositionY = _PositionY * (_PositionY >= 0); _ForPositionY < ((intptr_t)(_Height) + _PositionY < (intptr_t)(ColorHDR->GetHeight()) ? _Height + _PositionY : ColorHDR->GetHeight()); _ForPositionY++)
	{
		for (size_t _ForPositionX = _PositionX * (_PositionX >= 0); _ForPositionX < ((intptr_t)(_Width) + _PositionX < (intptr_t)(ColorHDR->GetWidth()) ? _Width + _PositionX : ColorHDR->GetWidth()); _ForPositionX++)
		{
			for (size_t _Channel = 0; _Channel < (_ChannelsCount < ColorHDR->GetChannelsCount() ? _ChannelsCount : ColorHDR->GetChannelsCount()); _Channel++)
			{
				_Data[((_ForPositionX - _PositionX) + (_ForPositionY - _PositionY) * _Width) * _ChannelsCount + _Channel] =
					(uint8_t)
					(
						Math::Clamp
						(
							(*ColorHDR)[_ForPositionY][_ForPositionX * ColorHDR->GetChannelsCount() + _Channel],
							0.0f,
							1.0f
						) *
						255.0f
					);
			}
		}
	}
}

void BFW::Rasterizer::FrameBuffer::ReadHDR(const intptr_t _PositionX, const intptr_t _PositionY, const size_t _Width, const size_t _Height, const size_t _ChannelsCount, float* _Data)
{
	if (!_Width || !_Height || !_ChannelsCount || _ChannelsCount > 4 || !_Data || (!ColorSDR && !ColorHDR))
	{
		LastError = true;
		return;
	}

	for (size_t _ForPositionY = 0; _ForPositionY < _Height; _ForPositionY++)
	{
		for (size_t _ForPositionX = 0; _ForPositionX < _Width; _ForPositionX++)
		{
			for (size_t _Channel = 0; _Channel < _ChannelsCount; _Channel++)
			{
				_Data[(_ForPositionX + _ForPositionY * _Width) * _ChannelsCount + _Channel] = 0.0f;
			}

			if (_ChannelsCount == 4)
			{
				_Data[(_ForPositionX + _ForPositionY * _Width) * _ChannelsCount + 3] = 1.0f;
			}
		}
	}

	if (ColorSDR)
	{
		for (size_t _ForPositionY = _PositionY * (_PositionY >= 0); _ForPositionY < ((intptr_t)(_Height) + _PositionY < (intptr_t)(ColorSDR->GetHeight()) ? _Height + _PositionY : ColorSDR->GetHeight()); _ForPositionY++)
		{
			for (size_t _ForPositionX = _PositionX * (_PositionX >= 0); _ForPositionX < ((intptr_t)(_Width) + _PositionX < (intptr_t)(ColorSDR->GetWidth()) ? _Width + _PositionX : ColorSDR->GetWidth()); _ForPositionX++)
			{
				for (size_t _Channel = 0; _Channel < (_ChannelsCount < ColorSDR->GetChannelsCount() ? _ChannelsCount : ColorSDR->GetChannelsCount()); _Channel++)
				{
					_Data[((_ForPositionX - _PositionX) + (_ForPositionY - _PositionY) * _Width) * _ChannelsCount + _Channel] = (float)((*ColorSDR)[_ForPositionY][_ForPositionX * ColorSDR->GetChannelsCount() + _Channel]) / 255.0f;
				}
			}
		}

		return;
	}

	for (size_t _ForPositionY = _PositionY * (_PositionY >= 0); _ForPositionY < ((intptr_t)(_Height) + _PositionY < (intptr_t)(ColorHDR->GetHeight()) ? _Height + _PositionY : ColorHDR->GetHeight()); _ForPositionY++)
	{
		for (size_t _ForPositionX = _PositionX * (_PositionX >= 0); _ForPositionX < ((intptr_t)(_Width) + _PositionX < (intptr_t)(ColorHDR->GetWidth()) ? _Width + _PositionX : ColorHDR->GetWidth()); _ForPositionX++)
		{
			for (size_t _Channel = 0; _Channel < (_ChannelsCount < ColorHDR->GetChannelsCount() ? _ChannelsCount : ColorHDR->GetChannelsCount()); _Channel++)
			{
				_Data[((_ForPositionX - _PositionX) + (_ForPositionY - _PositionY) * _Width) * _ChannelsCount + _Channel] = (*ColorHDR)[_ForPositionY][_ForPositionX * ColorHDR->GetChannelsCount() + _Channel];
			}
		}
	}
}

void BFW::Rasterizer::FrameBuffer::ReadDepth(const intptr_t _PositionX, const intptr_t _PositionY, const size_t _Width, const size_t _Height, float* _Data)
{
	if (!_Width || !_Height || !_Data || !Depth)
	{
		LastError = true;
		return;
	}

	for (size_t _ForPositionY = 0; _ForPositionY < _Height; _ForPositionY++)
	{
		for (size_t _ForPositionX = 0; _ForPositionX < _Width; _ForPositionX++)
		{
			_Data[_ForPositionX + _ForPositionY * _Width] = 0.0f;
		}
	}

	for (size_t _ForPositionY = _PositionY * (_PositionY >= 0); _ForPositionY < ((intptr_t)(_Height) + _PositionY < (intptr_t)(Depth->GetHeight()) ? _Height + _PositionY : Depth->GetHeight()); _ForPositionY++)
	{
		for (size_t _ForPositionX = _PositionX * (_PositionX >= 0); _ForPositionX < ((intptr_t)(_Width) + _PositionX < (intptr_t)(Depth->GetWidth()) ? _Width + _PositionX : Depth->GetWidth()); _ForPositionX++)
		{
			_Data[(_ForPositionX - _PositionX) + (_ForPositionY - _PositionY) * _Width] = (*Depth)[_ForPositionY][_ForPositionX];
		}
	}
}

BFW::Rasterizer::FrameBuffer& BFW::Rasterizer::FrameBuffer::operator= (const FrameBuffer& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	ColorSDR = _Other.ColorSDR;
	ColorHDR = _Other.ColorHDR;
	Depth = _Other.Depth;

	return *this;
}

BFW::Rasterizer::FrameBuffer& BFW::Rasterizer::FrameBuffer::operator= (FrameBuffer&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	ColorSDR = _Other.ColorSDR;
	ColorHDR = _Other.ColorHDR;
	Depth = _Other.Depth;

	_Other.ColorSDR = nullptr;
	_Other.ColorHDR = nullptr;
	_Other.Depth = nullptr;

	return *this;
}



void BFW::Rasterizer::SetLastError()
{
	LastError = true;
}

const bool BFW::Rasterizer::GetLastError()
{
	if (LastError)
	{
		LastError = false;
		return true;
	}

	return false;
}
