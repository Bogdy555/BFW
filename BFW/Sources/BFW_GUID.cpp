#include "../Headers/BFW.hpp"



static std::mutex GUIDMutex;
static BFW::Math::RandomUInt64 RandomGenerator;
static BFW::Trie<bool> ExistentGUIDs;



const uint64_t BFW_API BFW::GUID::Get()
{
	GUIDMutex.lock();

	uint64_t _Result = RandomGenerator();

	while (ExistentGUIDs.GetData(BFW_TO_STRING(_Result).c_str()) != nullptr || _Result == 0)
	{
		_Result = RandomGenerator();
	}

	ExistentGUIDs.Push(BFW_TO_STRING(_Result).c_str(), true);

	GUIDMutex.unlock();

	return _Result;
}

void BFW_API BFW::GUID::Release(const uint64_t _GUID)
{
	GUIDMutex.lock();

	ExistentGUIDs.Erase(BFW_TO_STRING(_GUID).c_str());

	GUIDMutex.unlock();
}

const BFW_STRING_TYPE_A BFW_API BFW::GUID::GetStringA()
{
	return BFW_TO_STRING_A(Get());
}

const BFW_STRING_TYPE_W BFW_API BFW::GUID::GetStringW()
{
	return BFW_TO_STRING_W(Get());
}

const BFW_STRING_TYPE BFW_API BFW::GUID::GetString()
{
	BFW_UNICODE_CALL(return GetStringW());
	BFW_NON_UNICODE_CALL(return GetStringA());
}

void BFW_API BFW::GUID::ReleaseStringA(const BFW_STRING_TYPE_A& _GUID)
{
	GUIDMutex.lock();

	ExistentGUIDs.Erase(BFW_UTF8_TO_MACHINE(_GUID, nullptr).c_str());

	GUIDMutex.unlock();
}

void BFW_API BFW::GUID::ReleaseStringW(const BFW_STRING_TYPE_W& _GUID)
{
	GUIDMutex.lock();

	ExistentGUIDs.Erase(BFW_UNICODE_TO_MACHINE(_GUID, nullptr).c_str());

	GUIDMutex.unlock();
}

void BFW_API BFW::GUID::ReleaseString(const BFW_STRING_TYPE& _GUID)
{
	BFW_UNICODE_CALL(ReleaseStringW(_GUID));
	BFW_NON_UNICODE_CALL(ReleaseStringA(_GUID));
}
