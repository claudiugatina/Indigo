#include "Triangle.h"



Triangle::Triangle()
{
}


Triangle::~Triangle()
{
}

Triangle::Triangle(Position * a, Position * b, Position * c)
{
	m_a = a;
	m_b = b;
	m_c = c;
}

void Triangle::draw(GLHandler & gl)
{
	
}

void Triangle::calcNormal()
{
	Position V = *m_b - *m_a;
	Position W = *m_c - *m_a;

	m_normal = Direction(
		V.y() * W.z() - V.z() * W.y(),
		V.z() * W.x() - V.x() * W.z(),
		V.x() * W.y() - V.y() * W.x());
}
