#ifndef BFW_GUID_hpp

#define BFW_GUID_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace GUID
	{

		const size_t Get();
		void Release(const size_t _GUID);
		const BFW_STRING_TYPE_A GetStringA();
		const BFW_STRING_TYPE_W GetStringW();
		const BFW_STRING_TYPE GetString();
		void ReleaseStringA(const BFW_STRING_TYPE_A& _GUID);
		void ReleaseStringW(const BFW_STRING_TYPE_W& _GUID);
		void ReleaseString(const BFW_STRING_TYPE& _GUID);

	}

}



#endif
