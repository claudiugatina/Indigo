#include "TorusShaderProgram.h"



TorusShaderProgram::TorusShaderProgram() : ShaderProgram("torusShaderProgram.sp")
{
}


TorusShaderProgram::~TorusShaderProgram()
{
}

void TorusShaderProgram::use(const glm::vec3 & cameraPos, const glm::mat4 & VP)
{
	ShaderProgram::use();
	setUniform3f(string("cameraPos"), cameraPos);

	for (auto& obj : objects)
	{
		setUniformMat4("MVP", VP * obj->calcTransform());
		// even though the position goes to the shaders through the MVP, the current solution is to give the position
		// to the geometry shader so that it can compute normals
		setUniformVec3("object_position", obj->m_position);
		setUniform1f("r", obj->m_r);
		setUniform1f("R", obj->m_R);
		setUniform1f("resolution_big", obj->m_resolution_big);
		setUniform1f("resolution_small", obj->m_resolution_small);
		obj->draw();
	}
}
