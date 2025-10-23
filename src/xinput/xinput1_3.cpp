#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include "framework.h"
#include "xinput/xinput1_3.h"

LPCSTR xinput_import_names[] = { 
	"DllMain", 
	"XInputGetState",
	"XInputSetState",
	"XInputGetCapabilities",
	"XInputEnable",
	"XInputGetDSoundAudioDeviceGuids",
	"XInputGetBatteryInformation", 
	"XInputGetKeystroke", 
	(LPCSTR)100, 
	(LPCSTR)101, 
	(LPCSTR)102, 
	(LPCSTR)103 
};

extern "C" UINT_PTR xinput_imports[12] = { 0 };

static_assert(sizeof(xinput_import_names) == sizeof(xinput_imports), "Import count mismatch");

BOOL load_xinput() {
	char dll_path[MAX_PATH];
	GetSystemDirectoryA(dll_path, MAX_PATH);

	strcat_s(dll_path, "\\xinput1_3.dll");
	HMODULE	loaded_dll = LoadLibraryA(dll_path);

	if (loaded_dll == NULL)  {
		RUNTIME_ERROR("Failed to load original xinput1_3.dll");
		return false;
	}

	for (int i = 0; i < (sizeof(xinput_imports) / sizeof(UINT_PTR)); i++) {
		xinput_imports[i] = (UINT_PTR)GetProcAddress(loaded_dll, xinput_import_names[i]);

		if (!xinput_imports[i]) {
			RUNTIME_ERROR("Failed to load xinput1_3.dll import");
			return false;
		}
	}

	DEBUG_LOG("Loaded original xinput1_3.dll");
	return true;
}