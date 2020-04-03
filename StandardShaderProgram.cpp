#include "StandardShaderProgram.h"



StandardShaderProgram::StandardShaderProgram() : ShaderProgram("standardShaderProgram.sp")
{
}


StandardShaderProgram::~StandardShaderProgram()
{
}

void StandardShaderProgram::use(glm::vec3 & cameraPos, glm::mat4 & VP)
{
	ShaderProgram::use();
	setUniform3f(string("cameraPos"), cameraPos);
	for (auto& obj : objects)
	{
		setUniformMat4("MVP", VP * obj->calcTransform());
		obj->draw();
	}
}
