#ifndef BFW_Hardware_hpp

#define BFW_Hardware_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace Hardware
	{

#ifdef BFW_WINDOWS_PLATFORM

		class BFW_API SerialPort
		{

		public:

			SerialPort();
			SerialPort(const SerialPort& _Other) = delete;
			SerialPort(SerialPort&& _Other) noexcept;
			~SerialPort();

			bool Open(const wchar_t* _PortName = L"\\\\.\\COM7", const unsigned long _BaudRate = 9600);
			bool Update();
			void Close();

			unsigned long Read(char* _Buff, const unsigned long _Size);
			unsigned long Write(const unsigned char* _Buff, const unsigned long _Size);

			const bool CheckConnected() const;
			const wchar_t* GetPortName() const;
			const unsigned long GetBaudRate() const;

			void operator= (const SerialPort& _Other) = delete;
			void operator= (SerialPort&& _Other) noexcept;

		private:

			HANDLE FileHandle;
			COMSTAT Status;

			const wchar_t* PortName;
			bool Connected;
			unsigned long BaudRate;

		};

#endif

#ifdef BFW_ARDUINO_PLATFORM

		class BFW_API DigitalInputPullupPin
		{

		public:

			DigitalInputPullupPin();
			DigitalInputPullupPin(const DigitalInputPullupPin& _Other) = delete;
			DigitalInputPullupPin(DigitalInputPullupPin&& _Other) noexcept;
			~DigitalInputPullupPin();

			void Update();
			void DeleteState();

			void Bind(const unsigned long _Number);

			const unsigned long GetNumber() const;
			const Time::Timer& GetHoldTimer() const;

			const bool operator[] (const unsigned long _Index) const;

			void operator= (const DigitalInputPullupPin& _Other) = delete;
			void operator= (DigitalInputPullupPin&& _Other) noexcept;

		private:

			unsigned long Number;
			Time::Timer HoldTimer;
			bool State[2];

		};

		class BFW_API DigitalInputPin
		{

		public:

			DigitalInputPin();
			DigitalInputPin(const DigitalInputPin& _Other) = delete;
			DigitalInputPin(DigitalInputPin&& _Other) noexcept;
			~DigitalInputPin();

			void Update();
			void DeleteState();

			void Bind(const unsigned long _Number);

			const unsigned long GetNumber() const;
			const Time::Timer& GetHoldTimer() const;

			const bool operator[] (const unsigned long _Index) const;

			void operator= (const DigitalInputPin& _Other) = delete;
			void operator= (DigitalInputPin&& _Other) noexcept;

		private:

			unsigned long Number;
			Time::Timer HoldTimer;
			bool State[2];

		};

		class BFW_API DigitalOutputPin
		{

		public:

			DigitalOutputPin();
			DigitalOutputPin(const DigitalOutputPin& _Other) = delete;
			DigitalOutputPin(DigitalOutputPin&& _Other) noexcept;
			~DigitalOutputPin();

			void Write(const bool _State);
			const bool Read() const;

			void Bind(const unsigned long _Number);

			const unsigned long GetNumber() const;
			const Time::Timer& GetHoldTimer() const;
			const bool GetState() const;

			void operator= (const DigitalOutputPin& _Other) = delete;
			void operator= (DigitalOutputPin&& _Other) noexcept;

		private:

			unsigned long Number;
			Time::Timer HoldTimer;
			bool State;

		};

		class BFW_API AnalogInputPin
		{

		public:

			AnalogInputPin();
			AnalogInputPin(const AnalogInputPin& _Other) = delete;
			AnalogInputPin(AnalogInputPin&& _Other) noexcept;
			~AnalogInputPin();

			void Update();
			void DeleteState();

			void Bind(const unsigned long _Number);

			const unsigned long GetNumber() const;

			const unsigned long operator[] (const unsigned long _Index) const;

			void operator= (const AnalogInputPin& _Other) = delete;
			void operator= (AnalogInputPin&& _Other) noexcept;

		private:

			unsigned long Number;
			unsigned long State[2];

		};

		class BFW_API AnalogOutputPin
		{

		public:

			AnalogOutputPin();
			AnalogOutputPin(const AnalogOutputPin& _Other) = delete;
			AnalogOutputPin(AnalogOutputPin&& _Other) noexcept;
			~AnalogOutputPin();

			void Write(const unsigned char _State);

			void Bind(const unsigned long _Number);

			const unsigned long GetNumber() const;
			const Time::Timer& GetHoldTimer() const;
			const unsigned char GetState() const;

			void operator= (const AnalogOutputPin& _Other) = delete;
			void operator= (AnalogOutputPin&& _Other) noexcept;

		private:

			unsigned long Number;
			Time::Timer HoldTimer;
			unsigned char State;

		};

#endif

	}

}



#endif
