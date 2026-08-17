#ifndef BFW_Input_hpp

#define BFW_Input_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace Input
	{

#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

#ifdef BFW_WINDOWS_PLATFORM

		enum BFW_API KeyIds : const uint8_t
		{
			_MouseLKeyId = 1,
			_MouseRKeyId = 2,
			_CancelKeyId = 3,
			_MouseMKeyId = 4,
			_MouseX1KeyId = 5,
			_MouseX2KeyId = 6,
			_BackSpaceKeyId = 8,
			_TabKeyId = 9,
			_ClearKeyId = 12,
			_EnterKeyId = 13,
			_ShiftKeyId = 16,
			_ControlKeyId = 17,
			_AltKeyId = 18,
			_PauseKeyId = 19,
			_CapsLockKeyId = 20,
			_KanaKeyId = 21,
			_HangulKeyId = 21,
			_IMEOnKeyId = 22,
			_JunjaKeyId = 23,
			_FinalKeyId = 24,
			_HanjaKeyId = 25,
			_KanjiKeyId = 25,
			_IMEOffKeyId = 26,
			_EscKeyId = 27,
			_ConvertKeyId = 28,
			_NonConvertKeyId = 29,
			_AcceptKeyId = 30,
			_ModeChangeKeyId = 31,
			_SpaceKeyId = 32,
			_PageUpKeyId = 33,
			_PageDownKeyId = 34,
			_EndKeyId = 35,
			_HomeKeyId = 36,
			_LeftArrowKeyId = 37,
			_UpArrowKeyId = 38,
			_RightArrowKeyId = 39,
			_DownArrowKeyId = 40,
			_SelectKeyId = 41,
			_PrintKeyId = 42,
			_ExecuteKeyId = 43,
			_PrintScreenKeyId = 44,
			_InsertKeyId = 45,
			_DeleteKeyId = 46,
			_HelpKeyId = 47,
			_Key0KeyId = 48,
			_Key1KeyId = 49,
			_Key2KeyId = 50,
			_Key3KeyId = 51,
			_Key4KeyId = 52,
			_Key5KeyId = 53,
			_Key6KeyId = 54,
			_Key7KeyId = 55,
			_Key8KeyId = 56,
			_Key9KeyId = 57,
			_AKeyId = 65,
			_BKeyId = 66,
			_CKeyId = 67,
			_DKeyId = 68,
			_EKeyId = 69,
			_FKeyId = 70,
			_GKeyId = 71,
			_HKeyId = 72,
			_IKeyId = 73,
			_JKeyId = 74,
			_KKeyId = 75,
			_LKeyId = 76,
			_MKeyId = 77,
			_NKeyId = 78,
			_OKeyId = 79,
			_PKeyId = 80,
			_QKeyId = 81,
			_RKeyId = 82,
			_SKeyId = 83,
			_TKeyId = 84,
			_UKeyId = 85,
			_VKeyId = 86,
			_WKeyId = 87,
			_XKeyId = 88,
			_YKeyId = 89,
			_ZKeyId = 90,
			_LeftOSKeyId = 91,
			_RightOSKeyId = 92,
			_OptionsKeyId = 93,
			_SleepKeyId = 95,
			_Numpad0KeyId = 96,
			_Numpad1KeyId = 97,
			_Numpad2KeyId = 98,
			_Numpad3KeyId = 99,
			_Numpad4KeyId = 100,
			_Numpad5KeyId = 101,
			_Numpad6KeyId = 102,
			_Numpad7KeyId = 103,
			_Numpad8KeyId = 104,
			_Numpad9KeyId = 105,
			_NumpadMultiplyKeyId = 106,
			_NumpadAddKeyId = 107,
			_NumpadSeparatorKeyId = 108,
			_NumpadSubtractKeyId = 109,
			_NumpadDecimalKeyId = 110,
			_NumpadDivideKeyId = 111,
			_F1KeyId = 112,
			_F2KeyId = 113,
			_F3KeyId = 114,
			_F4KeyId = 115,
			_F5KeyId = 116,
			_F6KeyId = 117,
			_F7KeyId = 118,
			_F8KeyId = 119,
			_F9KeyId = 120,
			_F10KeyId = 121,
			_F11KeyId = 122,
			_F12KeyId = 123,
			_F13KeyId = 124,
			_F14KeyId = 125,
			_F15KeyId = 126,
			_F16KeyId = 127,
			_F17KeyId = 128,
			_F18KeyId = 129,
			_F19KeyId = 130,
			_F20KeyId = 131,
			_F21KeyId = 132,
			_F22KeyId = 133,
			_F23KeyId = 134,
			_F24KeyId = 135,
			_NumLockKeyId = 144,
			_ScrollLockKeyId = 145,
			_LeftShiftKeyId = 160,
			_RightShiftKeyId = 161,
			_LeftControlKeyId = 162,
			_RightControlKeyId = 163,
			_LeftAltKeyId = 164,
			_RightAltKeyId = 165,
			_BrowserBackKeyId = 166,
			_BrowserForwardKeyId = 167,
			_BrowserRefreshKeyId = 168,
			_BrowserStopKeyId = 169,
			_BrowserSearchKeyId = 170,
			_BrowserFavoritesKeyId = 171,
			_BrowserHomeKeyId = 172,
			_VolumeMuteKeyId = 173,
			_VolumeDownKeyId = 174,
			_VolumeUpKeyId = 175,
			_MediaNextTrackKeyId = 176,
			_MediaPrevTrackKeyId = 177,
			_MediaStopKeyId = 178,
			_MediaPlayPauseKeyId = 179,
			_LaunchMailKeyId = 180,
			_LaunchMediaSelectKeyId = 181,
			_LaunchApp1KeyId = 182,
			_LaunchApp2KeyId = 183,
			_SemiColonKeyId = 186,
			_PlusKeyId = 187,
			_CommaKeyId = 188,
			_MinusKeyId = 189,
			_PeriodKeyId = 190,
			_SlashKeyId = 191,
			_TildeKeyId = 192,
			_OpenBracketKeyId = 219,
			_BackSlashKeyId = 220,
			_CloseBracketKeyId = 221,
			_QuotationMarkKeyId = 222,
			_OEM8KeyId = 223,
			_OEM102KeyId = 226,
			_ProcessKeyPressKeyId = 229,
			_PacketKeyId = 231,
			_AttentionKeyId = 246,
			_CursorSelectKeyId = 247,
			_ExtendedSelectKeyId = 248,
			_EraseEndOfFileKeyId = 249,
			_PlayKeyId = 250,
			_ZoomKeyId = 251,
			_ProgramAttention1KeyId = 253,
			_OEMClearKeyId = 254
		};

#endif

#ifdef BFW_LINUX_PLATFORM

		enum BFW_API KeyIds : const uint8_t
		{

		};

#endif

#endif

		class BFW_API Key
		{

		public:

			Key();
			Key(const Key& _Other);
			Key(Key&& _Other) noexcept;
			~Key();

			void UpdateState(const bool _NewState);
			void CleanState();

			const bool IsPressed() const;
			const bool WasPressed() const;
			const bool JustPressed() const;
			const bool JustReleased() const;
			const Time::Timer& GetHoldTime() const;

			Key& operator= (const Key& _Other);
			Key& operator= (Key&& _Other) noexcept;

		private:

			bool State[2];
			Time::Timer HoldTime;

		};

		struct BFW_API ClickEvent
		{

			intptr_t X, Y;
			bool Control;
			bool Shift;

			ClickEvent();
			ClickEvent(const intptr_t _PositionX, const intptr_t _PositionY, const bool _Control, const bool _Shift);
			ClickEvent(const ClickEvent& _Other) = default;
			ClickEvent(ClickEvent&& _Other) noexcept;
			ClickEvent& operator= (const ClickEvent& _Other) = default;
			ClickEvent& operator= (ClickEvent&& _Other) noexcept;

		};

		struct BFW_API WheelEvent
		{

			intptr_t Delta;
			intptr_t X, Y;
			bool Control;
			bool Shift;

			WheelEvent();
			WheelEvent(const intptr_t _Delta, const intptr_t _PositionX, const intptr_t _PositionY, const bool _Control, const bool _Shift);
			WheelEvent(const WheelEvent& _Other) = default;
			WheelEvent(WheelEvent&& _Other) noexcept;
			WheelEvent& operator= (const WheelEvent& _Other) = default;
			WheelEvent& operator= (WheelEvent&& _Other) noexcept;

		};

#if defined BFW_WINDOWS_PLATFORM || defined BFW_LINUX_PLATFORM

		class BFW_API Controller
		{

		public:

			Controller();
			Controller(const Controller& _Other);
			Controller(Controller&& _Other) noexcept;
			~Controller();

			void UpdateState(const uint8_t _ControllerIndex, const bool _DeadZone = true, const bool _Threshold = true);
			void CleanState();

			const bool CheckConnected() const;
			const float GetXLeft() const;
			const float GetYLeft() const;
			const float GetXRight() const;
			const float GetYRight() const;
			const float GetTriggerLeft() const;
			const float GetTriggerRight() const;
			const Key& GetStart() const;
			const Key& GetBack() const;
			const Key& GetThumbLeft() const;
			const Key& GetThumbRight() const;
			const Key& GetButtonA() const;
			const Key& GetButtonB() const;
			const Key& GetButtonX() const;
			const Key& GetButtonY() const;
			const Key& GetButtonLeft() const;
			const Key& GetButtonRight() const;
			const Key& GetButtonUp() const;
			const Key& GetButtonDown() const;
			const Key& GetShoulderLeft() const;
			const Key& GetShoulderRight() const;

			Controller& operator= (const Controller& _Other);
			Controller& operator= (Controller&& _Other) noexcept;

#ifdef BFW_WINDOWS_PLATFORM

			static const bool SetRumble(const uint8_t _ControllerIndex, const float _RumbleLeft, const float _RumbleRight);

#endif

			private:

			bool Connected;

			float XLeft;
			float YLeft;

			float XRight;
			float YRight;

			float TriggerLeft;
			float TriggerRight;

			Key Start;
			Key Back;

			Key ThumbLeft;
			Key ThumbRight;

			Key ButtonA;
			Key ButtonB;
			Key ButtonX;
			Key ButtonY;

			Key ButtonLeft;
			Key ButtonRight;
			Key ButtonUp;
			Key ButtonDown;

			Key ShoulderLeft;
			Key ShoulderRight;

#ifdef BFW_LINUX_PLATFORM

			int32_t File;

#endif

		};

#endif

	}

}



#endif
