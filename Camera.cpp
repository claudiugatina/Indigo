#include "Camera.h"



Position & Camera::position()
{
	return m_position;
}

Rotation & Camera::rotation()
{
	return m_rotation;
}

Direction & Camera::direction()
{
	return m_direction;
}

Camera::Camera(Position position, Rotation rotation, Direction direction) : m_position(position), m_direction(direction), m_rotation(rotation)
{
}

Camera::Camera()
{
}


Camera::~Camera()
{
}
