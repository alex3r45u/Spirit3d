#include "sppch.h"
#include "LayerStack.h"
#include "Layer.h"


Spirit::LayerStack::~LayerStack()
{
	for (auto i : m_Layers) {
		delete i;
	}
}

void Spirit::LayerStack::AddLayer(Layer* layer)
{
	m_Layers.push_back(layer);
	layer->OnAttach();
	m_LayerInsertIndex++;
}

void Spirit::LayerStack::PopLayer(Layer* layer)
{
	auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
	if (it != m_Layers.end())
	{
		layer->OnDetach();
		m_Layers.erase(it);
		m_LayerInsertIndex--;
	}
}

void Spirit::LayerStack::Update(TimeStep ts)
{
	for (auto l : m_Layers) {
		l->Update(ts);
	}
}

void Spirit::LayerStack::LightUpdate()
{
	for (auto l : m_Layers) {
		l->LightUpdate();
	}
}

void Spirit::LayerStack::RenderUpdate(TimeStep ts)
{
	for (auto l : m_Layers) {
		l->RenderUpdate(ts);
	}
}

void Spirit::LayerStack::ImGuiUpdate()
{
	for (auto l : m_Layers) {
		l->ImGuiUpdate();
	}
}

void Spirit::LayerStack::OnEvent(Event& e)
{
	for (auto l : m_Layers) {
		l->OnEvent(e);
		if (e.Handled)
			break;
	}
}
