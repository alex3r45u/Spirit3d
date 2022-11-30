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
#include "Spirit/Core/AssetLibrary.h"
#include "Spirit/Project/ProjectSerializer.h"
#include "Spirit/Core/File.h"

namespace Spirit {


#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;
	Application::Application()
	{
		Init();
	}

	Application::Application(const std::filesystem::path& projectPath)
	{
		
		//m_Project = ProjectSerializer::CreateProject("C:\\Users\\ap\\OneDrive\\Desktop\\asdf\\MeinProject.spiritproject", "ressources");
		m_Project = ProjectSerializer::CreateProject(projectPath, "ressources");
		//ProjectSerializer ps = ProjectSerializer(project);
		
		//if (!ps.Deserialize(projectPath))
		//	SP_CORE_ERROR("Failed to load Project");
		Init();
	}




	void Application::SetProject(const std::shared_ptr<Spirit::Project>& project)
	{
		m_Project = project;
	}

	void Application::Init()
	{
		SP_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_ImGuiLayer = new ImGuiLayer();
		m_LayerStack.AddLayer(m_ImGuiLayer);

		AssetLibrary::Init();
		Render::Renderer::Init();
		Scripting::ScriptController::Init(Spirit::File::Merge2Paths(m_Project->GetSettings().Path, m_Project->GetSettings().ProjectName + ".dll").string(), Spirit::File::Merge2Paths(m_Project->GetSettings().Path, "SpiritScript.dll").string());
		Scripting::ComponentsCs::Bind();
		Scripting::EntityCs::Bind();
		//Scripting::ScriptObject script = Scripting::ScriptController::GetDomain().GetClass("GameScripts.Class1").CreateInstance();
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
			AssetLibrary::Update();
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