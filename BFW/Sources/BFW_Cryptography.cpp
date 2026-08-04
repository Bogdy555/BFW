#include "../Headers/BFW.hpp"



const size_t BFW::Cryptography::HashA(const BFW_CHAR_TYPE_A* _Buffer, const size_t _Length)
{
	return std::hash<std::string_view>()(std::string_view(_Buffer, _Length));
}

const size_t BFW::Cryptography::HashW(const BFW_CHAR_TYPE_W* _Buffer, const size_t _Length)
{
	return std::hash<std::wstring_view>()(std::wstring_view(_Buffer, _Length));
}

const size_t BFW::Cryptography::Hash(const BFW_CHAR_TYPE* _Buffer, const size_t _Length)
{
	BFW_UNICODE_CALL(return HashW(_Buffer, _Length));
	BFW_NON_UNICODE_CALL(return HashA(_Buffer, _Length));
}

const size_t BFW::Cryptography::GetGUID()
{
	return 0;
}

void BFW::Cryptography::ReleaseGUID(const size_t _GUID)
{

}

const BFW_STRING_TYPE_A BFW::Cryptography::GetGUIDStringA()
{
	return "0";
}

const BFW_STRING_TYPE_W BFW::Cryptography::GetGUIDStringW()
{
	return L"0";
}

const BFW_STRING_TYPE BFW::Cryptography::GetGUIDString()
{
	BFW_UNICODE_CALL(return GetGUIDStringW());
	BFW_NON_UNICODE_CALL(return GetGUIDStringA());
}

void BFW::Cryptography::ReleaseGUIDStringA(const BFW_STRING_TYPE_A& _GUID)
{

}

void BFW::Cryptography::ReleaseGUIDStringW(const BFW_STRING_TYPE_W& _GUID)
{

}

void BFW::Cryptography::ReleaseGUIDString(const BFW_STRING_TYPE& _GUID)
{
	BFW_UNICODE_CALL(ReleaseGUIDStringW(_GUID));
	BFW_NON_UNICODE_CALL(ReleaseGUIDStringA(_GUID));
}
