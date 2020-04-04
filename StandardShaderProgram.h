#pragma once
#include "ShaderProgram.h"
#include "Object.h"

class StandardShaderProgram :
	public ShaderProgram
{
public:
	vector<Object*> objects;
	StandardShaderProgram();
	virtual ~StandardShaderProgram();
	// VP stands for view and projection
	void use(const glm::vec3 & cameraPos, const glm::mat4 & VP);
};

