#include "Camera.h"



glm::vec3 & Camera::position()
{
	return m_position;
}

glm::vec3 & Camera::rotation()
{
	return m_rotation;
}

glm::vec3 & Camera::direction()
{
	return m_direction;
}
glm::vec3 & Camera::up()
{
	return m_up;
}
//
//Camera::Camera(Position position, Rotation rotation, Direction direction) : m_position(position), m_direction(direction), m_rotation(rotation)
//{
//}

Camera::Camera()
{
}


Camera::~Camera()
{
}
