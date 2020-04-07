#pragma once

#include "../glm/glm.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include <gtx/normal.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VertexAttribute
{
public:
	VertexAttribute();
	VertexAttribute(glm::vec3 pos, glm::vec3 color, glm::vec3 normal) : m_pos(pos), m_color(color), m_normal(normal) {}
	~VertexAttribute();

	glm::vec3 m_pos;
	glm::vec3 m_color;
	glm::vec3 m_normal;
};

const int floatsPerAttrib = sizeof(VertexAttribute) / sizeof(float);