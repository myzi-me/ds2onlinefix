#pragma once
#include <cstdint>

bool get_cache(char* out_ip, uint16_t* out_port);
bool write_cache(const char* ip, uint16_t port);