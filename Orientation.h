#pragma once

class Orientation
{
public:
	float roll();
	float pitch();
	float skew();
	Orientation();
	~Orientation();
private:
	// over z axis
	float m_roll;
	// over x axis
	float m_pitch;
	// over y axis
	float m_skew;
};

