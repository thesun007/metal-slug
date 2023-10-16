#ifndef __DEBUG_HPP__
#define __DEBUG_HPP__

#ifdef _DEBUG
#pragma warning(disable : 4996)
#ifndef _WINDOWS_
#include <Windows.h>
#endif
#ifndef _INC_STRING
#include <string.h>
#endif

class __errfind__
{
public:
__errfind__(const std::string& file, const std::string& func):_file(file),_func(func) 
{
 _file = _file.substr(_file.rfind('\\') + 1, _file.length());
 OutputDebugStringA("File [ ");
 OutputDebugStringA(_file.c_str());
 OutputDebugStringA(" ] Function [ ");
 OutputDebugStringA(_func.c_str());
 OutputDebugStringA(" ] Entry \n");
}
~__errfind__() 
{
 OutputDebugStringA("File [ ");
 OutputDebugStringA(_file.c_str());
 OutputDebugStringA(" ] Function [ ");
 OutputDebugStringA(_func.c_str());
 OutputDebugStringA(" ] Exit \n");
}
void __stdcall __errlinecheck__(const int& line)
{
 char _line[32];
 itoa(line, _line, 10);
 OutputDebugStringA("File [ ");
 OutputDebugStringA(_file.c_str());
 OutputDebugStringA(" ] Function [ ");
 OutputDebugStringA(_func.c_str());
 OutputDebugStringA(" ] Line [ ");
 OutputDebugStringA(_line);
 OutputDebugStringA(" ]\n");
}
private: std::string _file, _func;
};
#define DEBUG_ENTRY_EXIT __errfind__ __errfindcheckclass__(__FILE__, __FUNCTION__)
#define DEBUG_LINE __errfindcheckclass__.__errlinecheck__(__LINE__)

#include <stdarg.h>
#include <stdio.h>

class __debugclass
{
private:
	HANDLE _hconsole;
	char _tempa[256];
	wchar_t _tempw[256];
public:
	static __debugclass** _getinst()
	{
		static __debugclass* hInst = 0;
		if (hInst == 0)
			hInst = new __debugclass;
		return &hInst;
	}
	static void __destroy()
	{
		__debugclass** hInst = _getinst();
		if (*hInst != 0)
		{
			delete *hInst;
			*hInst = 0;
		}
	}
	void __createconsole()
	{
		if (AllocConsole() == false)
			return;
		_hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if (_hconsole == INVALID_HANDLE_VALUE)
			FreeConsole();
	}
#ifdef _UNICODE
	void __writew(wchar_t* str, ...)
	{
		va_list ap;
		va_start(ap, str);
		vswprintf_s(_tempw, str, ap);
		va_end(ap);
		DWORD dwByte;
		::WriteConsole(_hconsole, _tempw, wcslen(_tempw), &dwByte, 0);
		::WriteConsole(_hconsole, L"\n", wcslen(L"\n"), &dwByte, 0);
	}
#else
	void __writea(char* str, ...)
	{
		va_list ap;
		va_start(ap, str);
		vsprintf_s(_tempa, str, ap);
		va_end(ap);
		DWORD dwByte;
		::WriteConsole(_hconsole, _tempa, strlen(_tempa), &dwByte, 0);
		::WriteConsole(_hconsole, "\n", strlen("\n"), &dwByte, 0);
	}
#endif
	void __clear()
	{
		if(_hconsole == 0)
			return;
		COORD Pos = {0, 0};
		DWORD dwByte;
		FillConsoleOutputCharacter(_hconsole, (TCHAR) ' ', 200 * 200, Pos, &dwByte );
		SetConsoleCursorPosition(_hconsole, Pos);
	}
private: __debugclass(){_hconsole = 0;}
public: ~__debugclass(){FreeConsole();CloseHandle(_hconsole);}
};

#define CREATE_DEBUG_CONSOLE (*__debugclass::_getinst())->__createconsole()
#define DESTROY_DEBUG_CONSOLE (__debugclass::__destroy())
#define DebugLogClear (*__debugclass::_getinst())->__clear()
#ifdef _UNICODE
#define DebugLogW(str, ...) (*__debugclass::_getinst())->__writew(str, __VA_ARGS__)
#define DebugLog DebugLogW
#else
#define DebugLogA(str, ...) (*__debugclass::_getinst())->__writea(str, __VA_ARGS__)
#define DebugLog DebugLogA
#endif

#else
#define DEBUG_ENTRY_EXIT
#define DEBUG_LINE
#define CREATE_DEBUG_CONSOLE 
#define DESTROY_DEBUG_CONSOLE
#define DebugLogClear
#define DebugLogW(str, ...)
#define DebugLogA(str, ...)
#define DebugLog(str, ...)
#endif

#endif