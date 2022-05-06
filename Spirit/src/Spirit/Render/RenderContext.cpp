#include "sppch.h"
#include "RenderContext.h"
#include "Renderer.h"
#include "Spirit/Platform/OpenGL/OpenGlRenderContext.h"

std::unique_ptr<Spirit::Render::RenderContext> Spirit::Render::RenderContext::Create(void* window)
{
	switch (Render::Renderer::GetAPI())
	{
	case Render::RenderAPI::API::None:    SP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case Render::RenderAPI::API::OpenGl:  return std::make_unique<Render::OpenGlRenderContext>(static_cast<GLFWwindow*>(window));
	}

	SP_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}