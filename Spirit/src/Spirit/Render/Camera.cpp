#include "sppch.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Spirit/Input/Input.h"
#include "Spirit/Scene/Components.h"





void Spirit::Render::PerspectiveCamera::CalcMats(TransformComponent& transform)
{
	m_Projection = glm::perspective(
		glm::radians(45.0f),
		(float)m_Width / (float)m_Height,
		0.1f,
		100.0f
	);

	m_View = glm::lookAt(transform.Position, transform.Position + transform.GetForward(), glm::vec3(0.0f, 1.0f, 0.0f));
}


