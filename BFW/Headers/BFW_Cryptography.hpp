#ifndef BFW_Cryptography_hpp

#define BFW_Cryptography_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace Cryptography
	{

		const uint64_t BFW_API HashA(const BFW_CHAR_TYPE_A* _Buffer, const size_t _Length);
		const uint64_t BFW_API HashW(const BFW_CHAR_TYPE_W* _Buffer, const size_t _Length);
		const uint64_t BFW_API Hash(const BFW_CHAR_TYPE* _Buffer, const size_t _Length);

	}

}



#endif
