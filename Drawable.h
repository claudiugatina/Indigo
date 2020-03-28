#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Drawable
{
public:
	virtual void draw() = 0;
	Drawable();
	~Drawable();
protected:
	bool visible;
	GLuint VAO;
	GLuint VBO;
};

