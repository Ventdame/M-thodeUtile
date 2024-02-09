//////////////////////////////
// Inclusion des librairies //
//////////////////////////////

#define _KEEP_STD_REALLOC
#include "BisConsole.h"

#using <System.dll>
//#using <System.Drawing.dll>
//#using <System.Windows.Forms.dll>

using namespace System;
using namespace System::Diagnostics;
//using namespace System::Drawing;
//using namespace System::Windows::Forms;


////////////////////////////////////////
// Fonctions manquantes de Visual C++ //
////////////////////////////////////////

__pragma(warning(push))
__pragma(warning(disable:28251))
int vsscanf(const char *str, const char *p_format, va_list arg_list);
__pragma(warning(pop))


///////////////////////////////////////
// Fonctions de traitement de chaÓne //
///////////////////////////////////////

void* BisRealloc(void* Pointer, size_t Size)
{
	if (Pointer == NULL) return malloc(Size); else return realloc(Pointer, Size);
}

__pragma(warning(push))
__pragma(warning(disable:6387))
char* BisStringCopy(char* Target, const char* Source)
{
	#ifdef _DEBUG
		Debug::Assert((Target != NULL), "BisStringCopy >>> paramËtre Target NULL");
		Debug::Assert((Source != NULL), "BisStringCopy >>> paramËtre Source NULL");
	#else
		assert((Target != NULL) && (Source != NULL));
	#endif
	rsize_t Length = strlen(Source);
	strcpy_s(Target, Length+1, Source);
	return Target;
}
__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable:28182))
char* BisStringCopyN(char* Target, const char* Source, long Size)
{
	#ifdef _DEBUG
		Debug::Assert((Target != NULL), "BisStringCopyN >>> paramËtre Target NULL");
		Debug::Assert((Source != NULL), "BisStringCopyN >>> paramËtre Source NULL");
		Debug::Assert((Size >= 0), "BisStringCopyN >>> paramËtre Size < 0");
	#else
		assert((Target != NULL) && (Source != NULL) && (Size >= 0));
	#endif
	//rsize_t Length = strlen(Source);
	//strncpy_s(Target, Length+1, Source, Size); // Cette fonction de Microsoft plante le dÈboggueur !!!
	const char* s1=Source;
	char* s2=Target;
	for (long n = 0; (*s1 != 0) && (n < Size); s1++,s2++,n++) *s2 = *s1;
	return Target;
}
__pragma(warning(pop))

int BisStringCompareI(const char* Source1, const char* Source2)
{
	return _stricmp(Source1,Source2);
}

int BisStringCompareNI(const char* Source1, const char* Source2, size_t MaxCount)
{
	return _strnicmp(Source1,Source2,MaxCount);
}

__pragma(warning(push))
__pragma(warning(disable:6387))
char* BisStringConcat(char* Target, const char* Source)
{
	#ifdef _DEBUG
		Debug::Assert((Target != NULL), "BisStringCopy >>> paramËtre Target NULL");
		Debug::Assert((Source != NULL), "BisStringCopy >>> paramËtre Source NULL");
	#else
		assert((Target != NULL) && (Source != NULL));
	#endif
	rsize_t Length = strlen(Target) + strlen(Source);
	strcat_s(Target, Length+1, Source);
	return Target;
}
__pragma(warning(pop))

__pragma(warning(push))
__pragma(warning(disable:4793))
int __cdecl	BisSPrintF(char* Target, const char* Format, ...)
{
	assert((Target != NULL) && (Format != NULL));
	va_list Arguments;
	va_start(Arguments, Format);
	size_t Length = _vscprintf(Format, Arguments);
	if (Length == 0)
	{
		*Target = 0;
		va_end(Arguments);
		return 0;
	}
	char* Buffer = (char*)malloc((Length+1)*sizeof(char));
	if (Buffer == NULL) return -1;
	int Result = vsprintf_s(Buffer, Length+1, Format, Arguments);
	strcpy_s(Target, Length+1, Buffer);
	free(Buffer);
	va_end(Arguments);
	return Result;
}

int __cdecl	BisSNPrintF(char* Target, size_t MaxCount, const char* Format, ...)
{
	assert((Target != NULL) && (Format != NULL));
	va_list Arguments;
	va_start(Arguments, Format);
	size_t Length = _vscprintf(Format, Arguments);
	if (Length == 0)
	{
		*Target = 0;
		va_end(Arguments);
		return 0;
	}
	char* Buffer = (char*)malloc((Length+1)*sizeof(char));
	if (Buffer == NULL) return -1;
	int Result = vsnprintf_s(Buffer, Length+1, MaxCount, Format, Arguments);
	strcpy_s(Target, Length+1, Buffer);
	free(Buffer);
	va_end(Arguments);
	return Result;
}

int __cdecl BisPrintF(const char* Format, ...)
{
	assert(Format != NULL);
	va_list Arguments;
	va_start(Arguments, Format);
	size_t Length = _vscprintf(Format, Arguments);
	if (Length == 0)
	{
		va_end(Arguments);
		return 0;
	}
	char* Buffer = (char*)malloc((Length+1)*sizeof(char));
	if (Buffer == NULL) return -1;
	int Result = vsprintf_s(Buffer, Length+1, Format, Arguments);
	BisConsoleWrite(Buffer);
	free(Buffer);
	va_end(Arguments);
	return Result;
}

int __cdecl BisScanF(const char* Format, ...)
{
	static const int Length = 16384;
	static char* Buffer = NULL;
	assert(Format != NULL);
	va_list Arguments;
	va_start(Arguments, Format);
	if (Buffer == NULL)
	{
		Buffer = (char*)malloc((Length+1)*sizeof(char));
		if (Buffer == NULL) return -1;
	}
	BisConsoleRead(Buffer);
	int Result = vsscanf(Buffer, Format, Arguments);
	va_end(Arguments);
	return Result;
}
__pragma(warning(pop))

char* BisGetS(char* Target)
{
	#ifdef _DEBUG
		Debug::Assert((Target != NULL), "BisGetS >>> paramËtre Target NULL");
	#else
		assert(Target != NULL);
	#endif
	BisConsoleRead(Target);
	return Target;
}


///////////////////////////////////////
// Fonctions de gestion des fichiers //
///////////////////////////////////////

FILE* BisFOpen(const char* filename, const char* mode)
{
	FILE* Fichier = NULL;
	return (fopen_s(&Fichier, filename, mode) == 0) ? Fichier : NULL;
}

////////////////////////////////////////
// Fonctions de gestion de la console //
////////////////////////////////////////

template <typename T> class ValuesStack
{
public:
	static const long SizeIncrement = 16;

	ValuesStack()
		:m_Size(0), m_Count(0), m_Array(NULL)
	{
	}
	
	~ValuesStack()
	{
		Clear();
	}

	void Clear()
	{
		if (m_Array != NULL)
		{
			free(m_Array);
			m_Array = NULL;
		}
		m_Count = 0;
		m_Size = 0;
	}

	bool Push(const T& Value)
	{
		if (m_Count == m_Size)
		{
			void* NewArray = realloc(m_Array, (m_Size + SizeIncrement) * sizeof(T));
			if (NewArray == NULL) return false;
			m_Array = (T*)NewArray;
			m_Size += SizeIncrement;
		}
		m_Array[m_Count++] = Value;
		return true;
	}

	bool Pop()
	{
		if (m_Count == 0) return false;
		m_Count--;
		return true;
	}

	bool Pop(T& Value)
	{
		if (m_Count == 0) return false;
		Value = m_Array[--m_Count];
		return true;
	}

	bool IsEmpty()
	{
		return (m_Count == 0);
	}

private:
	long	m_Size, m_Count;
	T*		m_Array;
};

typedef struct
{
	int Left, Top;
} TCursorPosition;

class CBisEntryPoint
{
public:
__pragma(warning(push))
__pragma(warning(disable:6031))
__pragma(warning(disable:6308))
	CBisEntryPoint()
	{
		m_FullName = (char*)BisConsoleGetTitle();
		assert(m_FullName != NULL);
		m_PathName = _strdup(m_FullName);
		assert(m_PathName != NULL);
		char* c = strrchr(m_PathName,'\\');
		if (c != NULL) *(c+1) = 0; else *m_PathName = 0;
		m_PathName = (char*)realloc(m_PathName, (strlen(m_PathName)+1) * sizeof(char));
		const char* cc = strrchr(m_FullName,'\\');
		m_FileName = (cc != NULL) ? _strdup(cc+1) : _strdup(m_FullName);
		assert(m_FileName != NULL);
		m_FileName = (char*)realloc(m_FileName, (strlen(m_FileName)+1) * sizeof(char));
		m_CurrentTitle = _strdup(m_FullName);
		assert(m_CurrentTitle != NULL);
		_CrtMemCheckpoint(&m_HeapStatus);
	}
__pragma(warning(pop))
	~CBisEntryPoint()
	{
		_CrtMemDumpAllObjectsSince(&m_HeapStatus);
		#if _MSC_VER <= 1600
		if (m_FullName != NULL) free(m_FullName);
		if (m_PathName != NULL) free(m_PathName);
		if (m_FileName != NULL) free(m_FileName);
		if (m_CurrentTitle != NULL) free(m_CurrentTitle);
		#endif
	}
	const char*	FullName()
	{
		return m_FullName;
	}
	const char*	PathName()
	{
		return m_PathName;
	}
	const char*	FileName()
	{
		return m_FileName;
	}
	const char*	CurrentTitle()
	{
		return m_CurrentTitle;
	}
	bool		CurrentTitle(const char* Source)
	{
		if (Source != NULL)
		{
			void* Result = realloc(m_CurrentTitle, (strlen(Source)+1) * sizeof(char));
			if (Result == NULL) return false;
			m_CurrentTitle = (char*)Result;
			strcpy(m_CurrentTitle,Source);
		}
		char* Title = _strdup(m_CurrentTitle);
		assert(Title != NULL);
		ChangeTitle(Title);
		free(Title);
		return true;
	}
	void		ClearCursorStack()
	{
		m_CursorStack.Clear();
	}
	bool		PushCursor()
	{
		TCursorPosition Position;
		Position.Left = Console::CursorLeft;
		Position.Top = Console::CursorTop;
		return m_CursorStack.Push(Position);
	}
	bool		PopCursor()
	{
		TCursorPosition Position;
		if (!m_CursorStack.Push(Position)) return false;
		Console::CursorLeft = Position.Left;
		Console::CursorTop = Position.Top;
		return true;
	}
private:
	void ChangeTitle(const char* Source)
	{
		String^ SystemString = gcnew String(Source);
		Console::Title = SystemString;
	}
private:
	_CrtMemState					m_HeapStatus;
	char*							m_FullName;
	char*							m_PathName;
	char*							m_FileName;
	char*							m_CurrentTitle;
	ValuesStack<TCursorPosition>	m_CursorStack;
} EntryPoint;

const char* BisConsoleGetFilename(bool WithFullPath)
{
	return (WithFullPath) ? EntryPoint.FullName() : EntryPoint.FileName();
}

const char* BisConsoleGetPath()
{
	return EntryPoint.PathName();
}

const char* BisConsoleGetTitle()
{
	static bool FirstCallFlag = false;
	if (FirstCallFlag == false)
	{
		FirstCallFlag = true;
		String^ SystemString = Console::Title;
		array<Byte>^ Chars = System::Text::Encoding::GetEncoding(1252)->GetBytes(SystemString); // Codepage 1252 = ISO-8859-1
		pin_ptr<Byte> CharsPointer = &(Chars[0]);
		char* NativeCharsPointer = reinterpret_cast<char *>(static_cast<unsigned char *>(CharsPointer));
		char* Target = (char*)malloc((Chars->Length+1) * sizeof(char));
		assert(Target != NULL);
		memcpy(Target, NativeCharsPointer, Chars->Length * sizeof(char));
		Target[Chars->Length] = 0;
		return Target;
	}
	else
	{
		return EntryPoint.CurrentTitle();
	}
}

void BisConsoleClearCursorStack()
{
	EntryPoint.ClearCursorStack();
}

bool BisConsolePushCursor()
{
	return EntryPoint.PushCursor();
}

bool BisConsolePopCursor()
{
	return EntryPoint.PopCursor();
}

void BisConsoleSetTitle(const char* Source)
{
	#ifdef _DEBUG
		Debug::Assert((Source != NULL), "BisConsoleSetTitle >>> paramËtre Source NULL");
	#else
		assert(Source != NULL);
	#endif
	EntryPoint.CurrentTitle(Source);
}

void BisConsoleSetTextColor(ColorCode Color)
{
	Console::ForegroundColor = (System::ConsoleColor)(int)Color;
}

void BisConsoleSetBackColor(ColorCode Color)
{
	Console::BackgroundColor = (System::ConsoleColor)(int)Color;
}

ColorCode BisConsoleGetTextColor()
{
	return (ColorCode)(int)Console::ForegroundColor;
}

ColorCode BisConsoleGetBackColor()
{
	return (ColorCode)(int)Console::BackgroundColor;
}

void BisConsoleClear()
{
	Console::Clear();
}

__pragma(warning(push))
__pragma(warning(disable:6387))
__pragma(warning(disable:6011))
void BisConsoleRead(char* Target)
{
	#ifdef _DEBUG
		Debug::Assert((Target != NULL), "BisConsoleRead >>> paramËtre Target NULL");
	#else
		assert(Target != NULL);
	#endif
	String^ SystemString = Console::ReadLine();
	//caractËres ASCII Ètendus -> ¡¿¬ƒ√·‡‚‰„…» ÀÈËÍÎÕÃŒœÌÏÓÔ”“‘÷’ÛÚÙˆı⁄Ÿ€‹˙˘˚¸›˝ˇ«Á∆Ê'´ª
	array<Byte>^ Chars = System::Text::Encoding::GetEncoding(1252)->GetBytes(SystemString); // Codepage 1252 = ISO-8859-1
	if (Chars->Length > 0)
	{
		pin_ptr<Byte> CharsPointer = &(Chars[0]);
		char* NativeCharsPointer = reinterpret_cast<char *>(static_cast<unsigned char *>(CharsPointer));
		memcpy(Target, NativeCharsPointer, Chars->Length * sizeof(char));
	}
	Target[Chars->Length] = 0;
}
__pragma(warning(pop))

void BisConsoleWrite(const char* Source)
{
	#ifdef _DEBUG
		Debug::Assert((Source != NULL), "BisConsoleWrite >>> paramËtre Source NULL");
	#else
		assert(Source != NULL);
	#endif
	String^ SystemString = gcnew String(Source);
	Console::Write(SystemString);
}

void BisConsoleResize(int Width, int Height)
{
	#ifdef _DEBUG
		Debug::Assert((Width >= 10), "BisConsoleResize >>> paramËtre Width trop petit : un minimum de 10 est requis");
		Debug::Assert((Width >= Console::WindowWidth), "BisConsoleResize >>> paramËtre Width trop petit : il doit Ítre plus grand ou Ègal ‡ " + Console::WindowWidth.ToString());
		Debug::Assert((Width <= 1000), "BisConsoleResize >>> paramËtre Width trop grand : il doit Ítre plus petit ou Ègal ‡ 1000");
	#else
		assert((Width >= 10) && (Width >= Console::WindowWidth) && (Width <= 1000));
	#endif
	#ifdef _DEBUG
		Debug::Assert((Height >= 10), "BisConsoleResize >>> paramËtre Height trop petit : un minimum de 10 est requis");
		Debug::Assert((Height >= Console::WindowHeight), "BisConsoleResize >>> paramËtre Height trop petit : il doit Ítre plus grand ou Ègal ‡ " + Console::WindowHeight.ToString());
		Debug::Assert((Height <= 1000), "BisConsoleResize >>> paramËtre Height trop grand : il doit Ítre plus petit ou Ègal ‡ 1000");
	#else
		assert((Height >= 10) && (Height >= Console::WindowHeight) && (Height <= 1000));
	#endif
	Console::BufferWidth = Width;
	Console::BufferHeight = Height;
}

void BisConsoleWindowResize(int Width, int Height)
{
	#ifdef _DEBUG
		Debug::Assert((Width >= 10), "BisConsoleWindowResize >>> paramËtre Width trop petit : un minimum de 10 est requis");
		Debug::Assert((Width <= Console::BufferWidth), "BisConsoleWindowResize >>> paramËtre Width trop grand : il doit Ítre plus petit ou Ègal ‡ " + Console::BufferWidth.ToString());
		Debug::Assert((Width <= Console::LargestWindowWidth), "BisConsoleWindowResize >>> paramËtre Width trop grand : il doit Ítre plus petit ou Ègal ‡ " + Console::LargestWindowWidth.ToString());
	#else
		assert((Width >= 10) && (Width <= Console::BufferWidth) && (Width <= Console::LargestWindowWidth));
	#endif
	#ifdef _DEBUG
		Debug::Assert((Height >= 10), "BisConsoleWindowResize >>> paramËtre Height trop petit : un minimum de 10 est requis");
		Debug::Assert((Height <= Console::BufferHeight), "BisConsoleWindowResize >>> paramËtre Height trop grand : il doit Ítre plus petit ou Ègal ‡ " + Console::BufferHeight.ToString());
		Debug::Assert((Height <= Console::LargestWindowHeight), "BisConsoleWindowResize >>> paramËtre Height trop grand : il doit Ítre plus petit ou Ègal ‡ " + Console::LargestWindowHeight.ToString());
	#else
		assert((Height >= 10) && (Height <= Console::BufferHeight) && (Height <= Console::LargestWindowHeight));
	#endif
	Console::WindowWidth = Width;
	Console::WindowHeight = Height;
}

int BisConsoleGetWindowWidth()
{
	return (int)Console::WindowWidth;
}

int BisConsoleGetWindowHeight()
{
	return (int)Console::WindowHeight;
}

int BisConsoleGetWidth()
{
	return (int)Console::BufferWidth;
}

int BisConsoleGetHeight()
{
	return (int)Console::BufferHeight;
}

int BisGetCh()
{
	ConsoleKeyInfo Info = Console::ReadKey(true);
	return (int)Info.KeyChar;
}

int BisGetChE()
{
	ConsoleKeyInfo Info = Console::ReadKey(false);
	return (int)Info.KeyChar;
}


///////////////////////////
// Fonctions utilitaires //
///////////////////////////

// Code rÈcupÈrÈ d'Internet et un peu modifiÈ ...
// >>>
#if _MSC_VER <= 1600
__pragma(warning(push))
__pragma(warning(disable:4793))
int vsscanf(const char *str, const char *p_format, va_list arg_list)
{
	char *nformat = _strdup(p_format);
	char *format = nformat;
	int i;
	int n=0;
	int convtot=0;
	for (i=0; format[i]; i++)
	{
		if (format[i] == '%')
		{
			if (format[i+1] == '%' || format[i+1] == '*' || format[i+1] == '\0')
				i++; // pas comptÈ comme variable ‡ allouer, je saute
			else
			{
				// c'est une variable
				if (n==0) // premiËre variable: OK
					n++;
				else
				{ // deuxiËme variable: on coupe juste avant
					char f[3];
					f[1]=format[i+1];
					f[2]=format[i+2];
					format[i+1]='n';
					format[i+2]='\0';
					// %n = nombre de caractËres lus dans l'entrÈe
					void* p = va_arg(arg_list, void* );
					int lu=-1,conv;
					//conv = sscanf_s(str, format, p, &lu);
					conv = sscanf(str, format, p, &lu);
					if (lu==-1)
					{ // Èchec ‡ la conversion
						convtot += conv; // peut-Ítre converti quand mÍme une variable?
						break; // mais ensuite on arrÍte
					}
					convtot++; // une variable lue
					str += lu; // avancer dans l'entrÈe
					format[i+1]=f[1];
					format[i+2]=f[2]; // rÈtablir la chaÓne de format
					format += i;
					i = -1; // avancer dans le format
					n=0; // on repart avec 0 variable dÈtectÈe dans la nouvelle chaÓne
				}
			}
		}
	}
	if ((format[i]=='\0') && (n>0))
	{ 
		// on est arrivÈ au bout, et il reste une variable ‡ convertir
		void* p = va_arg(arg_list, void* );
		int conv;
		//conv = sscanf_s(str, format, p);
		conv = sscanf(str, format, p);
		convtot += conv;
	}
	free(nformat);
	return convtot;
}
__pragma(warning(pop))
#endif
// <<<
