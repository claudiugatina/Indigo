#pragma once
#include "Object.h"
class Torus :
	public Object
{
	float m_r;
	float m_R;
	int m_resolution_big;
	int m_resolution_small;
public:
	glm::vec3 torPoint(int i, int j);
	glm::vec3 project(glm::vec3 position, float height = 0);
	glm::vec3 up(glm::vec3 position);
	Torus(float r, float R, glm::vec3 color, int resolutionBig, int resolutionSmall);
	virtual ~Torus();
};

