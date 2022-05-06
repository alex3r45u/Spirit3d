#include <Spirit.h>

class TestLayer : public Spirit::Layer {
public:
	TestLayer() : Layer("Test") {
	}

	virtual void OnAttach() override {
		m_Camera = std::make_shared<Spirit::Render::Camera>(glm::vec3(.0f, .0f, .0f), glm::vec3(0.0f, 0.0f, 0.0f));




		Spirit::AssetLibrary::s_MeshLibrary.Load("default", "assets/monkey.fbx");
		mat = std::make_shared<Spirit::Render::GeneratedMaterial>(glm::vec3(1.0f, .0f, .0f), glm::vec3(0.5f), glm::vec3(0.5f), 1.0f);

		Spirit::AssetLibrary::s_MaterialLibrary.Add("default", mat);
		Spirit::AssetLibrary::s_ShaderLibrary.Load("default", "assets/vertex.glsl", "assets/fragment.glsl");
		//m_Texture = Spirit::Render::Texture2d::Create("assets/dmark.jpg");
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
		Spirit::Render::RenderCommand::SetClearColor({ 0.1f, .1f, .1f, 1 });
		Spirit::Render::RenderCommand::Clear();

		Spirit::Render::Renderer::BeginScene(m_Camera);
		mat->SetUniforms(Spirit::AssetLibrary::s_ShaderLibrary.Get("default"));
		Spirit::AssetLibrary::s_MeshLibrary.Get("default")->Render(Spirit::AssetLibrary::s_ShaderLibrary.Get("default"));
		Spirit::Render::Renderer::EndScene();
	}



	void OnEvent(Spirit::Event& event) override {

	}
private:

	std::shared_ptr<Spirit::Render::Camera> m_Camera;
	std::shared_ptr<Spirit::Render::Material> mat;
};



class Sandbox : public Spirit::Application
{
public:
	Sandbox() : Spirit::Application()
	{
		m_LayerStack.AddLayer(new TestLayer());
	}

	~Sandbox()
	{

	}




};

Spirit::Application* Spirit::CreateApplication()
{
	return new Sandbox();
}