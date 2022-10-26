#include <Spirit.h>
#include <imgui/imgui.h>
#include "Windows/SceneHierarchyPanel.h"
#include "Windows/PropertiesPanel.h"
#include "Windows/FileExplorerPanel.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include "Core/ScriptSolution.h"
#include "Spirit/Utils/FileDialog.h"
#include "Spirit/Project/ProjectSerializer.h"
#include "Spirit/Scene/Scripting/ScriptController.h"
#include "Spirit/Core/File.h"
#define PROJECT Spirit::Application::Get().GetProject()

enum class SceneState {
	None = 0,
	Edit,
	Play,
	PlayStop,
};


class EditorLayer : public Spirit::Layer {
public:
	EditorLayer() : Layer("Editor") {
	}

	virtual void OnAttach() override {
		m_State = SceneState::Edit;
		Spirit::AssetLibrary::GetShaderRegistry().AddMember({ "default", "vertex.glsl", "fragment.glsl" });
		Spirit::Render::FramebufferSettings fbosettings;
		fbosettings.Width = 1280;
		fbosettings.Height = 720;
		m_Fbo = Spirit::Render::Framebuffer::Create(fbosettings);
		
		ReloadPanels();
		
		

	}
	void ReloadPanels() {
		m_SceneHierarchyPanel.SetScene(PROJECT->GetActiveScene());
		m_PropertiesPanel.SetScene(PROJECT->GetActiveScene());
		m_PropertiesPanel.SetSceneHierarchy(&m_SceneHierarchyPanel);

		m_FileExplorerPanel.SetScene(PROJECT->GetActiveScene());
		m_FileExplorerPanel.SetDirectory(Spirit::Application::Get().GetProject()->GetSettings().AssetPath);
	}

	virtual void Update(Spirit::TimeStep ts) override {
		

		
		
	}

	void RenderUpdate(Spirit::TimeStep ts) override {
    	m_Fbo->Bind();
		Spirit::Render::RenderCommand::SetClearColor({ 0.1f, .1f, .1f, 1 });
		Spirit::Render::RenderCommand::Clear();

		PROJECT->GetActiveScene()->OnUpdate(ts);
		m_Fbo->Unbind();
	}


	
	void OnEvent(Spirit::Event& event) override {
		
	}

	void ImGuiUpdate() override {
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;


		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;


		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::Button(m_State == SceneState::Edit ? "Play" : "Edit")) {
				m_State = m_State == SceneState::Edit ? SceneState::Play : SceneState::Edit;

				switch (m_State)
				{
				case SceneState::Edit:
					break;
				case SceneState::Play: {
					std::string activeSceneName = PROJECT->GetActiveScene()->GetPath().string();
					PROJECT->SaveActiveScene(std::filesystem::path(activeSceneName));
					break;
				}
					
				case SceneState::PlayStop:
					break;
				default:
					break;
				}
			}
			if (m_State == SceneState::Play) {
				if(ImGui::Button("Stop")) {
					m_State = SceneState::PlayStop;
				}
			} else if (m_State == SceneState::PlayStop) {
				if (ImGui::Button("Start")) {
					m_State = SceneState::Play;
				}
			}
			if (ImGui::BeginMenu("File"))
			{
				
				if (ImGui::MenuItem("Create")) {
					std::string path = Spirit::FileDialog::SaveFile("Spirit Project (*.spiritproject)\0*.spiritproject\0");
					if (!path.empty()) {
						PROJECT->SaveActiveScene(PROJECT->GetActiveScene()->GetPath());
						std::shared_ptr<Spirit::Project> project = Spirit::ProjectSerializer::CreateProject(path, "ressources");
						Spirit::Application::Get().SetProject(project);
						Spirit::ScriptSolution::Create(project);
						Spirit::ScriptSolution::Open(project);
						ReloadPanels();
					}
				}
				if (ImGui::MenuItem("Open")) {
					std::string path = Spirit::FileDialog::OpenFile("Spirit Project (*.spiritproject)\0*.spiritproject\0");
					if (!path.empty()) {
						PROJECT->SaveActiveScene(PROJECT->GetActiveScene()->GetPath());
						std::shared_ptr<Spirit::Project> project = std::make_shared<Spirit::Project>();
						Spirit::ProjectSerializer serializer(project);
						serializer.Deserialize(path);
						Spirit::Application::Get().SetProject(project);
						PROJECT->SetLoadScene(PROJECT->GetSettings().StartScene);
						ReloadPanels();
						Spirit::Scripting::ScriptController::Reload();
					}
				}
				if (ImGui::MenuItem("Save")) {
					Spirit::ProjectSerializer serializer(PROJECT);
					serializer.Serialize(PROJECT->GetSettings().Path);
					PROJECT->SaveActiveScene(PROJECT->GetActiveScene()->GetPath());
				}
				if (ImGui::MenuItem("Export")) {}
				if (ImGui::MenuItem("Open Script Solution")) {
					Spirit::ScriptSolution::Open(PROJECT);
				}
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}
		m_SceneHierarchyPanel.ImGuiRender();
		m_PropertiesPanel.ImGuiRender();
		m_FileExplorerPanel.ImGuiRender();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Spirit::Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		if (m_ViewportSize != *((glm::vec2*)&viewportPanelSize))
		{
			m_Fbo->Reseize(viewportPanelSize.x, viewportPanelSize.y);
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

			PROJECT->GetActiveScene()->OnReseize(viewportPanelSize.x, viewportPanelSize.y);
		}
		
		uint32_t textureID = m_Fbo->GetRendererID();
		ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();

		


		
	}


private:
	SceneState m_State;
	std::shared_ptr<Spirit::Render::Framebuffer> m_Fbo;
	glm::vec2 m_ViewportSize;
	bool m_ViewportFocused = false, m_ViewportHovered = false;


	Spirit::Entity m_Camera;
	Spirit::Entity m_Monkey;
	Spirit::SceneHierarchyPanel m_SceneHierarchyPanel;
	Spirit::PropertiesPanel m_PropertiesPanel;
	Spirit::FileExplorerPanel m_FileExplorerPanel;
};



class EditorApp : public Spirit::Application
{
public:
	EditorApp() : Spirit::Application("")
	{
		m_LayerStack.AddLayer(new EditorLayer());
	}

	~EditorApp()
	{

	}


	

};

Spirit::Application* Spirit::CreateApplication()
{
	return new EditorApp();
}