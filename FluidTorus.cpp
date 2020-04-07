#include "FluidTorus.h"



glm::vec3 FluidTorus::project(glm::vec3 position, float height)
{
	// get the relative position
	position -= m_position;
	glm::vec3 direction = glm::normalize(position);
	// project on the xz plane
	direction.y = 0.0f;
	glm::vec3 positionOnBigCircle = glm::normalize(direction) * m_R;
	glm::vec3 positionOnSmallCircle = positionOnBigCircle + glm::normalize(position - positionOnBigCircle) * (m_r + height);
	return positionOnSmallCircle;
}

glm::vec3 FluidTorus::up(glm::vec3 position)
{
	position -= m_position;
	glm::vec3 direction = glm::normalize(position);
	// project on the xz plane
	direction.y = 0.0f;
	glm::vec3 positionOnBigCircle = glm::normalize(direction) * m_R;
	return glm::normalize(position - positionOnBigCircle);
}

FluidTorus::FluidTorus(float r, float R, glm::vec3 color, int resolutionBig, int resolutionSmall) :
	m_r(r),
	m_R(R),
	m_resolution_big(resolutionBig),
	m_resolution_small(resolutionSmall)
{
	for (int i = 0; i < resolutionBig; ++i)
		for (int j = 0; j < resolutionSmall; ++j)
		{
			m_vertexAttributes.push_back(FluidVertexAttribute(glm::vec2(float(i), float(j)), color));
		}

	for (int i = 0; i < resolutionBig; ++i)
	{
		for (int j = 0; j < resolutionSmall; ++j)
		{
			unsigned int lu = i * resolutionBig + j;
			unsigned int ld = i * resolutionBig + (j + 1) % resolutionSmall;
			unsigned int ru = ((i + 1) % resolutionBig) * resolutionBig + j;
			unsigned int rd = ((i + 1) % resolutionBig) * resolutionBig + (j + 1) % resolutionSmall;

			m_indices.push_back(lu);
			m_indices.push_back(ld);
			m_indices.push_back(ru);

			m_indices.push_back(ld);
			m_indices.push_back(ru);
			m_indices.push_back(rd);
		}
	}

	init();
}

FluidTorus::FluidTorus()
{
}


FluidTorus::~FluidTorus()
{
}
