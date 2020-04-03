#include "GLHandler.h"


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void GLHandler::processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		moveLeft();

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		moveRight();

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		moveForward();

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		moveBackward();

	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		translateDeep();

	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		translateClose();

	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		sprint();
	m_camera.position() = 15.5f * glm::normalize(m_camera.position());
}

void GLHandler::sprint()
{
	m_speed = 1.0f;
}

void GLHandler::moveLeft()
{
	m_camera.position() -= m_speed * glm::normalize(glm::cross(m_camera.direction(), m_camera.position()));

	m_speed = 0.1f;
}

void GLHandler::moveRight()
{
	m_camera.position() += m_speed * glm::normalize(glm::cross(m_camera.direction(), m_camera.position()));

	m_speed = 0.1f;
}

void GLHandler::moveForward()
{
	// TODO: change direction also so that you don't have to keep moving the mouse down when moving forward
	m_camera.position() += m_speed * m_camera.direction();
	m_speed = 0.1f;
}

void GLHandler::moveBackward()
{
	m_camera.position() -= m_speed * m_camera.direction();
	m_speed = 0.1f;
}

void GLHandler::translateDeep()
{
	m_camera.rotation().x -= 0.1;
}

void GLHandler::translateClose()
{
	m_camera.rotation().x += 0.1;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void GLHandler::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


int GLHandler::initWindow()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, GLHandler::framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
}

// TODO: find a way to not have to use a global camera
Camera *cameraForCallback;

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	const float pi = 3.14159;
	static double x, y;
	glm::vec3& d = cameraForCallback->direction();
	glm::vec3& r = cameraForCallback->rotation();
	glm::vec3& u = cameraForCallback->up();
	glm::vec3& p = cameraForCallback->position();
	r.y += (xpos - x) / 200.0;
	u = glm::normalize(p);
	d = glm::normalize(d + float(xpos - x) / 2000.0f * glm::cross(d, p) - float(ypos - y) / 2000.0f * p);
	x = xpos;
	//r.x += (ypos - y) / 200.0;
	y = ypos;
	//if (r.y > 2 * pi)
	//	r.y -= 2 * pi;
	//if (r.y < -2 * pi)
	//	r.y += 2 * pi;
	//if (r.x > 1.5)
	//	r.x = 1.5;
	//if (r.x < -1.5)
	//	r.x = -1.5;
	
}

void GLHandler::initShaders()
{
	rippleShader.shaderProgram = new ShaderProgram("wavesShaderProgram.sp");

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	rippleShader.shaderProgram->use();

	m_projectionMatrix = glm::mat4(1.0f);
	m_projectionMatrix = glm::perspective(glm::radians(50.0f), 800.0f / 600.0f, 0.1f, 200.0f);

	glEnable(GL_DEPTH_TEST);
	cameraForCallback = &m_camera;
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// glDeleteShader(vertexShader);
	// glDeleteShader(fragmentShader);

	standardShader.shaderProgram = new ShaderProgram("standardShaderProgram.sp");

	standardShader.shaderProgram->use();

	glEnable(GL_DEPTH_TEST);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

extern float gety(float, float);

void GLHandler::render()
{
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		rippleShader.shaderProgram->use();
		rippleShader.shaderProgram->setUniform3f(string("cameraPos"), m_camera.position());
		rippleShader.shaderProgram->setUniform1f(string("time"), glfwGetTime());

		glm::mat4 view = glm::lookAt(m_camera.position(), m_camera.position() + m_camera.direction(), m_camera.position() + m_camera.up());

		glm::mat4 VP = m_projectionMatrix * view;

		for (auto& obj : rippleShader.objects)
		{
			rippleShader.shaderProgram->setUniformMat4("MVP", VP * obj->calcTransform());
			obj->draw();
		}

		standardShader.shaderProgram->use();
		standardShader.shaderProgram->setUniform3f(string("cameraPos"), m_camera.position());

		for (auto& obj : standardShader.objects)
		{
			standardShader.shaderProgram->setUniformMat4("MVP", VP * obj->calcTransform());
			obj->draw();
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();

		Sleep(10);
	}
	glfwTerminate();
}

void GLHandler::initObjects(vector<vector<float> >& initialObjects)
{
	// TODO: not hardcode this:
	//rippleShader.objects.push_back(new Object(initialObjects[0]));
	//standardShader.objects.push_back(new Object(initialObjects[1]));
	standardShader.objects.push_back(new Object(initialObjects[2]));
//	for (auto & rawVector : initialObjects)
//		objects.push_back(Object(rawVector));
}

void GLHandler::init(vector<vector<float> >& initialObjects)
{
	m_camera.position() = glm::vec3(0.0, 6.0, 0.0);
	m_speed = 0.2;
	initWindow();
	initShaders();
	initObjects(initialObjects);
}



void GLHandler::run(vector<vector<float> >& initialObjects)
{
	init(initialObjects);
	render();
}

