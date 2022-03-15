#include "Window.h"
#include <iostream>
Window::Window()
{
	width = 800;
	height = 600;
	
	for (size_t i = 0; i < 1024; i++) {
		keys[i] = 0;
		clicks[i] = 0;

	}
	
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	for (size_t i = 0; i < 1024; i++) {
		keys[i] = 0;
		clicks[i] = 0;
	}
	
}


int Window::intitialise() {

	// Initialise GLFW
	if (!glfwInit())
	{
		printf("GLFW initialisation failed!");
		glfwTerminate();
		return 1;
	}

	// Setup GLFW window properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core Profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow Forward Compatbility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the window
	mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);
	if (!mainWindow)
	{
		printf("GLFW window creation failed!");
		glfwTerminate();
		return 1;
	}

	// Get Buffer Size information
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	createCallbacks();
	

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	// Setup Viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);
	glfwSetWindowUserPointer(mainWindow, this); // to know which object called

	
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, keyboard_button_callback);
	glfwSetMouseButtonCallback(mainWindow, mouse_button_callback);
}

void Window::keyboard_button_callback(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	std::cout << key;


	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);

	}


	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			theWindow->keys[key] = true;
		}
		if (action == GLFW_RELEASE) {
			theWindow->keys[key] = false;

		}



	}

}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		GLdouble xpos, ypos;
		//getting cursor position
		glfwGetCursorPos(window, &xpos, &ypos);
		//std::cout << "Cursor Position at (" << xpos << " : " << ypos << "\n";

		int width, height;
		glfwGetWindowSize(window, &width, &height);
		float x = -1.0f + 2 * xpos / width;
		float y = +1.0f - 2 * ypos / height;
		glm::vec3 newPoint = glm::vec3(x, y, 0.0f);
		std::cout << "X: " << x << std::endl;
		std::cout << "Y: " << y << std::endl;
		//Store vector point into vector array
		theWindow->vertices.push_back(newPoint);

		int verticeSize = theWindow->vertices.size();
		if (verticeSize>1) {
			theWindow->indices.push_back(verticeSize - 2);
			theWindow->indices.push_back(verticeSize-1);
		}
		
		std::cout << verticeSize <<" " << theWindow->indices.size() << std::endl;

	}


	/*if (button >= 0 && button < 1024) {
		if (action == GLFW_PRESS) {
			theWindow->clicks[button] = true;
		}
		if (action == GLFW_RELEASE) {
			theWindow->clicks[button] = false;

		}


	}*/
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}

