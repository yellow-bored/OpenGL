#include "IndexBuffer.h"
#include "Render.h"

IndexBuffer::IndexBuffer(unsigned int count, const unsigned int* data) :m_count(count)
{
	ASSERT(sizeof(unsigned) == sizeof(GLuint));
	GLErrorCall(glGenBuffers(1, &m_ID));
	GLErrorCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
	GLErrorCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GLErrorCall(glDeleteBuffers(1, &m_ID));
}

void IndexBuffer::Bind() const
{
	GLErrorCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
}

void IndexBuffer::UnBind() const
{
	GLErrorCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}


