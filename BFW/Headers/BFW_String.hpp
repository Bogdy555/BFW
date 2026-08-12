#ifndef BFW_String_hpp

#define BFW_String_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace String
	{

		const bool BFW_API Init();
		void BFW_API Stop();

		BFW_API const BFW_CHAR_TYPE_A* GetDefaultLocale();

		const BFW_STRING_TYPE_W BFW_API FromUTF8ToUnicode(const BFW_STRING_VIEW_TYPE_A& _String, bool* _Error = nullptr);
		const BFW_STRING_TYPE_A BFW_API FromUnicodeToUTF8(const BFW_STRING_VIEW_TYPE_W& _String, bool* _Error = nullptr);

		const bool BFW_API IsHexA(const BFW_CHAR_TYPE_A _Char);
		const bool BFW_API IsHexW(const BFW_CHAR_TYPE_W _Char);
		const bool BFW_API IsHex(const BFW_CHAR_TYPE _Char);

		const uint8_t BFW_API HexCharToNibbleA(const BFW_CHAR_TYPE_A _Char);
		const uint8_t BFW_API HexCharToNibbleW(const BFW_CHAR_TYPE_W _Char);
		const uint8_t BFW_API HexCharToNibble(const BFW_CHAR_TYPE _Char);

		const bool BFW_API IsUTF8MultiByte2(const BFW_CHAR_TYPE_A _Char);
		const bool BFW_API IsUTF8MultiByte3(const BFW_CHAR_TYPE_A _Char);
		const bool BFW_API IsUTF8MultiByte4(const BFW_CHAR_TYPE_A _Char);

		const bool BFW_API IsValidUTF8MultiByte2(const BFW_CHAR_TYPE_A _Char);
		const bool BFW_API IsValidUTF8MultiByte3(const BFW_CHAR_TYPE_A _Char);
		const bool BFW_API IsValidUTF8MultiByte4(const BFW_CHAR_TYPE_A _Char);

		const bool BFW_API IsUTF8MultiByteContinuation(const BFW_CHAR_TYPE_A _Char);

		const bool BFW_API IsValidUTF8MultiByte3FirstContinuation(const BFW_CHAR_TYPE_A _Char1, const BFW_CHAR_TYPE_A _Char2);
		const bool BFW_API IsValidUTF8MultiByte4FirstContinuation(const BFW_CHAR_TYPE_A _Char1, const BFW_CHAR_TYPE_A _Char2);

		const bool BFW_API IsUnicodeSurrogated(const uint32_t _Char);
		const bool BFW_API IsUnicodeSurrogatedContinuation(const uint32_t _Char);

		const bool BFW_API IsValidUnicodePoint1A(const uint32_t _Char);
		const bool BFW_API IsValidUnicodePoint2A(const uint32_t _Char);
		const bool BFW_API IsValidUnicodePoint3A(const uint32_t _Char);
		const bool BFW_API IsValidUnicodePoint4A(const uint32_t _Char);
		const bool BFW_API IsValidUnicodePointW(const uint32_t _Char);

		const uint32_t BFW_API ConstructUnicodePointA(const BFW_CHAR_TYPE_A _Char);
		const uint32_t BFW_API ConstructUnicodePointA(const BFW_CHAR_TYPE_A _Char1, const BFW_CHAR_TYPE_A _Char2);
		const uint32_t BFW_API ConstructUnicodePointA(const BFW_CHAR_TYPE_A _Char1, const BFW_CHAR_TYPE_A _Char2, const BFW_CHAR_TYPE_A _Char3);
		const uint32_t BFW_API ConstructUnicodePointA(const BFW_CHAR_TYPE_A _Char1, const BFW_CHAR_TYPE_A _Char2, const BFW_CHAR_TYPE_A _Char3, const BFW_CHAR_TYPE_A _Char4);

#ifdef BFW_WINDOWS_PLATFORM

		const uint32_t BFW_API ConstructUnicodePointW(const BFW_CHAR_TYPE_W _Char1, const BFW_CHAR_TYPE_W _Char2);

#endif

		const bool BFW_API IsValidUTF8String(const BFW_STRING_VIEW_TYPE_A& _String);
		const bool BFW_API IsValidUnicodeString(const BFW_STRING_VIEW_TYPE_W& _String);

		const bool BFW_API IsControlCharacter(const BFW_CHAR_TYPE_A _Char);
		const bool BFW_API IsControlCharacter(const BFW_CHAR_TYPE_W _Char);

		const bool BFW_API IsExtendedControlCharacter(const BFW_CHAR_TYPE_A _Char);
		const bool BFW_API IsExtendedControlCharacter(const BFW_CHAR_TYPE_W _Char);

	}

}



#endif
