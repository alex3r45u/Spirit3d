#include "sppch.h"
#include "Scene.h"
#include "Components.h"
#include "Spirit/Render/Camera.h"
#include "Spirit/Render/Renderer.h"
#include <glm/glm.hpp>
#include "Spirit/Render/Lights/LightManager.h"
#include "Entity.h"
#include "Scripting/ScriptController.h"
#include "Spirit/Core/AssetLibrary.h"



Spirit::Scene::~Scene()
{
}

Spirit::Scene::Scene()
{
	m_Path = "Not Found";
}

Spirit::Scene::Scene(const std::filesystem::path& path)
{
	m_Path = path;
}

Spirit::Entity Spirit::Scene::CreateEntity(const std::string& name)
{
	Entity entity = { m_Registry.create(), this };
	entity.AddComponent<TransformComponent>();
	auto& tag = entity.AddComponent<TagComponent>();
	tag.Tag = name.empty() ? "Entity" : name;
	//m_ScriptingECS.AddComponent((unsigned int)entity, std::make_shared<Scripting::ScriptObject>(Scripting::ScriptController::GetDomain().GetClass("MeinProject.assets.Class1").CreateInstance()));
	return entity;
}

void Spirit::Scene::RemoveEntity(Entity& entity)
{
	m_ScriptingECS.RemoveEntity(entity);
	m_Registry.destroy(entity);
}


void Spirit::Scene::OnUpdate(TimeStep ts)
{

	{
		m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc){
			if (!nsc.Instance)
			{
				nsc.Instance = nsc.InstantiateScript();
				nsc.Instance->entity = Entity{ entity, this };
				nsc.Instance->transform = nsc.Instance->entity.GetComponent<TransformComponent>();
				nsc.Instance->OnCreate();
			}

			nsc.Instance->OnUpdate(ts);
		});
	}
	m_ScriptingECS.UpdateScriptingECS();


	std::shared_ptr<Render::Camera> mainCamera = nullptr;
	TransformComponent* cameraTransform = nullptr;
	{
		auto view = m_Registry.view<TransformComponent, CameraComponent>();
		for (auto entity : view)
		{
			auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
			if (!camera.IsMain)
				continue;
			mainCamera = camera.Camera;
			cameraTransform = &transform;
			break;
			
		}
	}

	if (mainCamera)
	{
		
		{
			Spirit::Render::LightManager::Start(AssetLibrary::GetShaderRegistry().GetMember({ "default", "vertex.glsl", "fragment.glsl" }));
			{
				auto view = m_Registry.view <TransformComponent, PointLightComponent>();
				for (auto entity : view) {
					auto [transform, light] = view.get<TransformComponent, PointLightComponent>(entity);
					Spirit::Render::LightManager::Submit(light.PointLight, transform);
				}
				
			}
			{
				auto view = m_Registry.view <TransformComponent, DirectionalLightComponent>();
				for (auto entity : view) {
					auto [transform, light] = view.get<TransformComponent, DirectionalLightComponent>(entity);
					Spirit::Render::LightManager::Submit(light.DirectionalLight, transform);
				}
			}
			{
				auto view = m_Registry.view <TransformComponent, SpotLightComponent>();
				for (auto entity : view) {
					auto [transform, light] = view.get<TransformComponent, SpotLightComponent>(entity);
					Spirit::Render::LightManager::Submit(light.SpotLight, transform);
				}
			}
			

			Spirit::Render::LightManager::End();
		}
		
		{
			Spirit::Render::Renderer::BeginScene(mainCamera, cameraTransform);
			auto view = m_Registry.view<TransformComponent, MeshRendererComponent, MaterialComponent>();
			for (auto entity : view)
			{
				auto [transform, mesh, material] = view.get<TransformComponent, MeshRendererComponent, MaterialComponent>(entity);

				for (auto va : AssetLibrary::GetMeshRegistry().GetMember({ mesh.Path.string()})->GetVertexArray()) {
					Spirit::Render::Renderer::Submit(va, AssetLibrary::GetShaderRegistry().GetMember({ "default", "assets/vertex.glsl", "assets/fragment.glsl" }), material.Material, transform);
				}
			}

			Spirit::Render::Renderer::EndScene();
		}
		
	}
}

void Spirit::Scene::OnReseize(unsigned int width, unsigned int height)
{
	auto view = m_Registry.view<CameraComponent>();
	for (auto entity : view)
	{
		auto& camera = view.get<CameraComponent>(entity);
		camera.Camera->SetViewport(width, height);
		
		
	}
}

Spirit::Entity Spirit::Scene::GetEntityByIndex(entt::entity handle)
{
	return Entity(handle, this);
}

void Spirit::Scene::SetPath(const std::filesystem::path& path)
{
	m_Path = path;
}

