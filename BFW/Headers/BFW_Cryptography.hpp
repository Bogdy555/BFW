#ifndef BFW_Cryptography_hpp

#define BFW_Cryptography_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace Cryptography
	{

		const size_t HashA(const BFW_CHAR_TYPE_A* _Buffer, const size_t _Length);
		const size_t HashW(const BFW_CHAR_TYPE_W* _Buffer, const size_t _Length);
		const size_t Hash(const BFW_CHAR_TYPE* _Buffer, const size_t _Length);

		const size_t GetGUID();
		void ReleaseGUID(const size_t _GUID);
		const BFW_STRING_TYPE_A GetGUIDStringA();
		const BFW_STRING_TYPE_W GetGUIDStringW();
		const BFW_STRING_TYPE GetGUIDString();
		void ReleaseGUIDStringA(const BFW_STRING_TYPE_A& _GUID);
		void ReleaseGUIDStringW(const BFW_STRING_TYPE_W& _GUID);
		void ReleaseGUIDString(const BFW_STRING_TYPE& _GUID);

	}

}



#endif
