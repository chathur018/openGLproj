#include "vertexArray.h"

#include "vertexBufferLayout.h"
#include "renderer.h"

vertexArray::vertexArray()
{
	GLCall(glGenVertexArrays(1, &m_rendererID));
	GLCall(glBindVertexArray(m_rendererID));
}

vertexArray::~vertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_rendererID));
}

void vertexArray::addBuffer(const vertexBuffer& vb, const vertexBufferLayout& layout)
{
	bind();
	vb.bind();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;

	for(unsigned int i=0; i<elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset));
		offset += element.count * vertexBufferElement::getSizeOfType(element.type);
	}
}

void vertexArray::bind() const
{
	GLCall(glBindVertexArray(m_rendererID));
}

void vertexArray::unbind() const
{
	GLCall(glBindVertexArray(0));
}