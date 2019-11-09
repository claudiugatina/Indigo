#pragma once
#include "Drawable.h"
#include "Position.h"
#include "Triangle.h"
#include <cstdlib>
#include "GLHandler.h"

class Map :
	public Drawable
{
public:
	void init();
	void initGL();
	void initVertices();
	void draw(GLHandler& gl);
	Map();
	~Map();
private:
	unsigned int VBO;
	unsigned int VAO;
	vector<Position> m_vertices;
	vector<unsigned short> m_indices;
	vector<Triangle> m_triangles;
};

