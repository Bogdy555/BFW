#include "../Headers/BFW.hpp"



static thread_local bool LastErrorValue = false;



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
		LastErrorValue = true;
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
		LastErrorValue = true;
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



BFW::Rasterizer::VertexArrayEntry::VertexArrayEntry() : Count(0), DataType(_FloatDataType), Normalize(false), Stride(0), Offset(0)
{

}

BFW::Rasterizer::VertexArrayEntry::VertexArrayEntry(const size_t _Count, const uint8_t _DataType, const bool _Normalize, const size_t _Stride, const size_t _Offset) : Count(_Count), DataType(_DataType), Normalize(_Normalize), Stride(_Stride), Offset(_Offset)
{

}

BFW::Rasterizer::VertexArrayEntry::VertexArrayEntry(VertexArrayEntry&& _Other) noexcept : Count(_Other.Count), DataType(_Other.DataType), Normalize(_Other.Normalize), Stride(_Other.Stride), Offset(_Other.Offset)
{
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

	Count = _Other.Count;
	DataType = _Other.DataType;
	Normalize = _Other.Normalize;
	Stride = _Other.Stride;
	Offset = _Other.Offset;

	_Other.Count = 0;
	_Other.DataType = _FloatDataType;
	_Other.Normalize = false;
	_Other.Stride = 0;
	_Other.Offset = 0;

	return *this;
}



BFW::Rasterizer::VertexArray::VertexArray() : EnabledEntries(), Entries()
{

}

BFW::Rasterizer::VertexArray::VertexArray(const VertexArray& _Other) : EnabledEntries(_Other.EnabledEntries), Entries(_Other.Entries)
{

}

BFW::Rasterizer::VertexArray::VertexArray(VertexArray&& _Other) noexcept : EnabledEntries((Vector<bool>&&)(_Other.EnabledEntries)), Entries((Vector<VertexArrayEntry>&&)(_Other.Entries))
{

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
	Entries[_Index] = VertexArrayEntry();
}

void BFW::Rasterizer::VertexArray::DisableAttribute(const size_t _Index)
{
	if (_Index >= EnabledEntries.GetSize())
	{
		LastErrorValue = true;
		return;
	}

	EnabledEntries[_Index] = false;
	Entries[_Index] = VertexArrayEntry();

	while (EnabledEntries.GetSize() && !EnabledEntries[EnabledEntries.GetSize() - 1])
	{
		EnabledEntries.Erase(EnabledEntries.GetSize() - 1);
		Entries.Erase(Entries.GetSize() - 1);
	}
}

void BFW::Rasterizer::VertexArray::AttributePointer(const size_t _Index, const VertexArrayEntry& _Entry)
{
	if (_Index >= EnabledEntries.GetSize() || !EnabledEntries[_Index])
	{
		LastErrorValue = true;
		return;
	}

	Entries[_Index] = _Entry;
}

BFW::Rasterizer::VertexArray& BFW::Rasterizer::VertexArray::operator= (const VertexArray& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

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

	EnabledEntries = (Vector<bool>&&)(_Other.EnabledEntries);
	Entries = (Vector<VertexArrayEntry>&&)(_Other.Entries);

	return *this;
}



BFW::Rasterizer::Program::Program() : VertexShader(nullptr), GeometryShader(nullptr), FragmentShader(nullptr)
{

}

BFW::Rasterizer::Program::Program(const VertexShaderFnc& _VertexShader, const GeometryShaderFnc& _GeometryShader, const FragmentShaderFnc& _FragmentShader) : VertexShader(_VertexShader), GeometryShader(_GeometryShader), FragmentShader(_FragmentShader)
{

}

BFW::Rasterizer::Program::Program(Program&& _Other) noexcept : VertexShader(_Other.VertexShader), GeometryShader(_Other.GeometryShader), FragmentShader(_Other.FragmentShader)
{
	_Other.VertexShader = nullptr;
	_Other.GeometryShader = nullptr;
	_Other.FragmentShader = nullptr;
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

	_Other.VertexShader = nullptr;
	_Other.GeometryShader = nullptr;
	_Other.FragmentShader = nullptr;

	return *this;
}



const bool LastError()
{
	if (LastErrorValue)
	{
		LastErrorValue = false;
		return true;
	}

	return false;
}
