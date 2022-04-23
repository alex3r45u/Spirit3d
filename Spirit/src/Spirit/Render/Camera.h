#pragma once
#include <glm/glm.hpp>


namespace Spirit::Render {
	class Camera {
	public:
		Camera();
		Camera(glm::vec3& position, glm::vec3& rotation);


		void SetPosition(glm::vec3& position) { m_Position = position; CalcMats(); }
		void SetRotation(glm::vec3& rotation) { m_Rotation = rotation; CalcMats(); }
		const glm::vec3&  GetPosition()  { return m_Position; }
		const glm::vec3&  GetRotation()  { return m_Rotation; }

		void SetViewport(unsigned int width, unsigned int height) { m_Width = width; m_Height = height; CalcMats(); }

		void SetZoom(float& zoom) { m_Zoom = zoom; }
		const float& const GetZoom() const { return m_Zoom; }

		const glm::mat4& const GetPerspective() {  return m_Perspective; }
		const glm::mat4& const GetView() {  return m_View; }
		const glm::mat4& const GetViewPerspective() {  return m_Perspective * m_View; }

	private:
		void CalcMats();
	private:
		glm::vec3  m_Position;
		glm::vec3  m_Rotation;
		glm::mat4 m_Perspective;
		glm::mat4 m_View;

		unsigned int m_Width;
		unsigned int m_Height;

		float m_Zoom;
	};
}