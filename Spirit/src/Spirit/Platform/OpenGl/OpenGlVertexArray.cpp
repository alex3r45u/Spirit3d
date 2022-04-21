#include "sppch.h"
#include "OpenGlVertexArray.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>



static GLenum ShaderDataTypeToOpenGlBaseType(Spirit::Render::ShaderDataType type) {
	switch (type)
	{
	case Spirit::Render::Float:   return GL_FLOAT;
	case Spirit::Render::Float2:  return GL_FLOAT;
	case Spirit::Render::Float3:  return GL_FLOAT;
	case Spirit::Render::Float4:  return GL_FLOAT;
	case Spirit::Render::Mat3:    return GL_FLOAT;
	case Spirit::Render::Mat4:    return GL_FLOAT;
	case Spirit::Render::Int:     return GL_INT;
	case Spirit::Render::Int2:    return GL_INT;
	case Spirit::Render::Int3:    return GL_INT;
	case Spirit::Render::Int4:    return GL_INT;
	case Spirit::Render::Bool:    return GL_BOOL;
	}

	SP_CORE_ASSERT(false, "Unknown ShaderDataType");
	return 0;
}


Spirit::Render::OpenGlVertexArray::~OpenGlVertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

Spirit::Render::OpenGlVertexArray::OpenGlVertexArray()
{
	glCreateVertexArrays(1, &m_RendererID);
}

void Spirit::Render::OpenGlVertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void Spirit::Render::OpenGlVertexArray::UnBind() const
{
	glBindVertexArray(0);
}

void Spirit::Render::OpenGlVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
	glBindVertexArray(m_RendererID);
	vertexBuffer->Bind();
	unsigned int index = 0;
	const auto& layout = vertexBuffer->GetLayout();
	for (const auto& e : layout) {
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index,
			e.GetComponentCount(),
			ShaderDataTypeToOpenGlBaseType(e.Type),
			e.Normalized ? GL_TRUE : GL_FALSE,
			layout.GetStride(),
			(const void*)e.Offset);
		index++;
	}
	m_VertexBuffers.push_back(vertexBuffer);
}

void Spirit::Render::OpenGlVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
	glBindVertexArray(m_RendererID);
	indexBuffer->Bind();

	m_IndexBuffer = indexBuffer;
}
