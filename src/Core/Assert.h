#pragma once

#if defined(_MSC_VER)
    #include <intrin.h>
    #define DEBUG_BREAK() __debugbreak()
#elif defined(__GNUC__) || defined(__clang__)
    #include <signal.h>
    #define DEBUG_BREAK() __builtin_trap()  // or use __builtin_trap() if preferred
#else
    #define DEBUG_BREAK() ((void)0)  // fallback
#endif


#ifdef VG_ENABLE_ASSERTS // assert does not check other args when false, while validation runs code regardless of type
    #include "Log.h"
    #define VG_ASSERT(x, ...) { if(!(x)) { VG_ERROR("Assertion failed: {0}", __VA_ARGS__); DEBUG_BREAK(); } }
    #define VG_CORE_ASSERT(x, ...) { if(!(x)) { VG_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); DEBUG_BREAK(); } }
#else
    #define VG_ASSERT(x, ...)
    #define VG_CORE_ASSERT(x, ...)
#endif
