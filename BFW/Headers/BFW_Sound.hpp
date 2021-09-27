#ifndef BFW_Sound_hpp

#define BFW_Sound_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace Sound
	{

#ifdef BFW_WINDOWS_PLATFORM

		bool BFW_API LoadFromFile(const wchar_t* _FilePath, unsigned char** _Buff, unsigned __int32* _BuffSize, WAVEFORMATEX* _AudioInfo);
		void BFW_API ReleaseLoadedBuff(const unsigned char* _Buff);
		bool BFW_API StartStreamFromFile(const wchar_t* _FilePath, FILE** _File, WAVEFORMATEX* _AudioInfo, unsigned __int32* _BuffSize);
		bool BFW_API StreamFromFile(FILE** _File, unsigned char* _Buff, const unsigned __int32 _BuffSize, unsigned __int32* _ReadSize);
		bool BFW_API StopStreamFromFile(FILE** _File);

		bool BFW_API SaveToFile(const wchar_t* _FilePath, const unsigned char* _Buff, const unsigned __int32 _BuffSize, const WAVEFORMATEX _AudioInfo);
		bool BFW_API StartStreamToFile(const wchar_t* _FilePath, FILE** _File, const WAVEFORMATEX _AudioInfo);
		bool BFW_API StreamToFile(const wchar_t* _FilePath, FILE** _File, const unsigned char* _Buff, const unsigned __int32 _BuffSize);
		bool BFW_API StopStreamToFile(const wchar_t* _FilePath, FILE** _File);

#endif

	}

}



#endif
