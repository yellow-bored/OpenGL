#pragma once
class VertexBuffer
{
private:
	unsigned int m_ID;
public:
	VertexBuffer(unsigned int size, const void* data);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;

};

