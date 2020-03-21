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
	for (auto& object : objects)
	{
		object.position.x() -= 0.01;
	}
}

void GLHandler::translateRight()
{
	for (auto& object : objects)
	{
		object.position.x() += 0.01;
	}
}

void GLHandler::translateUp()
{
	for (auto& object : objects)
	{
		object.position.y() += 0.01;
	}
}

void GLHandler::translateDown()
{
	for (auto& object : objects)
	{
		object.position.y() -= 0.01;
	}
}

void GLHandler::translateDeep()
{
	for (auto& object : objects)
	{
		object.position.z() += 0.01;
	}
}

void GLHandler::translateClose()
{
	for (auto& object : objects)
	{
		object.position.z() -= 0.01;
	}
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

void GLHandler::render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glUseProgram(shaderProgram);

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*	GLint loc = glGetUniformLocation(shaderProgram, "rotMat");
		if (loc != -1)
		{
			glUniformMatrix3fv(loc, 1, GL_FALSE, rotMat);
		}

		loc = glGetUniformLocation(shaderProgram, "projMat");
		if (loc != -1)
		{
			glUniformMatrix4fv(loc, 1, GL_FALSE, projMat);
		}
		*/
		glm::mat4 view = glm::mat4(1.0f);
		// note that we're translating the scene in the reverse direction of where we want to move
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
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
	for (int i = 0; i < initialObjects.size(); ++i)
	{
		Object obj;
		obj.size = initialObjects[i].size();
		obj.vertexAttribPointer = new float[obj.size];
		for (int j = 0; j < initialObjects[i].size(); ++j)
			obj.vertexAttribPointer[j] = initialObjects[i][j];
		glGenVertexArrays(1, &obj.VAO);
		glGenBuffers(1, &obj.VBO);

		glBindVertexArray(obj.VAO);

		glBindBuffer(GL_ARRAY_BUFFER, obj.VBO);
		glBufferData(GL_ARRAY_BUFFER, obj.size * sizeof(float), obj.vertexAttribPointer, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		objects.push_back(obj);
	}

}

void GLHandler::init(vector<vector<float> >& initialObjects)
{
	initWindow();
	initShaders();
	initObjects(initialObjects);
}



void GLHandler::run(vector<vector<float> >& initialObjects)
{
	init(initialObjects);
	render();
}

