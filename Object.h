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

	glm::mat4& calcTransform();
	void init();
	virtual void draw();
	virtual glm::vec3 project(glm::vec3 position, float height = 0.0f) = 0;
	virtual glm::vec3 up(glm::vec3 position) = 0;
protected:
	vector<VertexAttribute> m_vertexAttributes;
	vector<unsigned int> m_indices;
};

