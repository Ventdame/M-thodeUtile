#ifndef BIS_CONSOLE_HEADER
#define BIS_CONSOLE_HEADER


// Include some standard ANSI libraries
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <search.h>
#include <crtdbg.h>


// Declare some BisConsole constants and miscelleanous enumarations

enum ColorCode { Black=0, DarkBlue, DarkGreen, DarkCyan, DarkRed, DarkMagenta, DarkYellow, Gray, DarkGray, Blue, Green, Cyan, Red, Magenta, Yellow, White };


// Declare some BisConsole global functions relative to the console managment
void		BisConsoleResize(int Width, int Height);
void		BisConsoleWindowResize(int Width, int Height);
void		BisConsoleWrite(const char* Source);
void		BisConsoleRead(char* Target);
const char*	BisConsoleGetTitle();
void		BisConsoleSetTitle(const char* Source);
const char*	BisConsoleGetFilename(bool WithFullPath=true);
const char*	BisConsoleGetPath();
void		BisConsoleSetTextColor(ColorCode Color);
void		BisConsoleSetBackColor(ColorCode Color);
ColorCode	BisConsoleGetTextColor();
ColorCode	BisConsoleGetBackColor();
void		BisConsoleClear();
void		BisConsoleClearCursorStack();
bool		BisConsolePushCursor();
bool		BisConsolePopCursor();
int			BisConsoleGetWindowWidth();
int			BisConsoleGetWindowHeight();
int			BisConsoleGetWidth();
int			BisConsoleGetHeight();


// Declare some BisConsole global functions relative to the I/O console
int __cdecl	BisPrintF(const char* Format, ...);
int __cdecl	BisScanF(const char* Format, ...);
int			BisGetCh();
int			BisGetChE();
char*		BisGetS(char* Target);


// Declare some BisConsole global functions relative to the string managment
void*		BisRealloc(void* Pointer, size_t Size);
char*		BisStringCopy(char* Target, const char* Source);
char*		BisStringCopyN(char* Target, const char* Source, long Size);
char*		BisStringConcat(char* Target, const char* Source);
int __cdecl	BisSPrintF(char* Target, const char* Format, ...);
int			BisStringCompareI(const char* Source1, const char* Source2);
int			BisStringCompareNI(const char* Source1, const char* Source2, size_t MaxCount);


// Declare some BisConsole global functions relative to the file managment
FILE*		BisFOpen(const char* filename, const char* mode);


// Standard redefines
#undef		getch
#define		getch					BisGetCh

#undef		getche
#define		getche					BisGetChE

#undef		gets
#define		gets					BisGetS

#undef		printf
#define		printf					BisPrintF

#undef		scanf
#define		scanf					BisScanF

#undef		strcpy
#define		strcpy					BisStringCopy

#undef		strncpy
#define		strncpy					BisStringCopyN

#undef		strcat
#define		strcat					BisStringConcat

#undef		stricmp
#define		stricmp					BisStringCompareI

#undef		strnicmp
#define		strnicmp				BisStringCompareNI

#undef		sprintf
#define		sprintf					BisSPrintF

#undef		sscanf
#define		sscanf					sscanf_s

#undef		fopen
#define		fopen					BisFOpen

#ifndef _KEEP_STD_REALLOC
#undef		realloc
#define		realloc					BisRealloc
#endif

// Specific redefines
#define		console_resize				BisConsoleResize
#define		console_window_resize		BisConsoleWindowResize
#define		console_set_title			BisConsoleSetTitle
#define		console_get_title			BisConsoleGetTitle
#define		console_get_filename		BisConsoleGetFilename
#define		console_get_path			BisConsoleGetPath
#define		console_set_textcolor		BisConsoleSetTextColor
#define		console_set_backcolor		BisConsoleSetBackColor
#define		console_get_textcolor		BisConsoleGetTextColor
#define		console_get_backcolor		BisConsoleGetBackColor
#define		console_clear				BisConsoleClear
#define		console_clear_cursor_stack	BisConsoleClearCursorStack
#define		console_push_cursor			BisConsolePushCursor
#define		console_pop_cursor			BisConsolePopCursor
#define		console_get_window_width	BisConsoleGetWindowWidth
#define		console_get_window_height	BisConsoleGetWindowHeight
#define		console_get_width			BisConsoleGetWidth
#define		console_get_height			BisConsoleGetHeight


#endif//BIS_CONSOLE_HEADER
