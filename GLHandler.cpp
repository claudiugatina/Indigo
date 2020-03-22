#include "GLHandler.h"


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void GLHandler::processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		translateLeft();

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		translateRight();

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		translateUp();

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		translateDown();

	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		translateDeep();

	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		translateClose();

}

void GLHandler::translateLeft()
{
	m_camera.position().x += 0.1;
}

void GLHandler::translateRight()
{
	m_camera.position().x -= 0.1;
}

void GLHandler::translateUp()
{
	m_speed += 0.001;
	m_camera.position() += m_speed * glm::vec3(
		(sin(glm::radians(m_camera.rotation().y))),
		0.0f,
		//(-sin(glm::radians(m_camera.rotation().x))), 
		(-cos(glm::radians(m_camera.rotation().x)) * cos(glm::radians(m_camera.rotation().y))));
}

void GLHandler::translateDown()
{
	m_camera.position().z -= 0.1;
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

void GLHandler::initShaders()
{
	readStringFromFile("vertexShader.txt", vertexShaderSource);
	readStringFromFile("fragmentShader.txt", fragmentShaderSource);

	const GLchar* vertexShaderSourceLocal = vertexShaderSource;
	const GLchar* fragmentShaderSourceLocal = fragmentShaderSource;

	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSourceLocal, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSourceLocal, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// glDeleteShader(vertexShader);
	// glDeleteShader(fragmentShader);

}

void GLHandler::readStringFromFile(char* filename, char* str)
{
	fstream f(filename, ios::in);
	
	char c;
	string s;
	while (f >> noskipws >> c)
	{
		s += c;
	}
	
	strcpy_s(str, MAX_SHADER_SIZE, s.data());
}

Camera *cameraForCallback;
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	cameraForCallback->rotation().y = xpos / 20.0;
	cameraForCallback->rotation().x = ypos / 20.0;
	if (cameraForCallback->rotation().y > 360.0)
		cameraForCallback->rotation().y -= 360.0;
	if (cameraForCallback->rotation().x > 360.0)
		cameraForCallback->rotation().x -= 360.0;
	if (cameraForCallback->rotation().y < 0.0)
		cameraForCallback->rotation().y += 360.0;
	if (cameraForCallback->rotation().x < 0.0)
		cameraForCallback->rotation().x += 360.0;
}

void GLHandler::render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glUseProgram(shaderProgram);

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glEnable(GL_DEPTH_TEST);
	cameraForCallback = &m_camera;
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		unsigned int cameraPosLoc = glGetUniformLocation(shaderProgram, "cameraPos");
		glUniform3f(cameraPosLoc, m_camera.position().x, m_camera.position().y, m_camera.position().z);

		glm::mat4 view = glm::mat4(1.0f);
		// note that we're translating the scene in the reverse direction of where we want to move
		view = glm::rotate(view, glm::radians(m_camera.rotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::rotate(view, glm::radians(m_camera.rotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, -m_camera.position());
		unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		for (auto& obj : objects)
		{
			unsigned int transformLoc = glGetUniformLocation(shaderProgram, "model");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(obj.transform));
			obj.draw();
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
	int floatsPerAttrib = sizeof(VertexAttrib) / sizeof(float);
	for (int i = 0; i < initialObjects.size(); ++i)
	{
		Object obj;
		obj.size = initialObjects[i].size() / floatsPerAttrib;
		obj.vertexAttribPointer = new VertexAttrib[obj.size];
		memcpy(obj.vertexAttribPointer, &initialObjects[i][0], initialObjects[i].size() * sizeof(float));

		glGenVertexArrays(1, &obj.VAO);
		glGenBuffers(1, &obj.VBO);

		glBindVertexArray(obj.VAO);

		glBindBuffer(GL_ARRAY_BUFFER, obj.VBO);
		glBufferData(GL_ARRAY_BUFFER, obj.size * sizeof(VertexAttrib), obj.vertexAttribPointer, GL_STATIC_DRAW);

		// declared only for pointer arithmetic below
		VertexAttrib x;
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttrib), (void*)((int)&x.x - (int)&x));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttrib), (void*)((int)&x.r - (int)&x));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, sizeof(VertexAttrib), (void*)((int)&x.nx - (int)&x));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		objects.push_back(obj);
	}

}

void GLHandler::init(vector<vector<float> >& initialObjects)
{
	m_camera.position() = glm::vec3(0.0, 6.0, 0.0);
	m_speed = 0.1;
	initWindow();
	initShaders();
	initObjects(initialObjects);
}



void GLHandler::run(vector<vector<float> >& initialObjects)
{
	init(initialObjects);
	render();
}

