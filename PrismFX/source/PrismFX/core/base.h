#pragma once

#if defined(PFX_PLATFORM_WINDOWS)
	#if defined(PFX_BUILD)
		#define PFX_API __declspec(dllexport)
	#else
		#define PFX_API __declspec(dllimport)
	#endif
#elif defined(PFX_PLATFORM_UNIX)
	#if defined(PFX_BUILD)
		#define PFX_API __attribute__((visibility("default")))
	#else
		#define PFX_API
	#endif
#else
	//#error Currently only supports Windows and Linux
	#define PFX_API
#endif
