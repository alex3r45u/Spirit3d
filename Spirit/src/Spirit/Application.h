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

namespace Spirit {

	class Application
	{
	public:
		Application();
		Application(std::filesystem::path assets, std::filesystem::path ressources);
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() const { return *m_Window; }

		std::filesystem::path GetAssetDir() const;
		std::filesystem::path GetRessourceDir() const;

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

		std::filesystem::path m_AssetPath;
		std::filesystem::path m_RessourcePath;
	protected:
		LayerStack m_LayerStack = LayerStack();

	};

	// To be defined in CLIENT
	Application* CreateApplication();

}