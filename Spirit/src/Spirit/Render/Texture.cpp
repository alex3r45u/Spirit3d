#include "sppch.h"
#include "Texture.h"
#include "Renderer.h"
#include "Spirit/Platform/OpenGl/OpenGlTexture.h"

std::shared_ptr<Spirit::Render::Texture2d> Spirit::Render::Texture2d::Create(const std::string& path)
{
	switch (Renderer::GetAPI())
	{
	case RenderAPI::API::None:    SP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case RenderAPI::API::OpenGl:  return std::make_shared<OpenGlTexture2d>(path);
	}

	SP_CORE_ASSERT(false, "Unknown RenderAPI!");
	return nullptr;
}
