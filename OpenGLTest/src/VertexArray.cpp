#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Render.h"

VertexArray::VertexArray(){
	GLErrorCall(glGenVertexArrays(1, &m_ID));
}

VertexArray::~VertexArray() {
	GLErrorCall(glDeleteVertexArrays(1, &m_ID));
}


void VertexArray::Bind() const
{
	GLErrorCall(glBindVertexArray(m_ID));
}

void VertexArray::UnBind() const
{
	GLErrorCall(glBindVertexArray(0));
}


void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	// °ó¶¨bufferr
	vb.Bind();
	// set layout
	const auto& paras = layout.Getpara();
	unsigned int offset = 0;
	unsigned int stride = layout.GetStride();
	for (int i = 0; i < paras.size(); ++i) {
		const auto& para = paras[i];
		GLErrorCall(glVertexAttribPointer(i, para.cnt, para.type, para.is_normalized, stride, (void*)offset));
		GLErrorCall(glEnableVertexAttribArray(i));
		offset += para.cnt * Array_para::GetTypeSize(para.type);
	}



}
