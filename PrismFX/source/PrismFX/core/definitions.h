#pragma once

#include "PrismFX/pfx_pch.h"



namespace PFX
{
	enum class RenderAPI
	{
		None = 0, OpenGL = 1 // For now it's just opengl
	};

	enum WindowFlag : uint8_t
	{
		WINDOW_FLAG_NONE = 0,
		WINDOW_FLAG_NOT_RESIZABLE = BIT(0),
		WINDOW_FLAG_NO_TITLEBAR = BIT(1),
		WINDO_FLAG_FULLSCREEN = BIT(2),
		WINDOW_FLAG_BORDERLESS = BIT(3)
	};
	using WindowFlags = uint16_t;

	struct PFX_API WindowCreateInfo
	{
		std::string Title = "PrismFX App";
		uint32_t Width = 800;
		uint32_t Height = 600;
		WindowFlags Flags = WINDOW_FLAG_NONE;
	};

	enum class CursorMode
	{
		HIDDEN = 0, DISABLED, NORMAL
	};
}