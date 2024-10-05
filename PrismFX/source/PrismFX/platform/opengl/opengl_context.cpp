#include "PrismFX/pfx_pch.h"
#include "opengl_context.h"

// Lib
#include <glad/glad.h>


namespace PFX
{
	OpenGLContext::OpenGLContext(GLFWwindow* p_window_handle)
		: m_WindowHandle(p_window_handle)
	{
		PFX_CORE_ASSERT(m_WindowHandle, "Window Handle is null, did you call new OpenGLContext() with your window?");
		PFX_CORE_INFO("OpenGLContext has Initialized!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PFX_CORE_ASSERT(status, "Failed to initialize Glad!");

		PFX_CORE_INFO("OpenGL Info: ");
		PFX_CORE_INFO("	Vendor: {0}",	(const char*)glGetString(GL_VENDOR));
		PFX_CORE_INFO("	Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		PFX_CORE_INFO("	Version: {0}",	(const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffer()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

	void OpenGLContext::SetVsync(bool p_enable)
	{
		glfwSwapInterval((p_enable) ? 1 : 0);
	}


} // PFX
