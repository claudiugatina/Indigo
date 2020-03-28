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
#include "ShaderProgram.h"
#include "Object.h"
#include "ShaderProgram.h"

using namespace std;

const unsigned int MAX_SHADER_SIZE = 5000;

// don't know why the compiler complains if I don't declare this here
class Object;

class GLHandler
{
	Camera m_camera;
	float m_speed;

	GLFWwindow* window;
	ShaderProgram* shaderProgram;

	// settings
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

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

	void initShaders();

	void render();

	void initObjects(vector<vector<float>>& initialObjects);

	void init(vector<vector<float>>& initialObjects);

public:
	
	void run(vector<vector<float>>& initialObjects);
};

