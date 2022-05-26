#pragma once

#include "Core.h"
#include "Spirit/Layer/LayerStack.h"
#include "Spirit/Window.h"
#include "Spirit/ImGui/ImGuiLayer.h"
#include "Spirit/Render/Shader.h"
#include "Spirit/Render/VertexArray.h"
#include "Spirit/Render/Camera.h"
#include "Spirit/Event/Event.h"
#include "Spirit/Event/ApplicationEvent.h"

namespace Spirit {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() const { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowReseize(WindowResizeEvent& e);

	private:
		static Application* s_Instance;
		std::unique_ptr<Window> m_Window;

		ImGuiLayer* m_ImGuiLayer;
		float m_LastTime;
		bool m_Running;
	protected:
		LayerStack m_LayerStack = LayerStack();

	};

	// To be defined in CLIENT
	Application* CreateApplication();

}