#include "VertexBuffer.h"
#include "Render.h"

VertexBuffer::VertexBuffer(unsigned int size, const void* data )
{
	GLErrorCall(glGenBuffers(1, &m_ID));
	GLErrorCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
	GLErrorCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));

}

VertexBuffer::~VertexBuffer()
{
	GLErrorCall(glDeleteBuffers(1, &m_ID));
}

void VertexBuffer::Bind() const
{
	GLErrorCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
}

void VertexBuffer::UnBind() const 
{
	GLErrorCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
