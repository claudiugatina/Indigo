#pragma once
#include "FluidObject.h"
class FluidTorus :
	public FluidObject
{
private:
public:
	float m_r;
	float m_R;
	int m_resolution_big;
	int m_resolution_small;
	glm::vec3 project(glm::vec3 position, float height = 0);
	glm::vec3 up(glm::vec3 position);
	FluidTorus(float r, float R, glm::vec3 color, int resolutionBig, int resolutionSmall);
	FluidTorus();
	virtual ~FluidTorus();
};

