#include "../Headers/BFW.hpp"



BFW::Assets::TriangleVertexData::TriangleVertexData() : Position(), Color(), Normal(), Tangent(), TextureCoords()
{

}

BFW::Assets::TriangleVertexData::TriangleVertexData(const Math::Vec4& _Position, const Math::Vec4& _Color, const Math::Vec3& _Normal, const Math::Vec3& _Tangent, const Math::Vec3& _TextureCoords) : Position(_Position), Color(_Color), Normal(_Normal), Tangent(_Tangent), TextureCoords(_TextureCoords)
{

}

BFW::Assets::TriangleVertexData::TriangleVertexData(TriangleVertexData&& _Other) noexcept : Position((Math::Vec4&&)(_Other.Position)), Color((Math::Vec4&&)(_Other.Color)), Normal((Math::Vec3&&)(_Other.Normal)), Tangent((Math::Vec3&&)(_Other.Tangent)), TextureCoords((Math::Vec3&&)(_Other.TextureCoords))
{

}

BFW::Assets::TriangleVertexData::~TriangleVertexData()
{

}

BFW::Assets::TriangleVertexData& BFW::Assets::TriangleVertexData::operator= (TriangleVertexData&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Position = (Math::Vec4&&)(_Other.Position);
	Color = (Math::Vec4&&)(_Other.Color);
	Normal = (Math::Vec3&&)(_Other.Normal);
	Tangent = (Math::Vec3&&)(_Other.Tangent);
	TextureCoords = (Math::Vec3&&)(_Other.TextureCoords);

	return *this;
}



BFW::Assets::TriangleIndexData::TriangleIndexData() : IndexA(0), IndexB(0), IndexC(0)
{

}

BFW::Assets::TriangleIndexData::TriangleIndexData(const uint32_t _IndexA, const uint32_t _IndexB, const uint32_t _IndexC) : IndexA(_IndexA), IndexB(_IndexB), IndexC(_IndexC)
{

}

BFW::Assets::TriangleIndexData::TriangleIndexData(TriangleIndexData&& _Other) noexcept : IndexA(_Other.IndexA), IndexB(_Other.IndexB), IndexC(_Other.IndexC)
{
	_Other.IndexA = 0;
	_Other.IndexB = 0;
	_Other.IndexC = 0;
}

BFW::Assets::TriangleIndexData::~TriangleIndexData()
{

}

BFW::Assets::TriangleIndexData& BFW::Assets::TriangleIndexData::operator= (TriangleIndexData&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	IndexA = _Other.IndexA;
	IndexB = _Other.IndexB;
	IndexC = _Other.IndexC;

	_Other.IndexA = 0;
	_Other.IndexB = 0;
	_Other.IndexC = 0;

	return *this;
}



BFW::Assets::LineVertexData::LineVertexData() : Position(), Color(), TextureCoords()
{

}

BFW::Assets::LineVertexData::LineVertexData(const Math::Vec4& _Position, const Math::Vec4& _Color, const Math::Vec3& _TextureCoords) : Position(_Position), Color(_Color), TextureCoords(_TextureCoords)
{

}

BFW::Assets::LineVertexData::LineVertexData(LineVertexData&& _Other) noexcept : Position((Math::Vec4&&)(_Other.Position)), Color((Math::Vec4&&)(_Other.Color)), TextureCoords((Math::Vec3&&)(_Other.TextureCoords))
{

}

BFW::Assets::LineVertexData::~LineVertexData()
{

}

BFW::Assets::LineVertexData& BFW::Assets::LineVertexData::operator= (LineVertexData&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Position = (Math::Vec4&&)(_Other.Position);
	Color = (Math::Vec4&&)(_Other.Color);
	TextureCoords = (Math::Vec3&&)(_Other.TextureCoords);

	return *this;
}



BFW::Assets::LineIndexData::LineIndexData() : IndexA(0), IndexB(0)
{

}

BFW::Assets::LineIndexData::LineIndexData(const uint32_t _IndexA, const uint32_t _IndexB) : IndexA(_IndexA), IndexB(_IndexB)
{

}

BFW::Assets::LineIndexData::LineIndexData(LineIndexData&& _Other) noexcept : IndexA(_Other.IndexA), IndexB(_Other.IndexB)
{
	_Other.IndexA = 0;
	_Other.IndexB = 0;
}

BFW::Assets::LineIndexData::~LineIndexData()
{

}

BFW::Assets::LineIndexData& BFW::Assets::LineIndexData::operator= (LineIndexData&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	IndexA = _Other.IndexA;
	IndexB = _Other.IndexB;

	_Other.IndexA = 0;
	_Other.IndexB = 0;

	return *this;
}



BFW::Assets::Mesh::Mesh() : Name(BFW_STRING_PREFIX("")), MaterialLib(BFW_STRING_PREFIX("")), MaterialName(BFW_STRING_PREFIX("")), TriangleVBO(), TriangleIBO(), LineVBO(), LineIBO()
{

}

BFW::Assets::Mesh::Mesh(const Mesh& _Other) : Name(_Other.Name), MaterialLib(_Other.MaterialLib), MaterialName(_Other.MaterialName), TriangleVBO(_Other.TriangleVBO), TriangleIBO(_Other.TriangleIBO), LineVBO(_Other.LineVBO), LineIBO(_Other.LineIBO)
{

}

BFW::Assets::Mesh::Mesh(Mesh&& _Other) noexcept : Name(_Other.Name), MaterialLib(_Other.MaterialLib), MaterialName(_Other.MaterialName), TriangleVBO((Vector<TriangleVertexData>&&)(_Other.TriangleVBO)), TriangleIBO((Vector<TriangleIndexData>&&)(_Other.TriangleIBO)), LineVBO((Vector<LineVertexData>&&)(_Other.LineVBO)), LineIBO((Vector<LineIndexData>&&)(_Other.LineIBO))
{
	_Other.Name = BFW_STRING_PREFIX("");
	_Other.MaterialLib = BFW_STRING_PREFIX("");
	_Other.MaterialName = BFW_STRING_PREFIX("");
}

BFW::Assets::Mesh::~Mesh()
{

}

void BFW::Assets::Mesh::GenerateUnitQuad()
{
	TriangleVBO.Clear();
	TriangleIBO.Clear();
	LineVBO.Clear();
	LineIBO.Clear();

	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(-0.5f, -0.5f, 0.0f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(0.0f, 0.0f, 1.0f), Math::Vec3(1.0f, 0.0f, 0.0f), Math::Vec3(0.0f, 0.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(-0.5f, 0.5f, 0.0f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(0.0f, 0.0f, 1.0f), Math::Vec3(1.0f, 0.0f, 0.0f), Math::Vec3(0.0f, 1.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(0.5f, -0.5f, 0.0f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(0.0f, 0.0f, 1.0f), Math::Vec3(1.0f, 0.0f, 0.0f), Math::Vec3(1.0f, 0.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(0.5f, 0.5f, 0.0f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(0.0f, 0.0f, 1.0f), Math::Vec3(1.0f, 0.0f, 0.0f), Math::Vec3(1.0f, 1.0f, 0.0f)));

	TriangleIBO.EmplaceBack(TriangleIndexData(0, 2, 1));
	TriangleIBO.EmplaceBack(TriangleIndexData(1, 2, 3));
}

void BFW::Assets::Mesh::GenerateUnitCube()
{
	TriangleVBO.Clear();
	TriangleIBO.Clear();
	LineVBO.Clear();
	LineIBO.Clear();

	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(-0.5f, -0.5f, 0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(-1.0f, 0.0f, 0.0f), Math::Vec3(0.0f, 0.0f, 1.0f), Math::Vec3(1.0f, 0.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(-0.5f, 0.5f, 0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(-1.0f, 0.0f, 0.0f), Math::Vec3(0.0f, 0.0f, 1.0f), Math::Vec3(1.0f, 1.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(-0.5f, 0.5f, -0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(-1.0f, 0.0f, 0.0f), Math::Vec3(0.0f, 0.0f, 1.0f), Math::Vec3(0.0f, 1.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(-0.5f, -0.5f, 0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(-1.0f, 0.0f, 0.0f), Math::Vec3(0.0f, 0.0f, 1.0f), Math::Vec3(1.0f, 0.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(-0.5f, 0.5f, -0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(-1.0f, 0.0f, 0.0f), Math::Vec3(0.0f, 0.0f, 1.0f), Math::Vec3(0.0f, 1.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(-0.5f, -0.5f, -0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(-1.0f, 0.0f, 0.0f), Math::Vec3(0.0f, 0.0f, 1.0f), Math::Vec3(0.0f, 0.0f, 0.0f)));

	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(-0.5f, -0.5f, -0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(0.0f, 0.0f, -1.0f), Math::Vec3(-1.0f, 0.0f, 0.0f), Math::Vec3(1.0f, 0.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(-0.5f, 0.5f, -0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(0.0f, 0.0f, -1.0f), Math::Vec3(-1.0f, 0.0f, 0.0f), Math::Vec3(1.0f, 1.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(0.5f, 0.5f, -0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(0.0f, 0.0f, -1.0f), Math::Vec3(-1.0f, 0.0f, 0.0f), Math::Vec3(0.0f, 1.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(-0.5f, -0.5f, -0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(0.0f, 0.0f, -1.0f), Math::Vec3(-1.0f, 0.0f, 0.0f), Math::Vec3(1.0f, 0.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(0.5f, 0.5f, -0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(0.0f, 0.0f, -1.0f), Math::Vec3(-1.0f, 0.0f, 0.0f), Math::Vec3(0.0f, 1.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(0.5f, -0.5f, -0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(0.0f, 0.0f, -1.0f), Math::Vec3(-1.0f, 0.0f, 0.0f), Math::Vec3(0.0f, 0.0f, 0.0f)));

	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(0.5f, -0.5f, -0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(1.0f, 0.0f, 0.0f), Math::Vec3(0.0f, 0.0f, -1.0f), Math::Vec3(1.0f, 0.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(0.5f, 0.5f, -0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(1.0f, 0.0f, 0.0f), Math::Vec3(0.0f, 0.0f, -1.0f), Math::Vec3(1.0f, 1.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(0.5f, 0.5f, 0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(1.0f, 0.0f, 0.0f), Math::Vec3(0.0f, 0.0f, -1.0f), Math::Vec3(0.0f, 1.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(0.5f, -0.5f, -0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(1.0f, 0.0f, 0.0f), Math::Vec3(0.0f, 0.0f, -1.0f), Math::Vec3(1.0f, 0.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(0.5f, 0.5f, 0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(1.0f, 0.0f, 0.0f), Math::Vec3(0.0f, 0.0f, -1.0f), Math::Vec3(0.0f, 1.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(0.5f, -0.5f, 0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(1.0f, 0.0f, 0.0f), Math::Vec3(0.0f, 0.0f, -1.0f), Math::Vec3(0.0f, 0.0f, 0.0f)));

	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(0.5f, -0.5f, 0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(0.0f, 0.0f, 1.0f), Math::Vec3(1.0f, 0.0f, 0.0f), Math::Vec3(1.0f, 0.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(0.5f, 0.5f, 0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(0.0f, 0.0f, 1.0f), Math::Vec3(1.0f, 0.0f, 0.0f), Math::Vec3(1.0f, 1.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(-0.5f, 0.5f, 0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(0.0f, 0.0f, 1.0f), Math::Vec3(1.0f, 0.0f, 0.0f), Math::Vec3(0.0f, 1.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(0.5f, -0.5f, 0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(0.0f, 0.0f, 1.0f), Math::Vec3(1.0f, 0.0f, 0.0f), Math::Vec3(1.0f, 0.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(-0.5f, 0.5f, 0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(0.0f, 0.0f, 1.0f), Math::Vec3(1.0f, 0.0f, 0.0f), Math::Vec3(0.0f, 1.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(-0.5f, -0.5f, 0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(0.0f, 0.0f, 1.0f), Math::Vec3(1.0f, 0.0f, 0.0f), Math::Vec3(0.0f, 0.0f, 0.0f)));

	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(-0.5f, -0.5f, -0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(0.0f, -1.0f, 0.0f), Math::Vec3(1.0f, 0.0f, 0.0f), Math::Vec3(0.0f, 0.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(0.5f, -0.5f, -0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(0.0f, -1.0f, 0.0f), Math::Vec3(1.0f, 0.0f, 0.0f), Math::Vec3(1.0f, 0.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(0.5f, -0.5f, 0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(0.0f, -1.0f, 0.0f), Math::Vec3(1.0f, 0.0f, 0.0f), Math::Vec3(1.0f, 1.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(-0.5f, -0.5f, -0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(0.0f, -1.0f, 0.0f), Math::Vec3(1.0f, 0.0f, 0.0f), Math::Vec3(0.0f, 0.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(0.5f, -0.5f, 0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(0.0f, -1.0f, 0.0f), Math::Vec3(1.0f, 0.0f, 0.0f), Math::Vec3(1.0f, 1.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(-0.5f, -0.5f, 0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(0.0f, -1.0f, 0.0f), Math::Vec3(1.0f, 0.0f, 0.0f), Math::Vec3(0.0f, 1.0f, 0.0f)));

	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(0.5f, 0.5f, -0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(0.0f, 1.0f, 0.0f), Math::Vec3(1.0f, 0.0f, 0.0f), Math::Vec3(1.0f, 1.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(-0.5f, 0.5f, -0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(0.0f, 1.0f, 0.0f), Math::Vec3(1.0f, 0.0f, 0.0f), Math::Vec3(0.0f, 1.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(-0.5f, 0.5f, 0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(0.0f, 1.0f, 0.0f), Math::Vec3(1.0f, 0.0f, 0.0f), Math::Vec3(0.0f, 0.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(0.5f, 0.5f, -0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(0.0f, 1.0f, 0.0f), Math::Vec3(1.0f, 0.0f, 0.0f), Math::Vec3(1.0f, 1.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(-0.5f, 0.5f, 0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(0.0f, 1.0f, 0.0f), Math::Vec3(1.0f, 0.0f, 0.0f), Math::Vec3(0.0f, 0.0f, 0.0f)));
	TriangleVBO.EmplaceBack(TriangleVertexData(Math::Vec4(0.5f, 0.5f, 0.5f, 1.0f), Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f), Math::Vec3(0.0f, 1.0f, 0.0f), Math::Vec3(1.0f, 0.0f, 0.0f), Math::Vec3(1.0f, 0.0f, 0.0f)));

	TriangleIBO.EmplaceBack(TriangleIndexData(0, 1, 2));
	TriangleIBO.EmplaceBack(TriangleIndexData(3, 4, 5));

	TriangleIBO.EmplaceBack(TriangleIndexData(6, 7, 8));
	TriangleIBO.EmplaceBack(TriangleIndexData(9, 10, 11));

	TriangleIBO.EmplaceBack(TriangleIndexData(12, 13, 14));
	TriangleIBO.EmplaceBack(TriangleIndexData(15, 16, 17));

	TriangleIBO.EmplaceBack(TriangleIndexData(18, 19, 20));
	TriangleIBO.EmplaceBack(TriangleIndexData(21, 22, 23));

	TriangleIBO.EmplaceBack(TriangleIndexData(24, 25, 26));
	TriangleIBO.EmplaceBack(TriangleIndexData(27, 28, 29));

	TriangleIBO.EmplaceBack(TriangleIndexData(30, 31, 32));
	TriangleIBO.EmplaceBack(TriangleIndexData(33, 34, 35));
}

BFW::Assets::Mesh& BFW::Assets::Mesh::operator= (const Mesh& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Name = _Other.Name;
	MaterialLib = _Other.MaterialLib;
	MaterialName = _Other.MaterialName;
	TriangleVBO = _Other.TriangleVBO;
	TriangleIBO = _Other.TriangleIBO;
	LineVBO = _Other.LineVBO;
	LineIBO = _Other.LineIBO;

	return *this;
}

BFW::Assets::Mesh& BFW::Assets::Mesh::operator= (Mesh&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Name = _Other.Name;
	MaterialLib = _Other.MaterialLib;
	MaterialName = _Other.MaterialName;
	TriangleVBO = (Vector<TriangleVertexData>&&)(_Other.TriangleVBO);
	TriangleIBO = (Vector<TriangleIndexData>&&)(_Other.TriangleIBO);
	LineVBO = (Vector<LineVertexData>&&)(_Other.LineVBO);
	LineIBO = (Vector<LineIndexData>&&)(_Other.LineIBO);

	_Other.Name = BFW_STRING_PREFIX("");
	_Other.MaterialLib = BFW_STRING_PREFIX("");
	_Other.MaterialName = BFW_STRING_PREFIX("");

	return *this;
}



BFW::Assets::WaveFrontObj::WaveFrontObj() : MeshNames(), Meshes()
{

}

BFW::Assets::WaveFrontObj::WaveFrontObj(const WaveFrontObj& _Other) : MeshNames(_Other.MeshNames), Meshes(_Other.Meshes)
{

}

BFW::Assets::WaveFrontObj::WaveFrontObj(WaveFrontObj&& _Other) noexcept : MeshNames((Vector<BFW_STRING_TYPE>&&)(_Other.MeshNames)), Meshes((Trie<Mesh>&&)(_Other.Meshes))
{

}

BFW::Assets::WaveFrontObj::~WaveFrontObj()
{

}

const bool BFW::Assets::WaveFrontObj::Load(const FileContent& _FileContent)
{
	Clear();

	if (!_FileContent.GetData())
	{
		return false;
	}

	Vector<BFW_STRING_TYPE> _Names;
	Vector<size_t> _FaceStarts;
	Vector<size_t> _LineStarts;

	Vector<Math::Vec4> _Positions;
	Vector<Math::Vec4> _Colors;
	Vector<Math::Vec3> _Normals;
	Vector<Math::Vec3> _TextureCoords;

	Vector<Vector<size_t>> _FacePositions;
	Vector<Vector<size_t>> _FaceNormals;
	Vector<Vector<size_t>> _FaceTextureCoords;
	Vector<Vector<size_t>> _LinePositions;
	Vector<Vector<size_t>> _LineTextureCoords;

	size_t _FileIndex = 0;

	while (_FileContent[_FileIndex] != '\0')
	{
		BFW_STRING_TYPE_A _FileLine;

		BFW_WINDOWS_PLATFORM_CALL(_FileLine.reserve(512));
		BFW_LINUX_PLATFORM_CALL(_FileLine.reserve(512));

		bool _KeepLine = true;

		while (_KeepLine)
		{
			_KeepLine = false;

			size_t _FileLineStart = _FileLine.size();

			while (_FileContent[_FileIndex] != '\n' && _FileContent[_FileIndex] != '\0')
			{
				if (_FileContent[_FileIndex] == '#')
				{
					break;
				}

				_FileLine += _FileContent[_FileIndex];
				_FileIndex++;
			}

			while (_FileContent[_FileIndex] != '\n' && _FileContent[_FileIndex] != '\0')
			{
				_FileIndex++;
			}

			if (_FileLine.size() != 0 && _FileLine[_FileLine.size() - 1] == '\r')
			{
				_FileLine.erase(_FileLine.begin() + _FileLine.size() - 1);
			}

			size_t _CharIndex = _FileLineStart;

			while (_CharIndex < _FileLine.size() && std::isspace((unsigned BFW_CHAR_TYPE_A)(_FileLine[_FileLine.size() - 1 - _CharIndex + _FileLineStart])))
			{
				_CharIndex++;
			}

			size_t _BackSlashCount = 0;

			while (_CharIndex < _FileLine.size() && _FileLine[_FileLine.size() - 1 - _CharIndex + _FileLineStart] == '\\')
			{
				_BackSlashCount++;
				_CharIndex++;
			}

			for (size_t _Index = 0; _Index < _BackSlashCount / 2; _Index++)
			{
				_FileLine.erase(_FileLine.begin() + _FileLine.size() - 1 - _CharIndex + 1 + _FileLineStart);
				_CharIndex--;
			}

			if (_BackSlashCount % 2 == 1)
			{
				_KeepLine = true;
				_FileLine[_FileLine.size() - 1 - _CharIndex + _BackSlashCount / 2 + 1 + _FileLineStart] = ' ';
			}

			if (_FileContent[_FileIndex] == '\0')
			{
				break;
			}

			_FileIndex++;
		}

		if (!_FileLine.size())
		{
			continue;
		}

		size_t _CharIndex = 0;

		while (std::isspace((unsigned BFW_CHAR_TYPE_A)(_FileLine[_CharIndex])))
		{
			_CharIndex++;
		}

		if (_CharIndex == _FileLine.size())
		{
			continue;
		}

		Vector<BFW_STRING_TYPE_A> _LineTokens;

		while (_FileLine[_CharIndex] != '\0')
		{
			BFW_STRING_TYPE_A& _Token = _LineTokens.EmplaceBack(BFW_STRING_TYPE_A());

			BFW_WINDOWS_PLATFORM_CALL(_Token.reserve(16));
			BFW_LINUX_PLATFORM_CALL(_Token.reserve(16));

			if (_FileLine[_CharIndex] == '\"')
			{
				_CharIndex++;

				while (_FileLine[_CharIndex] != '\"' && _FileLine[_CharIndex] != '\0')
				{
					if (String::IsControlCharacter(_FileLine[_CharIndex]))
					{
						return false;
					}

					if (_FileLine[_CharIndex] == '\\' && _FileLine[_CharIndex + 1] == '\"')
					{
						_Token += '\"';
						_CharIndex += 2;
						continue;
					}

					_Token += _FileLine[_CharIndex];
					_CharIndex++;
				}

				if (_FileLine[_CharIndex] == '\0')
				{
					return false;
				}

				_CharIndex++;

				while (std::isspace((unsigned BFW_CHAR_TYPE_A)(_FileLine[_CharIndex])))
				{
					_CharIndex++;
				}

				continue;
			}

			while (!std::isspace((unsigned BFW_CHAR_TYPE_A)(_FileLine[_CharIndex])) && _FileLine[_CharIndex] != '\0')
			{
				if (_FileLine[_CharIndex] == '\"')
				{
					break;
				}

				_Token += _FileLine[_CharIndex];
				_CharIndex++;
			}

			while (std::isspace((unsigned BFW_CHAR_TYPE_A)(_FileLine[_CharIndex])))
			{
				_CharIndex++;
			}
		}

		if (_LineTokens[0] == "o")
		{
			if (_LineTokens.GetSize() != 2)
			{
				return false;
			}

			bool _Error = false;

			BFW_STRING_TYPE _Name = BFW_UTF8_TO_MACHINE(_LineTokens[1], &_Error);

			if (_Error)
			{
				return false;
			}

			for (size_t _Index = 0; _Index < _Names.GetSize(); _Index++)
			{
				if (_Names[_Index] == _Name)
				{
					return false;
				}
			}

			_Names.PushBack(_Name);
			_FaceStarts.PushBack(_FacePositions.GetSize());
			_LineStarts.PushBack(_LinePositions.GetSize());

			continue;
		}

		if (_LineTokens[0] == "v")
		{
			switch (_LineTokens.GetSize())
			{
			case 4:
			{
				Vector<float> _Values(3);

				for (size_t _Index = 0; _Index < _Values.GetSize(); _Index++)
				{
					BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[_Index + 1]);

					if (!(_Stream >> _Values[_Index]) || !_Stream.eof())
					{
						return false;
					}
				}

				_Positions.PushBack(Math::Vec4(_Values[0], _Values[1], _Values[2], 1.0f));
				_Colors.PushBack(Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f));

				break;
			}
			case 5:
			{
				Vector<float> _Values(4);

				for (size_t _Index = 0; _Index < _Values.GetSize(); _Index++)
				{
					BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[_Index + 1]);

					if (!(_Stream >> _Values[_Index]) || !_Stream.eof())
					{
						return false;
					}
				}

				_Positions.PushBack(Math::Vec4(_Values[0], _Values[1], _Values[2], _Values[3]));
				_Colors.PushBack(Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f));

				break;
			}
			case 7:
			{
				Vector<float> _Values(6);

				for (size_t _Index = 0; _Index < _Values.GetSize(); _Index++)
				{
					BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[_Index + 1]);

					if (!(_Stream >> _Values[_Index]) || !_Stream.eof())
					{
						return false;
					}
				}

				_Positions.PushBack(Math::Vec4(_Values[0], _Values[1], _Values[2], 1.0f));
				_Colors.PushBack(Math::Vec4(_Values[3], _Values[4], _Values[5], 1.0f));

				break;
			}
			default:
			{
				return false;
			}
			}

			continue;
		}

		if (_LineTokens[0] == "vt")
		{
			switch (_LineTokens.GetSize())
			{
			case 2:
			{
				Vector<float> _Values(1);

				for (size_t _Index = 0; _Index < _Values.GetSize(); _Index++)
				{
					BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[_Index + 1]);

					if (!(_Stream >> _Values[_Index]) || !_Stream.eof())
					{
						return false;
					}
				}

				_TextureCoords.PushBack(Math::Vec3(_Values[0], 0.0f, 0.0f));

				break;
			}
			case 3:
			{
				Vector<float> _Values(2);

				for (size_t _Index = 0; _Index < _Values.GetSize(); _Index++)
				{
					BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[_Index + 1]);

					if (!(_Stream >> _Values[_Index]) || !_Stream.eof())
					{
						return false;
					}
				}

				_TextureCoords.PushBack(Math::Vec3(_Values[0], _Values[1], 0.0f));

				break;
			}
			case 4:
			{
				Vector<float> _Values(3);

				for (size_t _Index = 0; _Index < _Values.GetSize(); _Index++)
				{
					BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[_Index + 1]);

					if (!(_Stream >> _Values[_Index]) || !_Stream.eof())
					{
						return false;
					}
				}

				_TextureCoords.PushBack(Math::Vec3(_Values[0], _Values[1], _Values[2]));

				break;
			}
			default:
			{
				return false;
			}
			}

			continue;
		}

		if (_LineTokens[0] == "vn")
		{
			if (_LineTokens.GetSize() != 4)
			{
				return false;
			}

			Vector<float> _Values(3);

			for (size_t _Index = 0; _Index < _Values.GetSize(); _Index++)
			{
				BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[_Index + 1]);

				if (!(_Stream >> _Values[_Index]) || !_Stream.eof())
				{
					return false;
				}
			}

			_Normals.PushBack(Math::Vec3(_Values[0], _Values[1], _Values[2]));

			continue;
		}

		if (_LineTokens[0] == "f")
		{
			if (_LineTokens.GetSize() < 4)
			{
				return false;
			}

			Vector<Vector<size_t>> _SlashIndices;

			for (size_t _TokenIndex = 1; _TokenIndex < _LineTokens.GetSize(); _TokenIndex++)
			{
				Vector<size_t>& _CurrentSlashIndices = _SlashIndices.EmplaceBack(Vector<size_t>());

				if (_LineTokens[_TokenIndex][0] == '/' || _LineTokens[_TokenIndex][_LineTokens[_TokenIndex].size() - 1] == '/')
				{
					return false;
				}

				for (size_t _TokenCharIndex = 0; _TokenCharIndex < _LineTokens[_TokenIndex].size(); _TokenCharIndex++)
				{
					if (BFW_STRING_TYPE_A("+-0123456789/").find(_LineTokens[_TokenIndex][_TokenCharIndex]) == BFW_STRING_TYPE_A::npos || _LineTokens[_TokenIndex][_TokenCharIndex] == '\0')
					{
						return false;
					}

					if (_LineTokens[_TokenIndex][_TokenCharIndex] == '/')
					{
						_CurrentSlashIndices.PushBack(_TokenCharIndex);
					}
				}

				if (_CurrentSlashIndices.GetSize() > 2 || _CurrentSlashIndices.GetSize() != _SlashIndices[0].GetSize())
				{
					return false;
				}

				if (_SlashIndices[0].GetSize() == 2 && ((_SlashIndices[0][0] + 1 == _SlashIndices[0][1] && _CurrentSlashIndices[0] + 1 != _CurrentSlashIndices[1]) || (_SlashIndices[0][0] + 1 != _SlashIndices[0][1] && _CurrentSlashIndices[0] + 1 == _CurrentSlashIndices[1])))
				{
					return false;
				}
			}

			Vector<Vector<size_t>> _TokenIndices;
			intmax_t _TempValue = 0;

			if (_SlashIndices[0].GetSize() == 0)
			{
				for (size_t _TokenIndex = 1; _TokenIndex < _LineTokens.GetSize(); _TokenIndex++)
				{
					Vector<size_t>& _CurrentTokenIndices = _TokenIndices.EmplaceBack(Vector<size_t>());

					BFW_STRING_STREAM_TYPE_A _Stream1(_LineTokens[_TokenIndex]);

					if (!(_Stream1 >> _TempValue) || !_Stream1.eof())
					{
						return false;
					}

					if (_TempValue == 0)
					{
						return false;
					}
					else if (_TempValue > 0)
					{
						_TempValue--;
					}
					else
					{
						_TempValue = _Positions.GetSize() + _TempValue;
					}

					if ((size_t)(_TempValue) >= _Positions.GetSize())
					{
						return false;
					}

					_CurrentTokenIndices.PushBack((size_t)(_TempValue));

					_CurrentTokenIndices.PushBack(std::numeric_limits<size_t>::max());
					_CurrentTokenIndices.PushBack(std::numeric_limits<size_t>::max());
				}
			}
			else if (_SlashIndices[0].GetSize() == 1)
			{
				for (size_t _TokenIndex = 1; _TokenIndex < _LineTokens.GetSize(); _TokenIndex++)
				{
					Vector<size_t>& _CurrentTokenIndices = _TokenIndices.EmplaceBack(Vector<size_t>());

					BFW_STRING_STREAM_TYPE_A _Stream1(_LineTokens[_TokenIndex].substr(0, _SlashIndices[_TokenIndex - 1][0]));

					if (!(_Stream1 >> _TempValue) || !_Stream1.eof())
					{
						return false;
					}

					if (_TempValue == 0)
					{
						return false;
					}
					else if (_TempValue > 0)
					{
						_TempValue--;
					}
					else
					{
						_TempValue = _Positions.GetSize() + _TempValue;
					}

					if ((size_t)(_TempValue) >= _Positions.GetSize())
					{
						return false;
					}

					_CurrentTokenIndices.PushBack((size_t)(_TempValue));

					BFW_STRING_STREAM_TYPE_A _Stream2(_LineTokens[_TokenIndex].substr(_SlashIndices[_TokenIndex - 1][0] + 1, _LineTokens[_TokenIndex].size() - _SlashIndices[_TokenIndex - 1][0] - 1));

					if (!(_Stream2 >> _TempValue) || !_Stream2.eof())
					{
						return false;
					}

					if (_TempValue == 0)
					{
						return false;
					}
					else if (_TempValue > 0)
					{
						_TempValue--;
					}
					else
					{
						_TempValue = _TextureCoords.GetSize() + _TempValue;
					}

					if ((size_t)(_TempValue) >= _TextureCoords.GetSize())
					{
						return false;
					}

					_CurrentTokenIndices.PushBack((size_t)(_TempValue));

					_CurrentTokenIndices.PushBack(std::numeric_limits<size_t>::max());
				}
			}
			else if (_SlashIndices[0].GetSize() == 2)
			{
				if (_SlashIndices[0][0] + 1 == _SlashIndices[0][1])
				{
					for (size_t _TokenIndex = 1; _TokenIndex < _LineTokens.GetSize(); _TokenIndex++)
					{
						Vector<size_t>& _CurrentTokenIndices = _TokenIndices.EmplaceBack(Vector<size_t>());

						BFW_STRING_STREAM_TYPE_A _Stream1(_LineTokens[_TokenIndex].substr(0, _SlashIndices[_TokenIndex - 1][0]));

						if (!(_Stream1 >> _TempValue) || !_Stream1.eof())
						{
							return false;
						}

						if (_TempValue == 0)
						{
							return false;
						}
						else if (_TempValue > 0)
						{
							_TempValue--;
						}
						else
						{
							_TempValue = _Positions.GetSize() + _TempValue;
						}

						if ((size_t)(_TempValue) >= _Positions.GetSize())
						{
							return false;
						}

						_CurrentTokenIndices.PushBack((size_t)(_TempValue));

						_CurrentTokenIndices.PushBack(std::numeric_limits<size_t>::max());

						BFW_STRING_STREAM_TYPE_A _Stream2(_LineTokens[_TokenIndex].substr(_SlashIndices[_TokenIndex - 1][1] + 1, _LineTokens[_TokenIndex].size() - _SlashIndices[_TokenIndex - 1][1] - 1));

						if (!(_Stream2 >> _TempValue) || !_Stream2.eof())
						{
							return false;
						}

						if (_TempValue == 0)
						{
							return false;
						}
						else if (_TempValue > 0)
						{
							_TempValue--;
						}
						else
						{
							_TempValue = _Normals.GetSize() + _TempValue;
						}

						if ((size_t)(_TempValue) >= _Normals.GetSize())
						{
							return false;
						}

						_CurrentTokenIndices.PushBack((size_t)(_TempValue));
					}
				}
				else
				{
					for (size_t _TokenIndex = 1; _TokenIndex < _LineTokens.GetSize(); _TokenIndex++)
					{
						Vector<size_t>& _CurrentTokenIndices = _TokenIndices.EmplaceBack(Vector<size_t>());

						BFW_STRING_STREAM_TYPE_A _Stream1(_LineTokens[_TokenIndex].substr(0, _SlashIndices[_TokenIndex - 1][0]));

						if (!(_Stream1 >> _TempValue) || !_Stream1.eof())
						{
							return false;
						}

						if (_TempValue == 0)
						{
							return false;
						}
						else if (_TempValue > 0)
						{
							_TempValue--;
						}
						else
						{
							_TempValue = _Positions.GetSize() + _TempValue;
						}

						if ((size_t)(_TempValue) >= _Positions.GetSize())
						{
							return false;
						}

						_CurrentTokenIndices.PushBack((size_t)(_TempValue));

						BFW_STRING_STREAM_TYPE_A _Stream2(_LineTokens[_TokenIndex].substr(_SlashIndices[_TokenIndex - 1][0] + 1, _SlashIndices[_TokenIndex - 1][1] - _SlashIndices[_TokenIndex - 1][0] - 1));

						if (!(_Stream2 >> _TempValue) || !_Stream2.eof())
						{
							return false;
						}

						if (_TempValue == 0)
						{
							return false;
						}
						else if (_TempValue > 0)
						{
							_TempValue--;
						}
						else
						{
							_TempValue = _TextureCoords.GetSize() + _TempValue;
						}

						if ((size_t)(_TempValue) >= _TextureCoords.GetSize())
						{
							return false;
						}

						_CurrentTokenIndices.PushBack((size_t)(_TempValue));

						BFW_STRING_STREAM_TYPE_A _Stream3(_LineTokens[_TokenIndex].substr(_SlashIndices[_TokenIndex - 1][1] + 1, _LineTokens[_TokenIndex].size() - _SlashIndices[_TokenIndex - 1][1] - 1));

						if (!(_Stream3 >> _TempValue) || !_Stream3.eof())
						{
							return false;
						}

						if (_TempValue == 0)
						{
							return false;
						}
						else if (_TempValue > 0)
						{
							_TempValue--;
						}
						else
						{
							_TempValue = _Normals.GetSize() + _TempValue;
						}

						if ((size_t)(_TempValue) >= _Normals.GetSize())
						{
							return false;
						}

						_CurrentTokenIndices.PushBack((size_t)(_TempValue));
					}
				}
			}

			for (size_t _TokenIndex = 2; _TokenIndex < _LineTokens.GetSize() - 1; _TokenIndex++)
			{
				_FacePositions.PushBack({ _TokenIndices[0][0], _TokenIndices[_TokenIndex - 1][0], _TokenIndices[_TokenIndex][0] });
				_FaceTextureCoords.PushBack({ _TokenIndices[0][1], _TokenIndices[_TokenIndex - 1][1], _TokenIndices[_TokenIndex][1] });
				_FaceNormals.PushBack({ _TokenIndices[0][2], _TokenIndices[_TokenIndex - 1][2], _TokenIndices[_TokenIndex][2] });
			}

			continue;
		}

		if (_LineTokens[0] == "l")
		{
			if (_LineTokens.GetSize() < 3)
			{
				return false;
			}

			Vector<Vector<size_t>> _SlashIndices;

			for (size_t _TokenIndex = 1; _TokenIndex < _LineTokens.GetSize(); _TokenIndex++)
			{
				Vector<size_t>& _CurrentSlashIndices = _SlashIndices.EmplaceBack(Vector<size_t>());

				if (_LineTokens[_TokenIndex][0] == '/' || _LineTokens[_TokenIndex][_LineTokens[_TokenIndex].size() - 1] == '/')
				{
					return false;
				}

				for (size_t _TokenCharIndex = 0; _TokenCharIndex < _LineTokens[_TokenIndex].size(); _TokenCharIndex++)
				{
					if (BFW_STRING_TYPE_A("+-0123456789/").find(_LineTokens[_TokenIndex][_TokenCharIndex]) == BFW_STRING_TYPE_A::npos || _LineTokens[_TokenIndex][_TokenCharIndex] == '\0')
					{
						return false;
					}

					if (_LineTokens[_TokenIndex][_TokenCharIndex] == '/')
					{
						_CurrentSlashIndices.PushBack(_TokenCharIndex);
					}
				}

				if (_CurrentSlashIndices.GetSize() > 1 || _CurrentSlashIndices.GetSize() != _SlashIndices[0].GetSize())
				{
					return false;
				}
			}

			Vector<Vector<size_t>> _TokenIndices;
			intmax_t _TempValue = 0;

			if (_SlashIndices[0].GetSize() == 0)
			{
				for (size_t _TokenIndex = 1; _TokenIndex < _LineTokens.GetSize(); _TokenIndex++)
				{
					Vector<size_t>& _CurrentTokenIndices = _TokenIndices.EmplaceBack(Vector<size_t>());

					BFW_STRING_STREAM_TYPE_A _Stream1(_LineTokens[_TokenIndex]);

					if (!(_Stream1 >> _TempValue) || !_Stream1.eof())
					{
						return false;
					}

					if (_TempValue == 0)
					{
						return false;
					}
					else if (_TempValue > 0)
					{
						_TempValue--;
					}
					else
					{
						_TempValue = _Positions.GetSize() + _TempValue;
					}

					if ((size_t)(_TempValue) >= _Positions.GetSize())
					{
						return false;
					}

					_CurrentTokenIndices.PushBack((size_t)(_TempValue));

					_CurrentTokenIndices.PushBack(std::numeric_limits<size_t>::max());
				}
			}
			else if (_SlashIndices[0].GetSize() == 1)
			{
				for (size_t _TokenIndex = 1; _TokenIndex < _LineTokens.GetSize(); _TokenIndex++)
				{
					Vector<size_t>& _CurrentTokenIndices = _TokenIndices.EmplaceBack(Vector<size_t>());

					BFW_STRING_STREAM_TYPE_A _Stream1(_LineTokens[_TokenIndex].substr(0, _SlashIndices[_TokenIndex - 1][0]));

					if (!(_Stream1 >> _TempValue) || !_Stream1.eof())
					{
						return false;
					}

					if (_TempValue == 0)
					{
						return false;
					}
					else if (_TempValue > 0)
					{
						_TempValue--;
					}
					else
					{
						_TempValue = _Positions.GetSize() + _TempValue;
					}

					if ((size_t)(_TempValue) >= _Positions.GetSize())
					{
						return false;
					}

					_CurrentTokenIndices.PushBack((size_t)(_TempValue));

					BFW_STRING_STREAM_TYPE_A _Stream2(_LineTokens[_TokenIndex].substr(_SlashIndices[_TokenIndex - 1][0] + 1, _LineTokens[_TokenIndex].size() - _SlashIndices[_TokenIndex - 1][0] - 1));

					if (!(_Stream2 >> _TempValue) || !_Stream2.eof())
					{
						return false;
					}

					if (_TempValue == 0)
					{
						return false;
					}
					else if (_TempValue > 0)
					{
						_TempValue--;
					}
					else
					{
						_TempValue = _TextureCoords.GetSize() + _TempValue;
					}

					if ((size_t)(_TempValue) >= _TextureCoords.GetSize())
					{
						return false;
					}

					_CurrentTokenIndices.PushBack((size_t)(_TempValue));
				}
			}

			for (size_t _TokenIndex = 1; _TokenIndex < _LineTokens.GetSize() - 1; _TokenIndex++)
			{
				_LinePositions.PushBack({ _TokenIndices[_TokenIndex - 1][0], _TokenIndices[_TokenIndex][0] });
				_LineTextureCoords.PushBack({ _TokenIndices[_TokenIndex - 1][1], _TokenIndices[_TokenIndex][1] });
			}

			continue;
		}
	}

	if (_FileIndex != _FileContent.GetLength() - 1)
	{
		return false;
	}

	if (_Names.GetSize() == 0)
	{
		_Names.EmplaceBack(BFW_STRING_PREFIX("Default"));
		_FaceStarts.PushBack(0);
		_LineStarts.PushBack(0);
	}

	_FaceStarts.PushBack(_FacePositions.GetSize());
	_LineStarts.PushBack(_LinePositions.GetSize());

	for (size_t _NameIndex = 0; _NameIndex < _Names.GetSize(); _NameIndex++)
	{
		Mesh _Mesh;

		_Mesh.Name = _Names[_NameIndex];

		for (size_t _FaceIndex = _FaceStarts[_NameIndex]; _FaceIndex < _FaceStarts[_NameIndex + 1]; _FaceIndex++)
		{
			Vector<size_t>& _CurrentFacePositions = _FacePositions[_FaceIndex];
			Vector<size_t>& _CurrentFaceNormals = _FaceNormals[_FaceIndex];
			Vector<size_t>& _CurrentFaceTextureCoords = _FaceTextureCoords[_FaceIndex];

			TriangleVertexData _VertexA;
			TriangleVertexData _VertexB;
			TriangleVertexData _VertexC;

			_VertexA.Position = _Positions[_FacePositions[_FaceIndex][0]];
			_VertexA.Color = _Colors[_FacePositions[_FaceIndex][0]];

			_VertexB.Position = _Positions[_FacePositions[_FaceIndex][1]];
			_VertexB.Color = _Colors[_FacePositions[_FaceIndex][1]];

			_VertexC.Position = _Positions[_FacePositions[_FaceIndex][2]];
			_VertexC.Color = _Colors[_FacePositions[_FaceIndex][2]];

			Math::Vec3 _TrueNormal = Math::Vec3::Cross(_VertexB.Position - _VertexA.Position, _VertexC.Position - _VertexA.Position);

			if (_TrueNormal.Magnitude() >= 0.00000001f)
			{
				_TrueNormal.Normalize();
			}

			if (_FaceNormals[_FaceIndex][0] != std::numeric_limits<size_t>::max())
			{
				_VertexA.Normal = _Normals[_FaceNormals[_FaceIndex][0]];
			}
			else
			{
				_VertexA.Normal = _TrueNormal;
			}

			if (_FaceNormals[_FaceIndex][1] != std::numeric_limits<size_t>::max())
			{
				_VertexB.Normal = _Normals[_FaceNormals[_FaceIndex][1]];
			}
			else
			{
				_VertexB.Normal = _TrueNormal;
			}

			if (_FaceNormals[_FaceIndex][2] != std::numeric_limits<size_t>::max())
			{
				_VertexC.Normal = _Normals[_FaceNormals[_FaceIndex][2]];
			}
			else
			{
				_VertexC.Normal = _TrueNormal;
			}

			if (_FaceTextureCoords[_FaceIndex][0] != std::numeric_limits<size_t>::max())
			{
				_VertexA.TextureCoords = _TextureCoords[_FaceTextureCoords[_FaceIndex][0]];
			}

			if (_FaceTextureCoords[_FaceIndex][1] != std::numeric_limits<size_t>::max())
			{
				_VertexB.TextureCoords = _TextureCoords[_FaceTextureCoords[_FaceIndex][1]];
			}

			if (_FaceTextureCoords[_FaceIndex][2] != std::numeric_limits<size_t>::max())
			{
				_VertexC.TextureCoords = _TextureCoords[_FaceTextureCoords[_FaceIndex][2]];
			}

			if (_FaceTextureCoords[_FaceIndex][0] != std::numeric_limits<size_t>::max() && _FaceTextureCoords[_FaceIndex][1] != std::numeric_limits<size_t>::max() && _FaceTextureCoords[_FaceIndex][2] != std::numeric_limits<size_t>::max())
			{
				Math::Vec3 _Edge1 = Math::Vec3(_VertexB.Position - _VertexA.Position);
				Math::Vec3 _Edge2 = Math::Vec3(_VertexC.Position - _VertexA.Position);

				Math::Vec2 _Delta1 = Math::Vec2(_VertexB.TextureCoords - _VertexA.TextureCoords);
				Math::Vec2 _Delta2 = Math::Vec2(_VertexC.TextureCoords - _VertexA.TextureCoords);

				if (fabs(_Delta1.x * _Delta2.y - _Delta2.x * _Delta1.y) >= 0.00000001f)
				{
					float _Factor = 1.0f / (_Delta1.x * _Delta2.y - _Delta2.x * _Delta1.y);

					Math::Vec3 _Tangent = Math::Vec3(_Delta2.y * _Edge1.x - _Delta1.y * _Edge2.x, _Delta2.y * _Edge1.y - _Delta1.y * _Edge2.y, _Delta2.y * _Edge1.z - _Delta1.y * _Edge2.z) * _Factor;

					if (_Tangent.Magnitude() >= 0.00000001f)
					{
						_Tangent.Normalize();

						_VertexA.Tangent = _Tangent;
						_VertexB.Tangent = _Tangent;
						_VertexC.Tangent = _Tangent;
					}
					else
					{
						_VertexA.Tangent = _VertexB.Position - _VertexA.Position;
						_VertexB.Tangent = _VertexB.Position - _VertexA.Position;
						_VertexC.Tangent = _VertexB.Position - _VertexA.Position;
					}
				}
				else
				{
					_VertexA.Tangent = _VertexB.Position - _VertexA.Position;
					_VertexB.Tangent = _VertexB.Position - _VertexA.Position;
					_VertexC.Tangent = _VertexB.Position - _VertexA.Position;
				}
			}
			else
			{
				_VertexA.Tangent = _VertexB.Position - _VertexA.Position;
				_VertexB.Tangent = _VertexB.Position - _VertexA.Position;
				_VertexC.Tangent = _VertexB.Position - _VertexA.Position;
			}

			_Mesh.TriangleVBO.PushBack(_VertexA);
			_Mesh.TriangleVBO.PushBack(_VertexB);
			_Mesh.TriangleVBO.PushBack(_VertexC);

			_Mesh.TriangleIBO.PushBack(TriangleIndexData((uint32_t)(_Mesh.TriangleVBO.GetSize() - 3), (uint32_t)(_Mesh.TriangleVBO.GetSize() - 2), (uint32_t)(_Mesh.TriangleVBO.GetSize() - 1)));
		}

		for (size_t _LineIndex = _LineStarts[_NameIndex]; _LineIndex < _LineStarts[_NameIndex + 1]; _LineIndex++)
		{
			Vector<size_t>& _CurrentLinePositions = _LinePositions[_LineIndex];
			Vector<size_t>& _CurrentLineTextureCoords = _LineTextureCoords[_LineIndex];

			LineVertexData _VertexA;
			LineVertexData _VertexB;

			_VertexA.Position = _Positions[_LinePositions[_LineIndex][0]];
			_VertexA.Color = _Colors[_LinePositions[_LineIndex][0]];

			_VertexB.Position = _Positions[_LinePositions[_LineIndex][1]];
			_VertexB.Color = _Colors[_LinePositions[_LineIndex][1]];

			if (_LineTextureCoords[_LineIndex][0] != std::numeric_limits<size_t>::max())
			{
				_VertexA.TextureCoords = _TextureCoords[_LineTextureCoords[_LineIndex][0]];
			}

			if (_LineTextureCoords[_LineIndex][1] != std::numeric_limits<size_t>::max())
			{
				_VertexB.TextureCoords = _TextureCoords[_LineTextureCoords[_LineIndex][1]];
			}

			_Mesh.LineVBO.PushBack(_VertexA);
			_Mesh.LineVBO.PushBack(_VertexB);

			_Mesh.LineIBO.PushBack(LineIndexData((uint32_t)(_Mesh.LineVBO.GetSize() - 2), (uint32_t)(_Mesh.LineVBO.GetSize() - 1)));
		}

		MeshNames.PushBack(_Names[_NameIndex]);
		Meshes.Emplace(_Names[_NameIndex].c_str(), (Mesh&&)(_Mesh));
	}

	return true;
}

BFW::Assets::Mesh& BFW::Assets::WaveFrontObj::Push(const BFW_CHAR_TYPE* _Name, const Mesh& _Data)
{
	if (!_Name || _Name[0] == '\0')
	{
		throw nullptr;
	}

	bool _Found = false;

	for (size_t _Index = 0; _Index < MeshNames.GetSize(); _Index++)
	{
		if (MeshNames[_Index] == _Name)
		{
			_Found = true;
			break;
		}
	}

	if (!_Found)
	{
		MeshNames.EmplaceBack(_Name);
	}

	return Meshes.Push(_Name, _Data);
}

BFW::Assets::Mesh& BFW::Assets::WaveFrontObj::Emplace(const BFW_CHAR_TYPE* _Name, Mesh&& _Data)
{
	if (!_Name || _Name[0] == '\0')
	{
		throw nullptr;
	}

	bool _Found = false;

	for (size_t _Index = 0; _Index < MeshNames.GetSize(); _Index++)
	{
		if (MeshNames[_Index] == _Name)
		{
			_Found = true;
			break;
		}
	}

	if (!_Found)
	{
		MeshNames.EmplaceBack(_Name);
	}

	return Meshes.Emplace(_Name, (Mesh&&)(_Data));
}

void BFW::Assets::WaveFrontObj::Erase(const BFW_CHAR_TYPE* _Name)
{
	if (!_Name || _Name[0] == '\0')
	{
		throw nullptr;
	}

	for (size_t _Index = 0; _Index < MeshNames.GetSize(); _Index++)
	{
		if (MeshNames[_Index] == _Name)
		{
			MeshNames.Erase(_Index);
			break;
		}
	}

	Meshes.Erase(_Name);
}

void BFW::Assets::WaveFrontObj::Clear()
{
	MeshNames.Clear();
	Meshes.Clear();
}

BFW::Assets::FileContent BFW::Assets::WaveFrontObj::Save() const
{
	if (!MeshNames.GetSize())
	{
		return FileContent();
	}

	//...;

	BFW_STRING_STREAM_TYPE_A _Stream;

	//...;

	BFW_STRING_TYPE_A _String = _Stream.str();

	FileContent _FileContent;

	if (!_FileContent.Create(_String.size() + 1))
	{
		return FileContent();
	}

	_FileContent[_FileContent.GetLength() - 1] = '\0';

	for (size_t _Index = 0; _Index < _String.size(); _Index++)
	{
		_FileContent[_Index] = _String[_Index];
	}

	return _FileContent;
}

const BFW::Vector<BFW_STRING_TYPE>& BFW::Assets::WaveFrontObj::GetMeshNames() const
{
	return MeshNames;
}

BFW::Assets::Mesh* BFW::Assets::WaveFrontObj::GetData(const BFW_CHAR_TYPE* _Name)
{
	if (!_Name || _Name[0] == '\0')
	{
		throw nullptr;
	}

	return Meshes.GetData(_Name);
}

const BFW::Assets::Mesh* BFW::Assets::WaveFrontObj::GetData(const BFW_CHAR_TYPE* _Name) const
{
	if (!_Name || _Name[0] == '\0')
	{
		throw nullptr;
	}

	return Meshes.GetData(_Name);
}

BFW::Assets::Mesh& BFW::Assets::WaveFrontObj::operator[] (const BFW_CHAR_TYPE* _Name)
{
	if (!_Name || _Name[0] == '\0')
	{
		throw nullptr;
	}

	return Meshes[_Name];
}

const BFW::Assets::Mesh& BFW::Assets::WaveFrontObj::operator[] (const BFW_CHAR_TYPE* _Name) const
{
	if (!_Name || _Name[0] == '\0')
	{
		throw nullptr;
	}

	return Meshes[_Name];
}

BFW::Assets::WaveFrontObj& BFW::Assets::WaveFrontObj::operator= (const WaveFrontObj& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	MeshNames = _Other.MeshNames;
	Meshes = _Other.Meshes;

	return *this;
}

BFW::Assets::WaveFrontObj& BFW::Assets::WaveFrontObj::operator= (WaveFrontObj&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	MeshNames = (Vector<BFW_STRING_TYPE>&&)(_Other.MeshNames);
	Meshes = (Trie<Mesh>&&)(_Other.Meshes);

	return *this;
}
