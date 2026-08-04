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

	}

}



#endif
