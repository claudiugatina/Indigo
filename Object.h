#pragma once

#include "../glm/glm.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "VertexAttribute.h"
#include "Drawable.h"
#include <vector>

using namespace std;

class Object : public Drawable
{
public:
	Object();
	virtual ~Object();

	int size;
	glm::vec3 rotation;
	glm::vec3 position;
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, 1.0f);
	float scale;
	glm::mat4 transform;
	//GLuint VAO;
	//GLuint VBO;
	VertexAttribute* vertexAttribPointer;

	//Object() : position(0, 0, 0) {}

	Object(vector<float> rawFloats);

	glm::mat4& calcTransform();
	virtual void draw();

protected:
	virtual void pushSquare(vector<float>& res, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, glm::vec3 norm123, glm::vec3 norm234, glm::vec3 rgb);
};

