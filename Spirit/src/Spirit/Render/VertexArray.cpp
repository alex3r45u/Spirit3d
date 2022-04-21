#include "sppch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Spirit/Platform/OpenGl/OpenGlVertexArray.h"

Spirit::Render::VertexArray* Spirit::Render::VertexArray::Create() {
	switch (Renderer::GetAPI())
	{
	case RenderAPI::API::None:    SP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case RenderAPI::API::OpenGl:  return new OpenGlVertexArray();
	}

	SP_CORE_ASSERT(false, "Unknown RenderAPI!");
	return nullptr;


}