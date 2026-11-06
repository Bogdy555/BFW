#include "../Headers/BFW.hpp"



static const bool WaveFrontSaveString(BFW_STRING_STREAM_TYPE_A& _Stream, const BFW_STRING_TYPE& _String)
{
	bool _Error = false;

	BFW_STRING_TYPE_A _NewString = BFW_MACHINE_TO_UTF8(_String, &_Error);

	if (_Error || !_NewString.size())
	{
		return false;
	}

	_Stream << '\"';

	for (size_t _Index = 0; _Index < _NewString.size(); _Index++)
	{
		if (BFW::String::IsControlCharacter(_NewString[_Index]))
		{
			return false;
		}

		if (_NewString[_Index] == '\"')
		{
			_Stream << '\\' << '\"';
			continue;
		}

		_Stream << _NewString[_Index];
	}

	_Stream << '\"';

	return true;
}

static const bool MaterialLibLoadMap(const BFW::Vector<BFW_STRING_TYPE_A>& _LineTokens, const BFW_CHAR_TYPE_A* _Type, BFW_STRING_TYPE& _Texture, BFW::Assets::TextureSettings& _TextureSettings)
{
	bool _Found_blendu = false;
	bool _Found_blendv = false;
	bool _Found_clamp = false;
	bool _Found_imfchan = false;
	bool _Found_boost = false;
	bool _Found_mm = false;
	bool _Found_o = false;
	bool _Found_s = false;
	bool _Found_t = false;
	bool _Found_texres = false;
	bool _Found_bm = false;
	bool _Found_type = false;

	for (size_t _TokenIndex = 1; _TokenIndex < _LineTokens.GetSize() - 1; _TokenIndex++)
	{
		if (_LineTokens[_TokenIndex] == "-blendu")
		{
			if (_LineTokens.GetSize() < _TokenIndex + 2 + 1 || _Found_blendu)
			{
				return false;
			}

			_Found_blendu = true;

			if (_LineTokens[_TokenIndex + 1] == "1")
			{
				_TextureSettings.BlendU = true;
			}
			else if (_LineTokens[_TokenIndex + 1] == "0")
			{
				_TextureSettings.BlendU = false;
			}
			else
			{
				return false;
			}

			_TokenIndex += 1;

			continue;
		}

		if (_LineTokens[_TokenIndex] == "-blendv")
		{
			if (_LineTokens.GetSize() < _TokenIndex + 2 + 1 || _Found_blendv)
			{
				return false;
			}

			_Found_blendv = true;

			if (_LineTokens[_TokenIndex + 1] == "1")
			{
				_TextureSettings.BlendV = true;
			}
			else if (_LineTokens[_TokenIndex + 1] == "0")
			{
				_TextureSettings.BlendV = false;
			}
			else
			{
				return false;
			}

			_TokenIndex += 1;

			continue;
		}

		if (_LineTokens[_TokenIndex] == "-clamp")
		{
			if (_LineTokens.GetSize() < _TokenIndex + 2 + 1 || _Found_clamp)
			{
				return false;
			}

			_Found_clamp = true;

			if (_LineTokens[_TokenIndex + 1] == "1")
			{
				_TextureSettings.Clamp = true;
			}
			else if (_LineTokens[_TokenIndex + 1] == "0")
			{
				_TextureSettings.Clamp = false;
			}
			else
			{
				return false;
			}

			_TokenIndex += 1;

			continue;
		}

		if (_LineTokens[_TokenIndex] == "-imfchan")
		{
			if (_LineTokens.GetSize() < _TokenIndex + 2 + 1 || _Found_imfchan)
			{
				return false;
			}

			_Found_imfchan = true;

			if (_LineTokens[_TokenIndex + 1].size() != 1)
			{
				return false;
			}

			_TextureSettings.Channel = _LineTokens[_TokenIndex + 1][0];

			if (_TextureSettings.Channel != 'r' && _TextureSettings.Channel != 'g' && _TextureSettings.Channel != 'b' && _TextureSettings.Channel != 'm' && _TextureSettings.Channel != 'l' && _TextureSettings.Channel != 'z')
			{
				return false;
			}

			_TokenIndex += 1;

			continue;
		}

		if (_LineTokens[_TokenIndex] == "-boost")
		{
			if (_LineTokens.GetSize() < _TokenIndex + 2 + 1 || _Found_boost)
			{
				return false;
			}

			_Found_boost = true;

			BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[_TokenIndex + 1]);

			if (!(_Stream >> _TextureSettings.Boost) || !_Stream.eof() || !std::isfinite(_TextureSettings.Boost))
			{
				return false;
			}

			if (_TextureSettings.Boost < 0.0f)
			{
				return false;
			}

			_TokenIndex += 1;

			continue;
		}

		if (_LineTokens[_TokenIndex] == "-mm")
		{
			if (_LineTokens.GetSize() < _TokenIndex + 2 + 2 || _Found_mm)
			{
				return false;
			}

			_Found_mm = true;

			BFW_STRING_STREAM_TYPE_A _Stream1(_LineTokens[_TokenIndex + 1]);

			if (!(_Stream1 >> _TextureSettings.Base) || !_Stream1.eof() || !std::isfinite(_TextureSettings.Base))
			{
				return false;
			}

			BFW_STRING_STREAM_TYPE_A _Stream2(_LineTokens[_TokenIndex + 2]);

			if (!(_Stream2 >> _TextureSettings.Gain) || !_Stream2.eof() || !std::isfinite(_TextureSettings.Gain))
			{
				return false;
			}

			_TokenIndex += 2;

			continue;
		}

		if (_LineTokens[_TokenIndex] == "-o")
		{
			if (_LineTokens.GetSize() < _TokenIndex + 2 + 3 || _Found_o)
			{
				return false;
			}

			_Found_o = true;

			BFW_STRING_STREAM_TYPE_A _Stream1(_LineTokens[_TokenIndex + 1]);

			if (!(_Stream1 >> _TextureSettings.Offset.x) || !_Stream1.eof() || !std::isfinite(_TextureSettings.Offset.x))
			{
				return false;
			}

			BFW_STRING_STREAM_TYPE_A _Stream2(_LineTokens[_TokenIndex + 2]);

			if (!(_Stream2 >> _TextureSettings.Offset.y) || !_Stream2.eof() || !std::isfinite(_TextureSettings.Offset.y))
			{
				return false;
			}

			BFW_STRING_STREAM_TYPE_A _Stream3(_LineTokens[_TokenIndex + 3]);

			if (!(_Stream3 >> _TextureSettings.Offset.z) || !_Stream3.eof() || !std::isfinite(_TextureSettings.Offset.z))
			{
				return false;
			}

			_TokenIndex += 3;

			continue;
		}

		if (_LineTokens[_TokenIndex] == "-s")
		{
			if (_LineTokens.GetSize() < _TokenIndex + 2 + 3 || _Found_s)
			{
				return false;
			}

			_Found_s = true;

			BFW_STRING_STREAM_TYPE_A _Stream1(_LineTokens[_TokenIndex + 1]);

			if (!(_Stream1 >> _TextureSettings.Scale.x) || !_Stream1.eof() || !std::isfinite(_TextureSettings.Scale.x))
			{
				return false;
			}

			BFW_STRING_STREAM_TYPE_A _Stream2(_LineTokens[_TokenIndex + 2]);

			if (!(_Stream2 >> _TextureSettings.Scale.y) || !_Stream2.eof() || !std::isfinite(_TextureSettings.Scale.y))
			{
				return false;
			}

			BFW_STRING_STREAM_TYPE_A _Stream3(_LineTokens[_TokenIndex + 3]);

			if (!(_Stream3 >> _TextureSettings.Scale.z) || !_Stream3.eof() || !std::isfinite(_TextureSettings.Scale.z))
			{
				return false;
			}

			_TokenIndex += 3;

			continue;
		}

		if (_LineTokens[_TokenIndex] == "-t")
		{
			if (_LineTokens.GetSize() < _TokenIndex + 2 + 3 || _Found_t)
			{
				return false;
			}

			_Found_t = true;

			BFW_STRING_STREAM_TYPE_A _Stream1(_LineTokens[_TokenIndex + 1]);

			if (!(_Stream1 >> _TextureSettings.Turbulence.x) || !_Stream1.eof() || !std::isfinite(_TextureSettings.Turbulence.x))
			{
				return false;
			}

			BFW_STRING_STREAM_TYPE_A _Stream2(_LineTokens[_TokenIndex + 2]);

			if (!(_Stream2 >> _TextureSettings.Turbulence.y) || !_Stream2.eof() || !std::isfinite(_TextureSettings.Turbulence.y))
			{
				return false;
			}

			BFW_STRING_STREAM_TYPE_A _Stream3(_LineTokens[_TokenIndex + 3]);

			if (!(_Stream3 >> _TextureSettings.Turbulence.z) || !_Stream3.eof() || !std::isfinite(_TextureSettings.Turbulence.z))
			{
				return false;
			}

			_TokenIndex += 3;

			continue;
		}

		if (_LineTokens[_TokenIndex] == "-texres")
		{
			if (_LineTokens.GetSize() < _TokenIndex + 2 + 1 || _Found_texres)
			{
				return false;
			}

			_Found_texres = true;

			BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[_TokenIndex + 1]);

			if (!(_Stream >> _TextureSettings.Resolution) || !_Stream.eof())
			{
				return false;
			}

			_TokenIndex += 1;

			continue;
		}

		if (_LineTokens[_TokenIndex] == "-bm")
		{
			if (_LineTokens.GetSize() < _TokenIndex + 2 + 1 || _Found_bm)
			{
				return false;
			}

			_Found_bm = true;

			BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[_TokenIndex + 1]);

			if (!(_Stream >> _TextureSettings.BumpMultiplier) || !_Stream.eof() || !std::isfinite(_TextureSettings.BumpMultiplier))
			{
				return false;
			}

			_TokenIndex += 1;

			continue;
		}

		if (_LineTokens[_TokenIndex] == "-type")
		{
			if (_LineTokens.GetSize() < _TokenIndex + 2 + 1 || _Found_type)
			{
				return false;
			}

			_Found_type = true;

			bool _Error = false;

			_TextureSettings.ReflectionType = BFW_UTF8_TO_MACHINE(_LineTokens[_TokenIndex + 1], &_Error);

			if (_Error)
			{
				return false;
			}

			if (_TextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("sphere")) &&
				_TextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("cube_top")) &&
				_TextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("cube_bottom")) &&
				_TextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("cube_front")) &&
				_TextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("cube_back")) &&
				_TextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("cube_left")) &&
				_TextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("cube_right")))
			{
				return false;
			}

			_TokenIndex += 1;

			continue;
		}

		return false;
	}

	if (BFW_STRING_TYPE_A("refl") == _Type && !_Found_type)
	{
		return false;
	}

	if (BFW_STRING_TYPE_A("bump") != _Type && _Found_bm)
	{
		return false;
	}

	bool _Error = false;

	_Texture = BFW_UTF8_TO_MACHINE(_LineTokens[_LineTokens.GetSize() - 1], &_Error);

	if (_Error)
	{
		return false;
	}

	return true;
}

static const bool MaterialLibSaveMap(BFW_STRING_STREAM_TYPE_A& _Stream, const BFW_CHAR_TYPE_A* _Type, const BFW::Assets::TextureSettings& _TextureSettings, const BFW_STRING_TYPE& _Path)
{
	if (_Path.size() == 0)
	{
		return true;
	}

	_Stream << _Type << ' ';

	if (BFW_STRING_TYPE_A("refl") == _Type)
	{
		_Stream << " -type ";

		if (!WaveFrontSaveString(_Stream, _TextureSettings.ReflectionType))
		{
			return false;
		}
	}

	if (BFW_STRING_TYPE_A("bump") == _Type)
	{
		_Stream << " -bm " << _TextureSettings.BumpMultiplier;
	}

	if (BFW_STRING_TYPE_A("bump") == _Type || BFW_STRING_TYPE_A("decal") == _Type || BFW_STRING_TYPE_A("map_Ns") == _Type || BFW_STRING_TYPE_A("map_Pr") == _Type || BFW_STRING_TYPE_A("map_Pm") == _Type || BFW_STRING_TYPE_A("map_Pao") == _Type || BFW_STRING_TYPE_A("map_Ps") == _Type || BFW_STRING_TYPE_A("map_Pc") == _Type || BFW_STRING_TYPE_A("map_Pcr") == _Type || BFW_STRING_TYPE_A("map_aniso") == _Type || BFW_STRING_TYPE_A("map_anisor") == _Type || BFW_STRING_TYPE_A("map_d") == _Type || BFW_STRING_TYPE_A("disp") == _Type)
	{
		_Stream << " -imfchan " << _TextureSettings.Channel;
	}

	if (!_TextureSettings.BlendU)
	{
		_Stream << " -blendu " << _TextureSettings.BlendU;
	}

	if (!_TextureSettings.BlendV)
	{
		_Stream << " -blendv " << _TextureSettings.BlendV;
	}

	if (_TextureSettings.Clamp)
	{
		_Stream << " -clamp " << _TextureSettings.Clamp;
	}

	if (_TextureSettings.Boost != 1.0f)
	{
		_Stream << " -boost " << _TextureSettings.Boost;
	}

	if (_TextureSettings.Base != 0.0f || _TextureSettings.Gain != 1.0f)
	{
		_Stream << " -mm " << _TextureSettings.Base << ' ' << _TextureSettings.Gain;
	}

	if (_TextureSettings.Offset != BFW::Math::Vec3(0.0f, 0.0f, 0.0f))
	{
		_Stream << " -o " << _TextureSettings.Offset.x << ' ' << _TextureSettings.Offset.y << ' ' << _TextureSettings.Offset.z;
	}

	if (_TextureSettings.Scale != BFW::Math::Vec3(1.0f, 1.0f, 1.0f))
	{
		_Stream << " -s " << _TextureSettings.Scale.x << ' ' << _TextureSettings.Scale.y << ' ' << _TextureSettings.Scale.z;
	}

	if (_TextureSettings.Turbulence != BFW::Math::Vec3(0.0f, 0.0f, 0.0f))
	{
		_Stream << " -t " << _TextureSettings.Turbulence.x << ' ' << _TextureSettings.Turbulence.y << ' ' << _TextureSettings.Turbulence.z;
	}

	if (_TextureSettings.Resolution)
	{
		_Stream << " -texres " << _TextureSettings.Resolution;
	}

	if (!WaveFrontSaveString(_Stream, _Path))
	{
		return false;
	}

	_Stream BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';

	return true;
}



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
		uint8_t _QuoteCount = 0;

		while (_KeepLine)
		{
			_KeepLine = false;

			size_t _FileLineStart = _FileLine.size();

			while (_FileContent[_FileIndex] != '\n' && _FileContent[_FileIndex] != '\0')
			{
				if (_FileContent[_FileIndex] == '#' && _QuoteCount == 0)
				{
					break;
				}

				if (_FileContent[_FileIndex] == '\"')
				{
					_QuoteCount = (_QuoteCount + 1) % 2;
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

			if (_QuoteCount == 1)
			{
				return false;
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

				if (_Token.size() == 0)
				{
					return false;
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

					if (!(_Stream >> _Values[_Index]) || !_Stream.eof() || !std::isfinite(_Values[_Index]))
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

					if (!(_Stream >> _Values[_Index]) || !_Stream.eof() || !std::isfinite(_Values[_Index]))
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

					if (!(_Stream >> _Values[_Index]) || !_Stream.eof() || !std::isfinite(_Values[_Index]))
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

					if (!(_Stream >> _Values[_Index]) || !_Stream.eof() || !std::isfinite(_Values[_Index]))
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

					if (!(_Stream >> _Values[_Index]) || !_Stream.eof() || !std::isfinite(_Values[_Index]))
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

					if (!(_Stream >> _Values[_Index]) || !_Stream.eof() || !std::isfinite(_Values[_Index]))
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

				if (!(_Stream >> _Values[_Index]) || !_Stream.eof() || !std::isfinite(_Values[_Index]))
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

	_Stream.imbue(std::locale::classic());

	if (_SaveMaterials)
	{
		for (size_t _Index = 0; _Index < MaterialLibs.GetSize(); _Index++)
		{
			_Stream << "mtllib ";

			if (!WaveFrontSaveString(_Stream, MaterialLibs[_Index]))
			{
				return FileContent();
			}

			_Stream BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
		}
	}

	for (size_t _NameIndex = 0; _NameIndex < MeshNames.GetSize(); _NameIndex++)
	{
		const Mesh& _CurrentMesh = *Meshes.GetData(MeshNames[_NameIndex].c_str());

		_Stream << "o ";

		if (!WaveFrontSaveString(_Stream, MeshNames[_NameIndex]))
		{
			return FileContent();
		}

		_Stream BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';

		if (_CurrentMesh.MaterialName.size() && _SaveMaterials)
		{
			_Stream << "usemtl ";

			if (!WaveFrontSaveString(_Stream, _CurrentMesh.MaterialName))
			{
				return FileContent();
			}

			_Stream BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
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

	if (!_Stream)
	{
		return FileContent();
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



BFW::Assets::TextureSettings::TextureSettings() : BlendU(true), BlendV(true), Clamp(false), Channel('l'), Boost(1.0f), Base(0.0f), Gain(1.0f), Offset(Math::Vec3(0.0f, 0.0f, 0.0f)), Scale(Math::Vec3(1.0f, 1.0f, 1.0f)), Turbulence(Math::Vec3(0.0f, 0.0f, 0.0f)), Resolution(0), BumpMultiplier(1.0f), ReflectionType(BFW_STRING_PREFIX("sphere"))
{

}

BFW::Assets::TextureSettings::TextureSettings(const TextureSettings& _Other) : BlendU(_Other.BlendU), BlendV(_Other.BlendV), Clamp(_Other.Clamp), Channel(_Other.Channel), Boost(_Other.Boost), Base(_Other.Base), Gain(_Other.Gain), Offset(_Other.Offset), Scale(_Other.Scale), Turbulence(_Other.Turbulence), Resolution(_Other.Resolution), BumpMultiplier(_Other.BumpMultiplier), ReflectionType(_Other.ReflectionType)
{

}

BFW::Assets::TextureSettings::TextureSettings(TextureSettings&& _Other) noexcept : BlendU(_Other.BlendU), BlendV(_Other.BlendV), Clamp(_Other.Clamp), Channel(_Other.Channel), Boost(_Other.Boost), Base(_Other.Base), Gain(_Other.Gain), Offset(_Other.Offset), Scale(_Other.Scale), Turbulence(_Other.Turbulence), Resolution(_Other.Resolution), BumpMultiplier(_Other.BumpMultiplier), ReflectionType(_Other.ReflectionType)
{
	_Other.BlendU = true;
	_Other.BlendV = true;
	_Other.Clamp = false;
	_Other.Channel = 'l';
	_Other.Boost = 1.0f;
	_Other.Base = 0.0f;
	_Other.Gain = 1.0f;
	_Other.Offset = Math::Vec3(0.0f, 0.0f, 0.0f);
	_Other.Scale = Math::Vec3(1.0f, 1.0f, 1.0f);
	_Other.Turbulence = Math::Vec3(0.0f, 0.0f, 0.0f);
	_Other.Resolution = 0;
	_Other.BumpMultiplier = 1.0f;
	_Other.ReflectionType = BFW_STRING_PREFIX("sphere");
}

BFW::Assets::TextureSettings::~TextureSettings()
{

}

const bool BFW::Assets::TextureSettings::IsValid() const
{
	if (BFW_STRING_TYPE_A("rgbmlz").find(Channel) == BFW_STRING_TYPE_A::npos || Channel == '\0')
	{
		return false;
	}

	if (Boost < 0.0f)
	{
		return false;
	}

	if (ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("")) &&
		ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("sphere")) &&
		ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("cube_top")) &&
		ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("cube_bottom")) &&
		ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("cube_front")) &&
		ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("cube_back")) &&
		ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("cube_left")) &&
		ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("cube_right")))
	{
		return false;
	}

	return true;
}

BFW::Assets::TextureSettings& BFW::Assets::TextureSettings::operator= (const TextureSettings& _Other)
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
	Base = _Other.Base;
	Gain = _Other.Gain;
	Offset = _Other.Offset;
	Scale = _Other.Scale;
	Turbulence = _Other.Turbulence;
	Resolution = _Other.Resolution;
	BumpMultiplier = _Other.BumpMultiplier;
	ReflectionType = _Other.ReflectionType;

	return *this;
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
	Base = _Other.Base;
	Gain = _Other.Gain;
	Offset = _Other.Offset;
	Scale = _Other.Scale;
	Turbulence = _Other.Turbulence;
	Resolution = _Other.Resolution;
	BumpMultiplier = _Other.BumpMultiplier;
	ReflectionType = _Other.ReflectionType;

	_Other.BlendU = true;
	_Other.BlendV = true;
	_Other.Clamp = false;
	_Other.Channel = 'l';
	_Other.Boost = 1.0f;
	_Other.Base = 0.0f;
	_Other.Gain = 1.0f;
	_Other.Offset = Math::Vec3(0.0f, 0.0f, 0.0f);
	_Other.Scale = Math::Vec3(1.0f, 1.0f, 1.0f);
	_Other.Turbulence = Math::Vec3(0.0f, 0.0f, 0.0f);
	_Other.Resolution = 0;
	_Other.BumpMultiplier = 1.0f;
	_Other.ReflectionType = BFW_STRING_PREFIX("sphere");

	return *this;
}



BFW::Assets::Material::Material() :
	Albedo(Math::Vec3(1.0f, 1.0f, 1.0f)),
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

	AlbedoTexture(BFW_STRING_PREFIX("")),
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

	AlbedoTextureSettings(),
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
	ReflectionTexturesSettings(1)
{
	DecalTextureSettings.Channel = 'm';
}

BFW::Assets::Material::Material(const Material& _Other) :
	Albedo(_Other.Albedo),
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

	AlbedoTexture(_Other.AlbedoTexture),
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

	AlbedoTextureSettings(_Other.AlbedoTextureSettings),
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
	ReflectionTexturesSettings(_Other.ReflectionTexturesSettings)
{

}

BFW::Assets::Material::Material(Material&& _Other) noexcept :
	Albedo(_Other.Albedo),
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

	AlbedoTexture(_Other.AlbedoTexture),
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

	AlbedoTextureSettings(_Other.AlbedoTextureSettings),
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
	ReflectionTexturesSettings(_Other.ReflectionTexturesSettings)
{
	_Other = (const Material&)(Material());
}

BFW::Assets::Material::~Material()
{

}

const bool BFW::Assets::Material::IsValid() const
{
	if (Albedo.x < 0.0f || Albedo.x > 1.0f || Albedo.y < 0.0f || Albedo.y > 1.0f || Albedo.z < 0.0f || Albedo.z > 1.0f)
	{
		return false;
	}

	if (SpecularColor.x < 0.0f || SpecularColor.x > 1.0f || SpecularColor.y < 0.0f || SpecularColor.y > 1.0f || SpecularColor.z < 0.0f || SpecularColor.z > 1.0f)
	{
		return false;
	}

	if (SpecularExponent < 0.0f || SpecularExponent > 1000.0f)
	{
		return false;
	}

	if (EmissionColor.x < 0.0f || EmissionColor.y < 0.0f || EmissionColor.z < 0.0f)
	{
		return false;
	}

	if (Roughness < 0.0f || Roughness > 1.0f)
	{
		return false;
	}

	if (Metalness < 0.0f || Metalness > 1.0f)
	{
		return false;
	}

	if (AmbientOcclusion < 0.0f || AmbientOcclusion > 1.0f)
	{
		return false;
	}

	if (AmbientColor.x < 0.0f || AmbientColor.x > 1.0f || AmbientColor.y < 0.0f || AmbientColor.y > 1.0f || AmbientColor.z < 0.0f || AmbientColor.z > 1.0f)
	{
		return false;
	}

	if (Sheen < 0.0f || Sheen > 1.0f)
	{
		return false;
	}

	if (SheenColor.x < 0.0f || SheenColor.x > 1.0f || SheenColor.y < 0.0f || SheenColor.y > 1.0f || SheenColor.z < 0.0f || SheenColor.z > 1.0f)
	{
		return false;
	}

	if (ClearCoat < 0.0f || ClearCoat > 1.0f)
	{
		return false;
	}

	if (ClearCoatColor.x < 0.0f || ClearCoatColor.x > 1.0f || ClearCoatColor.y < 0.0f || ClearCoatColor.y > 1.0f || ClearCoatColor.z < 0.0f || ClearCoatColor.z > 1.0f)
	{
		return false;
	}

	if (ClearCoatRoughness < 0.0f || ClearCoatRoughness > 1.0f)
	{
		return false;
	}

	if (Anisotropy < 0.0f || Anisotropy > 1.0f)
	{
		return false;
	}

	if (AnisotropyRotation < 0.0f || AnisotropyRotation > 1.0f)
	{
		return false;
	}

	if (Alpha < 0.0f || Alpha > 1.0f)
	{
		return false;
	}

	if (TransmissionFilter.x < 0.0f || TransmissionFilter.y < 0.0f || TransmissionFilter.z < 0.0f)
	{
		return false;
	}

	if (IndexOfRefraction < 0.001f || IndexOfRefraction > 10.0f)
	{
		return false;
	}

	if (Displacement < 0.0f)
	{
		return false;
	}

	if (IlluminationModel > 10)
	{
		return false;
	}

	if (Normal.x < 0.0f || Normal.x > 1.0f || Normal.y < 0.0f || Normal.y > 1.0f || Normal.z < 0.0f || Normal.z > 1.0f)
	{
		return false;
	}

	if (Tangent.x < 0.0f || Tangent.x > 1.0f || Tangent.y < 0.0f || Tangent.y > 1.0f || Tangent.z < 0.0f || Tangent.z > 1.0f)
	{
		return false;
	}

	if (ClearCoatNormal.x < 0.0f || ClearCoatNormal.x > 1.0f || ClearCoatNormal.y < 0.0f || ClearCoatNormal.y > 1.0f || ClearCoatNormal.z < 0.0f || ClearCoatNormal.z > 1.0f)
	{
		return false;
	}

	if (!AlbedoTextureSettings.IsValid() || AlbedoTextureSettings.BumpMultiplier != 1.0f || AlbedoTextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("")))
	{
		return false;
	}

	if (!SpecularColorTextureSettings.IsValid() || SpecularColorTextureSettings.BumpMultiplier != 1.0f || SpecularColorTextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("")))
	{
		return false;
	}

	if (!SpecularExponentTextureSettings.IsValid() || SpecularExponentTextureSettings.BumpMultiplier != 1.0f || SpecularExponentTextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("")))
	{
		return false;
	}

	if (!EmissionColorTextureSettings.IsValid() || EmissionColorTextureSettings.BumpMultiplier != 1.0f || EmissionColorTextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("")))
	{
		return false;
	}

	if (!RoughnessTextureSettings.IsValid() || RoughnessTextureSettings.BumpMultiplier != 1.0f || RoughnessTextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("")))
	{
		return false;
	}

	if (!MetalnessTextureSettings.IsValid() || MetalnessTextureSettings.BumpMultiplier != 1.0f || MetalnessTextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("")))
	{
		return false;
	}

	if (!AmbientOcclusionTextureSettings.IsValid() || AmbientOcclusionTextureSettings.BumpMultiplier != 1.0f || AmbientOcclusionTextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("")))
	{
		return false;
	}

	if (!AmbientColorTextureSettings.IsValid() || AmbientColorTextureSettings.BumpMultiplier != 1.0f || AmbientColorTextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("")))
	{
		return false;
	}

	if (!SheenTextureSettings.IsValid() || SheenTextureSettings.BumpMultiplier != 1.0f || SheenTextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("")))
	{
		return false;
	}

	if (!SheenColorTextureSettings.IsValid() || SheenColorTextureSettings.BumpMultiplier != 1.0f || SheenColorTextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("")))
	{
		return false;
	}

	if (!ClearCoatTextureSettings.IsValid() || ClearCoatTextureSettings.BumpMultiplier != 1.0f || ClearCoatTextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("")))
	{
		return false;
	}

	if (!ClearCoatColorTextureSettings.IsValid() || ClearCoatColorTextureSettings.BumpMultiplier != 1.0f || ClearCoatColorTextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("")))
	{
		return false;
	}

	if (!ClearCoatRoughnessTextureSettings.IsValid() || ClearCoatRoughnessTextureSettings.BumpMultiplier != 1.0f || ClearCoatRoughnessTextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("")))
	{
		return false;
	}

	if (!AnisotropyTextureSettings.IsValid() || AnisotropyTextureSettings.BumpMultiplier != 1.0f || AnisotropyTextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("")))
	{
		return false;
	}

	if (!AnisotropyRotationTextureSettings.IsValid() || AnisotropyRotationTextureSettings.BumpMultiplier != 1.0f || AnisotropyRotationTextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("")))
	{
		return false;
	}

	if (!AlphaTextureSettings.IsValid() || AlphaTextureSettings.BumpMultiplier != 1.0f || AlphaTextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("")))
	{
		return false;
	}

	if (!TransmissionFilterTextureSettings.IsValid() || TransmissionFilterTextureSettings.BumpMultiplier != 1.0f || TransmissionFilterTextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("")))
	{
		return false;
	}

	if (!DisplacementTextureSettings.IsValid() || DisplacementTextureSettings.BumpMultiplier != 1.0f || DisplacementTextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("")))
	{
		return false;
	}

	if (!NormalTextureSettings.IsValid() || NormalTextureSettings.BumpMultiplier != 1.0f || NormalTextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("")))
	{
		return false;
	}

	if (!TangentTextureSettings.IsValid() || TangentTextureSettings.BumpMultiplier != 1.0f || TangentTextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("")))
	{
		return false;
	}

	if (!ClearCoatNormalTextureSettings.IsValid() || ClearCoatNormalTextureSettings.BumpMultiplier != 1.0f || ClearCoatNormalTextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("")))
	{
		return false;
	}

	if (!DecalTextureSettings.IsValid() || DecalTextureSettings.BumpMultiplier != 1.0f || DecalTextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("")))
	{
		return false;
	}

	if (!BumpTextureSettings.IsValid() || BumpTextureSettings.ReflectionType != BFW_STRING_TYPE(BFW_STRING_PREFIX("")))
	{
		return false;
	}

	if (ReflectionTextures.GetSize() != ReflectionTexturesSettings.GetSize())
	{
		return false;
	}

	if (ReflectionTexturesSettings.GetSize() != 0)
	{
		if (ReflectionTexturesSettings.GetSize() == 1)
		{
			if (!ReflectionTexturesSettings[0].IsValid() || ReflectionTexturesSettings[0].BumpMultiplier != 1.0f || ReflectionTexturesSettings[0].ReflectionType != BFW_STRING_PREFIX("sphere"))
			{
				return false;
			}
		}
		else if (ReflectionTexturesSettings.GetSize() == 6)
		{
			Vector<BFW_STRING_TYPE> _Types =
			{
				BFW_STRING_PREFIX("cube_top"),
				BFW_STRING_PREFIX("cube_bottom"),
				BFW_STRING_PREFIX("cube_front"),
				BFW_STRING_PREFIX("cube_back"),
				BFW_STRING_PREFIX("cube_left"),
				BFW_STRING_PREFIX("cube_right")
			};

			for (size_t _SettingIndex = 0; _SettingIndex < ReflectionTexturesSettings.GetSize(); _SettingIndex++)
			{
				if (!ReflectionTexturesSettings[_SettingIndex].IsValid() || ReflectionTexturesSettings[_SettingIndex].BumpMultiplier != 1.0f)
				{
					return false;
				}

				for (size_t _TypeIndex = 0; _TypeIndex < _Types.GetSize(); _TypeIndex++)
				{
					if (_Types[_TypeIndex] == ReflectionTexturesSettings[_SettingIndex].ReflectionType)
					{
						_Types.Erase(_TypeIndex);
						break;
					}
				}
			}

			if (_Types.GetSize() != 0)
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	return true;
}

BFW::Assets::Material& BFW::Assets::Material::operator= (const Material& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Albedo = _Other.Albedo;
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

	AlbedoTexture = _Other.AlbedoTexture;
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

	AlbedoTextureSettings = _Other.AlbedoTextureSettings;
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
	ReflectionTexturesSettings = _Other.ReflectionTexturesSettings;

	return *this;
}

BFW::Assets::Material& BFW::Assets::Material::operator= (Material&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Albedo = _Other.Albedo;
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

	AlbedoTexture = _Other.AlbedoTexture;
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

	AlbedoTextureSettings = _Other.AlbedoTextureSettings;
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
	ReflectionTexturesSettings = _Other.ReflectionTexturesSettings;

	_Other = (const Material&)(Material());

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

	bool _Found_Kd = false;
	bool _Found_Ks = false;
	bool _Found_Ns = false;
	bool _Found_Ke = false;
	bool _Found_Pr = false;
	bool _Found_Pm = false;
	bool _Found_Pao = false;
	bool _Found_Ka = false;
	bool _Found_Ps = false;
	bool _Found_Psc = false;
	bool _Found_Pc = false;
	bool _Found_Pcc = false;
	bool _Found_Pcr = false;
	bool _Found_aniso = false;
	bool _Found_anisor = false;
	bool _Found_d_Tr = false;
	bool _Found_Tf = false;
	bool _Found_Ni = false;
	bool _Found_Kdisp = false;
	bool _Found_illum = false;
	bool _Found_Kn = false;
	bool _Found_Kt = false;
	bool _Found_Pcn = false;
	bool _Found_map_Kd = false;
	bool _Found_map_Ks = false;
	bool _Found_map_Ns = false;
	bool _Found_map_Ke = false;
	bool _Found_map_Pr = false;
	bool _Found_map_Pm = false;
	bool _Found_map_Pao = false;
	bool _Found_map_Ka = false;
	bool _Found_map_Ps = false;
	bool _Found_map_Psc = false;
	bool _Found_map_Pc = false;
	bool _Found_map_Pcc = false;
	bool _Found_map_Pcr = false;
	bool _Found_map_aniso = false;
	bool _Found_map_anisor = false;
	bool _Found_map_d = false;
	bool _Found_map_Tf = false;
	bool _Found_disp = false;
	bool _Found_norm = false;
	bool _Found_tang = false;
	bool _Found_map_Pcn = false;
	bool _Found_decal = false;
	bool _Found_bump_map_Bump = false;

	size_t _FileIndex = 0;

	while (_FileContent[_FileIndex] != '\0')
	{
		BFW_STRING_TYPE_A _FileLine;

		BFW_WINDOWS_PLATFORM_CALL(_FileLine.reserve(512));
		BFW_LINUX_PLATFORM_CALL(_FileLine.reserve(512));

		bool _KeepLine = true;
		uint8_t _QuoteCount = 0;

		while (_KeepLine)
		{
			_KeepLine = false;

			size_t _FileLineStart = _FileLine.size();

			while (_FileContent[_FileIndex] != '\n' && _FileContent[_FileIndex] != '\0')
			{
				if (_FileContent[_FileIndex] == '#' && _QuoteCount == 0)
				{
					break;
				}

				if (_FileContent[_FileIndex] == '\"')
				{
					_QuoteCount = (_QuoteCount + 1) % 2;
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

			if (_QuoteCount == 1)
			{
				return false;
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

				if (_Token.size() == 0)
				{
					return false;
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

			_Found_Kd = false;
			_Found_Ks = false;
			_Found_Ns = false;
			_Found_Ke = false;
			_Found_Pr = false;
			_Found_Pm = false;
			_Found_Pao = false;
			_Found_Ka = false;
			_Found_Ps = false;
			_Found_Psc = false;
			_Found_Pc = false;
			_Found_Pcc = false;
			_Found_Pcr = false;
			_Found_aniso = false;
			_Found_anisor = false;
			_Found_d_Tr = false;
			_Found_Tf = false;
			_Found_Ni = false;
			_Found_Kdisp = false;
			_Found_illum = false;
			_Found_Kn = false;
			_Found_Kt = false;
			_Found_Pcn = false;
			_Found_map_Kd = false;
			_Found_map_Ks = false;
			_Found_map_Ns = false;
			_Found_map_Ke = false;
			_Found_map_Pr = false;
			_Found_map_Pm = false;
			_Found_map_Pao = false;
			_Found_map_Ka = false;
			_Found_map_Ps = false;
			_Found_map_Psc = false;
			_Found_map_Pc = false;
			_Found_map_Pcc = false;
			_Found_map_Pcr = false;
			_Found_map_aniso = false;
			_Found_map_anisor = false;
			_Found_map_d = false;
			_Found_map_Tf = false;
			_Found_disp = false;
			_Found_norm = false;
			_Found_tang = false;
			_Found_map_Pcn = false;
			_Found_decal = false;
			_Found_bump_map_Bump = false;

			continue;
		}

		if (_LineTokens[0] == "Kd")
		{
			if (_LineTokens.GetSize() != 4 || _Names.GetSize() == 0 || _Found_Kd)
			{
				return false;
			}

			_Found_Kd = true;

			for (size_t _ChannelIndex = 0; _ChannelIndex < 3; _ChannelIndex++)
			{
				BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[_ChannelIndex + 1]);

				if (!(_Stream >> _Materials[_Materials.GetSize() - 1].Albedo[_ChannelIndex]) || !_Stream.eof() || !std::isfinite(_Materials[_Materials.GetSize() - 1].Albedo[_CharIndex]))
				{
					return false;
				}

				if (_Materials[_Materials.GetSize() - 1].Albedo[_ChannelIndex] < 0.0f || _Materials[_Materials.GetSize() - 1].Albedo[_ChannelIndex] > 1.0f)
				{
					return false;
				}
			}

			continue;
		}

		if (_LineTokens[0] == "Ks")
		{
			if (_LineTokens.GetSize() != 4 || _Names.GetSize() == 0 || _Found_Ks)
			{
				return false;
			}

			_Found_Ks = true;

			for (size_t _ChannelIndex = 0; _ChannelIndex < 3; _ChannelIndex++)
			{
				BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[_ChannelIndex + 1]);

				if (!(_Stream >> _Materials[_Materials.GetSize() - 1].SpecularColor[_ChannelIndex]) || !_Stream.eof() || !std::isfinite(_Materials[_Materials.GetSize() - 1].SpecularColor[_CharIndex]))
				{
					return false;
				}

				if (_Materials[_Materials.GetSize() - 1].SpecularColor[_ChannelIndex] < 0.0f || _Materials[_Materials.GetSize() - 1].SpecularColor[_ChannelIndex] > 1.0f)
				{
					return false;
				}
			}

			continue;
		}

		if (_LineTokens[0] == "Ns")
		{
			if (_LineTokens.GetSize() != 2 || _Names.GetSize() == 0 || _Found_Ns)
			{
				return false;
			}

			_Found_Ns = true;

			BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[1]);

			if (!(_Stream >> _Materials[_Materials.GetSize() - 1].SpecularExponent) || !_Stream.eof() || !std::isfinite(_Materials[_Materials.GetSize() - 1].SpecularExponent))
			{
				return false;
			}

			if (_Materials[_Materials.GetSize() - 1].SpecularExponent < 0.0f || _Materials[_Materials.GetSize() - 1].SpecularExponent > 1000.0f)
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "Ke")
		{
			if (_LineTokens.GetSize() != 4 || _Names.GetSize() == 0 || _Found_Ke)
			{
				return false;
			}

			_Found_Ke = true;

			for (size_t _ChannelIndex = 0; _ChannelIndex < 3; _ChannelIndex++)
			{
				BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[_ChannelIndex + 1]);

				if (!(_Stream >> _Materials[_Materials.GetSize() - 1].EmissionColor[_ChannelIndex]) || !_Stream.eof() || !std::isfinite(_Materials[_Materials.GetSize() - 1].EmissionColor[_CharIndex]))
				{
					return false;
				}

				if (_Materials[_Materials.GetSize() - 1].EmissionColor[_ChannelIndex] < 0.0f)
				{
					return false;
				}
			}

			continue;
		}

		if (_LineTokens[0] == "Pr")
		{
			if (_LineTokens.GetSize() != 2 || _Names.GetSize() == 0 || _Found_Pr)
			{
				return false;
			}

			_Found_Pr = true;

			BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[1]);

			if (!(_Stream >> _Materials[_Materials.GetSize() - 1].Roughness) || !_Stream.eof() || !std::isfinite(_Materials[_Materials.GetSize() - 1].Roughness))
			{
				return false;
			}

			if (_Materials[_Materials.GetSize() - 1].Roughness < 0.0f || _Materials[_Materials.GetSize() - 1].Roughness > 1.0f)
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "Pm")
		{
			if (_LineTokens.GetSize() != 2 || _Names.GetSize() == 0 || _Found_Pm)
			{
				return false;
			}

			_Found_Pm = true;

			BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[1]);

			if (!(_Stream >> _Materials[_Materials.GetSize() - 1].Metalness) || !_Stream.eof() || !std::isfinite(_Materials[_Materials.GetSize() - 1].Metalness))
			{
				return false;
			}

			if (_Materials[_Materials.GetSize() - 1].Metalness < 0.0f || _Materials[_Materials.GetSize() - 1].Metalness > 1.0f)
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "Pao")
		{
			if (_LineTokens.GetSize() != 2 || _Names.GetSize() == 0 || _Found_Pao)
			{
				return false;
			}

			_Found_Pao = true;

			BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[1]);

			if (!(_Stream >> _Materials[_Materials.GetSize() - 1].AmbientOcclusion) || !_Stream.eof() || !std::isfinite(_Materials[_Materials.GetSize() - 1].AmbientOcclusion))
			{
				return false;
			}

			if (_Materials[_Materials.GetSize() - 1].AmbientOcclusion < 0.0f || _Materials[_Materials.GetSize() - 1].AmbientOcclusion > 1.0f)
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "Ka")
		{
			if (_LineTokens.GetSize() != 4 || _Names.GetSize() == 0 || _Found_Ka)
			{
				return false;
			}

			_Found_Ka = true;

			for (size_t _ChannelIndex = 0; _ChannelIndex < 3; _ChannelIndex++)
			{
				BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[_ChannelIndex + 1]);

				if (!(_Stream >> _Materials[_Materials.GetSize() - 1].AmbientColor[_ChannelIndex]) || !_Stream.eof() || !std::isfinite(_Materials[_Materials.GetSize() - 1].AmbientColor[_CharIndex]))
				{
					return false;
				}

				if (_Materials[_Materials.GetSize() - 1].AmbientColor[_ChannelIndex] < 0.0f || _Materials[_Materials.GetSize() - 1].AmbientColor[_ChannelIndex] > 1.0f)
				{
					return false;
				}
			}

			continue;
		}

		if (_LineTokens[0] == "Ps")
		{
			if (_LineTokens.GetSize() != 2 || _Names.GetSize() == 0 || _Found_Ps)
			{
				return false;
			}

			_Found_Ps = true;

			BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[1]);

			if (!(_Stream >> _Materials[_Materials.GetSize() - 1].Sheen) || !_Stream.eof() || !std::isfinite(_Materials[_Materials.GetSize() - 1].Sheen))
			{
				return false;
			}

			if (_Materials[_Materials.GetSize() - 1].Sheen < 0.0f || _Materials[_Materials.GetSize() - 1].Sheen > 1.0f)
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "Psc")
		{
			if (_LineTokens.GetSize() != 4 || _Names.GetSize() == 0 || _Found_Psc)
			{
				return false;
			}

			_Found_Psc = true;

			for (size_t _ChannelIndex = 0; _ChannelIndex < 3; _ChannelIndex++)
			{
				BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[_ChannelIndex + 1]);

				if (!(_Stream >> _Materials[_Materials.GetSize() - 1].SheenColor[_ChannelIndex]) || !_Stream.eof() || !std::isfinite(_Materials[_Materials.GetSize() - 1].SheenColor[_CharIndex]))
				{
					return false;
				}

				if (_Materials[_Materials.GetSize() - 1].SheenColor[_ChannelIndex] < 0.0f || _Materials[_Materials.GetSize() - 1].SheenColor[_ChannelIndex] > 1.0f)
				{
					return false;
				}
			}

			continue;
		}

		if (_LineTokens[0] == "Pc")
		{
			if (_LineTokens.GetSize() != 2 || _Names.GetSize() == 0 || _Found_Pc)
			{
				return false;
			}

			_Found_Pc = true;

			BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[1]);

			if (!(_Stream >> _Materials[_Materials.GetSize() - 1].ClearCoat) || !_Stream.eof() || !std::isfinite(_Materials[_Materials.GetSize() - 1].ClearCoat))
			{
				return false;
			}

			if (_Materials[_Materials.GetSize() - 1].ClearCoat < 0.0f || _Materials[_Materials.GetSize() - 1].ClearCoat > 1.0f)
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "Pcc")
		{
			if (_LineTokens.GetSize() != 4 || _Names.GetSize() == 0 || _Found_Pcc)
			{
				return false;
			}

			_Found_Pcc = true;

			for (size_t _ChannelIndex = 0; _ChannelIndex < 3; _ChannelIndex++)
			{
				BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[_ChannelIndex + 1]);

				if (!(_Stream >> _Materials[_Materials.GetSize() - 1].ClearCoatColor[_ChannelIndex]) || !_Stream.eof() || !std::isfinite(_Materials[_Materials.GetSize() - 1].ClearCoatColor[_CharIndex]))
				{
					return false;
				}

				if (_Materials[_Materials.GetSize() - 1].ClearCoatColor[_ChannelIndex] < 0.0f || _Materials[_Materials.GetSize() - 1].ClearCoatColor[_ChannelIndex] > 1.0f)
				{
					return false;
				}
			}

			continue;
		}

		if (_LineTokens[0] == "Pcr")
		{
			if (_LineTokens.GetSize() != 2 || _Names.GetSize() == 0 || _Found_Pcr)
			{
				return false;
			}

			_Found_Pcr = true;

			BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[1]);

			if (!(_Stream >> _Materials[_Materials.GetSize() - 1].ClearCoatRoughness) || !_Stream.eof() || !std::isfinite(_Materials[_Materials.GetSize() - 1].ClearCoatRoughness))
			{
				return false;
			}

			if (_Materials[_Materials.GetSize() - 1].ClearCoatRoughness < 0.0f || _Materials[_Materials.GetSize() - 1].ClearCoatRoughness > 1.0f)
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "aniso")
		{
			if (_LineTokens.GetSize() != 2 || _Names.GetSize() == 0 || _Found_aniso)
			{
				return false;
			}

			_Found_aniso = true;

			BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[1]);

			if (!(_Stream >> _Materials[_Materials.GetSize() - 1].Anisotropy) || !_Stream.eof() || !std::isfinite(_Materials[_Materials.GetSize() - 1].Anisotropy))
			{
				return false;
			}

			if (_Materials[_Materials.GetSize() - 1].Anisotropy < 0.0f || _Materials[_Materials.GetSize() - 1].Anisotropy > 1.0f)
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "anisor")
		{
			if (_LineTokens.GetSize() != 2 || _Names.GetSize() == 0 || _Found_anisor)
			{
				return false;
			}

			_Found_anisor = true;

			BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[1]);

			if (!(_Stream >> _Materials[_Materials.GetSize() - 1].AnisotropyRotation) || !_Stream.eof() || !std::isfinite(_Materials[_Materials.GetSize() - 1].AnisotropyRotation))
			{
				return false;
			}

			if (_Materials[_Materials.GetSize() - 1].AnisotropyRotation < 0.0f || _Materials[_Materials.GetSize() - 1].AnisotropyRotation > 1.0f)
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "d")
		{
			if (_LineTokens.GetSize() != 2 || _Names.GetSize() == 0 || _Found_d_Tr)
			{
				return false;
			}

			_Found_d_Tr = true;

			BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[1]);

			if (!(_Stream >> _Materials[_Materials.GetSize() - 1].Alpha) || !_Stream.eof() || !std::isfinite(_Materials[_Materials.GetSize() - 1].Alpha))
			{
				return false;
			}

			if (_Materials[_Materials.GetSize() - 1].Alpha < 0.0f || _Materials[_Materials.GetSize() - 1].Alpha > 1.0f)
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "Tr")
		{
			if (_LineTokens.GetSize() != 2 || _Names.GetSize() == 0 || _Found_d_Tr)
			{
				return false;
			}

			_Found_d_Tr = true;

			BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[1]);

			if (!(_Stream >> _Materials[_Materials.GetSize() - 1].Alpha) || !_Stream.eof() || !std::isfinite(_Materials[_Materials.GetSize() - 1].Alpha))
			{
				return false;
			}

			if (_Materials[_Materials.GetSize() - 1].Alpha < 0.0f || _Materials[_Materials.GetSize() - 1].Alpha > 1.0f)
			{
				return false;
			}

			_Materials[_Materials.GetSize() - 1].Alpha = 1.0f - _Materials[_Materials.GetSize() - 1].Alpha;

			continue;
		}

		if (_LineTokens[0] == "Tf")
		{
			if (_LineTokens.GetSize() != 4 || _Names.GetSize() == 0 || _Found_Tf)
			{
				return false;
			}

			_Found_Tf = true;

			for (size_t _ChannelIndex = 0; _ChannelIndex < 3; _ChannelIndex++)
			{
				BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[_ChannelIndex + 1]);

				if (!(_Stream >> _Materials[_Materials.GetSize() - 1].TransmissionFilter[_ChannelIndex]) || !_Stream.eof() || !std::isfinite(_Materials[_Materials.GetSize() - 1].TransmissionFilter[_CharIndex]))
				{
					return false;
				}

				if (_Materials[_Materials.GetSize() - 1].TransmissionFilter[_ChannelIndex] < 0.0f)
				{
					return false;
				}
			}

			continue;
		}

		if (_LineTokens[0] == "Ni")
		{
			if (_LineTokens.GetSize() != 2 || _Names.GetSize() == 0 || _Found_Ni)
			{
				return false;
			}

			_Found_Ni = true;

			BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[1]);

			if (!(_Stream >> _Materials[_Materials.GetSize() - 1].IndexOfRefraction) || !_Stream.eof() || !std::isfinite(_Materials[_Materials.GetSize() - 1].IndexOfRefraction))
			{
				return false;
			}

			if (_Materials[_Materials.GetSize() - 1].IndexOfRefraction < 0.001f || _Materials[_Materials.GetSize() - 1].IndexOfRefraction > 10.0f)
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "Kdisp")
		{
			if (_LineTokens.GetSize() != 2 || _Names.GetSize() == 0 || _Found_Kdisp)
			{
				return false;
			}

			_Found_Kdisp = true;

			BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[1]);

			if (!(_Stream >> _Materials[_Materials.GetSize() - 1].Displacement) || !_Stream.eof() || !std::isfinite(_Materials[_Materials.GetSize() - 1].Displacement))
			{
				return false;
			}

			if (_Materials[_Materials.GetSize() - 1].Displacement < 0.0f)
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "illum")
		{
			if (_LineTokens.GetSize() != 2 || _Names.GetSize() == 0 || _Found_illum)
			{
				return false;
			}

			_Found_illum = true;

			BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[1]);

			if (!(_Stream >> _Materials[_Materials.GetSize() - 1].IlluminationModel) || !_Stream.eof())
			{
				return false;
			}

			if (_Materials[_Materials.GetSize() - 1].IlluminationModel > 10)
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "Kn")
		{
			if (_LineTokens.GetSize() != 4 || _Names.GetSize() == 0 || _Found_Kn)
			{
				return false;
			}

			_Found_Kn = true;

			for (size_t _ChannelIndex = 0; _ChannelIndex < 3; _ChannelIndex++)
			{
				BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[_ChannelIndex + 1]);

				if (!(_Stream >> _Materials[_Materials.GetSize() - 1].Normal[_ChannelIndex]) || !_Stream.eof() || !std::isfinite(_Materials[_Materials.GetSize() - 1].Normal[_CharIndex]))
				{
					return false;
				}

				if (_Materials[_Materials.GetSize() - 1].Normal[_ChannelIndex] < 0.0f || _Materials[_Materials.GetSize() - 1].Normal[_ChannelIndex] > 1.0f)
				{
					return false;
				}
			}

			continue;
		}

		if (_LineTokens[0] == "Kt")
		{
			if (_LineTokens.GetSize() != 4 || _Names.GetSize() == 0 || _Found_Kt)
			{
				return false;
			}

			_Found_Kt = true;

			for (size_t _ChannelIndex = 0; _ChannelIndex < 3; _ChannelIndex++)
			{
				BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[_ChannelIndex + 1]);

				if (!(_Stream >> _Materials[_Materials.GetSize() - 1].Tangent[_ChannelIndex]) || !_Stream.eof() || !std::isfinite(_Materials[_Materials.GetSize() - 1].Tangent[_CharIndex]))
				{
					return false;
				}

				if (_Materials[_Materials.GetSize() - 1].Tangent[_ChannelIndex] < 0.0f || _Materials[_Materials.GetSize() - 1].Tangent[_ChannelIndex] > 1.0f)
				{
					return false;
				}
			}

			continue;
		}

		if (_LineTokens[0] == "Pcn")
		{
			if (_LineTokens.GetSize() != 4 || _Names.GetSize() == 0 || _Found_Pcn)
			{
				return false;
			}

			_Found_Pcn = true;

			for (size_t _ChannelIndex = 0; _ChannelIndex < 3; _ChannelIndex++)
			{
				BFW_STRING_STREAM_TYPE_A _Stream(_LineTokens[_ChannelIndex + 1]);

				if (!(_Stream >> _Materials[_Materials.GetSize() - 1].ClearCoatNormal[_ChannelIndex]) || !_Stream.eof() || !std::isfinite(_Materials[_Materials.GetSize() - 1].ClearCoatNormal[_CharIndex]))
				{
					return false;
				}

				if (_Materials[_Materials.GetSize() - 1].ClearCoatNormal[_ChannelIndex] < 0.0f || _Materials[_Materials.GetSize() - 1].ClearCoatNormal[_ChannelIndex] > 1.0f)
				{
					return false;
				}
			}

			continue;
		}

		if (_LineTokens[0] == "map_Kd")
		{
			if (_LineTokens.GetSize() < 2 || _Names.GetSize() == 0 || _Found_map_Kd || !_Found_illum)
			{
				return false;
			}

			_Found_map_Kd = true;

			if (!MaterialLibLoadMap(_LineTokens, "map_Kd", _Materials[_Materials.GetSize() - 1].AlbedoTexture, _Materials[_Materials.GetSize() - 1].AlbedoTextureSettings))
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "map_Ks")
		{
			if (_LineTokens.GetSize() < 2 || _Names.GetSize() == 0 || _Found_map_Ks || !_Found_illum)
			{
				return false;
			}

			_Found_map_Ks = true;

			if (!MaterialLibLoadMap(_LineTokens, "map_Ks", _Materials[_Materials.GetSize() - 1].SpecularColorTexture, _Materials[_Materials.GetSize() - 1].SpecularColorTextureSettings))
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "map_Ns")
		{
			if (_LineTokens.GetSize() < 2 || _Names.GetSize() == 0 || _Found_map_Ns || !_Found_illum)
			{
				return false;
			}

			_Found_map_Ns = true;

			if (!MaterialLibLoadMap(_LineTokens, "map_Ns", _Materials[_Materials.GetSize() - 1].SpecularExponentTexture, _Materials[_Materials.GetSize() - 1].SpecularExponentTextureSettings))
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "map_Ke")
		{
			if (_LineTokens.GetSize() < 2 || _Names.GetSize() == 0 || _Found_map_Ke || !_Found_illum)
			{
				return false;
			}

			_Found_map_Ke = true;

			if (!MaterialLibLoadMap(_LineTokens, "map_Ke", _Materials[_Materials.GetSize() - 1].EmissionColorTexture, _Materials[_Materials.GetSize() - 1].EmissionColorTextureSettings))
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "map_Pr")
		{
			if (_LineTokens.GetSize() < 2 || _Names.GetSize() == 0 || _Found_map_Pr || !_Found_illum)
			{
				return false;
			}

			_Found_map_Pr = true;

			if (!MaterialLibLoadMap(_LineTokens, "map_Pr", _Materials[_Materials.GetSize() - 1].RoughnessTexture, _Materials[_Materials.GetSize() - 1].RoughnessTextureSettings))
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "map_Pm")
		{
			if (_LineTokens.GetSize() < 2 || _Names.GetSize() == 0 || _Found_map_Pm || !_Found_illum)
			{
				return false;
			}

			_Found_map_Pm = true;

			if (!MaterialLibLoadMap(_LineTokens, "map_Pm", _Materials[_Materials.GetSize() - 1].MetalnessTexture, _Materials[_Materials.GetSize() - 1].MetalnessTextureSettings))
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "map_Pao")
		{
			if (_LineTokens.GetSize() < 2 || _Names.GetSize() == 0 || _Found_map_Pao || !_Found_illum)
			{
				return false;
			}

			_Found_map_Pao = true;

			if (!MaterialLibLoadMap(_LineTokens, "map_Pao", _Materials[_Materials.GetSize() - 1].AmbientOcclusionTexture, _Materials[_Materials.GetSize() - 1].AmbientOcclusionTextureSettings))
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "map_Ka")
		{
			if (_LineTokens.GetSize() < 2 || _Names.GetSize() == 0 || _Found_map_Ka || !_Found_illum)
			{
				return false;
			}

			_Found_map_Ka = true;

			if (!MaterialLibLoadMap(_LineTokens, "map_Ka", _Materials[_Materials.GetSize() - 1].AmbientColorTexture, _Materials[_Materials.GetSize() - 1].AmbientColorTextureSettings))
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "map_Ps")
		{
			if (_LineTokens.GetSize() < 2 || _Names.GetSize() == 0 || _Found_map_Ps || !_Found_illum)
			{
				return false;
			}

			_Found_map_Ps = true;

			if (!MaterialLibLoadMap(_LineTokens, "map_Ps", _Materials[_Materials.GetSize() - 1].SheenTexture, _Materials[_Materials.GetSize() - 1].SheenTextureSettings))
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "map_Psc")
		{
			if (_LineTokens.GetSize() < 2 || _Names.GetSize() == 0 || _Found_map_Psc || !_Found_illum)
			{
				return false;
			}

			_Found_map_Psc = true;

			if (!MaterialLibLoadMap(_LineTokens, "map_Psc", _Materials[_Materials.GetSize() - 1].SheenColorTexture, _Materials[_Materials.GetSize() - 1].SheenColorTextureSettings))
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "map_Pc")
		{
			if (_LineTokens.GetSize() < 2 || _Names.GetSize() == 0 || _Found_map_Pc || !_Found_illum)
			{
				return false;
			}

			_Found_map_Pc = true;

			if (!MaterialLibLoadMap(_LineTokens, "map_Pc", _Materials[_Materials.GetSize() - 1].ClearCoatTexture, _Materials[_Materials.GetSize() - 1].ClearCoatTextureSettings))
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "map_Pcc")
		{
			if (_LineTokens.GetSize() < 2 || _Names.GetSize() == 0 || _Found_map_Pcc || !_Found_illum)
			{
				return false;
			}

			_Found_map_Pcc = true;

			if (!MaterialLibLoadMap(_LineTokens, "map_Pcc", _Materials[_Materials.GetSize() - 1].ClearCoatColorTexture, _Materials[_Materials.GetSize() - 1].ClearCoatColorTextureSettings))
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "map_Pcr")
		{
			if (_LineTokens.GetSize() < 2 || _Names.GetSize() == 0 || _Found_map_Pcr || !_Found_illum)
			{
				return false;
			}

			_Found_map_Pcr = true;

			if (!MaterialLibLoadMap(_LineTokens, "map_Pcr", _Materials[_Materials.GetSize() - 1].ClearCoatRoughnessTexture, _Materials[_Materials.GetSize() - 1].ClearCoatRoughnessTextureSettings))
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "map_aniso")
		{
			if (_LineTokens.GetSize() < 2 || _Names.GetSize() == 0 || _Found_map_aniso || !_Found_illum)
			{
				return false;
			}

			_Found_map_aniso = true;

			if (!MaterialLibLoadMap(_LineTokens, "map_aniso", _Materials[_Materials.GetSize() - 1].AnisotropyTexture, _Materials[_Materials.GetSize() - 1].AnisotropyTextureSettings))
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "map_anisor")
		{
			if (_LineTokens.GetSize() < 2 || _Names.GetSize() == 0 || _Found_map_anisor || !_Found_illum)
			{
				return false;
			}

			_Found_map_anisor = true;

			if (!MaterialLibLoadMap(_LineTokens, "map_anisor", _Materials[_Materials.GetSize() - 1].AnisotropyRotationTexture, _Materials[_Materials.GetSize() - 1].AnisotropyRotationTextureSettings))
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "map_d")
		{
			if (_LineTokens.GetSize() < 2 || _Names.GetSize() == 0 || _Found_map_d || !_Found_illum)
			{
				return false;
			}

			_Found_map_d = true;

			if (!MaterialLibLoadMap(_LineTokens, "map_d", _Materials[_Materials.GetSize() - 1].AlphaTexture, _Materials[_Materials.GetSize() - 1].AlphaTextureSettings))
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "map_Tf")
		{
			if (_LineTokens.GetSize() < 2 || _Names.GetSize() == 0 || _Found_map_Tf || !_Found_illum)
			{
				return false;
			}

			_Found_map_Tf = true;

			if (!MaterialLibLoadMap(_LineTokens, "map_Tf", _Materials[_Materials.GetSize() - 1].TransmissionFilterTexture, _Materials[_Materials.GetSize() - 1].TransmissionFilterTextureSettings))
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "disp")
		{
			if (_LineTokens.GetSize() < 2 || _Names.GetSize() == 0 || _Found_disp || !_Found_illum)
			{
				return false;
			}

			_Found_disp = true;

			if (!MaterialLibLoadMap(_LineTokens, "disp", _Materials[_Materials.GetSize() - 1].DisplacementTexture, _Materials[_Materials.GetSize() - 1].DisplacementTextureSettings))
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "norm")
		{
			if (_LineTokens.GetSize() < 2 || _Names.GetSize() == 0 || _Found_norm || !_Found_illum)
			{
				return false;
			}

			_Found_norm = true;

			if (!MaterialLibLoadMap(_LineTokens, "norm", _Materials[_Materials.GetSize() - 1].NormalTexture, _Materials[_Materials.GetSize() - 1].NormalTextureSettings))
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "tang")
		{
			if (_LineTokens.GetSize() < 2 || _Names.GetSize() == 0 || _Found_tang || !_Found_illum)
			{
				return false;
			}

			_Found_tang = true;

			if (!MaterialLibLoadMap(_LineTokens, "tang", _Materials[_Materials.GetSize() - 1].TangentTexture, _Materials[_Materials.GetSize() - 1].TangentTextureSettings))
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "map_Pcn")
		{
			if (_LineTokens.GetSize() < 2 || _Names.GetSize() == 0 || _Found_map_Pcn || !_Found_illum)
			{
				return false;
			}

			_Found_map_Pcn = true;

			if (!MaterialLibLoadMap(_LineTokens, "map_Pcn", _Materials[_Materials.GetSize() - 1].ClearCoatNormalTexture, _Materials[_Materials.GetSize() - 1].ClearCoatNormalTextureSettings))
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "decal")
		{
			if (_LineTokens.GetSize() < 2 || _Names.GetSize() == 0 || _Found_decal || !_Found_illum)
			{
				return false;
			}

			_Found_decal = true;

			if (!MaterialLibLoadMap(_LineTokens, "decal", _Materials[_Materials.GetSize() - 1].DecalTexture, _Materials[_Materials.GetSize() - 1].DecalTextureSettings))
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "bump")
		{
			if (_LineTokens.GetSize() < 2 || _Names.GetSize() == 0 || _Found_bump_map_Bump || !_Found_illum)
			{
				return false;
			}

			_Found_bump_map_Bump = true;

			if (!MaterialLibLoadMap(_LineTokens, "bump", _Materials[_Materials.GetSize() - 1].BumpTexture, _Materials[_Materials.GetSize() - 1].BumpTextureSettings))
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "map_Bump")
		{
			if (_LineTokens.GetSize() < 2 || _Names.GetSize() == 0 || _Found_bump_map_Bump || !_Found_illum)
			{
				return false;
			}

			_Found_bump_map_Bump = true;

			if (!MaterialLibLoadMap(_LineTokens, "bump", _Materials[_Materials.GetSize() - 1].BumpTexture, _Materials[_Materials.GetSize() - 1].BumpTextureSettings))
			{
				return false;
			}

			continue;
		}

		if (_LineTokens[0] == "refl")
		{
			if (_LineTokens.GetSize() < 2 || _Names.GetSize() == 0 || !_Found_illum)
			{
				return false;
			}

			if (_Materials[_Materials.GetSize() - 1].ReflectionTextures.GetSize() == 0)
			{
				_Materials[_Materials.GetSize() - 1].ReflectionTextures.Reserve(1);
				_Materials[_Materials.GetSize() - 1].ReflectionTexturesSettings.Reserve(1);

				if (!MaterialLibLoadMap(_LineTokens, "refl", _Materials[_Materials.GetSize() - 1].ReflectionTextures[0], _Materials[_Materials.GetSize() - 1].ReflectionTexturesSettings[0]))
				{
					return false;
				}

				if (_Materials[_Materials.GetSize() - 1].ReflectionTexturesSettings[0].ReflectionType != BFW_STRING_PREFIX("sphere"))
				{
					_Materials[_Materials.GetSize() - 1].ReflectionTextures.Reserve(6);
					_Materials[_Materials.GetSize() - 1].ReflectionTexturesSettings.Reserve(6);
				}
			}
			else if (_Materials[_Materials.GetSize() - 1].ReflectionTextures.GetSize() == 1)
			{
				return false;
			}
			else if (_Materials[_Materials.GetSize() - 1].ReflectionTextures.GetSize() == 6)
			{
				size_t _NextIndex = 0;

				while (_NextIndex < 6 && _Materials[_Materials.GetSize() - 1].ReflectionTexturesSettings[_NextIndex].ReflectionType.size())
				{
					_NextIndex++;
				}

				if (_NextIndex == 6)
				{
					return false;
				}

				if (!MaterialLibLoadMap(_LineTokens, "refl", _Materials[_Materials.GetSize() - 1].ReflectionTextures[_NextIndex], _Materials[_Materials.GetSize() - 1].ReflectionTexturesSettings[_NextIndex]))
				{
					return false;
				}

				for (size_t _PrevIndex = 0; _PrevIndex < _NextIndex; _PrevIndex++)
				{
					if (_Materials[_Materials.GetSize() - 1].ReflectionTexturesSettings[_NextIndex].ReflectionType == _Materials[_Materials.GetSize() - 1].ReflectionTexturesSettings[_PrevIndex].ReflectionType)
					{
						return false;
					}
				}
			}

			continue;
		}

		if (_LineTokens[0] == "map_refl")
		{
			if (_LineTokens.GetSize() < 2 || _Names.GetSize() == 0 || !_Found_illum)
			{
				return false;
			}

			if (_Materials[_Materials.GetSize() - 1].ReflectionTextures.GetSize() == 0)
			{
				_Materials[_Materials.GetSize() - 1].ReflectionTextures.Reserve(1);
				_Materials[_Materials.GetSize() - 1].ReflectionTexturesSettings.Reserve(1);

				if (!MaterialLibLoadMap(_LineTokens, "refl", _Materials[_Materials.GetSize() - 1].ReflectionTextures[0], _Materials[_Materials.GetSize() - 1].ReflectionTexturesSettings[0]))
				{
					return false;
				}

				if (_Materials[_Materials.GetSize() - 1].ReflectionTexturesSettings[0].ReflectionType != BFW_STRING_PREFIX("sphere"))
				{
					_Materials[_Materials.GetSize() - 1].ReflectionTextures.Reserve(6);
					_Materials[_Materials.GetSize() - 1].ReflectionTexturesSettings.Reserve(6);
				}
			}
			else if (_Materials[_Materials.GetSize() - 1].ReflectionTextures.GetSize() == 1)
			{
				return false;
			}
			else if (_Materials[_Materials.GetSize() - 1].ReflectionTextures.GetSize() == 6)
			{
				size_t _NextIndex = 0;

				while (_NextIndex < 6 && _Materials[_Materials.GetSize() - 1].ReflectionTexturesSettings[_NextIndex].ReflectionType.size())
				{
					_NextIndex++;
				}

				if (_NextIndex == 6)
				{
					return false;
				}

				if (!MaterialLibLoadMap(_LineTokens, "refl", _Materials[_Materials.GetSize() - 1].ReflectionTextures[_NextIndex], _Materials[_Materials.GetSize() - 1].ReflectionTexturesSettings[_NextIndex]))
				{
					return false;
				}

				for (size_t _PrevIndex = 0; _PrevIndex < _NextIndex; _PrevIndex++)
				{
					if (_Materials[_Materials.GetSize() - 1].ReflectionTexturesSettings[_NextIndex].ReflectionType == _Materials[_Materials.GetSize() - 1].ReflectionTexturesSettings[_PrevIndex].ReflectionType)
					{
						return false;
					}
				}
			}

			continue;
		}
	}

	if (_FileIndex != _FileContent.GetLength() - 1)
	{
		return false;
	}

	for (size_t _Index = 0; _Index < _Materials.GetSize(); _Index++)
	{
		if (!_Materials[_Index].IsValid())
		{
			return false;
		}
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
	if (!MaterialNames.GetSize())
	{
		return FileContent();
	}

	BFW_STRING_STREAM_TYPE_A _Stream;

	_Stream.imbue(std::locale::classic());

	for (size_t _NameIndex = 0; _NameIndex < MaterialNames.GetSize(); _NameIndex++)
	{
		const Material& _CurrentMaterial = *Materials.GetData(MaterialNames[_NameIndex].c_str());

		if (!_CurrentMaterial.IsValid())
		{
			return FileContent();
		}

		_Stream << "newmtl ";

		if (!WaveFrontSaveString(_Stream, MaterialNames[_NameIndex]))
		{
			return FileContent();
		}

		_Stream BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';

		_Stream << "Kd " << _CurrentMaterial.Albedo.x << ' ' << _CurrentMaterial.Albedo.y << ' ' << _CurrentMaterial.Albedo.z BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
		_Stream << "Ks " << _CurrentMaterial.SpecularColor.x << ' ' << _CurrentMaterial.SpecularColor.y << ' ' << _CurrentMaterial.SpecularColor.z BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
		_Stream << "Ns " << _CurrentMaterial.SpecularExponent BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
		_Stream << "Ke " << _CurrentMaterial.EmissionColor.x << ' ' << _CurrentMaterial.EmissionColor.y << ' ' << _CurrentMaterial.EmissionColor.z BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
		_Stream << "Pr " << _CurrentMaterial.Roughness BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
		_Stream << "Pm " << _CurrentMaterial.Metalness BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
		_Stream << "Pao " << _CurrentMaterial.AmbientOcclusion BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
		_Stream << "Ka " << _CurrentMaterial.AmbientColor.x << ' ' << _CurrentMaterial.AmbientColor.y << ' ' << _CurrentMaterial.AmbientColor.z BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
		_Stream << "Ps " << _CurrentMaterial.Sheen BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
		_Stream << "Psc " << _CurrentMaterial.SheenColor.x << ' ' << _CurrentMaterial.SheenColor.y << ' ' << _CurrentMaterial.SheenColor.z BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
		_Stream << "Pc " << _CurrentMaterial.ClearCoat BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
		_Stream << "Pcc " << _CurrentMaterial.ClearCoatColor.x << ' ' << _CurrentMaterial.ClearCoatColor.y << ' ' << _CurrentMaterial.ClearCoatColor.z BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
		_Stream << "Pcr " << _CurrentMaterial.ClearCoatRoughness BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
		_Stream << "aniso " << _CurrentMaterial.Anisotropy BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
		_Stream << "anisor " << _CurrentMaterial.AnisotropyRotation BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
		_Stream << "d " << _CurrentMaterial.Alpha BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
		_Stream << "Tf " << _CurrentMaterial.TransmissionFilter.x << ' ' << _CurrentMaterial.TransmissionFilter.y << ' ' << _CurrentMaterial.TransmissionFilter.z BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
		_Stream << "Ni " << _CurrentMaterial.IndexOfRefraction BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
		_Stream << "Kdisp " << _CurrentMaterial.Displacement BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
		_Stream << "Kn " << _CurrentMaterial.Normal.x << ' ' << _CurrentMaterial.Normal.y << ' ' << _CurrentMaterial.Normal.z BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
		_Stream << "Kt " << _CurrentMaterial.Tangent.x << ' ' << _CurrentMaterial.Tangent.y << ' ' << _CurrentMaterial.Tangent.z BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
		_Stream << "Pcn " << _CurrentMaterial.ClearCoatNormal.x << ' ' << _CurrentMaterial.ClearCoatNormal.y << ' ' << _CurrentMaterial.ClearCoatNormal.z BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';

		_Stream << "illum " << (uint16_t)(_CurrentMaterial.IlluminationModel) BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';

		if (!MaterialLibSaveMap(_Stream, "map_Kd", _CurrentMaterial.AlbedoTextureSettings, _CurrentMaterial.AlbedoTexture))
		{
			return FileContent();
		}

		if (!MaterialLibSaveMap(_Stream, "map_Ks", _CurrentMaterial.SpecularColorTextureSettings, _CurrentMaterial.SpecularColorTexture))
		{
			return FileContent();
		}

		if (!MaterialLibSaveMap(_Stream, "map_Ns", _CurrentMaterial.SpecularExponentTextureSettings, _CurrentMaterial.SpecularExponentTexture))
		{
			return FileContent();
		}

		if (!MaterialLibSaveMap(_Stream, "map_Ke", _CurrentMaterial.EmissionColorTextureSettings, _CurrentMaterial.EmissionColorTexture))
		{
			return FileContent();
		}

		if (!MaterialLibSaveMap(_Stream, "map_Pr", _CurrentMaterial.RoughnessTextureSettings, _CurrentMaterial.RoughnessTexture))
		{
			return FileContent();
		}

		if (!MaterialLibSaveMap(_Stream, "map_Pm", _CurrentMaterial.MetalnessTextureSettings, _CurrentMaterial.MetalnessTexture))
		{
			return FileContent();
		}

		if (!MaterialLibSaveMap(_Stream, "map_Pao", _CurrentMaterial.AmbientOcclusionTextureSettings, _CurrentMaterial.AmbientOcclusionTexture))
		{
			return FileContent();
		}

		if (!MaterialLibSaveMap(_Stream, "map_Ka", _CurrentMaterial.AmbientColorTextureSettings, _CurrentMaterial.AmbientColorTexture))
		{
			return FileContent();
		}

		if (!MaterialLibSaveMap(_Stream, "map_Ps", _CurrentMaterial.SheenTextureSettings, _CurrentMaterial.SheenTexture))
		{
			return FileContent();
		}

		if (!MaterialLibSaveMap(_Stream, "map_Psc", _CurrentMaterial.SheenColorTextureSettings, _CurrentMaterial.SheenColorTexture))
		{
			return FileContent();
		}

		if (!MaterialLibSaveMap(_Stream, "map_Pc", _CurrentMaterial.ClearCoatTextureSettings, _CurrentMaterial.ClearCoatTexture))
		{
			return FileContent();
		}

		if (!MaterialLibSaveMap(_Stream, "map_Pcc", _CurrentMaterial.ClearCoatColorTextureSettings, _CurrentMaterial.ClearCoatColorTexture))
		{
			return FileContent();
		}

		if (!MaterialLibSaveMap(_Stream, "map_Pcr", _CurrentMaterial.ClearCoatRoughnessTextureSettings, _CurrentMaterial.ClearCoatRoughnessTexture))
		{
			return FileContent();
		}

		if (!MaterialLibSaveMap(_Stream, "map_aniso", _CurrentMaterial.AnisotropyTextureSettings, _CurrentMaterial.AnisotropyTexture))
		{
			return FileContent();
		}

		if (!MaterialLibSaveMap(_Stream, "map_anisor", _CurrentMaterial.AnisotropyRotationTextureSettings, _CurrentMaterial.AnisotropyRotationTexture))
		{
			return FileContent();
		}

		if (!MaterialLibSaveMap(_Stream, "map_d", _CurrentMaterial.AlphaTextureSettings, _CurrentMaterial.AlphaTexture))
		{
			return FileContent();
		}

		if (!MaterialLibSaveMap(_Stream, "map_Tf", _CurrentMaterial.TransmissionFilterTextureSettings, _CurrentMaterial.TransmissionFilterTexture))
		{
			return FileContent();
		}

		if (!MaterialLibSaveMap(_Stream, "disp", _CurrentMaterial.DisplacementTextureSettings, _CurrentMaterial.DisplacementTexture))
		{
			return FileContent();
		}

		if (!MaterialLibSaveMap(_Stream, "norm", _CurrentMaterial.NormalTextureSettings, _CurrentMaterial.NormalTexture))
		{
			return FileContent();
		}

		if (!MaterialLibSaveMap(_Stream, "tang", _CurrentMaterial.TangentTextureSettings, _CurrentMaterial.TangentTexture))
		{
			return FileContent();
		}

		if (!MaterialLibSaveMap(_Stream, "map_Pcn", _CurrentMaterial.ClearCoatNormalTextureSettings, _CurrentMaterial.ClearCoatNormalTexture))
		{
			return FileContent();
		}

		if (!MaterialLibSaveMap(_Stream, "decal", _CurrentMaterial.DecalTextureSettings, _CurrentMaterial.DecalTexture))
		{
			return FileContent();
		}

		if (!MaterialLibSaveMap(_Stream, "bump", _CurrentMaterial.BumpTextureSettings, _CurrentMaterial.BumpTexture))
		{
			return FileContent();
		}

		if (_CurrentMaterial.ReflectionTextures.GetSize() != 0)
		{
			if (_CurrentMaterial.ReflectionTextures.GetSize() == 1)
			{
				if (!MaterialLibSaveMap(_Stream, "refl", _CurrentMaterial.ReflectionTexturesSettings[0], _CurrentMaterial.ReflectionTextures[0]))
				{
					return FileContent();
				}
			}
			else if (_CurrentMaterial.ReflectionTextures.GetSize() == 6)
			{
				for (size_t _Index = 0; _Index < _CurrentMaterial.ReflectionTextures.GetSize(); _Index++)
				{
					if (!MaterialLibSaveMap(_Stream, "refl", _CurrentMaterial.ReflectionTexturesSettings[_Index], _CurrentMaterial.ReflectionTextures[_Index]))
					{
						return FileContent();
					}
				}
			}
		}

		if (_NameIndex != MaterialNames.GetSize() - 1)
		{
			_Stream BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
		}
	}

	if (!_Stream)
	{
		return FileContent();
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
