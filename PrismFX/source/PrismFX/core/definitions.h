#pragma once

#include "PrismFX/pfx_pch.h"



namespace PFX
{
	enum class RenderAPI
	{
		None = 0, OpenGL = 1 // For now it's just opengl
	};

	enum class WindowAPI
	{
		None = 0, GLFW = 1 // For now it's just GLFW
	};

	enum WindowFlag : uint8_t
	{
		WINDOW_FLAG_NONE = 0,
		WINDOW_FLAG_NOT_RESIZABLE = BIT(0),
		WINDOW_FLAG_NO_TITLEBAR = BIT(1),
	};
	using WindowFlags = uint16_t;

	enum class WindowMode
	{
		WINDOWED = 0,
		FULLSCREEN,
		BORDERLESS
	};

	struct PFX_API WindowCreateInfo
	{
		std::string Title = "PrismFX App";
		uint32_t Width = 800;
		uint32_t Height = 600;
		WindowMode Mode = WindowMode::WINDOWED;
		WindowFlags Flags = WINDOW_FLAG_NONE;
	};

	enum class CursorMode
	{
		HIDDEN = 0, DISABLED, NORMAL
	};
}