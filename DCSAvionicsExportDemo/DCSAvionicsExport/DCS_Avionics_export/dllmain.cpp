// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "stdio.h"
#define CONSOLE_ENABLED
FILE* stream;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
#ifdef CONSOLE_ENABLED //Console commented out
        if (AllocConsole())
        {
            freopen_s(&stream, "CONOUT$", "w", stdout);
            SetConsoleTitle((L"DCS Avionics export Debug Console"));
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
#endif
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

