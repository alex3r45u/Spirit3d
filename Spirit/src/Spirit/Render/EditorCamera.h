#pragma once
#include "Spirit/Input/Input.h"
#include "Spirit/Scene/Components.h"

namespace Spirit::Render {
	class EditorCamera
	{
	public:

		EditorCamera();

		void OnUpdate();
		TransformComponent* GetTransform() { return m_Transform; }
		std::shared_ptr<Camera> GetCamera() { return m_Camera; }
	private:
		float m_Speed;
		Spirit::TransformComponent* m_Transform;
		std::shared_ptr<Camera> m_Camera;

	};
}


