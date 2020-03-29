#include "Object.h"

Object::Object()
{
	int x;
}


Object::~Object()
{
}

Object::Object(vector<float> rawFloats)
{
	size = rawFloats.size() / floatsPerAttrib;
	vertexAttribPointer = new VertexAttribute[size];
	memcpy(vertexAttribPointer, &rawFloats[0], rawFloats.size() * sizeof(float));

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(VertexAttribute), vertexAttribPointer, GL_STATIC_DRAW);

	// declared only for pointer arithmetic below
	VertexAttribute x;
	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)((int)&x.x - (int)&x));
	glEnableVertexAttribArray(0);

	// color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)((int)&x.r - (int)&x));
	glEnableVertexAttribArray(1);

	// normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, sizeof(VertexAttribute), (void*)((int)&x.nx - (int)&x));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Object::calcTransform()
{
	transform = glm::mat4(1.0f);
	transform = glm::translate(transform, position);
}

void Object::draw()
{
	calcTransform();
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// apparently the next line is not needed. This should speed things up for static objects
	//glBufferData(GL_ARRAY_BUFFER, size * sizeof(VertexAttribute), vertexAttribPointer, GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, size);
}