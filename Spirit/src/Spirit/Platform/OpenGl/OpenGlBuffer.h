#pragma once
#include "Spirit/Render/Buffer.h"


namespace Spirit::Render {
	class OpenGlVertexBuffer : public VertexBuffer {
	public:
		OpenGlVertexBuffer(float* vertices, unsigned int size);
		virtual ~OpenGlVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
	private:
		unsigned int m_RendererID;
		BufferLayout m_Layout;
	};

	class OpenGlIndexBuffer : public IndexBuffer {
	public:
		OpenGlIndexBuffer(unsigned int* indices, unsigned int size);
		virtual ~OpenGlIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual unsigned int GetCount() const override { return m_Count; }
	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
	};
}