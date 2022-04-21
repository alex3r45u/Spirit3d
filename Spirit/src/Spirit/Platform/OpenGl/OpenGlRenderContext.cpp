#include "sppch.h"
#include "OpenGlRenderContext.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h>

Spirit::Render::OpenGlRenderContext::OpenGlRenderContext(GLFWwindow* windowHandle)
{
	m_WindowHandle = windowHandle;
	SP_CORE_ASSERT(windowHandle, "Window handle is null!");
}



void Spirit::Render::OpenGlRenderContext::Init()
{
	glfwMakeContextCurrent(m_WindowHandle);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	SP_CORE_ASSERT(status, "Failed to initialize Glad!");

	SP_CORE_INFO("OpenGL Info:");
	SP_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
	SP_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
	SP_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

}

void Spirit::Render::OpenGlRenderContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}
