#include "../Headers/BFW.hpp"



const size_t BFW::GUID::Get()
{
	return 0;
}

void BFW::GUID::Release(const size_t _GUID)
{

}

const BFW_STRING_TYPE_A BFW::GUID::GetStringA()
{
	return "0";
}

const BFW_STRING_TYPE_W BFW::GUID::GetStringW()
{
	return L"0";
}

const BFW_STRING_TYPE BFW::GUID::GetString()
{
	BFW_UNICODE_CALL(return GetStringW());
	BFW_NON_UNICODE_CALL(return GetStringA());
}

void BFW::GUID::ReleaseStringA(const BFW_STRING_TYPE_A& _GUID)
{

}

void BFW::GUID::ReleaseStringW(const BFW_STRING_TYPE_W& _GUID)
{

}

void BFW::GUID::ReleaseString(const BFW_STRING_TYPE& _GUID)
{
	BFW_UNICODE_CALL(ReleaseStringW(_GUID));
	BFW_NON_UNICODE_CALL(ReleaseStringA(_GUID));
}
