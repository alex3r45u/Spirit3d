#pragma once
#include "Spirit/Render/RenderAPI.h"

namespace Spirit::Render {
	class OpenGlRenderAPI : public RenderAPI {
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Init() override;
		virtual void SetViewport(unsigned int width, unsigned int height) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}