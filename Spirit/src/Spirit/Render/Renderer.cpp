#include "sppch.h"
#include "Renderer.h"
#include "RenderCommand.h"
std::shared_ptr<Spirit::Render::Camera> Spirit::Render::Renderer::s_Camera;
Spirit::TransformComponent* Spirit::Render::Renderer::s_CamTransform;


void Spirit::Render::Renderer::Init()
{
	RenderCommand::Init();
}

void Spirit::Render::Renderer::OnReseize(unsigned int width, unsigned int height)
{
	RenderCommand::SetViewport(width, height);
}

void Spirit::Render::Renderer::BeginScene(const std::shared_ptr<Camera>& camera, Spirit::TransformComponent* transform)
{
	s_Camera = camera;
	s_CamTransform = transform;
	
}

void Spirit::Render::Renderer::EndScene()
{
}

void Spirit::Render::Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, TransformComponent& model)
{
	shader->Bind();
	shader->SetMat4("u_ViewPerspective", s_Camera->GetViewProjection(*s_CamTransform));
	shader->SetMat4("u_Model", model);
	shader->SetFloat3("u_ObjRot", model.Rotation.x, model.Rotation.y, model.Rotation.z);
	shader->SetFloat3("u_ViewPos", s_CamTransform->Position.x, s_CamTransform->Position.y, s_CamTransform->Position.z);
	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}





static void SetUniformsMaterial(const std::shared_ptr<Spirit::Render::Shader>& shader, const std::shared_ptr<Spirit::Render::Material>& material) {
	shader->SetFloat3("u_Material.Albedo",material->Albedo);
	shader->SetFloat("u_Material.Roughness", material->Roughness);
	shader->SetFloat("u_Material.Metallic", material->Metallic);
	shader->SetFloat("u_Material.AO", material->AO);

	//Todo Maps
}

void Spirit::Render::Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Material>& material, TransformComponent& model)
{
	shader->Bind();
	shader->SetMat4("u_ViewPerspective", s_Camera->GetViewProjection(*s_CamTransform));
	shader->SetMat4("u_Model", model);
	shader->SetFloat3("u_ObjRot", model.Rotation.x, model.Rotation.y, model.Rotation.z);
	SetUniformsMaterial(shader, material);
	shader->SetFloat3("u_ViewPos", s_CamTransform->Position.x, s_CamTransform->Position.y, s_CamTransform->Position.z);
	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}
