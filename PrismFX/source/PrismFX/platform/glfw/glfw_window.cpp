#include "PrismFX/pfx_pch.h"
#include "PrismFX/platform/glfw/glfw_window.h"

#include "PrismFX/events/application_event.h"
#include "PrismFX/events/mouse_event.h"
#include "PrismFX/events/key_event.h"




namespace PFX
{
	struct Flag
	{
		WindowFlag Flag;
		int Hint;
		int Value;
	};
	static const std::vector<Flag> s_WindowFlags = {
		{WINDOW_FLAG_NO_TITLEBAR, GLFW_DECORATED, GLFW_FALSE},
		{WINDOW_FLAG_NOT_RESIZABLE, GLFW_RESIZABLE, GLFW_FALSE},
	};


	namespace Utils
	{
		int CursorModeToGLFWCursorMode(CursorMode p_mode)
		{
			switch (p_mode)
			{
				case PFX::CursorMode::HIDDEN:   return GLFW_CURSOR_HIDDEN;
				case PFX::CursorMode::DISABLED: return GLFW_CURSOR_DISABLED;
				case PFX::CursorMode::NORMAL:   return GLFW_CURSOR_NORMAL;
			}

			PFX_CORE_ERROR("Unknown cursor mode!")
			return 0;
		}
	}

	static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int p_error, const char* p_description)
	{
		PFX_CORE_ERROR("GLFW Error ({0}): {1}", p_error, p_description)
	}

	GLFWWindow::GLFWWindow(const WindowCreateInfo& p_info)
	{
		Init(p_info);
	}

	GLFWWindow::~GLFWWindow()
	{
		Shutdown();
	}

	void GLFWWindow::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffer();
	}

	void GLFWWindow::SetCursorMode(CursorMode p_mode)
	{
		int mode = Utils::CursorModeToGLFWCursorMode(p_mode);
		if (mode != 0)
			glfwSetInputMode(m_Window, GLFW_CURSOR, mode);
	}

	void GLFWWindow::Init(const WindowCreateInfo& p_info)
	{
		m_Data.Title = p_info.Title;
		m_Data.Width = p_info.Width;
		m_Data.Height = p_info.Height;

		PFX_CORE_INFO("Creating window {0} ({1}, {2})", p_info.Title, p_info.Width, p_info.Height);

		if (s_GLFWWindowCount == 0)
		{
			int success = glfwInit();
			PFX_CORE_ASSERT(success, "Could not initialize glfw!");
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		for (const auto& flag : s_WindowFlags)
		{
			if (p_info.Flags & flag.Flag)
			{
				glfwWindowHint(flag.Hint, flag.Value);
			}
		}

		m_Window = glfwCreateWindow((int)p_info.Width, (int)p_info.Height, m_Data.Title.c_str(), nullptr, nullptr);
		PFX_CORE_ASSERT(m_Window, "Could not create the window!");
		m_Context = GraphicsContext::Create(m_Window);
		m_Context->Init();
		++s_GLFWWindowCount;

		glfwSetWindowUserPointer(m_Window, &m_Data);

		// Set GLFW callbacks
		// ===============================================================

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* p_window, int p_width, int p_height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_window);
			data.Width = p_width;
			data.Height = p_height;

			WindowResizeEvent event(p_width, p_height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* p_window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* p_window, int p_key, int p_scancode, int p_action, int p_mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_window);

			switch (p_action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(p_key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(p_key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(p_key, true);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* p_window, int p_button, int p_action, int p_mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_window);

			switch (p_action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(p_button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(p_button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* p_window, double p_xoffset, double p_yoffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_window);

			MouseScrolledEvent event((float)p_xoffset, (float)p_yoffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* p_window, double p_xpos, double p_ypos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_window);

			MouseMovedEvent event((float)p_xpos, (float)p_ypos);
			data.EventCallback(event);
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* p_window, unsigned int p_keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_window);

			KeyTypedEvent event(p_keycode);
			data.EventCallback(event);
		});

		glfwSetDropCallback(m_Window, [](GLFWwindow* p_window, int p_path_count, const char* p_paths[])
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_window);

			std::vector<std::filesystem::path> filepaths(p_path_count);
			for (int i = 0; i < p_path_count; i++)
				filepaths[i] = p_paths[i];

			WindowDropEvent event(std::move(filepaths));
			data.EventCallback(event);
		});
	}

	void GLFWWindow::Shutdown() noexcept
	{
		PFX_CORE_WARN("{} window shutdown", m_Data.Title)
		delete m_Context;
		m_Context = nullptr;
		glfwDestroyWindow(m_Window);
		--s_GLFWWindowCount;

		if (s_GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}

	void GLFWWindow::SetVsync(bool p_enabled)
	{
		PFX_CORE_TRACE("Set vsync {}", p_enabled)
		m_Data.Vsync = p_enabled;
		m_Context->SetVsync(p_enabled);
	}

	bool GLFWWindow::IsVsync() const
	{
		return m_Data.Vsync;
	}
}