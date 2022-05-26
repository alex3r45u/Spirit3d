#pragma once
#include <vector>
#include "Spirit/Core/TimeStep.h" 
#include "Spirit/Event/Event.h"

namespace Spirit {
	class Layer;
	class LayerStack {
	public:
		LayerStack() {}
		~LayerStack();
		void AddLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void Update(TimeStep ts);
		void LightUpdate();
		void RenderUpdate(TimeStep ts);
		void ImGuiUpdate();
		void OnEvent(Event& e);

	private:
		std::vector<Layer*> m_Layers;
		int m_LayerInsertIndex = 0;
	};
}