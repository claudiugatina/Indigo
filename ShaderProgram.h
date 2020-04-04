#pragma once
#include <vector>
#include <string>
#include "Shader.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/type_ptr.hpp"

using namespace std;

class ShaderProgram
{
private:
	GLuint shaderProgramIdentifier;

	void linkShaders();


protected:
	void setUniformVec3(string variableName, const glm::vec3 & value);
	void setUniformMat4(string variableName, const glm::mat4 & value);
	void setUniform1f(string variableName, float value);
	void setUniform3f(string variableName, const glm::vec3& value);

	virtual void use();
	
	ShaderProgram();
	ShaderProgram(string shaderProgramFileName);
	ShaderProgram(vector<string> shaderFileNames);
public:
	virtual ~ShaderProgram();
};

