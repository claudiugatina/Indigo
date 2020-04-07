#include "Object.h"

Object::Object()
{
}


Object::~Object()
{
}

void Object::init()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertexAttributes.size() * sizeof(VertexAttribute), &m_vertexAttributes[0], GL_STATIC_DRAW);

	// declared only for pointer arithmetic below
	VertexAttribute x;
	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)((int)&x.m_pos - (int)&x));
	glEnableVertexAttribArray(0);

	// color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)((int)&x.m_color - (int)&x));
	glEnableVertexAttribArray(1);

	// normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, sizeof(VertexAttribute), (void*)((int)&x.m_normal - (int)&x));
	glEnableVertexAttribArray(2);

	// indices
	glGenBuffers(1, &elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

glm::mat4& Object::calcTransform()
{
	m_transform = glm::mat4(1.0f);
	m_transform = glm::translate(m_transform, m_position);
	return m_transform;
}

void Object::draw()
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// apparently the next line is not needed. This should speed things up for static objects
	//glBufferData(GL_ARRAY_BUFFER, size * sizeof(VertexAttribute), vertexAttribPointer, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, (void*)0);
}