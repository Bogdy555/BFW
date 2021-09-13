#ifndef BFW_Templates_hpp

#define BFW_Templates_hpp



#include "BFW.hpp"



#if defined BFW_DLL_BUILD || defined BFW_DLL_LINK



BFW_EXTERN template class BFW_API BFW::Vector<BFW::Debug::HeapPointer>;

BFW_EXTERN template class BFW_API BFW::Vector<BFW::Log::Tree*>;

BFW_EXTERN template class BFW_API BFW::Vector<BFW::Input::RumbleState>;

BFW_EXTERN template class BFW_API std::chrono::duration<std::chrono::system_clock::rep, std::chrono::system_clock::period>;
BFW_EXTERN template class BFW_API std::chrono::time_point<std::chrono::system_clock>;

BFW_EXTERN template class BFW_API std::mersenne_twister_engine<unsigned int, 32, 624, 397, 31, 2567483615, 11, 4294967295, 7, 2636928640, 15, 4022730752, 18, 1812433253>;
BFW_EXTERN template class BFW_API std::mersenne_twister_engine<unsigned __int64, 64, 312, 156, 31, 13043109905998158313, 29, 6148914691236517205, 17, 8202884508482404352, 37, 18444473444759240704, 43, 6364136223846793005>;

struct BFW_API std::uniform_int<long>::param_type;
BFW_EXTERN template class BFW_API std::uniform_int_distribution<long>;
struct BFW_API std::uniform_int<long long>::param_type;
BFW_EXTERN template class BFW_API std::uniform_int_distribution<long long>;

struct BFW_API std::uniform_real<float>::param_type;
BFW_EXTERN template class BFW_API std::uniform_real_distribution<float>;
struct BFW_API std::uniform_real<double>::param_type;
BFW_EXTERN template class BFW_API std::uniform_real_distribution<double>;



#endif



#endif
