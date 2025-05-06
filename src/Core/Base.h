#pragma once

// #include "Hazel/Core/PlatformDetection.h"

#include "pch.h"

// #ifdef VG_PLATFORM_WINDOWS
//     #ifdef VG_DLL_EXPORT
//         #define VG_DLL_API __declspec(dllexport)  // Exporting symbol for the DLL
//     #else
//         #define VG_DLL_API __declspec(dllimport)  // Importing symbol for using the DLL
//     #endif
// #else
//     #error Jerky only supports Windows
// #endif

// #ifdef VG_DEBUG
// 	#if defined(VG_PLATFORM_WINDOWS)
// 		#define VG_DEBUGBREAK() __debugbreak()
// 	#elif defined(VG_PLATFORM_LINUX)
// 		#include <signal.h>
// 		#define VG_DEBUGBREAK() raise(SIGTRAP)
// 	#else
// 		#error "Platform doesn't support debugbreak yet!"
// 	#endif
// 	#define VG_ENABLE_ASSERTS
// #else
// 	#define VG_DEBUGBREAK()
// #endif

#define VG_EXPAND_MACRO(x) x
#define VG_STRINGIFY_MACRO(x) #x

// #define VG_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Voyager {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}
