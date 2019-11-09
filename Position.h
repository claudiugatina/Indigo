#pragma once
class Position
{
public:
	float x();
	float y();
	float z();
	Position();
	~Position();
private:
	float m_x, m_y, m_z;
};

