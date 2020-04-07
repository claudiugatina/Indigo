#pragma once
#include "../glm/glm.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include <gtx/normal.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class FluidVertexAttribute
{
public:
	// 3d position is computed by mapping the 2d position
	glm::vec2 m_pos;
	glm::vec3 m_color;
	// normal is computed on the spot
	FluidVertexAttribute();
	FluidVertexAttribute(glm::vec2 pos, glm::vec3 color) : m_pos(pos), m_color(color) {}
	~FluidVertexAttribute();
};

