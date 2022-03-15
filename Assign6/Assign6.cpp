#include <iostream>
#include "Window.h"
#include "Shader.h"
#include "Mesh.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include<vector>
// Vertex Shader code
static const char* vShader = "Shaders/shader.vert";


// Fragment Shader
static const char* fShader = "Shaders/shader.frag";

//std::vector<Shader> shaderList;
Shader shader;
Mesh obj;


void CreateShader() {
	//Shader* shader = new Shader;
	shader.createFromFiles(vShader, fShader);
}



int main()


{
	GLfloat vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};
	GLuint indices[] = {  // note that we start from 0!
		0, 1,   // first line
		1, 2,    // second line
		2,3,
	};

	Window mainWindow = Window(800, 600);
	mainWindow.intitialise();
	CreateShader();
	//obj.CreateMesh(vertices, indices, 6);

	int maxPoints = 100;

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
		glClearColor(0.48f, 0.917f, 0.87f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.UseProgram();
		glBindVertexArray(VAO);


		//obj.RenderMesh();

		// Get + Handle user input events

		std::vector<glm::vec3> newVertices = mainWindow.getVertices();
		std::vector<int> newIndices = mainWindow.getIndices();
		//int indc[100] = {0};

		if (newVertices.size() > 1) {

		
			/*for (int i = 0; i < newIndices.size(); i++) {
				indc[i] = newIndices[i];
			
			}*/
			std::cout << sizeof(newVertices)<< " "<< newVertices.size() << " " << sizeof(newIndices)<< newIndices.size() << " " << "\n";
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(newVertices[0]) * newVertices.size(), newVertices.data());
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(newIndices[0]) * newIndices.size(), newIndices.data());

			//glDrawArrays(GL_LINES, 0, 3);


			glDrawElements(GL_LINES, newIndices.size(), GL_UNSIGNED_INT, 0);

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
