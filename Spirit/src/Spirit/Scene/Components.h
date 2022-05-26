#pragma once
#include <glm/glm.hpp>
#include <string>
#include "Spirit/Render/Mesh.h"
#include "Spirit/Render/Camera.h"
#include <memory>
#include "Spirit/Core/AssetLibrary.h"

namespace Spirit {
	struct TagComponent {
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};

	struct TransformComponent {
		glm::mat4 Transform = glm::mat4(1.0f);

		glm::vec3 Position = glm::vec3(0.0f);
		glm::vec3 Rotation = glm::vec3(0.0f);
		glm::vec3 Scale = glm::vec3(1.0f);

		glm::vec3 GetForward() { Recalculate();  return m_Forward; }
		glm::vec3 GetBackward() { Recalculate(); return m_Backward; }
		glm::vec3 GetLeft() { Recalculate(); return m_Left; }
		glm::vec3 GetRight() { Recalculate(); return m_Right; }



		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : Position(position), Rotation(rotation), Scale(scale) {}

		operator glm::mat4& () { Recalculate();  return Transform; }
	private:
		void Recalculate() {
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
	};

	struct MeshRendererComponent
	{
		std::shared_ptr<Spirit::Render::Mesh> Mesh;

		MeshRendererComponent() = default;
		MeshRendererComponent(const MeshRendererComponent&) = default;
		MeshRendererComponent(const std::shared_ptr<Spirit::Render::Mesh>& mesh) : Mesh(mesh) {}
		MeshRendererComponent(const std::string& name) { Mesh = AssetLibrary::s_MeshLibrary.Get(name); }
	};

	struct PerspectiveCameraComponent {
		Spirit::Render::PerspectiveCamera Camera;

		PerspectiveCameraComponent() = default;
		PerspectiveCameraComponent(const PerspectiveCameraComponent&) = default;
		PerspectiveCameraComponent(const Spirit::Render::PerspectiveCamera& camera) : Camera(camera) {}

	};
}