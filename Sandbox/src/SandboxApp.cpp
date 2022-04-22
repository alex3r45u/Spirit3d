#include <Spirit.h>

class TestLayer : public Spirit::Layer {
public:
	TestLayer() : Layer("Tsst") {
	}

	virtual void OnAttach() override {
		m_Camera = std::make_shared<Spirit::Render::Camera>(glm::vec3(.0f, .0f, .0f), glm::vec3(0.0f, 0.0f, 0.0f));


		m_VertexArray.reset(Spirit::Render::VertexArray::Create());

		float vertices[] = {
			// position  
			-0.5f, -0.5f, -0.5f,    
			 0.5f, -0.5f, -0.5f,    
			 0.5f,  0.5f, -0.5f,    
			 0.5f,  0.5f, -0.5f,    
			-0.5f,  0.5f, -0.5f,    
			-0.5f, -0.5f, -0.5f,    

			-0.5f, -0.5f,  0.5f,    
			 0.5f, -0.5f,  0.5f,    
			 0.5f,  0.5f,  0.5f,    
			 0.5f,  0.5f,  0.5f,    
			-0.5f,  0.5f,  0.5f,    
			-0.5f, -0.5f,  0.5f,    

			-0.5f,  0.5f,  0.5f,    
			-0.5f,  0.5f, -0.5f,    
			-0.5f, -0.5f, -0.5f,    
			-0.5f, -0.5f, -0.5f,    
			-0.5f, -0.5f,  0.5f,    
			-0.5f,  0.5f,  0.5f,    

			 0.5f,  0.5f,  0.5f,    
			 0.5f,  0.5f, -0.5f,    
			 0.5f, -0.5f, -0.5f,    
			 0.5f, -0.5f, -0.5f,    
			 0.5f, -0.5f,  0.5f,    
			 0.5f,  0.5f,  0.5f,    

			-0.5f, -0.5f, -0.5f,    
			 0.5f, -0.5f, -0.5f,    
			 0.5f, -0.5f,  0.5f,    
			 0.5f, -0.5f,  0.5f,    
			-0.5f, -0.5f,  0.5f,    
			-0.5f, -0.5f, -0.5f,    

			-0.5f,  0.5f, -0.5f,    
			 0.5f,  0.5f, -0.5f,    
			 0.5f,  0.5f,  0.5f,    
			 0.5f,  0.5f,  0.5f,    
			-0.5f,  0.5f,  0.5f,    
			-0.5f,  0.5f, -0.5f,    
		};

		std::shared_ptr<Spirit::Render::VertexBuffer> vertexBuffer;
		vertexBuffer = Spirit::Render::VertexBuffer::Create(vertices, sizeof(vertices));
		Spirit::Render::BufferLayout layout = {
			{ Spirit::Render::ShaderDataType::Float3, "a_Position" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[36];
		for (int i = 0; i < 36; i++) {
			indices[i] = i;
		}
		std::shared_ptr<Spirit::Render::IndexBuffer> indexBuffer;
		indexBuffer = Spirit::Render::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));
		m_VertexArray->SetIndexBuffer(indexBuffer);


		mesh = Spirit::Render::Mesh("assets/monkey.fbx");
		mat = std::make_shared<Spirit::Render::GeneratedMaterial>(glm::vec3(1.0f,.0f,.0f));
		
		Spirit::AssetLibrary::s_MaterialLibrary.Add("default", mat);
		Spirit::AssetLibrary::s_ShaderLibrary.Load("default", "assets/vertex.glsl", "assets/fragment.glsl");
		//m_Texture = Spirit::Render::Texture2d::Create("assets/dmark.jpg");
	}

	virtual void LightUpdate() override {
		Spirit::Render::LightManager::Start(Spirit::AssetLibrary::s_ShaderLibrary.Get("default"));
		Spirit::Render::LightManager::Submit(std::make_shared<Spirit::Render::DirectionalLight>(glm::vec3(0.0f), glm::vec3(.1f)));
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
		
	}

	void RenderUpdate() override {
		Spirit::Render::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Spirit::Render::RenderCommand::Clear();

		Spirit::Render::Renderer::BeginScene(m_Camera);
		//Spirit::Render::Renderer::Submit(m_VertexArray, m_ShaderLibrary.Get("default"), glm::mat4(1.0f));
		mat->SetUniforms(Spirit::AssetLibrary::s_ShaderLibrary.Get("default"));
		mesh.Render(Spirit::AssetLibrary::s_ShaderLibrary.Get("default"));
		Spirit::Render::Renderer::EndScene();
	}


	
	void OnEvent(Spirit::Event& event) override {
		
	}
private:
	std::shared_ptr<Spirit::Render::VertexArray> m_VertexArray;

	std::shared_ptr<Spirit::Render::Camera> m_Camera;
	std::shared_ptr<Spirit::Render::Material> mat;
	Spirit::Render::Mesh mesh;
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