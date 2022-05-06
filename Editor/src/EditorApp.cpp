#include <Spirit.h>
#include <imgui/imgui.h>


class TestLayer : public Spirit::Layer {
public:
	TestLayer() : Layer("Test") {
	}

	virtual void OnAttach() override {
		m_Camera = std::make_shared<Spirit::Render::Camera>(glm::vec3(.0f, .0f, .0f), glm::vec3(0.0f, 0.0f, 0.0f));

		Spirit::AssetLibrary::s_MeshLibrary.Load("default", "assets/monkey.fbx");
		mat = std::make_shared<Spirit::Render::GeneratedMaterial>(glm::vec3(1.0f,.0f,.0f), glm::vec3(0.5f), glm::vec3(0.5f), 1.0f);
		Spirit::AssetLibrary::s_MaterialLibrary.Add("default", mat);
		Spirit::AssetLibrary::s_ShaderLibrary.Load("default", "assets/vertex.glsl", "assets/fragment.glsl");

		Spirit::Render::FramebufferSettings fbosettings;
		fbosettings.Width = 1280;
		fbosettings.Height = 720;
		m_Fbo = Spirit::Render::Framebuffer::Create(fbosettings);
	}

	virtual void LightUpdate() override {
		Spirit::Render::LightManager::Start(Spirit::AssetLibrary::s_ShaderLibrary.Get("default"));
		Spirit::Render::LightManager::Submit(std::make_shared<Spirit::Render::DirectionalLight>(glm::vec3(180.0f, .0f, .0f), glm::vec3(1.0f, 1.0f, 1.0f)));
		Spirit::Render::LightManager::End();
	}

	virtual void Update(Spirit::TimeStep ts) override {
		
		if (Spirit::Input::IsKeyPressed(SP_KEY_W)) {
			m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3(.10f, 0.0f, 0.0f));
		}
		if (Spirit::Input::IsKeyPressed(SP_KEY_S)) {
			m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3(-.10f, 0.0f, 0.0f));
		}
		if (Spirit::Input::IsKeyPressed(SP_KEY_D)) {
			m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3(.0f, 0.0f, .10f));
		}
		if (Spirit::Input::IsKeyPressed(SP_KEY_A)) {
			m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3(.0f, 0.0f, -.10f));
		}
		if (Spirit::Input::IsKeyPressed(SP_KEY_LEFT_SHIFT)) {
			m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3(.0f, -.10f, .0f));
		}
		if (Spirit::Input::IsKeyPressed(SP_KEY_SPACE)) {
			m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3(.0f, .10f, .0f));
		}
		//glm::vec3 camrot = m_Camera->GetRotation();
		//m_Camera->SetRotation(glm::vec3(camrot.x + Spirit::Input::GetMouseDx() * .1f, 0.0f, 0.0f));
		
	}

	void RenderUpdate() override {
    	m_Fbo->Bind();
		Spirit::Render::RenderCommand::SetClearColor({ 0.1f, .1f, .1f, 1 });
		Spirit::Render::RenderCommand::Clear();

		Spirit::Render::Renderer::BeginScene(m_Camera);
		mat->SetUniforms(Spirit::AssetLibrary::s_ShaderLibrary.Get("default"));
		Spirit::AssetLibrary::s_MeshLibrary.Get("default")->Render(Spirit::AssetLibrary::s_ShaderLibrary.Get("default"));
		Spirit::Render::Renderer::EndScene();
		m_Fbo->Unbind();
	}


	
	void OnEvent(Spirit::Event& event) override {
		
	}

	void ImGuiUpdate() override {
        static bool p_Open = true;
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &p_Open, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

		ImGui::Begin("Viewport");
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		if (m_ViewportSize != *((glm::vec2*)&viewportPanelSize))
		{
			m_Fbo->Reseize(viewportPanelSize.x, viewportPanelSize.y);
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

			m_Camera->SetViewport(viewportPanelSize.x, viewportPanelSize.y);
		}
		uint32_t textureID = m_Fbo->GetRendererID();
		ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();

        ImGui::End();

		
	}


private:

	std::shared_ptr<Spirit::Render::Camera> m_Camera;
	std::shared_ptr<Spirit::Render::Material> mat;
	std::shared_ptr<Spirit::Render::Framebuffer> m_Fbo;
	glm::vec2 m_ViewportSize;
};



class EditorApp : public Spirit::Application
{
public:
	EditorApp() : Spirit::Application()
	{
		m_LayerStack.AddLayer(new TestLayer());
	}

	~EditorApp()
	{

	}


	

};

Spirit::Application* Spirit::CreateApplication()
{
	return new EditorApp();
}