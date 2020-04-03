#include "RippleShaderProgram.h"



RippleShaderProgram::RippleShaderProgram() : ShaderProgram("wavesShaderProgram.sp")
{
}

RippleShaderProgram::~RippleShaderProgram()
{
}

void RippleShaderProgram::use(glm::vec3 & cameraPos, float time, glm::mat4 & VP)
{
	ShaderProgram::use();
	setUniform3f(string("cameraPos"), cameraPos);
	setUniform1f("time", time);
	for (auto& obj : objects)
	{
		setUniformMat4("MVP", VP * obj->calcTransform());
		obj->draw();
	}
}
