#pragma once

#include <fstream>
#include <glad/glad.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

using namespace std;

const unsigned int MAX_SHADER_SIZE = 5000;

class GLHandler
{
	struct Vertex
	{
		float x, y, z;
	};

	struct Object
	{
		int size;
		unsigned int VAO;
		unsigned int VBO;
		float* vertexPositionPointer;
		float* vertexColorPointer;

		void draw()
		{
			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertexPositionPointer, GL_STATIC_DRAW);
			glDrawArrays(GL_TRIANGLES, 0, size / 3);
		}
	};



	GLFWwindow* window;
	int shaderProgram;

	// settings
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	char vertexShaderSource[MAX_SHADER_SIZE];

	char fragmentShaderSource[MAX_SHADER_SIZE];

	vector<Object> objects;

	void processInput(GLFWwindow * window);

	void translateLeft();

	void translateRight();

	void translateUp();

	void translateDown();

	void translateDeep();

	void translateClose();

	static void framebuffer_size_callback(GLFWwindow * window, int width, int height);

	int initWindow();

	void readStringFromFile(char* filename, char* str);

	void initShaders();

	void render();

	void initObjects(vector<vector<float>>& initialObjects);

	void init(vector<vector<float>>& initialObjects);

public:
	
	void run(vector<vector<float>>& initialObjects);
};

