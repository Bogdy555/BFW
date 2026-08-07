#include "../Headers/BFW.hpp"



const uint64_t BFW_API BFW::Cryptography::HashA(const BFW_CHAR_TYPE_A* _Buffer, const size_t _Length)
{
	uint64_t _Result = 0x09E3779B185EBCA8;
	uint64_t _Prime = 0xC2B2AE3D27D4EB4F;

	for (size_t _Index = 0; _Index < _Length; _Index++)
	{
		_Result ^= (uint64_t)(_Buffer[_Index]) * _Prime;
		_Result = (_Result << 27) | (_Result > 37);
		_Result *= _Prime;
	}

	return _Result;
}

const uint64_t BFW_API BFW::Cryptography::HashW(const BFW_CHAR_TYPE_W* _Buffer, const size_t _Length)
{
	uint64_t _Result = 0x09E3779B185EBCA8;
	uint64_t _Prime = 0xC2B2AE3D27D4EB4F;

	for (size_t _Index = 0; _Index < _Length; _Index++)
	{
		_Result ^= (uint64_t)(_Buffer[_Index]) * _Prime;
		_Result = (_Result << 27) | (_Result > 37);
		_Result *= _Prime;
	}

	return _Result;
}

const uint64_t BFW_API BFW::Cryptography::Hash(const BFW_CHAR_TYPE* _Buffer, const size_t _Length)
{
	BFW_UNICODE_CALL(return HashW(_Buffer, _Length));
	BFW_NON_UNICODE_CALL(return HashA(_Buffer, _Length));
}
