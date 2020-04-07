#pragma once
#include "Drawable.h"
#include "FluidVertexAttribute.h"
#include <vector>



class FluidObject : public Drawable
{
public:
	FluidObject();
	virtual ~FluidObject();

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
	std::vector<FluidVertexAttribute> m_vertexAttributes;
	std::vector<unsigned int> m_indices;
};

