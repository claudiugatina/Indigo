#pragma once
#include "Position.h"
#include "Rotation.h"
#include "Direction.h"
#include <glm.hpp>

class Camera
{
public:
//	Camera(Position position, Rotation rotation, Direction direction);
	Camera();
	~Camera();

	glm::vec3& position();
	glm::vec3& rotation();
	glm::vec3& direction();

private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_direction;
};

