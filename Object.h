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
	float scale;
	glm::mat4 transform;
	//GLuint VAO;
	//GLuint VBO;
	VertexAttribute* vertexAttribPointer;

	//Object() : position(0, 0, 0) {}

	Object(vector<float> rawFloats);

	void calcTransform();
	void draw();
};

