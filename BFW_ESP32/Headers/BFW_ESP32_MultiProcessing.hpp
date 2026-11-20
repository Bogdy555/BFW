#ifndef BFW_ESP32_MultiProcessing_hpp

#define BFW_ESP32_MultiProcessing_hpp



#include "BFW_ESP32.hpp"



namespace BFW_ESP32
{

	namespace MultiProcessing
	{

		BFW::Trie<void*> LoadLibrary(const BFW_CHAR_TYPE* _Path);

	}

}



#endif
