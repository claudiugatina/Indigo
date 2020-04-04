#pragma once

#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include <../glm/gtc/quaternion.hpp>
#include <../glm/gtx/quaternion.hpp>
#include "Camera.h"
#include "ShaderProgram.h"
#include "Object.h"
#include "Sphere.h"
#include "ShaderProgram.h"
#include "StandardShaderProgram.h"
#include "RippleShaderProgram.h"
#include "Torus.h"

using namespace std;

const unsigned int MAX_SHADER_SIZE = 5000;
const float minDistancing = 2.0f;
const float maxDistancing = 70.0f;

class GLHandler
{
	float m_distancing = 5.0f;
	Camera m_camera;
	Object * m_map;
	Object * m_character;
	float m_speed;

	GLFWwindow* window;

	StandardShaderProgram * standardShader;
	RippleShaderProgram * rippleShader;

	// settings
	const unsigned int SCR_WIDTH = 1200;
	const unsigned int SCR_HEIGHT = 1000;

	glm::mat4 m_projectionMatrix;

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

