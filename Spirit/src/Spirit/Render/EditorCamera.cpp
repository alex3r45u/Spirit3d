#include "sppch.h"
#include "EditorCamera.h"

Spirit::Render::EditorCamera::EditorCamera()
{

	m_Speed = .2;
	m_Camera = std::make_shared<Spirit::Render::PerspectiveCamera>();
	m_Transform = new TransformComponent();
}

void Spirit::Render::EditorCamera::OnUpdate()
{

	if (Spirit::Input::IsMouseButtonPressed(1)) {
		if (Spirit::Input::IsKeyPressed(SP_KEY_W)) {
			m_Transform->Translate(m_Transform->GetForward(), m_Speed);
		}

		if (Spirit::Input::IsKeyPressed(SP_KEY_A)) {
			m_Transform->Translate(m_Transform->GetLeft(), m_Speed);
		}

		if (Spirit::Input::IsKeyPressed(SP_KEY_S)) {
			m_Transform->Translate(m_Transform->GetBackward(), m_Speed);
		}

		if (Spirit::Input::IsKeyPressed(SP_KEY_D)) {
			m_Transform->Translate(m_Transform->GetRight(), m_Speed);
		}

		if (Spirit::Input::IsKeyPressed(SP_KEY_SPACE)) {
			m_Transform->Position = glm::vec3(m_Transform->Position.x, m_Transform->Position.y + m_Speed, m_Transform->Position.z);
		}

		if (Spirit::Input::IsKeyPressed(SP_KEY_LEFT_SHIFT)) {
			m_Transform->Position = glm::vec3(m_Transform->Position.x, m_Transform->Position.y - m_Speed, m_Transform->Position.z);
		}

		m_Transform->Rotation.x += Spirit::Input::GetMouseDx()*.1;
		m_Transform->Rotation.y -= Spirit::Input::GetMouseDy()*.1;
	}
}
