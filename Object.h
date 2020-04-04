#pragma once

#include "../glm/glm.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include <gtx/normal.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "VertexAttribute.h"
#include "Drawable.h"
#include <vector>

using namespace std;

const float pi = 3.14159265359f;
const float twoPi = 2.0f * pi;

class Object : public Drawable
{
public:
	Object();
	virtual ~Object();

	int size;
	glm::vec3 m_position;
	glm::vec3 m_direction = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	float m_scale;
	glm::mat4 m_transform;
	VertexAttribute* m_vertexAttribPointer;

	glm::mat4& calcTransform();
	void init(vector<float> rawFloats);
	virtual void draw();
	virtual glm::vec3 project(glm::vec3 position, float height = 0.0f) = 0;
	virtual glm::vec3 up(glm::vec3 position) = 0;
protected:
	virtual void pushSquare(vector<float>& res, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, glm::vec3 norm123, glm::vec3 norm234, glm::vec3 rgb);
};

