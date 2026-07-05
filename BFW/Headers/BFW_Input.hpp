#ifndef BFW_Input_hpp

#define BFW_Input_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace Input
	{

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
			const float GetHoldTime() const;

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
