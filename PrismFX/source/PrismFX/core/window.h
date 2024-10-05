#pragma once

#include "PrismFX/pfx_pch.h"

#include "PrismFX/core/base.h"
#include "PrismFX/events/event.h"
#include "PrismFX/core/definitions.h"



namespace PFX
{
	// Interface representing a desktop system based Window
	class PFX_API Window
	{
		public:
			using EventCallbackFn = std::function<void(Event&)>;

			virtual ~Window() {}

			virtual void OnUpdate() = 0;

			virtual uint32_t GetWidth() const = 0;
			virtual uint32_t GetHeight() const = 0;

			// Window attributes
			virtual void SetEventCallback(const EventCallbackFn& p_callback) = 0;
			virtual void SetVsync(bool p_enabled) = 0;
			virtual bool IsVsync() const = 0;

			virtual void* GetNativeWindow() const = 0;

			virtual void SetCursorMode(CursorMode p_mode) = 0;

			static Window* Create(const WindowCreateInfo& p_info = WindowCreateInfo());
	};

}