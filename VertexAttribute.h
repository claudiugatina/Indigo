#pragma once
class VertexAttribute
{
public:
	VertexAttribute();
	~VertexAttribute();

	float x, y, z;
	float r, g, b;
	float nx, ny, nz;
};

const int floatsPerAttrib = sizeof(VertexAttribute) / sizeof(float);