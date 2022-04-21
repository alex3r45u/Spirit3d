#pragma once

#include "Spirit/Render/VertexArray.h"

namespace Spirit::Render {
	class OpenGlVertexArray : public VertexArray {
	public:
		OpenGlVertexArray();
		virtual ~OpenGlVertexArray();
		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		virtual std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffer() const override { return m_VertexBuffers; }
		virtual std::shared_ptr<IndexBuffer> GetIndexBuffer() const override { return m_IndexBuffer; }
	private:
		unsigned int m_RendererID;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
}