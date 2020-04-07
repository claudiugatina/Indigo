#include "Torus.h"

glm::vec3 Torus::torPoint(int i, int j)
{
	glm::vec3 res;
	float angleBig = (twoPi / float(m_resolution_big)) * float(i);
	float xBig = sin(angleBig) * m_R;
	float yBig = 0.0f;
	float zBig = cos(angleBig) * m_R;

	float angleSmall = (twoPi / float(m_resolution_small)) * float(j);
	res.x = sin(angleBig) * (m_R + sin(angleSmall) * m_r);
	res.y = yBig + cos(angleSmall) * m_r;
	res.z = cos(angleBig) * (m_R + sin(angleSmall) * m_r);

	return res;
}

glm::vec3 Torus::project(glm::vec3 position, float height)
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

glm::vec3 Torus::up(glm::vec3 position)
{
	position -= m_position;
	glm::vec3 direction = glm::normalize(position);
	// project on the xz plane
	direction.y = 0.0f;
	glm::vec3 positionOnBigCircle = glm::normalize(direction) * m_R;
	return glm::normalize(position - positionOnBigCircle);
}

Torus::Torus(float r, float R, glm::vec3 color, int resolutionBig, int resolutionSmall) :
	m_r(r), 
	m_R(R), 
	m_resolution_big(resolutionBig),
	m_resolution_small(resolutionSmall)
{
	vector<float> torrus;

	for (int i = 0; i < resolutionBig; ++i)
	{

		for (int j = 0; j < resolutionSmall; ++j)
		{
			glm::vec3 p1 = torPoint(i, j), p2 = torPoint(i, j + 1), p3 = torPoint(i + 1, j), p4 = torPoint(i + 1, j + 1);
			glm::vec3 norm123 = glm::triangleNormal(p1, p2, p3);
			glm::vec3 norm234 = glm::triangleNormal(p2, p3, p4);

//			pushSquare(torrus, p1, p2, p3, p4, norm123, norm234, color);
		}
	}
//	init(torrus);
}


Torus::~Torus()
{
}
