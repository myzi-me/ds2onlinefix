#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <Winternl.h>
#include <cstdint>

void null_buffer(void* dst, size_t size);
bool write_protected_buffer(void* dst, void* src, size_t size);

#define OFBASE(rel) reinterpret_cast<void*>(*reinterpret_cast<uint64_t*>(reinterpret_cast<uint64_t>(NtCurrentTeb()->ProcessEnvironmentBlock) + 0x10) + static_cast<uint64_t>(rel))
#define DEF_FUNC(name, addr, ret, params) auto name = reinterpret_cast<ret(__fastcall*) ## params>(addr);
#define DEC_FUNC(name, addr, ret, params) auto name = reinterpret_cast<ret(__fastcall*) ## params>(nullptr);
#define INIT_FUNC(name, addr) name = reinterpret_cast<decltype(name)>(addr);