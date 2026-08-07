#ifndef BFW_Templates_hpp

#define BFW_Templates_hpp



#include "BFW.hpp"



#include "BFW_Vector.hpp"

#include "BFW_SmartPointers.hpp"

#include "BFW_Trie.hpp"

#include "BFW_Heap.hpp"

#include "BFW_Animation.hpp"



#if defined BFW_BUILD_DYNAMIC || defined BFW_LINK_DYNAMIC

#ifdef BFW_WINDOWS_PLATFORM

struct BFW_API std::_Container_base12;
BFW_EXTERN template struct BFW_API std::char_traits<BFW_CHAR_TYPE_A>;
BFW_EXTERN template class BFW_API std::allocator<BFW_CHAR_TYPE_A>;
BFW_EXTERN template struct BFW_API std::_Simple_types<BFW_CHAR_TYPE_A>;
union BFW_API std::_String_val<std::_Simple_types<BFW_CHAR_TYPE_A>>::_Bxty;
BFW_EXTERN template class BFW_API std::_String_val<std::_Simple_types<BFW_CHAR_TYPE_A>>;
BFW_EXTERN template class BFW_API std::_Compressed_pair<std::allocator<BFW_CHAR_TYPE_A>, std::_String_val<std::_Simple_types<BFW_CHAR_TYPE_A>>, true>;
BFW_EXTERN template class BFW_API std::basic_string<BFW_CHAR_TYPE_A, std::char_traits<BFW_CHAR_TYPE_A>, std::allocator<BFW_CHAR_TYPE_A>>;
BFW_EXTERN template struct BFW_API std::char_traits<BFW_CHAR_TYPE_W>;
BFW_EXTERN template class BFW_API std::allocator<BFW_CHAR_TYPE_W>;
BFW_EXTERN template struct BFW_API std::_Simple_types<BFW_CHAR_TYPE_W>;
union BFW_API std::_String_val<std::_Simple_types<BFW_CHAR_TYPE_W>>::_Bxty;
BFW_EXTERN template class BFW_API std::_String_val<std::_Simple_types<BFW_CHAR_TYPE_W>>;
BFW_EXTERN template class BFW_API std::_Compressed_pair<std::allocator<BFW_CHAR_TYPE_W>, std::_String_val<std::_Simple_types<BFW_CHAR_TYPE_W>>, true>;
BFW_EXTERN template class BFW_API std::basic_string<BFW_CHAR_TYPE_W, std::char_traits<BFW_CHAR_TYPE_W>, std::allocator<BFW_CHAR_TYPE_W>>;

BFW_EXTERN template class BFW_API std::mersenne_twister_engine<uint32_t, 32, 624, 397, 31, 2567483615, 11, 4294967295, 7, 2636928640, 15, 4022730752, 18, 1812433253>;
BFW_EXTERN template class BFW_API std::mersenne_twister_engine<uint64_t, 64, 312, 156, 31, 13043109905998158313, 29, 6148914691236517205, 17, 8202884508482404352, 37, 18444473444759240704, 43, 6364136223846793005>;

#endif

BFW_EXTERN template class BFW_API BFW::Vector<uint8_t>;
BFW_EXTERN template class BFW_API BFW::Vector<size_t>;
BFW_EXTERN template class BFW_API BFW::Vector<BFW_CHAR_TYPE_A>;
BFW_EXTERN template class BFW_API BFW::Vector<BFW_CHAR_TYPE_W>;

BFW_EXTERN template class BFW_API BFW::Vector<BFW::Debug::HeapPointer>;

BFW_EXTERN template class BFW_API std::chrono::duration<std::chrono::system_clock::rep, std::chrono::system_clock::period>;
BFW_EXTERN template class BFW_API std::chrono::time_point<std::chrono::system_clock>;

BFW_EXTERN template class BFW_API BFW::Vector<BFW::FileSystem::File>;
BFW_EXTERN template class BFW_API BFW::Vector<BFW::FileSystem::Directory>;

BFW_EXTERN template class BFW_API BFW::UniquePointer<BFW::FileSystem::FileContent>;
BFW_EXTERN template class BFW_API BFW::Vector<BFW::Trie<BFW::FileSystem::FileContent>>;
BFW_EXTERN template class BFW_API BFW::Trie<BFW::FileSystem::FileContent>;
BFW_EXTERN template class BFW_API BFW::UniquePointer<BFW::Trie<BFW::FileSystem::FileContent>>;
BFW_EXTERN template class BFW_API BFW::Vector<BFW::Trie<BFW::Trie<BFW::FileSystem::FileContent>>>;
BFW_EXTERN template class BFW_API BFW::Trie<BFW::Trie<BFW::FileSystem::FileContent>>;

BFW_EXTERN template class BFW_API BFW::Vector<BFW::Input::ClickEvent>;
BFW_EXTERN template class BFW_API BFW::Vector<BFW::Input::WheelEvent>;
BFW_EXTERN template class BFW_API BFW::Vector<BFW::GUI::SafePopUpPointer>;
BFW_EXTERN template class BFW_API BFW::Vector<const BFW::GUI::SafePopUpPointer>;
BFW_EXTERN template class BFW_API BFW::Vector<BFW::GUI::PopUp>;
BFW_EXTERN template class BFW_API BFW::Vector<BFW::Vector<BFW::GUI::PopUp>>;
BFW_EXTERN template class BFW_API BFW::Vector<BFW::GUI::SafePopUpPointer*>;

#endif



#endif
