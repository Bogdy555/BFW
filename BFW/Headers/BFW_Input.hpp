#ifndef BFW_Input_hpp

#define BFW_Input_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace Input
	{

#ifdef BFW_WINDOWS_PLATFORM

		class BFW_API Key
		{

		public:

			Key();
			Key(const Key& _Other);
			Key(Key&& _Other) noexcept;
			~Key();

			void UpdateState();
			void DeleteState();

			void SetVKCode(const unsigned char _VKCode);

			const unsigned char GetVKCode() const;
			const Time::Timer& GetHoldTimer() const;

			const bool operator[] (const unsigned long _Index) const;

			void operator= (const Key& _Other);
			void operator= (Key&& _Other) noexcept;

		private:

			unsigned char VKCode;
			Time::Timer HoldTimer;
			bool State[2];

		};

		namespace Cursor
		{

			extern const Typedef::PointRef BFW_API CursorPosition;

			void BFW_API UpdatePosition();
			bool BFW_API SetPosition(const long _X, const long _Y);

		}

		class BFW_API RumbleState
		{

		public:

			unsigned short RumbleSpeedLeft, RumbleSpeedRight;
			float Begin, End;

			RumbleState(const unsigned short _RumbleSpeedLeft = 0, const unsigned short _RumbleSpeedRight = 0, const float _Begin = 0.0f, const float _End = 0.0f);
			RumbleState(const RumbleState& _Other);
			RumbleState(RumbleState&& _Other) noexcept;
			~RumbleState();

			void operator= (const RumbleState& _Other);
			void operator= (RumbleState&& _Other) noexcept;

		};

		class BFW_API RumbleSequence
		{

		public:

			RumbleSequence();
			RumbleSequence(const RumbleSequence& _Other);
			RumbleSequence(RumbleSequence&& _Other) noexcept;
			~RumbleSequence();

			bool Update(const float _DeltaTime);

			void SetTime(const float _Time);
			void SetIndex(const unsigned long _Index);

			const float GetTime() const;
			const unsigned long GetIndex() const;
			const RumbleState& GetCurrentRumbleState() const;

			Vector<RumbleState>& GetRumbleStateVec();
			const Vector<RumbleState>& GetRumbleStateVec() const;

			void Load(const float* _Time, const unsigned short* _RumbleSpeed, const unsigned long _Count);
			void Load(const float* _Begin, const float* _End, const unsigned short* _RumbleSpeedLeft, const unsigned short* _RumbleSpeedRight, const unsigned long _Count);

			void operator= (const RumbleSequence& _Other);
			void operator= (RumbleSequence&& _Other) noexcept;

		private:

			float Time;
			unsigned long Index;
			Vector<RumbleState> RumbleStateVec;

		};

		class BFW_API Controller
		{

		public:

			const Typedef::BoolPtr Start, Select;
			const Typedef::ShortPtr XLeft, YLeft, XRight, YRight;
			const Typedef::BoolPtr ThumbLeft, ThumbRight;
			const Typedef::BoolPtr BtnLeft, BtnRight, BtnUp, BtnDown;
			const Typedef::BoolPtr DPadLeft, DPadRight, DPadUp, DPadDown;
			const Typedef::BoolPtr ShoulderUpLeft, ShoulderUpRight;
			const Typedef::UnsignedCharPtr ShoulderDownLeft, ShoulderDownRight;

			Controller(const unsigned long _ID = 0);
			Controller(const Controller& _Other) = delete;
			Controller(Controller&& _Other) noexcept = delete;
			~Controller();

			bool UpdateState();
			void DeleteState();

			void SetID(const unsigned long _ID);
			const unsigned long GetID() const;

			const bool CheckConnected() const;

			void SetThresHold(const bool _ThresHold);
			const bool GetThresHold() const;

			void SetDeadZone(const bool _DeadZone);
			const bool GetDeadZone() const;

			bool SetRumbleSpeed(const unsigned short _RumbleSpeedLeft, const unsigned short _RumbleSpeedRight);
			void GetRumbleSpeed(unsigned short& _RumbleSpeedLeft, unsigned short& _RumbleSpeedRight) const;

			const bool ValidID() const;

			static bool ValidID(const unsigned long _ID);

			void operator= (const Controller& _Other) = delete;
			void operator= (Controller&& _Other) noexcept = delete;

		private:

			unsigned long ID;
			bool Connected;
			bool ThresHold, DeadZone;
			unsigned short RumbleSpeedLeft, RumbleSpeedRight;

			bool _Start[2], _Select[2];
			short _XLeft[2], _YLeft[2], _XRight[2], _YRight[2];
			bool _ThumbLeft[2], _ThumbRight[2];
			bool _BtnLeft[2], _BtnRight[2], _BtnUp[2], _BtnDown[2];
			bool _DPadLeft[2], _DPadRight[2], _DPadUp[2], _DPadDown[2];
			bool _ShoulderUpLeft[2], _ShoulderUpRight[2];
			unsigned char _ShoulderDownLeft[2], _ShoulderDownRight[2];

		};

#endif

	}

}



#endif
