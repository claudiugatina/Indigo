#include "FluidObject.h"



FluidObject::FluidObject()
{
}


FluidObject::~FluidObject()
{
}

glm::mat4 & FluidObject::calcTransform()
{
	m_transform = glm::mat4(1.0f);
	m_transform = glm::translate(m_transform, m_position);
	return m_transform;
}

void FluidObject::init()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertexAttributes.size() * sizeof(FluidVertexAttribute), &m_vertexAttributes[0], GL_STATIC_DRAW);

	// declared only for pointer arithmetic below
	FluidVertexAttribute x;
	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(FluidVertexAttribute), (void*)((int)&x.m_pos - (int)&x));
	glEnableVertexAttribArray(0);

	// color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(FluidVertexAttribute), (void*)((int)&x.m_color - (int)&x));
	glEnableVertexAttribArray(1);

	// indices
	glGenBuffers(1, &EB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void FluidObject::draw()
{
	if (!visible)
		return;
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, (void*)0);
}
