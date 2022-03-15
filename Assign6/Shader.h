#pragma once

#include <stdio.h>
#include <string.h>
#include <cmath>
#include<vector>
#include<fstream>
#include<iostream>
#include<string>

#include<glad/glad.h>
#include<GLFW/glfw3.h>
//#include <glm\glm.hpp>
//#include <glm\gtc\matrix_transform.hpp>
//#include <glm\gtc\type_ptr.hpp>

class Shader
{
public:
	Shader();
	void createFromString(const char* vertexCode, const char* fragmentCode);
	void createFromFiles(const char* vertexLocation, const char* fragmentLocation);

	std::string ReadFile(const char* fileLocation);

	GLuint GetColourLocation() { return uniformColour; };

	void UseProgram();
	void ClearShader();


	~Shader();
private:
	GLuint shaderID, uniformColour;

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);

};

