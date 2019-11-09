#pragma once
class Position
{
public:
	float x();
	float y();
	float z();
	Position operator-(Position &pos2);
	Position(float a, float b, float c);
	Position();
	~Position();
private:
	float m_x, m_y, m_z;
};

