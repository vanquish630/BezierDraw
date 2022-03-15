#pragma once

#include<stdio.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include<vector>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);


	int intitialise();


	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }

	bool* getsKeys() { return keys; }
	bool* getsClicks() { return clicks; }
	std::vector<glm::vec3> getVertices() { return vertices; }
	std::vector<int> getIndices() { return indices; }
	bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

	void swapBuffers() { glfwSwapBuffers(mainWindow); }


	~Window();

private:

	GLFWwindow* mainWindow;

	GLint width, height;
	GLint bufferWidth, bufferHeight;
	bool keys[1024];
	bool clicks[1024];
	std::vector<glm::vec3> vertices;
	std::vector<int> indices;
	void createCallbacks();
	static void keyboard_button_callback(GLFWwindow* window, int key, int code, int action, int mode); // static required for callback

	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

};

