#include "sppch.h"
#include "OpenGlRenderAPI.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Spirit::Render::OpenGlRenderAPI::SetClearColor(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void Spirit::Render::OpenGlRenderAPI::Init()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
}

void Spirit::Render::OpenGlRenderAPI::SetViewport(unsigned int width, unsigned int height)
{
	glViewport(0, 0, width, height);
}

void Spirit::Render::OpenGlRenderAPI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Spirit::Render::OpenGlRenderAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
{
	glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);
}
