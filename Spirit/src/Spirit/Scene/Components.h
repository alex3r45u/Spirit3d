#pragma once
#include <glm/glm.hpp>
#include <string>
#include "Spirit/Render/Mesh.h"
#include "Spirit/Render/Camera.h"
#include <memory>
#include "Spirit/Core/AssetLibrary.h"
#include <filesystem>
#include "Spirit/Render/Lights/DirectionalLight.h"
#include "Spirit/Render/Lights/PointLight.h"
#include "Spirit/Render/Lights/SpotLight.h"
#include "ScriptableEntity.h"

namespace Spirit {

	struct UUIDComponent {

	};

	struct TagComponent {
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};


	class TransformComponent {
	public:
		glm::mat4 Transform = glm::mat4(1.0f);

		glm::vec3 Position = glm::vec3(0.0f);
		glm::vec3 Rotation = glm::vec3(0.0f);
		glm::vec3 Scale = glm::vec3(1.0f);

		glm::vec3 GetForward() { Recalculate();  return m_Forward; }
		glm::vec3 GetBackward() { Recalculate(); return m_Backward; }
		glm::vec3 GetLeft() { Recalculate(); return m_Left; }
		glm::vec3 GetRight() { Recalculate(); return m_Right; }
		glm::vec3 GetUp() { Recalculate(); return m_Up; }
		glm::vec3 GetDown() { Recalculate(); return m_Down; }



		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : Position(position), Rotation(rotation), Scale(scale) { Recalculate(); }

		operator glm::mat4& () { Recalculate();  return Transform; }
	private:
		void Recalculate() {
			Transform = glm::mat4(1.0f);
			glm::vec3 direction;
			direction.x = cos(glm::radians(Rotation.x)) * cos(glm::radians(Rotation.y));
			direction.y = sin(glm::radians(Rotation.y));
			direction.z = sin(glm::radians(Rotation.x)) * cos(glm::radians(Rotation.y));
			m_Forward = glm::normalize(direction);
			m_Backward = -m_Forward;
			m_Right = glm::normalize(glm::cross(m_Forward, glm::vec3(0.0f, 1.0f, 0.0f)));
			m_Left = -m_Right;

			Transform = glm::translate(Transform, Position);
			Transform = glm::scale(Transform, Scale);
			Transform = glm::rotate(Transform, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
			Transform = glm::rotate(Transform, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
			Transform = glm::rotate(Transform, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		}
	private:
		glm::vec3 m_Forward;
		glm::vec3 m_Backward;
		glm::vec3 m_Left;
		glm::vec3 m_Right;
		glm::vec3 m_Up;
		glm::vec3 m_Down;
	};

	struct MeshRendererComponent
	{
		std::shared_ptr<Spirit::Render::Mesh> Mesh;
		MeshRendererComponent() { Mesh = std::make_shared < Spirit::Render::Mesh>(); }
		MeshRendererComponent(const MeshRendererComponent&) = default;
		MeshRendererComponent(const std::string& name) { Mesh = AssetLibrary::GetMeshRegistry().GetMember({ name }); }
	};

	struct MaterialComponent {
		std::shared_ptr<Spirit::Render::Material> Material;
		MaterialComponent() { Material = std::make_shared <Spirit::Render::Material>(); }
		MaterialComponent(const MaterialComponent&) = default;
	};
	
	enum class CameraType {
		Perspective,
		Orthographic
	};
	struct CameraComponent {
		std::shared_ptr<Spirit::Render::Camera> Camera;
		bool IsMain = false;
		CameraType Type;
		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(const CameraType& type) {
			switch (type) {
			case CameraType::Perspective:
				Camera = std::make_shared<Render::PerspectiveCamera>();
				Type = CameraType::Perspective;
				break;
			case CameraType::Orthographic:
				//TODO
				Type = CameraType::Orthographic;
				break;
			}
		}

	};

	struct DirectionalLightComponent {
		std::shared_ptr<Spirit::Render::DirectionalLight> DirectionalLight;

		DirectionalLightComponent() { DirectionalLight = std::make_shared<Spirit::Render::DirectionalLight>(); }
		DirectionalLightComponent(const DirectionalLightComponent&) = default;
		DirectionalLightComponent(const std::shared_ptr<Spirit::Render::DirectionalLight>& direcLight) : DirectionalLight(direcLight) {}
	};
	struct PointLightComponent {
		std::shared_ptr<Spirit::Render::PointLight> PointLight;

		PointLightComponent() { PointLight = std::make_shared<Spirit::Render::PointLight>(); }
		PointLightComponent(const PointLightComponent&) = default;
		PointLightComponent(const std::shared_ptr<Spirit::Render::PointLight>& pointLight) : PointLight(pointLight) {}
	};
	struct SpotLightComponent {
		std::shared_ptr<Spirit::Render::SpotLight> SpotLight;

		SpotLightComponent() { SpotLight = std::make_shared<Spirit::Render::SpotLight>(); }
		SpotLightComponent(const SpotLightComponent&) = default;
		SpotLightComponent(const std::shared_ptr<Spirit::Render::SpotLight>& spotLight) : SpotLight(spotLight) {}
	};

	struct NativeScriptComponent {
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};

}