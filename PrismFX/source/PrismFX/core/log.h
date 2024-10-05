#pragma once

#include "PrismFX/core/base.h"

// Lib
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>



namespace PFX
{
	class PFX_API Log
	{
		public:
			static void Init();

			inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
			inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

		private:
			static std::shared_ptr<spdlog::logger> s_CoreLogger;
			static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};


	#ifndef PFX_DISABLE_LOG
		// Core log macros
		#define PFX_CORE_TRACE(...)   	PFX::Log::GetCoreLogger()->trace(__VA_ARGS__);
		#define PFX_CORE_INFO(...)    	PFX::Log::GetCoreLogger()->info(__VA_ARGS__);
		#define PFX_CORE_WARN(...)    	PFX::Log::GetCoreLogger()->warn(__VA_ARGS__);
		#define PFX_CORE_ERROR(...)   	PFX::Log::GetCoreLogger()->error(__VA_ARGS__);
		#define PFX_CORE_CRITICAL(...)	PFX::Log::GetCoreLogger()->critical(__VA_ARGS__);

		// Client log macros
		#define PFX_TRACE(...)			PFX::Log::GetClientLogger()->trace(__VA_ARGS__);
		#define PFX_INFO(...)	      	PFX::Log::GetClientLogger()->info(__VA_ARGS__);
		#define PFX_WARN(...)			PFX::Log::GetClientLogger()->warn(__VA_ARGS__);
		#define PFX_ERROR(...)			PFX::Log::GetClientLogger()->error(__VA_ARGS__);
		#define PFX_CRITICAL(...)		PFX::Log::GetClientLogger()->critical(__VA_ARGS__);
	#else
		// Core log macros
		#define PFX_CORE_TRACE(...)
		#define PFX_CORE_INFO(...)
		#define PFX_CORE_WARN(...)
		#define PFX_CORE_ERROR(...)
		#define PFX_CORE_CRITICAL(...)

		// Client log macros
		#define PFX_TRACE(...)
		#define PFX_INFO(...)
		#define PFX_WARN(...)
		#define PFX_ERROR(...)
		#define PFX_CRITICAL(...)
	#endif

} // PFX