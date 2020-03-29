#include "Shader.h"



Shader::Shader()
{
}

Shader::Shader(string sourceFileName)
{
	string sourceCode;
	readStringFromFile(sourceFileName, sourceCode);

	string fileExtension;
	for (int i = sourceFileName.length() - 1; i >= 0 && sourceFileName[i] != '.'; --i)
		fileExtension += sourceFileName[i];

	// extension is reversed so far, we need to reverse it again to get the actual extension
	for (int i = 0; i < fileExtension.length() / 2; ++i)
		swap(fileExtension[i], fileExtension[fileExtension.length() - 1 - i]);
	
	setShaderType(fileExtension);

	cout << "Compiling " << sourceFileName << '\n';
	compile(sourceCode);
}

void Shader::compile(string & sourceCode)
{
	// glShaderSource takes a pointer to a char pointer as an argument, so we need to copy the pointer to the source code data into another lvalue
	const char* sourceCodeCharPtr = sourceCode.data();
	glShaderSource(shaderIdentifier, 1, &sourceCodeCharPtr, NULL);
	glCompileShader(shaderIdentifier);

	// check compile status
	int success;
	char infoLog[512];
	glGetShaderiv(shaderIdentifier, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderIdentifier, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	else
	{
		cout << "Successfully compiled\n";
	}
}

GLuint Shader::getIdentifier()
{
	return shaderIdentifier;
}

void Shader::setShaderType(string extension)
{
	if (extension == string("vs"))
	{
		shaderIdentifier = glCreateShader(GL_VERTEX_SHADER);
		return;
	}
	if (extension == string("fs"))
	{
		shaderIdentifier = glCreateShader(GL_FRAGMENT_SHADER);
		return;
	}
	if (extension == string("gs"))
	{
		shaderIdentifier = glCreateShader(GL_GEOMETRY_SHADER);
		return;
	}
	cout << "SHADER EXTENSION NOT RECOGNIZED\n";
}

void Shader::readStringFromFile(string filename, string& filetext)
{
	// reset file text to nothing
	filetext = "";
	fstream f(filename.data(), ios::in);

	char c;
	while (f >> noskipws >> c)
	{
		filetext += c;
	}
	f.close();
}

Shader::~Shader()
{
}
