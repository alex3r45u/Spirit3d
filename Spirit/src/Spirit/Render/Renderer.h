#pragma once
#include "RenderAPI.h"
#include "Camera.h"
#include "Shader.h"
#include "Material.h"
#include <memory>
#include "Spirit/Scene/Components.h"

namespace Spirit::Render {


	class Renderer
	{
	public:

		static void Init();
		static void OnReseize(unsigned int width, unsigned int height);

		static void BeginScene(const Camera& camera, Spirit::TransformComponent& transform);
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, glm::mat4& model);
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Material>& material, glm::mat4& model);


		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
	private:
		static Camera& s_Camera;
		static Spirit::TransformComponent& s_CamTransform;
	};
}

