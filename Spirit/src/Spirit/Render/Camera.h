#pragma once
#include <glm/glm.hpp>

namespace Spirit {
	class TransformComponent;
}

namespace Spirit::Render {


	class Camera {
	public:
		Camera() = default;
		virtual ~Camera() {}
		const glm::mat4& GetView(TransformComponent& transform) { CalcView(transform); return m_View;  }
		const glm::mat4& GetProjection() { CalcProjection(); return m_Projection;  }

		const glm::mat4& GetViewProjection(TransformComponent& transform) { CalcView(transform); CalcProjection(); return m_Projection * m_View; }

		void SetViewport(unsigned int width, unsigned int height) { m_Width = width; m_Height = height; }
		

		int GetWidth() { return m_Width; }
		int GetHeight() { return m_Height; }
	protected:
		virtual void CalcView(TransformComponent& transform) = 0;
		virtual void CalcProjection() = 0;
		glm::mat4 m_Projection;
		glm::mat4 m_View;

		unsigned int m_Width;
		unsigned int m_Height;
	};

	class PerspectiveCamera : public Camera {
	public:
		PerspectiveCamera() : m_Zoom(45.0f) {}
		PerspectiveCamera(unsigned int width, unsigned int height, float zoom) {
			SetViewport(width, height);
			m_Zoom = zoom;
		}



		void SetZoom(float zoom) { m_Zoom = zoom; CalcProjection();}
		float GetZoom() { return m_Zoom; }
	protected:
		virtual void CalcProjection() override;
		virtual void CalcView(TransformComponent& transform) override;
	private:
		float m_Zoom;
	};

	

}