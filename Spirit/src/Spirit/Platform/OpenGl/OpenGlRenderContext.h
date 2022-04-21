#pragma once
#include "Spirit/Render/RenderContext.h"

struct GLFWwindow;

namespace Spirit::Render {
	class OpenGlRenderContext : public RenderContext{
	public:
		OpenGlRenderContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}