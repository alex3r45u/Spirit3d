#pragma once
#include "RenderAPI.h"


namespace Spirit::Render {
	class RenderCommand
	{
	public:
		inline static void Init() {
			s_RendererAPI->Init();
		}

		inline static void SetViewport(unsigned int width, unsigned int height) {
			s_RendererAPI->SetViewport(width, height);
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}
	private:
		static RenderAPI* s_RendererAPI;
	};
}