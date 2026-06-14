#ifndef BFW_Templates_hpp

#define BFW_Templates_hpp



#include "BFW.hpp"



#include "BFW_Vector.hpp"

#include "BFW_Animation.hpp"



#if defined BFW_BUILD_DYNAMIC || defined BFW_LINK_DYNAMIC

BFW_EXTERN template class BFW_API BFW::Vector<BFW::Debug::HeapPointer>;

BFW_EXTERN template class BFW_API std::chrono::duration<std::chrono::system_clock::rep, std::chrono::system_clock::period>;
BFW_EXTERN template class BFW_API std::chrono::time_point<std::chrono::system_clock>;

#endif



#endif
