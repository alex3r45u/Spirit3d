#include "sppch.h"
#include "Scene.h"
#include "Components.h"
#include "Spirit/Render/Camera.h"
#include "Spirit/Render/Renderer.h"
#include <glm/glm.hpp>

#include "Entity.h"

Spirit::Scene::Scene()
{
	entt::entity entity = m_Registry.create();
}

Spirit::Scene::~Scene()
{
}

Spirit::Entity Spirit::Scene::CreateEntity(const std::string& name)
{
	Entity entity = { m_Registry.create(), this };
	entity.AddComponent<TransformComponent>();
	auto& tag = entity.AddComponent<TagComponent>();
	tag.Tag = name.empty() ? "Entity" : name;
	return entity;
}


void Spirit::Scene::OnUpdate(TimeStep ts)
{
	Spirit::Render::PerspectiveCamera* mainCamera = nullptr;
	Spirit::TransformComponent* cameraTransform = nullptr;
	{
		auto view = m_Registry.view<TransformComponent, PerspectiveCameraComponent>();
		for (auto entity : view)
		{
			auto& [transform, camera] = view.get<TransformComponent, PerspectiveCameraComponent>(entity);
			mainCamera = &camera.Camera;
			cameraTransform = &transform;
			break;
			
		}
	}

	if (mainCamera)
	{
		Spirit::Render::Renderer::BeginScene(*mainCamera, *cameraTransform);

		auto view = m_Registry.view<TransformComponent, MeshRendererComponent>();
		for (auto entity : view)
		{
			auto& [transform, mesh] = view.get<TransformComponent, MeshRendererComponent>(entity);

			for (auto va : mesh.Mesh->GetVertexArray()) {
				Spirit::Render::Renderer::Submit(va, AssetLibrary::s_ShaderLibrary.Get("default"), AssetLibrary::s_MaterialLibrary.Get("default"), transform);
			}
		}

		Spirit::Render::Renderer::EndScene();
	}
}

void Spirit::Scene::OnReseize(unsigned int width, unsigned int height)
{
	auto view = m_Registry.view<PerspectiveCameraComponent>();
	for (auto entity : view)
	{
		auto& camera = view.get<PerspectiveCameraComponent>(entity);
		camera.Camera.SetViewport(width, height);
	}
}
