#include "mem/hook.h"
#include "framework.h"
#include "mem/memory.h"
#include "MinHook.h"

#define JMP_OP 0xE9
#define CALL_OP 0xE8

void pre_hooks() {
	if (MH_Initialize() != MH_OK) {
		RUNTIME_ERROR("Failed to init MinHook");
	}
}

bool call_hook(void* src, void* dst) {
	if (MH_CreateHook(src, dst, nullptr) == MH_OK) {
		if (MH_EnableHook(src) == MH_OK) {
			uint8_t call_op = CALL_OP;
			if (write_protected_buffer(src, &call_op, sizeof(call_op))) {
				return true;
			}
		}
	}

	RUNTIME_ERROR("Failed to init call hook");
	return false;
}

bool jmp_hook(void* src, void* dst) {
	if (MH_CreateHook(src, dst, nullptr) == MH_OK) {
		if (MH_EnableHook(src) == MH_OK) {
			return true;
		}
	}

	RUNTIME_ERROR("Failed to init jmp hook");
	return false;
}

void* vt_hook(void* src, void* dst) {
	void* old = *reinterpret_cast<void**>(src);
	if (!write_protected_buffer(src, &dst, sizeof(src))) {
		RUNTIME_ERROR("Failed to init vt hook");
		return nullptr;
	}
	return old;
}