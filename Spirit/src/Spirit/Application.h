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

#include <filesystem>
#include "Spirit/Project/Project.h"

namespace Spirit {

	class Application
	{
	public:
		Application();
		Application(const std::filesystem::path& projectPath);
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() const { return *m_Window; }

		std::shared_ptr<Spirit::Project> GetProject() { return m_Project; }
		void SetProject(const std::shared_ptr<Spirit::Project>& project);

	private:
		void Init();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowReseize(WindowResizeEvent& e);

	private:
		static Application* s_Instance;
		std::unique_ptr<Window> m_Window;

		ImGuiLayer* m_ImGuiLayer;
		float m_LastTime;
		bool m_Running;

		std::shared_ptr<Project> m_Project;
	protected:
		LayerStack m_LayerStack = LayerStack();

	};

	// To be defined in CLIENT
	Application* CreateApplication();

}