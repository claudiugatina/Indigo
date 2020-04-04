#include "RippleShaderProgram.h"



RippleShaderProgram::RippleShaderProgram() : ShaderProgram("wavesShaderProgram.sp")
{
}

RippleShaderProgram::~RippleShaderProgram()
{
}

void RippleShaderProgram::use(const glm::vec3 & cameraPos, float time, const glm::mat4 & VP)
{
	ShaderProgram::use();
	setUniform3f(string("cameraPos"), cameraPos);
	setUniform1f("time", time);
	for (auto& obj : objects)
	{
		setUniformMat4("MVP", VP * obj->calcTransform());
		// even though the position goes to the shaders through the MVP, the current solution is to give the position
		// to the geometry shader so that it can compute normals
		setUniformVec3("object_position", obj->m_position);
		obj->draw();
	}
}
