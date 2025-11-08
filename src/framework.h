#pragma once
#include <cstdio>
#include <cstdlib>
#include <stdexcept>

#ifndef NDEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

// uses login server as game server if 0
// caches game server ip and port to file if 1
#define USE_IP_CACHE 0

#define FORCEINLINE __forceinline
#define FORCENOINLINE __declspec(noinline)
#define DLL_EXPORT __declspec(dllexport)

#if DEBUG
#define DEBUG_LOG(fmt, ...) \
    fprintf(stderr, fmt "\n", \
        ##__VA_ARGS__);

#define RUNTIME_ERROR(log) \
	DEBUG_LOG(log); \
	throw std::runtime_error(log);
#else
#define DEBUG_LOG(fmt, ...)
#define RUNTIME_ERROR(str) throw std::runtime_error("An error has occured")
#endif