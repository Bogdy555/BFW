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



BFW::Assets::Mesh::Mesh() : MaterialName(BFW_STRING_PREFIX("")), TriangleVBO(), TriangleIBO(), LineVBO(), LineIBO()
{

}

BFW::Assets::Mesh::Mesh(const Mesh& _Other) : MaterialName(_Other.MaterialName), TriangleVBO(_Other.TriangleVBO), TriangleIBO(_Other.TriangleIBO), LineVBO(_Other.LineVBO), LineIBO(_Other.LineIBO)
{

}

BFW::Assets::Mesh::Mesh(Mesh&& _Other) noexcept : MaterialName(_Other.MaterialName), TriangleVBO((Vector<TriangleVertexData>&&)(_Other.TriangleVBO)), TriangleIBO((Vector<TriangleIndexData>&&)(_Other.TriangleIBO)), LineVBO((Vector<LineVertexData>&&)(_Other.LineVBO)), LineIBO((Vector<LineIndexData>&&)(_Other.LineIBO))
{
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

	MaterialName = _Other.MaterialName;
	TriangleVBO = (Vector<TriangleVertexData>&&)(_Other.TriangleVBO);
	TriangleIBO = (Vector<TriangleIndexData>&&)(_Other.TriangleIBO);
	LineVBO = (Vector<LineVertexData>&&)(_Other.LineVBO);
	LineIBO = (Vector<LineIndexData>&&)(_Other.LineIBO);

	_Other.MaterialName = BFW_STRING_PREFIX("");

	return *this;
}



BFW::Assets::WaveFrontObj::WaveFrontObj() : MeshNames(), Meshes(), MaterialLibs()
{

}

BFW::Assets::WaveFrontObj::WaveFrontObj(const WaveFrontObj& _Other) : MeshNames(_Other.MeshNames), Meshes(_Other.Meshes), MaterialLibs(_Other.MaterialLibs)
{

}

BFW::Assets::WaveFrontObj::WaveFrontObj(WaveFrontObj&& _Other) noexcept : MeshNames((Vector<BFW_STRING_TYPE>&&)(_Other.MeshNames)), Meshes((Trie<Mesh>&&)(_Other.Meshes)), MaterialLibs((Vector<BFW_STRING_TYPE>&&)(_Other.MaterialLibs))
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

	Vector<BFW_STRING_TYPE> _MaterialLibs;

	Vector<BFW_STRING_TYPE> _Names;
	Vector<BFW_STRING_TYPE> _MaterialNames;
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
			_MaterialNames.PushBack(BFW_STRING_TYPE(BFW_STRING_PREFIX("")));
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

		if (_LineTokens[0] == "mtllib")
		{
			if (_LineTokens.GetSize() != 2)
			{
				return false;
			}

			bool _Error = false;

			_MaterialLibs.PushBack(BFW_UTF8_TO_MACHINE(_LineTokens[1], &_Error));

			if (_Error)
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "usemtl")
		{
			if (_LineTokens.GetSize() != 2 || _MaterialNames.GetSize() == 0)
			{
				return false;
			}

			bool _Error = false;

			_MaterialNames[_MaterialNames.GetSize() - 1] = BFW_UTF8_TO_MACHINE(_LineTokens[1], &_Error);

			if (_Error)
			{
				return false;
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

		_Mesh.MaterialName = _MaterialNames[_NameIndex];

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

	MaterialLibs = (Vector<BFW_STRING_TYPE>&&)(_MaterialLibs);

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
	MaterialLibs.Clear();
}

BFW::Assets::FileContent BFW::Assets::WaveFrontObj::Save(const bool _SaveColors, const bool _SaveNormals, const bool _SaveTextureCoords, const bool _SaveMaterials) const
{
	if (!MeshNames.GetSize())
	{
		return FileContent();
	}

	size_t _GlobalIndex = 0;

	BFW_STRING_STREAM_TYPE_A _Stream;

	if (_SaveMaterials)
	{
		for (size_t _Index = 0; _Index < MaterialLibs.GetSize(); _Index++)
		{
			bool _Error = false;

			_Stream << "mtllib " << BFW_MACHINE_TO_UTF8(MaterialLibs[_Index], &_Error) BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';

			if (_Error)
			{
				return FileContent();
			}
		}
	}

	for (size_t _NameIndex = 0; _NameIndex < MeshNames.GetSize(); _NameIndex++)
	{
		const Mesh& _CurrentMesh = *Meshes.GetData(MeshNames[_NameIndex].c_str());

		bool _Error = false;

		_Stream << "o " << BFW_MACHINE_TO_UTF8(MeshNames[_NameIndex], &_Error) BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';

		if (_Error)
		{
			return FileContent();
		}

		if (_CurrentMesh.MaterialName.size() && _SaveMaterials)
		{
			_Stream << "usemtl " << BFW_MACHINE_TO_UTF8(_CurrentMesh.MaterialName, &_Error) BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';

			if (_Error)
			{
				return FileContent();
			}
		}

		for (size_t _VBOIndex = 0; _VBOIndex < _CurrentMesh.TriangleVBO.GetSize(); _VBOIndex++)
		{
			const TriangleVertexData& _CurrentVO = _CurrentMesh.TriangleVBO[_VBOIndex];

			if (_SaveColors)
			{
				_Stream << "v " <<
					_CurrentVO.Position.x << ' ' << _CurrentVO.Position.y << ' ' << _CurrentVO.Position.z << ' ' <<
					_CurrentVO.Color.x << ' ' << _CurrentVO.Color.y << ' ' << _CurrentVO.Color.z
					BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
			}
			else
			{
				_Stream << "v " << _CurrentVO.Position.x << ' ' << _CurrentVO.Position.y << ' ' << _CurrentVO.Position.z << ' ' << _CurrentVO.Position.w BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
			}

			if (_SaveNormals)
			{
				_Stream << "vn " << _CurrentVO.Normal.x << ' ' << _CurrentVO.Normal.y << ' ' << _CurrentVO.Normal.z BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
			}

			if (_SaveTextureCoords)
			{
				_Stream << "vt " << _CurrentVO.TextureCoords.x << ' ' << _CurrentVO.TextureCoords.y << ' ' << _CurrentVO.TextureCoords.z BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
			}
		}

		for (size_t _IBOIndex = 0; _IBOIndex < _CurrentMesh.TriangleIBO.GetSize(); _IBOIndex++)
		{
			const TriangleIndexData& _CurrentIO = _CurrentMesh.TriangleIBO[_IBOIndex];

			if (_CurrentIO.IndexA >= _CurrentMesh.TriangleVBO.GetSize() || _CurrentIO.IndexB >= _CurrentMesh.TriangleVBO.GetSize() || _CurrentIO.IndexC >= _CurrentMesh.TriangleVBO.GetSize())
			{
				return FileContent();
			}

			if (_SaveTextureCoords)
			{
				if (_SaveNormals)
				{
					_Stream << "f " <<
						_CurrentIO.IndexA + _GlobalIndex + 1 << '/' << _CurrentIO.IndexA + _GlobalIndex + 1 << '/' << _CurrentIO.IndexA + _GlobalIndex + 1 << ' ' <<
						_CurrentIO.IndexB + _GlobalIndex + 1 << '/' << _CurrentIO.IndexB + _GlobalIndex + 1 << '/' << _CurrentIO.IndexB + _GlobalIndex + 1 << ' ' <<
						_CurrentIO.IndexC + _GlobalIndex + 1 << '/' << _CurrentIO.IndexC + _GlobalIndex + 1 << '/' << _CurrentIO.IndexC + _GlobalIndex + 1
						BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
				}
				else
				{
					_Stream << "f " <<
						_CurrentIO.IndexA + _GlobalIndex + 1 << '/' << _CurrentIO.IndexA + _GlobalIndex + 1 << ' ' <<
						_CurrentIO.IndexB + _GlobalIndex + 1 << '/' << _CurrentIO.IndexB + _GlobalIndex + 1 << ' ' <<
						_CurrentIO.IndexC + _GlobalIndex + 1 << '/' << _CurrentIO.IndexC + _GlobalIndex + 1
						BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
				}
			}
			else
			{
				if (_SaveNormals)
				{
					_Stream << "f " <<
						_CurrentIO.IndexA + _GlobalIndex + 1 << "//" << _CurrentIO.IndexA + _GlobalIndex + 1 << ' ' <<
						_CurrentIO.IndexB + _GlobalIndex + 1 << "//" << _CurrentIO.IndexB + _GlobalIndex + 1 << ' ' <<
						_CurrentIO.IndexC + _GlobalIndex + 1 << "//" << _CurrentIO.IndexC + _GlobalIndex + 1
						BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
				}
				else
				{
					_Stream << "f " <<
						_CurrentIO.IndexA + _GlobalIndex + 1 << ' ' <<
						_CurrentIO.IndexB + _GlobalIndex + 1 << ' ' <<
						_CurrentIO.IndexC + _GlobalIndex + 1
						BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
				}
			}
		}

		_GlobalIndex += _CurrentMesh.TriangleVBO.GetSize();

		for (size_t _VBOIndex = 0; _VBOIndex < _CurrentMesh.LineVBO.GetSize(); _VBOIndex++)
		{
			const LineVertexData& _CurrentVO = _CurrentMesh.LineVBO[_VBOIndex];

			if (_SaveColors)
			{
				_Stream << "v " <<
					_CurrentVO.Position.x << ' ' << _CurrentVO.Position.y << ' ' << _CurrentVO.Position.z << ' ' <<
					_CurrentVO.Color.x << ' ' << _CurrentVO.Color.y << ' ' << _CurrentVO.Color.z
					BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
			}
			else
			{
				_Stream << "v " << _CurrentVO.Position.x << ' ' << _CurrentVO.Position.y << ' ' << _CurrentVO.Position.z << ' ' << _CurrentVO.Position.w BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
			}

			if (_SaveTextureCoords)
			{
				_Stream << "vt " << _CurrentVO.TextureCoords.x << ' ' << _CurrentVO.TextureCoords.y << ' ' << _CurrentVO.TextureCoords.z BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
			}
		}

		for (size_t _IBOIndex = 0; _IBOIndex < _CurrentMesh.LineIBO.GetSize(); _IBOIndex++)
		{
			const LineIndexData& _CurrentIO = _CurrentMesh.LineIBO[_IBOIndex];

			if (_CurrentIO.IndexA >= _CurrentMesh.LineVBO.GetSize() || _CurrentIO.IndexB >= _CurrentMesh.LineVBO.GetSize())
			{
				return FileContent();
			}

			if (_SaveTextureCoords)
			{
				_Stream << "l " <<
					_CurrentIO.IndexA + _GlobalIndex + 1 << '/' << _CurrentIO.IndexA + _GlobalIndex + 1 << ' ' <<
					_CurrentIO.IndexB + _GlobalIndex + 1 << '/' << _CurrentIO.IndexB + _GlobalIndex + 1
					BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
			}
			else
			{
				_Stream << "l " <<
					_CurrentIO.IndexA + _GlobalIndex + 1 << ' ' <<
					_CurrentIO.IndexB + _GlobalIndex + 1
					BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
			}
		}

		_GlobalIndex += _CurrentMesh.LineVBO.GetSize();
	}

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

BFW::Vector<BFW_STRING_TYPE>& BFW::Assets::WaveFrontObj::GetMaterialLibs()
{
	return MaterialLibs;
}

const BFW::Vector<BFW_STRING_TYPE>& BFW::Assets::WaveFrontObj::GetMaterialLibs() const
{
	return MaterialLibs;
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
	MaterialLibs = _Other.MaterialLibs;

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
	MaterialLibs = (Vector<BFW_STRING_TYPE>&&)(_Other.MaterialLibs);

	return *this;
}



BFW::Assets::TextureSettings::TextureSettings() : BlendU(true), BlendV(true), Clamp(false), Channel('l'), Boost(0.0f), Brightness(0.0f), Contrast(1.0f), Offset(Math::Vec3(0.0f, 0.0f, 0.0f)), Scale(Math::Vec3(1.0f, 1.0f, 1.0f)), Turbulance(Math::Vec3(0.0f, 0.0f, 0.0f)), Resolution(0), BumpMultiplier(1.0f), ReflectionType(BFW_STRING_PREFIX("sphere"))
{

}

BFW::Assets::TextureSettings::TextureSettings(TextureSettings&& _Other) noexcept : BlendU(_Other.BlendU), BlendV(_Other.BlendV), Clamp(_Other.Clamp), Channel(_Other.Channel), Boost(_Other.Boost), Brightness(_Other.Brightness), Contrast(_Other.Contrast), Offset(_Other.Offset), Scale(_Other.Scale), Turbulance(_Other.Turbulance), Resolution(_Other.Resolution), BumpMultiplier(_Other.BumpMultiplier), ReflectionType(_Other.ReflectionType)
{
	_Other.BlendU = true;
	_Other.BlendV = true;
	_Other.Clamp = false;
	_Other.Channel = 'l';
	_Other.Boost = 0.0f;
	_Other.Brightness = 0.0f;
	_Other.Contrast = 1.0f;
	_Other.Offset = Math::Vec3(0.0f, 0.0f, 0.0f);
	_Other.Scale = Math::Vec3(1.0f, 1.0f, 1.0f);
	_Other.Turbulance = Math::Vec3(0.0f, 0.0f, 0.0f);
	_Other.Resolution = 0;
	_Other.BumpMultiplier = 1.0f;
	_Other.ReflectionType = BFW_STRING_PREFIX("sphere");
}

BFW::Assets::TextureSettings& BFW::Assets::TextureSettings::operator= (TextureSettings&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	BlendU = _Other.BlendU;
	BlendV = _Other.BlendV;
	Clamp = _Other.Clamp;
	Channel = _Other.Channel;
	Boost = _Other.Boost;
	Brightness = _Other.Brightness;
	Contrast = _Other.Contrast;
	Offset = _Other.Offset;
	Scale = _Other.Scale;
	Turbulance = _Other.Turbulance;
	Resolution = _Other.Resolution;
	BumpMultiplier = _Other.BumpMultiplier;
	ReflectionType = _Other.ReflectionType;

	_Other.BlendU = true;
	_Other.BlendV = true;
	_Other.Clamp = false;
	_Other.Channel = 'l';
	_Other.Boost = 0.0f;
	_Other.Brightness = 0.0f;
	_Other.Contrast = 1.0f;
	_Other.Offset = Math::Vec3(0.0f, 0.0f, 0.0f);
	_Other.Scale = Math::Vec3(1.0f, 1.0f, 1.0f);
	_Other.Turbulance = Math::Vec3(0.0f, 0.0f, 0.0f);
	_Other.Resolution = 0;
	_Other.BumpMultiplier = 1.0f;
	_Other.ReflectionType = BFW_STRING_PREFIX("sphere");

	return *this;
}



BFW::Assets::Material::Material() :
	DiffuseColor(Math::Vec3(1.0f, 1.0f, 1.0f)),
	SpecularColor(Math::Vec3(1.0f, 1.0f, 1.0f)),
	SpecularExponent(1.0f),
	EmissionColor(Math::Vec3(0.0f, 0.0f, 0.0f)),
	Roughness(0.0f),
	Metalness(0.0f),
	AmbientOcclusion(1.0f),
	AmbientColor(Math::Vec3(1.0f, 1.0f, 1.0f)),
	Sheen(0.0f),
	SheenColor(Math::Vec3(1.0f, 1.0f, 1.0f)),
	ClearCoat(0.0f),
	ClearCoatColor(Math::Vec3(1.0f, 1.0f, 1.0f)),
	ClearCoatRoughness(0.0f),
	Anisotropy(0.0f),
	AnisotropyRotation(0.0f),
	Alpha(1.0f),
	TransmissionFilter(Math::Vec3(1.0f, 1.0f, 1.0f)),
	IndexOfRefraction(1.0f),
	Displacement(0.0f),
	IlluminationModel(9),
	Normal(Math::Vec3(0.5f, 0.5f, 1.0f)),
	Tangent(Math::Vec3(1.0f, 0.5f, 0.5f)),
	ClearCoatNormal(Math::Vec3(0.5f, 0.5f, 1.0f)),

	DiffuseColorTexture(BFW_STRING_PREFIX("")),
	SpecularColorTexture(BFW_STRING_PREFIX("")),
	SpecularExponentTexture(BFW_STRING_PREFIX("")),
	EmissionColorTexture(BFW_STRING_PREFIX("")),
	RoughnessTexture(BFW_STRING_PREFIX("")),
	MetalnessTexture(BFW_STRING_PREFIX("")),
	AmbientOcclusionTexture(BFW_STRING_PREFIX("")),
	AmbientColorTexture(BFW_STRING_PREFIX("")),
	SheenTexture(BFW_STRING_PREFIX("")),
	SheenColorTexture(BFW_STRING_PREFIX("")),
	ClearCoatTexture(BFW_STRING_PREFIX("")),
	ClearCoatColorTexture(BFW_STRING_PREFIX("")),
	ClearCoatRoughnessTexture(BFW_STRING_PREFIX("")),
	AnisotropyTexture(BFW_STRING_PREFIX("")),
	AnisotropyRotationTexture(BFW_STRING_PREFIX("")),
	AlphaTexture(BFW_STRING_PREFIX("")),
	TransmissionFilterTexture(BFW_STRING_PREFIX("")),
	DisplacementTexture(BFW_STRING_PREFIX("")),
	NormalTexture(BFW_STRING_PREFIX("")),
	TangentTexture(BFW_STRING_PREFIX("")),
	ClearCoatNormalTexture(BFW_STRING_PREFIX("")),
	DecalTexture(BFW_STRING_PREFIX("")),
	BumpTexture(BFW_STRING_PREFIX("")),
	ReflectionTextures({ BFW_STRING_PREFIX("") }),

	DiffuseColorTextureSettings(),
	SpecularColorTextureSettings(),
	SpecularExponentTextureSettings(),
	EmissionColorTextureSettings(),
	RoughnessTextureSettings(),
	MetalnessTextureSettings(),
	AmbientOcclusionTextureSettings(),
	AmbientColorTextureSettings(),
	SheenTextureSettings(),
	SheenColorTextureSettings(),
	ClearCoatTextureSettings(),
	ClearCoatColorTextureSettings(),
	ClearCoatRoughnessTextureSettings(),
	AnisotropyTextureSettings(),
	AnisotropyRotationTextureSettings(),
	AlphaTextureSettings(),
	TransmissionFilterTextureSettings(),
	DisplacementTextureSettings(),
	NormalTextureSettings(),
	TangentTextureSettings(),
	ClearCoatNormalTextureSettings(),
	DecalTextureSettings(),
	BumpTextureSettings(),
	ReflectionTextureSettings(1)
{
	DecalTextureSettings.Channel = 'm';
}

BFW::Assets::Material::Material(Material&& _Other) noexcept :
	DiffuseColor(_Other.DiffuseColor),
	SpecularColor(_Other.SpecularColor),
	SpecularExponent(_Other.SpecularExponent),
	EmissionColor(_Other.EmissionColor),
	Roughness(_Other.Roughness),
	Metalness(_Other.Metalness),
	AmbientOcclusion(_Other.AmbientOcclusion),
	AmbientColor(_Other.AmbientColor),
	Sheen(_Other.Sheen),
	SheenColor(_Other.SheenColor),
	ClearCoat(_Other.ClearCoat),
	ClearCoatColor(_Other.ClearCoatColor),
	ClearCoatRoughness(_Other.ClearCoatRoughness),
	Anisotropy(_Other.Anisotropy),
	AnisotropyRotation(_Other.AnisotropyRotation),
	Alpha(_Other.Alpha),
	TransmissionFilter(_Other.TransmissionFilter),
	IndexOfRefraction(_Other.IndexOfRefraction),
	Displacement(_Other.Displacement),
	IlluminationModel(_Other.IlluminationModel),
	Normal(_Other.Normal),
	Tangent(_Other.Tangent),
	ClearCoatNormal(_Other.ClearCoatNormal),

	DiffuseColorTexture(_Other.DiffuseColorTexture),
	SpecularColorTexture(_Other.SpecularColorTexture),
	SpecularExponentTexture(_Other.SpecularExponentTexture),
	EmissionColorTexture(_Other.EmissionColorTexture),
	RoughnessTexture(_Other.RoughnessTexture),
	MetalnessTexture(_Other.MetalnessTexture),
	AmbientOcclusionTexture(_Other.AmbientOcclusionTexture),
	AmbientColorTexture(_Other.AmbientColorTexture),
	SheenTexture(_Other.SheenTexture),
	SheenColorTexture(_Other.SheenColorTexture),
	ClearCoatTexture(_Other.ClearCoatTexture),
	ClearCoatColorTexture(_Other.ClearCoatColorTexture),
	ClearCoatRoughnessTexture(_Other.ClearCoatRoughnessTexture),
	AnisotropyTexture(_Other.AnisotropyTexture),
	AnisotropyRotationTexture(_Other.AnisotropyRotationTexture),
	AlphaTexture(_Other.AlphaTexture),
	TransmissionFilterTexture(_Other.TransmissionFilterTexture),
	DisplacementTexture(_Other.DisplacementTexture),
	NormalTexture(_Other.NormalTexture),
	TangentTexture(_Other.TangentTexture),
	ClearCoatNormalTexture(_Other.ClearCoatNormalTexture),
	DecalTexture(_Other.DecalTexture),
	BumpTexture(_Other.BumpTexture),
	ReflectionTextures(_Other.ReflectionTextures),

	DiffuseColorTextureSettings(_Other.DiffuseColorTextureSettings),
	SpecularColorTextureSettings(_Other.SpecularColorTextureSettings),
	SpecularExponentTextureSettings(_Other.SpecularExponentTextureSettings),
	EmissionColorTextureSettings(_Other.EmissionColorTextureSettings),
	RoughnessTextureSettings(_Other.RoughnessTextureSettings),
	MetalnessTextureSettings(_Other.MetalnessTextureSettings),
	AmbientOcclusionTextureSettings(_Other.AmbientOcclusionTextureSettings),
	AmbientColorTextureSettings(_Other.AmbientColorTextureSettings),
	SheenTextureSettings(_Other.SheenTextureSettings),
	SheenColorTextureSettings(_Other.SheenColorTextureSettings),
	ClearCoatTextureSettings(_Other.ClearCoatTextureSettings),
	ClearCoatColorTextureSettings(_Other.ClearCoatColorTextureSettings),
	ClearCoatRoughnessTextureSettings(_Other.ClearCoatRoughnessTextureSettings),
	AnisotropyTextureSettings(_Other.AnisotropyTextureSettings),
	AnisotropyRotationTextureSettings(_Other.AnisotropyRotationTextureSettings),
	AlphaTextureSettings(_Other.AlphaTextureSettings),
	TransmissionFilterTextureSettings(_Other.TransmissionFilterTextureSettings),
	DisplacementTextureSettings(_Other.DisplacementTextureSettings),
	NormalTextureSettings(_Other.NormalTextureSettings),
	TangentTextureSettings(_Other.TangentTextureSettings),
	ClearCoatNormalTextureSettings(_Other.ClearCoatNormalTextureSettings),
	DecalTextureSettings(_Other.DecalTextureSettings),
	BumpTextureSettings(_Other.BumpTextureSettings),
	ReflectionTextureSettings(_Other.ReflectionTextureSettings)
{
	_Other = Material();
}

BFW::Assets::Material& BFW::Assets::Material::operator= (Material&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	DiffuseColor = _Other.DiffuseColor;
	SpecularColor = _Other.SpecularColor;
	SpecularExponent = _Other.SpecularExponent;
	EmissionColor = _Other.EmissionColor;
	Roughness = _Other.Roughness;
	Metalness = _Other.Metalness;
	AmbientOcclusion = _Other.AmbientOcclusion;
	AmbientColor = _Other.AmbientColor;
	Sheen = _Other.Sheen;
	SheenColor = _Other.SheenColor;
	ClearCoat = _Other.ClearCoat;
	ClearCoatColor = _Other.ClearCoatColor;
	ClearCoatRoughness = _Other.ClearCoatRoughness;
	Anisotropy = _Other.Anisotropy;
	AnisotropyRotation = _Other.AnisotropyRotation;
	Alpha = _Other.Alpha;
	TransmissionFilter = _Other.TransmissionFilter;
	IndexOfRefraction = _Other.IndexOfRefraction;
	Displacement = _Other.Displacement;
	IlluminationModel = _Other.IlluminationModel;
	Normal = _Other.Normal;
	Tangent = _Other.Tangent;
	ClearCoatNormal = _Other.ClearCoatNormal;

	DiffuseColorTexture = _Other.DiffuseColorTexture;
	SpecularColorTexture = _Other.SpecularColorTexture;
	SpecularExponentTexture = _Other.SpecularExponentTexture;
	EmissionColorTexture = _Other.EmissionColorTexture;
	RoughnessTexture = _Other.RoughnessTexture;
	MetalnessTexture = _Other.MetalnessTexture;
	AmbientOcclusionTexture = _Other.AmbientOcclusionTexture;
	AmbientColorTexture = _Other.AmbientColorTexture;
	SheenTexture = _Other.SheenTexture;
	SheenColorTexture = _Other.SheenColorTexture;
	ClearCoatTexture = _Other.ClearCoatTexture;
	ClearCoatColorTexture = _Other.ClearCoatColorTexture;
	ClearCoatRoughnessTexture = _Other.ClearCoatRoughnessTexture;
	AnisotropyTexture = _Other.AnisotropyTexture;
	AnisotropyRotationTexture = _Other.AnisotropyRotationTexture;
	AlphaTexture = _Other.AlphaTexture;
	TransmissionFilterTexture = _Other.TransmissionFilterTexture;
	DisplacementTexture = _Other.DisplacementTexture;
	NormalTexture = _Other.NormalTexture;
	TangentTexture = _Other.TangentTexture;
	ClearCoatNormalTexture = _Other.ClearCoatNormalTexture;
	DecalTexture = _Other.DecalTexture;
	BumpTexture = _Other.BumpTexture;
	ReflectionTextures = _Other.ReflectionTextures;

	DiffuseColorTextureSettings = _Other.DiffuseColorTextureSettings;
	SpecularColorTextureSettings = _Other.SpecularColorTextureSettings;
	SpecularExponentTextureSettings = _Other.SpecularExponentTextureSettings;
	EmissionColorTextureSettings = _Other.EmissionColorTextureSettings;
	RoughnessTextureSettings = _Other.RoughnessTextureSettings;
	MetalnessTextureSettings = _Other.MetalnessTextureSettings;
	AmbientOcclusionTextureSettings = _Other.AmbientOcclusionTextureSettings;
	AmbientColorTextureSettings = _Other.AmbientColorTextureSettings;
	SheenTextureSettings = _Other.SheenTextureSettings;
	SheenColorTextureSettings = _Other.SheenColorTextureSettings;
	ClearCoatTextureSettings = _Other.ClearCoatTextureSettings;
	ClearCoatColorTextureSettings = _Other.ClearCoatColorTextureSettings;
	ClearCoatRoughnessTextureSettings = _Other.ClearCoatRoughnessTextureSettings;
	AnisotropyTextureSettings = _Other.AnisotropyTextureSettings;
	AnisotropyRotationTextureSettings = _Other.AnisotropyRotationTextureSettings;
	AlphaTextureSettings = _Other.AlphaTextureSettings;
	TransmissionFilterTextureSettings = _Other.TransmissionFilterTextureSettings;
	DisplacementTextureSettings = _Other.DisplacementTextureSettings;
	NormalTextureSettings = _Other.NormalTextureSettings;
	TangentTextureSettings = _Other.TangentTextureSettings;
	ClearCoatNormalTextureSettings = _Other.ClearCoatNormalTextureSettings;
	DecalTextureSettings = _Other.DecalTextureSettings;
	BumpTextureSettings = _Other.BumpTextureSettings;
	ReflectionTextureSettings = _Other.ReflectionTextureSettings;

	_Other = Material();

	return *this;
}



BFW::Assets::MaterialLib::MaterialLib() : MaterialNames(), Materials()
{

}

BFW::Assets::MaterialLib::MaterialLib(const MaterialLib& _Other) : MaterialNames(_Other.MaterialNames), Materials(_Other.Materials)
{

}

BFW::Assets::MaterialLib::MaterialLib(MaterialLib&& _Other) noexcept : MaterialNames((Vector<BFW_STRING_TYPE>&&)(_Other.MaterialNames)), Materials((Trie<Material>&&)(_Other.Materials))
{

}

BFW::Assets::MaterialLib::~MaterialLib()
{

}

const bool BFW::Assets::MaterialLib::Load(const FileContent& _FileContent)
{
	Clear();

	if (!_FileContent.GetData())
	{
		return false;
	}

	Vector<BFW_STRING_TYPE> _Names;
	Vector<Material> _Materials;

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

		if (_LineTokens[0] == "newmtl")
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
			_Materials.EmplaceBack(Material());

			continue;
		}

		// if no active name in alte case uri atunci error
	}

	if (_FileIndex != _FileContent.GetLength() - 1)
	{
		return false;
	}

	for (size_t _Index = 0; _Index < _Materials.GetSize(); _Index++)
	{
		MaterialNames.PushBack(_Names[_Index]);
		Materials.Emplace(_Names[_Index].c_str(), (Material&&)(_Materials[_Index]));
	}

	return true;
}

BFW::Assets::Material& BFW::Assets::MaterialLib::Push(const BFW_CHAR_TYPE* _Name, const Material& _Data)
{
	if (!_Name || _Name[0] == '\0')
	{
		throw nullptr;
	}

	bool _Found = false;

	for (size_t _Index = 0; _Index < MaterialNames.GetSize(); _Index++)
	{
		if (MaterialNames[_Index] == _Name)
		{
			_Found = true;
			break;
		}
	}

	if (!_Found)
	{
		MaterialNames.EmplaceBack(_Name);
	}

	return Materials.Push(_Name, _Data);
}

BFW::Assets::Material& BFW::Assets::MaterialLib::Emplace(const BFW_CHAR_TYPE* _Name, Material&& _Data)
{
	if (!_Name || _Name[0] == '\0')
	{
		throw nullptr;
	}

	bool _Found = false;

	for (size_t _Index = 0; _Index < MaterialNames.GetSize(); _Index++)
	{
		if (MaterialNames[_Index] == _Name)
		{
			_Found = true;
			break;
		}
	}

	if (!_Found)
	{
		MaterialNames.EmplaceBack(_Name);
	}

	return Materials.Emplace(_Name, (Material&&)(_Data));
}

void BFW::Assets::MaterialLib::Erase(const BFW_CHAR_TYPE* _Name)
{
	if (!_Name || _Name[0] == '\0')
	{
		throw nullptr;
	}

	for (size_t _Index = 0; _Index < MaterialNames.GetSize(); _Index++)
	{
		if (MaterialNames[_Index] == _Name)
		{
			MaterialNames.Erase(_Index);
			break;
		}
	}

	Materials.Erase(_Name);
}

void BFW::Assets::MaterialLib::Clear()
{
	MaterialNames.Clear();
	Materials.Clear();
}

BFW::Assets::FileContent BFW::Assets::MaterialLib::Save() const
{
	...;
}

const BFW::Vector<BFW_STRING_TYPE>& BFW::Assets::MaterialLib::GetMaterialNames() const
{
	return MaterialNames;
}

BFW::Assets::Material* BFW::Assets::MaterialLib::GetData(const BFW_CHAR_TYPE* _Name)
{
	if (!_Name || _Name[0] == '\0')
	{
		throw nullptr;
	}

	return Materials.GetData(_Name);
}

const BFW::Assets::Material* BFW::Assets::MaterialLib::GetData(const BFW_CHAR_TYPE* _Name) const
{
	if (!_Name || _Name[0] == '\0')
	{
		throw nullptr;
	}

	return Materials.GetData(_Name);
}

BFW::Assets::Material& BFW::Assets::MaterialLib::operator[] (const BFW_CHAR_TYPE* _Name)
{
	if (!_Name || _Name[0] == '\0')
	{
		throw nullptr;
	}

	return Materials[_Name];
}

const BFW::Assets::Material& BFW::Assets::MaterialLib::operator[] (const BFW_CHAR_TYPE* _Name) const
{
	if (!_Name || _Name[0] == '\0')
	{
		throw nullptr;
	}

	return Materials[_Name];
}

BFW::Assets::MaterialLib& BFW::Assets::MaterialLib::operator= (const MaterialLib& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	MaterialNames = _Other.MaterialNames;
	Materials = _Other.Materials;

	return *this;
}

BFW::Assets::MaterialLib& BFW::Assets::MaterialLib::operator= (MaterialLib&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	MaterialNames = (Vector<BFW_STRING_TYPE>&&)(_Other.MaterialNames);
	Materials = (Trie<Material>&&)(_Other.Materials);

	return *this;
}
