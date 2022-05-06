#include "sppch.h"
#include "Framebuffer.h"
#include "Renderer.h"
#include "Spirit/Platform/OpenGl/OpenGlFramebuffer.h"

std::shared_ptr<Spirit::Render::Framebuffer> Spirit::Render::Framebuffer::Create(const FramebufferSettings settings)
{
	switch (Renderer::GetAPI())
	{
	case RenderAPI::API::None:    SP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case RenderAPI::API::OpenGl:  return std::make_shared<OpenGlFramebuffer>(settings);
	}

	SP_CORE_ASSERT(false, "Unknown RenderAPI!");
	return nullptr;
}
