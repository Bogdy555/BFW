#include "../Headers/BFW.hpp"



const uint64_t BFW_API BFW::Cryptography::HashA(const BFW_CHAR_TYPE_A* _Buffer, const size_t _Length)
{
	return std::hash<std::string_view>()(std::string_view(_Buffer, _Length));
}

const uint64_t BFW_API BFW::Cryptography::HashW(const BFW_CHAR_TYPE_W* _Buffer, const size_t _Length)
{
	return std::hash<std::wstring_view>()(std::wstring_view(_Buffer, _Length));
}

const uint64_t BFW_API BFW::Cryptography::Hash(const BFW_CHAR_TYPE* _Buffer, const size_t _Length)
{
	BFW_UNICODE_CALL(return HashW(_Buffer, _Length));
	BFW_NON_UNICODE_CALL(return HashA(_Buffer, _Length));
}
