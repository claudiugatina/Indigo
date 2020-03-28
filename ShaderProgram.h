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
public:
	ShaderProgram();
	ShaderProgram(vector<string> shaderFileNames);
	void setUniformMat4(string variableName, glm::mat4 & value);
	void setUniform1f(string variableName, float value);
	void setUniform3f(string variableName, glm::vec3 value);
	void use();
	virtual ~ShaderProgram();
};

