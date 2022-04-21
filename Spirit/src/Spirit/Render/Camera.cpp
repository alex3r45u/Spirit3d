#include "sppch.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>


Spirit::Render::Camera::Camera(glm::vec3& position, glm::vec3& rotation) : m_Zoom(45.0f), m_Position(position), m_Rotation(rotation), m_Width(16), m_Height(9)
{
	CalcMats();
}

void Spirit::Render::Camera::CalcMats()
{
	m_Perspective = glm::perspective(
		glm::radians(45.0f),
		(float)m_Width / (float)m_Height,
		0.1f,
		100.0f
	);


	glm::vec3 direction;
	float yaw = m_Rotation.x;
	float pitch = m_Rotation.y;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	glm::vec3 forwardDir = glm::normalize(direction);
	m_View = glm::lookAt(m_Position, m_Position + forwardDir, glm::vec3(0.0f, 1.0f, 0.0f));
}
