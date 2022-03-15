#include <iostream>
#include<vector>

#include "Window.h"
#include "Shader.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>



// Vertex Shader code
static const char* vShader = "Shaders/shader.vert";


// Fragment Shader
static const char* fShader = "Shaders/shader.frag";

//std::vector<Shader> shaderList;
Shader shader;


void CreateShader() {
	shader.createFromFiles(vShader, fShader);
}



glm::vec3 decast(std::vector<glm::vec3> control , int r, float t, int i) {


	if (r == 0) {
		return control[i];
	}
	else {

		return (1 - t) * decast(control, r - 1,t, i) + t * decast(control, r - 1,t, i + 1);
	}

}


int main()


{
	
	Window mainWindow = Window(800, 600);
	mainWindow.intitialise();
	CreateShader();

	int maxPoints = 1000;

	GLuint VBO, VAO, EBO;
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, maxPoints*3*sizeof(GLfloat), (void*)0, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (maxPoints) *2* sizeof(GLuint), (void*)0, GL_DYNAMIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	int indx = 0;
	while (!mainWindow.getShouldClose())
	{

		
		// Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.UseProgram();
		glBindVertexArray(VAO);

		std::vector<glm::vec3> newVertices = mainWindow.getVertices();
		std::vector<int> newIndices = mainWindow.getIndices();
		std::vector<glm::vec3> bezierPoints;
		std::vector<int> bezierIndices;

		if (newVertices.size() > 1) {

			glUniform4f(shader.GetColourLocation(), 1.0f, 0.0f, 0.0f, 1.0f);

	
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(newVertices[0]) * newVertices.size(), newVertices.data());
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(newIndices[0]) * newIndices.size(), newIndices.data());


			glDrawElements(GL_LINES, newIndices.size(), GL_UNSIGNED_INT, 0);


			for (float t = 0.0f; t <= 1.0f; t += 0.05f) {
				
				glm::vec3 point;
				point = decast(newVertices, newVertices.size()-1, t, 0);
				bezierPoints.push_back(point);
				if (bezierPoints.size()>1) {
					bezierIndices.push_back(bezierPoints.size()-2);
					bezierIndices.push_back(bezierPoints.size() - 1);
				}
				//std::cout << point[0] << " " << point[1] << " " << point[2] << "\n";
					
			}
			bezierPoints.push_back(newVertices.back());
			bezierIndices.push_back(bezierPoints.size() - 2);
			bezierIndices.push_back(bezierPoints.size() - 1);

			glUniform4f(shader.GetColourLocation(), 0.0f, 1.0f, 0.0f, 1.0f);


			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bezierPoints[0]) * bezierPoints.size(), bezierPoints.data());
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(bezierIndices[0]) * bezierIndices.size(), bezierIndices.data());


			glDrawElements(GL_LINES, bezierIndices.size(), GL_UNSIGNED_INT, 0);


		}
		
		

	
		mainWindow.swapBuffers();
		glfwPollEvents();


	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	//obj.ClearMesh();
	shader.ClearShader();
	return 0;



}
