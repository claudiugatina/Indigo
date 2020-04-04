#include "ShaderProgram.h"



ShaderProgram::ShaderProgram()
{
}

ShaderProgram::ShaderProgram(string shaderProgramFileName)
{
	fstream file(shaderProgramFileName.data(), ios::in);

	vector<string> shaderFileNames;
	string shaderFileName;
	while (file >> shaderFileName)
		shaderFileNames.push_back(shaderFileName);
	*this = ShaderProgram(shaderFileNames);

	file.close();
}

ShaderProgram::ShaderProgram(vector<string> shaderFileNames)
{
	shaderProgramIdentifier = glCreateProgram();
	for (string & shaderFileName : shaderFileNames)
	{
		// the shader gets its GL identifier in the constructor
		Shader shader(shaderFileName);
		glAttachShader(shaderProgramIdentifier, shader.getIdentifier());
	}
	linkShaders();
}

void ShaderProgram::linkShaders()
{
	glLinkProgram(shaderProgramIdentifier);

	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgramIdentifier, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramIdentifier, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	else
	{
		cout << "Linking successful\n";
	}
}

void ShaderProgram::setUniformVec3(string variableName, const glm::vec3 & value)
{
	// variableLocation will be set to -1 if the variable name isn't found in the program
	// we don't treat this case for efficiency
	GLuint variableLocation = glGetUniformLocation(shaderProgramIdentifier, variableName.data());
	glUniform3f(variableLocation, value.x, value.y, value.z);
}


void ShaderProgram::setUniformMat4(string variableName, const glm::mat4 & value)
{
	// variableLocation will be set to -1 if the variable name isn't found in the program
	// we don't treat this case for efficiency
	GLuint variableLocation = glGetUniformLocation(shaderProgramIdentifier, variableName.data());
	glUniformMatrix4fv(variableLocation, 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::setUniform1f(string variableName, float value)
{
	// variableLocation will be set to -1 if the variable name isn't found in the program
	// we don't treat this case for efficiency
	GLuint variableLocation = glGetUniformLocation(shaderProgramIdentifier, variableName.data());
	glUniform1f(variableLocation, value);
}

void ShaderProgram::setUniform3f(string variableName, const glm::vec3& value)
{
	// variableLocation will be set to -1 if the variable name isn't found in the program
	// we don't treat this case for efficiency
	GLuint variableLocation = glGetUniformLocation(shaderProgramIdentifier, variableName.data());
	glUniform3f(variableLocation, value.x, value.y, value.z);
}

void ShaderProgram::use()
{
	glUseProgram(shaderProgramIdentifier);	
}

ShaderProgram::~ShaderProgram()
{
}
