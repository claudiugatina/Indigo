#pragma once
#include "Position.h"
#include "Rotation.h"
#include "Direction.h"

class Camera
{
public:
	Camera(Position position, Rotation rotation, Direction direction);
	Camera();
	~Camera();

	Position& position();
	Rotation& rotation();
	Direction& direction();

private:
	Position m_position;
	Rotation m_rotation;
	Direction m_direction;
};

