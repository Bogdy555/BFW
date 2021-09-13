#include "..\Headers\BFW.hpp"



#ifdef BFW_WINDOWS_PLATFORM



BFW::Log::Tree::Tree(const wchar_t* _Text, const unsigned short _Attribute, const bool _PrintKids) :
	Text(_Text), Attribute(_Attribute), PrintKids(_PrintKids), Kids()
{

}

BFW::Log::Tree::Tree(const Tree& _Other) :
	Text(_Other.Text), Attribute(_Other.Attribute), PrintKids(_Other.PrintKids), Kids((const Vector<Tree*>&)(_Other.Kids))
{

}

BFW::Log::Tree::Tree(Tree&& _Other) noexcept :
	Text(_Other.Text), Attribute(_Other.Attribute), PrintKids(_Other.PrintKids), Kids((Vector<Tree*>&&)(_Other.Kids))
{
	_Other.Text = nullptr;
	_Other.Attribute = 0;
	_Other.PrintKids = true;
}

BFW::Log::Tree::~Tree()
{

}

void BFW::Log::Tree::SetText(const wchar_t* _Text)
{
	Text = _Text;
}

void BFW::Log::Tree::SetAttribute(const unsigned short _Attribute)
{
	Attribute = _Attribute;
}

void BFW::Log::Tree::SetPrintKids(const bool _PrintKids)
{
	PrintKids = _PrintKids;
}

const wchar_t* BFW::Log::Tree::GetText() const
{
	return Text;
}

const unsigned short BFW::Log::Tree::GetAttribute() const
{
	return Attribute;
}

const bool BFW::Log::Tree::GetPrintKids() const
{
	return PrintKids;
}

BFW::Vector<BFW::Log::Tree*>& BFW::Log::Tree::GetKids()
{
	return Kids;
}

const BFW::Vector<BFW::Log::Tree*>& BFW::Log::Tree::GetKids() const
{
	return Kids;
}

const bool BFW::Log::Tree::LogToConsole(const unsigned long _Tab, const unsigned long _Level) const
{
	if (ConsoleOutHandle == INVALID_HANDLE_VALUE || ConsoleOutHandle == NULL)
	{
		BFW_DEBUG_BREAK_MSG(L"BFW::Log has not been initialized!");
		return false;
	}

	if (!Text)
	{
		BFW_DEBUG_BREAK_MSG(L"No text to output to console!");
		return false;
	}

	if (!SetTextAttribute(Attribute))
	{
		return false;
	}

	for (unsigned long i = 0; i < _Level * _Tab; i++)
	{
		BFW_PRINT(L'\t');
	}

	BFW_PRINT(Text);
	BFW_PRINT(L'\n');

	if (PrintKids)
	{
		for (unsigned long i = 0; i < Kids.GetSize(); i++)
		{
			if (!Kids[i]->LogToConsole(_Tab, _Level + 1))
			{
				return false;
			}
		}
	}

	return true;
}

const bool BFW::Log::Tree::LogToFile(std::wofstream* _FOut, const bool _LogAtribute, const unsigned long _Tab, const unsigned long _Level) const
{
	if (!_FOut)
	{
		BFW_DEBUG_BREAK_MSG(L"No file to output to!");
		return false;
	}

	if (!Text)
	{
		BFW_DEBUG_BREAK_MSG(L"No text to output in file!");
		return false;
	}

	for (unsigned long i = 0; i < _Level * _Tab; i++)
	{
		*_FOut << L'\t';
	}

	if (_LogAtribute)
	{
		*_FOut << Attribute << L' ';
	}

	*_FOut << Text << L'\n';

	if (PrintKids)
	{
		for (unsigned long i = 0; i < Kids.GetSize(); i++)
		{
			if (!Kids[i]->LogToFile(_FOut, _Tab, _Level + 1))
			{
				return false;
			}
		}
	}

	return true;
}

void BFW::Log::Tree::operator= (const Tree& _Other)
{
	Text = _Other.Text;
	Attribute = _Other.Attribute;
	PrintKids = _Other.PrintKids;
	Kids = (const Vector<Tree*>&)(_Other.Kids);
}

void BFW::Log::Tree::operator= (Tree&& _Other) noexcept
{
	Text = _Other.Text;
	Attribute = _Other.Attribute;
	PrintKids = _Other.PrintKids;
	Kids = (Vector<Tree*>&&)(_Other.Kids);

	_Other.Text = nullptr;
	_Other.Attribute = 0;
	_Other.PrintKids = true;
}



static HANDLE _ConsoleOutHandle = NULL;

const BFW::Typedef::HandleRef BFW_API BFW::Log::ConsoleOutHandle = _ConsoleOutHandle;

static unsigned short _DefaultAttribute = 0;

const BFW::Typedef::UnsignedShortRef BFW_API BFW::Log::DefaultAttribute = _DefaultAttribute;



bool BFW_API BFW::Log::Init()
{
	if (_ConsoleOutHandle != INVALID_HANDLE_VALUE && _ConsoleOutHandle != NULL)
	{
		return true;
	}

	_ConsoleOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (_ConsoleOutHandle == INVALID_HANDLE_VALUE || _ConsoleOutHandle == NULL)
	{
		_ConsoleOutHandle = NULL;
		return false;
	}

	CONSOLE_SCREEN_BUFFER_INFO _ConsoleInfo;
	if (!GetConsoleScreenBufferInfo(_ConsoleOutHandle, &_ConsoleInfo))
	{
		CloseHandle(_ConsoleOutHandle);
		_ConsoleOutHandle = NULL;
		return false;
	}

	_DefaultAttribute = _ConsoleInfo.wAttributes;

	return true;
}

void BFW_API BFW::Log::Stop()
{
	if (_ConsoleOutHandle == INVALID_HANDLE_VALUE || _ConsoleOutHandle == NULL)
	{
		return;
	}

	SetTextAttribute(_DefaultAttribute);
	_DefaultAttribute = 0;

	CloseHandle(_ConsoleOutHandle);
	_ConsoleOutHandle = NULL;
}

bool BFW_API BFW::Log::GetConsoleAttributes(CONSOLE_SCREEN_BUFFER_INFO& _ConsoleInfo)
{
	if (_ConsoleOutHandle == INVALID_HANDLE_VALUE || _ConsoleOutHandle == NULL)
	{
		BFW_DEBUG_BREAK_MSG(L"BFW::Log has not been initialized!");
		return false;
	}
	return GetConsoleScreenBufferInfo(_ConsoleOutHandle, &_ConsoleInfo);
}

bool BFW_API BFW::Log::SetTextAttribute(const unsigned short _Attribute)
{
	if (_ConsoleOutHandle == INVALID_HANDLE_VALUE || _ConsoleOutHandle == NULL)
	{
		BFW_DEBUG_BREAK_MSG(L"BFW::Log has not been initialized!");
		return false;
	}
	return SetConsoleTextAttribute(_ConsoleOutHandle, _Attribute);
}



#endif



#ifdef BFW_ARDUINO_PLATFORM



BFW::Log::Tree::Tree(const char* _Text, const bool _PrintKids) :
	Text(_Text), PrintKids(_PrintKids), Kids()
{

}

BFW::Log::Tree::Tree(const Tree& _Other) :
	Text(_Other.Text), PrintKids(_Other.PrintKids), Kids((const Vector<Tree*>&)(_Other.Kids))
{

}

BFW::Log::Tree::Tree(Tree&& _Other) noexcept :
	Text(_Other.Text), PrintKids(_Other.PrintKids), Kids((Vector<Tree*>&&)(_Other.Kids))
{

}

BFW::Log::Tree::~Tree()
{

}

void BFW::Log::Tree::SetText(const char* _Text)
{
	Text = _Text;
}

void BFW::Log::Tree::SetPrintKids(const bool _PrintKids)
{
	PrintKids = _PrintKids;
}

const char* BFW::Log::Tree::GetText() const
{
	return Text;
}

const bool BFW::Log::Tree::GetPrintKids() const
{
	return PrintKids;
}

BFW::Vector<BFW::Log::Tree*>& BFW::Log::Tree::GetKids()
{
	return Kids;
}

const BFW::Vector<BFW::Log::Tree*>& BFW::Log::Tree::GetKids() const
{
	return Kids;
}

const bool BFW::Log::Tree::LogToSerialPort(const unsigned long _Tab, const unsigned long _Level) const
{
	if (!CurrentBitRate)
	{
		BFW_DEBUG_BREAK_MSG("BFW::Log has not been initialized!");
		return false;
	}

	if (!Text)
	{
		BFW_DEBUG_BREAK_MSG("No text to output to serial port!");
		return false;
	}

	for (unsigned long i = 0; i < _Level * _Tab; i++)
	{
		BFW_PRINT('\t');
	}

	BFW_PRINT(Text);
	BFW_PRINT('\n');

	if (PrintKids)
	{
		for (unsigned long i = 0; i < Kids.GetSize(); i++)
		{
			if (!Kids[i]->LogToSerialPort(_Tab, _Level + 1))
			{
				return false;
			}
		}
	}

	return true;
}

void BFW::Log::Tree::operator= (const Tree& _Other)
{
	Text = _Other.Text;
	PrintKids = _Other.PrintKids;
	Kids = (const Vector<Tree*>&)(_Other.Kids);
}

void BFW::Log::Tree::operator= (Tree&& _Other) noexcept
{
	Text = _Other.Text;
	PrintKids = _Other.PrintKids;
	Kids = (Vector<Tree*>&&)(_Other.Kids);

	_Other.Text = nullptr;
	_Other.PrintKids = true;
}



static unsigned long _CurrentBitRate = 0;

const BFW::Typedef::UnsignedLongRef BFW_API BFW::Log::CurrentBitRate = _CurrentBitRate;



void BFW_API BFW::Log::Init(const unsigned long _BitRate)
{
	if (_BitRate == 0)
	{
		return;
	}
	if (CurrentBitRate == _BitRate)
	{
		return;
	}
	if (CurrentBitRate)
	{
		Stop();
	}
	Serial.begin(_BitRate);
	_CurrentBitRate = _BitRate;
}

void BFW_API BFW::Log::Stop()
{
	if (_CurrentBitRate)
	{
		_CurrentBitRate = 0;
		Serial.end();
	}
}



#endif
