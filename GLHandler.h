#pragma once

#include <fstream>
#include <glad/glad.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "Camera.h"

using namespace std;

const unsigned int MAX_SHADER_SIZE = 5000;

class GLHandler
{
	Camera m_camera;
	float m_speed;

	struct VertexAttrib
	{
		float x, y, z;
		float r, g, b;
		float nx, ny, nz;
	};

	struct Object
	{
		int size;
		Rotation rotation;
		Position position;
		float scale;
		glm::mat4 transform;
		GLuint VAO;
		GLuint VBO;
		VertexAttrib* vertexAttribPointer;

		Object() : position(0, 0, 0) {}

		void calcTransform()
		{
			transform = glm::mat4(1.0f);
			transform = glm::translate(transform, glm::vec3(position.x(), position.y(), position.z()));
		//	transform = glm::rotate(transform, glm::vec3(rotation.roll(), rotation.pitch(), rotation.skew()));
		}

		void draw()
		{
			calcTransform();
			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, size * sizeof(VertexAttrib), vertexAttribPointer, GL_STATIC_DRAW);
			glDrawArrays(GL_TRIANGLES, 0, size);
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

	void sprint();

	void moveLeft();

	void moveRight();

	void moveForward();

	void moveBackward();

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

