#pragma once
#include <string>
#include "Spirit/Core/TimeStep.h"
#include "Spirit/Event/Event.h"

namespace Spirit {
	class Layer {
	public:
		Layer(const std::string& name) {
			m_Name = name;
		}
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void Update(TimeStep ts) {}
		virtual void LightUpdate() {}
		virtual void RenderUpdate() {}
		virtual void ImGuiUpdate() {}
		virtual void OnEvent(Event& event) {}
		const std::string& GetName() const { return m_Name; }
	private:

		std::string m_Name;
	};
}