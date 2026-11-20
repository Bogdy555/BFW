#include "../Headers/BFW_ESP32.hpp"



BFW::Trie<void*> BFW_ESP32::MultiProcessing::LoadLibrary(const BFW_CHAR_TYPE* _Path)
{
	if (!_Path || _Path[0] == BFW_STRING_PREFIX('\0'))
	{
		return BFW::Trie<void*>();
	}

	BFW::Trie<void*> _Result;



	return _Result;
}
