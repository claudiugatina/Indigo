#pragma once
#include "GLHandler.h"
#include "Camera.h"

class Drawable
{
public:
	virtual void draw(GLHandler & gl) = 0;
protected:
	unsigned int VAO;
	unsigned int VBO;
};

