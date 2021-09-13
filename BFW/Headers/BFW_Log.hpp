#ifndef BFW_Log_hpp

#define BFW_Log_hpp



#include "BFW.hpp"



#ifdef BFW_WINDOWS_PLATFORM

#define BFW_STRING(X) L ## X

#define BFW_PRINT(X) std::wcout << X

#endif

#ifdef BFW_ARDUINO_PLATFORM

#define BFW_STRING(X) X

#define BFW_PRINT(X) Serial.print(X)

#endif



#ifndef BFW_DEBUG

#define BFW_LOG(X)

#endif

#ifdef BFW_DEBUG

#define BFW_LOG(X) BFW_PRINT(X)

#endif



namespace BFW
{

	namespace Log
	{

#ifdef BFW_WINDOWS_PLATFORM

		class BFW_API Tree
		{

		public:

			Tree(const wchar_t* _Text = nullptr, const unsigned short _Attribute = Enums::_ConsoleTxtTurquoise | Enums::_ConsoleBkgBlack, const bool _PrintKids = true);
			Tree(const Tree& _Other);
			Tree(Tree&& _Other) noexcept;
			~Tree();

			void SetText(const wchar_t* _Text);
			void SetAttribute(const unsigned short _Attribute);

			void SetPrintKids(const bool _PrintKids);

			const wchar_t* GetText() const;
			const unsigned short GetAttribute() const;

			const bool GetPrintKids() const;

			Vector<Tree*>& GetKids();
			const Vector<Tree*>& GetKids() const;

			const bool LogToConsole(const unsigned long _Tab = 1, const unsigned long _Level = 0) const;
			const bool LogToFile(std::wofstream* _FOut, const bool _LogAtribute = false, const unsigned long _Tab = 1, const unsigned long _Level = 0) const;

			void operator= (const Tree& _Other);
			void operator= (Tree&& _Other) noexcept;

		private:

			const wchar_t* Text;
			unsigned short Attribute;

			bool PrintKids;

			Vector<Tree*> Kids;

		};

		extern const Typedef::HandleRef BFW_API ConsoleOutHandle;

		extern const Typedef::UnsignedShortRef BFW_API DefaultAttribute;

		bool BFW_API Init();
		void BFW_API Stop();

		bool BFW_API GetConsoleAttributes(CONSOLE_SCREEN_BUFFER_INFO& _ConsoleInfo);
		bool BFW_API SetTextAttribute(const unsigned short _Attribute);

#endif

#ifdef BFW_ARDUINO_PLATFORM

		class BFW_API Tree
		{

		public:

			Tree(const char* _Text = nullptr, const bool _PrintKids = true);
			Tree(const Tree& _Other);
			Tree(Tree&& _Other) noexcept;
			~Tree();

			void SetText(const char* _Text);

			void SetPrintKids(const bool _PrintKids);

			const char* GetText() const;

			const bool GetPrintKids() const;

			Vector<Tree*>& GetKids();
			const Vector<Tree*>& GetKids() const;

			const bool LogToSerialPort(const unsigned long _Tab = 1, const unsigned long _Level = 0) const;

			void operator= (const Tree& _Other);
			void operator= (Tree&& _Other) noexcept;

		private:

			const char* Text;

			bool PrintKids;

			Vector<Tree*> Kids;

		};

		extern const Typedef::UnsignedLongRef BFW_API CurrentBitRate;

		void BFW_API Init(const unsigned long _BitRate = 9600);
		void BFW_API Stop();

#endif

	}

}



#endif
