#pragma once

#include <string>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <iostream>

using namespace std;

class Shader
{
private:
	GLuint shaderIdentifier;
public:
	Shader();
	Shader(string sourceFileName);
	void compile(string & sourceCode);
	GLuint getIdentifier();
	void setShaderType(string extension);
	void readStringFromFile(string filename, string & filetext);
	virtual ~Shader();
};

