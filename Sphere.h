#pragma once
#include "Object.h"
#include <vector>

class Sphere :
	public Object
{
private:
	float m_radius;
	int m_resolution;
	glm::vec3 m_color;
public:
	glm::vec3 spherePoint(int i, int j);
	vector<float> generateSphere();
	glm::vec3 project(glm::vec3 position, float height);
	glm::vec3 up(glm::vec3 position);
	Sphere(float radius, int resolution, glm::vec3 color);
	virtual ~Sphere();
};

