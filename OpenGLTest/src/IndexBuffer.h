#pragma once
class IndexBuffer
{
private:
	unsigned int m_ID;
	unsigned int m_count;
public:
	IndexBuffer(unsigned int size, const unsigned int* data);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;
	inline unsigned int GetCount() const {
		return m_count;
	}
};


