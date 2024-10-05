#pragma once

#include "PrismFX/core/log.h"
#include <filesystem>


#define PFX_EXPAND_MACRO(x) x
#define PFX_STRINGIFY_MACRO(x) #x


#if defined(_WIN32) && defined(_MSC_VER)
	#define PFX_DEBUGBREAK() __debugbreak()
#else
	#if defined(__linux__) && (defined(__GNUC__) || defined(__clang__))
		#include <signal.h>
		#if defined(__i386__) || defined(__x86_64__)
			#define PFX_DEBUGBREAK() __asm__ volatile("int3")
		#elif defined(__aarch64__) || defined(__arm__)
			#define PFX_DEBUGBREAK() __builtin_trap()
		#else
			#include <csignal>
		#endif

		#if defined(SIGTRAP)
			#define PFX_DEBUGBREAK() raise(SIGTRAP)
		#else
			#define PFX_DEBUGBREAK() raise(SIGABRT)
		#endif
	#else
		#error Currently only support windows (msvc) and linux (gcc/clang)!
	#endif
#endif


#define PFX_ENABLE_ASSERTS
#define PFX_ENABLE_VERIFY


#ifdef PFX_ENABLE_ASSERTS
	#define PFX_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { PFX##type##ERROR(msg, __VA_ARGS__); PFX_DEBUGBREAK(); } }
	#define PFX_INTERNAL_ASSERT_WITH_MSG(type, check, ...) PFX_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define PFX_INTERNAL_ASSERT_NO_MSG(type, check) PFX_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", PFX_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define PFX_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define PFX_INTERNAL_ASSERT_GET_MACRO(...) PFX_EXPAND_MACRO( PFX_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, PFX_INTERNAL_ASSERT_WITH_MSG, PFX_INTERNAL_ASSERT_NO_MSG) )

	// the first argument is the condition and the second is the message fmt (optional)
	// and the rest is the va args  (optional)
	#define PFX_ASSERT(...) PFX_EXPAND_MACRO( PFX_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	// the first argument is the condition and the second is the message fmt (optional)
	// and the rest is the va args  (optional)
	#define PFX_CORE_ASSERT(...) PFX_EXPAND_MACRO( PFX_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	// the first argument is the condition and the second is the message fmt (optional)
	// and the rest is the va args  (optional)
	#define PFX_ASSERT(...)
	// the first argument is the condition and the second is the message fmt (optional)
	// and the rest is the va args  (optional)
	#define PFX_CORE_ASSERT(...)
#endif

#ifdef PFX_ENABLE_VERIFY
	#define PFX_INTERNAL_VERIFY_IMPL(type, check, msg, ...) { if(!(check)) { PFX##type##ERROR(msg, __VA_ARGS__); PFX_DEBUGBREAK(); } }
	#define PFX_INTERNAL_VERIFY_WITH_MSG(type, check, ...) PFX_INTERNAL_VERIFY_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define PFX_INTERNAL_VERIFY_NO_MSG(type, check) PFX_INTERNAL_VERIFY_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", PFX_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define PFX_INTERNAL_VERIFY_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define PFX_INTERNAL_VERIFY_GET_MACRO(...) PFX_EXPAND_MACRO( PFX_INTERNAL_VERIFY_GET_MACRO_NAME(__VA_ARGS__, PFX_INTERNAL_VERIFY_WITH_MSG, PFX_INTERNAL_VERIFY_NO_MSG) )

	// the first argument is the condition and the second is the message fmt (optional)
	// and the rest is the va args  (optional)
	#define PFX_VERIFY(...) PFX_EXPAND_MACRO( PFX_INTERNAL_VERIFY_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	// the first argument is the condition and the second is the message fmt (optional)
	// and the rest is the va args  (optional)
	#define PFX_CORE_VERIFY(...) PFX_EXPAND_MACRO( PFX_INTERNAL_VERIFY_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	// the first argument is the condition and the second is the message fmt (optional)
	// and the rest is the va args  (optional)
	#define PFX_VERIFY(...)
	// the first argument is the condition and the second is the message fmt (optional)
	// and the rest is the va args  (optional)
	#define PFX_CORE_VERIFY(...)
#endif