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

void Object::pushSquare(vector<float>& res, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, glm::vec3 norm123, glm::vec3 norm234, glm::vec3 rgb)
{
	vector<float> toPush = {
		p1.x, p1.y, p1.z, rgb.x, rgb.y, rgb.z, norm123.x, norm123.y, norm123.z,
		p2.x, p2.y, p2.z, rgb.x, rgb.y, rgb.z, norm123.x, norm123.y, norm123.z,
		p3.x, p3.y, p3.z, rgb.x, rgb.y, rgb.z, norm123.x, norm123.y, norm123.z,

		p2.x, p2.y, p2.z, rgb.x, rgb.y, rgb.z, norm234.x, norm234.y, norm234.z,
		p3.x, p3.y, p3.z, rgb.x, rgb.y, rgb.z, norm234.x, norm234.y, norm234.z,
		p4.x, p4.y, p4.z, rgb.x, rgb.y, rgb.z, norm234.x, norm234.y, norm234.z,
	};

	res.insert(res.end(), toPush.begin(), toPush.end());
}

glm::mat4& Object::calcTransform()
{
	transform = glm::mat4(1.0f);
	transform = glm::translate(transform, position);
	return transform;
}

void Object::draw()
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// apparently the next line is not needed. This should speed things up for static objects
	//glBufferData(GL_ARRAY_BUFFER, size * sizeof(VertexAttribute), vertexAttribPointer, GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, size);
}