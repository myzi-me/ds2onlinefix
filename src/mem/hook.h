#pragma once

void pre_hooks();
bool call_hook(void* src, void* dst);
bool jmp_hook(void* src, void* dst);
void* vt_hook(void* src, void* dst);