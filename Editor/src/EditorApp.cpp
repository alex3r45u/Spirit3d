#include <Spirit.h>
#include <imgui/imgui.h>


class EditorLayer : public Spirit::Layer {
public:
	EditorLayer() : Layer("Editor") {
	}

	virtual void OnAttach() override {
		

		Spirit::AssetLibrary::s_MeshLibrary.Load("default", "assets/monkey.fbx");
		mat = std::make_shared<Spirit::Render::GeneratedMaterial>(glm::vec3(1.0f,.0f,.0f), glm::vec3(0.5f), glm::vec3(0.5f), 1.0f);
		Spirit::AssetLibrary::s_MaterialLibrary.Add("default", mat);
		Spirit::AssetLibrary::s_ShaderLibrary.Load("default", "assets/vertex.glsl", "assets/fragment.glsl");
		Spirit::Render::FramebufferSettings fbosettings;
		fbosettings.Width = 1280;
		fbosettings.Height = 720;
		m_Fbo = Spirit::Render::Framebuffer::Create(fbosettings);
		
		m_ActiveScene = std::make_shared<Spirit::Scene>();

		m_Camera = m_ActiveScene->CreateEntity("Cam");
		m_Camera.AddComponent<Spirit::PerspectiveCameraComponent>(Spirit::Render::PerspectiveCamera(1280, 720, 45.0f));
		
		m_Monkey = m_ActiveScene->CreateEntity("Monkey");
		m_Monkey.AddComponent<Spirit::MeshRendererComponent>("default");
		// 
		// 
		//m_Camera = std::make_shared<Spirit::Render::Camera>(glm::vec3(.0f, .0f, .0f), glm::vec3(0.0f, 0.0f, 0.0f));


	}

	virtual void LightUpdate() override {
		Spirit::Render::LightManager::Start(Spirit::AssetLibrary::s_ShaderLibrary.Get("default"));
		Spirit::Render::LightManager::Submit(std::make_shared<Spirit::Render::DirectionalLight>(glm::vec3(180.0f, .0f, .0f), glm::vec3(1.0f, 1.0f, 1.0f)));
		Spirit::Render::LightManager::End();
	}

	virtual void Update(Spirit::TimeStep ts) override {
		
		//if (m_ViewportHovered)
			//m_Camera->Update(ts);
		
		
	}

	void RenderUpdate(Spirit::TimeStep ts) override {
    	m_Fbo->Bind();
		Spirit::Render::RenderCommand::SetClearColor({ 0.1f, .1f, .1f, 1 });
		Spirit::Render::RenderCommand::Clear();

		m_ActiveScene->OnUpdate(ts);
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
			if (ImGui::BeginMenu("File"))
			{

				if (ImGui::MenuItem("Open")) {}
				if (ImGui::MenuItem("Save")) {}
				if (ImGui::MenuItem("Export")) {}
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}


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

			m_ActiveScene->OnReseize(viewportPanelSize.x, viewportPanelSize.y);
		}
		
		uint32_t textureID = m_Fbo->GetRendererID();
		ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();

		


		
	}


private:
	std::shared_ptr<Spirit::Render::Material> mat;
	std::shared_ptr<Spirit::Render::Framebuffer> m_Fbo;
	glm::vec2 m_ViewportSize;
	bool m_ViewportFocused = false, m_ViewportHovered = false;

	std::shared_ptr<Spirit::Scene> m_ActiveScene;

	Spirit::Entity m_Camera;
	Spirit::Entity m_Monkey;
};



class EditorApp : public Spirit::Application
{
public:
	EditorApp() : Spirit::Application()
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