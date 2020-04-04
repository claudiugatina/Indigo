#include "StandardShaderProgram.h"



StandardShaderProgram::StandardShaderProgram() : ShaderProgram("standardShaderProgram.sp")
{
}


StandardShaderProgram::~StandardShaderProgram()
{
}

void StandardShaderProgram::use(const glm::vec3 & cameraPos, const glm::mat4 & VP)
{
	ShaderProgram::use();
	setUniform3f(string("cameraPos"), cameraPos);
	for (auto& obj : objects)
	{
		setUniformMat4("MVP", VP * obj->calcTransform());
		obj->draw();
	}
}
