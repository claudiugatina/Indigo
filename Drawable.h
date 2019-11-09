#pragma once
#include "GLHandler.h"
#include "Camera.h"

class Drawable
{
public:
	virtual void draw(GLHandler gl, Camera camera) = 0;
};

