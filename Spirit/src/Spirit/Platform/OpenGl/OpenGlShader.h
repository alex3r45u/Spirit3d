#pragma once
#include "Spirit/Render/Shader.h"
#include <string>

namespace Spirit::Render {
	class OpenGlShader : public Shader {
	public:
		OpenGlShader(const std::string& name, const std::filesystem::path& vertPath, const std::filesystem::path& fragPath);
		virtual ~OpenGlShader();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual const std::string& GetName() override { return m_Name; }
		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetBool(const std::string& name, bool value) override;
		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetFloat2(const std::string& name, float value1, float value2) override;
		virtual void SetFloat3(const std::string& name, float value1, float value2, float value3) override;
		virtual void SetFloat4(const std::string& name, float value1, float value2, float value3, float value4) override;
		virtual void SetMat4(const std::string& name, glm::mat4 value) override;

	private:
		std::string ReadFile(const std::string& path);
	private:
		unsigned int m_RendererID;
		std::string m_Name;
	};
}