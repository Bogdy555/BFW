#ifndef BFW_String_hpp

#define BFW_String_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace String
	{

		const BFW_STRING_TYPE_W BFW_API FromUTF8ToUnicode(const BFW_STRING_VIEW_TYPE_A& _String);
		const BFW_STRING_TYPE_A BFW_API FromUnicodeToUTF8(const BFW_STRING_VIEW_TYPE_W& _String);

	}

}



#endif
