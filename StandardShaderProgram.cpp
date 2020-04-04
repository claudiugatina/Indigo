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
		// even though the position goes to the shaders through the MVP, the current solution is to give the position
		// to the geometry shader so that it can compute normals
		setUniformVec3("object_position", obj->m_position);
		obj->draw();
	}
}
