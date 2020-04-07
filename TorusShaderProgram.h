#pragma once
#include "ShaderProgram.h"
#include "FluidTorus.h"
class TorusShaderProgram :
	public ShaderProgram
{
public:
	vector<FluidTorus*> objects;
	TorusShaderProgram();
	virtual ~TorusShaderProgram();
	void use(const glm::vec3 & cameraPos, const glm::mat4 & VP);
};

