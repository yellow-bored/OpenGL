#pragma once

#include<vector>
#include<GL/glew.h>
#include"Render.h"


struct Array_para {
	unsigned int cnt;
	unsigned int type;
	unsigned char is_normalized;

	static unsigned GetTypeSize(unsigned int type) {
		switch (type) 
		{
			case GL_UNSIGNED_INT: return 4;
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
			default: ASSERT(false); break;
		}
	}
};

class VertexBufferLayout
{
public:
	VertexBufferLayout() :m_stride(0){};
	~VertexBufferLayout() {};
	inline const std::vector<Array_para> Getpara() const { return m_paras; };
	inline const unsigned int GetStride() const { return m_stride; };

	template<typename T>
	void Push(unsigned int count) {}

	template<>
	void Push<unsigned int>(unsigned int count) {
		m_paras.push_back({ count, GL_UNSIGNED_INT, GL_FALSE });
		m_stride += count * Array_para::GetTypeSize(GL_UNSIGNED_INT);
	}

	template<>
	void Push<float>(unsigned int count) {
		m_paras.push_back({ count, GL_FLOAT, GL_FALSE });
		m_stride += count * Array_para::GetTypeSize(GL_FLOAT);
	}

	template<>
	void Push<unsigned char>(unsigned int count) {
		m_paras.push_back({ count, GL_UNSIGNED_BYTE, GL_FALSE });
		m_stride += count * Array_para::GetTypeSize(GL_UNSIGNED_BYTE);
	}
private:
	std::vector<Array_para>  m_paras;
	unsigned int m_stride;






};

