#pragma once
#include "Spirit/Layer/Layer.h"

namespace Spirit {
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() {}

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void ImGuiUpdate() override;

		void Begin();
		void End();

	};

}