#pragma once
#include "Spirit/Input/Input.h"

namespace Spirit {
	class WindowsInput : public Input {
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
		virtual float GetMouseDxImpl() override;
		virtual float GetMouseDyImpl() override;
		virtual void OnUpdate() override;
	private:
		float m_LastX = 0;
		float m_LastY = 0;

		float m_Dx;
		float m_Dy;
	};
}