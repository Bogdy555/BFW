#ifndef BFW_String_hpp

#define BFW_String_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace String
	{

		const std::wstring BFW_API FromUTF8ToUnicode(const std::string_view& _String);
		const std::string BFW_API FromUnicodeToUTF8(const std::wstring_view& _String);

	}

}



#endif
