#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>



namespace Spirit::Render {



	class Shader {
	public:
		Shader() {}
		virtual ~Shader() {}

		virtual void Bind() = 0;
		virtual void Unbind() = 0;


		static std::shared_ptr<Shader> Create(const std::string& name, const std::string& vertPath, const std::string& fragPath);

		virtual const std::string& GetName() = 0;
		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetBool(const std::string& name, bool value) = 0;
		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetFloat2(const std::string& name, float value1, float value2) = 0;
		virtual void SetFloat3(const std::string& name, float value1, float value2, float value3) = 0;
		virtual void SetFloat4(const std::string& name, float value1, float value2, float value3, float value4) = 0;
		virtual void SetMat4(const std::string& name, glm::mat4 value) = 0;
		
	};

	class ShaderLibrary {
	public:
		void Add(const std::string& name, const std::shared_ptr<Shader>& shader);
		void Add(const std::shared_ptr<Shader>& shader);
		std::shared_ptr<Shader> Load(const std::string& name, const std::string& vertPath, const std::string& fragPath);

		std::shared_ptr<Shader> Get(const std::string& name);

		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
	};
}