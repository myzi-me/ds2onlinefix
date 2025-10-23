#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include "framework.h"
#include "frpg2/frpg2sv.h"
#include "mem/hook.h"
#include "xinput/xinput1_3.h"

void enable_console() {
#if DEBUG
    AllocConsole();
    FILE* pFile;
    freopen_s(&pFile, "CONIN$", "r", stdin);
    freopen_s(&pFile, "CONOUT$", "w", stderr);
    freopen_s(&pFile, "CONOUT$", "w", stdout);
#endif
}

void ds2_online_fix_main() {
    enable_console();
    load_xinput();
    pre_hooks();
    init_frpg2sv_hooks();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        ds2_online_fix_main();
        break;

    case DLL_THREAD_ATTACH:
        break;

    case DLL_THREAD_DETACH:
        break;

    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}