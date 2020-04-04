#pragma once
#include "ShaderProgram.h"
#include "Object.h"

class RippleShaderProgram :
	public ShaderProgram
{
public:
	vector<Object*> objects;
	RippleShaderProgram();
	virtual ~RippleShaderProgram();
	void use(const glm::vec3 & cameraPos, float time, const glm::mat4 & VP);
};

