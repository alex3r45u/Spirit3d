#pragma once
#include <glm/glm.hpp>
#include <memory>
#include "VertexArray.h"

namespace Spirit::Render {
	class RenderAPI {
	public:
		enum class API
		{
			None = 0, OpenGl = 1
		};
	public:
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void Init() = 0;
		virtual void SetViewport(unsigned int width, unsigned int height) = 0;


		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};
}