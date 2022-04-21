
#include "sppch.h"
#include "OpenGlBuffer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>




Spirit::Render::OpenGlVertexBuffer::OpenGlVertexBuffer(float* vertices, unsigned int size)
{
	glCreateBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

Spirit::Render::OpenGlVertexBuffer::~OpenGlVertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void Spirit::Render::OpenGlVertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void Spirit::Render::OpenGlVertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


Spirit::Render::OpenGlIndexBuffer::OpenGlIndexBuffer(unsigned int* indices, unsigned int size)
{
	m_Count = size;

	glCreateBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

Spirit::Render::OpenGlIndexBuffer::~OpenGlIndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void Spirit::Render::OpenGlIndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void Spirit::Render::OpenGlIndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

