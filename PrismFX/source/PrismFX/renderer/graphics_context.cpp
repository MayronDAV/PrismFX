#include "PrismFX/pfx_pch.h"
#include "graphics_context.h"

#include "PrismFX/core/engine.h"
#include "PrismFX/platform/opengl/opengl_context.h"



namespace PFX
{
    GraphicsContext* GraphicsContext::Create(GLFWwindow* p_window_handle)
    {
        switch (Engine::GetAPI())
        {
            case RenderAPI::OpenGL:
                return new OpenGLContext(p_window_handle);
            default:
                PFX_CORE_ERROR("Unknown render api!")
                return nullptr;
        }
    }

} // PFX

