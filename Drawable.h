#pragma once
#include "GLHandler.h"
#include "Camera.h"

class Drawable
{
	bool visible;
public:
	virtual void draw() = 0;
protected:
	unsigned int VAO;
	unsigned int VBO;
};

