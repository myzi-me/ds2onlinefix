#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include "framework.h"
#include "frpg2/frpg2sv_cache.h"
#include "mem/memory.h"

// ip char[16] + port uint16
#define CACHE_FILE_NAME "ds2onlinefix.cache"
#define CACHE_FILE_SIZE 18

struct ServerRedirectCache {
    char server_ip[16];
    uint16_t server_port;

    ServerRedirectCache() {
        null_buffer(&server_ip[0], sizeof(server_ip));
        server_port = 0;
    }
};

bool write_cache(const char* ip, uint16_t port) {
    ServerRedirectCache cache_data;

    strncpy(cache_data.server_ip, ip, 16);
    cache_data.server_port = port;

    HANDLE new_cache_file = CreateFileA(CACHE_FILE_NAME, GENERIC_READ | GENERIC_WRITE, 0,
        NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (new_cache_file == INVALID_HANDLE_VALUE) {
        return false;
    }

    if (!WriteFile(new_cache_file, &cache_data, sizeof(cache_data), NULL, NULL)) {
        DEBUG_LOG("Failed to write login cache: %lu", GetLastError());
    };

    CloseHandle(new_cache_file);

    return true;
}


// out_ip needs to be 16 bytes
bool get_cache(char* out_ip, uint16_t* out_port) {
    HANDLE cache_file = CreateFileA(CACHE_FILE_NAME, GENERIC_READ, 0,
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (cache_file == INVALID_HANDLE_VALUE) {
        DEBUG_LOG("Failed to open login cache: %lu", GetLastError());
        return false;
    }

    ServerRedirectCache cache_data;
    DWORD file_size = 0;
    if (!ReadFile((HANDLE)cache_file, &cache_data, sizeof(cache_data), &file_size, NULL)) {
        DEBUG_LOG("Failed to read login cache: %lu", GetLastError());
        CloseHandle((HANDLE)cache_file);
        return false;
    };

    if (file_size != CACHE_FILE_SIZE) {
        DEBUG_LOG("Invalid login cache file size: %lu", GetLastError());
        CloseHandle((HANDLE)cache_file);
        return false;
    }

    strncpy(out_ip, cache_data.server_ip, 16);
    *out_port = cache_data.server_port;

    CloseHandle((HANDLE)cache_file);

    return true;
}

static_assert(sizeof(ServerRedirectCache) == CACHE_FILE_SIZE, "Struct size mismatch");