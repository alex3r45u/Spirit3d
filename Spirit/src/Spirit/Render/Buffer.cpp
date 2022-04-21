#include "sppch.h"
#include "Buffer.h"
#include "Renderer.h"

#include "Spirit/Platform/OpenGl/OpenGlBuffer.h"

std::shared_ptr<Spirit::Render::VertexBuffer> Spirit::Render::VertexBuffer::Create(float* vertices, unsigned int size)
{
	switch (Renderer::GetAPI())
	{
	case RenderAPI::API::None:    SP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case RenderAPI::API::OpenGl:  return std::make_shared<OpenGlVertexBuffer>(vertices, size);
	}

	SP_CORE_ASSERT(false, "Unknown RenderAPI!");
	return nullptr;
}

std::shared_ptr<Spirit::Render::IndexBuffer> Spirit::Render::IndexBuffer::Create(unsigned int* indices, unsigned int size)
{
	switch (Renderer::GetAPI())
	{
	case RenderAPI::API::None:    SP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case RenderAPI::API::OpenGl:  return std::make_shared<OpenGlIndexBuffer>(indices, size);
	}

	SP_CORE_ASSERT(false, "Unknown RenderAPI!");
	return nullptr;
}