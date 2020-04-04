#include "Sphere.h"

glm::vec3 Sphere::spherePoint(int i, int j)
{
	float anglex = twoPi / float(m_resolution) * float(j);
	float angley = twoPi / float(m_resolution) * float(i);

	glm::vec3 res;

	res.x = m_radius * sin(anglex) * sin(angley);
	res.y = m_radius * cos(anglex);
	res.z = m_radius * sin(anglex) * cos(angley);

	return res;
}

vector<float> Sphere::generateSphere()
{
	vector<float> res;
	for (int i = 0; i < m_resolution; ++i)
	{
		for (int j = 0; j < m_resolution; ++j)
		{
			glm::vec3 p1 = spherePoint(i, j), p2 = spherePoint(i, j + 1), p3 = spherePoint(i + 1, j), p4 = spherePoint(i + 1, j + 1);
			glm::vec3 norm123 = glm::triangleNormal(p1, p2, p3);
			glm::vec3 norm234 = glm::triangleNormal(p2, p3, p4);

			pushSquare(res, p1, p2, p3, p4, norm123, norm234, m_color);

		}
	}
	return res;
}

glm::vec3 Sphere::project(glm::vec3 position, float height)
{
	return m_position + glm::normalize(position) * (m_radius + height);
}

glm::vec3 Sphere::up(glm::vec3 position)
{
	return position - m_position;
}

Sphere::Sphere(float radius, int resolution, glm::vec3 color) : m_radius(radius), m_resolution(resolution), m_color(color)
{
	m_direction = glm::vec3(0.0f, 0.0f, 1.0f);
	m_position = glm::vec3(0.0f);
	init(generateSphere());
}

Sphere::~Sphere()
{
}
