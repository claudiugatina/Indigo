#pragma once
#include "Drawable.h"
#include "Position.h"

class Map :
	public Drawable
{
public:
	Map();
	~Map();
private:
	vector<Position> vertices;
	vector<int> triangulationIndices;
};

