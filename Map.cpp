#include "Map.h"



void Map::init()
{
	initVertices();
	initGL();
}

void Map::initGL()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Position), &m_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Position), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Position), (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Map::initVertices()
{
	for (float z = -15.0; z <= 15.0; z += 0.5)
	{
		for (float x = -15; x <= 15.0; x += 0.5)
		{
			float y = float(rand() % 100) * 0.05;
			Position p(x, y, z);
			m_vertices.push_back(p);
		}
	}
}

void Map::draw(GLHandler & gl)
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), &m_vertices[0], GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
}

Map::Map()
{
}


Map::~Map()
{
}
