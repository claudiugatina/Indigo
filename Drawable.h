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
	bool visible = true;
	GLuint VAO;
	GLuint VBO;
	// element buffer
	GLuint EB;
};

