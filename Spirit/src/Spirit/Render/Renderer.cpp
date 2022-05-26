#include "sppch.h"
#include "Renderer.h"
#include "RenderCommand.h"
Spirit::Render::Camera& Spirit::Render::Renderer::s_Camera = Spirit::Render::PerspectiveCamera();
Spirit::TransformComponent& Spirit::Render::Renderer::s_CamTransform = Spirit::TransformComponent();


void Spirit::Render::Renderer::Init()
{
	RenderCommand::Init();
}

void Spirit::Render::Renderer::OnReseize(unsigned int width, unsigned int height)
{
	RenderCommand::SetViewport(width, height);
}

void Spirit::Render::Renderer::BeginScene(const Camera& camera, TransformComponent& transform)
{
	s_Camera = camera;
	s_CamTransform = transform;
}

void Spirit::Render::Renderer::EndScene()
{
}

void Spirit::Render::Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, glm::mat4& model)
{
	shader->Bind();
	shader->SetMat4("u_ViewPerspective", s_Camera.GetViewProjection(s_CamTransform));
	shader->SetMat4("u_Model", model);
	shader->SetFloat3("u_ViewPos", s_CamTransform.Position.x, s_CamTransform.Position.y, s_CamTransform.Position.z);
	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}

void Spirit::Render::Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Material>& material, glm::mat4& model)
{
	shader->Bind();
	shader->SetMat4("u_ViewPerspective", s_Camera.GetViewProjection(s_CamTransform));
	shader->SetMat4("u_Model", model);
	material->SetUniforms(shader);
	shader->SetFloat3("u_ViewPos", s_CamTransform.Position.x, s_CamTransform.Position.y, s_CamTransform.Position.z);
	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}
