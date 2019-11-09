#pragma once
#include "Position.h"
#include "Direction.h"
#include "Drawable.h"

class Triangle :
	public Drawable
{
public:
	Triangle();
	~Triangle();
	Triangle(Position *a, Position *b, Position *c);
	void draw(GLHandler& gl);
	void calcNormal();
private:
	Position* m_a;
	Position* m_b;
	Position* m_c;

	Direction m_normal;
};

