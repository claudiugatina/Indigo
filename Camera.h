#pragma once
#include "Position.h"
#include "Orientation.h"

class Camera
{
public:
	Position position();
	Orientation orientation();
	Camera();
	~Camera();
private:
	Position m_position;
	Orientation m_orientation;
};

