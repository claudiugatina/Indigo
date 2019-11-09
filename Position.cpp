#include "Position.h"



float Position::x()
{
	return m_x;
}

float Position::y()
{
	return m_y;
}

float Position::z()
{
	return m_z;
}

Position Position::operator-(Position & pos2)
{
	return Position(x() - pos2.x(), y() - pos2.y(), z() - pos2.z());
}

Position::Position(float a, float b, float c)
{
	m_x = a;
	m_y = b;
	m_z = c;
}

Position::Position()
{
}


Position::~Position()
{
}
