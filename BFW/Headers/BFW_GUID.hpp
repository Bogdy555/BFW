#ifndef BFW_GUID_hpp

#define BFW_GUID_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace GUID
	{

		const uint64_t BFW_API Get();
		void BFW_API Release(const uint64_t _GUID);
		const BFW_STRING_TYPE_A BFW_API GetStringA();
		const BFW_STRING_TYPE_W BFW_API GetStringW();
		const BFW_STRING_TYPE BFW_API GetString();
		void BFW_API ReleaseStringA(const BFW_STRING_TYPE_A& _GUID);
		void BFW_API ReleaseStringW(const BFW_STRING_TYPE_W& _GUID);
		void BFW_API ReleaseString(const BFW_STRING_TYPE& _GUID);

	}

}



#endif
