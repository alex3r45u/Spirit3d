#include "sppch.h"
#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Spirit/Input/Input.h"
#include "Render/RenderCommand.h"
#include "Render/Renderer.h"
#include "Spirit/Core/TimeStep.h"
#include "Core.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Spirit/Scene/Scripting/ScriptController.h"
#include "Spirit/Scene/Scripting/ComponentsCs.h"
#include "Spirit/Scene/Scripting/EntityCs.h"

namespace Spirit {


#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;
	Application::Application()
	{
		Init();
	}

	Application::Application(std::filesystem::path assets, std::filesystem::path ressources)
	{
		m_AssetPath = assets;
		m_RessourcePath = ressources;
	}


	void Application::Init()
	{
		SP_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_ImGuiLayer = new ImGuiLayer();
		m_LayerStack.AddLayer(m_ImGuiLayer);


		Render::Renderer::Init();
		Scripting::ScriptController::Init("GameScripts.dll");
		Scripting::ComponentsCs::Bind();
		Scripting::EntityCs::Bind();
		Scripting::ScriptObject script = Scripting::ScriptController::GetDomain().GetClass("GameScripts.Class1").CreateInstance();
		//SP_CORE_INFO(script.GetTypeName());
	}



	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running) {
			float time = glfwGetTime(); //TODO 
			TimeStep ts = TimeStep(time - m_LastTime);
			m_LastTime = time;

			Input::Update();

			m_LayerStack.Update(ts);
			//Update ImGui
			m_LayerStack.LightUpdate();
			m_LayerStack.RenderUpdate(ts);

			m_ImGuiLayer->Begin();
			m_LayerStack.ImGuiUpdate();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();

		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowReseize));
		m_LayerStack.OnEvent(e);
	}





	std::filesystem::path Application::GetAssetDir() const
	{
		return m_AssetPath;
	}

	std::filesystem::path Application::GetRessourceDir() const
	{
		return m_RessourcePath;
	}

	

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowReseize(WindowResizeEvent& e) {
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			//m_Minimized = true;
			return false;
		}

		//m_Minimized = false;
		Render::Renderer::OnReseize(e.GetWidth(), e.GetHeight());

		

		return false;
	}
}