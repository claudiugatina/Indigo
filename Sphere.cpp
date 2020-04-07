#include "Sphere.h"

glm::vec3 Sphere::spherePoint(int i, int j)
{
	float angley = twoPi / float(m_resolution) * float(j);
	float anglex = pi / float(m_resolution) * float(i);

	glm::vec3 res;

	res.x = m_radius * sin(anglex) * sin(angley);
	res.y = m_radius * cos(anglex);
	res.z = m_radius * sin(anglex) * cos(angley);

	return res;
}

glm::vec3 Sphere::project(glm::vec3 position, float height)
{
	return m_position + glm::normalize(position) * (m_radius + height);
}

glm::vec3 Sphere::up(glm::vec3 position)
{
	return glm::normalize(position - m_position);
}

Sphere::Sphere(float radius, int resolution, glm::vec3 color) : m_radius(radius), m_resolution(resolution), m_color(color)
{
	m_direction = glm::vec3(0.0f, 0.0f, 1.0f);
	m_position = glm::vec3(0.0f);

	VertexAttribute top(glm::vec3(0.0f, m_radius, 0.0f), glm::vec3(m_color), glm::vec3(0.0f, 1.0f, 0.0f));

	m_vertexAttributes.push_back(top);

	for (int i = 1; i < m_resolution - 1; ++i)
	{
		for (int j = 0; j < m_resolution; ++j)
		{
			glm::vec3 pos = spherePoint(i, j);
			m_vertexAttributes.push_back(VertexAttribute(pos, m_color, glm::normalize(pos)));
		}
	}

	VertexAttribute bottom(glm::vec3(0.0f, -m_radius, 0.0f), m_color, glm::vec3(0.0f, -1.0f, 0.0f));

	m_vertexAttributes.push_back(bottom);

	// indices for triangles
	// top and bottom
	unsigned int last = m_vertexAttributes.size() - 1;
	for (int i = 1; i < m_resolution; ++i)
	{
		m_indices.push_back(0);
		m_indices.push_back(i);
		m_indices.push_back(i + 1);


		m_indices.push_back(last);
		m_indices.push_back(last - i);
		m_indices.push_back(last - i - 1);
	}
	m_indices.push_back(0);
	m_indices.push_back(1);
	m_indices.push_back(m_resolution);

	m_indices.push_back(last);
	m_indices.push_back(last - 1);
	m_indices.push_back(last - m_resolution);

	// rest of the sphere
	for (int i = 0; i < m_resolution - 2; ++i)
	{
		for (int j = 0; j < m_resolution - 1; ++j)
		{
			unsigned int lu = i * m_resolution + j + 1;
			unsigned int ld = (i + 1) * m_resolution + j + 1;
			unsigned int ru = i * m_resolution + j + 1 + 1;
			unsigned int rd = (i + 1) * m_resolution + j + 1 + 1;

			m_indices.push_back(lu);
			m_indices.push_back(ld);
			m_indices.push_back(ru); 
			
			m_indices.push_back(ld);
			m_indices.push_back(ru);
			m_indices.push_back(rd); 
		}
		unsigned int lu = (i + 1) * m_resolution;
		unsigned int ld = (i + 2) * m_resolution;
		unsigned int ru = i * m_resolution + 1;
		unsigned int rd = (i + 1) * m_resolution + 1;

		m_indices.push_back(lu);
		m_indices.push_back(ld);
		m_indices.push_back(ru);

		m_indices.push_back(ld);
		m_indices.push_back(ru);
		m_indices.push_back(rd);
	}
	init();
}

Sphere::~Sphere()
{
}
