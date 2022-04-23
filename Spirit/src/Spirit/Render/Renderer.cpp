#include "sppch.h"
#include "Renderer.h"
#include "RenderCommand.h"

std::shared_ptr<Spirit::Render::Camera> Spirit::Render::Renderer::s_Camera = nullptr;


void Spirit::Render::Renderer::Init()
{
	RenderCommand::Init();
}

void Spirit::Render::Renderer::OnReseize(unsigned int width, unsigned int height)
{
	RenderCommand::SetViewport(width, height);
	s_Camera->SetViewport(width, height);
}

void Spirit::Render::Renderer::BeginScene(std::shared_ptr<Camera> camera)
{
	s_Camera = camera;
}

void Spirit::Render::Renderer::EndScene()
{
}

void Spirit::Render::Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, glm::mat4& model)
{
	shader->Bind();
	shader->SetMat4("u_ViewPerspective", s_Camera->GetViewPerspective());
	shader->SetMat4("u_Model", model);
	glm::vec3 camPos = s_Camera->GetPosition();
	shader->SetFloat3("u_ViewPos", camPos.x, camPos.y, camPos.z);
	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}

void Spirit::Render::Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Material> material, glm::mat4& model)
{
	shader->Bind();
	shader->SetMat4("u_ViewPerspective", s_Camera->GetViewPerspective());
	shader->SetMat4("u_Model", model);
	material->SetUniforms(shader);
	glm::vec3 camPos = s_Camera->GetPosition();
	shader->SetFloat3("u_ViewPos", camPos.x, camPos.y, camPos.z);
	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}
