#include "sppch.h"
#include "OpenGlShader.h"
#include <filesystem>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Spirit/Core/File.h"

static void LogErrors(unsigned int shader) {
	char infoLog[512];
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		SP_CORE_ERROR("Shadercompilation failed {0}", infoLog);
	};
}

Spirit::Render::OpenGlShader::OpenGlShader(const std::string& name, const std::filesystem::path& vertPath, const std::filesystem::path& fragPath) : m_Name(name)
{

	std::string vertSrc = Spirit::File::Read(FileRegion::Ressource, vertPath);
	std::string fragSrc = Spirit::File::Read(FileRegion::Ressource, fragPath);
	unsigned int vertShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertSource = vertSrc.c_str();
	glShaderSource(vertShader, 1, &vertSource, 0);
	glCompileShader(vertShader);
	LogErrors(vertShader);

	unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragSource = fragSrc.c_str();
	glShaderSource(fragShader, 1, &fragSource, 0);
	glCompileShader(fragShader);
	LogErrors(fragShader);
	m_RendererID = glCreateProgram();

	glAttachShader(m_RendererID, vertShader);
	glAttachShader(m_RendererID, fragShader);

	glLinkProgram(m_RendererID);

	glDetachShader(m_RendererID, fragShader);
	glDetachShader(m_RendererID, vertShader);


}




Spirit::Render::OpenGlShader::~OpenGlShader()
{
	glDeleteProgram(m_RendererID);
}

void Spirit::Render::OpenGlShader::Bind()
{
	glUseProgram(m_RendererID);
}

void Spirit::Render::OpenGlShader::Unbind()
{
	glUseProgram(0);
}

void Spirit::Render::OpenGlShader::SetInt(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
}

void Spirit::Render::OpenGlShader::SetBool(const std::string& name, bool value)
{
	glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), (int)value);
}

void Spirit::Render::OpenGlShader::SetFloat(const std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(m_RendererID, name.c_str()), value);
}

void Spirit::Render::OpenGlShader::SetFloat2(const std::string& name, float value1, float value2)
{
	glUniform2f(glGetUniformLocation(m_RendererID, name.c_str()), value1, value2);
}

void Spirit::Render::OpenGlShader::SetFloat3(const std::string& name, float value1, float value2, float value3)
{
	glUniform3f(glGetUniformLocation(m_RendererID, name.c_str()), value1, value2, value3);
}

void Spirit::Render::OpenGlShader::SetFloat4(const std::string& name, float value1, float value2, float value3, float value4)
{
	glUniform4f(glGetUniformLocation(m_RendererID, name.c_str()), value1, value2, value3, value4);
}

void Spirit::Render::OpenGlShader::SetMat4(const std::string& name, glm::mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

