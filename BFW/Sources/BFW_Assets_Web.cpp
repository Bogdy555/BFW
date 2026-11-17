#include "../Headers/BFW.hpp"



static const bool IsValidXMLFile(const BFW::Assets::FileContent& _FileContent)
{
	for (size_t _Index = 0; _Index < _FileContent.GetLength() - 1; _Index++)
	{
		if (BFW::String::IsUTF8MultiByte2(_FileContent[_Index]))
		{
			if (!BFW::String::IsValidUTF8MultiByte2(_FileContent[_Index]))
			{
				return false;
			}

			_Index++;

			if (_Index >= _FileContent.GetLength() - 1)
			{
				return false;
			}

			if (!BFW::String::IsUTF8MultiByteContinuation(_FileContent[_Index]))
			{
				return false;
			}

			uint32_t _CodePoint = BFW::String::ConstructUnicodePointA(_FileContent[_Index - 1], _FileContent[_Index]);

			if (!BFW::String::IsValidUnicodePoint2A(_CodePoint) || BFW::String::IsUnicodeSurrogated(_CodePoint) || BFW::String::IsUnicodeSurrogatedContinuation(_CodePoint))
			{
				return false;
			}

			if (_CodePoint != 0x9 && _CodePoint != 0xA && _CodePoint != 0xD && !(_CodePoint >= 0x20 && _CodePoint <= 0xD7FF) && !(_CodePoint >= 0xE000 && _CodePoint <= 0xFFFD) && !(_CodePoint >= 0x10000 && _CodePoint <= 0x10FFFF))
			{
				return false;
			}

			continue;
		}

		if (BFW::String::IsUTF8MultiByte3(_FileContent[_Index]))
		{
			if (!BFW::String::IsValidUTF8MultiByte3(_FileContent[_Index]))
			{
				return false;
			}

			_Index++;

			if (_Index >= _FileContent.GetLength() - 1)
			{
				return false;
			}

			if (!BFW::String::IsUTF8MultiByteContinuation(_FileContent[_Index]) || !BFW::String::IsValidUTF8MultiByte3FirstContinuation(_FileContent[_Index - 1], _FileContent[_Index]))
			{
				return false;
			}

			_Index++;

			if (_Index >= _FileContent.GetLength() - 1)
			{
				return false;
			}

			if (!BFW::String::IsUTF8MultiByteContinuation(_FileContent[_Index]))
			{
				return false;
			}

			uint32_t _CodePoint = BFW::String::ConstructUnicodePointA(_FileContent[_Index - 2], _FileContent[_Index - 1], _FileContent[_Index]);

			if (!BFW::String::IsValidUnicodePoint3A(_CodePoint) || BFW::String::IsUnicodeSurrogated(_CodePoint) || BFW::String::IsUnicodeSurrogatedContinuation(_CodePoint))
			{
				return false;
			}

			if (_CodePoint != 0x9 && _CodePoint != 0xA && _CodePoint != 0xD && !(_CodePoint >= 0x20 && _CodePoint <= 0xD7FF) && !(_CodePoint >= 0xE000 && _CodePoint <= 0xFFFD) && !(_CodePoint >= 0x10000 && _CodePoint <= 0x10FFFF))
			{
				return false;
			}

			continue;
		}

		if (BFW::String::IsUTF8MultiByte4(_FileContent[_Index]))
		{
			if (!BFW::String::IsValidUTF8MultiByte4(_FileContent[_Index]))
			{
				return false;
			}

			_Index++;

			if (_Index >= _FileContent.GetLength() - 1)
			{
				return false;
			}

			if (!BFW::String::IsUTF8MultiByteContinuation(_FileContent[_Index]) || !BFW::String::IsValidUTF8MultiByte4FirstContinuation(_FileContent[_Index - 1], _FileContent[_Index]))
			{
				return false;
			}

			_Index++;

			if (_Index >= _FileContent.GetLength() - 1)
			{
				return false;
			}

			if (!BFW::String::IsUTF8MultiByteContinuation(_FileContent[_Index]))
			{
				return false;
			}

			_Index++;

			if (_Index >= _FileContent.GetLength() - 1)
			{
				return false;
			}

			if (!BFW::String::IsUTF8MultiByteContinuation(_FileContent[_Index]))
			{
				return false;
			}

			uint32_t _CodePoint = BFW::String::ConstructUnicodePointA(_FileContent[_Index - 3], _FileContent[_Index - 2], _FileContent[_Index - 1], _FileContent[_Index]);

			if (!BFW::String::IsValidUnicodePoint4A(_CodePoint) || BFW::String::IsUnicodeSurrogated(_CodePoint) || BFW::String::IsUnicodeSurrogatedContinuation(_CodePoint))
			{
				return false;
			}

			if (_CodePoint != 0x9 && _CodePoint != 0xA && _CodePoint != 0xD && !(_CodePoint >= 0x20 && _CodePoint <= 0xD7FF) && !(_CodePoint >= 0xE000 && _CodePoint <= 0xFFFD) && !(_CodePoint >= 0x10000 && _CodePoint <= 0x10FFFF))
			{
				return false;
			}

			continue;
		}

		if (BFW::String::IsUTF8MultiByteContinuation(_FileContent[_Index]))
		{
			return false;
		}

		uint32_t _CodePoint = BFW::String::ConstructUnicodePointA(_FileContent[_Index]);

		if (!BFW::String::IsValidUnicodePoint1A(_CodePoint) || BFW::String::IsUnicodeSurrogated(_CodePoint) || BFW::String::IsUnicodeSurrogatedContinuation(_CodePoint))
		{
			return false;
		}

		if (_CodePoint != 0x9 && _CodePoint != 0xA && _CodePoint != 0xD && !(_CodePoint >= 0x20 && _CodePoint <= 0xD7FF) && !(_CodePoint >= 0xE000 && _CodePoint <= 0xFFFD) && !(_CodePoint >= 0x10000 && _CodePoint <= 0x10FFFF))
		{
			return false;
		}
	}

	return true;
}

static const bool IsValidXMLCDATA(const BFW_STRING_VIEW_TYPE_A& _Text)
{
	BFW::Vector<uint32_t> _CodePoints;

	for (size_t _Index = 0; _Index < _Text.size(); _Index++)
	{
		if (BFW::String::IsUTF8MultiByte2(_Text[_Index]))
		{
			if (!BFW::String::IsValidUTF8MultiByte2(_Text[_Index]))
			{
				return false;
			}

			_Index++;

			if (_Index >= _Text.size())
			{
				return false;
			}

			if (!BFW::String::IsUTF8MultiByteContinuation(_Text[_Index]))
			{
				return false;
			}

			uint32_t _CodePoint = BFW::String::ConstructUnicodePointA(_Text[_Index - 1], _Text[_Index]);

			if (!BFW::String::IsValidUnicodePoint2A(_CodePoint) || BFW::String::IsUnicodeSurrogated(_CodePoint) || BFW::String::IsUnicodeSurrogatedContinuation(_CodePoint))
			{
				return false;
			}

			_CodePoints.PushBack(_CodePoint);

			continue;
		}

		if (BFW::String::IsUTF8MultiByte3(_Text[_Index]))
		{
			if (!BFW::String::IsValidUTF8MultiByte3(_Text[_Index]))
			{
				return false;
			}

			_Index++;

			if (_Index >= _Text.size())
			{
				return false;
			}

			if (!BFW::String::IsUTF8MultiByteContinuation(_Text[_Index]) || !BFW::String::IsValidUTF8MultiByte3FirstContinuation(_Text[_Index - 1], _Text[_Index]))
			{
				return false;
			}

			_Index++;

			if (_Index >= _Text.size())
			{
				return false;
			}

			if (!BFW::String::IsUTF8MultiByteContinuation(_Text[_Index]))
			{
				return false;
			}

			uint32_t _CodePoint = BFW::String::ConstructUnicodePointA(_Text[_Index - 2], _Text[_Index - 1], _Text[_Index]);

			if (!BFW::String::IsValidUnicodePoint3A(_CodePoint) || BFW::String::IsUnicodeSurrogated(_CodePoint) || BFW::String::IsUnicodeSurrogatedContinuation(_CodePoint))
			{
				return false;
			}

			_CodePoints.PushBack(_CodePoint);

			continue;
		}

		if (BFW::String::IsUTF8MultiByte4(_Text[_Index]))
		{
			if (!BFW::String::IsValidUTF8MultiByte4(_Text[_Index]))
			{
				return false;
			}

			_Index++;

			if (_Index >= _Text.size())
			{
				return false;
			}

			if (!BFW::String::IsUTF8MultiByteContinuation(_Text[_Index]) || !BFW::String::IsValidUTF8MultiByte4FirstContinuation(_Text[_Index - 1], _Text[_Index]))
			{
				return false;
			}

			_Index++;

			if (_Index >= _Text.size())
			{
				return false;
			}

			if (!BFW::String::IsUTF8MultiByteContinuation(_Text[_Index]))
			{
				return false;
			}

			_Index++;

			if (_Index >= _Text.size())
			{
				return false;
			}

			if (!BFW::String::IsUTF8MultiByteContinuation(_Text[_Index]))
			{
				return false;
			}

			uint32_t _CodePoint = BFW::String::ConstructUnicodePointA(_Text[_Index - 3], _Text[_Index - 2], _Text[_Index - 1], _Text[_Index]);

			if (!BFW::String::IsValidUnicodePoint4A(_CodePoint) || BFW::String::IsUnicodeSurrogated(_CodePoint) || BFW::String::IsUnicodeSurrogatedContinuation(_CodePoint))
			{
				return false;
			}

			_CodePoints.PushBack(_CodePoint);

			continue;
		}

		if (BFW::String::IsUTF8MultiByteContinuation(_Text[_Index]))
		{
			return false;
		}

		uint32_t _CodePoint = BFW::String::ConstructUnicodePointA(_Text[_Index]);

		if (!BFW::String::IsValidUnicodePoint1A(_CodePoint) || BFW::String::IsUnicodeSurrogated(_CodePoint) || BFW::String::IsUnicodeSurrogatedContinuation(_CodePoint))
		{
			return false;
		}

		_CodePoints.PushBack(_CodePoint);
	}

	for (size_t _Index = 0; _Index < _CodePoints.GetSize(); _Index++)
	{
		if (_CodePoints[_Index] != 0x9 &&
			_CodePoints[_Index] != 0xA &&
			_CodePoints[_Index] != 0xD &&
			!(_CodePoints[_Index] >= 0x20 && _CodePoints[_Index] <= 0xD7FF) &&
			!(_CodePoints[_Index] >= 0xE000 && _CodePoints[_Index] <= 0xFFFD) &&
			!(_CodePoints[_Index] >= 0x10000 && _CodePoints[_Index] <= 0x10FFFF))
		{
			return false;
		}
	}

	return true;
}

static const bool IsValidXMLToken(const BFW_STRING_VIEW_TYPE_A& _Token)
{
	if (!_Token.size() || BFW_STRING_TYPE_A("-.:0123456789").find(_Token[0]) != BFW_STRING_TYPE_A::npos)
	{
		return false;
	}

	size_t _IndexDots = _Token.find(':');

	if (_IndexDots != BFW_STRING_TYPE_A::npos && BFW_STRING_TYPE_A("-.:0123456789").find(_Token[_IndexDots + 1]) != BFW_STRING_TYPE_A::npos)
	{
		return false;
	}

	BFW::Vector<uint32_t> _CodePoints;

	for (size_t _Index = 0; _Index < _Token.size(); _Index++)
	{
		if (BFW::String::IsUTF8MultiByte2(_Token[_Index]))
		{
			if (!BFW::String::IsValidUTF8MultiByte2(_Token[_Index]))
			{
				return false;
			}

			_Index++;

			if (_Index >= _Token.size())
			{
				return false;
			}

			if (!BFW::String::IsUTF8MultiByteContinuation(_Token[_Index]))
			{
				return false;
			}

			uint32_t _CodePoint = BFW::String::ConstructUnicodePointA(_Token[_Index - 1], _Token[_Index]);

			if (!BFW::String::IsValidUnicodePoint2A(_CodePoint) || BFW::String::IsUnicodeSurrogated(_CodePoint) || BFW::String::IsUnicodeSurrogatedContinuation(_CodePoint))
			{
				return false;
			}

			_CodePoints.PushBack(_CodePoint);

			continue;
		}

		if (BFW::String::IsUTF8MultiByte3(_Token[_Index]))
		{
			if (!BFW::String::IsValidUTF8MultiByte3(_Token[_Index]))
			{
				return false;
			}

			_Index++;

			if (_Index >= _Token.size())
			{
				return false;
			}

			if (!BFW::String::IsUTF8MultiByteContinuation(_Token[_Index]) || !BFW::String::IsValidUTF8MultiByte3FirstContinuation(_Token[_Index - 1], _Token[_Index]))
			{
				return false;
			}

			_Index++;

			if (_Index >= _Token.size())
			{
				return false;
			}

			if (!BFW::String::IsUTF8MultiByteContinuation(_Token[_Index]))
			{
				return false;
			}

			uint32_t _CodePoint = BFW::String::ConstructUnicodePointA(_Token[_Index - 2], _Token[_Index - 1], _Token[_Index]);

			if (!BFW::String::IsValidUnicodePoint3A(_CodePoint) || BFW::String::IsUnicodeSurrogated(_CodePoint) || BFW::String::IsUnicodeSurrogatedContinuation(_CodePoint))
			{
				return false;
			}

			_CodePoints.PushBack(_CodePoint);

			continue;
		}

		if (BFW::String::IsUTF8MultiByte4(_Token[_Index]))
		{
			if (!BFW::String::IsValidUTF8MultiByte4(_Token[_Index]))
			{
				return false;
			}

			_Index++;

			if (_Index >= _Token.size())
			{
				return false;
			}

			if (!BFW::String::IsUTF8MultiByteContinuation(_Token[_Index]) || !BFW::String::IsValidUTF8MultiByte4FirstContinuation(_Token[_Index - 1], _Token[_Index]))
			{
				return false;
			}

			_Index++;

			if (_Index >= _Token.size())
			{
				return false;
			}

			if (!BFW::String::IsUTF8MultiByteContinuation(_Token[_Index]))
			{
				return false;
			}

			_Index++;

			if (_Index >= _Token.size())
			{
				return false;
			}

			if (!BFW::String::IsUTF8MultiByteContinuation(_Token[_Index]))
			{
				return false;
			}

			uint32_t _CodePoint = BFW::String::ConstructUnicodePointA(_Token[_Index - 3], _Token[_Index - 2], _Token[_Index - 1], _Token[_Index]);

			if (!BFW::String::IsValidUnicodePoint4A(_CodePoint) || BFW::String::IsUnicodeSurrogated(_CodePoint) || BFW::String::IsUnicodeSurrogatedContinuation(_CodePoint))
			{
				return false;
			}

			_CodePoints.PushBack(_CodePoint);

			continue;
		}

		if (BFW::String::IsUTF8MultiByteContinuation(_Token[_Index]))
		{
			return false;
		}

		uint32_t _CodePoint = BFW::String::ConstructUnicodePointA(_Token[_Index]);

		if (!BFW::String::IsValidUnicodePoint1A(_CodePoint) || BFW::String::IsUnicodeSurrogated(_CodePoint) || BFW::String::IsUnicodeSurrogatedContinuation(_CodePoint))
		{
			return false;
		}

		_CodePoints.PushBack(_CodePoint);
	}

	if (_CodePoints[0] != '_' &&
		_CodePoints[0] != ':' &&
		!(_CodePoints[0] >= 'A' && _CodePoints[0] <= 'Z') &&
		!(_CodePoints[0] >= 'a' && _CodePoints[0] <= 'z') &&
		!(_CodePoints[0] >= 0xC0 && _CodePoints[0] <= 0xD6) &&
		!(_CodePoints[0] >= 0xD8 && _CodePoints[0] <= 0xF6) &&
		!(_CodePoints[0] >= 0xF8 && _CodePoints[0] <= 0x2FF) &&
		!(_CodePoints[0] >= 0x370 && _CodePoints[0] <= 0x37D) &&
		!(_CodePoints[0] >= 0x37F && _CodePoints[0] <= 0x1FFF) &&
		!(_CodePoints[0] >= 0x200C && _CodePoints[0] <= 0x200D) &&
		!(_CodePoints[0] >= 0x2070 && _CodePoints[0] <= 0x218F) &&
		!(_CodePoints[0] >= 0x2C00 && _CodePoints[0] <= 0x2FEF) &&
		!(_CodePoints[0] >= 0x3001 && _CodePoints[0] <= 0xD7FF) &&
		!(_CodePoints[0] >= 0xF900 && _CodePoints[0] <= 0xFDCF) &&
		!(_CodePoints[0] >= 0xFDF0 && _CodePoints[0] <= 0xFFFD) &&
		!(_CodePoints[0] >= 0x10000 && _CodePoints[0] <= 0xEFFFF))
	{
		return false;
	}

	if (_IndexDots != BFW_STRING_TYPE_A::npos &&
		_CodePoints[_IndexDots + 1] != '_' &&
		_CodePoints[_IndexDots + 1] != ':' &&
		!(_CodePoints[_IndexDots + 1] >= 'A' && _CodePoints[_IndexDots + 1] <= 'Z') &&
		!(_CodePoints[_IndexDots + 1] >= 'a' && _CodePoints[_IndexDots + 1] <= 'z') &&
		!(_CodePoints[_IndexDots + 1] >= 0xC0 && _CodePoints[_IndexDots + 1] <= 0xD6) &&
		!(_CodePoints[_IndexDots + 1] >= 0xD8 && _CodePoints[_IndexDots + 1] <= 0xF6) &&
		!(_CodePoints[_IndexDots + 1] >= 0xF8 && _CodePoints[_IndexDots + 1] <= 0x2FF) &&
		!(_CodePoints[_IndexDots + 1] >= 0x370 && _CodePoints[_IndexDots + 1] <= 0x37D) &&
		!(_CodePoints[_IndexDots + 1] >= 0x37F && _CodePoints[_IndexDots + 1] <= 0x1FFF) &&
		!(_CodePoints[_IndexDots + 1] >= 0x200C && _CodePoints[_IndexDots + 1] <= 0x200D) &&
		!(_CodePoints[_IndexDots + 1] >= 0x2070 && _CodePoints[_IndexDots + 1] <= 0x218F) &&
		!(_CodePoints[_IndexDots + 1] >= 0x2C00 && _CodePoints[_IndexDots + 1] <= 0x2FEF) &&
		!(_CodePoints[_IndexDots + 1] >= 0x3001 && _CodePoints[_IndexDots + 1] <= 0xD7FF) &&
		!(_CodePoints[_IndexDots + 1] >= 0xF900 && _CodePoints[_IndexDots + 1] <= 0xFDCF) &&
		!(_CodePoints[_IndexDots + 1] >= 0xFDF0 && _CodePoints[_IndexDots + 1] <= 0xFFFD) &&
		!(_CodePoints[_IndexDots + 1] >= 0x10000 && _CodePoints[_IndexDots + 1] <= 0xEFFFF))
	{
		return false;
	}

	size_t _Count = _CodePoints[0] == ':';

	for (size_t _Index = 1; _Index < _CodePoints.GetSize(); _Index++)
	{
		if (_CodePoints[_Index] != '-' &&
			_CodePoints[_Index] != '_' &&
			_CodePoints[_Index] != '.' &&
			_CodePoints[_Index] != ':' &&
			_CodePoints[_Index] != 0xB7 &&
			!(_CodePoints[_Index] >= 'A' && _CodePoints[_Index] <= 'Z') &&
			!(_CodePoints[_Index] >= 'a' && _CodePoints[_Index] <= 'z') &&
			!(_CodePoints[_Index] >= '0' && _CodePoints[_Index] <= '9') &&
			!(_CodePoints[_Index] >= 0xC0 && _CodePoints[_Index] <= 0xD6) &&
			!(_CodePoints[_Index] >= 0xD8 && _CodePoints[_Index] <= 0xF6) &&
			!(_CodePoints[_Index] >= 0xF8 && _CodePoints[_Index] <= 0x2FF) &&
			!(_CodePoints[_Index] >= 0x370 && _CodePoints[_Index] <= 0x37D) &&
			!(_CodePoints[_Index] >= 0x37F && _CodePoints[_Index] <= 0x1FFF) &&
			!(_CodePoints[_Index] >= 0x200C && _CodePoints[_Index] <= 0x200D) &&
			!(_CodePoints[_Index] >= 0x2070 && _CodePoints[_Index] <= 0x218F) &&
			!(_CodePoints[_Index] >= 0x2C00 && _CodePoints[_Index] <= 0x2FEF) &&
			!(_CodePoints[_Index] >= 0x3001 && _CodePoints[_Index] <= 0xD7FF) &&
			!(_CodePoints[_Index] >= 0xF900 && _CodePoints[_Index] <= 0xFDCF) &&
			!(_CodePoints[_Index] >= 0xFDF0 && _CodePoints[_Index] <= 0xFFFD) &&
			!(_CodePoints[_Index] >= 0x10000 && _CodePoints[_Index] <= 0xEFFFF) &&
			!(_CodePoints[_Index] >= 0x0300 && _CodePoints[_Index] <= 0x036F) &&
			!(_CodePoints[_Index] >= 0x203F && _CodePoints[_Index] <= 0x2040))
		{
			return false;
		}

		_Count += _CodePoints[_Index] == ':';
	}

	if (_Count > 1)
	{
		return false;
	}

	return true;
}

static const bool ValidateXMLNamespaces(const BFW::Assets::XMLNode& _Node, BFW::Vector<BFW_STRING_TYPE_A>& _Namespaces)
{
	size_t _Count = 0;

	for (size_t _Index = 0; _Index < _Node.GetAttributes().GetSize(); _Index++)
	{
		if (_Node.GetAttributes()[_Index].starts_with("xmlns:"))
		{
			BFW_STRING_TYPE_A _Namespace = _Node.GetAttributes()[_Index].substr(6, _Node.GetAttributes()[_Index].size() - 6);

			if (_Namespace.size() == 0 || ((_Namespace[0] == 'X' || _Namespace[0] == 'x') && (_Namespace[1] == 'M' || _Namespace[1] == 'm') && (_Namespace[2] == 'L' || _Namespace[2] == 'l')))
			{
				return false;
			}

			for (size_t _Index2 = 0; _Index2 < _Count; _Index2++)
			{
				if (_Namespace == _Namespaces[_Namespaces.GetSize() - _Count + _Index2])
				{
					return false;
				}
			}

			_Count++;
			_Namespaces.PushBack(_Namespace);
		}
	}

	size_t _IndexTag = _Node.GetTag().find(':');

	if (_IndexTag != BFW_STRING_TYPE_A::npos)
	{
		if (_IndexTag == _Node.GetTag().size() - 1 || _IndexTag == 0)
		{
			return false;
		}

		BFW_STRING_TYPE_A _Namespace = _Node.GetTag().substr(0, _IndexTag);

		bool _Found = (_Namespace[0] == 'X' || _Namespace[0] == 'x') && (_Namespace[1] == 'M' || _Namespace[1] == 'm') && (_Namespace[2] == 'L' || _Namespace[2] == 'l') && _Namespace[3] == '\0';

		for (size_t _Index = 0; _Index < _Namespaces.GetSize(); _Index++)
		{
			if (_Namespaces[_Index] == _Namespace)
			{
				_Found = true;
				break;
			}
		}

		if (!_Found)
		{
			return false;
		}
	}

	for (size_t _AttributeForIndex = 0; _AttributeForIndex < _Node.GetAttributes().GetSize(); _AttributeForIndex++)
	{
		if (_Node.GetAttributes()[_AttributeForIndex].starts_with("xmlns:"))
		{
			continue;
		}

		size_t _IndexAttribute = _Node.GetAttributes()[_AttributeForIndex].find(':');

		if (_IndexAttribute != BFW_STRING_TYPE_A::npos)
		{
			if (_IndexAttribute == _Node.GetAttributes()[_AttributeForIndex].size() - 1 || _IndexAttribute == 0)
			{
				return false;
			}

			BFW_STRING_TYPE_A _Namespace = _Node.GetAttributes()[_AttributeForIndex].substr(0, _IndexAttribute);

			bool _Found = (_Namespace[0] == 'X' || _Namespace[0] == 'x') && (_Namespace[1] == 'M' || _Namespace[1] == 'm') && (_Namespace[2] == 'L' || _Namespace[2] == 'l') && _Namespace[3] == '\0';

			for (size_t _Index = 0; _Index < _Namespaces.GetSize(); _Index++)
			{
				if (_Namespaces[_Index] == _Namespace)
				{
					_Found = true;
					break;
				}
			}

			if (!_Found)
			{
				return false;
			}
		}
	}

	for (size_t _Index = 0; _Index < _Node.GetChildren().GetSize(); _Index++)
	{
		if (_Node.GetChildren()[_Index].GetType() == BFW::Assets::_TextXMLNodeType)
		{
			continue;
		}

		if (!ValidateXMLNamespaces(_Node.GetChildren()[_Index], _Namespaces))
		{
			return false;
		}
	}

	for (size_t _Index = 0; _Index < _Count; _Index++)
	{
		_Namespaces.Erase(_Namespaces.GetSize() - 1);
	}

	return true;
}

static const bool SolveXMLNamespaces(const BFW::Assets::XMLNode& _Node, BFW::Vector<BFW_STRING_TYPE_A>& _Namespaces, BFW::Vector<BFW_STRING_TYPE_A>& _NamespaceValues, const BFW::Assets::XMLNode& _SolvingNode, BFW_STRING_TYPE_A& _SolvingTagNamespace, BFW::Vector<BFW_STRING_TYPE_A>& _SolvingAttributesNamespaces, bool& _Exit)
{
	size_t _Count = 0;

	for (size_t _Index = 0; _Index < _Node.GetAttributes().GetSize(); _Index++)
	{
		if (_Node.GetAttributes()[_Index].starts_with("xmlns:") || _Node.GetAttributes()[_Index] == "xmlns")
		{
			BFW_STRING_TYPE_A _Namespace = _Node.GetAttributes()[_Index].substr(6, _Node.GetAttributes()[_Index].size() - 6);

			if ((_Namespace.size() == 0 && _Node.GetAttributes()[_Index].starts_with("xmlns:")) || (_Namespace.size() != 0 && (_Namespace[0] == 'X' || _Namespace[0] == 'x') && (_Namespace[1] == 'M' || _Namespace[1] == 'm') && (_Namespace[2] == 'L' || _Namespace[2] == 'l')))
			{
				return false;
			}

			for (size_t _Index2 = 0; _Index2 < _Count; _Index2++)
			{
				if (_Namespace == _Namespaces[_Namespaces.GetSize() - _Count + _Index2])
				{
					return false;
				}
			}

			_Count++;
			_Namespaces.PushBack(_Namespace);
			_NamespaceValues.PushBack(_Node.GetAttributeValues()[_Index]);
		}
	}

	if (&_Node != &_SolvingNode)
	{
		for (size_t _Index = 0; _Index < _Node.GetChildren().GetSize(); _Index++)
		{
			if (_Node.GetChildren()[_Index].GetType() == BFW::Assets::_TextXMLNodeType)
			{
				continue;
			}

			if (SolveXMLNamespaces(_Node.GetChildren()[_Index], _Namespaces, _NamespaceValues, _SolvingNode, _SolvingTagNamespace, _SolvingAttributesNamespaces, _Exit))
			{
				return true;
			}

			if (_Exit)
			{
				return false;
			}
		}

		for (size_t _Index = 0; _Index < _Count; _Index++)
		{
			_Namespaces.Erase(_Namespaces.GetSize() - 1);
			_NamespaceValues.Erase(_NamespaceValues.GetSize() - 1);
		}

		return false;
	}

	size_t _IndexTag = _Node.GetTag().find(':');

	if (_IndexTag != BFW_STRING_TYPE_A::npos)
	{
		if (_IndexTag == _Node.GetTag().size() - 1 || _IndexTag == 0)
		{
			_Exit = true;
			return false;
		}

		BFW_STRING_TYPE_A _Namespace = _Node.GetTag().substr(0, _IndexTag);

		bool _Found = (_Namespace[0] == 'X' || _Namespace[0] == 'x') && (_Namespace[1] == 'M' || _Namespace[1] == 'm') && (_Namespace[2] == 'L' || _Namespace[2] == 'l') && _Namespace[3] == '\0';

		if (_Found)
		{
			_SolvingTagNamespace = "http://www.w3.org/XML/1998/namespace";
		}

		for (size_t _Index = 0; _Index < _Namespaces.GetSize(); _Index++)
		{
			if (_Namespaces[_Namespaces.GetSize() - 1 - _Index] == _Namespace)
			{
				_Found = true;
				_SolvingTagNamespace = _NamespaceValues[_NamespaceValues.GetSize() - 1 - _Index];
				break;
			}
		}

		if (!_Found)
		{
			_Exit = true;
			return false;
		}
	}
	else
	{
		for (size_t _Index = 0; _Index < _Namespaces.GetSize(); _Index++)
		{
			if (_Namespaces[_Namespaces.GetSize() - 1 - _Index] == "")
			{
				_SolvingTagNamespace = _NamespaceValues[_NamespaceValues.GetSize() - 1 - _Index];
				break;
			}
		}
	}

	_SolvingAttributesNamespaces.Reserve(_Node.GetAttributes().GetSize());

	for (size_t _AttributeForIndex = 0; _AttributeForIndex < _Node.GetAttributes().GetSize(); _AttributeForIndex++)
	{
		if (_Node.GetAttributes()[_AttributeForIndex].starts_with("xmlns:") || _Node.GetAttributes()[_AttributeForIndex] == "xmlns")
		{
			_SolvingAttributesNamespaces.EmplaceBack("http://www.w3.org/2000/xmlns/");
			continue;
		}

		_SolvingAttributesNamespaces.EmplaceBack("");

		size_t _IndexAttribute = _Node.GetAttributes()[_AttributeForIndex].find(':');

		if (_IndexAttribute != BFW_STRING_TYPE_A::npos)
		{
			if (_IndexAttribute == _Node.GetAttributes()[_AttributeForIndex].size() - 1 || _IndexAttribute == 0)
			{
				return false;
			}

			BFW_STRING_TYPE_A _Namespace = _Node.GetAttributes()[_AttributeForIndex].substr(0, _IndexAttribute);

			bool _Found = (_Namespace[0] == 'X' || _Namespace[0] == 'x') && (_Namespace[1] == 'M' || _Namespace[1] == 'm') && (_Namespace[2] == 'L' || _Namespace[2] == 'l') && _Namespace[3] == '\0';

			if (_Found)
			{
				_SolvingAttributesNamespaces[_SolvingAttributesNamespaces.GetSize() - 1] = "http://www.w3.org/XML/1998/namespace";
			}

			for (size_t _Index = 0; _Index < _Namespaces.GetSize(); _Index++)
			{
				if (_Namespaces[_Namespaces.GetSize() - 1 - _Index] == _Namespace)
				{
					_Found = true;
					_SolvingAttributesNamespaces[_SolvingAttributesNamespaces.GetSize() - 1] = _NamespaceValues[_NamespaceValues.GetSize() - 1 - _Index];
					break;
				}
			}

			if (!_Found)
			{
				return false;
			}
		}
	}

	return true;
}

static const bool LoadXMLComment(const BFW::Assets::FileContent& _FileContent, size_t& _CurrentPos)
{
	if (_FileContent[_CurrentPos] != '<' || _FileContent[_CurrentPos + 1] != '!' || _FileContent[_CurrentPos + 2] != '-' || _FileContent[_CurrentPos + 3] != '-')
	{
		return false;
	}

	_CurrentPos += 4;

	while (_CurrentPos + 2 < _FileContent.GetLength() - 1 && (_FileContent[_CurrentPos] != '-' || _FileContent[_CurrentPos + 1] != '-' || _FileContent[_CurrentPos + 2] != '>'))
	{
		if (_FileContent[_CurrentPos] == '-' && _FileContent[_CurrentPos + 1] == '-')
		{
			return false;
		}

		_CurrentPos++;
	}

	if (_CurrentPos + 2 == _FileContent.GetLength() - 1)
	{
		return false;
	}

	_CurrentPos += 3;

	while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
	{
		_CurrentPos++;
	}

	return true;
}

static const bool LoadXMLString(const BFW::Assets::FileContent& _FileContent, size_t& _CurrentPos, BFW_STRING_TYPE_A& _String)
{
	if (_FileContent[_CurrentPos] != '\"' && _FileContent[_CurrentPos] != '\'')
	{
		return false;
	}

	BFW_CHAR_TYPE_A _Quotes = _FileContent[_CurrentPos];

	_CurrentPos++;

	while (_CurrentPos < _FileContent.GetLength() - 1 && _FileContent[_CurrentPos] != _Quotes)
	{
		if (_FileContent[_CurrentPos] <= 0x08 || (_FileContent[_CurrentPos] >= 0x0B && _FileContent[_CurrentPos] <= 0x1F))
		{
			return false;
		}

		if (_FileContent[_CurrentPos] == '&' && _FileContent[_CurrentPos + 1] == '#' && _FileContent[_CurrentPos + 2] >= '0' && _FileContent[_CurrentPos + 2] <= '9')
		{
			_CurrentPos += 2;

			size_t _Count = 0;
			uint32_t _CodePoint = 0;

			while (_CurrentPos < _FileContent.GetLength() - 1 && _FileContent[_CurrentPos] >= '0' && _FileContent[_CurrentPos] <= '9' && _FileContent[_CurrentPos] != ';')
			{
				_CodePoint = _CodePoint * 10 + _FileContent[_CurrentPos] - '0';
				_Count++;
				_CurrentPos++;
			}

			if (_CurrentPos == _FileContent.GetLength() - 1 || _FileContent[_CurrentPos] != ';' || _Count > 7)
			{
				return false;
			}

			_CurrentPos++;

			if (_CodePoint == 0x0 || _CodePoint == 0xFFFE || _CodePoint == 0xFFFF || _CodePoint > 0x10FFFF || (_CodePoint >= 0xD800 && _CodePoint <= 0xDFFF))
			{
				return false;
			}

			BFW::Vector<BFW_CHAR_TYPE_W> _Chars = BFW::String::DeconstructUnicodePointW(_CodePoint);

			BFW_STRING_TYPE_W _WString = L"";

			for (size_t _Index = 0; _Index < _Chars.GetSize(); _Index++)
			{
				_WString += _Chars[_Index];
			}

			if (!BFW::String::IsValidUnicodeString(_WString))
			{
				return false;
			}

			bool _Error = false;
			_String += BFW::String::FromUnicodeToUTF8(_WString, &_Error);

			if (_Error)
			{
				return false;
			}

			continue;
		}

		if (_FileContent[_CurrentPos] == '&' && _FileContent[_CurrentPos + 1] == '#' && _FileContent[_CurrentPos + 2] == 'x' && BFW::String::IsHexA(_FileContent[_CurrentPos + 3]))
		{
			_CurrentPos += 3;

			size_t _Count = 0;
			uint32_t _CodePoint = 0;

			while (_CurrentPos < _FileContent.GetLength() - 1 && BFW::String::IsHexA(_FileContent[_CurrentPos]) && _FileContent[_CurrentPos] != ';')
			{
				_CodePoint = (_CodePoint << 4) + BFW::String::HexCharToNibbleA(_FileContent[_CurrentPos]);
				_Count++;
				_CurrentPos++;
			}

			if (_CurrentPos == _FileContent.GetLength() - 1 || _FileContent[_CurrentPos] != ';' || _Count > 6)
			{
				return false;
			}

			_CurrentPos++;

			if (_CodePoint == 0x0 || _CodePoint == 0xFFFE || _CodePoint == 0xFFFF || _CodePoint > 0x10FFFF || (_CodePoint >= 0xD800 && _CodePoint <= 0xDFFF))
			{
				return false;
			}

			BFW::Vector<BFW_CHAR_TYPE_W> _Chars = BFW::String::DeconstructUnicodePointW(_CodePoint);

			BFW_STRING_TYPE_W _WString = L"";

			for (size_t _Index = 0; _Index < _Chars.GetSize(); _Index++)
			{
				_WString += _Chars[_Index];
			}

			if (!BFW::String::IsValidUnicodeString(_WString))
			{
				return false;
			}

			bool _Error = false;
			_String += BFW::String::FromUnicodeToUTF8(_WString, &_Error);

			if (_Error)
			{
				return false;
			}

			continue;
		}

		if (_FileContent[_CurrentPos] == '&' && _FileContent[_CurrentPos + 1] == 'a' && _FileContent[_CurrentPos + 2] == 'm' && _FileContent[_CurrentPos + 3] == 'p' && _FileContent[_CurrentPos + 4] == ';')
		{
			_String += '&';
			_CurrentPos += 5;
			continue;
		}

		if (_FileContent[_CurrentPos] == '&' && _FileContent[_CurrentPos + 1] == 'l' && _FileContent[_CurrentPos + 2] == 't' && _FileContent[_CurrentPos + 3] == ';')
		{
			_String += '<';
			_CurrentPos += 4;
			continue;
		}

		if (_FileContent[_CurrentPos] == '&' && _FileContent[_CurrentPos + 1] == 'g' && _FileContent[_CurrentPos + 2] == 't' && _FileContent[_CurrentPos + 3] == ';')
		{
			_String += '>';
			_CurrentPos += 4;
			continue;
		}

		if (_FileContent[_CurrentPos] == '&' && _FileContent[_CurrentPos + 1] == 'q' && _FileContent[_CurrentPos + 2] == 'u' && _FileContent[_CurrentPos + 3] == 'o' && _FileContent[_CurrentPos + 4] == 't' && _FileContent[_CurrentPos + 5] == ';')
		{
			_String += '\"';
			_CurrentPos += 6;
			continue;
		}

		if (_FileContent[_CurrentPos] == '&' && _FileContent[_CurrentPos + 1] == 'a' && _FileContent[_CurrentPos + 2] == 'p' && _FileContent[_CurrentPos + 3] == 'o' && _FileContent[_CurrentPos + 4] == 's' && _FileContent[_CurrentPos + 5] == ';')
		{
			_String += '\'';
			_CurrentPos += 6;
			continue;
		}

		_String += _FileContent[_CurrentPos];
		_CurrentPos++;
	}

	if (_CurrentPos == _FileContent.GetLength() - 1)
	{
		return false;
	}

	_CurrentPos++;

	while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
	{
		_CurrentPos++;
	}

	return true;
}

static const bool LoadXMLText(const BFW::Assets::FileContent& _FileContent, size_t& _CurrentPos, BFW::Assets::XMLNode& _Entry)
{
	BFW_STRING_TYPE_A _String;
	bool _EndCDATA = false;

	while (_CurrentPos < _FileContent.GetLength() - 1 && (_FileContent[_CurrentPos] != '<' || (_FileContent[_CurrentPos + 1] == '!' && ((_FileContent[_CurrentPos + 2] == '-' && _FileContent[_CurrentPos + 3] == '-') || (_FileContent[_CurrentPos + 2] == '[' && _FileContent[_CurrentPos + 3] == 'C' && _FileContent[_CurrentPos + 4] == 'D' && _FileContent[_CurrentPos + 5] == 'A' && _FileContent[_CurrentPos + 6] == 'T' && _FileContent[_CurrentPos + 7] == 'A' && _FileContent[_CurrentPos + 8] == '[')))))
	{
		_EndCDATA = false;

		if (_FileContent[_CurrentPos] == '\r' && _FileContent[_CurrentPos + 1] == '\n')
		{
			_CurrentPos++;
			continue;
		}

		if (_FileContent[_CurrentPos] == '<' && _FileContent[_CurrentPos + 1] == '!' && _FileContent[_CurrentPos + 2] == '-' && _FileContent[_CurrentPos + 3] == '-')
		{
			if (!LoadXMLComment(_FileContent, _CurrentPos))
			{
				return false;
			}

			continue;
		}

		if (_FileContent[_CurrentPos] == '<' && _FileContent[_CurrentPos + 1] == '!' && _FileContent[_CurrentPos + 2] == '[' && _FileContent[_CurrentPos + 3] == 'C' && _FileContent[_CurrentPos + 4] == 'D' && _FileContent[_CurrentPos + 5] == 'A' && _FileContent[_CurrentPos + 6] == 'T' && _FileContent[_CurrentPos + 7] == 'A' && _FileContent[_CurrentPos + 8] == '[')
		{
			_EndCDATA = true;

			_CurrentPos += 9;

			size_t _StringIndex = _String.size();

			while (_CurrentPos + 2 < _FileContent.GetLength() - 1 && (_FileContent[_CurrentPos] != ']' || _FileContent[_CurrentPos + 1] != ']' || _FileContent[_CurrentPos + 2] != '>'))
			{
				if (_FileContent[_CurrentPos] == '\r' && _FileContent[_CurrentPos + 1] == '\n')
				{
					_CurrentPos++;
					continue;
				}

				if (_FileContent[_CurrentPos] <= 0x08 || (_FileContent[_CurrentPos] >= 0x0B && _FileContent[_CurrentPos] <= 0x1F))
				{
					return false;
				}

				_String += _FileContent[_CurrentPos];
				_CurrentPos++;
			}

			if (_CurrentPos + 2 == _FileContent.GetLength() - 1)
			{
				return false;
			}

			_CurrentPos += 3;

			if (_String.size() && !IsValidXMLCDATA(_String.data() + _StringIndex))
			{
				return false;
			}

			continue;
		}

		if (_FileContent[_CurrentPos] <= 0x08 || (_FileContent[_CurrentPos] >= 0x0B && _FileContent[_CurrentPos] <= 0x1F))
		{
			return false;
		}

		if (_FileContent[_CurrentPos] == '&' && _FileContent[_CurrentPos + 1] == '#' && _FileContent[_CurrentPos + 2] >= '0' && _FileContent[_CurrentPos + 2] <= '9')
		{
			_CurrentPos += 2;

			size_t _Count = 0;
			uint32_t _CodePoint = 0;

			while (_CurrentPos < _FileContent.GetLength() - 1 && _FileContent[_CurrentPos] >= '0' && _FileContent[_CurrentPos] <= '9' && _FileContent[_CurrentPos] != ';')
			{
				_CodePoint = _CodePoint * 10 + _FileContent[_CurrentPos] - '0';
				_Count++;
				_CurrentPos++;
			}

			if (_CurrentPos == _FileContent.GetLength() - 1 || _FileContent[_CurrentPos] != ';' || _Count > 7)
			{
				return false;
			}

			_CurrentPos++;

			if (_CodePoint == 0x0 || _CodePoint == 0xFFFE || _CodePoint == 0xFFFF || _CodePoint > 0x10FFFF || (_CodePoint >= 0xD800 && _CodePoint <= 0xDFFF))
			{
				return false;
			}

			BFW::Vector<BFW_CHAR_TYPE_W> _Chars = BFW::String::DeconstructUnicodePointW(_CodePoint);

			BFW_STRING_TYPE_W _WString = L"";

			for (size_t _Index = 0; _Index < _Chars.GetSize(); _Index++)
			{
				_WString += _Chars[_Index];
			}

			if (!BFW::String::IsValidUnicodeString(_WString))
			{
				return false;
			}

			bool _Error = false;
			_String += BFW::String::FromUnicodeToUTF8(_WString, &_Error);

			if (_Error)
			{
				return false;
			}

			continue;
		}

		if (_FileContent[_CurrentPos] == '&' && _FileContent[_CurrentPos + 1] == '#' && _FileContent[_CurrentPos + 2] == 'x' && BFW::String::IsHexA(_FileContent[_CurrentPos + 3]))
		{
			_CurrentPos += 3;

			size_t _Count = 0;
			uint32_t _CodePoint = 0;

			while (_CurrentPos < _FileContent.GetLength() - 1 && BFW::String::IsHexA(_FileContent[_CurrentPos]) && _FileContent[_CurrentPos] != ';')
			{
				_CodePoint = (_CodePoint << 4) + BFW::String::HexCharToNibbleA(_FileContent[_CurrentPos]);
				_Count++;
				_CurrentPos++;
			}

			if (_CurrentPos == _FileContent.GetLength() - 1 || _FileContent[_CurrentPos] != ';' || _Count > 6)
			{
				return false;
			}

			_CurrentPos++;

			if (_CodePoint == 0x0 || _CodePoint == 0xFFFE || _CodePoint == 0xFFFF || _CodePoint > 0x10FFFF || (_CodePoint >= 0xD800 && _CodePoint <= 0xDFFF))
			{
				return false;
			}

			BFW::Vector<BFW_CHAR_TYPE_W> _Chars = BFW::String::DeconstructUnicodePointW(_CodePoint);

			BFW_STRING_TYPE_W _WString = L"";

			for (size_t _Index = 0; _Index < _Chars.GetSize(); _Index++)
			{
				_WString += _Chars[_Index];
			}

			if (!BFW::String::IsValidUnicodeString(_WString))
			{
				return false;
			}

			bool _Error = false;
			_String += BFW::String::FromUnicodeToUTF8(_WString, &_Error);

			if (_Error)
			{
				return false;
			}

			continue;
		}

		if (_FileContent[_CurrentPos] == '&' && _FileContent[_CurrentPos + 1] == 'a' && _FileContent[_CurrentPos + 2] == 'm' && _FileContent[_CurrentPos + 3] == 'p' && _FileContent[_CurrentPos + 4] == ';')
		{
			_String += '&';
			_CurrentPos += 5;
			continue;
		}

		if (_FileContent[_CurrentPos] == '&' && _FileContent[_CurrentPos + 1] == 'l' && _FileContent[_CurrentPos + 2] == 't' && _FileContent[_CurrentPos + 3] == ';')
		{
			_String += '<';
			_CurrentPos += 4;
			continue;
		}

		if (_FileContent[_CurrentPos] == '&' && _FileContent[_CurrentPos + 1] == 'g' && _FileContent[_CurrentPos + 2] == 't' && _FileContent[_CurrentPos + 3] == ';')
		{
			_String += '>';
			_CurrentPos += 4;
			continue;
		}

		if (_FileContent[_CurrentPos] == '&' && _FileContent[_CurrentPos + 1] == 'q' && _FileContent[_CurrentPos + 2] == 'u' && _FileContent[_CurrentPos + 3] == 'o' && _FileContent[_CurrentPos + 4] == 't' && _FileContent[_CurrentPos + 5] == ';')
		{
			_String += '\"';
			_CurrentPos += 6;
			continue;
		}

		if (_FileContent[_CurrentPos] == '&' && _FileContent[_CurrentPos + 1] == 'a' && _FileContent[_CurrentPos + 2] == 'p' && _FileContent[_CurrentPos + 3] == 'o' && _FileContent[_CurrentPos + 4] == 's' && _FileContent[_CurrentPos + 5] == ';')
		{
			_String += '\'';
			_CurrentPos += 6;
			continue;
		}

		_String += _FileContent[_CurrentPos];
		_CurrentPos++;
	}

	if (_CurrentPos == _FileContent.GetLength() - 1)
	{
		return false;
	}

	if (!_EndCDATA)
	{
		size_t _Index = 0;

		while (_Index < _String.size() && std::isspace((const unsigned BFW_CHAR_TYPE_A)(_String[_String.size() - 1 - _Index])))
		{
			_Index++;
		}

		_String = _String.substr(0, _String.size() - _Index);
	}

	if (!_String.size())
	{
		return false;
	}

	_Entry.SetText(_String);

	while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
	{
		_CurrentPos++;
	}

	return true;
}

static const bool LoadXMLEntry(const BFW::Assets::FileContent& _FileContent, size_t& _CurrentPos, BFW::Assets::XMLNode& _Entry, bool& _LeftClosed, bool& _RightClosed)
{
	_LeftClosed = false;
	_RightClosed = false;

	if (_FileContent[_CurrentPos] != '<')
	{
		return false;
	}

	_CurrentPos++;

	if (_FileContent[_CurrentPos] == '/')
	{
		_LeftClosed = true;
		_CurrentPos++;
	}

	while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
	{
		_CurrentPos++;
	}

	BFW_STRING_TYPE_A _Tag;

	while (_CurrentPos < _FileContent.GetLength() - 1 && !std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])) && _FileContent[_CurrentPos] != '>' && (_FileContent[_CurrentPos] != '/' || _FileContent[_CurrentPos + 1] != '>'))
	{
		_Tag += _FileContent[_CurrentPos];
		_CurrentPos++;
	}

	if (_CurrentPos == _FileContent.GetLength() - 1 || !IsValidXMLToken(_Tag))
	{
		return false;
	}

	while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
	{
		_CurrentPos++;
	}

	_Entry.SetTag(_Tag);

	BFW::Vector<BFW_STRING_TYPE_A>& _Attributes = _Entry.GetAttributes();
	BFW::Vector<BFW_STRING_TYPE_A>& _AttributeValues = _Entry.GetAttributeValues();

	while (_CurrentPos < _FileContent.GetLength() - 1 && _FileContent[_CurrentPos] != '>' && (_FileContent[_CurrentPos] != '/' || _FileContent[_CurrentPos + 1] != '>'))
	{
		BFW_STRING_TYPE_A _Attribute;

		while (_CurrentPos < _FileContent.GetLength() - 1 && !std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])) && _FileContent[_CurrentPos] != '>' && (_FileContent[_CurrentPos] != '/' || _FileContent[_CurrentPos + 1] != '>') && _FileContent[_CurrentPos] != '=')
		{
			_Attribute += _FileContent[_CurrentPos];
			_CurrentPos++;
		}

		if (_CurrentPos == _FileContent.GetLength() - 1 || !IsValidXMLToken(_Attribute))
		{
			return false;
		}

		while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
		{
			_CurrentPos++;
		}

		_Attributes.PushBack(_Attribute);

		if (_FileContent[_CurrentPos] != '=')
		{
			_AttributeValues.EmplaceBack("");
			continue;
		}

		_CurrentPos++;

		while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
		{
			_CurrentPos++;
		}

		BFW_STRING_TYPE_A _AttributeValue;

		if (!LoadXMLString(_FileContent, _CurrentPos, _AttributeValue))
		{
			return false;
		}

		_AttributeValues.PushBack(_AttributeValue);
	}

	if (_CurrentPos == _FileContent.GetLength() - 1)
	{
		return false;
	}

	if (_FileContent[_CurrentPos] == '/')
	{
		_RightClosed = true;
		_CurrentPos++;
	}

	_CurrentPos++;

	if ((_LeftClosed && _RightClosed) || (_LeftClosed && _Attributes.GetSize()))
	{
		return false;
	}

	while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
	{
		_CurrentPos++;
	}

	return true;
}

static const bool LoadXMLExclamation(const BFW::Assets::FileContent& _FileContent, size_t& _CurrentPos, BFW::Vector<BFW::Assets::XMLNode>& _ExclamationMarks)
{
	if (_FileContent[_CurrentPos] != '<' || _FileContent[_CurrentPos + 1] != '!')
	{
		return false;
	}

	_CurrentPos += 2;

	while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
	{
		_CurrentPos++;
	}

	BFW_STRING_TYPE_A _Tag;

	while (_CurrentPos < _FileContent.GetLength() - 1 && !std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])) && _FileContent[_CurrentPos] != '>')
	{
		_Tag += _FileContent[_CurrentPos];
		_CurrentPos++;
	}

	if (_CurrentPos == _FileContent.GetLength() - 1 || _Tag != "DOCTYPE")
	{
		return false;
	}

	while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
	{
		_CurrentPos++;
	}

	BFW::Assets::XMLNode& _Exclamation = _ExclamationMarks.EmplaceBack(BFW::Assets::XMLNode());

	_Exclamation.SetTag(_Tag);

	BFW::Vector<BFW_STRING_TYPE_A>& _Attributes = _Exclamation.GetAttributes();
	BFW::Vector<BFW_STRING_TYPE_A>& _AttributeValues = _Exclamation.GetAttributeValues();

	while (_CurrentPos < _FileContent.GetLength() - 1 && _FileContent[_CurrentPos] != '>')
	{
		BFW_STRING_TYPE_A _Attribute;

		if (_FileContent[_CurrentPos] == '\"')
		{
			if (!LoadXMLString(_FileContent, _CurrentPos, _Attribute))
			{
				return false;
			}

			_Attributes.PushBack(_Attribute);
			_AttributeValues.EmplaceBack("\"");

			continue;
		}

		if (_FileContent[_CurrentPos] == '[')
		{
			_CurrentPos++;

			BFW_CHAR_TYPE_A _Quotes = '\0';

			while (_CurrentPos < _FileContent.GetLength() - 1 && (_FileContent[_CurrentPos] != ']' || _Quotes != '\0'))
			{
				if (_Quotes == '\0')
				{
					if (_FileContent[_CurrentPos] == '\"' || _FileContent[_CurrentPos] == '\'')
					{
						_Quotes = _FileContent[_CurrentPos];
					}
				}
				else
				{
					if (_FileContent[_CurrentPos] == _Quotes)
					{
						_Quotes = '\0';
					}
				}

				_Attribute += _FileContent[_CurrentPos];
				_CurrentPos++;
			}

			if (_CurrentPos == _FileContent.GetLength() - 1)
			{
				return false;
			}

			_CurrentPos++;

			while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
			{
				_CurrentPos++;
			}

			_Attributes.PushBack(_Attribute);
			_AttributeValues.EmplaceBack("[");

			continue;
		}

		while (_CurrentPos < _FileContent.GetLength() - 1 && !std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])) && _FileContent[_CurrentPos] != '>' && _FileContent[_CurrentPos] != '=')
		{
			_Attribute += _FileContent[_CurrentPos];
			_CurrentPos++;
		}

		if (_CurrentPos == _FileContent.GetLength() - 1 || !IsValidXMLToken(_Attribute))
		{
			return false;
		}

		while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
		{
			_CurrentPos++;
		}

		_Attributes.PushBack(_Attribute);

		if (_FileContent[_CurrentPos] != '=')
		{
			_AttributeValues.EmplaceBack("");
			continue;
		}

		_CurrentPos++;

		while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
		{
			_CurrentPos++;
		}

		BFW_STRING_TYPE_A _AttributeValue;

		if (!LoadXMLString(_FileContent, _CurrentPos, _AttributeValue))
		{
			return false;
		}

		_AttributeValues.PushBack(_AttributeValue);
	}

	if (_CurrentPos == _FileContent.GetLength() - 1)
	{
		return false;
	}

	_CurrentPos++;

	while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
	{
		_CurrentPos++;
	}

	return true;
}

static const bool LoadXMLQuestion(const BFW::Assets::FileContent& _FileContent, size_t& _CurrentPos, BFW::Vector<BFW::Assets::XMLNode>& _QuestionMarks)
{
	if (_FileContent[_CurrentPos] != '<' || _FileContent[_CurrentPos + 1] != '?')
	{
		return false;
	}

	_CurrentPos += 2;

	while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
	{
		_CurrentPos++;
	}

	BFW_STRING_TYPE_A _Tag;

	while (_CurrentPos + 1 < _FileContent.GetLength() - 1 && !std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])) && (_FileContent[_CurrentPos] != '?' || _FileContent[_CurrentPos + 1] != '>'))
	{
		_Tag += _FileContent[_CurrentPos];
		_CurrentPos++;
	}

	if (_CurrentPos + 1 == _FileContent.GetLength() - 1 || _Tag != "xml")
	{
		return false;
	}

	while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
	{
		_CurrentPos++;
	}

	BFW::Assets::XMLNode& _Question = _QuestionMarks.EmplaceBack(BFW::Assets::XMLNode());

	_Question.SetTag(_Tag);

	BFW::Vector<BFW_STRING_TYPE_A>& _Attributes = _Question.GetAttributes();
	BFW::Vector<BFW_STRING_TYPE_A>& _AttributeValues = _Question.GetAttributeValues();

	while (_CurrentPos + 1 < _FileContent.GetLength() - 1 && (_FileContent[_CurrentPos] != '?' || _FileContent[_CurrentPos + 1] != '>'))
	{
		BFW_STRING_TYPE_A _Attribute;

		while (_CurrentPos + 1 < _FileContent.GetLength() - 1 && !std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])) && (_FileContent[_CurrentPos] != '?' || _FileContent[_CurrentPos + 1] != '>') && _FileContent[_CurrentPos] != '=')
		{
			_Attribute += _FileContent[_CurrentPos];
			_CurrentPos++;
		}

		if (_CurrentPos + 1 == _FileContent.GetLength() - 1 || !IsValidXMLToken(_Attribute))
		{
			return false;
		}

		while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
		{
			_CurrentPos++;
		}

		_Attributes.PushBack(_Attribute);

		if (_FileContent[_CurrentPos] != '=')
		{
			_AttributeValues.EmplaceBack("");
			continue;
		}

		_CurrentPos++;

		while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
		{
			_CurrentPos++;
		}

		BFW_STRING_TYPE_A _AttributeValue;

		if (!LoadXMLString(_FileContent, _CurrentPos, _AttributeValue))
		{
			return false;
		}

		_AttributeValues.PushBack(_AttributeValue);
	}

	if (_CurrentPos + 1 == _FileContent.GetLength() - 1)
	{
		return false;
	}

	_CurrentPos += 2;

	while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
	{
		_CurrentPos++;
	}

	return true;
}

static const bool LoadXMLHeader(const BFW::Assets::FileContent& _FileContent, size_t& _CurrentPos, BFW::Vector<BFW::Assets::XMLNode>& _ExclamationMarks, BFW::Vector<BFW::Assets::XMLNode>& _QuestionMarks)
{
	bool _FoundXMLExclamation = false;
	bool _FoundXMLQuestion = false;

	while (_FileContent[_CurrentPos] == '<' && (_FileContent[_CurrentPos + 1] == '!' || _FileContent[_CurrentPos + 1] == '?'))
	{
		if (_FileContent[_CurrentPos + 1] == '!' && _FileContent[_CurrentPos + 2] == '-' && _FileContent[_CurrentPos + 3] == '-')
		{
			if (!LoadXMLComment(_FileContent, _CurrentPos))
			{
				return false;
			}

			continue;
		}

		if (_FileContent[_CurrentPos + 1] == '!')
		{
			if (!LoadXMLExclamation(_FileContent, _CurrentPos, _ExclamationMarks))
			{
				return false;
			}

			_FoundXMLExclamation = true;

			continue;
		}

		if (_FoundXMLExclamation || _FoundXMLQuestion || !LoadXMLQuestion(_FileContent, _CurrentPos, _QuestionMarks))
		{
			return false;
		}

		_FoundXMLQuestion = true;
	}

	return true;
}

static const bool LoadXMLNode(const BFW::Assets::FileContent& _FileContent, size_t& _CurrentPos, BFW::Assets::XMLNode& _Node)
{
	while (_FileContent[_CurrentPos] == '<' && _FileContent[_CurrentPos + 1] == '!' && _FileContent[_CurrentPos + 2] == '-' && _FileContent[_CurrentPos + 3] == '-')
	{
		if (!LoadXMLComment(_FileContent, _CurrentPos))
		{
			return false;
		}
	}

	bool _LeftClosed = false;
	bool _RightClosed = false;

	if (!LoadXMLEntry(_FileContent, _CurrentPos, _Node, _LeftClosed, _RightClosed))
	{
		return false;
	}

	if (_LeftClosed)
	{
		return false;
	}

	if (_RightClosed ||
		_Node.GetTag() == "area" ||
		_Node.GetTag() == "base" ||
		_Node.GetTag() == "br" ||
		_Node.GetTag() == "col" ||
		_Node.GetTag() == "embed" ||
		_Node.GetTag() == "hr" ||
		_Node.GetTag() == "img" ||
		_Node.GetTag() == "input" ||
		_Node.GetTag() == "link" ||
		_Node.GetTag() == "meta" ||
		_Node.GetTag() == "source" ||
		_Node.GetTag() == "track" ||
		_Node.GetTag() == "wbr")
	{
		return true;
	}

	if (_Node.GetTag() == "script")
	{
		_Node.GetChildren().EmplaceBack(BFW::Assets::XMLNode());
		_Node.GetChildren()[0].SetText("");

		while (_CurrentPos < _FileContent.GetLength() - 1)
		{
			size_t _OldCurrentPos = _CurrentPos;
			BFW::Assets::XMLNode _CurrentEntry;

			if (LoadXMLEntry(_FileContent, _CurrentPos, _CurrentEntry, _LeftClosed, _RightClosed) && _LeftClosed && !_RightClosed && _CurrentEntry.GetTag() == "script")
			{
				if (_Node.GetChildren()[0].GetText() == "")
				{
					_Node.GetChildren().Erase(0);
				}

				return true;
			}

			_CurrentPos = _OldCurrentPos;

			if (_FileContent[_CurrentPos] == '<')
			{
				_Node.GetChildren()[0].SetText(_Node.GetChildren()[0].GetText() + "<");
				_CurrentPos++;
			}

			if (!LoadXMLText(_FileContent, _CurrentPos, _CurrentEntry))
			{
				return false;
			}

			_Node.GetChildren()[0].SetText(_Node.GetChildren()[0].GetText() + _CurrentEntry.GetText());
		}

		return false;
	}

	while (_CurrentPos < _FileContent.GetLength() - 1)
	{
		BFW::Assets::XMLNode _CurrentEntry;

		if (_FileContent[_CurrentPos] == '<' && _FileContent[_CurrentPos + 1] == '/')
		{
			if (!LoadXMLEntry(_FileContent, _CurrentPos, _CurrentEntry, _LeftClosed, _RightClosed))
			{
				return false;
			}

			if (_RightClosed || !_LeftClosed || _CurrentEntry.GetTag() != _Node.GetTag())
			{
				return false;
			}

			return true;
		}

		if (_FileContent[_CurrentPos] == '<' && _FileContent[_CurrentPos + 1] == '!' && _FileContent[_CurrentPos + 2] == '-' && _FileContent[_CurrentPos + 3] == '-')
		{
			if (!LoadXMLComment(_FileContent, _CurrentPos))
			{
				return false;
			}

			continue;
		}

		if (_FileContent[_CurrentPos] != '<')
		{
			if (!LoadXMLText(_FileContent, _CurrentPos, _CurrentEntry))
			{
				return false;
			}

			_Node.GetChildren().PushBack(_CurrentEntry);

			continue;
		}

		if (!LoadXMLNode(_FileContent, _CurrentPos, _CurrentEntry))
		{
			return false;
		}

		_Node.GetChildren().PushBack(_CurrentEntry);
	}

	return false;
}

static const bool SaveXMLString(BFW_STRING_STREAM_TYPE_A& _Stream, const BFW_STRING_VIEW_TYPE_A& _String)
{
	_Stream << '\"';

	for (size_t _Index = 0; _Index < _String.size(); _Index++)
	{
		if ((const unsigned BFW_CHAR_TYPE_A)(_String[_Index]) <= 0x08 || ((const unsigned BFW_CHAR_TYPE_A)(_String[_Index]) >= 0x0B && (const unsigned BFW_CHAR_TYPE_A)(_String[_Index]) <= 0x1F))
		{
			return false;
		}

		if (_String[_Index] == '&')
		{
			_Stream << "&amp;";
			continue;
		}

		if (_String[_Index] == '<')
		{
			_Stream << "&lt;";
			continue;
		}

		if (_String[_Index] == '>')
		{
			_Stream << "&gt;";
			continue;
		}

		if (_String[_Index] == '\"')
		{
			_Stream << "&quot;";
			continue;
		}

		if (_String[_Index] == '\'')
		{
			_Stream << "&amp;";
			continue;
		}

		_Stream << _String[_Index];
	}

	_Stream << '\"';

	return true;
}

static const bool SaveXMLText(BFW_STRING_STREAM_TYPE_A& _Stream, const BFW_STRING_VIEW_TYPE_A& _String)
{
	if (_String.size() == 0)
	{
		return false;
	}

	size_t _End = 0;

	while (_End < _String.size() && std::isspace((const unsigned BFW_CHAR_TYPE_A)(_String[_String.size() - 1 - _End])))
	{
		_End++;
	}

	for (size_t _Index = 0; _Index < _String.size() - _End; _Index++)
	{
		if ((const unsigned BFW_CHAR_TYPE_A)(_String[_Index]) <= 0x08 || ((const unsigned BFW_CHAR_TYPE_A)(_String[_Index]) >= 0x0B && (const unsigned BFW_CHAR_TYPE_A)(_String[_Index]) <= 0x1F))
		{
			return false;
		}

		if (_String[_Index] == '&')
		{
			_Stream << "&amp;";
			continue;
		}

		if (_String[_Index] == '<')
		{
			_Stream << "&lt;";
			continue;
		}

		if (_String[_Index] == '>')
		{
			_Stream << "&gt;";
			continue;
		}

		_Stream << _String[_Index];
	}

	if (_End == 0)
	{
		return true;
	}

	if (!IsValidXMLCDATA(_String.substr(_String.size() - _End, _End)))
	{
		return false;
	}

	_Stream << "<![CDATA[";

	for (size_t _Index = _String.size() - _End; _Index < _String.size(); _Index++)
	{
		if ((const unsigned BFW_CHAR_TYPE_A)(_String[_Index]) <= 0x08 || ((const unsigned BFW_CHAR_TYPE_A)(_String[_Index]) >= 0x0B && (const unsigned BFW_CHAR_TYPE_A)(_String[_Index]) <= 0x1F))
		{
			return false;
		}

		_Stream << _String[_Index];
	}

	_Stream << "]]>";

	return true;
}

static const bool SaveXMLHeader(BFW_STRING_STREAM_TYPE_A& _Stream, const BFW::Vector<BFW::Assets::XMLNode>& _ExclamationMarks, const BFW::Vector<BFW::Assets::XMLNode>& _QuestionMarks)
{
	if (_QuestionMarks.GetSize() > 1 || (_QuestionMarks.GetSize() == 1 && (_QuestionMarks[0].GetType() != BFW::Assets::_NodeXMLNodeType || _QuestionMarks[0].GetChildren().GetSize() != 0 || _QuestionMarks[0].GetTag() != "xml" || _QuestionMarks[0].GetAttributes().GetSize() != _QuestionMarks[0].GetAttributeValues().GetSize())))
	{
		return false;
	}

	if (_QuestionMarks.GetSize())
	{
		_Stream << "<?" << _QuestionMarks[0].GetTag();

		for (size_t _Index = 0; _Index < _QuestionMarks[0].GetAttributes().GetSize(); _Index++)
		{
			if (!IsValidXMLToken(_QuestionMarks[0].GetAttributes()[_Index]))
			{
				return false;
			}

			_Stream << ' ' << _QuestionMarks[0].GetAttributes()[_Index] << "=";

			if (!SaveXMLString(_Stream, _QuestionMarks[0].GetAttributeValues()[_Index]))
			{
				return false;
			}
		}

		_Stream << "?>" BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
	}

	for (size_t _ExclamationIndex = 0; _ExclamationIndex < _ExclamationMarks.GetSize(); _ExclamationIndex++)
	{
		const BFW::Assets::XMLNode& _Exclamation = _ExclamationMarks[_ExclamationIndex];

		if (_Exclamation.GetType() != BFW::Assets::_NodeXMLNodeType || _Exclamation.GetChildren().GetSize() != 0 || _Exclamation.GetTag() != "DOCTYPE" || _Exclamation.GetAttributes().GetSize() != _Exclamation.GetAttributeValues().GetSize())
		{
			return false;
		}

		_Stream << "<!" << _Exclamation.GetTag();

		for (size_t _Index = 0; _Index < _Exclamation.GetAttributes().GetSize(); _Index++)
		{
			if (_Exclamation.GetAttributeValues()[_Index] == "")
			{
				if (!IsValidXMLToken(_Exclamation.GetAttributes()[_Index]))
				{
					return false;
				}

				_Stream << ' ' << _Exclamation.GetAttributes()[_Index];

				continue;
			}

			if (_Exclamation.GetAttributeValues()[_Index] == "\"")
			{
				_Stream << ' ';

				if (!SaveXMLString(_Stream, _Exclamation.GetAttributes()[_Index]))
				{
					return false;
				}

				continue;
			}

			if (_Exclamation.GetAttributeValues()[_Index] == "[")
			{
				BFW_CHAR_TYPE_A _Quotes = '\0';
				size_t _Open = 0;

				for (size_t _CharIndex = 0; _CharIndex < _Exclamation.GetAttributes()[_Index].size(); _CharIndex++)
				{
					const BFW_CHAR_TYPE_A& _Char = _Exclamation.GetAttributes()[_Index][_CharIndex];

					if (_Quotes == '\0')
					{
						if (_Char == '\'' || _Char == '\"')
						{
							_Quotes = _Char;
						}

						if (_Char == '[')
						{
							_Open++;
						}

						if (_Char == ']')
						{
							if (_Open)
							{
								_Open--;
							}
							else
							{
								return false;
							}
						}
					}
					else
					{
						if (_Quotes == _Char)
						{
							_Quotes = '\0';
						}
					}
				}

				if (_Quotes != '\0' || _Open)
				{
					return false;
				}

				_Stream << " [" << _Exclamation.GetAttributes()[_Index] << ']';

				continue;
			}

			if (!IsValidXMLToken(_Exclamation.GetAttributes()[_Index]))
			{
				return false;
			}

			_Stream << ' ' << _Exclamation.GetAttributes()[_Index] << "=";

			if (!SaveXMLString(_Stream, _Exclamation.GetAttributeValues()[_Index]))
			{
				return false;
			}
		}

		_Stream << '>' BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
	}

	return true;
}

static const bool SaveXMLNode(size_t& _TabLevel, BFW_STRING_STREAM_TYPE_A& _Stream, const BFW::Assets::XMLNode& _Node)
{
	if (_Node.GetAttributes().GetSize() != _Node.GetAttributeValues().GetSize() || !IsValidXMLToken(_Node.GetTag()))
	{
		return false;
	}

	if (_Node.GetChildren().GetSize() == 0)
	{
		for (size_t _Index = 0; _Index < _TabLevel; _Index++)
		{
			_Stream << '\t';
		}

		_Stream << '<' << _Node.GetTag();

		for (size_t _Index = 0; _Index < _Node.GetAttributes().GetSize(); _Index++)
		{
			if (!IsValidXMLToken(_Node.GetAttributes()[_Index]))
			{
				return false;
			}

			_Stream << ' ' << _Node.GetAttributes()[_Index] << "=";

			if (!SaveXMLString(_Stream, _Node.GetAttributeValues()[_Index]))
			{
				return false;
			}
		}

		_Stream << "/>" BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';

		return true;
	}

	for (size_t _Index = 0; _Index < _TabLevel; _Index++)
	{
		_Stream << '\t';
	}

	_Stream << '<' << _Node.GetTag();

	for (size_t _Index = 0; _Index < _Node.GetAttributes().GetSize(); _Index++)
	{
		if (!IsValidXMLToken(_Node.GetAttributes()[_Index]))
		{
			return false;
		}

		_Stream << ' ' << _Node.GetAttributes()[_Index] << "=";

		if (!SaveXMLString(_Stream, _Node.GetAttributeValues()[_Index]))
		{
			return false;
		}
	}

	_Stream << '>' BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';

	_TabLevel++;

	for (size_t _ChildIndex = 0; _ChildIndex < _Node.GetChildren().GetSize(); _ChildIndex++)
	{
		if (_Node.GetChildren()[_ChildIndex].GetType() == BFW::Assets::_TextXMLNodeType)
		{
			for (size_t _Index = 0; _Index < _TabLevel; _Index++)
			{
				_Stream << '\t';
			}

			if (!SaveXMLText(_Stream, _Node.GetChildren()[_ChildIndex].GetText()))
			{
				return false;
			}

			_Stream BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';

			continue;
		}

		if (!SaveXMLNode(_TabLevel, _Stream, _Node.GetChildren()[_ChildIndex]))
		{
			return false;
		}
	}

	_TabLevel--;

	for (size_t _Index = 0; _Index < _TabLevel; _Index++)
	{
		_Stream << '\t';
	}

	_Stream << "</" << _Node.GetTag() << '>' BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';

	return true;
}

static const bool LoadJsonNull(const BFW::Assets::FileContent& _FileContent, size_t& _CurrentPos, BFW::Assets::Json& _Json)
{
	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != 'n')
	{
		return false;
	}

	_CurrentPos++;

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != 'u')
	{
		return false;
	}

	_CurrentPos++;

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != 'l')
	{
		return false;
	}

	_CurrentPos++;

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != 'l')
	{
		return false;
	}

	_CurrentPos++;

	_Json.SetNull();

	return true;
}

static const bool LoadJsonBool(const BFW::Assets::FileContent& _FileContent, size_t& _CurrentPos, BFW::Assets::Json& _Json)
{
	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != 't' && (const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != 'f')
	{
		return false;
	}

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == 't')
	{
		_CurrentPos++;

		if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != 'r')
		{
			return false;
		}

		_CurrentPos++;

		if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != 'u')
		{
			return false;
		}

		_CurrentPos++;

		if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != 'e')
		{
			return false;
		}

		_CurrentPos++;

		_Json.SetBool(true);

		return true;
	}

	_CurrentPos++;

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != 'a')
	{
		return false;
	}

	_CurrentPos++;

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != 'l')
	{
		return false;
	}

	_CurrentPos++;

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != 's')
	{
		return false;
	}

	_CurrentPos++;

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != 'e')
	{
		return false;
	}

	_CurrentPos++;

	_Json.SetBool(false);

	return true;
}

static const bool LoadJsonNumber(const BFW::Assets::FileContent& _FileContent, size_t& _CurrentPos, BFW::Assets::Json& _Json)
{
	bool _Negative = false;

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == '-')
	{
		_Negative = true;
		_CurrentPos++;
	}
	else if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == '+')
	{
		_CurrentPos++;
	}

	if (BFW_STRING_TYPE_A("e.0123456789").find((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])) == BFW_STRING_TYPE_A::npos || (const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == '\0')
	{
		return false;
	}

	float _Number = 0.0f;

	bool _FoundDot = false;
	float _NumberExponent = 1.0f;

	while (BFW_STRING_TYPE_A(".0123456789").find((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])) != BFW_STRING_TYPE_A::npos && (const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != '\0')
	{
		if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == '.')
		{
			if (_FoundDot)
			{
				return false;
			}

			_FoundDot = true;

			_CurrentPos++;
			continue;
		}

		if (_FoundDot)
		{
			_NumberExponent /= 10.0f;
			_Number += _NumberExponent * ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) - '0');

			_CurrentPos++;
			continue;
		}

		_Number *= 10;
		_Number += (const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) - '0';

		_CurrentPos++;
	}

	float _Exponent = 0.0f;

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == 'e')
	{
		_CurrentPos++;

		bool _NegativeExponent = false;

		if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == '-')
		{
			_NegativeExponent = true;
			_CurrentPos++;
		}
		else if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == '+')
		{
			_CurrentPos++;
		}

		bool _FoundExponentDot = false;
		float _ExponentExponent = 1.0f;

		while (BFW_STRING_TYPE_A(".0123456789").find((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])) != BFW_STRING_TYPE_A::npos && (const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != '\0')
		{
			if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == '.')
			{
				if (_FoundExponentDot)
				{
					return false;
				}

				_FoundExponentDot = true;

				_CurrentPos++;
				continue;
			}

			if (_FoundExponentDot)
			{
				_ExponentExponent /= 10.0f;
				_Exponent += _ExponentExponent * ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) - '0');

				_CurrentPos++;
				continue;
			}

			_Exponent *= 10;
			_Exponent += (const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) - '0';

			_CurrentPos++;
		}

		if (_NegativeExponent)
		{
			_Exponent = -_Exponent;
		}
	}

	if (_Negative)
	{
		_Json.SetNumber(-_Number * powf(10.0f, _Exponent));
	}
	else
	{
		_Json.SetNumber(_Number * powf(10.0f, _Exponent));
	}

	return true;
}

static const bool LoadJsonString(const BFW::Assets::FileContent& _FileContent, size_t& _CurrentPos, BFW::Assets::Json& _Json)
{
	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != '\"')
	{
		return false;
	}

	_CurrentPos++;

	BFW_STRING_TYPE_A _String;

	BFW_WINDOWS_PLATFORM_CALL(_String.reserve(64));
	BFW_LINUX_PLATFORM_CALL(_String.reserve(64));

	while ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != '\"')
	{
		if (BFW::String::IsControlCharacter((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
		{
			return false;
		}

		if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == '\\')
		{
			_CurrentPos++;

			switch ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]))
			{
			case '\"':
			{
				_String += '\"';
				break;
			}
			case '\\':
			{
				_String += '\\';
				break;
			}
			case '/':
			{
				_String += '/';
				break;
			}
			case 'b':
			{
				_String += '\b';
				break;
			}
			case 'f':
			{
				_String += '\f';
				break;
			}
			case 'n':
			{
				_String += '\n';
				break;
			}
			case 'r':
			{
				_String += '\r';
				break;
			}
			case 't':
			{
				_String += '\t';
				break;
			}
			case 'u':
			{
				BFW_CHAR_TYPE_W _WChar = L'\0';

				for (size_t _Index = 0; _Index < 4; _Index++)
				{
					_CurrentPos++;

					if (!BFW::String::IsHexA((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
					{
						return false;
					}

					_WChar = (_WChar << 4) + BFW::String::HexCharToNibbleA((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]));
				}

				if (BFW::String::IsUnicodeSurrogated(_WChar))
				{
					_CurrentPos++;

					if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != '\\')
					{
						return false;
					}

					_CurrentPos++;

					if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != 'u')
					{
						return false;
					}

					BFW_CHAR_TYPE_W _WChar2 = L'\0';

					for (size_t _Index = 0; _Index < 4; _Index++)
					{
						_CurrentPos++;

						if (!BFW::String::IsHexA((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
						{
							return false;
						}

						_WChar2 = (_WChar2 << 4) + BFW::String::HexCharToNibbleA((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]));
					}

					if (!BFW::String::IsUnicodeSurrogatedContinuation(_WChar2))
					{
						return false;
					}

					uint32_t _CodePoint = BFW::String::CompositUnicodeSurrogates(_WChar, _WChar2);
					BFW::Vector<BFW_CHAR_TYPE_W> _Chars = BFW::String::DeconstructUnicodePointW(_CodePoint);

					BFW_STRING_TYPE_W _WString = L"";

					for (size_t _Index = 0; _Index < _Chars.GetSize(); _Index++)
					{
						_WString += _Chars[_Index];
					}

					if (!BFW::String::IsValidUnicodeString(_WString))
					{
						return false;
					}

					bool _Error = false;
					_String += BFW::String::FromUnicodeToUTF8(_WString, &_Error);

					if (_Error)
					{
						return false;
					}

					break;
				}

				BFW_STRING_TYPE_W _WString = L"";
				_WString += _WChar;

				if (!BFW::String::IsValidUnicodeString(_WString))
				{
					return false;
				}

				bool _Error = false;
				_String += BFW::String::FromUnicodeToUTF8(_WString, &_Error);

				if (_Error)
				{
					return false;
				}

				break;
			}
			default:
			{
				return false;
			}
			}

			_CurrentPos++;
			continue;
		}

		_String += (const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]);

		_CurrentPos++;
	}

	_CurrentPos++;

	if (!BFW::String::IsValidUTF8String(_String))
	{
		return false;
	}

	_Json.SetString(_String);

	return true;
}

static const bool LoadJsonArray(const BFW::Assets::FileContent& _FileContent, size_t& _CurrentPos, BFW::Assets::Json& _Json);

static const bool LoadJsonObject(const BFW::Assets::FileContent& _FileContent, size_t& _CurrentPos, BFW::Assets::Json& _Json)
{
	_Json.SetObject();

	BFW::Assets::JsonObjectData& _ObjectData = _Json.GetObjectData();

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != '{')
	{
		return false;
	}

	_CurrentPos++;

	while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
	{
		_CurrentPos++;
	}

	while ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != '}')
	{
		BFW::Assets::Json _Tag;

		if (!LoadJsonString(_FileContent, _CurrentPos, _Tag) || _Tag.GetString().size() == 0)
		{
			return false;
		}

		BFW::Assets::Json& _TagObject = _ObjectData.Object.PushBack(BFW::Assets::Json());
		_ObjectData.Tags.PushBack(_Tag.GetString());

		while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
		{
			_CurrentPos++;
		}

		if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != ':')
		{
			return false;
		}

		_CurrentPos++;

		while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
		{
			_CurrentPos++;
		}

		switch ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]))
		{
		case 'n':
		{
			if (!LoadJsonNull(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case 't':
		{
			if (!LoadJsonBool(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case 'f':
		{
			if (!LoadJsonBool(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case '.':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case '0':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case '1':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case '2':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case '3':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case '4':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case '5':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case '6':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case '7':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case '8':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case '9':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case '\"':
		{
			if (!LoadJsonString(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case '{':
		{
			if (!LoadJsonObject(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		case '[':
		{
			if (!LoadJsonArray(_FileContent, _CurrentPos, _TagObject))
			{
				return false;
			}

			break;
		}
		default:
		{
			return false;
		}
		}

		while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
		{
			_CurrentPos++;
		}

		if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != ',' && (const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != '}')
		{
			return false;
		}

		if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == ',')
		{
			_CurrentPos++;

			while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
			{
				_CurrentPos++;
			}

			if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == '}')
			{
				return false;
			}

			continue;
		}
	}

	_CurrentPos++;

	return true;
}

static const bool LoadJsonArray(const BFW::Assets::FileContent& _FileContent, size_t& _CurrentPos, BFW::Assets::Json& _Json)
{
	_Json.SetArray();

	BFW::Vector<BFW::Assets::Json>& _Array = _Json.GetArray();

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != '[')
	{
		return false;
	}

	_CurrentPos++;

	while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
	{
		_CurrentPos++;
	}

	while ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != ']')
	{
		BFW::Assets::Json& _Object = _Array.EmplaceBack(BFW::Assets::Json());

		switch ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]))
		{
		case 'n':
		{
			if (!LoadJsonNull(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case 't':
		{
			if (!LoadJsonBool(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case 'f':
		{
			if (!LoadJsonBool(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case '.':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case '0':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case '1':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case '2':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case '3':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case '4':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case '5':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case '6':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case '7':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case '8':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case '9':
		{
			if (!LoadJsonNumber(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case '\"':
		{
			if (!LoadJsonString(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case '{':
		{
			if (!LoadJsonObject(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		case '[':
		{
			if (!LoadJsonArray(_FileContent, _CurrentPos, _Object))
			{
				return false;
			}

			break;
		}
		default:
		{
			return false;
		}
		}

		while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
		{
			_CurrentPos++;
		}

		if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != ',' && (const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != ']')
		{
			return false;
		}

		if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == ',')
		{
			_CurrentPos++;

			while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
			{
				_CurrentPos++;
			}

			if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == ']')
			{
				return false;
			}

			continue;
		}
	}

	_CurrentPos++;

	return true;
}

static void SaveJsonNull(size_t& _TabLevel, BFW_STRING_STREAM_TYPE_A& _Stream, const BFW::Assets::Json& _Json)
{
	_Stream << "null";
}

static void SaveJsonBool(size_t& _TabLevel, BFW_STRING_STREAM_TYPE_A& _Stream, const BFW::Assets::Json& _Json)
{
	if (_Json.GetBool())
	{
		_Stream << "true";
	}
	else
	{
		_Stream << "false";
	}
}

static void SaveJsonNumber(size_t& _TabLevel, BFW_STRING_STREAM_TYPE_A& _Stream, const BFW::Assets::Json& _Json)
{
	if (std::isnan(_Json.GetNumber()))
	{
		_Stream << 0.0f;
		return;
	}

	if (!std::isfinite(_Json.GetNumber()) && _Json.GetNumber() < 0.0f)
	{
		_Stream << std::numeric_limits<float>::max();
		return;
	}

	if (!std::isfinite(_Json.GetNumber()) && _Json.GetNumber() > 0.0f)
	{
		_Stream << std::numeric_limits<float>::min();
		return;
	}

	_Stream << _Json.GetNumber();
}

static const bool SaveJsonString(size_t& _TabLevel, BFW_STRING_STREAM_TYPE_A& _Stream, const BFW::Assets::Json& _Json)
{
	_Stream << '\"';

	BFW_STRING_TYPE_A _String = _Json.GetString();

	if (!BFW::String::IsValidUTF8String(_String))
	{
		return false;
	}

	for (size_t _Index = 0; _Index < _String.size(); _Index++)
	{
		if (_String[_Index] == '\"')
		{
			_Stream << '\\' << '\"';
			continue;
		}

		if (_String[_Index] == '\\')
		{
			_Stream << '\\' << '\\';
			continue;
		}

		if (_String[_Index] == '\b')
		{
			_Stream << '\\' << 'b';
			continue;
		}

		if (_String[_Index] == '\f')
		{
			_Stream << '\\' << 'f';
			continue;
		}

		if (_String[_Index] == '\n')
		{
			_Stream << '\\' << 'n';
			continue;
		}

		if (_String[_Index] == '\r')
		{
			_Stream << '\\' << 'r';
			continue;
		}

		if (_String[_Index] == '\t')
		{
			_Stream << '\\' << 't';
			continue;
		}

		if (BFW::String::IsControlCharacter(_String[_Index]))
		{
			return false;
		}

		_Stream << _String[_Index];
	}

	_Stream << '\"';

	return true;
}

static const bool SaveJsonArray(size_t& _TabLevel, BFW_STRING_STREAM_TYPE_A& _Stream, const BFW::Assets::Json& _Json);

static const bool SaveJsonObject(size_t& _TabLevel, BFW_STRING_STREAM_TYPE_A& _Stream, const BFW::Assets::Json& _Json)
{
	_Stream << '{' BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';

	_TabLevel++;

	const BFW::Assets::JsonObjectData& _ObjectData = _Json.GetObjectData();

	for (size_t _Index = 0; _Index < _ObjectData.Tags.GetSize(); _Index++)
	{
		BFW::Assets::Json _Tag;

		_Tag.SetString(_ObjectData.Tags[_Index]);

		for (size_t _Index = 0; _Index < _TabLevel; _Index++)
		{
			_Stream << '\t';
		}

		if (!SaveJsonString(_TabLevel, _Stream, _Tag) || _Tag.GetString().size() == 0)
		{
			return false;
		}

		_Stream << ":";

		const BFW::Assets::Json& _CurrentJson = _ObjectData.Object[_Index];

		if (_CurrentJson.GetType() == BFW::Assets::_ObjectJsonType || _CurrentJson.GetType() == BFW::Assets::_ArrayJsonType)
		{
			_Stream BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';

			for (size_t _Index = 0; _Index < _TabLevel; _Index++)
			{
				_Stream << '\t';
			}
		}
		else
		{
			_Stream << ' ';
		}

		switch (_CurrentJson.GetType())
		{
		case BFW::Assets::_NullJsonType:
		{
			SaveJsonNull(_TabLevel, _Stream, _CurrentJson);
			break;
		}
		case BFW::Assets::_BoolJsonType:
		{
			SaveJsonBool(_TabLevel, _Stream, _CurrentJson);
			break;
		}
		case BFW::Assets::_NumberJsonType:
		{
			SaveJsonNumber(_TabLevel, _Stream, _CurrentJson);
			break;
		}
		case BFW::Assets::_StringJsonType:
		{
			if (!SaveJsonString(_TabLevel, _Stream, _CurrentJson))
			{
				return false;
			}

			break;
		}
		case BFW::Assets::_ObjectJsonType:
		{
			if (!SaveJsonObject(_TabLevel, _Stream, _CurrentJson))
			{
				return false;
			}

			break;
		}
		case BFW::Assets::_ArrayJsonType:
		{
			if (!SaveJsonArray(_TabLevel, _Stream, _CurrentJson))
			{
				return false;
			}

			break;
		}
		default:
		{
			break;
		}
		}

		if (_Index != _ObjectData.Tags.GetSize() - 1)
		{
			_Stream << ',';
		}

		_Stream BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
	}

	_TabLevel--;

	for (size_t _Index = 0; _Index < _TabLevel; _Index++)
	{
		_Stream << '\t';
	}

	_Stream << '}';

	return true;
}

static const bool SaveJsonArray(size_t& _TabLevel, BFW_STRING_STREAM_TYPE_A& _Stream, const BFW::Assets::Json& _Json)
{
	_Stream << '[' BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';

	_TabLevel++;

	const BFW::Vector<BFW::Assets::Json>& _Array = _Json.GetArray();

	for (size_t _Index = 0; _Index < _Array.GetSize(); _Index++)
	{
		for (size_t _Index = 0; _Index < _TabLevel; _Index++)
		{
			_Stream << '\t';
		}

		const BFW::Assets::Json& _CurrentJson = _Array[_Index];

		switch (_CurrentJson.GetType())
		{
		case BFW::Assets::_NullJsonType:
		{
			SaveJsonNull(_TabLevel, _Stream, _CurrentJson);
			break;
		}
		case BFW::Assets::_BoolJsonType:
		{
			SaveJsonBool(_TabLevel, _Stream, _CurrentJson);
			break;
		}
		case BFW::Assets::_NumberJsonType:
		{
			SaveJsonNumber(_TabLevel, _Stream, _CurrentJson);
			break;
		}
		case BFW::Assets::_StringJsonType:
		{
			if (!SaveJsonString(_TabLevel, _Stream, _CurrentJson))
			{
				return false;
			}

			break;
		}
		case BFW::Assets::_ObjectJsonType:
		{
			if (!SaveJsonObject(_TabLevel, _Stream, _CurrentJson))
			{
				return false;
			}

			break;
		}
		case BFW::Assets::_ArrayJsonType:
		{
			if (!SaveJsonArray(_TabLevel, _Stream, _CurrentJson))
			{
				return false;
			}

			break;
		}
		default:
		{
			break;
		}
		}

		if (_Index != _Array.GetSize() - 1)
		{
			_Stream << ',';
		}

		_Stream BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';
	}

	_TabLevel--;

	for (size_t _Index = 0; _Index < _TabLevel; _Index++)
	{
		_Stream << '\t';
	}

	_Stream << ']';

	return true;
}



BFW::Assets::JsonObjectData::JsonObjectData() : Object(), Tags()
{

}

BFW::Assets::JsonObjectData::JsonObjectData(const JsonObjectData& _Other) : Object(_Other.Object), Tags(_Other.Tags)
{

}

BFW::Assets::JsonObjectData::JsonObjectData(JsonObjectData&& _Other) noexcept : Object((Vector<Json>&&)(_Other.Object)), Tags((Vector<BFW_STRING_TYPE_A>&&)(_Other.Tags))
{

}

BFW::Assets::JsonObjectData::~JsonObjectData()
{

}

BFW::Assets::Json& BFW::Assets::JsonObjectData::operator[] (const BFW_CHAR_TYPE_A* _Tag)
{
	for (size_t _Index = 0; _Index < Tags.GetSize(); _Index++)
	{
		if (Tags[_Index] == _Tag)
		{
			return Object[_Index];
		}
	}

	throw nullptr;
}

const BFW::Assets::Json& BFW::Assets::JsonObjectData::operator[] (const BFW_CHAR_TYPE_A* _Tag) const
{
	for (size_t _Index = 0; _Index < Tags.GetSize(); _Index++)
	{
		if (Tags[_Index] == _Tag)
		{
			return Object[_Index];
		}
	}

	throw nullptr;
}

BFW::Assets::JsonObjectData& BFW::Assets::JsonObjectData::operator= (const JsonObjectData& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Object = _Other.Object;
	Tags = _Other.Tags;

	return *this;
}

BFW::Assets::JsonObjectData& BFW::Assets::JsonObjectData::operator= (JsonObjectData&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Object = (Vector<Json>&&)(_Other.Object);
	Tags = (Vector<BFW_STRING_TYPE_A>&&)(_Other.Tags);

	return *this;
}



BFW::Assets::XMLNode::XMLNode() : Type(_TextXMLNodeType), Tag(""), Attributes(), AttributeValues(), Children(), Text("Hello!")
{

}

BFW::Assets::XMLNode::XMLNode(const XMLNode& _Other) : Type(_Other.Type), Tag(_Other.Tag), Attributes(_Other.Attributes), AttributeValues(_Other.AttributeValues), Children(_Other.Children), Text(_Other.Text)
{

}

BFW::Assets::XMLNode::XMLNode(XMLNode&& _Other) noexcept : Type(_Other.Type), Tag(_Other.Tag), Attributes((Vector<BFW_STRING_TYPE_A>&&)(_Other.Attributes)), AttributeValues((Vector<BFW_STRING_TYPE_A>&&)(_Other.AttributeValues)), Children((Vector<XMLNode>&&)(_Other.Children)), Text(_Other.Text)
{
	_Other.Type = _TextXMLNodeType;
	_Other.Tag = "";
	_Other.Text = "Hello!";
}

BFW::Assets::XMLNode::~XMLNode()
{

}

void BFW::Assets::XMLNode::SetTag(const BFW_STRING_VIEW_TYPE_A& _Tag)
{
	Type = _NodeXMLNodeType;
	Tag = _Tag;
	Text = "Hello!";
}

void BFW::Assets::XMLNode::SetText(const BFW_STRING_VIEW_TYPE_A& _Text)
{
	Type = _TextXMLNodeType;
	Tag = "";
	Attributes = Vector<BFW_STRING_TYPE_A>();
	AttributeValues = Vector<BFW_STRING_TYPE_A>();
	Children = Vector<XMLNode>();
	Text = _Text;
}

const uint8_t BFW::Assets::XMLNode::GetType() const
{
	return Type;
}

const BFW_STRING_TYPE_A BFW::Assets::XMLNode::GetTag() const
{
	if (Type != _NodeXMLNodeType)
	{
		throw nullptr;
	}

	return Tag;
}

BFW::Vector<BFW_STRING_TYPE_A>& BFW::Assets::XMLNode::GetAttributes()
{
	if (Type != _NodeXMLNodeType)
	{
		throw nullptr;
	}

	return Attributes;
}

const BFW::Vector<BFW_STRING_TYPE_A>& BFW::Assets::XMLNode::GetAttributes() const
{
	if (Type != _NodeXMLNodeType)
	{
		throw nullptr;
	}

	return Attributes;
}

BFW::Vector<BFW_STRING_TYPE_A>& BFW::Assets::XMLNode::GetAttributeValues()
{
	if (Type != _NodeXMLNodeType)
	{
		throw nullptr;
	}

	return AttributeValues;
}

const BFW::Vector<BFW_STRING_TYPE_A>& BFW::Assets::XMLNode::GetAttributeValues() const
{
	if (Type != _NodeXMLNodeType)
	{
		throw nullptr;
	}

	return AttributeValues;
}

BFW::Vector<BFW::Assets::XMLNode>& BFW::Assets::XMLNode::GetChildren()
{
	if (Type != _NodeXMLNodeType)
	{
		throw nullptr;
	}

	return Children;
}

const BFW::Vector<BFW::Assets::XMLNode>& BFW::Assets::XMLNode::GetChildren() const
{
	if (Type != _NodeXMLNodeType)
	{
		throw nullptr;
	}

	return Children;
}

const BFW_STRING_TYPE_A& BFW::Assets::XMLNode::GetText() const
{
	if (Type != _TextXMLNodeType)
	{
		throw nullptr;
	}

	return Text;
}

BFW::Assets::XMLNode& BFW::Assets::XMLNode::operator= (const XMLNode& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Type = _Other.Type;
	Tag = _Other.Tag;
	Attributes = _Other.Attributes;
	AttributeValues = _Other.AttributeValues;
	Children = _Other.Children;
	Text = _Other.Text;

	return *this;
}

BFW::Assets::XMLNode& BFW::Assets::XMLNode::operator= (XMLNode&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Type = _Other.Type;
	Tag = _Other.Tag;
	Attributes = (Vector<BFW_STRING_TYPE_A>&&)(_Other.Attributes);
	AttributeValues = (Vector<BFW_STRING_TYPE_A>&&)(_Other.AttributeValues);
	Children = (Vector<XMLNode>&&)(_Other.Children);
	Text = _Other.Text;

	_Other.Type = _TextXMLNodeType;
	_Other.Tag = "";
	_Other.Text = "Hello!";

	return *this;
}



BFW::Assets::XML::XML() : ExclamationMarks(), QuestionMarks(), Root()
{

}

BFW::Assets::XML::XML(const XML& _Other) : ExclamationMarks(_Other.ExclamationMarks), QuestionMarks(_Other.QuestionMarks), Root(_Other.Root)
{

}

BFW::Assets::XML::XML(XML&& _Other) noexcept : ExclamationMarks((Vector<XMLNode>&&)(_Other.ExclamationMarks)), QuestionMarks((Vector<XMLNode>&&)(_Other.QuestionMarks)), Root((XMLNode&&)(_Other.Root))
{

}

BFW::Assets::XML::~XML()
{

}

const bool BFW::Assets::XML::Load(const FileContent& _FileContent)
{
	*this = XML();

	if (!_FileContent.GetData() || _FileContent[_FileContent.GetLength() - 1] != '\0' || !IsValidXMLFile(_FileContent))
	{
		return false;
	}

	size_t _CurrentPos = 0;

	while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
	{
		_CurrentPos++;
	}

	if (!LoadXMLHeader(_FileContent, _CurrentPos, ExclamationMarks, QuestionMarks))
	{
		*this = XML();
		return false;
	}

	if (!LoadXMLNode(_FileContent, _CurrentPos, Root))
	{
		*this = XML();
		return false;
	}

	if (!IsValid())
	{
		*this = XML();
		return false;
	}

	if (_CurrentPos != _FileContent.GetLength() - 1)
	{
		*this = XML();
		return false;
	}

	return true;
}

BFW::Assets::FileContent BFW::Assets::XML::Save() const
{
	if (Root.GetType() != _NodeXMLNodeType)
	{
		return FileContent();
	}

	if (!IsValid())
	{
		return FileContent();
	}

	size_t _TabLevel = 0;
	BFW_STRING_STREAM_TYPE_A _Stream;

	_Stream.imbue(std::locale::classic());

	if (!SaveXMLHeader(_Stream, ExclamationMarks, QuestionMarks))
	{
		return FileContent();
	}

	if (!SaveXMLNode(_TabLevel, _Stream, Root))
	{
		return FileContent();
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

const bool BFW::Assets::XML::IsValid() const
{
	if (QuestionMarks.GetSize() > 1 || (QuestionMarks.GetSize() == 1 && (QuestionMarks[0].GetType() != BFW::Assets::_NodeXMLNodeType || QuestionMarks[0].GetChildren().GetSize() != 0 || QuestionMarks[0].GetTag() != "xml" || QuestionMarks[0].GetAttributes().GetSize() != QuestionMarks[0].GetAttributeValues().GetSize())))
	{
		return false;
	}

	if (QuestionMarks.GetSize() == 1)
	{
		for (size_t _Index = 0; _Index < QuestionMarks[0].GetAttributes().GetSize(); _Index++)
		{
			if (!IsValidXMLToken(QuestionMarks[0].GetAttributes()[_Index]))
			{
				return false;
			}

			for (size_t _Index2 = 0; _Index2 < _Index; _Index2++)
			{
				if (QuestionMarks[0].GetAttributes()[_Index] == QuestionMarks[0].GetAttributes()[_Index2])
				{
					return false;
				}
			}

			for (size_t _CharIndex = 0; _CharIndex < QuestionMarks[0].GetAttributeValues()[_Index].size(); _CharIndex++)
			{
				const uint8_t _Char = QuestionMarks[0].GetAttributeValues()[_Index][_CharIndex];

				if (_Char <= 0x08 || (_Char >= 0x0B && _Char <= 0x1F))
				{
					return false;
				}
			}
		}
	}

	for (size_t _ExclamationIndex = 0; _ExclamationIndex < ExclamationMarks.GetSize(); _ExclamationIndex++)
	{
		const BFW::Assets::XMLNode& _Exclamation = ExclamationMarks[_ExclamationIndex];

		if (_Exclamation.GetType() != BFW::Assets::_NodeXMLNodeType || _Exclamation.GetChildren().GetSize() != 0 || _Exclamation.GetTag() != "DOCTYPE" || _Exclamation.GetAttributes().GetSize() != _Exclamation.GetAttributeValues().GetSize())
		{
			return false;
		}

		for (size_t _Index = 0; _Index < _Exclamation.GetAttributes().GetSize(); _Index++)
		{
			for (size_t _Index2 = 0; _Index2 < _Index; _Index2++)
			{
				if (_Exclamation.GetAttributes()[_Index] == _Exclamation.GetAttributes()[_Index2])
				{
					return false;
				}
			}

			if (_Exclamation.GetAttributeValues()[_Index] == "")
			{
				if (!IsValidXMLToken(_Exclamation.GetAttributes()[_Index]))
				{
					return false;
				}

				continue;
			}

			if (_Exclamation.GetAttributeValues()[_Index] == "\"")
			{
				for (size_t _CharIndex = 0; _CharIndex < _Exclamation.GetAttributes()[_Index].size(); _CharIndex++)
				{
					const uint8_t _Char = _Exclamation.GetAttributes()[_Index][_CharIndex];

					if (_Char <= 0x08 || (_Char >= 0x0B && _Char <= 0x1F))
					{
						return false;
					}
				}

				continue;
			}

			if (_Exclamation.GetAttributeValues()[_Index] == "[")
			{
				BFW_CHAR_TYPE_A _Quotes = '\0';
				size_t _Open = 0;

				for (size_t _CharIndex = 0; _CharIndex < _Exclamation.GetAttributes()[_Index].size(); _CharIndex++)
				{
					const BFW_CHAR_TYPE_A& _Char = _Exclamation.GetAttributes()[_Index][_CharIndex];

					if (_Quotes == '\0')
					{
						if (_Char == '\'' || _Char == '\"')
						{
							_Quotes = _Char;
						}

						if (_Char == '[')
						{
							_Open++;
						}

						if (_Char == ']')
						{
							if (_Open)
							{
								_Open--;
							}
							else
							{
								return false;
							}
						}
					}
					else
					{
						if (_Quotes == _Char)
						{
							_Quotes = '\0';
						}
					}
				}

				if (_Quotes != '\0' || _Open)
				{
					return false;
				}

				continue;
			}

			if (!IsValidXMLToken(_Exclamation.GetAttributes()[_Index]))
			{
				return false;
			}

			for (size_t _CharIndex = 0; _CharIndex < _Exclamation.GetAttributeValues()[_Index].size(); _CharIndex++)
			{
				const uint8_t _Char = _Exclamation.GetAttributeValues()[_Index][_CharIndex];

				if (_Char <= 0x08 || (_Char >= 0x0B && _Char <= 0x1F))
				{
					return false;
				}
			}
		}
	}

	Vector<const XMLNode*> _Queue;
	_Queue.PushBack(&Root);

	while (_Queue.GetSize())
	{
		const XMLNode* _Current = _Queue[0];
		_Queue.Erase(0);

		if (_Current->GetType() == _TextXMLNodeType)
		{
			const BFW_STRING_TYPE_A& _Text = _Current->GetText();

			if (!_Text.size())
			{
				return false;
			}

			for (size_t _Index = 0; _Index < _Text.size(); _Index++)
			{
				const uint8_t _Char = _Text[_Index];

				if (_Char <= 0x08 || (_Char >= 0x0B && _Char <= 0x1F))
				{
					return false;
				}
			}

			size_t _End = 0;

			while (_End < _Text.size() && std::isspace((const unsigned BFW_CHAR_TYPE_A)(_Text[_Text.size() - 1 - _End])))
			{
				_End++;
			}

			if (_End == 0)
			{
				continue;
			}

			if (!IsValidXMLCDATA(_Text.substr(_Text.size() - _End, _End)))
			{
				return false;
			}

			continue;
		}

		if (!IsValidXMLToken(_Current->GetTag()))
		{
			return false;
		}

		const Vector<BFW_STRING_TYPE_A>& _Attributes = _Current->GetAttributes();
		const Vector<BFW_STRING_TYPE_A>& _AttributeValues = _Current->GetAttributeValues();

		if (_Attributes.GetSize() != _AttributeValues.GetSize())
		{
			return false;
		}

		for (size_t _Index = 0; _Index < _Attributes.GetSize(); _Index++)
		{
			if (!IsValidXMLToken(_Attributes[_Index]))
			{
				return false;
			}

			for (size_t _Index2 = 0; _Index2 < _Index; _Index2++)
			{
				if (_Attributes[_Index] == _Attributes[_Index2])
				{
					return false;
				}
			}

			for (size_t _CharIndex = 0; _CharIndex < _AttributeValues[_Index].size(); _CharIndex++)
			{
				const uint8_t _Char = _AttributeValues[_Index][_CharIndex];

				if (_Char <= 0x08 || (_Char >= 0x0B && _Char <= 0x1F))
				{
					return false;
				}
			}
		}

		const Vector<XMLNode>& _Children = _Current->GetChildren();

		for (size_t _Index = 0; _Index < _Children.GetSize(); _Index++)
		{
			_Queue.PushBack(&_Children[_Index]);
		}
	}

	Vector<BFW_STRING_TYPE_A> _Namespaces;

	return ValidateXMLNamespaces(Root, _Namespaces);
}

const bool BFW::Assets::XML::ResolveNamespace(const XMLNode& _Node, BFW_STRING_TYPE_A& _TagNamespace, Vector<BFW_STRING_TYPE_A>& _AttributesNamespaces) const
{
	_TagNamespace = "http://www.w3.org/2000/xmlns/";
	_AttributesNamespaces.Clear();

	if (!IsValid() || _Node.GetType() != _NodeXMLNodeType)
	{
		return false;
	}

	Vector<BFW_STRING_TYPE_A> _Namespaces;
	Vector<BFW_STRING_TYPE_A> _NamespaceValues;
	bool _Exit = false;

	return SolveXMLNamespaces(Root, _Namespaces, _NamespaceValues, _Node, _TagNamespace, _AttributesNamespaces, _Exit);
}

BFW::Vector<BFW::Assets::XMLNode>& BFW::Assets::XML::GetExclamationMarks()
{
	return ExclamationMarks;
}

const BFW::Vector<BFW::Assets::XMLNode>& BFW::Assets::XML::GetExclamationMarks() const
{
	return ExclamationMarks;
}

BFW::Vector<BFW::Assets::XMLNode>& BFW::Assets::XML::GetQuestionMarks()
{
	return QuestionMarks;
}

const BFW::Vector<BFW::Assets::XMLNode>& BFW::Assets::XML::GetQuestionMarks() const
{
	return QuestionMarks;
}

BFW::Assets::XMLNode& BFW::Assets::XML::GetRoot()
{
	return Root;
}

const BFW::Assets::XMLNode& BFW::Assets::XML::GetRoot() const
{
	return Root;
}

BFW::Assets::XML& BFW::Assets::XML::operator= (const XML& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	ExclamationMarks = _Other.ExclamationMarks;
	QuestionMarks = _Other.QuestionMarks;
	Root = _Other.Root;

	return *this;
}

BFW::Assets::XML& BFW::Assets::XML::operator= (XML&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	ExclamationMarks = (Vector<XMLNode>&&)(_Other.ExclamationMarks);
	QuestionMarks = (Vector<XMLNode>&&)(_Other.QuestionMarks);
	Root = (XMLNode&&)(_Other.Root);

	return *this;
}



BFW::Assets::Json::Json() : Type(_NullJsonType), BoolValue(false), NumberValue(0.0f), StringValue(""), ArrayValue(), ObjectDataValue()
{

}

BFW::Assets::Json::Json(const Json& _Other) : Type(_Other.Type), BoolValue(_Other.BoolValue), NumberValue(_Other.NumberValue), StringValue(_Other.StringValue), ArrayValue(_Other.ArrayValue), ObjectDataValue(_Other.ObjectDataValue)
{

}

BFW::Assets::Json::Json(Json&& _Other) noexcept : Type(_Other.Type), BoolValue(_Other.BoolValue), NumberValue(_Other.NumberValue), StringValue(_Other.StringValue), ArrayValue((Vector<Json>&&)(_Other.ArrayValue)), ObjectDataValue((JsonObjectData&&)(_Other.ObjectDataValue))
{
	_Other.Type = _NullJsonType;
	_Other.BoolValue = false;
	_Other.NumberValue = 0.0f;
	_Other.StringValue = "";
}

BFW::Assets::Json::~Json()
{

}

const bool BFW::Assets::Json::Load(const FileContent& _FileContent)
{
	*this = Json();

	if (!_FileContent.GetData() || _FileContent[_FileContent.GetLength() - 1] != '\0')
	{
		return false;
	}

	size_t _CurrentPos = 0;

	while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
	{
		_CurrentPos++;
	}

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != '{' && (const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) != '[')
	{
		return false;
	}

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == '{')
	{
		if (!LoadJsonObject(_FileContent, _CurrentPos, *this))
		{
			*this = Json();
			return false;
		}
	}

	if ((const BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos]) == '[')
	{
		if (!LoadJsonArray(_FileContent, _CurrentPos, *this))
		{
			*this = Json();
			return false;
		}
	}

	while (std::isspace((const unsigned BFW_CHAR_TYPE_A)(_FileContent[_CurrentPos])))
	{
		_CurrentPos++;
	}

	if (_CurrentPos != _FileContent.GetLength() - 1)
	{
		*this = Json();
		return false;
	}

	return true;
}

void BFW::Assets::Json::SetNull()
{
	Type = _NullJsonType;
	BoolValue = false;
	NumberValue = 0.0f;
	StringValue = "";
	ArrayValue = Vector<Json>();
	ObjectDataValue = JsonObjectData();
}

void BFW::Assets::Json::SetBool(const bool _BoolValue)
{
	Type = _BoolJsonType;
	BoolValue = _BoolValue;
	NumberValue = 0.0f;
	StringValue = "";
	ArrayValue = Vector<Json>();
	ObjectDataValue = JsonObjectData();
}

void BFW::Assets::Json::SetNumber(const float _NumberValue)
{
	Type = _NumberJsonType;
	BoolValue = false;
	NumberValue = _NumberValue;
	StringValue = "";
	ArrayValue = Vector<Json>();
	ObjectDataValue = JsonObjectData();
}

void BFW::Assets::Json::SetString(const BFW_STRING_VIEW_TYPE_A& _StringValue)
{
	Type = _StringJsonType;
	BoolValue = false;
	NumberValue = 0.0f;
	StringValue = _StringValue;
	ArrayValue = Vector<Json>();
	ObjectDataValue = JsonObjectData();
}

void BFW::Assets::Json::SetArray()
{
	Type = _ArrayJsonType;
	BoolValue = false;
	NumberValue = 0.0f;
	StringValue = "";
	ArrayValue = Vector<Json>();
	ObjectDataValue = JsonObjectData();
}

void BFW::Assets::Json::SetObject()
{
	Type = _ObjectJsonType;
	BoolValue = false;
	NumberValue = 0.0f;
	StringValue = "";
	ArrayValue = Vector<Json>();
	ObjectDataValue = JsonObjectData();
}

BFW::Assets::FileContent BFW::Assets::Json::Save() const
{
	if (Type != _ObjectJsonType && Type != _ArrayJsonType)
	{
		return FileContent();
	}

	size_t _TabLevel = 0;
	BFW_STRING_STREAM_TYPE_A _Stream;

	_Stream.imbue(std::locale::classic());

	if (Type == _ObjectJsonType)
	{
		if (!SaveJsonObject(_TabLevel, _Stream, *this))
		{
			return FileContent();
		}
	}

	if (Type == _ArrayJsonType)
	{
		if (!SaveJsonArray(_TabLevel, _Stream, *this))
		{
			return FileContent();
		}
	}

	_Stream BFW_WINDOWS_PLATFORM_CALL(<< '\r') << '\n';

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

const uint8_t BFW::Assets::Json::GetType() const
{
	return Type;
}

const bool BFW::Assets::Json::GetBool() const
{
	if (Type != _BoolJsonType)
	{
		throw nullptr;
	}

	return BoolValue;
}

const float BFW::Assets::Json::GetNumber() const
{
	if (Type != _NumberJsonType)
	{
		throw nullptr;
	}

	return NumberValue;
}

const BFW_STRING_TYPE_A& BFW::Assets::Json::GetString() const
{
	if (Type != _StringJsonType)
	{
		throw nullptr;
	}

	return StringValue;
}

BFW::Vector<BFW::Assets::Json>& BFW::Assets::Json::GetArray()
{
	if (Type != _ArrayJsonType)
	{
		throw nullptr;
	}

	return ArrayValue;
}

const BFW::Vector<BFW::Assets::Json>& BFW::Assets::Json::GetArray() const
{
	if (Type != _ArrayJsonType)
	{
		throw nullptr;
	}

	return ArrayValue;
}

BFW::Assets::JsonObjectData& BFW::Assets::Json::GetObjectData()
{
	if (Type != _ObjectJsonType)
	{
		throw nullptr;
	}

	return ObjectDataValue;
}

const BFW::Assets::JsonObjectData& BFW::Assets::Json::GetObjectData() const
{
	if (Type != _ObjectJsonType)
	{
		throw nullptr;
	}

	return ObjectDataValue;
}

BFW::Assets::Json& BFW::Assets::Json::operator= (const Json& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Type = _Other.Type;
	BoolValue = _Other.BoolValue;
	NumberValue = _Other.NumberValue;
	StringValue = _Other.StringValue;
	ArrayValue = _Other.ArrayValue;
	ObjectDataValue = _Other.ObjectDataValue;

	return *this;
}

BFW::Assets::Json& BFW::Assets::Json::operator= (Json&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Type = _Other.Type;
	BoolValue = _Other.BoolValue;
	NumberValue = _Other.NumberValue;
	StringValue = _Other.StringValue;
	ArrayValue = (Vector<Json>&&)(_Other.ArrayValue);
	ObjectDataValue = (JsonObjectData&&)(_Other.ObjectDataValue);

	_Other.Type = _NullJsonType;
	_Other.BoolValue = false;
	_Other.NumberValue = 0.0f;
	_Other.StringValue = "";

	return *this;
}
