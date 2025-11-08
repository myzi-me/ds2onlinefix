#include "mem/memory.h"
#include "framework.h"

void null_buffer(void* dst, size_t size) {
	memset(dst, 0x00, size);
}

bool write_protected_buffer(void* dst, void* src, size_t size) {
	DWORD old_protect;
	if (VirtualProtect(dst, sizeof(dst), PAGE_EXECUTE_READWRITE, &old_protect)) {
		memcpy(dst, src, size);
		if (VirtualProtect(dst, sizeof(dst), old_protect, &old_protect)) {
			return true;
		}
	}

	RUNTIME_ERROR("Failed to write protected buffer");
	return false;
}

uint16_t swap_endian(uint16_t x) {
	return (x << 8) | (x >> 8);
}